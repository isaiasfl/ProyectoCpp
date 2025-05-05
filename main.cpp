#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Vector2D.h"
#include "Particula.h"
#include "ConjuntoParticulas.h"

// Función auxiliar para mostrar separadores en la consola
void mostrarSeparador(const std::string& titulo) {
    std::cout << "\n===== " << titulo << " =====" << std::endl;
}

// Prueba de la clase Vector2D
void probarVector2D() {
    mostrarSeparador("PRUEBA DE VECTOR2D");
    
    // Crear varios vectores
    Vector2D v1;
    Vector2D v2(3.0, 4.0);
    Vector2D v3(-1.0, 2.0);
    
    // Mostrar vectores iniciales
    std::cout << "v1: " << v1.toString() << std::endl;
    std::cout << "v2: " << v2.toString() << std::endl;
    std::cout << "v3: " << v3.toString() << std::endl;
    
    // Probar métodos
    std::cout << "\nMódulo de v2: " << v2.modulo() << std::endl;
    std::cout << "Distancia entre v2 y v3: " << v2.distancia(v3) << std::endl;
    
    // Probar suma
    v1.setXY(1.0, 1.0);
    std::cout << "\nv1 modificado: " << v1.toString() << std::endl;
    v1.sumar(v2);
    std::cout << "v1 + v2: " << v1.toString() << std::endl;
    
    // Probar escalar
    v2.escalar(2.0);
    std::cout << "v2 * 2: " << v2.toString() << std::endl;
    
    // Probar normalizar
    Vector2D v4(5.0, 0.0);
    std::cout << "v4 original: " << v4.toString() << std::endl;
    v4.normalizar();
    std::cout << "v4 normalizado: " << v4.toString() << std::endl;
    std::cout << "Módulo de v4 normalizado: " << v4.modulo() << std::endl;
}

// Prueba de la clase Particula
void probarParticula() {
    mostrarSeparador("PRUEBA DE PARTICULA");
    
    // Crear partículas
    Particula p1;  // Partícula aleatoria
    Particula p2(1);  // Partícula estática
    
    Vector2D pos(100, 100);
    Vector2D vel(2, 3);
    Vector2D ace(0.1, 0.2);
    Particula p3(pos, ace, vel, 5.0, 2);  // Partícula con valores específicos
    
    // Mostrar partículas
    std::cout << "p1 (aleatoria): " << p1.toString() << std::endl;
    std::cout << "p2 (estática): " << p2.toString() << std::endl;
    std::cout << "p3 (personalizada): " << p3.toString() << std::endl;
    
    // Probar mover
    std::cout << "\nMoviendo p3..." << std::endl;
    p3.mover();
    std::cout << "p3 después de mover: " << p3.toString() << std::endl;
    
    // Probar rebotar
    std::cout << "\nRebotando p3..." << std::endl;
    p3.rebotar();
    std::cout << "p3 después de rebotar: " << p3.toString() << std::endl;
    
    // Probar wrap
    std::cout << "\nHaciendo wrap de p3..." << std::endl;
    // Primero la llevamos a un borde
    p3.setPos(Vector2D(MAX_X + 10, p3.getPos().getY()));
    std::cout << "p3 fuera del borde: " << p3.toString() << std::endl;
    p3.wrap();
    std::cout << "p3 después de wrap: " << p3.toString() << std::endl;
    
    // Probar colisión
    Particula p4(Vector2D(102, 102), Vector2D(0, 0), Vector2D(0, 0), 5.0, 3);
    std::cout << "\nComprobando colisión entre p3 y p4:" << std::endl;
    std::cout << "p3: " << p3.toString() << std::endl;
    std::cout << "p4: " << p4.toString() << std::endl;
    if (p3.colision(p4)) {
        std::cout << "¡Colisión detectada!" << std::endl;
        std::cout << "Chocando partículas..." << std::endl;
        p3.choque(p4);
        std::cout << "p3 después del choque: " << p3.toString() << std::endl;
        std::cout << "p4 después del choque: " << p4.toString() << std::endl;
    } else {
        std::cout << "No hay colisión." << std::endl;
    }
}

