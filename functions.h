#include <stdio.h>

typedef struct student
{
    char name[10];
    int id;
    char birth_date[10];
    char address[100];
    long phone_number;
    int mark;
    struct student *next;
} student_t;

void new_student(student_t *head);
int main_menu(void);
student_t *create_student_node(void);
void delete_student(student_t **head);
void print_list(student_t *head);
void student_edit(student_t *head);
void rank_student(student_t **head);
void student_score(student_t *head);
void sort_alphabetical(student_t **head);
void student_list(student_t **head);
void sort_ascending(student_t **head);
