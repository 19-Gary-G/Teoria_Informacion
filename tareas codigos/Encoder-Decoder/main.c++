#include <iostream>
#include <string>

int main() {
    std::string msg = "este mensaje secreto";
    std::string msgRedun = "";
    std::string msgRuido = "";

    for (int i = 0; i < msg.length(); i++) {
        std::cout << (int)msg[i] << " ";  // Mostrar el valor ASCII del carácter

        // Concatenar el carácter 3 veces para la redundancia
        msgRedun += msg[i];  // 1ra copia
        msgRedun += msg[i];  // 2da copia
        msgRedun += msg[i];  // 3ra copia

        // Aplicar XOR con 3 y agregar al mensaje de ruido
        msgRuido += (char)(msg[i] ^ 3);
    }

    std::cout << "\nEl mensaje redundante es: " << msgRedun << std::endl;
    std::cout << "El mensaje con ruido es: " << msgRuido << std::endl;

    return 0;
}
