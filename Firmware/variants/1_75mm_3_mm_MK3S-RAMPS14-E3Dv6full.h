//*******************************//
// Suitable for Prusa MK3S clone //
//*******************************//

#ifndef CONFIGURATION_PRUSA_H
#define CONFIGURATION_PRUSA_H

#include <limits.h>
#include "printers.h"
/*------------------------------------
 GENERAL SETTINGS
 *------------------------------------*/

// Enable to select 2.85mm. 
// If not, 1.75mm settings are used.
// #define FILAMENT_3MM

// Printer revision
#define PRINTER_TYPE PRINTER_MK3S
#define PRINTER_NAME PRINTER_MK3S_NAME
#define PRINTER_MMU_TYPE PRINTER_MK3S_MMU2		// dummy item (due to successfully compilation / building only)
#define PRINTER_MMU_NAME PRINTER_MK3S_MMU2_NAME	// dummy item (due to successfully compilation / building only)

#ifdef FILAMENT_3MM		
	#define FILAMENT_SIZE "2_85mm_MK3S"
#else
	#define FILAMENT_SIZE "1_75mm_MK3S"
#endif
#define NOZZLE_TYPE "E3Dv6full"


#ifdef FILAMENT_3MM
	#define DEFAULT_NOMINAL_FILAMENT_DIA  2.85  //Enter the diameter (in mm) of the filament generally used (3.0 mm or 1.75 mm). Used by the volumetric extrusion.
#else
	#define DEFAULT_NOMINAL_FILAMENT_DIA  1.75  //Enter the diameter (in mm) of the filament generally used (3.0 mm or 1.75 mm). Used by the volumetric extrusion.
#endif

// Printer LCD 
// Choose one: DISCOUNT_SMART_CONTROLLER or GADGETS3D G3D LCD/SD Controller
// The RepRapDiscount Smart Controller (white PCB)
// http://reprap.org/wiki/RepRapDiscount_Smart_Controller
//
// GADGETS3D G3D LCD/SD Controller
// http://reprap.org/wiki/RAMPS_1.3/1.4_GADGETS3D_Shield_with_Panel
//#define G3D_PANEL

//
// RepRapDiscount FULL GRAPHIC Smart Controller
// http://reprap.org/wiki/RepRapDiscount_Full_Graphic_Smart_Controller
//
#define REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER
	
#ifndef G3D_PANEL
  #ifdef REPRAP_DISCOUNT_FULL_GRAPHIC_SMART_CONTROLLER
    #define DOGLCD
    #define U8GLIB_ST7920
	  #define REPRAP_DISCOUNT_SMART_CONTROLLER

    #define ULTIPANEL

    #define ST7920_DELAY_1 DELAY_NS(0) // After CLK LOW
    #define ST7920_DELAY_2 DELAY_NS(400) // After DAT
    #define ST7920_DELAY_3 DELAY_NS(0) // After CLK HIGH
	
  	#define STD_ENCODER_PULSES_PER_STEP 4
  	#define STD_ENCODER_STEPS_PER_MENU_ITEM 1
  #else
    #define REPRAP_DISCOUNT_SMART_CONTROLLER
  #endif
#endif // !G3D_PANEL




// Developer flag
#define DEVELOPER

// Printer name
#define CUSTOM_MENDEL_NAME "Prusa i3 MK3S - By BeSoft"

// Electronics
#define MOTHERBOARD BOARD_RAMPS_14_EFB //BOARD_EINSY_1_0a
//#define TMC2130		//uncomment if having this drivers installed

#if MOTHERBOARD == BOARD_RAMPS_14_EFB
	// New XYZ calibration
	#define NEW_XYZCAL

	#define HEATBED_V2
  #define Y_COMPENSATION_FOR_CALIBRATION // adjust Y-axis movement (ultralcd.cpp), to properly find endstop when doing Z-axis calibration!
	//#define STEEL_SHEET
	//#define TACH0PULLUP

	//#define TEMP_SENSOR_PINDA 1

	// Power panic feature
	//#define UVLO_ENABLE  

	// Watchdog support
	//#define WATCHDOG
	
	// Fan check
	//#define FANCHECK

	// TMC2130 drivers
	//#define TMC2130	
	#ifdef TMC2130
		#undef UVLO_ENABLE	//UVLO uses same Z_MAX_PIN so we have to disable feature to enable drivers!
							// or we need to find another pin for UVLO!
	#endif

	// Filament sensor
	//#define FILAMENT_SENSOR
	#ifdef FILAMENT_SENSOR
		// Option 1:
		//#define PAT9125

		// Option 2:
		//#define IR_SENSOR
	#endif // FILAMENT_SENSOR
