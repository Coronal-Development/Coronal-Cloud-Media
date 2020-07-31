#ifndef MERI_COVER_TO_SDL_KEY_MAP_H_
#define MERI_COVER_TO_SDL_KEY_MAP_H_
#include "common/common.h"
#include "SDL2/SDL_keycode.h"
#include <algorithm>
namespace meri
{
	static std::map<int, std::pair<SDL_Keycode, unsigned short>> kKeyBoardMapSdlkeyAndScancode = {
	{8 , {SDLK_BACKSPACE, SDL_SCANCODE_BACKSPACE}},
	{9 , {SDLK_TAB, SDL_SCANCODE_TAB}},
	{13, {SDLK_RETURN, SDL_SCANCODE_RETURN}},
	{16, {SDLK_LSHIFT, SDL_SCANCODE_LSHIFT}},
	{17, {SDLK_LCTRL, SDL_SCANCODE_LCTRL}},
	{18, {SDLK_LALT, SDL_SCANCODE_LALT}},
	{19, {SDLK_PAUSE, SDL_SCANCODE_PAUSE}},
	{27, {SDLK_ESCAPE, SDL_SCANCODE_ESCAPE}},
	{32, {SDLK_SPACE, SDL_SCANCODE_SPACE}},
	{33, {SDLK_PAGEUP, SDL_SCANCODE_PAGEUP}},
	{34, {SDLK_PAGEDOWN, SDL_SCANCODE_PAGEDOWN}},
	{35, {SDLK_END, SDL_SCANCODE_END}},
	{36, {SDLK_HOME, SDL_SCANCODE_HOME}},
	{37, {SDLK_LEFT, SDL_SCANCODE_LEFT}},
	{38, {SDLK_UP, SDL_SCANCODE_UP}},
	{39, {SDLK_RIGHT, SDL_SCANCODE_RIGHT}},
	{40, {SDLK_DOWN, SDL_SCANCODE_DOWN}},
	{45, {SDLK_INSERT, SDL_SCANCODE_INSERT}},
	{46, {SDLK_DELETE, SDL_SCANCODE_DELETE}},
	{48, {SDLK_0, SDL_SCANCODE_0}},
	{49, {SDLK_1, SDL_SCANCODE_1}},
	{50, {SDLK_2, SDL_SCANCODE_2}},
	{51, {SDLK_3, SDL_SCANCODE_3}},
	{52, {SDLK_4, SDL_SCANCODE_4}},
	{53, {SDLK_5, SDL_SCANCODE_5}},
	{54, {SDLK_6, SDL_SCANCODE_6}},
	{55, {SDLK_7, SDL_SCANCODE_7}},
	{56, {SDLK_8, SDL_SCANCODE_8}},
	{57, {SDLK_9, SDL_SCANCODE_9}},
	{65, {SDLK_a, SDL_SCANCODE_A}},
	{66, {SDLK_b, SDL_SCANCODE_B}},
	{67, {SDLK_c, SDL_SCANCODE_C}},
	{68, {SDLK_d, SDL_SCANCODE_D}},
	{69, {SDLK_e, SDL_SCANCODE_E}},
	{70, {SDLK_f, SDL_SCANCODE_F}},
	{71, {SDLK_g, SDL_SCANCODE_G}},
	{72, {SDLK_h, SDL_SCANCODE_H}},
	{73, {SDLK_i, SDL_SCANCODE_I}},
	{74, {SDLK_j, SDL_SCANCODE_J}},
	{75, {SDLK_k, SDL_SCANCODE_K}},
	{76, {SDLK_l, SDL_SCANCODE_L}},
	{77, {SDLK_m, SDL_SCANCODE_M}},
	{78, {SDLK_n, SDL_SCANCODE_N}},
	{79, {SDLK_o, SDL_SCANCODE_O}},
	{80, {SDLK_p, SDL_SCANCODE_P}},
	{81, {SDLK_q, SDL_SCANCODE_Q}},
	{82, {SDLK_r, SDL_SCANCODE_R}},
	{83, {SDLK_s, SDL_SCANCODE_S}},
	{84, {SDLK_t, SDL_SCANCODE_T}},
	{85, {SDLK_u, SDL_SCANCODE_U}},
	{86, {SDLK_v, SDL_SCANCODE_V}},
	{87, {SDLK_w, SDL_SCANCODE_W}},
	{88, {SDLK_x, SDL_SCANCODE_X}},
	{89, {SDLK_y, SDL_SCANCODE_Y}},
	{90, {SDLK_z, SDL_SCANCODE_Z}},
	{96, {SDLK_KP_0, SDL_SCANCODE_KP_0}},
	{97, {SDLK_KP_1, SDL_SCANCODE_KP_1}},
	{98, {SDLK_KP_2, SDL_SCANCODE_KP_2}},
	{99, {SDLK_KP_3, SDL_SCANCODE_KP_3}},
	{100, {SDLK_KP_4, SDL_SCANCODE_KP_4}},
	{101, {SDLK_KP_5, SDL_SCANCODE_KP_5}},
	{102, {SDLK_KP_6, SDL_SCANCODE_KP_6}},
	{103, {SDLK_KP_7, SDL_SCANCODE_KP_7}},
	{104, {SDLK_KP_8, SDL_SCANCODE_KP_8}},
	{105, {SDLK_KP_9, SDL_SCANCODE_KP_9}},
	{106, {SDLK_KP_MULTIPLY, SDL_SCANCODE_KP_MULTIPLY}},
	{107, {SDLK_KP_PLUSMINUS, SDL_SCANCODE_KP_PLUSMINUS}},
	{109, {SDLK_MINUS, SDL_SCANCODE_KP_MINUS}},
	{110, {SDLK_KP_PERIOD, SDL_SCANCODE_KP_PERIOD}},
	{111, {SDLK_SLASH, SDL_SCANCODE_SLASH}},
	{112, {SDLK_F1, SDL_SCANCODE_F1}},
	{113, {SDLK_F2, SDL_SCANCODE_F2}},
	{114, {SDLK_F3, SDL_SCANCODE_F3}},
	{115, {SDLK_F4, SDL_SCANCODE_F4}},
	{116, {SDLK_F5, SDL_SCANCODE_F5}},
	{117, {SDLK_F6, SDL_SCANCODE_F6}},
	{118, {SDLK_F7, SDL_SCANCODE_F7}},
	{119, {SDLK_F8, SDL_SCANCODE_F8}},
	{120, {SDLK_F9, SDL_SCANCODE_F9}},
	{121, {SDLK_F10, SDL_SCANCODE_F10}},
	{122, {SDLK_F11, SDL_SCANCODE_F11}},
	{123, {SDLK_F12, SDL_SCANCODE_F12}},
	{144, {SDLK_NUMLOCKCLEAR, SDL_SCANCODE_NUMLOCKCLEAR}},
	{145, {SDLK_SCROLLLOCK, SDL_SCANCODE_SCROLLLOCK}},
	{186, {SDLK_SEMICOLON , SDL_SCANCODE_SEMICOLON}},
	{187, {SDLK_PLUS, SDL_SCANCODE_KP_PLUS}},
	{188, {SDLK_COMMA, SDL_SCANCODE_COMMA}},
	{189, {SDLK_MINUS,SDL_SCANCODE_KP_MINUS }},
	{190, {SDLK_PERIOD, SDL_SCANCODE_PERIOD}},
	{191, {SDLK_SLASH, SDL_SCANCODE_SLASH}},
	{192, {SDLK_BACKQUOTE, SDL_SCANCODE_GRAVE}},
	{219, {SDLK_LEFTBRACKET, SDL_SCANCODE_LEFTBRACKET}},
	{220, {SDLK_BACKSLASH, SDL_SCANCODE_BACKSLASH}},
	{221, {SDLK_RIGHTBRACKET, SDL_SCANCODE_RIGHTBRACKET}},
	{222, {SDLK_QUOTE,SDL_SCANCODE_APOSTROPHE }}
	};

