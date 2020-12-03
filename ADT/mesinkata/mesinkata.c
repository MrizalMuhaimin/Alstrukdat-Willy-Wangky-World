
/* File: mesinkata.h */
/* Definisi Mesin Kata: Model Akuisisi Versi I */


#include "mesinkata.h"
#include <stdio.h>

boolean EndKata;
Kata CKata;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */
{
    while ((CC == BLANK) && (CC != MARK)){
        ADV();
    }
}

void STARTKATA()
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
    START();
    IgnoreBlank();

    if (CC == MARK){
        EndKata = true;
    }
    else{
        EndKata = false;
        SalinKata();
    }
}

void STARTKATAFILE(char* filename)
/* I.S. : CC sembarang  dan dibaca dari file yang bernama filename.
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
    STARTFILE(filename);

    if (CC == MARK){
        EndKata = true;
    }
    else{
        EndKata = false;
    }
}

void ADVKATA()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
    IgnoreBlank();

    if (CC == MARK){
        EndKata = true;
    }else{
        SalinKata();
        IgnoreBlank();
    } 
}

void ADVKATAFILE()
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{

    if (CC == MARK){
        EndKata = true;
    }else{
        SalinKataFile();

    } 
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    int i;
    i = 0;
    while ((i < NMax) && (CC != MARK) && (CC != EOL) && (CC != BLANK))
    {
        CKata.TabKata[i] = CC;
        ADV();
        i++;
    }
    CKata.Length = i;
}

void SalinKataFile()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    int i;
    i = 0;
    while ((i < NMax) && (CC != MARK) && (CC != '-') && (CC != EOL))
    {
        CKata.TabKata[i] = CC;
        ADV();
        i++;
    }

    if(CC == '-') {
      ADV();
    }
    // if(CC == EOL) {
    //   ADV();
    // }
    CKata.Length = i;
}

boolean IsKataSama (const char *command)
/* mengirimkan true jika command sama dengan tata yang ada dalam CKata */
{
    /* Membandingkan CKata dengan string

    */
    boolean ans = true;
    int i = 0;

    while(command[i] != '\0' && ans){ //ngecek panjang command sekaligus ngecompare command sama CKata
        if(command[i] != CKata.TabKata[i]) ans = false;
        i++;
    }

    if(i != CKata.Length) ans = false;

    return ans;
}

boolean IsKataSamaKata (Kata K1, Kata K2)
/* mengembalikan true juka K1 sama dengan K2 
   I.S : K1 terdefiniki Kata dan K2 Alamat yang bertipe Kata
   F.S :  true jika K2 = K1 dimana setiap carakter di K1 dan K2 saman dan memiliki panjang kata sama */

{
    /* Membandingkan kata dengan kata

    */
    boolean ans = true;
    int i = 0;

    if(K1.Length == K2.Length){
        while(ans && i < K1.Length){
            if(K1.TabKata[i] != K2.TabKata[i]) ans = false;
            i++;
        }
    } else {
        ans = false;
    }

    return ans;
}

void CopyKata(Kata K1, Kata * K2)
/* Menyalin kata K1 Ke alamat kata K2*
   I.S : K1 terdefiniki Kata dan K2 Alamat yang bertipe Kata
   F.S : tersalin K2 = K1 dimana setiap carakter di K1 dan K2 saman dan memiliki panjang kata sama */


{
    K2->Length = K1.Length;
    for (int i = 0; i<K1.Length; i++){
        (K2->TabKata)[i] = K1.TabKata[i];
    }
}

void PrintKata(Kata K)
/* Pesedure yang menampilkan kata dalam layar
   I.S : K dalam kata
   I.F : nelakukan penampilan karakter kata menjadi kata yang utuh di layar*/

{
    /* Note: Tidak memberikan newline di akhir */
    int i;
    for (i = 0; i < K.Length; i++) {
        printf("%c",K.TabKata[i]);
    }
}

int convToInt (Kata CKata)
/* Mereturn hasil convert CKata menjadi integer */
/* I.S. CKata harus berupa angka */
/* F.S. Integer baru bernilai sama dengan CKT */
{
  int total = 0, i;
  /* ALGORITMA */
  for (i = 0; i < CKata.Length ;i++) {
    total = total*10 + (CKata.TabKata[i] - '0');
  }
  return total;
}