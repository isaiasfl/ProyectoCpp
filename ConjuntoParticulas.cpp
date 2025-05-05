#include "ConjuntoParticulas.h"
#include <sstream>

// Métodos privados para manejo de memoria

/**
 * Reserva memoria para un array de partículas del tamaño especificado
 * @param tam Tamaño del array a reservar
 */
void ConjuntoParticulas::reservarMemoria(int tam) {
    // Solo reservamos si el tamaño es positivo
    if (tam > 0) {
        // Reservar un array de partículas del tamaño indicado
        set = new Particula[tam];
        // Actualizar la capacidad
        capacidad = tam;
    } else {
        // Si el tamaño es 0 o negativo, inicializamos a valores por defecto
        set = nullptr;
        capacidad = 0;
    }
    // Inicialmente no hay elementos útiles
    utiles = 0;
}

/**
 * Libera la memoria reservada para el array de partículas
 */
void ConjuntoParticulas::liberarMemoria() {
    // Solo liberamos memoria si hay algo que liberar
    if (set != nullptr) {
        delete[] set;
        set = nullptr;
    }
    // Reiniciamos los contadores
    capacidad = 0;
    utiles = 0;
}

/**
 * Redimensiona el array a una nueva capacidad
 * @param nuevaCapacidad Nueva capacidad del array
 */
void ConjuntoParticulas::redimensionar(int nuevaCapacidad) {
    // Solo redimensionamos si la nueva capacidad es diferente y válida
    if (nuevaCapacidad != capacidad && nuevaCapacidad >= 0) {
        // Caso especial: nueva capacidad es 0
        if (nuevaCapacidad == 0) {
            liberarMemoria();
            return;
        }
        
        // Creamos un array temporal con la nueva capacidad
        Particula* temp = new Particula[nuevaCapacidad];
        
        // Copiamos las partículas útiles (como máximo la nueva capacidad)
        int elementosACopiar = (nuevaCapacidad < utiles) ? nuevaCapacidad : utiles;
        for (int i = 0; i < elementosACopiar; i++) {
            temp[i] = set[i];
        }
        
        // Liberamos la memoria del array antiguo
        delete[] set;
        
        // Actualizamos el array y la capacidad
        set = temp;
        capacidad = nuevaCapacidad;
        
        // Ajustamos el número de útiles si es necesario
        if (utiles > capacidad) {
            utiles = capacidad;
        }
    }
}

// Implementación de los métodos públicos

/**
 * Constructor que crea un conjunto con n partículas aleatorias
 * @param n Número de partículas iniciales (por defecto 0)
 */
ConjuntoParticulas::ConjuntoParticulas(int n) {
    // Inicialmente no hay array
    set = nullptr;
    capacidad = 0;
    utiles = 0;
    
    // Si se solicitan partículas iniciales, las creamos
    if (n > 0) {
        // Reservar memoria para n partículas
        reservarMemoria(n);
        
        // Crear n partículas aleatorias utilizando el constructor por defecto de Particula
        for (int i = 0; i < n; i++) {
            // El constructor por defecto de Particula crea una partícula aleatoria
            set[i] = Particula();
            utiles++;
        }
    }
}

/**
 * Constructor de copia
 * @param otro Conjunto a copiar
 */
ConjuntoParticulas::ConjuntoParticulas(const ConjuntoParticulas& otro) {
    // Inicializamos el nuevo conjunto como vacío
    set = nullptr;
    capacidad = 0;
    utiles = 0;
    
    // Copiamos el conjunto si tiene elementos
    if (otro.utiles > 0) {
        // Reservamos memoria para la misma capacidad
        reservarMemoria(otro.capacidad);
        
        // Copiamos cada partícula útil
        for (int i = 0; i < otro.utiles; i++) {
            set[i] = otro.set[i];
        }
        
        // Actualizamos el contador de útiles
        utiles = otro.utiles;
    }
}

/**
 * Destructor - libera la memoria reservada
 */
ConjuntoParticulas::~ConjuntoParticulas() {
    liberarMemoria();
}

/**
 * Obtiene el número de partículas útiles
 * @return Número de partículas
 */
