/* File : wahana.h */

#ifndef WAHANA_H
#define WAHANA_H

#include "../jam/jam.h"
#include "../point/point.h"
#include "../boolean/boolean.h"
#include "../listlinier/listlinier.h"
#include "../mesinkata/mesinkata.h"
#include "../peta/peta.h"
#include "../player/player.h"
#include "../matriks/matriks.h"

extern boolean EndKata;
extern Kata CKata;
extern char CC;
extern boolean EOP;


typedef struct tElmtWahanaS *addressWahanaS;
/*ElmtWahanaStatis merupakan Node dalam TreeWahanaS, 
datanya berupa data statis dari txt*/
typedef struct tElmtWahanaS {
    int IDWahana;
    Kata NameWahana;
    Kata TipeWahana;
    int PriceWahana;
    Kata DescWahana;
    int CapacityWahana;
    int TimeWahana; //dalam menit
    Kata BahanWahana;
    int JumlahBahan;
    int UpgradeCost; // (tambahan) biaya untuk upgrade
	  addressWahanaS left; //untuk anak kiri
    addressWahanaS right; //untuk anak kanan

} ElmtWahanaStatis;

typedef struct tElmtWahanaD *addressWahanaD;
/*ElmtWahanaDinamis merupakan list linier, 
datanya berupa data dinamis yang berubah2 tergantung pd jalannya program*/
/*Akan terisi jika wahana sudah di bangun*/
//typedef struct infotypeWahana *infotypeW;


typedef struct tElmtWahanaD {
    //int IDWahanaD;
    //Kata NameWahanaD;
    POINT PositionWahana;
    int PetaWahana;
    boolean StatusWahana; //berfungsi : true, rusak: false
    //boolean BuildWahana; // 
    int TotalFreqWahana;
    int IncomeWahana;
    int DailyFreqWahana;
    addressWahanaD next;
    //addressWahanaD prev;
    addressWahanaS ElmtStatis;
} ElmtWahanaDinamis;

typedef struct {
	addressWahanaD First; //pointer ke ElmtWahanaDinamis
} ListWahanaD;

/*TreeWahanaS merupakan tree yang setiap nodenya berisi ElmtWahanaStatis*/
typedef addressWahanaS TreeWahanaS; //ganti jd ini keknya
// typedef struct {
// 	addressWahanaS Root;
// } TreeWahanaS;

// extern addressWahanaS temptree[10];

/*T : TreeWahanaS
  N : Node dari TreeWahanaS, berupa ElmtWahanaStatis
  D : addressWahanaD yang merupakan address list linier ElmtWahanaDinamis*/

#define FirstWahana(L) ((L).First)

#define Root(T) (T).Root
#define Left(N) (N)->left
#define Right(N) (N)->right

#define IDWahana(N) (N)->IDWahana 
#define NamaWahana(N) (N)->NameWahana 
#define TipeWahana(N) (N)->TipeWahana
#define PriceWahana(N) (N)->PriceWahana 
#define DescWahana(N) (N)->DescWahana 
#define CapacityWahana(N) (N)->CapacityWahana 
#define TimeWahana(N) (N)->TimeWahana 
#define BahanWahana(N) (N)->BahanWahana
#define JmlBahan(N) (N)->JumlahBahan
#define UpgradeCost(N) (N)->UpgradeCost

#define PositionWahana(D) (D)->PositionWahana
#define PetaWahana(D) (D)->PetaWahana
#define StatusWahana(D) (D)->StatusWahana 
#define TotalFreqWahana(D) (D)->TotalFreqWahana
#define IncomeWahana(D) (D)->IncomeWahana
#define DailyFreqWahana(D) (D)->DailyFreqWahana
#define NextWahana(D) (D)->next
#define ElmtStatis(D) (D)->ElmtStatis

extern TreeWahanaS UpgradeTree;
extern ListWahanaD WahanaBuilt;

void Details();
/* I.S namaWahana dimasukkan user */
/* F.S Menampilkan detail dari wahana*/

addressWahanaD SearchWahanaD (Kata namaWahana, ListWahanaD L);
/* I.S namaWahana dimasukkan user */
/* F.S Mengembalikan address dnegan wahana yang sesuai dengan yang dicari*/

void SubTree(addressWahanaS parent, addressWahanaS l, addressWahanaS r);
/* Membuat pohon dengan parent, left, right*/

