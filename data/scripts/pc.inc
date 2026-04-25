EventScript_PC::
	setvar VAR_ENABLE_ANIMATIONS 1
	goto EventScript_PC_Internal
	end

EventScript_PC_NoAnimation::
	setvar VAR_ENABLE_ANIMATIONS 0
	goto EventScript_PC_Internal
	end

EventScript_PC_Internal::
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_set FLAG_SYS_PC_STORAGE_DISABLED, EventScript_PCDisabled
	call_if_eq VAR_ENABLE_ANIMATIONS, 1, EventScript_PC_SetPcHelpContext
	call_if_eq VAR_ENABLE_ANIMATIONS, 1, EventScript_PC_AnimateTurnOn
	call_if_eq VAR_ENABLE_ANIMATIONS, 1, EventScript_PC_PlayPcOnSE
	msgbox Text_BootedUpPC
	goto EventScript_PCMainMenu
	end

EventScript_PC_SetPcHelpContext::
	setvar VAR_0x8004, HELPCONTEXT_PC
	special Script_SetHelpContext
	setvar VAR_0x8004, 0
	return

EventScript_PC_PlayPcOnSE::
	playse SE_PC_ON
	return

EventScript_PC_AnimateTurnOn::
	special AnimatePcTurnOn
	return

@ For when the player first arrives on One Island
EventScript_PCDisabled::
	msgbox OneIsland_PokemonCenter_1F_Text_UsualPCServicesUnavailable
	releaseall
	end

EventScript_PCMainMenu::
	message Text_AccessWhichPC
	waitmessage
	special CreatePCMenu
	waitstate
	goto EventScript_ChoosePCMenu
	end

EventScript_ChoosePCMenu::
	switch VAR_RESULT
	case 0, EventScript_AccessPokemonStorage
	case 1, EventScript_AccessPlayersPC
	case 2, EventScript_AccessProfOaksPC
	case 3, EventScript_AccessHallOfFame
	case 4, EventScript_TurnOffPC
	case SCR_MENU_CANCEL, EventScript_TurnOffPC
	end

EventScript_AccessPlayersPC::
	playse SE_PC_LOGIN
	msgbox Text_AccessedPlayersPC
	special PlayerPC
	waitstate
	goto EventScript_PCMainMenu
	end

EventScript_AccessPokemonStorage::
	playse SE_PC_LOGIN
	call_if_unset FLAG_SYS_NOT_SOMEONES_PC, EventScript_AccessSomeonesPC
	call_if_set FLAG_SYS_NOT_SOMEONES_PC, EventScript_AccessBillsPC
	msgbox Text_OpenedPkmnStorage
	special ShowPokemonStorageSystemPC
	waitstate
	goto_if_eq VAR_ENABLE_ANIMATIONS, 1, EventScript_PC_SetPcHelpContext
	goto EventScript_PCMainMenu
	end

EventScript_AccessSomeonesPC::
	msgbox Text_AccessedSomeonesPC
	return

EventScript_AccessBillsPC::
	msgbox Text_AccessedBillsPC
	return

EventScript_TurnOffPC::
	playse SE_PC_OFF
	call_if_eq VAR_ENABLE_ANIMATIONS, 1, EventScript_AnimateTurnOffPC
	releaseall
	end

EventScript_AnimateTurnOffPC::
	setvar VAR_0x8004, 0
	special AnimatePcTurnOff
	special SetHelpContextForMap
	return

EventScript_AccessHallOfFame::
	goto_if_unset FLAG_SYS_GAME_CLEAR, EventScript_TurnOffPC
	playse SE_PC_LOGIN
	setvar VAR_0x8004, HELPCONTEXT_PC_MISC
	special BackupHelpContext
	special Script_SetHelpContext
	special HallOfFamePCBeginFade
	waitstate
	special RestoreHelpContext
	goto EventScript_ChoosePCMenu
	end

EventScript_AccessProfOaksPC::
	goto_if_unset FLAG_SYS_POKEDEX_GET, EventScript_TurnOffPC
	playse SE_PC_LOGIN
	msgbox Text_AccessedProfOaksPC
	msgbox Text_HavePokedexRated, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EventScript_ExitOaksPC
	setflag FLAG_OAKS_RATING_IS_VIA_PC
	call PokedexRating_EventScript_Rate
	clearflag FLAG_OAKS_RATING_IS_VIA_PC
	goto EventScript_ExitOaksPC
	end

EventScript_ExitOaksPC::
	msgbox Text_ClosedLinkToProfOaksPC
	goto EventScript_PCMainMenu
	end
