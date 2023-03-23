#include "helpers.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

cz_writer_impl writeChar(cz_writer* w, char c) {
  return w->vt.write(w->w, &c, 1);
}

cz_writer_impl writeComma(cz_writer* w) {
  return writeChar(w, ',');
}

cz_writer_impl writeName(cz_writer* w, const char* name) {
  w->w = writeString(w, name);
  w->w = writeChar(w, ':');
  return w->w;
}

char* hex = "0123456789abcdef";

cz_writer_impl writeCharHex(cz_writer* w, char c) {
  w->w = writeChar(w, hex[(c>>4)&0xf]);
  w->w = writeChar(w, hex[c&0xf]);
  return w->w;
}

cz_writer_impl writeChars(cz_writer* w, const char* val) {
  for (const char* i = val; *i; i++) {
    char c = *i;
    w->w = writeChar(w, c);
  }
  return w->w;
}

cz_writer_impl writeUnsigned(cz_writer* w, unsigned long long int ulli) {
  char buf[21];
  snprintf((char*)&buf, 21, "%llu", ulli);
  return writeChars(w, (char*)&buf);
}

typedef struct {
  long codepoint;
  short len;
} rune;

// decode a codepoint in a null-terminated character string pointed to
// by src and return the number of bytes consumed and the codepoint in
// a rune struct
rune decodeRune(const char* src) {
  rune r = (rune){.codepoint = 0, .len = 1};
  short want = 1;
  unsigned char c = *src;
  src++;
  if ((c & 0b11100000) == 0b11000000) {
    want = 2;
    r.codepoint = c & 0b11111;
  } else if ((c & 0b11110000) == 0b11100000) {
    want = 3;
    r.codepoint = c & 0b1111;
  } else if ((c & 0b11111000) == 0b11110000) {
    want = 4;
    // printf("(want=4!;c=%.2x)", c);
    r.codepoint = c & 0b111;
  } else {
    r.codepoint = 0xfffd;
    return r;
  }
  for (unsigned char c; r.len < want; src++) {
    c=*src;
    if ((c & 0xc0) != 0x80) {
      break;
    }
    r.len++;
    // printf("(len=%d;c=%.2x==%.2x)", r.len, c, (c & 0b111111));
    r.codepoint = (r.codepoint << 6) | (c & 0b111111);
    if (r.codepoint == 0 || r.codepoint > 0x10ffff) {
      break;
    }
  }
  if (r.len != want) {
    r.codepoint = 0xfffd; // replacement character
  }
  return r;
}

/* FIXME - replace the below with an off-the-shelf library not an
   off-the-self hack */

// writes a single unicode codepoint as a \u240A or \u{010b23}
// sequence
cz_writer_impl writeRune(cz_writer* w, rune r) {
  w->w = writeChar(w, '\\');
  w->w = writeChar(w, 'u');
  if (r.codepoint > 0xffff) {
    int leadSurrogate = 0xd800 + (r.codepoint>>10);
    w->w = writeCharHex(w, leadSurrogate >> 8 & 0xff);
    w->w = writeCharHex(w, leadSurrogate & 0xff);
    int tailSurrogate = 0xdc00 + (r.codepoint & 0b1111111111);
    w->w = writeChar(w, '\\');
    w->w = writeChar(w, 'u');
    w->w = writeCharHex(w, tailSurrogate >> 8 & 0xff);
    w->w = writeCharHex(w, tailSurrogate & 0xff);
    return w->w;
  }
  w->w = writeCharHex(w, r.codepoint >> 8 & 0xff);
  w->w = writeCharHex(w, r.codepoint & 0xff);
  return w->w;
}

cz_writer_impl writeString(cz_writer* w, const char* val) {
  w->w = writeChar(w, '"');
  for (const char* i = val; *i; i++) {
    unsigned char c = *i;
    switch (c) {
    case '\t':
      w->w = writeChars(w, "\\t");
      break;
    case '\n':
      w->w = writeChars(w, "\\n");
      break;
    case '\r':
      w->w = writeChars(w, "\\r");
      break;
    case '\f':
      w->w = writeChars(w, "\\f");
      break;
    case '\b':
      w->w = writeChars(w, "\\b");
      break;
    case '\\':
    case '"':
      w->w = writeChar(w, '\\');
      // fallthrough
    default:
      if (c > 0x7f) {
	// oh fuck, unicode
	rune r = decodeRune(i);
	i += r.len - 1;
	w->w = writeRune(w, r);
	continue;
      } else if (c < 0x20) {
	// needs a hexadecimal escape
	w->w = writeRune(w, (rune){.len=1,.codepoint=c});
	w->w = writeCharHex(w, c);
	continue;
      }
      w->w = writeChar(w, c);
    }
  }
  w->w = writeChar(w, '"');
  return w->w;
}

