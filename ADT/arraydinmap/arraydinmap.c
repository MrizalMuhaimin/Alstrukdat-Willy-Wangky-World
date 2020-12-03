#include <stdio.h>
#include <stdlib.h>
#include "arraydinmap.h"
#include "../mesinkata/mesinkata.h"
#include "../mesinkar/mesinkar.h"

/* ********** SELEKTOR ********** */
// #define Neff(T) (T).Neff
// #define TI(T) (T).TI
// #define Elmt(T, i) (T).TI[(i)]
// #define MaxEl(T) (T).MaxEl

/* ********** KONSTRUKTOR ********** */
Tab File_material;
/* Konstruktor : create tabel kosong  */
void MakeEmptyDin(Tab *T, int maxel)
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */
{

    // Kamus

    // ALGORITMA
    MaxElMap(*T) = maxel;
    Neff(*T) = 0;
    TI(*T) = (MapEntry *) malloc(maxel * sizeof(MapEntry));
}

void Dealokasi(Tab *T)
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxEl(T)=0; Neff(T)=0 */
{
    MaxElMap(*T) = 0;
    Neff(*T) = 0;
    free(TI(*T));
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmtDin(Tab T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
{
    return Neff(T);
}

int MaxElement(Tab T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
{
    return MaxElMap(T);
}
/* *** Selektor INDEKS *** */
IdxType GetFirstIdxDin(Tab T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
    return IdxMin;
}

IdxType GetLastIdxDin(Tab T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
    return Neff(T)-1;
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValidDin(Tab T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    return i >= 0 && i < MaxElMap(T);
}

boolean IsIdxEffDin(Tab T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
    return i >= GetFirstIdxDin(T) && i <= GetLastIdxDin(T);
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmptyDin(Tab T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
    return Neff(T) == 0;
}

/* *** Test tabel penuh *** */
boolean IsFullDin(Tab T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
    return Neff(T) == MaxElMap(T);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi(Tab *T)
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxElement(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
{
    // Kamus
    int N;
    int i;

    // Algoritma
    printf("Masukkan nilai N: ");
    do {
        scanf("%d", &N);
    } while (N<0 || N>MaxElMap(*T));
    Neff(*T) = N;
    printf("Masukkan input tabel: \n");
    printf("Untuk key:\n");
    STARTKATA();
    CopyKata(CKata,&Elmt(*T,0).key);
    for (i=0; i<N; i++){
        printf("Key: ");
        STARTKATA();
        CopyKata(CKata,&Elmt(*T,i).key);
    } ADVKATA(); 
    printf("Untuk value:\n");
    for (i=IdxMin; i<IdxMin+N; i++){
        printf("Value: ");
        scanf("%d", &Elmt(*T,i).value);
    }
}

void TulisIsiTab(Tab T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{
    // Kamus Lokal
    int i;
    // Algoritma
    if(!IsEmptyDin(T)){
        printf("           Daftar bahan yang dimiliki:\n");
        for (i=GetFirstIdxDin(T); i<=GetLastIdxDin(T); i++){
            printf("           ");
            PrintKata(Elmt(T,i).key);
            printf(" - ");
            printf("%d",Elmt(T,i).value);
            printf("\n");
        }
    } else {
        printf("           Anda tidak memiliki bahan apapun\n");
    }
}


void BacaIsiMaterial(Tab *T)
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* NOTE: PROSEDUR INI BUAT BACA FILE EXTERNAL TERUS BIKIN TABELNYA */
{
    MakeEmptyDin(T,30);
    STARTKATAFILE("Files/material.txt"); // Gabisa dijalanin dari driver_arraydinmap ganti "../../Files/material.txt"
	int count = 0;
    int i=0;
	SalinKataFile();
	while (!EndKata){
		Kata k;
		int v;
		if (i % 2 == 0) {
			CopyKata(CKata, &k);
		} 
        else {
			v = convToInt(CKata);
		}
		if (CC == EOL){
            AddAsLastEl(T, k, v);
			ADV();
		}
		i ++; 
		ADVKATAFILE();
    }
/* 
    for (i=IdxMin; i<IdxMin+N; i++){
        printf("Masukkan key: ");
  //
    }
    
    for (i=IdxMin; i<IdxMin+N; i++){
            printf("masukkan value:" );
            scanf("%d", &Elmt(*T,i).value);
    }
*/
}
/* 
	Map File_Buy;
	CreateEmptyMap (&File_Buy);
	STARTKATAFILE("../../Files/material.txt");
	int count = 0;
	SalinKataFile();

	while( ! EndKata){
		Kata keyKata;
		int val;
		if (count % 2 == 0 ){
			CopyKata (CKata, &keyKata);
			
		} else{
			val = convToInt (CKata);
			Insert (&File_Buy, keyKata, val);
		}
		if (CC == EOL){
			ADV();
		}
		count ++;
		ADVKATAFILE();
	} */
void TulisIsiTabMaterial(Tab T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T titak kosong */
/* F.S. Mencetak dengan format: <NamaBahan> <HargaBahan> susun ke bawah */
{
    // Kamus Lokal
    int i;
    // Algoritma
    printf("Ingin Membangun Apa? \n<NamaBahan> <Harga>\n");
    if(!IsEmptyDin(T)){
        for (i=GetFirstIdxDin(T); i<=GetLastIdxDin(T); i++){
            printf("    - ");
            PrintKata(Elmt(T,i).key);
            printf(" %d",Elmt(T,i).value);
            printf("\n");
        }
    }
}


/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
boolean IsEQ(Tab T1, Tab T2)
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika Neff T1 = T2 dan semua elemennya sama */
{
    // Kamus Lokal
    boolean ans;
    int i;

    // Algoritma
    if (NbElmtDin(T1) != NbElmtDin(T2)) return false;
    
    // else
    ans = true;
    i = GetFirstIdxDin(T1);

    while (i<=GetLastIdxDin(T1) && ans){
        if (!IsKataSamaKata(Elmt(T1,i).key,Elmt(T2,i).key)) ans=false;
        //if(Elmt(T1,i).key != Elmt(T2,i).key) ans=false;
        if(Elmt(T1,i).value != Elmt(T2,i).value) ans=false;
        i++;
    }
    
    return ans;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType Search1(Tab T, keyType k, valType v)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
/* KAYAKNYA GAPERLU SIH */
{
    // Kamus Lokal
    int ans;
    int i;

    // Algoritma
    if(NbElmtDin(T) == 0) return IdxUndef;

    // else
    ans = IdxUndef;
    i = GetFirstIdxDin(T)-1;

    do{
        i++;
        if (IsKataSamaKata(Elmt(T,i).key,k)){
            ans = i;
        }
    } while (i<=GetLastIdxDin(T)&& (!IsKataSamaKata(Elmt(T,i).key,k)));
    
    return ans;
}

valType SearchVal(Tab T, keyType k)
/* Search apakah ada elemen tabel T yang keynya adalah k */
/* Jika ada, menghasilkan value elemen tabel T yang keynya adalah k */
/* Jika tidak ada atau tabel kosong, mengirimkan -1 */
/* Skema Searching yang digunakan bebas */
{
    // Kamus Lokal
    int ans;
    int i;

    // Algoritma
    if(NbElmtDin(T) == 0) return -1; // Kalo gaketemu, return -1
    // else
    ans = -1;
    i = GetFirstIdxDin(T)-1;

    do{
        i++;
        if (IsKataSamaKata(Elmt(T,i).key,k)){
            ans = Elmt(T,i).value;
        }
    } while (i<=GetLastIdxDin(T)&& (!IsKataSamaKata(Elmt(T,i).key,k)));
    
    return ans;
}

boolean SearchB(Tab T, keyType k, valType v)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
/* NOTE: NANTI BAKAL BIKIN FUNGSI UNTUK NGECEK PERSEDIAAN (?) (kalo bakal disimpen di arraydin), JADI CEK VALUENYA JUGA. */
// Semoga bener
{
    // Kamus Lokal
    boolean ans;
    int i;

    // Algoritma
    ans=false;
    i=GetFirstIdxDin(T)-1;

    do{
        i++;
        if(IsKataSamaKata(Elmt(T,i).key,k) && (Elmt(T,i).value >= v)) {
            ans = true;
        }
    } while (i<=GetLastIdxDin(T) && (!IsKataSamaKata(Elmt(T,i).key,k)));

    return ans;

    /* 
    // Kamus Lokal
    boolean ans;
    int i;

    // Algoritma
    ans=false;
    i=GetFirstIdxDin(T)-1;

    do{
        i++;
        if(IsKataSamaKata(Elmt(T,i).key,k) && (Elmt(T,i).val>=v)) {
            ans = true;
        }
    } while (i<=GetLastIdxDin(T) && (!IsKataSamaKata(Elmt(T,i).key,k) && (Elmt(T,i).val<v)));

    return ans;
    */
}

boolean SearchK(Tab T, keyType k)
/* mengembalikan true jika key ada di Tap T */
{
    int i = 0;
    while (i < Neff(T) && !IsKataSamaKata(Elmt(T, i).key,k))
    {
        i++;
        
    }
    return IsKataSamaKata(Elmt(T, i).key,k);
    
}


/* ********** OPERASI LAIN ********** */
void CopyTab(Tab Tin, Tab *Tout)
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */
{
    // Kamus
    int i;

    // Algoritma
    MakeEmptyDin(Tout, MaxElMap(Tin));
    for (i=0; i< Neff(Tin); i++){
        Elmt(*Tout, i).key = Elmt(Tin, i).key;
        Elmt(*Tout, i).value = Elmt(Tin, i).value;
        Neff(*Tout)++;
    }
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl(Tab *T, keyType k, valType v)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

{
    // Algoritma
    if(IsEmptyDin(*T)) {
        Elmt(*T, IdxMin).key = k;
        Elmt(*T, IdxMin).value = v;
    }
    else{
        Elmt(*T, Neff(*T)).key = k;
        Elmt(*T, Neff(*T)).value = v;
    }

    Neff(*T)++;
}

void AddElTab(Tab *T, keyType k, valType v)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

{
    // Algoritma
    if(IsEmptyDin(*T)) {
        Elmt(*T, IdxMin).key = k;
        Elmt(*T, IdxMin).value = v;
        Neff(*T) ++;
    }
    else{
        if (SearchK(*T,k)) { // kalo udah ada
            IdxType indeks = Search1(*T,k,v);
            Elmt(*T,indeks).value = Elmt(*T,indeks).value + v;
        }
        else { // add as last el
            Elmt(*T, Neff(*T)).key = k;
            Elmt(*T, Neff(*T)).value = v;
            Neff(*T)++;
        }
    }

}
/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl(Tab *T, keyType *k, valType *v)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
    // Algoritma
    k = &Elmt(*T, GetLastIdxDin(*T)).key;
    v = &Elmt(*T, GetLastIdxDin(*T)).value;
    Neff(*T)--;

}

void DelElTab (Tab *T, keyType k, valType v) {
    if (SearchB(*T,k,v)) { // kalo ketemu >=
        IdxType indeks = Search1(*T,k,v);
        if (v == (Elmt(*T,indeks).value)) { // kalau jumlahnya sama, otomatis jadi 0.

            Neff(*T)--;
        }
        else { // jumlahnya lebih
            Elmt(*T,indeks).value = Elmt(*T,indeks).value - v;
        }
    }
    else { // kalo gak ketemu
        printf("Tidak ada elemen dengan key tersebut dalam tabel.\n"); // harusnya sih ketemu
    }
}