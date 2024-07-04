#include "pitches.h"

bool checkExitPress() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) ||
      M5Cardputer.Keyboard.isKeyPressed('`')) {
    return true;
  }
  return false;
}

struct Melody {
  uint8_t note;
  uint8_t duration;
};

Melody superMarioMelody[] = {
    {660, 100}, {660, 100}, {510, 100}, {660, 100}, {770, 100}, {380, 100},
    {510, 100}, {380, 100}, {320, 100}, {440, 100}, {480, 80},  {450, 100},
    {430, 100}, {380, 100}, {660, 80},  {760, 50},  {860, 100}, {700, 80},
    {760, 50},  {660, 80},  {520, 80},  {580, 80},  {480, 80},  {510, 100},
    {380, 100}, {320, 100}, {440, 100}, {480, 80},  {450, 100}, {430, 100},
    {380, 100}, {660, 80},  {760, 50},  {860, 100}, {700, 80},  {760, 50},
    {660, 80},  {520, 80},  {580, 80},  {480, 80},  {500, 100}, {760, 100},
    {720, 100}, {680, 100}, {620, 150}, {650, 150}, {380, 100}, {430, 100},
    {500, 100}, {430, 100}, {500, 100}, {570, 100}, {500, 100}, {760, 100},
    {720, 100}, {680, 100}, {620, 150}, {650, 200}, {1020, 80}, {1020, 80},
    {1020, 80}, {380, 100}, {500, 100}, {760, 100}, {720, 100}, {680, 100},
    {620, 150}, {650, 150}, {380, 100}, {430, 100}, {500, 100}, {430, 100},
    {500, 100}, {570, 100}, {585, 100}, {550, 100}, {500, 100}, {380, 100},
    {500, 100}, {500, 100}, {500, 100}, {500, 100}, {760, 100}, {720, 100},
    {680, 100}, {620, 150}, {650, 150}, {380, 100}, {430, 100}, {500, 100},
    {430, 100}, {500, 100}, {570, 100}, {500, 100}, {760, 100}, {720, 100},
    {680, 100}, {620, 150}, {650, 200}, {1020, 80}, {1020, 80}, {1020, 80},
    {380, 100}, {500, 100}, {760, 100}, {720, 100}, {680, 100}, {620, 150},
    {650, 150}, {380, 100}, {430, 100}, {500, 100}, {430, 100}, {500, 100},
    {570, 100}, {585, 100}, {550, 100}, {500, 100}, {380, 100}, {500, 100},
    {500, 100}, {500, 100}, {500, 60},  {500, 80},  {500, 60},  {500, 80},
    {580, 80},  {660, 80},  {500, 80},  {430, 80},  {380, 80},  {500, 60},
    {500, 80},  {500, 60},  {500, 80},  {580, 80},  {660, 80},  {870, 80},
    {760, 80},  {500, 60},  {500, 80},  {500, 60},  {500, 80},  {580, 80},
    {660, 80},  {500, 80},  {430, 80},  {380, 80},  {660, 100}, {660, 100},
    {660, 100}, {510, 100}, {660, 100}, {770, 100}, {380, 100},
};
uint8_t superMarioMelodySize = sizeof(superMarioMelody) / sizeof(Melody);

uint8_t superMarioDelay[] = {
    300, 300, 100, 300, 550, 575, 450, 400, 500, 300, 330, 150, 300, 200, 200,
    150, 300, 150, 350, 300, 150, 150, 500, 450, 400, 500, 300, 330, 150, 300,
    200, 200, 150, 300, 150, 350, 300, 150, 150, 500, 300, 100, 150, 150, 300,
    300, 150, 150, 300, 150, 100, 220, 300, 100, 150, 150, 300, 300, 300, 150,
    300, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300, 150, 100, 420, 450,
    420, 36,  300, 300, 150, 300, 300, 100, 150, 150, 300, 300, 150, 150, 300,
    150, 100, 220, 300, 100, 150, 150, 300, 300, 300, 150, 300, 300, 300, 100,
    150, 150, 300, 300, 150, 150, 300, 150, 100, 420, 450, 420, 36,  300, 300,
    150, 300, 150, 300, 350, 150, 350, 150, 300, 150, 600, 150, 300, 350, 150,
    150, 550, 325, 600, 150, 300, 350, 150, 350, 150, 300, 150, 600, 150, 300,
    300, 100, 300, 550, 575,
};

void superMarioBrossSound() {
  for (uint8_t note = 0; note < superMarioMelodySize; note++) {
    M5Cardputer.Speaker.tone(superMarioMelody[note].note,
                             superMarioMelody[note].duration);

    if (checkExitPress()) {
      return;
    }

    delay(superMarioDelay[note]);
  }
}

