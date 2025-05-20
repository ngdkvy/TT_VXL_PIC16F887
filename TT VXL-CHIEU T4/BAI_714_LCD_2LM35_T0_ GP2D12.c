#include <tv_pickit2_shift_1.c> 
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>

unsigned int8     j, solan=100; 
unsigned int16    lm35a, lm35b;
unsigned int8     donvi_lm35a, chuc_lm35a, donvi_lm35b, chuc_lm35b, donvi_counter, chuc_counter, donvi_kcach, chuc_kcach;
unsigned int16    kqadc, kcach, chenh_lenh_kcach;
unsigned int8     t0;

void GM_LCD()
{
   donvi_lm35a   = lm35a%10+0x30;
   chuc_lm35a    = lm35a/10+0x30; 
   donvi_lm35b   = lm35b%10+0x30;
   chuc_lm35b    =  lm35b/10+0x30;
   donvi_counter = t0%10+0x30;
   chuc_counter  =  t0/10+0x30;
   donvi_kcach   = kcach%10+0x30;
   chuc_kcach    =  kcach/10+0x30;
   
   if (chuc_lm35a   == 0x30)   chuc_lm35a = 0x20;
   if (chuc_lm35b   == 0x30)   chuc_lm35b = 0x20;
   if (chuc_counter == 0x30)     chuc_counter = 0x20;
   if (chuc_kcach   == 0x30)     chuc_kcach = 0x20;
}

void hienthi_lcd()
{
   GM_LCD();
   lcd_goto_xy(0,0);
   lcd_data(chuc_lm35a); 
   lcd_data(donvi_lm35a); 
   lcd_goto_xy(0,16);
   lcd_data(chuc_lm35b); 
   lcd_data(donvi_lm35b); 
   lcd_goto_xy(1,0);
   lcd_data(chuc_counter); 
   lcd_data(donvi_counter); 
   lcd_goto_xy(2,0);
   lcd_data(chuc_kcach); 
   lcd_data(donvi_kcach); 
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

void doc_kc() 
{
   set_adc_channel(2); 
   kqadc = 0;
   delay_ms(1);
   for (j=0; j<solan; j++) 
   {
      kqadc = kqadc + read_adc(); 
      delay_ms(10);
   }
   kqadc = kqadc / solan;
   if (kqadc <= 80)
      kcach = 80;
   else if ((kqadc > 80) && (kqadc < 87))
   {
      chenh_lenh_kcach = kqadc - 80;
      kcach = 80 - chenh_lenh_kcach/0.77;
   }
   else if (kqadc == 87)
      kcach = 70;
   else if ((kqadc > 87) && (kqadc < 106))
   {
      chenh_lenh_kcach = kqadc - 87;
      kcach = 70 - chenh_lenh_kcach/2.11;
   }
   else if (kqadc == 106)
      kcach = 60;
   else if ((kqadc > 106) && (kqadc < 124))
   {
      chenh_lenh_kcach = kqadc - 106;
      kcach = 60 - chenh_lenh_kcach/2;
   }
   else if (kqadc == 124)
      kcach = 50;
   else if ((kqadc > 124) && (kqadc < 150))
   {
      chenh_lenh_kcach = kqadc - 124;
      kcach = 50 - chenh_lenh_kcach/2.88;
   }
   else if (kqadc == 150)
      kcach = 40;
   else if ((kqadc > 150) && (kqadc < 196))
   {
      chenh_lenh_kcach = kqadc - 150;
      kcach = 40 - chenh_lenh_kcach/5.11;
   }
   else if (kqadc == 196)
      kcach = 30;
   else if ((kqadc > 196) && (kqadc < 276))
   {
      chenh_lenh_kcach = kqadc - 196;
      kcach = 30 - chenh_lenh_kcach/8.88;
   }
   else if (kqadc == 276)
      kcach = 20;
   else if ((kqadc > 276) && (kqadc < 490))
   {
      chenh_lenh_kcach = kqadc - 276;
      kcach = 20 - chenh_lenh_kcach/23.77;
   }
   else if (kqadc == 490)
      kcach = 10;
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
      doc_kc();
      hienthi_lcd();
   }
}
