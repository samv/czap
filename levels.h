#ifndef CZAP_LEVELS
#define CZAP_LEVELS

#include <stdbool.h>

typedef enum _czap_level { DEBUG, INFO, WARN, ERROR, FATAL } czap_level;

// czap_level_enabled returns true if the message level is equal to or
// higher than the log level
bool czap_level_enabled(czap_level log_level, czap_level message);

#endif
