# Morse I/O on Arduino

This project turns your Arduino into a functional Morse code input/output device using physical buttons and a 16x2 LCD display. Users can type messages in Morse code, view them on the LCD, and scroll through long messages. Great for learning Morse and building embedded interaction systems.

## 📦 Features

- Tap-based Morse input using a button
- Dot/dash distinction based on press duration
- Real-time Morse display
- Auto letter detection after pause
- Message display with horizontal scrolling
- Space, delete (short press), and full-clear (long press) controls

---

## 🧠 How It Works

- A **short press (<250ms)** is treated as a dot `.`  
- A **long press (≥250ms)** is treated as a dash `-`  
- After **1.5 seconds of no input**, the current Morse code sequence is translated into a character  
- Users can add **spaces**, **delete the last character**, or **clear the full message**  
- Use **scroll buttons** to navigate long messages (>16 characters) on the display  

---

## 🖼️ Schematic


**Wiring (Arduino UNO):**

| Component          | Pin |
|--------------------|-----|
| LCD RS             | 7   |
| LCD EN             | 8   |
| LCD D4             | 9   |
| LCD D5             | 10  |
| LCD D6             | 11  |
| LCD D7             | 12  |
| Morse Input Button | 2   |
| Space Button       | 3   |
| Delete Button      | 4   |
| Scroll Left        | 5   |
| Scroll Right       | 6   |

*Use `INPUT_PULLUP` for all buttons.*

---

## ▶️ How to Run

1. **Connect components** using the schematic above.
2. **Upload the code** using the Arduino IDE.
3. **Open Serial Monitor (9600 baud)** to see message logs.
4. **Press the Morse input button**:
   - Tap: `.` (dot)
   - Hold: `-` (dash)
5. After 1.5 seconds pause, the character will appear.
6. Use the extra buttons:
   - **Space**: adds space
   - **Delete**: short press removes last character; long press clears message
   - **Scroll Left/Right**: to move through long messages

---

## 📷 Photos & Videos

![breadboard](https://github.com/user-attachments/assets/b6580166-20fa-4458-bc2f-b806848c8875)
![schematic](https://github.com/user-attachments/assets/47385173-b6ee-47fe-af52-bb616b39e30f)


---

## 🛠️ Dependencies

- Arduino UNO (or compatible)
- 16x2 LCD (HD44780 compatible)
- 5 tactile buttons
- Arduino `LiquidCrystal` library (included by default)

---

## 📄 License

MIT License. Feel free to use and modify this project.

---

## 💬 Credits

Developed by Aryan Roshan using components from the ELEGOO kit.

