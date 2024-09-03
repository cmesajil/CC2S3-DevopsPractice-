¡Nuevo! Combinaciones de teclas … 
Las combinaciones de teclas de Drive se han actualizado para que puedas navegar escribiendo las primeras letras

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <climits>

using namespace std;

// arista
struct arista
{
    int datoDestino;
    int peso;
    arista *sgteArista;
};
typedef arista *parista;

// vertice
struct vertice
{
    int datoOrigen;
    arista *adyacente;
    vertice *sgteVertice;
};
typedef vertice *pvertice;

// grafo
class grafo
{
private:
    pvertice pGrafo;

public:
    grafo();
    ~grafo();
    void insertarVertice(int);
    void insertarArista(int, int, int);
    void imprimirGrafo();
    pvertice getpGrafo();
    pvertice getvertice(int);
    int nv();
};

pvertice grafo::getvertice(int v)
{
    pvertice p = pGrafo;
    while (p != NULL && v != p->datoOrigen)
    {
        p = p->sgteVertice;
    }
    return p;
}

int grafo::nv()
{
    pvertice p = pGrafo;
    int count = 0;
    while (p != NULL)
    {
        count++;
        p = p->sgteVertice;
    }
    return count;
}

pvertice grafo::getpGrafo()
{
    pvertice p = pGrafo;
    return p;
}
// Constructor

grafo::grafo()
{
    pGrafo = NULL;
};
// destructor

grafo::~grafo()
{
    pvertice p, rp;
    parista r, ra;
    p = pGrafo;
    while (p != NULL)
    {
        r = p->adyacente;
        while (r != NULL)
        {
            ra = r;
            r = r->sgteArista;
            delete ra;
        }
        rp = p;
        p = p->sgteVertice;
        delete rp;
    }
};
// insertar vertice

void grafo::insertarVertice(int x)
{
    pvertice p;
    p = new vertice;
    p->datoOrigen = x;
    p->adyacente = NULL;
    p->sgteVertice = pGrafo;
    pGrafo = p;
};

// insertar Arista

void grafo::insertarArista(int x, int y, int pesito)
{
    pvertice p = pGrafo;
    parista a;
    if (p != NULL)
    {
        while (p != NULL && p->datoOrigen != x)
        {
            p = p->sgteVertice;
        }
        if (p != NULL)
        {
            a = new arista;
            a->datoDestino = y;
            a->peso = pesito;
            a->sgteArista = p->adyacente;
            p->adyacente = a;
        }
    }
}
// imprimir

void grafo::imprimirGrafo()
{
    pvertice p;
    parista a;
    p = pGrafo;
    if (p == NULL)
    {
        cout << "Grafo vacio" << endl;
    }
    else
    {
        while (p != NULL)
        {
            cout << p->datoOrigen;
            a = p->adyacente;
            while (a != NULL)
            {
                cout << a->datoDestino;
                a = a->sgteArista;
            }
            cout << endl;
            p = p->sgteVertice;
        }
    }
}

vector<int> OrderAristList(grafo &g)
{
    vector<int> aristas;
    pvertice p = g.getpGrafo();
    parista a;
    while (p != NULL)
    {
        a = p->adyacente;
        while (a != NULL)
        {
            aristas.push_back(a->peso);
            a = a->sgteArista;
        }
        p = p->sgteVertice;
    }

    sort(aristas.begin(), aristas.end());
    return aristas;
}

int find(int parent[], int i)
{
    if (parent[i] == -1)
    {
        return i;
    }
    return find(parent, parent[i]);
}

void Union(int parent[], int x, int y)
{
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

struct Edge
{
    int src, dest, weight;
};

bool verificar(vector<int> &a)
{
    int suma = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        suma += a[i];
    }
    return suma;
}

void printExplore(const vector<int> &explore)
{
    std::cout <<"Conjunto T"<<endl;
    for (int i = 0; i < explore.size(); ++i)
    {
        if(explore[i]==0){
            std::cout << i << ", ";
        }
        
    }
    std::cout << std::endl;
}

