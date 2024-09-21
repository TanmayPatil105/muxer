/*
 * helper.c
 */

#include <stdio.h>

#include "helper.h"
#include "shm.h"
#include "utils.h"

void
helper_setup_shm (key_t key,
                  int   r_count)
{
  int shm_id;

  shm_id = shm_create (key);

  if (shm_id == -1)
    {
      if (errno == EEXIST)
        utils_throw_error ("shared memory already exists");
      else
        utils_throw_error (NULL);
    }

  shm_set_r_count (shm_id, r_count);

  shm_put_content (shm_id);
}

void
helper_share_key (int proj_id)
{
  fprintf (stdout, "%d\n", proj_id);
}
