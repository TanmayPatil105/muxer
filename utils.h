/*
 * utils.h
 */

#include <errno.h>

typedef unsigned int uint;

uint utils_get_num_from_str       (char *str);
uint utils_generate_random_number (void);
void utils_throw_error            (char *message);
