#include "includes.h"

namespace features
{
	//All features that have to be updated every tick come in that function
	void updateFeatures()
	{

	}

	void teleport(Vector3 pos)
	{
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), pos.x, pos.y, pos.z, true, true, true, false);
	}
}