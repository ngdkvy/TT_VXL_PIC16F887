#include <tv_pickit2_shift_1.c> 
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>

unsigned int8     j, solan=100; 
unsigned int16    lm35a, lm35b;
unsigned int8     donvi, chuc, tram, ngan, tr, ng;
unsigned int8     t0;

void GM_LCD()
{
   donvi = lm35a%10+0x30;
   chuc  = lm35a/10+0x30; 
   tram  = lm35b%10+0x30;
   ngan =  lm35b/10+0x30;
   tr  = t0%10+0x30;
   ng =  t0/10+0x30;
   if (chuc == 0x30)   chuc = 0x20;
   if (ngan == 0x30)   ngan = 0x20;
   if (ng == 0x30)   ng = 0x20;
}

void hienthi_lcd()
{
   GM_LCD();
   lcd_goto_xy(0,16);
   lcd_data(chuc); 
   lcd_data(donvi); 
   lcd_goto_xy(1,16);
   lcd_data(ngan); 
   lcd_data(tram); 
   lcd_goto_xy(2,16);
   lcd_data(ng); 
   lcd_data(tr); 
}

void so_sanh_dk_den() 
{
   if ((lm35a > 40) && (lm35b > 40)) 
      triac_2_off();
   if ((lm35a < 35) && (lm35b < 35)) 
      triac_2_on();
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

void doc_nd_lm35b() 
{
   set_adc_channel(1); 
   delay_ms(1);
   lm35b = 0;
   for (j=0; j<solan; j++) 
   {
      lm35b = lm35b + read_adc(); 
      delay_us(100);
   }
   lm35b = lm35b /2.046; 
   lm35b = lm35b /solan;
}

void main() 
{
   set_up_port_ic_chot(); 
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an1|vss_vdd );
   setup_lcd();
   setup_timer_0 (t0_ext_l_to_h | t0_div_1); 
   set_timer0(0);
   t0 = 0;
   
   lcd_goto_xy(0,0);
   lcd_data("NHIET DO LM35A: ");
   lcd_goto_xy(1,0);
   lcd_data("NHIET DO LM35B: ");
   lcd_goto_xy(2,0);
   lcd_data("DEM SAN PHAM: ");

   
   while(true)
   {
      t0 = get_timer0();
      if (t0 >= 100) 
      {
         set_timer0(0);
         t0 = 0;
      }
      doc_nd_lm35a();
      doc_nd_lm35b();
      hienthi_lcd();
   }
}
