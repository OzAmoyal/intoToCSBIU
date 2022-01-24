#include <stdio.h>
#include <math.h>

/******************
* Function Name: hello
* Input: None
* Output: "hello \/\/orld %d\n"
* Function Operation: the function prints the requested expression with the special symbols
******************/

void hello() {
printf("\"hello \\/\\/orld %%d\\n\"\n"); //print the requested expression to the user with the special symbols.
}

/******************
* Function Name:distance
* Input: int x1,x2,y1,y2 (valid value - any Integer)
* Output: double(values are bigger than 0)
* Function Operation: the function calculates the distance between the given coordinates
******************/

void distance() {
int x1,x2,y1,y2; //variables for the coordinates
printf("Enter x1:\n");
scanf("%d",&x1);
printf("Enter y1:\n");
scanf("%d",&y1);
printf("Enter x2:\n");
scanf("%d",&x2);
printf("Enter y2:\n");
scanf("%d",&y2);
double distance=sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))); //the calculation of the distance between two coordinates
printf("The distance between the points is: %.4f\n",distance); //show the calculation to the user

}

/******************
* Function Name: conversions
* Input: unsigned long long int nanoMeterInput (valid value 0<=nanoMeterInput<1e11)
* Output:double outputs (values between 0000.0000-10000.0000 )
* Function Operation:the function converts the given length in Nanometer to Kilometer, Meter,Decimeter,Centimeter,and Milimeter,
         and prints the conversions and also the given number with the matching symbol for the unit afterwards.
******************/

void conversions() {
    //constants we need to calculate the different units
    const double KM_TO_NM=1e12;
    const double METER_TO_NM=1e9;
    const double DM_TO_NM=1e8;
    const double CM_TO_NM=1e7;
    const double MM_TO_NM=1e6;

    unsigned long long int nanoMeterInput; //variable to get input of length from the user
    
    printf("Please enter nm:\n");
    scanf("%llu",&nanoMeterInput);
    double nanoMeter=(double)nanoMeterInput; //convert the input to double type
    //convert the number to the desired unit with the constants and print it
    printf("%010.4f km\n%010.4f m\n%010.4f dm\n%010.4f cm\n%010.4f mm\n%0.10llu nm\n",
            nanoMeter/KM_TO_NM,nanoMeter/METER_TO_NM,nanoMeter/DM_TO_NM,nanoMeter/CM_TO_NM,nanoMeter/MM_TO_NM,nanoMeterInput);


}

/******************
* Function Name:baking
* Input: int howManyHours,hoursOfEnter(valid values 0<=x<=24),
            howManyMinutes,minutesOfEnter (valid values 0<=x<=60),
            howManySeconds,,secondOfEnter (valid values 0<=x<=60)
* Output:char [hh:mm:ss] where hh=int readyHour, mm=int readyMinute, ss=int readySecond 
* Function Operation: the function gets the time that the cake needs to be baked and the time it entered into the over,
                    and it calculates when will the cake be ready
******************/

void baking() {
    const int SECANDMIN=60; //constant that we will use to calculate the minutes and seconds
    const int HOURS=24; ////constant that we will use to calculate the hours
    //to get the time of enter and time of baking from the users we will get integers

    int howManyHours,howManyMinutes,howManySeconds,hourOfEnter,minuteOfEnter,secondOfEnter; 
    
    printf("Please enter the baking time: [hh:mm:ss]\n");
    scanf("%02d:%02d:%02d",&howManyHours,&howManyMinutes,&howManySeconds);
     printf("When did you put the cake into the oven? [hh:mm:ss]\n");
    scanf("%02d:%02d:%02d",&hourOfEnter,&minuteOfEnter,&secondOfEnter);
    //now we calculate the time the cake will be ready by using the constats of time and modulu.
    int readySecond= (howManySeconds+secondOfEnter)%SECANDMIN; 
    int readyMinute=(((howManyMinutes+minuteOfEnter)+((howManySeconds+secondOfEnter)/SECANDMIN))%SECANDMIN); 
    int readyHour=((howManyHours+hourOfEnter)+((howManyMinutes+minuteOfEnter+((howManySeconds+secondOfEnter)%SECANDMIN))/SECANDMIN))%HOURS;
    //print the calculated time in [hh:mm:ss]
    printf("The cake will be ready at %02d:%02d:%02d o\'clock.\n",readyHour,readyMinute,readySecond);

}


void main() {
    hello();
    distance();
    conversions();
    baking();
}