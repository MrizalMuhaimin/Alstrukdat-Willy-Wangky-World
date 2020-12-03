/* file : build.h
merupakan bagian preparation phase
yang menampilkan commad BUILD
*/

#include "../wahana/wahana.h"
#include "../arraydinmap/arraydinmap.h"
#include "../graph/graph.h"
#include "../point/point.h"
#include "../peta/peta.h"
#include "../player/player.h"
#include "../stack/stackt.h"
#include <stdio.h>

void ProsedureBuild(POINT Pos, ListWahanaD *L);
/* Menambahkan  status build kedalam stack dan list wahana */

void CommmandBuild();
/* Menampikkan kelayar list wahana kemudian meminta inputan dan memangil fungsi prosedurBuild*/
/* UNTUK MAIN PROGRAM */

/*Command ini digunakan untuk membuat wahana baru di petak di mana
pemain sedang berdiri.
1. Setelah meminta command ini, program akan menampilkan
wahana dasar yang mungkin dibuat (hasil load file eksternal).
2. Setelah pemain memilih wahana dasar yang ingin dibuat.
3. Jika resource untuk membangun wahana tidak mencukupi, maka
akan ditampilkan pesan error.
4. Setelah itu, perintah eksekusi ini akan dimasukkan ke dalam
stack*/


void UndoBuild();
// Tambahin uang
    // Tambahin bahan -> cek inventory pake PrintIsiTab
    // Delete di list wahana built -> Cek list WahanaBuilt
    // Pop

void CommmandBuyArray();
/* melakukan semua perintah yang ada didalam Command Buy
menampilkan daftar bahan kemudian menerima inputan dan mengatusr senua case 
input salah atau benar kemudian masukin ke stack */

void UndoBuy();

void Undo();

void upgradeWahana() ;

void UndoUpgrade();

void PrepMain();

void PrepExecute();