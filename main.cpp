#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;
using namespace std::chrono;

int maxSubarrayCubico(const vector<int>& A) {
    int n = A.size();
    int mejor = A[0];

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int suma = 0;

            for (int k = i; k <= j; k++) {
                suma += A[k];
            }

            if (suma > mejor) {
                mejor = suma;
            }
        }
    }

    return mejor;
}

int maxSubarrayCuadratico(const vector<int>& A) {
    int n = A.size();
    int mejor = A[0];

    for (int i = 0; i < n; i++) {
        int suma = 0;

        for (int j = i; j < n; j++) {
            suma += A[j];

            if (suma > mejor) {
                mejor = suma;
            }
        }
    }

    return mejor;
}

int maxSubarrayKadane(const vector<int>& A) {
    int actual = A[0];
    int mejor = A[0];

    for (int i = 1; i < A.size(); i++) {
        if (actual + A[i] > A[i]) {
            actual = actual + A[i];
        } else {
            actual = A[i];
        }

        if (actual > mejor) {
            mejor = actual;
        }
    }

    return mejor;
}

vector<int> generarArreglo(int n) {
    vector<int> A(n);

    for (int i = 0; i < n; i++) {
        A[i] = rand() % 201 - 100;
    }

    return A;
}

bool verificarAlgoritmos() {
    for (int prueba = 1; prueba <= 1000; prueba++) {
        int n = rand() % 20 + 1;

        vector<int> A = generarArreglo(n);

        int r1 = maxSubarrayCubico(A);
        int r2 = maxSubarrayCuadratico(A);
        int r3 = maxSubarrayKadane(A);

        if (r1 != r2 || r2 != r3) {
            cout << "\nError en la prueba " << prueba << "\n";
            return false;
        }
    }

    return true;
}

double medirCubico(const vector<int>& A) {
    auto inicio = high_resolution_clock::now();

    int resultado = maxSubarrayCubico(A);

    auto fin = high_resolution_clock::now();

    return duration<double>(fin - inicio).count();
}

double medirCuadratico(const vector<int>& A) {
    auto inicio = high_resolution_clock::now();

    int resultado = maxSubarrayCuadratico(A);

    auto fin = high_resolution_clock::now();

    return duration<double>(fin - inicio).count();
}

double medirKadane(const vector<int>& A) {
    auto inicio = high_resolution_clock::now();

    int resultado = maxSubarrayKadane(A);

    auto fin = high_resolution_clock::now();

    return duration<double>(fin - inicio).count();
}

struct ResultadoMedicion {
    int n;
    double cubica;
    double cuadratica;
    double kadane;
    double razonCubica;
    double razonCuadratica;
    double razonKadane;
};

string formatearTiempo(double segundos) {
    stringstream salida;

    if (segundos >= 1.0) {
        if (segundos >= 100.0) {
            salida << fixed << setprecision(0) << segundos << " s";
        } else if (segundos >= 10.0) {
            salida << fixed << setprecision(1) << segundos << " s";
        } else {
            salida << fixed << setprecision(2) << segundos << " s";
        }
    } else if (segundos >= 0.001) {
        double milisegundos = segundos * 1000;

        if (milisegundos >= 100.0) {
            salida << fixed << setprecision(0) << milisegundos << " ms";
        } else if (milisegundos >= 10.0) {
            salida << fixed << setprecision(1) << milisegundos << " ms";
        } else {
            salida << fixed << setprecision(2) << milisegundos << " ms";
        }
    } else {
        double microsegundos = segundos * 1000000;

        if (microsegundos >= 100.0) {
            salida << fixed << setprecision(0) << microsegundos << " us";
        } else if (microsegundos >= 10.0) {
            salida << fixed << setprecision(1) << microsegundos << " us";
        } else {
            salida << fixed << setprecision(2) << microsegundos << " us";
        }
    }

    return salida.str();
}

string formatearN(int n) {
    string numero = to_string(n);
    string resultado;
    int contador = 0;

    for (int i = numero.size() - 1; i >= 0; i--) {
        resultado = numero[i] + resultado;
        contador++;

        if (contador == 3 && i != 0) {
            resultado = " " + resultado;
            contador = 0;
        }
    }

    return resultado;
}

void imprimirTabla(const vector<ResultadoMedicion>& resultados) {
    cout << "\n";
    cout << "===============================================================\n";
    cout << "                    MAXIMO SUBARREGLO\n";
    cout << "===============================================================\n\n";

    cout << left
         << setw(12) << "n"
         << setw(18) << "Cubica"
         << setw(20) << "Cuadratica"
         << setw(18) << "Kadane"
         << "\n";

    cout << "---------------------------------------------------------------\n";

    for (int i = 0; i < resultados.size(); i++) {
        cout << left
             << setw(12) << formatearN(resultados[i].n)
             << setw(18) << formatearTiempo(resultados[i].cubica)
             << setw(20) << formatearTiempo(resultados[i].cuadratica)
             << setw(18) << formatearTiempo(resultados[i].kadane)
             << "\n";
    }

    cout << "\n";

    cout << left
         << setw(12) << "Razon"
         << setw(18) << "x8"
         << setw(20) << "x4"
         << setw(18) << "x2"
         << "\n";

    cout << left
         << setw(12) << "Orden"
         << setw(18) << "O(n^3)"
         << setw(20) << "O(n^2)"
         << setw(18) << "O(n)"
         << "\n";

    cout << "===============================================================\n";
}

