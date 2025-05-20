//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c> 
signed int8  gio, phut, giay, bdn;
unsigned int8 giatri_mod;
#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
} 
void hien_thi_gia_tri_mod ( ) 
{
   lcd_command(0x8a); 
   lcd_data(giatri_mod+0x30);
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

void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0]= ma7doan [giay %10]; 
   led_7dq[1]= ma7doan [giay /10]; 
   led_7dq[3]= ma7doan [phut %10]; 
   led_7dq[4]= ma7doan [phut /10]; 
   led_7dq[6]= ma7doan [gio %10];
   led_7dq[7]= ma7doan [gio /10];
   if      (giatri_mod==1)  led_7dq[6]=led_7dq[6] & 0x7f; 
   else if (giatri_mod==2)  led_7dq[3]=led_7dq[3] & 0x7f; 
   else if (giatri_mod==3)  led_7dq[0]=led_7dq[0] & 0x7f;
}

void phim_mod() 
{
   if (!input(BT0)) 
   {
      delay_ms(20);
      if (!input(BT0))
      {
         if(giatri_mod<3)  giatri_mod++;
         else              giatri_mod=0;
         while(!input(BT0));
      }
   } 
}

void phim_up() 
{
   if (!input(BT1)) 
   {
      delay_ms(20);
      if (!input(BT1))
      {
         switch (giatri_mod)
         {
            case 1:  if (giay == 60) giay=0;
                     else
                     {
                        giay++;
                     }
                     break;
            
            case 2:  if (phut == 60) phut = 0;
                     else
                     {
                        phut++;

                     }

                     break;
            
            case 3:  if (gio == 24) gio=0;
                     else
                     {
                        gio++;
                     }
                     break;
            default: break;
         }
         while(!input(BT1));
      }
   }
}

void phim_dw() 
{
   if (!input(BT2)) 
   {
      delay_ms(20);
      if (!input(BT2))
      {
         switch (giatri_mod)
         {
            case 1:  if (giay == 0) giay = 59;
                     else
                     {
                        giay--;
                     }
                     break;
            
            case 2:  if (phut == 0) phut=59;
                     else
                     {
                        phut--;
                     }
                     break;
            
            case 3:  if (gio == 0) gio = 23;
                     else
                     {
                        gio--;
                     }
                     break;
            
            default: break;
         }
         while(!input(BT2));
      }
   }
} 

void nhap_nhay_con_tro() 
{
   switch (giatri_mod) 
   {
      case 1:  lcd_command(0x92);
               lcd_data("  ");
               break;
      case 2:  lcd_command(0x8f);
               lcd_data("  ");
               break;
      case 3:  lcd_command(0x8c);
               lcd_data("  ");
               break;
      default: break;
   }
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
    giatri_mod = 0;
    lcd_hienthi_dongho();
    while(true)
    {
         giai_ma_gan_cho_8led_quet(); 
         hien_thi_gia_tri_mod ( ) ;
         phim_mod(); 
         phim_up();  
         phim_dw();
        if    (bdn<10) 
        {
           hien_thi_8led_7doan_quet();
           if (bdn <5)
              nhap_nhay_con_tro();
           else
              lcd_hienthi_dongho(); 
        }
        else
        {
            bdn = bdn-10;
            giay++;
            lcd_hienthi_dongho();
        }
    }
}
