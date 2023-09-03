#include "math.h"

class Ponto {
public:
  double x, y;
};

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