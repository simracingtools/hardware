#define ENC_STEPS 4

#define KEY_IGN        "i"
#define KEY_START      KEY_S
#define KEY_PIT        "p"
#define KEY_TCR_TOGGLE KEY_Q
#define KEY_TCR1_DEC   "1"
#define KEY_TCR1_INC   "2"
#define KEY_TCR2_DEC   "3"
#define KEY_TCR2_INC   "4"
#define KEY_ABS_TOGGLE KEY_A
#define KEY_ABS_DEC    "5"
#define KEY_ABS_INC    "6"
#define KEY_ENG1_DEC   "7"
#define KEY_ENG1_INC   "8"
#define KEY_ENG2_DEC   "9"
#define KEY_ENG2_INC   "0"

#define PIN_SW_IGN 0         // Ignition switch
#define PIN_BTN_START 1      // Engine starter
#define PIN_SW_PIT 2         // ACC1 switch
#define PIN_SW_TCR 3         // ACC2 switch
#define PIN_BTN_ENG 4        // ENG push
#define PIN_BTN_ABS 17       // ABS push
#define PIN_BTN_TCR 18       // TCR push
#define PIN_LED_RED 19       // LED red
#define PIN_LED_BLUE 20      // LED blue
#define PINS_ENC_ENG 5,16    // Engine encoder pins
#define PINS_ENC_ABS 6,15    // ABS encoder pins
#define PINS_ENC_TCR 7,14    // TCR encoder pins

#define BOUNCE_TIME 10       // Bounce delay for button lib
#define LED_BRIGHTNESS 128   // PWM value for LED brightness 
