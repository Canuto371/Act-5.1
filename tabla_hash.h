#ifndef TABLA_HASH_H
#define TABLA_HASH_H

#include <vector>
#include <list>

// Clase HASH_TABLE: Implementa una tabla hash con manejo de colisiones mediante
// sondeo cuadrático y encadenamiento.
class HASH_TABLE {
    std::vector<std::list<int>> table; // Estructura principal: vector de listas enlazadas
    int hash_tech(int key); // Función hash para calcular el índice de inserción

public:
    HASH_TABLE(int size); // Constructor: Inicializa la tabla con un tamaño ajustado al siguiente número primo
    void disp_tab(); // Muestra el contenido de la tabla
    void quadratic(int key); // Inserta un elemento usando sondeo cuadrático
    void chain(int key); // Inserta un elemento usando encadenamiento
};

#endif