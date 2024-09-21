/*
 * helper.h
 */

#include <sys/shm.h>

void helper_setup_shm (key_t key,
                       int   r_count);
void helper_share_key (int   proj_id);
