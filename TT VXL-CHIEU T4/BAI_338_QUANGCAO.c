#include    <tv_pickit2_shift_1.c>
//!#include    <tv_pickit2_shift_1_proteus.c>
#include    <tv_pickit2_shift_32led_don.c> 
void main()
{
  set_up_port_ic_chot(); 
  while(true)
  {
    if (ttct_td==1)    sang_tat_32led(10,0);
    if (ttct_td==2)    sang_tat_dan_pst_32led(10,0);
    if (ttct_td==3)    sang_tat_dan_tsp_32led(10,0);
    if (ttct_td==4)    sang_tat_dan_ngoai_vao_32led(10,0);
    if (ttct_td==5)    sang_tat_dan_trong_ra_32led(10,0);
    if (ttct_td==6)    sang_don_pst_32led(10,0);
    if (ttct_td==7)    diem_sang_dich_trai_mat_dan_32led(10,0);
    if (ttct_td==8)    sang_don_tsp_32led(10,0);
    if (ttct_td==9)    diem_sang_dich_phai_mat_dan_32led(10,0);
    if (ttct_td==10)   sang_tat_dan_trai_sang_phai_2x16led(40,0); 
    if (ttct_td==11)   sang_tat_dan_phai_sang_trai_2x16led(40,0); 
    if (ttct_td==12)   diem_sang_di_chuyen_pst_32led(40,0);
    if (ttct_td==13)   diem_sang_di_chuyen_tsp_32led(40,0);
    if (ttct_td==14)   sang_don_tnt_32led(40,0);
    if (ttct_td==15)   sang_don_ttr_32led(40,0);
    if (ttct_td>15)    ttct_td=1; 
  xuat_4led_7doan_2so(ma7doan[ttct_td/10],ma7doan[ttct_td%10]);
  }
}
