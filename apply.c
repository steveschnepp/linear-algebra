#include <stdio.h>
#include <math.h>

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

    while (1) {
        struct v3f v = { 0 };
        int r = scanf("%f %f %f", &v.x, &v.y, &v.z);
        if (r < 3) return 0;

        v = m4f_apply(matrix, v);
        print_v3f(v);
    }
}