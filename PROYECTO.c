#include <stdio.h>

// Definiciones recomendadas para limitar el alcance
#define NUM_EQUIPOS 4
#define NUM_EVENTOS 4
#define TOTAL_LOGS 12
#define UMBRAL_X 3 // Umbral fijo de la regla de detección

// Prototipos de funciones
int esEventoValido(int evento);          // 4.3 Paso por valor
void registrarEvento(int *contador);     // 4.4 Paso por referencia

int main() {
    // 4.1 Arreglos unidimensionales (Secuencia de eventos)
    // Equipos: 0 a 3 (Representan PC-01 a PC-04)
    int log_equipos[TOTAL_LOGS] = {0, 1, 1, 2, 0, 1, 3, 3, 1, 0, 2, 1};
    // Eventos: 0=Correcto, 1=Pass Incorrecta, 2=Usuario Inexistente, 3=Bloqueado
    int log_eventos[TOTAL_LOGS] = {0, 1, 1, 2, 0, 1, 2, 2, 2, 3, 0, 1}; 

    // 4.2 Arreglo bidimensional (Equipos x Tipos de evento) inicializado en 0
    int matriz[NUM_EQUIPOS][NUM_EVENTOS] = {0};
    int *ptr_matriz = &matriz[0][0]; // 4.5 Uso de apuntadores

    // Procesamiento de logs
    for (int i = 0; i < TOTAL_LOGS; i++) {
        int equipo = log_equipos[i];
        int evento = log_eventos[i];

        if (esEventoValido(evento)) { 
            // 4.5 Aritmética de apuntadores para ubicar la celda exacta
            int *celda = ptr_matriz + (equipo * NUM_EVENTOS) + evento;
            registrarEvento(celda); 
        }
    }

    // Impresión del log original
    printf("--- LOG DE EVENTOS ORIGINAL ---\n");
    for (int i = 0; i < TOTAL_LOGS; i++) {
        printf("Log %d -> Equipo: PC-%02d | Evento ID: %d\n", i+1, log_equipos[i]+1, log_eventos[i]);
    }

    // 4.6 Aplicación de la regla de detección y salida
    printf("\n--- REPORTE DE EQUIPOS (Umbral X=%d) ---\n", UMBRAL_X);
    for (int i = 0; i < NUM_EQUIPOS; i++) {
        // Sumar intentos fallidos: Contraseña incorrecta (Col 1) + Usuario inexistente (Col 2)
        int intentos_fallidos = matriz[i][1] + matriz[i][2];
        
        printf("PC-%02d: ", i + 1);
        if (intentos_fallidos > UMBRAL_X) {
            printf("SOSPECHOSO (Intentos fallidos: %d)\n", intentos_fallidos);
        } else {
            printf("Normal (Intentos fallidos: %d)\n", intentos_fallidos);
        }
    }

    return 0;
}

// Implementación de 4.3 (Paso por valor)
int esEventoValido(int evento) {
    return (evento >= 0 && evento < NUM_EVENTOS);
}

// Implementación de 4.4 (Paso por referencia)
void registrarEvento(int *contador) {
    (*contador)++; 
}
