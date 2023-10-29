#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Ogrenci yapısı tanımlandı
struct Ogrenci {
    int ogrenci_no;   // Öğrenci numarası
    char ad[80];      // Öğrenci adı
    int yas;          // Öğrenci yaş
    struct Ogrenci *sonraki;
};

struct Ogrenci *bas = NULL;  // Bağlı liste başlangıç düğümü

// Yeni bir öğrenci ekleme fonksiyonu
void ogrenciEkle(int ogrenci_no, char ad[], int yas) {
    struct Ogrenci *yeniOgrenci = (struct Ogrenci *)malloc(sizeof(struct Ogrenci));
    yeniOgrenci->ogrenci_no = ogrenci_no;
    strcpy(yeniOgrenci->ad, ad);
    yeniOgrenci->yas = yas;
    yeniOgrenci->sonraki = NULL;

    if (bas == NULL) {
        bas = yeniOgrenci;
    } else {
        struct Ogrenci *gezici = bas;
        while (gezici->sonraki != NULL) {
            gezici = gezici->sonraki;
        }
        gezici->sonraki = yeniOgrenci;
    }
}

// Öğrencileri ekranda gösterme fonksiyonu
void ogrencileriGoruntule() {
    struct Ogrenci *gezici = bas;
    int index = 1;
    while (gezici != NULL) {
        printf("%d- %s %d %d\n", index, gezici->ad, gezici->yas, gezici->ogrenci_no);
        gezici = gezici->sonraki;
        index++;
    }
}

// Öğrenci numarasına göre öğrencileri başa ve sona ekleme fonksiyonu
void numaralariBasaVeSonaEkle() {
    struct Ogrenci *gezici = bas;
    struct Ogrenci *tek_bas = NULL;
    struct Ogrenci *cift_bas = NULL;

    while (gezici != NULL) {
        struct Ogrenci *sonraki = gezici->sonraki;
        if (gezici->ogrenci_no % 2 == 1) {
            gezici->sonraki = tek_bas;
            tek_bas = gezici;
        } else {
            gezici->sonraki = cift_bas;
            cift_bas = gezici;
        }
        gezici = sonraki;
    }

    gezici = tek_bas;
    if (gezici == NULL) {
        bas = cift_bas;
    } else {
        while (gezici->sonraki != NULL) {
            gezici = gezici->sonraki;
        }
        gezici->sonraki = cift_bas;
        bas = tek_bas;
    }
}

// Öğrencileri isme göre sıralama fonksiyonu
void ismeGoreOgrencileriSirala() {
    struct Ogrenci *gezici, *index;
    char gecici_ad[50];
    int gecici_yas, gecici_ogrenci_no;

    if (bas == NULL) {
        printf("Liste bos\n");
        return;
    } else {
        for (gezici = bas; gezici != NULL; gezici = gezici->sonraki) {
            for (index = gezici->sonraki; index != NULL; index = index->sonraki) {
                if (strcmp(gezici->ad, index->ad) > 0) {
                    strcpy(gecici_ad, gezici->ad);
                    strcpy(gezici->ad, index->ad);
                    strcpy(index->ad, gecici_ad);

                    gecici_yas = gezici->yas;
                    gezici->yas = index->yas;
                    index->yas = gecici_yas;

                    gecici_ogrenci_no = gezici->ogrenci_no;
                    gezici->ogrenci_no = index->ogrenci_no;
                    index->ogrenci_no = gecici_ogrenci_no;
                }
            }
        }
    }
}

// İsmi verilen öğrenciyi arama fonksiyonu
void ismeGoreOgrenciAra(char ad[]) {
    struct Ogrenci *gezici = bas;
    int bulundu = 0;
    while (gezici != NULL) {
        if (strcmp(gezici->ad, ad) == 0) {
            printf("Ogrenci bulundu: %d- %s %d %d\n", gezici->ogrenci_no, gezici->ad, gezici->yas, gezici->ogrenci_no);
            bulundu = 1;
            break;
        }
        gezici = gezici->sonraki;
    }
    if (!bulundu) {
        printf("Ogrenci bulunamadi\n");
    }
}

// İsmi verilen öğrencinin bir sonraki öğrencisini silme fonksiyonu
void ismeGoreBirSonrakiOgrenciyiSil(char ad[]) {
    struct Ogrenci *gezici = bas;
    struct Ogrenci *gecici = NULL;
    int bulundu = 0;

    while (gezici != NULL) {
        if (strcmp(gezici->ad, ad) == 0) {
            if (gezici->sonraki != NULL) {
                gecici = gezici->sonraki;
                gezici->sonraki = gezici->sonraki->sonraki;
                free(gecici);
                bulundu = 1;
                printf("%s'in sonraki ogrencisi silindi\n", ad);
            } else {
                printf("%s'in sonraki ogrencisi yok\n", ad);
            }
            break;
        }
        gezici = gezici->sonraki;
    }

    if (!bulundu) {
        printf("Ogrenci bulunamadi\n");
    }
}

// En uzun ismi bulma fonksiyonu
void enUzunIsmiBul() {
    struct Ogrenci *gezici = bas;
    char en_uzun_ad[50];
    int max_uzunluk = 0;

    while (gezici != NULL) {
        int uzunluk = strlen(gezici->ad);
        if (uzunluk > max_uzunluk) {
            max_uzunluk = uzunluk;
            strcpy(en_uzun_ad, gezici->ad);
        }
        gezici = gezici->sonraki;
    }

    printf("Listedeki en uzun isim: %s\n", en_uzun_ad);
}

int main() {
    int secim;

    do {
        printf("\nMenu:\n");
        printf("1. Ogrenci ekle\n");
        printf("2. Tum ogrencileri goruntule\n");
        printf("3. Numaralari basa ve sona ekle\n");
        printf("4. Ogrencileri isme gore sirala\n");
        printf("5. Isme gore ogrenci ara\n");
        printf("6. Isme gore bir sonraki ogrenciyi sil\n");
        printf("7. En uzun ismi bul\n");
        printf("0. Cikis\n");
        printf("Seciminizi girin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1: {
                int ogrenci_no, yas;
                char ad[50];
                printf("Ogrenci numarasini girin: ");
                scanf("%d", &ogrenci_no);
                printf("Ismi girin: ");
                scanf("%s", ad);
                printf("Yasi girin: ");
                scanf("%d", &yas);
                ogrenciEkle(ogrenci_no, ad, yas);
                break;
            }
            case 2: {
                ogrencileriGoruntule();
                break;
            }
            case 3: {
                numaralariBasaVeSonaEkle();
                break;
            }
            case 4: {
                ismeGoreOgrencileriSirala();
                break;
            }
            case 5: {
                char arama_ad[50];
                printf("Aranacak ismi girin: ");
                scanf("%s", arama_ad);
                ismeGoreOgrenciAra(arama_ad);
                break;
            }
            case 6: {
                char silme_ad[50];
                printf("Bir sonraki ogrenciyi silmek istediginiz ogrencinin adini girin: ");
                scanf("%s", silme_ad);
                ismeGoreBirSonrakiOgrenciyiSil(silme_ad);
                break;
            }
            case 7: {
                enUzunIsmiBul();
                break;
            }
        }
    } while (secim != 0);

    return 0;
}