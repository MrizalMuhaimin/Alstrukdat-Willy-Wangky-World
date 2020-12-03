/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "../boolean/boolean.h"
#include "../mesinkar/mesinkar.h"

#define NMax 100
#define BLANK ' '
#define EOL '\n'

typedef struct {
	char TabKata[NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
    int Length;
} Kata;

/* State Mesin Kata */
extern boolean EndKata;
extern Kata CKata;

void IgnoreBlank();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATAFILE(char* filename);
/* I.S. : CC sembarang  dan dibaca dari file yang bernama filename.
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void STARTKATA();
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void ADVKATAFILE();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi dari kata pembacaaan file 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
void ADVKATA();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void SalinKataFile();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = - atau CC = MARK atau CC = \n ; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

void SalinKata();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

boolean IsKataSama (const char *command);
/* mengirimkan true jika command sama dengan tata yang ada dalam CKata */

void CopyKata(Kata K1, Kata * K2);

boolean IsKataSamaKata (Kata K1, Kata K2);
/* mengembalikan true juka K1 sama dengan K2 
   I.S : K1 terdefiniki Kata dan K2 Alamat yang bertipe Kata
   F.S :  true jika K2 = K1 dimana setiap carakter di K1 dan K2 saman dan memiliki panjang kata sama */

void PrintKata(Kata K);
/* Pesedure yang menampilkan kata dalam layar
   I.S : K dalam kata
   I.F : nelakukan penampilan karakter kata menjadi kata yang utuh di layar*/

int convToInt (Kata CKata);
/* mengembalikan K menjadi integer 
   I.S : K adlah kata yang setiap carakter murukakan char of integer
   I.F : Merubah kata menjadi dalam tipe integer*/

#endif

