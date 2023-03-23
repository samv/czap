#ifndef CZAP_LOGGER
#define CZAP_LOGGER

#include "buffer.h"
#include "levels.h"
#include "writers.h"

/* czap_logger is a 'log context' which lets you create contextualized logging statements */
typedef struct czap_logger {
  cz_writer *output;    /* pointer to the writer this logger is using */
  struct czap_logger* parent;  /* pointer to parent log context */
  buffer* frag;                /* rendered JSON (except ts) for log context */
  czap_level level;
} czap_logger;

/* logging - checks level, timestamps, emits to writer */
void czap_log(czap_logger *logger, czap_level level, char* msg, ...);

#endif