#else
	//MK2.5
	// New XYZ calibration
	#define NEW_XYZCAL

	// Fan check
	#define FANCHECK


	// Watchdog support
	#define WATCHDOG

	// Filament sensor
	#define FILAMENT_SENSOR
	#define PAT9125
	#define HEATBED_V2
	#define STEEL_SHEET
	#define TACH0PULLUP
	#define TEMP_SENSOR_PINDA 1
	//#define UVLO_ENABLE
#endif

// Uncomment the below for the E3D PT100 temperature sensor (with or without PT100 Amplifier)
//#define E3D_PT100_EXTRUDER_WITH_AMP
//#define E3D_PT100_EXTRUDER_NO_AMP
//#define E3D_PT100_BED_WITH_AMP
//#define E3D_PT100_BED_NO_AMP


/*------------------------------------
 AXIS SETTINGS
 *------------------------------------*/

//enable if using 1.8 degree motors and GT2-16T pulleys. 
//XYZ calibration may fail if using different settings!
#define STEPS100  

#ifndef STEPS100
	#define CUSTOM_X_STEPS 80 //define X steps
	#define CUSTOM_Y_STEPS 80 //define Y steps
#endif
// Steps per unit {X,Y,Z,E}
#if MOTHERBOARD == BOARD_RAMPS_14_EFB
	#if defined(STEPS100) && defined(FILAMENT_3MM)
		#define DEFAULT_AXIS_STEPS_PER_UNIT   {100,100,3200/8,143} //2.85mm
	#elif defined(FILAMENT_3MM)
		#define DEFAULT_AXIS_STEPS_PER_UNIT   {CUSTOM_X_STEPS,CUSTOM_Y_STEPS,3200/8,143} //2.85mm
	#elif defined(STEPS100)
		#define DEFAULT_AXIS_STEPS_PER_UNIT   {100,100,3200/8,133} //1.75mm
	#else
		#define DEFAULT_AXIS_STEPS_PER_UNIT   {CUSTOM_X_STEPS,CUSTOM_Y_STEPS,3200/8,133} //1.75mm
	#endif // STEPS100
#else
	#define DEFAULT_AXIS_STEPS_PER_UNIT   {100,100,3200/8,133} //1.75mm - Original Prusa
#endif

// Endstop inverting
#if MOTHERBOARD == BOARD_RAMPS_14_EFB
	#define X_MIN_ENDSTOP_INVERTING 1 // set to 1 to invert the logic of the endstop.
	#define Y_MIN_ENDSTOP_INVERTING 1 // set to 1 to invert the logic of the endstop.
	#define Z_MIN_ENDSTOP_INVERTING 1 // set to 1 to invert the logic of the endstop.

  //#define Z_MIN_PROBE_ENDSTOP_INVERTING 1 // set to 1 to invert the logic of the probe.
#else
	#define X_MIN_ENDSTOP_INVERTING 0 // set to 1 to invert the logic of the endstop.
	#define Y_MIN_ENDSTOP_INVERTING 0 // set to 1 to invert the logic of the endstop.
	#define Z_MIN_ENDSTOP_INVERTING 0 // set to 1 to invert the logic of the endstop.
#endif

// Direction inverting
#if MOTHERBOARD == BOARD_RAMPS_14_EFB
	#define INVERT_X_DIR 0    // for Mendel set to 0, for Orca set to 1
	#define INVERT_Y_DIR 0    // for Mendel set to 1, for Orca set to 0
	#define INVERT_Z_DIR 0    // for Mendel set to 0, for Orca set to 1
	#define INVERT_E0_DIR 0    // for direct drive extruder v9 set to 1, for geared extruder set to 0
	#define INVERT_E1_DIR 0    // for direct drive extruder v9 set to 1, for geared extruder set to 0
	#define INVERT_E2_DIR 0    // for direct drive extruder v9 set to 1, for geared extruder set to 0
#else
	#define INVERT_X_DIR 0    // for Mendel set to 0, for Orca set to 1
	#define INVERT_Y_DIR 0    // for Mendel set to 1, for Orca set to 0
	#define INVERT_Z_DIR 0    // for Mendel set to 0, for Orca set to 1
	#define INVERT_E0_DIR 1    // for direct drive extruder v9 set to 1, for geared extruder set to 0
	#define INVERT_E1_DIR 1    // for direct drive extruder v9 set to 1, for geared extruder set to 0
	#define INVERT_E2_DIR 1    // for direct drive extruder v9 set to 1, for geared extruder set to 0
