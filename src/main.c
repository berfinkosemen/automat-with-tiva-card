/*
Fatma Degirmenci, 170201008
Berfin Kosemen, 170201058
*/

#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include <string.h>

#include <stdlib.h>
#define PORTD (GPIO_PORTD_DATA_R)
#define BIT_SET(VAR, BIT_NO) do {VAR |= 1<<BIT_NO;} while (0)
#define BIT_RESET(VAR, BIT_NO) do {VAR &= ~(1<<BIT_NO);} while (0)

//seri port
#include <stdbool.h>
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#define BAUDRATE 600


//#define LCD GPIOB
#define RS 1 // PB0
#define RW 2 // PB1
#define EN 4 // PB2
void delayUzun(int n);
void delayKisa(int n);
void LCD_yaz(unsigned char data, unsigned char control);
void LCD_Cmp(unsigned char command);
void LCD_K_Yaz(unsigned char data);
void LCD_Init(void);
void init_port_E(void);
void init_port_F(void);
void init_port_D(void);
void temizle(void);
void temizle2(void);
void Yazibas( char* s);
void satirdegis(char x, char y);
void integerbas(int atilanPara);
void init_UARTstdio();
void integerbas2(int atilanPara);
char basayir(int atilanPara);


int main(){
	int basamak = 0;
	    char txt[] = "20,20,20, 1,su,30,50 Kurus, 2,cay,20,1 TL, 3,kahve,15,1.5 TL, 4,cikolata,50,1.75 TL, 5,biskuvi,100,2 TL ";

	    int stok[5];
		int para[5];
		int kasa[5];

	    int sayac1=0, sayac2=0, sayacvirgul=0;
	    int j;
	    for(int i=0; i<strlen(txt)-1; i++) {
	        if(sayacvirgul < 3 && txt[i] == ',') {
	            kasa[sayacvirgul] = (txt[i-2] - '0') *10 + (txt[i-1] - '0');
	            sayacvirgul++;
	        }


	        if(txt[i] == 's' && txt[i+1] == 'u') {
	            j = i+2;
	            while(txt[j+1] != ',') {
	                basamak++;
	                j++;
	            }
	            if(basamak == 1) {
	                stok[sayac1] = (txt[i+3] - '0');
	                sayac1++;
	            } else if(basamak == 2) {
	                stok[sayac1] = (txt[i+3] - '0')*10 + (txt[i+4] - '0');
	                sayac1++;
	            } else if(basamak == 3) {
	                stok[sayac1] = (txt[i+3] - '0')*100 + (txt[i+4] - '0')*10 + (txt[i+5] - '0');
	                sayac1++;
	            }
	            basamak = 0;


	            j = i+5;
	            while(txt[j+1] != ' ') {
	                basamak++;
	                j++;
	            }
	            if(basamak == 1) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = (txt[i+6] - '0') * 100;
	                    sayac2++;
	                } else {
	                    para[sayac2] = (txt[i+6] - '0');
	                    sayac2++;
	                }
	            } else if(basamak == 2) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = ((txt[i+6] - '0') * 10 + (txt[i+7] - '0'))*100;
	                    sayac2++;
	                } else {
	                    para[sayac2] = ((txt[i+6] - '0') * 10 + (txt[i+7] - '0'));
	                    sayac2++;
	                }
	            } else if(basamak == 3) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = (txt[i+6] - '0') * 100 + (txt[i+8] - '0')*10;
	                    sayac2++;
	                }
	            } else if(basamak == 4) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = (txt[i+6] - '0') * 100 + (txt[i+8] - '0')*10 + (txt[i+9] - '0');
	                    sayac2++;
	                }
	            }
	            basamak = 0;
	        }

	        if(txt[i] == 'c' && txt[i+1] == 'a') {
	            j = i+3;

	            while(txt[j+1] != ',') {
	                basamak++;
	                j++;
	            }
	            if(basamak == 1) {
	                stok[sayac1] = (txt[i+4] - '0');
	                sayac1++;
	            } else if(basamak == 2) {
	                stok[sayac1] = (txt[i+4] - '0')*10 + (txt[i+5] - '0');
	                sayac1++;
	            } else if(basamak == 3) {
	                stok[sayac1] = (txt[i+4] - '0')*100 + (txt[i+5] - '0')*10 + (txt[i+6] - '0');
	                sayac1++;
	            }
	            basamak = 0;


	            j = i+6;
	            while(txt[j+1] != ' ') {
	                basamak++;
	                j++;
	            }
	            j++;
	            if(basamak == 1) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = ((txt[i+7] - '0') * 100);
	                    sayac2++;
	                } else {
	                    para[sayac2] = (txt[i+7] - '0');
	                    sayac2++;
	                }
	            } else if(basamak == 2) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = ((txt[i+7] - '0') * 10 + (txt[i+8] - '0'))*100;
	                    sayac2++;
	                } else {
	                    para[sayac2] = ((txt[i+7] - '0') * 10 + (txt[i+8] - '0'));
	                    sayac2++;
	                }
	            } else if(basamak == 3) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = (txt[i+7] - '0') * 100 + (txt[i+9] - '0')*10;
	                    sayac2++;
	                }
	            } else if(basamak == 4) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = (txt[i+7] - '0') * 100 + (txt[i+9] - '0')*10 + (txt[i+10] - '0');
	                    sayac2++;
	                }
	            }
	            basamak = 0;

	        }

	        if(txt[i] == 'k' && txt[i+1] == 'a') {
	            j = i+5;
	            while(txt[j+1] != ',') {
	                basamak++;
	                j++;
	            }
	            if(basamak == 1) {
	                stok[sayac1] = (txt[i+6] - '0');
	                sayac1++;
	            } else if(basamak == 2) {
	                stok[sayac1] = (txt[i+6] - '0')*10 + (txt[i+7] - '0');
	                sayac1++;
	            } else if(basamak == 3) {
	                stok[sayac1] = (txt[i+6] - '0')*100 + (txt[i+7] - '0')*10 + (txt[i+8] - '0');
	                sayac1++;
	            }
	            basamak = 0;

	            j = i+8;
	            while(txt[j+1] != ' ') {
	                basamak++;
	                j++;
	            }
	            j++;
	            if(basamak == 1) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = ((txt[i+9] - '0') * 100);
	                    sayac2++;
	                } else {
	                    para[sayac2] = (txt[i+9] - '0');
	                    sayac2++;
	                }
	            } else if(basamak == 2) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = ((txt[i+9] - '0') * 10 + (txt[i+10] - '0'))*100;
	                    sayac2++;
	                } else {
	                    para[sayac2] = ((txt[i+9] - '0') * 10 + (txt[i+10] - '0'));
	                    sayac2++;
	                }
	            } else if(basamak == 3) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = (txt[i+9] - '0') * 100 + (txt[i+11] - '0')*10;
	                    sayac2++;
	                }
	            } else if(basamak == 4) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = (txt[i+9] - '0') * 100 + (txt[i+11] - '0')*10 + (txt[i+12] - '0');
	                    sayac2++;
	                }
	            }
	            basamak = 0;


	        }
	        if(txt[i] == 'c' && txt[i+1] == 'i') {
	            j = i+8;
	            while(txt[j+1] != ',') {
	                basamak++;
	                j++;
	            }
	            if(basamak == 1) {
	                stok[sayac1] = (txt[i+9] - '0');
	                sayac1++;
	            } else if(basamak == 2) {
	                stok[sayac1] = (txt[i+9] - '0')*10 + (txt[i+10] - '0');
	                sayac1++;
	            } else if(basamak == 3) {
	                stok[sayac1] = (txt[i+9] - '0')*100 + (txt[i+10] - '0')*10 + (txt[i+11] - '0');
	                sayac1++;
	            }
	            basamak = 0;

	            j = i+11;
	            while(txt[j+1] != ' ') {
	                basamak++;
	                j++;
	            }
	            j++;
	            if(basamak == 1) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = ((txt[i+12] - '0') * 100);
	                    sayac2++;
	                } else {
	                    para[sayac2] = (txt[i+12] - '0');
	                    sayac2++;
	                }
	            } else if(basamak == 2) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = ((txt[i+12] - '0') * 10 + (txt[i+13] - '0'))*100;
	                    sayac2++;
	                } else {
	                    para[sayac2] = ((txt[i+12] - '0') * 10 + (txt[i+13] - '0'));
	                    sayac2++;
	                }
	            } else if(basamak == 3) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = (txt[i+12] - '0') * 100 + (txt[i+14] - '0')*10;
	                    sayac2++;
	                }
	            } else if(basamak == 4) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = (txt[i+12] - '0') * 100 + (txt[i+14] - '0')*10 + (txt[i+15] - '0');
	                    sayac2++;
	                }
	            }
	            basamak = 0;

	        }
	        if(txt[i] == 'b' && txt[i+1] == 'i') {
	            j = i+7;
	            while(txt[j+1] != ',') {
	                basamak++;
	                j++;
	            }
	            if(basamak == 1) {
	                stok[sayac1] = (txt[i+8] - '0');
	                sayac1++;
	            } else if(basamak == 2) {
	                stok[sayac1] = (txt[i+8] - '0')*10 + (txt[i+9] - '0');
	                sayac1++;
	            } else if(basamak == 3) {
	                stok[sayac1] = (txt[i+8] - '0')*100 + (txt[i+9] - '0')*10 + (txt[i+10] - '0');
	                sayac1++;
	            }

	            j = i+7+basamak+1;
	            basamak = 0;
	            while(txt[j+1] != ' ' || txt[j+1] != ' ') {
	                basamak++;
	                j++;
	            }
	            j++;
	            if(basamak == 1) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = ((txt[i+12] - '0') * 100);
	                    sayac2++;
	                } else {
	                    para[sayac2] = (txt[i+12] - '0');
	                    sayac2++;
	                }
	            } else if(basamak == 2) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = ((txt[i+12] - '0') * 10 + (txt[i+13] - '0'))*100;
	                    sayac2++;

	                } else {
	                    para[sayac2] = ((txt[i+12] - '0') * 10 + (txt[i+13] - '0'));
	                    sayac2++;
	                }
	            } else if(basamak == 3) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = (txt[i+12] - '0') * 100 + (txt[i+14] - '0')*10;
	                    sayac2++;
	                }
	            } else if(basamak == 4) {
	                if(txt[j+1] == 'T') { //tl ise 10 ile carp
	                    para[sayac2] = (txt[i+12] - '0') * 100 + (txt[i+14] - '0')*10 + (txt[i+15] - '0');
	                    sayac2++;
	                }
	            }
	            basamak = 0;

	        }
	    }



	    int i,stock_yedek[5],kasa_yedek[3];
	    for(i=0;i<5;i++){
	    	stock_yedek[i] = stok[i];
	    }
	    for(i=0;i<3;i++){
	    	kasa_yedek[i] = kasa[i];
	    }


	int randomNumber;
	init_port_E();
	init_port_F();
	init_port_D();
	LCD_Init();
	LCD_Cmp(1);
	LCD_Cmp(0x80);
	delayUzun(500);
	Bas:
	delayUzun(1);

	satirdegis(1,1);
	Yazibas("Para Yuklemesi");
	satirdegis(2,1);
	Yazibas("Yapiniz");
	delayUzun(500);


	volatile unsigned long delay;
	int atilanPara = 0,atilanPara_yedek=0;
	int button_1, button_2,button_3,button_4,button_5,button_6,button_7,button_8,button_9,button_10,button_11;
	while (1) {

		button_1 = GPIO_PORTE_DATA_R & 0b00001;
		button_2 = GPIO_PORTE_DATA_R & 0b00010;
		button_3 = GPIO_PORTE_DATA_R & 0b00100;
		button_4 = GPIO_PORTE_DATA_R & 0b01000;

		if (button_1 != 0) {
			 atilanPara = atilanPara + 25;
			 integerbas(atilanPara);
			 kasa[0]++;
	}

		else if(button_2 != 0) {
			 atilanPara = atilanPara + 50;
			 integerbas(atilanPara);
			 kasa[1]++;
		}

		else if (button_3 != 0) {
			 atilanPara = atilanPara + 100;
			 integerbas(atilanPara);
			 kasa[2]++;
		}
		else if(button_4 != 0){
			break;
		}

	}


	satirdegis(2,0);
	Yazibas("Urun seciniz");
	delayUzun(1000);
	temizle();

	atilanPara_yedek = atilanPara;




 	while(1){

 		button_1 = GPIO_PORTE_DATA_R & 0b00001;
		button_2 = GPIO_PORTE_DATA_R & 0b00010;
		button_3 = GPIO_PORTE_DATA_R & 0b00100;
		button_4 = GPIO_PORTE_DATA_R & 0b01000;
		button_5 = GPIO_PORTE_DATA_R & 0b10000;
		button_6 = GPIO_PORTE_DATA_R & 0b100000;
		button_7 = GPIO_PORTF_DATA_R & 0b010000;


		if (button_1 != 0) {
			if(atilanPara >= 50){
				if(stok[0] != 0){
					atilanPara -= 50;
					integerbas(atilanPara);
					stok[0] = stok[0]-1;
				}
				else{
					satirdegis(2,0);
					Yazibas("Urun kalmadi");
					delayUzun(1000);
					temizle();
				}
			}else{
				satirdegis(2,0);
				Yazibas("bakiye yetersiz");
				delayUzun(1000);
				temizle();
			}

		}
		else if (button_2 != 0) {
			if(atilanPara >=100){
				if(stok[1] != 0){
					atilanPara -= 100;
					integerbas(atilanPara);
					stok[1] = stok[1]-1;
				}
				else{
					satirdegis(2,0);
					Yazibas("Urun kalmadi");
					delayUzun(1000);
					temizle();
				}
			}else{
				satirdegis(2,0);
				Yazibas("bakiye yetersiz");
				delayUzun(1000);
				temizle();
			}

		}
		else if (button_3 != 0) {
			if(atilanPara >= 150){
				if(stok[2] != 0){
					atilanPara -= 150;
					integerbas(atilanPara);
					stok[2] = stok[2]-1;
				}
				else{
					satirdegis(2,0);
					Yazibas("Urun kalmadi");
					delayUzun(1000);
					temizle();
				}
			}else{
				satirdegis(2,0);
				Yazibas("bakiye yetersiz");
				delayUzun(1000);
				temizle();
			}

		}
		else if (button_4 != 0) {
			if(atilanPara >= 175){
				if(stok[3] != 0){
					atilanPara -= 175;
					integerbas(atilanPara);
					stok[3] = stok[3]-1;
				}
				else{
					satirdegis(2,0);
					Yazibas("Urun kalmadi");
					delayUzun(1000);
					temizle();
				}
			}else{
				satirdegis(2,0);
				Yazibas("bakiye yetersiz");
				delayUzun(1000);
				temizle();
			}
		}
		else if (button_5 != 0) {
			if(atilanPara >= 200){
				if(stok[4] != 0){
					atilanPara -= 200;
					integerbas(atilanPara);
					stok[4] = stok[4]-1;
				}
				else{
					satirdegis(2,0);
					Yazibas("Urun kalmadi");
					delayUzun(1000);
					temizle();
				}
			}else{
				satirdegis(2,0);
				Yazibas("bakiye yetersiz");
				delayUzun(1000);
				temizle();
			}
		}
		else if (button_6 != 0)
			break;

		else if (button_7 != 0) {
			atilanPara = atilanPara_yedek;
			integerbas(atilanPara);
			stok[0] = stock_yedek[0];
			stok[1] = stock_yedek[1];
			stok[2] = stock_yedek[2];
			stok[3] = stock_yedek[3];
			stok[4] = stock_yedek[4];
		}
	}



 	temizle();
 	randomNumber = rand()%4+1;
 	integerbas2(randomNumber);
 	satirdegis(2,4);
 	Yazibas("random sayi");
 	delayUzun(1000);
 	temizle();


 	 if(randomNumber == 2) {

 		 BIT_SET(PORTD, 3);
 		 BIT_RESET(PORTD,2);
 	     delayUzun(1000);
 	     satirdegis(2,0);
 	     Yazibas(" para takildi");
 	     temizle();
 	     delayUzun(1000);
 	     int k25 = kasa[0]-kasa_yedek[0];
 	     int k50 = kasa[1]-kasa_yedek[1];
 	     int tl1 = kasa[2]-kasa_yedek[2];
 	     kasa[0] = kasa_yedek[0];
 	     kasa[1] = kasa_yedek[1];
 	     kasa[2] = kasa_yedek[2];
 	     stok[0] = stock_yedek[0];
 	     stok[1] = stock_yedek[1];
 	     stok[2] = stock_yedek[2];
 	     stok[3] = stock_yedek[3];
 	     stok[4] = stock_yedek[4];
 	     satirdegis(2,0);
 	     Yazibas("para iadesi");
 	     delayUzun(1000);
 	     temizle();
 	     integerbas2(tl1);
 	     satirdegis(2,5);
 	     Yazibas("tane 1 TL");
 	     delayUzun(1000);
 	     temizle();
 	     integerbas2(k50);
 	     satirdegis(2,3);
 	     Yazibas("tane 50 kurus");
 	     delayUzun(1000);
 	     temizle();
 	     integerbas2(k25);
 	     satirdegis(2,3);
 	     Yazibas("tane 25 kurus");
 	     delayUzun(1000);
 	     temizle();

 	  } else {

 		 BIT_SET(PORTD,2);
 		 BIT_RESET(PORTD,3);
 		 satirdegis(2,0);
 		 Yazibas("islem basarili");
 		 delayUzun(1000);
 		 temizle();


 		if(kasa[0]*25+kasa[1]*50+kasa[2]*100 < atilanPara){
 		     satirdegis(2,1);
 		     Yazibas("ParaUstu yetersiz");
 		     delayUzun(1000);
 		  }
 		     		 else{
 		     		 		if(kasa[2] > 0){
 		     		 			int tl1Sayisi = atilanPara/100;
 		     		 			if(tl1Sayisi != 0){
 		     		 				int i,n=tl1Sayisi;
 		     		 				if(n > kasa[2]){
 		     		 					satirdegis(2,0);
 		     		 					Yazibas("Para Ustu");
 		     		 					delayUzun(1000);
 		     		 					temizle();
 		     		 					integerbas2(kasa[2]);
 		     		 					satirdegis(2,4);
 		     		 					Yazibas("tane 1 TL");
 		     		 					delayUzun(1000);
 		     		 					temizle();
 		     		 					atilanPara -= 100*kasa[2];
 		     		 					kasa[2] = kasa[2]-kasa[2];
 		     		 				}
 		     		 				if(n <= kasa[2]){
 		     		 					satirdegis(2,0);
 		     		 					Yazibas("Para Ustu");
 		     		 					delayUzun(1000);
 		     		 					temizle();
 		     		 					integerbas2(n);
 		     		 					satirdegis(2,4);
 		     		 	 				Yazibas("tane 1 TL");
 		     		 					delayUzun(1000);
 		     		 	 				temizle();
 		     		 					atilanPara = atilanPara%100;
 		     		 					kasa[2] = kasa[2]-n;
 		     		 				}

 		     		 			}
 		     		 		}
 		     		 		if(kasa[1] > 0){
 		     		 			int kurus50Sayisi = atilanPara/50;
 		     		 			if(kurus50Sayisi != 0){
 		     		 				int i,n=kurus50Sayisi;
 		     		 				if(n > kasa[1]){
 		     		 					satirdegis(2,0);
 		     		 					Yazibas("Para Ustu");
 		     		 					delayUzun(1000);
 		     		 					temizle();
 		     		 					integerbas2(kasa[1]);
 		     		 					satirdegis(2,4);
 		     		 					Yazibas("tane 50 kurus");
 		     		 					delayUzun(1000);
 		     		 					temizle();
 		     		 				    atilanPara -= 50*kasa[1];
 		     		 				    kasa[1] = kasa[1]-kasa[1];
 		     		 				}
 		     		 				if(n <= kasa[1]){
 		     		 					satirdegis(2,0);
 		     		 					Yazibas("Para Ustu");
 		     		 					delayUzun(1000);
 		     		 					temizle();
 		     		 					integerbas2(n);
 		     		  					satirdegis(2,4);
 		     		  					Yazibas("tane 50 kurus");
 		     		 					delayUzun(1000);
 		     		 					temizle();
 		     		 					atilanPara = atilanPara%50;
 		     		 					kasa[1] = kasa[1]-n;
 		     		 				}
 		     		 			}
 		     		 		}
 		     		 		if(kasa[0] > 0){
 		     		 		 	int kurus25Sayisi = atilanPara/25;
 		     		 		 	if(kurus25Sayisi != 0){
 		     		 		 	int i,n=kurus25Sayisi;
 		     		 		 	if(n > kasa[0]){
 		     		 		 		satirdegis(2,0);
 		     		 		 		Yazibas("Para Ustu");
 		     		 		 		delayUzun(1000);
 		     		 		 		temizle();
 		     		 		 		integerbas2(kasa[0]);
 		     		 		 		satirdegis(2,4);
 		     		 		 		Yazibas("tane 25 kurus");
 		     		 		 		delayUzun(1000);
 		     		 		 		temizle();
 		     		 		 		atilanPara -= 25*kasa[2];
 		     		 		 		kasa[0] = kasa[0]-kasa[0];
 		     		 		 	}
 		     		 		 	if(n <= kasa[0]){
 		     		 		 		satirdegis(2,0);
 		     		 		 		Yazibas("Para Ustu");
 		     		 		 		delayUzun(1000);
 		     		 		 		temizle();
 		     		 		 		integerbas2(n);
 		     		 		 		satirdegis(2,4);
 		     		 		 		Yazibas("tane 25 kurus");
 		     		 		 		delayUzun(1000);
 		     		 		 	    temizle();
 		     		 		 		atilanPara = atilanPara%25;
 		     		 		 		kasa[0] = kasa[0]-n;
 		     		 		 	}
 		     		 		  }
 		     		 		}
 		     		 	}


 	  }

 	BIT_RESET(PORTD, 2);
    BIT_RESET(PORTD, 3);



    satirdegis(2,0);
    Yazibas("kasa");
    delayUzun(1000);
    temizle();
    integerbas2(kasa[0]);
    satirdegis(2,4);
    Yazibas("tane 25 kurus");
    delayUzun(1000);
    temizle();

    satirdegis(2,0);
    Yazibas("kasa");
    delayUzun(1000);
    temizle();
    integerbas2(kasa[1]);
    satirdegis(2,4);
    Yazibas("tane 50 kurus");
    delayUzun(1000);
    temizle();

    satirdegis(2,0);
    Yazibas("kasa");
    delayUzun(1000);
    temizle();
    integerbas2(kasa[0]);
    satirdegis(2,4);
    Yazibas("tane 1 TL");
    delayUzun(1000);
    temizle();

    satirdegis(2,0);
    Yazibas("stoklar");
    delayUzun(1000);
    temizle();
    integerbas2(stok[0]);
    satirdegis(2,4);
    Yazibas("tane su");
    delayUzun(1000);
    temizle();

    satirdegis(2,0);
    Yazibas("stoklar");
    delayUzun(1000);
    temizle();
    integerbas2(stok[1]);
    satirdegis(2,4);
    Yazibas("tane cay");
    delayUzun(1000);
    temizle();

    satirdegis(2,0);
    Yazibas("stoklar");
    delayUzun(1000);
    temizle();
    integerbas2(stok[2]);
    satirdegis(2,4);
    Yazibas("tane kahve");
    delayUzun(1000);
    temizle();

    satirdegis(2,0);
    Yazibas("stoklar");
    delayUzun(1000);
    temizle();
    integerbas2(stok[3]);
    satirdegis(2,4);
    Yazibas("tane cikolata");
    delayUzun(1000);
    temizle();

    satirdegis(2,0);
    Yazibas("stoklar");
    delayUzun(1000);
    temizle();
    integerbas2(stok[4]);
    satirdegis(2,4);
    Yazibas("tane biskuvi");
    delayUzun(1000);
    temizle();


    init_UARTstdio();
    UARTprintf("kasada kalan paralar");
    UARTprintf(basayir(kasa[0]));
    UARTprintf(kasa[1]);
    UARTprintf(kasa[2]);
 	UARTprintf("stokta kalan urunlar");
 	UARTprintf(stok[0]);
 	UARTprintf(stok[1]);
 	UARTprintf(stok[2]);
 	UARTprintf(stok[3]);
 	UARTprintf(stok[4]);
}


