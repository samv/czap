#include "fieldtypes.h"

cz_vt _cz_string_vt = (cz_vt){writeStringField};

cz_writer_impl writeStringField(cz_writer *w, const char* const name, cz_fieldval val) {

  /* only write field if there is content */
  if (strlen(val.str) == 0)
    return w->w;

  /* always write a comma first */
  w->w = writeComma(w);
  w->w = writeName(w, name);
  w->w = writeString(w, val.str);

  return w->w;
};
