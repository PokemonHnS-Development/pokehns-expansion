#!/usr/bin/env python3
"""Live hnsrun session for exploration, driven over a Unix socket.

  sess.py serve ROM OUTDIR SAVE [--clip] [--src SRC]   start the runner, listen on OUTDIR/sess.sock
  sess.py send OUTDIR < script                          run tour-language lines, print the output

Lines are the hns.py/r3bf.py tour language. A line `py: CODE` runs Python with `emu`, `hns`.
The session never exits on an error; it prints the error and keeps the game where it stopped.
"""
import io
import os
import socket
import sys
import tempfile
import traceback
import contextlib

EMU = "tools/hebrew/emu"
sys.path.insert(0, EMU)
sys.path.insert(0, os.path.join(EMU, "scripts", "r3_frontier"))
sys.path.insert(0, os.path.join(EMU, "scripts", "r2_safari_pokeblock_bug_contest"))
sys.path.insert(0, os.path.join(EMU, "scripts", "r2_battle_frontier_facilities"))
sys.path.insert(0, os.path.join(EMU, "scripts", "r2_bfpass"))


SOCKDIR = os.environ.get("SESS_SOCKDIR", tempfile.gettempdir())


def sockpath(outdir):
    return os.path.join(SOCKDIR, os.path.basename(os.path.abspath(outdir)) + ".sock")


def serve(rom, outdir, save, clip):
    import hns
    import r3bf  # noqa: F401  registers drive/pick/vars and the r2 ops
    try:
        import bffops  # noqa: F401  ops for this round
    except ImportError as e:
        print("no bffops: %s" % e)
    import bfpops  # noqa: F401  ops for this group
    outdir = os.path.abspath(outdir)
    os.makedirs(outdir, exist_ok=True)
    emu = hns.Emu(rom, None, outdir, save)
    if clip:
        hns.clip_hook(emu, outdir)
    sock_path = sockpath(outdir)
    if os.path.exists(sock_path):
        os.remove(sock_path)
    srv = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    srv.bind(sock_path)
    srv.listen(1)
    print("serving on %s" % sock_path, flush=True)
    g = {"emu": emu, "hns": hns}
    n = 0
    while True:
        conn, _ = srv.accept()
        data = b""
        while True:
            chunk = conn.recv(65536)
            if not chunk:
                break
            data += chunk
            if data.endswith(b"\n\x04\n"):
                data = data[:-3]
                break
        text = data.decode("utf-8")
        buf = io.StringIO()
        quit_after = False
        with contextlib.redirect_stdout(buf):
            try:
                py, rest = [], []
                for line in text.splitlines():
                    if line.strip() == "quit":
                        quit_after = True
                        break
                    if line.startswith("py:"):
                        if rest:
                            n += 1
                            p = os.path.join(outdir, "_cmd%04d.txt" % n)
                            open(p, "w").write("\n".join(rest) + "\n")
                            rest = []
                            emu.run_script(p)
                        exec(line[3:].strip(), g)
                    else:
                        rest.append(line)
                if rest:
                    n += 1
                    p = os.path.join(outdir, "_cmd%04d.txt" % n)
                    open(p, "w").write("\n".join(rest) + "\n")
                    emu.run_script(p)
                print("OK @%d" % emu.sync())
            except Exception as e:
                print("ERROR %s: %s" % (type(e).__name__, e))
                traceback.print_exc(file=buf)
                try:
                    print("  cb2 %s tasks %s" % (emu.cb2_name(), [t[2] for t in emu.tasks()]))
                except Exception:
                    pass
        out = buf.getvalue()
        conn.sendall(out.encode("utf-8"))
        conn.close()
        with open(os.path.join(outdir, "sess.log"), "a") as fh:
            fh.write(">>> " + text.replace("\n", "\n>>> ") + "\n" + out)
        if quit_after:
            emu.close()
            break


def send(outdir):
    text = sys.stdin.read()
    s = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    s.connect(sockpath(outdir))
    s.sendall(text.encode("utf-8") + b"\n\x04\n")
    out = b""
    while True:
        c = s.recv(65536)
        if not c:
            break
        out += c
    sys.stdout.write(out.decode("utf-8"))


if __name__ == "__main__":
    a = sys.argv[1:]
    if a[0] == "serve":
        serve(a[1], a[2], a[3] if len(a) > 3 and not a[3].startswith("--") else None, "--clip" in a)
    elif a[0] == "send":
        send(a[1])
