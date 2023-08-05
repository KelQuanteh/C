#include <stdio.h> 
#include <string.h> 

#define tam 100

typedef struct student_t
{
  char name[100];
  int age;
  int grade; 
} student ;

void initVect (student s[], int size){
    for(int i= 0; i< size; i++){
        strcpy(s[i].name, ""); 
        s[i].age = 0; 
        s[i].grade = 0; 
    }
}

int main(){
    student students[tam]; 
    initVect(students, tam);

    int size_of_students = sizeof(students);
    printf("size of students: %d\n", size_of_students);
 
    int num_of_students = sizeof(students) / sizeof(students[0]);
    printf("Number of students: %d\n", num_of_students);

    return 0; 
}
