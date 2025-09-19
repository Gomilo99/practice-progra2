#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <stdexcept>

// --- Motor de aleatoriedad (más moderno y mejor que rand()) ---
std::random_device rd;
std::mt19937 gen(rd());

// --- Listas de nombres y apellidos para generar datos realistas ---
const std::vector<std::string> NOMBRES = {
    "Alvaro", "Beatriz", "Carlos", "Diana", "Esteban", "Fatima", "Gabriel", "Helena",
    "Ivan", "Jimena", "Kevin", "Laura", "Mateo", "Nora", "Oscar", "Patricia", "Raul",
    "Michelle", "Yulianny", "Jesus Eduardo", "Sofia", "Tomas", "Valeria", "William", "Ximena", "Yago", "Zoe"
};
const std::vector<std::string> APELLIDOS = {
    "Hernandez", "Lord Cambwell", "Betancourt", "Sayas", "De la Cruz", "Espinoza", "Campbell", "Hendrix", "Tyler", "Gomez", "Ruiz", "Diaz", "Perez",
    "Garcia", "Lopez", "Mora", "Soto", "Vargas", "Rojas", "Jimenez", "Castillo"
};

// --- Función para generar un nombre aleatorio ---
std::string generarNombreAleatorio() {
    std::uniform_int_distribution<> distNombres(0, NOMBRES.size() - 1);
    std::uniform_int_distribution<> distApellidos(0, APELLIDOS.size() - 1);
    return NOMBRES[distNombres(gen)] + " " + APELLIDOS[distApellidos(gen)];
}

// --- Función para generar un número entero en un rango ---
int generarNumero(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// --- Función principal para generar el archivo de casos ---
void generarArchivoDeCasos(int totalCasos) {
    // La primera línea es la cantidad total de casos de prueba
    std::cout << totalCasos << std::endl;

    for (int i = 0; i < totalCasos; ++i) {
        // --- MODIFICACIONES CLAVE ---
        int n = 200; // Número fijo de elementos iniciales
        int m = generarNumero(50, 100); // Inserciones (rango ajustado para N=200)
        int k = generarNumero(50, 150); // Eliminaciones (rango ajustado para N=200)

        std::cout << n << " " << m << " " << k << std::endl;

        // Escribimos los 200 nombres iniciales
        for (int j = 0; j < n; ++j) {
            std::cout << "\"" << generarNombreAleatorio() << "\"";
            if (j < n - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    // Genera directamente los 10,000 casos
    const int casosAGenerar = 10000;
    generarArchivoDeCasos(casosAGenerar);
    
    // Mensaje de confirmación a la salida de error para no contaminar el archivo de salida
    std::cerr << "✅ Archivo de prueba gigante generado exitosamente en la salida estándar." << std::endl;
    return 0;
}