#include <LCD1602A.h>
#define rs 2
#define rw 3
#define e 4
#define d0 5
#define d1 6
#define d2 7
#define d3 8
#define d4 9
#define d5 10
#define d6 11
#define d7 12
LCD1602A lcd(rs,rw,e,d0,d1,d2,d3,d4,d5,d6,d7);
//LCD1602A lcd(rs,e,d0,d1,d2,d3,d4,d5,d6,d7);
//LCD1602A lcd(rs,rw,e,d4,d5,d6,d7);
//LCD1602A lcd(rs,e,d4,d5,d6,d7);
/*1 = Doldur
 *0 = Doldurma
 *Not: lcd ekrana en fazla 8 tane karakter oluşturabilirsiniz. 8.'den sonra en başa dönerek yaptım bu uygulamayı.
 *Not2: Karakteri loop'ta oluşturursanız o karakteri basmak için konumunu ayarlamak zorundasınız. Yoksa basmaz.
 */
byte c[8] = { //ç harfi
  0b00000,  //     
  0b01110,  // *** 
  0b10000,  //*    
  0b10000,  //*    
  0b10001,  //*   *
  0b01110,  // *** 
  0b00000,  //     
  0b00100   //  *  
};
byte C[8] = { //Ç harfi
  0b01110,  // *** 
  0b10001,  //*   *
  0b10000,  //*    
  0b10000,  //*    
  0b10001,  //*   *
  0b01110,  // *** 
  0b00000,  //     
  0b00100   //  *  
};
byte g[8] = { //ğ harfi
  0b01110,  // *** 
  0b00000,  //     
  0b01111,  // ****
  0b10001,  //*   *
  0b10001,  //*   *
  0b01111,  // ****
  0b00001,  //    *
  0b01110   // *** 
};
byte G[8] = { //Ğ harfi
  0b01110,  // *** 
  0b00000,  //     
  0b01110,  // *** 
  0b10001,  //*   *
  0b10000,  //*    
  0b10111,  //* ***
  0b10001,  //*   *
  0b01111   // ****
};
byte i[8] = { //ı harfi
  0b00000,  //     
  0b00000,  //     
  0b00000,  //     
  0b01100,  // **  
  0b00100,  //  *  
  0b00100,  //  *  
  0b00100,  //  *  
  0b01110   // *** 
};
byte I[8] = { //İ harfi
  0b00100,  //  *  
  0b00000,  //     
  0b01110,  // *** 
  0b00100,  //  *  
  0b00100,  //  *  
  0b00100,  //  *  
  0b00100,  //  *  
  0b01110   // *** 
};
byte o[8] = { //ö harfi
  0b00000,  //     
  0b01010,  // * * 
  0b00000,  //     
  0b01110,  // *** 
  0b10001,  //*   *
  0b10001,  //*   *
  0b10001,  //*   *
  0b01110   // *** 
};
byte O[8] = { //Ö harfi
  0b01010,  // * * 
  0b00000,  //     
  0b01110,  // *** 
  0b10001,  //*   *
  0b10001,  //*   *
  0b10001,  //*   *
  0b10001,  //*   *
  0b01110   // *** 
};
byte s[8] = { //ş harfi
  0b00000,  //     
  0b01110,  // *** 
  0b10000,  //*    
  0b01110,  // *** 
  0b00001,  //    *
  0b11110,  //**** 
  0b00000,  //     
  0b00100   //  *  
};
byte S[8] = { //Ş harfi
  0b01111,  // ****
  0b10000,  //*    
  0b01110,  // *** 
  0b00001,  //    *
  0b00001,  //    *
  0b11110,  //**** 
  0b00000,  //     
  0b00100   //  *  
};
byte u[8] = { //ü harfi
  0b00000,  //     
  0b01010,  // * * 
  0b00000,  //     
  0b10001,  //*   *
  0b10001,  //*   *
  0b10001,  //*   *
  0b10011,  //*  **
  0b01101   // ** *
};
byte U[8] = { //Ü harfi
  0b01010,  // * * 
  0b00000,  //     
  0b10001,  //*   *
  0b10001,  //*   *
  0b10001,  //*   *
  0b10001,  //*   *
  0b10001,  //*   *
  0b01110   // *** 
};
void setup() {
  lcd.baslat(16, 2); //16 sütun 2 satır
  lcd.konum(0,1); //konumu alt baslangica ayarlıyor
  lcd.yazdir("cCgGiIoOsSuU"); //Türkçe karakterlerin zıt harfleri yazıyor
}
void loop() {
  lcd.satirTemizle(0); //bulunduğu satırı temizliyor
  lcd.karakterOlustur(0,c); //0 adresine "ç" harfini tanıt
  lcd.baslangic(); //yazacağımız yazının konumunu en başa çekiyor
  lcd.karakterYazdir(0); //oluşturduğumuz karakteri basıyor
  delay(500);
  lcd.satirTemizle(0); //bulunduğu satırı temizliyor
  lcd.karakterOlustur(1,C); //1 adresine "Ç" harfini tanıt
  lcd.konum(1,0); //yazının konumu bir yana kaydırıyor
  lcd.karakterYazdir(1); //oluşturduğumuz karakteri basıyor
  delay(500);
  lcd.satirTemizle(0); //bulunduğu satırı temizliyor
  lcd.karakterOlustur(2,g); //2 adresine "g" harfini tanıt
  lcd.konum(2,0); //yazının konumu bir yana kaydırıyor
  lcd.karakterYazdir(2); //oluşturduğumuz karakteri basıyor
  delay(500);
  lcd.satirTemizle(0); //bulunduğu satırı temizliyor
  lcd.karakterOlustur(3,G); //3 adresine "Ğ" harfini tanıt
  lcd.konum(3,0); //yazının konumu bir yana kaydırıyor
  lcd.karakterYazdir(3); //oluşturduğumuz karakteri basıyor
  delay(500);
  lcd.satirTemizle(0); //bulunduğu satırı temizliyor
  lcd.karakterOlustur(4,i); //4 adresine "ı" harfini tanıt
  lcd.konum(4,0); //yazının konumu bir yana kaydırıyor
  lcd.karakterYazdir(4); //oluşturduğumuz karakteri basıyor
  delay(500);
  lcd.satirTemizle(0); //bulunduğu satırı temizliyor
  lcd.karakterOlustur(5,I); //5 adresine "İ" harfini tanıt
  lcd.konum(5,0); //yazının konumu bir yana kaydırıyor
  lcd.karakterYazdir(5); //oluşturduğumuz karakteri basıyor
  delay(500);
  lcd.satirTemizle(0); //bulunduğu satırı temizliyor
  lcd.karakterOlustur(6,o); //6 adresine "ö" harfini tanıt
  lcd.konum(6,0); //yazının konumu bir yana kaydırıyor
  lcd.karakterYazdir(6); //oluşturduğumuz karakteri basıyor
  delay(500);
  lcd.satirTemizle(0); //bulunduğu satırı temizliyor
  lcd.karakterOlustur(7,O); //7 adresine "Ö" harfini tanıt
  lcd.konum(7,0); //yazının konumu bir yana kaydırıyor
  lcd.karakterYazdir(7); //oluşturduğumuz karakteri basıyor
  delay(500);
  lcd.satirTemizle(0); //bulunduğu satırı temizliyor
  lcd.karakterOlustur(0,s); //0 adresini "ş" harfi ile değiştir
  lcd.konum(8,0); //yazının konumu bir yana kaydırıyor
  lcd.karakterYazdir(0); //oluşturduğumuz karakteri basıyor
  delay(500);
  lcd.satirTemizle(0); //bulunduğu satırı temizliyor
  lcd.karakterOlustur(1,S); //1 adresini "Ş" harfi ile değiştir
  lcd.konum(9,0); //yazının konumu bir yana kaydırıyor
  lcd.karakterYazdir(1); //oluşturduğumuz karakteri basıyor
  delay(500);
  lcd.satirTemizle(0); //bulunduğu satırı temizliyor
  lcd.karakterOlustur(2,u); //2 adresini "ü" harfi ile değiştir
  lcd.konum(10,0); //yazının konumu bir yana kaydırıyor
  lcd.karakterYazdir(2); //oluşturduğumuz karakteri basıyor
  delay(500);
  lcd.satirTemizle(0); //bulunduğu satırı temizliyor
  lcd.karakterOlustur(3,U); //3 adresini "Ü" harfi ile değiştir
  lcd.konum(11,0); //yazının konumu bir yana kaydırıyor
  lcd.karakterYazdir(3); //oluşturduğumuz karakteri basıyor
  delay(500);
}
