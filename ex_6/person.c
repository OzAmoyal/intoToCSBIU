/***********************
* Oz Shlomi Amoyal
* ex_6
***********************/

#include "person.h"
#include "string.h"
#include "stdlib.h"
#include <stdio.h>

/******************
* Function Name:swapPersons
* Input:void* arr(Person arry),int i(index of person to swap),int j(index of person to swap)
* Output:none
* Function Operation:gets an arary of Person and indexes of persons in the array and swaps between them
******************/

void swapPersons(void* arr, int i, int j)
{
    Person *perArr=(Person*)arr;
    Person temp=perArr[i];
    perArr[i]=perArr[j];
    perArr[j]=temp;
}

/******************
* Function Name:load
* Input:const char* inputFile(file name),Person persons[] (array to load data into),int* numOfPersonsPtr(persons counter)
* Output:none
* Function Operation:gets a file to read from and loads the data into a Person array,and updates the counter of persons
******************/
void load(const char* inputFile, Person persons[], int* numOfPersonsPtr)
{
    //open file in read mode
    FILE* input = fopen(inputFile, "r");
    //if file open fails
    if (!input) {
        printf("File not found: %s\n", inputFile);
        return;
    }
    char buffer[MAX_STR_LEN];
    //while there are still lines in the file to read enter the next line into the buffer array
    while (fgets(buffer, MAX_STR_LEN, input)) {
        //get the index of the last place in the array
        int personIndex=*(numOfPersonsPtr);
        //increase counter by one
        *numOfPersonsPtr+=1;
        //strtok to divide the data into the right place in the person struct
        char* tokPtr= strtok(buffer,DELIM);
        //enter firstname to person in the array
        strcpy(persons[personIndex].firstName,tokPtr);
        tokPtr=strtok(NULL,DELIM);
        //enter lastname into person in the array
        strcpy(persons[personIndex].lastName,tokPtr);
        tokPtr=strtok(NULL,DELIM);
        //enter date of birth into the person in the array
        persons[personIndex].dateOfBirth.day=atoi(tokPtr);
        tokPtr=strtok(NULL,DELIM);
        persons[personIndex].dateOfBirth.month=atoi(tokPtr);
        tokPtr=strtok(NULL,DELIM);
        persons[personIndex].dateOfBirth.year=atoi(tokPtr);
        tokPtr=strtok(NULL,DELIM);
        //enter height into the person in the array using atoi function
        persons[personIndex].height= atoi((tokPtr));
        tokPtr=strtok(NULL,"\n");
        //enter height into the person in the array using atof function
        persons[personIndex].weight= atof(tokPtr);

    }
    //if file close failed
    if (fclose(input)) {
        printf("Error with closing file: %s\n", inputFile);
        return;
    }
}
/******************
* Function Name:save
* Input:const char* outputFile(file name),Person persons[] (array to load data into),int numOfPersonsPtr(persons counter)
* Output:none
* Function Operation:exports data from the persons array into a text file
******************/
void save(const char* outputFile, Person persons[], int numOfPersons)
{
    //open file in read+write mode
    FILE* output = fopen(outputFile, "a");
    //if file open fails
    if (!output) {
        printf("Error with file: %s\n", outputFile);
        return;
    }
    //for every person in the array
    for(int i=0;i<numOfPersons;i++)
    {
        //put data into file
        fprintf(output, "%s,%s,%d,%d,%d,%d,%.2f\n",persons[i].firstName,persons[i].lastName,persons[i].dateOfBirth.day,
                persons[i].dateOfBirth.month,persons[i].dateOfBirth.year,persons[i].height,persons[i].weight);
    }
    //if file close fails
    if (fclose(output)) {
        printf("Error with closing file: %s\n", outputFile);
        return;
    }
}
/******************
* Function Name:comparePersonByFirstName
* Input:void* arr(persons array), int i(first person index), int j(second person index)
* Output:0 or 1
* Function Operation:compares 2 persons from the array by lexicographic value of firstName,if first has smaller value
                    the function returns 1 else returns zero
******************/
int comparePersonByFirstName(void* arr, int i, int j)
{
    Person *perArr=(Person*)arr;
    //compare between firstName by lexicographic value
    int isBigger=strcmp(perArr[i].firstName,perArr[j].firstName);
    if(isBigger<0)
    {
        return 1;
    }
    return 0;
}
/******************
* Function Name:comparePersonByLastName
* Input:void* arr(persons array), int i(first person index), int j(second person index)
* Output:0 or 1
* Function Operation:compares 2 persons from the array by lexicographic value of lastName,if first has smaller value
                    the function returns 1 else returns zero
******************/
int comparePersonByLastName(void* arr, int i, int j)
{
    Person *perArr=(Person*)arr;
    //compare between lastName by lexicographic value
    int isBigger=(strcmp(perArr[i].lastName,perArr[j].lastName));
    if(isBigger<0)
        return 1;
    return 0;
}
/******************
* Function Name:comparePersonByWeight
* Input:void* arr(persons array), int i(first person index), int j(second person index)
* Output:0 or 1
* Function Operation:compares 2 persons from the array by Weight,if first weighs more
                    the function returns 1 else returns zero
******************/
int comparePersonByWeight(void* arr, int i, int j)
{
    Person *perArr = (Person *) arr;
    int isSecondBigger = (perArr[i].weight < perArr[j].weight);
    //compare between Weight
    if (isSecondBigger > 0)
        return 1;
    return 0;
}
/******************
* Function Name:comparePersonByHeight
* Input:void* arr(persons array), int i(first person index), int j(second person index)
* Output:0 or 1
* Function Operation:compares 2 persons from the array by Height,if first is higher
                    the function returns 1 else returns zero
******************/
int comparePersonByHeight(void* arr, int i, int j)
{
    Person *perArr = (Person *) arr;
    //compare between Height
    int isSecondBigger = (perArr[i].height < perArr[j].height);
    if (isSecondBigger > 0)
        return 1;
    return 0;
}
/******************
* Function Name:toMeter
* Input:int height(valid values >0)
* Output:double meterHeight
* Function Operation:get a height in cm and convert it to meter
******************/
static double toMeter(int height)
{
    double meterHeight=(double) height;
    meterHeight/=100;
    return meterHeight;
}
/******************
* Function Name:comparePersonByBMI
* Input:void* arr(persons array), int i(first person index), int j(second person index)
* Output:0 or 1
* Function Operation:calculates and compares 2 persons from the array by BMI,if first has a smaller BMI value
                    the function returns 1 else returns zero
******************/
int comparePersonByBMI(void* arr, int i, int j)
{
    Person *perArr = (Person *) arr;
    //conversion of height from cm to Meter using the toMeter fucntion
    double firstHeight=toMeter(perArr[i].height);
    double secondHeight= toMeter(perArr[j].height);
    //calculate both BMI values
    double firstBMI=((perArr[i].weight)/(firstHeight*firstHeight));
    double secondBMI=((perArr[j].weight)/(secondHeight*secondHeight));
    //compare between BMI

        return 1;
    return 0;
}
/******************
* Function Name:comparePersonByDate
* Input:void* arr(persons array), int i(first person index), int j(second person index)
* Output:0 or 1
* Function Operation:compares 2 persons from the array by DateOfBirth, if the first person is older
                    the function returns 1 else returns zero
******************/
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
