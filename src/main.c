#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* ptr;
    uint16_t buffer_length;
} BUFFER;

int main() {

    char ch;
    FILE* file_one;
    BUFFER file_one_Buffer;
    file_one_Buffer.ptr = NULL;
    file_one_Buffer.buffer_length = 0;
    file_one = fopen("assets/example.txt", "r");

    if(file_one == NULL) {

        printf("Could not open the file!\n");
        exit(EXIT_FAILURE);
    }

    while((ch = fgetc(file_one)) != EOF) {
        
        char* temp;
        
        temp = realloc(file_one_Buffer.ptr, (sizeof(char)*file_one_Buffer.buffer_length+1));
        
        if(temp == NULL) {
            printf("Failed to reallocate buffer space\n");
            free(file_one_Buffer.ptr);
            fclose(file_one);
            exit(EXIT_FAILURE);
        }

        file_one_Buffer.ptr = temp;
        file_one_Buffer.buffer_length++;

        file_one_Buffer.ptr[file_one_Buffer.buffer_length-1] = ch;
    }

    for(int i = 0; i < file_one_Buffer.buffer_length; i++) {
        if(!isprint(file_one_Buffer.ptr[i])) {
            printf("Invalid character found: %c\n", file_one_Buffer.ptr[i]);
            free(file_one_Buffer.ptr);
            file_one_Buffer.buffer_length = 0;
            fclose(file_one);
            exit(EXIT_FAILURE);
        }
    }

    char* temp = realloc(file_one_Buffer.ptr, (sizeof(char)*file_one_Buffer.buffer_length+1));
        
    if(temp == NULL) {
        printf("Failed to reallocate buffer space\n");
        free(file_one_Buffer.ptr);
        fclose(file_one);
        exit(EXIT_FAILURE);
    }

    file_one_Buffer.ptr = temp;
    file_one_Buffer.buffer_length++;

    file_one_Buffer.ptr[file_one_Buffer.buffer_length-1] = '\0';

    printf("%s",file_one_Buffer.ptr);
    fclose(file_one);
    free(file_one_Buffer.ptr);
    file_one_Buffer.buffer_length  = 0;
    printf("\n");

    return 0;
}

