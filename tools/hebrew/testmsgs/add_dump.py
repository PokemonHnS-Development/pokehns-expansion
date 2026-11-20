"""Add a temporary message dump to a tree's test runner (test/test_runner_battle.c).

  add_dump.py TREE

Every battle message the game records during `make check` is printed as MSGT/MSGH/MSGE lines
(test name, hex bytes). Never commit it: restore the file with git checkout afterwards.
"""
import sys
p=sys.argv[1]+'/test/test_runner_battle.c'; s=open(p,encoding='utf-8').read()
if 'HNSDUMP' in s: print('already'); sys.exit()
old='''void TestRunner_Battle_RecordMessage(const u8 *string)
{
    s32 queuedEvent;
    s32 match;
    struct QueuedEvent *event;
'''
new='''static void HnsDumpMessage(const u8 *string) // HNSDUMP
{
    static const char hex[] = "0123456789ABCDEF";
    char buf[121];
    u32 n = 0;
    Test_MgbaPrintf("MSGT|%d|%s", STATE->runParameter, gTestRunnerState.test->name);
    while (*string != EOS)
    {
        buf[n++] = hex[*string >> 4];
        buf[n++] = hex[*string & 0xF];
        string++;
        if (n == 120)
        {
            buf[n] = 0;
            Test_MgbaPrintf("MSGH|%s", buf);
            n = 0;
        }
    }
    buf[n] = 0;
    Test_MgbaPrintf("MSGH|%s", buf);
    Test_MgbaPrintf("MSGE|");
}

void TestRunner_Battle_RecordMessage(const u8 *string)
{
    s32 queuedEvent;
    s32 match;
    struct QueuedEvent *event;

    HnsDumpMessage(string);
'''
assert s.count(old)==1; s=s.replace(old,new); open(p,'w',encoding='utf-8').write(s); print('patched',p)