#endif

// Home position
#define MANUAL_X_HOME_POS 0
#define MANUAL_Y_HOME_POS -2.2
#define MANUAL_Z_HOME_POS 0.15

// Travel limits after homing
#if MOTHERBOARD == BOARD_RAMPS_14_EFB
  // The size of the print bed
  #define X_BED_SIZE 200
  #define Y_BED_SIZE 200

	#define X_MAX_POS X_BED_SIZE
	#define X_MIN_POS -16 //0
 
	#define Y_MAX_POS Y_BED_SIZE
	#define Y_MIN_POS 0
 
	#define Z_MAX_POS 190 //212 //* original value = 210, I have a higher Z axis height => check parameter in ultralcd.cpp */
	#define Z_MIN_POS 0 //0.15
#else
	#define X_MAX_POS 250
	#define X_MIN_POS 0
	#define Y_MAX_POS 210
	#define Y_MIN_POS -4
	#define Z_MAX_POS 210
	#define Z_MIN_POS 0.15
#endif


// Canceled home position
#define X_CANCEL_POS 50
#define Y_CANCEL_POS 190

//Pause print position
#define X_PAUSE_POS 50
#define Y_PAUSE_POS 190
#define Z_PAUSE_LIFT 20

#define NUM_AXIS 4 // The axis order in all axis related arrays is X, Y, Z, E
#define HOMING_FEEDRATE {3000, 3000, 800, 0}  // set the homing speeds (mm/min) // 3000 is also valid for stallGuard homing. Valid range: 2200 - 3000

/**
 * [0,0] steel sheet print area point X coordinate in bed print area coordinates
 */
#define SHEET_PRINT_ZERO_REF_X 0.f
/**
 * [0,0] steel sheet print area point Y coordinate in bed print area coordinates
 */
#define SHEET_PRINT_ZERO_REF_Y 0.f

#define DEFAULT_MAX_FEEDRATE          {200, 200, 12, 120}      // (mm/sec)   max feedrate (M203)
#define DEFAULT_MAX_FEEDRATE_SILENT   {172, 172, 12, 120}      // (mm/sec)   max feedrate (M203), silent mode
#define DEFAULT_MAX_ACCELERATION      {1000, 1000, 200, 5000}  // (mm/sec^2) max acceleration (M201)
#define DEFAULT_MAX_ACCELERATION_SILENT     {960, 960, 200, 5000}    // (mm/sec^2) max acceleration (M201), silent mode


#define DEFAULT_ACCELERATION          1250   // X, Y, Z and E max acceleration in mm/s^2 for printing moves (M204S)
#define DEFAULT_RETRACT_ACCELERATION  1250   // X, Y, Z and E max acceleration in mm/s^2 for retracts (M204T)

#define MANUAL_FEEDRATE {2700, 2700, 1000, 100}   // set the speeds for manual moves (mm/min)

//number of bytes from end of the file to start check
#define END_FILE_SECTION 20000

#define Z_AXIS_ALWAYS_ON 1

// Safety timer
#define SAFETYTIMER
#define DEFAULT_SAFETYTIMER_TIME_MINS 30
#define FARM_DEFAULT_SAFETYTIMER_TIME_ms (45*60*1000ul)

#define DEBUG_DCODE3 //D code for EEPROM

