#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
signed int8    i,dem;
unsigned int8    donvi, chuc;

void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy(x1,y1); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x1+1,y1); 
      lcd_data(lcd_so_x[lcd_so][i]);
  }
}
void giai_ma_hien_thi (unsigned int8 tam)
{
   donvi = ma7doan[tam %10];
   chuc  = ma7doan[tam/10]; 
   if (chuc==0xc0)   chuc=0xff;
   xuat_4led_7doan_2so(chuc, donvi);
}

void main()
{
   set_up_port_ic_chot();
   setup_lcd();
   lcd_goto_xy(0,0);
   lcd_data("**dem tu 00 den 99**");
   
   lcd_command(0x40);
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
   lcd_hienthi_so_z_toado_xy(0,2,0); 
   while(true)
   {
      for (dem=0;dem<100;dem++)
      {
         lcd_hienthi_so_z_toado_xy(dem/10,2,0); 
         lcd_hienthi_so_z_toado_xy(dem%10,2,3);
         giai_ma_hien_thi (dem);
         delay_ms(500);
      }
   }
}
