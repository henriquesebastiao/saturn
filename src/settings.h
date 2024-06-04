// Info
#define SATURN_VERSION "dev"

// Style
#define MAIN_COLOR CYAN
#define BG_COLOR BLACK
#define DISPLAY_CENTER_X DISPLAY.width() / 2  // Center of the screen
#define SMALL_TEXT 1
#define MEDIUM_TEXT 2
#define LARGE_TEXT 4
#define SPACING_MENU_ITEMS 33  // Spacing between menu items
#define HEIGHT_MENU_ITEMS 4  // Height of the menu items

// Interactions
//#define SOUND

// Languages
//#define LANGUAGE_EN_US
#define LANGUAGE_PT_BR

// Aliases
#define DISPLAY M5Cardputer.Display
#define BACKLIGHT 38
#define MINBRIGHT 165

// IR Settings
#define IR_SEND_PIN 44
#define IR_REPEAT 3
#define ACTIVE_LOW_IR

// Battery Settings
#define VBAT_PIN 10

int cursor = 0;
bool rstOverride = false;
bool isSwitching = true;
int currentProc = 1;
bool portalActive = false;
int brightness = 100;
bool activeQR = false;