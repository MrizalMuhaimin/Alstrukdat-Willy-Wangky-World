#include <stdio.h>
#include "menu.h"


Graph GraphPeta;
MATRIKS Peta1, Peta2, Peta3, Peta4;
TreeWahanaS UpgradeTree;
player Player;
// ListWahanaD WahanaBuilt;

void MainMenu(){
    printf("\033[1;33m");
    printf("          _ _ _                                   _          _\n");     
    printf("         (_| | |                                 | |        ( )\n");    
    printf("__      ___| | |_   _  __      ____ _ _ __   __ _| | ___   _|/ ___\n"); 
    printf("\\ \\ /\\ / | | | | | | | \\ \\ /\\ / / _` | '_ \\ / _` | |/ | | | | / __|\n");
    printf(" \\ V  V /| | | | |_| |  \\ V  V | (_| | | | | (_| |   <| |_| | \\__ \\\n");
    printf("  \\_/\\_/ |_|_|_|\\__, |   \\_/\\_/ \\__,_|_| |_|\\__, |_| \\_\\__, | |___/\n");
    printf("                 __/ |                       __/ |      __/ |\n");      
    printf("                |___/                       |___/      |___/       \n");
    printf("          __     __  ______  ______  __      _____\n");    
    printf("         /\\ \\  _ \\ \\/\\  __ \\/\\  == \\/\\ \\    /\\  __-.\n");  
    printf("         \\ \\ \\/ \".\\ \\ \\ \\/\\ \\ \\  __<\\ \\ \\___\\ \\ \\/\\ \\\n"); 
    printf("          \\ \\__/\".~\\_\\ \\_____\\ \\_\\ \\_\\ \\_____\\ \\____-\n"); 
    printf("           \\/_/   \\/_/\\/_____/\\/_/ /_/\\/_____/\\/____/\n\n"); 
    printf("\033[0m");                                         
    printf("====================================================================\n\n");
    printf("\033[0;35m");
    printf("                Welcome to Willy Wangky's World!\n");
    printf("Here, you can make your own amusement park and do so many fun stuff!\n\n");
    printf("\033[0m");
    printf("====================================================================\n\n");
    printf("\033[0;35m");
    printf(" __| |_______________| |__                __| |________________| |__\n");
    printf("(__   _______________   __)              (__   ________________   __)\n");
    printf("   | |               | |                    | |                | |\n");
    printf("   | |     N E W     | |                    | |     E X I T    | |\n");
    printf(" __| |_______________| |__                __| |________________| |__\n");
    printf("(__   _______________   __               (__   ________________   __ \n");
    printf("   | |               | |                    | |                | |\n\n");
    printf("\033[0m");
    printf("====================================================================\n");
    STARTKATA();

    printf("====================================================================\n");
}

void MenuJalan(player *p1, Graph G){
    CJam(*p1) = NextMenit(CJam(*p1));
    if (IsKataSama("w")){
        w(p1, G);
    }else if (IsKataSama("a")){
        a(p1, G);
    }else if (IsKataSama("s")){
        s(p1, G);
    }else if (IsKataSama("d")){
        d(p1, G);
    }
}

void ListCommand(){
    printf("================================================================\n");
    printf("Berjalan ke atas: \"w\"\n");
    printf("Berjalan ke kiri: \"a\"\n");
    printf("Berjalan ke bawah: \"s\"\n");
    printf("Berjalan ke kanan: \"d\"\n");
    printf("Memperbaiki wahana: \"repair\"\n");
    printf("   Hanya bisa digunakan ketika pemain berada di sebelah wahana\n");
    printf("Melihat detail wahana: \"detail\"\n");
    printf("   Hanya bisa digunakan ketika pemain berada di sebelah wahana\n");
    printf("Masuk office: \"office\"\n");
    printf("   Hanya bisa digunakan ketika pemain berada di atas office\n");
    printf("Keluar Game: \"exit\"\n\n");

    printf("Command yang hanya bisa dilakukan saat preparation phase:\n");
    printf("Bangun wahana: \"build\"\n");
    printf("Upgrade wahana: \"upgrade\"\n");
    printf("Beli item: \"buy\"\n");
    printf("Undo: \"undo\"\n");
    printf("Pergi ke Main Phase tanpa execute (stack): \"main\"\n");
    printf("Pergi ke Main Phase dengan execute (stack): \"execute\"\n\n");

    printf("Command yang hanya bisa dilakukan saat main phase:\n");
    printf("Melayani pelanggan saat main phase: \"main\"\n");
    printf("Melayani pengunjung: \"serve <nama wahana>\"\n");
    printf("   Hanya bisa digunakan ketika pemain berada di sebelah antrian\n");
    printf("Pergi ke Preparation Phase: \"prepare\"\n");
    printf("================================================================\n");
}

