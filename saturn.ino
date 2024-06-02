#include <M5Cardputer.h>

#include "src/settings.h"

struct Menu {
  char name[20];
  int command;
};

Menu mainMenu[] = {
  {"QR Codes", 1},
  {"Settings", 2},
};

void drawMenu(Menu thisMenu[], int size) {
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextSize(2);
  DISPLAY.setTextColor(BLACK);
  int y = 5;
  for (int i = 0; i < size; i++) {
    if (cursor == i) {
      DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, GREEN); // Highlight the current menu item
      DISPLAY.setTextColor(BLACK);
    } else {
      DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BLACK);
      DISPLAY.setTextColor(GREEN);
    }
    DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, GREEN); // Draw the border of the menu item
    DISPLAY.setCursor(20, y + 16);
    DISPLAY.print(thisMenu[i].name);
    y += 35; // Move to the next position for the next menu item
  }
}


void numberDrawMenu(int nums) {
  DISPLAY.setTextSize(SMALL_TEXT);
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setCursor(0, 0);
  if (cursor > 5) {
    for (int i = 0 + (cursor - 5); i < nums; i++) {
      if (cursor == i) {
        DISPLAY.setTextColor(BG_COLOR, TEXT_COLOR);
      }
      DISPLAY.printf(" %-19d\n", i);
      DISPLAY.setTextColor(TEXT_COLOR, BG_COLOR);
    }
  } else {
    for (int i = 0; i < nums; i++) {
      if (cursor == i) {
        DISPLAY.setTextColor(BG_COLOR, TEXT_COLOR);
      }
      DISPLAY.printf(" %-19d\n", i);
      DISPLAY.setTextColor(TEXT_COLOR, BG_COLOR);
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
  if (M5Cardputer.Keyboard.isKeyPressed(',') || M5Cardputer.Keyboard.isKeyPressed('`')){
    dimTimer();
    if (portalActive) {
      // shutdownWebServer();
      portalActive = false;
    }
    isSwitching = true;
    rstOverride = false;
    currentProc = 1;
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
  drawMenu(mainMenu, sizeof(mainMenu) / sizeof(Menu));
  delay(500);
}

void mainMenuLoop() {
  if (checkNextPress()) {
    cursor++;
    cursor = cursor % (sizeof(mainMenu) / sizeof(Menu));
    drawMenu(mainMenu, sizeof(mainMenu) / sizeof(Menu));
    delay(250);
  }
  if (checkSelectPress()) {
    rstOverride = false;
    isSwitching = true;
    currentProc = mainMenu[cursor].command;
  }
}

bool screen_dim_dimmed = false;
int screen_dim_current = 0;
int screen_dim_time = 30;

void screenBrightness(int bright){
  Serial.printf("Brightness: %d\n", bright);
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
  DISPLAY.setTextColor(GREEN);
  DISPLAY.setTextSize(4);
  DISPLAY.drawString("Saturn", DISPLAY_CENTER_X, 45);
  DISPLAY.setTextSize(2);
  DISPLAY.drawString("Cardputer", DISPLAY_CENTER_X, 75);
  DISPLAY.setTextSize(1);
  DISPLAY.drawString("v1.0.0", DISPLAY_CENTER_X, 95);

  // Beep on boot, similar to Mikrotik boot sound
  delay(500);
  M5Cardputer.Speaker.tone(5050, 90);
  delay(220);
  M5Cardputer.Speaker.tone(5050, 90);
  delay(500);
}

void loop() {
  // Background processes
  switcherButtonProc();
  checkMenuPress();

  if (isSwitching) {
    switch (currentProc) {
      case 1:
        mainMenuSetup();
        currentProc = 2;
        break;
    }
  }

  switch (currentProc) {
    case 1:
      mainMenuLoop();
      break;
  }
}