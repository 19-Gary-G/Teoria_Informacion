#include <iostream>
#include <fstream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()

void add_noise(const std::string& input_file, const std::string& output_file) {
    std::ifstream infile(input_file, std::ios::binary);
    std::ofstream outfile(output_file, std::ios::binary);

    if (!infile) {
        std::cerr << "No se puede abrir el archivo de entrada.\n";
        return;
    }

    if (!outfile) {
        std::cerr << "No se puede crear el archivo de salida.\n";
        return;
    }

    char byte;
    int count = 0;

    srand(time(0)); // Inicializa el generador de números aleatorios

    // Leer el archivo y modificar cada tercer byte
    while (infile.get(byte)) {
        if (count % 3 == 2) {
            // Generar ruido aleatorio (valor entre 0 y 255)
            byte = static_cast<char>(rand() % 256);
        }
        // Escribir el byte (original o con ruido) en el archivo de salida
        outfile.put(byte);
        ++count;
    }

    infile.close();
    outfile.close();
}

int main() {
    std::string input_file = "archivo_original.txt";
    std::string output_file = "archivo_con_ruido.txt";

    add_noise(input_file, output_file);

    std::cout << "Archivo con ruido generado con éxito.\n";
    return 0;
}
