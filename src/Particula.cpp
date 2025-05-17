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
        // Partícula dinámica con valores aleatorios
        // Inicializar la semilla aleatoria si es la primera vez
        static bool primerLlamada = true;
        if (primerLlamada) {
            srand(static_cast<unsigned int>(time(nullptr)));
            primerLlamada = false;
        }
        
        // Posición aleatoria dentro del mundo
        pos.setXY(aleatorio(radio*2, MAX_X - radio*2), aleatorio(radio*2, MAX_Y - radio*2));
        
        // Velocidad aleatoria con valores mínimos garantizados
        float vx = aleatorio(-MAX_VEL, MAX_VEL);
        float vy = aleatorio(-MAX_VEL, MAX_VEL);
        
        // Asegurar un mínimo de velocidad para evitar partículas casi estáticas
        if (std::abs(vx) < 1.0f) vx = (vx >= 0) ? 1.0f : -1.0f;
        if (std::abs(vy) < 1.0f) vy = (vy >= 0) ? 1.0f : -1.0f;
        
        veloc.setXY(vx, vy);
        
        // Aceleración más pequeña o nula para evitar acumulación direccional
        acel.setXY(aleatorio(-MAX_ACC/5.0f, MAX_ACC/5.0f), aleatorio(-MAX_ACC/5.0f, MAX_ACC/5.0f));
        
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
    
    // 2) Aplicar una pequeña fricción para evitar velocidades muy pequeñas
    if (std::abs(veloc.getX()) < FRICCION) veloc.setX(0);
    if (std::abs(veloc.getY()) < FRICCION) veloc.setY(0);
    
    // 3) Limitar la velocidad al máximo permitido
    if (veloc.getX() > MAX_VEL) veloc.setX(MAX_VEL);
    if (veloc.getX() < -MAX_VEL) veloc.setX(-MAX_VEL);
    if (veloc.getY() > MAX_VEL) veloc.setY(MAX_VEL);
    if (veloc.getY() < -MAX_VEL) veloc.setY(-MAX_VEL);
    
    // 4) Sumar velocidad a posición
    pos.sumar(veloc);
}

// Implementa el rebote contra los bordes del mundo
void Particula::rebotar() {
    bool reboteX = false, reboteY = false;
    
    // Verificar rebote en eje X
    if (pos.getX() - radio <= 0) {
        // Rebote desde el borde izquierdo - asegurar velocidad positiva
        float velocidadActual = std::abs(veloc.getX());
        // Asegurar velocidad mínima de rebote
        if (velocidadActual < VELOCIDAD_MIN_REBOTE) velocidadActual = VELOCIDAD_MIN_REBOTE;
        veloc.setX(velocidadActual * FACTOR_REBOTE);
        pos.setX(radio + MARGEN_SEPARACION); // Separar del borde para evitar atascamiento
        reboteX = true;
    } 
    else if (pos.getX() + radio >= MAX_X) {
        // Rebote desde el borde derecho - asegurar velocidad negativa
        float velocidadActual = std::abs(veloc.getX());
        // Asegurar velocidad mínima de rebote
        if (velocidadActual < VELOCIDAD_MIN_REBOTE) velocidadActual = VELOCIDAD_MIN_REBOTE;
        veloc.setX(-velocidadActual * FACTOR_REBOTE);
        pos.setX(MAX_X - radio - MARGEN_SEPARACION); // Separar del borde
        reboteX = true;
    }
    
    // Verificar rebote en eje Y
    if (pos.getY() - radio <= 0) {
        // Rebote desde el borde superior - asegurar velocidad positiva
        float velocidadActual = std::abs(veloc.getY());
        // Asegurar velocidad mínima de rebote
        if (velocidadActual < VELOCIDAD_MIN_REBOTE) velocidadActual = VELOCIDAD_MIN_REBOTE;
        veloc.setY(velocidadActual * FACTOR_REBOTE);
        pos.setY(radio + MARGEN_SEPARACION); // Separar del borde
        reboteY = true;
    } 
    else if (pos.getY() + radio >= MAX_Y) {
        // Rebote desde el borde inferior - asegurar velocidad negativa
        float velocidadActual = std::abs(veloc.getY());
        // Asegurar velocidad mínima de rebote
        if (velocidadActual < VELOCIDAD_MIN_REBOTE) velocidadActual = VELOCIDAD_MIN_REBOTE;
        veloc.setY(-velocidadActual * FACTOR_REBOTE);
        pos.setY(MAX_Y - radio - MARGEN_SEPARACION); // Separar del borde
        reboteY = true;
    }
    
    // Rebote especial para esquinas - si rebotó en ambos ejes a la vez
    if (reboteX && reboteY) {
        // Para una esquina, añadir un impulso adicional para alejarse
        veloc.setX(veloc.getX() * IMPULSO_ESQUINA);
        veloc.setY(veloc.getY() * IMPULSO_ESQUINA);
        
        // También reducir aceleración para evitar que regrese rápidamente
        acel.setX(acel.getX() * 0.5f);
        acel.setY(acel.getY() * 0.5f);
        
        // Aleatorizar ligeramente la dirección para romper patrones cíclicos
        float variacionX = (rand() % 100) / 500.0f; // Pequeña variación aleatoria
        float variacionY = (rand() % 100) / 500.0f;
        
        if (veloc.getX() > 0) veloc.setX(veloc.getX() + variacionX);
        else veloc.setX(veloc.getX() - variacionX);
        
        if (veloc.getY() > 0) veloc.setY(veloc.getY() + variacionY);
        else veloc.setY(veloc.getY() - variacionY);
    }
    
    // Asegurar que las partículas estén dentro de los límites
    if (pos.getX() < radio) pos.setX(radio);
    if (pos.getX() > MAX_X - radio) pos.setX(MAX_X - radio);
    if (pos.getY() < radio) pos.setY(radio);
    if (pos.getY() > MAX_Y - radio) pos.setY(MAX_Y - radio);
    
    // Modificar el manejo de aceleración para evitar que empuje hacia los bordes
    if (reboteX) {
        // Si hubo rebote en X, reducir componente X de aceleración
        acel.setX(acel.getX() * REDUC_ACEL);
        
        // Si es muy pequeña, añadir una aceleración aleatoria en dirección opuesta
        if (std::abs(acel.getX()) < UMBRAL_ACEL) {
            float nuevaAcel = (rand() % 100) / 100.0f * FACTOR_ACEL_ALEATORIA;
            if (pos.getX() < MAX_X/2) 
                acel.setX(nuevaAcel); // Acelerar hacia la derecha si está en la mitad izquierda
            else 
                acel.setX(-nuevaAcel); // Acelerar hacia la izquierda si está en la mitad derecha
        }
    }
    
    if (reboteY) {
        // Si hubo rebote en Y, reducir componente Y de aceleración
        acel.setY(acel.getY() * REDUC_ACEL);
        
        // Si es muy pequeña, añadir una aceleración aleatoria en dirección opuesta
        if (std::abs(acel.getY()) < UMBRAL_ACEL) {
            float nuevaAcel = (rand() % 100) / 100.0f * FACTOR_ACEL_ALEATORIA;
            if (pos.getY() < MAX_Y/2) 
                acel.setY(nuevaAcel); // Acelerar hacia abajo si está en la mitad superior
            else 
                acel.setY(-nuevaAcel); // Acelerar hacia arriba si está en la mitad inferior
        }
    }
}

