#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    char ch;
    char buffer[100];

   
    fp = fopen("example.txt", "w"); 
    if (fp == NULL) {
        printf("Error creating file.\n");
        exit(1);
    }
    fprintf(fp, "Hello, this is a file handling demo in C.\n");
    fprintf(fp, "This is a new line.\n");
    fclose(fp); 

    
    fp = fopen("example.txt", "a"); 
    if (fp == NULL) {
        printf("Error opening file for appending.\n");
        exit(1);
    }
    fprintf(fp, "This line is appended.\n");
    fclose(fp);

   
    fp = fopen("example.txt", "r"); 
    if (fp == NULL) {
        printf("Error opening file for reading.\n");
        exit(1);
    }
    printf("File content:\n");
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    fclose(fp);

    return 0;
}
