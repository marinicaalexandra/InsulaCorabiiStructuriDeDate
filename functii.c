#include "functii.h"
#include <string.h>
#include <limits.h>

TGL *AlocG(int nr) /* aloca spatiu pentru descriptor graf si vector de (n+1) adrese liste arce */
{
  TGL *g = (TGL *)malloc(sizeof(TGL)); /* spatiu descriptor */
  if (!g)
    return NULL;
  g->x = (AArc *)calloc((nr + 1), sizeof(AArc)); /* spatiu vector adr.liste arce */
  if (!g->x)
  {
    free(g);
    return NULL;
  }
  g->n = nr;
  return g;
}

void DistrG(TGL **ag)
{
  int i;
  AArc p, aux;
  for (i = 0; i <= (*ag)->n; i++)
  {
    p = (*ag)->x[i];
    while (p)
    {
      aux = p;
      p = p->urm;
      free(aux);
    }
  }
  free((*ag)->x);
  free(*ag);
  *ag = NULL;
}

// functie care citeste un graf neorientat
TGL *CitGraf()
{
  FILE *f;
  TGL *g = NULL;
  int s, d, contor = 0, x;
  AArc *p, aux;
  int n, m, cost;
  char **vizitate, inceput[50], sfarsit[50];

  f = fopen("tema3.in", "rt");
  if (!f)
    return NULL;
  fscanf(f, "%i", &n);
  fscanf(f, "%i", &m);

  vizitate = (char **)malloc((n + 1) * sizeof(char *));
  if (vizitate == NULL)
    return 0;
  for (int i = 0; i < n + 1; i++)
    vizitate[i] = (char *)malloc((50) * sizeof(char));

  g = AlocG(n);
  if (!g)
    return 0;
  while (fscanf(f, "%s%s%i", inceput, sfarsit, &x) == 3)
  {
    // printf("%s %s %i\n", inceput, sfarsit, x);
    s = -1;
    d = -1;
    for (int i = 1; i <= contor; i++)
    {
      if (strcmp(vizitate[i], inceput) == 0)
        s = i;
      if (strcmp(vizitate[i], sfarsit) == 0)
        d = i;
    }
    if (s == -1)
    {
      contor++;
      strcpy(vizitate[contor], inceput);
      s = contor;
    }
    if (d == -1)
    {
      contor++;
      strcpy(vizitate[contor], sfarsit);
      d = contor;
    }
    // printf("%d %d %d\n", s, d, x);
    p = g->x + s;
    while (*p && (*p)->d < d)
      p = &(*p)->urm;
    aux = (TCelArc *)calloc(sizeof(TCelArc), 1);
    if (!aux)
    {
      DistrG(&g);
      return NULL;
    }
    aux->urm = *p;
    *p = aux;
    aux->d = d;
    aux->c = x;

    p = g->x + d;
    while (*p && (*p)->d < s)
      p = &(*p)->urm;
    aux = (TCelArc *)calloc(sizeof(TCelArc), 1);
    if (!aux)
    {
      DistrG(&g);
      return NULL;
    }
    aux->urm = *p;
    *p = aux;
    aux->d = s;
    aux->c = x;
  }
  for (int i = 0; i < n + 1; i++)
  {
    free(vizitate[i]);
  }
  free(vizitate);
  fclose(f);
  return g;
}

void AfiGrafL(TGL *g)
{
  AArc l;
  int i;
  if (g == NULL)
  {
    printf("da\n");
    return;
  }
  for (i = 1; i <= g->n; i++)
  {
    l = g->x[i];
    if (!l)
      printf("%d: - \n", i);
    else
      printf("%d: ", i);
    for (; l != NULL; l = l->urm)
      printf(" %d (%d)", l->d, l->c);
    printf("\n");
  }
}

int DFS(int nod, int *vizitat, TGL *graf)
{
  vizitat[nod] = 1; /* marchează nodul ca vizitat */

  AArc arc = graf->x[nod];
  while (arc != NULL)
  {
    int vecin = arc->d;
    if (vizitat[vecin] == 0)
    {
      int x = DFS(vecin, vizitat, graf); /* parcurge recursiv vecinii nevizitați */
    }
    arc = arc->urm;
  }
  return 1;
}

void Prim_comp_conexe(TGL *graf, int V[100], FILE *fout)
{
  int contor = 0;
  for (int nod = 1; nod < graf->n; nod++)
  {
    if (V[nod] == 0)
    {
      DFS(nod, V, graf); /* apelează DFS pentru fiecare nod nevizitat */
      int suma = Prim(graf, nod);
      contor++;
      V[contor] = suma;
    }
  }
  for (int i = 1; i <= contor - 1; i++)
    for (int j = i + 1; j <= contor; j++)
      if (V[i] > V[j])
      {
        int aux = V[i];
        V[i] = V[j];
        V[j] = aux;
      }
  for (int i = 1; i <= contor; i++)
    fprintf(fout, "%d\n", V[i]);
}

