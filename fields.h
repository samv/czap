#ifndef CZAP_FIELD
#define CZAP_FIELD

#include "writers.h"

// fieldval interface
typedef union _cz_fieldval {
  /* integer types - passed by value */
  char sc;
  unsigned char uc;
  short ss;
  unsigned short us;
  long sl;
  unsigned long ul;
  long long sll;
  unsigned long long ull;
  /* floats - passed by value */
  float sf;
  double df;
  /* strings/bytes - passed by reference */
  char* str;
  /* other things  - passed by reference */
  void* ptr;
} cz_fieldval;

// cz_vt is functions that must be implemented by different field types
// to marshal out
typedef struct {
  cz_writer_impl (*writeField)(cz_writer *w, const char* const name, cz_fieldval val);
} cz_vt;

/* czap_field is a structure passed by value to the va_arg list */
typedef struct {
  cz_vt* vt;
  const char* const name; /* field name */
  cz_fieldval val;
} czap_field;

// for marking end of fields in va_args
czap_field czap_end;

#endif
