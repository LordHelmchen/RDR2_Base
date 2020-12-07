#pragma once

namespace hooks
{
	extern void init();
	namespace fiber
	{
		extern void wait_for(DWORD ms);
	}
}