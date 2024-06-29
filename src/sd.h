
bool sdcardMounted = false;
#if defined(SDCARD)
#include <FS.h>
#include <SD.h>
#include <SPI.h>

#if defined(CARDPUTER)
SPIClass* sdcardSPI = NULL;
#else
SPIClass sdcardSPI;
#endif
SemaphoreHandle_t sdcardSemaphore;

void appendToFile(fs::FS& fs, const char* path, const char* text) {
  if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE) {
    File file = fs.open(path, FILE_APPEND);
    if (!file) {
      Serial.println("Failed to open file for appending");
      xSemaphoreGive(sdcardSemaphore);
      return;
    }
    Serial.printf("Appending text '%s' to file: %s\n", text, path);
    if (file.println(text)) {
      Serial.println("Text appended");
    } else {
      Serial.println("Append failed");
    }
    file.close();
    xSemaphoreGive(sdcardSemaphore);
  }
}
#endif

bool setupSdCard() {
#if defined(SDCARD)
  sdcardSemaphore = xSemaphoreCreateMutex();
#if defined(CARDPUTER)
  sdcardSPI = new SPIClass(FSPI);
  sdcardSPI->begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);
#else
  sdcardSPI.begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN,
                  SD_CS_PIN);  // start SPI communications
#endif

  delay(10);

#if defined(CARDPUTER)
  if (!SD.begin(SD_CS_PIN, *sdcardSPI)) {
    sdcardSPI->end();
#else
  if (!SD.begin(SD_CS_PIN, sdcardSPI)) {  // excluded * -> poiter indicator -
    sdcardSPI.end();  // Closes SPI connections and release pin header.
#endif
    Serial.println("Failed to mount SDCARD");

    return false;
  } else {
    Serial.println("SDCARD mounted successfully");
    sdcardMounted = true;
    return true;
  }
#else
  return false;
#endif
}

#if defined(SDCARD)
#ifndef CARDPUTER
void ToggleSDCard() {
  rstOverride = true;
  isSwitching = true;
  uint8_t cardType = NULL;
  uint64_t cardSize = NULL;
  currentProc = 1;
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setCursor(5, 1);
  if (sdcardMounted == true) {
    sdcardMounted = false;
    uint8_t cardType = 0;
    uint64_t cardSize = 0;
    SD.end();
    sdcardSPI.end();  // Closes SPI connections and release pins.
    DISPLAY.println("SD Card Unmouted..");
    DISPLAY.println("pin header released.");
    Serial.println("SD Card Unmounted...");
  } else {
    sdcardSPI.begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);
    delay(10);

    if (!SD.begin(SD_CS_PIN, sdcardSPI)) {
      Serial.println("Card Mount Failed");
      DISPLAY.println("Card Mount Failed");
      sdcardSPI.end();

    } else {
      //
      sdcardMounted = true;
      uint8_t cardType = SD.cardType();
      if (cardType == CARD_NONE) {
        DISPLAY.println("None SD Card");
        Serial.println("None SD Card");
      }
      DISPLAY.print("SD Card Type: ");
      if (cardType == CARD_MMC) {
        DISPLAY.println("MMC");
        Serial.println("MMC");
      } else if (cardType == CARD_SD) {
        DISPLAY.println("SDSC");
        Serial.println("SDSC");
      } else if (cardType == CARD_SDHC) {
        DISPLAY.println("SDHC");
        Serial.println("SDHC");
      } else {
        DISPLAY.println("UNKNOWN");
        Serial.println("UNKNOWN");
      }
      uint64_t cardSize = SD.cardSize() / (1024 * 1024);
      DISPLAY.printf("SD Card Size: %lluMB\n", cardSize);
      Serial.printf("SD Card Size: %lluMB\n", cardSize);
    }
  }
  delay(1500);
}
#endif
#endif