Melody imperialMarchMelody[] = {
    {500, 500}, {500, 500}, {500, 500}, {400, 500}, {600, 200}, {500, 500},
    {400, 500}, {600, 200}, {500, 500}, {750, 500}, {750, 500}, {750, 500},
    {810, 500}, {600, 200}, {470, 500}, {400, 500}, {600, 200}, {500, 500},
};
uint8_t imperialMarchMelodySize = sizeof(imperialMarchMelody) / sizeof(Melody);

uint8_t imperialMarchDelay[] = {
    500, 500, 500, 400, 100, 500, 400, 100, 1000,
    500, 500, 500, 400, 100, 500, 400, 100, 1000,
};

void imperialMarchSound() {
  for (uint8_t note = 0; note < imperialMarchMelodySize; note++) {
    M5Cardputer.Speaker.tone(imperialMarchMelody[note].note,
                             imperialMarchMelody[note].duration);

    if (checkExitPress()) {
      return;
    }

    delay(imperialMarchDelay[note]);
  }
}

Melody ahaTakeOnMeMelody[] = {
    {740, 188}, {740, 188}, {740, 188}, {587, 188}, {494, 188}, {659, 188},
    {659, 188}, {659, 188}, {831, 188}, {831, 188}, {880, 188}, {988, 188},
    {880, 188}, {880, 188}, {880, 188}, {659, 188}, {587, 188}, {740, 188},
    {740, 188}, {740, 188}, {659, 188}, {659, 188}, {740, 188}, {659, 188},
    {740, 188}, {740, 188}, {740, 188}, {587, 188}, {494, 188}, {659, 188},
    {659, 188}, {659, 188}, {831, 188}, {831, 188}, {880, 188}, {988, 188},
    {880, 188}, {880, 188}, {880, 188}, {659, 188}, {587, 188}, {740, 188},
    {740, 188}, {740, 188}, {659, 188}, {659, 188}, {740, 188}, {659, 188},
};
uint8_t ahaTakeOnMeMelodySize = sizeof(ahaTakeOnMeMelody) / sizeof(Melody);

uint8_t ahaTakeOnMeDelay[] = {
    198, 198, 198, 198, 188, 198, 188, 198, 188, 198, 188, 198, 198,
    198, 198, 198, 198, 198, 198, 198, 188, 198, 188, 198, 188, 198,
    188, 198, 198, 198, 198, 198, 198, 198, 198, 198, 188, 198, 188,
    198, 188, 198, 188, 198, 198, 198, 198, 198, 198, 198, 198, 198,
    188, 198, 188, 198, 188, 198, 188, 198, 198, 198, 198, 19,
};

void ahaTakeOnMeSound() {
  for (uint8_t note = 0, iDelay = 0; note < ahaTakeOnMeMelodySize; note++) {
    M5Cardputer.Speaker.tone(ahaTakeOnMeMelody[note].note,
                             ahaTakeOnMeMelody[note].duration);

    if (checkExitPress()) {
      return;
    }

    delay(ahaTakeOnMeDelay[iDelay]);

    if (ahaTakeOnMeDelay[iDelay + 1] == 188) {
      delay(ahaTakeOnMeDelay[iDelay + 1]);
      iDelay++;
    }

    iDelay++;
  }
}

Melody jingleBellsMelody[] = {
    {523, 220}, {523, 220}, {523, 300}, {523, 200}, {523, 200}, {523, 300},
    {523, 220}, {623, 220}, {423, 220}, {473, 220}, {523, 600}, {553, 220},
    {553, 220}, {553, 300}, {553, 220}, {523, 220}, {523, 250}, {523, 220},
    {470, 220}, {470, 220}, {523, 300}, {470, 600},
};
uint8_t jingleBellsMelodySize = sizeof(jingleBellsMelody) / sizeof(Melody);

uint8_t jingleBellsDelay[] = {
    250, 250, 500, 250, 250, 500, 250, 250, 250, 250, 1000,
    250, 250, 500, 250, 250, 500, 250, 250, 250, 350, 1000,
};

void jingleBellsSound() {
  for (uint8_t note = 0; note < jingleBellsMelodySize; note++) {
    M5Cardputer.Speaker.tone(jingleBellsMelody[note].note,
                             jingleBellsMelody[note].duration);

    if (checkExitPress()) {
      return;
    }

    delay(jingleBellsDelay[note]);
  }
}

