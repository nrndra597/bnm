#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 100


const char *keywords[] = {
    "int", "float", "char", "double", "if", "else", "while",
    "for", "return", "void", "break", "continue", "do"
};
const int keyword_count = sizeof(keywords) / sizeof(keywords[0]);


int isKeyword(const char *str) {
    for (int i = 0; i < keyword_count; i++) {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }
    return 0;
}


int isOperator(char ch) {
    char operators[] = "+-*/%=<>!&|^";
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


int isNumber(const char *str) {
    int i = 0;
    if (str[0] == '-' || str[0] == '+') i = 1;
    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i]))
            return 0;
    }
    return i > 0; 
}

int main() {
    char filename[100];
    printf("Enter input C source file name: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file.\n");
        return 1;
    }

    char ch;
    char token[MAX_TOKEN_LEN];
    int tokenIndex = 0;

    printf("\n--- Lexical Analysis Output ---\n");

    while ((ch = fgetc(fp)) != EOF) {
        
        if (isspace(ch)) {
            if (tokenIndex > 0) {
                token[tokenIndex] = '\0';

                if (isKeyword(token))
                    printf("Keyword: %s\n", token);
                else if (isNumber(token))
                    printf("Constant: %s\n", token);
                else if (isIdentifier(token))
                    printf("Identifier: %s\n", token);
                else
                    printf("Unknown token: %s\n", token);

                tokenIndex = 0;
            }
            continue;
        }

        
        if (isOperator(ch) || strchr(";,(){}[]", ch)) {
            if (tokenIndex > 0) {
                token[tokenIndex] = '\0';

                if (isKeyword(token))
                    printf("Keyword: %s\n", token);
                else if (isNumber(token))
                    printf("Constant: %s\n", token);
                else if (isIdentifier(token))
                    printf("Identifier: %s\n", token);
                else
                    printf("Unknown token: %s\n", token);

                tokenIndex = 0;
            }
            
            if (isOperator(ch))
                printf("Operator: %c\n", ch);
            else
                printf("Punctuation: %c\n", ch);
            continue;
        }

        
        token[tokenIndex++] = ch;
        if (tokenIndex >= MAX_TOKEN_LEN - 1) {
            
            token[tokenIndex] = '\0';
            printf("Token too long: %s\n", token);
            tokenIndex = 0;
        }
    }

    
    if (tokenIndex > 0) {
        token[tokenIndex] = '\0';
        if (isKeyword(token))
            printf("Keyword: %s\n", token);
        else if (isNumber(token))
            printf("Constant: %s\n", token);
        else if (isIdentifier(token))
            printf("Identifier: %s\n", token);
        else
            printf("Unknown token: %s\n", token);
    }

    fclose(fp);
    return 0;
}
