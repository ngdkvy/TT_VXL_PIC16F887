#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_lcd.c>
const unsigned char char1[]={0x0a,0x15,0x11,0x11,0x0a,0x04,0,0}; 
const unsigned char char2[]={0x04,0x0A,0x11,0x0A,0x04,0,0,0}; 
const unsigned char char3[]={0x1F,0x11,0x11,0x11,0x11,0x11,0x11,0x1F}; 
const unsigned char char4[]={0x42,0x24,0xFF,0x55,0x2A,0,0,0}; 
const unsigned char char5[]={0x04,0x0A,0x11,0x04,0x0A,0,0x04,0}; 
const unsigned char char6[]={0x01,0x01,0x03,0x03,0x07,0x07,0x0F,0x1F}; 
const unsigned char char7[]={0,0x0E,0x11,0x11,0x11,0x11,0x0E,0}; 
const unsigned char char8[]={0x1F,0x11,0x11,0x11,0x1F,0,0,0}; 
signed int8  i;

void main()
{
   set_up_port_ic_chot(); 
   setup_lcd();
   lcd_goto_xy(0,0);
   lcd_data(" hien thi trai tim  ");
   
   lcd_command(0x40);
   for (i=0;i<8;i++)  {  lcd_data(char1[i]); }
   
   lcd_command(0x48);
   for (i=0;i<8;i++)  {  lcd_data(char2[i]); }
   
   lcd_command(0x50);
   for (i=0;i<8;i++)  {  lcd_data(char3[i]); }
   
   lcd_command(0x58);
   for (i=0;i<8;i++)  {  lcd_data(char4[i]); }
   
   lcd_command(0x60);
   for (i=0;i<8;i++)  {  lcd_data(char5[i]); }
   
   lcd_command(0x68);
   for (i=0;i<8;i++)  {  lcd_data(char6[i]); }
   
   lcd_command(0x70);
   for (i=0;i<8;i++)  {  lcd_data(char7[i]); }
   
   lcd_command(0x78);
   for (i=0;i<8;i++)  {  lcd_data(char8[i]); }
   
   lcd_goto_xy(1,0); 
   lcd_data(0); 
   
   lcd_goto_xy(1,10); 
   lcd_data(1);
   
   lcd_goto_xy(1,19); 
   lcd_data(2);
   
   lcd_goto_xy(2,0); 
   lcd_data(3); 
   
   lcd_goto_xy(2,10); 
   lcd_data(4);
   
   lcd_goto_xy(2,19); 
   lcd_data(5);
   
   lcd_goto_xy(3,0); 
   lcd_data(6); 
   
   lcd_goto_xy(3,10); 
   lcd_data(7);
   while(true);
}
