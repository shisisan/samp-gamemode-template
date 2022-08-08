#if defined _inc_account_callbacks
    #undef _inc_account_callbacks
#endif

#if defined _account_callbacks_included
    #endinput
#endif
#define _account_callbacks_included

function LoginPage(playerid, dialogid, response, listitem, string:inputtext[])
{
    new
        playerHash[128];

    strcopy(playerHash, inputtext);

    inline LoadPassword()
    {
        inline const CheckPlayerPassword(bool:same)
        {
            printf("Are they the same?: %s", same ? ("Yes") : ("No"));
            return 1;
        }

        new 
            hash[BCRYPT_HASH_LENGTH];

        cache_get_value_name(0, "account_password", hash, sizeof(hash));

        BCrypt_CheckInline(playerHash, hash, using inline CheckPlayerPassword);
    }

    if(!response)
        return Kick(playerid);

    MySQL_TQueryInline(MySQL_GetHandle(),
        using inline LoadPassword,
        "SELECT * FROM accounts WHERE account_name = '%e' LIMIT 1", 
            ReturnName(playerid)
    );
    return 1;
}

function RegisterPage(playerid, dialogid, response, listitem, string:inputtext[])
{

    inline const OnPasswordHash(string: result[])
    {
        inline OnAccountCreated()
        {
            AccountData[playerid][acID] = cache_insert_id();

            SendClientMessage(playerid, -1, "ACP password generated! you have successfully registered.");

            AccountData[playerid][acLogged] = true;
            Account_Verify(playerid);
            return 1;
        }

        MySQL_TQueryInline(MySQL_GetHandle(),
            using inline OnAccountCreated,
            "INSERT INTO `accounts` (`account_name`, `account_password`) VALUES ('%e', '%e')", ReturnName(playerid), result
        );
    }

    if(!response)
        return Kick(playerid);

    if(isnull(inputtext))
        return Dialog_ShowCallback(playerid, using public RegisterPage<iiiis>, DIALOG_STYLE_PASSWORD, "Register", va_return("Hello %s, Welcome to Roleplay server!\n\nYour account is not registered on our server, Please enter password to register your account.\n"GREY"For security purposes, enter a "TOMATO"unique password "GREY"that you haven't used before:", ReturnName(playerid)), "Register", "Close");
    
    if(strlen(inputtext) < 8 || strlen(inputtext) > 32)
        return Dialog_ShowCallback(playerid, using public RegisterPage<iiiis>, DIALOG_STYLE_PASSWORD, "Register", va_return("Hello %s, Welcome to Roleplay server!\n\nYour account is not registered on our server, Please enter password to register your account.\n"GREY"For security purposes, enter a "TOMATO"unique password "GREY"that you haven't used before:", ReturnName(playerid)), "Register", "Close");

    BCrypt_HashInline(inputtext, BCRYPT_COST, using inline OnPasswordHash);
    return 1;
}