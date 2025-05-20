//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>

unsigned int16   kqadc,k_cach; 

void main()
{
   set_up_port_ic_chot();
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an2|vss_vdd ); 
   set_adc_channel(2);
   while(true)
   {
      kqadc=read_adc();
      delay_ms(30);
      if      (kqadc >= 490)   k_cach = 10; 
      else if (kqadc >  276)   k_cach = 20; 
      else if (kqadc >  194)   k_cach = 30; 
      else if (kqadc >  150)   k_cach = 40; 
      else if (kqadc >  122)   k_cach = 50; 
      else if (kqadc >  106)   k_cach = 60; 
      else if (kqadc >  96)    k_cach = 70; 
      else if (kqadc >  80)    k_cach = 80;
      xuat_4led_7doan_giaima_xoa_so0(k_cach);
   }
}
