/*
 * helper.c
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "helper.h"
#include "shm.h"
#include "utils.h"

static char *
get_stdin (size_t *size)
{
  char *content = NULL;
  char buf[1024];
  size_t og_size = 0, i_size = 0;

  while (fgets (buf, sizeof(buf), stdin) != NULL)
    {
      size_t buf_len = strlen (buf);

      content = realloc (content, og_size + buf_len + 1);

      if (content == NULL)
        utils_throw_error (NULL);

      strcpy (content + i_size, buf);
      i_size += buf_len;

      og_size = i_size + 1;
    }

  if (content == NULL)
    *size = 0;
  else
    *size = og_size;

  return content;
}

void
helper_setup_shm (key_t key,
                  int   r_count)
{
  char *content;
  int shm_id;
  size_t size;

  content = get_stdin(&size);
  shm_id = shm_create (key, size);

  if (shm_id == -1)
    {
      if (errno == EEXIST)
        utils_throw_error ("shared memory already exists");
      else
        utils_throw_error (NULL);
    }

  /* Unfortunately Linux doesn't support this :( */
  /* shm_set_r_count (shm_id, r_count); */

  shm_put_content (shm_id, content, size);
}

void
helper_share_key (int proj_id)
{
  fprintf (stdout, "%d\n", proj_id);
}
