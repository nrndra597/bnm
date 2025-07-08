#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000


void runLengthEncode(char *input, char *output) {
    int count, i, j = 0;
    int len = strlen(input);

    for (i = 0; i < len; i++) {
        count = 1;
        
        while (i + 1 < len && input[i] == input[i + 1]) {
            count++;
            i++;
        }
        
        output[j++] = input[i];
        
        if (count > 1) {
            
            j += sprintf(&output[j], "%d", count);
        }
    }
    output[j] = '\0'; 
}

int main() {
    char input[MAX_LEN];
    char output[MAX_LEN * 2]; 

    printf("Enter the string to compress (max %d chars): ", MAX_LEN - 1);
    fgets(input, MAX_LEN, stdin);

    
    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    runLengthEncode(input, output);

    printf("Original string: %s\n", input);
    printf("RLE compressed string: %s\n", output);

    return 0;
}
