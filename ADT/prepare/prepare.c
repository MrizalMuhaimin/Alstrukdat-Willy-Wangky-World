/* file : buy.c
merupakan bagian preparation phase
yang menampilkan commad BUY
*/

#include "prepare.h"
#include <stdio.h>
#include <stdlib.h>

void ProsedureBuild(POINT Pos, ListWahanaD *L)
/* Menambahkan  status build kedalam stack dan list wahana */
/*Command ini digunakan untuk membuat wahana baru di petak di mana
pemain sedang berdiri.
1. Setelah meminta command ini, program akan menampilkan
wahana dasar yang mungkin dibuat (hasil load file eksternal).
2. Setelah pemain memilih wahana dasar yang ingin dibuat.
3. Jika resource untuk membangun wahana tidak mencukupi, maka
akan ditampilkan pesan error.
4. Setelah itu, perintah eksekusi ini akan dimasukkan ke dalam
stack*/
{
    //Menampilkan wahana dasar (ada 10, diambil dari tree wahana)
    printf("Daftar wahana yang dapat dibangun: \n");
    PrintTree(UpgradeTree);
    addressWahanaD P, Prec;
    printf("\nIngin membangun wahana apa?\n-> ");
    STARTKATA(); 
    if (!IsKataSama ("")) {
        addressWahanaS addrWahana = SearchAddress(UpgradeTree, CKata);
        if(SearchTree(CKata,UpgradeTree)) {// wahana bisa dibangun
             // Cek bahan
            if (BahanCukup(&Player,BahanWahana(addrWahana),JmlBahan(addrWahana))) {
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
                
                Money(Player) = Money(Player) - UpgradeCost(addrWahana);
                DelElTab(&Tab(Player),BahanWahana(addrWahana),JmlBahan(addrWahana));
                // Masukkin ke stack
                Kata command;
                command.TabKata[0]='B';
                command.TabKata[1]='u';
                command.TabKata[2]='i';
                command.TabKata[3]='l';
                command.TabKata[4]='d';
                command.TabKata[5]='\n';
                command.Length = 5;
                aksi X;
                X.commandStack = command;
                X.durasi = 120;
                X.MapNumAksi = MapNum(Player);
                X.PointWahana = Position(Player);
                X.NamaBahan = BahanWahana(addrWahana);
                X.JumlahBahan = JmlBahan(addrWahana); 
                X.uang = UpgradeCost(addrWahana);
                PushE (&stackExecute, X); //Variabel globla stackExecute

                //Menambahkan W ke peta
                AddWToPeta();
            } 
            else { // bahan tidak cukup
                printf("Bahan yang Anda miliki tidak cukup untuk membangun wahana ini.\n");
            } 
        }
        else { // tidak ada di dalam daftar wahana yang bisa dibangun
            printf("%s\n","Wahana tidak ada dalam list wahana\n" );
        }   
          //endif wahana bs dibangun     
    }
    else { 
        printf("%s\n","Masukkan Anda enter" ); 
    }
    

}

void CommmandBuild()
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
{
     CreateEmpty (&stackExecute); // coba // buat test di deklarai di main awal
     First(WahanaBuilt) = NilList;
     MakeTree();
     printf("Daftar Wahana: \n");
     PrintTree(UpgradeTree);
     POINT P = Position(Player);
     ProsedureBuild(P,&WahanaBuilt);
     //printf("\n");
     PrintInfoWD(WahanaBuilt);
     printf("\n");
     
     
     
}

void UndoBuild() {
    // Pop
    // Tambahin uang
    // Tambahin bahan -> cek inventory pake PrintIsiTab
    // Delete di list wahana built -> Cek list WahanaBuilt
    aksi X;
    Pop(&stackExecute,&X);
    PrintInfoStack(stackExecute);
    Money(Player) += X.uang; //Tambahin uang
    AddElTab(&Tab(Player),X.NamaBahan,X.JumlahBahan); // Nambahin inventory
    /* 
    int i = 0;
    while (i < Neff(Tab(Player)) && !IsKataSamaKata(Elmt(Tab(Player), i).key,X.NamaBahan))
    {
        i++;
        
    }
    // ketemu nama wahana yang sama dan Tambahin bahan 
    Elmt(Tab(Player), i).value += X.JumlahBahan;
    */
    // Menghapus W dari peta
    addressGraph CPeta = FirstGraph(GraphPeta);

    while(ID(CPeta) != X.MapNumAksi){
        CPeta = NextGraph(CPeta);
    }

    ElmtMatriks(Peta(CPeta), Ordinat(X.PointWahana), Absis(X.PointWahana)) = '-';
    //PrintInfoWD(WahanaBuilt);

// pencarian elemen list bulid sebelum terakir yang akan di dealokasi
    addressWahanaD P, Prec;
    Prec = First(WahanaBuilt); 
    if(Next(Prec) == NilList)
    {
        First(WahanaBuilt) = NilList;
        free(Next(Prec));
    }
    else
    {  
        while (Next(Next(Prec)) != NilList)
        {
            Prec = Next(Prec);
        }
        P = Next(Prec);
        Next(Prec) = NilList;
        free(P);
    }
}

