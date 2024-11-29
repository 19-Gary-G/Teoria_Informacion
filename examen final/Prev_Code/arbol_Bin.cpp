//arbol binario

#include <iostream>
using namespace std;

struct Nodo {
    int id;
    string name;
    Nodo* liga;
};

// Función para insertar un nodo en una posición específica
Nodo* insertarPosicion(Nodo* inicio, int pos, int id, string name) {
    Nodo* nuevo = new Nodo{id, name, nullptr};

    if (pos < 1) {
        cout << "¡Posición inválida!" << endl;
        return inicio;
    }

    // Caso especial para insertar al inicio
    if (pos == 1) {
        nuevo->liga = inicio;
        return nuevo;
    }

    // Recorrer hasta el nodo anterior a la posición de inserción
    Nodo* actual = inicio;
    for (int i = 1; i < pos - 1 && actual != nullptr; i++) {
        actual = actual->liga;
    }

    // Si la posición es mayor que el número de nodos
    if (actual == nullptr) {
        cout << "¡Posición inválida!" << endl;
        delete nuevo;
        return inicio;
    }

    // Insertar el nuevo nodo en la posición deseada
    nuevo->liga = actual->liga;
    actual->liga = nuevo;

    return inicio;
}

// Función para eliminar un nodo en una posición específica
Nodo* eliminarPosicion(Nodo* inicio, int pos) {
    if (inicio == nullptr || pos < 1) {
        cout << "¡Posición inválida!" << endl;
        return inicio;
    }

    // Caso especial para eliminar el primer nodo
    if (pos == 1) {
        Nodo* temp = inicio;
        inicio = inicio->liga;
        delete temp;
        return inicio;
    }

    // Recorrer hasta el nodo anterior a la posición de eliminación
    Nodo* actual = inicio;
    for (int i = 1; i < pos - 1 && actual != nullptr; i++) {
        actual = actual->liga;
    }

    // Verificar si la posición es válida
    if (actual == nullptr || actual->liga == nullptr) {
        cout << "¡Posición fuera de rango!" << endl;
        return inicio;
    }

    // Eliminar el nodo en la posición deseada
    Nodo* temp = actual->liga;
    actual->liga = actual->liga->liga;
    delete temp;

    return inicio;
}

// Función para recorrer y mostrar la lista
void recorrerLista(Nodo* inicio) {
    Nodo* aux = inicio;
    while (aux != nullptr) {
        cout << "ID: " << aux->id << ", Name: " << aux->name << endl;
        aux = aux->liga;
    }
}

int main() {
    Nodo* inicio = nullptr;

    // Insertar nodos en la lista
    inicio = insertarPosicion(inicio, 1, 22, "pepe");
    inicio = insertarPosicion(inicio, 2, 13, "Juan");
    inicio = insertarPosicion(inicio, 3, 7, "luisa");

    // Recorrer y mostrar la lista
    cout << "Lista enlazada actual:" << endl;
    recorrerLista(inicio);

    // Insertar un nodo en la posición 2
    cout << "\nInsertando un nodo en la posición 2:" << endl;
    inicio = insertarPosicion(inicio, 2, 30, "Ana");
    recorrerLista(inicio);

    // Eliminar el nodo en la posición 3
    cout << "\nEliminando el nodo en la posición 3:" << endl;
    inicio = eliminarPosicion(inicio, 3);
    recorrerLista(inicio);

    return 0;
}
