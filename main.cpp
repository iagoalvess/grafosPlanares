#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Ponto {
public:
  int grau, x, y;

  Ponto() : x(0), y(0), grau(0) {}
  Ponto(int _x, int _y) : x(_x), y(_y), grau(0) {}
  Ponto(int _x, int _y, int _grau) : x(_x), y(_y), grau(_grau) {}
};



class Grafo {
public:
  int numero_vertices, numero_arestas, numero_faces;

  vector<Ponto> vetor_vertices;
  vector<vector<int>> matriz_vizinhos;

  Grafo(int N, int M) : numero_vertices(N), numero_arestas(M) {
    matriz_vizinhos.resize(N);
    calcularNumeroFaces();
  }

  void calcularNumeroFaces() {
    numero_faces = numero_arestas - numero_vertices + 2;
  }
};



Ponto calcular_diferenca(const Ponto &a, const Ponto &b) {
  return Ponto(a.x - b.x, a.y - b.y);
}



int calcular_produto(const Ponto &difA, const Ponto &difB) {
  return difA.x * difB.y - difA.y * difB.x;
}



bool comparar_angulo(const Ponto &pontoA, const Ponto &pontoB, const Ponto &referencia) {
  Ponto difA = calcular_diferenca(pontoA, referencia);
  Ponto difB = calcular_diferenca(pontoB, referencia);

  if (difA.y < 0 || (difA.y == 0 && difA.x < 0)) {
    if (!(difB.y < 0 || (difB.y == 0 && difB.x < 0))) {
      return true;
    }
  } 
  else if (difB.y < 0 || (difB.y == 0 && difB.x < 0)) {
    return false;
  }

  int produtoVetorial = calcular_produto(difA, difB);
  return produtoVetorial > 0;
}



int determinarSinalProdutoVetorial(const Ponto &pontoA, const Ponto &pontoB, const Ponto &pontoC) {
  Ponto difA = calcular_diferenca(pontoA, pontoC);
  Ponto difB = calcular_diferenca(pontoB, pontoC);

  int produtoVetorial = calcular_produto(difA, difB);

  if (produtoVetorial > 0) {
    return 1;
  } 
  else if (produtoVetorial < 0) {
    return -1;
  }

  return 0;
}



vector<vector<bool>> inicializarMatrizVisitados(int n, const vector<vector<int>> &matriz_vizinhos, const vector<Ponto> &vetor_vertices) {
  vector<vector<bool>> matriz_visitados(n);

  for (int i = 0; i < n; i++) {
    matriz_visitados[i].resize(matriz_vizinhos[i].size());
    matriz_visitados[i].assign(matriz_vizinhos[i].size(), false);
  }

  return matriz_visitados;
}



vector<vector<int>> descobrirFacesGrafoPlanar(Grafo& grafo) {
  int numero_vertices = grafo.numero_vertices;
  vector<vector<bool>> matriz_visitados = inicializarMatrizVisitados(numero_vertices, grafo.matriz_vizinhos, grafo.vetor_vertices);

  for (int i = 0; i < numero_vertices; i++) {
    auto compare = [&](int l, int r) {
      return comparar_angulo(grafo.vetor_vertices[l], grafo.vetor_vertices[r], grafo.vetor_vertices[i]);
    };

    sort(grafo.matriz_vizinhos[i].begin(), grafo.matriz_vizinhos[i].end(), compare);
  }

  vector<vector<int>> matriz_faces;

  for (int indice_vertice = 0; indice_vertice < numero_vertices; indice_vertice++) {
    for (int indice_aresta = 0; indice_aresta < grafo.matriz_vizinhos[indice_vertice].size(); indice_aresta++) {
      if (matriz_visitados[indice_vertice][indice_aresta] == true) {
        continue;
      }

      vector<int> face;

      int vertice_atual = indice_vertice;
      int aresta_atual = indice_aresta;

      while (matriz_visitados[vertice_atual][aresta_atual] == false) {
        matriz_visitados[vertice_atual][aresta_atual] = true;
        face.push_back(vertice_atual);
        int vertice_vizinho = grafo.matriz_vizinhos[vertice_atual][aresta_atual];

        int proxima_aresta = -1;

        for (int i = 0; i < grafo.matriz_vizinhos[vertice_vizinho].size(); i++) {
          if (grafo.matriz_vizinhos[vertice_vizinho][i] == vertice_atual) {
            proxima_aresta = (i + 1) % grafo.matriz_vizinhos[vertice_vizinho].size();
            break;
          }
        }

        if (proxima_aresta == -1) {
          proxima_aresta = 0;
        }

        vertice_atual = vertice_vizinho;
        aresta_atual = proxima_aresta;
      }

      reverse(face.begin(), face.end());

      matriz_faces.emplace_back(face);
    }
  }
  return matriz_faces;
}



void imprimir_saida(const vector<vector<int>>& faces) {
  cout << faces.size() << endl;

  for (int i = 0; i < faces.size(); i++) {
    cout << faces[i].size() + 1 << " ";

    for (int j = 0; j < faces[i].size(); j++) {
      cout << faces[i][j] + 1 << " ";
    }
    cout << faces[i][0] + 1;
    cout << endl;
  }
}



int main() {
  int N, M;
  cin >> N >> M;

  Grafo grafo(N, M);

  for (int i = 0; i < N; i++) {
    float x, y;
    int grau;

    cin >> x >> y >> grau;
    
    Ponto aux(x, y, grau);

    grafo.vetor_vertices.push_back(aux);

    for (int j = 0; j < grau; j++) {
      int vizinho;
      cin >> vizinho;
      vizinho--;
      
      grafo.matriz_vizinhos[i].push_back(vizinho);
    }
  }

  vector<vector<int>> faces = descobrirFacesGrafoPlanar(grafo);
  imprimir_saida(faces);

  return 0;
}