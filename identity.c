#include <stdio.h>

#include "m4f.h"
#include "io.h"

int main(int argc, char* argv[]) {
    struct m4f identity = m4f_identity();
    print_m4f(identity);
}