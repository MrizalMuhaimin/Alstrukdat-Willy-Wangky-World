/* NIM: 13519040
Nama: Shafira Naya Aprisadianti
Tanggal: 21 Oktober 2020
Topik: Pra praktikum 8
Deskripsi: implementasi stack
*/

/* File : stackt.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */


#include "../boolean/boolean.h"
#include <stdio.h>
#include "stackt.h"

Stack stackExecute;

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty (Stack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxElS */
/* jadi indeksnya antara 0.. MaxElS */
/* Ciri stack kosong : TOP bernilai Nil */
{
    Top(*S)=Nil;
}
/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack (Stack S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
    return(Top(S)==Nil);
}
boolean IsFullStack (Stack S)
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
{
    return(Top(S)==(MaxElS-1));
}
/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, aksi X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
    Top(*S)++;
    InfoTop(*S)=X;
}
/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, aksi* X)
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
    *X=InfoTop(*S);
    Top(*S)--;
}

/* Operasi-operasi lain */
void CopyStack (Stack Sin, Stack *Sout)
/* Membuat salinan Sin */
/* I.S. Sin terdefinisi, Sout sembarang */
/* F.S. Sout berisi salinan Sin yang identik */
{
    Stack Stemp;
    aksi X;
    CreateEmpty(&Stemp);
    CreateEmpty(Sout);
    while (!IsEmptyStack(Sin)) {
        Pop(&Sin,&X);
        Push(&Stemp,X);
    }
    while (!IsEmptyStack(Stemp)) {
        Pop(&Stemp,&X);
        Push(Sout,X);
    }
}

void InverseStack (Stack S) {
    Stack Stemp1;
    Stack Stemp2;
    aksi X;
    CreateEmpty(&Stemp1);
    CreateEmpty(&Stemp2);
    while (!IsEmptyStack(S)) {
        Pop(&S,&X);
        Push(&Stemp1,X);
    }
    while (!IsEmptyStack(Stemp1)) {
        Pop(&Stemp1,&X);
        Push(&Stemp2,X);
    }
    while (!IsEmptyStack(Stemp2)) {
        Pop(&Stemp2,&X);
        Push(&S,X);
    }
}
void PrintStack (Stack S) { // Ini biar ngebantu aja
    aksi X;
    if (IsEmptyStack(S)) {
        printf("\nStacknya kosong\n") ; 
    }
    else {
        while (!IsEmptyStack(S)) {
            aksi top = InfoTop(S);
            printf("Uang yang dibutuhkan per aksi: %d\n", top.uang);
            printf("Durasi yang dibutuhkan per aksi: %d\n", top.durasi);
            Pop(&S,&X);
        }
    }
}

int SumDurasiStack (Stack S) {
    int sum=0;
    aksi X;
    while (!IsEmptyStack(S)) {
        sum += (InfoTop(S)).durasi;
        Pop(&S,&X);
    }
    return sum;
}

int SumUangStack (Stack S) {
    int sum=0;
    aksi X;
    while (!IsEmptyStack(S)) {
        sum += (InfoTop(S)).uang;
        Pop(&S,&X);
    }
    return sum;
}

int NbElmtStack (Stack S) {
    int count=0;
    aksi X;
    while (!IsEmptyStack(S)) {
        count += 1;
        Pop(&S,&X);
    }
    return count;
}

void PrintUpgraded(addressWahanaS prevWahana, addressWahanaS nextWahana) {
    // INI BUAT NGETEST
    printf("\nUpgraded!\n");
    printf("Nama wahana yang baru   : ");PrintKata(NamaWahana(nextWahana));printf("\n");
    printf("Deskripsi               : ");PrintKata(DescWahana(nextWahana));printf("\n");
    printf("Nama wahana sebelumnya  : ");PrintKata(NamaWahana(prevWahana));printf("\n");
}

void UpgradeStack(addressWahanaS prevWahana, addressWahanaS nextWahana) {
/* FUNGSI INI UNTUK NGE PUSH AKSI UPGRADE KE STACK */
/* IF AND ONLY IF UPGRADENYA BERHASIL (RESOURCES DAN UANG CUKUP !!! ) */
        aksi aksiUpgrade;
        Kata kataUpgrade;
		kataUpgrade.TabKata[0]='U';
		kataUpgrade.TabKata[1]='p';
		kataUpgrade.TabKata[2]='g';
		kataUpgrade.TabKata[3]='r';
		kataUpgrade.TabKata[4]='a';
		kataUpgrade.TabKata[5]='d';
		kataUpgrade.TabKata[6]='e';
		kataUpgrade.TabKata[7]='\n';
		kataUpgrade.Length = 6;

        aksiUpgrade.commandStack = kataUpgrade;
        aksiUpgrade.durasi = 240; // setiap upgrade butuh waktu 240 menit (2 jam)
        addressWahanaD elmtDin = SearchWahanaD(NamaWahana(nextWahana),WahanaBuilt);
        aksiUpgrade.PointWahana = PositionWahana(elmtDin);
        aksiUpgrade.MapNumAksi = PetaWahana(elmtDin);
        aksiUpgrade.NamaBahan = BahanWahana(nextWahana);
        aksiUpgrade.JumlahBahan = JmlBahan(nextWahana);
        aksiUpgrade.uang = UpgradeCost(prevWahana);
        aksiUpgrade.addrPrevWahana = prevWahana; 
        PushE(&stackExecute,aksiUpgrade);
}


    
void PrintInfoStack (Stack S) {
    if(IsEmptyStack(S)){
        printf("           Tidak ada aksi yang akan dilakukan\n");
    }else{
        printf("           Total aksi yang akan dilakukan: %d",NbElmtStack(S));
        printf("\n");
        printf("           Total waktu yang akan dibutuhkan:\n");
        printf("          ");TulisTimeRemaining(SumDurasiStack(S));
        printf("\n");   
        printf("           Total uang yang dibutuhkan: %d",SumUangStack(S));
        printf("\n");   
    }
 
}

boolean UangCukup (player *P, int harga) {
    return(Money(*P)>=harga);
}

boolean BahanCukup (player *P, Kata NamaBahan, int JumlahBahan) {
    return (SearchB(Tab(*P),NamaBahan,JumlahBahan));
}

boolean SemuaCukup (player *P, Kata NamaBahan, int JumlahBahan, int BiayaUpgrade) {
    return (UangCukup(P,BiayaUpgrade) && BahanCukup(P,NamaBahan,JumlahBahan));
}

void PushE(Stack * S, aksi X)
{
  int Time, Total;
  Stack ST = *S;
  Time = SumDurasiStack(ST);
  Total = Time + X.durasi;
  if( Total <= 720){
    Push (S,X);
  }
  else
  {
    printf("Total durasi aksi melebihi Time Remaining\n");
  }
  
}
