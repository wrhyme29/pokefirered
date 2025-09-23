.equ SIGN_LADY_READY, VAR_TEMP_2

PalletTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PalletTown_OnFrame
	.byte 0

PalletTown_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_PALLET_TOWN
	call_if_set FLAG_PALLET_LADY_NOT_BLOCKING_SIGN, PalletTown_EventScript_TryReadySignLady
	call_if_eq VAR_MAP_SCENE_PALLET_TOWN_SIGN_LADY, 0, PalletTown_EventScript_SetSignLadyPos
	call_if_eq VAR_MAP_SCENE_PALLET_TOWN_SIGN_LADY, 1, PalletTown_EventScript_SetSignLadyDone
	end

PalletTown_EventScript_TryReadySignLady::
	goto_if_unset FLAG_OPENED_START_MENU, EventScript_Return
	goto_if_ge VAR_MAP_SCENE_PALLET_TOWN_SIGN_LADY, 1, EventScript_Return
	setvar VAR_MAP_SCENE_PALLET_TOWN_SIGN_LADY, 1
	return

PalletTown_EventScript_SetSignLadyDone::
	setvar VAR_MAP_SCENE_PALLET_TOWN_SIGN_LADY, 2
	return

PalletTown_EventScript_SetSignLadyPos::
	goto_if_set FLAG_PALLET_LADY_NOT_BLOCKING_SIGN, PalletTown_EventScript_MoveSignLadyToRouteEntrance
	setobjectxyperm LOCALID_PALLET_SIGN_LADY, 5, 15
	setobjectmovementtype LOCALID_PALLET_SIGN_LADY, MOVEMENT_TYPE_FACE_UP
	return

PalletTown_EventScript_MoveSignLadyToRouteEntrance::
	setobjectxyperm LOCALID_PALLET_SIGN_LADY, 12, 2
	setobjectmovementtype LOCALID_PALLET_SIGN_LADY, MOVEMENT_TYPE_FACE_DOWN
	setvar SIGN_LADY_READY, TRUE
	return

PalletTown_OnFrame::
	map_script_2 VAR_MAP_SCENE_PALLET_TOWN_OAK, 2, PalletTown_EventScript_OakRatingScene
	.2byte 0

@ Oak approaches player after exiting their house post Elite Four to check if they should receieve the National Dex
PalletTown_EventScript_OakRatingScene::
	lockall
	textcolor NPC_TEXT_COLOR_MALE
	setobjectxyperm LOCALID_PALLET_PROF_OAK, 14, 14
	setobjectmovementtype LOCALID_PALLET_PROF_OAK, MOVEMENT_TYPE_FACE_LEFT
	addobject LOCALID_PALLET_PROF_OAK
	applymovement LOCALID_PALLET_PROF_OAK, PalletTown_Movement_OakWalkToPlayersDoor
	waitmovement 0
	goto_if_unset FLAG_WORLD_MAP_ONE_ISLAND, PalletTown_EventScript_NotBeenToOneIslandYet
	msgbox PalletTown_Text_OakLetMeSeePokedex
	setvar VAR_0x8004, 0
	specialvar VAR_RESULT, GetPokedexCount
	copyvar VAR_0x8008, VAR_0x8005
	copyvar VAR_0x8009, VAR_0x8006
	buffernumberstring STR_VAR_1, VAR_0x8008
	buffernumberstring STR_VAR_2, VAR_0x8009
	goto_if_lt VAR_0x8009, 60, PalletTown_EventScript_NotEnoughMonsForNationalDex
	msgbox PalletTown_Text_CaughtXImpressiveFollowMe
	closemessage
	playbgm MUS_FOLLOW_ME, 0
	applymovement LOCALID_PLAYER, PalletTown_Movement_PlayerWalkToLabFromHouse
	applymovement LOCALID_PALLET_PROF_OAK, PalletTown_Movement_OakWalkToLabFromHouse
	waitmovement 0
	opendoor 16, 13
	waitdooranim
	applymovement LOCALID_PALLET_PROF_OAK, PalletTown_Movement_OakEnterLab
	applymovement LOCALID_PLAYER, PalletTown_Movement_PlayerEnterLab
	waitmovement 0
	closedoor 16, 13
	waitdooranim
	setvar VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 7
	setvar VAR_MAP_SCENE_PALLET_TOWN_OAK, 3
	setflag FLAG_HIDE_OAK_IN_PALLET_TOWN
	warp MAP_PALLET_TOWN_PROFESSOR_OAKS_LAB, 6, 12
	waitstate
	releaseall
	end

