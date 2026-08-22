	.include "asm/macros.inc"

	.section .rodata
	.align 1

@ Converted from mus_lilycove_museum.mid
@ BPM: 68  |  MIDI ticks/beat: 24  |  GBS unit: 6 ticks
@ Tick grid: 1 GBS unit = 6 MIDI ticks = 12 frames (tempo 282)

@ ────────────────────────────────────────────────────────────
@ Ch1: Square 1
@ ────────────────────────────────────────────────────────────

gbs_mus_lilycove_museum_Ch1:
	gbs_switch 0
	tempo 282
	volume 7, 7
	duty_cycle 2
	stereo_panning FALSE, TRUE
	vibrato 16, 0, 4
	note_type 12, 11, 3

gbs_mus_lilycove_museum_Ch1.mainloop:
	octave 3
	note D_, 4
	note G_, 2
	note D_, 2
	note A_, 2
	note D_, 2
	note B_, 2
	octave 4
	note C_, 2
	octave 3
	note B_, 2
	note G_, 2
	volume_envelope 10, 3
	note Fs, 1
	note Fs, 1
	note G_, 1
	volume_envelope 11, 3
	note E_, 1
	note Fs, 2
	note C_, 2
	note Fs, 2
	note G_, 2
	note A_, 2
	note Fs, 2
	note G_, 2
	note E_, 2
	note B_, 2
	note G_, 2
	octave 4
	note E_, 2
	octave 3
	note B_, 2
	octave 4
	note G_, 2
	note E_, 2
	volume_envelope 10, 3
	note Fs, 1
	note Fs, 1
	note G_, 1
	volume_envelope 11, 3
	note E_, 1
	note Fs, 2
	note G_, 2
	volume_envelope 10, 3
	note A_, 2
	volume_envelope 11, 3
	note Fs, 2
	note D_, 2
	note C_, 2
	octave 3
	note G_, 2
	note D_, 2
	note A_, 2
	note D_, 2
	note B_, 2
	octave 4
	note C_, 2
	octave 3
	note B_, 2
	note G_, 2
	volume_envelope 10, 3
	note Fs, 1
	note Fs, 1
	note G_, 1
	volume_envelope 11, 3
	note E_, 1
	note Fs, 2
	note C_, 2
	note Fs, 2
	note G_, 2
	note A_, 2
	note Fs, 2
	note G_, 2
	note E_, 2
	note B_, 2
	note G_, 2
	octave 4
	note E_, 2
	octave 3
	note B_, 2
	octave 4
	note G_, 2
	note E_, 2
	volume_envelope 10, 3
	note Fs, 1
	note Fs, 1
	note G_, 1
	volume_envelope 11, 3
	note E_, 1
	note Fs, 2
	note G_, 2
	volume_envelope 10, 3
	note A_, 2
	volume_envelope 11, 3
	note Fs, 2
	note D_, 2
	volume_envelope 9, 3
	octave 5
	note C_, 2
	volume_envelope 5, 3
	octave 4
	note B_, 1
	volume_envelope 1, 3
	note B_, 1
	volume_envelope 5, 3
	note G_, 1
	volume_envelope 1, 3
	note G_, 1
	volume_envelope 5, 3
	note B_, 1
	volume_envelope 1, 3
	note B_, 1
	volume_envelope 5, 3
	note D_, 1
	volume_envelope 1, 3
	note D_, 1
	volume_envelope 5, 3
	note B_, 1
	volume_envelope 1, 3
	note B_, 1
	volume_envelope 5, 3
	note G_, 1
	volume_envelope 1, 3
	note G_, 1
	volume_envelope 5, 3
	note B_, 1
	volume_envelope 1, 3
	note B_, 1
	volume_envelope 5, 3
	note D_, 1
	volume_envelope 1, 3
	note D_, 1
	volume_envelope 5, 3
	octave 5
	note C_, 1
	volume_envelope 1, 3
	note C_, 1
	volume_envelope 5, 3
	octave 4
	note G_, 1
	volume_envelope 1, 3
	note G_, 1
	volume_envelope 5, 3
	octave 5
	note C_, 1
	volume_envelope 1, 3
	note C_, 1
	volume_envelope 5, 3
	octave 4
	note E_, 1
	volume_envelope 1, 3
	note E_, 1
	volume_envelope 5, 3
	octave 5
	note C_, 1
	volume_envelope 1, 3
	note C_, 1
	volume_envelope 5, 3
	octave 4
	note G_, 1
	volume_envelope 1, 3
	note G_, 1
	volume_envelope 5, 3
	octave 5
	note C_, 1
	volume_envelope 1, 3
	note C_, 1
	volume_envelope 5, 3
	octave 4
	note E_, 1
	volume_envelope 1, 3
	note E_, 1
	volume_envelope 5, 3
	octave 5
	note Cs, 1
	volume_envelope 1, 3
	note Cs, 1
	volume_envelope 5, 3
	octave 4
	note G_, 1
	volume_envelope 1, 3
	note G_, 1
	volume_envelope 5, 3
	octave 5
	note Cs, 1
	volume_envelope 1, 3
	note Cs, 1
	volume_envelope 5, 3
	octave 4
	note E_, 1
	volume_envelope 1, 3
	note E_, 1
	volume_envelope 5, 3
	octave 5
	note Cs, 1
	volume_envelope 1, 3
	note Cs, 1
	volume_envelope 5, 3
	octave 4
	note G_, 1
	volume_envelope 1, 3
	note G_, 1
	volume_envelope 5, 3
	octave 5
	note Cs, 1
	volume_envelope 1, 3
	note Cs, 1
	volume_envelope 5, 3
	octave 4
	note E_, 1
	volume_envelope 1, 3
	note E_, 1
	volume_envelope 5, 3
	octave 5
	note D_, 1
	octave 4
	note A_, 1
	octave 5
	note C_, 1
	octave 4
	note B_, 1
	note A_, 1
	rest 1
	note D_, 2
	note Fs, 2
	note G_, 2
	note A_, 4
	volume_envelope 11, 3
	octave 2
	note G_, 7
	rest 1
	note D_, 7
	rest 1
	note Fs, 7
	rest 1
	note C_, 7
	rest 1
	note E_, 7
	rest 1
	octave 1
	note B_, 8
	octave 2
	note D_, 8
	volume_envelope 9, 3
	octave 3
	note C_, 2
	note D_, 2
	note E_, 2
	note Fs, 2
	volume_envelope 10, 3
	note G_, 2
	note D_, 2
	note A_, 2
	note D_, 2
	note B_, 2
	octave 4
	note C_, 2
	octave 3
	note B_, 2
	note G_, 2
	volume_envelope 9, 3
	note Fs, 1
	note Fs, 1
	note G_, 1
	volume_envelope 10, 3
	note E_, 1
	note Fs, 2
	note C_, 2
	note Fs, 2
	note G_, 2
	note A_, 2
	note Fs, 2
	note G_, 2
	note E_, 2
	note B_, 2
	note G_, 2
	octave 4
	note E_, 2
	octave 3
	note B_, 2
	octave 4
	note G_, 2
	note E_, 2
	volume_envelope 9, 3
	note Fs, 1
	note Fs, 1
	note G_, 1
	volume_envelope 10, 3
	note E_, 1
	note Fs, 2
	note G_, 2
	volume_envelope 9, 3
	note A_, 2
	volume_envelope 10, 3
	note Fs, 2
	note D_, 2
	note C_, 2
	octave 3
	note G_, 2
	note D_, 2
	note A_, 2
	note D_, 2
	note B_, 2
	octave 4
	note C_, 2
	octave 3
	note B_, 2
	note G_, 2
	volume_envelope 9, 3
	note Fs, 1
	note Fs, 1
	note G_, 1
	volume_envelope 10, 3
	note E_, 1
	note Fs, 2
	note G_, 2
	note A_, 2
	note B_, 2
	octave 4
	note C_, 2
	octave 3
	note Fs, 2
	note G_, 2
	note E_, 2
	note B_, 2
	note G_, 2
	octave 4
	note D_, 2
	note C_, 2
	octave 3
	note B_, 2
	octave 4
	note C_, 2
	octave 3
	note A_, 7
	rest 1
	note Fs, 4
	note G_, 2
	note Fs, 2
	note G_, 11
	rest 1
	note D_, 4

	sound_loop 0, gbs_mus_lilycove_museum_Ch1.mainloop

