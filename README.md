# Simulación de la Distribución de Temperatura en una Placa 2D  
### Método de Jacobi — Implementación Secuencial

Este proyecto implementa una simulación numérica de la distribución de temperatura en una placa bidimensional utilizando el **método iterativo de Jacobi**.  
Actualmente el repositorio contiene la **versión secuencial**, la cual será extendida posteriormente con una versión **paralela usando MPI**.

---

## 1. Fundamento Teórico

La ecuación del calor en estado estacionario en 2D se aproxima mediante diferencias finitas:

```math
T_{i,j}^{(k+1)} = \frac{1}{4}\left(
T_{i+1,j}^{(k)} +
T_{i-1,j}^{(k)} +
T_{i,j+1}^{(k)} +
T_{i,j-1}^{(k)}
\right)
```

El método consiste en:

1. Aproximar la placa como una malla 2D.  
2. Aplicar condiciones de frontera (bordes).  
3. Actualizar cada celda como el promedio de sus vecinos.  
4. Repetir hasta que la diferencia entre iteraciones sea menor que una tolerancia.

---

## 2. Estructura del Proyecto
Simulacion-de-la-Distribucion-de-Temperatura-en-una-Placa-2D/
```
  ->src/
    ->jacobi_secuencial.c # Implementación secuencial del método de Jacobi

  ->.gitignore # Ignora ejecutables, .o, build/, dist/

  ->README.md # Documentación del proyecto
```

---

## 3. Cómo Compilar

Desde la carpeta `src/`:

gcc jacobi_secuencial.c -o jacobi

---

## 4. Cómo Ejecutar

./jacobi


El programa mostrará:

- Número de iteraciones
- Error final
- Tiempo de ejecución
- Estado final de la malla