// Implementa el comportamiento de "envolver" la partícula cuando sale del mundo
void Particula::wrap() {
    // Verificar si ha salido completamente por un borde horizontal
    if (pos.getX() + radio < 0) {
        // Ha salido completamente por la izquierda, aparecer por la derecha
        pos.setX(MAX_X - radio);
    } 
    else if (pos.getX() - radio > MAX_X) {
        // Ha salido completamente por la derecha, aparecer por la izquierda
        pos.setX(radio);
    }
    
    // Verificar si ha salido completamente por un borde vertical
    if (pos.getY() + radio < 0) {
        // Ha salido completamente por arriba, aparecer por abajo
        pos.setY(MAX_Y - radio);
    } 
    else if (pos.getY() - radio > MAX_Y) {
        // Ha salido completamente por abajo, aparecer por arriba
        pos.setY(radio);
    }
    
    // Casos donde parte de la partícula está dentro y parte fuera
    if (pos.getX() - radio < 0 && pos.getX() + radio > 0) {
        pos.setX(MAX_X - (radio - pos.getX()));
    }
    else if (pos.getX() + radio > MAX_X && pos.getX() - radio < MAX_X) {
        pos.setX(radio + (pos.getX() - (MAX_X - radio)));
    }
    
    if (pos.getY() - radio < 0 && pos.getY() + radio > 0) {
        pos.setY(MAX_Y - (radio - pos.getY()));
    }
    else if (pos.getY() + radio > MAX_Y && pos.getY() - radio < MAX_Y) {
        pos.setY(radio + (pos.getY() - (MAX_Y - radio)));
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
    
    // Separar ligeramente las partículas para evitar que queden atascadas
    float distancia = pos.distancia(otra.pos);
    float minDistancia = radio + otra.radio;
    
    if (distancia < minDistancia && distancia > 0) {
        // Calcular vector unitario entre las partículas
        Vector2D dir;
        dir.setX(otra.pos.getX() - pos.getX());
        dir.setY(otra.pos.getY() - pos.getY());
        dir.normalizar();
        
        // Separar las partículas
        float correccion = (minDistancia - distancia) / 2.0f;
        pos.setX(pos.getX() - dir.getX() * correccion);
        pos.setY(pos.getY() - dir.getY() * correccion);
        otra.pos.setX(otra.pos.getX() + dir.getX() * correccion);
        otra.pos.setY(otra.pos.getY() + dir.getY() * correccion);
    }
}

// Representación como string de la partícula
std::string Particula::toString() const {
    std::ostringstream oss;
    oss << "{" << pos.toString() << ", " << veloc.toString() << ", " 
        << acel.toString() << ", " << radio << ", " << tipo << "}";
    return oss.str();
}