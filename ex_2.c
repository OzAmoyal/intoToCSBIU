/***********************
* Name: Oz Shlomi AMOYAL
* ID:207231663
* Assignment:ex_2
***********************/ 

#include <stdio.h>
#include <math.h>

void hexToDecimal();
void decimalToBase();
void baseToDecimal();
void plusBinary();
void bitCount();
void shape();
int menu();

/******************
* Function Name: main
* Input: none
* Output: 0
* Function Operation:The function calls to the function that prints the menu and with the output calls to the desired function,
                    until the menu function returns 7 and we exit the program with code 0;
******************/
int main() {
    int input=menu();
    while(input!=7)//the loop calls the menu function until it returns 7 into the input variable 
    {
    if(input==1)
    {
      
        hexToDecimal();
    }
    else if(input==2)
    {
        decimalToBase();
    }
    else if(input==3)
    {

        baseToDecimal();
    }
    else if(input==4)
    {
        plusBinary();
    }
    else if(input==5)
    {
        shape();
    }
    else if(input==6)
    {
        bitCount();
    }
    else if(input==7)
        break;
    else
    {
        printf("Wrong option!\n");
    }
    input=menu();//the call for menu function to print the menu again
    
    }
    return 0;

}
/******************
* Function Name:menu
* Input:char userinput (valid values ('1'-'7'))
* Output:int (values 1-8)
* Function Operation: the function prints the menu and gets the user input, checks if it's valid. 
                    if it is it returns the number in as int, if it's not valid it returns 8.
******************/

int menu(){
    char userInput;
    int output=0,counter=0;
    printf("Choose an option:\n	1. hexaDecimal to Decimal\n	2. Decimal to Base\n	3. Base to Decimal\n	4. PLUS\n	5. Shape\n	6. Count bits\n	7. Exit\n");
    scanf(" %c",&userInput); //the first input ignores spcaes and \n
    do //the loop gets the input from the user into char until it gets \n
    { 
    if (userInput=='0')
    {
        counter++;
        
    }
    
    else if(userInput=='1')
    {
        output+=1;
        counter++;
    }
    else if(userInput=='2')
    {
        output+=2;
        counter++;
    }
    else if(userInput=='3')
    
    {
        output+=3;
        counter++;
    }
    else if(userInput=='4')
    
    {
        output+=4;
        counter++;
    }
    else if(userInput=='5')
    
    {
        output+=5;
        counter++;
    }
    else if(userInput=='6')
    
    {
        output+=6;
        counter++;
    }
    else if(userInput=='7')
    
    {
       return 7;
    }
    else 
    {
    return 8;
    }
    scanf("%c",&userInput);//gets another value from the buffer

    }while(userInput!='\n');
    
    if(counter==1)//we used a counter to validate the user entered a single char input
        return output;
    else
        return 8; // the value for wrong input
    

}

/******************
* Function Name:hexToDecimal
* Input:infinite hexadecimal number as single chars (valid values :'0'-'9','a'-'f','A','F')
* Output: unsigned long long int (values >=0)
* Function Operation:the function gets a reversed infinite number in hexadecimal base, and returns the converted value in base 10
******************/

void hexToDecimal(){
    printf("Enter a reversed number in base 16:\n");
    int countPow=0;
    int isError=0;
    unsigned long long int sumDecimal=0;
    char hexInput;
    scanf(" %c",&hexInput);//the first input ignores spcaes and \n

     //the loop gets the infinite reversed hex number from the user and validates it's valid and if it is it converts it into a decimal number
    do
    {
        if (hexInput=='0')
        {
            countPow++;
        }
        else if (hexInput=='1')
        {
            sumDecimal+=(1*(int)pow(16,countPow));
            countPow++;
        }
        else if(hexInput=='2')
        {
            sumDecimal+=(2*(int)pow(16,countPow));
            countPow++;
        }
        else if(hexInput=='3')
        {
            sumDecimal+=(3*(int)pow(16,countPow));
            countPow++;
        }
        else if(hexInput=='4')
        {
            sumDecimal+=(4*(int)pow(16,countPow));
            countPow++;
        }
        else if(hexInput=='5')
        {
            sumDecimal+=(5*(int)pow(16,countPow));
            countPow++;
        }
        else if(hexInput=='6')
        {
            sumDecimal+=(6*(int)pow(16,countPow));
            countPow++; 
        }
        else if(hexInput=='7')
        {
            sumDecimal+=(7*(int)pow(16,countPow));
            countPow++;
        }
        else if(hexInput=='8')
        {
            sumDecimal+=(8*(int)pow(16,countPow));
            countPow++;
        }
        else if(hexInput=='9')
        {
            sumDecimal+=(9*(int)pow(16,countPow));
            countPow++;
        }
        else if (hexInput=='a'||hexInput=='A')
        {
            sumDecimal+=(10*(int)pow(16,countPow));
            countPow++;
        }
        else if (hexInput=='b'||hexInput=='B')
        {
            sumDecimal+=(11*(int)pow(16,countPow));
            countPow++;
        }
        else if (hexInput=='c'||hexInput=='C')
        {
            sumDecimal+=(12*(int)pow(16,countPow));
            countPow++;
        }
        else if (hexInput=='d'||hexInput=='D')
        {
            sumDecimal+=(13*(int)pow(16,countPow));
            countPow++;
        }
        else if (hexInput=='e'||hexInput=='E')
        {
            sumDecimal+=(14*(int)pow(16,countPow));
            countPow++;
        }
        else if (hexInput=='f'||hexInput=='F')
        {
            sumDecimal+=(15*(int)pow(16,countPow));
            countPow++;
        }
        
        else{
            printf("Error!\n");
            isError++;
            
        }

    scanf("%c",&hexInput);

    } while(hexInput!='\n');
    if (isError==0)//we used a the isError variable as a flag to know if the user typed a string with an unvalid character
    {
        printf("%llu\n",sumDecimal);
    }
    
    
    
    
}  
/******************
* Function Name: decimalToBase
* Input:int baseNumber(valid values 2-9),unsigned long int DecimalInput(valid values >=0)
* Output:unsigned long long int (valid values >=0)
* Function Operation:the function gets from the user a base number and a decimal number ,converts it to the base and returns the number
                    in the desired base
******************/

