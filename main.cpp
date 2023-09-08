#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

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
    return -1;
  }
  if (val > 0) {
    return +1;
  }
  return 0;
}



bool compararVertices(const Ponto& ponto1, const Ponto& ponto2, const Ponto& referencia) {
  double x1 = ponto1.x - referencia.x;
  double y1 = ponto1.y - referencia.y;

  double x2 = ponto2.x - referencia.x;
  double y2 = ponto2.y - referencia.y;

  int valor_orientacao = TipoCurva(referencia, ponto1, ponto2);
  if (valor_orientacao != 0) {
    return valor_orientacao > 0;
  }

  return x1 < x2 || (x1 == x2 && y1 < y2);
}

vector<vector<size_t>> encontrarFaces(vector<Ponto> vertices, vector<vector<size_t>> matriz_adjacencia) {
  vector<vector<bool>> arestas_visitadas(vertices.size());

  for (size_t i = 0; i < vertices.size(); i++) {
    arestas_visitadas[i].resize(matriz_adjacencia[i].size(), false);
    sort(matriz_adjacencia[i].begin(), matriz_adjacencia[i].end(), [&](size_t l, size_t r) { 
      return compararVertices(vertices[l], vertices[r], vertices[i]); 
    });
  }

  vector<vector<size_t>> faces;
  for (size_t i = 0; i < vertices.size(); i++) {
    for (size_t j = 0; j < matriz_adjacencia[i].size(); j++) {
      if (arestas_visitadas[i][j] == true) {
        continue;
      }

      vector<size_t> face;
      size_t aux_1 = i;
      size_t aux_2 = j;

      while (arestas_visitadas[aux_1][aux_2] == false) {
        arestas_visitadas[aux_1][aux_2] = true;
        face.push_back(aux_1);

        size_t a = matriz_adjacencia[aux_1][aux_2];
        size_t b = std::lower_bound(matriz_adjacencia[a].begin(), matriz_adjacencia[a].end(), aux_1, [&](size_t l, size_t r) { 
          return compararVertices(vertices[l], vertices[r], vertices[a]); 
        }) - matriz_adjacencia[a].begin() + 1;

        if (b == matriz_adjacencia[a].size()) {
          b = 0;
        }

        aux_1 = a;
        aux_2 = b;
      }
      std::reverse(face.begin(), face.end());

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
  vector<vector<size_t>> matriz_adjacencia(N);

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



int main() {
  Grafo g = lerEntrada();

  vector<vector<size_t>> faces = encontrarFaces(g.vertices, g.matriz_adjacencia);

  for (size_t i = 0; i < faces.size(); i++)
  {
    cout << "Face " << i + 1 << ": ";
    for (size_t j = 0; j < faces[i].size(); j++)
    {
      cout << faces[i][j] + 1 << " ";
    }
    cout << endl;
  }

  return 0;
}