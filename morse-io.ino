#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Pin assignments
const int morseButtonPin  = 2;
const int spaceButtonPin  = 3;
const int deleteButtonPin = 4;
const int scrollLeftPin   = 5;
const int scrollRightPin  = 6;

// Morse tracking
unsigned long pressStart = 0;
unsigned long lastRelease = 0;
bool isPressed = false;
String morseInput = "";
String message = "";

// Scroll
int scrollIndex = 0;

void setup() {
  pinMode(morseButtonPin, INPUT_PULLUP);
  pinMode(spaceButtonPin, INPUT_PULLUP);
  pinMode(deleteButtonPin, INPUT_PULLUP);
  pinMode(scrollLeftPin, INPUT_PULLUP);
  pinMode(scrollRightPin, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Morse I/O");
  lcd.setCursor(0, 1);
  lcd.print("Press to Start!");

  // Wait for Morse button to be pressed and released
  while (digitalRead(morseButtonPin) == HIGH); // wait for press
  while (digitalRead(morseButtonPin) == LOW);  // wait for release

  lcd.clear();
  lcd.print("Morse Typing:");
  Serial.begin(9600);
}


void loop() {
  // Morse Input
  bool currentState = digitalRead(morseButtonPin) == LOW;

  if (currentState && !isPressed) {
    isPressed = true;
    pressStart = millis();
  }

  if (!currentState && isPressed) {
    isPressed = false;
    unsigned long pressDuration = millis() - pressStart;

    if (pressDuration < 250) {
      morseInput += ".";
    } else {
      morseInput += "-";
    }

    lcd.setCursor(0, 1);
    lcd.print(morseInput + "            ");
    lastRelease = millis();
  }

  // End of letter
  if (!isPressed && morseInput.length() > 0 && millis() - lastRelease > 1500) {
    char letter = decodeMorse(morseInput);
    message += letter;
    morseInput = "";
    scrollIndex = max(0, message.length() - 16);
    updateLCD();
  }

  // Space Button
  if (digitalRead(spaceButtonPin) == LOW) {
    message += ' ';
    scrollIndex = max(0, message.length() - 16);
    updateLCD();
    delay(300);
  }

  // Delete / Clear Button
  if (digitalRead(deleteButtonPin) == LOW) {
    unsigned long holdStart = millis();
    while (digitalRead(deleteButtonPin) == LOW);  // wait for release
    unsigned long duration = millis() - holdStart;

    if (duration < 1000) {
      // Short press deletes last character
      if (message.length() > 0) {
        message.remove(message.length() - 1);
        scrollIndex = max(0, message.length() - 16);
        updateLCD();
      }
    } else {
      // Long press clears entire message
      message = "";
      scrollIndex = 0;
      updateLCD();
    }
    delay(300);
  }

  // Scroll Left
  if (digitalRead(scrollLeftPin) == LOW) {
    if (scrollIndex > 0) scrollIndex--;
    updateLCD();
    delay(200);
  }

  // Scroll Right
  if (digitalRead(scrollRightPin) == LOW) {
    if (scrollIndex < max(0, message.length() - 16)) scrollIndex++;
    updateLCD();
    delay(200);
  }
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Message:");
  lcd.setCursor(0, 1);

  if (message.length() <= 16) {
    scrollIndex = 0;
    lcd.print(message);
  } else {
    if (scrollIndex < message.length() - 16) {
      scrollIndex = message.length() - 16;  // auto-scroll to right
    }
    lcd.print(message.substring(scrollIndex, scrollIndex + 16));
  }

  Serial.println("Message: " + message);
}

char decodeMorse(String code) {
  if (code == ".-") return 'A';
  if (code == "-...") return 'B';
  if (code == "-.-.") return 'C';
  if (code == "-..") return 'D';
  if (code == ".") return 'E';
  if (code == "..-.") return 'F';
  if (code == "--.") return 'G';
  if (code == "....") return 'H';
  if (code == "..") return 'I';
  if (code == ".---") return 'J';
  if (code == "-.-") return 'K';
  if (code == ".-..") return 'L';
  if (code == "--") return 'M';
  if (code == "-.") return 'N';
  if (code == "---") return 'O';
  if (code == ".--.") return 'P';
  if (code == "--.-") return 'Q';
  if (code == ".-.") return 'R';
  if (code == "...") return 'S';
  if (code == "-") return 'T';
  if (code == "..-") return 'U';
  if (code == "...-") return 'V';
  if (code == ".--") return 'W';
  if (code == "-..-") return 'X';
  if (code == "-.--") return 'Y';
  if (code == "--..") return 'Z';
  if (code == ".-.-.-") return '.';
  if (code == "--..--") return ',';
  if (code == "..--..") return '?';
  if (code == "-.-.--") return '!';
  if (code == "-....-") return '-';
  if (code == "-..-.") return '/';
  if (code == ".--.-.") return '@';
  if (code == "-.--.") return '(';
  if (code == "-.--.-") return ')';
  if (code == ".-..-.") return '"';

  return '?';
}
