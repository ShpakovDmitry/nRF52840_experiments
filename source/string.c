#include <string.h>

#define MAX_STRLEN 1024

size_t strlen(const char* str) {
    size_t len = 0;
    for (size_t i = 0; i < MAX_STRLEN; i++) {
        if ( str[i] == '\0' ) {
            len = i;
            break;
        }
    }
    return len;
}
