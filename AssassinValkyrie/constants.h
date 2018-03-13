// Programming 2D Games
// Copyright (c) 2011 by:
// Charles Kelly
// Chapter 6 constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------

// window
const char CLASS_NAME[] = "AssassinValkyrie";
const char GAME_TITLE[] = "Assassin Valkyrie";
const bool FULLSCREEN = false;              // windowed or fullscreen
const UINT GAME_WIDTH = 1280;               // width of game in pixels
const UINT GAME_HEIGHT = 720;               // height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 80.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 60.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations
const float GRAVITY = 9.81f;

const int	INIT_STAGE = 0;
const int	FINAL_STAGE = 3;

// graphic images
const char MMBACKGROUND_IMAGE[] = "pictures\\mainMenuBackground.png";
const char LOADING_IMAGE[] = "pictures\\Loading.png";
const char MOUSE_IMAGE[] = "pictures\\mouse.png";
const char ENEMY_IMAGE[] = "pictures\\enemyTexture.png";
const char BUTTON_IMAGE[] = "pictures\\Buttons.png";
const char SKILL_IMAGE[] = "pictures\\skillIcon.png";
const char DASHBOARD_IMAGE[] = "pictures\\dashboard.png";
const char PAUSE_IMAGE[] = "pictures\\pause.png";
const char BAR_IMAGE[] = "pictures\\bar.png";
const char TOOLTIP_IMAGE[] = "pictures\\tooltip.png";

const char PLAYER_IMAGE[] = "pictures\\Player.png";
const char FLOOR_IMAGE[] = "pictures\\newElements.png";
const char BACKGROUND_IMAGE[] = "pictures\\backgroundBIG.png";
const char PICKUP_IMAGE[] = "pictures\\pickupTextures.png";

const char ENEMY_TROOPER_IMAGE[] = "pictures\\enemyTexture.png";
const char ENEMY_GUNNER_IMAGE[] = "pictures\\enemyTexture_gunner.png";
const char ENEMY_SERPANT_IMAGE[] = "pictures\\enemyTexture_serpant.png";
const char BULLET_IMAGE[] = "pictures\\bullets.png";
const char HEALTH_IMAGE[] = "pictures\\healthTexture.png";

// WAVE_BANK must be location of .xwb file.
const char WAVE_BANK[] = "audio\\Win\\Wave Bank.xwb";
// SOUND_BANK must be location of .xsb file.
const char SOUND_BANK[] = "audio\\Win\\Sound Bank.xsb";

// audio cues
const char STEALTH[] = "stealth";
const char RUSH[] = "rush";
const char BUTTON_ENTER[] = "menu1";
const char BUTTON_HOVER[] = "menu2";
const char ALERT[] = "alert";
const char FIREBALL[] = "fireball";
const char BULLET[] = "laser";
const char SWORD[] = "sword";
const char PICKUP[] = "pickup";
const char DIE[] = "die";
const char DIE2[] = "die2";
const char PLAYERMELEE[] = "playermelee";
const char PLAYERRANGE[] = "playerrange";
const char LEVELUP[] = "levelup";

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR ESC_KEY      = VK_ESCAPE;       // escape key
const UCHAR ALT_KEY      = VK_MENU;         // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;       // Enter key


//control key for player ship
const UCHAR DEFAULT_RIGHT_KEY = 'D';
const UCHAR DEFAULT_LEFT_KEY = 'A';
const UCHAR DEFAULT_DOWN_KEY = 'S';
const UCHAR DEFAULT_UP_KEY = 'W';
const UCHAR DEFAULT_MELEE_KEY = 'G';
const UCHAR DEFAULT_RANGE_KEY = 'F';
const UCHAR DEFAULT_DISTRACT_KEY = 'H';
const UCHAR DEFAULT_ASSASSINATE_KEY = 'R';
const UCHAR DEFAULT_JUMPING_KEY = VK_SPACE;
const UCHAR CLIMBING_KEY = 'W';
const UCHAR CLIMBING_UP_KEY = 'W';
const UCHAR CLIMBING_DOWN_KEY = 'S';
const UCHAR ENTER_HIDEOUT = 'W';

// weapon types
enum WEAPON { };

#endif