//#define DEBUG_BUILD 
#ifdef DEBUG_BUILD
//#define _NO_ASM
#define DEBUG_DCODES //D codes
//#define DEBUG_DCODE5 //D code for flash!
#define DEBUG_STACK_MONITOR        //Stack monitor in stepper ISR
//#define DEBUG_FSENSOR_LOG          //Reports fsensor status to serial
//#define DEBUG_CRASHDET_COUNTERS  //Display crash-detection counters on LCD
//#define DEBUG_RESUME_PRINT       //Resume/save print debug enable
//#define DEBUG_UVLO_AUTOMATIC_RECOVER // Power panic automatic recovery debug output
//#define DEBUG_DISABLE_XMINLIMIT  //x min limit ignored
//#define DEBUG_DISABLE_XMAXLIMIT  //x max limit ignored
//#define DEBUG_DISABLE_YMINLIMIT  //y min limit ignored
//#define DEBUG_DISABLE_YMAXLIMIT  //y max limit ignored
//#define DEBUG_DISABLE_ZMINLIMIT  //z min limit ignored
//#define DEBUG_DISABLE_ZMAXLIMIT  //z max limit ignored
#define DEBUG_DISABLE_STARTMSGS //no startup messages
//#define DEBUG_DISABLE_MINTEMP   //mintemp error ignored
//#define DEBUG_DISABLE_SWLIMITS  //sw limits ignored
//#define DEBUG_DISABLE_LCD_STATUS_LINE  //empty four lcd line
//#define DEBUG_DISABLE_PREVENT_EXTRUDER //cold extrusion and long extrusion allowed
//#define DEBUG_DISABLE_PRUSA_STATISTICS //disable prusa_statistics() mesages
//#define DEBUG_XSTEP_DUP_PIN 21   //duplicate x-step output to pin 21 (SCL on P3)
//#define DEBUG_YSTEP_DUP_PIN 21   //duplicate y-step output to pin 21 (SCL on P3)
#define DEBUG_DISABLE_FANCHECK     //disable fan check (no ISR INT7, check disabled)
//#define DEBUG_DUMP_TO_2ND_SERIAL   //dump received characters to 2nd serial line
//#define DEBUG_STEPPER_TIMER_MISSED // Stop on stepper timer overflow, beep and display a message.
//#define PLANNER_DIAGNOSTICS // Show the planner queue status on printer display.
//#define CMD_DIAGNOSTICS //Show cmd queue length on printer display
#endif /* DEBUG_BUILD */

//#define FSENSOR_QUALITY


/*------------------------------------
 EXTRUDER SETTINGS
 *------------------------------------*/

// Mintemps
#define HEATER_0_MINTEMP 15 //30
#define HEATER_1_MINTEMP 5
#define HEATER_2_MINTEMP 5
#define HEATER_MINTEMP_DELAY 15000                // [ms] ! if changed, check maximal allowed value @ ShortTimer
#if HEATER_MINTEMP_DELAY>USHRT_MAX
#error "Check maximal allowed value @ ShortTimer (see HEATER_MINTEMP_DELAY definition)"
#endif
#define BED_MINTEMP 15 //30
#define BED_MINTEMP_DELAY 50000                   // [ms] ! if changed, check maximal allowed value @ ShortTimer
#if BED_MINTEMP_DELAY>USHRT_MAX
#error "Check maximal allowed value @ ShortTimer (see BED_MINTEMP_DELAY definition)"
#endif

// Maxtemps
#if defined(E3D_PT100_EXTRUDER_WITH_AMP) || defined(E3D_PT100_EXTRUDER_NO_AMP)
#define HEATER_0_MAXTEMP 410
#else
#define HEATER_0_MAXTEMP 250
#endif
#define HEATER_1_MAXTEMP 250
#define HEATER_2_MAXTEMP 250
#define BED_MAXTEMP 120

#if defined(E3D_PT100_EXTRUDER_WITH_AMP) || defined(E3D_PT100_EXTRUDER_NO_AMP)
// Define PID constants for extruder with PT100
#define  DEFAULT_Kp 21.70
#define  DEFAULT_Ki 1.60
#define  DEFAULT_Kd 73.76
#else
// Define PID constants for extruder
#define DEFAULT_Kp 39.55  //#define  DEFAULT_Kp 20  //40    //20
#define DEFAULT_Ki 4.09   //#define  DEFAULT_Ki 0.4 //0.7   //0.4
#define DEFAULT_Kd 95.57  //#define  DEFAULT_Kd 80  //160   //50
// #define  DEFAULT_Kp 16.13 // Original Prusa
// #define  DEFAULT_Ki 1.1625// Original Prusa
// #define  DEFAULT_Kd 56.23 // Original Prusa
#endif

// Extrude mintemp
#define EXTRUDE_MINTEMP 175

// Extruder cooling fans
#define EXTRUDER_0_AUTO_FAN_PIN   8
#define EXTRUDER_1_AUTO_FAN_PIN   -1
#define EXTRUDER_2_AUTO_FAN_PIN   -1
#define EXTRUDER_AUTO_FAN_TEMPERATURE 50
#define EXTRUDER_AUTO_FAN_SPEED   255  // == full speed


/*------------------------------------
 LOAD/UNLOAD FILAMENT SETTINGS
 *------------------------------------*/

