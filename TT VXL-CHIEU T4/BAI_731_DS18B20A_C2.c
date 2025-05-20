#include    <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_ds18b20.c> 

void main() 
{
   set_up_port_ic_chot(); 
   khoi_tao_ds18b20(); 
   xuat_4led_7doan_giaima_xoa_so0(0);
   while(true)
   {
      if(touch_present()) 
      {
         doc_giatri_ds18b20();
         ds18a   =  ds18a>>4;
         ds18a   =  ds18a & 0x0ff;
      }
      xuat_4led_7doan_giaima_xoa_so0(ds18a); 

   }
}
