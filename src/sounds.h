#include "pitches.h"

bool checkStopSoundPress() {
  M5Cardputer.update();
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) ||
      M5Cardputer.Keyboard.isKeyPressed('`') || M5Cardputer.Keyboard.isKeyPressed(',')) {
    return true;
  }
  return false;
}

struct Melody {
  int note;
  int duration;
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
int superMarioMelodySize = sizeof(superMarioMelody) / sizeof(Melody);

int superMarioDelay[] = {
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
  for (int note = 0; note < superMarioMelodySize; note++) {
    M5Cardputer.Speaker.tone(superMarioMelody[note].note,
                             superMarioMelody[note].duration);

    if (checkStopSoundPress()) {
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
int imperialMarchMelodySize = sizeof(imperialMarchMelody) / sizeof(Melody);

int imperialMarchDelay[] = {
    500, 500, 500, 400, 100, 500, 400, 100, 1000,
    500, 500, 500, 400, 100, 500, 400, 100, 1000,
};

void imperialMarchSound() {
  for (int note = 0; note < imperialMarchMelodySize; note++) {
    M5Cardputer.Speaker.tone(imperialMarchMelody[note].note,
                             imperialMarchMelody[note].duration);

    if (checkStopSoundPress()) {
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
int ahaTakeOnMeMelodySize = sizeof(ahaTakeOnMeMelody) / sizeof(Melody);

int ahaTakeOnMeDelay[] = {
    198, 198, 198, 198, 188, 198, 188, 198, 188, 198, 188, 198, 198,
    198, 198, 198, 198, 198, 198, 198, 188, 198, 188, 198, 188, 198,
    188, 198, 198, 198, 198, 198, 198, 198, 198, 198, 188, 198, 188,
    198, 188, 198, 188, 198, 198, 198, 198, 198, 198, 198, 198, 198,
    188, 198, 188, 198, 188, 198, 188, 198, 198, 198, 198, 19,
};

void ahaTakeOnMeSound() {
  for (int note = 0, iDelay = 0; note < ahaTakeOnMeMelodySize; note++) {
    M5Cardputer.Speaker.tone(ahaTakeOnMeMelody[note].note,
                             ahaTakeOnMeMelody[note].duration);

    if (checkStopSoundPress()) {
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
int jingleBellsMelodySize = sizeof(jingleBellsMelody) / sizeof(Melody);

int jingleBellsDelay[] = {
    250, 250, 500, 250, 250, 500, 250, 250, 250, 250, 1000,
    250, 250, 500, 250, 250, 500, 250, 250, 250, 350, 1000,
};

void jingleBellsSound() {
  for (int note = 0; note < jingleBellsMelodySize; note++) {
    M5Cardputer.Speaker.tone(jingleBellsMelody[note].note,
                             jingleBellsMelody[note].duration);

    if (checkStopSoundPress()) {
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
int ozzyOsbornCrazyTrainMelodySize =
    sizeof(ozzyOsbornCrazyTrainMelody) / sizeof(Melody);

int ozzyOsbornCrazyTrainDelay[] = {
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
  for (int note = 0; note < ozzyOsbornCrazyTrainMelodySize; note++) {
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

    if (checkStopSoundPress()) {
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
int starWarsMelodySize = sizeof(starWarsMelody) / sizeof(Melody);

int starWarsDelay[] = {
    177,  177, 177,  1010, 1010, 177, 177, 177,  1010, 510, 177,  177,  177,
    1010, 510, 177,  177,  177,  677, 333, 177,  177,  177, 1010, 1010, 177,
    177,  177, 1010, 510,  177,  177, 177, 1010, 510,  177, 177,  177,  677,
};

void starWarsSound() {
  for (int note = 0, iDelay = 0; note < starWarsMelodySize; note++) {
    M5Cardputer.Speaker.tone(starWarsMelody[note].note,
                             starWarsMelody[note].duration);

    if (checkStopSoundPress()) {
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

int nokiaMelody[] = {NOTE_E5,  NOTE_D5, NOTE_FS4, NOTE_GS4, NOTE_CS5,
                     NOTE_B4,  NOTE_D4, NOTE_E4,  NOTE_B4,  NOTE_A4,
                     NOTE_CS4, NOTE_E4, NOTE_A4};

int nokiaDurations[] = {8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 2};
int nokiaDurationsSize = sizeof(nokiaDurations) / sizeof(int);

void nokiaSound() {
  for (int note = 0; note < nokiaDurationsSize; note++) {
    int duration = 1000 / nokiaDurations[note];
    M5Cardputer.Speaker.tone(nokiaMelody[note], duration);

    int pauseBetweenNotes = duration * 1.30;

    if (checkStopSoundPress()) {
      return;
    }

    delay(pauseBetweenNotes);
  }
}

int theSimpsonsMelody[] = {
    NOTE_C4,  NOTE_E4,  NOTE_FS4, REST,     NOTE_A4,  NOTE_G4, NOTE_E4,
    NOTE_C4,  NOTE_A3,  NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3, REST,
    NOTE_FS3, NOTE_FS3, NOTE_FS3, NOTE_G3,  NOTE_AS3, NOTE_B3, REST};

int theSimpsonsDurations[] = {2, 4, 4, 32, 8, 2, 4, 4, 8, 8, 8,
                              8, 4, 2, 8,  8, 8, 4, 2, 2, 2};
int theSimpsonsDurationSize = sizeof(theSimpsonsDurations) / sizeof(int);

void theSimpsonsSound() {
  for (int note = 0; note < theSimpsonsDurationSize; note++) {
    int duration = 1000 / theSimpsonsDurations[note];
    M5Cardputer.Speaker.tone(theSimpsonsMelody[note], duration);

    int pauseBetweenNotes = duration * 1.30;

    if (checkStopSoundPress()) {
      return;
    }

    delay(pauseBetweenNotes);
  }
}

int pacmanMelody[] = {NOTE_B4,  NOTE_B5,  NOTE_FS5, NOTE_DS5, NOTE_B5, NOTE_FS5,
                      NOTE_DS5, NOTE_C5,  NOTE_C6,  NOTE_G6,  NOTE_E6, NOTE_C6,
                      NOTE_G6,  NOTE_E6,

                      NOTE_B4,  NOTE_B5,  NOTE_FS5, NOTE_DS5, NOTE_B5, NOTE_FS5,
                      NOTE_DS5, NOTE_DS5, NOTE_E5,  NOTE_F5,  NOTE_F5, NOTE_FS5,
                      NOTE_G5,  NOTE_G5,  NOTE_GS5, NOTE_A5,  NOTE_B5};

int pacmanDurations[] = {16, 16, 16, 16, 32, 16, 8, 16, 16, 16, 16, 32, 16, 8,

                         16, 16, 16, 16, 32, 16, 8, 32, 32, 32, 32, 32, 32, 32,
                         32, 16, 8};
int pacmanDurationSize = sizeof(pacmanDurations) / sizeof(int);

void pacmanSound() {
  for (int note = 0; note < pacmanDurationSize; note++) {
    int duration = 1000 / pacmanDurations[note];
    M5Cardputer.Speaker.tone(pacmanMelody[note], duration);

    int pauseBetweenNotes = duration * 1.30;

    if (checkStopSoundPress()) {
      return;
    }

    delay(pauseBetweenNotes);
  }
}

int doomMelody[] = {
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

int doomDurations[] = {
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
int doomDurationsSize = sizeof(doomDurations) / sizeof(int);

void doomSound() {
  for (int note = 0; note < doomDurationsSize; note++) {
    int duration = 1000 / doomDurations[note];
    M5Cardputer.Speaker.tone(doomMelody[note], duration);

    int pauseBetweenNotes = duration * 1.30;

    if (checkStopSoundPress()) {
      return;
    }

    delay(pauseBetweenNotes);
  }
}

int shapeOfYouMelody[] = {
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

int shapeOfYouDurations[] = {
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
int shapeOfYouDurationsSize = sizeof(shapeOfYouDurations) / sizeof(int);

void shapeOfYouSound() {
  for (int note = 0; note < shapeOfYouDurationsSize; note++) {
    int duration = 1000 / shapeOfYouDurations[note];
    M5Cardputer.Speaker.tone(shapeOfYouMelody[note], duration);

    int pauseBetweenNotes = duration * 1.30;

    if (checkStopSoundPress()) {
      return;
    }

    delay(pauseBetweenNotes);
  }
}

int gameOfThronesMelody[] = {
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

int gameOfThronesDurations[] = {
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
int gameOfThronesDurationsSize = sizeof(gameOfThronesDurations) / sizeof(int);

void gameOfThronesSound() {
  for (int note = 0; note < gameOfThronesDurationsSize; note++) {
    int duration = 1000 / gameOfThronesDurations[note];
    M5Cardputer.Speaker.tone(gameOfThronesMelody[note], duration);

    int pauseBetweenNotes = duration * 1.30;

    if (checkStopSoundPress()) {
      return;
    }

    delay(pauseBetweenNotes);
  }
}