void MakeTree();
/* I.S P adalah tree kosong */
/* F.S P adalah tree berisi ElmtWahanaStatis yang diambil dari file txt */

boolean isSekitarPemain();

addressWahanaD WahanaSekitar();

void Repair(addressWahanaD *W);

void wahanaRusak();

/* Manajemen Memory */
addressWahanaS AlokNode(int i);
/* Mengirimkan addressWahanaS hasil alokasi sebuah Node */
/* Jika alokasi berhasil, maka addressWahanaS tidak Niil, dan misalnya menghasilkan P, 
  maka Left(P) = Niil, Right(P)=Niil */
/* Jika alokasi gagal, mengirimkan Niil */

void DealokNode(addressWahanaS *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressWahanaS P */


/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty(TreeWahanaS T);
/* Mengirimkan true jika P adalah pohon biner kosong */
boolean IsTreeOneElmt(TreeWahanaS T);
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
boolean IsUnerLeft(TreeWahanaS T);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
boolean IsUnerRight(TreeWahanaS T);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
boolean IsBiner(TreeWahanaS T);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/

void initWahana(TreeWahanaS T);
/* Mencetak 3 wahana awal yang dapat dibangun pertama kali*/

void PrintTreeNode(addressWahanaS P);
/* Mencetak node tree dengan address P */

void PrintTree(TreeWahanaS T);
/* Mencetak tree dengan PreOrder */
/*Print PreOrder
[A]Coaster
[B]Helicap
[C]Jungle
[D]Stars
[E]Shotgun
[F]Dancingking
[G]Watersplash
[H]Marinebay
[I]Rush
[J]Liftup

     A
  B     G
C  E   H  J
D  F   I
*/

void buildWahana(POINT Pos, ListWahanaD *L);
/*Command ini digunakan untuk membuat wahana baru di petak di mana
pemain sedang berdiri.
1. Setelah meminta command ini, program akan menampilkan
wahana dasar yang mungkin dibuat (hasil load file eksternal).
2. Setelah pemain memilih wahana dasar yang ingin dibuat.
3. Jika resource untuk membangun wahana tidak mencukupi, maka
akan ditampilkan pesan error. TANPA MASUKKIN KE STACK */

addressWahanaD AlokWahana (POINT P, Kata NamaWahana);
/*membuat node dalam list linier elemen dinamis
untuk build wahana baru*/

//Tadinya buat load tapi gajadi
// addressWahanaD AlokWahanaFile (POINT P, Kata NamaWahana, int TotalFreq, int Income, int DailyFreq, boolean Stat);

boolean SearchTree(Kata X, addressWahanaS P);

boolean IsEmptyListW (ListWahanaD L);

void InsAfterW(ListWahanaD *L, addressWahanaD P, addressWahanaD Prec);

void InsFirstW (ListWahanaD *L, addressWahanaD D);

void PrintInfoWD (ListWahanaD L);

addressWahanaS SearchAddress (TreeWahanaS P, Kata NamWahana);
//Mencari address Statis dari Upgrade Tree (berdasarkan nama yg diinput)

addressWahanaS SearchAddressID (TreeWahanaS P, int num);
//Mencari address Statis dari Upgrade Tree (berdasarkan ID yg diinput)

addressWahanaD SearchWahanaDP (POINT Pos, int MapNum, ListWahanaD L);
//Mencari address Dinamis dari WahanaBuilt (berdasarkan POINT Posisi Wahana yg diinput)

//random ID wahana yang rusak dari ID 1-10
//cari address statis P dan address dinamis D yang bersesuaian dgn ID
//mengubah StatusWahana pada address dinamis D menjadi 'false'

boolean isWahanaRusak (player Pemain, addressWahanaD *D);
//Mengembalikan status wahana yang memiliki posisi Pos

POINT SekitarPemain (POINT Pemain, char C);
//Mengembalikan POINT dari tempat yang berada di sebelah Pemain

void Repair(addressWahanaD *D);
//Mengubah StatusWahana pada address dinamis D menjadi 'true'

void PrintListW(ListWahanaD LW);

void Inoffice();

void PrintHistory(Kata Wahana, addressWahanaS T);

void PrintElmtS (addressWahanaS P, TreeWahanaS T);

void details();

void report();

#endif