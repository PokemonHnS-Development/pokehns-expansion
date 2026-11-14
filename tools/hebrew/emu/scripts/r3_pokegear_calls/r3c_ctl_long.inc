@ Negative control for the clip report in the field call box: one line wider than the 192 px
@ the box leaves beside the Pokegear icon (sMatchCallTextWindow, x 32).
	lockall
	pokenavcall R3Ctl_Text_Long
	waitmessage
	delay 30
	releaseall
	end

R3Ctl_Text_Long:
	.string "שורה ארוכה מאוד מאוד מאוד מאוד מאוד מאוד מאוד מאוד מאוד$"
