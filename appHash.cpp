/*
Programación de estructuras de datos y algoritmos fundamentales (Gpo 601)
Act 5.1 - Implementación individual de operaciones sobre conjuntos

Integrante: ###
Matrícula: A###
Fecha: 24/11/2024

Este programa implementa una tabla hash con dos métodos de manejo de colisiones: resolución de colisiones por sondeo cuadrático y 
resolución de colisiones por encadenamiento. La tabla hash se inicializa con un tamaño ajustado al siguiente número primo mayor o igual al **doble** del número de elementos 
proporcionado, utilizando la función `next_prime`, que busca eficientemente primos a partir de un número dado.

El programa permite insertar elementos en la tabla utilizando ambos métodos de manejo de colisiones. Para la resolución cuadrática, se calcula el índice base mediante una función hash
y se buscan índices vacíos aplicando un desplazamiento cuadrático, garantizando que no haya colisiones. En el caso del encadenamiento, los elementos se almacenan en listas enlazadas 
asociadas a cada índice de la tabla.

Finalmente, el programa muestra el contenido de la tabla después de realizar inserciones con ambos métodos, permitiendo observar la distribución de los elementos en la tabla hash 
y la efectividad del manejo de colisiones en cada método.
*/

#include "tabla_hash.h"
#include <cmath>
#include <iostream>

// Función para encontrar el siguiente número primo
// Complejidad: O(√n * log n)
// La complejidad surge porque para encontrar el siguiente primo iteramos sobre números consecutivos,
// y para cada número verificamos si es primo en O(√n). La densidad de números primos en un intervalo está relacionada con log(n),
// lo que da como resultado una complejidad combinada de O(√n * log n).
int next_prime(int num) {
    auto is_prime = [](int n) {
        if (n < 2) return false; // Los números menores que 2 no son primos
        // Verifica si el número tiene algún divisor entre 2 y √n
        for (int i = 2; i <= std::sqrt(n); ++i) {
            if (n % i == 0) return false; // Si es divisible por algún número, no es primo
        }
        return true; // Si no tiene divisores, es primo
    };

    // Incrementa el número hasta encontrar el siguiente primo
    while (!is_prime(num)) {
        ++num;
    }
    return num; // Devuelve el número primo encontrado
}

// Constructor: ajusta el tamaño de la tabla al siguiente número primo
// Complejidad: O(√n * log n)
// Llama a `next_prime` para calcular el tamaño ajustado de la tabla, cuya complejidad domina.
HASH_TABLE::HASH_TABLE(int size) : table(next_prime(size)) {
    std::cout << "Tamaño de la tabla ajustado al número primo: " << table.size() << std::endl;
}

// Función hash: usa el tamaño actual de la tabla
// Complejidad: O(1)
// Realiza una operación módulo, que tiene un tiempo constante, por lo que la complejidad es O(1).
int HASH_TABLE::hash_tech(int key) {
    return key % table.size(); // Calcula el índice hash aplicando módulo
}

// Mostrar contenido de la tabla
// Complejidad: O(n)
// Se recorren todos los índices de la tabla (O(m), donde m es el tamaño de la tabla) y, si hay elementos, se recorren todas las listas enlazadas.
// En el peor caso, si todos los elementos están almacenados en la tabla, la complejidad es proporcional al número total de elementos, O(n).
void HASH_TABLE::disp_tab() {
    for (size_t i = 0; i < table.size(); ++i) {
        std::cout << "Index " << i << ": ";
        if (table[i].empty()) {
            std::cout << "null" << std::endl; // Índice vacío
        } else {
            // Imprime todos los elementos almacenados en la lista enlazada de este índice
            for (const auto& elemento : table[i]) {
                std::cout << elemento << " ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

// Inserción con resolución cuadrática
// Complejidad: O(n)
// En el peor caso, cuando la tabla está llena o casi llena, el algoritmo puede realizar hasta n intentos para encontrar un índice vacío.
// Cada intento verifica una posición, lo que lleva a una complejidad total de O(n) en el peor escenario.
void HASH_TABLE::quadratic(int key) {
    int index_hash = hash_tech(key); // Calcula el índice base del hash
    int i = 0; // Inicializa el contador para la resolución cuadrática

    // Realiza la resolución cuadrática para encontrar un índice vacío
    while (!table[(index_hash + i * i) % table.size()].empty()) {
        i++; // Incrementa el desplazamiento cuadrático
        if (i >= table.size()) { // Control para evitar loops infinitos si la tabla está llena
            std::cerr << "Error: Tabla hash llena, no se puede insertar " << key << std::endl;
            return;
        }
    }
    // Inserta el elemento en el índice encontrado
    table[(index_hash + i * i) % table.size()].push_back(key);
}

// Inserción con encadenamiento
// Complejidad: O(1)
// La inserción en el índice calculado por el hash es una operación constante, ya que simplemente agregamos el elemento al final de la lista enlazada en ese índice.
void HASH_TABLE::chain(int key) {
    int index_hash = hash_tech(key); // Calcula el índice base del hash
    table[index_hash].push_back(key); // Inserta el elemento al final de la lista enlazada
}

// Función principal
int main() {
    int num_elements;
    std::cout << "Ingrese la cantidad de elementos: ";
    std::cin >> num_elements;

    std::vector<int> hash_nums(num_elements); // Vector para almacenar los elementos a insertar
    std::cout << "Ingrese los elementos (separados por espacio): ";
    for (int i = 0; i < num_elements; ++i) {
        std::cin >> hash_nums[i]; // Lee los elementos desde la entrada estándar
    }

    // Ajustar el tamaño inicial de la tabla al siguiente primo mayor al doble del número de elementos
    int table_size = next_prime(num_elements * 2);

    // Crear tablas hash con el tamaño ajustado
    HASH_TABLE table1(table_size), table2(table_size);

    // Insertar con resolución cuadrática
    for (int num : hash_nums) {
        table1.quadratic(num); // Inserta cada elemento usando resolución cuadrática
    }
    std::cout << "---- Manejo de desbordamiento por sondeo cuadrático ----" << std::endl;
    table1.disp_tab(); // Muestra el contenido de la tabla después de la inserción

    // Insertar con encadenamiento
    for (int num : hash_nums) {
        table2.chain(num); // Inserta cada elemento usando encadenamiento
    }
    std::cout << "---- Manejo de desbordamiento por encadenamiento ----" << std::endl;
    table2.disp_tab(); // Muestra el contenido de la tabla después de la inserción

    return 0;
}

