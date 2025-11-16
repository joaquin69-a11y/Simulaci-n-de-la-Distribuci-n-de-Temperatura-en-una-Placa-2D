#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100          // tamaño de la malla
#define MAX_ITER 10000 // máximo de iteraciones
#define TOL 1e-4       // tolerancia de convergencia

int main() {
    double u[N][N];
    double u_new[N][N];
    double diff, max_diff;
    int iter, i, j;

    // Inicializar malla en 0
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            u[i][j] = 0.0;
        }
    }

    // Condiciones de frontera (ejemplo)
    for (i = 0; i < N; i++) {
        u[i][0] = 100.0;   // lado izquierdo caliente
        u[i][N-1] = 100.0; // lado derecho caliente
    }

    printf("Iniciando método de Jacobi 2D...\n");

    // Iteraciones
    for (iter = 0; iter < MAX_ITER; iter++) {
        max_diff = 0.0;

        for (i = 1; i < N-1; i++) {
            for (j = 1; j < N-1; j++) {
                u_new[i][j] = 0.25 * (u[i+1][j] + u[i-1][j] + u[i][j+1] + u[i][j-1]);
                diff = fabs(u_new[i][j] - u[i][j]);

                if (diff > max_diff)
                    max_diff = diff;
            }
        }

        // Copiar u_new → u
        for (i = 1; i < N-1; i++) {
            for (j = 1; j < N-1; j++) {
                u[i][j] = u_new[i][j];
            }
        }

        if (iter % 100 == 0)
            printf("Iteración %d, max diff = %f\n", iter, max_diff);

        if (max_diff < TOL) {
            printf("\nConvergencia alcanzada en %d iteraciones.\n", iter);
            break;
        }
    }

    printf("Método completado.\n");
    return 0;
}
