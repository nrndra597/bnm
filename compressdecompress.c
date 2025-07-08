#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compressFile(FILE *in, FILE *out) {
    int count;
    int current, next;

    current = fgetc(in);
    if (current == EOF) return;

    count = 1;
    while ((next = fgetc(in)) != EOF) {
        if (next == current && count < 255) {
            count++;
        } else {
            
            fputc(current, out);
            fputc(count, out);
            current = next;
            count = 1;
        }
    }
    
    fputc(current, out);
    fputc(count, out);
}

void decompressFile(FILE *in, FILE *out) {
    int ch, count;

    while ((ch = fgetc(in)) != EOF) {
        count = fgetc(in);
        if (count == EOF) {
            fprintf(stderr, "Invalid compressed file format.\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < count; i++) {
            fputc(ch, out);
        }
    }
}

void printUsage(const char *progName) {
    printf("Usage:\n");
    printf("  %s compress <inputfile> <outputfile>   : Compress the input file\n", progName);
    printf("  %s decompress <inputfile> <outputfile> : Decompress the input file\n", progName);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    const char *mode = argv[1];
    const char *inputFile = argv[2];
    const char *outputFile = argv[3];

    FILE *fin = fopen(inputFile, "rb");
    if (!fin) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    FILE *fout = fopen(outputFile, "wb");
    if (!fout) {
        perror("Error opening output file");
        fclose(fin);
        return EXIT_FAILURE;
    }

    if (strcmp(mode, "compress") == 0) {
        compressFile(fin, fout);
        printf("File compressed successfully.\n");
    } else if (strcmp(mode, "decompress") == 0) {
        decompressFile(fin, fout);
        printf("File decompressed successfully.\n");
    } else {
        printUsage(argv[0]);
        fclose(fin);
        fclose(fout);
        return EXIT_FAILURE;
    }

    fclose(fin);
    fclose(fout);
    return EXIT_SUCCESS;
}
