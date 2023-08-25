#include <stdio.h>
#include <string.h>
#include <time.h>

int currentDay, currentMonth, currentYear;
struct University university;
int students = 0;


struct Subject {
    char name[50];
};

struct SubjectList {
    struct Subject subjects[10];
};


struct Course 
{
    char name[35];
    struct SubjectList subjectList;
    int price;
};

struct Address
{
    char street[10];
    char district[30];
    char city[10];
    char country[10];
};

struct Student
{
    char name[20];
    int age;
    char registration[15];
    struct Address address;
    struct Course course;
    int period;
    int monthlyPayment;
};

struct University 
{
    char name[23];
    struct Student students[5];
    struct Course courses[3];
};

// strcpy

void getYear()
{
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);
    localTime = localtime(&currentTime);

    currentYear = localTime->tm_year + 1900;
    currentMonth = localTime->tm_mon + 1;
    currentDay = localTime->tm_mday;
};

void getUniversityData(struct University *university)
{    
    strcpy(university->name, "Universidade Católica");

    struct Course courses[3] = {
        {"Analysis and Systems Development",
        {"Algoritmos e programação estruturada", "Modelagem de banco de dados", "Sistemas computacionais"},
        100},
        {"Software Engineering", 
        {"Algoritmos e programação estruturada", "Modelagem de banco de dados", "Sistemas computacionais"},
        100},
        {"Computer Science", 
        {"Algoritmos e programação estruturada", "Modelagem de banco de dados", "Sistemas computacionais"},
        100}
};

    for(int i = 0; i < 3; i++) {
        university->courses[i] = courses[i];
    }
};

void setConfigs() 
{
    getYear();
    getUniversityData(&university);
};

void clearBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
};

int setStudentAge(struct Student *student)
{
    int birthYear, birthMonth, birthDay;
    printf("Data de nascimento do estudante...\n");
    printf("dia: ");
    scanf("%2d", &birthDay );
    clearBuffer();
    
    printf("mês: ");
    scanf("%2d", &birthMonth );
    clearBuffer();
    
    printf("ano: ");
    scanf("%4d", &birthYear );
    
    int age = currentYear - birthYear;

    // adjust age
    if (currentMonth < birthMonth || currentDay < birthDay) age--;

    student->age = age;
};

void setStudentAddress(struct Student *student)
{
    printf("Endereço do estudante... \n");
    clearBuffer();

    printf("rua: ");
    fgets(student->address.street, 10, stdin);

    printf("bairro: ");
    fgets(student->address.district, 30, stdin);

    printf("cidade: ");
    fgets(student->address.city, 10, stdin);

    printf("país: ");
    fgets(student->address.country, 10, stdin);
};

void setStudentCourse(struct Student *student) 
{
    printf("Selecione seu curso:\n");

    for(int i = 0; i < 3; i++) {
        printf("%d%c%s\n", i + 1, ' ', university.courses[i].name);
    };

    int courseOption;
    scanf("%1d", &courseOption);
    clearBuffer();

    courseOption--;
    student->course = university.courses[courseOption];
    student->monthlyPayment = university.courses[courseOption].price;
    student->period = 1;
};

void setStudentRegistration(struct Student *student)
{
    strcpy(student->registration, "A1B2C3D4E5");
};

void listStudents() 
{
    printf("estudantes: \n");
    int i;
    for(i = 0; i < 3; i++)
    {
        printf("%s\n", university.students[i].name);
    };
};

void showRegisteredStudentData(struct Student *student)
{
    printf("name: %s\n", student->name);
    printf("age: %d\n", student->age);
    printf("course: %s\n", student->course.name);
    printf("course period: %d\n", student->period);
    printf("course payment: %d\n", student->monthlyPayment);
    printf("registration: %s\n", student->registration);
    printf("address:\n street: %s\n district: %s\n city: %s\n country: %s\n", student->address.street, student->address.district, student->address.city, student->address.country);
};

void createStudent()
{
    struct Student student;

    printf("Nome do estudante: ");
    fgets(student.name, 20, stdin);

    setStudentAge(&student);

    setStudentAddress(&student);
    
    setStudentCourse(&student);

    setStudentRegistration(&student);

    int studentsLength = sizeof(university.students) / sizeof(university.students[0]);

    university.students[students] = student; 
    students++;
    showRegisteredStudentData(&student);
};

int main()
{
    setConfigs();
    printf("Bem vindo ao portal do estudante!\n\n");
    printf("Escolha uma opção.\n");
    printf("1 - Criar estudante\n");
    printf("2 - Listar estudantes\n");

    int option;
    scanf("%1d", &option);
    clearBuffer();

    switch(option)
    {
        case 1: 
        {
            createStudent();
            main();
            break;
        }
        case 2: 
        {
            listStudents();
            break;
        }
    };
    
    return 0;
};



