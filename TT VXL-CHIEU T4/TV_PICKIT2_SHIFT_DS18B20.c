#DEFINE     TOUCH_PIN PIN_A5
#INCLUDE    <TOUCH.c>
#DEFINE       SKIP_ROM              0xCC
#DEFINE       CONVERT_T             0x44
#DEFINE       READ_SCRATCHPAD       0xBE
#DEFINE       WRITE_SCRATCHPAD      0x4E
#DEFINE       COPY_SCRATCHPAD       0x48    
UNSIGNED INT8     DS18AL, DS18AH, DS18A_TAM;
UNSIGNED INT16    DS18A;
unsigned int8     nguyen;
unsigned int16    tp;

VOID  KHOI_TAO_DS18B20()
{                         
      TOUCH_PRESENT();
      TOUCH_WRITE_BYTE(SKIP_ROM);      
      TOUCH_WRITE_BYTE(WRITE_SCRATCHPAD);    
      TOUCH_WRITE_BYTE(0x0);       // ghi 2 byte rong
      TOUCH_WRITE_BYTE(0x0);       //
//!      TOUCH_WRITE_BYTE(0x1F);      //Cau hinh do phan giai 9 bit
//!      TOUCH_WRITE_BYTE(0x3F);      //Cau hinh do phan giai 10 bit
      TOUCH_WRITE_BYTE(0x5F);      //Cau hinh do phan giai 11 bit
//!      TOUCH_WRITE_BYTE(0x7F);      //Cau hinh do phan giai 12 bit

      TOUCH_PRESENT();
      TOUCH_WRITE_BYTE(SKIP_ROM);      
      TOUCH_WRITE_BYTE(COPY_SCRATCHPAD); 
}
VOID  DOC_GIATRI_DS18B20()
{ 
      TOUCH_WRITE_BYTE(SKIP_ROM);
      TOUCH_WRITE_BYTE (CONVERT_T);   
      TOUCH_PRESENT();
      TOUCH_WRITE_BYTE(SKIP_ROM);
      TOUCH_WRITE_BYTE(READ_SCRATCHPAD);  
      DS18AL = TOUCH_READ_BYTE();
      DS18AH = TOUCH_READ_BYTE();      
      DS18A  =  MAKE16(DS18AH,DS18AL);       
      nguyen = ds18a >> 4;
//!      tp     = ds18a & 0x0ff; //so nguyen
//!      tp     = (ds18a & 0x000f) * 10/16; //lay 1 so thap phan
//!      tp     = (ds18a & 0x000f) * 100/16; //lay 2 so thap phan
      tp     = (ds18a & 0x000f) * 1000/16; //lay 3 so thap phan
//!      tp     = (ds18a & 0x000f) * 10000/16; //lay 4 so thap phan
}
            

