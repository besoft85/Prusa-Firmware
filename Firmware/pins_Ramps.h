/*****************************************************************
* Arduino RAMPS 1.3/1.4 Pin Assignments
******************************************************************/

#define ELECTRONICS "RAMPS_14EFB"

#define KNOWN_BOARD
#ifndef __AVR_ATmega2560__
  #error Oops!  Make sure you have 'Arduino Mega 2560' selected from the 'Tools -> Boards' menu.
#endif

//#define UVLO_SUPPORT
//#define PINDA_THERMISTOR
//#define SWI2C_SDA      20 //SDA (already defined in pins.h)
//#define SWI2C_SCL      21 //SCL (already defined in pins.h)

// RAMPS pinout
#ifdef TMC2130
#define X_TMC2130_CS	44 //53
#define X_TMC2130_DIAG	X_MAX_PIN //-1 // NO DIAG OUTPUTS
#endif
#define X_STEP_PIN		54
#define X_DIR_PIN		55
#define X_ENABLE_PIN    38

#define X_MIN_PIN		3
#define X_MAX_PIN		2
#define X_MS1_PIN		-1
#define X_MS2_PIN		-1

#ifdef TMC2130
#define Y_TMC2130_CS	64 //49
#define Y_TMC2130_DIAG	Y_MAX_PIN //-1 // NO DIAG OUTPUTS
#endif
#define Y_STEP_PIN		60
#define Y_DIR_PIN		61
#define Y_ENABLE_PIN    56

#define Y_MIN_PIN		14
#define Y_MAX_PIN		15
#define Y_MS1_PIN		-1
#define Y_MS2_PIN		-1

#ifdef TMC2130
#define Z_TMC2130_CS	40
#define Z_TMC2130_DIAG	Z_MAX_PIN //-1 // NO DIAG OUTPUTS
#endif
#define Z_STEP_PIN		46
#define Z_DIR_PIN		48
#define Z_ENABLE_PIN    62
#define Z_MIN_PIN		18
#ifdef UVLO_SUPPORT
    #define Z_MAX_PIN	-1
#else
    #define Z_MAX_PIN	19
#endif // UVLO_SUPPORT
#define Z_MS1_PIN		-1
#define Z_MS2_PIN		-1

#ifdef TMC2130
#define E0_TMC2130_CS	42
#define E0_TMC2130_DIAG	65 //Z_MIN_PROBE_PIN // -1 // NO DIAG OUTPUTS
#endif
#define E0_STEP_PIN         26
#define E0_DIR_PIN          28
#define E0_ENABLE_PIN       24
#define E0_MS1_PIN          -1
#define E0_MS2_PIN          -1

#define HEATER_BED_PIN		 8  //PH5
/*Array index for adc_samples[], not pin number */
#define TEMP_BED_PIN		  14  //A14 (not equal to digital Y_MIN_PIN!)

#define HEATER_0_PIN		  10  //PB4
/*Array index for adc_samples[], not pin number */
#define TEMP_0_PIN			  13 //A13 (not equal to digital LED_PIN!)

#define HEATER_1_PIN        -1
#ifdef PINDA_THERMISTOR
	#define TEMP_1_PIN       15 //A15 (not equal to digital Y_MAX_PIN!)
#else
	#define TEMP_1_PIN      -1
#endif //PINDA_THERMISTOR

#define HEATER_2_PIN        -1
#define TEMP_2_PIN          -1

/*test*/
//#define TEMP_AMBIENT_PIN	-1
//#define TEMP_PINDA_PIN    -1

//#define MOTOR_CURRENT_PWM_XY_PIN -1
//#define MOTOR_CURRENT_PWM_Z_PIN  -1
//#define MOTOR_CURRENT_PWM_E_PIN  -1

#define IR_SENSOR_PIN 		5 //IR sensor on RAMPS pin D5 of servo motors pins

#define FAN_PIN         	9
#define LED_PIN         	13
#define FAN_1_PIN       	-1

#define SDSS                53
#define TACH_0				-1	//32	// noctua extruder fan
#define KILL_PIN            41  //
#define SUICIDE_PIN     	-1  // PIN that has to be turned on right after start, to keep power flowing.
#define PS_ON_PIN           -1	//12

#define SDPOWER             -1
#define SDCARDDETECT        49
#define BEEPER              37  // Beeper

//buttons are directly attached using AUX-2
#define BTN_EN1             31
#define BTN_EN2             33
#define BTN_ENC             35  // the click

//
// LCD Display output pins
//
#define LCD_PINS_RS         16
#define LCD_PINS_ENABLE     17
#define LCD_PINS_D4         23
#define LCD_PINS_D5         25
#define LCD_PINS_D6         27
#define LCD_PINS_D7         29

