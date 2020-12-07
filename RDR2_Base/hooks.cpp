#include "includes.h"


namespace hooks
{

	using namespace std;

	typedef BOOL(__fastcall* is_cam_active_fn)(__int64 a1, __int64 a2);

	namespace original
	{
		is_cam_active_fn o_is_cam_active;
	}


	void main()
	{
		menu::updateMenu();
		UI::checkControls();
		features::updateFeatures();
	}


	namespace fiber {
		static HANDLE main_fiber = nullptr;
		static DWORD time_to_wake_up = 0;

		void wait_for(DWORD ms) {
			time_to_wake_up = timeGetTime() + ms;
			SwitchToFiber(main_fiber);
		}

		void __stdcall fiber_thread(LPVOID params) {
			srand(GetTickCount64());
			while (true) {

				main();
				wait_for(0);
			}
		}

		void on_tick() {
			if (!main_fiber)
				main_fiber = ConvertThreadToFiber(nullptr);

			if (time_to_wake_up > timeGetTime())
				return;

			static HANDLE fiber_handle = nullptr;
			if (fiber_handle) {
				SwitchToFiber(fiber_handle);
			}
			else {
				fiber_handle = CreateFiber(NULL, fiber_thread, nullptr);
			}
		}
	}


	BOOL __fastcall is_cam_active_hook(__int64 a1, __int64 a2)
	{
		fiber::on_tick();
		return original::o_is_cam_active(a1, a2);
	}



	void init()
	{
#ifdef CONSOLE
		if (AllocConsole()) {
			freopen("CONIN$", "r", stdin);
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
		}
#endif

		auto hwnd_ = FindWindowA(0, "Red Dead Redemption 2");
		GetWindowRect(hwnd_, &globals::resolution);

		auto status = MH_Initialize();
		auto is_cam_active = (void*)get_handler(0x153AD457764FD704);
		status = MH_CreateHook(is_cam_active, is_cam_active_hook, reinterpret_cast<void**>(&original::o_is_cam_active));
		cout << MH_StatusToString(status) << endl;
		status = MH_EnableHook((LPVOID)is_cam_active);
		cout << MH_StatusToString(status) << endl;
	}
}