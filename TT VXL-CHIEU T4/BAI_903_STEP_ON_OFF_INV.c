#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_step_motor.c> 

int1 TT_ONOFF;

void phim_ONOFF()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
//!         Dao trang thai bien
         TT_ONOFF= ~ TT_ONOFF;         
         while (!input(BT0));
      }
   }
} 

void phim_inv()
{
   if (!input(BT1))
   {
      delay_ms(20);
      if (!input(BT1))
      {
         stepmotor_tn=~stepmotor_tn;    
         motor_step_run_fs();
         delay_ms(stepmotor_delay);
         while (!input(BT1));
      }
   }
} 

void main() 
{
   set_up_port_ic_chot(); 
   stepmotor_delay=5;
   stepmotor_onoff=1;   //de khoi canh bao 
   while(true)
   {
      phim_ONOFF();
      if (TT_ONOFF == 1)
      {
         motor_step_run_fs();
         delay_ms(stepmotor_delay);
         phim_inv();
      }
   } 
}
