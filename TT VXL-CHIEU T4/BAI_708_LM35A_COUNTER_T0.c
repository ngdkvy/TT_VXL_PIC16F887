#include <tv_pickit2_shift_1.c>
unsigned int8    j, solan=100; 
unsigned int16   lm35a; 
unsigned int8    t0;
unsigned int8    donvi, chuc, tram, ngan;

void giai_xoa_so_0_vo_nghia()
{
   donvi    = ma7doan[lm35a %10]; 
   chuc     = ma7doan[lm35a/10];
   if (chuc == 0xc0)
      chuc=0xff;
   tram   = ma7doan[t0 %10]; 
   ngan     = ma7doan[t0 /10];
   if (ngan == 0xc0)
      ngan = 0xff;
   xuat_4led_7doan_4so(ngan, tram & 0x7F,chuc, donvi);
}

void main() 
{
   set_up_port_ic_chot(); 
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0|vss_vdd ); 
   set_adc_channel(0);
   
   setup_timer_0 (t0_ext_l_to_h | t0_div_1); 
   set_timer0(97);
   t0 = 97;
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
      
      t0=get_timer0();
      if (t0>=100)   
      {
         set_timer0(0);
         t0=0;
      }
      giai_xoa_so_0_vo_nghia();
   } 
}
