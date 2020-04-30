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
String deger="";
void setup() {
  lcd.baslat(16,2); //16 sütun 2 satır
  Serial.begin(9600); //Seri port başlatma
}
void loop() {
  if (Serial.available()>0) { //Serial.available()=yazıdaki karakter uzunluğu
    delay(100);
    deger=""; //daha önce başka bir kelime girmiş olabiliriz diye içini boşaltıyoruz
    lcd.temizle(); //boş ekrana yazsın
    lcd.baslangic(); //başlangıç noktasından yazsın
    while (Serial.available() > 0) {
      char karakter=Serial.read(); //girdiğimiz yazının her harfini okuyor. (Serial.available() degerini 0 yapıyor.)
      deger+=karakter; //karakterleri (harfleri) kelimeye ekliyor
    }
    lcd.yazdir(deger); //kelimeyi yazdırıyor
  }
}
