#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void multiply(int, char);

#define MAX_LIMIT 30000
#define MEM_ERROR_MSG "Memory allocation error!\nPlease, free your memory to use this program, properly."

int main(int argc, char **argv)
{
	size_t i_limit = MAX_LIMIT;
	char *input = (char *)malloc(MAX_LIMIT * sizeof(char));

	if (input == NULL)
	{
		puts(MEM_ERROR_MSG);
		return 1;
	}

	input[0] = '\0';

	if (argc == 1) {
        printf("Enter an input: ");
        int c;
        size_t i = 0;
        
        while ((c = getchar()) != '\n' && c != EOF) {
            if (i + 1 >= i_limit) {
                i_limit += 1000;
                char* tmp = (char*)realloc(input, i_limit);
                if (tmp == NULL) {
                    puts(MEM_ERROR_MSG);
                    free(input);
                    return 1;
                }
                input = tmp;
            }
            input[i++] = (char)c;
        }
        input[i] = '\0';
    }

	for (int i = 1; i < argc; ++i) {

        size_t n_mem = strlen(input) + strlen(argv[i]) + 2; 
        
        if (n_mem >= i_limit) {
            i_limit = n_mem + 1000;
            char* tmp = (char*)realloc(input, i_limit);
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

	int tmp, t;
	for (int i = 0; input[i]; ++i)
	{
		if (i)
		{
			tmp = abs(input[i] - input[i - 1]);
			t = input[i] > input[i - 1];
			if (tmp <= 10)
				multiply(tmp, t ? '+' : '-');

			else
			{
				multiply(tmp % 10, t ? '+' : '-');
				putchar('>');
				multiply(tmp / 10, t ? '+' : '-');
				putchar('[');
				putchar('<');
				multiply(10, '+');
				putchar('>');
				putchar('-');
				putchar(']');
				putchar('<');
			}
		}
		else
		{
			multiply(input[i] % 10, '+');
			putchar('>');
			multiply(input[i] / 10, '+');
			putchar('[');
			putchar('<');
			multiply(10, '+');
			putchar('>');
			putchar('-');
			putchar(']');
			putchar('<');
		}
		putchar('.');
		putchar('\n');
	}
	free(input);
	return 0;
}

void multiply(int n, char c)
{
	for (int i = 0; i < n; ++i)
	{
		putchar(c);
	}
}