@ ────────────────────────────────────────────────────────────
@ Ch2: Square 2
@ ────────────────────────────────────────────────────────────

gbs_mus_lilycove_museum_Ch2:
	gbs_switch 1
	duty_cycle 2
	stereo_panning TRUE, FALSE
	vibrato 16, 0, 4
	note_type 12, 12, 3

gbs_mus_lilycove_museum_Ch2.mainloop:
	rest 4
	octave 2
	note B_, 8
	rest 2
	note G_, 2
	octave 3
	note D_, 2
	octave 2
	note B_, 2
	note A_, 8
	octave 3
	note C_, 2
	octave 2
	note B_, 2
	note A_, 2
	note Fs, 2
	note G_, 8
	octave 3
	note G_, 2
	note E_, 2
	note B_, 2
	note G_, 2
	note A_, 8
	note C_, 4
	octave 2
	note Fs, 2
	octave 3
	note C_, 2
	octave 2
	note B_, 8
	rest 2
	note G_, 2
	octave 3
	note D_, 2
	octave 2
	note B_, 2
	note A_, 8
	octave 3
	note C_, 2
	octave 2
	note B_, 2
	note A_, 2
	note Fs, 2
	note G_, 8
	octave 3
	note G_, 2
	note E_, 2
	note B_, 2
	note G_, 2
	note A_, 8
	note Fs, 4
	octave 2
	note A_, 2
	octave 3
	note Fs, 2
	octave 2
	note G_, 4
	octave 1
	note G_, 6
	octave 2
	note D_, 2
	note E_, 2
	note Fs, 2
	note G_, 4
	octave 1
	note G_, 6
	octave 2
	note G_, 2
	note A_, 2
	note B_, 2
	octave 3
	note Cs, 2
	octave 2
	note E_, 1
	rest 1
	note E_, 4
	octave 3
	note Cs, 2
	octave 2
	note E_, 1
	rest 1
	note Cs, 4
	octave 3
	note Fs, 6
	rest 2
	note A_, 2
	note B_, 2
	octave 4
	note C_, 2
	volume_envelope 10, 3
	octave 3
	note C_, 1
	rest 1
	note Fs, 1
	volume_envelope 12, 3
	octave 2
	note B_, 1
	note G_, 2
	octave 3
	note C_, 2
	octave 2
	note G_, 2
	octave 3
	note D_, 2
	note E_, 2
	note D_, 2
	octave 2
	note B_, 2
	note A_, 4
	octave 3
	note C_, 2
	octave 2
	note A_, 2
	octave 3
	note C_, 2
	note D_, 2
	note E_, 2
	note C_, 2
	octave 2
	note G_, 6
	octave 1
	note B_, 2
	octave 2
	note G_, 6
	note E_, 2
	octave 3
	note D_, 1
	octave 2
	note A_, 1
	octave 3
	note Fs, 1
	note D_, 1
	note A_, 1
	note G_, 1
	note Fs, 1
	note G_, 1
	note Fs, 2
	note E_, 2
	note D_, 2
	note C_, 2
	octave 2
	note B_, 8
	rest 2
	note G_, 2
	octave 3
	note D_, 2
	octave 2
	note B_, 2
	note A_, 8
	octave 3
	note C_, 2
	octave 2
	note B_, 2
	note A_, 2
	note Fs, 2
	note G_, 8
	octave 3
	note G_, 2
	note E_, 2
	note B_, 2
	note G_, 2
	note A_, 8
	note C_, 4
	octave 2
	note Fs, 2
	octave 3
	note C_, 2
	octave 2
	note B_, 8
	rest 2
	note G_, 2
	octave 3
	note D_, 2
	octave 2
	note B_, 2
	note A_, 8
	octave 3
	note C_, 2
	octave 2
	note B_, 2
	note A_, 2
	note Fs, 2
	note G_, 8
	note G_, 4
	note G_, 4
	rest 1
	octave 1
	note Fs, 2
	octave 2
	note C_, 2
	note Fs, 2
	octave 3
	note C_, 2
	note D_, 6
	rest 1
	note D_, 8
	octave 2
	note B_, 8

	sound_loop 0, gbs_mus_lilycove_museum_Ch2.mainloop

