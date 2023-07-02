#include <stdio.h>

#include "m4f.h"
#include "io.h"

int main(int argc, char* argv[]) {
    // Skip program name
    argc --; argv ++;

    if (argc < 3) {
        print_m4f(m4f_identity());
        return 0;
    }

    struct v3f v;
    sscanf(argv[0], "%f", &v.x);
    sscanf(argv[1], "%f", &v.y);
    sscanf(argv[2], "%f", &v.z);

    struct m4f translation_matrix = m4f_translate(v.x, v.y, v.z);
    print_m4f(translation_matrix);
}