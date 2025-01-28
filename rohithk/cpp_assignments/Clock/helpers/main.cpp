#include <helpers.h>

tm *getCurrentTimeInStructFormat(time_t explicitTime) {
  if (explicitTime) {
    return localtime(&explicitTime);
  }
  time_t currentTime = time(NULL);
  tm *structFormat = localtime(&currentTime);
  return structFormat;
}