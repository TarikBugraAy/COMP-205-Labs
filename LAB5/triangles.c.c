//Tarık Buğra Ay 042101100
#include <stdio.h>

// Constants for triangle classification
const float SMALL_TRIANGLE_THRESHOLD = 12.0;

// Global variables for triangle counts
static int equi_cnt, iso_cnt, sca_cnt;

// Function to classify triangles based on side lengths
void classify_triangles(float side1, float side2, float side3) {
    // Check if the triangle is small
    if ((side1 + side2 + side3) <= SMALL_TRIANGLE_THRESHOLD)
        printf("You entered a small triangle.\n");

    // Classify based on side lengths
    if (side1 == side2 && side2 == side3) 
        equi_cnt++;
    else if ((side1 == side2 && side1 != side3) || 
             (side1 == side3 && side1 != side2) ||
             (side2 == side3 && side2 != side1))
        iso_cnt++;
    else
        sca_cnt++;
}

int main() {
    while (1) {
        // Variables for triangle sides
        float side1 = 0, side2 = 0, side3 = 0;

        // User input for triangle sides
        printf("Enter the side lengths of the triangle: ");
        scanf("%f %f %f", &side1, &side2, &side3);

        // Check for exit condition
        if (side1 == -1 && side2 == -1 && side3 == -1)
            break;

        // Classify the triangle and update counts
        classify_triangles(side1, side2, side3);
    }

    // Print the counts of different types of triangles
    printf("Equilateral triangles: %d\n", equi_cnt);
    printf("Isosceles triangles: %d\n", iso_cnt);
    printf("Scalene triangles: %d\n", sca_cnt);

    return 0;
}

