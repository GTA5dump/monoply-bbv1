#pragma once
#include "Discord_RPC.h"
#include "Discord_Register.h"


namespace monopoly
{
	class discordhandler
	{
	public:
		void Init();
		void Tick(); // to the menu not rpc
		void Shutdown(); // show
	};
	inline std::unique_ptr<discordhandler> g_Discord;
}