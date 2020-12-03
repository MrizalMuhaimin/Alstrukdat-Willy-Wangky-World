/* File listplayer.h */
/* Basically list linier untuk menampung customer yang sedang bermain */
/* dan masih punya wahana lain yg mau dinaiki */


#ifndef LISTPLAYER_H
#define LISTPLAYER_H


#include "../jam/jam.h"
#include "../prioqueue/prioqueue.h"
#include <stdlib.h>

#define NilList NULL

typedef struct {
    int remaining; // Integer --> dianggap semua satuan durasinya menit
	int remPatience;
    List player;
} infoLP;

typedef struct tElmtLP *addressLP;

typedef struct tElmtLP {
	infoLP info;
	addressLP next;
} ElmtLP;

typedef struct {
	addressLP First;
} listPlayer;

#define Remaining(p) (p).remaining
#define RemainingPat(p) (p).remPatience
#define PlayerInfo(p) (p).player
#define InfoLP(LP) (LP)->info
#define NextLP(LP) (LP)->next
#define FirstLP(L) ((L).First)

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyLP (listPlayer LP);
/* Mengirim true jika list player kosong */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyLP (listPlayer *LP);
/* I.S. sembarang             */
/* F.S. Terbentuk list player kosong */

/****************** Manajemen Memori ******************/
addressLP AlokasiLP (infoLP P);
/* Mengirimkan addressList hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressList tidak NilList, dan misalnya */
/* menghasilkan P, maka InfoList(P)=X, Next(P)=NilList */
/* Jika alokasi gagal, mengirimkan NilList */
void DealokasiLP (addressLP *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressList P */

/****************** Manajemen Jam Permainan ******************/
void ReduceTime (listPlayer *LP);
/* Mengurangi jam tersisa pemain dalam memainkan permainan sebanyak satu menit */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstLP (listPlayer *LP, addressLP P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressList P sebagai elemen pertama */
void InsertAfterLP (listPlayer *LP, addressLP P, addressLP Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
void InsertLastLP (listPlayer *LP, addressLP P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

void InsVLastLP (listPlayer *LP, infoLP X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstLP (listPlayer *LP, addressLP *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelLP (listPlayer *LP, infoLP X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan InfoList(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan InfoList bernilai X */
/* maka yang dihapus hanya elemen pertama dengan InfoList = X */
/* Jika tidak ada elemen list dengan InfoList(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
void DelLastLP (listPlayer *LP, addressLP *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */

void DelAfterLP (listPlayer *LP, addressLP *Pdel, addressLP Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */

void DelCompleted (listPlayer *LP, infoLP *del);
/* Menghapus pemain yang sudah selesai bermain */
/* I.S. List terdefinisi dan tidak kosong */
/* F.S. Elemen list akan berkurang dengan syarat Remamining(p) = 0 */

int CountCompleted(listPlayer LP);
/* Menghitung jumlah customer yang telah selesai bermain */

#endif