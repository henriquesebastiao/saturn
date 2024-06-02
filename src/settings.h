// Colors
#define BG_COLOR    BLACK
#define MENU_COLOR  BLUE
#define TEXT_COLOR  WHITE

// Aliases
#define DISPLAY M5Cardputer.Display
#define BACKLIGHT 38
#define MINBRIGHT 165

// Aling
#define DISPLAY_CENTER_X DISPLAY.width() / 2

// Size
#define SMALL_TEXT 0.5

int cursor = 0;
bool rstOverride = false;
bool isSwitching = true;
int currentProc = 1;
bool portalActive = false;
int brightness = 100;