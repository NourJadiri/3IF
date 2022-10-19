#include <stdio.h>

void write_initial_content(FILE* file) {
    int i,j;
    for (i=0; i<20; i++) {
        for (j=0; j<40; j++) fputc('_', file);
        fputc('\n', file);
    }
}

void print_file(FILE* file) {
    rewind(file);
    while (1) {
        char c = fgetc(file);
        if (c == EOF) break;
        fputc(c, stdout);
    }
}

void replace_char(FILE* file, char k, int offset) {
    fseek(file, offset, SEEK_SET);
    fputc(k, file);
}

int main() {
    char* file_name = "dest_file";
    FILE* file = fopen(file_name, "w+");

    write_initial_content(file);

    char k;
    int offset;
    while (1) {
        print_file(file);
        printf("character: "); scanf(" %c", &k);
        if (k=='q') break;
        printf("offset: "); scanf(" %d", &offset);
        replace_char(file, k, offset);
    }
    
    if (!fclose(file)) return -1; // try to close file

    return 0;
}
