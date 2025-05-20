#include    <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds18b20.c> 

unsigned int8     donvi_lm35, chuc_lm35, donvi_ds18a, chuc_ds18a;
unsigned int16    lm35a;
unsigned int8     j, solan=100; 

void  giai_ma_hien_thi ()
{
   donvi_lm35 = ma7doan[lm35a % 10];
   chuc_lm35  = ma7doan[lm35a / 10];
   
   donvi_ds18a = ma7doan[ds18a % 10];
   chuc_ds18a  = ma7doan[ds18a / 10];
   
   xuat_4led_7doan_4so(chuc_ds18a, donvi_ds18a &0x7f, chuc_lm35, donvi_lm35);
}

void doc_nd_lm35a() 
{
   set_adc_channel(0); 
   lm35a = 0;
   delay_ms(1);
   for (j=0; j<solan; j++) 
   {
      lm35a = lm35a + read_adc(); 
      delay_us(100);
   }
   lm35a = lm35a /2.046; 
   lm35a = lm35a /solan;
}

void main() 
{
   set_up_port_ic_chot(); 
   khoi_tao_ds18b20(); 
   while(true)
   {
      if(touch_present()) 
      {
         doc_giatri_ds18b20();
         ds18a   =  ds18a>>4;
         ds18a   =  ds18a & 0x0ff;
      }
      doc_nd_lm35a();
      giai_ma_hien_thi ();
   }
}
