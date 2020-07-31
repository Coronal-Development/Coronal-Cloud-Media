#include "Controller.h"
#include <SDL2/SDL_keycode.h>

// only support SDL2: remap key codes 1.2 -> 2.0
#define	SDLK_KP0	SDLK_KP_0
#define	SDLK_KP1	SDLK_KP_1
#define	SDLK_KP2	SDLK_KP_2
#define	SDLK_KP3	SDLK_KP_3
#define	SDLK_KP4	SDLK_KP_4
#define	SDLK_KP5	SDLK_KP_5
#define	SDLK_KP6	SDLK_KP_6
#define	SDLK_KP7	SDLK_KP_7
#define	SDLK_KP8	SDLK_KP_8
#define	SDLK_KP9	SDLK_KP_9
//
#define SDLK_NUMLOCK	SDLK_NUMLOCKCLEAR
#define SDLK_SCROLLOCK	SDLK_SCROLLLOCK
#define SDLK_RMETA	SDLK_RGUI
#define SDLK_LMETA	SDLK_LGUI
//#define SDLK_LSUPER
//#define SDLK_RSUPER
//#define SDLK_COMPOSE
//#define SDLK_PRINT
#define SDLK_BREAK	SDLK_PRINTSCREEN

namespace meri
{
	Controller::~Controller()
	{
		if (work_rect_ != nullptr)
		{
			delete work_rect_;
			work_rect_ = nullptr;
		}
	}
	int Controller::Init(void* merirect)
	{
		meri::MeriRect* rect = reinterpret_cast<meri::MeriRect*>(merirect);
		work_rect_->x_ = rect->x_;
		work_rect_->y_ = rect->y_;
		work_rect_->width_ = rect->width_ +1;
		work_rect_->height_ = rect->height_ + 1;
		work_rect_->linesize_ = work_rect_->width_ * 4;
		work_rect_->size_ = work_rect_->width_ * work_rect_->height_ * 4;
		return work_rect_->size_ > 10 ? true : false;
	}

	int Controller::Start(void* args)
	{
		return 0;
	}
	
	int Controller::Stop(void* args)
	{
		return 0;
	}
	
	int Controller::Deinit(void* args)
	{
		return 0;
	}
	
	int Controller::IOCtrl(int command, int argsize, void* arg)
	{
		return 0;
	}

	int Controller::Notify(void* args)
	{
		return 0;
	}

	int Controller::Raw(void* arg, int* size)
	{
		return 0;
	}

	Controller::Controller()
		:work_rect_(new MeriRect())
	{
	}

