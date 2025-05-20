#include <tv_pickit2_shift_1.c> 
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#include <tv_pickit2_shift_ds18b20.c> 
#include <tv_pickit2_shift_key4x4_138.c> 

unsigned int8     j, solan=100; 
unsigned int16    lm35a, lm35b;
unsigned int8     donvi_lm35a, chuc_lm35a, donvi_lm35b, chuc_lm35b, donvi_kcach, chuc_kcach;
unsigned int8     donvi_ds18a, chuc_ds18a, donvi_counter, chuc_counter, donvi_nd_max, chuc_nd_max;
unsigned int16    kqadc, kcach, chenh_lenh_kcach;
unsigned int8     t0;
unsigned int8     nd_max;
signed int8       mp;

void GM_LCD_nhietdo_LM35()
{
   donvi_lm35a     = lm35a%10+0x30;
   chuc_lm35a      = lm35a/10+0x30; 
   donvi_lm35b     = lm35b%10+0x30;
   chuc_lm35b      = lm35b/10+0x30;
   
   if (chuc_lm35a  == 0x30)       chuc_lm35a = 0x20;
   if (chuc_lm35b  == 0x30)       chuc_lm35b = 0x20;
   
   lcd_goto_xy(0,0);
   lcd_data(chuc_lm35a); 
   lcd_data(donvi_lm35a); 
   lcd_goto_xy(0,18);
   lcd_data(chuc_lm35b); 
   lcd_data(donvi_lm35b); 
}

void GM_LCD_counter()
{
   donvi_counter    = t0%10+0x30;
   chuc_counter     = t0/10+0x30;
   if (chuc_counter == 0x30)   chuc_counter   = 0x20;
   
   lcd_goto_xy(1,0);
   lcd_data(chuc_counter); 
   lcd_data(donvi_counter); 
}

void GM_LCD_kcach()
{
   donvi_kcach    = kcach%10+0x30;
   chuc_kcach     = kcach/10+0x30;
   if (chuc_kcach == 0x30)   chuc_kcach   = 0x20;
   
   lcd_goto_xy(2,0);
   lcd_data(chuc_kcach); 
   lcd_data(donvi_kcach); 
}

void GM_LCD_nhietdo_DS18()
{
   donvi_ds18a    = ds18a % 10 + 0x30;
   chuc_ds18a     = ds18a / 10 + 0x30;
   donvi_nd_max   = nd_max % 10 + 0x30;
   chuc_nd_max    = nd_max / 10 + 0x30;

   lcd_goto_xy(3,18);
   lcd_data(chuc_ds18a); 
   lcd_data(donvi_ds18a); 
   lcd_goto_xy(3,0);
   lcd_data(chuc_nd_max); 
   lcd_data(donvi_nd_max); 
}

void  giai_ma_hien_thi ()
{
   donvi_nd_max = ma7doan[nd_max % 10];
   chuc_nd_max  = ma7doan[nd_max / 10];
   
   donvi_ds18a = ma7doan[ds18a % 10];
   chuc_ds18a  = ma7doan[ds18a / 10];
   
   xuat_4led_7doan_4so(chuc_nd_max, donvi_nd_max &0x7f, chuc_ds18a, donvi_ds18a);
}

void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0] = ma7doan [ds18a %10];
   led_7dq[1] = ma7doan [ds18a/10];
   
   led_7dq[6] = ma7doan [nd_max %10];
   led_7dq[7] = ma7doan [nd_max /10];
   
}

void doc_nd_lm35a() 
{
   set_adc_channel(0); 
   lm35a = 0;
   for (j=0; j<solan; j++) 
   {
      lm35a = lm35a + read_adc(); 
      hien_thi_8led_7doan_quet(); 
   }
   lm35a = lm35a /2.046; 
   lm35a = lm35a /solan;
}

void doc_nd_lm35b() 
{
   set_adc_channel(1); 
   lm35b = 0;
   for (j=0; j<solan; j++) 
   {
      lm35b = lm35b + read_adc(); 
      hien_thi_8led_7doan_quet(); 
   }
   lm35b = lm35b /2.046; 
   lm35b = lm35b /solan;
}

void doc_kc() 
{
   set_adc_channel(2); 
   kqadc = 0;
   for (j=0; j<solan; j++) 
   {
      kqadc = kqadc + read_adc(); 
      hien_thi_8led_7doan_quet(); 
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

void doc_ds18a()
{
   if(touch_present()) 
   {
      doc_giatri_ds18b20();
      ds18a   =  ds18a>>4;
      ds18a   =  ds18a & 0x0ff;
   }
}

void bao_qua_nhiet()
{
   if (ds18a>nd_max)
   {
      triac_2_off();
      xuat_32led_don_1dw(0x0000ffff);
   }
   else if (ds18a<nd_max)
   {
      xuat_32led_don_1dw(0);
   }
   if (ds18a<nd_max)
   {
      triac_2_on();
   }
}

void main() 
{
   set_up_port_ic_chot(); 
   khoi_tao_ds18b20(); 
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an1|vss_vdd );
   setup_lcd();
   setup_timer_0 (t0_ext_l_to_h | t0_div_1); 
   set_timer0(0);
   t0 = 0;
   nd_max = 35;
   while(true)
   {
      t0 = get_timer0();
      if (t0 >= 100) 
      {
         set_timer0(0);
         t0 = 0;
      }
      mp = key_4x4_up();
      if (mp != 0xff)
      {
         if ((mp == 1) && (nd_max < 60))
            nd_max++;
         if ((mp == 2) && (nd_max > 35))
            nd_max--;
         giai_ma_hien_thi ();
         GM_LCD_nhietdo_DS18();
         giai_ma_gan_cho_8led_quet();
         hien_thi_8led_7doan_quet(); 
      }
      doc_ds18a();
      doc_nd_lm35a();
      doc_nd_lm35b();
      doc_kc();
      bao_qua_nhiet();
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet(); 
      giai_ma_hien_thi ();
      GM_LCD_nhietdo_LM35();
      GM_LCD_counter();
      GM_LCD_kcach();
      GM_LCD_nhietdo_DS18();
   }
}
