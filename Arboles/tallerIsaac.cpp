#include <iostream>
#include "arbolN.h"
#include "lista.h"

using namespace std;

// Función recursiva para calcular MSI
void calculateMSI(const ArbolN<int>& tree, int& include, int& exclude) {
    if (tree.esNulo()) {
        include = 0;
        exclude = 0;
        return;
    }
    
    include = tree.getRaiz();
    exclude = 0;
    
    // Obtener todos los hijos
    Lista<ArbolN<int>> hijos = tree.getHijos();
    int numHijos = hijos.getLength();
    
    // Procesar cada hijo
    for (int i = 0; i < numHijos; i++) {
        ArbolN<int> hijo = hijos.consultar(i);
        int childInclude, childExclude;
        calculateMSI(hijo, childInclude, childExclude);
        
        include += childExclude;
        exclude += (childInclude > childExclude) ? childInclude : childExclude;
    }
}

// Función para calcular MSI
int getMSI(const ArbolN<int>& tree) {
    int include, exclude;
    calculateMSI(tree, include, exclude);
    return (include > exclude) ? include : exclude;
}

// Función para calcular el balance de hojas
void calculateLeafBalance(const ArbolN<int>& tree, int level, int& evenLeaves, int& oddLeaves) {
    if (tree.esNulo()) {
        return;
    }
    
    // Obtener hijos
    Lista<ArbolN<int>> hijos = tree.getHijos();
    int numHijos = hijos.getLength();
    
    // Si es hoja (no tiene hijos)
    if (numHijos == 0) {
        if (level % 2 == 0) {
            evenLeaves++;
        } else {
            oddLeaves++;
        }
        return;
    }
    
    // Procesar cada hijo recursivamente
    for (int i = 0; i < numHijos; i++) {
        ArbolN<int> hijo = hijos.consultar(i);
        calculateLeafBalance(hijo, level + 1, evenLeaves, oddLeaves);
    }
}

// Función para obtener el balance
int getBalance(const ArbolN<int>& tree) {
    int evenLeaves = 0, oddLeaves = 0;
    calculateLeafBalance(tree, 0, evenLeaves, oddLeaves);
    return evenLeaves - oddLeaves;
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        // Leer eficiencias
        Lista<int> efficiencies;
        for (int i = 0; i < n; i++) {
            int eff;
            cin >> eff;
            efficiencies.insertar(eff, i);
        }
        
        // Leer aristas y construir lista de hijos para cada nodo
        Lista<Lista<int>> hijosPorNodo; // Lista de listas de hijos (índice 1-based)
        for (int i = 0; i <= n; i++) {
            hijosPorNodo.insertar(Lista<int>(), i);
        }
        
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            Lista<int> hijosU = hijosPorNodo.consultar(u);
            hijosU.insertar(v, hijosU.getLength());
            hijosPorNodo.modificar(hijosU, u);
        }
        
        // Función recursiva para construir el árbol desde las hojas hacia la raíz
        Lista<ArbolN<int>> arbolesConstruidos;
        for (int i = 0; i <= n; i++) {
            arbolesConstruidos.insertar(ArbolN<int>(), i);
        }
        
        // Construir árboles de forma recursiva (empezando desde las hojas)
        for (int i = n; i >= 1; i--) {
            Lista<int> hijos = hijosPorNodo.consultar(i);
            Lista<ArbolN<int>> arbolesHijos;
            
            // Construir lista de árboles hijos
            for (int j = 0; j < hijos.getLength(); j++) {
                int hijoId = hijos.consultar(j);
                ArbolN<int> arbolHijo = arbolesConstruidos.consultar(hijoId);
                arbolesHijos.insertar(arbolHijo, arbolesHijos.getLength());
            }
            
            // Crear el árbol actual
            int eficiencia = efficiencies.consultar(i - 1);
            ArbolN<int> arbolActual(eficiencia, arbolesHijos);
            arbolesConstruidos.modificar(arbolActual, i);
        }
        
        // Obtener el árbol raíz (nodo 1)
        ArbolN<int> tree = arbolesConstruidos.consultar(1);
        
        // Calcular MSI y Balance
        int msi = getMSI(tree);
        int balance = getBalance(tree);
        int chupa = msi * balance;
        
        cout << chupa << endl;
    }
    
    return 0;
}