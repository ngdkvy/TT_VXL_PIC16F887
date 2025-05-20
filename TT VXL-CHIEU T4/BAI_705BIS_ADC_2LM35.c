#include <tv_pickit2_shift_1.c> 
#include <tv_pickit2_shift_lcd.c> 

unsigned int8     j, solan=100; 
unsigned int16    lm35a, lm35b;
unsigned int8     donvi, chuc, tram, ngan;
unsigned int8     dv, ch, tr, ng;
signed int8       bdn;
int1              TT_NN;

#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
} 

//!Module 4 LED 8 doan: xoa so 0 vo nghia
void giai_ma_gan_cho_8led_quet()
{
//!   Luu so de hien thi ra LED 8
      led_7dq[0] = ma7doan [lm35b %10];
      led_7dq[1] = ma7doan [lm35b/10];
      
      led_7dq[6] = ma7doan [lm35a %10];
      led_7dq[7] = ma7doan [lm35a/10];
      
      if (led_7dq[1] == 0xc0) led_7dq[1] = 0xff;
      if (led_7dq[7] == 0xc0) led_7dq[7] = 0xff;

}

//!Module 4 LED 8 doan: xoa so 0 vo nghia
void tat_8led_quet()
{
   led_7dq[1] = led_7dq[7] = led_7dq[0] = led_7dq[6] = 0xff;
}

//!Module 4 LED 7 doan: xoa so 0 vo nghia
void  giai_ma_hien_thi (unsigned int16 Tb, unsigned int16 Ta)
{
   donvi = ma7doan[Tb %10];
   chuc  = ma7doan[Tb/10%10]; 
   if (chuc==0xc0)   chuc=0xff;
   
   tram = ma7doan[Ta %10];
   ngan  = ma7doan[Ta/10%10]; 
   if (ngan==0xc0)   ngan=0xff;
   
   xuat_4led_7doan_4so(ngan, tram&0x7f, chuc, donvi);
}

//!LCD: xoa so 0 vo nghia
void GM_LCD()
{
//!   Luu so de hien thi ra LCD 
   dv = lm35a%10+0x30;
   ch = lm35a/10+0x30; 
   
//!   Xoa so 0 vo nghia
   if (ch == 0x30)   ch = 0x20;
   
//!   Luu so de hien thi ra LCD 
   tr = lm35b%10+0x30;
   ng = lm35b/10+0x30; 
   
//!   Xoa so 0 vo nghia
   if (ng == 0x30)   ng = 0x20;
}

//!LCD: hien thi nhiet do ra man hinh
void hienthi_lcd()
{
   GM_LCD();
   lcd_goto_xy(0,0);
   lcd_data(ch); 
   lcd_data(dv);
   
   lcd_goto_xy(0,18);
   lcd_data(ng); 
   lcd_data(tr);
}

//!Doc nhiet do o kenh 0
void doc_nd_lm35a() 
{
   set_adc_channel(0); 
   lm35a = 0;
   delay_ms(1);
   for (j=0; j<solan; j++) 
   {
      lm35a = lm35a + read_adc(); 
      hien_thi_8led_7doan_quet();
   }
   lm35a = lm35a /2.046; 
   lm35a = lm35a /solan;
}

//!Doc nhiet do o kenh 1
void doc_nd_lm35b() 
{
   set_adc_channel(1); 
   delay_ms(1);
   lm35b = 0;
   for (j=0; j<solan; j++) 
   {
      lm35b = lm35b + read_adc(); 
      hien_thi_8led_7doan_quet();
   }
   lm35b = lm35b /2.046; 
   lm35b = lm35b /solan;
}

void main() 
{
   set_up_port_ic_chot(); 
   setup_lcd();
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an1|vss_vdd );

   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global); 
   enable_interrupts(int_timer1); 
   TT_NN = 0;
   
   while(true)
   {
      doc_nd_lm35a();
      doc_nd_lm35b();
      giai_ma_hien_thi (lm35b, lm35a);
      hienthi_lcd();
      if ((lm35a > 30) | (lm35b > 30))
         TT_NN = 1;
      else 
         TT_NN = 0;
      if (TT_NN  == 1)
      {
         if (bdn < 5)
         {
            tat_8led_quet();
         }
         else if (bdn < 10) 
         {
            giai_ma_gan_cho_8led_quet();  
            hien_thi_8led_7doan_quet();
         }
         else 
            bdn = 0;
      }
      else 
      {
         giai_ma_gan_cho_8led_quet();
         hien_thi_8led_7doan_quet();
         giai_ma_hien_thi (lm35b, lm35a);
      }
   }
}
