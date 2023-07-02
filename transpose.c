#include <stdio.h>

#include "m4f.h"
#include "io.h"

int main(int argc, char* argv[]) {
    // Skip program name
    argc --; argv ++;

    // get the transformation matrix from args
    struct m4f matrix;
    if (argc < 16) {
        matrix = m4f_identity();
    } else {
        matrix = sscan_m4f_args(argv);
    }

    matrix = m4f_transpose(matrix);

    print_m4f(matrix);
}