int ConjuntoParticulas::getUtiles() const {
    return utiles;
}

/**
 * Obtiene la capacidad total del conjunto
 * @return Capacidad del array
 */
int ConjuntoParticulas::getCapacidad() const {
    return capacidad;
}

/**
 * Agrega una partícula al conjunto
 * @param part Partícula a agregar
 */
void ConjuntoParticulas::agregar(const Particula& part) {
    // Si no hay espacio, aumentamos la capacidad
    if (utiles >= capacidad) {
        // Aumentamos en TAM_BLOQUE unidades
        redimensionar(capacidad + TAM_BLOQUE);
    }
    
    // Agregamos la partícula al final del array y aumentamos útiles
    set[utiles] = part;
    utiles++;
}

/**
 * Borra una partícula en la posición indicada
 * @param pos Posición de la partícula a borrar
 */
void ConjuntoParticulas::borrar(int pos) {
    // Verificar que la posición sea válida
    if (pos >= 0 && pos < utiles) {
        // Reemplazamos la partícula a borrar con la última útil
        set[pos] = set[utiles - 1];
        
        // Reducimos el contador de útiles
        utiles--;
        
        // Verificamos si hay espacio extra que podemos liberar
        if ((capacidad - utiles) > TAM_BLOQUE) {
            // Redimensionamos para ajustar exactamente a las partículas útiles
            redimensionar(utiles);
        }
    }
}

/**
 * Obtiene una referencia a la partícula en la posición indicada
 * @param pos Posición de la partícula
 * @return Referencia a la partícula
 */
Particula& ConjuntoParticulas::obtener(int pos) {
    // Verificar que la posición sea válida
    if (pos >= 0 && pos < utiles) {
        return set[pos];
    } else {
        // Si la posición no es válida, devolvemos la primera partícula
        // Nota: esto es un comportamiento de seguridad, en un programa real
        // sería mejor lanzar una excepción o manejar este caso de otra forma
        return set[0];
    }
}

/**
 * Reemplaza una partícula en la posición indicada
 * @param pos Posición a reemplazar
 * @param part Nueva partícula
 */
void ConjuntoParticulas::reemplazar(int pos, const Particula& part) {
    // Verificar que la posición sea válida
    if (pos >= 0 && pos < utiles) {
        // Reemplazamos la partícula en la posición indicada
        set[pos] = part;
    }
}

/**
 * Mueve todas las partículas del conjunto según el tipo indicado
 * @param tipo Tipo de movimiento: 0 = mover, 1 = mover+rebotar, 2 = mover+wrap
 */
void ConjuntoParticulas::mover(int tipo) {
    // Iterar por todas las partículas útiles
    for (int i = 0; i < utiles; i++) {
        // Siempre aplicamos el método mover
        set[i].mover();
        
        // Según el tipo, aplicamos comportamientos adicionales
        switch (tipo) {
            case 1:
                // Mover con rebote
                set[i].rebotar();
                break;
                
            case 2:
                // Mover con wrap
                set[i].wrap();
                break;
                
            default:
                // Para cualquier otro valor, solo mover (ya aplicado)
                break;
        }
    }
}

/**
 * Gestiona las colisiones entre partículas
 */
void ConjuntoParticulas::gestionarColisiones() {
    // Verificar cada par de partículas
    for (int i = 0; i < utiles - 1; i++) {
        for (int j = i + 1; j < utiles; j++) {
            // Verificar si hay colisión entre las partículas i y j
            if (set[i].colision(set[j])) {
                // Si colisionan, aplica el choque elástico
                set[i].choque(set[j]);
            }
        }
    }
}

/**
 * Devuelve una representación en string del conjunto
 * @return String con la información del conjunto
 */
std::string ConjuntoParticulas::toString() const {
    std::ostringstream oss;
    
    // Mostrar información general del conjunto
    oss << "Conjunto de Partículas: [Capacidad: " << capacidad 
        << ", Útiles: " << utiles << "]" << std::endl;
    
    // Mostrar cada partícula
    for (int i = 0; i < utiles; i++) {
        oss << "  " << i << ": " << set[i].toString() << std::endl;
    }
    
    return oss.str();
}