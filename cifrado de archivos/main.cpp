#include <iostream>
#include <fstream>
#include <vector>

// Función para realizar la operación XOR en los datos
void xorData(std::vector<char>& data, char key) {
    for (auto& byte : data) {
        byte ^= key;
    }
}

// Función para leer el archivo
std::vector<char> readFile(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file) {
        throw std::runtime_error("No se puede abrir el archivo.");
    }
    return std::vector<char>((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
}

// Función para escribir en un archivo
void writeFile(const std::string& fileName, const std::vector<char>& data) {
    std::ofstream file(fileName, std::ios::binary);
    if (!file) {
        throw std::runtime_error("No se puede abrir el archivo para escribir.");
    }
    file.write(data.data(), data.size());
}

int main() {
    std::string inputFileName = "archivo.jpg";  // nombre del archivo
    std::string encryptedFileName = "archivo_encriptado.bin";
    std::string decryptedFileName = "archivo_desencriptado.jpg";
    char key = 'K';  // Clave para la operación XOR

    try {
        // Leer el archivo original
        std::vector<char> data = readFile(inputFileName);

        // Cifrar los datos
        xorData(data, key);
        writeFile(encryptedFileName, data);
        std::cout << "Archivo cifrado y guardado como " << encryptedFileName << std::endl;

        // Leer el archivo cifrado
        std::vector<char> encryptedData = readFile(encryptedFileName);

        // Descifrar los datos
        xorData(encryptedData, key);
        writeFile(decryptedFileName, encryptedData);
        std::cout << "Archivo descifrado y guardado como " << decryptedFileName << std::endl;

        // Mostrar el mensaje original
        std::cout << "Contenido del archivo original:\n";
        for (char c : encryptedData) {
            std::cout << c;
        }
        std::cout << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}