Melody ozzyOsbornCrazyTrainMelody[] = {
    {370, 175}, {370, 175}, {0, 0},     {440, 175}, {440, 175}, {0, 0},
    {330, 175}, {330, 175}, {0, 0},     {370, 175}, {370, 175}, {0, 0},
    {587, 175}, {587, 175}, {0, 0},     {330, 175}, {330, 175}, {0, 0},
    {370, 175}, {370, 175}, {554, 175}, {370, 175}, {587, 175}, {370, 175},
    {554, 175}, {370, 175}, {494, 175}, {440, 175}, {415, 175}, {440, 175},
    {494, 175}, {440, 175}, {415, 175}, {330, 175}, {370, 175}, {370, 175},
    {554, 175}, {370, 175}, {587, 175}, {370, 175}, {554, 175}, {370, 175},
    {494, 175}, {440, 175}, {415, 175}, {440, 175}, {494, 175}, {440, 175},
    {415, 175}, {330, 175}, {370, 175}, {370, 175}, {554, 175}, {370, 175},
    {587, 175}, {370, 175}, {554, 175}, {370, 175}, {494, 175}, {440, 175},
    {415, 175}, {440, 175}, {494, 175}, {440, 175}, {415, 175}, {330, 175},
    {370, 175}, {370, 175}, {554, 175}, {370, 175}, {587, 175}, {370, 175},
    {554, 175}, {494, 175}, {587, 775}, {330, 775}, {440, 175}, {440, 75},
    {440, 75},  {880, 175}, {440, 75},  {440, 75},  {440, 75},  {440, 75},
    {784, 175}, {440, 75},  {440, 75},  {440, 75},  {440, 75},  {740, 175},
    {440, 75},  {440, 75},  {440, 75},  {440, 75},  {659, 575}, {392, 75},
    {415, 75},  {440, 175}, {440, 175}, {440, 75},  {440, 75},  {880, 175},
    {440, 75},  {440, 75},  {440, 75},  {440, 75},  {784, 175}, {440, 75},
    {440, 75},  {440, 75},  {440, 75},  {740, 175}, {440, 75},  {440, 75},
    {440, 75},  {440, 75},  {659, 575}, {440, 375}, {659, 175}, {554, 575},
    {0, 0},     {0, 0},     {554, 175}, {494, 175}, {440, 175}, {440, 175},
    {440, 375}, {494, 175}, {554, 375}, {0, 0},     {880, 175}, {880, 175},
    {880, 175}, {740, 375}, {659, 575}, {0, 0},     {659, 175}, {740, 175},
    {659, 175}, {659, 175}, {587, 375}, {659, 175}, {587, 175}, {554, 175},
    {440, 775}, {0, 0},     {659, 175}, {554, 575}, {0, 0},     {0, 0},
    {494, 175}, {494, 175}, {440, 375}, {440, 375}, {494, 175}, {554, 375},
    {0, 0},     {0, 0},     {0, 0},     {880, 175}, {880, 175}, {880, 175},
    {880, 175}, {740, 175}, {659, 375}, {0, 0},     {659, 175}, {659, 175},
    {740, 175}, {659, 175}, {659, 175}, {587, 375}, {659, 175}, {587, 175},
    {554, 175}, {440, 775},
};
uint8_t ozzyOsbornCrazyTrainMelodySize =
    sizeof(ozzyOsbornCrazyTrainMelody) / sizeof(Melody);

uint8_t ozzyOsbornCrazyTrainDelay[] = {
    200, 200, 1200, 200,  200, 400,  200, 200, 400, 200, 200, 1200, 200, 200,
    400, 200, 200,  400,  200, 200,  200, 200, 200, 200, 200, 200,  200, 200,
    200, 200, 200,  200,  200, 200,  200, 200, 200, 200, 200, 200,  200, 200,
    200, 200, 200,  200,  200, 200,  200, 200, 200, 200, 200, 200,  200, 200,
    200, 200, 200,  200,  200, 200,  200, 200, 200, 200, 200, 200,  200, 200,
    200, 200, 200,  200,  800, 800,  200, 100, 100, 200, 100, 100,  100, 100,
    200, 100, 100,  100,  100, 200,  100, 100, 100, 100, 600, 100,  100, 200,
    200, 100, 100,  200,  100, 100,  100, 100, 200, 100, 100, 100,  100, 200,
    100, 100, 100,  100,  600, 400,  200, 600, 800, 600, 200, 200,  200, 200,
    400, 200, 400,  2400, 200, 200,  200, 400, 600, 600, 200, 200,  200, 200,
    400, 200, 200,  200,  800, 1600, 200, 600, 800, 600, 200, 200,  400, 400,
    200, 400, 800,  800,  600, 200,  200, 200, 200, 200, 400, 800,  200, 200,
    200, 200, 200,  400,  200, 200,  200, 800,
};

void ozzyOsbornCrazyTrainSound() {
  for (uint8_t note = 0; note < ozzyOsbornCrazyTrainMelodySize; note++) {
    Serial.printf("note: %d, duration: %d\n",
                  ozzyOsbornCrazyTrainMelody[note].note,
                  ozzyOsbornCrazyTrainMelody[note].duration);
    Serial.printf("delay: %d\n", ozzyOsbornCrazyTrainDelay[note]);

    if (ozzyOsbornCrazyTrainMelody[note].note == 0) {
      delay(ozzyOsbornCrazyTrainDelay[note]);
      continue;
    }

    M5Cardputer.Speaker.tone(ozzyOsbornCrazyTrainMelody[note].note,
                             ozzyOsbornCrazyTrainMelody[note].duration);

    if (checkExitPress()) {
      return;
    }

    delay(ozzyOsbornCrazyTrainDelay[note]);
  }
  Serial.printf("done");
}

