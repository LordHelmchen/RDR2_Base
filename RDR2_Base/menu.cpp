#include "includes.h"

namespace variables
{
	bool godmode;
	Player selectedPlayer;
}

namespace menu
{
	void updateMenu()
	{
		if (UI::menuOpen)
		{
			if (UI::currentMenu("mainmenu"))
			{
				UI::Header();
				UI::MenuOption("Self", "Self");
				UI::MenuOption("Online players", "online");
			}
			if (UI::currentMenu("Self"))
			{
				UI::Header();
				if (UI::BoolOption("godmode", &variables::godmode))
				{
					ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), variables::godmode);
				}
			}
			if (UI::currentMenu("online"))
			{
				UI::Header();
				for (int i = 0; i < NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS(); i++)
				{
					if (UI::MenuOption(PLAYER::GET_PLAYER_NAME(i), "online_player"))
					{
						variables::selectedPlayer = i;
					}
				}
			}
			if (UI::currentMenu("online_player"))
			{
				UI::Header();
				if (UI::Option("Teleport to player"))
				{
					Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED(variables::selectedPlayer), true, true);
					ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), pos.x, pos.y, pos.z, true, true, true, false);
				}
			}
		}
	}
}