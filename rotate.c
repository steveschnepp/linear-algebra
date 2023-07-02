#include <stdio.h>
#include <math.h>

#include "m4f.h"
#include "io.h"

int main(int argc, char* argv[]) {
    // Skip program name
    argc --; argv ++;

    if (argc < 4) {
        print_m4f(m4f_identity());
        return 0;
    }

    float angle_in_deg;
    struct v3f v;

    sscanf(argv[0], "%f", &angle_in_deg);
    sscanf(argv[1], "%f", &v.x);
    sscanf(argv[2], "%f", &v.y);
    sscanf(argv[3], "%f", &v.z);

    v = v3f_normalize(v);
    float angle_in_rad = angle_in_deg / 180 * M_PI;
    struct m4f rotate_matrix = m4f_rotate(v, angle_in_rad);
    print_m4f(rotate_matrix);
}