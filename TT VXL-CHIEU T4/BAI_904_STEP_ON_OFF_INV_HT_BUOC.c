#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_step_motor.c> 

int1 TT_ONOFF;
unsigned int16 so_buoc;
unsigned int16 donvi_motor, chuc_motor, tram_motor, ngan_motor;

void  giai_ma_hien_thi ()
{
//!   Luu so de hien thi ra LED 
   donvi_motor = ma7doan[so_buoc%10];
   chuc_motor  = ma7doan[so_buoc/10%10]; 
   tram_motor  = ma7doan[so_buoc/100%10]; 
   ngan_motor  = ma7doan[so_buoc/1000]; 
   
//!   Xoa so 0 vo nghia
   if (ngan_motor == 0xc0)   
   {
      ngan_motor = 0xff;
      if (tram_motor == 0xc0)   
      {
         tram_motor = 0xff;
         if (chuc_motor == 0xc0)   
            chuc_motor = 0xff;
      }
   }
   xuat_4led_7doan_4so(ngan_motor, tram_motor, chuc_motor, donvi_motor);
}

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
         so_buoc = 0;
         giai_ma_hien_thi ();
         delay_ms(stepmotor_delay);

         while (!input(BT1));
      }
   }
} 


void main() 
{
   set_up_port_ic_chot(); 
   set_tris_b(0x3c);
   stepmotor_delay=5;
   stepmotor_onoff=1;   //de khoi canh bao 
   so_buoc = 0;
   while(true)
   {
      phim_ONOFF();
      if (TT_ONOFF == 1)
      {
         motor_step_run_fs();
         so_buoc++;
         delay_ms(stepmotor_delay);
         phim_inv();
         
      }
      else if (!TT_ONOFF)
         so_buoc = 0;
      giai_ma_hien_thi ();
   } 
}