PalletTown_EventScript_EndOakRatingScene::
	closemessage
	applymovement LOCALID_PALLET_PROF_OAK, PalletTown_Movement_OakExit
	waitmovement 0
	removeobject LOCALID_PALLET_PROF_OAK
	setvar VAR_MAP_SCENE_PALLET_TOWN_OAK, 3
	releaseall
	end

PalletTown_EventScript_NotEnoughMonsForNationalDex::
	msgbox PalletTown_Text_CaughtXPuttingInHonestEffort
	goto PalletTown_EventScript_EndOakRatingScene
	end

PalletTown_EventScript_NotBeenToOneIslandYet::
	msgbox PalletTown_Text_OakYouEnjoyingTraveling
	goto PalletTown_EventScript_EndOakRatingScene
	end

PalletTown_Movement_OakWalkToPlayersDoor::
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

PalletTown_Movement_OakExit::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

PalletTown_Movement_OakWalkToLabFromHouse::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

PalletTown_Movement_PlayerWalkToLabFromHouse::
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

PalletTown_EventScript_OakTriggerLeft::
	lockall
	setvar VAR_TEMP_1, 0
	goto PalletTown_EventScript_OakTrigger
	end

PalletTown_EventScript_OakTriggerRight::
	lockall
	setvar VAR_TEMP_1, 1
	goto PalletTown_EventScript_OakTrigger
	end

PalletTown_EventScript_OakTrigger::
	famechecker FAMECHECKER_OAK, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	textcolor NPC_TEXT_COLOR_MALE
	delay 30
	playbgm MUS_OAK, 0
	message PalletTown_Text_OakDontGoOut
	waitmessage
	delay 85
	closemessage
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	delay 30
	addobject LOCALID_PALLET_PROF_OAK
	call_if_eq VAR_TEMP_1, 0, PalletTown_EventScript_OakEnterLeft
	call_if_eq VAR_TEMP_1, 1, PalletTown_EventScript_OakEnterRight
	delay 30
	msgbox PalletTown_Text_OakGrassUnsafeNeedMon
	closemessage
	delay 30
	call_if_eq VAR_TEMP_1, 0, PalletTown_EventScript_OakLeadPlayerToLabLeft
	call_if_eq VAR_TEMP_1, 1, PalletTown_EventScript_OakLeadPlayerToLabRight
	opendoor 16, 13
	waitdooranim
	applymovement LOCALID_PALLET_PROF_OAK, PalletTown_Movement_OakEnterLab
	applymovement LOCALID_PLAYER, PalletTown_Movement_PlayerEnterLab
	waitmovement 0
	closedoor 16, 13
	waitdooranim
	setvar VAR_MAP_SCENE_PALLET_TOWN_PROFESSOR_OAKS_LAB, 1
	clearflag FLAG_HIDE_OAK_IN_HIS_LAB
	setvar VAR_MAP_SCENE_PALLET_TOWN_OAK, 1
	setflag FLAG_HIDE_OAK_IN_PALLET_TOWN
	setflag FLAG_DONT_TRANSITION_MUSIC
	warp MAP_PALLET_TOWN_PROFESSOR_OAKS_LAB, 6, 12
	waitstate
	releaseall
	end

