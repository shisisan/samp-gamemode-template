#if defined _inc_player_hooks
    #undef _inc_player_hooks
#endif

#if defined _player_hooks_included
    #endinput
#endif
#define _player_hooks_included

#include <YSI_Coding\y_hooks>

hook OnGameModeInitEx()
{
    EnableStuntBonusForAll(0);
	DisableInteriorEnterExits();
    
    return 1;
}