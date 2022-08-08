/*
        
        ███╗░░██╗██╗░░░██╗░░░░░░██████╗░██████╗░
        ████╗░██║██║░░░██║░░░░░░██╔══██╗██╔══██╗
        ██╔██╗██║╚██╗░██╔╝█████╗██████╔╝██████╔╝
        ██║╚████║░╚████╔╝░╚════╝██╔══██╗██╔═══╝░
        ██║░╚███║░░╚██╔╝░░░░░░░░██║░░██║██║░░░░░
        ╚═╝░░╚══╝░░░╚═╝░░░░░░░░░╚═╝░░╚═╝╚═╝░░░░░

        

        * Copyright (C) 2022 Thouthan1
        * 
        * Licensed under the Apache License, Version 2.0 (the "License");
        * you may not use this file except in compliance with the License.
        * You may obtain a copy of the License at
        * 
        * http://www.apache.org/licenses/LICENSE-2.0
        * 
        * Unless required by applicable law or agreed to in writing, software
        * distributed under the License is distributed on an "AS IS" BASIS,
        * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
        * See the License for the specific language governing permissions and
        * limitations under the License.
*/

#if defined _inc_database
    #undef _inc_database
#endif

#if defined _database_included
    #endinput
#endif
#define _database_included

#include <YSI_Coding\y_hooks>

new MySQL:g_MySQL = MYSQL_INVALID_HANDLE;
new static va_query[2048];

#define MySQL_GetHandle() g_MySQL

hook OnGameModeInitEx()
{
    InitDatabaseConnection();
    return Y_HOOKS_CONTINUE_RETURN_1;
}

hook OnGameModeExit()
{
    if (!mysql_close(g_MySQL))
        printf("[NV:RP DATABASES]: Unable to complete database connection.");

    return Y_HOOKS_CONTINUE_RETURN_1;
}

static stock InitDatabaseConnection()
{
	static
        mysql_hostname[10],
        mysql_username[5],
        mysql_database[14];

	if (Env_Has("MYSQL_HOSTNAME"))
        Env_Get("MYSQL_HOSTNAME", mysql_hostname);

	if (Env_Has("MYSQL_USERNAME"))
        Env_Get("MYSQL_USERNAME", mysql_username);

	if (Env_Has("MYSQL_DATABASE"))
        Env_Get("MYSQL_DATABASE", mysql_database);

	new MySQLOpt:options = mysql_init_options();
    mysql_set_option(options, AUTO_RECONNECT, true);
    mysql_set_option(options, MULTI_STATEMENTS, true);
    mysql_set_option(options, POOL_SIZE, 2);

    MySQL_GetHandle() = mysql_connect(mysql_hostname, mysql_username, "", mysql_database, options);

    if (mysql_errno(MySQL_GetHandle()))
    {
        new 
            string: error_format[128];

        mysql_error(error_format, sizeof(error_format), MySQL_GetHandle());
        printf("[NV:RP DATABASES]: Error. (%s)", string:error_format);
        SendRconCommand("exit");
        return 1;
    }

    printf("[NV:RP DATABASES]: Succesfully ensured.");
	return 1;
}

stock mysql_fquery(MySQL:connectionHandle, const fquery[], va_args<>)
{
    mysql_format(connectionHandle, va_query, sizeof(va_query), fquery, va_start<2>);

    mysql_tquery(SQL_Handle(), "START TRANSACTION");
	mysql_tquery(connectionHandle, va_query);
    mysql_tquery(SQL_Handle(), "COMMIT");

    return 1;
}

// Formated mysql_format with direct string returning
stock va_fquery(MySQL:connectionHandle, const fquery[], va_args<>)
{
	mysql_format(connectionHandle, va_query, sizeof(va_query), fquery, va_start<2>);
	return va_query;
}