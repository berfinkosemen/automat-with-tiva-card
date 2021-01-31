# automat-with-tiva-card

    
En Az Sayıda Bozuk Para Verme Problemi

Berfin Kösemen	

Fatma Değirmenci

Bu README.md dosyası, En Az Sayıda Bozuk Para Verme Problemi projesine aittir.
Bu paket, kaynak kodu ile aynı dizin içerisinde bulunacaktır.


1-PAKETİN İÇERİĞİ:
----------
Projenin dosyaları.
README.md - Bu dosya.
----------


2-SİSTEM GEREKSİNİMLERİ:
-------------------
Oracle VM virtualbox - https://www.virtualbox.org/
Sanal Makine İmajı   - https://github.com/KOU-Embedded-System-Lab/os-base-image/releases
-------------------


3-PROJEYİ ÇALIŞTIRMAK:
-------------------
Paket içeriğini yukarıda görebilirsiniz.

Bu kod, 2 adet önceden tanımlanmış sanal makinelerde çalıştırıldı.

Sanal makineyi indirmek için;
https://github.com/KOU-Embedded-System-Lab/os-base-image/releases
adresini ziyaret edebilirsiniz.

Bu iki durumda da, kod, herhangi bir hata vermeksizin, daha önceden
belirlenen kriterlere uygun çalıştı.


4-KODU DERLEMEK:
------------------
Artık bilgisayarımızda kurulu olan sanal makine ile kodu kolayca derleyebiliriz.

Projeyi geliştirim kartında çalıştırmak için kodu daha önceden oluşturulmuş Tiva C
projesinde yer alan "main.c"ye yapıştırıp build butonuna tıkladıktan sonra debug 
butonuna tıklamanız yeterli.

Eğer kart, sanal makine tarafından bulunamadıysa (OpenOCD hatası) sanal makineye
bağlı olan bir kart olmayabilir. Sağ alt kısımdan usb ikonuna sağ tıklayarak 
Texas Instruments'ı seçip sanal makineye bağlamanız gerekmektedir.

Ana Makinesi GNU/Linux olan makinelerde VirtualBox, kullanıcı izinlerine sahip
olmayabiliyor. Eğer takılı olan USB aygıtları tanımıyorsa, 
'sudo usermod -G vboxusers -a $USER'
kodunu çalıştırmanız ve sisteminizi yeniden başlatmanız gerekmektedir. 
------------------


5- PARAMETRELER
---------------------------
Kodun çalışması için başlangıçta herhangi bir parametre gerekmiyor.
------------------


6- PROGRAMIN KULLANIMI
-----------------------------
En Az Sayıda Bozuk Para Verme Problemi, kullanıcıdan, butonlar yardımı ile girdi alarak
girilen miktar doğrultusunda ürün seçimi yapmasını sağlar.

İlk buton 25 kuruş eklemek için kullanılır. 

İkinci buton 50 kuruş eklemek için kullanılır.

Üçüncü buton 1 TL eklemek için kullanılır. 

Dördüncü buton para girme işlemini tamamlamak için kullanılır. Kullanıcı istediği 
miktarda para girdikten sonra ürün seçmek için buton 4'e basmalıdır.

Her butona basıp para eklendiğinde LCD ekranında girilen toplam tutar görülmektedir.

Dördüncü butona basıldıktan sonra ürün seçme işlemi yapılmalıdır. Ürün seçimi için;

İlk buton su, ikinci buton çay, üçüncü buton kahve, dördüncü buton çikolata, beşinci
buton bisküvidir. 

Seçilen her ürün için girilen toplam tutardan seçilen ürünün ücreti kesilir. 

Yedinci buton reset butonudur. Kullanıcı ürün seçimi esnasında yedinci butona basarsa
seçilen tüm ürünler sıfırlanır ve girilen toplam tutar ilk haline döner. Kullanıcıdan
yeniden ürün seçimi yapması istenilir.

Altıncı buton ürün seçimini tamamlar.

Para sıkışması durumu için 1-4 arası random bir sayı üretilir. Üretilen sayı 2 ise
para sıkışma durumu gözlenir ve kırmızı led yanar. Aksi durumda yeşil led yanacaktır. 
Kırmızı led yanması durumunda program para iadesi yapar ve girilen ürünler stoktan düşmez.
Para sıkışması olmazsa kasadaki bozuk paralara göre para üüstü verilir. Ve son durumda 
kasadaki ve stoktaki ürünlerin miktarları ekrana bastırılır.