PalletTown_EventScript_OakEnterLeft::
	applymovement LOCALID_PALLET_PROF_OAK, PalletTown_Movement_OakEnterLeft
	waitmovement 0
	return

PalletTown_EventScript_OakEnterRight::
	applymovement LOCALID_PALLET_PROF_OAK, PalletTown_Movement_OakEnterRight
	waitmovement 0
	return

PalletTown_EventScript_OakLeadPlayerToLabLeft::
	applymovement LOCALID_PALLET_PROF_OAK, PalletTown_Movement_OakWalkToLabLeft
	applymovement LOCALID_PLAYER, PalletTown_Movement_PlayerWalkToLabLeft
	waitmovement 0
	return

PalletTown_EventScript_OakLeadPlayerToLabRight::
	applymovement LOCALID_PALLET_PROF_OAK, PalletTown_Movement_OakWalkToLabRight
	applymovement LOCALID_PLAYER, PalletTown_Movement_PlayerWalkToLabRight
	waitmovement 0
	return

PalletTown_Movement_OakEnterLeft::
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	step_end

PalletTown_Movement_OakEnterRight::
	walk_right
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	walk_right
	walk_up
	walk_up
	step_end

	.macro walk_to_lab
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	.endm

PalletTown_Movement_OakWalkToLabLeft::
	walk_down
	walk_to_lab
	walk_right
	walk_in_place_faster_up
	step_end

PalletTown_Movement_OakWalkToLabRight::
	walk_down
	walk_left
	walk_to_lab
	walk_right
	walk_in_place_faster_up
	step_end

PalletTown_Movement_OakEnterLab::
	walk_up
	set_invisible
	step_end

PalletTown_Movement_PlayerWalkToLabLeft::
	walk_down
	walk_down
	walk_to_lab
	step_end

PalletTown_Movement_PlayerWalkToLabRight::
	walk_down
	walk_down
	walk_left
	walk_to_lab
	step_end

PalletTown_Movement_PlayerEnterLab::
	walk_right
	walk_up
	set_invisible
	step_end

PalletTown_EventScript_SignLady::
	lock
	goto_if_eq VAR_MAP_SCENE_PALLET_TOWN_SIGN_LADY, 2, PalletTown_EventScript_SignLadyDone
	goto_if_eq VAR_MAP_SCENE_PALLET_TOWN_SIGN_LADY, 1, PalletTown_EventScript_SignLadyJustShowedSign
	goto_if_eq SIGN_LADY_READY, TRUE, PalletTown_EventScript_SignLadyStartShowSign
	goto_if_set FLAG_TEMP_2, PalletTown_EventScript_SignLadyGoReadSign
	msgbox PalletTown_Text_HmmIsThatRight
	applymovement LOCALID_PALLET_SIGN_LADY, Common_Movement_FacePlayer
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_PALLET_SIGN_LADY, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_PALLET_SIGN_LADY, Common_Movement_Delay48
	waitmovement 0
	msgbox PalletTown_Text_OhLookLook
	closemessage
	call_if_eq VAR_FACING, DIR_EAST, PalletTown_EventScript_SignLadyMoveOutOfWayRight
	call_if_ne VAR_FACING, DIR_EAST, PalletTown_EventScript_SignLadyMoveOutOfWayLeft
	copyobjectxytoperm LOCALID_PALLET_SIGN_LADY
	setflag FLAG_TEMP_2
	release
	end

PalletTown_EventScript_SignLadyMoveOutOfWayRight::
	applymovement LOCALID_PALLET_SIGN_LADY, PalletTown_Movement_SignLadyMoveOutOfWayRight
	waitmovement 0
	return

PalletTown_EventScript_SignLadyMoveOutOfWayLeft::
	applymovement LOCALID_PALLET_SIGN_LADY, PalletTown_Movement_SignLadyMoveOutOfWayLeft
	waitmovement 0
	return