void init_port_E(){
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOE;		// E portunu aktive et
	delay = SYSCTL_RCGC2_R;						// E portunun aktive edilmesini 1 tick bekle
	GPIO_PORTE_DIR_R |= 0x00;					// E portunun giriş çıkışlarını belirle
	GPIO_PORTE_DEN_R |= 0b00111111;				// E portunun pinlerini aktifleştir
}
void init_port_F() {
volatile unsigned long delay;
SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;
delay = SYSCTL_RCGC2_R;
GPIO_PORTF_DIR_R |= 0x00;
GPIO_PORTF_DEN_R |= 0xFF;
}

void init_port_D() {
	volatile unsigned long delay;
    SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; //port D yi aktiflestir
    delay = SYSCTL_RCGC2_R;
    GPIO_PORTD_DIR_R |= 0x0F; //Port D 3,2,1,0 pinlerini cikis yap
    //GPIO_PORTD_AFSEL_R &= ~0x0F; //Port D 3,2,1,0 pinlerini alternatif fonksiyonu 0 yap
    GPIO_PORTD_DEN_R |= 0x0F; //Port D 3,2,1,0 pinlerini aktiflestir
}

void temizle(){
	satirdegis(2,1);
	Yazibas("                ");
}
void temizle2(){
	satirdegis(1,1);
	Yazibas("                ");
}


