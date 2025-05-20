#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_step_motor.c> 
#include <tv_pickit2_shift_key4x4_138.c> 

int1 TT_ONOFF;
signed int8  mp;
unsigned int8 mp_motor[2]={' '};
unsigned int16 so_buoc;

void  chucnang()
{
   if (mp < 10)
   {
      mp_motor[1] = mp_motor[0];
      mp_motor[0] = mp;
      xuat_4led_7doan_1so(ma7doan[mp]);
   }
   if (mp == 13)
   {
     TT_ONOFF = 1;
   }
   if (mp == 15)
   {
      so_buoc = (mp_motor[1]*10 + mp_motor[0])*200;
   }
}

void main() 
{
   set_up_port_ic_chot(); 
   set_tris_b(0x3c);
   stepmotor_delay=5;
   stepmotor_onoff=1;   //de khoi canh bao 
   so_buoc = 0;
   TT_ONOFF = 0;
   while(true)
   {
      mp = key_4x4_dw();
      if (mp != 0xff)
      {
         chucnang();
      }
      if (TT_ONOFF == 1)
      {
         if (so_buoc >= 0)
         {
            step_motor_quay_thuan_fs();
            so_buoc--;
            delay_ms(stepmotor_delay); 
         }
      }
   } 
}
