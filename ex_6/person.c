#include "person.h"
#include "string.h"
#include "stdlib.h"
#include <stdio.h>

void swapPersons(void* arr, int i, int j)
{
    Person *perArr=(Person*)arr;
    Person temp=perArr[i];
    perArr[i]=perArr[j];
    perArr[j]=temp;
}
void load(const char* inputFile, Person persons[], int* numOfPersonsPtr)
{
    FILE* input = fopen(inputFile, "r");
    if (!input) {
        printf("File not found: %s\n", inputFile);
        return;
    }
    char buffer[MAX_STR_LEN];
    while (fgets(buffer, MAX_STR_LEN, input)) {
        printf("%s", buffer);
        int personIndex=*(numOfPersonsPtr);
        *numOfPersonsPtr+=1;
        char* tokPtr= strtok(buffer,DELIM);

            strcpy(persons[personIndex].firstName,tokPtr);
            tokPtr=strtok(NULL,DELIM);
            strcpy(persons[personIndex].lastName,tokPtr);
            tokPtr=strtok(NULL,DELIM);
            persons[personIndex].dateOfBirth.day=atoi(tokPtr);
            tokPtr=strtok(NULL,DELIM);
            persons[personIndex].dateOfBirth.month=atoi(tokPtr);
            tokPtr=strtok(NULL,DELIM);
            persons[personIndex].dateOfBirth.year=atoi(tokPtr);
            tokPtr=strtok(NULL,DELIM);
            persons[personIndex].height= atoi((tokPtr));
            tokPtr=strtok(NULL,"\n");
            persons[personIndex].weight= atof(tokPtr);

    }
    if (fclose(input)) {
        printf("Error with closing file: %s\n", inputFile);
        return;
    }
}

void save(const char* outputFile, Person persons[], int numOfPersons)
{
    FILE* output = fopen(outputFile, "a");
    if (!output) {
        printf("Error with file: %s\n", outputFile);
        return;
    }
    for(int i=0;i<numOfPersons;i++)
    {
        fprintf(output, "%s,%s,%d,%d,%d,%d,%.2f\n",persons[i].firstName,persons[i].lastName,persons[i].dateOfBirth.day,persons[i].dateOfBirth.month,persons[i].dateOfBirth.year,persons[i].height,persons[i].weight);
    }
    if (fclose(output)) {
        printf("Error with closing file: %s\n", outputFile);
        return;
    }
}

int comparePersonByFirstName(void* arr, int i, int j)
{
    Person *perArr=(Person*)arr;
    int isBigger=strcmp(perArr[i].firstName,perArr[j].firstName);
    if(isBigger<0)
    {
        return 1;
    }
    return 0;
}
int comparePersonByLastName(void* arr, int i, int j)
{
    Person *perArr=(Person*)arr;
    int isBigger=(strcmp(perArr[i].lastName,perArr[j].lastName));
    if(isBigger<0)
        return 1;
    return 0;
}
int comparePersonByWeight(void* arr, int i, int j)
{
    Person *perArr = (Person *) arr;
    int isBigger = (perArr[i].weight < perArr[j].weight);
    if (isBigger > 0)
        return 1;
    return 0;
}
int comparePersonByHeight(void* arr, int i, int j)
{
    Person *perArr = (Person *) arr;
    int isBigger = (perArr[i].height < perArr[j].height);
    if (isBigger > 0)
        return 1;
    return 0;
}
static double toMeter(int height)
{
    double meterHeight=(double) height;
    meterHeight/=100;
    return meterHeight;
}

int comparePersonByBMI(void* arr, int i, int j)
{
    Person *perArr = (Person *) arr;
    double firstHeight=toMeter(perArr[i].height);
    double secondHeight= toMeter(perArr[j].height);
    double firstBMI=((perArr[i].weight)/(firstHeight*firstHeight));
    double secondBMI=((perArr[j].weight)/(secondHeight*secondHeight));
    if(firstBMI<secondBMI)
        return 1;
    return 0;
}
int comparePersonByDate(void* arr, int i, int j)
{
    Person *perArr = (Person *) arr;
    if(perArr[i].dateOfBirth.year<perArr[j].dateOfBirth.year)
        return 1;
    if(perArr[i].dateOfBirth.year==perArr[j].dateOfBirth.year)
    {
        if (perArr[i].dateOfBirth.month < perArr[j].dateOfBirth.month)
        {
            return 1;
        }
        if(perArr[i].dateOfBirth.month==perArr[j].dateOfBirth.month)
        {
            if (perArr[i].dateOfBirth.day < perArr[j].dateOfBirth.day)
                return 1;

        }
    }
    return  0;
}