void Yazibas( char* s){

        while(*s)
                LCD_K_Yaz(*s++);
}
void satirdegis(char x, char y){

        if(x==1)
                LCD_Cmp(0x80+((y-1)%16));
        else
                LCD_Cmp(0xC0+((y-1)%16));
}

void LCD_Init(void)
{
	SYSCTL_RCGC2_R |= (1<<1);
	GPIO_PORTB_DIR_R |= 0xFF;
	GPIO_PORTB_DEN_R |= 0XFF;
	LCD_Cmp(0x28);
	LCD_Cmp(0x06);
	LCD_Cmp(0x01);
	LCD_Cmp(0x0F);

}


void LCD_yaz(unsigned char data, unsigned char control)
{
	data &= 0xF0; // son dort bit data
	control &= 0x0F; // ilk dort bit control
	GPIO_PORTB_DATA_R = data | control;
	GPIO_PORTB_DATA_R = data | control | EN;
	delayKisa(0);
	GPIO_PORTB_DATA_R = data ;

}

void LCD_Cmp(unsigned char command)
{
	LCD_yaz(command & 0xF0,0);
	LCD_yaz(command<<4,0);

	if(command < 4)
	{
		delayUzun(2);
	}
	else
		delayKisa(40);
}
void LCD_K_Yaz(unsigned char data)
{
	LCD_yaz(data & 0xF0,RS);
	LCD_yaz(data <<4,RS);
	delayKisa(40);
}
void delayUzun(int n)
{
	int x,y;
	for(x=0;x<n;x++)
	{
		for(y=0;y<3333;y++)
		{

		}
	}

}
void delayKisa(int n){
	int x,y;
		for(x=0;x<n;x++){
			for(y=0;y<3;y++){

			}
		}
}

