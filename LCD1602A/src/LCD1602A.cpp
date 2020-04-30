/*coklu=true: 8 bit
 *coklu=false: 4 bit
 *2'lik sayı sistemi (binary):
 *Örnek:
 *52:
 *52/(2^7)%2 = 0
 *52/(2^6)%2 = 0
 *52/(2^5)%2 = 1
 *52/(2^4)%2 = 1
 *52/(2^3)%2 = 0
 *52/(2^2)%2 = 1
 *52/(2^1)%2 = 0
 *52/(2^0)%2 = 0
 *‭0           0		      1           1           0           1           0           0‬
 *0*(2^7)  +  0*(2^6)  +  1*(2^5)  +  1*(2^4)  +  0*(2^3)  +  1*(2^2)  +  0*(2^1)  +  0*(2^0)  =  52
 *(bu işlemleri python üzerinde yapacaksanız "^" işareti yerine "**" işaretini koymanız gerekiyor!)
 *a>>b: a/(2^b)
 *a<<b: a*(2^b)
 *rs: Register Select (işleme ayarı) (LOW: diğer fonksiyonları (kütüphanedeki) bas, HIGH: karakter bas (ascii'den veya kendi ayarladığın))
 *rw: Read/Write (oku ya da yaz) (LOW: yaz, HIGH: oku) (bizim bu pinle bir işimiz yok)
 *e: Enable (etkin) (bu pini birkaç defa HIGH-LOW yapmanız gerekiyor) (kullandığımız fonksiyonu çalıştırıyor) (tetikle)
*/
#include "LCD1602A.h" //kütüphaneyi çağırıyoruz
#include "Arduino.h" //Arduino'nun kendi fonksiyonlarını çağırmak için çağırdığımız kütüphane
#include <math.h> //matematiksel fonksiyonların kütüphanesi
#include <string.h> //kelimlerle ilgili fonksiyon
bool ekran_acik=true;
bool imlec_acik=false;
bool kirpma_acik=false;
bool sag=true;
bool otomatik_kaydirma=false;
int LCD1602A::basamak_sayisi(double s,bool n=false) { //s: sayı, n: ondalık veya tamsayı
   int basamak=0;
   if(not n) {
      if(int(s)==0) {
         basamak++;
      }
      else {
         while(int(abs(s))>=pow(10,basamak)) {
            basamak++;
         }
      }
   }
   else {
      float nokta=s;
      while(nokta!=int(nokta)) {
         nokta*=10;
         basamak++;
      }
   }
   return basamak;
}
LCD1602A::LCD1602A(int rs,int rw,int e,int d0,int d1,int d2,int d3,int d4,int d5,int d6,int d7) { //bağladığımız pinler
	coklu=true;
	pinler[0]=rs;
	pinler[1]=e;
	pinler[2]=d7;
	pinler[3]=d6;
	pinler[4]=d5;
	pinler[5]=d4;
	pinler[6]=d3;
	pinler[7]=d2;
	pinler[8]=d1;
	pinler[9]=d0;
	pinler[10]=rw;
	for(int i=0; i<11; i++) {
		pinMode(pinler[i],OUTPUT);
	}
	digitalWrite(rw,LOW);
}
LCD1602A::LCD1602A(int rs,int e,int d0,int d1,int d2,int d3,int d4,int d5,int d6,int d7) { //bağladığımız pinler
	coklu=true;
	pinler[0]=rs;
	pinler[1]=e;
	pinler[2]=d7;
	pinler[3]=d6;
	pinler[4]=d5;
	pinler[5]=d4;
	pinler[6]=d3;
	pinler[7]=d2;
	pinler[8]=d1;
	pinler[9]=d0;
	for(int i=0; i<10; i++) {
		pinMode(pinler[i],OUTPUT);
	}
}
LCD1602A::LCD1602A(int rs,int rw,int e,int d4,int d5,int d6,int d7) { //bağladığımız pinler
	coklu=false;
	pinler[0]=rs;
	pinler[1]=e;
	pinler[2]=d7;
	pinler[3]=d6;
	pinler[4]=d5;
	pinler[5]=d4;
	pinler[6]=rw;
	for(int i=0; i<7; i++) {
		pinMode(pinler[i],OUTPUT);
	}
	digitalWrite(rw,LOW);
}
LCD1602A::LCD1602A(int rs,int e,int d4,int d5,int d6,int d7) { //bağladığımız pinler
	coklu=false;
	pinler[0]=rs;
	pinler[1]=e;
	pinler[2]=d7;
	pinler[3]=d6;
	pinler[4]=d5;
	pinler[5]=d4;
	for(int i=0; i<7; i++) {
		pinMode(pinler[i],OUTPUT);
	}
}
void LCD1602A::tetikle() {
	digitalWrite(pinler[1],LOW);
	delayMicroseconds(20);
	digitalWrite(pinler[1],HIGH);
	delayMicroseconds(20);
	digitalWrite(pinler[1],LOW);
	delayMicroseconds(100);
}
void LCD1602A::temizle() {
	digitalWrite(pinler[0],LOW);
	if(coklu) { //8 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		digitalWrite(pinler[6],LOW);
		digitalWrite(pinler[7],LOW);
		digitalWrite(pinler[8],LOW);
		digitalWrite(pinler[9],HIGH); //temizleme
		tetikle();
		delayMicroseconds(1530);
	}
	else { //4 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		tetikle();
		delayMicroseconds(1530);
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],HIGH); //temizleme
		tetikle();
		delayMicroseconds(1530);
	}
}
void LCD1602A::baslangic() {
	digitalWrite(pinler[0],LOW);
	if(coklu) { //8 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		digitalWrite(pinler[6],LOW);
		digitalWrite(pinler[7],LOW);
		digitalWrite(pinler[8],HIGH); //baslangıç noktasına getirme
		digitalWrite(pinler[9],LOW);
		tetikle();
		delayMicroseconds(1530);
	}
	else { //4 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		tetikle();
		delayMicroseconds(1530);
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],HIGH); //baslangıç noktasına getirme
		digitalWrite(pinler[5],LOW);
		tetikle();
		delayMicroseconds(1530);
	}
}
void LCD1602A::yazi_yonu_ayarlari(bool yon=true,bool otomatik=false) {
	digitalWrite(pinler[0],LOW);
	if(coklu) { //8 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		digitalWrite(pinler[6],LOW);
		digitalWrite(pinler[7],HIGH); //yazı yönü ayarlama açık
		digitalWrite(pinler[8],yon); //yazının yönü
		digitalWrite(pinler[9],otomatik); //otomatik kaydırıp kaydırmama
		tetikle();
		delayMicroseconds(39);
	}
	else { //4 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		tetikle();
		delayMicroseconds(39);
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],HIGH); //yazı yönü ayarlama açık
		digitalWrite(pinler[4],yon); //yazının yönü
		digitalWrite(pinler[5],otomatik); //otomatik kaydırıp kaydırmama
		tetikle();
		delayMicroseconds(39);
	}
}
void LCD1602A::ekran_ayarlari(bool ekran=true,bool imlec=false,bool kirpma=false) {
	digitalWrite(pinler[0],LOW);
	if(coklu) { //8 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		digitalWrite(pinler[6],HIGH); //ekran ayarları açık
		digitalWrite(pinler[7],ekran); //ekranı açıp açmama
		digitalWrite(pinler[8],imlec); //imlec gösterip göstermeme
		digitalWrite(pinler[9],kirpma); //kırpma gösterip göstermeme
		tetikle();
		delayMicroseconds(39);
	}
	else { //4 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		tetikle();
		delayMicroseconds(39);
		digitalWrite(pinler[2],HIGH); //ekran ayarları açık
		digitalWrite(pinler[3],ekran); //ekranı açıp açmama
		digitalWrite(pinler[4],imlec); //imlec gösterip göstermeme
		digitalWrite(pinler[5],kirpma); //kırpma gösterip göstermeme
		tetikle();
		delayMicroseconds(39);
	}
}
void LCD1602A::yazi_kaydirma(bool yon,bool konum_degistir=true) {
	digitalWrite(pinler[0],LOW);
	if(coklu) { //8 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],HIGH); //kaydırma açık
		digitalWrite(pinler[6],konum_degistir); //yazacağımız yerin konumunu kaydırılan yerin olup olmaması
		digitalWrite(pinler[7],yon); //kaydırma yönü
		digitalWrite(pinler[8],LOW);
		digitalWrite(pinler[9],LOW);
		tetikle();
		delayMicroseconds(39);
	}
	else { //4 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],HIGH); //kaydırma açık
		tetikle();
		delayMicroseconds(39);
		digitalWrite(pinler[2],konum_degistir); //yazacağımız yerin konumunu kaydırılan yerin olup olmaması
		digitalWrite(pinler[3],yon); //kaydırma yönü
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		tetikle();
		delayMicroseconds(39);
	}
}
void LCD1602A::genel_ayarlar(bool satir2=true,bool sutun5_satir11=false) {
	digitalWrite(pinler[0],LOW);
	if(coklu) { //8 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],HIGH); //lcd ayarları açık
		digitalWrite(pinler[5],coklu); //lcd ekran için 8 pin kullanıp kullanmama
		digitalWrite(pinler[6],satir2); //2 satır olup olmama
		digitalWrite(pinler[7],sutun5_satir11); //her karakterin 5x11 olup olmaması
		digitalWrite(pinler[8],LOW);
		digitalWrite(pinler[9],LOW);
		tetikle();
		delayMicroseconds(39);
	}
	else { //4 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],HIGH); //lcd ayarları açık
		digitalWrite(pinler[5],coklu); //lcd ekran için 8 pin kullanıp kullanmama
		tetikle();
		delayMicroseconds(39);
		digitalWrite(pinler[2],satir2); //2 satır olup olmama
		digitalWrite(pinler[3],sutun5_satir11); //her karakterin 5x11 olup olmaması
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		tetikle();
		delayMicroseconds(39);
	}
}
void LCD1602A::karakter_adres(int adres) {
	digitalWrite(pinler[0],LOW);
	if(coklu) { //8 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],HIGH); //yeni karakter ayarlama açık (kaydedeceği adres)
		digitalWrite(pinler[4],(adres>>2)%2); //adresin 4'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[5],(adres>>1)%2); //adresin 2'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[6],adres%2); //adresin 1'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[7],LOW);
		digitalWrite(pinler[8],LOW);
		digitalWrite(pinler[9],LOW);
		tetikle();
		delayMicroseconds(39);
	}
	else { //4 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],HIGH); //yeni karakter ayarlama açık (kaydedeceği adres)
		digitalWrite(pinler[4],(adres>>2)%2); //adresin 4'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[5],(adres>>1)%2); //adresin 2'ler basamağı (2'lik sayı sistemi)
		tetikle();
		delayMicroseconds(39);
		digitalWrite(pinler[2],adres%2); //adresin 1'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		tetikle();
		delayMicroseconds(39);
	}
}
void LCD1602A::konum(int sutun,int satir) {
	digitalWrite(pinler[0],LOW);
	int adres;
	if(satir<0) {
		adres=sutun;
	}
	else if(satir>=alanlar[1]) {
		adres=(alanlar[1]-1>2)*20+(alanlar[1]-1%2)*64+sutun;
	}
	else {
		adres=(satir>2)*20+(satir%2)*64+sutun;
	}
	if(coklu) { //8 bit
		digitalWrite(pinler[2],HIGH); //yazacağımız yerin adresini ayarlama açık
		digitalWrite(pinler[3],(adres>>6)%2); //adresin 64'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[4],(adres>>5)%2); //adresin 32'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[5],(adres>>4)%2); //adresin 16'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[6],(adres>>3)%2); //adresin 8'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[7],(adres>>2)%2); //adresin 4'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[8],(adres>>1)%2); //adresin 2'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[9],adres%2); //adresin 1'ler basamağı (2'lik sayı sistemi)
		tetikle();
		delayMicroseconds(39);
	}
	else { //4 bit
		digitalWrite(pinler[2],HIGH); //yazacağımız yerin adresini ayarlama açık
		digitalWrite(pinler[3],(adres>>6)%2); //adresin 64'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[4],(adres>>5)%2); //adresin 32'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[5],(adres>>4)%2); //adresin 16'ler basamağı (2'lik sayı sistemi)
		tetikle();
		delayMicroseconds(39);
		digitalWrite(pinler[2],(adres>>3)%2); //adresin 8'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[3],(adres>>2)%2); //adresin 4'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[4],(adres>>1)%2); //adresin 2'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[5],adres%2); //adresin 1'ler basamağı (2'lik sayı sistemi)
		tetikle();
		delayMicroseconds(39);
	}
}
void LCD1602A::karakterYazdir(int adres) {
	digitalWrite(pinler[0],HIGH); //karakter basma açık (kaydettiğiniz karakter)
	if(coklu) { //8 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		digitalWrite(pinler[6],LOW);
		digitalWrite(pinler[7],(adres>>2)%2); //adresin 4'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[8],(adres>>1)%2); //adresin 2'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[9],adres%2); //adresin 1'ler basamağı (2'lik sayı sistemi)
		tetikle();
		delayMicroseconds(39);
	}
	else { //4 bit
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],LOW);
		digitalWrite(pinler[5],LOW);
		tetikle();
		delayMicroseconds(39);
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],(adres>>2)%2); //adresin 4'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[4],(adres>>1)%2); //adresin 2'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[5],adres%2); //adresin 1'ler basamağı (2'lik sayı sistemi)
		tetikle();
		delayMicroseconds(39);
	}
}
void LCD1602A::ekran(bool ek) {
	ekran_ayarlari(ek,imlec_acik,kirpma_acik);
	ekran_acik=ek;
}
void LCD1602A::imlec(bool im) {
	ekran_ayarlari(ekran_acik,im,kirpma_acik);
	imlec_acik=im;
}
void LCD1602A::kirpma(bool ki) {
	ekran_ayarlari(ekran_acik,imlec_acik,ki);
	kirpma_acik=ki;
}
void LCD1602A::soldanSaga() {
	yazi_yonu_ayarlari(HIGH,otomatik_kaydirma);
	sag=true;
}
void LCD1602A::sagdanSola() {
	yazi_yonu_ayarlari(LOW,otomatik_kaydirma);
	sag=false;
}
void LCD1602A::otomatikKaydir(bool ok) {
	yazi_yonu_ayarlari(sag,ok);
	otomatik_kaydirma=ok;
}
void LCD1602A::sagaKaydir() {
	yazi_kaydirma(HIGH);
}
void LCD1602A::solaKaydir() {
	yazi_kaydirma(LOW);
}
void LCD1602A::karakterOlustur(int adres,int degerler[]) {
	karakter_adres(adres);
	for(int i=0; i<karakter_boy; i++) {
		karakterYazdir(degerler[i]);
	}
}
void LCD1602A::karakter(char k) { //karakteri basma (ascii'ye göre)
	if(coklu) { //8 bit
		digitalWrite(pinler[2],(k>>7)%2); //karakterin 128'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[3],(k>>6)%2); //karakterin 64'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[4],(k>>5)%2); //karakterin 32'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[5],(k>>4)%2); //karakterin 16'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[6],(k>>3)%2); //karakterin 8'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[7],(k>>2)%2); //karakterin 4'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[8],(k>>1)%2); //karakterin 2'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[9],k%2); //karakterin 1'ler basamağı (2'lik sayı sistemi)
		tetikle();
		delayMicroseconds(39);
	}
	else { //4 bit
		digitalWrite(pinler[2],(k>>7)%2); //karakterin 128'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[3],(k>>6)%2); //karakterin 64'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[4],(k>>5)%2); //karakterin 32'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[5],(k>>4)%2); //karakterin 16'ler basamağı (2'lik sayı sistemi)
		tetikle();
		delayMicroseconds(39);
		digitalWrite(pinler[2],(k>>3)%2); //karakterin 8'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[3],(k>>2)%2); //karakterin 4'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[4],(k>>1)%2); //karakterin 2'ler basamağı (2'lik sayı sistemi)
		digitalWrite(pinler[5],k%2); //karakterin 1'ler basamağı (2'lik sayı sistemi)
		tetikle();
		delayMicroseconds(39);
	}
}
void LCD1602A::yazdir(char deger) {
	digitalWrite(pinler[0],HIGH);
	karakter(deger);
	
}
void LCD1602A::yazdir(int deger) {
	int basamak_tamsayi=basamak_sayisi(deger);
	digitalWrite(pinler[0],HIGH);
	if(deger<0) {
		karakter('-');
		deger=-deger;
	}
	for(int i=basamak_tamsayi-1; i>=0; i--) {
		karakter(abs(deger)/long(pow(10,i))%10+48);
	}
}
void LCD1602A::yazdir(long unsigned int deger) {
	int basamak_tamsayi=basamak_sayisi(deger);
	digitalWrite(pinler[0],HIGH);
	if(deger<0) {
		karakter('-');
		deger=-deger;
	}
	for(int i=basamak_tamsayi-1; i>=0; i--) {
		karakter(abs(deger)/long(pow(10,i))%10+48);
	}
}
void LCD1602A::yazdir(double deger) {
	int basamak_tamsayi=basamak_sayisi(deger,false);
	int basamak_ondalik=basamak_sayisi(deger,true);
	digitalWrite(pinler[0],HIGH);
	if(deger<0) {
		karakter('-');
	}
	for(int i=basamak_tamsayi-1; i>=0; i--) {
		karakter(int(abs(deger)/long(pow(10,i)))%10+48);
	}
	karakter('.');
	for(int i=1; i<=basamak_ondalik; i++) {
		karakter(int(abs(deger)*long(pow(10,i)))%10+48);
	}
}
void LCD1602A::yazdir(String deger) {
	digitalWrite(pinler[0],HIGH);
	for(int i=0; i<deger.length(); i++) {
		karakter(deger[i]);
	}
}
void LCD1602A::baslat(int sutun_sayisi,int satir_sayisi,int pixel_en=5,int pixel_boy=8) {
	alanlar[0]=sutun_sayisi;
	alanlar[1]=satir_sayisi;
	karakter_boy=pixel_boy;
	delay(50);
	digitalWrite(pinler[0],LOW);
	digitalWrite(pinler[2],LOW);
	digitalWrite(pinler[3],LOW);
	digitalWrite(pinler[4],LOW);
	digitalWrite(pinler[5],HIGH);
	tetikle();
	delayMicroseconds(4500);
	tetikle();
	delayMicroseconds(150);
	tetikle();
	if(not coklu) {
		digitalWrite(pinler[2],LOW);
		digitalWrite(pinler[3],LOW);
		digitalWrite(pinler[4],HIGH);
		digitalWrite(pinler[5],LOW);
		tetikle();
	}
	genel_ayarlar(satir_sayisi>1,pixel_en==5 and pixel_boy==11);
	ekran(true);
	temizle();
	soldanSaga();
}