void Preparation(player *p1){
    boolean invalid = false;
    do{
        addressGraph CPeta = FirstGraph(GraphPeta);
        while(ID(CPeta) != MapNum(Player)) CPeta = NextGraph(CPeta);

        if (!IsKataSama("command") && !invalid){
            printf("==========================================================\n");
            printf("\033[0;34m");
            printf("\n                    Preparation Phase\n");
            printf("                         Day %d\n\n", Day(*p1));
            printf("\033[0m");
            printf("==========================================================\n\n");
            printf("\033[0;34m");
            TulisMATRIKS(Peta(CPeta));
            printf("\033[0m");
            printf("\n==========================================================\n");
            printf("\033[0;34m");
            printf("           ");printf("Legend:\n");
            printf("           ");printf("A = Antrian\n");
            printf("           ");printf("P = Player\n");
            printf("           ");printf("W = Wahana\n");
            printf("           ");printf("O = Office\n");
            printf("           ");printf("^, >, v, < = Gerbang\n");
            printf("\033[0m");
            printf("==========================================================\n");
            printf("\033[0;34m");
            TulisPlayer();
            printf("           ");printf("Current Time: "); TulisJAM(CJam(*p1)); printf("\n");
            printf("           ");printf("Opening Time: "); TulisJAM(JamBuka); printf("\n");
            printf("           ");printf("Time Remaining:"); TulisTimeRemaining(Durasi(CJam(*p1), JamBuka)); 
            printf("\n\n"); TulisIsiTab(Tab(Player)); printf("\n");
            PrintInfoStack(stackExecute);
            printf("\033[0m");
            // Total aksi yang akan dilakukan:
            // Total waktu yang dibutuhkan:
            // Total uang yang dibutuhkan:
            printf("==========================================================\n");
            printf("\033[0;35m");
            printf("Masukkan \"command\" untuk melihat daftar command yang ada\n");
            printf("\033[0m");
            printf("==========================================================\n");
            if(ElmtMatriks(Peta(CPeta), Y(Player), X(Player)) == 'O'){
                printf("\033[0;35m");
                printf("Masukkan 'office' untuk mengakses office \n");
                printf("\033[0m");
                printf("==========================================================\n");
            }
        }
        
        if(!invalid){
            printf("\033[0;33m");
            printf("Masukkan perintah: ");
            printf("\033[0m");
            STARTKATA();
        }

        invalid = false;

        if (IsKataSama("w") || IsKataSama("a") || IsKataSama("s") || IsKataSama("d")){
           MenuJalan(p1, GraphPeta);
        } else if (IsKataSama("command")){
            ListCommand();
        } else if (IsKataSama("build")){
            //buildWahana(Position(Player), &WahanaBuilt);
            ProsedureBuild(Position(Player), &WahanaBuilt);
            //printf("%d\n", IsEmptyListW(WahanaBuilt));
        } else if (IsKataSama("buy")){
            CommmandBuyArray();
        } else if (IsKataSama("upgrade")){
            upgradeWahana();
        } else if (IsKataSama("office")){
            if(ElmtMatriks(Peta(CPeta), Y(Player), X(Player)) == 'O'){
                Inoffice();
            } else {
                printf("\033[0;31m");
                printf("Anda sedang tidak ada berada di dalam office\n");
                printf("\033[0m");
            }
        } else if (IsKataSama("undo")) {
            Undo();
        } else if (IsKataSama("execute")) {
            PrepExecute();
        } else if (IsKataSama("main")) {
            PrepMain();
        }
        // nanti tambahin elif aja buat command yang lain
        else if(!(IsKataSama("main") || IsKataSama("exit") || IsKataSama("execute"))){
            printf("\033[0;31m");
            printf("==========================================================\n");
            printf("Command tidak tersedia\n");
            printf("==========================================================\n");
            printf("\033[0;35m");
            printf("Masukkan \"command\" untuk melihat daftar command yang ada\n");
            printf("\033[0m");
            printf("==========================================================\n");
            printf("\033[0m");
            printf("\033[0;33m");
            printf("Masukkan perintah: ");
            printf("\033[0m");
            invalid = true;
            STARTKATA();
        }
    } while (!(IsKataSama("main") || (IsKataSama("exit")) || IsKataSama("execute")));
}

