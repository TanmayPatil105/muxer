/*
 * utils.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include "utils.h"

uint
utils_get_num_from_str (char *str)
{
  char *ptr = str;

  while (*ptr != '\0')
    {
      if(!isdigit(*ptr))
        return -1;

      *ptr++;
    }

  return (uint) atoi(str);
}

uint
utils_generate_random_number ()
{
  srand(time(NULL));

  return rand();
}

void
utils_throw_error (char *message)
{
  if (message)
    fprintf (stderr, "muxer: %s\n", message);
  else
    fprintf (stderr, "muxer: %s\n", strerror(errno));

  exit (EXIT_FAILURE);
}
