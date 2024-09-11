#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NUM_DEPARTMENTS 6


struct Student {
    int unique_number;
    char name[50];
    char first_name[50];
    char date_of_birth[11];
    char department[20];
    float general_note;
};


const char departments[NUM_DEPARTMENTS][50] = {"biology", "CS", "english", "history", "mathematics", "physics"};

struct Student students[MAX_STUDENTS];

int student_count = 0;



// Comparison functions
int compare_by_name(struct Student a, struct Student b) {
    return strcmp(a.name, b.name);
}

int compare_by_general_note(struct Student a, struct Student b) {
    if (a.general_note > b.general_note) return -1;
    if (a.general_note < b.general_note) return 1;
    return 0;
}

int compare_by_success_status(struct Student a, struct Student b) {
    int a_status = a.general_note >= 10 ? 1 : 0;
    int b_status = b.general_note >= 10 ? 1 : 0;
    return b_status - a_status;
}



//compare pointer function
void bubble_sort(int (*compare)(struct Student, struct Student)) {
    int i, j;
    for (i = 0; i < student_count - 1; i++) {
        for (j = 0; j < student_count - i - 1; j++) {
            if (compare(students[j], students[j + 1]) > 0) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}






void add_student() {
    
    if (student_count >= MAX_STUDENTS) {
        printf("Student list is full.\n");
        return;
    }

    

    printf("\nEnter unique number: ");
    scanf("%d", &students[student_count].unique_number);
    printf("Enter last name: ");
    scanf("%s", students[student_count].name);
    printf("Enter first name: ");
    scanf("%s", &students[student_count].first_name);
    printf("Enter date of birth (DD/MM/YYYY): ");
    scanf("%s", &students[student_count].date_of_birth);

    
   
    int validtion = 0;
    while (!validtion)
    {
         printf("Enter department (biology, CS, english, history, mathematics, physics): ");
    scanf("%s", &students[student_count].department);
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(students[student_count].department, departments[i]) == 0)
        {
            validtion = 1;

        }
    }
    if (!validtion)
    {
     printf("wrong insertion!!! \n");
    }
    
    }

    printf("Enter general note: ");
    scanf("%f", &students[student_count].general_note);


    student_count++;

    // Sort by name after adding a new student
    bubble_sort(compare_by_name);
}

void edit_student() {
    int unique_number;
    printf("\nEnter unique number of the student to edit: \n");
    scanf("%d", &unique_number);

    int i = 0;
    while (i < student_count) {
        if (students[i].unique_number == unique_number) {
            printf("\nEditing student with unique number %d\n", unique_number);
            printf("Enter new name: ");
            scanf("%s", students[i].name);
            printf("Enter new first name: ");
            scanf("%s", students[i].first_name);
            printf("Enter new date of birth (DD/MM/YYYY): ");
            scanf("%s", students[i].date_of_birth);
            printf("Enter new department (biology, computer science, english, history, mathematics, physics): ");
            scanf("%s", students[i].department);
            printf("Enter new general note: ");
            scanf("%f", &students[i].general_note);

            
            bubble_sort(compare_by_name);
            return;
        }
        i++;
    }
    printf("Student with unique number %d not found.\n", unique_number);
}

