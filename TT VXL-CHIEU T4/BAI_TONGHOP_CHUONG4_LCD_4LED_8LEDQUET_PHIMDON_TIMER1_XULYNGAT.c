//!BT tong hop: Counter timer0, Timer1 dem thoi gian, Xu ly ngat
//!1. Hien thi gia tri Counter va chu SP len 4 led 7 doan (co dau cham o giua)
//!   Ban dau, 2 led trai hien thi gia tri Counter, 2 led phai hien thi chu SP
//!a. Hien thi, co xoa so 0 vo nghia
//!b. 1 nut nhan START/PAUSE (BT0)
//!c. 1 nut nhan dao chieu dem (BT1)
//!d. 1 nut nhan doi ben hien thi (BT2)
//!2. Hien thi gia tri Counter va dem giay len 8 led 7 doan quet
//!Led ben trai: dem san pham
//!Led ben phai: dem giay
//!Xu ly cau a, b, c, d giong cau 1
//!e. 1 nut nhan doi chieu dem giay (BT2)
//!3. Hien thi len LCD
//!a.  Hang 1: Gia tri cai (gia tri dem toi da)
//!     Hang 2: Gia tri dem (dem san pham)
//!     Hang 3: Dem giay (Timer1, Xu ly ngat)
//!   Hang 4: Hien thi phim duoc nhan



//!BT0
//!TT_SP = 0 => Pause
//!TT_SP = 1 => Start

//!BT1
//!TT_DC = 0 => Dem len
//!TT_DC = 1 => Dem xuong

//!BT2
//!TT_HT = 0 => Counter ben trai, SP ben phai
//!TT_HT = 1 => Nguoc lai

//!BT3
//!TT_DG = 0 => Giay dem len
//!TT_DG = 1 => Giay dem xuong

#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c> 

unsigned int8    t0, tmax;
unsigned int8    donvi, chuc;
unsigned int8    dv, ch, tr, ng, tri, ctr;
signed int8       giay, bdn;
int1 TT_SP, TT_HT, TT_DC, TT_DG;

//!Chuong trinh ngat
#int_timer1
void interrupt_timer1()
{
    bdn++;
    set_timer1(3036);
} 

//!Phim nhan Start/Pause + in ra LCD phim BT0 duoc nhan
void phim_SP()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
//!         Dao trang thai bien
         TT_SP= ~ TT_SP;
         
//!         Thong bao nut duoc nhan
         lcd_goto_xy(3,14);  
         lcd_data("BT0"); 
         
         while (!input(BT0));
      }
   }
} 

//!Phim nhan dao chieu + in ra LCD phim BT1 duoc nhan
void phim_DC()
{
   if (!input(BT1))
   {
      delay_ms(20);
      if (!input(BT1))
      {
//!         Dao trang thai bien
         TT_DC = ~ TT_DC;
         
//!         Thong bao nut duoc nhan         
         lcd_goto_xy(3,14);  
         lcd_data("BT1"); 
         while (!input(BT1));
      }
   }
} 

//!Phim nhan dao hien thi + in ra LCD phim BT2 duoc nhan
void phim_HT()
{
   if (!input(BT2))
   {
      delay_ms(20);
      if (!input(BT2))
      {
//!         Dao trang thai bien
         TT_HT = ~ TT_HT;
         
//!         Thong bao nut duoc nhan
         lcd_goto_xy(3,14);  
         lcd_data("BT2"); 
         while (!input(BT2));
      }
   }
} 

//!Phim nhan dao chieu dem giay + in ra LCD phim BT3 duoc nhan
void phim_DG()
{
   if (!input(BT3))
   {
      delay_ms(20);
      if (!input(BT3))
      {
//!         Dao trang thai bien
         TT_DG = ~ TT_DG;
         
//!         Thong bao nut duoc nhan
         lcd_goto_xy(3,14);  
         lcd_data("BT3"); 
         while (!input(BT3));
      }
   }
} 

//!Module 4 led 7 doan: In ra gia tri counter va chu SP + xoa so 0 vo nghia + dao ben hien thi 
void  giai_ma_hien_thi (unsigned int16 tam)
{
//!   Luu so de hien thi ra LED 
   donvi = ma7doan[tam %10];
   chuc  = ma7doan[tam/10%10]; 
   
//!   Xoa so 0 vo nghia
   if (chuc==0xc0)   chuc=0xff;
   
//!   Xu ly dao ben hien thi
   if (!TT_HT)
      xuat_4led_7doan_4so(chuc,donvi &0x7f, 0x92, 0x8c);
   else 
      xuat_4led_7doan_4so(0x92, 0x0c, chuc,donvi);
}

