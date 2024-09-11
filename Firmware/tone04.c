//tone04.c
// use atmega timer4 as main tone timer instead of timer2
// timer2 is used for System timer.

#include "system_timer.h"
#include "Configuration_var.h"

#ifdef SYSTEM_TIMER_2

#include "pins.h"
#include "fastio.h"
#include "macros.h"

void timer4_init(void)
{
	CRITICAL_SECTION_START;

	SET_OUTPUT(BEEPER);
	WRITE(BEEPER, LOW);

	SET_OUTPUT(EXTRUDER_0_AUTO_FAN_PIN);

	// Set timer mode 9 (PWM,Phase and Frequency Correct)
	// Prescaler is CLK/1024
	// Output compare is disabled on all timer pins
	// Input capture is disabled
	// All interrupts are disabled
	TCCR4A = _BV(WGM40);
	TCCR4B = _BV(WGM43) | _BV(CS42) | _BV(CS40);
	OCR4A = 255U;
	OCR4B = 255U;
	OCR4C = 255U;
	TIMSK4 = 0;

	CRITICAL_SECTION_END;
}

#ifdef EXTRUDER_0_AUTO_FAN_PIN
void timer4_set_fan0(uint8_t duty)
{
	if (duty == 0 || duty == 255)
	{
		// We use digital logic if the duty cycle is 0% or 100%
		/*RAMPS*/
		#if 0 && (MOTHERBOARD == BOARD_RAMPS_14_EFB || MOTHERBOARD == BOARD_MKS_GEN_L_21)
		TCCR4A &= ~_BV(COM4B1);
		OCR4B = 0;
		#else
		TCCR4A &= ~_BV(COM4C1);
		OCR4C = 0;
		#endif
		/*RAMPS*/
		WRITE(EXTRUDER_0_AUTO_FAN_PIN, duty);
	}
	else
	{
		// Use the timer for fan speed. Enable the timer compare output and set the duty cycle.
		// This function also handles the impossible scenario of a fan speed change during a Tone.
		// Better be safe than sorry.
		CRITICAL_SECTION_START;
		// Enable the PWM output on the fan pin.
		/*RAMPS*/
		#if 0 && (MOTHERBOARD == BOARD_RAMPS_14_EFB || MOTHERBOARD == BOARD_MKS_GEN_L_21)
		TCCR4A |= _BV(COM4B1);
		OCR4B = (((uint16_t)duty) * ((uint16_t)((TIMSK4 & _BV(OCIE4A)) ? OCR4A : 255U))) / 255U;
		#else
		TCCR4A |= _BV(COM4C1);
		OCR4C = (((uint16_t)duty) * ((uint16_t)((TIMSK4 & _BV(OCIE4A)) ? OCR4A : 255U))) / 255U;
		#endif
		/*RAMPS*/
		CRITICAL_SECTION_END;
	}
}
#endif //EXTRUDER_0_AUTO_FAN_PIN

// Because of the timer mode change, we need two interrupts. We could also try to assume that the frequency is x2
// and use a TOGGLE(), but this seems to work well enough so I left it as it is now.
ISR(TIMER4_COMPA_vect)
{
	WRITE(BEEPER, 1);
}

ISR(TIMER4_OVF_vect)
{
	WRITE(BEEPER, 0);
}

void tone4(_UNUSED uint8_t _pin, uint16_t frequency)
{
	//this ocr and prescalarbits calculation is taken from the Arduino core and simplified for one type of timer only
	uint8_t prescalarbits = 0b001;
	uint32_t pwm_freq = F_CPU / (2 * frequency);

	if (pwm_freq > UINT16_MAX) {
		pwm_freq /= 64; // Increase prescaler to 64
		prescalarbits = 0b011;
	}

	uint16_t ocr = pwm_freq - 1;

	CRITICAL_SECTION_START;
	// Set calcualted prescaler
	TCCR4B = (TCCR4B & 0b11111000) | prescalarbits;
#ifdef EXTRUDER_0_AUTO_FAN_PIN
	// Scale the fan PWM duty cycle so that it remains constant, but at the tone frequency
	/*RAMPS*/
	#if 0 && (MOTHERBOARD == BOARD_RAMPS_14_EFB || MOTHERBOARD == BOARD_MKS_GEN_L_21)
	OCR4B = (OCR4B * ocr) / (uint16_t)((TIMSK4 & _BV(OCIE4A)) ? OCR4A : 255U);
	#else
	OCR4C = (OCR4C * ocr) / (uint16_t)((TIMSK4 & _BV(OCIE4A)) ? OCR4A : 255U);
	#endif
	/*RAMPS*/
#endif //EXTRUDER_0_AUTO_FAN_PIN
	// Set calcualted ocr
	OCR4A = ocr;
	// Enable Output compare A interrupt and timer overflow interrupt
	TIMSK4 |= _BV(OCIE4A) | _BV(TOIE4);
	CRITICAL_SECTION_END;
}

void noTone4(_UNUSED uint8_t _pin)
{
	CRITICAL_SECTION_START;
	// Revert prescaler to CLK/1024
	TCCR4B = (TCCR4B & 0b11111000) | _BV(CS42) | _BV(CS40);
#ifdef EXTRUDER_0_AUTO_FAN_PIN
	// Scale the fan OCR back to the original value.
	/*RAMPS*/
	#if 0 && (MOTHERBOARD == BOARD_RAMPS_14_EFB || MOTHERBOARD == BOARD_MKS_GEN_L_21)
	OCR4B = (OCR4B * 255U) / (uint16_t)((TIMSK4 & _BV(OCIE4A)) ? OCR4A : 255U);
	#else
	OCR4C = (OCR4C * 255U) / (uint16_t)((TIMSK4 & _BV(OCIE4A)) ? OCR4A : 255U);
	#endif
	/*RAMPS*/
#endif //EXTRUDER_0_AUTO_FAN_PIN
	OCR4A = 255U;
	// Disable Output compare A interrupt and timer overflow interrupt
	TIMSK4 &= ~(_BV(OCIE4A) | _BV(TOIE4));
	CRITICAL_SECTION_END;
	// Turn beeper off if it was on when noTone was called
	WRITE(BEEPER, 0);
}


#endif //SYSTEM_TIMER_2