@ ────────────────────────────────────────────────────────────
@ Ch3: Wave
@ ────────────────────────────────────────────────────────────

gbs_mus_lilycove_museum_Ch3:
	gbs_switch 2
	note_type 12, 12, 3

gbs_mus_lilycove_museum_Ch3.mainloop:
	rest 4
	octave 2
	note G_, 4
	octave 1
	note G_, 6
	octave 2
	note D_, 4
	note G_, 2
	note Fs, 4
	octave 1
	note Fs, 6
	octave 2
	note Fs, 4
	note C_, 2
	note E_, 4
	octave 1
	note E_, 6
	note B_, 2
	octave 2
	note G_, 2
	note B_, 2
	octave 3
	note D_, 4
	octave 1
	note D_, 6
	octave 2
	note D_, 4
	note A_, 2
	note G_, 4
	octave 1
	note G_, 6
	octave 2
	note D_, 4
	note G_, 2
	note Fs, 4
	octave 1
	note Fs, 6
	octave 2
	note Fs, 4
	note C_, 2
	note E_, 4
	octave 1
	note E_, 6
	note B_, 2
	octave 2
	note G_, 2
	note B_, 2
	note D_, 4
	octave 1
	note D_, 6
	octave 2
	note D_, 4
	octave 3
	note D_, 2
	note B_, 1
	note As, 1
	note B_, 1
	octave 4
	note C_, 1
	octave 3
	note B_, 2
	note A_, 2
	note G_, 2
	note Fs, 2
	note E_, 2
	note D_, 2
	note E_, 1
	note Ds, 1
	note E_, 1
	note Fs, 1
	note G_, 2
	note E_, 2
	octave 4
	note C_, 2
	octave 3
	note B_, 2
	note A_, 2
	note G_, 2
	rest 1
	octave 4
	note Ds, 1
	note E_, 1
	note Ds, 1
	note E_, 1
	rest 1
	note Cs, 1
	rest 2
	note Ds, 1
	note E_, 1
	note Ds, 1
	note E_, 1
	rest 1
	note Cs, 1
	rest 1
	note D_, 1
	octave 3
	note A_, 1
	octave 4
	note C_, 1
	octave 3
	note B_, 1
	note A_, 2
	note D_, 2
	note Fs, 2
	note G_, 2
	note A_, 2
	volume_envelope 10, 3
	octave 2
	note A_, 1
	octave 3
	note D_, 1
	volume_envelope 12, 3
	note G_, 2
	note D_, 2
	note A_, 2
	note D_, 2
	note B_, 2
	octave 4
	note C_, 2
	octave 3
	note B_, 2
	note G_, 2
	note Fs, 1
	note Fs, 1
	volume_envelope 10, 3
	note G_, 1
	volume_envelope 12, 3
	note E_, 1
	note Fs, 2
	note C_, 2
	note Fs, 2
	note G_, 2
	note A_, 2
	note Fs, 2
	note G_, 1
	octave 2
	note B_, 1
	octave 3
	note Fs, 1
	octave 2
	note B_, 1
	octave 3
	note G_, 1
	octave 2
	note B_, 1
	octave 3
	note E_, 1
	octave 2
	note B_, 1
	octave 3
	note B_, 1
	note E_, 1
	note As, 1
	octave 2
	note B_, 1
	octave 3
	note B_, 1
	note E_, 1
	octave 4
	note G_, 1
	note E_, 1
	note Fs, 6
	note E_, 2
	note D_, 2
	note C_, 2
	octave 3
	note B_, 2
	note A_, 2
	octave 2
	note G_, 4
	octave 1
	note G_, 6
	octave 2
	note D_, 4
	note G_, 2
	note Fs, 4
	octave 1
	note Fs, 6
	octave 2
	note Fs, 4
	note C_, 2
	note E_, 4
	octave 1
	note E_, 6
	note B_, 2
	octave 2
	note G_, 2
	note B_, 2
	octave 3
	note D_, 4
	octave 1
	note D_, 6
	octave 2
	note D_, 4
	note A_, 2
	note G_, 4
	octave 1
	note G_, 6
	octave 2
	note D_, 4
	note G_, 2
	note Fs, 4
	octave 1
	note Fs, 6
	octave 2
	note Fs, 4
	note C_, 2
	note E_, 4
	octave 1
	note E_, 4
	octave 2
	note D_, 2
	note D_, 4
	octave 1
	note G_, 2
	note D_, 2
	note A_, 2
	octave 2
	note D_, 2
	note A_, 2
	note A_, 7
	rest 1
	note B_, 8
	octave 1
	note G_, 8

	sound_loop 0, gbs_mus_lilycove_museum_Ch3.mainloop

	.align 4
	.global gbs_mus_lilycove_museum_Header
gbs_mus_lilycove_museum_Header:
	.byte 3	@ NumTrks
	.byte 0	@ NumBlks
	.byte 0	@ Priority
	.byte 0	@ Reverb

	.int voicegroup000

	.int gbs_mus_lilycove_museum_Ch1
	.int gbs_mus_lilycove_museum_Ch2
	.int gbs_mus_lilycove_museum_Ch3
