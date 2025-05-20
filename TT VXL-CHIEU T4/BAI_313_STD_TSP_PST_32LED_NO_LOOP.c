#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
unsigned int32 y;
unsigned int8 TT_CT;
unsigned int16 k;
void main()
{
   set_up_port_ic_chot () ;
   TT_CT = 1;
   y = 0;
   xuat_32led_don_1dw (y) ;
   delay_ms (100) ;
   while (true)
   {
      if (TT_CT == 1) //SD TSP
      {
         if (k < 32)
         {
            y = (y>>1)|0x80000000;
            xuat_32led_don_1dw (y) ;
            delay_ms (100) ;
            k++;
         }

         else
         {
            k = 0;
            TT_CT ++;
         }
      }
      if (TT_CT == 2) //TD TSP
      {
         if (k < 32)
         {
            y = y>>1;
            xuat_32led_don_1dw (y) ;
            delay_ms (100) ;
            k++;
         }

         else
         {
            k = 0;
            TT_CT ++;
         }
      }
      if (TT_CT == 3) //SD PST
      {
         if (k < 32)
         {
            y = (y<<1)|0x01;
            xuat_32led_don_1dw (y) ;
            delay_ms (100) ;
            k++;
         }

         else
         {
            k = 0;
            TT_CT++;
         }
      }

      if (TT_CT == 4)//TD PST
      {
         if (k < 32)
         {
            y = (y<<1);
            xuat_32led_don_1dw (y) ;
            delay_ms (100) ;
            k++;
         }

         else
         {
            k = 0;
            TT_CT = 1;
         }
      }
   }
}