PalletTown_EventScript_SignLadyDone::
	applymovement LOCALID_PALLET_SIGN_LADY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox PalletTown_Text_RaisingMonsToo
	release
	end

PalletTown_EventScript_SignLadyGoReadSign::
	applymovement LOCALID_PALLET_SIGN_LADY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox PalletTown_Text_ReadItReadIt
	release
	end

PalletTown_EventScript_SignLadyJustShowedSign::
	applymovement LOCALID_PALLET_SIGN_LADY, Common_Movement_FacePlayer
	waitmovement 0
	msgbox PalletTown_Text_SignsAreUsefulArentThey
	release
	end

PalletTown_Movement_SignLadyMoveOutOfWayRight::
	walk_right
	walk_in_place_faster_left
	step_end

PalletTown_Movement_SignLadyMoveOutOfWayLeft::
	walk_left
	walk_in_place_faster_right
	step_end

PalletTown_EventScript_FatMan::
	msgbox PalletTown_Text_CanStoreItemsAndMonsInPC, MSGBOX_NPC
	end

PalletTown_EventScript_Aliza::
  lock
  faceplayer
	specialvar VAR_RESULT, CalculatePlayerPartyCount
	goto_if_eq VAR_RESULT, 0, PalletTown_EventScript_Aliza_NoPokemon
  call PalletTown_EventScript_Aliza_CountBadges
  call PalletTown_EventScript_Aliza_Greeting
  release
	end

PalletTown_EventScript_Aliza_NoPokemon::
	msgbox PalletTown_Text_Aliza_NoPokemon
	release
	end

PalletTown_EventScript_Aliza_CountBadges::
  setvar VAR_BADGE_COUNT 0
  call_if_set FLAG_BADGE01_GET, PalletTown_EventScript_Aliza_IncrementBadgeCount
  call_if_set FLAG_BADGE02_GET, PalletTown_EventScript_Aliza_IncrementBadgeCount
  call_if_set FLAG_BADGE03_GET, PalletTown_EventScript_Aliza_IncrementBadgeCount
  call_if_set FLAG_BADGE04_GET, PalletTown_EventScript_Aliza_IncrementBadgeCount
  call_if_set FLAG_BADGE05_GET, PalletTown_EventScript_Aliza_IncrementBadgeCount
  call_if_set FLAG_BADGE06_GET, PalletTown_EventScript_Aliza_IncrementBadgeCount
  call_if_set FLAG_BADGE07_GET, PalletTown_EventScript_Aliza_IncrementBadgeCount
  call_if_set FLAG_BADGE08_GET, PalletTown_EventScript_Aliza_IncrementBadgeCount
  return

PalletTown_EventScript_Aliza_IncrementBadgeCount::
  addvar VAR_BADGE_COUNT 1
  return

PalletTown_EventScript_Aliza_Greeting::
  buffernumberstring STR_VAR_1, VAR_BADGE_COUNT
  msgbox PalletTown_Text_Aliza_BadgeCount
  goto_if_eq VAR_BADGE_COUNT, 0, PalletTown_EventScript_Aliza_ZeroBadges
  goto_if_eq VAR_BADGE_COUNT, 1, PalletTown_EventScript_Aliza_OneBadge
  goto_if_eq VAR_BADGE_COUNT, 2, PalletTown_EventScript_Aliza_TwoBadges
  goto_if_eq VAR_BADGE_COUNT, 3, PalletTown_EventScript_Aliza_ThreeBadges
  goto_if_eq VAR_BADGE_COUNT, 4, PalletTown_EventScript_Aliza_FourBadges
  goto_if_eq VAR_BADGE_COUNT, 5, PalletTown_EventScript_Aliza_FiveBadges
  goto_if_eq VAR_BADGE_COUNT, 6, PalletTown_EventScript_Aliza_SixBadges
  goto_if_eq VAR_BADGE_COUNT, 7, PalletTown_EventScript_Aliza_SevenBadges
  goto_if_eq VAR_BADGE_COUNT, 8, PalletTown_EventScript_Aliza_EightBadges
  return