void integerbas(int atilanPara){
	int tl;
							int kurus;

							tl = atilanPara/100;
							kurus = atilanPara%100;
				            char strToplamPara[10];

				            for(int i=0; i<10; i++) {
				                strToplamPara[i] = '\0';
				            }

				            if(tl<10) {
				                strToplamPara[0] = tl + '0';
				                strToplamPara[1] = '.';

				                if(kurus<10) {
				                    strToplamPara[2] = kurus + '0';

				                    strToplamPara[3] = ' ';
				                    strToplamPara[4] = 'T';
				                    strToplamPara[5] = 'L';
				                } else {
				                    strToplamPara[2] = (kurus/10) + '0';
				                    strToplamPara[3] = (kurus%10) + '0';

				                    strToplamPara[4] = ' ';
				                    strToplamPara[5] = 'T';
				                    strToplamPara[6] = 'L';
				                }

				            } else {
				                strToplamPara[0] = (tl/10) + '0';
				                strToplamPara[1] = (tl%10) + '0';
				                strToplamPara[2] = '.';

				                if(kurus<10) {
				                    strToplamPara[3] = kurus + '0';

				                    strToplamPara[4] = ' ';
				                    strToplamPara[5] = 'T';
				                    strToplamPara[6] = 'L';
				                } else {
				                    strToplamPara[3] = (kurus/10) + '0';
				                    strToplamPara[4] = (kurus%10) + '0';

				                    strToplamPara[5] = ' ';
				                    strToplamPara[6] = 'T';
				                    strToplamPara[7] = 'L';
				                }
				            }

				           satirdegis(1,1);
				           Yazibas("Toplam Tutar");
				           satirdegis(2,1);
				           Yazibas(strToplamPara);
				           delayUzun(500);
				           temizle2();

}

