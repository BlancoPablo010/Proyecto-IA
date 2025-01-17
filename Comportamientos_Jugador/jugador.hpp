#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

struct state {
  int fil;
  int col;
  Orientacion brujula;
};

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      current_state.fil = current_state.col = 99;
      current_state.brujula = norte;
      last_action = actIDLE;
      girar_derecha = false;
      bien_situado = false;
      girando = 0;
      ultimoGiro = 1;
      borde = 0;
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
  private:
  
  // Declarar aquí las variables de estado
  state current_state;
  Action last_action;
  bool girar_derecha;
  bool bien_situado;
  bool zapatillas;
  bool bikini;
  int girando;
  int ultimoGiro; // 0 = izquierda, 1 = derecha
  int borde;

};

#endif
