#include    <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c> 
#include <tv_pickit2_shift_ds18b20.c> 

unsigned int8     donvi_ds18a, chuc_ds18a, thapphan1_ds18a, thapphan2_ds18a;
signed int8       i;
void  giai_ma_4_led_7_doan ()
{   
   donvi_ds18a = ma7doan[nguyen % 10];
   chuc_ds18a  = ma7doan[nguyen / 10];
   thapphan1_ds18a = ma7doan[tp%10];
   thapphan2_ds18a = ma7doan[tp/10];
   xuat_4led_7doan_4so(chuc_ds18a, donvi_ds18a&0x7f,thapphan1_ds18a, thapphan2_ds18a);
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

void hienthi_LCD_nhietdo_to()
{
   lcd_hienthi_so_z_toado_xy(nguyen/10, 0, 0);
   lcd_hienthi_so_z_toado_xy(nguyen%10, 0, 3);
   lcd_goto_xy(1,6);
   lcd_data('.');
   lcd_hienthi_so_z_toado_xy(tp/100, 0, 7);
   lcd_hienthi_so_z_toado_xy(tp/10%10, 0, 10);
   lcd_hienthi_so_z_toado_xy(tp%10, 0, 13);
}


void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0] = ma7doan [tp % 10];
   led_7dq[1] = ma7doan [tp / 10];
   
   led_7dq[2] = ma7doan [nguyen % 10];
   led_7dq[3] = ma7doan [nguyen / 10];
}


void main() 
{
   set_up_port_ic_chot(); 
   
   khoi_tao_ds18b20(); 
   
   setup_lcd();
   lcd_command(0x40); 
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
   while(true)
   {
      if(touch_present()) 
      {
         doc_giatri_ds18b20();
      }
      giai_ma_4_led_7_doan ();
      hienthi_LCD_nhietdo_to();
//!      giai_ma_gan_cho_8led_quet();
//!      hien_thi_8led_7doan_quet(); 
   }
}
