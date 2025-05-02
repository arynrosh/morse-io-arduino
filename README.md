# Morse I/O with LCD Display

This Arduino project lets you input Morse code through a pushbutton and view the decoded message on a 16x2 LCD screen. It also includes buttons to insert spaces, delete characters, clear the message, and scroll through the message if it exceeds 16 characters.

---

## Features

- Morse code entry via single button (dot/dash by press duration)
- Automatic decoding into alphabet and punctuation
- Real-time message display on LCD
- Add space, delete characters, or clear entire message
- Scroll left/right through long messages

---

## Hardware Required

- Arduino UNO
- 16x2 LCD Display
- 5 Pushbuttons
- Jumper wires
- Breadboard or protoboard
- USB Cable
  
---

## Pin Configuration

| Component         | Arduino Pin |
|------------------|-------------|
| LCD RS           | 7           |
| LCD EN           | 8           |
| LCD D4           | 9           |
| LCD D5           | 10          |
| LCD D6           | 11          |
| LCD D7           | 12          |
| Morse Button     | 2           |
| Space Button     | 3           |
| Delete Button    | 4           |
| Scroll Left      | 5           |
| Scroll Right     | 6           |

---

## Schematic Diagram

![breadboard](https://github.com/user-attachments/assets/0737f0da-3754-40a7-9505-99befac385b3)

![schematic](https://github.com/user-attachments/assets/7b542d55-cbfc-4ebe-97cb-e1e83b62f8f6)

---

## How to Run

1. Connect all buttons and LCD according to the pinout above.
2. Upload the `morse-io.ino` sketch to your Arduino UNO using the Arduino IDE.
3. Power the board and wait for the prompt: **“Press to Start!”**
4. Press the Morse button once to begin typing.
5. Start entering Morse code by pressing and holding for dots and dashes.

---

## Demo Video

Watch the Morse I/O project in action:  
[![Watch the video](https://img.youtube.com/vi/JBAV1wwMZnk/0.jpg)](https://www.youtube.com/watch?v=JBAV1wwMZnk)

---

## How It Works

- **Morse Button (Pin 2):**
  - Press and release quickly → `.` (dot)
  - Press and hold (>250ms) → `-` (dash)
  - If no press for 1.5s → decode current Morse sequence

- **Space Button (Pin 3):**
  - Adds a space to the message

- **Delete Button (Pin 4):**
  - Short press → delete last character
  - Long press (>1s) → clear entire message

- **Scroll Buttons:**
  - **Scroll Left (Pin 5)** → move left in message
  - **Scroll Right (Pin 6)** → move right in message

- **LCD Display:**
  - Line 1: Static label (e.g., “Message:”)
  - Line 2: Current message (scrollable)

---

## Supported Characters

Morse decoder supports:
- Letters: A–Z  
- Symbols: `. , ? ! - / @ ( ) "`

Any unrecognized Morse pattern will return a `?`.

---

## License

This project is licensed under the MIT License.  
You may use, modify, and distribute it for educational or personal use.

---

## Contributions

Feel free to fork, suggest improvements, or submit pull requests.  
Ideas like EEPROM saving, tone output, or better decoding logic are welcome!
