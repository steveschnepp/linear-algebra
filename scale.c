#include <stdio.h>

#include "m4f.h"
#include "io.h"

int main(int argc, char* argv[]) {
    struct v3f scale = { 1, 1, 1 };

    // Skip program name
    argc --; argv ++;

    float f;
    switch (argc)
    {
        case 0:
            break;
        case 1:
            sscanf(argv[0], "%f", &f);
            scale.x = scale.y = scale.z = f;
            break;

        default:
        case 3:
            sscanf(argv[2], "%f", &f);
            scale.z = f;
        case 2:
            sscanf(argv[1], "%f", &f);
            scale.y = f;
            sscanf(argv[0], "%f", &f);
            scale.x = f;
            break;
    }

    struct m4f scale_matrix = m4f_scale(scale.x, scale.y, scale.z);
    print_m4f(scale_matrix);
}