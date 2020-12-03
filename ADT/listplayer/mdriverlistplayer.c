#include "listplayer.h"
#include "../listlinier/listlinier.h"
#include "../mesinkata/mesinkata.h"
#include "../prioqueue/prioqueue.h"

int main() {
    /* KAMUS */
    List L;
    listPlayer LP;
    infotypeQueue infoQ, del;
    PrioQueue Q;
    /* ALGORITMA */
    srand(time(NULL));
    CreateEmptyLP(&LP);
    CreateEmptyQueue(&Q, 10);

    STARTKATA();
    while(!IsKataSama("done") && !(IsFullQueue(Q))) {
        CreateEmptyList(&L);
        while (!IsKataSama("next")) {
            InsVLast(&L, CKata);
            printf("Next to enqueue. ");
            STARTKATA();        
            printf("\n");
        }
        InfoQueue(infoQ) = L;
        Prio(infoQ) = rand() % 4 + 1;
        Patience(infoQ) = rand() % 4 + 1;
        Enqueue(&Q, infoQ);
        STARTKATA();
        printf("Done to finish filling up queue. ");
        printf("\n");
    }
    
    infoLP info;
    STARTKATA();
    while (!IsKataSama('stop')) {
        if(!IsemptyLP(LP)) {
            ReduceTime(&LP);
            for(int i = 0; i < CountCompleted(LP); i++) {
                DelCompleted(&LP, &del);
                FirstEnqueue(&Q, del);
            }
        }
        Dequeue(&Q, &del);
        Remaining(info) = 5;
        RemainingPat(info) = Patience(del);
        PlayerInfo(info) = InfoQueue(del); 
        InsVLastLP(&LP, info);
        PrintPrioQueue(Q);
        printf("Stop to quit. ");
        STARTKATA();
        printf("\n");
    }
    
    return 0;
}