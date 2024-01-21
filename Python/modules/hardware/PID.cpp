#include "PID.h"

PID::PID() : K_p(0.0), K_i(0.0), K_d(0.0), prev_error(0.0), integral_error(0.0), current_time(0), prev_time(0),dt(0) {
    // Constructor implementation
}

void PID::setParameters(float K_p_new, float K_i_new, float K_d_new) {
    K_p = K_p_new;
    K_i = K_i_new;
    K_d = K_d_new;
    prev_error = 0;
    integral_error = 0; 
    u_t = 0;
    
}
// varaibles may need be in terms of position
void PID::calculateNewSignal(int target_speed, int current_speed) {
    
    // Calculate error
    int error = target_speed - current_speed; // target speed defined by movement code

    // Variables for PID controller
    int P = error;
    float I = integral_error + error * (dt);  // Simple integration
    float D = (error - prev_error) / (dt);

    // Find u_t signal
    u_t= K_p * P + K_i * I + K_d * D;

    // Motor Power 
    int pwr = fabs(u_t); 
    int pwmMax = 400; // define Max PWM that can be sent
    if ( pwr > pwmMax){
      pwr = pwmMax;
      }
    // Motor Direction
    int dir = 1;
    if (u_t < 0){
      dir = -1;
      }

    // Update variables for the next iteration
    prev_error = error;
    integral_error = I;
    prev_time = current_time;

    // setMotor(); // Write u_t signal to motor
};
