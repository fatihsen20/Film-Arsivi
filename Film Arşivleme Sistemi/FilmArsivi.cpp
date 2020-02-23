#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<locale.h>

#define size 25
using namespace std;

struct film_bilgileri{
	char film_adi[size];
	char yonetmen[size];
	char basrol[size];
	char senarist[size];
	int yil;
}filmler;
//Fonksiyon imzalarý.
int Menu();
void filmEkle();
void film_sil();
void FilmListele();
void Film_ara();
void film_guncelle();
void Film_ara();
int main()
{
	//Alt satýrda ki kodu printler içine Türkçe dil desteði eklemek için yazdým.
	setlocale(LC_ALL, "Turkish");
	//Alt satýrda ki kod cmd ekranýnýn renkli olmasýný saðlar.
	system("color fc");
	printf("+++++++++++++++++++++++++++++++FÝLM ARÞÝVLEME SÝSTEMÝ++++++++++++++++++++++++++++++\n\n");
	Menu();
    getch();
    return 0;
}
//Menü sistemini fonksiyon olarak yazdým.Görünüþ açýsýndan daha hoþ.
int Menu()
{
	//Switch-case sistemi ve if yardýmýyla menü sistemini yazdým.
     char Tercih = 'r';
     printf("\n");
	printf(" Film Ekle-->1\n Filmleri Listele-->2\n Film Güncelle-->3\n Film Sil-->4\n Film Ara-->5\n");	
     Tercih = getche();
     while(Tercih != 'E' || Tercih != 'e') {
          switch(Tercih)
          {
                        case '1': {filmEkle();break;}
                        case '2': {FilmListele();break;}
                        case '3': {film_guncelle();break;}
                        case '4': {film_sil();break;}
                        case '5': {Film_ara();break;}
						
						
						
          }
          printf("\nBaþka iþlem yapmak istiyor musunuz(E/H)?\n");
          Tercih = getche();
          if(Tercih == 'H' || Tercih == 'h') {
                    break;
          }
          if(Tercih == 'E' || Tercih== 'e'){
          	//Ýþlemlerin tekrar yapýlabilmesi için kendini yenileyip menüye giden fonksiyonu yazdým.
          	return Menu();
		  }
     }
}
void filmEkle()
{
	//Dosya tipinde pointer oluþturarak veritabanýný oluþturdum.
	FILE *fp;
	fp = fopen("filmveritabaný.dat","a");
	fflush(stdin);//boþluklarý karakter olarak almasýný engellemek için fflush(stdin) fonksiyonunu yazdým ve gets ile verileri aldým.
	printf("\n");
	printf("Lütfen Filmin Adýný giriniz:\n");
	gets(filmler.film_adi);
	fflush(stdin);
	fflush(stdin);
	printf("Lütfen Filmin Baþrolünü giriniz:\n");
	gets(filmler.basrol);
	fflush(stdin);
	fflush(stdin);
	printf("Lütfen Filmin Senaristini giriniz:\n");
	gets(filmler.senarist);
	fflush(stdin);
	fflush(stdin);
	printf("Lütfen Filmin Yönetmenini giriniz:\n");
	gets(filmler.yonetmen);
	fflush(stdin);
	printf("Lütfen Filmin Yayýnlanma Yýlýný giriniz:\n");
	scanf("%d",&filmler.yil);
	//fwrite komutu aldýðýmýz verileri dosyaya yazmak için kullanýlýr.
	fwrite(&filmler,sizeof(film_bilgileri),1,fp);
	//fclose fonksiyonu dosyayý kapatmaya yarar.
	fseek(fp,0,SEEK_SET);
	fclose(fp);
	printf("Film baþarýyla eklendi^__^\n");
	return;
}
void film_sil(){
     char filmad_temp[30];
     FILE *FilmDB;
     FILE *TempFilmDB;
     printf("\nSilmek istediðiniz filmin adýný giriniz: \n");
     fflush(stdin);
     gets(filmad_temp);
     // Dosyadaki bütün kayýtlar taranýr ve silinmesini istediðimiz kayýt atlanarak geçici bir dosyaya, silinecek kayýt dýþýndakilerin hepsi yazýlýr. 
     FilmDB = fopen("filmveritabaný.dat","r");
     TempFilmDB = fopen("TempFile.dat","a");
     //Burada temp dosyasýna yazdýrma iþlemi yapýlýyor.
	 while(fread(&filmler, sizeof(film_bilgileri),1,FilmDB))
     {
                if(strcmp(filmler.film_adi,filmad_temp)==0)
                {
                	char x;
				printf("Film silinecek emin misiniz?(Silmek için y/vazgeçmek için n)\n");
				fflush(stdin);
				scanf("%c" ,&x);
				if(x=='y'|| x=='Y'){
                    printf("\nFilm baþarýyla silindi^__^\n");
					}
					else{
						printf("Silme iptal edildi-__-\n");
						fwrite(&filmler, sizeof(film_bilgileri),1,TempFilmDB);
					}
				}
					else{
						fwrite(&filmler, sizeof(film_bilgileri),1,TempFilmDB);
					}
					if(strcmp(filmler.film_adi,filmad_temp)==0){
					}
                	
                
            
     }
     //Ýmleç dosya baþýna gönderiliyor.
     fseek(TempFilmDB,0,SEEK_SET);
     fclose(FilmDB);
     fclose(TempFilmDB);
     // Dosya silinir.
     remove("filmveritabaný.dat");
     // geçici dosyanýn ismi asýl dosya ismi deðiþtirilir.
     rename("TempFile.dat","filmveritabaný.dat");
}
void FilmListele(){
	struct film_bilgileri gecici;
	FILE *fp;
	fp = fopen("filmveritabaný.dat","r");
	//struct dizisi oluþturarak sýralama iþini gerçekleþtirdim.
	struct film_bilgileri filmler[size] = {"","","","",0};
	int i = 0;
	if(fp == NULL)
	{	printf("\nDosya açýlamadý-__-\n");
	return;
	}
	else{
		while(fread(&filmler[i],sizeof(film_bilgileri),1,fp))
		{ i++;
		}
		//Bubble sort algoritmasý ile sýralama gerçekleþtirildi.
	for(i = 0; i < size-1; i++){
		for(int j = 0; j < size-i-1; j++){
			if(filmler[j+1].yil > filmler[j].yil){
				gecici = filmler[j];
				filmler[j] = filmler[j+1];
				filmler[j+1] = gecici;

				}
			}
		}
	printf("\nFilm Adý\tBaþrol\t\tYönetmen\tSenarist\tYayýnlanma Yýlý\n");
	for (i = 0; i < size; i++){
		if(filmler[i].yil == 0 ){
			}
		else{
			printf("\n");
			printf("%s\t\t%s\t\t%s\t\t%s\t\t%4d\n",filmler[i].film_adi,filmler[i].basrol,filmler[i].yonetmen,filmler[i].senarist,filmler[i].yil);
			}
		}
	}
rewind(fp); //Dosyayý baþa yollayarak fonlsiyonun stabil çalýþmasýný saðladým. 
fclose(fp);
printf("\n");
return;
}
void film_guncelle(){
	//struct dizileri oluþturup verileri buraya kaydettik.
	struct film_bilgileri guncelleme = {"","","","",0};
	struct film_bilgileri sil = {"","","","",0};
	FILE *filep;//File cinsinde bir pointer oluþturuldu.
    char isim[size];	 
    
    printf("Güncellemek istediðiniz filmin adýný giriniz: ");
    scanf("%s",&isim);
    //burada film verilerini çekiyoruz.
        if((filep=fopen("filmveritabaný.dat","r+"))==NULL)
        {
            printf("Veritabaný bulunamadý-__-");
        }
        else
        {	rewind(filep);
         while (fread(&guncelleme,sizeof(filmler),1,filep))
            {
		
        //Burada güncelleme iþlemleri yapýlýyor.
            if(strcmp(guncelleme.film_adi,isim)==0)
            {
                
            	           
                printf("Güncellenecek film "
                        "%s %s %s %s %d",
		        guncelleme.film_adi,guncelleme.yonetmen,guncelleme.basrol,guncelleme.senarist,guncelleme.yil);
				            
                fflush(stdin);
                printf("\nyeni film adý:");
                gets(guncelleme.film_adi);
				printf("\n%s filminin yönetmenini giriniz:",guncelleme.film_adi);
                gets(guncelleme.yonetmen);
				printf("\n%s filminin baþrolünü giriniz:",guncelleme.film_adi);
                gets(guncelleme.basrol);
				printf("\n%s filminin senaristini giriniz:",guncelleme.film_adi);
                gets(guncelleme.senarist);
				printf("\n%s filminin yýlýný giriniz :",guncelleme.film_adi);
                scanf("%d",&guncelleme.yil);
                
                //Silme ve güncelleme iþlemleri yapýlýyor.
                int imlec=ftell(filep);

                fseek(filep,-imlec,SEEK_CUR );
                  fwrite(&sil,sizeof(filmler),1,filep);
				                  
                 fseek(filep,-imlec,SEEK_CUR);
                fwrite(&guncelleme,sizeof(filmler),1,filep);
                 imlec=ftell(filep);

                break;
            }
        }}
        fclose(filep);
}
 void Film_ara(){
 	//iþimize yarayacak deðiþkinler tanýmlandý.
	struct film_bilgileri arama = {"","","","",0};
	FILE *fileptr;
	char filmadi[size];
	char yonetmenadi[size];
	char basroladi[size];
	char senaristadi[size];
	int yil;
	int bulundu=0;
	char secim;
			
	if((fileptr=fopen("filmveritabaný.dat","r"))==NULL)
        {
            printf("Dosya bulunamadý-__-");
        }
        
    else
        {
        	
    printf("\nFilm adýna göre arama:1\n");
    printf("Filmin yönetmenine göre arama:2\n");
    printf("Filmin baþrol oyuncusuna göre arama:3\n");
    printf("Filmin senaristine göre arama:4\n");
    printf("Filmin yayýnlanma yýlýna göre arama:5\n");
    printf("Çýkýþ yapmak için:0\n");
    
    printf("\nMenudekilerden Birini Seçiniz.\n");
    scanf("%d",&secim);
	    	
    switch(secim){    	
	case 1:		
		fflush(stdin);
		printf("Aradýðýnýz filmin adýný giriniz:");
        gets(filmadi);            
	while(!feof(fileptr))
        {            
            fread(&arama,sizeof(filmler),1,fileptr);
            if((strcmp(arama.film_adi,filmadi))==0)
                {
                	bulundu++;
                    printf("|----------Arama--Sonucu------------|\n\n"
                    "Aradýðýnýz Ýsimdeki Filmler\n\n"
                    "Filmin adý : %s\nFilmin yönetmeni : %s\nFilmin baþrolü : %s\nFilmin senaristi : %s\nYayýnlanma yýlý : %d\n"
					,arama.film_adi,arama.yonetmen,arama.basrol,arama.senarist,arama.yil);										
                }
        }
        if(bulundu > 0)
		{
            printf("\n%d Tane film bulundu^__^",bulundu);	
		}
		else
		{
		    printf("\nHiçbir film bulunamadý-__-");	
		}        
	break;	
	case 2:		
		fflush(stdin);
		printf("Aradýðýnýz yönetmeninin adýný giriniz:");
        gets(yonetmenadi);            
	while(!feof(fileptr))
        {            
            fread(&arama,sizeof(filmler),1,fileptr);
            if((strcmp(arama.yonetmen,yonetmenadi))==0)
                {
                	bulundu++;
                    printf("|----------Arama--Sonucu------------|\n\n"
                    "Aradýðýnýz Yönetmenin Filmleri\n\n"
                    "Filmin adý : %s\nFilmin yönetmeni : %s\nFilmin baþrolü : %s\nFilmin senaristi : %s\nYayýnlanma yýlý : %d\n"
					,arama.film_adi,arama.yonetmen,arama.basrol,arama.senarist,arama.yil);										
                }
        }
        if(bulundu > 0)
		{
            printf("\n%d Tane film bulundu^__^",bulundu);	
		}
		else
		{
		    printf("\nHiçbir film bulunamadý-__-");	
		}	
	break;			
	case 3:		
		fflush(stdin);
		printf("Aradýðýnýz basrolun adýný girin:");
        gets(basroladi);           
	while(!feof(fileptr))
        {            
            fread(&arama,sizeof(filmler),1,fileptr);
            if((strcmp(arama.basrol,basroladi))==0)
                {
                	bulundu++;
                    printf("|----------Arama--Sonucu------------|\n\n"
                    "Aradýðýnýz Baþrolün Filmleri\n\n"
                    "Filmin adý : %s\nFilmin yönetmeni : %s\nFilmin baþrolü : %s\nFilmin senaristi : %s\nYayýnlanma yýlý : %d\n"
					,arama.film_adi,arama.yonetmen,arama.basrol,arama.senarist,arama.yil);										
                }
        }
        if(bulundu > 0)
		{
            printf("\n%d Tane film bulundu^__^",bulundu);	
		}
		else
		{
		    printf("\nHiçbir film bulunamadý-__-");	
		}		
	break;	
	case 4:	
		fflush(stdin);
		printf("Aradýðýnýz senaristin adýný girin:");
        gets(senaristadi);            
	while(!feof(fileptr))
        {            
            fread(&arama,sizeof(filmler),1,fileptr);
            if((strcmp(arama.senarist,senaristadi))==0)
                {
                	bulundu++;
                    printf("|----------Arama--Sonucu------------|\n\n"
                    "Aradýðýnýz Senaristin Filmleri\n\n"
                    "Filmin adý : %s\nFilmin yönetmeni : %s\nFilmin baþrolü : %s\nFilmin senaristi : %s\nYayýnlanma yýlý : %d\n"
					,arama.film_adi,arama.yonetmen,arama.basrol,arama.senarist,arama.yil);										
                }
        }
        if(bulundu > 0)
		{
            printf("\n%d Tane film bulundu^__^",bulundu);	
		}
		else
		{
		    printf("\nHiçbir film bulunamadý-__-");	
		}		
	break;	
	case 5:
	
		fflush(stdin);
		printf("Aradýðýnýz yýlý girin:");
        scanf("%d",&yil);            
	while(fread(&arama,sizeof(filmler),1,fileptr))
        {            
            if(yil != 0){
            	if(arama.yil == yil)
                {
                	bulundu++;
                    printf("|----------Arama--Sonucu------------|\n\n"
                    "Aradýðýnýz Yýldaki Filmler\n\n"
                    "Filmin adý : %s\nFilmin yönetmeni : %s\nFilmin baþrolü : %s\nFilmin senaristi : %s\nYayýnlanma yýlý : %d\n"
					,arama.film_adi,arama.yonetmen,arama.basrol,arama.senarist,arama.yil);										
                }
			}            
        }
        if(bulundu > 0)
		{
            printf("\n%d Tane film bulundu^__^",bulundu);	
		}
		else
		{
		    printf("\nHiçbir film bulunamadý-__-");	
		}		
	break;	
	case 0:
		printf("Ana menüye dönüyorsunuz.");
	break;	
	default :	
	printf("Gecersiz bir deger girdiniz-__-\n\n");
	break;			
    }
        }
    fclose(fileptr);		        
}
