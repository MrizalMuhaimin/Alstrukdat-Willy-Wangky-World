#include "graph.h"
#include "../peta/peta.h"
#include <stdio.h>

// Buat ngetest graph berhasil dibikin apa engga
int main(){
    Graph G;
    loadPeta();
    CreateGraphPeta();
    PrintGraph(G);
    PrintPetaGraph(G);
}

// gcc drivergraph.c graph.c ../mesinkata/mesinkata.c ../mesinkar/mesinkar.c ../matriks/matriks.c ../peta/peta.c -o test