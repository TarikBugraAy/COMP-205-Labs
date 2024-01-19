#include <stdio.h>
#include <string.h>

#define SIZE 6 // Define the number of students
#define NUM_OF_SCORES 3 // Number of subjects

// Struct to store student information
struct Student {
    char name[100]; // Student name
    float englishGrade; // English grade
    float mathGrade; // Math grade
    float physicsGrade; // Physics grade
};

// Function to store information from file to Student struct array
void store_info(FILE* file, struct Student* stu) {
    char line[100]; // Buffer for reading lines from file
    for (int i = 0; i < SIZE; i++) { // Loop through each student
        if (fgets(line, sizeof(line), file)) { // Read a line (student's name)
            line[strcspn(line, "\n")] = 0; // Remove newline character from the read line
            strcpy(stu[i].name, line); // Copy the name to the struct
        }

        for (int j = 0; j < NUM_OF_SCORES; j++) { // Loop through each subject score
            int grade; // Temporary variable to store read grade
            if (fscanf(file, "%d\n", &grade) == 1) { // Read a grade from the file
                // Assign the grade to the respective subject in struct
                if (j == 0) stu[i].englishGrade = grade;
                if (j == 1) stu[i].mathGrade = grade;
                if (j == 2) stu[i].physicsGrade = grade;
            }
        }
    }
}

// Function to print student information and calculate averages
void print(struct Student* stu) {
    float totalEnglish = 0, totalMath = 0, totalPhysics = 0; // Variables for total grades
    for (int i = 0; i < SIZE; i++) { // Loop through each student
        // Print student's name and grades
        printf("Name: %s\n", stu[i].name);
        printf("Grades: English: %.2f, Math: %.2f, Physics: %.2f\n\n", 
               stu[i].englishGrade, stu[i].mathGrade, stu[i].physicsGrade);

        // Add grades to total
        totalEnglish += stu[i].englishGrade;
        totalMath += stu[i].mathGrade;
        totalPhysics += stu[i].physicsGrade;
    }

    // Print average grades for each subject
    printf("Average Grades:\n English: %.2f\n Math: %.2f\n Physics: %.2f\n",
           totalEnglish / SIZE, totalMath / SIZE, totalPhysics / SIZE);
}

// Main function
int main() {
    struct Student students[SIZE]; // Array of Student structs
    FILE* file = fopen("scores.txt", "r"); // Open file for reading

    if (file == NULL) { // Check if file opened successfully
        printf("Error opening file\n");
        return 1;
    }

    store_info(file, students); // Store information from file to struct array
    print(students); // Print student information and averages

    fclose(file); // Close the file
    return 0;
}