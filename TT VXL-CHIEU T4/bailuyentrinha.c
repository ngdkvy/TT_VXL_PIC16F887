//!#include <tv_pickit2_shift_1.c> 
#include <tv_pickit2_shift_1_proteus.c> 
#include <tv_pickit2_shift_lcd.c> 
#include <tv_pickit2_shift_ds18b20.c> 

float             lm35b;
int16             kq_ht_lm35b;
unsigned int8     j, solan_lm35 = 100; 
signed int8       i;
const unsigned char daucham[] = {32, 3, 32, 32, 32, 32};
unsigned int8     donvi_lcd, chuc_lcd;

void doc_nd_lm35b() 
{
   set_adc_channel(1); 
   delay_ms(1);
   lm35b = 0;
   for (j=0; j<solan_lm35; j++) 
   {
      lm35b = lm35b + read_adc(); 
      hien_thi_8led_7doan_quet();
   }
   lm35b = lm35b /2.046; 
   lm35b = lm35b /solan_lm35;
   kq_ht_lm35b = (int16) (lm35b*10); 
}

void giai_ma_gan_cho_8led_quet()
{
   led_7dq[2] = ma7doan [kq_ht_lm35b /10%10] &0x7f;
   led_7dq[3] = ma7doan [kq_ht_lm35b/100] ;
   
   led_7dq[0] = ma7doan [ds18a % 10];
   led_7dq[1] = ma7doan [ds18a / 10];
}

void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy(x1,y1); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x1+1,y1); 
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}

void lcd_hienthi_daucham(signed int8 x2, y2)
{
   lcd_goto_xy(x2,y2); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x2+1,y2); 
      lcd_data(daucham[i]);
   }
}

void hienthi_LCD_font_nho()
{
   donvi_lcd    = ds18a%10+0x30;
   chuc_lcd     = ds18a/10+0x30; 
   lcd_goto_xy(3,0);
   lcd_data(donvi_lcd);
   lcd_goto_xy(3,19);
   lcd_data(chuc_lcd);

}

void hienthi_LCD_font_to()
{
   lcd_hienthi_so_z_toado_xy(kq_ht_lm35b%10, 2, 6);
   lcd_hienthi_daucham(3, 9);
   lcd_hienthi_so_z_toado_xy(kq_ht_lm35b/100, 2, 12);
   lcd_hienthi_so_z_toado_xy(kq_ht_lm35b/10%10, 2, 15);
}
void main()
{
   set_up_port_ic_chot(); 

   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an1|vss_vdd );
   
   khoi_tao_ds18b20();
   
   setup_lcd();
   lcd_command(0x40); 
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
   while(true)
   {
      doc_nd_lm35b();
      if(touch_present()) 
      {
         doc_giatri_ds18b20();
         ds18a   =  ds18a>>4;
         ds18a   =  ds18a & 0x0ff;
      }
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet();
      hienthi_LCD_font_nho();
      hienthi_LCD_font_to();
   }

}
