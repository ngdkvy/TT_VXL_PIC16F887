#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
const unsigned char hang2[]={0x0a,0x15,0x11,0x11,0x0a,0x04,0,0}; 
const unsigned char hang3[]={0x04,0x0A,0x11,0x0A,0x04,0,0,0}; 
const unsigned char hang4[]={0x1F,0x11,0x11,0x11,0x1F,0,0,0}; 
signed int8  i;

void main()
{
   set_up_port_ic_chot(); 
   setup_lcd();
   lcd_goto_xy(0,0);
   lcd_data(" hien thi trai tim  ");
   
   lcd_command(0x40);
   for (i=0;i<8;i++)  {  lcd_data(hang2[i]); }
   lcd_command(0x48);
   for (i=0;i<8;i++)  {  lcd_data(hang3[i]); }
   lcd_command(0x50);
   for (i=0;i<8;i++)  {  lcd_data(hang4[i]); }
   lcd_goto_xy(1,10); 
   lcd_data(0); 
   lcd_goto_xy(2,10); 
   lcd_data(1);
   lcd_goto_xy(3,10); 
   lcd_data(2);
   while(true);
}
