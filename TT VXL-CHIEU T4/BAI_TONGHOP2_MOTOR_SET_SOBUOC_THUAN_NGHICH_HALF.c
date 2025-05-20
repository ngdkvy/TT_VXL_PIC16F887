#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_step_motor.c> 
#include <tv_pickit2_shift_key4x4_138.c> 

unsigned int16 so_buoc_thuan, so_buoc_nghich;
unsigned int16 donvi_motor, chuc_motor, tram_motor, capdo_motor;
unsigned int8  capdo;
int1 TT_SS ;
signed int8  mp;
unsigned int8 mp_motor[2]={' '};

void  giai_ma_hien_thi (unsigned int16 tam)
{
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
void  chucnang()
{
   if (mp < 10)
   {
      mp_motor[1] = mp_motor[0];
      mp_motor[0] = mp;
      xuat_4led_7doan_1so(ma7doan[mp]);
   }
   if (mp == 10) 
   {
       if (capdo < 9)
         {
            capdo++;   
            stepmotor_delay-=5;
         }
   }
   if (mp == 11)
   {
      if (capdo > 0)
      {
         capdo--;    
         stepmotor_delay+=5;
      }
   }
   if (mp == 13)
   {
      TT_SS = ~ TT_SS;
      capdo = 0;
      stepmotor_delay=100;
      giai_ma_hien_thi (so_buoc_thuan);
   }
   if (mp == 15)
   {
      so_buoc_thuan = (mp_motor[1]*10 + mp_motor[0]);
      so_buoc_nghich = so_buoc_thuan / 2;
   }
}

void main() 
{
   set_up_port_ic_chot(); 
   set_tris_b(0x3c);
   stepmotor_delay=100;
   stepmotor_onoff=1;   //de khoi canh bao 
   capdo = 0;
   TT_SS = 0;
   while(true)
   {
      mp = key_4x4_up();
      if (mp != 0xff)
      {
         chucnang();
      }
      if ((capdo != 0) && (TT_SS))
      {
         if (so_buoc_thuan > 0)
         {
            step_motor_quay_thuan_fs();
            so_buoc_thuan--;
            giai_ma_hien_thi (so_buoc_thuan);
         }
         if ((so_buoc_thuan == 0) && (so_buoc_nghich > 0))
         {
            step_motor_quay_nghich_fs();
            so_buoc_nghich--;
            giai_ma_hien_thi (so_buoc_nghich);
         }
         delay_ms(stepmotor_delay);
      }   

   } 
}
