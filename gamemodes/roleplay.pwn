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

    - Author :
        {
            [
                Owner & Developer: Thouthan 1
            ]
        }
*/

#pragma warning disable 239
#pragma warning disable 214

#define YSI_YES_HEAP_MALLOC
#define YSI_NO_VERSION_CHECK
#define YSI_NO_MODE_CACHE
#define YSI_NO_OPTIMISATION_MESSAGE

#define FOREACH_NO_BOTS
#define FOREACH_NO_STREAMED

#include <a_samp>
#include <a_mysql>
#include <chrono>
#include <streamer>
#include <sscanf2>
#include <env>
#include <samp_bcrypt>
#include <jit>

#include <YSF>
#include <YSI_Coding\y_unique>
#include <YSI_Coding\y_timers>
#include <YSI_Coding\y_iterate>
#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_va>
#include <YSI_Coding\y_inline>
#include <YSI_Server\y_colours>
#include <YSI_Visual\y_commands>
#include <YSI_Visual\y_dialog>

#include <YSI_Extra\y_inline_mysql>
#include <YSI_Extra\y_inline_bcrypt>

/** Modules */
#include <macro>
#include <database>
#include <function>
#include <account>

/** Forwarding */
forward OnGameModeInitEx();
forward OnJITCompile();

main()
{
    new
		Timestamp: ts = Timestamp: Now(),
		string: time_format[24];

    OnJITCompile();
	TimeFormat(Timestamp: ts, ISO6801_TIME, string: time_format, sizeof(time_format));
    printf("[NV:RP JIT]: JIT says %s", (IsJITPresent() ? ("Is not present.") : ("Is present.")));
    printf("[NV:RP]: Started Initialize %s.", string: time_format);
}


public OnGameModeInit()
{
    CallLocalFunction(#OnGameModeInitEx, "");
    return 1;
}

public OnGameModeExit()
{
    return 1;
}

public OnJITCompile()
{
	printf("[NV:RP JIT]: OnJITCompile->JIT %s", (IsJITPresent() ? ("Is not present.") : ("Is present.")));
	return 1;
}
