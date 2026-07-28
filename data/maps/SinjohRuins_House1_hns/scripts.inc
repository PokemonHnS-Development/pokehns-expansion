SinjohRuins_House1_hns_MapScripts::
	.byte 0


SinjohRuins_Lab_EventScript_Scientist_Male1::
	msgbox SinjohRuins_Lab_Text_MS1 MSGBOX_NPC
	end

SinjohRuins_Lab_Text_MS1:
    .string "I'm currently working on mapping\n"
	.string "the ruins with GPR and my partner!\l"
	.string "So far we've discovered\n"
	.string "6 subterrainian chambers!$"

SinjohRuins_Lab_EventScript_Scientist_Female1::
    msgbox SinjohRuins_Lab_Text_FS1 MSGBOX_NPC
	end

SinjohRuins_Lab_Text_FS1:
    .string "Ugh....\n"
	.string "There's so many gliphs\l"
	.string "to translate..\p"
	.string "But it'll be worth it in the\n"
	.string "end if something amazing happens!$"

SinjohRuins_Lab_EventScript_Scientist_Female2::
    msgbox SinjohRuins_Lab_Text_FS2 MSGBOX_NPC
	end

SinjohRuins_Lab_Text_FS2:
    .string "That flute you're carrying...\n"
	.string "It's known as the Azure Flute.\p"
	.string "There is a legend that states when\n"
	.string "it is played with all 18 plates\l"
	.string "nearby, a stairway that pierces\l"
	.string "the sky shall appear.\p"
	.string "If you have such a thing...\n"
	.string "maybe it was a good thing boss\l"
	.string "sent that request for help\l"
	.string "from Mr.Steven Stone.$"

SinjohRuins_Lab_EventScript_Growlithe_Hisui::
    lock
	faceplayer
	playmoncry SPECIES_GROWLITHE, 0
	msgbox SinjohRuins_Lab_Text_Growlithe_Cry, MSGBOX_DEFAULT
	waitmoncry
    closemessage
	release
	end

SinjohRuins_Lab_Text_Growlithe_Cry:
    .string "Growh owh!!$"

SinjohRuins_Lab_EventScript_GrowlithePokeball::
    msgbox SinjohRuins_Lab_Text_GrowlitheBall MSGBOX_SIGN
	end

SinjohRuins_Lab_Text_GrowlitheBall:
    .string "This appears to be Growlithe's ball..\n"
	.string "I better leave it alone.$"

SinjohRuins_Lab_EventScript_Scientist_Male2::
	msgbox SinjohRuins_Lab_Text_MS2 MSGBOX_NPC
	release
	end

SinjohRuins_Lab_Text_MS2:
    .string "Look at this wonderful specimen!\n"
	.string "Isn't he just the goodest boy?$"




@ENVIRONMENT
SinjohRuins_EventScript_Notes1::
    lock
	msgbox SinjohRuins_Notes1_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_EventScript_Notes2::
    lock
	msgbox SinjohRuins_Notes2_Text MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_EventScript_BetterStop
	msgbox SinjohRuins_Notes2_Part2_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_EventScript_Notes3::
    lock
	msgbox SinjohRuins_Notes3_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_EventScript_Notes4::
    lock
	msgbox SinjohRuins_Notes4_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_EventScript_Notes5::
    lock
	msgbox SinjohRuins_Notes5_Text MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_EventScript_BetterStop
	msgbox SinjohRuins_Notes5_Part2_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_EventScript_Notes6::
    lock
	msgbox SinjohRuins_Notes6_Text MSGBOX_YESNO
	goto_if_eq VAR_RESULT, FALSE, SinjohRuins_EventScript_BetterStop
	msgbox SinjohRuins_Notes6_Part2_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_EventScript_Notes7::
    lock
	msgbox SinjohRuins_Notes7_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_Notes1_Text:
    .string "Research Log 1: Discovery Day.\p"
	.string "We've received reports of\n"
	.string "a large structure deep under\l"
	.string "the snow, north of Mt.Silver.\p"
	.string "Once we obtain clearence\n"
	.string "from the league, I am hopeful\l"
	.string "that the excavation team\l"
	.string "will be allowed through the mountain..$"

SinjohRuins_Notes2_Text:
    .string "Research Log 2: Too Much Ice.\p"
	.string "It's been one week since the\n"
	.string "group of muscle men we've hired\l"
	.string "started digging...and they've\l"
	.string "already hit a major issue.\p"
	.string "Ice. And a lot of it.\n"
	.string "This doesn't seem to be\l"
	.string "normal ice either, not even\l"
	.string "a MACHAMP was able to break it.\p"
	.string ".........\n"
	.string "Keep reading?$"

SinjohRuins_Notes2_Part2_Text:
    .string "Research Log 2.5: A Toasty Solution.\p"
	.string "I've got it! If brute force\n"
	.string "can't shatter the ice,\l"
	.string "then what if we slowly melt it down?\p"
	.string "The Boss' family exclusively raises\n"
	.string "FIRE type POKEMON, if I could convice\l"
	.string "them to lend me a couple dozen\l"
	.string "diffrent species then maybe...\p"
	.string "........\n"
	.string "It seems the author didn't finish\l"
	.string "writing this log...$"