Melody starWarsMelody[] = {
    {698, 167},  {698, 167},  {698, 167},   {932, 1000},  {1397, 1000},
    {1245, 167}, {1175, 167}, {1047, 167},  {1865, 1000}, {1397, 500},
    {1245, 167}, {1175, 167}, {1047, 167},  {1865, 1000}, {1397, 500},
    {1245, 167}, {1175, 167}, {1245, 167},  {1047, 667},  {698, 167},
    {698, 167},  {698, 167},  {932, 1000},  {1397, 1000}, {1245, 167},
    {1175, 167}, {1047, 167}, {1865, 1000}, {1397, 500},  {1245, 167},
    {1175, 167}, {1047, 167}, {1865, 1000}, {1397, 500},  {1245, 167},
    {1175, 167}, {1245, 167}, {1047, 667},
};
uint8_t starWarsMelodySize = sizeof(starWarsMelody) / sizeof(Melody);

uint8_t starWarsDelay[] = {
    177,  177, 177,  1010, 1010, 177, 177, 177,  1010, 510, 177,  177,  177,
    1010, 510, 177,  177,  177,  677, 333, 177,  177,  177, 1010, 1010, 177,
    177,  177, 1010, 510,  177,  177, 177, 1010, 510,  177, 177,  177,  677,
};

void starWarsSound() {
  for (uint8_t note = 0, iDelay = 0; note < starWarsMelodySize; note++) {
    M5Cardputer.Speaker.tone(starWarsMelody[note].note,
                             starWarsMelody[note].duration);

    if (checkExitPress()) {
      return;
    }

    delay(starWarsDelay[iDelay]);

    if (starWarsDelay[iDelay + 1] == 333) {
      delay(starWarsDelay[iDelay + 1]);
      iDelay++;
    }

    iDelay++;
  }
}

uint8_t nokiaMelody[] = {NOTE_E5,  NOTE_D5, NOTE_FS4, NOTE_GS4, NOTE_CS5,
                         NOTE_B4,  NOTE_D4, NOTE_E4,  NOTE_B4,  NOTE_A4,
                         NOTE_CS4, NOTE_E4, NOTE_A4};

uint8_t nokiaDurations[] = {8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 2};
uint8_t nokiaDurationsSize = sizeof(nokiaDurations) / sizeof(uint8_t);

void nokiaSound() {
  for (uint8_t note = 0; note < nokiaDurationsSize; note++) {
    uint8_t duration = 1000 / nokiaDurations[note];
    M5Cardputer.Speaker.tone(nokiaMelody[note], duration);

    uint8_t pauseBetweenNotes = duration * 1.30;

    if (checkExitPress()) {
      return;
    }

    delay(pauseBetweenNotes);
  }
}

uint8_t theSimpsonsMelody[] = {
    NOTE_C4,  NOTE_E4,  NOTE_FS4, REST,     NOTE_A4,  NOTE_G4, NOTE_E4,
    NOTE_C4,  NOTE_A3,  NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3, REST,
    NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3,  NOTE_AS3, NOTE_B3, REST};

uint8_t theSimpsonsDurations[] = {2, 4, 4, 32, 8, 2, 4, 4, 8, 8, 8,
                                  8, 4, 2, 8,  8, 8, 4, 2, 2, 2};
uint8_t theSimpsonsDurationSize =
    sizeof(theSimpsonsDurations) / sizeof(uint8_t);

void theSimpsonsSound() {
  for (uint8_t note = 0; note < theSimpsonsDurationSize; note++) {
    uint8_t duration = 1000 / theSimpsonsDurations[note];
    M5Cardputer.Speaker.tone(theSimpsonsMelody[note], duration);

    uint8_t pauseBetweenNotes = duration * 1.30;

    if (checkExitPress()) {
      return;
    }

    delay(pauseBetweenNotes);
  }
}

uint8_t pacmanMelody[] = {
    NOTE_B4,  NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_B5,  NOTE_FS5, NOTE_DS5,
    NOTE_C5,  NOTE_C6, NOTE_G6,  NOTE_E6,  NOTE_C6,  NOTE_G6,  NOTE_E6,

    NOTE_B4,  NOTE_B5, NOTE_FS5, NOTE_DS5, NOTE_B5,  NOTE_FS5, NOTE_DS5,
    NOTE_DS5, NOTE_E5, NOTE_F5,  NOTE_F5,  NOTE_FS5, NOTE_G5,  NOTE_G5,
    NOTE_GS5, NOTE_A5, NOTE_B5};

uint8_t pacmanDurations[] = {
    16, 16, 16, 16, 32, 16, 8, 16, 16, 16, 16, 32, 16, 8,

    16, 16, 16, 16, 32, 16, 8, 32, 32, 32, 32, 32, 32, 32, 32, 16, 8};
uint8_t pacmanDurationSize = sizeof(pacmanDurations) / sizeof(uint8_t);