void guardarCSV(const vector<ResultadoMedicion>& resultados) {
    ofstream archivo("tiempos.csv");

    if (!archivo.is_open()) {
        cout << "\nNo se pudo crear tiempos.csv\n";
        return;
    }

    archivo << "n,cubica_s,cuadratica_s,kadane_s\n";

    archivo << fixed << setprecision(9);

    for (int i = 0; i < resultados.size(); i++) {
        archivo
            << resultados[i].n << ","
            << resultados[i].cubica << ","
            << resultados[i].cuadratica << ","
            << resultados[i].kadane
            << "\n";
    }

    archivo.close();

    cout << "\nResultados guardados en tiempos.csv\n";
}

double predecir(double tiempoBase, int nBase, int nObjetivo, int grado) {
    double factor = (double)nObjetivo / nBase;

    return tiempoBase * pow(factor, grado);
}

void mostrarPredicciones(const vector<ResultadoMedicion>& resultados) {
    if (resultados.empty()) {
        return;
    }

    ResultadoMedicion ultimo = resultados[resultados.size() - 1];

    int nObjetivo = 100000000;

    double prediccionCubica =
        predecir(
            ultimo.cubica,
            ultimo.n,
            nObjetivo,
            3
        );

    double prediccionCuadratica =
        predecir(
            ultimo.cuadratica,
            ultimo.n,
            nObjetivo,
            2
        );

    double prediccionKadane =
        predecir(
            ultimo.kadane,
            ultimo.n,
            nObjetivo,
            1
        );

    cout << "\n";
    cout << "===============================================================\n";
    cout << "              PREDICCION PARA n = 10^8\n";
    cout << "===============================================================\n\n";

    cout << "Referencia: n = "
         << formatearN(ultimo.n)
         << "\n\n";

    cout << left
         << setw(18) << "Algoritmo"
         << setw(20) << "Prediccion"
         << setw(20) << "Ejecutar"
         << "\n";

    cout << "---------------------------------------------------------------\n";

    cout << left
         << setw(18) << "Cubica"
         << setw(20) << formatearTiempo(prediccionCubica)
         << setw(20) << (prediccionCubica < 60 ? "SI" : "NO")
         << "\n";

    cout << left
         << setw(18) << "Cuadratica"
         << setw(20) << formatearTiempo(prediccionCuadratica)
         << setw(20) << (prediccionCuadratica < 60 ? "SI" : "NO")
         << "\n";

    cout << left
         << setw(18) << "Kadane"
         << setw(20) << formatearTiempo(prediccionKadane)
         << setw(20) << (prediccionKadane < 60 ? "SI" : "NO")
         << "\n";

    cout << "===============================================================\n";
}

int main() {
    srand(time(0));

    cout << "===============================================================\n";
    cout << "                    MAXIMO SUBARREGLO\n";
    cout << "===============================================================\n";

    cout << "\nVerificando implementaciones...\n";

    if (!verificarAlgoritmos()) {
        cout << "La verificacion fallo.\n";
        return 1;
    }

    cout << "Verificacion correcta.\n";

    vector<int> tamanos = {
        1000,
        2000,
        4000,
        8000,
        16000
    };

    vector<ResultadoMedicion> resultados;

    double anteriorCubica = -1;
    double anteriorCuadratica = -1;
    double anteriorKadane = -1;

    for (int i = 0; i < tamanos.size(); i++) {
        int n = tamanos[i];

        cout << "\nMidiendo n = "
             << formatearN(n)
             << "...\n";

        vector<int> A = generarArreglo(n);

        ResultadoMedicion r;

        r.n = n;

        r.cubica = medirCubico(A);
        r.cuadratica = medirCuadratico(A);
        r.kadane = medirKadane(A);

        if (anteriorCubica > 0) {
            r.razonCubica = r.cubica / anteriorCubica;
        } else {
            r.razonCubica = -1;
        }

        if (anteriorCuadratica > 0) {
            r.razonCuadratica = r.cuadratica / anteriorCuadratica;
        } else {
            r.razonCuadratica = -1;
        }

        if (anteriorKadane > 0) {
            r.razonKadane = r.kadane / anteriorKadane;
        } else {
            r.razonKadane = -1;
        }

        resultados.push_back(r);

        anteriorCubica = r.cubica;
        anteriorCuadratica = r.cuadratica;
        anteriorKadane = r.kadane;
    }

    imprimirTabla(resultados);

    guardarCSV(resultados);

    mostrarPredicciones(resultados);

    cout << "\n";
    cout << "Programa finalizado.\n";

    return 0;
}