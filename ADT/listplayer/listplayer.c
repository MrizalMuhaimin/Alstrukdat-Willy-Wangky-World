/* File listplayer.c */
/* Basically list linier untuk menampung customer yang sedang bermain */
/* dan masih punya wahana lain yg mau dinaiki */

#include <stdlib.h>
#include "../jam/jam.h"
#include "../prioqueue/prioqueue.h"
#include "listplayer.h"

/****************** TEST LIST KOSONG ******************/
boolean IsEmptyLP (listPlayer LP) {
    /* Mengirim true jika list player kosong */
    return(FirstLP(LP) == NULL);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyLP (listPlayer *LP) {
    /* I.S. sembarang             */
    /*  F.S. Terbentuk list player kosong */
    FirstLP(*LP) = NilList;
}

/****************** Manajemen Memori ******************/
addressLP AlokasiLP (infoLP X) {
    /* Mengirimkan addressList hasil alokasi sebuah elemen */
    /* Jika alokasi berhasil, maka addressList tidak NilList, dan misalnya */
    /* menghasilkan P, maka InfoList(P)=X, Next(P)=NilList */
    /* Jika alokasi gagal, mengirimkan NilList */
    /* KAMUS */
   addressLP P;
   /* ALGORITMA */
   P = (ElmtLP *) malloc(sizeof(ElmtLP));
   if (P != NilList) {
       InfoLP(P) = X;
       NextLP(P) = NilList;
    }
    return P;
}
void DealokasiLP (addressLP *P){
    /* I.S. P terdefinisi */
   /* F.S. P dikembalikan ke sistem */
   /* Melakukan DealokasiList/pengembalian addressLisPlayer P */
   free(*P);
}

/****************** Manajemen Jam Permainan ******************/
void ReduceTime (listPlayer * LP) {
    /* Mengurangi jam tersisa pemain dalam memainkan permainan sebanyak satu menit */
    addressLP P = FirstLP(*LP);

    while(P != NilList) {
        Remaining(InfoLP(P)) -= 1;
        P = NextLP(P);
    }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstLP (listPlayer *LP, addressLP *P) {
    /* I.S. List tidak kosong */
    /* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
    /*      Elemen list berkurang satu (mungkin menjadi kosong) */
    /* First element yg baru adalah suksesor elemen pertama yang lama */
    addressLP A = FirstLP(*LP);
    FirstLP(*LP) = NextLP(A);
    *P = A;
}

void DelAfterLP (listPlayer *LP, addressLP *Pdel, addressLP Prec) {
	/* I.S. List tidak kosong. Prec adalah anggota list  */
	/* F.S. Menghapus Next(Prec): */
	/*      Pdel adalah alamat elemen list yang dihapus  */
	/* KAMUS */
	addressLP P = FirstLP(*LP);
	boolean found = false;
	/* ALGORITMA  */
	while((P != NilList) && (!found)) {
        if (P == Prec) {
            found = true;
        } else {
            P = NextLP(P);
        }
    }

    *Pdel = NextLP(P);
    NextLP(P) = NextLP(NextLP(P));
    NextLP(*Pdel) = NilList;
}

void DelCompleted (listPlayer *LP, infoLP *del) {
    /* I.S. Sembarang */
    /* F.S. Jika ada elemen list beraddress P, dengan InfoList(P)=X  */
    /* Maka P dihapus dari list dan di-dealokasi */
    /* Jika ada lebih dari satu elemen list dengan InfoList bernilai X */
    /* maka yang dihapus hanya elemen pertama dengan InfoList = X */
    /* Jika tidak ada elemen list dengan InfoList(P)=X, maka list tetap */
    /* List mungkin menjadi kosong karena penghapusan */
    /* KAMUS */
   addressLP P = FirstLP(*LP), prec = NilList, Pdel = NilList;
   boolean found = false;
   /* ALGORITMA */
   while((P != NilList) && (!found)) {
       if (Remaining(InfoLP(P)) == 0) {
           found = true;
       } else {
           prec = P;
           P = NextLP(P);
       }
    }
 
   if(found) {
        if (prec == NilList) {
            DelFirstLP(LP, &Pdel);
        } else {
            DelAfterLP(LP, &Pdel, prec);
        }
    }

    *del = InfoLP(Pdel);
}

void InsertFirstLP (listPlayer *LP, addressLP P){
   /* I.S. Sembarang, P sudah dialokasi  */
   /* F.S. Menambahkan elemen ber-addressList P sebagai elemen pertama */
   /* ALGORITMA */
   NextLP(P) = FirstLP(*LP);
   FirstLP(*LP) = P;
}

void InsertAfterLP (listPlayer *LP, addressLP P, addressLP Prec){
   /* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
   /*      P sudah dialokasi  */
   /* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
   /* ALGORITMA */
   NextLP(P) = NextLP(Prec);
   NextLP(Prec) = P;
}

void InsertLastLP (listPlayer *LP, addressLP P){
   /* I.S. Sembarang, P sudah dialokasi  */
   /* F.S. P ditambahkan sebagai elemen terakhir yang baru */
   /* KAMUS */
   addressLP last;
   /* ALGORITMA */
    if(IsEmptyLP(*LP)) {
        InsertFirstLP(LP, P);
    } else {
        last = FirstLP(*LP);
        while (NextLP(last) != NilList) {
            last = NextLP(last);
        }
        InsertAfterLP(LP, P, last);
    }
}

void InsVLastLP (listPlayer *LP, infoLP X){
   /* I.S. L mungkin kosong */
   /* F.S. Melakukan alokasi sebuah elemen dan */
   /* menambahkan elemen list di akhir: elemen terakhir yang baru */
   /* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
   /* KAMUS */
   addressLP P;
   /* ALGORITMA */
   P = AlokasiLP(X);
   if(P != NilList) {
       InsertLastLP(LP,P);
    }
}

int CountCompleted (listPlayer LP) {
    /* Menghitung jumlah customer yang telah selesai bermain */
    /* KAMUS */
    int count = 0;
    addressLP P = FirstLP(LP);
    boolean found = false;
    /* ALGORITMA */
     while(P != NilList) {
        if (Remaining(InfoLP(P)) == 0) {
            count++;
        }
        P = NextLP(P);
    }
    return count;
}