void pacmanSound() {
  for (uint8_t note = 0; note < pacmanDurationSize; note++) {
    uint8_t duration = 1000 / pacmanDurations[note];
    M5Cardputer.Speaker.tone(pacmanMelody[note], duration);

    uint8_t pauseBetweenNotes = duration * 1.30;

    if (checkExitPress()) {
      return;
    }

    delay(pauseBetweenNotes);
  }
}

uint8_t doomMelody[] = {
    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_FS3, NOTE_D3,  NOTE_B2,  NOTE_A3,
    NOTE_FS3, NOTE_B2,  NOTE_D3,  NOTE_FS3, NOTE_A3,  NOTE_FS3, NOTE_D3,
    NOTE_B2,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_B3,  NOTE_G3,  NOTE_E3,  NOTE_G3,
    NOTE_B3,  NOTE_E4,  NOTE_G3,  NOTE_B3,  NOTE_E4,  NOTE_B3,  NOTE_G4,
    NOTE_B4,

    NOTE_A2,  NOTE_A2,  NOTE_A3,  NOTE_A2,  NOTE_A2,  NOTE_G3,  NOTE_A2,
    NOTE_A2,  NOTE_F3,  NOTE_A2,  NOTE_A2,  NOTE_DS3, NOTE_A2,  NOTE_A2,
    NOTE_E3,  NOTE_F3,  NOTE_A2,  NOTE_A2,  NOTE_A3,  NOTE_A2,  NOTE_A2,
    NOTE_G3,  NOTE_A2,  NOTE_A2,  NOTE_F3,  NOTE_A2,  NOTE_A2,  NOTE_DS3,

    NOTE_A2,  NOTE_A2,  NOTE_A3,  NOTE_A2,  NOTE_A2,  NOTE_G3,  NOTE_A2,
    NOTE_A2,  NOTE_F3,  NOTE_A2,  NOTE_A2,  NOTE_DS3, NOTE_A2,  NOTE_A2,
    NOTE_E3,  NOTE_F3,  NOTE_A2,  NOTE_A2,  NOTE_A3,  NOTE_A2,  NOTE_A2,
    NOTE_G3,  NOTE_A2,  NOTE_A2,  NOTE_A3,  NOTE_F3,  NOTE_D3,  NOTE_A3,
    NOTE_F3,  NOTE_D3,  NOTE_C4,  NOTE_A3,  NOTE_F3,  NOTE_A3,  NOTE_F3,
    NOTE_D3,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2,

    NOTE_CS3, NOTE_CS3, NOTE_CS4, NOTE_CS3, NOTE_CS3, NOTE_B3,  NOTE_CS3,
    NOTE_CS3, NOTE_A3,  NOTE_CS3, NOTE_CS3, NOTE_G3,  NOTE_CS3, NOTE_CS3,
    NOTE_GS3, NOTE_A3,  NOTE_B2,  NOTE_B2,  NOTE_B3,  NOTE_B2,  NOTE_B2,
    NOTE_A3,  NOTE_B2,  NOTE_B2,  NOTE_G3,  NOTE_B2,  NOTE_B2,  NOTE_F3,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_B3,  NOTE_G3,  NOTE_E3,  NOTE_G3,
    NOTE_B3,  NOTE_E4,  NOTE_G3,  NOTE_B3,  NOTE_E4,  NOTE_B3,  NOTE_G4,
    NOTE_B4,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_FS3, NOTE_DS3, NOTE_B2,  NOTE_FS3,
    NOTE_DS3, NOTE_B2,  NOTE_G3,  NOTE_D3,  NOTE_B2,  NOTE_DS4, NOTE_DS3,
    NOTE_B2,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_E4,  NOTE_B3,  NOTE_G3,  NOTE_G4,
    NOTE_E4,  NOTE_G3,  NOTE_B3,  NOTE_D4,  NOTE_E4,  NOTE_G4,  NOTE_E4,
    NOTE_G3,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2,

    NOTE_A2,  NOTE_A2,  NOTE_A3,  NOTE_A2,  NOTE_A2,  NOTE_G3,  NOTE_A2,
    NOTE_A2,  NOTE_F3,  NOTE_A2,  NOTE_A2,  NOTE_DS3, NOTE_A2,  NOTE_A2,
    NOTE_E3,  NOTE_F3,  NOTE_A2,  NOTE_A2,  NOTE_A3,  NOTE_A2,  NOTE_A2,
    NOTE_G3,  NOTE_A2,  NOTE_A2,  NOTE_A3,  NOTE_F3,  NOTE_D3,  NOTE_A3,
    NOTE_F3,  NOTE_D3,  NOTE_C4,  NOTE_A3,  NOTE_F3,  NOTE_A3,  NOTE_F3,
    NOTE_D3,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2,

    NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,  NOTE_D3,  NOTE_E2,
    NOTE_E2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_AS2, NOTE_E2,  NOTE_E2,
    NOTE_B2,  NOTE_C3,  NOTE_E2,  NOTE_E2,  NOTE_E3,  NOTE_E2,  NOTE_E2,
    NOTE_D3,  NOTE_E2,  NOTE_E2,  NOTE_B3,  NOTE_G3,  NOTE_E3,  NOTE_B2,
    NOTE_E3,  NOTE_G3,  NOTE_C4,  NOTE_B3,  NOTE_G3,  NOTE_B3,  NOTE_G3,
    NOTE_E3};

