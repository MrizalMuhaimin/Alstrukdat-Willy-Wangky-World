#ifndef PETA_H
#define PETA_H

#include "../player/player.h" 
#include "../matriks/matriks.h" 
#include "../graph/graph.h" 

void CopyPETA (MATRIKS MIn, MATRIKS * MHsl);
/* Melakukan assignment MHsl  MIn */

void TulisPETA (player Pl, Graph G);
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis PETA 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
void MakePETA (char* filename, MATRIKS * P);
/* Mengisi matriks P dengan peta yang ada di filename
   I.S Matriks P bebas
   F.S Matriks P terisi dengan Peta yang ada di filename */

void MovePeta(player *P, Graph G, int NewMapID);
/* Memindahkan player dari satu arena ke arena yang lain
   I.S. Player berada di arena yang sesuai dengan MapNum(P)
   F.S. Player berada di arena dengan ID NewMapID
*/
void w(player *P, Graph G);
/* Player bergerak ke "atas"
   I.S Player berada di point X,Y
   F.S Jika X,Y-1 kosong, player berada di point X,Y-1. Jika tidak kosong, player tetep berada di X,Y
*/
void a(player *P, Graph G);
/* Player bergerak ke "kiri"
   I.S Player berada di point X,Y
   F.S Jika X-1,Y kosong, player berada di point X-1,Y. Jika tidak kosong, player tetep berada di X,Y
*/

void s(player *P, Graph G);
/* Player bergerak ke "bawah"
   I.S Player berada di point X,Y
   F.S Jika X,Y+1 kosong, player berada di point X,Y+1. Jika tidak kosong, player tetep berada di X,Y
*/

void d(player *P, Graph G);
/* Player bergerak ke "kanan"
   I.S Player berada di point X,Y
   F.S Jika X+1,Y kosong, player berada di point X+1,Y. Jika tidak kosong, player tetep berada di X,Y
*/

void loadPeta();
/* Me-load seluruh peta arena yang ada
   I.S Matriks Peta1, Peta2, Peta3, Peta4 bebas
   F.S Matriks Peta1, Peta2, Peta3, Peta4 berisi peta yang ada di file-file peta
*/

void AddWToPeta();
/* Menambahkan Wahana ke peta
   I.S Player berada di point X,Y
   F.S point X,Y pada peta menjadi W. Player pindah ke kanan/kiri/atas/bawah point sebelumnya yang kosong.

*/
#endif