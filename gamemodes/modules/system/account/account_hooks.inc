#if defined _inc_account_hooks
    #undef _inc_account_hooks
#endif

#if defined _account_hooks_included
    #endinput
#endif
#define _account_hooks_included

#include <YSI_Coding\y_hooks>

HOOK__ OnPlayerConnect(playerid)
{
    if(IsPlayerNPC(playerid))
        return 1;

    g_RaceCheck[playerid]++;
    ResetAccountData(playerid);
    return 1;
}

HOOK__ OnPlayerRequestClass(playerid, classid)
{
    if(!IsAccountLogged(playerid))
    {
        TogglePlayerSpectating(playerid, true);
        
        Account_Verify(playerid);
    }
    return 1;
}