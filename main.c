#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

#define SELF_NAME argv[0]
#define MEM_ERROR_MSG "Memory allocation error!\nPlease, free your memory to use this program, properly."
#define print_usage(name) printf("%s <filename> [options]\n", name);
#define print_options                                                                         \
	puts("Options:");                                                                         \
	puts("\t-s\tASCII number for separation of digits");                                      \
	puts("\t-c\tIt prints the output as decimal (separated by space), instead of character"); \
	puts("\t-h\tIt prints the help message");

#define MAX_CELLS 30000
#define MAX_ASCII 256

struct ProgParser
{
	char *filename;
	int is_error;
	int non_char;
	int help;
	char sep;
};

// DON'T TOUCH THIS, PLEASE!
const char *P_OPTIONS = "chs:";

void parse_opts(char *, int, char **, struct ProgParser *);
int check_ext(const char *);

unsigned char cells[MAX_CELLS] = {0};

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		print_usage(SELF_NAME);
		return 0;
	}

	struct ProgParser parser = {.sep = ' '};

	parse_opts(SELF_NAME, argc, argv, &parser);

	if (parser.is_error)
		return 1;

	if (parser.help)
	{
		print_usage(SELF_NAME);
		print_options;
		return 0;
	}

	if (parser.filename == NULL && argc > 1)
	{
		printf("%s: option \"filename\" is required\n", SELF_NAME);
		return 1;
	}

	FILE *f = fopen(parser.filename, "r");

	if (f == NULL)
	{
		printf("%s: The file \"%s\" is not exist in the directory\n", SELF_NAME, parser.filename);
		return 1;
	}
	if (check_ext(parser.filename))
	{
		printf("%s: File extension of \"%s\" is not valid!\n", SELF_NAME, argv[1]);
		return 1;
	}

	int stack_loop[100];
	int stack_i = -1;

	size_t i_limit = MAX_CELLS;
	char *input = (char *)malloc(i_limit * sizeof(char));
	if (input == NULL)
	{
		puts(MEM_ERROR_MSG);
		fclose(f);
		return 1;
	}

	int c;
	size_t i = 0;

	while ((c = fgetc(f)) != EOF)
	{
		if (i >= i_limit - 1)
		{
			i_limit += MAX_CELLS;
			char *tmp = (char *)realloc(input, i_limit);
			if (tmp == NULL)
			{
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

	size_t input_len = strlen(input);
	size_t x = 0;
	for (size_t i = 0; i < input_len; ++i)
	{
		switch (input[i])
		{
		case '>':
			x = (x + 1) % MAX_CELLS;
			break;
		case '<':
			x = (x == 0) ? MAX_CELLS - 1 : x - 1;
			break;
		case '+':   cells[x] += 1;  break;
		case '-':   cells[x] -= 1;  break;
		case '[':
			if (cells[x] == 0)
			{
				int opbr = 1;
				while (opbr > 0 && i + 1 < strlen(input))
				{
					i++;
					if (input[i] == '[')
					{
						opbr++;
					}
					else if (input[i] == ']')
					{
						opbr--;
					}
				}
			}
			else
			{
				stack_loop[++stack_i] = i;
			}
			break;
		case ',':
			scanf("%c", &cells[x]);
			break;
		case ']':
			if (cells[x] != 0)
				i = stack_loop[stack_i];
			else
				--stack_i;
			break;
		case '.':
			if (parser.non_char)
			{
				printf("%d", cells[x]);
				if ((i + 3) < strlen(input))
					printf("%c", parser.sep);
			}
			else
				putchar(cells[x]);
			break;
		}
	}
	free(input);
	return 0;
}

int check_ext(const char *filename)
{
	// strrchr finds the last '.' in the string safely
	const char *ext = strrchr(filename, '.');

	// If we found a dot, check if the string matches our allowed extensions
	if (ext != NULL)
	{
		if (strcmp(ext, ".bf") == 0 || strcmp(ext, ".b") == 0)
		{
			return 0; // 0 means false/no error (Valid extension!)
		}
	}

	return 1; // 1 means true/error (Invalid or missing extension)
}

void parse_opts(char *name, int argc, char **argv, struct ProgParser *inp_parser)
{
	int i, tmp;
	while ((i = getopt(argc, argv, P_OPTIONS)) != -1)
	{
		switch (i)
		{
		case 'h':
			inp_parser->help = 1;
			break;
		case 'c':
			inp_parser->non_char = 1;
			break;
		case '?':
			inp_parser->is_error = 1;
			break;
		case 's':
			tmp = atol(optarg);
			if (tmp < 0)
			{
				printf("%s: Invalid value for option -s (the value should be decimal)\n", name);
				inp_parser->is_error = 1;
				return;
			}
			inp_parser->sep = tmp;
			break;
		case ':':
			printf("%s: Option -s requires an argument", name);
			inp_parser->is_error = 1;
			break;
		}
	}
	inp_parser->filename = argv[optind];
	return;
}
