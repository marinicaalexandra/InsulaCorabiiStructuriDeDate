#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct celarc
{ int adancime;    /*pt taskul 2*/
  int d;           /* destinatie arc */
  int c;            /* cost arc */
  struct celarc *urm; /* adresa urmatorul adiacent */
} TCelArc, *AArc;

typedef struct 
{ int n;     /* numar noduri */
  AArc* x;    /* vector adrese liste arce */
} TGL;

TGL* AlocG(int nr);
void DistrG(TGL** ag);
TGL *CitGraf();
void AfiGrafL(TGL * g);
int DFS(int nod, int* vizitat, TGL* graf);
int NumarComponenteConexe(TGL* graf);
//int Prim(TGL *g, int suma, int nod);
int Prim(TGL *g, int nod);
void comp_conexe(TGL* graf);
void Prim_comp_conexe(TGL* graf, int V[100], FILE *fout);

TGL *CitGraf2(int *indice_insula, int *indice_corabie, int *greutate_comoara, char vizitate[1000][1000], int vector_adancime[1000]);
int Dijstra_insula_corabie(TGL *g, int indice_insula, int indice_corabie, int vector_adancime[1000]);
int Dijstra_corabie_insula(TGL *g, int indice_insula, int indice_corabie, int vector_adancime[1000]);
int Dijstra_reconstruire_drum(TGL* g, int indice_insula, int indice_corabie, char noduri[1000][1000], int vector_adancime[1000], FILE *fout);


int Dijstra_insula_corabie_scor(TGL *g, int indice_insula, int indice_corabie, int vector_adancime[1000]);