void dijkstra2(grafo g)
{
    pvertice p = g.getpGrafo();
    int nv=g.nv();
    vector<vector<int>> distancia(nv, vector<int>(2, -1));
    vector<int> explore(nv, -1);
    if (p != NULL)
    {
        explore[p->datoOrigen] = 0;
        distancia[p->datoOrigen] = {0, p->datoOrigen};
        p = p->sgteVertice;
        while (p != NULL)
        {
            distancia[p->datoOrigen] = {INT_MAX, p->datoOrigen};
            p = p->sgteVertice;
        }
    }
    p = g.getpGrafo();
    parista a ;
    int menor = INT_MAX;
    int ind_menor= p->datoOrigen;

    while (verificar(explore))
    {
        menor=INT_MAX;
        for (int i = 0; i < explore.size(); ++i) {
            if(explore[i]!=0 && distancia[i][0]<menor){
                menor=distancia[i][0];
                ind_menor=i;
            }
        }
        p = g.getvertice(ind_menor);
        explore[p->datoOrigen] = 0;
        printExplore(explore);
        a= p->adyacente;
        
        while (a != NULL)
        {
            
            if ((a->peso + distancia[p->datoOrigen][0]) < distancia[a->datoDestino][0] && explore[a->datoDestino] != 0)
            {
                
                distancia[a->datoDestino][0] = a->peso+distancia[p->datoOrigen][0];
                distancia[a->datoDestino][1] = p->datoOrigen;
            }
            a = a->sgteArista;
        }
        
    std::cout <<"franja de T"<<endl;
    for (int i = 0; i < explore.size(); ++i) {
        if (explore[i] == -1 && distancia[i][0] != INT_MAX) {
            // Imprimir la fila i
            cout << "Camino al " << i << ": " << distancia[i][0] << " viene del nodo: " << distancia[i][1] << endl;
        }
    }

    
    if(!verificar(explore)){
        std::cout <<"-----------------------Arbol SPT-------------------------"<<endl;
        for (int i = 0; i < explore.size(); ++i) {
            // Imprimir la fila i
            cout << "Camino al " << i << ": " << distancia[i][0] << " viene del nodo: " << distancia[i][1] << endl;
        
    }

    }
    }
    

    printExplore(explore);

}

void helloWorld(grafo g)
{
    cout << "Hello, World!" << endl;
    g.imprimirGrafo();
}

int main()
{
    grafo miGrafo;

    // Insertar vértices y aristas
    miGrafo.insertarVertice(5);
    miGrafo.insertarVertice(4);
    miGrafo.insertarVertice(3);
    miGrafo.insertarVertice(2);
    miGrafo.insertarVertice(1);
    miGrafo.insertarVertice(0);
    
    miGrafo.insertarArista(0, 1, 41);
    miGrafo.insertarArista(0, 3, 45);
    miGrafo.insertarArista(0, 5, 29);
    miGrafo.insertarArista(1, 0, 41);
    miGrafo.insertarArista(1, 5, 24);
    miGrafo.insertarArista(1, 4, 32);
    miGrafo.insertarArista(1, 2, 51);
    miGrafo.insertarArista(2, 1, 51);
    miGrafo.insertarArista(2, 3, 50);
    miGrafo.insertarArista(2, 4, 32);
    miGrafo.insertarArista(3, 2, 50);
    miGrafo.insertarArista(3, 4, 36);
    miGrafo.insertarArista(3, 5, 38);
    miGrafo.insertarArista(3, 0, 45);
    miGrafo.insertarArista(4, 3, 36);
    miGrafo.insertarArista(4, 5, 21);
    miGrafo.insertarArista(4, 2, 32);
    miGrafo.insertarArista(4, 1, 32);
    miGrafo.insertarArista(5, 3, 38);
    miGrafo.insertarArista(5, 4, 21);
    miGrafo.insertarArista(5, 1, 24);
    miGrafo.insertarArista(5, 0, 29);

 
    

    // Imprimir el grafo
    cout << "Grafo--------------------------------------------------" << endl;
    miGrafo.imprimirGrafo();
    cout << "Grafo--------------------------------------------------" << endl;
    // helloWorld(miGrafo);
    dijkstra2(miGrafo);
    return 0;
}