void delete_student() {
    int unique_number;
    printf("\nEnter unique number of the student to delete: ");
    scanf("%d", &unique_number);

    int i = 0;
    while (i < student_count) {
        if (students[i].unique_number == unique_number) {
            printf("\nDeleting student with unique number... %d\n", unique_number);
            int j;
            for (j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;

            // Sort by name after deleting a student
            bubble_sort(compare_by_name);
            return;
        }
        i++;
    }
    printf("Student with unique number %d not found.\n", unique_number);
}

void view_student_details() {
    int unique_number;
    printf("\nEnter unique number of the student to view details: ");
    scanf("%d", &unique_number);

    int i = 0;
    while (i < student_count) {
        if (students[i].unique_number == unique_number) {
            printf("\nStudent Details:\n");
            printf("Unique Number: %d\n", students[i].unique_number);
            printf("Last Name: %s\n", students[i].name);
            printf("First Name: %s\n", students[i].first_name);
            printf("Date of Birth: %s\n", students[i].date_of_birth);
            printf("Department: %s\n", students[i].department);
            printf("General Note: %.2f\n", students[i].general_note);
            return;
        }
        i++;
    }
    printf("Student with unique number %d not found.\n", unique_number);
}

void calculate_overall_average() {
    float department_averages[NUM_DEPARTMENTS] = {0};
    int department_counts[NUM_DEPARTMENTS] = {0};
    float total_average = 0;
    int total_students = 0;

    int i = 0;
    while (i < student_count) {
        int dept_index = -1;
        int j = 0;
        while (j < NUM_DEPARTMENTS) {
            if (strcmp(students[i].department, departments[j]) == 0) {
                dept_index = j;
                break;
            }
            j++;
        }
        if (dept_index != -1) {
            department_averages[dept_index] += students[i].general_note;
            department_counts[dept_index]++;
            total_average += students[i].general_note;
            total_students++;
        }
        i++;
    }

    printf("\nOverall Average for Each Department:\n");
    for (int k = 0; k < NUM_DEPARTMENTS; k++) {
        if (department_counts[k] > 0) {
            printf("%s: %.2f\n", departments[k], department_averages[k] / department_counts[k]);
        }
    }

    if (total_students > 0) {
        printf("Overall Average for the University: %.2f\n", total_average / total_students);
    } else {
        printf("\nNo students to calculate average.\n");
    }
}

void show_statistics() {
    int dept_counts[NUM_DEPARTMENTS] = {0};
    int successful_students[NUM_DEPARTMENTS] = {0};
    struct Student top_students[3];
    int num_top_students = 0;

    int i = 0;
    while (i < student_count) {
        int dept_index = -1;
        int j = 0;
        while (j < NUM_DEPARTMENTS) {
            if (strcmp(students[i].department, departments[j]) == 0) {
                dept_index = j;
                break;
            }
            j++;
        }
        if (dept_index != -1) {
            dept_counts[dept_index]++;
            if (students[i].general_note >= 10) {
                successful_students[dept_index]++;
            }
            if (num_top_students < 3) {
                top_students[num_top_students] = students[i];
                num_top_students++;
            } else {
                int min_index = 0;
                for (int k = 0; k < num_top_students; k++) {
                    if (students[k].general_note > top_students[min_index].general_note) {
                         min_index = k;
                        
                    }
                }
                if (students[i].general_note > top_students[min_index].general_note) {
                         top_students[min_index] = students[i];
                    }
            }
        }
        i++;
    }



for (int i = 0; i < num_top_students - 1; i++) {
        for (int j = 0; j < num_top_students - i - 1; j++) {
            if (top_students[j].general_note > top_students[j + 1].general_note) {
                struct Student temp = top_students[j];
                top_students[j] = top_students[j + 1];
                top_students[j + 1] = temp;
            }
        }
    }


    printf ("Total student enrolled : %d\n", student_count);
    printf("Department Statistics:\n");
    for (int k = 0; k < NUM_DEPARTMENTS; k++) {
        printf("%s: Total Students = %d, Successful Students = %d\n",
               departments[k], dept_counts[k], successful_students[k]);
    }
   


    printf("Top 3 Students:\n");
    int top = 3;
    for (int k = 0; k < num_top_students; k++) {
        printf("Student %d: %s %s, General Note: %.2f\n",
               top , top_students[k].first_name, top_students[k].name, top_students[k].general_note);

               top--;

    }
}


void search_student() {
    int choice;
    printf("1. Search by Name\n");
    printf("2. List by Department\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        char search_name[50];
        printf("\nEnter name to search: ");
        scanf("%s", search_name);

        int i = 0;
        while (i < student_count) {
            if (strcmp(students[i].name, search_name) == 0) {
                printf("\nFound student with name : %s\n", search_name);
                printf("Unique Number: %d\n", students[i].unique_number);
                printf("First Name: %s\n", students[i].first_name);
                printf("Date of Birth: %s\n", students[i].date_of_birth);
                printf("Department: %s\n", students[i].department);
                printf("General Note: %.2f\n", students[i].general_note);
                return;
            }
            i++;
        }
        printf("Student with name %s not found.\n", search_name);
    } else if (choice == 2) {
        char dept_name[20];
        printf("Enter department to list (biology, computer science, english, history, mathematics, physics): ");
        scanf("%s", dept_name);

        int i = 0;
        while (i < student_count) {
            if (strcmp(students[i].department, dept_name) == 0) {
                printf("Student in department %s:\n", dept_name);
                printf("Unique Number: %d\n", students[i].unique_number);
                printf("Name: %s\n", students[i].name);
                printf("First Name: %s\n", students[i].first_name);
                printf("Date of Birth: %s\n", students[i].date_of_birth);
                printf("General Note: %.2f\n", students[i].general_note);
            }
            i++;
        }
    } else {
        printf("Invalid choice.\n");
    }
}


void sort_students() {
    int choice;
    printf("1. Sort by Name\n");
    printf("2. Sort by General Note\n");
    printf("3. Sort by Success Status\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);


    if (choice == 1) {
        bubble_sort(compare_by_name);
        printf("Students sorted by name:\n");
        for (int i = 0; i < student_count; i++) {
            printf("Name: %s %s, Unique Number: %d, General Note: %.2f\n",
                   students[i].first_name, students[i].name, students[i].unique_number, students[i].general_note);
        }
    } else if (choice == 2) {
        bubble_sort(compare_by_general_note);
        printf("Students sorted by general note:\n");
        for (int i = 0; i < student_count; i++) {
            printf("Name: %s %s, Unique Number: %d, General Note: %.2f\n",
                   students[i].first_name, students[i].name, students[i].unique_number, students[i].general_note);
        }
    } else if (choice == 3) {
        bubble_sort(compare_by_success_status);
        printf("Students sorted by success status:\n");
        for (int i = 0; i < student_count; i++) {
            printf("Name: %s %s, Unique Number: %d, General Note: %.2f\n",
                   students[i].first_name, students[i].name, students[i].unique_number, students[i].general_note);
        }
    } else {
        printf("Invalid choice.\n");
    }
}


int main() {
    int choice;

    do {
        printf("\n ___________________________________\n");
        printf("|  Main Menu:                       |\n");
        printf("|___________________________________|\n");
        printf("|1. Add Student                     |\n");
        printf("|2. Edit Student                    |\n");
        printf("|3. Delete Student                  |\n");
        printf("|4. View Student Details            |\n");
        printf("|5. Calculate Overall Average       |\n");
        printf("|6. Show Statistics                 |\n");
        printf("|7. Search for a Student            |\n");
        printf("|8. Sort Students                   |\n");
        printf("|0. Exit                            |\n");
        printf("|___________________________________|");
        printf("\nEnter your choice:");
        scanf("%d", &choice);


        if (choice == 1) {
            add_student();
        } else if (choice == 2) {
            edit_student();
        } else if (choice == 3) {
            delete_student();
        } else if (choice == 4) {
            view_student_details();
        } else if (choice == 5) {
            calculate_overall_average();
        } else if (choice == 6) {
            show_statistics();
        } else if (choice == 7) {
            search_student();
        }else if (choice == 8) {
            sort_students();
        } else if (choice == 0) {
            printf ("Exiting...\n");
        } else {
            printf("\nInvalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}