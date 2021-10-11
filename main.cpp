#include "Arbol.h"

string stringToFormato(string);
string getRandom8Puzzle();

int main() {
    string cadenaDe8PuzzleRandom = getRandom8Puzzle();
    Arbol* tree = new Arbol(cadenaDe8PuzzleRandom);

    cout << "Posicion Inicial: " << cadenaDe8PuzzleRandom << endl;
    cout << "Posicion Objetivo: " << tree->getPuntoObjetivo() << endl;

    getc(stdin);


    vector<string> resultado = tree->busquedaPorProfundidad();

    for(string i : resultado){
        if (i == "vacio")
            break;
        cout << stringToFormato(i) << endl;
    }

    cout << "Nodos Creados: " << tree->getNodosCreados() << endl;
    getc(stdin);

    return 0;
}


string getRandom8Puzzle() {
    srand(time(NULL));
    string cadena = "";
    vector<string> opciones;
    string numeros [9] = {"0", "1", "2", "3", "4", "5", "6", "7", "8"};
    for(int i=0 ; i < 9 ; i++) {
        opciones.push_back(numeros[i]);
    }
    for (int i=9 ; i > 0 ; i--){
        int rand_num = rand() % i;
        cadena += opciones[rand_num];
        opciones.erase(opciones.begin() + rand_num);
    }
    return cadena;
}

string stringToFormato(string cadena) {
    string x;
    for (int i=0 ; i < cadena.length() ; i++){
        if (i % 3 == 0){
            x += "\n";
        }
        x += cadena[i];
        x += "\t";
    }
    return x;
}