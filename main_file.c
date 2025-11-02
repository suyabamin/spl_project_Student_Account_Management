#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[100];
    char gender;
    char bldgrp[100];
    int ID;
    char guardian[100];
    int section;
    int age;
    char father_name[20];
    char mother_name[20];
    char progam_name[20];
    int admission_test_marks;
};

void addStudent(struct Student p[], int *srl);
void savetofile(struct Student p[], int srl);
void srchStudent(int ID);
void rmvStudent(int ID);
void admitStudent(int ID, const char date[]);

int main()
{
    int chc1, chc2 = 0, srl;
    char date[20];
    FILE *srlF;
    srlF = fopen("Serial.txt", "r");
    if (srlF == NULL)
    {
        srl = 0;
    } else
    {
        fscanf(srlF, "%d", &srl);
        fclose(srlF);
    }

    int cntct, sCntct;
    struct Student p[150];

    while(1)
    {
        LOGin:
        printf("\n1. Student Login.");
        printf("\n2. Authority Login.\n");
        printf("Enter choice: ");
        scanf("%d", &chc1);

        if (chc1 == 1)
        {
            printf("Enter student ID To Login: ");
            scanf("%d", &sCntct);
            srchStudent(sCntct);
        }
        else if (chc1 == 2)
        {
            while (chc2 != 7)
            {
                printf("1. ADD STUDENT.\n");
                printf("2. SAVE STUDENT INFO TO FILE\n");
                printf("3. SEARCH STUDENT.\n");
                printf("4. ADMIT STUDENT.\n");
                printf("5. REMOVE STUDENT.\n");
                printf("6. Return to Log In.\n");
                printf("7. EXIT\n");
                printf("Enter choice: ");
                scanf("%d", &chc2);
                getchar();

                switch (chc2)
                {
                    case 1:
                        addStudent(p, &srl);
                        srlF = fopen("Serial.txt", "w");
                        fprintf(srlF, "%d", srl);
                        fclose(srlF);
                        break;
                    case 2:
                        savetofile(p, srl);
                        printf("Student Info saved to File\n");
                        break;
                    case 3:
                        printf("Enter Student ID: ");
                        scanf("%d", &sCntct);
                        srchStudent(sCntct);
                        break;

                    case 4:
                        printf("Enter Student ID: ");
                        scanf("%d" , &cntct);
                        printf("Date(day-month-year): ");
                        scanf("%s", date);
                        admitStudent(cntct , date);
                        break;
                    case 5:
                        printf("Student ID: ");
                        scanf("%d", &sCntct);
                        rmvStudent(sCntct);
                        srl--;
                        srlF = fopen("Serial.txt", "w");
                        fprintf(srlF, "%d", srl);
                        fclose(srlF);
                        break;
                    case 6:
                        goto LOGin;
                        break;
                    case 7:
                        return 0;
                }
            }
        }
        else
            printf("WRONG INPUT. Try again.\n");
    }

    return 0;
}

void addStudent(struct Student p[], int *srl)
{
    printf("Name(please add a space first): ");
    getchar();
    gets(p[*srl].name);

    printf("Gender (F/M): ");
    scanf("%c", &p[*srl].gender);
    getchar();

    printf("Blood Group: ");
    gets(p[*srl].bldgrp);

    printf("ID: ");
    scanf("%d", &p[*srl].ID);
    getchar();

    printf("Guardian: ");
    gets(p[*srl].guardian);


    p[*srl].section = *srl + 1;
    printf("Section: %d\n", p[*srl].section);

    printf("Age: ");
    scanf("%d", &p[*srl].age);
    getchar();

    printf("Father name: ");
    gets(p[*srl].father_name);

    printf("Mother name: ");
    gets(p[*srl].mother_name);

    printf("Program name: ");
    gets(p[*srl].progam_name);

    printf("Admission test marks: ");
    scanf("%d", &p[*srl].admission_test_marks);
    getchar();

    (*srl)++;
}

void savetofile(struct Student p[], int srl)
{
    for (int i = 0; i < srl; i++) {
        char filename[20];
        sprintf(filename, "%d.txt", p[i].ID);
        FILE *pFile = fopen(filename, "a");

        if (pFile == NULL)
        {
            perror("Error opening file.");
            continue;
        }

        fprintf(pFile, "Student %d\n", i + 1);
        fprintf(pFile, "Name: %s\n", p[i].name);
        fprintf(pFile, "Gender: %c\n", p[i].gender);
        fprintf(pFile, "Blood Group: %s\n", p[i].bldgrp);
        fprintf(pFile, "Contact: %d\n", p[i].ID);
        fprintf(pFile, "Guardian: %s\n", p[i].guardian);
        fprintf(pFile, "Section: %d\n", p[i].section);
        fprintf(pFile, "Age: %d\n", p[i].age);
        fprintf(pFile, "Father name: %s\n", p[i].father_name);
        fprintf(pFile, "Mother name: %s\n", p[i].mother_name);
        fprintf(pFile, "Program name: %s\n", p[i].progam_name);
        fprintf(pFile, "\n");

        fclose(pFile);
    }
}

void srchStudent(int ID)
{
    FILE *pFile;
    char fileName[20];
    char line[1000];
    sprintf(fileName, "%d.txt", ID);
    pFile = fopen(fileName, "r");

    if (pFile == NULL)
    {
        perror("Error opening file\n");
        return;
    }
    while (fgets(line, sizeof(line), pFile) != NULL)
    {
        printf("%s", line);
    }
    fclose(pFile);
}

void rmvStudent(int ID)
{
    char filename[20];
    sprintf(filename, "%d.txt", ID);
    if (remove(filename) == 0)
    {
        printf("Student removed successfully.\n");
    }
    else
    {
        printf("Error: Removing Student Failed.\n");
    }
}

void admitStudent(int ID, const char date[])
{
    FILE *addmit;
    addmit=fopen("AdmitStudent.txt" , "a");
    if(addmit==NULL)
    {
        perror("Error opening file");
        return;
    }
    fprintf(addmit , "%d\t\t\t\t%s\n", ID, date);

    fclose(addmit);
}
