#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>

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
  vector<vector<int>> matriz_adjacencia;

  Grafo(vector<Ponto> _vertices, vector<vector<int>> _matriz_adjacencia) : vertices(_vertices), matriz_adjacencia(_matriz_adjacencia) {}
};



// Calcula a inclinação relativa entre dois pontos p e q
double inclinacaoRelativa(const Ponto& p, const Ponto& q) {
  return atan2(q.y - p.y, q.x - p.x);
}



// Compara dois vértices (ponto1 e ponto2) em relação a um ponto de referência
bool compararVertices(const Ponto& ponto1, const Ponto& ponto2, const Ponto& referencia) {
  double angulo1 = inclinacaoRelativa(ponto1, referencia);
  double angulo2 = inclinacaoRelativa(ponto2, referencia);

  if (angulo1 != angulo2) {
    return angulo1 < angulo2;
  }

  double dist1 = (ponto1.x - referencia.x) * (ponto1.x - referencia.x) + (ponto1.y - referencia.y) * (ponto1.y - referencia.y);
  double dist2 = (ponto2.x - referencia.x) * (ponto2.x - referencia.x) + (ponto2.y - referencia.y) * (ponto2.y - referencia.y);

  return dist1 < dist2;
}



// Função que encontra as faces do grafo usando busca em profundidade
vector<vector<int>> DFSparaEncontrarFaces(vector<Ponto> vertices, vector<vector<int>> matriz_adjacencia) {
  vector<vector<bool>> arestas_visitadas(vertices.size());

  for (int i = 0; i < vertices.size(); i++) {
    arestas_visitadas[i].resize(matriz_adjacencia[i].size(), false);
    sort(matriz_adjacencia[i].begin(), matriz_adjacencia[i].end(), [&](int l, int r) { 
      return compararVertices(vertices[l], vertices[r], vertices[i]); 
    });
  }

  vector<vector<int>> faces;
  for (int i = 0; i < vertices.size(); i++) {
    for (int j = 0; j < matriz_adjacencia[i].size(); j++) {
      if (arestas_visitadas[i][j] == true) {
        continue;
      }

      vector<int> face;
      int aux_1 = i;
      int aux_2 = j;

      while (arestas_visitadas[aux_1][aux_2] == false) {
        arestas_visitadas[aux_1][aux_2] = true;
        face.push_back(aux_1);

        int a = matriz_adjacencia[aux_1][aux_2];
        int b = lower_bound(matriz_adjacencia[a].begin(), matriz_adjacencia[a].end(), aux_1, [&](int l, int r) { 
          return compararVertices(vertices[l], vertices[r], vertices[a]); 
        }) - matriz_adjacencia[a].begin() + 1;

        if (b >= matriz_adjacencia[a].size()) {
          b = 0;
        }

        aux_1 = a;
        aux_2 = b;
      }
      reverse(face.begin(), face.end());

      face.push_back(face[0]);
      faces.emplace_back(face);
    }
  }

  return faces;
}



Grafo lerEntrada() {
  int N, M;
  cin >> N >> M;

  vector<Ponto> vertices(N);
  vector<vector<int>> matriz_adjacencia(N);

  for (int i = 0; i < N; i++) {
    double x, y;
    int d;
    cin >> x >> y >> d;

    assert(d > 0 && d <= N);

    vertices[i] = Ponto(x, y);
    for (int j = 0; j < d; j++) {
      int v;
      cin >> v;
      v--;
      assert(v >= 0 && v < N && v != i);
      matriz_adjacencia[i].push_back(v);
    }
  }

  return Grafo(vertices, matriz_adjacencia);
}



void imprimirSaida(const vector<vector<int>>& faces) {
  cout << faces.size() << endl;

  for (int i = 0; i < faces.size(); i++) {
    cout << faces[i].size() << " ";
    for (int j = 0; j < faces[i].size(); j++) {
      cout << faces[i][j] + 1 << " ";
    }
    cout << endl;
  }
}



int main() {
  Grafo grafo = lerEntrada();

  vector<vector<int>> faces = DFSparaEncontrarFaces(grafo.vertices, grafo.matriz_adjacencia);

  imprimirSaida(faces);

  return 0;
}