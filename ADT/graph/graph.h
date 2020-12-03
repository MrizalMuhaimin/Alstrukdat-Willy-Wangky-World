/* File: graph.h */
/* ADT graph dengan representasi multilist */

#ifndef GRAPH_H
#define GRAPH_H

#include "../boolean/boolean.h"
#include "../matriks/matriks.h"

// Linked List buat Link graph
typedef int infoTypeLink;

typedef struct tElmtlink *addressLink;
typedef struct tElmtlink {
	infoTypeLink InfoList;
	addressLink next;
} ElmtListLink;

typedef struct {
	addressLink First;
} ListLink;

#define InfoLink(P) (P)->InfoList
#define NextLink(P) (P)->next
#define FirstLink(L) ((L).First)

// ADT Graphnya
typedef int infoTypeLink;
typedef struct tElmtgraph *addressGraph;
typedef struct tElmtgraph {
	int ID;
	MATRIKS Peta;
	ListLink link;
	addressGraph next;
} ElmtGraph;
typedef struct {
	addressGraph First;
} Graph;

#define ID(P) (P)->ID
#define Peta(P) (P)->Peta
#define NextGraph(P) (P)->next
#define Link(P) 	 (P)->link
#define FirstGraph(G) ((G).First)

extern Graph GraphPeta;
/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyLink (ListLink L);
/* Mengirim true jika list kosong */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyLink (ListLink *L);
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */

/****************** Manajemen Memori ******************/
addressLink AlokasiLink (infoTypeLink X);
/* Mengirimkan addressLink hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressLink tidak NilList, dan misalnya */
/* menghasilkan P, maka InfoList(P)=X, Next(P)=NilList */
/* Jika alokasi gagal, mengirimkan NilList */
void DealokasiLink (addressLink *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressLink P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressLink SearchLink (ListLink L, int X);
/* Mencari apakah ada elemen list dengan InfoList(P)= X */
/* Jika ada, mengirimkan addressLink elemen tersebut. */
/* Jika tidak ada, mengirimkan NilList */

void InsVLastLink (ListLink *L, infoTypeLink X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

void PrintID (ListLink L);
// I.S Sembarang, L muingkin kosong
// F.S Mencetak ID Peta yang terhubung dengan peta yang memiliki listlink L

void CreateEmptyGraph(Graph *G);
/* I.S. sembarang             */
/* F.S. Terbentuk graph kosong */

boolean IsGraphEmpty(Graph G);
/* Mengirimkan true jika graph kosong */

addressGraph AlokasiGraph(int id, MATRIKS peta);
/* Mengirimkan addressGraph hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressGraph tidak nil, dan misalnya */
/* menghasilkan P, maka InfoGraph(P)=X, NextGraph(P)=NULL, dan Link(P) berisi list kosong */
/* Jika alokasi gagal, mengirimkan NULL */

void InsGraphLast(Graph * G, addressGraph P);
/*I.S. G mungkin kosong, P adalah elemen graph*/
/*F.S. P menjadi elemen terakhir dari G*/

void PrintGraph(Graph G);
/* I.S. Graph mungkin kosong */
/* F.S. Jika Graph tidak kosong, isi info Graph dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika Graph kosong : menulis [] */

void PrintLink(Graph G, infoTypeLink X);
/* Mencetak list link dari elemen graph dengan ID X */

boolean IsLinked(Graph G, infoTypeLink n, infoTypeLink p);
/* Mengembalikan true jika pada link n ada p */

addressGraph SearchGraph(Graph G, infoTypeLink X);
/*Mengembalikan address elemen graph yang memiliki ID X*/

void CreateGraphPeta();
/* I.S. GraphPeta kosong */
/* F.S GraphPeta berisi peta-peta dari file-file .txt lengkap dengan linknya*/

void PrintPetaGraph(Graph G);
/*Mencetak Seluruh graph yang ada di peta beserta masing2 linknya*/

void MakeLink(addressGraph * P);
/* I.S P memiliki list link kosong */
/* F.s list link dari p akan berisi elemen graph yg terhubung dengna peta P */

#endif