PalletTown_EventScript_Aliza_AlreadyWon::
	msgbox PalletTown_Text_Aliza_AlreadyWon
	release
	end

PalletTown_EventScript_Aliza_WonAll::
	msgbox PalletTown_Text_Aliza_WonAll
	release
	end

PalletTown_EventScript_Aliza_BattleDeclined::
	msgbox PalletTown_Text_Aliza_BattleDeclined
	release
	end

PalletTown_EventScript_Aliza_ZeroBadges::
	goto_if_set FLAG_ALIZA_WON_BATTLE_ZERO, PalletTown_EventScript_Aliza_AlreadyWon
  msgbox PalletTown_Text_Aliza_BattleZeroAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PalletTown_EventScript_Aliza_BattleDeclined
	trainerbattle_no_intro TRAINER_POKEFAN_ALIZA_ZERO_BADGES, PalletTown_Text_Aliza_BattleZeroWon
	setflag FLAG_ALIZA_WON_BATTLE_ZERO
	return

PalletTown_EventScript_Aliza_OneBadge::
	goto_if_set FLAG_ALIZA_WON_BATTLE_ONE, PalletTown_EventScript_Aliza_AlreadyWon
  msgbox PalletTown_Text_Aliza_BattleOneAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PalletTown_EventScript_Aliza_BattleDeclined
	trainerbattle_no_intro TRAINER_POKEFAN_ALIZA_ONE_BADGE, PalletTown_Text_Aliza_BattleOneWon
	setflag FLAG_ALIZA_WON_BATTLE_ONE
	return

PalletTown_EventScript_Aliza_TwoBadges::
	goto_if_set FLAG_ALIZA_WON_BATTLE_TWO, PalletTown_EventScript_Aliza_AlreadyWon
  msgbox PalletTown_Text_Aliza_BattleTwoAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PalletTown_EventScript_Aliza_BattleDeclined
	trainerbattle_no_intro TRAINER_POKEFAN_ALIZA_TWO_BADGES, PalletTown_Text_Aliza_BattleTwoWon
	setflag FLAG_ALIZA_WON_BATTLE_TWO
	return

PalletTown_EventScript_Aliza_ThreeBadges::
	goto_if_set FLAG_ALIZA_WON_BATTLE_THREE, PalletTown_EventScript_Aliza_AlreadyWon
  msgbox PalletTown_Text_Aliza_BattleThreeAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PalletTown_EventScript_Aliza_BattleDeclined
	trainerbattle_no_intro TRAINER_POKEFAN_ALIZA_THREE_BADGES, PalletTown_Text_Aliza_BattleThreeWon
	setflag FLAG_ALIZA_WON_BATTLE_THREE
	return

PalletTown_EventScript_Aliza_FourBadges::
	goto_if_set FLAG_ALIZA_WON_BATTLE_FOUR, PalletTown_EventScript_Aliza_AlreadyWon
  msgbox PalletTown_Text_Aliza_BattleFourAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PalletTown_EventScript_Aliza_BattleDeclined
	trainerbattle_no_intro TRAINER_POKEFAN_ALIZA_FOUR_BADGES, PalletTown_Text_Aliza_BattleFourWon
	setflag FLAG_ALIZA_WON_BATTLE_FOUR
	return

PalletTown_EventScript_Aliza_FiveBadges::
	goto_if_set FLAG_ALIZA_WON_BATTLE_FIVE, PalletTown_EventScript_Aliza_AlreadyWon
  msgbox PalletTown_Text_Aliza_BattleFiveAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PalletTown_EventScript_Aliza_BattleDeclined
	trainerbattle_no_intro TRAINER_POKEFAN_ALIZA_FIVE_BADGES, PalletTown_Text_Aliza_BattleFiveWon
	setflag FLAG_ALIZA_WON_BATTLE_FIVE
	return

