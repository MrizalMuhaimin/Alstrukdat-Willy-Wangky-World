#include <stdio.h>
#include <stdlib.h>
#include "listlinier.h"
//#include "../wahana/wahana.h"

/****************** TEST LIST KOSONG ******************/
boolean IsEmptyList (List L){
   /* Mengirim true jika list kosong */
   return(First(L) == NULL);
}
 
/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyList (List *L){
   /* I.S. sembarang             */
   /* F.S. Terbentuk list kosong */
   First(*L) = NilList;
   
}
 
/****************** Manajemen Memori ******************/
addressList Alokasi (infotypeList X){
   /* Mengirimkan addressList hasil alokasi sebuah elemen */
   /* Jika alokasi berhasil, maka addressList tidak NilList, dan misalnya */
   /* menghasilkan P, maka InfoList(P)=X, Next(P)=NilList */
   /* Jika alokasi gagal, mengirimkan NilList */
   /* KAMUS */
   addressList P;
   /* ALGORITMA */
   P = (ElmtList *) malloc(sizeof(ElmtList));
   if (P!= NilList) {
       InfoList(P) = X;
       Next(P) = NilList;
    }
    return P;
}
void DealokasiList (addressList *P){
   /* I.S. P terdefinisi */
   /* F.S. P dikembalikan ke sistem */
   /* Melakukan DealokasiList/pengembalian addressList P */
   free(*P);
}
 
/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressList Search (List L, Kata X){
   /* Mencari apakah ada elemen list dengan InfoList(P)= X */
   /* Jika ada, mengirimkan addressList elemen tersebut. */
   /* Jika tidak ada, mengirimkan NilList */
   /* KAMUS */
   CKata = X;
   addressList P = First(L);
   boolean found = false;
   /* ALGORITMA */
   while(!found && (P != NilList)) {
       if (IsKataSamaKata(InfoList(P), X)) {
           found = true;
        } else {
           P = Next(P);
        }
    }
    return P;
}
 
boolean SearchBool (List L, Kata X){
   /* Mencari apakah ada elemen list dengan InfoList(P)= X */
   /* Jika ada, mengirimkan addressList elemen tersebut. */
   /* Jika tidak ada, mengirimkan NilList */
   /* KAMUS */
   CKata = X;
   addressList P = First(L);
   boolean found = false;
   /* ALGORITMA */
   while(!found && (P != NilList)) {
       if (IsKataSamaKata(InfoList(P), X)) {
           found = true;
        } else {
           P = Next(P);
        }
    }
    return found;
}
/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotypeList X){
   /* I.S. L mungkin kosong */
   /* F.S. Melakukan alokasi sebuah elemen dan */
   /* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
   /* KAMUS */
   addressList P = Alokasi(X);
   /* ALGORITMA */
   if(P != NilList) {
       Next(P) = First(*L);
       First(*L) = P;
    }
}
void InsVLast (List *L, infotypeList X){
   /* I.S. L mungkin kosong */
   /* F.S. Melakukan alokasi sebuah elemen dan */
   /* menambahkan elemen list di akhir: elemen terakhir yang baru */
   /* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
   /* KAMUS */
   addressList P;
   /* ALGORITMA */
   P = Alokasi(X);
   if(P != NilList) {
       InsertLast(L,P);
    }
}
 
/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotypeList *X){
   /* I.S. List L tidak kosong  */
   /* F.S. Elemen pertama list dihapus: nilai InfoList disimpan pada X */
   /*      dan alamat elemen pertama di-DealokasiList */
   /* KAMUS */
   addressList P;
   /* ALGORITMA */
   DelFirst(L, &P);
   *X = InfoList(P);
   DealokasiList(&P);
}
void DelVLast (List *L, infotypeList *X){
   /* I.S. list tidak kosong */
   /* F.S. Elemen terakhir list dihapus: nilai InfoList disimpan pada X */
   /*      dan alamat elemen terakhir di-DealokasiList */
   /* KAMUS */
   addressList P;
   /* ALGORITMA */
   DelLast(L, &P);
   *X = InfoList(P);
   DealokasiList(&P);
}
 
/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, addressList P){
   /* I.S. Sembarang, P sudah dialokasi  */
   /* F.S. Menambahkan elemen ber-addressList P sebagai elemen pertama */
   /* ALGORITMA */
   Next(P) = First(*L);
   First(*L) = P;
}
void InsertAfter (List *L, addressList P, addressList Prec){
   /* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
   /*      P sudah dialokasi  */
   /* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
   /* ALGORITMA */
   Next(P) = Next(Prec);
   Next(Prec) = P;
}
void InsertLast (List *L, addressList P){
   /* I.S. Sembarang, P sudah dialokasi  */
   /* F.S. P ditambahkan sebagai elemen terakhir yang baru */
   /* KAMUS */
   addressList last;
   /* ALGORITMA */
    if(IsEmptyList(*L)) {
        InsertFirst(L, P);
    } else {
        last = First(*L);
        while (Next(last) != NilList) {
            last = Next(last);
        }
        InsertAfter(L, P, last);
    }
}
 
/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, addressList *P){
   /* I.S. List tidak kosong */
   /* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
   /*      Elemen list berkurang satu (mungkin menjadi kosong) */
   /* First element yg baru adalah suksesor elemen pertama yang lama */
   /* ALGORITMA */
   addressList A = First(*L);
   First(*L) = Next(A);
   *P = A;
}

