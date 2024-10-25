#include <stdio.h>

int main() {
    #ifdef __clang__
        printf("Clang version: %d.%d.%d\n", __clang_major__, __clang_minor__, __clang_patchlevel__);
    #elif defined(__GNUC__)
        printf("GCC version: %d.%d.%d\n", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
    #else
        printf("Unknown compiler\n");
    #endif
    return 0;
}

// gcc -fsanitize=thread -o check_tsan_version check_tsan_version.c
// ./check_tsan_version