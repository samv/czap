#ifndef CZAP_TYPES
#define CZAP_TYPES

#include "writers.h"
#include "fields.h"
#include "helpers.h"

#include <string.h>

cz_writer_impl writeStringField(cz_writer *w, const char* const name, cz_fieldval val);

cz_vt _cz_string_vt;

#endif /* CZAP_TYPES */
