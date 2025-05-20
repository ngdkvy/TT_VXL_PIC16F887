#include <tv_pickit2_shift_1.c> 

#define nd_tren  40
#define nd_duoi  35 

unsigned int8     j, solan = 100; 
unsigned int16   lm35a, lm35b;
unsigned int8 donvi, chuc, tram, ngan;

void so_sanh_dk_den() 
{
   if ((lm35a<nd_duoi) && (lm35b<nd_duoi))
      triac_2_on();
   if ((lm35a>nd_tren) | (lm35b>nd_tren))
   {
      triac_2_off();
      xuat_32led_don_4byte(0,  0,  0,  0xff);
   }
   else if ((lm35a<nd_tren) && (lm35b<nd_tren))
   {
      xuat_32led_don_4byte(0,  0,  0,  0);
   }

}

void  giai_ma_hien_thi (unsigned int16 Tb, unsigned int16 Ta)
{
   donvi = ma7doan[Ta %10];
   chuc  = ma7doan[Ta/10%10]; 
   if (chuc==0xc0)   chuc=0xff;
   
   tram = ma7doan[Tb %10];
   ngan  = ma7doan[Tb/10%10]; 
   if (ngan==0xc0)   ngan=0xff;
   
   xuat_4led_7doan_4so(ngan, tram&0x7f, chuc, donvi);
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

void doc_nd_lm35b() 
{
   set_adc_channel(1); 
   delay_ms(1);
   lm35b = 0;
   for (j=0; j<solan; j++) 
   {
      lm35b = lm35b + read_adc(); 
      delay_us(100);
   }
   lm35b = lm35b /2.046; 
   lm35b = lm35b /solan;
}

void main() 
{
   set_up_port_ic_chot(); 
   setup_adc(adc_clock_div_32); 
   setup_adc_ports(an0_to_an1|vss_vdd );
   
   while(true)
   {
      doc_nd_lm35a();
      doc_nd_lm35b();
      so_sanh_dk_den();
      giai_ma_hien_thi (lm35b, lm35a);
   }
}
