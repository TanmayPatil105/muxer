/*
 * client.c
 */

#include <stdio.h>

#include "shm.h"
#include "client.h"

void
client_read_shm (key_t key)
{
  void *addr;
  int shm_id;
  uint *r_count;


  shm_id = shm_ret_id (key);

  if (shm_id == -1)
    {
      utils_throw_error (NULL);
    }

  addr = shm_get (shm_id);

  fprintf (stdout, "%s",
                   (char*) ((char*) addr + sizeof(uint)));

  r_count = (uint *) addr;
  *r_count -=1;

  /* Free up memory */
  shm_cleanup (addr, shm_id);
}
