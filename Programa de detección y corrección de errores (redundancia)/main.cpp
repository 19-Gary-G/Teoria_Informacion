#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>  // Para isprint()

// Función que verifica si un byte es un carácter imprimible
bool is_printable(char byte) {
    return std::isprint(static_cast<unsigned char>(byte));
}

// Función para aplicar el algoritmo de votación y corrección de errores sobre un solo archivo
void vote_and_correct(const std::string& input_file, const std::string& output_file, int block_size) {
    std::ifstream infile(input_file, std::ios::binary);
    std::ofstream outfile(output_file, std::ios::binary);

    if (!infile) {
        std::cerr << "Error: No se puede abrir el archivo de entrada.\n";
        return;
    }

    if (!outfile) {
        std::cerr << "Error: No se puede crear el archivo de salida.\n";
        return;
    }

    std::vector<char> block(block_size); // Bloque que contendrá varias copias de los datos
    int bytes_error_count = 0; // Contador de bytes con errores

    // Leer el archivo en bloques de tamaño block_size
    while (infile.read(block.data(), block_size)) {
        std::map<char, int> byte_count;

        // Contar la frecuencia de cada byte en el bloque, identificando caracteres no imprimibles
        for (char byte : block) {
            byte_count[byte]++;
        }

        // Encontrar el byte con más votos
        char majority_byte = std::max_element(byte_count.begin(), byte_count.end(),
            [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
                return a.second < b.second;
            })->first;

        // Verificar si el byte mayoritario es imprimible, si no lo es, cuenta como error
        if (!is_printable(majority_byte)) {
            ++bytes_error_count; // Contar bytes no imprimibles o erróneos
        }

        // Escribir el byte mayoritario o reemplazar con un valor predeterminado si es no imprimible
        if (is_printable(majority_byte)) {
            outfile.put(majority_byte);
        } else {
            // En este caso, puedes decidir qué hacer con el byte no imprimible:
            // 1. Escribir un valor predeterminado (ejemplo: ' ')
            outfile.put(' ');  // Reemplaza los caracteres no reconocidos con un espacio
        }
    }

    std::cout << "Proceso completado. Bytes con errores detectados: " << bytes_error_count << "\n";

    infile.close();
    outfile.close();
}

int main() {
    std::string input_file = "archivo_con_ruido.txt";
    std::string output_file = "archivo_corregido.txt";

    int block_size = 3;  // Número de copias redundantes de cada dato en el archivo

    // Aplicar el algoritmo de votación y corrección de errores
    vote_and_correct(input_file, output_file, block_size);

    return 0;
}
