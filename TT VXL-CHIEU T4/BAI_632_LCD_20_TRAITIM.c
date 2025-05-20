#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
const unsigned char hang2[]={0x0a,0x15,0x11,0x11,0x0a,0x04,0,0}; 
signed int8  i, j;

void main()
{
   set_up_port_ic_chot(); 
   setup_lcd();
   lcd_goto_xy(0,0);
   lcd_data(" hien thi trai tim  ");
   
   lcd_command(0x40);
   for (i=0;i<8;i++)  {  lcd_data(hang2[i]); }
   for (j = 0; j < 20; j++)
   {
   lcd_goto_xy(1,j);
   lcd_data(0); 
   }
   while(true);
}
