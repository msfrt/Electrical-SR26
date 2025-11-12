#ifndef FANS_HPP
#define FANS_HPP

#include <PWMControl.h>
#include <StateCAN.h>

#include "CAN/raptor_CAN1.hpp"
#include "CAN/raptor_CAN2.hpp"

extern int fan_signalL;
extern int fan_signalR;
extern int wp_signal;

// **Left Fan Variables**
int fanl_pin = 28; // pwm4 signal
int fanl_min_pwm = 0;
int fanl_max_pwm = 255;
int fanl_ss_dur = 5000; // Soft start duration in milliseconds
int fanl_update_freq = 10;
int fanl_pwm_freq_norm = 40;
int fanl_pwm_freq_ss = 420;

// **Right Fan Variables**
int fanr_pin = 29; // pwm5 signal
int fanr_min_pwm = 0;
int fanr_max_pwm = 255;
int fanr_ss_dur = 5000;
int fanr_update_freq = 10;
int fanr_pwm_freq_norm = 40;
int fanr_pwm_freq_ss = 420;

StateSignal fan_left_row_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal fan_left_col_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal fan_left_override(16, true, 0, 0, 0, 100, 1);

StateSignal fan_right_row_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal fan_right_col_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal fan_right_override(16, true, 0, 0, 0, 100, 1);

// pwm fans
PWMDevice fan_left(fanl_pin, 12, 14, 10, 10000, fan_left_row_signal, fan_left_col_signal, fan_left_override,
                   fanl_min_pwm, fanl_max_pwm, fanl_ss_dur, fanl_update_freq, fanl_pwm_freq_norm, fanl_pwm_freq_ss);

PWMDevice fan_right(fanr_pin, 12, 14, 10, 10000, fan_right_row_signal, fan_right_col_signal, fan_right_override,
                    fanr_min_pwm, fanr_max_pwm, fanr_ss_dur, fanr_update_freq, fanr_pwm_freq_norm, fanr_pwm_freq_ss);

// **Water Pump1 Variables**
int wp1_pin = 14; // ch7pwm
int wp1_min_pwm = 0;
int wp1_max_pwm = 255;
int wp1_ss_dur = 5000;
int wp1_update_freq = 10;
int wp1_pwm_freq_norm = 40;
int wp1_pwm_freq_ss = 420;

// **Water Pump2 Variables**
int wp2_pin = 15; // ch8pwm
int wp2_min_pwm = 0;
int wp2_max_pwm = 255;
int wp2_ss_dur = 5000;
int wp2_update_freq = 10;
int wp2_pwm_freq_norm = 40;
int wp2_pwm_freq_ss = 420;

// **Declare StateSignal for Water Pump1**
StateSignal wp1_row_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal wp1_col_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal wp1_override(16, true, 0, 0, 0, 100, 1);

// **Declare StateSignal for Water Pump2**
StateSignal wp2_row_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal wp2_col_signal(16, true, 0, 0, 0, 1500, 0.1);
StateSignal wp2_override(16, true, 0, 0, 0, 100, 1);

// water pump 1
PWMDevice water_pump1(wp1_pin, 12, 14, 10, 10000, wp1_row_signal, wp1_col_signal, wp1_override,
                     wp1_min_pwm, wp1_max_pwm, wp1_ss_dur, wp1_update_freq, wp1_pwm_freq_norm, wp1_pwm_freq_ss);

// water pump 2
PWMDevice water_pump1(wp2_pin, 12, 14, 10, 10000, wp2_row_signal, wp2_col_signal, wp2_override,
                     wp2_min_pwm, wp2_max_pwm, wp2_ss_dur, wp2_update_freq, wp2_pwm_freq_norm, wp2_pwm_freq_ss);

void updateFanSpeed(int canFanL, int canFanR, int canWp1, int canWp2) {
    fan_signalL = constrain(canFanL, 0, 100); // Ensure valid range (0-100%)
    fan_signalR = constrain(canFanR, 0, 100);
    wp1_signal1 = constrain(canWp1, 0, 100);
    wp1_signal2 = constrain(canWp2, 0, 100);

    // Use override to set PWM directly
    fan_left.set_pwm(0, 0, 2, fan_signalL);
    fan_right.set_pwm(0, 0, 2, fan_signalR);
    water_pump1.set_pwm(0,0,2, wp1_signal);
    water_pump2.set_pwm(0,0,2, wp2_signal);
}

#endif