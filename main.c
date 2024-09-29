/*
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <stdbool.h>

#include "utils.h"
#include "helper.h"
#include "client.h"

int
main (int   argc,
      char *argv[])
{
  key_t key = -1;
  uint r_count = 1;
  bool create = true;
  uint proj_id;

  if (argc > 1 && (strcmp (argv[1], "-c") != 0))
    {
      create = false;
      proj_id = utils_get_num_from_str (argv[1]);

      if (proj_id == (uint) -1)
        {
          fprintf (stderr, "%s: provide a valid id\n", argv[0]);
          return 1;
        }
    }
  else
    {
      if (argc > 2 && (strcmp (argv[1], "-c") == 0))
        {
          r_count = utils_get_num_from_str (argv[2]);

          if (r_count == (uint) -1)
            {
              fprintf (stderr, "%s: provide a valid number of readers\n", argv[0]);
              return 1;
            }
        }

      proj_id = utils_generate_random_number ();
    }

  key = ftok (argv[0], proj_id);

  if (create == true)
    {
      helper_setup_shm (key, r_count);
      helper_share_key (proj_id);
    }
  else
    {
      client_read_shm (key);
    }

  return 0;
}
