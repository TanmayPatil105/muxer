/*
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
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
  key_t key;
  int shm_id;
  int r_count = 1;
  bool create = true;
  uint proj_id;

  if (argc > 1)
    {
      create = false;
      proj_id = utils_get_num_from_str (argv[1]);

      if (key == -1)
        {
          fprintf (stderr, "%s: provide a valid id\n", argv[0]);
          return EINVAL;
        }
    }
  else
    {
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