void decimalToBase(){
    printf("Enter base and a number:\n");
    int baseNumber,countPow=0;
    unsigned long int decimalInput;
    unsigned long long int convertedNumber=0;
    scanf("%d%lu",&baseNumber,&decimalInput); //get the input base and decimal number from the user

//the loop converts the input number with the remainder of the division by the base number multiplied by ten by power of the countPow counter
    while (decimalInput!=0)  
    {
        convertedNumber+=(decimalInput%baseNumber)*((int)pow(10,countPow));
        decimalInput/=baseNumber; //move one digit left
        countPow++;//increase the Power Counter that repressents the position
    }
    printf("%llu\n",convertedNumber);//print the converted number
}

/******************
* Function Name:baseToDecimal
* Input:int baseNumber (valid values (2,9),unsigned long int baseInput(valid values >=0 **with digits 0<=digit<=baseNumber)
* Output: unsigned long int decimalOutput (values >=0)
* Function Operation:gets a base number and a number in the base, validates it and returns the converted decimal number
******************/

void baseToDecimal(){
    printf("Enter base and a number:\n");
    int isError=0,baseNumber,countPow=0;
    unsigned long int decimalOutput=0,baseInput;
    scanf("%d%lu",&baseNumber,&baseInput);

//the loop validates the right digit and if it's valid it converts it's value by power of the base number
//and adds it to the sum of the converted decimal number
    {
    while (baseInput!=0) 
        if (baseInput%10>=baseNumber) //validate if the right digit is in the base the user inputed
        {
            printf("Wrong Input!\n");
            isError++;
            break;
        }
        else
        {
        decimalOutput+=(baseInput%10)*(int)pow(baseNumber,countPow); //sum the right digit by power of it's position
        baseInput/=10; //move one digit left
        countPow++; //increase the Power Counter that repressents the position
        }
        
    }
    if (isError==0) // if the user did not enter an unvalid input
    {
        printf("%lu\n",decimalOutput);
    }    
}

/******************
* Function Name:plusBinary
* Input:unsigned long int inputBinary1,inputBinary2(valid values (any number with digits 0,1))
* Output: unsigned long int binaryOutput(valid values any number with digit 0,1),carry(valid values any number with digit 0,1)
* Function Operation:gets two binary numbers, and prints the calculation of the sum between them including the carry(if neccesery)
******************/