uint8_t doomDurations[] = {
    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 8,  8,  8,  2,

    8, 8, 8, 8, 8, 8, 8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,
    8, 8, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};
uint8_t doomDurationsSize = sizeof(doomDurations) / sizeof(uint8_t);

void doomSound() {
  for (uint8_t note = 0; note < doomDurationsSize; note++) {
    uint8_t duration = 1000 / doomDurations[note];
    M5Cardputer.Speaker.tone(doomMelody[note], duration);

    uint8_t pauseBetweenNotes = duration * 1.30;

    if (checkExitPress()) {
      return;
    }

    delay(pauseBetweenNotes);
  }
}

uint8_t shapeOfYouMelody[] = {
    NOTE_CS4, NOTE_E4,  NOTE_CS4, NOTE_CS4, NOTE_E4,  NOTE_CS4, NOTE_CS4,
    NOTE_E4,  NOTE_CS4, NOTE_DS4, NOTE_CS4, NOTE_CS4, NOTE_E4,  NOTE_CS4,
    NOTE_B3,  NOTE_CS4, NOTE_E4,  NOTE_CS4, NOTE_CS4, NOTE_E4,  NOTE_CS4,
    NOTE_DS4, NOTE_CS4, NOTE_E4,  NOTE_B3,  NOTE_E4,  NOTE_E4,  NOTE_E4,
    NOTE_E4,  NOTE_E4,  NOTE_E4,  NOTE_E4,  NOTE_E4,  NOTE_E4,  NOTE_E4,
    NOTE_E4,  NOTE_E4,  NOTE_E4,  NOTE_FS4, NOTE_GS4, NOTE_GS4, NOTE_GS4,
    NOTE_E4,  NOTE_FS4, NOTE_B4,  NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_GS4,
    NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_GS4, NOTE_FS4, NOTE_FS4,
    NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_GS4, NOTE_FS4, NOTE_E4,  NOTE_CS4,
    NOTE_CS4, NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_GS4,
    NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_B4,
    NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_E4,  NOTE_GS4, NOTE_FS4,
    NOTE_E4,  NOTE_E4,  NOTE_E4,  NOTE_B4,  NOTE_GS4, NOTE_GS4, NOTE_GS4,
    NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4, NOTE_FS4,
    NOTE_FS4, NOTE_FS4, NOTE_E4,  NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_CS4,
    NOTE_CS4, NOTE_GS3, NOTE_B3,  NOTE_CS4, NOTE_CS4, NOTE_FS4, NOTE_GS4,
    NOTE_E4,  NOTE_FS4, NOTE_B3,  NOTE_E4,  NOTE_FS4, NOTE_GS4, NOTE_FS4,
    NOTE_E4,  NOTE_CS4, NOTE_E4,  NOTE_GS4, NOTE_FS4, NOTE_E4,  NOTE_FS4,
    NOTE_CS4, NOTE_B4,  NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_FS4, NOTE_E4,
    NOTE_CS4, NOTE_E4,  NOTE_FS4, NOTE_GS4, NOTE_FS4, NOTE_E4,  NOTE_FS4,
    NOTE_E4,  NOTE_CS4, NOTE_CS4, NOTE_B3,  NOTE_CS4, NOTE_CS4, NOTE_FS4,
    NOTE_GS4, NOTE_E4,  NOTE_FS4, NOTE_FS4, NOTE_B3,  NOTE_FS4, NOTE_GS4,
    NOTE_FS4, NOTE_E4,  NOTE_CS4, NOTE_E4,  NOTE_GS4, NOTE_FS4, NOTE_E4,
    NOTE_FS4, NOTE_CS4, NOTE_B4,  NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_FS4,
    NOTE_E4,  NOTE_CS4, NOTE_B4,  NOTE_GS4, NOTE_GS4, NOTE_FS4, NOTE_FS4,
    NOTE_E4,  NOTE_CS4, NOTE_CS4, NOTE_GS3, NOTE_B3,  NOTE_E4,  NOTE_FS4,
    NOTE_GS4, NOTE_FS4, NOTE_E4,  NOTE_E4,  NOTE_E4,  NOTE_FS4, NOTE_FS4,
    NOTE_E4,  NOTE_FS4, NOTE_GS4, NOTE_FS4, NOTE_E4,  NOTE_E4,  NOTE_E4,
    NOTE_FS4, NOTE_CS4, NOTE_E4,  NOTE_FS4, NOTE_GS4, NOTE_CS4, NOTE_E4,
    NOTE_E4,  NOTE_FS4, NOTE_FS4, NOTE_E4,  NOTE_FS4, NOTE_GS4, NOTE_FS4,
    NOTE_E4,  NOTE_E4,  NOTE_FS4, NOTE_CS4, NOTE_CS4, NOTE_FS4, NOTE_GS4,
    NOTE_B4,  NOTE_GS4, NOTE_FS4, NOTE_E4,  NOTE_E4,  NOTE_FS4, NOTE_E4,
    NOTE_FS4, NOTE_GS4, NOTE_FS4, NOTE_E4,  NOTE_E4,  NOTE_FS4, NOTE_CS4,
    NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_E4,  NOTE_FS4, NOTE_GS4,
    NOTE_CS4, NOTE_E4,  NOTE_FS4, NOTE_E4,  NOTE_FS4, NOTE_E4,  NOTE_FS4,
    NOTE_GS4, NOTE_FS4, NOTE_E4,  NOTE_E4,  NOTE_FS4, NOTE_CS4, NOTE_CS4,
    NOTE_CS4, NOTE_E4,  NOTE_E4,  NOTE_FS4, NOTE_FS4, NOTE_GS4, NOTE_GS4,
    NOTE_E4,  NOTE_FS4, NOTE_GS4, NOTE_FS4, NOTE_E4,  NOTE_E4,  NOTE_FS4,
    NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_E4,  NOTE_E4,  NOTE_FS4, NOTE_FS4,
    NOTE_GS4, NOTE_GS4, NOTE_E4,  NOTE_FS4, NOTE_GS4, NOTE_FS4, NOTE_E4,
    NOTE_E4,  NOTE_FS4, NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_E4,  NOTE_E4,
    NOTE_FS4, NOTE_FS4, NOTE_GS4, NOTE_GS4, NOTE_E4,  NOTE_FS4, NOTE_GS4,
    NOTE_FS4, NOTE_E4,  NOTE_E4,  NOTE_FS4, NOTE_CS4, NOTE_CS4, NOTE_CS4,
    NOTE_CS4, NOTE_CS4, NOTE_CS4, NOTE_E4,  NOTE_FS4, NOTE_GS4, NOTE_CS4,
    NOTE_E4,  NOTE_FS4, NOTE_CS4,
};

