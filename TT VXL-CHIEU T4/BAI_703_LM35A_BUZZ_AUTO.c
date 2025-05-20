#include <tv_pickit2_shift_1.c>
#define nd_tren  40
#define nd_duoi  40 
unsigned int8     j, solan=100;
unsigned int16   lm35a; 
void so_sanh_dk_den() 
{
   if (lm35a>nd_tren) 
   {
      triac_2_off();
      xuat_32led_don_4byte(0,  0,  0,  0xff);
   }
   else if (lm35a<nd_tren)
   {
      xuat_32led_don_4byte(0,  0,  0,  0);
   }
   if (lm35a<nd_duoi) 
      triac_2_on();
}
void main() 
{
    set_up_port_ic_chot(); 
    setup_adc(adc_clock_div_32); 
    setup_adc_ports(an0|vss_vdd ); 
    set_adc_channel(0);
    while(true)
    {
       lm35a = 0;
       for (j=0; j<solan; j++)
       {
          lm35a = lm35a + read_adc();
          delay_ms(1);
       }
       lm35a = lm35a /2.046;
       lm35a = lm35a /solan;
       xuat_4led_7doan_giaima_xoa_so0(lm35a); 
       so_sanh_dk_den();
    }
}