int Prim(TGL *g, int nod)
{
  int suma = 0;
  int *visited = calloc(g->n + 1, sizeof(int));

  if (!visited)
  {
    printf("Malloc error");
    return 0;
  }

  visited[nod] = 1;

  while (1)
  {
    int min = 10000;
    int x = -1, y = -1;

    for (int i = 1; i <= g->n; i++)
    {
      if (visited[i])
      {
        AArc p = g->x[i];

        while (p)
        {
          if (visited[p->d] == 0 && min > p->c)
          {
            x = i;
            y = p->d;
            min = p->c;
          }
          p = p->urm;
        }
      }
    }

    if (x == -1 || y == -1)
      break;

    suma += min;
    visited[y] = 1;
  }

  free(visited);
  return suma;
}

// functie care citeste un graf orientat
TGL *CitGraf2(int *indice_insula, int *indice_corabie, int *greutate_comoara, char vizitate[1000][1000], int vector_adancime[1000])
{
  FILE *f;
  TGL *g = NULL;
  int s, d, contor = 0, x;
  AArc *p, aux;
  int n, m, cost;
  // char **vizitate;
  char inceput[50], sfarsit[50];

  f = fopen("tema3.in", "rt");
  if (!f)
    return NULL;
  fscanf(f, "%i", &n); // citesc numarul de noduri
  fscanf(f, "%i", &m); // citesc numarul de muchii

  // vizitate = (char **)malloc((n + 1) * sizeof(char *));
  // if (vizitate == NULL)
  //   return 0;
  // for (int i = 0; i < n + 1; i++)
  //   vizitate[i] = (char *)malloc((50) * sizeof(char));

  // vector_adancime = (int *)malloc((n+1) * sizeof(int));

  g = AlocG(n);
  if (!g)
    return 0;
  // while (fscanf(f, "%s%s%i", inceput, sfarsit, &x) == 3)
  for (int indice = 1; indice <= m; indice++)
  {
    fscanf(f, "%s%s%i", inceput, sfarsit, &x);
    // printf("%s %s %i\n", inceput, sfarsit, x);
    s = -1;
    d = -1;
    for (int i = 1; i <= contor; i++)
    {
      if (strcmp(vizitate[i], inceput) == 0)
        s = i;
      if (strcmp(vizitate[i], sfarsit) == 0)
        d = i;
    }
    if (s == -1)
    {
      contor++;
      strcpy(vizitate[contor], inceput);
      s = contor;
    }
    if (d == -1)
    {
      contor++;
      strcpy(vizitate[contor], sfarsit);
      d = contor;
    }
    if (strcmp(inceput, "Insula") == 0)
      *indice_insula = s;
    if (strcmp(inceput, "Corabie") == 0)
      *indice_corabie = s;
    if (strcmp(sfarsit, "Insula") == 0)
      *indice_insula = d;
    if (strcmp(sfarsit, "Corabie") == 0)
      *indice_corabie = d;
    // printf("%d %d %d\n", s, d, x);
    p = g->x + s;
    while (*p && (*p)->d < d)
      p = &(*p)->urm;
    aux = (TCelArc *)calloc(sizeof(TCelArc), 1);
    if (!aux)
    {
      DistrG(&g);
      return NULL;
    }
    aux->urm = *p;
    *p = aux;
    aux->d = d;
    aux->c = x;
  }
  char string[50];
  int valoare;
  for (int indice = 1; indice <= n; indice++)
  {
    fscanf(f, "%s%d", string, &valoare);
    for (int i = 1; i <= n; i++)
      if (strcmp(vizitate[i], string) == 0)
      {
        vector_adancime[i] = valoare;
      }
  }
  fscanf(f, "%d", &valoare);
  *greutate_comoara = valoare;

  fclose(f);
  return g;
}

int Dijstra_insula_corabie(TGL *g, int indice_insula, int indice_corabie, int vector_adancime[1000])
{
  int rezultat[1000] = {0};
  int nod_curent = 1;
  int *visited = calloc(g->n + 1, sizeof(int));
  if (!visited)
  {
    printf("Malloc error");
    return 0;
  }

  float *dist = calloc(g->n + 1, sizeof(float));
  if (!dist)
  {
    free(visited);
    printf("Malloc error");
    return 0;
  }

  for (int i = 1; i <= g->n; i++)
    dist[i] = INT_MAX;

  dist[indice_insula] = 0;
  rezultat[indice_insula] = 0;
  for (int i = 1; i <= g->n; i++)
  {
    int min = INT_MAX;

    for (int j = 1; j <= g->n; j++)
    {
      if (!visited[j] && dist[j] < min)
      {
        min = dist[j];
        nod_curent = j;
      }
    }
    visited[nod_curent] = 1;
    AArc p = g->x[nod_curent];

    while (p)
    {
      if (!visited[p->d] && dist[p->d] > dist[nod_curent] + (1.0 * p->c / vector_adancime[p->d]))
      {
        dist[p->d] = dist[nod_curent] + (1.0 * p->c / vector_adancime[p->d]);
        rezultat[p->d] = rezultat[nod_curent] + p->c;
      }
      p = p->urm;
    }
  }

  for (int i = 1; i <= g->n; i++)
  {
    if (indice_corabie == i)
    {
      int x = rezultat[i];
      free(dist);
      free(visited);
      return x;
    }
  }

  free(dist);
  free(visited);
}

