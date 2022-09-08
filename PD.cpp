#include "main.h"


using namespace pros;

//variable for PID

float kP = 0.40f;
float kD = 0.00f;



void moveDistance(float distance_target_inch)
{
  // int distance_target_deg = distance_target_inch * degrees_side_per_inch; 
  // int start_enc_value = L_Encoder.get_value();
  // int desire_target = distance_target_deg + start_enc_value; 

  float start_distance = L_Encoder.get_value()/degrees_side_per_inch;
  float desire_target = distance_target_inch + start_distance;

  int error = 0;

  int derivative = 0;

  int prev_error = 0;

  float power = 0;
  
  while(true)
  {
  error = desire_target - (L_Encoder.get_value()/degrees_side_per_inch);

  derivative = error - prev_error;

  prev_error = error;

  power = (error*kP + derivative*kD);

  if (power>100)
  {
    power = 100;
  }

      // set the motors to move
    fl.move_velocity(power);
    bl.move_velocity(power);
    fr.move_velocity(power);
    br.move_velocity(power);

    lcd::print(6, "error:%d", error);

    // end the loop when the robot have disired heading
    if (error == 0)
    {
      break;
    }

    
   delay(20);
  }
  BrakeSet();
}
