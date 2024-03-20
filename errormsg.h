#pragma once

#include <stdbool.h>

#include "util.h"

typedef struct IntList_ {int i; struct IntList_ * rest;} * IntList;

extern bool EM_any_errors;
extern int EM_token_pos;

void EM_newline();
void EM_error(int, string, ...);
void EM_impossible(string, ...);
void EM_reset(string file_name);
