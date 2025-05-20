#include    <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds18b20.c> 

unsigned int8     donvi_ds18a, chuc_ds18a, donvi_counter, chuc_counter;
unsigned int8     t0;
void  giai_ma_hien_thi ()
{
   donvi_counter = ma7doan[t0 % 10];
   chuc_counter  = ma7doan[t0 / 10];
   
   donvi_ds18a = ma7doan[ds18a % 10];
   chuc_ds18a  = ma7doan[ds18a / 10];
   
   xuat_4led_7doan_4so(chuc_counter, donvi_counter &0x7f, chuc_ds18a, donvi_ds18a);
}

void main() 
{
   set_up_port_ic_chot(); 
   khoi_tao_ds18b20(); 
   
   setup_timer_0 (t0_ext_l_to_h | t0_div_1| t0_8_bit); 
   set_timer0(0);
   
   t0 = 0;
   
   while(true)
   {
      t0 = get_timer0();
      if (t0 >= 100)
      {
         t0 = 0;
         set_timer0(0);
      }
      if(touch_present())
      {
         doc_giatri_ds18b20();
         ds18a   =  ds18a>>4;
         ds18a   =  ds18a & 0x0ff;
      }
      giai_ma_hien_thi ();
   }
}
