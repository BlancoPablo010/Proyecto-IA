#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;

void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st, vector<vector<unsigned char>> &matriz) {
	matriz[st.fil][st.col] = terreno[0];
	int i = 0;
	switch (st.brujula) {
		case norte:
			while(i < 16) {
				if(i == 0) {
					matriz[st.fil][st.col] = terreno[0];
					i++;
				}
				else if(i >=1 && i <= 3) {
					for(int col=-1;col<2;col++) {
						matriz[st.fil-1][st.col+col] = terreno[i];
						i++;
					}
				}
				else if(i >=4 && i <= 8) {
					for(int col=-2;col<3;col++) {
						matriz[st.fil-2][st.col+col] = terreno[i];
						i++;
					}
				}
				else {
					for(int col=-3;col<4;col++) {
						matriz[st.fil-3][st.col+col] = terreno[i];
						i++;
					}
				}
			}
			break;
 		case noreste:
		    matriz[st.fil-1][st.col+1] = terreno[2];
			break;
		case este:
		    matriz[st.fil][st.col+1] = terreno[2];
			break;
		case sureste:
			matriz[st.fil+1][st.col+1] = terreno[2];
			break;
		case sur:
		    matriz[st.fil+1][st.col] = terreno[2];
			break;
		case suroeste:
		    matriz[st.fil+1][st.col-1] = terreno[2];
			break;
		case oeste:
		    matriz[st.fil][st.col-1] = terreno[2];
			break;
		case noroeste:
		    matriz[st.fil-1][st.col-1] = terreno[2];
			break;
	}
}



Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;
	int a;

	//Hecho en clase
	/*
	if (sensores.nivel == 0) {
		mapaResultado[sensores.posF][sensores.posC] = sensores.terreno[0];
		switch (sensores.sentido) { 
		case oeste:
			mapaResultado[sensores.posF+1][sensores.posC-1] = sensores.terreno[1];
			break;

		case norte:
		    mapaResultado[sensores.posF-1][sensores.posC-1] = sensores.terreno[1];
			break;
		
		}
	}

	if (sensores.terreno[2] != 'P') accion = actFORWARD;
	else accion = actTURN_SR;
	*/
	//Tarea 1
	
	switch (last_action) {
		case actFORWARD: 
			switch (current_state.brujula) {
				case norte:		current_state.fil--; break;
				case noreste:	current_state.fil--; current_state.col++;
				case este:		current_state.col++; break;
				case sureste:	current_state.fil++; current_state.col++; break;
				case sur: 		current_state.fil++; break;
				case suroeste:	current_state.fil++; current_state.col--; break;
				case oeste:     current_state.col--; break;
				case noroeste:  current_state.fil--; current_state.col--; break;
			}
			break;
		case actTURN_SL:
			a = current_state.brujula;
			a = (a+7)%8;
			current_state.brujula = static_cast<Orientacion>(a);
			break;
		case actTURN_SR:
		    a = current_state.brujula;
			a = (a+1)%8;
			current_state.brujula = static_cast<Orientacion>(a);
			break;
		case actTURN_BL:
			a = current_state.brujula;
			a = (a+5)%8;
			current_state.brujula = static_cast<Orientacion>(a);
			break;
		case actTURN_BR:
		    a = current_state.brujula;
			a = (a+3)%8;
			current_state.brujula = static_cast<Orientacion>(a);
			break;
	}
	
	if(sensores.nivel == 0) {
		if (borde%2 == 0 and girando == 0 and sensores.terreno[2] == 'P') {
			accion = actTURN_SL;
			girando++;
		}	
		else if (borde%2 == 1 and girando == 0 and sensores.terreno[2] == 'P') {
            accion = actTURN_SR;
            girando++;
        }
	}
    else if(sensores.nivel == 1) {
		if (sensores.terreno[0] == 'G' and !bien_situado) {
			current_state.fil = sensores.posF;
			current_state.col = sensores.posC;
			current_state.brujula = sensores.sentido;
			bien_situado = true;
		}
		
		if (bien_situado) {
			PonerTerrenoEnMatriz(sensores.terreno, current_state, mapaResultado);
		}

		
		//Decidir la nueva acción

		if(!bien_situado) {
			/*
			if ((sensores.terreno[2] == 'T' or sensores.terreno[2] == 'S' or
				sensores.terreno[2] == 'G' ) and sensores.superficie[2] == '_') {
				cout << "Avanzar\n";
				accion = actFORWARD;

			}
			else if (girando < 4 ) {
				if ((sensores.terreno[1] == 'T' or sensores.terreno[1] == 'S' or
					sensores.terreno[1] == 'G') and sensores.superficie[1] == '_') {
					accion = actTURN_SL;
					girando=0;
					ultimoGiro = 0;
					cout << "Puede avanzar izquierda\n";
					
				}
				else if ((sensores.terreno[3] == 'T' or sensores.terreno[3] == 'S' or
					sensores.terreno[3] == 'G') and sensores.superficie[3] == '_') {
					accion = actTURN_SR;
					girando = 0;
					ultimoGiro = 1;
					cout << "Puede avanzar derecha\n";
				}
				if (girando >= 0 and girando <= 3) {
					if (ultimoGiro == 0) {
						accion = actTURN_SL;
						girando++;
						cout << "Giro izquierda\n";
					}
					else {
						accion = actTURN_SR;
						girando++;
						cout << "Giro derecha\n";
					}
				}
			}
			else if (girando == 3 and ultimoGiro == 0) {
				accion = actTURN_BR;
				girando = 0;
				ultimoGiro = 1;
				cout << "Giro grande derecha\n";
			}
			else if (girando == 3 and ultimoGiro == 1) {
				accion = actTURN_BL;
				girando = 0;
				ultimoGiro = 0;
				cout << "Giro grande izquierda\n";
			}
			else {
				accion = actTURN_BL;
				cout << "Por defecto, giro grande derecha\n";
			}
			*/



			if (borde%2 == 0 and girando == 0 and sensores.terreno[2] == 'P') {
				girando++;
				accion = actTURN_SL;
			}
			else if (borde%2 == 0 and girando == 1 and sensores.terreno[2] == 'P') {
				borde++;
				girando = 0;
				accion = actTURN_SL;
			}
			else if (borde%2 == 1 and girando == 0 and sensores.terreno[2] == 'P') {
				girando++;
				accion = actTURN_SR;
			}
			else if (borde%2 == 1 and girando == 1 and sensores.terreno[2] == 'P') {
				girando = 0;
				accion = actTURN_SR;
			}
			else {
				accion = actFORWARD;
			}
			
		}
		else {
			switch (current_state.brujula) {
				case norte: 
					if (mapaResultado[current_state.fil-1][current_state.col+1] == '?') {
						accion = actTURN_SR;
					}
					break;
				case noreste:
					if (mapaResultado[current_state.fil][current_state.col+1] == '?' ){
						accion = actTURN_SR;
					}
					break;
				case este:
					if (mapaResultado[current_state.fil+1][current_state.col+1] == '?' ){
						accion = actTURN_SR;
					}
					break;
				case sureste:
					if (mapaResultado[current_state.fil+1][current_state.col] == '?' ){
						accion = actTURN_SR;
					}
					break;
				case sur:
					if (mapaResultado[current_state.fil+1][current_state.col-1] == '?' ){
						accion = actTURN_SR;
					}
					break;
				case suroeste:
					if (mapaResultado[current_state.fil][current_state.col-1] == '?' ){
						accion = actTURN_SR;
					}
					break;
				case oeste:
					if (mapaResultado[current_state.fil-1][current_state.col-1] == '?' ){
						accion = actTURN_SR;
					}
					break;
				case noroeste:
					if (mapaResultado[current_state.fil-1][current_state.col] == '?' ){
						accion = actTURN_SR;
					}
					break;
			}

			borde = 0;

			switch (current_state.brujula) {
				case noreste:
					accion = actTURN_SL;
				case sureste:
					accion = actTURN_SR;
				case suroeste:
					accion = actTURN_SL;
				case noroeste:
					accion = actTURN_SR;
			}

			if (borde%2 == 0  and girando == 0 and sensores.terreno[2] == 'P') {
				accion = actTURN_SL;
				girando++;
			}
			else if(borde%2 == 1 and girando == 0 and sensores.terreno[2] == 'P') {
				accion = actTURN_SR;
				girando++;
			}
			else if (borde%2 == 0 and girando == 1 and sensores.terreno[2] == 'P') {
				borde++;
				girando = 0;
				accion = actTURN_SL;
			}
			else if(borde%2 == 1 and girando == 1 and sensores.terreno[2] == 'P') {
				borde++;
				girando = 0;
				accion = actTURN_SR;
			}
			else {
				accion = actFORWARD;
			}
			
		}
	}
	// Determinar el efecto de la ultima accion enviada
	last_action = accion;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
