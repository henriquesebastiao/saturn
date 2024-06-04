// Saturn Firmware for the M5 Stack Cardputer
// By: Henrique Sebastião (contato@henriquesebastiao.com)
// https://github.com/henriquesebastiao/saturn

// This code contains a lot of logic borrowed from https://github.com/n0xa/m5stick-nemo

#include <M5Cardputer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

#include "src/settings.h"
#include "src/language.h"
#include "src/infrared.h"

IRsend irsend(IR_SEND_PIN);

struct Menu {
  char name[20];
  int command;
};

struct QrCode {
  char name[13];
  String url;
};

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
  {"Power", 7},
  {TXT_MUTE, 10},
  {"Volume +", 8},
  {"Volume -", 9},
  {"Menu", 18},
  {TXT_CHANNEL_UP, 11},
  {TXT_CHANNEL_DOWN, 12},
  {TXT_UP, 13},
  {TXT_DOWN, 14},
  {TXT_LEFT, 15},
  {TXT_RIGHT, 16},
  {"Enter", 17},
  {TXT_BACK, 0},
};
int irTvMenuSize = sizeof(irTvMenu) / sizeof(Menu);

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

Menu settingsMenu[] = {
  {TXT_BATTERY_INFO, 19},
  {TXT_BACK, 0},
};

// -=-=-= FUNCTIONS OF DRAWING MENUS =-=-=-

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

