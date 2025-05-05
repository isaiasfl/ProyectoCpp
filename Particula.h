#ifndef PARTICULA_H
#define PARTICULA_H

#include "Vector2D.h"
#include "params.h"
#include <string>
#include <cstdlib>
#include <ctime>

class Particula {
private:
    Vector2D pos;   // posición
    Vector2D acel;  // aceleración
    Vector2D veloc; // velocidad
    float radio;
    int tipo;

public:
    
    void wrap();

    // Constructor con valor por defecto
    Particula(int tipoPart = 0);
    
    // Constructor con parámetros
    Particula(const Vector2D& pos, const Vector2D& acel, const Vector2D& veloc, float radio, int tipo);
    
    // Métodos get/set
    Vector2D getPos() const;
    Vector2D getAcel() const;
    Vector2D getVeloc() const;
    float getRadio() const;
    int getTipo() const;
    
    void setPos(const Vector2D& pos);
    void setAcel(const Vector2D& acel);
    void setVeloc(const Vector2D& veloc);
    void setRadio(float radio);
    
    // Métodos de movimiento y colisión
    void mover();
    void rebotar();
    bool colision(const Particula& otra) const;
    void choque(Particula& otra);
    
    // Representación como string
    std::string toString() const;
};

#endif // PARTICULA_H