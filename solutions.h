#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>
#include <libgen.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

#define TRUE 1
#define FALSE 0

int **zeroMatrix(int **matrix, int n, int m);

#endif /* SOLUTIONS_H */