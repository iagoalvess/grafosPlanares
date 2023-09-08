#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Ponto {
public:
  double x, y;

  Ponto() : x(0.0), y(0.0) {}
  Ponto(double _x, double _y) : x(_x), y(_y) {}
};



class Grafo {
public:
  vector<Ponto> vertices;
  vector<vector<size_t>> matriz_adjacencia;

  Grafo(vector<Ponto> _vertices, vector<vector<size_t>> _matriz_adjacencia) : vertices(_vertices), matriz_adjacencia(_matriz_adjacencia) {}
};



// Distancia euclidiana de a para b
double Distancia(Ponto a, Ponto b) {
  double x = (a.x - b.x), y = (a.y - b.y);
  return sqrt(x*x + y*y);
}

// Coeficiente da reta que passa na origem e p
double Inclinacao(Ponto p) {
  return atan2(p.y, p.x);
}

// Coeficiente da reta orientada de p para q.
double InclinacaoRelativa(Ponto p, Ponto q) {
  return atan2(q.y - p.y, q.x - p.x);
}

// Determina se ao caminhar de a para b e depois de b para c estamos 
// fazendo uma curva a esquerda, a direita, ou seguindo em frente.
int TipoCurva(Ponto a, Ponto b, Ponto c) {
  double v = a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
  if (v < 0) return -1; // esquerda.
  if (v > 0) return +1; // direita.
  return 0; // em frente.
}

void lerEntrada(Grafo& grafo) {
  int n, m;
  cin >> n >> m;

  grafo = Grafo(n , m);

  for (int i = 0; i < grafo.num_vertices; i++) {
    double x, y;
    int grau;
    int vizinho;

    cin >> x >> y >> grau;
    grafo.vertices.push_back(Vertice(x, y, grau));

    for (int j = 0; j < grau; j++) {
      cin >> vizinho;
      grafo.vertices[i].vizinhos.push_back(vizinho);
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << "Vértice " << i + 1 << ": (" << grafo.vertices[i].p.x << ", " << grafo.vertices[i].p.y << "), Grau: " << grafo.vertices[i].grau << ", Vizinhos: ";

    for (int j = 0; j < grafo.vertices[i].grau; ++j) {
      cout << grafo.vertices[i].vizinhos[j] << " ";
    }
    cout << endl;
  }
}

void encontrarFaces(Grafo& grafo) {

// DFS DE ARESTAS



}
  
/*void imprimirArestas(const Grafo& grafo) {
  for (const Aresta& aresta : grafo.arestas) {
    cout << "Origem: " << aresta.origem << ", Destino: " << aresta.destino << ", Comprimento: " << aresta.comprimento << endl;
  }
}*/

int main() {
  Grafo grafo;

  lerEntrada(grafo);
  
  encontrarFaces(grafo);

  return 0;
}