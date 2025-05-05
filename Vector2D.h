#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <string>
#include <cmath>

class Vector2D {
private:
    float x, y;

public:
    // Constructor con valores por defecto
    Vector2D(float x = 0.0f, float y = 0.0f);
    
    // Métodos get/set
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
    void setXY(float x, float y);
    
    // Operaciones con vectores
    void sumar(const Vector2D& otro);
    void escalar(float factor);
    float modulo() const;
    void normalizar();
    float distancia(const Vector2D& otro) const;
    
    // Representación como string
    std::string toString() const;
};

#endif // VECTOR2D_H

