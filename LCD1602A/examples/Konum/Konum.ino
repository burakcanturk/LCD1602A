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
int sutun_sayisi=16;
int satir_sayisi=2;
void setup() {
  lcd.baslat(16,2); //16 sütun 2 sütun
}
void loop() {
  for(char harf='a'; harf<='z'; harf++) { //bütün küçük harfleri göster (ingiliz alfabesi)
    for(int  satir=0; satir<satir_sayisi; satir++) { //bütün satırlara yaz
      for(int sutun=0; sutun<sutun_sayisi; sutun++) { //bütün sütunlara yaz
        lcd.konum(sutun,satir); //konumumuzu "for" döngüsündeki değerleri ayarla
        lcd.yazdir(harf); //harfi yaz
        delay(200);
      }
    }
  }
}
