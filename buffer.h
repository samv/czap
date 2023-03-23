#ifndef CZAP_BUFFER
#define CZAP_BUFFER

#include <stdio.h>

// buffer
typedef struct {
  size_t buf_sz;
  int buf_len;
  char data[];
} buffer;

/* append buffer functions that add to data, until buffer is too big,
   then free+malloc a new buffer */
buffer * append_str(buffer* buf, const char*src, int len);
buffer * append_char(buffer* buf, char c);

// returns a new buffer copied from the passed-in buffer, grown to at
// least 'c' above 'buf_len'
buffer * copy_grow(buffer* buf, size_t c);

#endif /* CZAP_BUFFER */
