﻿#include "notifications/notifications.h"
#include "fiber_pool.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"
#include "gui/list/script/MainScript.hpp"
#include "gui/list/UIManager.hpp"
#include "features.hpp"
#include "../discord_rpc.h"







BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	using namespace monopoly;
	if (reason == DLL_PROCESS_ATTACH)
	{

		DisableThreadLibraryCalls(hmod);

		g_hmodule = hmod;
		g_main_thread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
		{
			while (!FindWindow(L"grcWindow", L"Grand Theft Auto V"))
				std::this_thread::sleep_for(1s);

			auto logger_instance = std::make_unique<logger>();
			try
			{
				LOG(RAW_GREEN_TO_CONSOLE) << u8R"kek(
                                                                  
                                                                                               
                                                                                        
				                                                                               
                                                                                        
          ____                                                        ,--,              
        ,'  , `.                                ,-.----.            ,--.'|              
     ,-+-,.' _ |   ,---.        ,---,    ,---.  \    /  \    ,---.  |  | :              
  ,-+-. ;   , ||  '   ,'\   ,-+-. /  |  '   ,'\ |   :    |  '   ,'\ :  : '              
 ,--.'|'   |  || /   /   | ,--.'|'   | /   /   ||   | .\ : /   /   ||  ' |        .--,  
|   |  ,', |  |,.   ; ,. :|   |  ,"' |.   ; ,. :.   : |: |.   ; ,. :'  | |      /_ ./|  
|   | /  | |--' '   | |: :|   | /  | |'   | |: :|   |  \ :'   | |: :|  | :   , ' , ' :  
|   : |  | ,    '   | .; :|   | |  | |'   | .; :|   : .  |'   | .; :'  : |__/___/ \: |  
|   : |  |/     |   :    ||   | |  |/ |   :    |:     |`-'|   :    ||  | '.'|.  \  ' |  
|   | |`-'       \   \  / |   | |--'   \   \  / :   : :    \   \  / ;  :    ; \  ;   :  
|   ;/            `----'  |   |/        `----'  |   | :     `----'  |  ,   /   \  \  ;  
'---'                     '---'                 `---'.|              ---`-'     :  \  \ 
                                                  `---`                          \  ' ; 
                                                                                  `--`  
																										 )kek";



		

				auto pointers_instance = std::make_unique<pointers>();
				LOG(INFO) << "Pointers initialized.";

				auto renderer_instance = std::make_unique<renderer>();
				LOG(INFO) << "Renderer initialized.";

				auto fiber_pool_instance = std::make_unique<fiber_pool>(10);
				LOG(INFO) << "Fiber pool initialized.";
				
				auto hooking_instance = std::make_unique<hooking>();
				LOG(INFO) << "Hooking initialized.";
				
				auto uimanager_instance = std::make_unique<UserInterface::UIManager>();
				LOG(INFO) << "UIManager initialized.";

				
		
				g_hooking->enable();
				LOG(INFO) << "Hooking enabled.";
				
				g_script_mgr.add_script(std::make_unique<script>(&gui::script_func));
				g_script_mgr.add_script(std::make_unique<script>(&MainScript::script_func));
				g_script_mgr.add_script(std::make_unique<script>(&features::script_func));
				LOG(INFO) << "Scripts registered.";

				
				
				
				

				Notify("Welcome to 0.2.0", "", 7000, None);
				Notify("Open With INSERT", "", 7000, Protections);
				while (g_running)
				{
				
					std::this_thread::sleep_for(500ms);
				}

				features::DiscordInit();
				
				g_hooking->disable();
				LOG(INFO) << "Hooking disabled.";

				std::this_thread::sleep_for(1000ms);

				g_script_mgr.remove_all_scripts();
				LOG(INFO) << "Scripts unregistered.";


				uimanager_instance.reset();
				LOG(INFO) << "UIManager uninitialized.";

				hooking_instance.reset();
				LOG(INFO) << "Hooking uninitialized.";

				fiber_pool_instance.reset();
				LOG(INFO) << "Fiber pool uninitialized.";

				renderer_instance.reset();
				LOG(INFO) << "Renderer uninitialized.";

				pointers_instance.reset();
				LOG(INFO) << "Pointers uninitialized.";
				
			}
			catch (std::exception const &ex)
			{
				LOG(WARNING) << ex.what();
				MessageBoxA(nullptr, ex.what(), nullptr, MB_OK | MB_ICONEXCLAMATION);
			}
			Discord_Shutdown();
			LOG(INFO_TO_FILE) << "Uninjected Succesfully!";
			logger_instance.reset();
			CloseHandle(g_main_thread);
			FreeLibraryAndExitThread(g_hmodule, 0);
		}, nullptr, 0, &g_main_thread_id);
	}

	return true;
}
