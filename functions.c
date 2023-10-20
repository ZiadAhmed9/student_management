#include "functions.h"
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define clear() printf("\033[H\033[J")

static int first_student = 1;
static int id = 1;
static student_t *head = NULL;

void new_student(student_t *head)
{
    student_t *new_pointer = create_student_node();
    if (new_pointer == 0)
    {
        return;
    }
    student_t *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = new_pointer;
}

int main_menu(void)
{
    int choice;
    while (1)
    {
        clear();
        choice = 0;
        printf("--------------------------\n");
        printf("Welcome to our school\n");
        printf("Choose from the following Options:\n");
        printf("    1.Add new student\n    2.Delete existing student\n    3.Print the student list\n    4.Edit existing student\n    5.Rank students\n    6.Add a mark to students\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            clear();
            if (first_student)
            {
                head = create_student_node();
                if (head == 0)
                {
                    return 0;
                }
                first_student--;
            }
            else
            {
                new_student(head);
            }
            break;
        case 2:
            clear();
            delete_student(&head);
            break;
        case 3:
            clear();
            student_list(&head);
            break;
        case 4:
            clear();
            student_edit(head);
            break;
        case 5:
            clear();
            rank_student(&head);
            break;
        case 6:
            clear();
            student_score(head);
            break;
        default:
            continue;
        }
    }
}

student_t *create_student_node(void)
{
    student_t *new_student = (student_t *)malloc(sizeof(student_t));
    if (new_student == 0)
    {
        clear();
        printf("ERROR!!!");
        return 0;
    }
    printf("Enter the name of the student\n");
    scanf("%s", &new_student->name);
    printf("Enter the birthdate of the student\n");
    scanf("%s", &new_student->birth_date);
    printf("Enter the address of the student\n");
    scanf("%s", &new_student->address);
    printf("Enter the phone number of the student\n");
    scanf("%ld", &new_student->phone_number);
    new_student->id = id;
    new_student->mark = 0;
    id++;
    new_student->next = NULL;
    return new_student;
}
void delete_student(student_t **head)
{
    if (*head == NULL)
    {
        printf("The list is empty");
        getchar();
        return;
    }
    int id_delete;
    student_t *current = *head;
    student_t *previous = NULL;
    clear();
    printf("Enter the ID of the student you want to delete\n");
    scanf("%d", &id_delete);
    while (current != NULL)
    {
        if (current->id == id_delete)
        {
            if (previous == NULL)
            {
                // If the student to be deleted is the first node.
                *head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            free(current); // Deallocate the memory of the deleted node
            printf("Student with ID %d has been deleted.\nPress any key to continue", id_delete);
            getchar();
            return;
        }
    }
    printf("Student with ID %d not found in the list.\n", id);
}

void print_list(student_t *head)
{
    student_t *current = head;
    while (current != NULL)
    {
        printf("Student number %d\nStudent Name is %s\nStudent address is %s\nStudent Birthdate is %s\nStudent phone number is %ld\nStudent total mark is %d\n", current->id, current->name, current->address, current->birth_date, current->phone_number, current->mark);
        printf("------------------------------------------\n");
        current = current->next;
    }
    printf("Press any key to continue\n");
    getch();
}
void student_edit(student_t *head)
 {
    int idToEdit;
    printf("Enter the ID of the student you want to edit");
    scanf("%d",&idToEdit);
    student_t *current = head;

    while (current != NULL) {
        if (current->id == idToEdit) {
            // Found the student with the given ID, so we'll edit it.
            printf("Editing Student with ID %d\n", idToEdit);
            printf("Enter the new name: ");
            scanf("%s", current->name);
            printf("Enter the new birth date: ");
            scanf("%s", current->birth_date);
            printf("Enter the new address: ");
            scanf("%s", current->address);
            printf("Enter the new phone number: ");
            scanf("%ld", &current->phone_number);
            printf("Student information updated successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("Student with ID %d not found in the list.\n", idToEdit);
}

void student_list(student_t **head)
{
    sort_alphabetical(head);
    print_list(*head);
}
void rank_student(student_t **head)
{
    sort_ascending(head);
    print_list(*head);
}
void student_score(student_t *head)
{
    student_t *current = head;
    printf("Give marks to all students");
    while (current != NULL)
    {
        printf("Please enter a mark for student %s with ID %d\n", current->name, current->id);
        scanf("%d", &current->mark);
        current = current->next;
    }
}

void sort_alphabetical(student_t **head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }

    student_t *sortedList = NULL;
    student_t *current = *head;

    while (current != NULL)
    {
        student_t *next = current->next;
        if (sortedList == NULL || strcasecmp(current->name, sortedList->name) < 0)
        {
            current->next = sortedList;
            sortedList = current;
        }
        else
        {
            student_t *sortedCurrent = sortedList;
            while (sortedCurrent->next != NULL && strcasecmp(sortedCurrent->next->name, current->name) < 0)
            {
                sortedCurrent = sortedCurrent->next;
            }
            current->next = sortedCurrent->next;
            sortedCurrent->next = current;
        }
        current = next;
    }

    *head = sortedList;
}

void sort_ascending(student_t **head)
{
    if (*head == NULL || (*head)->next == NULL)
    {
        return;
    }

    student_t *sortedList = NULL;
    student_t *current = *head;

    while (current != NULL)
    {
        student_t *next = current->next;
        if (sortedList == NULL || current->mark > sortedList->mark)
        {
            current->next = sortedList;
            sortedList = current;
        }
        else
        {
            student_t *sortedCurrent = sortedList;
            while (sortedCurrent->next != NULL && sortedCurrent->next->mark > current->mark)
            {
                sortedCurrent = sortedCurrent->next;
            }
            current->next = sortedCurrent->next;
            sortedCurrent->next = current;
        }
        current = next;
    }

    *head = sortedList; // Update the head to point to the sorted list
}