void plusBinary(){
    printf("Enter 2 binary numbers:\n");
    int isError=0,carry=0,countPow=0;
    unsigned long int inputBinary1,inputBinary2,binaryOutput=0,checkTemp1,checkTemp2,carryOutput=0;
    scanf("%lu%lu",&inputBinary1,&inputBinary2);
    checkTemp1=inputBinary1;
    checkTemp2=inputBinary2;
//the loop calculates the sum of the right digit of each number and if its bigger than one it adds the value  to the carry variable
    while (checkTemp1!=0||checkTemp2!=0||carry!=0)
    {
     if (checkTemp1%10>1||checkTemp2%10>1)//validate the input
        {
             isError++;
            printf("Error!\n");
            break;
        }
    else//if input is valid
    {
    if (checkTemp1%10+checkTemp2%10+carry==3)
    {
        carryOutput+=1*(unsigned long int)pow(10,countPow+1);//calculate carry
        carry=1;//add one to the carry for the next calculation
        binaryOutput+=1*(unsigned long int)pow(10,countPow);//add the value to the binary sum
        countPow++;//move one digit left on the output
    }
    else if (checkTemp1%10+checkTemp2%10+carry==2)
    {
    carryOutput+=1*(unsigned long int)pow(10,countPow+1);
    carry=1;
    countPow++;
    }
    else if (checkTemp1%10+checkTemp2%10+carry==1)
    {
        carry=0;
        binaryOutput+=1*(unsigned long int)pow(10,countPow);//add the value to the binary sum
        countPow++;//move one digit left on the output
    }
    else if (checkTemp1%10+checkTemp2%10+carry==0)
    {
        carry=0;
        countPow++;//move one digit left on the output
    }
    
   
    checkTemp1/=10;//move one digit left on first number
    checkTemp2/=10;//move one digit left on second number
    }
    }
    if (isError==0)//if the number is valid
    {   
        if (carryOutput!=0)//if we have carry at all
    {
        printf("%lu\n",carryOutput);//prints carry
    }

//check if the first input is bigger than the second and prints the longer first, both of them padded with zeros
        if (inputBinary1>inputBinary2) 
    {  
        printf("%0*lu\n+\n",countPow,inputBinary1); 
        printf("%0*lu\n",countPow,inputBinary2); 
    }
    else
    {
        printf("%0*lu\n+\n",countPow,inputBinary2);
        printf("%0*lu\n",countPow,inputBinary1);
    }//prints '-' in the length of the binary output number
    for (int i = 0; i < countPow; i++)
        {
            printf("-");
        }
        printf("\n%lu\n",binaryOutput);//print the calculation result
    }  
  
}

/******************
* Function Name:bitCount
* Input:unsigned long int Decimal input(valid values >=0)
* Output: int Count ones (valid values >=0)
* Function Operation:gets a decimal number and returns (prints) the number of times the digit '1' is in the binary form of the number
******************/

void bitCount(){
    unsigned long int decimalInput;
    unsigned long long int convertedBinary=0;
    int countOnes=0,countPow=0;
    printf("enter a number:\n");
    scanf("%lu",&decimalInput);
     while (decimalInput!=0)//the loop converts the decimal number to binary
    {
        convertedBinary+=(decimalInput%2)*((int)pow(10,countPow));//convert the right digit remainder
        decimalInput/=2;//divide by 2
        countPow++;//increase the power counter by 1
    }
    
    while (convertedBinary!=0)//the loop counts the number of times the digit '1' is in the binary converted number
    {
        if (convertedBinary%10==1)//check the right digit
        {
            countOnes++;//if one increase the counter by one
        }
        convertedBinary/=10;//move one digit left
        
    }
    printf("no of bits those are 1 in its binary representation: %d\n",countOnes); //print the number of ones



}

/******************
* Function Name:shape
* Input:unsigned long int size (valid value>=0)
* Output: none
* Function Operatio: prints butterfly shape by width of 2*size and length of size *2 -1, with '#' in the side
******************/
void shape(){
unsigned long int size;

    printf("Enter a number:\n");    
    scanf("%lu",&size);
    for(int i=0;i<((2*size)+1);i++)// loop that repressents the line value
    {
        for(int j=0;j<((2*size)+2);j++) //loop that repressents the column value
        {
         if((i==0)||(i==2*size))//corners and sides
        {
            if(j<3||j>2*(size-1))
            {
                putchar('#');
            }
            else
            {
                putchar(' ');
            }   
        }
        else if(i>=1&&i<size){//second line untill the middle
            if(j==0||j==((2*size)+1)||j==(i+1)||j==((2*size)-(i)))//prints what happens in every column in the line 
            {
                putchar('#');
            }
            else if ((j>=1&&j<=i)||((j>=(2*size)-i)&&j<=(2*size)))
            {
                putchar('*');
            }
            else
            {
                putchar(' ');
            }
        }
        else if(i==size)//middle line
        {
            if (j==0||j==2*size+1)
            {
                putchar('#');
            }
            else
            {
                putchar('*');
            }

            
        }
        else if(i>size&&i<2*size)//lines - middle to end
        {
          if (j==0||j==((2*size)+1)||j==(2*size)-i+1||j==i)//what it prints in every column of the line
            {
              putchar('#');
            }
            else if((j>=1&&j<=(2*size)-i)||(j>i&&j<=(2*size)))
            {
                putchar('*');
            }
            else
            {
            putchar(' ');
            }
        }
        }
    putchar('\n');//go down one line ()
    }
    if (size==0)//if the user inputs zero we get one row of ## so to be sure
    {
        printf("##\n");
    }
    
}