SinjohRuins_EventScript_BetterStop::
    msgbox SinjohRuins_BetterStop_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_BetterStop_Text:
    .string "Seems like the author keeps\n"
	.string "going for awhile...\l"
	.string "Better take a break and come\l"
	.string "back later.$"

SinjohRuins_Notes3_Text:
    .string "Research Log 3: A Resounding Success!\p"
	.string "After a very inense call, I somehow\n"
	.string "managed to convice them to transfer\l"
	.string "30 specimens from the HOENN\l"
	.string "and SINNOH reigons to help deal\l"
	.string "with our big issue...\p"
	.string "I will update once I figure\n"
	.string "out how to get them this far north..$"


SinjohRuins_Notes4_Text:
    .string "Research Log 4: A Major Discovery!\p"
	.string "Things have been so busy I forgot\n"
	.string "all about these!\p"
	.string "After we melted and pumped out\n"
	.string "most of the ice, several diffrent\l"
	.string "structures revealed themselves!\p"
	.string "My first observation of the\n"
	.string "main structure is that it shares\l"
	.string "a lot of arcitectual cues from\l"
	.string "the ancient Celestica peoples...\p"
	.string "Once we confirm the stability of the\n"
	.string "building, Boss wants to\l"
	.string "open it up...$"


SinjohRuins_Notes5_Text:
    .string "Research Log 5: The Big Burst.\p"
	.string "After several attempts, Boss\n"
	.string "managed to crack the entrance open!\p"
	.string "However, once he did..a huge wave\n"
	.string "of energy errupted out from the main\l"
	.string "hall, not only that but tall\l"
	.string "beacons of pure light shot up from\l"
	.string "the ground all over the\l"
	.string "surrounding areas!\p"
    .string ".........\n"
	.string "Keep reading?$"

SinjohRuins_Notes5_Part2_Text:
    .string "Research Log 5.5: A Stroke of Luck!\p"
    .string "A member of our team happened\n"
	.string "to be conducting an aerial\l"
	.string "archeological study of the ruins\l"
	.string "while everything went down!\p"
	.string "His report he notes that a\n"
	.string "total of 17 pillars of energy\l"
	.string "appeared through the local areas...\p"
	.string "Tomorrow the Boss is going to hold\n"
	.string "a stratagy meeting on how to\l"
	.string "procced from here...$"

SinjohRuins_Notes6_Text:
    .string "Research Log 6: A Frustrating Decision.\p"
	.string "During the meeting, it was\n"
	.string "decided that I, Edward, will\l"
	.string "have to stay back and raise\l"
	.string "all the fire type POKEMON living\l"
	.string "with us....\p"
	.string "The Boss said that since it was\n"
	.string "my idea to have them brought\l"
	.string "here, I need to take ownership\l"
	.string "of them all!\p"
	.string ".........\n"
	.string "Keep reading...?$"

SinjohRuins_Notes6_Part2_Text:
    .string "How utterly preposterous!\p"
	.string "I did not spend 20 years of my life\n"
	.string "studying under several diffrent\l"
	.string "schools just to be downgraded\l"
	.string "to a daycare worker!!\p"
	.string "Alas, there is nothing I can do...\p"
	.string "If I want to see what lies\n"
	.string "beneath these great halls,\l"
	.string "I must stick with this work..$"


SinjohRuins_Notes7_Text:
    .string "Research Log 7: An Eceological\n"
	.string "Nightmare and My Failure.\p"
	.string "It's all over, my carrier and my life.\n"
	.string "I accidently let nearly all of them out\l"
	.string "into the wild near Mt.Silver..\p"
	.string "I tried to catch them all before it\n"
	.string "was too late but they completely\l"
	.string "swept my team!\p"
	.string "I think tomorrow I might be arrested\n"
	.string "for causing damage to the local\l"
	.string "ecosystem...\p"
	.string "Tonight I'm making my\n"
	.string "escape to the village\l"
	.string "in the south, to my fellow\l"
	.string "collegues, I am deeply sorry...$"


SinjohRuins_EventScript_DisplayCase::
    lock
	msgbox SinjohRuins_DisplayCase_Text MSGBOX_DEFAULT
	release
	end


SinjohRuins_DisplayCase_Text:
    .string "It's a display case neatly\n"
	.string "packed and lined with samples\l"
	.string "and artifacts!$"

SinjohRuins_EventScript_WallSign::
    lock
	msgbox SinjohRuins_WallSign_Text MSGBOX_DEFAULT
	release
	end

SinjohRuins_WallSign_Text:
   .string "Xray and printing lab.$"


SinjohRuins_EventScript_Artifact::
   lock
   msgbox SinjohRuins_Artifact_Text MSGBOX_DEFAULT
   release
   end

SinjohRuins_Artifact_Text:
   .string "It's an artifact found from\n"
   .string "inside the ruins!$"

