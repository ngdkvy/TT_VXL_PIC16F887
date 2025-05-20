#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_step_motor.c> 

unsigned int16 so_buoc;
unsigned int16 donvi_motor, chuc_motor, tram_motor, capdo_motor;
unsigned int8  capdo;

void  giai_ma_hien_thi ()
{
   unsigned int16 tam;
   tam = so_buoc / 2;
   donvi_motor = ma7doan[tam%10];
   chuc_motor  = ma7doan[tam/10%10]; 
   tram_motor  = ma7doan[tam/100%10]; 
   capdo_motor  = ma7doan[capdo]; 
   
//!   Xoa so 0 vo nghia
   if (tram_motor == 0xc0)   
      {
         tram_motor = 0xff;
         if (chuc_motor == 0xc0)   
            chuc_motor = 0xff;
      }
   xuat_4led_7doan_4so(capdo_motor, tram_motor, chuc_motor, donvi_motor);
}

void phim_up()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
         if (capdo < 9)
         {
            capdo++;   
            stepmotor_delay-=5;
         }
         while (!input(BT0));
      }
   }
} 

void phim_dw()
{
   if (!input(BT1))
   {
      delay_ms(20);
      if (!input(BT1))
      {
         if (capdo > 0)
         {
            capdo--;    
            stepmotor_delay+=5;
         }
         while (!input(BT1));
      }
   }
} 

void phim_stop()
{
   if (!input(BT2))
   {
      delay_ms(20);
      if (!input(BT2))
      {
         capdo = 0;
         so_buoc = 0;
         while (!input(BT2));
      }
   }
} 


void main() 
{
   set_up_port_ic_chot(); 
   stepmotor_delay=50;
   stepmotor_onoff=1;   //de khoi canh bao 
   so_buoc = 0;
   capdo = 0;
   while(true)
   {
      phim_up();   
      phim_dw();
      phim_stop();
      if (capdo != 0)
      {
         step_motor_quay_thuan_fs();
         so_buoc++;
         delay_ms(stepmotor_delay);
      }   
      giai_ma_hien_thi ();


   } 
}
