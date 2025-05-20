//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>
#define nd_tren  40

unsigned int8    j, solan=100; 
float   lm35a;
int16 kq_ht;
unsigned int8     donvi_led, chuc_led, thapphan_led;
unsigned int8     donvi_lcd, chuc_lcd, thapphan_lcd;
signed int8       i;

void giai_xoa_so_0_vo_nghia_nhiet_do()
{
   thapphan_led = ma7doan[kq_ht %10];
   donvi_led    = ma7doan[kq_ht/10%10] & 0x7F; 
   chuc_led     = ma7doan[kq_ht/100];
   if (chuc_led == 0xc0) chuc_led = 0xff;
   xuat_4led_7doan_3so(chuc_led, donvi_led & 0x7f, thapphan_led);
}

void GM_LCD_font_nho()
{
   donvi_lcd    = kq_ht/10%10+0x30;
   chuc_lcd     = kq_ht/100+0x30; 
   thapphan_lcd = kq_ht %10+0x30;
   lcd_goto_xy(1,5);
   lcd_data(chuc_lcd);
   lcd_data(donvi_lcd);
   lcd_goto_xy(1,8);
   lcd_data(thapphan_lcd); 
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

void so_sanh_dk_led_don()
{
   if (lm35a>nd_tren)
      xuat_32led_don_4byte(0,  0,  0,  0xff);
   else if (lm35a<nd_tren)
      xuat_32led_don_4byte(0,  0,  0,  0);
}
void main() 
{
   set_up_port_ic_chot(); 
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0|vss_vdd ); 
   setup_lcd();
   
   lcd_command(0x40);
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
   lcd_goto_xy(1,0);
   lcd_data("ND =   .");
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
      kq_ht = (int16) (lm35a*10);
      giai_xoa_so_0_vo_nghia_nhiet_do();
      so_sanh_dk_led_don();
      GM_LCD_font_nho();
      
      lcd_hienthi_so_z_toado_xy(kq_ht/100, 2, 0);
      lcd_hienthi_so_z_toado_xy(kq_ht/10%10, 2, 3);
      lcd_goto_xy(3,7); 
      lcd_data(3);
      lcd_hienthi_so_z_toado_xy(kq_ht %10, 2, 9);
   } 
}
