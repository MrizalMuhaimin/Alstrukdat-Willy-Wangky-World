#include "saveload.h"
#include <string.h>

void load(){
    struct dirent *entries;  // Pointer for directory entry 
    char directory[50] = "../../Save";
    boolean found = false;
    char* tempdir;
    addressWahanaD P, Prec;
    MakeTree();

    DIR *dr = opendir(directory); 
  
    if (dr != NULL)  // opendir returns NULL if couldn't open directory 
    {
        entries = readdir(dr);
        entries = readdir(dr);
        if((entries = readdir(dr)) != NULL){
            printf("Pilih user:\n");
            printf("%s\n", entries->d_name);
        }
        while ((entries = readdir(dr)) != NULL){
            printf("%s\n", entries->d_name);
        }
    } 

    closedir(dr); 

    STARTKATA();

    while(!found){
        DIR *dr = opendir(directory);
        entries = readdir(dr);
        do{
            if(IsKataSama(entries->d_name)) found = true;
            else entries = readdir(dr);
        } while (entries != NULL && !found);
        closedir(dr);

        if(!found){
            printf("User tidak ada\n");
            STARTKATA();
        }
    }
    strcat(directory, "/");
    strcat(directory, entries->d_name);

    //Ini ngeload player
    strcpy(tempdir, directory);
    printf("%s\n", directory);
    strcat(tempdir, "/");
    
    strcat(tempdir, "player.txt");
    
    STARTFILE(tempdir);
    
    //Nyalin nama
    SalinKataFile();
    CopyKata(CKata, &(Player.Name));

    //Nyalin posisi
    SalinKataFile();
    X(Player) = convToInt(CKata);

    SalinKataFile();
    Y(Player) = convToInt(CKata);

    //Nyalin mapnum
    SalinKataFile();
    MapNum(Player) = convToInt(CKata);

    //Nyalin CJam
    SalinKataFile();
    int Jam = convToInt(CKata);
    SalinKataFile();
    int Menit = convToInt(CKata);
    CJam(Player) = MakeJAM(Jam, Menit);

    //Nyalin Uang
    SalinKataFile();
    Money(Player) = convToInt(CKata);

    //Nyalin hari
    SalinKataFile();
    Day(Player) = convToInt(CKata);
    ADV();
    
    //Masih kurang inventory

    printf("\n");
    TulisPOINT(Position(Player));
    printf("\nMapnum:%d\nDay:%d\n", MapNum(Player), Day(Player));
    TulisJAM(CJam(Player));
    printf("\nMoney: %d\n\n", Money(Player));

    //Nyalin wahana yang udah dibangun
    First(WahanaBuilt) = NULL;

    while(!EOP){
        //Nyalin point wahana
        SalinKataFile();
        int X = convToInt(CKata);
        SalinKataFile();
        int Y = convToInt(CKata);
        POINT PWahana = MakePOINT(X,Y);
        
        //Total freq
        SalinKataFile();
        int TotalFreq = convToInt(CKata);

        // income
        SalinKataFile();
        int Income = convToInt(CKata);

        // DailyFreq
        SalinKataFile();
        int DailyFreq = convToInt(CKata);

        //Status
        SalinKataFile();
        boolean Stat = convToInt(CKata);

        SalinKataFile();

        P = AlokWahanaFile(PWahana, CKata, TotalFreq, Income, DailyFreq, Stat);

        PrintKata(CKata); printf("\n");

        TulisPOINT(PositionWahana(P)); printf("\n");

        printf("TotalFreq: %d\nIncome: %d\nDailyFreq; %d\nStat: %d\n\n", TotalFreqWahana(P), IncomeWahana(P), DailyFreqWahana(P), StatusWahana(P));
        //masukkin ke list  wahana
        if (IsEmptyListW(WahanaBuilt)){
            InsFirstW(&WahanaBuilt,P);
        }else{
            Prec = First(WahanaBuilt); 

            while (Next(Prec)!=NilList){
                Prec = Next(Prec);
            }
            InsAfterW(&WahanaBuilt, P, Prec);
        }
        ADV();
    }

    PrintInfoWD(WahanaBuilt);
    //Nyalin peta
    strcpy(tempdir, directory);
    strcat(tempdir, "/");
    strcat(tempdir, "Peta_1.txt");

    MakePETA(tempdir, &Peta1);

    strcpy(tempdir, directory);
    strcat(tempdir, "/");
    strcat(tempdir, "Peta_2.txt");

    MakePETA(tempdir, &Peta2);

    strcpy(tempdir, directory);
    strcat(tempdir, "/");
    strcat(tempdir, "Peta_3.txt");

    MakePETA(tempdir, &Peta3);

    strcpy(tempdir, directory);
    strcat(tempdir, "/");
    strcat(tempdir, "Peta_4.txt");

    MakePETA(tempdir, &Peta4);

    CreateGraphPeta();
}

// gcc driver.c ../wahana/wahana.c ../graph/graph.c ../arraydinmap/arraydinmap.c ../peta/peta.c ../matriks/matriks.c ../point/point.c saveload.c ../jam/jam.c ../player/player.c ../mesinkar/mesinkar.c ../mesinkata/mesinkata.c -o test