// Load filament commands
#ifdef FILAMENT_3MM
//For 2.85mm filaments
#define LOAD_FILAMENT_0 "M83"
#define LOAD_FILAMENT_1 "G1 E70 F245"
#define LOAD_FILAMENT_2 "G1 E40 F65"
#else
//For 1.75mm filaments
#define LOAD_FILAMENT_0 "M83"
#define LOAD_FILAMENT_1 "G1 E70 F400"
#define LOAD_FILAMENT_2 "G1 E40 F100"
#endif // FILAMENT_3MM


// Unload filament commands
#define UNLOAD_FILAMENT_0 "M83"
#define UNLOAD_FILAMENT_1 "G1 E-90 F7000" //"G1 E-80 F7000"

/*------------------------------------
 CHANGE FILAMENT SETTINGS
 *------------------------------------*/

// Filament change configuration
#define FILAMENTCHANGEENABLE
#ifdef FILAMENTCHANGEENABLE
#define FILAMENTCHANGE_XPOS 211
#define FILAMENTCHANGE_YPOS 0
#define FILAMENTCHANGE_ZADD 2
#define FILAMENTCHANGE_FIRSTRETRACT -2
#define FILAMENTCHANGE_FINALRETRACT -80

#define FILAMENTCHANGE_FIRSTFEED 70 //E distance in mm for fast filament loading sequence used used in filament change (M600)
#define FILAMENTCHANGE_FINALFEED 25 //E distance in mm for slow filament loading sequence used used in filament change (M600) and filament load (M701)
#define FILAMENTCHANGE_RECFEED 5

#define FILAMENTCHANGE_XYFEED 50
#define FILAMENTCHANGE_EFEED_FIRST 20 // feedrate in mm/s for fast filament loading sequence used in filament change (M600)
#define FILAMENTCHANGE_EFEED_FINAL 3.3f // feedrate in mm/s for slow filament loading sequence used in filament change (M600) and filament load (M701)
//#define FILAMENTCHANGE_RFEED 400
#define FILAMENTCHANGE_RFEED 7000 / 60
#define FILAMENTCHANGE_EXFEED 2
#define FILAMENTCHANGE_ZFEED 15

#endif

/*------------------------------------
 ADDITIONAL FEATURES SETTINGS
 *------------------------------------*/

// Define Prusa filament runout sensor
//#define FILAMENT_RUNOUT_SUPPORT

#ifdef FILAMENT_RUNOUT_SUPPORT
	#define FILAMENT_RUNOUT_SENSOR 1
#endif

// temperature runaway
#define TEMP_RUNAWAY_BED_HYSTERESIS 5
#define TEMP_RUNAWAY_BED_TIMEOUT 360

#define TEMP_RUNAWAY_EXTRUDER_HYSTERESIS 15
#define TEMP_RUNAWAY_EXTRUDER_TIMEOUT 45

/*------------------------------------
 MOTOR CURRENT SETTINGS
 *------------------------------------*/

// Motor Current setting for BIG RAMBo
#define DIGIPOT_MOTOR_CURRENT {135,135,135,135,135} // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
#define DIGIPOT_MOTOR_CURRENT_LOUD {135,135,135,135,135}

#if MOTHERBOARD == BOARD_RAMPS_14_EFB // It doesn't matter for A9800 drivers
#define MOTOR_CURRENT_PWM_RANGE 2000
#define DEFAULT_PWM_MOTOR_CURRENT  {270, 830, 450} // {XY,Z,E}
#define DEFAULT_PWM_MOTOR_CURRENT_LOUD  {540, 830, 500} // {XY,Z,E}
#define Z_SILENT 0
#define Z_HIGH_POWER 200
#endif

// Motor Current settings for RAMBo mini PWM value = MotorCurrentSetting * 255 / range
#if MOTHERBOARD == BOARD_RAMBO_MINI_1_0 || MOTHERBOARD == BOARD_RAMBO_MINI_1_3
#define MOTOR_CURRENT_PWM_RANGE 2000
#define DEFAULT_PWM_MOTOR_CURRENT  {270, 830, 450} // {XY,Z,E}
#define DEFAULT_PWM_MOTOR_CURRENT_LOUD  {540, 830, 500} // {XY,Z,E}
#define Z_SILENT 0
#define Z_HIGH_POWER 200
#endif

/*------------------------------------
 BED SETTINGS
 *------------------------------------*/

// Define Mesh Bed Leveling system to enable it
#define MESH_BED_LEVELING
#ifdef MESH_BED_LEVELING

#define MBL_Z_STEP 0.01