void MainPhase(player * p1){
    PrioQueue Q;
    listPlayer LP;
    infoLP del;
    boolean enter = false;
    boolean invalid = false;
    CreateEmptyQueue(&Q, 5);
    CreateEmptyLP(&LP);
    if (!IsEmptyListW(WahanaBuilt)) {
        RandomizeQueue(&Q, WahanaBuilt);
    }

    do{
        addressGraph CPeta = FirstGraph(GraphPeta);
        while(ID(CPeta) != MapNum(Player)) CPeta = NextGraph(CPeta);

        if (!IsEmptyListW(WahanaBuilt) && IsEmptyQueue(Q)) {
            int X = rand() % 2;
            if(X == 1){
                RandomizeQueue(&Q, WahanaBuilt);
                enter = false;
            }
            
        }

        if(enter && !IsEmptyQueue(Q)){
            ReducePatience(&Q);
            Q = AngryCustomer(Q);
        }
        
        if(!IsEmptyLP(LP)){
            ReduceTime(&LP);
            for(int i = 0; i < CountCompleted(LP); i++) {
                DelCompleted(&LP, &del);
                FirstEnqueue(&Q, del);
            }
        }

        enter = true;

        
        if (!IsKataSama("command") && !invalid){
            printf("==========================================================\n");
            printf("\033[0;34m");
            printf("\n                      Main Phase\n");
            printf("                        Day %d\n\n", Day(*p1));
            printf("\033[0m");
            printf("==========================================================\n\n");
            printf("\033[0;34m");
            TulisMATRIKS(Peta(CPeta));
            printf("\033[0m");
            printf("\n==========================================================\n");
            printf("\033[0;34m");
            printf("           ");printf("Legend:\n");
            printf("           ");printf("A = Antrian\n");
            printf("           ");printf("P = Player\n");
            printf("           ");printf("W = Wahana\n");
            printf("           ");printf("O = Office\n");
            printf("           ");printf("^, >, v, < = Gerbang\n");
            printf("\033[0m");
            printf("==========================================================\n");
            printf("\n");
            printf("\033[0;34m");
            TulisPlayer(); //print nama dan uang
            printf("           ");printf("Current Time: "); TulisJAM(CJam(*p1)); printf("\n");
            printf("           ");printf("Closing Time: "); TulisJAM(JamTutup); printf("\n");
            printf("           ");printf("Time Remaining:"); TulisTimeRemaining(Durasi(CJam(*p1), JamTutup)); 
            printf("\n");
            printf("\n");
            if (IsEmptyListW(WahanaBuilt)) {
                printf("\033[0;31m");
                printf("Tidak ada wahana yang tersedia.\n");
                printf("\033[0m");
            } else{
                if(!IsEmptyQueue(Q)){
                    printf("     Antrian [%d/5] :\n", NbElmtQueue(Q));
                    PrintPrioQueue(Q);
                } else {
                    printf("\033[0;31m");
                    printf("Antrian kosong\n");
                    printf("\033[0m");
                }
            }
            
            printf("\033[0;31m");
            addressWahanaD P = First(WahanaBuilt);
            while (P != NilList){
                if ((StatusWahana(P)) == false){
                    printf("\033[0;31m");
                    printf("Broken : ");
                    PrintKata(NamaWahana(ElmtStatis(P)));
                    printf("\033[0;31m");
                }
                P = NextWahana(P);
            }
            printf("\033[0m");
            
            printf("\n");
            printf("==========================================================\n");
            printf("\033[0;35m");
            printf("Masukkan \"command\" untuk melihat daftar command yang ada\n");
            printf("\033[0m");
            printf("==========================================================\n");
            if(ElmtMatriks(Peta(CPeta), Y(Player), X(Player)) == 'O'){
                printf("\033[0;35m");
                printf("Masukkan 'office' untuk mengakses office \n");
                printf("\033[0m");
                printf("==========================================================\n");
            }
        }

        if(!invalid){
            printf("\033[0;33m");
            printf("Masukkan perintah: ");
            printf("\033[0m");
            
            STARTKATA();
        }

        invalid = false;

        if (IsKataSama("w") || IsKataSama("a") || IsKataSama("s") || IsKataSama("d")){
           MenuJalan(p1, GraphPeta);
        } else if (IsKataSama("command")){
            ListCommand();
        } else if (IsKataSama("serve")) {
            ADVKATA();
            addressGraph CPeta = FirstGraph(GraphPeta);
            int x = X(*p1), y = Y(*p1);
            while(ID(CPeta) != MapNum(*p1)){
                CPeta = NextGraph(CPeta);
            }
            if(ElmtMatriks(Peta(CPeta), y + 1, x) == 'A' || ElmtMatriks(Peta(CPeta), y, x+1) == 'A' || ElmtMatriks(Peta(CPeta), y - 1, x) == 'A' || ElmtMatriks(Peta(CPeta), y, x - 1) == 'A'){
                Serve(p1, CKata, &Q, &LP, WahanaBuilt);
                addressWahanaS P; addressWahanaD D;
                wahanaRusak(&P, &D);
            } else {
                printf("\033[0;31m");
                printf("Silahkan pergi ke sebelah antrian untuk menggunakan command ini \n\n");
                printf("\033[0m");
            }
        } else if (IsKataSama("office")){
            if(ElmtMatriks(Peta(CPeta), Y(Player), X(Player)) == 'O'){
                Inoffice();
            } else {
                printf("\033[0;31m");
                printf("Anda sedang tidak ada berada di dalam office\n");
                printf("\033[0m");
            }
        } else if (IsKataSama("repair")) {
            if (isSekitarPemain()) {
                addressWahanaD wahana = WahanaSekitar();
                Repair(&wahana);
            } else {
                printf("Tidak ada wahana di sekitarmu!");
            }
        }
        // nanti tambahin elif aja buat command yang lain 
        // else if (!(IsKataSama("prepare") || IsKataSama("exit"))) {
        //     printf("==========================================================\n");
        //     printf("Command tidak tersedia\n");
        //     printf("==========================================================\n");
        //     printf("Masukkan \"command\" untuk melihat daftar command yang ada\n");
        //     printf("==========================================================\n");
        // } 
        else if (!(IsKataSama("prepare") || IsKataSama("exit"))) {
            printf("\033[0;31m");
            printf("==========================================================\n");
            printf("Command tidak tersedia\n");
            printf("==========================================================\n");
            printf("Masukkan \"command\" untuk melihat daftar command yang ada\n");
            printf("==========================================================\n");
            printf("\033[0m");
            printf("\033[0;33m");
            printf("Masukkan perintah: ");
            printf("\033[0m");
            STARTKATA();
            invalid = true;
        } 
        
    } while(!(IsKataSama("prepare") || (IsKataSama("exit"))));
}