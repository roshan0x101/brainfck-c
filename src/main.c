#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "utils.h"
#include "interpreter.h"
#include "generator.h"

#define SELF_NAME argv[0]

void print_run_usage(const char* name) {
    printf("Usage: %s run <filename> [options]\n", name);
    puts("Options:");
    puts("\t-s\tASCII number for separation of digits");
    puts("\t-c\tPrints the output as decimal (separated by space), instead of characters");
    puts("\t-h\tPrints the help message");
}

int check_ext(const char *filename) {
    const char *ext = strrchr(filename, '.');
    if (ext != NULL) {
        if (strcmp(ext, ".bf") == 0 || strcmp(ext, ".b") == 0) return 0;
    }
    return 1;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Brainfuck-C Multi-Tool\n");
        printf("Usage: %s <command> [args...]\n", SELF_NAME);
        printf("Commands: run, gen, help\n");
        return 0;
    }

    const char* cmd = argv[1];

    // --- COMMAND: HELP ---
    if (strcmp(cmd, "help") == 0) {
        printf("Brainfuck-C Multi-Tool\n");
        printf("Usage: %s <command> [args...]\n\n", SELF_NAME);
        printf("Commands:\n");
        printf("  run <file> [-c] [-s sep]  Execute a Brainfuck file\n");
        printf("  gen [text...]             Generate optimized Brainfuck code\n");
        return 0;
    }

    // --- COMMAND: RUN (INTERPRETER) ---
    if (strcmp(cmd, "run") == 0) {
        // Shift getopt to start looking at arguments AFTER the word "run"
        optind = 2; 
        
        int help = 0, is_error = 0, non_char = 0;
        char sep = ' ';
        char* filename = NULL;
        int opt;

        while ((opt = getopt(argc, argv, "chs:")) != -1) {
            switch (opt) {
                case 'h': help = 1; break;
                case 'c': non_char = 1; break;
                case 's':
                    int tmp = atol(optarg);
                    if (tmp < 0) {
                        printf("%s run: Invalid value for option -s\n", SELF_NAME);
                        is_error = 1;
                    } else {
                        sep = (char)tmp;
                    }
                    break;
                case '?': is_error = 1; break;
            }
        }

        if (help) {
            print_run_usage(SELF_NAME);
            return 0;
        }
        if (is_error) return 1;

        if (optind < argc) {
            filename = argv[optind];
        } else {
            printf("%s run: option \"filename\" is required\n", SELF_NAME);
            return 1;
        }

        FILE *f = fopen(filename, "r");
        if (f == NULL) {
            printf("%s run: The file \"%s\" does not exist.\n", SELF_NAME, filename);
            return 1;
        }
        if (check_ext(filename)) {
            printf("%s run: File extension of \"%s\" is not valid!\n", SELF_NAME, filename);
            fclose(f);
            return 1;
        }

        // Read the .bf file safely into a string
        size_t i_limit = MAX_CELLS;
        char *input = (char *)malloc(i_limit * sizeof(char));
        if (input == NULL) {
            puts(MEM_ERROR_MSG);
            fclose(f);
            return 1;
        }

        int c;
        size_t i = 0;
        while ((c = fgetc(f)) != EOF) {
            if (i >= i_limit - 1) {
                i_limit += MAX_CELLS;
                char *tmp = (char *)realloc(input, i_limit);
                if (tmp == NULL) {
                    puts(MEM_ERROR_MSG);
                    free(input);
                    fclose(f);
                    return 1;
                }
                input = tmp;
            }
            input[i++] = (char)c;
        }
        input[i] = '\0';
        fclose(f);

        // Pass the pure string to our interpreter module!
        int result = run_brainfuck(input, non_char, sep);
        free(input);
        return result;
    }

    // --- COMMAND: GEN (GENERATOR) ---
    if (strcmp(cmd, "gen") == 0) {
        char* input = NULL;

        if (argc == 2) {
            // Interactive Mode
            printf("Enter an input: ");
            input = get_safe_input();
            if (input == NULL) return 1;
        } else {
            size_t i_limit = MAX_CELLS;
            input = (char *)malloc(i_limit);
            if (input == NULL) {
                puts(MEM_ERROR_MSG);
                return 1;
            }
            input[0] = '\0';

            // We start at i = 2 because argv[0] is "./brainfk" and argv[1] is "gen"
            for (int i = 2; i < argc; ++i) {
                size_t needed_space = strlen(input) + strlen(argv[i]) + 2;
                if (needed_space >= i_limit) {
                    i_limit = needed_space + MAX_CELLS;
                    char *tmp = (char *)realloc(input, i_limit);
                    if (tmp == NULL) {
                        puts(MEM_ERROR_MSG);
                        free(input);
                        return 1;
                    }
                    input = tmp;
                }
                strcat(input, argv[i]);
                strcat(input, " ");
            }
            if (strlen(input) > 0) {
                input[strlen(input) - 1] = '\0';
            }
        }

        int result = generate_brainfuck(input);
        free(input);
        return result;
    }

    printf("Unknown command: %s\n", cmd);
    printf("Run '%s help' for usage instructions.\n", SELF_NAME);
    return 1;
}