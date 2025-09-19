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
    "Ivan", "Jimena", "Kevin", "Laura", "Mateo", "Nora", "Oscar", "Patricia"
};
const std::vector<std::string> APELLIDOS = {
    "Espinoza", "Campbell", "Hendrix", "Tyler", "Gomez", "Ruiz", "Diaz", "Perez",
    "Garcia", "Lopez", "Mora", "Soto", "Vargas", "Rojas", "Jimenez"
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

// --- Función principal para generar un archivo de casos ---
void generarArchivoDeCasos(int totalCasos, const std::string& nombreArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    // La primera línea es la cantidad total de casos de prueba
    archivo << totalCasos << std::endl;

    for (int i = 0; i < totalCasos; ++i) {
        // Generamos N, M, K aleatorios. Ajusta los rangos según tus necesidades.
        int n = generarNumero(1, 50);  // Elementos iniciales
        int m = generarNumero(0, 25);  // Inserciones
        int k = generarNumero(0, n);   // Eliminaciones (nunca más que los elementos iniciales)

        archivo << n << " " << m << " " << k << std::endl;

        // Escribimos los N nombres iniciales
        for (int j = 0; j < n; ++j) {
            archivo << "\"" << generarNombreAleatorio() << "\"";
            if (j < n - 1) {
                archivo << ", ";
            }
        }
        archivo << std::endl;
    }

    archivo.close();
    std::cout << "✅ Archivo '" << nombreArchivo << "' generado con " << totalCasos << " casos." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <numero_de_casos> <nombre_archivo_salida>" << std::endl;
        return 1;
    }

    try {
        int casos = std::stoi(argv[1]);
        std::string archivo = argv[2];
        generarArchivoDeCasos(casos, archivo);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: El número de casos debe ser un entero." << std::endl;
        return 1;
    }

    return 0;
}