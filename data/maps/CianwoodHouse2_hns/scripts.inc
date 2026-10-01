CianwoodHouse2_hns_MapScripts::
	.byte 0

CianwoodHouse2_EventScript_Teacher::
	lock
	faceplayer
	msgbox CianwoodCity_Text_LugiaHouseTeacher, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse2_EventScript_Lass::
	lock
	faceplayer
	msgbox CianwoodCity_Text_LugiaHouseLass, MSGBOX_DEFAULT
	closemessage
	release
	end

CianwoodHouse2_EventScript_Twin::
	lock
	faceplayer
	msgbox CianwoodCity_Text_LugiaHouseTwin, MSGBOX_DEFAULT
	closemessage
	release
	end
	
CianwoodCity_Text_LugiaHouseTeacher:
	.string "¿Vienes de CIUDAD OLIVO?\p"
	.string "¿Recuerdas las cuatro islas\n"
	.string "que hay en el camino?\p"
	.string "Oí que una criatura marina\n"
	.string "mítica se esconde allí.$"

CianwoodCity_Text_LugiaHouseLass:
	.string "Dicen que solo puedes verla\n"
	.string "si tienes un ALA DE PLATA.\p"
	.string "Debe tener el mismo aroma que\n"
	.string "la criatura.$"

CianwoodCity_Text_LugiaHouseTwin:
	.string "He oído que los remolinos\n"
	.string "de las islas son causados por\l"
	.string "la criatura marina.\p"
	.string "Tal vez necesites un movimiento\n"
	.string "especial para pasar.$"
