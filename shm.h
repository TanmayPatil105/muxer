/*
 * shm.h
 */

#include <sys/ipc.h>

#include "utils.h"

int   shm_create      (key_t  key,
                       size_t size);
int   shm_ret_id      (key_t  key);
char *shm_get         (int    shm_id);
void  shm_put_content (int    shm_id,
                       char  *content,
                       size_t size);
void  shm_set_r_count (int    shm_id,
                       uint   count);
void  shm_cleanup     (char  *addr,
                       int    shm_id);
