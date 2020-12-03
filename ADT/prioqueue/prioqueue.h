/* File : prioqueue.h */
/* Definisi ADT Priority Queue Char dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */
/* Elemen queue terurut tidak mengecil berdasarkan elemen prio */

#ifndef PrioQueue_H
#define PrioQueue_H

#include "../jam/jam.h"
#include "../boolean/boolean.h"
#include  "../listlinier/listlinier.h"
#include "../listplayer/listplayer.h"
#include "../mesinkata/mesinkata.h"
#include "../player/player.h"
#include "../wahana/wahana.h"


#define NilQueue -1
/* Konstanta untuk mendefinisikan addressQueue tak terdefinisi */


/* Definisi elemen dan addressQueue */
typedef struct {
    int patience;
    int prio;  /* [1..100], prioritas dengan nilai 1..100 (1 adalah prioritas tertinggi) */
    List info;  /* elemen karakter */
} infotypeQueue;

typedef int addressQueue;   /* indeks tabel */
/* Contoh deklarasi variabel bertype PrioQueue : */
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct {
    infotypeQueue * T;   /* tabel penyimpan elemen */
    addressQueue HEAD;  /* alamat penghapusan */
    addressQueue TAIL;  /* alamat penambahan */
    int MaxEl;     /* Max elemen queue */
} PrioQueue;
/* Definisi PrioQueue kosong: HEAD=Nil; TAIL=Nil. */

extern Kata CKata;
extern char CC;

/* ********* AKSES (Selektor) ********* */
/* Jika e adalah infotypeQueue dan Q adalah PrioQueue, maka akses elemen : */
#define Patience(e) (e).patience
#define Prio(e)     (e).prio
#define InfoQueue(e)     (e).info
#define Head(Q)     (Q).HEAD
#define Tail(Q)     (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxEl(Q)    (Q).MaxEl
#define ElmtQueue(Q,i)   (Q).T[(i)]

/* ********* Prototype ********* */
boolean IsEmptyQueue (PrioQueue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFullQueue (PrioQueue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int NbElmtQueue (PrioQueue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void CreateEmptyQueue (PrioQueue * Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DealokasiQueue(PrioQueue * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

void ReducePatience(PrioQueue *Q);
/* Mengurangi kesabaran tiap customer yang sedang mengantri */
/* I.S. Q adalah prioqueue tidak kosong yang terdefinisi */
/* F.S. Kesabaran tiap elemen di queue berkurang, tetapi prioritas bertambah */

/* *** Primitif Add/Delete *** */
void FirstEnqueue(PrioQueue *Q, infoLP LP);
/* Menambahkan X ke dalam queue dengan prioritas terbesar */
/* I.S. Q bisa kosong dan terdefinisi */
/* F.S. Isi Q bertamabah */

void Enqueue (PrioQueue * Q, infotypeQueue X);
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut mengecil berdasarkan prio */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
        TAIL "maju" dengan mekanisme circular buffer; */
void Dequeue (PrioQueue * Q, infotypeQueue * X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */

/* Operasi Tambahan */
void PrintPrioQueue (PrioQueue Q);
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<prio-1> <elemen-1>
...
<prio-n> <elemen-n>
#
*/

void RandomizeQueue (PrioQueue *Q, ListWahanaD LW);
/* Mengisi queue Q secara random */
/* I.S. Q terdefinisi dan kosong */
/* F.S. Q terisi secara random */

void Serve(player *P, Kata W, PrioQueue *Q, listPlayer *LP, ListWahanaD LW);
/* I.S. W adalah wahana, bisa tidak valid. Q adalah priority queue */
/* F.S. Jika wahana terdapat pada salah satu list wahana di priority queue, maka */
/*      wahana akan dikeluarkan dari list tersebut. Jika list menjadi kosong, antrian berkurang */


PrioQueue AngryCustomer(PrioQueue Q);
/* Mengeluarkan elemen Q yang kesabarannya 0 */
/* I.S. Q terdefinisi tidak kosong */
/* F.S. Elemen Q tidak berkurang, tidak ada yang kesabarannya 0 */

#endif