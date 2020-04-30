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
char thisChar = 'a';
void setup() {
  lcd.baslat(16,2); //16 sütun 2 satır
  lcd.imlec(HIGH); //yazıları yazarken imleç bulunsun
}
void loop() {
  lcd.baslangic(); //yazıyı baslangıç noktasına al
  lcd.soldanSaga(); //yazıyı soldan sağa doğru yazsın (lcd.baslat() fonksiyonunun varsayılan yazı ayarlama şekli)
  for(char i='a'; i<'q'; i++) { //harflerimizi satır sonuna kadar yazsın ('a' harfi ingilizce alfabenin ilk harfi, 'q' harfi ise 17. harftir; bu yüzden satır sonuna gitsin diye ayarladık)
    lcd.yazdir(i); //harfleri yazsın
    delay(500);
  }
  lcd.konum(15,0); //en sağ konumu ayarlasın (normalde konumu 16,0 oluyor ama oradan ilk harfi yazamadığı için böyle bir ayar yapıldı)
  lcd.sagdanSola(); //yazıyı sağdan sola doğru yazsın
  for(char i='q'; i<='z'; i++) { //harflerimizi alfabe bitene kadar kadar yazsın ('q' harfi ingilizce alfabenin 17. harfi ve yukarıda dahil etmedik, 'z' harfi ise son harftir; aradaki harf farkı 9 olduğu için bitene kadar yazsın diye ayarladık)
    lcd.yazdir(i); //harfleri yazsın
    delay(500);
  }
  lcd.temizle(); //en sonunda ekrandaki herşeyi silsin
}
