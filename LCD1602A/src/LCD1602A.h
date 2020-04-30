/*Kütüphaneyle ilgili bir sorun yaşarsanız
 *Telefon numaram: +905417710333
 *Gmail adresim: burakcanturk12@gmail.com
*/
#ifndef LCD1602A_h
#define LCD1602A_h //kütüphanemizin ismi
#include "Arduino.h"
class LCD1602A {
	public: //Arduino'da kullandığımız fonksiyonlar ve değişkenler
		LCD1602A(int rs,int rw,int e,int d0,int d1,int d2,int d3,int d4,int d5,int d6,int d7); //pinleri tanimlama (11'li)
		LCD1602A(int rs,int e,int d0,int d1,int d2,int d3,int d4,int d5,int d6,int d7); //pinleri tanimlama (10'lu)
		LCD1602A(int rs,int rw,int e,int d4,int d5,int d6,int d7); //pinleri tanimlama (7'li)
		LCD1602A(int rs,int e,int d4,int d5,int d6,int d7); //pinleri tanimlama (6'lı)
		void baslat(int sutun_sayisi,int satir_sayisi,int pixel_en=5,int pixel_boy=8); //lcd ekranı kullanıma hazır hale getirir
		void temizle(); //lcd ekranındaki herşeyi siler
		void baslangic(); //lcd ekranın yazı konumunu en başa getirir
		void ekran(bool ek); //ekranın görünme durumunu ayarlar
		void imlec(bool im); //imlecin görünme durumunu ayarlar
		void kirpma(bool ki); //kırpmanın görünme durumunu ayarlar
		void soldanSaga(); //yaziyi soldan sağa doğru yazmayı ayarlar
		void sagdanSola(); //yaziyi sağdan sola doğru yazmayı ayarlar
		void otomatikKaydir(bool ok); //bütün yazıyı ters yöne kaydırır (hangi yönü ayarlamışsanız)
		void sagaKaydir(); //yaziyi sağa kaydirir
		void solaKaydir(); //yaziyi sola kaydirir
		void konum(int sutun,int satir); //lcd ekranın yazı konumunu ayarlar
		void karakterOlustur(int adres,int degerler[]); //yeni bir karakter oluşturur
		void karakterYazdir(int adres); //oluşturduğun karakterleri yazdırır
		void yazdir(char deger); //lcd ekrana yazı yazar (tek karakter)
		void yazdir(int deger); //lcd ekrana yazı yazar (küçük tam sayılar (-32768, 32768))
		void yazdir(long unsigned int deger); //lcd ekrana yazı yazar (büyük tam sayılar (0, 4294967296))
		void yazdir(double deger); //lcd ekrana yazı yazar (reel sayı)
		void yazdir(String deger); //lcd ekrana yazı yazar (kelime)
	private: //kütüphanenin kullandığımız fonksiyonlar ve değişkenler
		bool coklu; //D pinlerinden kaç tanesini kullandığına göre verilir. (LCD1602A)
		int pinler[11]; //girilen pinleri birlikte tutan liste (LCD1602A)
		int alanlar[2]; //lcd ekranının kaç sütün ve sutun olduğunu tutan liste (baslat)
		int basamak_sayisi(double s,bool n=false); //sayinin virgülden önce veya sonra kaç basamk olduğunu bulan fonksiyon (yazdir(int veya double))
		bool sag; //otomatik kaydırmayı hangi yönden yapacağını tutan değişken (otomatikKaydir)
		bool otomatik_kaydirma; //otomatik kaydırma durumunu tutan değişken (soldanSaga ve sagdanSola)
		bool ekran_acik; //ekranın açma durumunu ayarlayan değişken (ekran)
		bool imlce_acik; //imlecin açma durumunu ayarlayan değişken (imlec)
		bool kirpma_acik; //kırpmanın açma durumunu ayarlayan değişken (kirpma)
		int karakter_boy; //"baslat" fonksiyonunda girdiğimiz lcd ekranın her bir parçasının yüksekliğini verir (karakterOlustur)
		void tetikle(); //verdiğimiz komutu uygulaması için koyduğumuz komut (hepsi)
		void genel_ayarlar(bool satir2=true,bool sutun5_satir11=false); //lcd ekranın hazırlık ayarları (baslat)
		void ekran_ayarlari(bool ekran=true,bool imlec=false,bool kirpma=false); //ekranla ilgi ayarlar (ekran, imlec ve kirpma)
		void yazi_yonu_ayarlari(bool yon=true,bool otomatik=false); //yazının yön ayarları (sagdanSola, soldanSaga ve otomatikKaydir)
		void yazi_kaydirma(bool yon,bool konum_degistir=true); //yazi kaydırma ayarları (sagaKaydir ve solaKaydir)
		void karakter_adres(int adres); //karakter oluşturma satırı açar (karakterOlustur)
		void karakter(char k); //ascii tablosuna göre verdiğimiz sayının karakterini basar (yazdir)
};
#endif