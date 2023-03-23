#include "levels.h"

bool czap_level_enabled(czap_level log_level, czap_level message) {
  return (message >= log_level);
}
