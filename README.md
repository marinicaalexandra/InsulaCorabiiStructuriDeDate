TASK 1: Pentru acest task, am avut nevoie sa citesc n noduri, m muchii si cele m relatii intre cate 2 noduri. In timp ce am
facut citire am construit graful neorientat cu ajutorul listelor de adiacenta, avand grija ca atunci cand mi se da muchie
intre nodurile a si b, sa o construiesc si intre nodurile b si a. Totodata, am pus costul corespunzator fiecarei muchii.
Pe prima linie in fisierul de iesire, trebuie sa afisez cate zone sunt despartite de apa, acestea reprezentand componentele
conexe ale grafului. Astfel, m-am folosit de o parcurgere DFS astfel: am initializat un vector de n noduri cu 0 (acest vector
se numeste vizitate) pe care l-am parcurs, si de fiecare data cand intalneam o valoare de 0(adica nodul nu a fost parcurs)
aplic DFS si astfel vizitez nodurile care fac parte din acea componenta conexa. Apoi, am implementat alogoritmul prim pentru
pentru a determina costul total al drumurilor care trebuie refacute.

TASK 2: Prima data am facut citirea datelor din fisierul de intrare. De data aceasta, graful a fost orientat. In plus, am avut
de citit si adancimea fiecarui nod pe care am pastrat-o intr-un vector numit vector_adncime. In paralel, am creeat si un 
vector in care am pastrat toate nodurile grafului, in ordinea in care au aparut in datele de citire. Avand aceste informatii,
m-am apucat sa implementez algoritmul Dijkstra(o data pentru a afla distanta minima de la insula la corabie si o data pentru
a afla distanta minima de la corabie la insula). Am facut acest lucru pentru a determina daca exista posibilitatea de a
transporta comoara la corabie. Apoi, am implementat o alta functie pentru reconstituirea drumului parcurs. De asemeneam, am
tinut cont de scorul fiecarei muchii pentru a vedea care este cel mai bun drum.