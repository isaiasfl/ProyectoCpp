#ifndef CONJUNTO_PARTICULAS_H
#define CONJUNTO_PARTICULAS_H

#include "Particula.h"

// Tamaño del bloque para redimensionar el array
const int TAM_BLOQUE = 3;

class ConjuntoParticulas {
private:
    Particula* set;        // Array dinámico de partículas
    int capacidad;         // Capacidad total del array
    int utiles;            // Posiciones ocupadas actualmente
    
    /**
     * Reserva memoria para el array de partículas
     * @param tam Tamaño del array a reservar
     */
    void reservarMemoria(int tam);
    
    /**
     * Libera la memoria del array de partículas
     */
    void liberarMemoria();
    
    /**
     * Redimensiona el array para ajustar su capacidad
     * @param nuevaCapacidad Nueva capacidad del array
     */
    void redimensionar(int nuevaCapacidad);
    
public:
    /**
     * Constructor por defecto
     * @param n Número inicial de partículas (por defecto 0)
     */
    ConjuntoParticulas(int n = 0);
    
    /**
     * Constructor de copia
     * @param otro Conjunto a copiar
     */
    ConjuntoParticulas(const ConjuntoParticulas& otro);
    
    /**
     * Destructor
     */
    ~ConjuntoParticulas();
    
    /**
     * Obtiene el número de partículas útiles
     * @return Número de partículas
     */
    int getUtiles() const;
    
    /**
     * Obtiene la capacidad total del conjunto
     * @return Capacidad del array
     */
    int getCapacidad() const;
    
    /**
     * Agrega una partícula al conjunto
     * @param part Partícula a agregar
     */
    void agregar(const Particula& part);
    
    /**
     * Borra una partícula en la posición indicada
     * @param pos Posición de la partícula a borrar
     */
    void borrar(int pos);
    
    /**
     * Obtiene una referencia a la partícula en la posición indicada
     * @param pos Posición de la partícula
     * @return Referencia a la partícula
     */
    Particula& obtener(int pos);
    
    /**
     * Reemplaza una partícula en la posición indicada
     * @param pos Posición a reemplazar
     * @param part Nueva partícula
     */
    void reemplazar(int pos, const Particula& part);
    
    /**
     * Mueve todas las partículas del conjunto según el tipo indicado
     * @param tipo Tipo de movimiento: 0 = mover, 1 = mover+rebotar, 2 = mover+wrap
     */
    void mover(int tipo = 0);
    
    /**
     * Gestiona las colisiones entre partículas
     */
    void gestionarColisiones();
    
    /**
     * Devuelve una representación en string del conjunto
     * @return String con la información del conjunto
     */
    std::string toString() const;
};

#endif // CONJUNTO_PARTICULAS_H