void CommmandBuyArray()
/* melakukan semua perintah yang ada didalam Command Buy
menampilkan daftar bahan kemudian menerima inputan dan mengatusr senua case 
input salah atau benar kemudian masukin ke stack */
{
	//CreateEmpty (&stackExecute); // coba // buat test
	//Tab File_material; //variabel global
	BacaIsiMaterial(&File_material);
	TulisIsiTabMaterial(File_material);
	printf("\n%s\n%s\n%s\n%s","Masukkan Perintah:","<jumlah> <material>","<enter untuk keluar>","-> ");
	STARTKATA();
	while (!IsKataSama (""))
	{
		player PTes; // TEST
		CreatePlayer(&PTes); // TEST
		int val;
		int Nbahan;
		Nbahan = convToInt(CKata);
		ADVKATA();
		if (SearchK(File_material, CKata) && !IsKataSama (""))
		{
			val = Nbahan * SearchVal(File_material, CKata);
			//printf("%i\n",val);
            if (UangCukup(&Player,val)) {
                Money(Player) = Money(Player) - val;
                AddElTab(&Tab(Player),CKata,Nbahan);  // TEST

                Kata command;
                command.TabKata[0]='B';
                command.TabKata[1]='u';
                command.TabKata[2]='y';
                command.TabKata[3]='\n';
                command.Length = 3;

                POINT P = MakePOINT(0,0);

                aksi X;
                X.commandStack = command;
                X.durasi = 10;
                X.PointWahana = P;
                X.NamaBahan = CKata;
                X.JumlahBahan = Nbahan;
                X.uang = val;
                
                printf("\nAnda membeli "); PrintKata(CKata); printf(" sebanyak %d buah.\n\n",Nbahan);
                printf("Daftar bahan yang dimiliki:\n");
                for (int i=GetFirstIdxDin(Tab(Player)); i<=GetLastIdxDin(Tab(Player)); i++){
                    PrintKata(Elmt(Tab(Player),i).key);
                    printf(" - ");
                    printf("%d",Elmt(Tab(Player),i).value);
                    printf("\n");
                }
                PushE(&stackExecute, X); //Variabel globla stackExecute
            }
            else {
                printf("Uang Anda tidak cukup untuk melakukan pembelian.\n");
            }
		}
		else
		{
			printf("%s\n","Material tidak ada di list atau perintah Anda tidak valid.\n" );
		}
		printf("\n%s\n%s\n%s\n%s","Masukkan Perintah:","<jumlah> <material>","<enter untuk keluar>","-> ");
		STARTKATA();	
	}
	// else
	// {
		printf("Anda keluar dari menu buy\n");
        //UndoBuy ();
        //PrintInfoStack(stackExecute); 
	// }

}

void UndoBuy () {
// Pop
// Uang ditambah
// Inventory berkurang (delete dari arraydinmap) -> belom bikin fungsinya. Cek inventory pake print Isi
aksi X;
Pop(&stackExecute,&X);
Money(Player) += X.uang;
DelElTab(&Tab(Player), X.NamaBahan, X.JumlahBahan);
}


