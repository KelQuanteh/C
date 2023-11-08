#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

// Define a custom structure to represent complex numbers with real and imaginary parts.
typedef struct {
    double real;
    double imag;
} ComplexNumber;

int main() {
    ComplexNumber num;

    // Prompt the user to enter the real part of the complex number.
    printf("Enter the real part: ");
    scanf("%lf", &num.real);

    // Prompt the user to enter the imaginary part of the complex number.
    printf("Enter the imaginary part: ");
    scanf("%lf", &num.imag);

    // Create a GSL complex number from the user-provided real and imaginary parts.
    gsl_complex z = gsl_complex_rect(num.real, num.imag);

    // Calculate the exponential of the complex number.
    gsl_complex result = gsl_complex_exp(z);

    // Extract the real and imaginary parts of the result.
    double real_result = GSL_REAL(result);
    double imag_result = GSL_IMAG(result);

    // Display the result, which is the exponential of the input complex number.
    printf("Result: %f + %fi\n", real_result, imag_result);

    return 0;
}
