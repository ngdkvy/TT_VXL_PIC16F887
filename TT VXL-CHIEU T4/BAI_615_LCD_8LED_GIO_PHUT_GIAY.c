//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c> 
signed int8  gio, phut, giay, bdn;

#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
} 

void lcd_hienthi_dongho()
{
   lcd_goto_xy(0,12);
   lcd_data(gio/10+0x30); lcd_data(gio%10+0x30); 
   lcd_data(' ');
   lcd_data(phut/10+0x30); lcd_data(phut%10+0x30); 
   lcd_data(' ');
   lcd_data(giay/10+0x30); lcd_data(giay%10+0x30);
}
void XULY()
{
   if (giay==60)
   {
      giay=0;  phut++;
      if (phut==60) 
      {
         phut=0;
         gio++;
         if (gio==24) 
            gio=0;
      }
   }
}
void phim_GIAY()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
         giay++;
         XULY();
         while (!input(BT0));
      }
   }
} 
void phim_PHUT()
{
   if (!input(BT1))
   {
      delay_ms(20);
      if (!input(BT1))
      {
         phut++;
         if (phut==60) 
         {
            phut=0;
            gio++;
            if (gio==24) 
               gio=0;
         }
         while (!input(BT1));
      }
   }
} 
void phim_GIO()
{
   if (!input(BT2))
   {
      delay_ms(20);
      if (!input(BT2))
      {
         gio++;
         if (gio==24) 
            gio = phut = giay = 0;
         while (!input(BT2));
      }
   }
} 
void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0]= ma7doan [giay %10]; 
   led_7dq[1]= ma7doan [giay /10]; 
   led_7dq[3]= ma7doan [phut %10]; 
   led_7dq[4]= ma7doan [phut /10]; 
   led_7dq[6]= ma7doan [gio %10];
   led_7dq[7]= ma7doan [gio /10]; 
}

void main()
{
    set_up_port_ic_chot();
    setup_lcd();
    setup_timer_1(t1_internal | t1_div_by_8);
    set_timer1(3036);
    enable_interrupts(global); 
    enable_interrupts(int_timer1); 
    gio = phut = giay = 0;
    bdn=0;
    lcd_hienthi_dongho();
    while(true)
    {
        giai_ma_gan_cho_8led_quet(); 
        if    (bdn<10) 
           hien_thi_8led_7doan_quet();
        else
        {
            bdn = bdn-10;
            giay++;
            lcd_hienthi_dongho();
            XULY();
        }
    }
}
