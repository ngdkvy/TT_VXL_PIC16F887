#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
signed int8    i;

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
   setup_lcd();
   
   lcd_goto_xy(0,0);
   lcd_data("hien thi so 0123 hang 3");
   
   lcd_command(0x40);
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
   lcd_hienthi_so_z_toado_xy(0,2,0); 
   lcd_hienthi_so_z_toado_xy(1,2,4); 
   lcd_hienthi_so_z_toado_xy(2,2,8); 
   lcd_hienthi_so_z_toado_xy(3,2,12); 
   while(true);
}