// -=-=-= MENU FUNCTIONS =-=-=-

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

  #if defined(IR_SEND_PIN)
    irsend.begin();
  #endif
  // Hack: Set IRLED high to turn it off after setup. Otherwise it stays on (active low)
  digitalWrite(IR_SEND_PIN, HIGH);

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
    } else if (irTvMenu[cursor].command == 7) {  // Power
      // sendIrRawCodes(allIrPowerCodesRawTV, allIrPowerCodesRawTVLength, "POWER");
      sendIrProntoCodes(allIrPowerCodesProntoTV, allIrPowerCodesProntoTVLength, "POWER");
    } else if (irTvMenu[cursor].command == 10) {  // Mute
      // sendIrRawCodes(allIrMuteCodesRawTV, allIrMuteCodesRawTVLength, TXT_MUTE_TXT_UP);
      sendIrProntoCodes(allIrMuteCodesProntoTV, allIrMuteCodesProntoTVLength, TXT_MUTE_TXT_UPPER);
    } else if (irTvMenu[cursor].command == 8) {  // Volume +
      sendIrProntoCodes(allIrVolumeUpCodesProntoTV, allIrVolumeUpCodesProntoTVLength, "VOL +");
    } else if (irTvMenu[cursor].command == 9) {  // Volume -
      sendIrProntoCodes(allIrVolumeDownCodesProntoTV, allIrVolumeDownCodesProntoTVLength, "VOL -");
    } else if (irTvMenu[cursor].command == 11) {  // Channel +
      sendIrProntoCodes(allIrChannelUpCodesProntoTV, allIrChannelUpCodesProntoTVLength, TXT_CHANNEL_UP_UPPER);
    } else if (irTvMenu[cursor].command == 12) {  // Channel -
      sendIrProntoCodes(allIrChannelDownCodesProntoTV, allIrChannelDownCodesProntoTVLength, TXT_CHANNEL_DOWN_UPPER);
    } else if (irTvMenu[cursor].command == 13) {  // Up
      sendIrProntoCodes(allIrUpCodesProntoTV, allIrUpCodesProntoTVLength, TXT_UP_UPPER);
    } else if (irTvMenu[cursor].command == 14) {  // Down
      sendIrProntoCodes(allIrDownCodesProntoTV, allIrDownCodesProntoTVLength, TXT_DOWN_UPPER);
    } else if (irTvMenu[cursor].command == 15) {  // Left
      sendIrProntoCodes(allIrLeftCodesProntoTV, allIrLeftCodesProntoTVLength, TXT_LEFT_UPPER);
    } else if (irTvMenu[cursor].command == 16) {  // Right
      sendIrProntoCodes(allIrRightCodesProntoTV, allIrRightCodesProntoTVLength, TXT_RIGHT_UPPER);
    } else if (irTvMenu[cursor].command == 17) {  // Enter
      sendIrProntoCodes(allIrEnterCodesProntoTV, allIrEnterCodesProntoTVLength, "ENTER");
    } else if (irTvMenu[cursor].command == 18) {  // Menu
      sendIrProntoCodes(allIrMenuCodesProntoTV, allIrMenuCodesProntoTVLength, "MENU");
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
    if (qrMenu[cursor].url.length() < 1){
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

// -=-=-= IR FUNCTIONS =-=-=-

void sendIrRawCodes(uint16_t *codes[], int sizes[], String name) {
  int size_all_codes = sizeof(codes) / sizeof(uint16_t*);

  Serial.println("\nSize of all codes: " + String(size_all_codes));
  bool endingEarly = false;

  for (int i = 0; i < size_all_codes; i++) {
    int size = sizes[i];
    DISPLAY.fillScreen(BG_COLOR);
    DISPLAY.setTextSize(LARGE_TEXT);
    DISPLAY.drawString(name, DISPLAY_CENTER_X, 50);
    DISPLAY.setTextSize(MEDIUM_TEXT);
    DISPLAY.drawString("<- p/ voltar", DISPLAY_CENTER_X, 80);

    irsend.sendRaw(codes[i], size, 38);

    Serial.println("\nSize of IR code: " + String(size));
    Serial.println("Sent IR codes:");
    for (int j = 0; j < size; j++) {
      Serial.print(codes[i][j]);
      Serial.print(", ");
    }
    delay(40);
  }
  digitalWrite(IR_SEND_PIN, HIGH);
  delay(1000);
  if (checkSelectPress()){
    Serial.println("STOPPING PREMATURELY");
    endingEarly = true;
    currentProc = 5;
  }
}

void sendIrProntoCodes(uint16_t *codes[], int sizes[], String name) {
  int size_all_codes = sizeof(codes) / sizeof(uint16_t*);

  Serial.println("\nSize of all codes: " + String(size_all_codes));
  bool endingEarly = false;
  
  for (int i = 0; i < size_all_codes; i++) {
    int size = sizes[i];
    DISPLAY.fillScreen(BG_COLOR);
    DISPLAY.setTextSize(LARGE_TEXT);
    DISPLAY.drawString(name, DISPLAY_CENTER_X, 50);
    DISPLAY.setTextSize(MEDIUM_TEXT);
    DISPLAY.drawString("<- p/ voltar", DISPLAY_CENTER_X, 80);

    irsend.sendPronto(codes[i], size);

    Serial.println("\nSize of IR code: " + String(size));
    Serial.println("Sent IR codes:");
    for (int j = 0; j < size; j++) {
      Serial.print(codes[i][j]);
      Serial.print(", ");
    }
    delay(40);
  }
  digitalWrite(IR_SEND_PIN, HIGH);
  delay(1000);
  if (checkSelectPress()){
    Serial.println("STOPPING PREMATURELY");
    endingEarly = true;
    currentProc = 5;
  }
}

void settingsMenuSetup() {
  cursor = 0;
  rstOverride = true;
  drawMenu(settingsMenu, sizeof(settingsMenu) / sizeof(Menu));
  delay(500);
}

void settingsMenuLoop() {
  if (checkNextPress()) {
    cursor++;
    cursor = cursor % (sizeof(settingsMenu) / sizeof(Menu));
    drawMenu(settingsMenu, sizeof(settingsMenu) / sizeof(Menu));
    delay(250);
  }
  if (checkSelectPress()) {
    if (settingsMenu[cursor].command == 19) {
      isSwitching = true;
      currentProc = 19;
    } else if (settingsMenu[cursor].command == 0) {
      isSwitching = true;
      currentProc = 1;
    }
  }
}

// -=-=-= BATTERY INFO =-=-=-

uint8_t oldBattery = 0;

void batteryDrawMenu(uint8_t battery) {
  // Battery bar color based on percentage
  uint16_t batteryBarColor = MAIN_COLOR;
  if(battery < 20) {
    batteryBarColor = RED;
  } else if(battery < 60) {
    batteryBarColor = ORANGE;
  } else {
    batteryBarColor = MAIN_COLOR;
  }
  // Draw battery bar
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.drawRect(10, 10, 220, 100, batteryBarColor);
  DISPLAY.fillRect(10, 10, (220 * battery / 100), 100, batteryBarColor);

  // Battery percentage
  DISPLAY.setTextColor(BLACK);
  DISPLAY.setTextSize(LARGE_TEXT);
  DISPLAY.setCursor(90, 60, 1);
  DISPLAY.print(battery);
  DISPLAY.println("%");

  // Exit text
  DISPLAY.setCursor(10, 120, 1);
  DISPLAY.setTextColor(WHITE);
  DISPLAY.setTextSize(SMALL_TEXT);
  DISPLAY.println(TXT_EXIT);
  DISPLAY.setTextColor(MAIN_COLOR, BG_COLOR);
}

int getBatteryVoltage() {
    return M5.Power.getBatteryLevel();
  }

void batterySetup() {
  rstOverride = false;
  pinMode(VBAT_PIN, INPUT);
  uint8_t battery = ((((analogRead(VBAT_PIN)) - 1842) * 100) / 738);
  batteryDrawMenu(battery);
  delay(500); // Prevent switching after menu loads up
  /*
    Used minimum 3,0V and maximum 4,2V for battery. So it may show wrong values. Needs testing.
    It only shows decent values when disconnected from charger, due to HW limitations.
    Equation: Bat% = ((Vadc - 1842) / (2580 - 1842)) * 100. Where: 4,2V = 2580, 3,0V = 1842.
  */
}

void batteryLoop() {
  // Read 30 battery values to calculate the average (avoiding unprecise and close values)
  uint16_t batteryValues = 0;
  for(uint8_t i = 0; i < 30; i++) { // 30 iterations X 100ms = 3 seconds for each refresh
    delay(100);
    batteryValues += ((((analogRead(VBAT_PIN)) - 1842) * 100) / 738);
    M5Cardputer.update();
    if(M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) { // If any key is pressed
      rstOverride = false;
      isSwitching = true;
      currentProc = 1;
      break;
    }
  }

  if(!isSwitching) { // If is not switching, calculate battery average
    uint8_t battery = batteryValues / 30; // Iteration times
    Serial.printf("Battery Level: %d\n", battery);
    if(battery != oldBattery) { // Only draw a new screen if value is different
      oldBattery = battery;
      batteryDrawMenu(battery);
    }
  }
}

// -=-=-= SETUP AND LOOP =-=-=-

void setup() {
  auto cfg = M5.config();
  M5Cardputer.begin(cfg);
  M5Cardputer.Display.setRotation(1);
  DISPLAY.setTextDatum(middle_center);

  #if defined(IR_SEND_PIN)
    pinMode(IR_SEND_PIN, OUTPUT);
    digitalWrite(IR_SEND_PIN, HIGH);
  #endif
  
  // Boot screen
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextColor(MAIN_COLOR);
  DISPLAY.setTextSize(LARGE_TEXT);
  DISPLAY.drawString("Saturn", DISPLAY_CENTER_X, 45);
  DISPLAY.setTextSize(MEDIUM_TEXT);
  DISPLAY.drawString("Cardputer", DISPLAY_CENTER_X, 75);
  DISPLAY.setTextSize(SMALL_TEXT);
  DISPLAY.drawString(SATURN_VERSION, DISPLAY_CENTER_X, 95);

  Serial.println("\nSaturn " + String(SATURN_VERSION) + " started");
  Serial.println("Hello, world!");
  Serial.println("IR Send Pin: " + String(IR_SEND_PIN));
  #if defined(LANGUAGE_EN_US)
    Serial.println("Language: English (US)");
  #else
    Serial.println("Language: Portuguese (BR)");
  #endif

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
        settingsMenuSetup();
        break;
      case 4:
        irDevicesMenuSetup();
        break;
      case 5:
        irTvMenuSetup();
        break;
      case 19:
        batterySetup();
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
      settingsMenuLoop();
      break;
    case 4:
      irDevicesMenuLoop();
      break;
    case 5:
      irTvMenuLoop();
      break;
    case 19:
      batteryLoop();
      break;
  }
}