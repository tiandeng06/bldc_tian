/*
	Copyright 2016 Benjamin Vedder	benjamin@vedder.se

	This file is part of the VESC firmware.

	The VESC firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The VESC firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    */

#ifndef MC_INTERFACE_H_
#define MC_INTERFACE_H_

#include "conf_general.h"
#include "hw.h"
#include "datatypes.h"

// Functions
void mc_interface_init(void);
int mc_interface_motor_now(void);
void mc_interface_select_motor_thread(int motor);
int mc_interface_get_motor_thread(void);
const volatile mc_configuration* mc_interface_get_configuration(void);
void mc_interface_set_configuration(mc_configuration *configuration);
unsigned mc_interface_calc_crc(mc_configuration* conf, bool is_motor_2);
bool mc_interface_dccal_done(void);
void mc_interface_set_pwm_callback(void (*p_func)(void));
void mc_interface_lock(void);
void mc_interface_unlock(void);
void mc_interface_lock_override_once(void);
mc_fault_code mc_interface_get_fault(void);
const char* mc_interface_fault_to_string(mc_fault_code fault);
mc_state mc_interface_get_state(void);
mc_control_mode mc_interface_get_control_mode(void);
void mc_interface_set_duty(float dutyCycle);
void mc_interface_set_duty_noramp(float dutyCycle);
void mc_interface_set_pid_speed(float rpm);
void mc_interface_set_pid_pos(float pos);
void mc_interface_set_current(float current);
void mc_interface_set_brake_current(float current);
void mc_interface_set_current_rel(float val);
void mc_interface_set_brake_current_rel(float val);
void mc_interface_set_handbrake(float current);
void mc_interface_set_handbrake_rel(float val);
void mc_interface_set_openloop_current(float current, float rpm);
void mc_interface_set_openloop_phase(float current, float phase);
void mc_interface_set_openloop_duty(float dutyCycle, float rpm);
void mc_interface_set_openloop_duty_phase(float dutyCycle, float phase);
int mc_interface_set_tachometer_value(int steps);
void mc_interface_brake_now(void);
void mc_interface_release_motor(void);
void mc_interface_release_motor_override(void);
bool mc_interface_wait_for_motor_release(float timeout);
float mc_interface_get_duty_cycle_set(void);
float mc_interface_get_duty_cycle_now(void);
float mc_interface_get_sampling_frequency_now(void);
float mc_interface_get_rpm(void);
float mc_interface_get_amp_hours(bool reset);
float mc_interface_get_amp_hours_charged(bool reset);
float mc_interface_get_watt_hours(bool reset);
float mc_interface_get_watt_hours_charged(bool reset);
float mc_interface_get_tot_current(void);
float mc_interface_get_tot_current_filtered(void);
float mc_interface_get_tot_current_directional(void);
float mc_interface_get_tot_current_directional_filtered(void);
float mc_interface_get_tot_current_in(void);
float mc_interface_get_tot_current_in_filtered(void);
float mc_interface_get_input_voltage_filtered(void);
int mc_interface_get_tachometer_value(bool reset);
int mc_interface_get_tachometer_abs_value(bool reset);
float mc_interface_get_last_inj_adc_isr_duration(void);
float mc_interface_read_reset_avg_motor_current(void);
float mc_interface_read_reset_avg_input_current(void);
float mc_interface_read_reset_avg_id(void);
float mc_interface_read_reset_avg_iq(void);
float mc_interface_read_reset_avg_vd(void);
float mc_interface_read_reset_avg_vq(void);
float mc_interface_get_pid_pos_set(void);
float mc_interface_get_pid_pos_now(void);
void mc_interface_update_pid_pos_offset(float angle_now, bool store);
float mc_interface_get_last_sample_adc_isr_duration(void);
void mc_interface_sample_print_data(debug_sampling_mode mode, uint16_t len, uint8_t decimation, bool raw, 
		void(*reply_func)(unsigned char *data, unsigned int len));
float mc_interface_temp_fet_filtered(void);
float mc_interface_temp_motor_filtered(void);
float mc_interface_get_battery_level(float *wh_left);
float mc_interface_get_speed(void);
float mc_interface_get_distance(void);
float mc_interface_get_distance_abs(void);
void mc_interface_override_wheel_speed(bool ovr, float speed);

setup_values mc_interface_get_setup_values(void);
volatile gnss_data *mc_interface_gnss(void);

float modify_duty(float dutyCycle); // SeaDrive modify duty function
float modify_duty_with_limits(float dutyCycle); // SeaDrive modify duty function with limits
float modify_duty_with_fixed_time(float dutyCycle);

// odometer
uint64_t mc_interface_get_odometer(void);
void mc_interface_set_odometer(uint64_t new_odometer_meters);

void mc_interface_ignore_input(int time_ms);

void mc_interface_set_current_off_delay(float delay_sec);

void mc_interface_override_temp_motor(float temp);

void mc_interface_ignore_input_both(int time_ms);
void mc_interface_release_motor_override_both(void);
bool mc_interface_wait_for_motor_release_both(float timeout);

// Statistics
float mc_interface_stat_speed_avg(void);
float mc_interface_stat_speed_max(void);
float mc_interface_stat_power_avg(void);
float mc_interface_stat_power_max(void);
float mc_interface_stat_current_avg(void);
float mc_interface_stat_current_max(void);
float mc_interface_stat_temp_mosfet_avg(void);
float mc_interface_stat_temp_mosfet_max(void);
float mc_interface_stat_temp_motor_avg(void);
float mc_interface_stat_temp_motor_max(void);
float mc_interface_stat_count_time(void);
void mc_interface_stat_reset(void);

// MC implementation functions
void mc_interface_set_fault_info(const char *str, int argn, float arg0, float arg1);
void mc_interface_fault_stop(mc_fault_code fault, bool is_second_motor, bool is_isr);
int mc_interface_try_input(void);
void mc_interface_mc_timer_isr(bool is_second_motor);

// Interrupt handlers
void mc_interface_adc_inj_int_handler(void);

// External variables
extern volatile uint16_t ADC_Value[];
extern volatile float ADC_curr_norm_value[];
extern volatile float ADC_curr_raw[];


// Common fixed parameters
#ifndef HW_DEAD_TIME_NSEC
#define HW_DEAD_TIME_NSEC				360.0	// Dead time
#endif


#endif /* MC_INTERFACE_H_ */
