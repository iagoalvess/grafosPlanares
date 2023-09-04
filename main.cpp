#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Ponto {
public:
  double x, y;
};

class Vertice {
public:
  Ponto p;
  int grau;
  vector<int> vizinhos;
  double inclinacao;
};

class Grafo {
public:
  int num_vertices;
  int num_arestas;

  vector<Vertice> vertices;

  Grafo() {
    num_vertices = 0;
    num_arestas = 0;
  }

  Grafo(int v, int a) {
    num_vertices = v;
    num_arestas = a;
    vertices.resize(v);
  }
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
    cin >> grafo.vertices[i].p.x >> grafo.vertices[i].p.y >> grafo.vertices[i].grau;

    grafo.vertices[i].vizinhos.resize(grafo.vertices[i].grau);

    for (int j = 0; j < grafo.vertices[i].grau; j++) {
      cin >> grafo.vertices[i].vizinhos[j];
    }
  }
}

void OrdenaGrafo(vector<Vertice>& grafo) {

}

int main() {
  Grafo grafo;
  lerEntrada(grafo);
  //OrdenaGrafo(grafo);

  return 0;
}