void upgradeWahana() {
/* STEPS:
- Cek titik, krn cuma bisa upgrade di sekitar tempat yg ada wahana.
- Cek uang dan resource, kalo gacukup tampilkan pesan error.
- Kalo cukup => pengen upgrade apa?

1. Setelah meminta command ini, program akan menampilkan daftar
upgrade yang mungkin untuk tipe wahana tersebut.
2. Jika resource untuk mengupgrade wahana tidak mencukupi, maka
akan ditampilkan pesan error.
3. Setelah itu, perintah eksekusi ini akan dimasukkan ke dalam
stack

 */
    int X = X(Player);
    int Y = Y(Player);
    POINT P;

    addressGraph CPeta = FirstGraph(GraphPeta);
    while(ID(CPeta) != MapNum(Player)) CPeta = NextGraph(CPeta);
    if (ElmtMatriks(Peta(CPeta), Y-1, X) == 'W' || ElmtMatriks(Peta(CPeta), Y+1, X) == 'W' || ElmtMatriks(Peta(CPeta), Y, X-1) == 'W' || ElmtMatriks(Peta(CPeta), Y, X+1) == 'W'){
        printf("\nList wahana yang bisa diupgrade:\n");

        if(ElmtMatriks(Peta(CPeta), Y-1, X) == 'W'){
            P = MakePOINT(X,Y-1);
            PrintKata(NamaWahana(ElmtStatis(SearchWahanaDP(P, MapNum(Player), WahanaBuilt)))); printf("\n");
        }

        if(ElmtMatriks(Peta(CPeta), Y+1, X) == 'W'){
            P = MakePOINT(X, Y+1);
            PrintKata(NamaWahana(ElmtStatis(SearchWahanaDP(P, MapNum(Player), WahanaBuilt)))); printf("\n");
        }

        if(ElmtMatriks(Peta(CPeta), Y, X-1) == 'W'){
            P = MakePOINT(X-1,Y);
            PrintKata(NamaWahana(ElmtStatis(SearchWahanaDP(P, MapNum(Player), WahanaBuilt)))); printf("\n");
        }

        if(ElmtMatriks(Peta(CPeta), Y, X+1) == 'W'){
            P = MakePOINT(X+1, Y);
            PrintKata(NamaWahana(ElmtStatis(SearchWahanaDP(P, MapNum(Player), WahanaBuilt)))); printf("\n");
        }

        printf("\nPilih wahana yang ingin diupgrade: ");
        STARTKATA(); printf("\n");
        addressWahanaD wahanaToUpgrade = SearchWahanaD(CKata, WahanaBuilt);
        addressWahanaS elmtStatisUpgrade = ElmtStatis(wahanaToUpgrade);
        addressWahanaS addrPrevWahana = elmtStatisUpgrade; // address wahana sebelumnya

        //addressWahanaD elmtStatisUpgradeD = SearchWahanaD(namaWahana,WahanaBuilt);
        //addressWahanaS elmtStatisUpgrade;
        /* 
        if (elmtStatisUpgradeD != NULL) {
            elmtStatisUpgrade = ElmtStatis(elmtStatisUpgradeD);
            printf("Ketemu, nama wahana: "); printf("\n");
            PrintKata(NamaWahana(elmtStatisUpgrade)); printf("\n");
            printf("Ingin melakukan upgrade apa?\n"); */
            
            addressWahanaS addrElmtUpgraded; // address wahana setelah upgrade
            if (Left(elmtStatisUpgrade)== NULL && Right(elmtStatisUpgrade)==NULL) { // Kondisi udah mentok gabisa diupgrade
                printf("Tidak dapat diupgrade.");
            }
            else { // bisa diupgrade
                // Kalo bisa diupgrade, tampilin list terus cek resource dan uang
                // Ngecek resource: wahana yang dituju
                // Ngecek uang (upgrade cost): wahana asal
                Kata elmtUpgrade;
                printf("List:\n");
                if (Left(elmtStatisUpgrade)!=NULL && Right(elmtStatisUpgrade)==NULL){ // Cuma bisa upgrade ke left
                    PrintKata(NamaWahana(Left(elmtStatisUpgrade))); printf("\n");
                    // cek resource DAN UPGRADE COST 
                    if (SemuaCukup (&Player,BahanWahana(Left(elmtStatisUpgrade)),JmlBahan(Left(elmtStatisUpgrade)),UpgradeCost(elmtStatisUpgrade))) {
                        // Bisa upgrade
                        /* Kode mau upgrade kemana */
                        printf("\nMau upgrade kemana: ");
                        STARTKATA();
                        printf("\n");
                        CopyKata(CKata,&elmtUpgrade);
                        while ((!IsKataSamaKata(elmtUpgrade,NamaWahana(Left(elmtStatisUpgrade))))) {
                            printf("Nama wahana yang Anda tulis salah. Mau upgrade kemana: ");
                            STARTKATA();
                            CopyKata(CKata,&elmtUpgrade);
                        }


                        // Kurangin uang dan bahan
                        Money(Player) = Money(Player) - UpgradeCost(elmtStatisUpgrade);
                        DelElTab(&Tab(Player),BahanWahana(Left(elmtStatisUpgrade)),JmlBahan(Left(elmtStatisUpgrade)));


                        addrElmtUpgraded = Left(elmtStatisUpgrade);

                        ElmtStatis(wahanaToUpgrade) = addrElmtUpgraded; // mengganti elemen statisnya
                        elmtStatisUpgrade = addrElmtUpgraded; // mengganti elemen statisnya
                        PrintUpgraded(addrPrevWahana,elmtStatisUpgrade);

                            UpgradeStack(addrPrevWahana,elmtStatisUpgrade); // Buat nge push ke stack
                            PrintInfoStack(stackExecute);
                    }
                    else {
                        printf("\nBahan atau uang yang kamu miliki \ntidak cukup untuk melakukan upgrade.\n");
                    }
                } 
                else if (Left(elmtStatisUpgrade)==NULL && Right(elmtStatisUpgrade)!=NULL){ // Cuma bisa upgrade ke right
                    PrintKata(NamaWahana(Right(elmtStatisUpgrade))); printf("\n");
                    if (SemuaCukup (&Player,BahanWahana(Right(elmtStatisUpgrade)),JmlBahan(Right(elmtStatisUpgrade)),UpgradeCost(elmtStatisUpgrade))) {
                        
                        // Bisa upgrade
                        /* Kode mau upgrade kemana */
                        printf("Mau upgrade kemana: ");
                        STARTKATA();
                        CopyKata(CKata,&elmtUpgrade);
                        while ((!IsKataSamaKata(elmtUpgrade,NamaWahana(Right(elmtStatisUpgrade))))) {
                            printf("Nama wahana yang Anda tulis salah. \nMau upgrade kemana: ");
                            STARTKATA();
                            CopyKata(CKata,&elmtUpgrade);
                        }
                            // Kurangin uang dan bahan
                            Money(Player) = Money(Player) - UpgradeCost(elmtStatisUpgrade);
                            DelElTab(&Tab(Player),BahanWahana(Right(elmtStatisUpgrade)),JmlBahan(Right(elmtStatisUpgrade)));

                        addrElmtUpgraded = Right(elmtStatisUpgrade);
                        ElmtStatis(wahanaToUpgrade) = addrElmtUpgraded; // mengganti elemen statisnya
                        elmtStatisUpgrade = addrElmtUpgraded;

                            PrintUpgraded(addrPrevWahana,elmtStatisUpgrade);

                            UpgradeStack(addrPrevWahana,elmtStatisUpgrade); // Buat nge push ke stack
                            PrintInfoStack(stackExecute);
                    }
                    else {
                        printf("Bahan atau uang yang kamu miliki \ntidak cukup untuk melakukan upgrade.\n");
                    }
                }
                else { // Bisa diupgrade ke left ataupun right
                    PrintKata(NamaWahana(Left(elmtStatisUpgrade))); printf("\n");
                    PrintKata(NamaWahana(Right(elmtStatisUpgrade))); printf("\n");
                    printf("Mau upgrade kemana: ");
                    STARTKATA();
                    CopyKata(CKata,&elmtUpgrade);
                    while ((!IsKataSamaKata(elmtUpgrade,NamaWahana(Left(elmtStatisUpgrade)))) && (!IsKataSamaKata(elmtUpgrade,NamaWahana(Right(elmtStatisUpgrade))))) {
                        printf("Nama wahana yang Anda tulis salah. \nMau upgrade kemana: ");
                        STARTKATA();
                        CopyKata(CKata,&elmtUpgrade);
                    }
                    if (IsKataSamaKata(elmtUpgrade,NamaWahana(Left(elmtStatisUpgrade)))) {
                        // Mau upgrade ke kiri
                        if (SemuaCukup (&Player,BahanWahana(Left(elmtStatisUpgrade)),JmlBahan(Left(elmtStatisUpgrade)),UpgradeCost(elmtStatisUpgrade))) {
                            // Bisa upgrade

                            // Kurangin uang dan bahan
                            Money(Player) = Money(Player) - UpgradeCost(elmtStatisUpgrade);
                            DelElTab(&Tab(Player),BahanWahana(Left(elmtStatisUpgrade)),JmlBahan(Left(elmtStatisUpgrade)));

                            addrElmtUpgraded = Left(elmtStatisUpgrade);
                            ElmtStatis(wahanaToUpgrade) = addrElmtUpgraded; // mengganti elemen statisnya
                            elmtStatisUpgrade = addrElmtUpgraded;
                            PrintUpgraded(addrPrevWahana,elmtStatisUpgrade);

                            UpgradeStack(addrPrevWahana,elmtStatisUpgrade); // Buat nge push ke stack
                            PrintInfoStack(stackExecute); 
                            }
                        else {
                            printf("Bahan atau uang yang kamu miliki \ntidak cukup untuk melakukan upgrade.\n");
                        }
                    }
                    if (IsKataSamaKata(elmtUpgrade,NamaWahana(Right(elmtStatisUpgrade)))) {
                        if (SemuaCukup (&Player,BahanWahana(Right(elmtStatisUpgrade)),JmlBahan(Right(elmtStatisUpgrade)),UpgradeCost(elmtStatisUpgrade))) {
                            // Mau upgrade ke kanan
                            // Bisa upgrade
                            // Kurangin uang dan bahan
                            Money(Player) = Money(Player) - UpgradeCost(elmtStatisUpgrade);
                            DelElTab(&Tab(Player),BahanWahana(Right(elmtStatisUpgrade)),JmlBahan(Right(elmtStatisUpgrade)));
                            
                            addrElmtUpgraded = Right(elmtStatisUpgrade);
                            ElmtStatis(wahanaToUpgrade) = addrElmtUpgraded; // mengganti elemen statisnya
                            elmtStatisUpgrade = addrElmtUpgraded;

                            PrintUpgraded(addrPrevWahana,elmtStatisUpgrade);

                            UpgradeStack(addrPrevWahana,elmtStatisUpgrade); // Buat nge push ke stack
                            PrintInfoStack(stackExecute);
                            }
                        else { // gabisa upgrade
                            printf("Bahan atau uang yang kamu miliki \ntidak cukup untuk melakukan upgrade.\n");
                        }
                    }
                }
 
        }

    } else { // Tidak bisa upgrade, karena tidak di sekitar wahana
        printf("Tidak bisa melakukan upgrade, karena tidak berada di sekitar wahana\n");
    }
}