PalletTown_EventScript_Aliza_SixBadges::
	goto_if_set FLAG_ALIZA_WON_BATTLE_SIX, PalletTown_EventScript_Aliza_AlreadyWon
  msgbox PalletTown_Text_Aliza_BattleSixAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PalletTown_EventScript_Aliza_BattleDeclined
	trainerbattle_no_intro TRAINER_POKEFAN_ALIZA_SIX_BADGES, PalletTown_Text_Aliza_BattleSixWon
	setflag FLAG_ALIZA_WON_BATTLE_SIX
	return

PalletTown_EventScript_Aliza_SevenBadges::
	goto_if_set FLAG_ALIZA_WON_BATTLE_SEVEN, PalletTown_EventScript_Aliza_AlreadyWon
  msgbox PalletTown_Text_Aliza_BattleSevenAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PalletTown_EventScript_Aliza_BattleDeclined
	trainerbattle_no_intro TRAINER_POKEFAN_ALIZA_SEVEN_BADGES, PalletTown_Text_Aliza_BattleSevenWon
	setflag FLAG_ALIZA_WON_BATTLE_SEVEN
	return

PalletTown_EventScript_Aliza_EightBadges::
	goto_if_set FLAG_ALIZA_WON_BATTLE_EIGHT, PalletTown_EventScript_Aliza_WonAll
  msgbox PalletTown_Text_Aliza_BattleEightAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, PalletTown_EventScript_Aliza_BattleDeclined
	trainerbattle_no_intro TRAINER_POKEFAN_ALIZA_EIGHT_BADGES, PalletTown_Text_Aliza_BattleEightWon
	setflag FLAG_ALIZA_WON_BATTLE_EIGHT
	return

PalletTown_EventScript_OaksLabSign::
	lockall
	famechecker FAMECHECKER_OAK, 0
	msgbox PalletTown_Text_OakPokemonResearchLab
	releaseall
	end

PalletTown_EventScript_PlayersHouseSign::
	msgbox PalletTown_Text_PlayersHouse, MSGBOX_SIGN
	end

PalletTown_EventScript_RivalsHouseSign::
	msgbox PalletTown_Text_RivalsHouse, MSGBOX_SIGN
	end

PalletTown_EventScript_TownSign::
	msgbox PalletTown_Text_TownSign, MSGBOX_SIGN
	end

PalletTown_EventScript_TrainerTips::
	lockall
	msgbox PalletTown_Text_PressStartToOpenMenu
	setvar VAR_MAP_SCENE_PALLET_TOWN_SIGN_LADY, 1
	releaseall
	end

PalletTown_EventScript_SignLadyTrigger::
	lockall
	applymovement LOCALID_PALLET_SIGN_LADY, Common_Movement_WalkInPlaceFasterRight
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	call PalletTown_EventScript_SignLadyShowSign
	releaseall
	end

PalletTown_EventScript_SignLadyShowSign::
	textcolor NPC_TEXT_COLOR_FEMALE
	msgbox PalletTown_Text_LookCopiedTrainerTipsSign
	closemessage
	delay 20
	textcolor NPC_TEXT_COLOR_NEUTRAL
	setflag FLAG_OPENED_START_MENU
	setvar VAR_MAP_SCENE_PALLET_TOWN_SIGN_LADY, 1
	setvar SIGN_LADY_READY, FALSE
	special SetWalkingIntoSignVars
	special DisableMsgBoxWalkaway
	signmsg
	msgbox PalletTown_Text_PressStartToOpenMenuCopy
	normalmsg
	return

PalletTown_EventScript_SignLadyStartShowSign::
	applymovement LOCALID_PALLET_SIGN_LADY, Common_Movement_FacePlayer
	waitmovement 0
	call PalletTown_EventScript_SignLadyShowSign
	release
	end
