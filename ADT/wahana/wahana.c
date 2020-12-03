
#include "wahana.h"
#include <stdio.h>
#include <stdlib.h>

boolean EndKata;
Kata CKata;
char CC;
boolean EOP;
TreeWahanaS UpgradeTree;
ListWahanaD WahanaBuilt;

void Details()
/* I.S namaWahana dimasukkan user */
/* F.S Menampilkan detail dari wahana*/ /*harus pas dia disebelah wahana*/
{   
    int X = X(Player);
    int Y = Y(Player);
    POINT P;
    addressGraph CPeta = FirstGraph(GraphPeta);
    
    while(ID(CPeta) != MapNum(Player)) CPeta = NextGraph(CPeta);
    
    if (ElmtMatriks(Peta(CPeta), Y-1, X) == 'W' || ElmtMatriks(Peta(CPeta), Y+1, X) == 'W' || ElmtMatriks(Peta(CPeta), Y, X-1) == 'W' || ElmtMatriks(Peta(CPeta), Y, X+1) == 'W'){
        if(ElmtMatriks(Peta(CPeta), Y-1, X) == 'W'){
            P = MakePOINT(X,Y-1);
            PrintElmtS(ElmtStatis(SearchWahanaDP(P, MapNum(Player), WahanaBuilt)), UpgradeTree); 
        }
        if(ElmtMatriks(Peta(CPeta), Y+1, X) == 'W'){
            P = MakePOINT(X, Y+1);
            PrintElmtS(ElmtStatis(SearchWahanaDP(P, MapNum(Player), WahanaBuilt)), UpgradeTree); 
        }
        if(ElmtMatriks(Peta(CPeta), Y, X-1) == 'W'){
            P = MakePOINT(X-1,Y);
            PrintElmtS(ElmtStatis(SearchWahanaDP(P, MapNum(Player), WahanaBuilt)), UpgradeTree);
        }
        if(ElmtMatriks(Peta(CPeta), Y, X+1) == 'W'){
            P = MakePOINT(X+1, Y);
            PrintElmtS(ElmtStatis(SearchWahanaDP(P, MapNum(Player), WahanaBuilt)), UpgradeTree); 
        }
    }
}

void SubTree(addressWahanaS parent, addressWahanaS l, addressWahanaS r){
    Left(parent) = l;
    Right(parent) = r;
}

void MakeTree()
/* I.S P adalah tree kosong */
/* F.S P adalah tree berisi ElmtWahanaStatis yang diambil dari file txt */
{
    boolean empty = true;
    addressWahanaS temptree[10];
    for (int i = 0; i < 10; i++)
        temptree[i] = AlokNode(i);

    STARTFILE("./Files/Wahana/wahana.txt");
    //printf("baca file\n");
    int i=0;
    int indexarr=0; //akan bertambah perbaris dan pernode

    while(!EOP){
        empty = false;
        SalinKataFile();
        i++;
        if(CC == EOL){
            if (i == 10){
                UpgradeCost(temptree[indexarr]) = convToInt(CKata);
                //printf("bisa 7, %d\n",TimeWahana(temptree[indexarr]));
            }
            ADV(); //pita maju 1 karakter
            i=0;
            //printf("\n");
            indexarr++;
            //printf("[index arr: %d] ",indexarr);
        } else {
            switch (i) {
                case 1:
                    IDWahana(temptree[indexarr]) = convToInt(CKata); 
                    //printf("bisa 1, %d\n",IDWahana(temptree[indexarr]));
                    break;
                case 2:
                    CopyKata(CKata, &NamaWahana(temptree[indexarr]));
                    //printf("bisa 2, "); PrintKata(NamaWahana(temptree[indexarr])); printf("\n");
                    break;
                case 3:
                    TipeWahana(temptree[indexarr]) = CKata;
                    //printf("bisa 3, "); PrintKata(TipeWahana(temptree[indexarr])); printf("\n");
                    break;
                case 4:
                    PriceWahana(temptree[indexarr]) = convToInt(CKata);
                    //printf("bisa 4, %d\n",PriceWahana(temptree[indexarr]));
                    break;
                case 5:
                    DescWahana(temptree[indexarr]) = CKata;
                    //printf("bisa 5, "); PrintKata(DescWahana(temptree[indexarr])); printf("\n");
                    break;
                case 6:
                    CapacityWahana(temptree[indexarr]) = convToInt(CKata);
                    //printf("bisa 6, %d\n",CapacityWahana(temptree[indexarr]));
                    break;
                case 7:
                    TimeWahana(temptree[indexarr]) = convToInt(CKata);
                    //printf("bisa 7, %d\n",TimeWahana(temptree[indexarr]));
                    break;
                case 8:
                    BahanWahana(temptree[indexarr]) = CKata;
                    break;
                case 9:
                    JmlBahan(temptree[indexarr]) = convToInt(CKata);
                    break;
                case 10:
                    UpgradeCost(temptree[indexarr]) = convToInt(CKata);
                    break;
                default:
                    break;
            }
        }
    }  

    if(!empty){
        SubTree(temptree[0], temptree[1], temptree[2]);
        SubTree(temptree[1], temptree[3], temptree[4]);
        SubTree(temptree[3], temptree[7], NilList);
        SubTree(temptree[4], temptree[8], NilList);
        SubTree(temptree[2], temptree[5], temptree[6]);
        SubTree(temptree[5], temptree[9], NilList);
        UpgradeTree = temptree[0];
    }
}

