#include <stdio.h>
#include <string.h>

void print_usage(char*);
int check_ext(char*);

char cells[100] = {0};

int main(int argc, char** argv) {
    FILE* f;

    if (argc == 1 || argc < 2){
        print_usage(argv[0]);
        return 0;
    }
    else if (argc == 2){
        f = fopen(argv[1], "r");

        if (f == NULL) {
            printf("%s: The file \"%s\" is not exist in the directory\n", argv[0], argv[1]);
            return 1;
        }
        if (check_ext(argv[1])){
            printf("%s: File extension of \"%s\" is not valid!\n", argv[0], argv[1]);
            return 1;
        }
    }

    char input[1000];
    int i = 0;

    while((input[i++] = getc(f)) != EOF);
    fclose(f);

    int x = sizeof(cells) / 2;
    for (int y = 0, i = 0; i < (int)strlen(input) && x < (int)sizeof(cells); ++i) {
        switch (input[i]) {
            case '>':
                ++x;
                break;
            case '<':
                --x;
                break;
            case '+':
                ++cells[x];
                break;
            case '-':
                --cells[x];
                break;
            case '[':
                y = i;
                break;
            case ']':
                if (cells[x] != 0) i = y;
                break;
            case '.':
                printf("%c", cells[x]);
                break;
            case ',':
                scanf("%c", &cells[x]);
                break;
        }
    }

    if (x >= (int)sizeof(cells)){
        printf("%s: Index is out of cells!\n", argv[0]);
        return 1;
    }

    printf("\n");

    return 0;
}

void print_usage(char* name) {
    printf("%s <filename>\n", name);
}

int check_ext(char* filename){
    char tmp[3];
    char* ext1 = (char*)"bf";
    char* ext2 = (char*)"b";
    char* tok = strtok(filename, ".");
    tok = strtok(NULL, ".");
    while (tok != NULL) {
        strncpy(tmp, filename, 2);
        tok = strtok(NULL, ".");
    }
    return strcmp(tmp, ext1) == 0 || strcmp(ext2, tmp) == 0;
}
