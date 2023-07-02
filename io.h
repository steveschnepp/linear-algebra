#ifndef __IO_H__
#define __IO_H__

#include <stdio.h>

#include "v3f.h"
#include "m4f.h"

static inline
int print_m4f(struct m4f m) {
    printf("%f %f %f %f\n", m.m11, m.m12, m.m13, m.m14);
    printf("%f %f %f %f\n", m.m21, m.m22, m.m23, m.m24);
    printf("%f %f %f %f\n", m.m31, m.m32, m.m33, m.m34);
    printf("%f %f %f %f\n", m.m41, m.m42, m.m43, m.m44);
}

static inline
struct m4f scan_m4f() {
    float f[16] = { 0 };
    for (int i = 0; i < 16; i ++) {
        scanf("%f", &f[i]);
    }

    struct m4f m = *f16v_to_m4f(f);
    return m;
}

static inline
struct m4f sscan_m4f_args(char* argv[]) {
    float f[16] = { 0 };
    for (int i = 0; i < 16; i ++) {
        sscanf(argv[i], "%f", &f[i]);
    }

    struct m4f m = *f16v_to_m4f(f);
    return m;
}

static inline
int print_v3f(struct v3f v) {
    printf("%f %f %f\n", v.x, v.y, v.z);
}

#endif // #ifndef __IO_H__
