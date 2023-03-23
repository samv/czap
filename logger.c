
#include <stdarg.h>
#include <time.h>

#include "fields.h"
#include "helpers.h"
#include "logger.h"

void czap_log(czap_logger *logger, czap_level level, char* msg, ...) {
  if (!czap_level_enabled(logger->level, level))
      return;
  // step 1 - get timestamp
  struct timespec ts;
  clock_gettime(CLOCK_REALTIME, &ts);   /* can use _COARSE on linux */
  unsigned long long int wallclock = (unsigned long long int)ts.tv_sec * 1e9;
  wallclock += (unsigned long long int)ts.tv_nsec;
  cz_writer *w = logger->output;
  w->w = writeChar(w, '{');
  w->w = writeName(w, "ts");
  w->w = writeUnsigned(w, wallclock);
  w->w = writeComma(w);
  w->w = writeName(w, "level");
  switch (level) {
  case FATAL:
    w->w = writeString(w, "FATAL");
    break;
  case ERROR:
    w->w = writeString(w, "ERROR");
    break;
  case WARN:
    w->w = writeString(w, "WARN");
    break;
  case INFO:
    w->w = writeString(w, "INFO");
    break;
  case DEBUG:
    w->w = writeString(w, "DEBUG");
    break;
  default:
    w->w = writeString(w, "??");
    break;
  }
  w->w = writeComma(w);
  w->w = writeName(w, "msg");
  w->w = writeString(w, msg);
  va_list ap;
  va_start(ap, msg);
  czap_field f;
  for (f = va_arg(ap, czap_field); f.vt != NULL; f = va_arg(ap, czap_field)) {
    w->w = f.vt->writeField(w, f.name, f.val);
  }
  w->w = writeChar(w, '}');
  w->w = writeChar(w, '\n');
}
