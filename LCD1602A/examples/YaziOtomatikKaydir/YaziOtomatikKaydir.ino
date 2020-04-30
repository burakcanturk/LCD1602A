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
void setup() {
  lcd.baslat(16,2); //16 sütun 2 satır
}
void loop() {
  lcd.konum(0, 0);
  for (int thisChar=0; thisChar<10; thisChar++) {
    lcd.yazdir(thisChar);
    delay(500);
  }
  lcd.konum(16,1);
  lcd.tersYazi(HIGH);
  for (int thisChar=0; thisChar<10; thisChar++) {
    lcd.yazdir(thisChar);
    delay(500);
  }
  lcd.tersYazi(LOW);
  lcd.temizle();
}
