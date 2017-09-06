#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

//constants
#define MAX 6

//prototype
void greet(void);
void clear(void);
void init(char **board);
void draw(char **board);
bool srokeCheck(const char *symbol_1, const char *symbol_2, int *move, char **board, const int *tile_one, const int *tile_two);
bool won(char *win, int *move, char **board);