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

void lerEntrada(vector<Vertice>& grafo) {
  int n, m;
  cin >> n >> m;
  grafo.resize(n);

  for (int i = 0; i < n; i++) {
    cin >> grafo[i].p.x >> grafo[i].p.y >> grafo[i].grau;
    grafo[i].vizinhos.resize(grafo[i].grau);

    for (int j = 0; j < grafo[i].grau; j++) {
      cin >> grafo[i].vizinhos[j];
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << "Vértice " << i + 1 << ": (" << grafo[i].p.x << ", " << grafo[i].p.y << "), Grau: " << grafo[i].grau << ", Vizinhos: ";

    for (int j = 0; j < grafo[i].grau; ++j) {
      cout << grafo[i].vizinhos[j] << " ";
    }
    cout << endl;
  }
}

// Dist^ancia euclidiana de a para b
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

// Função de comparação para ordenar os vértices com base na inclinação relativa.
bool CompararInclinacaoRelativa(const Vertice& a, const Vertice& b) {
    return a.inclinacao < b.inclinacao;
}

void OrdenaGrafo(vector<Vertice>& grafo) {
  // Calcular as inclinações relativas para cada vértice.
  for (Vertice &v : grafo) {
    for (int vizinho : v.vizinhos) {
      v.inclinacao = InclinacaoRelativa(v.p, grafo[vizinho].p);
    }
  }

  // Ordenar os vértices com base na inclinação relativa.
  std::sort(grafo.begin(), grafo.end(), CompararInclinacaoRelativa);

  // Exibir os vértices ordenados.
  std::cout << "Vértices ordenados por inclinação relativa:" << std::endl;
  for (const Vertice &v : grafo) {
    std::cout << "(" << v.p.x << ", " << v.p.y << "), Grau: " << v.grau << std::endl;
  }
}

int main() {
  vector<Vertice> grafo;
  lerEntrada(grafo);
  OrdenaGrafo(grafo);

  return 0;
}