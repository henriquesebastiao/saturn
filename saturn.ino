// Saturn Firmware for the M5 Stack Cardputer
// Created by: Henrique Sebastião
// https://github.com/henriquesebastiao/saturn

// This code contains a lot of logic borrowed from https://github.com/n0xa/m5stick-nemo

#include <M5Cardputer.h>

#include "src/settings.h"
#include "src/language.h"

struct Menu {
  char name[20];
  int command;
};

struct QrCode {
  char name[13];
  String url;
};

// Main Menu
Menu mainMenu[] = {
  {TXT_IR, 4},
  {"QR Codes", 2},
  {TXT_SETTINGS, 3},
};
int mainMenuSize = sizeof(mainMenu) / sizeof(Menu);

Menu irDevicesMenu[] = {
  {"TV", 5},
  {TXT_BACK, 0},
};
int irDevicesMenuSize = sizeof(irDevicesMenu) / sizeof(Menu);

Menu irTvMenu[] = {
  {TXT_POWER, 7},  // TODO
  {"Vol +", 8},  // TODO
  {"Vol -", 9},  // TODO
  {TXT_MUTE, 10},  // TODO
  {TXT_BACK, 0},
};
int irTvMenuSize = sizeof(irTvMenu) / sizeof(Menu);

// QR Codes Menu
QrCode qrMenu[] = {
  {"Saturn", "https://youtu.be/dzNvk80XY9s"},
  {TXT_INTERSTELLAR, "https://youtu.be/JuSsvM8B4Jc"},
  {"Shodan.io", "https://www.shodan.io/"},
  {"Fake Update", "https://fakeupdate.net/"},
  {"Hacker Typer", "https://hackertyper.com/"},
  {TXT_REPOSITORY, "https://github.com/henriquesebastiao/saturn"},
  {TXT_BACK, ""},
};
int qrMenuSize = sizeof(qrMenu) / sizeof(QrCode);

void drawMenu(Menu thisMenu[], int size) {
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextSize(2);
  DISPLAY.setTextColor(BG_COLOR);
  int y = HEIGHT_MENU_ITEMS;
  // Scrolling menu
  if (cursor < 0) {
    cursor = size - 1;  // rollover hack for up-arrow on cardputer
  }
  if (cursor > 3) {
    for (int i = 0 + (cursor - 3); i < size; i++) {
      if (cursor == i) {
        DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Highlight the current menu item
        DISPLAY.setTextColor(BG_COLOR);
      } else {
        DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BG_COLOR);
        DISPLAY.setTextColor(MAIN_COLOR);
      }
      DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Draw the border of the menu item
      DISPLAY.setCursor(20, y + 16);
      DISPLAY.print(thisMenu[i].name);
      y += SPACING_MENU_ITEMS; // Move to the next position for the next menu item
    }
  } else {
    for (int i = 0; i < size; i++) {
      if (cursor == i) {
        DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Highlight the current menu item
        DISPLAY.setTextColor(BG_COLOR);
      } else {
        DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BG_COLOR);
        DISPLAY.setTextColor(MAIN_COLOR);
      }
      DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Draw the border of the menu item
      DISPLAY.setCursor(20, y + 16);
      DISPLAY.print(thisMenu[i].name);
      y += SPACING_MENU_ITEMS; // Move to the next position for the next menu item
    }
  }
}

void qrDrawMenu(int size) {
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextSize(2);
  DISPLAY.setTextColor(BG_COLOR);
  int y = HEIGHT_MENU_ITEMS;
  // Scrolling menu
  if (cursor < 0) {
    cursor = size - 1;  // rollover hack for up-arrow on cardputer
  }
  if (cursor > 3) {
    for (int i = 0 + (cursor - 3); i < size; i++) {
      if (cursor == i) {
        DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Highlight the current menu item
        DISPLAY.setTextColor(BG_COLOR);
      } else {
        DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BG_COLOR);
        DISPLAY.setTextColor(MAIN_COLOR);
      }
      DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Draw the border of the menu item
      DISPLAY.setCursor(20, y + 16);
      DISPLAY.print(qrMenu[i].name);
      y += SPACING_MENU_ITEMS; // Move to the next position for the next menu item
    }
  } else {
    for (int i = 0; i < size; i++) {
      if (cursor == i) {
        DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Highlight the current menu item
        DISPLAY.setTextColor(BG_COLOR);
      } else {
        DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BG_COLOR);
        DISPLAY.setTextColor(MAIN_COLOR);
      }
      DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Draw the border of the menu item
      DISPLAY.setCursor(20, y + 16);
      DISPLAY.print(qrMenu[i].name);
      y += SPACING_MENU_ITEMS; // Move to the next position for the next menu item
    }
  }
}

void switcherButtonProc() {
  if (!rstOverride) {
    if (checkNextPress()) {
      isSwitching = true;
      currentProc = 1;
    }
  }
}

void checkMenuPress() {
  if (M5Cardputer.Keyboard.isKeyPressed('`')) {  // Return to the main menu by pressing ESC
    dimTimer();
    if (portalActive) {
      portalActive = false;
    }
    isSwitching = true;
    rstOverride = false;
    currentProc = 1;
  } else if (M5Cardputer.Keyboard.isKeyPressed(',')) {  // Return to the previous menu by pressing ,
    dimTimer();
    if (portalActive) {
      portalActive = false;
    }
    isSwitching = true;
    rstOverride = false;

    if (currentProc == 5) {
      currentProc = 4;
    } else {
      currentProc = 1;
    }
    delay(100);
  }
}

