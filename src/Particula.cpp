#include "Particula.h"
#include <sstream>
#include <cmath>

// Constructor con valor por defecto
Particula::Particula(int tipoPart) : tipo(tipoPart) {
    if (tipoPart != 0) {
        // Partícula estática
        pos.setXY(0, 0);
        acel.setXY(0, 0);
        veloc.setXY(0, 0);
        radio = 3.0f;
    } else {
        
        // Posición aleatoria dentro del mundo
        pos.setXY(aleatorio(radio*2, MAX_X - radio*2), aleatorio(radio*2, MAX_Y - radio*2));
        
        // Velocidad aleatoria con valores mínimos garantizados
        float vx = aleatorio(-MAX_VEL, MAX_VEL);
        float vy = aleatorio(-MAX_VEL, MAX_VEL);
        
        // Asegurar un mínimo de velocidad para evitar partículas casi estáticas
        if (std::abs(vx) < 1.0f) vx = (vx >= 0) ? 1.0f : -1.0f;
        if (std::abs(vy) < 1.0f) vy = (vy >= 0) ? 1.0f : -1.0f;
        
        veloc.setXY(vx, vy);
        
        // Inicializar con aceleración cero para evitar que las partículas se frenen
        acel.setXY(0.0f, 0.0f);
        
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
}

// Implementa el rebote contra los bordes del mundo
void Particula::rebotar() {
    // Verificar rebote en eje X
    if (pos.getX() - radio <= 0 || pos.getX() + radio >= MAX_X) {
        // Cambiar el signo de la velocidad en X (manteniendo la magnitud)
        veloc.setX(-veloc.getX());
        
        // Asegurar que la partícula no quede fuera de los límites
        if (pos.getX() - radio < 0) {
            pos.setX(radio);
        } else if (pos.getX() + radio > MAX_X) {
            pos.setX(MAX_X - radio);
        }
    }
    
    // Verificar rebote en eje Y
    if (pos.getY() - radio <= 0 || pos.getY() + radio >= MAX_Y) {
        // Cambiar el signo de la velocidad en Y (manteniendo la magnitud)
        veloc.setY(-veloc.getY());
        
        // Asegurar que la partícula no quede fuera de los límites
        if (pos.getY() - radio < 0) {
            pos.setY(radio);
        } else if (pos.getY() + radio > MAX_Y) {
            pos.setY(MAX_Y - radio);
        }
    }
}

// Implementa el comportamiento de "envolver" la partícula cuando sale del mundo
void Particula::wrap() {
    // Verificar si la partícula ha salido por un borde horizontal y hacer que aparezca por el lado opuesto
    if (pos.getX() + radio < 0) {
        // Ha salido completamente por la izquierda, aparecer por la derecha
        // Teniendo en cuenta el radio para que la partícula aparezca justo entrando por el borde derecho
        pos.setX(MAX_X - radio);
    } 
    else if (pos.getX() - radio > MAX_X) {
        // Ha salido completamente por la derecha, aparecer por la izquierda
        // Teniendo en cuenta el radio para que la partícula aparezca justo entrando por el borde izquierdo
        pos.setX(radio);
    }
    
    // Verificar si la partícula ha salido por un borde vertical y hacer que aparezca por el lado opuesto
    if (pos.getY() + radio < 0) {
        // Ha salido completamente por arriba, aparecer por abajo
        // Teniendo en cuenta el radio para que la partícula aparezca justo entrando por el borde inferior
        pos.setY(MAX_Y - radio);
    } 
    else if (pos.getY() - radio > MAX_Y) {
        // Ha salido completamente por abajo, aparecer por arriba
        // Teniendo en cuenta el radio para que la partícula aparezca justo entrando por el borde superior
        pos.setY(radio);
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
    // Intercambiar velocidades y aceleraciones (choque elástico con masas iguales)
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