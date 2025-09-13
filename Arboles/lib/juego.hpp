#ifndef JUEGO_HPP
#define JUEGO_HPP

#include <iostream>
#include <string>
#include <list>
#include <sstream>

using namespace std;
class Juego{
    private:
    string nombre, genero, desarrollador;
    int fecha;
    public:
    //Getters y Setters
    string getNombre() const { return nombre; }
    string getGenero() const { return genero; }
    string getDesarrollador() const { return desarrollador; }
    int getFecha() const { return fecha; }

    void setNombre(const string& n) { nombre = n; }
    void setGenero(const string& g) { genero = g; }
    void setDesarrollador(const string& d) { desarrollador = d; }
    void setFecha(int f) { fecha = f; }
    
    bool mayor(int fecha){ return this->fecha > fecha; }
    bool menor(int fecha){ return this->fecha < fecha; }
    bool operator== (const Juego otro){
        return (this->nombre == otro.nombre) && (this->genero == otro.genero) 
        && (this->desarrollador == otro.desarrollador) && (fecha == otro.fecha);
    }
    bool lecturaStandar() {
        string linea;
        int i = 0;
        if(!getline(cin, linea)) return false;
        //cout << linea;
            stringstream ss(linea);
            string nombre;
            while (getline(ss, nombre, ',')) {
                // Quitar espacios iniciales y finales
                size_t start = nombre.find_first_not_of(" \t\"");
                size_t end   = nombre.find_last_not_of(" \t\"");
                // la cadena solo tenía espacios/comillas
                if (start != string::npos ) 
                nombre = nombre.substr(start, end - start + 1);
                //cout << nombre;
                    switch (i)
                    {
                    case 0:
                        this->nombre = nombre;
                        break;
                    case 1:
                        this->genero = nombre;
                        break;
                    case 2:
                        this->desarrollador = nombre;
                        break;
                    case 3:
                        this->fecha = stoi(nombre);
                    default:
                        break;
                    }
                    i++;
            }
            return true;
    }
    void imprimirJuego(){
        cout << "Juego: " << this->nombre << " | Genero: " 
        << this->genero << " | Desarrollador: " << this->desarrollador 
        << " | Fecha de Lanzamiento: " << this->fecha << endl;
    }
};
#endif 