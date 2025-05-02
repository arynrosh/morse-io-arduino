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
unsigned long lastInteraction = 0;
bool isPressed = false;
bool showingSplash = false;
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

  Serial.begin(9600);
  showingSplash = true;
}

void loop() {
  // Wake from splash screen
  if (showingSplash && digitalRead(morseButtonPin) == LOW) {
    while (digitalRead(morseButtonPin) == LOW);
    lcd.clear();
    lcd.print("Morse Typing:");
    scrollIndex = 0;
    morseInput = "";
    message = "";
    showingSplash = false;
    lastInteraction = millis();
    delay(200);
    return;
  }

  if (showingSplash) return;

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
    lastInteraction = millis();
  }

  // End of letter
  if (!isPressed && morseInput.length() > 0 && millis() - lastRelease > 1500) {
    char letter = decodeMorse(morseInput);
    message += letter;
    morseInput = "";
    scrollIndex = max(0, message.length() - 16);
    updateLCD();
    lastInteraction = millis();
  }

  // Space Button
  if (digitalRead(spaceButtonPin) == LOW) {
    message += ' ';
    scrollIndex = max(0, message.length() - 16);
    updateLCD();
    lastInteraction = millis();
    delay(300);
  }

  // Delete / Clear Button
  if (digitalRead(deleteButtonPin) == LOW) {
    unsigned long holdStart = millis();
    while (digitalRead(deleteButtonPin) == LOW);
    unsigned long duration = millis() - holdStart;

    if (duration < 1000) {
      if (message.length() > 0) {
        message.remove(message.length() - 1);
        scrollIndex = max(0, message.length() - 16);
        updateLCD();
      }
    } else {
      message = "";
      scrollIndex = 0;
      updateLCD();
    }
    lastInteraction = millis();
    delay(300);
  }

  // Scroll Left
  if (digitalRead(scrollLeftPin) == LOW) {
    if (scrollIndex > 0) scrollIndex--;
    updateLCD();
    lastInteraction = millis();
    delay(200);
  }

  // Scroll Right
  if (digitalRead(scrollRightPin) == LOW) {
    if (scrollIndex < max(0, message.length() - 16)) scrollIndex++;
    updateLCD();
    lastInteraction = millis();
    delay(200);
  }

  // Timeout
  if (!showingSplash && millis() - lastInteraction > 10000) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Morse I/O");
    lcd.setCursor(0, 1);
    lcd.print("Press to Start!");
    showingSplash = true;
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
      scrollIndex = message.length() - 16;
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
