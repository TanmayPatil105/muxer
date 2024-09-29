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
shm_set_r_count (void *addr,
                 uint  count)
{
  /* Linux doesn't suppor the following operation */
  /*
  struct shmid_ds buf;

  if (shmctl (shm_id, IPC_STAT, &buf) == -1)
    utils_throw_error (NULL);

  buf.shm_nattch = count;

  if (shmctl (shm_id, IPC_SET, &buf) == -1)
    utils_throw_error (NULL);
  */

  memcpy ((char *)addr, &count, sizeof(uint));
}

void
shm_put_content (void  *addr,
                 char  *content,
                 size_t size)
{
  memcpy ((char *)addr + sizeof(uint), content, size);
}

void *
shm_get (int shm_id)
{
  void *ptr;

  ptr = shmat (shm_id, NULL, 0);

  return ptr;
}

static uint
get_n_attached (void *addr)
{
  return *(uint *) addr;
}

void
mark_for_removal (int shm_id)
{
  if (shmctl (shm_id, IPC_RMID, 0) == -1)
    utils_throw_error (NULL);
}

void
shm_cleanup (void *addr,
             int  shm_id)
{
  int ret;
  int n;

  n = get_n_attached (addr);
  ret = shmdt (addr);

  if (ret == -1)
    utils_throw_error (NULL);

  if (n == 0)
    mark_for_removal (shm_id);
}
