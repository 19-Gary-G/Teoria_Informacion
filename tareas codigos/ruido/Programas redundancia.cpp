#include <iostream>
#include <fstream>

void replicate_bytes(const std::string& input_file, const std::string& output_file) {
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
    while (infile.get(byte)) {
        // Escribe el byte 3 veces en el archivo de salida
        for (int i = 0; i < 3; ++i) {
            outfile.put(byte);
        }
    }

    infile.close();
    outfile.close();
}

int main() {
    std::string input_file = "archivo_original.txt";
    std::string output_file = "archivo_replicado.txt";

    replicate_bytes(input_file, output_file);

    std::cout << "Archivo replicado creado con éxito.\n";
    return 0;
}
