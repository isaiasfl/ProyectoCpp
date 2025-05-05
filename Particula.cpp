#include "Particula.h"
#include <sstream>

// Constructor con valor por defecto
Particula::Particula(int tipoPart) : tipo(tipoPart) {
    if (tipoPart != 0) {
        // Partícula estática
        pos.setXY(0, 0);
        acel.setXY(0, 0);
        veloc.setXY(0, 0);
        radio = 3.0f;
    } else {
        // Partícula dinámica con valores aleatorios
        // Inicializar la semilla aleatoria si es la primera vez
        static bool primerLlamada = true;
        if (primerLlamada) {
            srand(static_cast<unsigned int>(time(nullptr)));
            primerLlamada = false;
        }
        
        // Posición aleatoria dentro del mundo
        pos.setXY(aleatorio(0, MAX_X), aleatorio(0, MAX_Y));
        
        // Velocidad aleatoria dentro de los límites
        veloc.setXY(aleatorio(-MAX_VEL, MAX_VEL), aleatorio(-MAX_VEL, MAX_VEL));
        
        // Aceleración aleatoria dentro de los límites
        acel.setXY(aleatorio(-MAX_ACC, MAX_ACC), aleatorio(-MAX_ACC, MAX_ACC));
        
        // Radio aleatorio
        radio = aleatorio(MIN_R, MAX_R);
    }
}

// Constructor con parámetros
Particula::Particula(const Vector2D& pos, const Vector2D& acel, const Vector2D& veloc, float radio, int tipo)
    : pos(pos), acel(acel), veloc(veloc), radio(radio), tipo(tipo) {}

// Métodos get
Vector2D Particula::getPos() const {
    return pos;
}

Vector2D Particula::getAcel() const {
    return acel;
}

Vector2D Particula::getVeloc() const {
    return veloc;
}

float Particula::getRadio() const {
    return radio;
}

int Particula::getTipo() const {
    return tipo;
}

// Métodos set
void Particula::setPos(const Vector2D& pos) {
    this->pos = pos;
}

void Particula::setAcel(const Vector2D& acel) {
    this->acel = acel;
}

void Particula::setVeloc(const Vector2D& veloc) {
    this->veloc = veloc;
}

void Particula::setRadio(float radio) {
    this->radio = radio;
}

// Actualiza la posición de la partícula
void Particula::mover() {
    // 1) Sumar aceleración a velocidad
    veloc.sumar(acel);
    
    // 2) Limitar la velocidad al máximo permitido
    if (veloc.getX() > MAX_VEL) veloc.setX(MAX_VEL);
    if (veloc.getX() < -MAX_VEL) veloc.setX(-MAX_VEL);
    if (veloc.getY() > MAX_VEL) veloc.setY(MAX_VEL);
    if (veloc.getY() < -MAX_VEL) veloc.setY(-MAX_VEL);
    
    // 3) Sumar velocidad a posición
    pos.sumar(veloc);
    
    // Comprobar si la partícula se mantiene dentro del mundo
    if (pos.getX() < 0) pos.setX(0);
    if (pos.getX() > MAX_X) pos.setX(MAX_X);
    if (pos.getY() < 0) pos.setY(0);
    if (pos.getY() > MAX_Y) pos.setY(MAX_Y);
}

// Implementa el rebote contra los bordes del mundo
void Particula::rebotar() {
    // Rebote contra los bordes horizontales
    if (pos.getX() <= 0 || pos.getX() >= MAX_X) {
        veloc.setX(-veloc.getX());
    }
    
    // Rebote contra los bordes verticales
    if (pos.getY() <= 0 || pos.getY() >= MAX_Y) {
        veloc.setY(-veloc.getY());
    }
}

// Detecta colisión con otra partícula
bool Particula::colision(const Particula& otra) const {
    // Calcular la distancia entre los centros de las partículas
    float distancia = pos.distancia(otra.pos);
    
    // Hay colisión si la distancia es menor que la suma de los radios
    return distancia < (radio + otra.radio);
}

// Implementa el choque elástico entre partículas
void Particula::choque(Particula& otra) {
    // Intercambiar velocidades y aceleraciones
    Vector2D tempVeloc = veloc;
    Vector2D tempAcel = acel;
    
    veloc = otra.veloc;
    acel = otra.acel;
    
    otra.veloc = tempVeloc;
    otra.acel = tempAcel;
}

// Representación como string de la partícula
std::string Particula::toString() const {
    std::ostringstream oss;
    oss << "{" << pos.toString() << ", " << veloc.toString() << ", " 
        << acel.toString() << ", " << radio << ", " << tipo << "}";
    return oss.str();
}

/**
 * Implementa el comportamiento de "envolver" la partícula cuando sale del mundo
 * Si la partícula cruza un borde, aparece por el lado opuesto
 * Tiene en cuenta el radio para una transición suave
 */
void Particula::wrap() {
    // Verificar borde derecho
    if (pos.getX() > MAX_X) {
        // Aparece por el borde izquierdo teniendo en cuenta el radio
        pos.setX(0 + radio);
    }
    
    // Verificar borde izquierdo
    if (pos.getX() < 0) {
        // Aparece por el borde derecho teniendo en cuenta el radio
        pos.setX(MAX_X - radio);
    }
    
    // Verificar borde inferior
    if (pos.getY() > MAX_Y) {
        // Aparece por el borde superior teniendo en cuenta el radio
        pos.setY(0 + radio);
    }
    
    // Verificar borde superior
    if (pos.getY() < 0) {
        // Aparece por el borde inferior teniendo en cuenta el radio
        pos.setY(MAX_Y - radio);
    }
}