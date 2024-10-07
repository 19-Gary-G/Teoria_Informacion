#include <iostream>
#include <string>
using namespace std;

string decimal_a_binario(int decimal) {
    if (decimal == 0) return "0";
    string binario = "";
    while (decimal > 0) {
        int residuo = decimal % 2;
        binario = to_string(residuo) + binario;
        decimal = decimal / 2;
    }
    return binario;
}

int binario_a_decimal(string binario) {
    int decimal = 0;
    int potencia = 1;
    for (int i = binario.length() - 1; i >= 0; i--) {
        decimal += (binario[i] - '0') * potencia;
        potencia *= 2;
    }
    return decimal;
}

int main() {
    int opcion;
    cout << "Elige una opcion:" << endl;
    cout << "1. Convertir de decimal a binario" << endl;
    cout << "2. Convertir de binario a decimal" << endl;
    cin >> opcion;

    if (opcion == 1) {
        int numero_decimal;
        cout << "Introduce un numero en decimal: ";
        cin >> numero_decimal;
        string resultado = decimal_a_binario(numero_decimal);
        cout << "El numero en binario es: " << resultado << endl;
    } else if (opcion == 2) {
        string numero_binario;
        cout << "Introduce un numero en binario: ";
        cin >> numero_binario;
        int resultado = binario_a_decimal(numero_binario);
        cout << "El número en decimal es: " << resultado << endl;
    } else {
        cout << "Opcion no valida" << endl;
    }

    return 0;
}
