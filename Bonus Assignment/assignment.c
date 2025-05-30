#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    char name[100];
    int id;
    float salary;
    char department[50];
    int yearsOfExperience;
    float performanceScore;
};

void addEmployee(struct Employee **employees, int *numberOfEmployees) {
    // If this is the first employee, allocate memory
    if (*employees == NULL) {
        printf("Allocating memory\n");
        *employees = (struct Employee*) malloc(1 * sizeof(struct Employee));
    }

    // Increase employee count
    (*numberOfEmployees)++;
    
    // Dynamically allocate memory for new employee
    struct Employee *temp = (struct Employee*) realloc(*employees, *numberOfEmployees * sizeof(struct Employee));
    
    if (temp == NULL) {
        printf("Memory reallocation failed\n");
        return;
    }

    // Update original pointer to point to the new allocation
    *employees = temp;
    
    // Prompt for employee's data
    struct Employee *employee = &(*employees)[*numberOfEmployees - 1];

    while (getchar() != '\n'); // Clear '\n' from buffer
    char name[100];
    printf("Enter name of employee: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    strcpy((*employee).name, name);
    
    printf("Enter employee ID: ");
    scanf("%d", &(*employee).id);
    
    printf("Enter salary: ");
    scanf("%f", &(*employee).salary);
    
    while (getchar() != '\n'); // Clear '\n' from buffer
    char department[50];
    printf("Enter department: ");
    fgets(department, sizeof(department), stdin);
    department[strcspn(department, "\n")] = '\0';
    strcpy((*employee).department, department);
    
    printf("Enter years of experience: ");
    scanf("%d", &(*employee).yearsOfExperience);

    // Calculate performance score
    (*employee).performanceScore = 0.3 * (*employee).yearsOfExperience + 0.7 * (*employee).salary / 1000;
}

void updateEmployee(struct Employee **employees, int numberOfEmployees) {
    int employeeIdToUpdate;
    printf("Enter Employee ID to update: ");
    scanf("%d", &employeeIdToUpdate);

    for (int i = 0; i < numberOfEmployees; i++) {
        printf("%d\n", (*employees)[i].id);

        if ((*employees)[i].id == employeeIdToUpdate) {
            printf("Enter new salary: ");
            scanf("%f", &(*employees)[i].salary);

            while (getchar() != '\n'); // Clear '\n' from buffer
            char department[50];
            printf("Enter new department: ");
            fgets(department, sizeof(department), stdin);
            department[strcspn(department, "\n")] = '\0';
            strcpy((*employees)[i].department, department);

            // Update performance score
            (*employees)[i].performanceScore = 0.3 * (*employees)[i].yearsOfExperience + 0.7 * (*employees)[i].salary / 1000;

            printf("Employee information updated successfully!\n\n");
            break;
        }
    }
}

void searchEmployeeByName(struct Employee *employees, int numberOfEmployees) {
    while (getchar() != '\n'); // Clear '\n' from buffer
    char nameToSearch[100];
    printf("Enter name to search: ");
    fgets(nameToSearch, sizeof(nameToSearch), stdin);
    nameToSearch[strcspn(nameToSearch, "\n")] = '\0';

    printf("\nSearch Results: \n");

    for (int i = 0; i < numberOfEmployees; i++) {
        struct Employee *employee = &employees[i];
        
        if (strstr((*employee).name, nameToSearch) != NULL) {
            printf("Name: %s\n", (*employee).name);
            printf("Employee ID: %d\n", (*employee).id);
            printf("Salary: %.2f\n", (*employee).salary);
            printf("Department: %s\n", (*employee).department);
            printf("Years of Experience: %d\n", (*employee).yearsOfExperience);
            printf("Performance Score: %.2f\n", (*employee).performanceScore);
            printf("\n");
        }
    }
}

int compareByPerformance(const void *a, const void *b) {
    struct Employee *empA = (struct Employee *)a;
    struct Employee *empB = (struct Employee *)b;

    // Compare performance scores for sorting (descending order)
    if (empA->performanceScore > empB->performanceScore) {
        return -1; // Higher score comes first
    } else if (empA->performanceScore < empB->performanceScore) {
        return 1; // Lower score comes later
    }
    return 0; // Scores are equal, maintain order
}


void sortEmployeesByPerformance(struct Employee *employees, int numberOfEmployees) {
    qsort(employees, numberOfEmployees, sizeof(struct Employee), compareByPerformance);
}


int main(int argc, char *argv[]) {
    int numberOfEmployees = 0;
    struct Employee *employees = NULL;

    // Display menu
    int choice = 0;
    while (choice != 5) {
        printf("Employee Performance Management System\n");
        printf("1. Add Employee\n");
        printf("2. Update Employee\n");
        printf("3. Display All Employees\n");
        printf("4. Search Employee by Name\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Handle choice
        if (choice == 1) {
            addEmployee(&employees, &numberOfEmployees);
            
        } else if (choice == 2) {
            if (numberOfEmployees == 0) {
                printf("No employees to update.\n\n");
                continue;
            }

            updateEmployee(&employees, numberOfEmployees);
        } else if (choice == 3) {
            if (numberOfEmployees == 0) {
                printf("Employee Records (sorted by Performance Score):\n\n");
                printf("No employees to display.\n\n");
                continue;
            }

            sortEmployeesByPerformance(employees, numberOfEmployees);

            printf("Employee Records (sorted by Performance Score):\n\n");
            for (int i = 0; i < numberOfEmployees; i++) {
                printf("Name: %s\n", employees[i].name);
                printf("Employee ID: %d\n", employees[i].id);
                printf("Salary: %.2f\n", employees[i].salary);
                printf("Department: %s\n", employees[i].department);
                printf("Years of Experience: %d\n", employees[i].yearsOfExperience);
                printf("Performance Score: %.2f\n", employees[i].performanceScore);
                printf("\n");
            }
        } else if (choice == 4) {
            sortEmployeesByPerformance(employees, numberOfEmployees);
            searchEmployeeByName(&employees, numberOfEmployees);
        } else {
            printf("Exiting...\n");
            break;
        }
    }


    free(employees);

    return 0;
}