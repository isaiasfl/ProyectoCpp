#include "Vector2D.h"
#include <sstream>
#include <iomanip>

// Constructor
Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

// Métodos get/set
float Vector2D::getX() const {
    return x;
}

float Vector2D::getY() const {
    return y;
}

void Vector2D::setX(float x) {
    this->x = x;
}

void Vector2D::setY(float y) {
    this->y = y;
}

void Vector2D::setXY(float x, float y) {
    this->x = x;
    this->y = y;
}

// Suma otro vector al actual
void Vector2D::sumar(const Vector2D& otro) {
    x += otro.x;
    y += otro.y;
}

// Multiplica el vector por un factor escalar
void Vector2D::escalar(float factor) {
    x *= factor;
    y *= factor;
}

// Calcula el módulo (longitud) del vector
float Vector2D::modulo() const {
    return std::sqrt(x*x + y*y);
}

// Normaliza el vector (lo convierte en vector unitario)
void Vector2D::normalizar() {
    float mod = modulo();
    if (mod > 0) {
        x /= mod;
        y /= mod;
    }
}

// Calcula la distancia euclidea entre este vector y otro
float Vector2D::distancia(const Vector2D& otro) const {
    float dx = x - otro.x;
    float dy = y - otro.y;
    return std::sqrt(dx*dx + dy*dy);
}

// Devuelve una representación en string del vector
std::string Vector2D::toString() const {
    std::ostringstream oss;
    oss << "(" << x << "," << y << ")";
    return oss.str();
}