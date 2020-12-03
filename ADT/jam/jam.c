/* File: jam.c */
/* Tanggal: 2 September 2020 */
/* Realisasi ADT JAM */

#include <stdio.h>
#include <stdlib.h>
#include "jam.h"

JAM JamBuka;
JAM JamTutup;
/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsJAMValid (int H, int M){
    /* Mengirim true  jika H,M,S dapat membentuk J yang valid */
    /* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
    return (H >= 0 && H<=23 && M >= 0 && M<=59);
}
/* *** Konstruktor: Membentuk sebuah AM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM){
    /* Membentuk sebuah JAM dari komponen-komponennya yang valid */
    /* Prekondisi : HH, MM, SS valid untuk membentuk JAM */
    JAM J;
    Hour(J) = HH;
    Minute(J) = MM;
    return J;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J) {
    /* I.S. : J tidak terdefinisi */
    /* F.S. : J terdefinisi dan merupakan jam yang valid */
    /* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk J */
    /* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
    /* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
    dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
    /* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
    diulangi hingga didapatkan jam yang valid. */
    /* Contoh:
    60 3 4
    Jam tidak valid
    1 3 4
    --> akan terbentuk JAM <1,3,4> */

    int h, m, s;
    printf("Masukkkan Jam: ");
    scanf("%d", &h);
    printf("Masukkkan Menit: ");
    scanf("%d", &m);

    if(IsJAMValid(h, m)) MakeJAM(h, m);
    else printf("Jam tidak valid");

}

void TulisJAM (JAM J){
    /* I.S. : J sembarang */
    /* F.S. :   Nilai J ditulis dg format HH:MM:SS */
    /* Proses : menulis nilai setiap komponen J ke layar dalam format HH:MM:SS
    tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.
    Jika jam / menit / detik hanya satu digit, tuliskan satu digit tanpa 0 di depannya. */
    if(Hour(J) < 10) printf("0%d.", Hour(J));
    else printf("%d.", Hour(J));

    if(Minute(J) < 10) printf("0%d", Minute(J));
    else printf("%d", Minute(J));
}
/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */
long JAMToMenit (JAM J){
    /* Diberikan sebuah JAM, mengkonversi menjadi jumlah Menit dari pukul 0:0:0 */
    /* Rumus : Menit = 3600*HH + 60*MM + SS */
    /* Nilai maksimum = 3600*23+59*60+59 */

    return (60*Hour(J)+Minute(J));
}

JAM MenitToJAM (long N){
    /* Mengirim  konversi Menit ke JAM */
    /* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah Menit yang
    mewakili jumlah Menit yang mungkin dalam 1 hari, yaitu dengan rumus:
    N1 = N mod 86400, baru N1 dikonversi menjadi JAM */

    N = N % (60*24);

    JAM J;

    Hour(J) = (N/60) % 24;
    N = N%60;
    Minute(J) = N;

    return J;
}
/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */
boolean JEQ (JAM J1, JAM J2){
    return JAMToMenit(J1) == JAMToMenit(J2);
}
/* Mengirimkan true jika J1=J2, false jika tidak */

boolean JNEQ (JAM J1, JAM J2){
    return JAMToMenit(J1) != JAMToMenit(J2);
}
/* Mengirimkan true jika J1 tidak sama dengan J2 */

boolean JLT (JAM J1, JAM J2){
    return JAMToMenit(J1) < JAMToMenit(J2);

}
/* Mengirimkan true jika J1<J2, false jika tidak */

boolean JGT (JAM J1, JAM J2){
    return JAMToMenit(J1) > JAMToMenit(J2);
}
/* Mengirimkan true jika J1>J2, false jika tidak */

/* *** Operator aritmatika JAM *** */
JAM NextMenit (JAM J){
    return MenitToJAM(JAMToMenit(J) + 1);
}
/* Mengirim 1 detik setelah J dalam bentuk JAM */

JAM NextNMenit (JAM J, int N){
    return MenitToJAM(JAMToMenit(J) + N);
}
/* Mengirim N detik setelah J dalam bentuk JAM */

JAM PrevMenit (JAM J){
    long temp = JAMToMenit(J);
    temp-=60;
    if(temp < 0) temp += 86400;

    return MenitToJAM(temp);
}
/* Mengirim 1 detik sebelum J dalam bentuk JAM */
JAM PrevNMenit (JAM J, int N){
    long temp = JAMToMenit(J);
    temp -= N * 60;
    if(temp < 0) temp += 86400;

    return MenitToJAM(temp);
}
/* Mengirim N detik sebelum J dalam bentuk JAM */


/* *** Kelompok Operator Aritmetika *** */
long Durasi (JAM JAw, JAM JAkh){
    if(JAMToMenit(JAkh) > JAMToMenit(JAw)) return JAMToMenit(JAkh) - JAMToMenit(JAw);
    else return JAMToMenit(JAkh) + 60*24 - JAMToMenit(JAw);
}
/* Mengirim JAkh-JAw dlm Detik, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */

void CreateJamBukaTutup(){
    JamBuka = MakeJAM(9, 0);
    JamTutup = MakeJAM(21, 0);
}

void TulisTimeRemaining(int durasi){
    JAM J = MenitToJAM(durasi);
    if(Hour(J) == 1) printf(" %d Hour", Hour(J));
    else if(Hour(J) != 0) printf(" %d Hours", Hour(J));

    if(Minute(J) == 1) printf(" %d Minute", Minute(J));
    else if(Minute(J) != 0) printf(" %d Minutes", Minute(J));


}
