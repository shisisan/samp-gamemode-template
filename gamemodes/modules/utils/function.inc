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

#if defined _inc_function
    #undef _inc_function
#endif

#if defined _function_included
    #endinput
#endif
#define _function_included

stock ReturnName(playerid, underscore=1)
{
    new
        name[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, name, sizeof(name));

    if(!underscore) {
        for (new i = 0, len = strlen(name); i < len; i ++) {
                if(name[i] == '_') name[i] = ' ';
        }
    }
    return name;
}