// Mesh definitions
#if MOTHERBOARD == BOARD_RAMPS_14_EFB
#define MESH_MIN_X 35
#define MESH_MAX_X 239  //238
#define MESH_MIN_Y 8 //6
#define MESH_MAX_Y 202
#else
#define MESH_MIN_X 24
#define MESH_MAX_X 228
#define MESH_MIN_Y 6
#define MESH_MAX_Y 210
#endif

// Mesh upsample definition
#define MESH_NUM_X_POINTS 7
#define MESH_NUM_Y_POINTS 7
// Mesh measure definition
#define MESH_MEAS_NUM_X_POINTS 3
#define MESH_MEAS_NUM_Y_POINTS 3

// Maximum bed level correction value
#define BED_ADJUSTMENT_UM_MAX 100

#define MESH_HOME_Z_CALIB 0.2
#define MESH_HOME_Z_SEARCH 5.0f //Z lift for homing, mesh bed leveling etc.

#if MOTHERBOARD == BOARD_RAMPS_14_EFB  //CHECK BEFORE COMPILING!
	//for Prusa Bear upgrade:
	#define X_PROBE_OFFSET_FROM_EXTRUDER 25 //23    // Z probe to nozzle X offset: -left  +right
	#define Y_PROBE_OFFSET_FROM_EXTRUDER 8 //5 //4     // Z probe to nozzle Y offset: -front +behind
	#define Z_PROBE_OFFSET_FROM_EXTRUDER -0.4  // Z probe to nozzle Z offset: -below (always!)
#else
	#define X_PROBE_OFFSET_FROM_EXTRUDER 23     // Z probe to nozzle X offset: -left  +right
	#define Y_PROBE_OFFSET_FROM_EXTRUDER 5     // Z probe to nozzle Y offset: -front +behind
	#define Z_PROBE_OFFSET_FROM_EXTRUDER -0.4  // Z probe to nozzle Z offset: -below (always!)
#endif

#endif

// Bed Temperature Control
// Select PID or bang-bang with PIDTEMPBED. If bang-bang, BED_LIMIT_SWITCHING will enable hysteresis
//
// Uncomment this to enable PID on the bed. It uses the same frequency PWM as the extruder.
// If your PID_dT above is the default, and correct for your hardware/configuration, that means 7.689Hz,
// which is fine for driving a square wave into a resistive load and does not significantly impact you FET heating.
// This also works fine on a Fotek SSR-10DA Solid State Relay into a 250W heater.
// If your configuration is significantly different than this and you don't understand the issues involved, you probably
// shouldn't use bed PID until someone else verifies your hardware works.
// If this is enabled, find your own PID constants below.
#define PIDTEMPBED
//
//#define BED_LIMIT_SWITCHING

// This sets the max power delivered to the bed, and replaces the HEATER_BED_DUTY_CYCLE_DIVIDER option.
// all forms of bed control obey this (PID, bang-bang, bang-bang with hysteresis)
// setting this to anything other than 255 enables a form of PWM to the bed just like HEATER_BED_DUTY_CYCLE_DIVIDER did,
// so you shouldn't use it unless you are OK with PWM on your bed.  (see the comment on enabling PIDTEMPBED)
#define MAX_BED_POWER 255 // limits duty cycle to bed; 255=full current

// Bed temperature compensation settings
#define BED_OFFSET 10
#define BED_OFFSET_START 40
#define BED_OFFSET_CENTER 50


#ifdef PIDTEMPBED
//120v 250W silicone heater into 4mm borosilicate (MendelMax 1.5+)
//from FOPDT model - kp=.39 Tp=405 Tdead=66, Tc set to 79.2, aggressive factor of .15 (vs .1, 1, 10)
#if defined(E3D_PT100_BED_WITH_AMP) || defined(E3D_PT100_BED_NO_AMP)
// Define PID constants for extruder with PT100
#define  DEFAULT_bedKp 21.70
#define  DEFAULT_bedKi 1.60
#define  DEFAULT_bedKd 73.76
#else
#if MOTHERBOARD == BOARD_RAMPS_14_EFB
#define DEFAULT_bedKp 134.08 //#define  DEFAULT_bedKp 55       //97.51
#define DEFAULT_bedKi 25.18  //#define  DEFAULT_bedKi 0.5      //4.66
#define DEFAULT_bedKd 178.48 //#define  DEFAULT_bedKd 250      //510.14
//#define  DEFAULT_bedKp 109.69
//#define  DEFAULT_bedKi 4.87
//#define  DEFAULT_bedKd 617.80
#else
#define  DEFAULT_bedKp 126.13
#define  DEFAULT_bedKi 4.30
#define  DEFAULT_bedKd 924.76
#endif
#endif