bool checkNextPress() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(';')) {
    cursor = cursor - 2;
    dimTimer();
    return true;
  }
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_TAB) || M5Cardputer.Keyboard.isKeyPressed('.')) {
    dimTimer();
    return true;
  }
  return false;
}

bool checkSelectPress() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) || M5Cardputer.Keyboard.isKeyPressed('/')) {
    dimTimer();
    return true;
  }
  return false;
}

void mainMenuSetup() {
  cursor = 0;
  rstOverride = true;
  drawMenu(mainMenu, mainMenuSize);
  delay(500);
}

void mainMenuLoop() {
  if (checkNextPress()) {
    cursor++;
    cursor = cursor % mainMenuSize;
    drawMenu(mainMenu, mainMenuSize);
    delay(250);
  }
  if (checkSelectPress()) {
    rstOverride = false;
    isSwitching = true;
    currentProc = mainMenu[cursor].command;
  }
}

void irDevicesMenuSetup() {
  cursor = 0;
  rstOverride = true;
  drawMenu(irDevicesMenu, irDevicesMenuSize);
  delay(500);
}

void irDevicesMenuLoop() {
  if (checkNextPress()) {
    cursor++;
    cursor = cursor % irDevicesMenuSize;
    drawMenu(irDevicesMenu, irDevicesMenuSize);
    delay(250);
  }
  if (checkSelectPress()) {
    if (irDevicesMenu[cursor].command == 0) {
      isSwitching = true;
      currentProc = 1;
    } else if (irDevicesMenu[cursor].command == 5) {
      isSwitching = true;
      currentProc = 5;
    }
  }
}

void irTvMenuSetup() {
  cursor = 0;
  rstOverride = true;
  drawMenu(irTvMenu, irTvMenuSize);
  delay(500);
}

void irTvMenuLoop() {
  if (checkNextPress()) {
    cursor++;
    cursor = cursor % irTvMenuSize;
    drawMenu(irTvMenu, irTvMenuSize);
    delay(250);
  }
  if (checkSelectPress()) {
    if (irTvMenu[cursor].command == 0) {
      isSwitching = true;
      currentProc = 4;
    }    
  }
}

void qrMenuSetup() {
  cursor = 0;
  rstOverride = true;
  qrDrawMenu(qrMenuSize);
  delay(500);
}

void qrMenuLoop() {
  if (checkNextPress()) {
    cursor++;
    cursor = cursor % (qrMenuSize);
    qrDrawMenu(qrMenuSize);
    delay(250);
  }
  if (checkSelectPress()) {
    if (qrMenu[cursor].url.length() < 1){  // TODO
      currentProc = 1;
      isSwitching = true;
    }else if ( activeQR == false ) {
      activeQR = true;
      DISPLAY.fillScreen(WHITE);
      DISPLAY.qrcode(qrMenu[cursor].url, (DISPLAY.width() - DISPLAY.height()) / 2, 0, DISPLAY.height(), 5);
      delay(500);
    } else {
      isSwitching = true;
      activeQR = false;
      delay(250);
    }
  }
}

bool screen_dim_dimmed = false;
int screen_dim_current = 0;
int screen_dim_time = 30;

void screenBrightness(int bright){
  #if defined(BACKLIGHT)
    int bl = MINBRIGHT + round(((255 - MINBRIGHT) * bright / 100)); 
    analogWrite(BACKLIGHT, bl);
  #endif
}

int uptime(){
  return(int(millis() / 1000));
}

void dimTimer(){
  if(screen_dim_dimmed){
    screenBrightness(brightness);
    screen_dim_dimmed = false;
  }
  screen_dim_current = uptime() + screen_dim_time + 2;
}

void setup() {
  auto cfg = M5.config();
  M5Cardputer.begin(cfg);
  M5Cardputer.Display.setRotation(1);
  DISPLAY.setTextDatum(middle_center);
  
  // Boot screen
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextColor(MAIN_COLOR);
  DISPLAY.setTextSize(LARGE_TEXT);
  DISPLAY.drawString("Saturn", DISPLAY_CENTER_X, 45);
  DISPLAY.setTextSize(MEDIUM_TEXT);
  DISPLAY.drawString("Cardputer", DISPLAY_CENTER_X, 75);
  DISPLAY.setTextSize(SMALL_TEXT);
  DISPLAY.drawString(SATURN_VERSION, DISPLAY_CENTER_X, 95);

  // Beep on boot, similar to Mikrotik boot sound
  #if defined(SOUND)
    delay(500);
    M5Cardputer.Speaker.tone(5050, 90);
    delay(220);
    M5Cardputer.Speaker.tone(5050, 90);
    delay(500);
  #else
    delay(1400);  // Silence Mode
  #endif
}

// Proccesses
// 1 - Main Menu
// 2 - QR Codes
// 3 - Settings
// 4 - IR Devices
// 5 - IR TV

void loop() {
  // Background processes
  switcherButtonProc();
  checkMenuPress();

  if (isSwitching) {
    isSwitching = false;
    switch (currentProc) {
      case 1:
        mainMenuSetup();
        break;
      case 2:
        qrMenuSetup();
        break;
      case 3:
        // settingsMenuSetup(); // TODO
        break;
      case 4:
        irDevicesMenuSetup();
        break;
      case 5:
        irTvMenuSetup();
        break;
    }
  }

  switch (currentProc) {
    case 1:
      mainMenuLoop();
      break;
    case 2:
      qrMenuLoop();
      break;
    case 3:
      // settingsMenuLoop(); // TODO
      break;
    case 4:
      irDevicesMenuLoop();
      break;
    case 5:
      irTvMenuLoop();
      break;
  }
}