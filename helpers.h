#ifndef CZAP_HELPERS
#define CZAP_HELPERS

#include "writers.h"
#include "fields.h"

/* helper functions */
cz_writer_impl writeName(cz_writer* w, const char* name);
cz_writer_impl writeString(cz_writer* w, const char* val);
cz_writer_impl writeComma(cz_writer* w);
cz_writer_impl writeChar(cz_writer* w, const char c);
cz_writer_impl writeUnsigned(cz_writer* w, unsigned long long int ulli);

#endif /* CZAP_HELPERS */
