#include <tv_pickit2_shift_1.c> 
//!#include <tv_pickit2_shift_1_proteus.c>

unsigned int8     j, solan=100; 
unsigned int16   lm35a;
unsigned int8 donvi, chuc, tram, ngan;
unsigned int8 tmax;

void  giai_ma_hien_thi ()
{
   donvi = ma7doan[lm35a %10];
   chuc  = ma7doan[lm35a/10%10]; 
   if (chuc==0xc0)   chuc=0xff;
   
   tram = ma7doan[tmax %10];
   ngan  = ma7doan[tmax/10%10]; 
   
   xuat_4led_7doan_4so(ngan, tram&0x7F, chuc, donvi);
}

void so_sanh_dk_den() 
{
   if (lm35a > tmax) 
   {
      triac_2_off();
      xuat_32led_don_4byte(0,  0,  0,  0xff);
   }
   else if (lm35a < tmax)
   {
      xuat_32led_don_4byte(0,  0,  0,  0);
   }
   if (lm35a < (tmax - 5)) 
      triac_2_on();
}

void doc_nd_lm35a() 
{
   set_adc_channel(0); 
   lm35a = 0;
   delay_ms(1);
   for (j=0; j<solan; j++) 
   {
      lm35a = lm35a + read_adc(); 
      delay_us(100);
   }
   lm35a = lm35a /2.046; 
   lm35a = lm35a /solan;
}

void phim_UP()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
         if (tmax < 60) 
            tmax ++;
         giai_ma_hien_thi ();
         while (!input(BT0));
      }
   }
} 

void phim_DW()
{
   if (!input(BT1))
   {
      delay_ms(20);
      if (!input(BT1))
      {
         if (tmax >35) 
            tmax --;
         giai_ma_hien_thi ();
         while (!input(BT1));
      }
   }
} 

void main() 
{
   set_up_port_ic_chot(); 
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0|vss_vdd );
   tmax = 35;
   giai_ma_hien_thi ();
   while(true)
   {
      phim_UP();
      phim_DW();
      doc_nd_lm35a();
      giai_ma_hien_thi ();
      so_sanh_dk_den();
   }
}
