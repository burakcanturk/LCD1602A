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
String kelime="Merhaba Dunya"; //kelimemiz
void setup() {
  lcd.baslat(16,2); //16 sütun 2 satır
  lcd.yazdir(kelime); //kaydırılacak yazı
  delay(1000);
}
void loop() {
  for (int kaydirma=0; kaydirma<kelime.length(); kaydirma++) { //sola ne kadar kayacağımızı ayarlıyoruz (kelime değişkeni 13 karakter; yani en sağa kadar kaydırıyoruz)
    lcd.solaKaydir(); //yazı sola kayar
    delay(150);
  }
  for (int kaydirma=0; kaydirma<kelime.length()+16; kaydirma++) { //sağa ne kadar kayacağımızı ayarlıyoruz (kelime değişkeni 13 karakter; yani az önce en sağa kaydırdığımız için normal sütun sayısıyla birlikte en sola kadar kaydırıyoruz)
    lcd.sagaKaydir(); //yazı sağa kayar
    delay(150);
  }
  for (int kaydirma=0; kaydirma<16; kaydirma++) { //sola ne kadar kayacağımızı ayarlıyoruz (kelime değişkeni en başta durduğu için onu en sağa direk kaydırıyoruz)
    lcd.solaKaydir(); //yazı sola kayar
    delay(150);
  }
}
