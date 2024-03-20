/*
 * errormsg.c - functions used in all phases of the compiler to give
 *              error messages about the Tiger program.
 *
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "errormsg.h"
#include "util.h"

bool any_errors = false;
static string file_name = "";
static int line_num = 1;
int EM_token_pos = 0;
static IntList line_pos = NULL;
extern FILE * yyin;

static IntList make_IntList(int i, IntList rest) {
    IntList l = malloc_checked(sizeof *l);
    l->i = i;
    l->rest = rest;
    return l;
}

void EM_newline() {
    line_num++;
    line_pos = make_IntList(EM_token_pos, line_pos);
}

void EM_error(int pos, string message, ...) {
    va_list ap;
    IntList lines = line_pos; 
    int num = line_num;
    any_errors = true;
    while (lines && lines->i >= pos) {
        lines = lines->rest;
        num--;}
    if (file_name) {
        fprintf(stderr,"%s:", file_name);
    }
    if (lines) {
        fprintf(stderr,"%d.%d: ", num, pos - lines->i);
    }
    va_start(ap, message);
    vfprintf(stderr, message, ap);
    va_end(ap);
    fprintf(stderr, "\n");
}

void EM_reset(string fname) {
    any_errors = false;
    file_name = fname;
    line_num = 1;
    line_pos = make_IntList(0, NULL);
    yyin = fopen(fname, "r");
    if (!yyin) {
        perror("Cannot open input file");
        exit(EXIT_FAILURE);
    }
}

