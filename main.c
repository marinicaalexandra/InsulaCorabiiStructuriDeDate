#include "functii.h"
#include <limits.h>
#include <string.h>

int main(int argc, char *argv[])
{
    TGL *graf;
    if(atoi(argv[1]) == 1)
    {
        graf = CitGraf();
        int* vizitat = (int*)calloc(graf->n + 1, sizeof(int));  /* inițializează vectorul de vizitate cu 0 */
        if (!vizitat)
        {
            printf("Malloc error");
            return 0;
        }
        int numarComponente = 0;

        int nod =1;
        while(nod <= graf->n) 
        {
            if(!vizitat[nod])
                {
                    DFS(nod, vizitat, graf);  /* apelează DFS pentru fiecare nod nevizitat */
                    numarComponente++;
                }
                nod++;
        }
    
        free(vizitat);  /* eliberează memoria alocată pentru vectorul de vizitate */
    
        FILE *fout = fopen("tema3.out", "w");
        fprintf(fout, "%d\n", numarComponente);

        int V[100] = {0};
        Prim_comp_conexe(graf, V, fout);
        DistrG(&graf);
        fclose(fout);
    }
    else 
    {
        int indice_insula, indice_corabie, greutate_comoara, vector_adancime[1000];
        char noduri[1000][1000];
        graf = CitGraf2(&indice_insula, &indice_corabie, &greutate_comoara, noduri, vector_adancime);

        FILE *fout = fopen("tema3.out", "w");
        int d_insula_corabie, d_corabie_insula, adancime_min;
        d_insula_corabie = Dijstra_insula_corabie(graf, indice_insula, indice_corabie, vector_adancime);
        d_corabie_insula = Dijstra_corabie_insula(graf, indice_insula, indice_corabie, vector_adancime);
        if(d_corabie_insula != INT_MAX && d_insula_corabie != INT_MAX && d_insula_corabie>0 && d_corabie_insula>0)
        {
            adancime_min = Dijstra_reconstruire_drum(graf, indice_insula, indice_corabie, noduri, vector_adancime, fout);
            fprintf(fout, "%d\n", adancime_min);
            if(adancime_min)
                fprintf(fout, "%d\n", greutate_comoara/adancime_min);
        }
        else
        if(d_corabie_insula == INT_MAX)
            fprintf(fout, "Echipajul nu poate ajunge la insula\n");
        else
            fprintf(fout, "Echipajul nu poate transporta comoara inapoi la corabie\n");
        DistrG(&graf);
        fclose(fout);
        }
}