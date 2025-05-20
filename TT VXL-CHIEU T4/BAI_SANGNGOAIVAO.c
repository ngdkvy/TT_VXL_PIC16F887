#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int16 yt, yp, savet, savep, runt, runp;
unsigned int8 i, j;

void sangdon()
{
   yt = 0; yp = 0;
   xuat_32led_don_2word(yt,yp);
   delay_ms(100);
   savet = 0; savep = 0;
   for (i = 0 ; i < 16 ; i++)
   {
      runt = 0x8000;
      runp = 0x01;
      for (j = i ; j < 16 ; j++)
      {
         yt = runt|savet;
         yp = runp|savep;
         xuat_32led_don_2word(yt,yp);
         delay_ms(100);
         runt = runt>>1;
         runp=runp<<1;
      }
      savet = yt; 
      savep = yp;
   }
}
void main()
{
   set_up_port_ic_chot();
   yt = 0; yp = 0;
   xuat_32led_don_2word(yt, yp);
   delay_ms(100);
   while (true)
   {
      sangdon();
   }
}
         
