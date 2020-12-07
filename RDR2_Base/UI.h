#pragma once

namespace UI
{
	extern void checkControls();
	extern bool menuOpen;
	extern void Header();
	extern bool Option(const char* option);
	extern bool currentMenu(const char* menuname);
	extern bool MenuOption(const char* option, const char* menu);
	extern bool BoolOption(const char* option, bool* isEnabled);
	extern void PrintSubtitle(const char* text);
}