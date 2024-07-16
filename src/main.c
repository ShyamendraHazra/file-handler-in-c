#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFFER_ALLOCATED 1
#define BUFFER_DEALLOCATED 0
#define BUFFER_CORRUPTED -1

#define FILE_OPEN 1
#define FILE_CLOSE 0
typedef struct {
    
    char* ptr;
    uint16_t buffer_length;
    int8_t buffer_state;
} BUFFER;

int main() {

    int8_t file_state = FILE_CLOSE;

    char ch;
    
    FILE* file_one;
    
    BUFFER file_one_Buffer;
    file_one_Buffer.ptr = NULL;
    file_one_Buffer.buffer_length = 0;
    file_one_Buffer.buffer_state = BUFFER_DEALLOCATED;

    file_one = fopen("assets/example.txt", "r");

    if(file_one == NULL) {

        printf("Could not open the file!\n");
        exit(EXIT_FAILURE);
    }

    file_state = FILE_OPEN;

    // Reading file content to buffer

    while((ch = fgetc(file_one)) != EOF) {
        
        char* temp;
        
        if (file_one_Buffer.buffer_length == UINT16_MAX) {
            printf("Buffer Limit Reached!\n, skipping rest of the file. Null terminator will be added\n");
            
            if(file_state == FILE_OPEN)
            {
                fclose(file_one);
                file_state = FILE_CLOSE;
            }

            break;
        }

        temp = realloc(file_one_Buffer.ptr, (sizeof(char)*(file_one_Buffer.buffer_length+1)));
        
        if(temp == NULL) {
            printf("Failed to reallocate buffer space! \n");
            if (file_one_Buffer.buffer_state == BUFFER_ALLOCATED) {
                file_one_Buffer.buffer_state = BUFFER_CORRUPTED;
                file_one_Buffer.buffer_length = 0;
            }

            if(file_state == FILE_OPEN)
            {
                fclose(file_one);
                file_state = FILE_CLOSE;
            }

            break;
        }

        file_one_Buffer.buffer_state = BUFFER_ALLOCATED;
        file_one_Buffer.ptr = temp;
        file_one_Buffer.ptr[file_one_Buffer.buffer_length] = ch;
        file_one_Buffer.buffer_length++;

    }


    // Adding null terminator

    char* temp = realloc(file_one_Buffer.ptr, (sizeof(char)*(file_one_Buffer.buffer_length+1)));
        
    if(temp == NULL) {

        printf("Failed to reallocate buffer space for null terminator\n");
        
        if (file_one_Buffer.buffer_state == BUFFER_ALLOCATED) {
            
            file_one_Buffer.buffer_state = BUFFER_CORRUPTED;
            file_one_Buffer.buffer_length = 0;
        }

        if(file_state == FILE_OPEN)
        {
            fclose(file_one);
            file_state = FILE_CLOSE;
        }
    }

    file_one_Buffer.ptr = temp;
    printf("after null terminator buffer length : %d\n",file_one_Buffer.buffer_length);
    file_one_Buffer.ptr[file_one_Buffer.buffer_length] = '\0';


    //  Checking for Invalide or non-printable characters

    for(int i = 0; i < file_one_Buffer.buffer_length; i++) {
        if(!isprint(file_one_Buffer.ptr[i]) && file_one_Buffer.ptr[i] != '\n') {
            printf("Invalid character found at index %d | ASCII =>%d | Char => %c\n", i,file_one_Buffer.ptr[i],file_one_Buffer.ptr[i]);
            if (file_one_Buffer.buffer_state == BUFFER_ALLOCATED) {
                file_one_Buffer.buffer_state = BUFFER_CORRUPTED;
                file_one_Buffer.buffer_length = 0;
            }
            
            if(file_state == FILE_OPEN)
            {
                fclose(file_one);
                file_state = FILE_CLOSE;
            }
            
            break;
        }
    }


    if (file_one_Buffer.buffer_state == BUFFER_ALLOCATED) {

        printf("%s\n\ncharacter count : %d\n",file_one_Buffer.ptr, file_one_Buffer.buffer_length-1);
    }
    
    if(file_state == FILE_OPEN)
    {
        fclose(file_one);
        file_state = FILE_CLOSE;
    }
    
    
    if (file_one_Buffer.buffer_state == BUFFER_ALLOCATED || file_one_Buffer.buffer_state == BUFFER_CORRUPTED) {
        
        free(file_one_Buffer.ptr);
        file_one_Buffer.ptr = NULL;
        file_one_Buffer.buffer_state = BUFFER_DEALLOCATED;
        file_one_Buffer.buffer_length = 0;
    }

    return 0;
}

