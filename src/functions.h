/**
 * @brief Prints a transition screen with two lines of message and waits one second.
 *
 * Print a transition screen with a text message centered on the screen,
 * stating what will be done next, and wait a second to move to the next screen.
 *
 * @param text1 Text to be printed on the first line.
 * @param text2 Text to be printed on the second line.
 */
void transitionScreenTwoLines(char *text1, char *text2) {
  DISPLAY.fillScreen(BG_COLOR);
  DISPLAY.setTextSize(BIG_TEXT);
  DISPLAY.drawString(text1, DISPLAY_CENTER_X, 50);
  DISPLAY.drawString(text2, DISPLAY_CENTER_X, 80);
  delay(1000);
}

void drawRoundRectMenuItems(int y, int index) {
  if (cursor == index) {
    DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Highlight the current menu item
    DISPLAY.setTextColor(BG_COLOR);
  } else {
    DISPLAY.fillRoundRect(5, y, DISPLAY.width() - 10, 30, 10, BG_COLOR);
    DISPLAY.setTextColor(MAIN_COLOR);
  }
  DISPLAY.drawRoundRect(5, y, DISPLAY.width() - 10, 30, 10, MAIN_COLOR); // Draw the border of the menu item
  DISPLAY.setCursor(20, y + 16);
}