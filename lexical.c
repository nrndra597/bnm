#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100
#define NUM_KEYWORDS 13


const char *keywords[NUM_KEYWORDS] = {
    "int", "float", "char", "if", "else", "while",
    "for", "return", "void", "break", "continue",
    "double", "long"
};


int isKeyword(const char *str) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}


int isOperator(char ch) {
    char operators[] = "+-*/=%<>&|^!";
    for (int i = 0; operators[i] != '\0'; i++) {
        if (ch == operators[i])
            return 1;
    }
    return 0;
}


int isIdentifier(const char *str) {
    if (!isalpha(str[0]) && str[0] != '_')
        return 0;
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_')
            return 0;
    }
    return 1;
}

int main() {
    FILE *fp;
    char fname[MAX_LEN], ch, buffer[MAX_LEN];
    int i = 0;

    printf("Enter source file name: ");
    scanf("%s", fname);

    fp = fopen(fname, "r");
    if (fp == NULL) {
        printf("Cannot open file.\n");
        return 1;
    }

    printf("\n--- Lexical Analysis Output ---\n");

    while ((ch = fgetc(fp)) != EOF) {
        
        if (isspace(ch) || isOperator(ch) || ch == ';' || ch == ',' || ch == '(' || ch == ')' || ch == '{' || ch == '}') {
            if (i > 0) {
                buffer[i] = '\0';
                if (isKeyword(buffer))
                    printf("[Keyword]    : %s\n", buffer);
                else if (isIdentifier(buffer))
                    printf("[Identifier] : %s\n", buffer);
                i = 0;
            }
            
            if (isOperator(ch))
                printf("[Operator]   : %c\n", ch);
        } else {
            buffer[i++] = ch;
        }
    }

    fclose(fp);
    return 0;
}
