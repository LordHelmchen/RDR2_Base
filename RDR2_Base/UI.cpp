#include "includes.h"

namespace UI
{

	//Credit: SirMestre 

	using namespace std;
	void DrawSprite(const char* category, const char* sprite, float x, float y, float scalex, float scaley, float rotation, int r, int g, int b, int a)
	{
		auto width = globals::resolution.right,
			height = globals::resolution.bottom;
		x /= width; scalex /= width;
		y /= height; scaley /= height;
		if (!TXD::HAS_STREAMED_TEXTURE_DICT_LOADED(sprite))
			TXD::REQUEST_STREAMED_TEXTURE_DICT(sprite, 0);
		GRAPHICS::DRAW_SPRITE(category, sprite, x, y, scalex, scaley, rotation, r, g, b, a, 1);
		TXD::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(category);
	}

	void draw_Text(string text, float font_size, float x, float y, float r, float g, float b, float a, bool centered = false)
	{
		x /= globals::resolution.right; y /= globals::resolution.bottom;
		font_size /= 100.f;
		HUD::SET_TEXT_SCALE(font_size, font_size);
		HUD::_SET_TEXT_COLOR(r, g, b, a);
		auto str = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text.c_str());
		HUD::_DISPLAY_TEXT(str, x, y);
	}

	void drawRect(float x, float y, float w, float h, int r, int g, int b, int a)
	{
		auto width = globals::resolution.right,
			height = globals::resolution.bottom;
		x /= width; w /= width;
		y /= height; h /= height;

		GRAPHICS::DRAW_RECT(x, y, w, h, r, g, b, a, true, 0);
	}

	void PrintSubtitle(const char* text)
	{
		const char* literalString = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text);
		UILOG::_LOG_SET_CACHED_OBJECTIVE(literalString);
		UILOG::_LOG_PRINT_CACHED_OBJECTIVE();
		UILOG::_LOG_CLEAR_CACHED_OBJECTIVE();
	}


	float menux = 330.f;
	float menuWidth = 450.f;
	float menuHeight = 702.5f;
	float menuy = 246;
	char* currentmenu[100];
	char* actualmenu = (char*)"mainmenu";
	int lastoption[100];
	int menulevel = 0;
	bool menuOpen = true;
	bool rightPress = false;
	int optioncount = 0;
	bool optionPressed = false;
	int currentoption = 0;

	void Header() {
		optioncount = 0;
		drawRect(330.f, 0, 450.f, 702.5f, 0, 0, 0, 255);
		draw_Text("RDR2 base", 50.f, 240.f, 0, 255, 255, 255, 255);

	}

	bool currentMenu(const char* menuname) {
		if (menuname == actualmenu) return true;
		else return false;
	}


	void backMenu() {
		menulevel--;
		actualmenu = currentmenu[menulevel];
		currentoption = lastoption[menulevel];
	}



	bool Option(const char* option) {
		optioncount++;
		bool thisOption = false;
		if (currentoption == optioncount) thisOption = true;

		if (currentoption <= 10 && optioncount <= 10) {
			draw_Text(option, 25, menux - 210.f, ((optioncount * 30.f) + 20), 255, 255, 255, 255);
			if (thisOption) drawRect(menux, ((optioncount * 30.22f) + 26.6), menuWidth, 29.f, 255, 140, 0, 180);
		}

		else if ((optioncount > (currentoption - 10)) && optioncount <= currentoption)
		{
			draw_Text(option, 25, menux - 210.f, (((optioncount - (currentoption - 10)) * 30.f) + 20), 255, 255, 255, 255);
			if (thisOption) drawRect(menux, (((optioncount - (currentoption - 10)) * 30.22f) + 26.6), menuWidth, 29.f, 255, 140, 0, 180);
		}

		if (optionPressed && currentoption == optioncount) return true;
		else return false;
	}

	bool BoolOption(const char* option, bool* isEnabled)
	{
		Option(option);
		if (currentoption <= 10 && optioncount <= 10)
		{
			if (*isEnabled)
			{
				DrawSprite("generic_textures", "tick", menux + 200.f, ((optioncount * 30.f) + 25), 25.0140625f, 25.025f, 0, 255, 255, 255, 255);
			}
			else
			{
				DrawSprite("menu_textures", "cross", menux + 200.f, ((optioncount * 30.f) + 25), 20.0140625f, 20.025f, 0, 255, 255, 255, 255);
			}
		}

		else if ((optioncount > (currentoption - 10)) && optioncount <= currentoption)
		{
			if (*isEnabled)
			{
				DrawSprite("generic_textures", "tick", menux + 200.f, (((optioncount - (currentoption - 10)) * 30.22f) + 31.6), 25.0140625f, 25.025f, 0, 255, 255, 255, 255);
			}
			else
			{
				DrawSprite("menu_textures", "cross", menux + 200.f, (((optioncount - (currentoption - 10)) * 30.22f) + 31.6), 20.0140625f, 20.025f, 0, 255, 255, 255, 255);
			}
		}

		if (optionPressed && currentoption == optioncount) {
			*isEnabled ^= 1;
			return true;
		}
		return false;
	}

	void changeMenu(const char* menuname) {
		currentmenu[menulevel] = actualmenu;
		lastoption[menulevel] = currentoption;
		menulevel++;
		actualmenu = (char*)menuname;
		currentoption = 1;
	}

	bool MenuOption(const char* option, const char* menu) {
		Option(option);
		if (optionPressed && currentoption == optioncount) {
			optionPressed = false;
			changeMenu(menu);
			return true;
		}
		else return false;
	}

	int Delay = GetTickCount64();

	void checkControls()
	{
		optionPressed = false;
		if (GetAsyncKeyState(VK_F8))
		{
			if (GetTickCount() - Delay > 200)
			{
				menuOpen = !menuOpen;
				Delay = GetTickCount();
			}
		}
		if (menuOpen)
		{
			if (GetAsyncKeyState(VK_RETURN))
			{
				if (GetTickCount() - Delay > 200)
				{
					optionPressed = true;
					AUDIO::PLAY_SOUND_FRONTEND("SELECT", "HUD_SHOP_SOUNDSET", true, 0);
					Delay = GetTickCount();
				}
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (GetTickCount() - Delay > 200)
				{
					if (currentoption < optioncount)
						currentoption++;
					else

						currentoption = 1;
					Delay = GetTickCount();
				}
			}
			if (GetAsyncKeyState(VK_UP))
			{
				if (GetTickCount() - Delay > 200)
				{
					if (currentoption > 1)
						currentoption--;
					else
						currentoption = optioncount;
					Delay = GetTickCount();
				}
			}
			if (GetAsyncKeyState(VK_BACK))
			{
				if (GetTickCount() - Delay > 200)
				{
					if (menulevel != 0)
					{
						menulevel--;
						actualmenu = currentmenu[menulevel];
						currentoption = lastoption[menulevel];
					}
					else
					{
						menuOpen = false;
					}
					Delay = GetTickCount();
				}
			}
		}

	}
}