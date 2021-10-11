//
// Created by Dorian on 21/09/2021.
//

#ifndef BUSQUEDAENPROFUNDIDAD_8_PUZZLE_ARBOL_H
#define BUSQUEDAENPROFUNDIDAD_8_PUZZLE_ARBOL_H
#include "string"
#include "vector"
#include <iostream>

using namespace std;


class Nodo {
private:
    Nodo* padre = nullptr;
    Nodo* hermano = nullptr;
    Nodo* primerHijo = nullptr;
    string cadena;
    int profundidad;
    bool estaEstancado = false;
public:
    Nodo() {}

    Nodo(string cadena) {
        this->cadena = cadena;
    }

    Nodo(string cadena, Nodo* padre, int profundidad) {
        this->cadena = cadena;
        this->padre = padre;
        this->profundidad = profundidad;
    }

    Nodo* getPadre() {
        return padre;
    }

    string getCadena() {
        return cadena;
    }

    void setProfundidad(int profundidad){
        this->profundidad = profundidad;
    }

    int getProfundidad(){
        return this->profundidad;
    }

    bool getEstaEstancado () {
        return this->estaEstancado;
    }
    void setEstaEstancado (bool estaEstancado) {
        this->estaEstancado = estaEstancado;
    }

    void setHermano(Nodo* hermano) {
        this->hermano = hermano;
    }

    Nodo* getHermano() {
        return this->hermano;
    }

    Nodo* getPrimerHijo() const {
        return primerHijo;
    }

    void setPrimerHijo(Nodo* primerHijo) {
        this->primerHijo = primerHijo;
    }

    void print() {
        cout << "Cadena:" << this->getCadena() << " - Padre:" << this->padre->getCadena() << endl;
    }

};

class Arbol {
private:
    int findZero(string cadena){
        for (int i=0 ; i < cadena.length(); i++) {
            if (cadena[i] == '0')
                return i;
        }
        return -1;
    }

    string cambiarCaracteres (string cadena, int posicion1, int posicion2) {
        char caracter1 = cadena[posicion1];
        char caracter2 = cadena[posicion2];
        cadena[posicion1] = caracter2;
        cadena[posicion2] = caracter1;

        return cadena;
    }


    vector<string> getMovimientosPosibles(string cadena) {
        int posicionDeCero = findZero(cadena);
        vector<string> arregloDePosiblesResultados;
        switch(posicionDeCero){
            case 0:
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,0,1));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,0,3));
                break;
            case 1:
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,1,0));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,1,2));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,1,4));
                break;
            case 2:
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,2,1));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,2,5));
                break;
            case 3:
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,3,0));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,3,4));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,3,6));
                break;
            case 4:
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,4,1));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,4,3));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,4,5));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,4,7));
                break;
            case 5:
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,5,2));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,5,4));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,5,8));
                break;
            case 6:
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,6,3));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,6,7));
                break;
            case 7:
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,7,4));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,7,6));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,7,8));
                break;
            case 8:
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,8,5));
                arregloDePosiblesResultados.push_back(cambiarCaracteres(cadena,8,7));
                break;
        }
        return arregloDePosiblesResultados;
    }

    vector<string> getPath(Nodo* resultado) {
        vector<string> path;
        Nodo* c = resultado;
        while (c) {
            path.push_back(c->getCadena());
            c = c->getPadre();
        }

        return path;
    }

    bool checarSiLaRamaSeEstanco (Nodo* nodoAVerificar) {
        string cadenaDelNodoAVerificar = nodoAVerificar->getCadena();

        nodoAVerificar = nodoAVerificar->getPadre();

        while (nodoAVerificar) {
            if (nodoAVerificar->getCadena() == cadenaDelNodoAVerificar)
                return true;
            nodoAVerificar = nodoAVerificar->getPadre();
        }

        return false;
    }

    Nodo* ancla;
    string punto_de_partida;
    string resultado_esperado = "012345678";
    uint64_t nodos_creados = 0;
public:
    Arbol(string punto_de_partida) {
        this->punto_de_partida = punto_de_partida;
        ancla = new Nodo(punto_de_partida);
        ancla->setProfundidad(0);
    };

    uint64_t getNodosCreados() {
        return this->nodos_creados;
    }
    string getPuntoObjetivo() {
        return this->resultado_esperado;
    }
    vector<string> busquedaPorProfundidad () {
        Nodo* resultado = ancla;
        if (resultado->getCadena() == this->resultado_esperado) {
            cout << "Resultado Encontrado" << endl;
            return getPath(resultado);
        }
        while (true) {
            if (!resultado->getEstaEstancado()) {
                vector<string> proximos_hijos = getMovimientosPosibles(resultado->getCadena());
                Nodo *hijoPasado = nullptr;
                for (string cadena_del_hijo: proximos_hijos) {
                    Nodo *hijo = new Nodo(cadena_del_hijo, resultado, (resultado->getProfundidad()) + 1);
                    if (hijo->getCadena() == this->resultado_esperado) {
                        cout << "Resultado Encontrado" << endl;
                        return getPath(hijo);
                    }
                    //hijo->print();
                    nodos_creados++;
                    if (hijoPasado) {
                        hijoPasado->setHermano(hijo);
                    } else {
                        hijo->getPadre()->setPrimerHijo(hijo);
                    }
                    hijo->setEstaEstancado(checarSiLaRamaSeEstanco(hijo));
                    hijoPasado = hijo;
                }
            }
            if (resultado->getPrimerHijo()) {
                resultado = resultado->getPrimerHijo();
            } else if (resultado->getHermano()) {
                resultado = resultado->getHermano();
            } else {
                do {
                    resultado = resultado->getPadre();
                } while (!resultado->getHermano());
                resultado = resultado->getHermano();
            }
            if (resultado)
                cout <<"Nodos creados: "<< this->nodos_creados << " - Profunfidad actual:" <<resultado->getProfundidad()<< endl;
        }
    }

    Nodo* search(Nodo* resultado) {
        if (!resultado->getEstaEstancado()) {
            vector<string> proximos_hijos = getMovimientosPosibles(resultado->getCadena());
            Nodo *hijoPasado = nullptr;
            for (string cadena_del_hijo: proximos_hijos) {
                Nodo *hijo = new Nodo(cadena_del_hijo, resultado, (resultado->getProfundidad()) + 1);
                if (resultado->getCadena() == this->resultado_esperado) {
                    cout << "Resultado Encontrado" << endl;
                    return resultado;
                }
                //hijo->print();
                nodos_creados++;
                if (hijoPasado) {
                    hijoPasado->setHermano(hijo);
                } else {
                    hijo->getPadre()->setPrimerHijo(hijo);
                }
                hijo->setEstaEstancado(checarSiLaRamaSeEstanco(hijo));
                hijoPasado = hijo;
            }

            resultado = resultado->getPrimerHijo();
            Nodo *respuesta = nullptr;
            while(resultado){
                if (resultado)
                    cout <<"Nodos creados: "<< this->nodos_creados << " - Profunfidad actual:" <<resultado->getProfundidad()<< endl;
                respuesta = search(resultado);
                if (respuesta) {
                    return respuesta;
                }
                resultado = resultado->getHermano();
            }
        }
        return nullptr;
    }


};


#endif //BUSQUEDAENPROFUNDIDAD_8_PUZZLE_ARBOL_H