//120v 250W silicone heater into 4mm borosilicate (MendelMax 1.5+)
//from pidautotune
//    #define  DEFAULT_bedKp 97.1
//    #define  DEFAULT_bedKi 1.41
//    #define  DEFAULT_bedKd 1675.16

// FIND YOUR OWN: "M303 E-1 C8 S90" to run autotune on the bed at 90 degreesC for 8 cycles.
#endif // PIDTEMPBED


/*-----------------------------------
 PREHEAT SETTINGS
 *------------------------------------*/

#define FARM_PREHEAT_HOTEND_TEMP 210
#define FARM_PREHEAT_HPB_TEMP 80
#define FARM_PREHEAT_FAN_SPEED 0

#define PREHEAT_HOTEND_TEMP 250
#define PREHEAT_HPB_TEMP 60

#define PLA_PREHEAT_HOTEND_TEMP 215
#define PLA_PREHEAT_HPB_TEMP 60

#define ASA_PREHEAT_HOTEND_TEMP 260
#define ASA_PREHEAT_HPB_TEMP 105

#define ABS_PREHEAT_HOTEND_TEMP 255
#define ABS_PREHEAT_HPB_TEMP 100

#define HIPS_PREHEAT_HOTEND_TEMP 220
#define HIPS_PREHEAT_HPB_TEMP 100

#define PP_PREHEAT_HOTEND_TEMP 254
#define PP_PREHEAT_HPB_TEMP 100

#define PC_PREHEAT_HOTEND_TEMP 254
#define PC_PREHEAT_HPB_TEMP 100

#define PET_PREHEAT_HOTEND_TEMP 230
#define PET_PREHEAT_HPB_TEMP 85

#define FLEX_PREHEAT_HOTEND_TEMP 240
#define FLEX_PREHEAT_HPB_TEMP 50

/*------------------------------------
 THERMISTORS SETTINGS
 *------------------------------------*/

//
//--NORMAL IS 4.7kohm PULLUP!-- 1kohm pullup can be used on hotend sensor, using correct resistor and table
//
//// Temperature sensor settings:
// -2 is thermocouple with MAX6675 (only for sensor 0)
// -1 is thermocouple with AD595
// 0 is not used
// 1 is 100k thermistor - best choice for EPCOS 100k (4.7k pullup)
// 2 is 200k thermistor - ATC Semitec 204GT-2 (4.7k pullup)
// 3 is Mendel-parts thermistor (4.7k pullup)
// 4 is 10k thermistor !! do not use it for a hotend. It gives bad resolution at high temp. !!
// 5 is 100K thermistor - ATC Semitec 104GT-2 (Used in ParCan & J-Head) (4.7k pullup)
// 6 is 100k EPCOS - Not as accurate as table 1 (created using a fluke thermocouple) (4.7k pullup)
// 7 is 100k Honeywell thermistor 135-104LAG-J01 (4.7k pullup)
// 71 is 100k Honeywell thermistor 135-104LAF-J01 (4.7k pullup)
// 8 is 100k 0603 SMD Vishay NTCS0603E3104FXT (4.7k pullup)
// 9 is 100k GE Sensing AL03006-58.2K-97-G1 (4.7k pullup)
// 10 is 100k RS thermistor 198-961 (4.7k pullup)
// 11 is 100k beta 3950 1% thermistor (4.7k pullup)
// 12 is 100k 0603 SMD Vishay NTCS0603E3104FXT (4.7k pullup) (calibrated for Makibox hot bed)
// 13 is 100k Hisens 3950  1% up to 300??C for hotend "Simple ONE " & "Hotend "All In ONE"
// 20 is the PT100 circuit found in the Ultimainboard V2.x
// 60 is 100k Maker's Tool Works Kapton Bed Thermistor beta=3950
//
//    1k ohm pullup tables - This is not normal, you would have to have changed out your 4.7k for 1k
//                          (but gives greater accuracy and more stable PID)
// 51 is 100k thermistor - EPCOS (1k pullup)
// 52 is 200k thermistor - ATC Semitec 204GT-2 (1k pullup)
// 55 is 100k thermistor - ATC Semitec 104GT-2 (Used in ParCan & J-Head) (1k pullup)
//
// 1047 is Pt1000 with 4k7 pullup
// 1010 is Pt1000 with 1k pullup (non standard)
// 147 is Pt100 with 4k7 pullup
// 148 is E3D Pt100 with 4k7 pullup and no PT100 Amplifier on a MiniRambo 1.3a
// 247 is Pt100 with 4k7 pullup and PT100 Amplifier
// 110 is Pt100 with 1k pullup (non standard)

