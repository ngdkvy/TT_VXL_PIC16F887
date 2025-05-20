#include    <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds18b20.c> 
unsigned int8 nd_1820;

void main() 
{
   set_up_port_ic_chot(); 
   khoi_tao_ds18b20(); 
   ds18a_tam=0;
   xuat_4led_7doan_giaima_xoa_so0(0);
   while(true)
   {
      if(touch_present()) 
      {
         doc_giatri_ds18b20();
      }
      if(ds18al!=ds18a_tam)
      {
         ds18a_tam =  ds18al;
         nd_1820 = ds18a;
         xuat_4led_7doan_giaima_xoa_so0(nd_1820); 
      }
   }
}
