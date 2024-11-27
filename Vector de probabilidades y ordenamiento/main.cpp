#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct nodo {
    float prob;
    char letra;
    nodo *izq;
    nodo *der;
};

int menu();
nodo* insertar();
void mostrar(const vector<nodo*>& vec);
vector<nodo*> ordenar(vector<nodo*>& vec);
vector<nodo*> reducirVector(vector<nodo*> vec);
void mostrar2(const vector<nodo*>& vec, size_t x);

vector<nodo*> vec; // Vector global de nodos

int main() {
    int op;
    cout << "Hola amigos" << endl;

    do {
        op = menu();
        switch (op) {
            case 1: {
                nodo* nodoNuevo = insertar();
                vec.push_back(nodoNuevo);
                break;
            }
            case 2:
                mostrar2(vec, vec.size());
                break;
            case 3:
                vec = ordenar(vec);
                cout << "Lista ordenada por probabilidad." << endl;
                break;
            case 4:
                vec = reducirVector(vec);
                break;
            case 5:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "La opcion no es valida." << endl;
                break;
        }
    } while (op != 5);

    return 0;
}

int menu() {
    int opt = 0;
    cout << "*** Menu ***" << endl;
    cout << "1. Insertar nodo" << endl;
    cout << "2. Mostrar lista" << endl;
    cout << "3. Ordenar lista" << endl;
    cout << "4. Reducir lista (Huffman)" << endl;
    cout << "5. Salir" << endl;
    cout << "Selecciona tu opcion: ";
    cin >> opt;
    return opt;
}

nodo* insertar() {
    nodo* aux = new nodo();
    cout << "Dame la probabilidad: ";
    cin >> aux->prob;
    cout << "Dame la letra: ";
    cin >> aux->letra;
    aux->izq = nullptr;
    aux->der = nullptr;
    return aux;
}

void mostrar(const vector<nodo*>& vec) {
    for (const nodo* aux : vec) {
        cout << "Probabilidad: " << aux->prob << " | Caracter: " << aux->letra << endl;
        cout << "******" << endl;
    }
}

vector<nodo*> ordenar(vector<nodo*>& vec) {
    sort(vec.begin(), vec.end(), [](nodo* a, nodo* b) {
        return a->prob < b->prob; // Ordena de menor a mayor probabilidad
    });
    return vec;
}

vector<nodo*> reducirVector(vector<nodo*> vec) {
    while (vec.size() > 1) {
        // Ordenar vector antes de reducir
        vec = ordenar(vec);

        // Tomar los dos nodos con menor probabilidad
        nodo* first = vec[0];
        nodo* second = vec[1];

        // Crear un nuevo nodo que combine ambos
        nodo* nuevo = new nodo();
        nuevo->prob = first->prob + second->prob;
        nuevo->letra = '-'; // Nodo intermedio no tiene letra asociada
        nuevo->izq = first;
        nuevo->der = second;

        // Eliminar los nodos combinados del vector
        vec.erase(vec.begin());
        vec.erase(vec.begin());

        // Insertar el nuevo nodo en el vector
        vec.push_back(nuevo);
    }
    return vec;
}

void mostrar2(const vector<nodo*>& vec, size_t x) {
    for (size_t i = 0; i < min(x, vec.size()); i++) {
        cout << "Probabilidad: " << vec[i]->prob << " | Caracter: " << vec[i]->letra << endl;
        cout << "******" << endl;
    }
}
