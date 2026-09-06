# Máximo Subarreglo

Implementación y comparación de tres algoritmos para encontrar la suma máxima de un subarreglo contiguo:

* Solución cúbica `O(n³)`
* Solución cuadrática `O(n²)`
* Algoritmo de Kadane `O(n)`

## Lenguaje y caracteristicas del ordenador

* **Lenguaje:** C++
* **Compilador:** g++
* **Procesador:** AMD Ryzen 7 7735HS
* **Memoria RAM:** 16 GB
* **Sistema operativo:** Windows
* **Estándar:** C++17


## Implementaciones

### 1. Solución cúbica — O(n³)

La solución cúbica considera todos los posibles subarreglos. Para cada uno de ellos, recorre sus elementos y calcula su suma.

Complejidad temporal:

`O(n³)`

### 2. Solución cuadrática — O(n²)

La solución cuadrática considera todos los posibles subarreglos, pero mantiene una suma acumulada mientras recorre el arreglo.

Complejidad temporal:

`O(n²)`

### 3. Algoritmo de Kadane — O(n)

El algoritmo de Kadane recorre el arreglo una sola vez. Mantiene la mejor suma del subarreglo que termina en la posición actual y la mejor suma encontrada hasta ese momento.

Complejidad temporal:

`O(n)`

## Verificación

Se realizaron **1000 pruebas con arreglos generados aleatoriamente**.

Los tamaños utilizados fueron aleatorios entre `1` y `20`, con valores entre `-100` y `100`.

En cada prueba se ejecutaron las tres implementaciones y se compararon sus resultados.

Resultado:

```text
Verificacion correcta.
```

Las tres implementaciones obtuvieron la misma suma máxima en todas las pruebas.

## Mediciones de tiempo

Se utilizaron los siguientes tamaños:

`1000, 2000, 4000, 8000, 16000`

Cada tamaño duplica al anterior.

Los tiempos obtenidos fueron:

|      n | Cúbica (s) | Cuadrática (s) | Kadane (s) |
| -----: | ---------: | -------------: | ---------: |
|  1,000 |     0.6073 |         0.0021 |   0.000024 |
|  2,000 |     5.1510 |         0.0084 |   0.000025 |
|  4,000 |    43.0141 |         0.0305 |   0.000087 |
|  8,000 |   469.8362 |         0.2139 |   0.000332 |
| 16,000 |  4219.3636 |         0.8641 |   0.000486 |
|                                                   |
| Razon  |      x8    |      x4        |      x2    |
| Orden  |   O(n^3)   |    O(n^2)      |     O(n)   |

Los datos de las mediciones se encuentran en `tiempos.csv`.


## Predicción para n = 10⁸

Para estimar el tiempo de ejecución para:

`n = 100,000,000`

se utilizó como referencia la última medición:

`n = 16,000`

La predicción se realizó utilizando la complejidad teórica de cada algoritmo.

| Algoritmo  | Complejidad |         Tiempo estimado | ¿Ejecutar? |
| ---------- | ----------- | ----------------------: | :--------: |
| Cúbica     | `O(n³)`     | 1,030,118,068,237,305 s |     No     |
| Cuadrática | `O(n²)`     |            33,754,250 s |     No     |
| Kadane     | `O(n)`      |                  3.04 s |     Sí     |