    void MapSdlKeyToSystem()
    {
        auto& keymap = meri::Controller::GetInstance()->keymap_;
		unsigned short i;
		//
		keymap[SDLK_BACKSPACE] = VK_BACK;		//		= 8,
		keymap[SDLK_TAB] = VK_TAB;		//		= 9,
		keymap[SDLK_CLEAR] = VK_CLEAR;		//		= 12,
		keymap[SDLK_RETURN] = VK_RETURN;		//		= 13,
		keymap[SDLK_PAUSE] = VK_PAUSE;		//		= 19,
		keymap[SDLK_ESCAPE] = VK_ESCAPE;		//		= 27,
		// Latin 1: starting from space (0x20)
		keymap[SDLK_SPACE] = VK_SPACE;		//		= 32,
		// (0x20) space, exclam, quotedbl, numbersign, dollar, percent, ampersand,
		// (0x27) quoteright, parentleft, parentright, asterisk, plus, comma,
		// (0x2d) minus, period, slash
		//SDLK_EXCLAIM		= 33,
		keymap[SDLK_QUOTEDBL] = VK_OEM_7;		//		= 34,
		//SDLK_HASH		= 35,
		//SDLK_DOLLAR		= 36,
		//SDLK_AMPERSAND		= 38,
		keymap[SDLK_QUOTE] = VK_OEM_7;		//		= 39,
		//SDLK_LEFTPAREN		= 40,
		//SDLK_RIGHTPAREN		= 41,
		//SDLK_ASTERISK		= 42,
		keymap[SDLK_PLUS] = VK_OEM_PLUS;		//		= 43,
		keymap[SDLK_COMMA] = VK_OEM_COMMA;		//		= 44,
		keymap[SDLK_MINUS] = VK_OEM_MINUS;		//		= 45,
		keymap[SDLK_PERIOD] = VK_OEM_PERIOD;	//		= 46,
		keymap[SDLK_SLASH] = VK_OEM_2;		//		= 47,
		keymap[SDLK_COLON] = VK_OEM_1;		//		= 58,
		keymap[SDLK_SEMICOLON] = VK_OEM_1;		//		= 59,
		keymap[SDLK_LESS] = VK_OEM_COMMA;		//		= 60,
		keymap[SDLK_EQUALS] = VK_OEM_PLUS;		//		= 61,
		keymap[SDLK_GREATER] = VK_OEM_PERIOD;	//		= 62,
		keymap[SDLK_QUESTION] = VK_OEM_2;		//		= 63,
		//SDLK_AT			= 64,
		/*
		   Skip uppercase letters
		 */
		keymap[SDLK_LEFTBRACKET] = VK_OEM_4;		//		= 91,
		keymap[SDLK_BACKSLASH] = VK_OEM_5;		//		= 92,
		keymap[SDLK_RIGHTBRACKET] = VK_OEM_6;		//		= 93,
		//SDLK_CARET		= 94,
		keymap[SDLK_UNDERSCORE] = VK_OEM_MINUS;		//		= 95,
		keymap[SDLK_BACKQUOTE] = VK_OEM_3;		//		= 96,
		// (0x30-0x39) 0-9
		for (i = 0x30; i <= 0x39; i++) {
			keymap[i] = i;
		}
		// (0x3a) colon, semicolon, less, equal, greater, question, at
		// (0x41-0x5a) A-Z
		// SDL: no upper cases, only lower cases
		// (0x5b) bracketleft, backslash, bracketright, asciicircum/caret,
		// (0x5f) underscore, grave
		// (0x61-7a) a-z
		for (i = 0x61; i <= 0x7a; i++) {
			keymap[i] = i & 0xdf;	// convert to uppercases
		}
		keymap[SDLK_DELETE] = VK_DELETE;		//		= 127,
		// SDLK_WORLD_0 (0xa0) - SDLK_WORLD_95 (0xff) are ignored
		/** @name Numeric keypad */
		keymap[SDLK_KP_0] = VK_NUMPAD0;	//		= 256,
		keymap[SDLK_KP_1] = VK_NUMPAD1;	//		= 257,
		keymap[SDLK_KP_2] = VK_NUMPAD2;	//		= 258,
		keymap[SDLK_KP_3] = VK_NUMPAD3;	//		= 259,
		keymap[SDLK_KP_4] = VK_NUMPAD4;	//		= 260,
		keymap[SDLK_KP_5] = VK_NUMPAD5;	//		= 261,
		keymap[SDLK_KP_6] = VK_NUMPAD6;	//		= 262,
		keymap[SDLK_KP_7] = VK_NUMPAD7;	//		= 263,
		keymap[SDLK_KP_8] = VK_NUMPAD8;	//		= 264,
		keymap[SDLK_KP_9] = VK_NUMPAD9;	//		= 265,
		keymap[SDLK_KP_PERIOD] = VK_DECIMAL;	//		= 266,
		keymap[SDLK_KP_DIVIDE] = VK_DIVIDE;	//		= 267,
		keymap[SDLK_KP_MULTIPLY] = VK_MULTIPLY;	//		= 268,
		keymap[SDLK_KP_MINUS] = VK_SUBTRACT;	//		= 269,
		keymap[SDLK_KP_PLUS] = VK_ADD;	//		= 270,
		//keymap[SDLK_KP_ENTER]	= XK_KP_Enter;	//		= 271,
		//keymap[SDLK_KP_EQUALS]	= XK_KP_Equal;	//		= 272,
		/** @name Arrows + Home/End pad */
		keymap[SDLK_UP] = VK_UP;	//		= 273,
		keymap[SDLK_DOWN] = VK_DOWN;	//		= 274,
		keymap[SDLK_RIGHT] = VK_RIGHT;	//		= 275,
		keymap[SDLK_LEFT] = VK_LEFT;	//		= 276,
		keymap[SDLK_INSERT] = VK_INSERT;	//		= 277,
		keymap[SDLK_HOME] = VK_HOME;	//		= 278,
		keymap[SDLK_END] = VK_END;	//		= 279,
		keymap[SDLK_PAGEUP] = VK_PRIOR;	//		= 280,
		keymap[SDLK_PAGEDOWN] = VK_NEXT;	//		= 281,
		/** @name Function keys */
		keymap[SDLK_F1] = VK_F1;	//		= 282,
		keymap[SDLK_F2] = VK_F2;	//		= 283,
		keymap[SDLK_F3] = VK_F3;	//		= 284,
		keymap[SDLK_F4] = VK_F4;	//		= 285,
		keymap[SDLK_F5] = VK_F5;	//		= 286,
		keymap[SDLK_F6] = VK_F6;	//		= 287,
		keymap[SDLK_F7] = VK_F7;	//		= 288,
		keymap[SDLK_F8] = VK_F8;	//		= 289,
		keymap[SDLK_F9] = VK_F9;	//		= 290,
		keymap[SDLK_F10] = VK_F10;	//		= 291,
		keymap[SDLK_F11] = VK_F11;	//		= 292,
		keymap[SDLK_F12] = VK_F12;	//		= 293,
		keymap[SDLK_F13] = VK_F13;	//		= 294,
		keymap[SDLK_F14] = VK_F14;	//		= 295,
		keymap[SDLK_F15] = VK_F15;	//		= 296,
		/** @name Key state modifier keys */
		keymap[SDLK_NUMLOCKCLEAR] = VK_NUMLOCK;	//		= 300,
		keymap[SDLK_CAPSLOCK] = VK_CAPITAL;	//		= 301,
		keymap[SDLK_SCROLLLOCK] = VK_SCROLL;	//		= 302,
		keymap[SDLK_RSHIFT] = VK_RSHIFT;	//		= 303,
		keymap[SDLK_LSHIFT] = VK_LSHIFT;	//		= 304,
		keymap[SDLK_RCTRL] = VK_RCONTROL;	//		= 305,
		keymap[SDLK_LCTRL] = VK_LCONTROL;	//		= 306,
		keymap[SDLK_RALT] = VK_RMENU;	//		= 307,
		keymap[SDLK_LALT] = VK_LMENU;	//		= 308,
		keymap[SDLK_RGUI] = VK_RWIN;	//		= 309,
		keymap[SDLK_LGUI] = VK_LWIN;	//		= 310,
		//keymap[SDLK_LSUPER]	= XK_Super_L;	//		= 311,		/**< Left "Windows" key */
		//keymap[SDLK_RSUPER]	= XK_Super_R;	//		= 312,		/**< Right "Windows" key */
		keymap[SDLK_MODE] = VK_MODECHANGE;//		= 313,		/**< "Alt Gr" key */
		//keymap[SDLK_COMPOSE]	= XK_Multi_key;	//		= 314,		/**< Multi-key compose key */
		/** @name Miscellaneous function keys */
		keymap[SDLK_HELP] = VK_HELP;	//		= 315,
		//keymap[SDLK_SYSREQ]	= XK_Sys_Req;	//		= 317,
		keymap[SDLK_PRINTSCREEN] = VK_CANCEL;	//		= 318,
		keymap[SDLK_MENU] = VK_MENU;	//		= 319,
#if 0
		SDLK_POWER = 320,		/**< Power Macintosh power key */
			SDLK_EURO = 321,		/**< Some european keyboards */
#endif
	//keymap[SDLK_UNDO]	= XK_Undo;	//		= 322,		/**< Atari keyboard has Undo */
	//
		return;
    }
}

