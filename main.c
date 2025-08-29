#include "student_functions.h"
#include <stdbool.h>

int main(void) {
    while (true) {
        if (menuInterface(getUserMenuChoice()) == 0) {
            break;
        }
    }

    return 0;
}