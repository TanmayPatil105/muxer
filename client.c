/*
 * client.c
 */

#include <stdio.h>

#include "shm.h"
#include "client.h"

void
client_read_shm (key_t key)
{
  char *ptr;
  int shm_id;

  shm_id = shm_ret_id (key);

  if (shm_id == -1)
    {
      utils_throw_error (NULL);
    }

  ptr = shm_get (shm_id);

  fprintf (stdout, "%s", ptr);

  /* Free up memory */
  shm_cleanup (ptr, shm_id);
}
