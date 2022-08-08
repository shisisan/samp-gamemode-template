#if defined _inc_account_variable
    #undef _inc_account_variable
#endif

#if defined _account_variable_included
    #endinput
#endif
#define _account_variable_included

enum E_ACCOUNT_DATA 
{
    acID,
    acName[24],
    bool:acLogged
}
new AccountData[MAX_PLAYERS][E_ACCOUNT_DATA];
new g_RaceCheck[MAX_PLAYERS];