#include <stdio.h>
#include <stdbool.h>
#include <string.h>

enum oncelik {
    DUSUK=1,
    ORTA,
    YUKSEK,
};
enum durum {
    TAMAMLANDI=1,
    DEVAM_EDİYOR,
};
enum kategori {
    YAZILIM=1,
    KISISEL,
    OKUL,
    IS,
};
struct gorev {
    char gorevIsmi[25];
    char sonTarih[20];
    enum oncelik oncelik;
    enum durum durum;
    enum kategori kategori;
};
struct gorev p;
struct gorev *ptr=&p;
void gorevEkle() {
    printf("Gorev ekle;\n");
        printf("Gorev ismini giriniz: ");
        scanf("%s",ptr->gorevIsmi);
        printf("Gorev icin son tarihi giriniz: ");
        scanf("%s",ptr->sonTarih);
        printf("Onceligi seciniz: ");
        printf("1-Dusuk\n2-Orta\n3-Yuksek\n");
        scanf("%d",(int *)&ptr->oncelik);
        printf("Durumu giriniz: ");
        printf("1-Tamamlandi\n2-Devam Ediyor\n");
        scanf("%d",(int *)&ptr->durum);
        printf("Kategoroyi seciniz: ");
        printf("1-Yazilim\n2-Kisisel\n3-Okul\n4-Is\n");
        scanf("%d",(int *)&ptr->kategori);
}
void dosyayaKaydet() {
    FILE* fptr;
    fptr=fopen("gorev.txt","a");
    if (fptr==NULL) {
        perror("Dosya basarisiz\n");
        return;
    }
    fprintf(fptr,"%s %s %d %d %d\n",ptr->gorevIsmi,ptr->sonTarih,ptr->oncelik,ptr->durum,ptr->kategori);
    fclose(fptr);
    printf("Gorev dosyaya kaydedildi\n");
}
void goreviListele() {
    FILE* fptr;
    fptr=fopen("gorev.txt","r");
    if(fptr==NULL) {
        perror("Dosya basarisiz\n");
    }
    else {
        while(fscanf(fptr,"%s %s %d %d %d",ptr->gorevIsmi,ptr->sonTarih,&ptr->oncelik,&ptr->durum,&ptr->kategori)==5) {
            printf("Gorev listesi: %s %s %d %d %d\n",ptr->gorevIsmi,ptr->sonTarih,ptr->oncelik,ptr->durum,ptr->kategori);
        }
    }
    fclose(fptr);
}
void gorevAra() {
    char arananGorevIsmi[25];
    bool bulundu=false;
    FILE* fptr;
    fptr=fopen("gorev.txt","r");
    if(fptr==NULL) {
        perror("Dosya basarisiz\n");
    }
    else {
        printf("Aranan mevcut gorev ismini giriniz ");
        scanf("%s",arananGorevIsmi);
        while(fscanf(fptr,"%s %s %d %d %d",ptr->gorevIsmi,ptr->sonTarih,&ptr->oncelik,&ptr->durum,&ptr->kategori)==5) {
        if(strcmp(arananGorevIsmi,ptr->gorevIsmi)==0) {
            bulundu=true;
            printf("Aranan mevcut gorev ismi bulundu\n");
        }
        }
        if (bulundu==false) {
            printf("Aranan mevcut gorev ismi bulunamadi\n");
        }
    }
    fclose(fptr);
}
void gorevSil() {
    char silinecekGorevIsmi[25];
    bool bulundu=false;
    FILE* fptr;
    FILE* gecici;
    fptr=fopen("gorev.txt","r");
    gecici=fopen("gecici.txt","w");
    if(fptr==NULL || gecici==NULL) {
        perror("Dosya basarisiz\n");
        if (fptr!=0) {
            fclose(fptr);
        }
        if (gecici!=0) {
            fclose(gecici);
        }
        return;
    }
        printf("Silinecek mevcut gorev ismini giriniz ");
        scanf("%s",silinecekGorevIsmi);
    while(fscanf(fptr,"%s %s %d %d %d",ptr->gorevIsmi,ptr->sonTarih,&ptr->oncelik,&ptr->durum,&ptr->kategori)==5) {
        if (strcmp(silinecekGorevIsmi,ptr->gorevIsmi)==0) {
            bulundu=true;
        }
            else {
                fprintf(gecici,"%s %s %d %d %d\n",ptr->gorevIsmi,ptr->sonTarih,ptr->oncelik,ptr->durum,ptr->kategori);
            }
    }
        fclose(fptr);
        fclose(gecici);
        remove("gorev.txt");
        rename("gecici.txt","gorev.txt");
        if (bulundu==true) {
            printf("Silinecek mevcut gorev ismi bulundu ve silindi\n");
        }
        if (bulundu==false) {
            printf("Silinecek mevcut gorev ismi bulunamadi ve silinemedi\n");
        }
}
void goreviGuncelle() {
    char guncelleSonTarih[20];
    char yeniSonTarih[20];
    bool bulundu=false;
    FILE* fptr;
    FILE* gecici;
    fptr=fopen("gorev.txt","r");
    gecici=fopen("gecici.txt","w");
    if(fptr==NULL || gecici==NULL) {
        perror("Dosya basarisiz\n");
        if (fptr!=0) {
            fclose(fptr);
        }
        if (gecici!=0) {
            fclose(gecici);
        }
        return;
    }
    printf("Guncellenecek mevcut son tarihi giriniz ");
    scanf("%s",guncelleSonTarih);
    printf("Guncellenecek yeni son tarihi giriniz: ");
    scanf("%s",yeniSonTarih);
    while(fscanf(fptr,"%s %s %d %d %d",ptr->gorevIsmi,ptr->sonTarih,&ptr->oncelik,&ptr->durum,&ptr->kategori)==5) {
        if (strcmp(guncelleSonTarih,ptr->sonTarih)==0) {
            bulundu=true;
            fprintf(gecici,"%s %s %d %d %d\n",ptr->gorevIsmi,yeniSonTarih,ptr->oncelik,ptr->durum,ptr->kategori);
        }
        else {
            fprintf(gecici,"%s %s %d %d %d\n",ptr->gorevIsmi,ptr->sonTarih,ptr->oncelik,ptr->durum,ptr->kategori);
        }
    }
        fclose(fptr);
        fclose(gecici);
        remove("gorev.txt");
        rename("gecici.txt","gorev.txt");
        if (bulundu==true) {
            printf("Guncellenecek mevcut son tarih bulundu ve guncellendi\n");
        }
        if (bulundu==false) {
            printf("Guncellencek mevcut son tarih bulunamadi ve guncellenemedi\n");
        }
}
void tamamlananlariGoster() {
    FILE* fptr;
    fptr=fopen("gorev.txt","r");
    if (fptr==NULL) {
        perror("Dosya basarisiz\n");
    }
    else {
        while(fscanf(fptr,"%s %s %d %d %d",ptr->gorevIsmi,ptr->sonTarih,&ptr->oncelik,&ptr->durum,&ptr->kategori)==5) {
            if (ptr->durum==TAMAMLANDI) {
                printf("Tamamlananlar: %s %s %d %d %d\n",ptr->gorevIsmi,ptr->sonTarih,ptr->oncelik,ptr->durum,ptr->kategori);
            }
        }
    }
    fclose(fptr);
}
void durumTamamlandi() {
    char tamamlanacakGorevIsmi[25];
    bool bulundu=false;
   FILE *fptr;
   FILE *gecici;
    fptr=fopen("gorev.txt","r");
    gecici=fopen("gecici.txt","w");
    if(fptr==NULL || gecici==NULL) {
        perror("Dosya basarisiz\n");
        if (fptr!=0) {
            fclose(fptr);
        }
        if (gecici!=0) {
            fclose(gecici);
        }
        return;
    }
    printf("Tamamlanacak gorevin ismini giriniz ");
    scanf("%s",tamamlanacakGorevIsmi);
    while(fscanf(fptr,"%s %s %d %d %d",ptr->gorevIsmi,ptr->sonTarih,&ptr->oncelik,&ptr->durum,&ptr->kategori)==5) {
        if (strcmp(tamamlanacakGorevIsmi,ptr->gorevIsmi)==0) {
            bulundu=true;
            ptr->durum=TAMAMLANDI;
            fprintf(gecici,"%s %s %d %d %d\n",ptr->gorevIsmi,ptr->sonTarih,ptr->oncelik,ptr->durum,ptr->kategori);
        }
    }
    fclose(fptr);
    fclose(gecici);
    remove("gorev.txt");
    rename("gecici.txt","gorev.txt");
    if (bulundu==true) {
        printf("Tamamlanacak mevcut gorev ismi bulundu,durum tamamlandi\n");
    }
if (bulundu==false) {
    printf("Tamamlanacak mevcut gorev ismi bulunamadi,durum tamamlanamadi\n");
}
}
void cikis() {
    printf("Cikis yapilmistir\n");
}
    int main() {
        int sec;
        do{
            printf("-----------------------------------------------------------------------------\n");
            printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>Gorev Yonetim Sistemi<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            printf("-----------------------------------------------------------------------------\n");
            printf("1-Gorev bilgileri\n");
            printf("2-Dosyaya kaydet\n");
            printf("3-Gorevi listele\n");
            printf("4-Gorevi isme gore ara\n");
            printf("5-Gorevi isme gore sil\n");
            printf("6-Gorevi son tarihe gore guncelle\n");
            printf("7-Tamamlananlari goster\n");
            printf("8-Durumu tamamlandi olarak isaretleme\n");
            printf("9-Cikis\n");
            printf("1 ile 9 Lutfen arasinda bir secim yapiniz: \n");
            scanf("%d",&sec);
            switch(sec) {
                case 1:gorevEkle();
                    break;
                case 2:dosyayaKaydet();
                    break;
                case 3:goreviListele();
                break;
                case 4:gorevAra();
                    break;
                case 5:gorevSil();
                    break;
                case 6:goreviGuncelle();
                    break;
                case 7:tamamlananlariGoster();
                    break;
                case 8:durumTamamlandi();
                    break;
                case 9:cikis();
                    break;
            }
        }while(sec!=9);
        return 0;
    }