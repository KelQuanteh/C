#include <gsl/gsl_complex.h>
#include <stdio.h>

int main() {
    gsl_complex z1 = gsl_complex_rect(3.0, 4.0); // Create a complex number 3 + 4i
    gsl_complex z2 = gsl_complex_rect(2.0, -1.0); // Create a complex number 2 - 1i

    gsl_complex sum = gsl_complex_add(z1, z2); // Add z1 and z2
    gsl_complex product = gsl_complex_mul(z1, z2); // Multiply z1 and z2

    printf("Sum: %f + %fi\n", GSL_REAL(sum), GSL_IMAG(sum));
    printf("Product: %f + %fi\n", GSL_REAL(product), GSL_IMAG(product));

    return 0;
}