void integerbas2(int atilanPara){
	char strToplamPara[10];

	for(int i=0; i<10; i++) {
		strToplamPara[i] = '\0';
	}
	int n = atilanPara /10;
	int m = atilanPara%10;
	if(n == 0){
			strToplamPara[0] = m + '0';
			satirdegis(2,1);
			Yazibas(strToplamPara);
	}
	else if(n != 0 && n<10){
		strToplamPara[0] = n + '0';
		strToplamPara[1] = m + '0';
		satirdegis(2,0);
		Yazibas(strToplamPara);
	}
	else{
		strToplamPara[0] = atilanPara/100 + '0';
		atilanPara = atilanPara%100;
		strToplamPara[1] = atilanPara/10 + '0';
		atilanPara = atilanPara%10;
		strToplamPara[2] = atilanPara + '0';
		satirdegis(2,0);
		Yazibas(strToplamPara);
	}


}

char basayir(int atilanPara){
	char strToplamPara[10];

	for(int i=0; i<10; i++) {
		strToplamPara[i] = '\0';
	}
	int n = atilanPara /10;
	int m = atilanPara%10;
	if(n == 0){
			strToplamPara[0] = m + '0';
	}
	else if(n != 0 && n<10){
		strToplamPara[0] = n + '0';
		strToplamPara[1] = m + '0';
	}
	else{
		strToplamPara[0] = atilanPara/100 + '0';
		atilanPara = atilanPara%100;
		strToplamPara[1] = atilanPara/10 + '0';
		atilanPara = atilanPara%10;
		strToplamPara[2] = atilanPara + '0';
	}

return strToplamPara;
}

/** UART (seri port) ayarini yapan fonksiyon */
void init_UARTstdio() {
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	GPIOPinConfigure(0x00000001);
	GPIOPinConfigure(0x00000401);
	GPIOPinTypeUART(0x40004000, 0x00000001 | 0x00000002);
	UARTConfigSetExpClk(0x40004000, SysCtlClockGet(), BAUDRATE,
                        	(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                         	UART_CONFIG_PAR_NONE));
	UARTStdioConfig(0, BAUDRATE, SysCtlClockGet());
}


