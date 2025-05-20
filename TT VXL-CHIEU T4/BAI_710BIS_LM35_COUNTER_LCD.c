//!LCD:
//!    dong    1: LM35a       LM35b
//!    dong    2: Counter
//!    dong 3, 4: LM35a       LM35b
//!8 LED quet:
//!               LM35a       LM35b
//!4 LED 7 doan: gia tri dem. gia tri nhiet do

//!BT0: tang gia tri dem
//!BT1: giam gia tri dem
//!BT2: tang gia tri nhiet do
//!BT3: giam gia tri nhiet do

//!#include <tv_pickit2_shift_1.c>
#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>

unsigned int8     j, solan = 100; 
unsigned int16    lm35a, lm35b;
unsigned int8     donvi_lm35a, chuc_lm35a, donvi_lm35b, chuc_lm35b, donvi_counter, chuc_counter;
unsigned int8     donvi_t0_max, chuc_t0_max, donvi_nd_max, chuc_nd_max;
signed int8       i;
unsigned int8     t0_max, t0;
unsigned int8     nd_max;

void GM_LCD_nhietdo()
{
   donvi_lm35a     = lm35a%10+0x30;
   chuc_lm35a      = lm35a/10+0x30; 
   donvi_lm35b     = lm35b%10+0x30;
   chuc_lm35b      = lm35b/10+0x30;
   if (chuc_lm35a  == 0x30)       chuc_lm35a = 0x20;
   if (chuc_lm35b  == 0x30)       chuc_lm35b = 0x20;
   
   lcd_goto_xy(0,0);
   lcd_data(chuc_lm35a); 
   lcd_data(donvi_lm35a); 
   lcd_goto_xy(0,16);
   lcd_data(chuc_lm35b); 
   lcd_data(donvi_lm35b); 
}

void GM_LCD_counter()
{
   donvi_counter    = t0%10+0x30;
   chuc_counter     = t0/10+0x30;
   if (chuc_counter == 0x30)   chuc_counter   = 0x20;
   
   lcd_goto_xy(1,0);
   lcd_data(chuc_counter); 
   lcd_data(donvi_counter); 
}


void lcd_hienthi_so_z_toado_xy(signed int8 lcd_so, x1, y1)
{
   lcd_goto_xy(x1,y1); 
   for (i=0;i<6;i++)
   {
      if (i==3)   lcd_goto_xy(x1+1,y1); 
      lcd_data(lcd_so_x[lcd_so][i]);
   }
}

void giai_ma_gan_cho_8led_quet()
{
   led_7dq[0] = ma7doan [lm35a %10];
   led_7dq[1] = ma7doan [lm35a/10];
   
   led_7dq[6] = ma7doan [lm35b %10];
   led_7dq[7] = ma7doan [lm35b /10];
   
   if (led_7dq[1] == 0xc0) led_7dq[1] = 0xff;
   if (led_7dq[7] == 0xc0) led_7dq[7] = 0xff;
}

void  giai_ma_hien_thi ()
{
   donvi_t0_max = ma7doan[t0_max%10];
   chuc_t0_max  = ma7doan[t0_max/10]; 
   donvi_nd_max = ma7doan[nd_max%10];
   chuc_nd_max  = ma7doan[nd_max/10]; 
   if (chuc_t0_max == 0xc0) chuc_t0_max = 0xff;
   xuat_4led_7doan_4so(chuc_nd_max, donvi_nd_max&0x7f, chuc_t0_max, donvi_t0_max);
}

void phim_UP_counter()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
         if (t0_max < 99) 
            t0_max ++;
         giai_ma_hien_thi ();
         while (!input(BT0));
      }
   }
} 

void phim_DW_counter()
{
   if (!input(BT1))
   {
      delay_ms(20);
      if (!input(BT1))
      {
         if (t0_max > 0) 
            t0_max --;
         giai_ma_hien_thi ();  
         while (!input(BT1));
      }
   }
} 

void phim_UP_nhietdo()
{
   if (!input(BT2))
   {
      delay_ms(20);
      if (!input(BT2))
      {
         if (nd_max < 60) 
            nd_max ++;
         giai_ma_hien_thi ();  
         while (!input(BT2));
      }
   }
} 

void phim_DW_nhietdo()
{
   if (!input(BT3))
   {
      delay_ms(20);
      if (!input(BT3))
      {
         if (nd_max > 35) 
            nd_max --;
         giai_ma_hien_thi ();  
         while (!input(BT3));
      }
   }
} 

void so_sanh_dk_den() 
{
   if ((lm35a > nd_max) && (lm35b > nd_max)) 
   {
      triac_2_off();
      xuat_32led_don_4byte(0,  0,  0,  0xff);
   }
   if ((lm35a < nd_max) && (lm35b < nd_max)) 
   {
      triac_2_on();
      xuat_32led_don_4byte(0,  0,  0,  0);
   }
}

void doc_nd_lm35a() 
{
   set_adc_channel(0); 
   lm35a = 0;
   delay_ms(1);
   for (j=0; j<solan; j++) 
   {
      lm35a = lm35a + read_adc(); 
      hien_thi_8led_7doan_quet();
   }
   lm35a = lm35a /2.046; 
   lm35a = lm35a /solan;
}

void doc_nd_lm35b() 
{
   set_adc_channel(1); 
   delay_ms(1);
   lm35b = 0;
   for (j=0; j<solan; j++) 
   {
      lm35b = lm35b + read_adc();
      hien_thi_8led_7doan_quet();
   }
   lm35b = lm35b /2.046; 
   lm35b = lm35b /solan;
}

void main() 
{
   set_up_port_ic_chot(); 
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an1|vss_vdd );
   setup_lcd();

   lcd_command(0x40);
   for (i=0;i<64;i++)  {  lcd_data(lcd_ma_8doan[i]); }
   
   t0_max = 9;
   giai_ma_hien_thi ();
   nd_max = 30;
   setup_timer_0 (t0_ext_l_to_h | t0_div_1); 
   set_timer0(0);
   t0 = 0;
   
   while(true)
   {
      phim_UP_counter();
      phim_DW_counter();
      phim_UP_nhietdo();
      phim_DW_nhietdo();
      t0 = get_timer0();
      if (t0 >= t0_max) 
      {
         set_timer0(0);
         t0 = 0;
      }
      doc_nd_lm35a();
      doc_nd_lm35b();
      so_sanh_dk_den();
      GM_LCD_nhietdo();
      GM_LCD_counter();
      
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet(); 
      giai_ma_hien_thi ();
      
      lcd_hienthi_so_z_toado_xy(lm35a/10, 2, 0);
      lcd_hienthi_so_z_toado_xy(lm35a%10, 2, 3);
      lcd_hienthi_so_z_toado_xy(lm35b/10, 2, 7);
      lcd_hienthi_so_z_toado_xy(lm35b%10, 2, 10);
   }
}
