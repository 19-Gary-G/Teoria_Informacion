#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// Nodo del árbol de Huffman
struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

// Comparador para la cola de prioridad
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// Función para generar códigos de Huffman
void generateCodes(HuffmanNode* root, std::string code, std::unordered_map<char, std::string>& huffmanCodes) {
    if (!root) return;

    if (root->character != '\0') {
        huffmanCodes[root->character] = code;
    }

    generateCodes(root->left, code + "0", huffmanCodes);
    generateCodes(root->right, code + "1", huffmanCodes);
}

// Función para obtener el tamaño del archivo en bytes
std::streamsize getFileSize(const std::string& fileName) {
    std::ifstream inFile(fileName, std::ios::binary | std::ios::ate);
    if (!inFile) throw std::runtime_error("No se puede abrir el archivo.");
    return inFile.tellg();
}

// Función para convertir tamaño en bytes a hexadecimal
std::string toHex(std::streamsize size) {
    std::stringstream ss;
    ss << std::hex << std::uppercase << size;
    return ss.str();
}

// Función para convertir tamaño en bytes a binario
std::string toBinary(std::streamsize size) {
    std::string binary;
    for (int i = sizeof(size) * 8 - 1; i >= 0; --i) {
        binary += ((size >> i) & 1) ? '1' : '0';
    }
    return binary;
}

// Función para obtener la extensión del archivo
std::string getFileExtension(const std::string& fileName) {
    size_t pos = fileName.find_last_of('.');
    if (pos != std::string::npos) {
        return fileName.substr(pos);
    }
    return "";
}

// Función para comprimir un archivo
void compressFile(const std::string& inputFileName) {
    std::ifstream inFile(inputFileName, std::ios::binary);
    if (!inFile) throw std::runtime_error("No se puede abrir el archivo original.");

    std::string data((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    std::unordered_map<char, int> freqMap;
    for (char ch : data) freqMap[ch]++;

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;
    for (const auto& [character, frequency] : freqMap) {
        pq.push(new HuffmanNode(character, frequency));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }
    HuffmanNode* root = pq.top();

    std::unordered_map<char, std::string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    std::string compressedFileName = inputFileName + "_cifrado";
    std::ofstream outFile(compressedFileName, std::ios::binary);
    if (!outFile) throw std::runtime_error("No se puede crear el archivo cifrado.");

    outFile << getFileExtension(inputFileName) << '\n';
    outFile << huffmanCodes.size() << '\n';
    for (const auto& [character, code] : huffmanCodes) {
        outFile << character << ' ' << code << '\n';
    }
    for (char ch : data) {
        outFile << huffmanCodes[ch];
    }

    outFile.close();

    std::streamsize compressedSize = getFileSize(compressedFileName);
    std::cout << "Archivo cifrado guardado como: " << compressedFileName << std::endl;
    std::cout << "Tamaño en bytes: " << compressedSize 
              << " (" << toHex(compressedSize) << " HEX, " 
              << toBinary(compressedSize) << " BIN)" << std::endl;
}

// Función para descomprimir un archivo
void decompressFile(const std::string& compressedFileName) {
    std::ifstream inFile(compressedFileName, std::ios::binary);
    if (!inFile) throw std::runtime_error("No se puede abrir el archivo cifrado.");

    std::string extension;
    std::getline(inFile, extension);

    int codeCount;
    inFile >> codeCount;
    inFile.ignore();

    std::unordered_map<std::string, char> reverseCodes;
    for (int i = 0; i < codeCount; ++i) {
        char character;
        std::string code;
        inFile >> character >> code;
        reverseCodes[code] = character;
    }
    inFile.ignore();

    std::string compressedData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    std::string currentCode;
    std::string originalData;
    for (char bit : compressedData) {
        currentCode += bit;
        if (reverseCodes.count(currentCode)) {
            originalData += reverseCodes[currentCode];
            currentCode.clear();
        }
    }

    std::string decompressedFileName = compressedFileName.substr(0, compressedFileName.find("_cifrado")) + "_descifrado" + extension;
    std::ofstream outFile(decompressedFileName, std::ios::binary);
    if (!outFile) throw std::runtime_error("No se puede crear el archivo descifrado.");
    outFile << originalData;
    outFile.close();

    std::streamsize decompressedSize = getFileSize(decompressedFileName);
    std::cout << "Archivo descifrado guardado como: " << decompressedFileName << std::endl;
    std::cout << "Tamaño en bytes: " << decompressedSize 
              << " (" << toHex(decompressedSize) << " HEX, " 
              << toBinary(decompressedSize) << " BIN)" << std::endl;
}

// Menú principal
int main() {
    int option;
    std::string fileName;
    std::string fileInQueue;

    do {
        std::cout << "\n*** Menu ***\n";
        std::cout << "1. Insertar el nombre del archivo\n";
        std::cout << "2. Cifrar archivo\n";
        std::cout << "3. Descifrar archivo\n";
        std::cout << "4. Mostrar archivo en espera\n";
        std::cout << "0. Salir\n";
        std::cout << "Selecciona una opcion: ";
        std::cin >> option;

        switch (option) {
            case 1:
                std::cout << "Introduce el nombre del archivo: ";
                std::cin >> fileInQueue;
                std::cout << "Archivo en espera: " << fileInQueue << std::endl;
                break;
            case 2:
                if (fileInQueue.empty()) {
                    std::cout << "No hay archivo en espera. Inserta primero un archivo.\n";
                } else {
                    try {
                        compressFile(fileInQueue);
                    } catch (const std::exception& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                }
                break;
            case 3:
                if (fileInQueue.empty()) {
                    std::cout << "No hay archivo en espera. Inserta primero un archivo.\n";
                } else {
                    try {
                        decompressFile(fileInQueue + "_cifrado");
                    } catch (const std::exception& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                }
                break;
            case 4:
                if (fileInQueue.empty()) {
                    std::cout << "No hay archivo en espera. Inserta primero un archivo.\n";
                } else {
                    std::streamsize size = getFileSize(fileInQueue);
                    std::cout << "Archivo en espera: " << fileInQueue 
                              << " (" << size << " bytes, " 
                              << toHex(size) << " HEX, " 
                              << toBinary(size) << " BIN)" << std::endl;
                }
                break;
            case 0:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opción inválida. Intenta de nuevo.\n";
        }
    } while (option != 0);

    return 0;
}
