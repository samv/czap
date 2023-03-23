#ifndef CZAP_H
#define CZAP_H

/*
 * CZap - more or less a straight port of go.uber.org/zap to C.
 *
 * There are big differences between C and Go in terms of memory
 * management, so this lib makes some assumptions:
 *
 * - a statement which emits a log does not assume that it can retain
 *   pointers to its boxed arguments
 *
 * - creating a new log context will always immediately render the log
 *   arguments into a JSON-ified string
 *
 * - pointers to fragments of parent contexts are allowed - they
 *   should be freed in reverse order.
 *
 * - due to the C variadic calling convention, an explicit
 *   end-of-fields marker is used
 */
#include <stdio.h>

#include "fields.h"
#include "fieldtypes.h"
#include "logger.h"

#define CZ_INFO(logger, msg, ...) czap_log(logger, INFO, msg, ##__VA_ARGS__, czap_end)

/* get a new logger */
czap_logger *czap_init(FILE *f);

/* add a trace ID to a logger */
czap_logger *czap_with(czap_logger* logger, ...);

/* convenience wrapper for adding czap_end at the end */
#define CZ_WITH(logger, ...) czap_with(logger, ##__VA_ARGS__, czap_end)

/* field initializers */
#define cz_int64(fieldname, intval) (czap_field){.vt=_cz_int_vt, .name=fieldname, .val=(cz_fieldval){.sll=intval}}
#define cz_uint64(fieldname, uintval) (czap_field){.vt=&_cz_uint_vt, .name=fieldname, .val=(cz_fieldval){.ull=uintval}}
#define cz_string(fieldname, string) (czap_field){.vt=&_cz_string_vt, .name=fieldname, .val=(cz_fieldval){.str=string}}
#define cz_int(fieldname, intval) (czap_field){.vt=&_cz_int_vt, .name=fieldname, .val=(cz_fieldval){.sll=intval}}

#endif /* CZAP_H */

