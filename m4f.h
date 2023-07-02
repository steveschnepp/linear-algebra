#ifndef __M4F_H__
#define __M4F_H__

#include "v3f.h"

struct m4f {
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;
};

static inline
float* m4f_to_f16v(struct m4f *m) {
	return (float *) m; // Raw cast
}

static inline
struct m4f* f16v_to_m4f(float *m) {
	return (struct m4f *) m; // Raw cast
}

static inline
struct m4f m4f_scale(float x, float y, float z) {
    struct m4f m = {0};
    m.m11 = x;
    m.m22 = y;
    m.m33 = z;
    m.m44 = 1;
    return m;
}

static inline
struct m4f m4f_identity() {
    return m4f_scale(1, 1, 1);
}

static inline
struct m4f m4f_translate(float x, float y, float z) {
    struct m4f m = m4f_identity();
    m.m14 = x;
    m.m24 = y;
    m.m34 = z;
    return m;
}

static inline
struct m4f m4f_rotate_x(float rad) {
    struct m4f m = m4f_identity();
    m.m22 = cosf(rad);
    m.m23 = sinf(rad);
    m.m32 =-sinf(rad);
    m.m33 = cosf(rad);
    return m;
}

static inline
struct m4f m4f_rotate_y(float rad) {
    struct m4f m = m4f_identity();
    m.m11 =  cosf(rad);
    m.m13 =  sinf(rad);
    m.m31 = -sinf(rad);
    m.m33 =  cosf(rad);
    return m;
}

static inline
struct m4f m4f_rotate_z(float rad) {
    struct m4f m = m4f_identity();
    m.m11 =  cosf(rad);
    m.m12 =  sinf(rad);
    m.m21 = -sinf(rad);
    m.m22 =  cosf(rad);
    return m;
}

/* n is the unit vector that is normal to the rotation plane */
static inline
struct m4f m4f_rotate(struct v3f n, float rad)
{
    struct m4f m = {0};

    m.m11 = n.x * n.x * ( 1 - cosf(rad) ) + cosf(rad);
    m.m12 = n.x * n.y * ( 1 - cosf(rad) ) - n.z * sinf(rad);
    m.m13 = n.x * n.z * ( 1 - cosf(rad) ) + n.y * sinf(rad);

    m.m21 = n.y * n.x * ( 1 - cosf(rad) ) + n.z * sinf(rad);
    m.m22 = n.y * n.y * ( 1 - cosf(rad) ) + cosf(rad) ;
    m.m23 = n.y * n.z * ( 1 - cosf(rad) ) - n.x * sinf(rad);

    m.m31 = n.z * n.x * ( 1 - cosf(rad) ) - n.y * sinf(rad);
    m.m32 = n.z * n.y * ( 1 - cosf(rad) ) + n.x * sinf(rad);
    m.m33 = n.z * n.z * ( 1 - cosf(rad) ) + cosf(rad);

    m.m44 = 1.0f;

    return m;
}

static inline
struct m4f m4f_add(struct m4f this, struct m4f m)
{
    this.m11 += m.m11; this.m12 += m.m12; this.m13 += m.m13; this.m14 += m.m14;
    this.m21 += m.m21; this.m22 += m.m22; this.m23 += m.m23; this.m24 += m.m24;
    this.m31 += m.m31; this.m32 += m.m32; this.m33 += m.m33; this.m34 += m.m34;
    this.m41 += m.m41; this.m42 += m.m42; this.m43 += m.m43; this.m44 += m.m44;
    return this;
}

static inline
struct m4f m4f_sub(struct m4f this, struct m4f m)
{
    this.m11 -= m.m11; this.m12 -= m.m12; this.m13 -= m.m13; this.m14 -= m.m14;
    this.m21 -= m.m21; this.m22 -= m.m22; this.m23 -= m.m23; this.m24 -= m.m24;
    this.m31 -= m.m31; this.m32 -= m.m32; this.m33 -= m.m33; this.m34 -= m.m34;
    this.m41 -= m.m41; this.m42 -= m.m42; this.m43 -= m.m43; this.m44 -= m.m44;
    return this;
}

static inline
struct m4f m4f_cross(struct m4f this, struct m4f m)
{
    struct m4f c;
    c.m11 = this.m11 * m.m11 + this.m12 * m.m21 + this.m13 * m.m31 + this.m14 * m.m41;
    c.m12 = this.m11 * m.m12 + this.m12 * m.m22 + this.m13 * m.m32 + this.m14 * m.m42;
    c.m13 = this.m11 * m.m13 + this.m12 * m.m23 + this.m13 * m.m33 + this.m14 * m.m43;
    c.m14 = this.m11 * m.m14 + this.m12 * m.m24 + this.m13 * m.m34 + this.m14 * m.m44;

    c.m21 = this.m21 * m.m11 + this.m22 * m.m21 + this.m23 * m.m31 + this.m24 * m.m41;
    c.m22 = this.m21 * m.m12 + this.m22 * m.m22 + this.m23 * m.m32 + this.m24 * m.m42;
    c.m23 = this.m21 * m.m13 + this.m22 * m.m23 + this.m23 * m.m33 + this.m24 * m.m43;
    c.m24 = this.m21 * m.m14 + this.m22 * m.m24 + this.m23 * m.m34 + this.m24 * m.m44;

    c.m31 = this.m31 * m.m11 + this.m32 * m.m21 + this.m33 * m.m31 + this.m34 * m.m41;
    c.m32 = this.m31 * m.m12 + this.m32 * m.m22 + this.m33 * m.m32 + this.m34 * m.m42;
    c.m33 = this.m31 * m.m13 + this.m32 * m.m23 + this.m33 * m.m33 + this.m34 * m.m43;
    c.m34 = this.m31 * m.m14 + this.m32 * m.m24 + this.m33 * m.m34 + this.m34 * m.m44;

    c.m41 = this.m41 * m.m11 + this.m42 * m.m21 + this.m43 * m.m31 + this.m44 * m.m41;
    c.m42 = this.m41 * m.m12 + this.m42 * m.m22 + this.m43 * m.m32 + this.m44 * m.m42;
    c.m43 = this.m41 * m.m13 + this.m42 * m.m23 + this.m43 * m.m33 + this.m44 * m.m43;
    c.m44 = this.m41 * m.m14 + this.m42 * m.m24 + this.m43 * m.m34 + this.m44 * m.m44;
    return c;
}


static inline
struct v3f m4f_apply(struct m4f this, struct v3f v)
{
    struct v3f c; // We pretend to append a 1 at the end
    c.x = v.x * this.m11 + v.y * this.m12 + v.z * this.m13 + 1 * this.m14;
    c.y = v.x * this.m21 + v.y * this.m22 + v.z * this.m23 + 1 * this.m24;
    c.z = v.x * this.m31 + v.y * this.m32 + v.z * this.m33 + 1 * this.m34;
    // We don't care about the last
    return c;
}

static inline
struct m4f m4f_transpose(struct m4f this) {
    struct m4f m = {
        this.m11, this.m21, this.m31, this.m41,
        this.m12, this.m22, this.m32, this.m42,
        this.m13, this.m23, this.m33, this.m43,
        this.m14, this.m24, this.m34, this.m44,
    };
    return m;
}

#endif // #ifndef __M4F_H__