uint8_t shapeOfYouDurations[] = {
    2, 2, 4, 2, 2, 4, 2, 2, 4, 2, 2, 2, 2, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 2,
    2, 8, 8, 4, 4, 8, 8, 8, 8, 8, 8, 8, 2, 8, 8, 4, 2, 8, 8, 4, 8, 8, 8, 4,
    4, 8, 8, 8, 8, 8, 4, 8, 4, 8, 8, 8, 8, 4, 2, 8, 8, 8, 8, 4, 8, 8, 8, 8,
    8, 8, 2, 8, 4, 8, 8, 8, 8, 8, 2, 4, 8, 8, 2, 4, 8, 8, 8, 8, 8, 8, 2, 8,
    8, 4, 4, 4, 8, 8, 2, 4, 4, 2, 4, 2, 2, 4, 8, 8, 8, 2, 2, 8, 4, 8, 4, 4,
    4, 4, 8, 8, 8, 8, 2, 8, 8, 4, 8, 8, 4, 2, 8, 4, 8, 4, 4, 4, 4, 2, 2, 2,
    2, 4, 8, 8, 8, 2, 2, 2, 4, 8, 4, 4, 4, 4, 8, 8, 8, 8, 2, 8, 8, 4, 8, 8,
    4, 2, 8, 8, 4, 8, 8, 4, 2, 2, 4, 2, 8, 8, 4, 8, 8, 4, 8, 8, 2, 8, 8, 4,
    8, 8, 4, 8, 8, 2, 8, 8, 4, 4, 4, 8, 8, 2, 8, 8, 4, 8, 8, 8, 4, 8, 2, 4,
    4, 8, 8, 4, 4, 8, 2, 8, 8, 4, 4, 4, 8, 8, 4, 8, 8, 8, 8, 8, 8, 4, 4, 4,
    4, 8, 2, 8, 8, 4, 8, 8, 8, 4, 8, 4, 4, 4, 4, 4, 4, 4, 2, 8, 8, 4, 8, 8,
    8, 4, 8, 4, 4, 4, 4, 4, 4, 4, 2, 8, 8, 4, 8, 8, 8, 4, 8, 4, 4, 4, 4, 4,
    4, 4, 2, 8, 8, 4, 8, 8, 8, 4, 8, 4, 8, 8, 8, 8, 8, 8, 4, 4, 4, 4, 2};
uint8_t shapeOfYouDurationsSize = sizeof(shapeOfYouDurations) / sizeof(uint8_t);

