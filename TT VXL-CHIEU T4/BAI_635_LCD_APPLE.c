#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
const unsigned char char1[]={0,0,0,0,0x06,0x0F,0x0F,0x0F}; 
const unsigned char char2[]={0x08,0x18,0x10,0,0x0C,0x1E,0x1E,0x1C}; 
const unsigned char char3[]={0x0F,0x0F,0x0F,0x07,0x03,0,0,0}; 
const unsigned char char4[]={0x1C,0X1E,0x1E,0x1C,0x18,0,0,0}; 
signed int8  i;

void main()
{
   set_up_port_ic_chot(); 
   setup_lcd();
   lcd_goto_xy(0,2);
   lcd_data("BIEU TUONG APPLE");
   
   lcd_command(0x40);
   for (i=0;i<8;i++)  {  lcd_data(char1[i]); }
   
   lcd_command(0x48);
   for (i=0;i<8;i++)  {  lcd_data(char2[i]); }
   
   lcd_command(0x50);
   for (i=0;i<8;i++)  {  lcd_data(char3[i]); }
   
   lcd_command(0x58);
   for (i=0;i<8;i++)  {  lcd_data(char4[i]); }
   
   lcd_goto_xy(1,9); 
   lcd_data(0); 
   
   lcd_goto_xy(1,10); 
   lcd_data(1); 
   
   lcd_goto_xy(2,9); 
   lcd_data(2); 
   
   lcd_goto_xy(2,10); 
   lcd_data(3); 
   
   while(true);
}