//!Module 8 led 7 doan quet: In ra gia tri counter va dem giay + xoa so 0 vo nghia + dao ben hien thi
void giai_ma_gan_cho_8led_quet()
{
//!   Xu ly dao ben hien thi
   if (!TT_HT)
   {
//!   Luu so de hien thi ra LED 
//!   Hien thi dem giay
      led_7dq[0] = ma7doan [giay %10];
      led_7dq[1] = ma7doan [giay/10];
//!   Hien thi dem san pham
      led_7dq[6] = ma7doan [t0 %10];
      led_7dq[7] = ma7doan [t0/10];
      

      if (led_7dq[1] == 0xc0) led_7dq[1] = 0xff;
      if (led_7dq[7] == 0xc0) led_7dq[7] = 0xff;
   }
   else
   {
//!   Luu so de hien thi ra LED 
//!   Hien thi dem giay
      led_7dq[6] = ma7doan [giay %10];
      led_7dq[7] = ma7doan [giay/10];
//!   Hien thi dem san pham
      led_7dq[0] = ma7doan [t0 %10];
      led_7dq[1] = ma7doan [t0/10];
      
//!   Xoa so 0 vo nghia      
      if (led_7dq[7] == 0xc0) led_7dq[7] = 0xff;
      if (led_7dq[1] == 0xc0) led_7dq[1] = 0xff;
   }
}

//!Ma tran phim: Tang, giam gia tri cai, Reset gia tri cai + gia tri Counter

void GM_LCD()
{
//!   Luu so de hien thi ra LCD 
//!   Hien thi gia tri cai
   dv = tmax%10+0x30;
   ch = tmax/10+0x30; 
//!   Xoa so 0 vo nghia
   if (ch == 0x30)   ch = 0x20;
   
//!   Luu so de hien thi ra LCD 
//!   Hien thi gia tri dem  
   tr = t0%10+0x30;
   ng = t0/10+0x30; 
//!   Xoa so 0 vo nghia
   if (ng == 0x30)   ng = 0x20;
 
//!   Luu so de hien thi ra LCD 
//!   Hien thi giay dang dem
   tri = giay%10+0x30;
   ctr = giay/10+0x30; 
//!   Xoa so 0 vo nghia
   if (ctr == 0x30)   ctr = 0x20;
}
void hienthi_lcd()
{
   lcd_goto_xy(0,0);
   lcd_data("Gia tri cai: "); 
   lcd_goto_xy(0,15);
   lcd_data(ch); 
   lcd_data(dv);
   
   lcd_goto_xy(1,0);
   lcd_data("Gia tri dem: "); 
   lcd_goto_xy(1,15);
   lcd_data(ng); 
   lcd_data(tr);
   
   lcd_goto_xy(2,0);
   lcd_data("Dem giay: "); 
   lcd_goto_xy(2,15);
   lcd_data(ctr); 
   lcd_data(tri);
   
   lcd_goto_xy(3,0);
   lcd_data("Phim nhan: "); 
}
void main()
{
//!   Khoi tao ban dau + LCD
   set_up_port_ic_chot();
   setup_lcd();
   
//!   Cai dat timer0
   setup_timer_0 (t0_ext_l_to_h | t0_div_1| t0_8_bit); 
   set_timer0(0);
   
//!   Cai dat Timer1 + Xu ly ngat
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   enable_interrupts(global); 
   enable_interrupts(int_timer1); 
   
//!   Khoi tao gia tri ban dau
   giay = bdn = 0;
   TT_SP = TT_HT = TT_DC = TT_DG = 0;
   t0 = 0;
   tmax = 99;
   
//!Hien thi ra LCD trang thai ban dau
   GM_LCD();
   hienthi_lcd();
   
   while(true)
   {
//!   Doc gia tri Counter
      t0 = get_timer0();
      
//!   Kiem tra phim nhan
      phim_SP();
      phim_HT();
      phim_DC();
      phim_DG();
      
//!   Doc gia tri ma tran phim + Kiem tra ma tran phim co duoc nhan khong? + Goi ham xu ly yeu cau lien quan
      GM_LCD();
      hienthi_lcd();
//!   Xu ly Start/Pause
      if (!TT_SP) 
         setup_timer_0(t0_off);
      else
         setup_timer_0 (t0_ext_l_to_h | t0_div_1| t0_8_bit); 
       
//!      Xu ly dao chieu dem len, dem xuong
      if (!TT_DC)
         t0 = get_timer0();
      else 
         t0 = tmax - get_timer0();
      if ((t0 > tmax) && (!TT_DC))
         t0 = set_timer0(1);
      if ((!t0) && (TT_DC))
         set_timer0(0);   
         
//!      Hien len module 4 LED 7 doan + 8 led 7 doan quet
      giai_ma_hien_thi (t0);
      giai_ma_gan_cho_8led_quet();
      hien_thi_8led_7doan_quet(); 
      
//!      Xu ly phan dem giay cua timer1
      if    (bdn<10)    hien_thi_8led_7doan_quet(); 
      else
      {
         bdn = bdn-10;
         if (!TT_DG)    giay++;
         else           giay --;
         if (giay == 60)  giay = 0;
         if (giay < 0)  giay = 59;
         hien_thi_8led_7doan_quet(); 
      }
      
      GM_LCD();
      hienthi_lcd();
   }
}


