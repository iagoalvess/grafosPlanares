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



int TipoCurva(const Ponto &p, const Ponto &q, const Ponto &r) {
  int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
  if (val < 0) {
    return -1; // ESQUERDA
  }
  if (val > 0) {
    return +1; // DIREITA
  }
  return 0;    // EM FRENTE
}

bool compareVertices(const Ponto& ponto1, const Ponto& ponto2, const Ponto& referencia) {
  double x1 = ponto1.x - referencia.x;
  double y1 = ponto1.y - referencia.y;

  double x2 = ponto2.x - referencia.x;
  double x2 = ponto2.y - referencia.y;

  int valor_orientacao = TipoCurva(referencia, ponto1, ponto2);
  if (valor_orientacao != 0) {
    return valor_orientacao > 0;
  }

  return x1 < x2 || (x1 == x2 && y1 < x2);
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