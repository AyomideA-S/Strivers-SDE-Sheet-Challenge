/**
 * @file driver_boilerplate.c
 * @author Ayomide Ayodele-Soyebo (midesuperbest@gmail.com)
 * @brief A boilerplate for writing C driver programs for online judges
 * @version 0.1
 * @date 2023-06-24
 *
 * @copyright Copyright (c) 2023
 *
 */



#include "solutions.h"

/**
 * @brief Print usage information for the program
 *
 * @param program_name The name of the program
 */
void help(char *program_name)
{
	printf("Usage: %s [OPTIONS] [FILE]\n", program_name);
	printf("Options:\n");
	printf("  -h, --help\t\t\t\tPrint usage\n");
	printf("  -v, --verbose\t\t\t\tVerbose output\n");
	printf("  -q, --quiet\t\t\t\tQuiet output\n");
	printf("  -s, --solution=FILE\t\t\tSolution file\n");
	printf("  -t, --time\t\t\t\tTime program\n");
	printf("  -o, --output=FILE\t\t\tOutput file\n");
}

/**
 * @brief Time the function
 *
 * @param matrix The matrix
 * @param rows Number of rows
 * @param columns Number of columns
 * @return double - The CPU time used by the function
 */
double calculate_time(int **matrix, int rows, int columns)
{
	clock_t start, end;

	start = clock();
	zeroMatrix(matrix, rows, columns);
	end = clock();

	/* calculate CPU time used */
	return (((double)(end - start)) / CLOCKS_PER_SEC);
}

/**
 * @brief Parse the matrix
 *
 * @param stream File stream
 * @param rows Number of rows
 * @param columns Number of columns
 * @return int** - The matrix
 */
int **parse_matrix(FILE *stream, int rows, int columns)
{
	int **matrix;
	int i, j, element;
	int index = 0, row_iter = 0, col_iter = 0;
	char line[512];

	/* allocate memory for matrix */
	matrix = (int **)malloc(rows * sizeof(int *));
	for (i = 0; i < rows; i++)
		matrix[i] = (int *)malloc(columns * sizeof(int));

	/* read matrix */
	while (!feof(stream) && !ferror(stream)) {
		if (fgets(line, sizeof(line), stream) != NULL) {
			char *token = strtok(line, " \n");
			while (token != NULL) {
				// element = atoi(token);
				element = strtol(token, NULL, 10);
				*(*(matrix + row_iter) + col_iter) = element;
				index++;
				row_iter = index / columns;
				col_iter = index % columns;
				token = strtok(NULL, " \n");
			}
		}
	}

	return matrix;
}

/**
 * @brief Print the matrix to the specified stream
 *
 * @param matrix A 2D array of integers
 * @param rows Number of rows in the matrix
 * @param cols Number of columns in the matrix
 * @param stream The stream to print to
 */
void print_matrix(int **matrix, int rows, int cols, FILE *stream)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			fprintf(stream, "%d", matrix[i][j]);
			if (j < cols - 1)
				fprintf(stream, " ");
		}
		if (i < rows - 1)
			fprintf(stream, "\n");
	}
	fprintf(stream, "\n");
}

/**
 * @brief A function to print verbose output
 *
 * @param matrix The matrix
 * @param rows Number of rows
 * @param columns Number of columns
 * @return double - The CPU time used by the function
 */
double verbose_print(int **matrix, int rows, int columns)
{
	double time;

	printf("Input:\n");
	printf("%d %d\n", rows, columns);
	print_matrix(matrix, rows, columns, stdout);
	printf("\n");
	time = calculate_time(matrix, rows, columns);
	printf("Output:\n");
	print_matrix(matrix, rows, columns, stdout);

	return time;
}

/**
 * @brief A function to write the matrix to a file
 *
 * @param stream File stream to write to
 * @param matrix A 2D array of integers
 * @param rows Number of rows
 * @param columns Number of columns
 */
void write_matrix(FILE *stream, int **matrix, int rows, int columns)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++) {
			fprintf(stream, "%d", matrix[i][j]);
			if (j < columns - 1)
				fprintf(stream, " ");
		}
		if (i < rows - 1)
			fprintf(stream, "\n");
	}
	fprintf(stream, "\n");
}

