// Key mapping definitions
#define KEY_IGN             "i"
#define KEY_START         KEY_S
#define KEY_PIT             "p"
#define KEY_TCR_TOGGLE    KEY_Q
#define KEY_TCR1_DEC        "1"
#define KEY_TCR1_INC        "2"
#define KEY_TCR2_DEC        "3"
#define KEY_TCR2_INC        "4"
#define KEY_ABS_TOGGLE    KEY_A
#define KEY_ABS_DEC         "5"
#define KEY_ABS_INC         "6"
#define KEY_ENG1_DEC        "7"
#define KEY_ENG1_INC        "8"
#define KEY_ENG2_DEC        "9"
#define KEY_ENG2_INC        "0"

// Joystick button definitions
#define JOY_BTN_BB1_DEC      1
#define JOY_BTN_BB1_INC      2
#define JOY_BTN_BB1_TOGGLE   3
#define JOY_BTN_BB2_DEC      4
#define JOY_BTN_BB2_INC      5
#define JOY_BTN_BB2_TOGGLE   6
#define JOY_BTN_BB_CAR       7
#define JOY_BTN_BB_PIT       8

// Pin assignment definitions
#define PIN_R1              16   // Relay 1
#define PIN_R2              17   // Relay 2
#define PIN_R3              18   // Relay 3
#define PIN_R4              19   // Relay 4
#define PIN_R5              20   // Relay 5
#define PIN_R6              21   // Relay 6
#define PIN_R7              22   // Relay 7
#define PIN_R8              23   // Relay 8
int relayPins[] = {PIN_R1, PIN_R2, PIN_R3, PIN_R4, PIN_R5, PIN_R6, PIN_R7, PIN_R8};

#define PIN_BTN_BBCAR        0
#define PIN_BTN_BBPIT        1
#define PIN_BTN_BB1          4   // BlackBox1 push
#define PIN_BTN_BB2          7   // BlackBox1 push

#define PINS_ENC_BB1       2,3   // BlackBox1 encoder pins
#define PINS_ENC_BB2       5,6   // BlackBox2 encoder pins

// Configuration definitions
#define ENC_STEPS            8   // Default encoder sensitivity
#define LED_BRIGHTNESS      12   // Default PWM value for LED brightness 
#define JOYSTICK_MODE    false   // Default operation mode Keyboard
#define BOUNCE_TIME         20   // Bounce delay for buttons
#define CONFIG_ADDRESS       0   // EEPROM address for config data
#define JOY_BTN_DURATION   100   // Delay between button press and release
#define LOOP_DELAY         100   // Delay in main loop
