//Programa Probabilidades de caracteres

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <iomanip> // Para formatear la salida

// Nodo del árbol de Huffman
struct HuffmanNode {
    char character;
    double frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char ch, double freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
};

// Comparador para la cola de prioridad
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

// Función para imprimir el árbol paso a paso
void printStep(const std::vector<HuffmanNode*>& nodes) {
    for (const auto& node : nodes) {
        if (node->character != '\0') {
            std::cout << node->character << "=" << std::fixed << std::setprecision(1) << node->frequency << ", ";
        } else {
            std::cout << std::fixed << std::setprecision(1) << node->frequency << ", ";
        }
    }
    std::cout << "\n";
}

// Función para construir el árbol de Huffman
HuffmanNode* buildHuffmanTree(std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare>& pq) {
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        // Crear un nuevo nodo combinando los dos menores
        HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        pq.push(parent);

        // Mostrar paso
        std::vector<HuffmanNode*> temp;
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> tempPQ = pq;
        while (!tempPQ.empty()) {
            temp.push_back(tempPQ.top());
            tempPQ.pop();
        }
        printStep(temp);
    }

    return pq.top(); // Raíz del árbol
}

int main() {
    std::string fileName;
    std::cout << "Introduce el nombre del archivo de texto: ";
    std::cin >> fileName;

    // Leer el archivo
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error al abrir el archivo.\n";
        return 1;
    }

    // Calcular frecuencias
    std::unordered_map<char, int> freqMap;
    char ch;
    int totalChars = 0;
    while (file.get(ch)) {
        if (!isspace(ch)) { // Ignorar espacios
            freqMap[ch]++;
            totalChars++;
        }
    }
    file.close();

    // Calcular probabilidades y construir los nodos
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;
    for (const auto& [character, count] : freqMap) {
        double probability = static_cast<double>(count) / totalChars * 100.0;
        pq.push(new HuffmanNode(character, probability));
    }

    // Imprimir las frecuencias iniciales
    std::cout << "Caracteres y frecuencias iniciales:\n";
    std::vector<HuffmanNode*> initialNodes;
    while (!pq.empty()) {
        initialNodes.push_back(pq.top());
        pq.pop();
    }
    printStep(initialNodes);

    // Reconstruir la cola de prioridad para procesar
    for (const auto& node : initialNodes) {
        pq.push(node);
    }

    // Construir el árbol de Huffman
    std::cout << "Proceso de construccion del arbol de Huffman:\n";
    HuffmanNode* root = buildHuffmanTree(pq);

    std::cout << "arbol de Huffman construido con exito.\n";
    return 0;
}
