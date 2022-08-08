#if defined _inc_account_function
    #undef _inc_account_function
#endif

#if defined _account_function_included
    #endinput
#endif
#define _account_function_included

IsAccountLogged(playerid)
    return AccountData[playerid][acLogged];

stock Account_Verify(playerid)
{
    inline OnAccountChecked()
    {
        if(cache_num_rows())
        {
            GetPlayerName(playerid, AccountData[playerid][acName], 24);
            cache_get_value_name_int(0, "account_id", AccountData[playerid][acID]);

            Dialog_ShowCallback(playerid, using public LoginPage<iiiis>, DIALOG_STYLE_PASSWORD, "Login", va_return("Hello %s, Welcome back to Roleplay server!\n\nYour account is registered on this server.\nPlease input your account password to proceed:", ReturnName(playerid)), "Login", "Exit");
        }
        else
        {
            Dialog_ShowCallback(playerid, using public RegisterPage<iiiis>, DIALOG_STYLE_PASSWORD, "Register", va_return("Hello %s, Welcome to Roleplay Server!\n\nYour account is not registered on our server, Please enter password to register your account.\n"GREY"For security purposes, enter a "TOMATO"unique password "GREY"that you haven't used before:", ReturnName(playerid)), "Register", "Close");
        }
        return 1;
    }

    MySQL_TQueryInline(MySQL_GetHandle(),
        using inline OnAccountChecked,
        "SELECT * FROM accounts WHERE account_name = '%e'",
            ReturnName(playerid)
    );
    return 1;
}

function ResetAccountData(playerid)
{
    AccountData[playerid][acLogged] = false;
    return 1;
}
