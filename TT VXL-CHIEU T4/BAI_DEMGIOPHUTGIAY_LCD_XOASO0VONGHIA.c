//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c> 

signed int8 gio, phut, giay, i, bdn; 
unsigned int8 ch_to, dv_to, ng_to, tr_to, ngan_to, tram_to;

#int_timer1  

void interrupt_timer1() 
{
   
   bdn++;
   set_timer1 (3036);
}

void giai_ma_gan_cho_8led_quet ()  
{
   led_7dq[0] = ma7doan [giay % 10];
   led_7dq[1] = ma7doan [giay / 10];
   led_7dq[3] = ma7doan [phut % 10];
   led_7dq[4] = ma7doan [phut / 10];
   led_7dq[6] = ma7doan [gio % 10];
   led_7dq[7] = ma7doan [gio / 10];
}

void xu_ly_so_to_xoa_0_vo_nghia(unsigned int16 so, tam, tim)
{
   
   ch_to = so / 10;
   dv_to = so % 10;
   if (ch_to == 0) ch_to = 10;
   
   ng_to = tam / 10;
   tr_to = tam % 10;
   if (ng_to == 0) ng_to = 10;
   
   ngan_to = tim / 10;
   tram_to = tim % 10;
   
   if (ngan_to == 0) ngan_to = 10;
      
}
void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy (x1, y1);
   for (i = 0; i < 6; i++)
   {
      if (i == 3) lcd_goto_xy (x1 + 1, y1);
      lcd_data (lcd_so_x[lcd_so][i]) ;
   }
}

 void main ()
 {
    
    set_up_port_ic_chot ();
    setup_lcd ();
    setup_timer_1 (t1_internal|t1_div_by_8);
    set_timer1 (3036);
    enable_interrupts (global);
    enable_interrupts (int_timer1);
    gio = 0;
    phut = 5;
    giay = 0;
    bdn = 0;
    lcd_command (0x40);
    for (i = 0; i < 64; i++) {lcd_data (lcd_ma_8doan[i]); }
    
    while (true)
    {
       giai_ma_gan_cho_8led_quet ();

       if (bdn < 10)
          hien_thi_8led_7doan_quet ();

       else
       {
          
          bdn = bdn - 10;
          giay++;

          if (giay == 60)
          {
             giay = 0;
             phut++;

             if (phut == 60)
             {
                phut = 0;
                gio++;
                
                if (gio == 24)
                   gio = 0;
             }
          }

          xu_ly_so_to_xoa_0_vo_nghia (gio, phut, giay);
          lcd_hienthi_so_z_toado_xy (ch_to, 2, 0);
          lcd_hienthi_so_z_toado_xy (dv_to, 2, 3);
          
          lcd_hienthi_so_z_toado_xy (ng_to, 2, 7);
          lcd_hienthi_so_z_toado_xy (tr_to, 2, 10);
          
          lcd_hienthi_so_z_toado_xy (ngan_to, 2, 14);
          lcd_hienthi_so_z_toado_xy (tram_to, 2, 17);
       }

    }
 }
