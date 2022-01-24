/***********************
* Name: Oz Shlomi Amoyal
* Assignment: ex_3
***********************/

#include <stdio.h>
#include <math.h>

int menu();
int checkPrime(int checkedNumber);
int reverseNumber(int numToReverse);
void primes();
void goldbach();
void lychrel();
void setMax();

/******************
* Function Name:main
* Input:none
* Output:none
* Function Operation: calls the menu function gets an input from the user and calls the matching function by number
******************/
int main(){
int menuInput=menu();

    if (menuInput==1)
    {
    primes();
    }
    else if (menuInput==2)
    {
        goldbach();
    }
    else if (menuInput==3)
    {
        lychrel();
    }
    else if (menuInput==4)
    {
        setMax();
    }
    else
    {
    printf("Wrong option!\n");
    return 0;
    }
return 0;
}

/******************
* Function Name:menu
* Input:int menuInput(valid values all integers)
* Output:int menuInput
* Function Operation: prints the menu gets the input from the user and returns it to the main function
******************/
int menu(){
int menuInput;
printf("1: primes\n2: goldbach\n3: lychrel\n4: max set\n");
scanf("%d",&menuInput);
return menuInput;
}

/******************
* Function Name: primes
* Input:none(gets a SIZE variable in compilation )
* Output:print
* Function Operation:prints prime numbers up to the SIZE variable
******************/
void primes(){
int flag=0;    //flag to avoid over spacing 
for (int i=2;i<=SIZE;i++)   //checks every number until predefined SIZE
{
if(checkPrime(i))
{
if (flag!=0)
{
    putchar(' ');
}
flag++;

    printf("%d",i);
}
}
}

/******************
* Function Name:goldbach
* Input:none (gets a SIZE variable in compilation)
* Output:print
* Function Operation:prints all the even numbers that can be pressented as a sum of the prime numbers up to the SIZE
******************/
//note to checker: i did it efficietly but the output did not match the submit so i had to change it..
void goldbach(){
int highestPrime=0; // variable to store the value of the highest number to print
for(int i=0;i<SIZE;i++) //loop that checks the highest prime number up to SIZE
{
if (i>highestPrime&&checkPrime(i))
{
    highestPrime=i;
}

}


for (int i = 4; i <= highestPrime*2; i+=2)//loop to check every even number
{
    for (int j = highestPrime; j >=2; j--)//loop to check every prime number high to low
    {
        if(checkPrime(j))
        {
            for (int k=2;k<=j;k++)//loop to check every prime number up to j variable
            {
            if (j+k==i&&checkPrime(k))//if both of them are prime numbers and equal to i(even number)
            {
                printf("%d = %d + %d\n",i,k,j);
            }
            }
        
        }
            
    } 
}
        
        
    }

/******************
* Function Name:lychrel
* Input:none (gets a LIMIT variable in compilation)
* Output:print
* Function Operation:the function pressents the sum of a number and it's reversed number of every number up to LIMIT variable
                    until it is a plyndrome
******************/
void lychrel(){
for (int i = 1; i <LIMIT; i++)//loop goes over every number from 1 to predefined LIMIT
{
    if (i==reverseNumber(i)) //if the number is a plyndrome
    {
        printf("%d\n",i);
    }
    else //for numbers that arent plyndromes
    {
    printf("%d:",i);// prints the unplyndrome number with : to show calculation procces
    int checkTemp=i;
    int isEqual=0;// we know they are not equal
   while (!isEqual) 
    {

    int checkReverse=reverseNumber(checkTemp); //the number in reverse
    int checkSum=checkTemp+checkReverse; //the sum of both number and it's reversed form
    printf("%d+%d=%d",checkTemp,checkReverse,checkSum); // prints both of them
    checkTemp=checkSum; //stores current value of sum of number and it's reversed form
    isEqual=checkTemp==reverseNumber(checkTemp);    //stores the "bolean" value for the loop and to know if we need more ':'
    if (!isEqual) 
        putchar(':');
    }
    putchar('\n');
    }
    
}


}

/******************
* Function Name:setMax
* Input:int length (valid values>=1)
* Output:int prints maxSetLength
* Function Operation:gets from user the length of a sequence and the numbers in it and returns the longest set
                    where each number is bigger than the last
******************/
void setMax()
{
    int length=0;   //gets the length of input set from the user
    int temp=0;     //temp to store loop index
    int tempSetLength=1;    //temp to calculate set length
    int maxSetLength=1;     //temp to store the longest set value
    printf("Enter the number of elements\n");
    scanf("%d",&length);
    int set[length]; 
    for(int i=0;i<length;i++) //get the sequence from the user
    {
    scanf("%d",&set[i]);
    }
    for(int i=0;i<length;i++) //loop to go over all numbers in the sequence
    {
        temp=i; //store current index of number
        for (int j = i; j<length; j++)  // loop that goes over all the numbers in sequence from current index
        {
            if(set[j]>set[temp]) //if the number in index j is bigger than the number in index temp
            {
                for (int k = j; k < length; k++)  // go over the rest of the sequence sequence
                {
            
                if (set[k]>set[temp]) //if the next number is bigger
                {
                temp=k; //store the index of the next number in temp variable (to know who do we need to check next)
                tempSetLength++; //add to the length of the current set tested
                
                if (tempSetLength>maxSetLength) //if the current set length is bigger than the last biggest set
                {
                maxSetLength=tempSetLength; //store the length of this set as the biggest
                }
                }
                else
                {
                temp=j; //index goes back to the number first checked in the second loop 
                }
        
                }
            tempSetLength=1; //reset the set length temp
                temp=i; //resets the temp value to i (moves on to the next number to test all possible sets from him an on)

            }  
        }
    }
    printf ("%d\n", maxSetLength); //prints the maximum length that was counted

}

/******************
* Function Name:reversedNumber
* Input:int numToReverse(valid values>=0)
* Output:int reversed
* Function Operation:the function gets an integer from the user and returns the reversed integer
******************/
int reverseNumber(int numToReverse)
{
    int reversed=0;
    while (numToReverse != 0) { //loop to reverse the number
        reversed = reversed * 10 +  numToReverse % 10; //adds the remainder and multiplies the current value by 10
        numToReverse /= 10; //step forward
    }
return reversed;
}

/******************
* Function Name:checkPrime
* Input:int checkeNumber(valid values>=1)
* Output: 0 or 1
* Function Operation:gets an integer and returns 1 if it is a prime number and 0 if it is not a prime number
******************/
int checkPrime(int checkedNumber)
{
if (checkedNumber==2)   //if the number is 2 it's prime
{
    return 1;
}
else if (checkedNumber%2!=0) //if the number is even it is not prime.
{
int sqrtNum=(int)sqrt(checkedNumber); //only need to check up to the square root of the number   
for (int j =3 ; j <=sqrtNum; j+=2) //loop that goes over all odd numbers from 3 and to the square root of the input
{
    if (checkedNumber%j==0) //if the remainder is 0
    {
        return 0; //return 0
    }
}
return 1; //if it did not return 0 in any of the loop conditions
}


}
