// Key mapping definitions
#define KEY_EXIT        KEY_ESC
#define KEY_BB_LAP       KEY_F1
#define KEY_BB_PABS      KEY_F2
#define KEY_BB_PREL      KEY_F3
#define KEY_BB_FUEL      KEY_F4
#define KEY_BB_TYRE      KEY_F5
#define KEY_BB_PIT       KEY_F7
#define KEY_BB_CAR       KEY_F8
#define KEY_BB_RADIO    KEY_F10

// Joystick button definitions
#define JOY_BTN_BB1_DEC      1
#define JOY_BTN_BB1_INC      2
#define JOY_BTN_BB1_TOGGLE   3
#define JOY_BTN_BB2_DEC      4
#define JOY_BTN_BB2_INC      5
#define JOY_BTN_BB2_TOGGLE   6

#define JOY_BTN_BB_CAR       7
#define JOY_BTN_BB_PIT       8
#define JOY_BTN_BB_FUEL      9
#define JOY_BTN_BB_TYRE     10
#define JOY_BTN_BB_PABS     11
#define JOY_BTN_BB_PREL     12
#define JOY_BTN_BB_LAP      13

#define JOY_BTN_RA1_DEC     14
#define JOY_BTN_RA1_INC     15
#define JOY_BTN_RA1_TOGGLE  16
#define JOY_BTN_RA2_DEC     17
#define JOY_BTN_RA2_INC     18
#define JOY_BTN_RA2_TOGGLE  19

#define JOY_BTN_VIEW_UP     20
#define JOY_BTN_VIEW_DN     21

// Macro definitions
#define TXT_FUEL            "#fuel "
#define TXT_CLEAR_TYRES     "#cleartires"
#define TXT_CLEAR_FUEL      "#clear fuel"
#define TXT_TYRES_FRONT     "#rf lf"
#define TXT_TYRES_REAR      "#rr lr"
#define TXT_TYRES_LEFT      "#lf lr"
#define TXT_TYRES_RIGHT     "#rf rr"

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

#define PIN_BTN_RA1          2   // Radio1 push
#define PIN_BTN_RA2          5   // Radio2 push
#define PINS_ENC_RA1       0,1   // Radio1 encoder pins
#define PINS_ENC_RA2       3,4   // Radio2 encoder pins
#define PIN_SW_VIEW_DN       6   // Switch view down
#define PIN_SW_VIEW_UP       7   // Switch view up
#define PIN_BTN_EXIT         8   // BTN exit
#define PIN_BTN_BBCAR        9   // InCar BB
#define PIN_BTN_BBPIT       10   // InPit BB
#define PIN_BTN_BBFUEL      11   // Fuel BB
#define PIN_BTN_BBTYRE      12   // Tyre BB
#define PIN_LED_T_RL        13   // Tyre Rear/Left LED
#define PIN_BTN_BBPREL      24   // PosRel BB
#define PIN_BTN_BBPABS      25   // PosAbs BB
#define PIN_BTN_BBLAP       26   // Lap BB
#define PIN_LED_FUEL        30   // Refuel LED
#define PINS_ENC_FUEL    29,28   // Fuel encoder pins
#define PIN_BTN_FUEL        27   // Fuel enc push
#define PIN_SW_O_R          32   // Switch oval/road
#define PIN_LED_T_FR        35   // Tyre Front/Right LED
#define PIN_BTN_BB1         36   // BlackBox1 push
#define PIN_BTN_BB2         37   // BlackBox2 push
#define PINS_ENC_BB1     14,15   // BlackBox1 encoder pins
#define PINS_ENC_BB2     38,39   // BlackBox2 encoder pins
#define PIN_BTN_TY_CLEAR    31   // BTN clear tyres
#define PIN_SW_TY_FR        34   // Switch trye front/right
#define PIN_SW_TY_RL        33   // Switch trye back/left


// Configuration definitions
#define ENC_STEPS            8   // Default encoder sensitivity
#define LED_BRIGHTNESS      12   // Default PWM value for LED brightness 
#define JOYSTICK_MODE     true   // Default operation mode Keyboard
#define BOUNCE_TIME         20   // Bounce delay for buttons
#define CONFIG_ADDRESS       0   // EEPROM address for config data
#define JOY_BTN_DURATION   100   // Delay between button press and release
#define LOOP_DELAY         100   // Delay in main loop
