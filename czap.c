
#include "czap.h"
#include <stdlib.h>
#include <stdio.h>

cz_writer_impl writeFile(cz_writer_impl writer, const char* src, int len) {
  for (int i = 0; i < len; i++) {
    fputc(*src, writer.a_file);
    src++;
  }
  return writer;
}

czap_logger *czap_init(FILE *f) {
  czap_logger *logger = (czap_logger *)malloc(sizeof(czap_logger)+sizeof(cz_writer));
  logger->level = INFO;
  logger->frag = 0;
  logger->parent = 0;
  logger->output = (cz_writer*)(void*)((char*)(void*)logger + sizeof(czap_logger));
  logger->output->vt = (cz_writer_vt){.write = writeFile};
  logger->output->w = (cz_writer_impl){.a_file = f};
  setvbuf(f, NULL, _IOLBF, 4096);
  return logger;
}
