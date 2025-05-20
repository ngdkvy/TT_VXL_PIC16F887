#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_32led_don.c>
signed ttct = 1;

void phim_up()
{
   if (!input(BT1) && (ttct < 7))
   {
      delay_ms(10);
      if (!input(BT1))
      {
         ttct++;
         while (!input(BT1));
      }
   }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void phim_dw()
{
   if (!input(BT2) && (ttct > 1))
   {
      delay_ms(10);
      if (!input(BT2))
      {
         ttct--;
         while (!input(BT2));
      }
   }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void phim_clr()
{
   if (!input(x) && (ttct > 1))
   {
      ttct = 1;
      reset_toan_bo_bien();
   }
}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void main()
{
   set_up_port_ic_chot();
   set_tris_b(0x3c);
   while (true)
   {
      xuat_4led_7doan_1so(ma7doan[ttct]);
      if (ttct == 1) sang_tat_32led(10,0);
      if (ttct == 2) sang_tat_dan_pst_32led(10,0);
      if (ttct == 3) sang_tat_dan_tsp_32led(10,0);
      if (ttct == 4) sang_tat_dan_ngoai_vao_32led(10,0);
      if (ttct == 5) sang_tat_dan_trong_ra_32led(10,0);
      if (ttct == 6) sang_don_pst_32led(10,0);
      if (ttct == 7) sang_don_tsp_32led(10,0);
      phim_dw();
      phim_up();
      phim_clr();
   }
}
