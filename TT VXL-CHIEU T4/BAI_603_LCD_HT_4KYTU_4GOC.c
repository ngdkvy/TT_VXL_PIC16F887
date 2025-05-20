#include <tv_pickit2_shift_1.c> 
#include <tv_pickit2_shift_lcd.c> 

void main()
{
    set_up_port_ic_chot();
    setup_lcd();

   //!xem sach trang 130
    lcd_command(0x80); 
    lcd_data("A");

    lcd_command(0X93);
    lcd_data("B");
    
    lcd_command(0XD4);
    lcd_data("C"); 
    
    lcd_command(0XE7);
    lcd_data("D");

    while(true);
}
