#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>

#define nd_tren  40
#define nd_duoi  40 

unsigned int8     j, solan=100;
unsigned int16   lm35a; 
unsigned int8 dv_to, ch_to;
unsigned int8 donvi, chuc;
signed int8 i;

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

void  giai_ma_hien_thi (unsigned int16 tam)
{
   donvi = ma7doan[tam %10];
   chuc  = ma7doan[tam/10%10]; 
   if (chuc==0xc0)   chuc=0xff;
   xuat_4led_7doan_2so(chuc, donvi);
}

void xu_ly_so_to_xoa_0_vo_nghia(unsigned int16 so)
{
   ch_to = so/10;
   dv_to = so%10;
   if(ch_to == 0) ch_to = 10;
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

void main() 
{
   set_up_port_ic_chot(); 
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0|vss_vdd ); 
   set_adc_channel(0);
   setup_lcd();
   lcd_command(0x40);
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
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
      giai_ma_hien_thi (lm35a);
      so_sanh_dk_den();
      lcd_goto_xy(0,0);
      lcd_data(" **NHIET DO LM35**");
      xu_ly_so_to_xoa_0_vo_nghia(lm35a);
      lcd_hienthi_so_z_toado_xy(ch_to,1,6);
      lcd_hienthi_so_z_toado_xy(dv_to,1,10);
   }

}