/* Manajemen Memory */
addressWahanaS AlokNode(int i)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P, 
  maka Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    addressWahanaS P;
    P = (ElmtWahanaStatis *)malloc(sizeof(ElmtWahanaStatis));
    if (P != NilList){
        Left(P) = NilList;
        Right(P) = NilList;
    }
    return P;
}

void DealokNode(addressWahanaS *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
{
    free(*P);
}

/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty(TreeWahanaS T)
/* Mengirimkan true jika P adalah pohon biner kosong */
{
    return (T ==  NilList);
}

boolean IsTreeOneElmt(TreeWahanaS T)
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
{
    if (IsTreeEmpty(T)) return false;
    else {
        if (Left(T) == NilList && Right(T) == NilList){
            return true;
        } 
        else{
            return false;
        }     
    }
}

boolean IsUnerLeft(TreeWahanaS T)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
{
    if (!IsTreeEmpty(T)) {
        if (Left(T) != NilList && Right(T) == NilList){
            return true;
        }    
        return false;
    }
    return false;
}

boolean IsUnerRight(TreeWahanaS T)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
{
    if (!IsTreeEmpty(T)){
        if (Right(T) != NilList && Left(T) == NilList){
            return true;    
        }

        return false;
    }
    return false;
}

boolean IsBiner(TreeWahanaS T)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/
{
    if (!IsTreeEmpty(T)) {
        if (Left(T) != NilList && Right(T) != NilList){
            return true;
        }
        return false; 
    }
    return false;
}
//ID-WAHANA-TIPE-HARGA-DESKRIPSI-KAPASITAS-DURASI(MENIT)

void PrintTreeNode(addressWahanaS P)
/* Mencetak node tree dengan address P */
{
    
    //int i = 0;
    if (P!= NilList){
        //i++;
        printf("- ");
        PrintKata(NamaWahana(P)); printf("\n");
        PrintTreeNode(Left(P));
        PrintTreeNode(Right(P));
    }
}

void PrintTree(TreeWahanaS T)
/* Mencetak tree dengan PreOrder */
{
    PrintTreeNode(T);
}

void initWahana(TreeWahanaS T)
{
    addressWahanaS Coaster1 = T;
    addressWahanaS Heli2 = Left(T);
    addressWahanaS Water3 = Right(T);
    printf("List:\n");
    printf("  -"); PrintKata(NamaWahana(Coaster1));printf("\n");
    printf("  -"); PrintKata(NamaWahana(Heli2));printf("\n");
    printf("  -"); PrintKata(NamaWahana(Water3));printf("\n");
    STARTKATA();
    //user masukin input wahana mana yang mau di build
    //build di tempat dia berdiri
    //player pindah ke bawah
}

void buildWahana(POINT Pos, ListWahanaD *L)
/*Command ini digunakan untuk membuat wahana baru di petak di mana
pemain sedang berdiri.
1. Setelah meminta command ini, program akan menampilkan
wahana dasar yang mungkin dibuat (hasil load file eksternal).
2. Setelah pemain memilih wahana dasar yang ingin dibuat.
3. Jika resource untuk membangun wahana tidak mencukupi, maka
akan ditampilkan pesan error. TANPA MASUKKIN KE STACK */
{
    //Menampilkan wahana dasar (ada 10, diambil dari tree wahana)
    addressWahanaD P, Prec;

    printf("\nIngin membangun wahana apa?\n-> ");
    STARTKATA(); 
    if (!IsKataSama (""))
    {
        if(SearchTree(CKata,UpgradeTree))
        {
            //masukkin ke list  wahana
            P = AlokWahana(Pos, CKata); 
            if (IsEmptyListW(*L)){
                InsFirstW(L,P);
            }
            else{
                Prec = First(*L); 

                while (Next(Prec)!=NilList){
                    Prec = Next(Prec);
                }
                InsAfterW(L, P, Prec);
            }
        }
        else
        {
            printf("%s\n","Wahana tidak ada dalam list wahana" );
        }   
    }
    else
	{
		printf("%s\n","Masukan Anda enter" );
	}
}

boolean IsEmptyListW (ListWahanaD L){
   /* Mengirim true jika list kosong */
   return(First(L) == NilList);
}

addressWahanaD WahanaSekitar() {     
    /* NOTE: PASTI KETEMU */
      
    boolean found = false;
    addressWahanaD P = First(WahanaBuilt);
    while (!found) {
        if(Ordinat(PositionWahana(P)) == Y(Player)){
            if((Absis(PositionWahana(P)) = X(Player) + 1) || (Absis(PositionWahana(P)) = X(Player) - 1)) {
                found = true;
            }
        } else if(Absis(PositionWahana(P)) == X(Player)) {
            if((Ordinat(PositionWahana(P)) = Y(Player) + 1) || (Ordinat(PositionWahana(P)) = Y(Player) - 1)) {
                found = true;
            }
        } else {
            P = NextWahana(P);
        }
    }

    return P;
}

void Repair(addressWahanaD *W) {
    if (StatusWahana(*W)) {
        printf("Wahana tidak rusak!\n");
    } else {
        for(int i = 0; i < 5; i++) {
            CJam(Player) = NextMenit(CJam(Player));
        }
        StatusWahana(*W) = true;
    }
}

addressWahanaD AlokWahana (POINT P, Kata NamaWahana){
   /* Mengirimkan addressList hasil alokasi sebuah elemen */
   /* Jika alokasi berhasil, maka addressList tidak NilList, dan misalnya */
   /* menghasilkan P, maka InfoList(P)=X, Next(P)=NilList */
   /* Jika alokasi gagal, mengirimkan NilList */
   /* KAMUS */
   addressWahanaD D;
   /* ALGORITMA */
   D = (ElmtWahanaDinamis *) malloc(sizeof(ElmtWahanaDinamis)); 
   if (D!= NilList) {
       PositionWahana(D) = P;
       PetaWahana(D) = MapNum(Player);
       StatusWahana(D) = true ;
       TotalFreqWahana(D) = 0;
       IncomeWahana(D) = 0;
       DailyFreqWahana(D) = 0;
       NextWahana(D) = NilList;
       ElmtStatis(D) = SearchAddress(UpgradeTree, NamaWahana);
    }
    return D;
    
}

// Tadinya buat load tapi gajadi
// addressWahanaD AlokWahanaFile (POINT P, Kata NamaWahana, int TotalFreq, int Income, int DailyFreq, boolean Stat){
//    /* Mengirimkan addressList hasil alokasi sebuah elemen */
//    /* Jika alokasi berhasil, maka addressList tidak NilList, dan misalnya */
//    /* menghasilkan P, maka InfoList(P)=X, Next(P)=NilList */
//    /* Jika alokasi gagal, mengirimkan NilList */
//    /* KAMUS */
//    addressWahanaD D;
//    /* ALGORITMA */
//    D = (ElmtWahanaDinamis *) malloc(sizeof(ElmtWahanaDinamis)); 
//    if (D!= NilList) {
//        PositionWahana(D) = P;
//        StatusWahana(D) = Stat;
//        TotalFreqWahana(D) = TotalFreq;
//        IncomeWahana(D) = Income;
//        DailyFreqWahana(D) = DailyFreq;
//        NextWahana(D) = NilList;
//        ElmtStatis(D) = SearchAddress(UpgradeTree, NamaWahana);
//     }
//     return D;
    
// }

void InsFirstW (ListWahanaD *L, addressWahanaD D){
   /* I.S. L mungkin kosong */
   /* F.S. Melakukan alokasi sebuah elemen dan */
   /* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
   /* KAMUS */
   Next(D) = First(*L);
   First(*L) = D;
}
void InsAfterW (ListWahanaD *L, addressWahanaD P, addressWahanaD Prec){
   /* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
   /*      P sudah dialokasi  */
   /* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
   /* ALGORITMA */
   Next(P) = Next(Prec);
   Next(Prec) = P;
}
//print wahana yang sudah dibangun
void PrintInfoWD (ListWahanaD L) {
	/* I.S. List mungkin kosong */
	/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
	/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
	/* Jika list kosong : menulis [] */
	/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
	/* KAMUS */
	addressWahanaD P;
	/* ALGORITMA */
	if(IsEmptyListW(L)) {
        printf("()");

    } else { 
        printf("(");
        P = First(L); 

        while(P != NilList) {
            PrintKata(NamaWahana(ElmtStatis(P)));
            if(Next(P) != NilList){
                printf(", ");
            }
            P = Next(P);
        }
        printf(")");
    }
}
boolean SearchTree(Kata X, addressWahanaS P)
/* Mengirimkan true jika ada node dari P yang bernilai X */
{
     if (P==NilList) {
         return false;
     }
     else {
         if (IsKataSamaKata(NamaWahana(P),X)) {
            return true;
       }
         else {
             return (SearchTree(X,Left(P)) || SearchTree(X,Right(P)));
         }
     }
 }

 addressWahanaS SearchAddress (TreeWahanaS P, Kata NamWahana){
    if(IsTreeEmpty(P)) return NULL;
    else if(IsKataSamaKata(NamaWahana(P), NamWahana)){
       return P;
    }
    else{
       addressWahanaS L = SearchAddress(Left(P), NamWahana);
       addressWahanaS R = SearchAddress(Right(P), NamWahana);
       if(L != NULL) return L;
       else if (R != NULL) return R;
       else return NULL;
    }
 }

 addressWahanaS SearchAddressID (TreeWahanaS P, int num){
    if(IsTreeEmpty(P)) return NULL;
    else if(num == IDWahana(P)){
       return P;
    }
    else{
       addressWahanaS L = SearchAddressID(Left(P), num);
       addressWahanaS R = SearchAddressID(Right(P), num);
       if(L != NULL) return L;
       else if (R != NULL) return R;
       else return NULL;
    }
}

addressWahanaD SearchWahanaD (Kata inputWahana, ListWahanaD L)
/* I.S namaWahana dimasukkan user */
/* F.S Mengembalikan address dnegan wahana yang sesuai dengan yang dicari,
       apakah dia sudah pernah di build atau belum*/
{
    //KAMUS LOKAL
    boolean found = false;
    addressWahanaD P = First(L);
    //ALGORITMA

    while (!found && (P != NilList)){
        if (IsKataSamaKata(inputWahana, NamaWahana(ElmtStatis(P)))){
            found = true;
        } else {
            P = Next(P);
        }
    }
    return P;    
}

addressWahanaD SearchWahanaDP (POINT Pos, int MapNum, ListWahanaD L)
/* I.S namaWahana dimasukkan user */
/* F.S Mengembalikan address dnegan wahana yang sesuai dengan yang dicari,
       apakah dia sudah pernah di build atau belum*/
{
    //KAMUS LOKAL
    boolean found = false;
    addressWahanaD P = First(L);
    POINT Point = PositionWahana(P);
    //ALGORITMA

    while (!found && (P != NilList)){
        if (IsEqPOINT(Pos,Point) && MapNum == PetaWahana(P)){
            found = true;
        } else {
            P = Next(P);
        }
    }
    return P;    
}

void wahanaRusak(){
    int num = (rand() % (9 - 0 + 1)) + 1; 
     
    addressWahanaS P = SearchAddressID(UpgradeTree,num);
    addressWahanaD D = SearchWahanaD (NamaWahana(P),WahanaBuilt);
    if (D!=NilList){
        StatusWahana(D) = false;
    }
}
/*
boolean isWahanaRusak (player Pemain, addressWahanaD *D){
    
    // POINT Pemain; //belum tau cara ambil posisi pemain
    POINT Pos = SekitarPemain(Position(Pemain),'W');
    
    *D = SearchWahanaDP(Pos, MapNum(Pemain), WahanaBuilt);
    if (*D != NilList){
        return (!StatusWahana(*D));
    }
} */

boolean isSekitarPemain(){
    addressGraph CPeta = FirstGraph(GraphPeta); 

    while(ID(CPeta) != MapNum(Player)) //MapNum is ID yang ditempatin
        CPeta = NextGraph(CPeta);
    // Pos : Posisi wahana
    int x = X(Player);
    int y = Y(Player);

    if ((ElmtMatriks(Peta(CPeta), y, x+1) == 'W') || (ElmtMatriks(Peta(CPeta), y+1, x) == 'W') || (ElmtMatriks(Peta(CPeta), y, x - 1) == 'W') ||(ElmtMatriks(Peta(CPeta), y - 1, x) == 'W')){
        return true;
    } else return false;
}

//masi belom bener
POINT SekitarPemain (POINT Pemain, char C){
    addressGraph CPeta = FirstGraph(GraphPeta); //kenapa gabisa ajg

    while(ID(CPeta) != MapNum(Player)) 
        CPeta = NextGraph(CPeta);
    // Pos : Posisi wahana
    int x = Absis(Pemain);
    int y = Ordinat(Pemain);

    if(ElmtMatriks(Peta(CPeta), x+1, y) == C){
        return MakePOINT(x+1, y);
    } 
    else if (ElmtMatriks(Peta(CPeta), x, y+1) == C){
        return MakePOINT(x, y+1);
    }
    else if (ElmtMatriks(Peta(CPeta), x - 1, y) == C){
        return MakePOINT(x-1, y);
    }
    else if (ElmtMatriks(Peta(CPeta), x, y - 1) == C){
        return MakePOINT(x, y-1);
    }
}

//repair
// void Repair(addressWahanaD *D){
//     POINT Pemain;
//     POINT Pos = SekitarPemain(Pemain,'W');

//     *D = SearchWahanaDP(Pos, MapNum(Player), WahanaBuilt);
//     if (*D!=NilList){
//         StatusWahana(*D) = true;
//     }
    
// }

void PrintListW(ListWahanaD LW) {
    addressWahanaD P;
	/* ALGORITMA */
	if(IsEmptyListW(LW)) {
        printf("()");
    } else { 
        printf("(");
        P = FirstWahana(LW);
        while(P != NilList) {
            PrintKata(NamaWahana(ElmtStatis(P)));
            if(NextWahana(P) != NilList){
                printf(", ");
            }
            P = NextWahana(P);
        }
        printf(")");
    }
}

void Inoffice(){//contoh 
    
    Kata Cdetails, Crep, Cexit;

    //Pembentuk kata Details
    Cdetails.Length = 7;
    Cdetails.TabKata[0] = 'D';
    Cdetails.TabKata[1] = 'e';
    Cdetails.TabKata[2] = 't';
    Cdetails.TabKata[3] = 'a';
    Cdetails.TabKata[4] = 'i';
    Cdetails.TabKata[5] = 'l';
    Cdetails.TabKata[6] = 's';

    //Pembentuk kata Report
    Crep.Length = 6;
    Crep.TabKata[0] = 'R';
    Crep.TabKata[1] = 'e';
    Crep.TabKata[2] = 'p';
    Crep.TabKata[3] = 'o';
    Crep.TabKata[4] = 'r';
    Crep.TabKata[5] = 't';

    //Pembentuk kata Exit
    Cexit.Length = 4;
    Cexit.TabKata[0] = 'E';
    Cexit.TabKata[1] = 'x';
    Cexit.TabKata[2] = 'i';
    Cexit.TabKata[3] = 't';

    printf("\nMasukkan perintah (Details / Report / Exit): \n");
    STARTKATA();
    boolean finish = false;

    while (!finish){
        if (IsKataSamaKata(Cdetails,CKata)){
            MakeTree(); //udah ada di main
            printf("\nDaftar Wahana: \n");
            PrintTree(UpgradeTree);
            details(); finish = true;
        }     
        else if (IsKataSamaKata(Crep,CKata)){
            MakeTree(); //udah ada di main
            printf("\nDaftar Wahana: \n");
            PrintTree(UpgradeTree);
            report();
            finish = true;
        }
        else if (IsKataSamaKata(Cexit, CKata))
            finish = true;
        else
        {
            printf("Input yang dimasukkan salah!\n"); printf("Masukkan kembali input : ");
            STARTKATA();
        }
    }
}

void PrintHistory(Kata Wahana, addressWahanaS T){
    if(IsKataSamaKata(Wahana, NamaWahana(T))){
        PrintKata(NamaWahana(T));
    }
    else if(SearchTree(Wahana, Right(T))){
        PrintKata(NamaWahana(T)); printf("->");
        PrintHistory(Wahana, Right(T));
    }else if(SearchTree(Wahana, Left(T))){
        PrintKata(NamaWahana(T)); printf("->");
        PrintHistory(Wahana, Left(T));
    }
}

void PrintElmtS (addressWahanaS P, TreeWahanaS T){
    addressWahanaD D = SearchWahanaD (NamaWahana(P),WahanaBuilt);
    printf("\n----------Details Wahana----------\n");
    printf("Nama : "); PrintKata(NamaWahana(P)); printf("\n");

    printf("Lokasi : "); 
    if (D!=NilList){
        TulisPOINT(PositionWahana(D));//nampilin dari addressD
    } else printf("-");
    printf("\n");
    
    printf("Upgrade(s) : ["); 
    if (Left(P)!= NilList){
        PrintKata(NamaWahana(Left(P))); printf(", ");
    } else printf("");
    if (Right(P)!=NilList){
        PrintKata(NamaWahana(Right(P)));
    } else printf("");
    printf("]\n");

    //PrintKata(NamaWahana(Left(P))); printf(", "); PrintKata(NamaWahana(Right(P))); printf("]\n"); 
    printf("History : "); PrintHistory(NamaWahana(P),P); printf("\n");
    
    printf("Status : ");
    if (D == NilList) printf("-");
    else
        if (StatusWahana(D)){
            printf("berfungsi");
        } else printf("rusak");
    printf("\n\n");
}

void details(){
    printf("\nPilih wahana yang ingin ditampilkan Details-nya: \n");
    STARTKATA();

    addressWahanaS P = SearchAddress (UpgradeTree, CKata);

   // boolean foundD = false;
    while (P == NilList){//P == NilList){
        printf("Input yang dimasukkan salah!\n"); 
        printf("Masukkan kembali input : ");
        STARTKATA(); //PrintKata(CKata);
        
        P = SearchAddress (UpgradeTree, CKata);
    } 
    
    PrintElmtS(P,UpgradeTree);

}

void report()
/* I.S namaWahana dimasukkan user */
/* F.S Menampilkan report dari wahana*/
{
    First(WahanaBuilt) = NilList;
    
    printf("\nPilih wahana yang ingin ditampilkan Report-nya: \n");
    STARTKATA();

    boolean found = SearchTree(CKata, UpgradeTree);
    //printf("oke\n");

    while(!found){
        printf("Input yang dimasukkan salah!\n"); 
        printf("Masukkan kembali input : ");
        STARTKATA(); 
        found = SearchTree(CKata, UpgradeTree);
    }
    
    addressWahanaD P = SearchWahanaD (CKata,WahanaBuilt);
    printf("\n----------Report Wahana----------\n");
    printf("Berapa kali total dinaiki : ");
    if (P!=NilList) printf("%d",TotalFreqWahana(P));
    else printf("-\n");

    printf("Berapa kali dinaiki hari ini : ");
    if (P!=NilList) printf("%d",IncomeWahana(P));
    else printf("-\n");

    printf("Total penghasilan : ");
    if (P!=NilList) printf("%d",DailyFreqWahana(P));
    else printf("-");
    printf("\n\n");
}