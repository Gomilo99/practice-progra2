#include <iostream>
#include <vector>   // Para std::vector
#include <string>   // Para std::string
#include <iomanip>  // Para std::setw y std::setfill

// Clase Reloj
class Reloj {
private:
    std::string tipo;
    std::string marca;
    int horaActual;
    int minutoActual;
    int segundoActual;

public:
    // Constructor
    Reloj(const std::string& tipo, const std::string& marca, int hora, int minuto, int segundo) {
        if (tipo != "analógico" && tipo != "digital") {
            throw std::invalid_argument("El tipo de reloj debe ser 'analógico' o 'digital'.");
        }
        if (!(hora >= 0 && hora < 24 && minuto >= 0 && minuto < 60 && segundo >= 0 && segundo < 60)) {
            throw std::invalid_argument("La hora, minuto o segundo inicial no son válidos.");
        }

        this->tipo = tipo;
        this->marca = marca;
        this->horaActual = hora;
        this->minutoActual = minuto;
        this->segundoActual = segundo;
    }

    // Método avanzarTiempo (O(1))
    void avanzarTiempo(int horas, int minutos, int segundos) {
        segundoActual += segundos;
        minutoActual += segundoActual / 60;
        segundoActual %= 60;

        minutoActual += minutos;
        horaActual += minutoActual / 60;
        minutoActual %= 60;

        horaActual += horas;
        horaActual %= 24;
    }

    // Métodos getters para acceder a los atributos (opcional, pero buena práctica)
    std::string getTipo() const { return tipo; }
    std::string getMarca() const { return marca; }
    int getHoraActual() const { return horaActual; }
    int getMinutoActual() const { return minutoActual; }
    int getSegundoActual() const { return segundoActual; }

    // Método setter para sincronizar (necesario para ZonaHoraria)
    void setHora(int hora, int minuto, int segundo) {
        if (!(hora >= 0 && hora < 24 && minuto >= 0 && minuto < 60 && segundo >= 0 && segundo < 60)) {
            throw std::invalid_argument("La hora, minuto o segundo de sincronización no son válidos.");
        }
        this->horaActual = hora;
        this->minutoActual = minuto;
        this->segundoActual = segundo;
    }

    // Método para imprimir la información del reloj
    void imprimir() const {
        std::cout << "[" << (tipo == "analógico" ? "Analógico" : "Digital") << "] "
                  << marca << " - "
                  << std::setw(2) << std::setfill('0') << horaActual << ":"
                  << std::setw(2) << std::setfill('0') << minutoActual << ":"
                  << std::setw(2) << std::setfill('0') << segundoActual;
    }
};

// Clase ZonaHoraria
class ZonaHoraria {
private:
    std::string nombre;
    std::vector<Reloj> relojes; // Usamos std::vector como un arreglo dinámico
    int numeroRelojes;

public:
    // Constructor
    ZonaHoraria(const std::string& nombre) : nombre(nombre), numeroRelojes(0) {}

    // Método agregarReloj
    void agregarReloj(const Reloj& reloj) {
        relojes.push_back(reloj);
        numeroRelojes++;
        std::cout << "Reloj agregado a la zona horaria '" << nombre << "': ";
        reloj.imprimir();
        std::cout << std::endl;
    }

    // Método eliminarRelojPorNumero
    bool eliminarRelojPorNumero(int n) {
        if (n < 0 || n >= numeroRelojes) {
            std::cout << "Error: No existe un reloj en la posición " << n << "." << std::endl;
            return false;
        }

        std::cout << "Reloj eliminado de la zona horaria '" << nombre << "': ";
        relojes[n].imprimir();
        std::cout << std::endl;

        relojes.erase(relojes.begin() + n);
        numeroRelojes--;
        return true;
    }

    // Método sincronizarRelojes
    void sincronizarRelojes(int horas, int minutos, int segundos) {
        if (!(horas >= 0 && horas < 24 && minutos >= 0 && minutos < 60 && segundos >= 0 && segundos < 60)) {
            std::cout << "Error: La hora, minuto o segundo de sincronización no son válidos." << std::endl;
            return;
        }

        std::cout << "\nSincronizando todos los relojes en la zona horaria '" << nombre
                  << "' a " << std::setw(2) << std::setfill('0') << horas << ":"
                  << std::setw(2) << std::setfill('0') << minutos << ":"
                  << std::setw(2) << std::setfill('0') << segundos << "..." << std::endl;

        for (Reloj& reloj : relojes) {
            reloj.setHora(horas, minutos, segundos);
            std::cout << "  - ";
            reloj.imprimir();
            std::cout << std::endl;
        }
    }

    // Método para imprimir la información de la zona horaria
    void imprimir() const {
        std::cout << "Zona Horaria: " << nombre << " (" << numeroRelojes << " relojes)" << std::endl;
        if (numeroRelojes == 0) {
            std::cout << "  (Ningún reloj)" << std::endl;
        } else {
            for (const Reloj& reloj : relojes) {
                std::cout << "  - ";
                reloj.imprimir();
                std::cout << std::endl;
            }
        }
    }
};

// Función principal para probar las clases
int main() {
    // Creando algunos relojes
    Reloj reloj1("digital", "Casio", 10, 0, 20);
    Reloj reloj2("analógico", "Rolex", 15, 30, 0);
    Reloj reloj3("digital", "Xiaomi", 7, 5, 10);

    std::cout << "--- Relojes Iniciales ---" << std::endl;
    reloj1.imprimir(); std::cout << std::endl;
    reloj2.imprimir(); std::cout << std::endl;
    reloj3.imprimir(); std::cout << std::endl;

    // Avanzando el tiempo del reloj1
    std::cout << "\n--- Avanzando Tiempo ---" << std::endl;
    std::cout << "Reloj 1 antes de avanzar: "; reloj1.imprimir(); std::cout << std::endl;
    reloj1.avanzarTiempo(10, 0, 30); // Ejemplo: 10:00:20 si avanzamos 10:00:30 la hora nueva sería 20:00:40.
    std::cout << "Reloj 1 después de avanzar (10h 0m 30s): "; reloj1.imprimir(); std::cout << std::endl; // Debería ser 20:00:50

    // Creando una zona horaria
    ZonaHoraria zonaMadrid("Europa/Madrid");
    std::cout << "\n--- Agregando Relojes a Zona Horaria ---" << std::endl;
    zonaMadrid.agregarReloj(reloj1);
    zonaMadrid.agregarReloj(reloj2);
    zonaMadrid.agregarReloj(reloj3);

    std::cout << "\n--- Estado Actual de la Zona Horaria ---" << std::endl;
    zonaMadrid.imprimir();

    // Eliminando un reloj por número (índice 0, que es reloj1)
    std::cout << "\n--- Eliminando Reloj de Zona Horaria ---" << std::endl;
    zonaMadrid.eliminarRelojPorNumero(0);

    std::cout << "\n--- Estado de la Zona Horaria Después de Eliminar ---" << std::endl;
    zonaMadrid.imprimir();

    // Sincronizando todos los relojes de la zona horaria
    zonaMadrid.sincronizarRelojes(9, 0, 0);

    std::cout << "\n--- Estado Final de la Zona Horaria ---" << std::endl;
    zonaMadrid.imprimir();

    // Intento de sincronización con valores inválidos
    zonaMadrid.sincronizarRelojes(25, 0, 0);

    return 0;
}