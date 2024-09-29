/*
 * shm.h
 */

#include <sys/ipc.h>

#include "utils.h"

int   shm_create      (key_t  key,
                       size_t size);
int   shm_ret_id      (key_t  key);
void *shm_get         (int    shm_id);
void  shm_put_content (void  *addr,
                       char  *content,
                       size_t size);
void  shm_set_r_count (void  *addr,
                       uint   count);
void  shm_cleanup     (void  *addr,
                       int    shm_id);