#if defined(E3D_PT100_EXTRUDER_WITH_AMP)
  #define TEMP_SENSOR_0 247
#elif defined(E3D_PT100_EXTRUDER_NO_AMP)
  #define TEMP_SENSOR_0 148
#else
  #define TEMP_SENSOR_0 1 //5 for Original Prusa
#endif
#define TEMP_SENSOR_1 0
#define TEMP_SENSOR_2 0

#if defined(E3D_PT100_BED_WITH_AMP)
  #define TEMP_SENSOR_BED 247
#elif defined(E3D_PT100_BED_NO_AMP)
  #define TEMP_SENSOR_BED 148
#else
  #define TEMP_SENSOR_BED 1
#endif

#define STACK_GUARD_TEST_VALUE 0xA2A2

#define MAX_BED_TEMP_CALIBRATION 50
#define MAX_HOTEND_TEMP_CALIBRATION 50

#define MAX_E_STEPS_PER_UNIT 250
#define MIN_E_STEPS_PER_UNIT 100

#define Z_BABYSTEP_MIN -3999
#define Z_BABYSTEP_MAX 0

#define PINDA_PREHEAT_X 20
#define PINDA_PREHEAT_Y 60
#define PINDA_PREHEAT_Z 0.15
/*
#define PINDA_PREHEAT_X 70
#define PINDA_PREHEAT_Y -3
#define PINDA_PREHEAT_Z 1*/
#define PINDA_HEAT_T 120 //time in s

#define PINDA_MIN_T 50
#define PINDA_STEP_T 10
#define PINDA_MAX_T 100

#define PING_TIME 60 //time in s
#define PING_TIME_LONG 600 //10 min; used when length of commands buffer > 0 to avoid 0 triggering when dealing with long gcodes
#define PING_ALLERT_PERIOD 60 //time in s

#define NC_TIME 10 //time in s for periodic important status messages sending which needs reponse from monitoring
#define NC_BUTTON_LONG_PRESS 15 //time in s

#define LONG_PRESS_TIME 1000 //time in ms for button long press
#define BUTTON_BLANKING_TIME 200 //time in ms for blanking after button release

#define DEFAULT_PID_TEMP 210

#define MIN_PRINT_FAN_SPEED 75


// How much shall the print head be lifted on power panic?
// Ideally the Z axis will reach a zero phase of the stepper driver on power outage. To simplify this,
// UVLO_Z_AXIS_SHIFT shall be an integer multiply of the stepper driver cycle, that is 4x full step.
// For example, the Prusa i3 MK2 with 16 microsteps per full step has Z stepping of 400 microsteps per mm.
// At 400 microsteps per mm, a full step lifts the Z axis by 0.04mm, and a stepper driver cycle is 0.16mm.
// The following example, 12 * (4 * 16 / 400) = 12 * 0.16mm = 1.92mm.
//#define UVLO_Z_AXIS_SHIFT 1.92
#define UVLO_Z_AXIS_SHIFT 0 //0.64
// When powered off during PP recovery, the Z axis position can still be re-adjusted. In this case
// we just need to shift to the nearest fullstep, but we need a move which is at least
// "dropsegments" steps long. All the above rules still need to apply.
#define UVLO_TINY_Z_AXIS_SHIFT 0 //0.16
// If power panic occured, and the current temperature is higher then target temperature before interrupt minus this offset, print will be recovered automatically. 
#define AUTOMATIC_UVLO_BED_TEMP_OFFSET 5

#define M600_TIMEOUT 600  //seconds

//#define SUPPORT_VERBOSITY

#define MMU_REQUIRED_FW_BUILDNR 132
#define MMU_FORCE_STEALTH_MODE
#define MMU_DEBUG //print communication between MMU2 and printer on serial
//#define MMU_HAS_CUTTER

#define MMU_IDLER_SENSOR_ATTEMPTS_NR 21 //max. number of attempts to load filament if first load failed; value for max bowden length and case when loading fails right at the beginning

//#define HEATBED_ANALYSIS //for meash bed leveling and heatbed analysis D-codes D80 and D81
//#define MICROMETER_LOGGING //related to D-codes D80 and D81, currently works on MK2.5 only (MK3 board pin definitions missing)

#endif //__CONFIGURATION_PRUSA_H