void UndoUpgrade(){
    // Pop
    // Tambahin uang
    // Tambahin bahan ke inventory
    // Balikin ke elemen parent nya
    aksi aksiUpgrade;
    Pop(&stackExecute,&aksiUpgrade);
    Money(Player) += aksiUpgrade.uang;
    AddElTab(&Tab(Player),aksiUpgrade.NamaBahan,aksiUpgrade.JumlahBahan);
    addressWahanaS parent = ElmtStatis(SearchWahanaDP(aksiUpgrade.PointWahana,aksiUpgrade.MapNumAksi,WahanaBuilt));
    parent = aksiUpgrade.addrPrevWahana; // semoga bener
}

void Undo(){
    Kata KataBuild;
    KataBuild.TabKata[0]='B';
    KataBuild.TabKata[1]='u';
    KataBuild.TabKata[2]='i';
    KataBuild.TabKata[3]='l';
    KataBuild.TabKata[4]='d';
    KataBuild.TabKata[5]='\n';
    KataBuild.Length = 5;

    Kata KataBuy;
    KataBuy.TabKata[0]='B';
    KataBuy.TabKata[1]='u';
    KataBuy.TabKata[2]='y';
    KataBuy.TabKata[3]='\n';
    KataBuy.Length = 3;

    Kata KataUpgrade;
    KataUpgrade.TabKata[0]='U';
    KataUpgrade.TabKata[1]='p';
    KataUpgrade.TabKata[2]='g';
    KataUpgrade.TabKata[3]='r';
    KataUpgrade.TabKata[4]='a';
    KataUpgrade.TabKata[5]='d';
    KataUpgrade.TabKata[6]='e';
    KataUpgrade.TabKata[7]='\n';
    KataUpgrade.Length = 6;

    if(IsKataSamaKata(KataBuild, InfoTop(stackExecute).commandStack)){
        UndoBuild();
    }else if(IsKataSamaKata(KataBuy, InfoTop(stackExecute).commandStack)){
        UndoBuy();
    }else if (IsKataSamaKata(KataUpgrade,InfoTop(stackExecute).commandStack)) {
        UndoUpgrade(); 
    }
}

void PrepMain() {
    while (!IsEmptyStack(stackExecute)) {
        Undo();
        //PrintInfoStack();
    }
}

void PrepExecute() {
    aksi X;
    InverseStack(stackExecute);
    while (!IsEmptyStack(stackExecute)) {
        Pop(&stackExecute,&X);
    }
}