// Prueba de la clase ConjuntoParticulas
void probarConjuntoParticulas() {
    mostrarSeparador("PRUEBA DE CONJUNTOPARTICULAS");
    
    // Crear conjuntos
    ConjuntoParticulas conjunto1;  // Conjunto vacío
    ConjuntoParticulas conjunto2(5);  // Conjunto con 5 partículas aleatorias
    
    // Mostrar conjuntos
    std::cout << "Conjunto1 (vacío):" << std::endl;
    std::cout << conjunto1.toString() << std::endl;
    
    std::cout << "Conjunto2 (5 partículas aleatorias):" << std::endl;
    std::cout << conjunto2.toString() << std::endl;
    
    // Probar agregar
    std::cout << "\nAgregando partículas al conjunto1..." << std::endl;
    Particula p1(Vector2D(50, 50), Vector2D(0.5, 0.5), Vector2D(1, 1), 4.0, 10);
    conjunto1.agregar(p1);
    conjunto1.agregar(Particula(Vector2D(100, 100), Vector2D(0, 0), Vector2D(2, -2), 5.0, 20));
    std::cout << "Conjunto1 después de agregar:" << std::endl;
    std::cout << conjunto1.toString() << std::endl;
    
    // Probar borrar
    std::cout << "\nBorrando la partícula en posición 0 del conjunto2..." << std::endl;
    conjunto2.borrar(0);
    std::cout << "Conjunto2 después de borrar:" << std::endl;
    std::cout << conjunto2.toString() << std::endl;
    
    // Probar obtener y reemplazar
    if (conjunto1.getUtiles() > 0) {
        std::cout << "\nObteniendo la partícula 0 del conjunto1:" << std::endl;
        Particula& p = conjunto1.obtener(0);
        std::cout << "Partícula obtenida: " << p.toString() << std::endl;
        
        std::cout << "Reemplazando la partícula 0 con una nueva..." << std::endl;
        Particula nueva(Vector2D(200, 200), Vector2D(0, 0), Vector2D(0, 0), 6.0, 30);
        conjunto1.reemplazar(0, nueva);
        std::cout << "Conjunto1 después de reemplazar:" << std::endl;
        std::cout << conjunto1.toString() << std::endl;
    }
    
    // Probar mover
    std::cout << "\nMoviendo las partículas del conjunto1 (tipo 0)..." << std::endl;
    conjunto1.mover(0);
    std::cout << "Conjunto1 después de mover:" << std::endl;
    std::cout << conjunto1.toString() << std::endl;
    
    // Probar mover con rebote
    std::cout << "\nMoviendo las partículas del conjunto1 con rebote (tipo 1)..." << std::endl;
    conjunto1.mover(1);
    std::cout << "Conjunto1 después de mover con rebote:" << std::endl;
    std::cout << conjunto1.toString() << std::endl;
    
    // Probar mover con wrap
    std::cout << "\nMoviendo las partículas del conjunto1 con wrap (tipo 2)..." << std::endl;
    conjunto1.mover(2);
    std::cout << "Conjunto1 después de mover con wrap:" << std::endl;
    std::cout << conjunto1.toString() << std::endl;
    
    // Probar gestionar colisiones
    std::cout << "\nCreando un conjunto con partículas cercanas para probar colisiones..." << std::endl;
    ConjuntoParticulas conjuntoColision;
    conjuntoColision.agregar(Particula(Vector2D(100, 100), Vector2D(0, 0), Vector2D(1, 0), 5.0, 1));
    conjuntoColision.agregar(Particula(Vector2D(109, 100), Vector2D(0, 0), Vector2D(-1, 0), 5.0, 2));
    std::cout << "Conjunto de colisión inicial:" << std::endl;
    std::cout << conjuntoColision.toString() << std::endl;
    
    std::cout << "Moviendo partículas..." << std::endl;
    conjuntoColision.mover(0);
    std::cout << "Después de mover:" << std::endl;
    std::cout << conjuntoColision.toString() << std::endl;
    
    std::cout << "Gestionando colisiones..." << std::endl;
    conjuntoColision.gestionarColisiones();
    std::cout << "Después de gestionar colisiones:" << std::endl;
    std::cout << conjuntoColision.toString() << std::endl;
    
    // Probar constructor de copia
    std::cout << "\nCreando una copia del conjunto1..." << std::endl;
    ConjuntoParticulas copia(conjunto1);
    std::cout << "Copia del conjunto1:" << std::endl;
    std::cout << copia.toString() << std::endl;
}

int main(int argc, char *argv[]) {
    // Inicializar generador de números aleatorios
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Ejecutar pruebas
    probarVector2D();
    probarParticula();
    probarConjuntoParticulas();
    
    return 0;
}