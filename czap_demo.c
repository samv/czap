/* this is czap */

#include "czap.h"

int main(int n, char** argv) {

  czap_logger *logger = czap_init(stdout);

  char* firmwareVersion = "1.2.34";
  
  CZ_INFO(logger, "Detected Firmware Version", cz_string("firmwareVersion", firmwareVersion));
  
}
