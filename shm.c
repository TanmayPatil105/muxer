/*
 * shm.c
 */

#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

#include "shm.h"
#include "utils.h"


int
shm_create (key_t  key,
            size_t size)
{
  return shmget (key, size, IPC_CREAT | IPC_EXCL | 511);
}

int
shm_ret_id (key_t key)
{
  return shmget (key, 0, 0);
}

void
shm_set_r_count (int  shm_id,
                 uint count)
{
  struct shmid_ds buf;

  if (shmctl (shm_id, IPC_STAT, &buf) == -1)
    utils_throw_error (NULL);

  buf.shm_nattch = count;

  if (shmctl (shm_id, IPC_SET, &buf) == -1)
    utils_throw_error (NULL);
}

void
shm_put_content (int    shm_id,
                 char  *content,
                 size_t size)
{
  char *ptr;

  ptr = shmat (shm_id, NULL, 0);

  if (ptr == (void *) -1)
    utils_throw_error (NULL);

  memcpy (ptr, content, size);
}

char *
shm_get (int shm_id)
{
  char *ptr;

  ptr = shmat (shm_id, NULL, 0);

  return ptr;
}

static int
get_n_attached (int shm_id)
{
  struct shmid_ds buf;

  if (shmctl (shm_id, IPC_STAT, &buf) == -1)
    utils_throw_error (NULL);

  return (int) buf.shm_nattch;
}

void
mark_for_removal (int shm_id)
{
  if (shmctl (shm_id, IPC_RMID, 0) == -1)
    utils_throw_error (NULL);
}

void
shm_cleanup (char *addr,
             int  shm_id)
{
  int ret;

  ret = shmdt ((void *) addr);

  if (ret == -1)
    utils_throw_error (NULL);

  if (get_n_attached (shm_id) == 0)
    mark_for_removal (shm_id);
}
