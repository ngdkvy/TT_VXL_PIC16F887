//!clean toan bo lcd

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


   lcd_command(0x40);
   for (i=0;i<8;i++)  {  lcd_data(char1[i]); }
   
   lcd_command(0x48);
   for (i=0;i<8;i++)  {  lcd_data(char2[i]); }
   
   lcd_command(0x50);
   for (i=0;i<8;i++)  {  lcd_data(char3[i]); }
   
   lcd_command(0x58);
   for (i=0;i<8;i++)  {  lcd_data(char4[i]); }
   while (true)
   {
      for (i = 0 ; i < 19 ; i++)
      {
         lcd_goto_xy(0,0);
         lcd_data("      BIEU TUONG APPLE");
         lcd_goto_xy(1,i); 
         lcd_data(0); 
         
         lcd_goto_xy(1,i+1); 
         lcd_data(1); 
     
         lcd_goto_xy(2,i); 
         lcd_data(2); 
         
         lcd_goto_xy(2,i+1); 
         lcd_data(3); 
         delay_ms(200);
         lcd_command(lcd_clear_display);
      }
      for (i = 18 ; i > 1 ; i--)
      {
         lcd_goto_xy(0,0);
         lcd_data("      BIEU TUONG APPLE");
         lcd_goto_xy(1,i-1); 
         lcd_data(0); 
         
         lcd_goto_xy(1,i); 
         lcd_data(1); 
     
         lcd_goto_xy(2,i-1); 
         lcd_data(2); 
         
         lcd_goto_xy(2,i); 
         lcd_data(3); 
         delay_ms(200);
         lcd_command(lcd_clear_display);
      }
   }
}
