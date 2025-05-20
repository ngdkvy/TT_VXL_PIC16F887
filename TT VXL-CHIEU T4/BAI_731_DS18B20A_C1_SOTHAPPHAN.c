#include    <tv_pickit2_shift_1.c>
//!#include    <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_ds18b20.c> 

unsigned int8 donvi_ds18a, chuc_ds18a, thapphan1_ds18a, thapphan2_ds18a;

void  giai_ma_hien_thi ()
{   
   donvi_ds18a = ma7doan[nguyen % 10];
   chuc_ds18a  = ma7doan[nguyen / 10];
   thapphan1_ds18a = ma7doan[tp%10];
   thapphan2_ds18a = ma7doan[tp/10];
   xuat_4led_7doan_4so(chuc_ds18a, donvi_ds18a&0x7f,thapphan1_ds18a, thapphan2_ds18a);
}

void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0] = ma7doan [tp % 10];
   led_7dq[1] = ma7doan [tp / 10];
   
   led_7dq[2] = ma7doan [nguyen % 10];
   led_7dq[3] = ma7doan [nguyen / 10];
}

void main() 
{
   set_up_port_ic_chot(); 
   khoi_tao_ds18b20(); 
   ds18a_tam=0;
   while(true)
   {
      if(touch_present()) 
      {
         doc_giatri_ds18b20();
      }
      giai_ma_hien_thi ();
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet(); 
   }
}