void shapeOfYouSound() {
  for (uint8_t note = 0; note < shapeOfYouDurationsSize; note++) {
    uint8_t duration = 1000 / shapeOfYouDurations[note];
    M5Cardputer.Speaker.tone(shapeOfYouMelody[note], duration);

    uint8_t pauseBetweenNotes = duration * 1.30;

    if (checkExitPress()) {
      return;
    }

    delay(pauseBetweenNotes);
  }
}

uint8_t gameOfThronesMelody[] = {
    NOTE_G4,  NOTE_C4,  NOTE_DS4, NOTE_F4,  NOTE_G4,  NOTE_C4,  NOTE_DS4,
    NOTE_F4,  NOTE_G4,  NOTE_C4,  NOTE_DS4, NOTE_F4,  NOTE_G4,  NOTE_C4,
    NOTE_DS4, NOTE_F4,  NOTE_G4,  NOTE_C4,  NOTE_E4,  NOTE_F4,  NOTE_G4,
    NOTE_C4,  NOTE_E4,  NOTE_F4,  NOTE_G4,  NOTE_C4,  NOTE_E4,  NOTE_F4,
    NOTE_G4,  NOTE_C4,  NOTE_E4,  NOTE_F4,  NOTE_G4,  NOTE_C4,

    NOTE_DS4, NOTE_F4,  NOTE_G4,  NOTE_C4,  NOTE_DS4, NOTE_F4,  NOTE_D4,
    NOTE_F4,  NOTE_AS3, NOTE_DS4, NOTE_D4,  NOTE_F4,  NOTE_AS3, NOTE_DS4,
    NOTE_D4,  NOTE_C4,

    NOTE_G4,  NOTE_C4,

    NOTE_DS4, NOTE_F4,  NOTE_G4,  NOTE_C4,  NOTE_DS4, NOTE_F4,  NOTE_D4,
    NOTE_F4,  NOTE_AS3, NOTE_DS4, NOTE_D4,  NOTE_F4,  NOTE_AS3, NOTE_DS4,
    NOTE_D4,  NOTE_C4,  NOTE_G4,  NOTE_C4,  NOTE_DS4, NOTE_F4,  NOTE_G4,
    NOTE_C4,  NOTE_DS4, NOTE_F4,

    NOTE_D4,  NOTE_F4,  NOTE_AS3, NOTE_D4,  NOTE_DS4, NOTE_D4,  NOTE_AS3,
    NOTE_C4,  NOTE_C5,  NOTE_AS4, NOTE_C4,  NOTE_G4,  NOTE_DS4, NOTE_DS4,
    NOTE_F4,  NOTE_G4,

    NOTE_C5,  NOTE_AS4, NOTE_C4,  NOTE_G4,  NOTE_DS4, NOTE_DS4, NOTE_D4,
    NOTE_C5,  NOTE_G4,  NOTE_GS4, NOTE_AS4, NOTE_C5,  NOTE_G4,  NOTE_GS4,
    NOTE_AS4, NOTE_C5,  NOTE_G4,  NOTE_GS4, NOTE_AS4, NOTE_C5,  NOTE_G4,
    NOTE_GS4, NOTE_AS4,

    REST,     NOTE_GS5, NOTE_AS5, NOTE_C6,  NOTE_G5,  NOTE_GS5, NOTE_AS5,
    NOTE_C6,  NOTE_G5,  NOTE_GS5, NOTE_AS5, NOTE_C6,  NOTE_G5,  NOTE_GS5,
    NOTE_AS5};

uint8_t gameOfThronesDurations[] = {
    8,  8,  16, 16, 8,  8,  16, 16, 8,  8,  16, 16, 8, 8,  16, 16, 8,
    8,  16, 16, 8,  8,  16, 16, 8,  8,  16, 16, 8,  8, 16, 16, 4,  4,

    16, 16, 4,  4,  16, 16, 1,  4,  4,  16, 16, 4,  4, 16, 16, 1,

    4,  4,

    16, 16, 4,  4,  16, 16, 1,  4,  4,  16, 16, 4,  4, 16, 16, 1,  4,
    4,  16, 16, 4,  4,  16, 16,

    2,  4,  4,  8,  8,  8,  8,  1,  2,  2,  2,  2,  2, 4,  4,  1,

    2,  2,  2,  2,  2,  4,  4,  8,  8,  16, 16, 8,  8, 16, 16, 8,  8,
    16, 16, 8,  8,  16, 16,

    4,  16, 16, 8,  8,  16, 16, 8,  16, 16, 16, 8,  8, 16, 16};
uint8_t gameOfThronesDurationsSize =
    sizeof(gameOfThronesDurations) / sizeof(uint8_t);

void gameOfThronesSound() {
  for (uint8_t note = 0; note < gameOfThronesDurationsSize; note++) {
    uint8_t duration = 1000 / gameOfThronesDurations[note];
    M5Cardputer.Speaker.tone(gameOfThronesMelody[note], duration);

    uint8_t pauseBetweenNotes = duration * 1.30;

    if (checkExitPress()) {
      return;
    }

    delay(pauseBetweenNotes);
  }
}