int Dijstra_corabie_insula(TGL *g, int indice_insula, int indice_corabie, int vector_adancime[1000])
{
  int nod_curent = 1;
  int *visited = calloc(g->n + 1, sizeof(int));
  if (!visited)
  {
    printf("Malloc error");
    return 0;
  }

  int *dist = calloc(g->n + 1, sizeof(int));
  if (!dist)
  {
    free(visited);
    printf("Malloc error");
    return 0;
  }

  for (int i = 1; i <= g->n; i++)
    dist[i] = INT_MAX;

  dist[indice_corabie] = 0;
  for (int i = 1; i <= g->n; i++)
  {
    int min = INT_MAX;

    for (int j = 1; j <= g->n; j++)
    {
      if (!visited[j] && dist[j] < min)
      {
        min = dist[j];
        nod_curent = j;
      }
    }
    visited[nod_curent] = 1;
    AArc p = g->x[nod_curent];

    while (p)
    {
      if (!visited[p->d] && dist[p->d] > dist[nod_curent] + p->c)
      {
        dist[p->d] = dist[nod_curent] + p->c;
      }
      p = p->urm;
    }
  }

  for (int i = 1; i <= g->n; i++)
  {
    if (indice_insula == i)
    {
      int x = dist[i];
      free(dist);
      free(visited);
      return x;
    }
  }

  free(dist);
  free(visited);
}

int Dijstra_reconstruire_drum(TGL *g, int indice_insula, int indice_corabie, char noduri[1000][1000], int vector_adancime[1000], FILE *fout)
{
  int rezultat[1000] = {0};
  int nod_curent = 1;
  int *visited = calloc(g->n + 1, sizeof(int));
  if (!visited)
  {
    printf("Malloc error");
    return 0;
  }

  float *dist = calloc(g->n + 1, sizeof(float));
  if (!dist)
  {
    free(visited);
    printf("Malloc error");
    return 0;
  }

  int *predecesor = calloc(g->n + 1, sizeof(int));
  if (!predecesor)
  {
    free(dist);
    free(visited);
    printf("Malloc error");
    return 0;
  }
  for (int i = 1; i <= g->n; i++)
  {
    dist[i] = INT_MAX;
  }

  dist[indice_insula] = 0;
  rezultat[indice_insula] = 0;
  for (int i = 1; i <= g->n; i++)
  {
    int min = INT_MAX;

    for (int j = 1; j <= g->n; j++)
    {
      if (!visited[j] && dist[j] < min)
      {
        min = dist[j];
        nod_curent = j;
      }
    }
    visited[nod_curent] = 1;
    AArc p = g->x[nod_curent];
    while (p)
    {
      if (!visited[p->d] && dist[p->d] > dist[nod_curent] + (1.0 * p->c / vector_adancime[p->d]))
      {
        dist[p->d] = dist[nod_curent] + (1.0 * p->c / vector_adancime[p->d]);
        predecesor[p->d] = nod_curent;
        rezultat[p->d] = rezultat[nod_curent] + p->c;
      }
      p = p->urm;
    }
  }

  int indice_aux = 0, drum_parcurs[1000], adancime_min = INT_MAX;
  // printf("Drumul de cost minim de la nodul %d la nodul %d: ", indice_insula, indice_corabie);
  int nod = indice_corabie;
  while (nod != indice_insula)
  {
    // printf("%d ", nod);
    indice_aux++;
    if (indice_aux >= g->n)
    {
      free(predecesor);
      free(dist);
      free(visited);
      return 0;
    }
    drum_parcurs[indice_aux] = nod;
    nod = predecesor[nod];
  }
  indice_aux++;
  drum_parcurs[indice_aux] = indice_insula;
  // printf("%d\n", indice_insula);

  if (rezultat[indice_corabie] == 0)
  {
    free(predecesor);
    free(dist);
    free(visited);
    return 0;
  }

  for (int k = indice_aux; k >= 1; k--)
  {
    // printf("%s ", noduri[drum_parcurs[k]]);
    fprintf(fout, "%s ", noduri[drum_parcurs[k]]);
    if (k != indice_aux && k != 1 && vector_adancime[drum_parcurs[k]] < adancime_min)
      adancime_min = vector_adancime[drum_parcurs[k]];
  }
  fprintf(fout, "\n%d\n", rezultat[indice_corabie]);

  free(predecesor);
  free(dist);
  free(visited);
  return adancime_min;
}
