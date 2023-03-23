#ifndef CZAP_WRITERS
#define CZAP_WRITERS

#include "buffer.h"

// writer abstraction
typedef union _cz_writers {
  buffer* buffer_ptr;
  FILE* a_file;
} cz_writer_impl;

typedef struct {
  cz_writer_impl (*write)(cz_writer_impl writer, const char* src, int len);
} cz_writer_vt;

typedef struct {
  cz_writer_vt vt;
  cz_writer_impl w;
} cz_writer;

#endif /* CZAP_WRITERS */