	static std::map<unsigned short, unsigned short> kSdlMapWindosSystemkey{};
	static void InitSystemkSdlMapWindosSystemkeytoSDL()
	{
		kSdlMapWindosSystemkey[SDLK_BACKSPACE] = VK_BACK;
		kSdlMapWindosSystemkey[SDLK_TAB] = VK_TAB;
		kSdlMapWindosSystemkey[SDLK_CLEAR] = VK_CLEAR;
		kSdlMapWindosSystemkey[SDLK_RETURN] = VK_RETURN;
		kSdlMapWindosSystemkey[SDLK_PAUSE] = VK_PAUSE;
		kSdlMapWindosSystemkey[SDLK_ESCAPE] = VK_ESCAPE;
		kSdlMapWindosSystemkey[SDLK_SPACE] = VK_SPACE;
		kSdlMapWindosSystemkey[SDLK_QUOTEDBL] = VK_OEM_7;
		kSdlMapWindosSystemkey[SDLK_QUOTE] = VK_OEM_7;
		kSdlMapWindosSystemkey[SDLK_PLUS] = VK_OEM_PLUS;
		kSdlMapWindosSystemkey[SDLK_COMMA] = VK_OEM_COMMA;
		kSdlMapWindosSystemkey[SDLK_MINUS] = VK_OEM_MINUS;
		kSdlMapWindosSystemkey[SDLK_PERIOD] = VK_OEM_PERIOD;
		kSdlMapWindosSystemkey[SDLK_SLASH] = VK_OEM_2;
		kSdlMapWindosSystemkey[SDLK_COLON] = VK_OEM_1;
		kSdlMapWindosSystemkey[SDLK_SEMICOLON] = VK_OEM_1;
		kSdlMapWindosSystemkey[SDLK_LESS] = VK_OEM_COMMA;
		kSdlMapWindosSystemkey[SDLK_EQUALS] = VK_OEM_PLUS;
		kSdlMapWindosSystemkey[SDLK_GREATER] = VK_OEM_PERIOD;
		kSdlMapWindosSystemkey[SDLK_QUESTION] = VK_OEM_2;
		kSdlMapWindosSystemkey[SDLK_LEFTBRACKET] = VK_OEM_4;
		kSdlMapWindosSystemkey[SDLK_BACKSLASH] = VK_OEM_5;
		kSdlMapWindosSystemkey[SDLK_RIGHTBRACKET] = VK_OEM_6;
		kSdlMapWindosSystemkey[SDLK_UNDERSCORE] = VK_OEM_MINUS;
		kSdlMapWindosSystemkey[SDLK_BACKQUOTE] = VK_OEM_3;
		for (auto i = 0x30; i <= 0x39; i++) {
			kSdlMapWindosSystemkey[i] = i;
		}
		for (auto i = 0x61; i <= 0x7a; i++) {
			kSdlMapWindosSystemkey[i] = i & 0xdf;
		}
		kSdlMapWindosSystemkey[SDLK_DELETE] = VK_DELETE;
		kSdlMapWindosSystemkey[SDLK_KP_0] = VK_NUMPAD0;
		kSdlMapWindosSystemkey[SDLK_KP_1] = VK_NUMPAD1;
		kSdlMapWindosSystemkey[SDLK_KP_2] = VK_NUMPAD2;
		kSdlMapWindosSystemkey[SDLK_KP_3] = VK_NUMPAD3;
		kSdlMapWindosSystemkey[SDLK_KP_4] = VK_NUMPAD4;
		kSdlMapWindosSystemkey[SDLK_KP_5] = VK_NUMPAD5;
		kSdlMapWindosSystemkey[SDLK_KP_6] = VK_NUMPAD6;
		kSdlMapWindosSystemkey[SDLK_KP_7] = VK_NUMPAD7;
		kSdlMapWindosSystemkey[SDLK_KP_8] = VK_NUMPAD8;
		kSdlMapWindosSystemkey[SDLK_KP_9] = VK_NUMPAD9;
		kSdlMapWindosSystemkey[SDLK_KP_PERIOD] = VK_DECIMAL;
		kSdlMapWindosSystemkey[SDLK_KP_DIVIDE] = VK_DIVIDE;
		kSdlMapWindosSystemkey[SDLK_KP_MULTIPLY] = VK_MULTIPLY;
		kSdlMapWindosSystemkey[SDLK_KP_MINUS] = VK_SUBTRACT;
		kSdlMapWindosSystemkey[SDLK_KP_PLUS] = VK_ADD;
		kSdlMapWindosSystemkey[SDLK_UP] = VK_UP;
		kSdlMapWindosSystemkey[SDLK_DOWN] = VK_DOWN;
		kSdlMapWindosSystemkey[SDLK_RIGHT] = VK_RIGHT;
		kSdlMapWindosSystemkey[SDLK_LEFT] = VK_LEFT;
		kSdlMapWindosSystemkey[SDLK_INSERT] = VK_INSERT;
		kSdlMapWindosSystemkey[SDLK_HOME] = VK_HOME;
		kSdlMapWindosSystemkey[SDLK_END] = VK_END;
		kSdlMapWindosSystemkey[SDLK_PAGEUP] = VK_PRIOR;
		kSdlMapWindosSystemkey[SDLK_PAGEDOWN] = VK_NEXT;
		kSdlMapWindosSystemkey[SDLK_F1] = VK_F1;
		kSdlMapWindosSystemkey[SDLK_F2] = VK_F2;
		kSdlMapWindosSystemkey[SDLK_F3] = VK_F3;
		kSdlMapWindosSystemkey[SDLK_F4] = VK_F4;
		kSdlMapWindosSystemkey[SDLK_F5] = VK_F5;
		kSdlMapWindosSystemkey[SDLK_F6] = VK_F6;
		kSdlMapWindosSystemkey[SDLK_F7] = VK_F7;
		kSdlMapWindosSystemkey[SDLK_F8] = VK_F8;
		kSdlMapWindosSystemkey[SDLK_F9] = VK_F9;
		kSdlMapWindosSystemkey[SDLK_F10] = VK_F10;
		kSdlMapWindosSystemkey[SDLK_F11] = VK_F11;
		kSdlMapWindosSystemkey[SDLK_F12] = VK_F12;
		kSdlMapWindosSystemkey[SDLK_F13] = VK_F13;
		kSdlMapWindosSystemkey[SDLK_F14] = VK_F14;
		kSdlMapWindosSystemkey[SDLK_F15] = VK_F15;
		kSdlMapWindosSystemkey[SDLK_NUMLOCKCLEAR] = VK_NUMLOCK;
		kSdlMapWindosSystemkey[SDLK_CAPSLOCK] = VK_CAPITAL;
		kSdlMapWindosSystemkey[SDLK_SCROLLLOCK] = VK_SCROLL;
		kSdlMapWindosSystemkey[SDLK_RSHIFT] = VK_RSHIFT;
		kSdlMapWindosSystemkey[SDLK_LSHIFT] = VK_LSHIFT;
		kSdlMapWindosSystemkey[SDLK_RCTRL] = VK_RCONTROL;
		kSdlMapWindosSystemkey[SDLK_LCTRL] = VK_LCONTROL;
		kSdlMapWindosSystemkey[SDLK_RALT] = VK_RMENU;
		kSdlMapWindosSystemkey[SDLK_LALT] = VK_LMENU;
		kSdlMapWindosSystemkey[SDLK_RGUI] = VK_RWIN;
		kSdlMapWindosSystemkey[SDLK_LGUI] = VK_LWIN;
		kSdlMapWindosSystemkey[SDLK_MODE] = VK_MODECHANGE;
		kSdlMapWindosSystemkey[SDLK_HELP] = VK_HELP;
		kSdlMapWindosSystemkey[SDLK_PRINTSCREEN] = VK_CANCEL;
		kSdlMapWindosSystemkey[SDLK_MENU] = VK_MENU;
	}

	std::tuple<unsigned short, unsigned short> CoverToSDLkey(uint32_t keyboard_which_button)
	{
		auto it = kKeyBoardMapSdlkeyAndScancode.find(keyboard_which_button);
		if (it != kKeyBoardMapSdlkeyAndScancode.end())
		{
			return it->second;
		}
		return{ 0,0 };
	}

	unsigned short CoverToSystemkey(unsigned short sdl_which_key)
	{
		static bool init_system_map_flag = true;
		if (init_system_map_flag)
		{
			InitSystemkSdlMapWindosSystemkeytoSDL();
			init_system_map_flag = false;
		}
		
		auto it = kSdlMapWindosSystemkey.find(sdl_which_key);
		if (it != kSdlMapWindosSystemkey.end())
		{
			return it->second;
		}
		return 0;
	}
}

#endif // !MERI_COVER_TO_SDL_KEY_MAP_H_
