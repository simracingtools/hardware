#define ENC_STEPS 4

#define JOY_BTN_IGN         1
#define JOY_BTN_START       2
#define JOY_BTN_PIT         3
#define JOY_BTN_TCR_TOGGLE 4
#define JOY_BTN_TCR1_DEC    5
#define JOY_BTN_TCR1_INC    6
#define JOY_BTN_TCR2_DEC    7
#define JOY_BTN_TCR2_INC   8
#define JOY_BTN_ABS_TOGGLE 9
#define JOY_BTN_ABS_DEC    10
#define JOY_BTN_ABS_INC    11
#define JOY_BTN_ENG1_DEC   12
#define JOY_BTN_ENG1_INC   13
#define JOY_BTN_ENG2_DEC   14
#define JOY_BTN_ENG2_INC   15

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
