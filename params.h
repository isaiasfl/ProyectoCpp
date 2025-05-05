#ifndef PARAMS_H
#define PARAMS_H

// Dimensiones del mundo
const int MAX_X = 600;
const int MAX_Y = 600;

// Límites de velocidad y aceleración
const int MAX_VEL = 7;
const float MAX_ACC = 2.0;

// Valores para el radio
const float RADIO = 3.0;
const float MIN_R = 3.0;
const float MAX_R = 7.0;

// Valor de tolerancia
const float EPSILON = 0.01;

// Función para generar números aleatorios en un rango
inline float aleatorio(float min, float max) {
    float r = rand() / static_cast<float>(RAND_MAX);
    float rango = max - min;
    return (r * rango + min);
}

#endif // PARAMS_H