void DelP (List *L, infotypeList X){
   /* I.S. Sembarang */
   /* F.S. Jika ada elemen list beraddress P, dengan InfoList(P)=X  */
   /* Maka P dihapus dari list dan di-DealokasiList */
   /* Jika ada lebih dari satu elemen list dengan InfoList bernilai X */
   /* maka yang dihapus hanya elemen pertama dengan InfoList = X */
   /* Jika tidak ada elemen list dengan InfoList(P)=X, maka list tetap */
   /* List mungkin menjadi kosong karena penghapusan */
   /* KAMUS */
   addressList P = First(*L), del, prec = NilList;
   boolean found = false;
   /* ALGORITMA */
   while((P != NilList) && (!found)) {
       if (IsKataSamaKata(InfoList(P), X)) {
           found = true;
       } else {
           prec = P;
           P = Next(P);
       }
    }
 
   if(found) {
        if (prec == NilList) {
            DelFirst(L, &del);
        } else {
            DelAfter(L, &del, prec);
        }
        DealokasiList(&del);
    }
}
 
void DelLast (List *L, addressList *P){
	/* I.S. List tidak kosong */
	/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
	/*      Elemen list berkurang satu (mungkin menjadi kosong) */
	/* Last element baru adalah predesesor elemen terakhir yg lama, */
	/* jika ada */
	/* KAMUS */
	addressList last = First(*L), precLast = NilList;
	/* KAMUS */
    while(Next(last) != NilList) {
        precLast = last;
        last = Next(last);
    }

    if(precLast == NilList) {
        DelFirst(L, P);
    } else {
        DelAfter(L, P, precLast);
    }

}
void DelAfter (List *L, addressList *Pdel, addressList Prec) {
	/* I.S. List tidak kosong. Prec adalah anggota list  */
	/* F.S. Menghapus Next(Prec): */
	/*      Pdel adalah alamat elemen list yang dihapus  */
	/* KAMUS */
	addressList P = First(*L);
	boolean found = false;
	/* ALGORITMA  */
	while((P != NilList) && (!found)) {
        if (P == Prec) {
            found = true;
        } else {
            P = Next(P);
        }
    }

    *Pdel = Next(P);
    Next(P) = Next(Next(P));
    Next(*Pdel) = NilList;
}
 
/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L) {
	/* I.S. List mungkin kosong */
	/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
	/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
	/* Jika list kosong : menulis [] */
	/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
	/* KAMUS */
	addressList P;
	/* ALGORITMA */
	if(IsEmptyList(L)) {
        printf("()");
    } else { 
        printf("(");
        P = First(L);
        while(P != NilList) {
            PrintKata(InfoList(P));
            if(Next(P) != NilList){
                printf(", ");
            }
            P = Next(P);
        }
        printf(")");
    }
}

int NbElmt (List L) {
	/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
	/* KAMUS */
	addressList P;
	int count = 0;
	/* ALGORITMA */
	if(IsEmptyList(L)){
		return 0;
	} else {
		P = First(L);
		while(P != NilList){
			count++;
			P = Next(P);
		}
		return count;
	}
}

/****************** PROSES TERHADAP LIST ******************/
void Konkat1 (List *L1, List *L2, List *L3) {
	/* I.S. L1 dan L2 sembarang */
	/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
	/* Konkatenasi dua buah list : L1 dan L2    */
	/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
	/* dan L1 serta L2 menjadi list kosong.*/
	/* Tidak ada alokasi/DealokasiList pada prosedur ini */
	/* KAMUS */
	addressList P;
	/* ALGORITMA */
    if(IsEmptyList(*L1)) {
        First(*L3) = First(*L2);
        First(*L2) = NilList;
    } else if(IsEmptyList(*L2)) {
        First(*L3) = First(*L1);
        First(*L1) = NilList;
    } else if(IsEmptyList(*L1) && IsEmptyList(*L2)) {
		First(*L3) = NilList;
	} else {
        First(*L3) = First(*L1);
        P = First(*L3);
        while(Next(P) != NilList){
            P = Next(P);
        }
        Next(P) = First(*L2);

        First(*L1) = NilList;
        First(*L2) = NilList;
	}
}

boolean IsListSama (List L1, List L2) {
    /* Memeriksa apakah L1 dan L2 adalah list yang sama */
    boolean sama = true;
    if (NbElmt(L1) == NbElmt(L2)) {
        addressList P1 = First(L1), P2 = First(L2);
        while (sama && P1 != NilList) {
            if (!IsKataSamaKata(InfoList(P1), InfoList(P2))) {
                sama = false;
            } else {
                P1 = Next(P1);
                P2 = Next(P2);
            }
        }
        return sama;
    } else {
        return false;
    }
}

List RemoveDouble(List  L) {
    List new;
    CreateEmptyList(&new);

    addressList P = First(L);
    while(P != NilList){
        if (IsEmptyList(new)) {
            InsVLast(&new, InfoList(P));
        } else {
            if(!SearchBool(new, InfoList(P))) {
                InsVLast(&new, InfoList(P));
            }
        }
        P = Next(P);
    }

    return new;

}

/*boolean IsAllRusak (List L, ListWahanaD LW) {
   addressList P = First(L);
   addressWahanaD W;
   boolean rusak = true;
    while(P != NilList && rusak){
        W = SearchWahanaD(InfoList(P), LW);
        if(W != NilList && !StatusWahana(W)) {
            rusak = false;
        } 
    }

    return rusak;
}*/
