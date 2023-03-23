#include <Keyboard.h>
#include <ctype.h>

#include <Keypad.h>

const byte ROWS = 10; // ten rows
const byte COLS = 9; // nine columns

char keys[ROWS][COLS] = {
    {KEY_BACKSPACE, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, // 1
    {' ', '1', '2', KEY_ESC, 'q', KEY_TAB, 'a', KEY_CAPS_LOCK, 'z'}, // 11
    {' ', '4', '3', 'e', 'w', 's', 'd', 'c', 'x'}, // 12
    {' ', '6', '5', 'r', 't', 'g', 'f', 'b', 'v'}, // 13
    {' ', '8', '7', 'u', 'y', 'h', 'j', 'n', ' '}, // 14
    {' ', '0', '9', 'o', 'i', 'l', 'k', 'm', ','}, // 15
    {' ', '=', '-', '[', 'p', '\'', ';', '/', '.'}, // 16
    {' ', KEY_DELETE, ']', KEY_RETURN, '\\', KEY_F4, KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT, KEY_RIGHT_CTRL},// 17 0x7e (ª),
    {' ', KEY_LEFT_ARROW, KEY_INSERT, KEY_F7, KEY_F8, KEY_F5, KEY_F1, KEY_F2, KEY_F10}, // 18 0x81 = COPY = Ctrl +c
    {' ', KEY_UP_ARROW, KEY_RIGHT_ARROW, KEY_DOWN_ARROW, KEY_F9, KEY_F6, KEY_F3, KEY_END, KEY_PAGE_DOWN} // 19
};

// KEY_LEFT_SHIFT

// The pins mapping for Arduino Leonardo

byte rowPins[ROWS] = {9, 10, 11, 12, A0, A1, A2, A3, A4, A5}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {0, 1, 2, 3, 4, 5, 6, 7, 8}; // connect to the column pinouts of the keypad

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

unsigned long loopCount;
unsigned long startTime;
int x = 0;

void setup()
{
    Serial.begin(9600);
    loopCount = 0;
    startTime = millis();

    Keyboard.begin();  // Initialise the library.
}


void loop()
{
    loopCount++;
    if ( (millis() - startTime) > 5000 ) {
        startTime = millis();
        loopCount = 0;
    }

    if (kpd.getKeys()) {
        for (int i = 0; i < LIST_MAX; i++) { 
            if ( kpd.key[i].stateChanged ) { 
                switch (kpd.key[i].kstate) {  
                    case PRESSED:
                        Keyboard.press(kpd.key[i].kchar);
                        break;

                    case HOLD:
                        break;

                    case RELEASED:
                        Keyboard.release(kpd.key[i].kchar);
                        break;

                    case IDLE:
                        break;
                } // switch

            }
        }
    }
}  
