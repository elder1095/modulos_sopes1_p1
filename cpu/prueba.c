#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Esta función ejecuta la instrucción dada y devuelve los datos obtenidos en una cadena
char *ejecutarComando(const char *comando) {
    char *resultado = NULL;
    char buffer[128];
    FILE *pipe = popen(comando, "r");
    
    if (pipe == NULL) {
        perror("Error al ejecutar el comando");
        return NULL;
    }
    
    size_t resultado_len = 0;
    size_t buffer_len;
    
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        buffer_len = strlen(buffer);
        resultado = realloc(resultado, resultado_len + buffer_len + 1);
        
        if (resultado == NULL) {
            perror("Error de asignación de memoria");
            pclose(pipe);
            return NULL;
        }
        
        strcpy(resultado + resultado_len, buffer);
        resultado_len += buffer_len;
    }
    
    pclose(pipe);
    
    return resultado;
}

char *buscarLineaPorUID(uid_t uid) {
    char *resultado = NULL;
    char buffer[128];
    FILE *archivo = fopen("/etc/passwd", "r");
    
    if (archivo == NULL) {
        perror("Error al abrir el archivo /etc/passwd");
        return NULL;
    }
    
    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        // Divide la línea en campos usando ':' como delimitador
        char *token = strtok(buffer, ":");
        if (token != NULL) {
            // El primer campo es el nombre de usuario, el tercer campo es el UID
            char *nombre_usuario = token;
            token = strtok(NULL, ":");
            token = strtok(NULL, ":");
            uid_t uid_encontrado = (uid_t)atoi(token);
            
            // Compara el UID
            if (uid == uid_encontrado) {
                resultado = (char *)malloc(strlen(nombre_usuario) + strlen(token) + 50);
                if (resultado != NULL) {
                    snprintf(resultado, strlen(nombre_usuario) + strlen(token) + 50, "%u - \"%s\"", uid_encontrado, nombre_usuario);
                }
                break; // Se encontró la línea correspondiente al UID, salir del bucle
            }
        }
    }
    
    fclose(archivo);
    
    return resultado;
}

int main() {
    // // Ejemplo de uso: ejecutar el comando y almacenar el resultado en una variable
    // const char *comando = "awk -F: '{print $3, \" - \", $1}' /etc/passwd | sort -n";
    // char *resultado = ejecutarComando(comando);
    
    // if (resultado != NULL) {
    //     printf("Resultado:\n%s", resultado);
    //     free(resultado);
    // }

    uid_t uid = 1000; // El UID que deseas buscar
    char *resultado2 = buscarLineaPorUID(uid);
    
    if (resultado2 != NULL) {
        printf("Resultado:\n%s\n", resultado2);
        free(resultado2);
    } else {
        printf("No se encontró una línea correspondiente al UID: %u\n", uid);
    }
    
    return 0;
}
