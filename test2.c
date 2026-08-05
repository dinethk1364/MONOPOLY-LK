#include <stdio.h>
#include <locale.h>

int main() {
    // Set the locale to the user's environment default (usually en_US or similar)
    setlocale(LC_NUMERIC, "");

    float num = 30000.00f;

    // The '\'' flag adds thousands separators based on locale
    // "%.2'f" specifies 2 decimal places with separators
    printf("%' .2f\n", num); // Output: 30,000.00
    printf("%'.0f\n", num);  // Output: 30,000

    return 0;
}