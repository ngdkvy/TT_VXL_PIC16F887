//!TT_SP = 0 => Pause
//!TT_SP = 1 => Start

//!TT_HT = 0 => Counter ben trai, SP ben phai
//!TT_HT = 1 => Nguoc lai

//!TT_DC = 0 => Dem len
//!TT_DC = 1 => Dem xuong

#include <tv_pickit2_shift_1.c>
//!#include <tv_pickit2_shift_1_proteus.c>
#include <tv_pickit2_shift_lcd.c>

unsigned int8    t0;
unsigned int8    donvi, chuc;
int1 TT_SP, TT_HT, TT_DC;

unsigned int8 dv_t0_lcd, ch_t0_lcd;

//khai bao nguyen ham - khai bao cac ham co trong chuong trinh
//khong quan tam den thu tu cua cac ham
void giai_ma_gan_cho_8led_quet_trai();
void giai_ma_gan_cho_8led_quet_phai();

void phim_SP()
{
   if (!input(BT0))
   {
      delay_ms(20);
      if (!input(BT0))
      {
         TT_SP= ~ TT_SP;
         while (!input(BT0));
      }
   }
} 
void phim_DC()
{
   if (!input(BT1))
   {
      delay_ms(20);
      if (!input(BT1))
      {
         TT_DC = ~ TT_DC;
         while (!input(BT1));
      }
   }
} 
void phim_HT()
{
   if (!input(BT2))
   {
      delay_ms(20);
      if (!input(BT2))
      {
         TT_HT = ~ TT_HT;
         while (!input(BT2));
      }
   }
} 

void  giai_ma_hien_thi (unsigned int16 tam)
{
   donvi = ma7doan[tam %10];
   chuc  = ma7doan[tam/10%10]; 
   if (chuc==0xc0)   chuc=0xff;
   
}

void giai_ma_gan_cho_8led_quet_phai() 
{         
    led_7dq[0] = ma7doan [t0 %10];                     
    led_7dq[1] = ma7doan [t0/10];  
    if(led_7dq[1] == 0xc0) led_7dq[1] = 0xff;
        
    led_7dq[6] = 0xFF;                     
    led_7dq[7] = 0xFF; 
}

void giai_ma_gan_cho_8led_quet_trai() 
{         
    led_7dq[6] = ma7doan [t0 %10];                     
    led_7dq[7] = ma7doan [t0/10];  
    if(led_7dq[7] == 0xc0) led_7dq[7] = 0xff;
    
    led_7dq[0] = 0xFF;                     
    led_7dq[1] = 0xFF; 
}

void GM_LCD() 
{ 
   dv_t0_lcd = t0%10 + 0x30; 
   ch_t0_lcd = t0/10%10 + 0x30;
   if(ch_t0_lcd == 0x30) ch_t0_lcd = 0x20; //32 = ' ' : khoang trang
} 

void HT_LCD() 
{ 
    lcd_goto_xy(0,0);      //hang 0, cot 0
    lcd_data("DEM SAN PHAM");
    
    lcd_goto_xy(1,9);   //xac dinh vi tri - hang 1, cot 18
    delay_us(20); 
    lcd_data(ch_t0_lcd); 
    lcd_data(dv_t0_lcd); 
} 

void main()
{
   set_up_port_ic_chot();
   
   //khoi tao counter 0
   setup_timer_0 (t0_ext_l_to_h | t0_div_1| t0_8_bit); 
   set_timer0(0);
  
   
   //khoi tao LCD
   setup_lcd(); 
//!   lcd_goto_xy(0,0); 
//!   lcd_data("dong ho:");   
//!   giay = 0; 
   
   //trang thai ban dau cua he thong
    TT_SP = TT_HT = TT_DC = 0;
   
   while(true)
   {
      t0=get_timer0();
      giai_ma_hien_thi (t0);
      
      //hien thi led quet
      //giai ma dat chung voi ham1 
      hien_thi_8led_7doan_quet();
      
      //!hien thi lcd
      gm_lcd();
      ht_lcd();
      
      //!Kiem tra phim nhan SP
      phim_SP();
      if (!TT_SP) 
         setup_timer_0(t0_off);
      else
         setup_timer_0 (t0_ext_l_to_h | t0_div_1| t0_8_bit); 
       
      //Kiem tra phim nhan HT
      phim_HT();
      if (!TT_HT)
      {
         xuat_4led_7doan_4so(chuc,donvi &0x7f, 0x92, 0x8c);
         giai_ma_gan_cho_8led_quet_trai();
      }
      else
      {
         xuat_4led_7doan_4so(0x92, 0x0c, chuc,donvi);
         giai_ma_gan_cho_8led_quet_phai();
      }
   
      //Kiem tra phim nhan DAO CHIEU
      phim_DC();
      //Xu ly dao chieu dem len, dem xuong
      if (!TT_DC)
         t0 = get_timer0();
      else 
         t0 = 4 - get_timer0();
      if ((t0 > 4) && (!TT_DC))
         t0 = set_timer0(1);
      if ((!t0) && (TT_DC))
         set_timer0(0);   
         
      
      
//!      delay_ms(200); //giam thoi gian thuc hien 1 chu ky
//!                     //de mo phong (giam toc do xu ly CPU)
   }
}

