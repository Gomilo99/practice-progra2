#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm> // Para std::shuffle
#include <numeric>   // Para std::iota

int main() {
    // --- Constantes ---
    const int TEST_CASES = 2000;
    const int MAX_NODES = 1000;
    const int MIN_NODES = 500;

    // --- Configuración del generador de números aleatorios ---
    // Usamos un generador moderno de C++ para obtener aleatoriedad de alta calidad.
    std::random_device rd;  // Obtiene una semilla aleatoria del hardware.
    std::mt19937 gen(rd()); // Motor generador Mersenne Twister, sembrado con rd.

    // --- Abrir el archivo de salida ---
    std::ofstream outFile("bigInput2.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo bigInput.txt para escribir." << std::endl;
        return 1;
    }

    // Escribir el número de casos de prueba.
    outFile << TEST_CASES << "\n";

    // --- Bucle principal para generar cada caso de prueba ---
    for (int i = 0; i < TEST_CASES; ++i) {
        // Distribución para generar el número de nodos en el rango [MIN, MAX].
        std::uniform_int_distribution<> nodeDist(MIN_NODES, MAX_NODES);
        int numberOfNodes = nodeDist(gen);
        outFile << numberOfNodes << "\n";

        // --- Generar eficiencias locales únicas (equivalente a random.sample) ---
        // 1. Crear un vector con la población de números posibles (-1000 a 999).
        std::vector<int> population(1999 - (-1000) + 1);
        std::iota(population.begin(), population.end(), -1000); // Rellena el vector.

        // 2. Barajar aleatoriamente la población.
        std::shuffle(population.begin(), population.end(), gen);

        // 3. Escribir los primeros 'numberOfNodes' elementos del vector barajado.
        for (int j = 0; j < numberOfNodes; ++j) {
            outFile << population[j] << " ";
        }
        outFile << "\n";

        // --- Generar la estructura del árbol (padre-hijo) ---
        int parent = 1;
        std::uniform_real_distribution<> probDist(0.0, 1.0); // Para la probabilidad de 0.5

        for (int j = 2; j <= numberOfNodes; ++j) {
            outFile << parent << " " << j << "\n";

            // Con una probabilidad de 0.5, cambiamos el padre a un nodo ya existente.
            if (probDist(gen) > 0.5) {
                std::uniform_int_distribution<> parentDist(1, j);
                parent = parentDist(gen);
            }
        }
    }

    outFile.close();
    std::cout << "El archivo 'bigInput.txt' ha sido generado exitosamente." << std::endl;

    return 0;
}