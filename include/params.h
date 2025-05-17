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

// Parámetros para el rebote de partículas
const float FACTOR_REBOTE = 1.2f;      // Factor multiplicador para la velocidad tras rebote
const float VELOCIDAD_MIN_REBOTE = 1.5f; // Velocidad mínima tras rebote
const float MARGEN_SEPARACION = 0.5f;  // Distancia para separar del borde tras rebote
const float IMPULSO_ESQUINA = 1.1f;    // Impulso adicional al rebotar en esquinas
const float REDUC_ACEL = 0.7f;         // Factor de reducción de aceleración tras rebote
const float UMBRAL_ACEL = 0.05f;       // Umbral para considerar aceleración significativa
const float FACTOR_ACEL_ALEATORIA = 0.1f; // Factor para nueva aceleración aleatoria


// Función para generar números aleatorios en un rango min y max
inline float aleatorio(float min, float max) {
    float r = rand() / static_cast<float>(RAND_MAX);
    float rango = max - min;
    return (r * rango + min);
}

#endif // PARAMS_H