/**
 * @brief A function to validate the output against the expected output
 *
 * @param matrix Output matrix
 * @param expected Expected output matrix
 * @param rows Number of rows
 * @param columns Number of columns
 * @return _Bool - 1 if the output is correct, 0 otherwise
 */
_Bool assert_matrix(int **matrix, int **expected, int rows, int columns)
{
	_Bool result = 1;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			result &= (matrix[i][j] == expected[i][j]);
	return result;
}

/**
 * @brief Main function for the program
 *
 * @param argc The number of command line arguments
 * @param argv The command line arguments
 * @return int - The exit status of the program
 */
int main(int argc, char *argv[])
{
	/* timing variables */
	double cpu_time_used;
	/* command line arguments flags and variables */
	char *program_name = basename(argv[0]);
	int verbose = 0, quiet = 0, time = 0;
	char *solution = NULL;
	char *output = NULL;
	/* iteration variables */
	int index, c;

	/**
	 * @brief The long options for the program
	 */
	struct option long_options[] = {
		{ "help", no_argument, NULL, 'h'},
		{ "verbose", no_argument, NULL, 'v' },
		{ "quiet", no_argument, NULL, 'q' },
		{ "solution", required_argument, NULL, 's' },
		{ "time", no_argument, NULL, 't' },
		{ "output", required_argument, NULL, 'o' },
		{ NULL, 0, NULL, 0 }
	};

	while ((c = getopt_long(argc, argv, "hvqs:to:", long_options, &index)) != -1)
	{
		switch (c)
		{
			case 'h':
				help(program_name);
				exit(0);
				break;
			case 'v':
				verbose = TRUE;
				break;
			case 'q':
				quiet = 1;
				break;
			case 's':
				solution = optarg;
				break;
			case 't':
				time = TRUE;
				break;
			case 'o':
				output = optarg;
				break;
			case '?':
				// invalid option
				printf("Invalid option: %c\n", optopt);
				exit(1);
				break;
			default:
				// should never happen
				exit(1);
				break;
		}
	}

	if (verbose && quiet){
		printf("Error: cannot specify both --verbose and --quiet\n");
		printf("Try '%s --help' for more information.\n", program_name);
		printf("Defaulting to --verbose\n\n");
		quiet = FALSE;
	}

	char* input_file = argv[optind];
	/* check if input file is specified */
	input_file = "C:/Users/Ayomide/Desktop/AYOMIDE/PROGRAMMING AND CODING/DSA/Strivers-SDE-Sheet-Challenge/Coding Ninjas/Day 01 - Arrays/Set Matrix Zeros/in/input5.txt";
	if (input_file == NULL) {
		printf("Error: no input file specified\n");
		printf("Try '%s --help' for more information.\n", program_name);
		exit(1);
	}

	// process remaining arguments
	for (int i = optind; i < argc; i++) {
		// do something with argv[i]
		continue;
	}

	FILE *fp = fopen(input_file, "r");
	// check if file exists
	if (fp == NULL) {
		printf("Error: could not open input file\n");
		exit(1);
	}

	//ANCHOR - core of the program goes here
	int n, m;

	/* read number of rows and columns */
	fscanf(fp, "%d %d", &n, &m);

	int **matrix = parse_matrix(fp, n, m);
	/* close the file */
	fclose(fp);
	fp = NULL;

	if (quiet)
		cpu_time_used = calculate_time(matrix, n, m);
	else
		cpu_time_used = verbose_print(matrix, n, m);

	if (solution != NULL) {
		FILE *answer = fopen(solution, "r");
		// check if file exists
		if (answer == NULL) {
			printf("Error: could not open solution file\n");
			exit(1);
		}
		fclose(answer);
		answer = NULL;

		int **valid = parse_matrix(answer, n, m);

		if (assert_matrix(matrix, valid, n, m))
			// printf(GREEN "Test Case Passed\n" RESET);
			printf("Test Case Passed\n");
		else
			// printf(RED "Test Case Failed\n" RESET);
			printf("Test Case Failed\n");
	}

	if (output != NULL) {
		FILE *output_file = fopen(output, "w");
		// check if file exists
		if (output_file == NULL) {
			printf("Error: could not open output file\n");
			exit(1);
		}

		// write to file
		write_matrix(output_file, matrix, n, m);

		fclose(output_file);
		output_file = NULL;
	}

	if (time)
		printf("Time taken: %f seconds\n", cpu_time_used);

	return 0;
}
