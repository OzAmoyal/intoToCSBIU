/***********************
* Name: Oz Shlomi Amoyal
* Assignment:ex_4
***********************/

#include <stdio.h>
#include <math.h>
#include <string.h>
#define SIZE 336
#define WORDLENGTH 21
#define WORDNUM 16
#define LIVES 5

void getUserInput(char *userInput);
void sortOptions(char *userInput,char (*wordOptions)[WORDLENGTH]);
int printOptions(char (*wordOptions)[WORDLENGTH]);
void printGame(char *gameword,int lifeCount,int isLeftToGuess);
int gamePrintWord(char *gameWord,char* lettersGuessed);
char gameGetLetter(char* lettersGueesed,int clueFlag,int isLeftToGuess);

/******************
* Function Name: getUserInput
* Input: char pointer(for the 'string' variable of the input)
* Output: none(void)
* Function Operation: gets the input from the user and inserts it into the desired variable
******************/
void getUserInput(char *userInput)
{
printf("Enter your words:\n");
//reads all the characters up to '\n' from the user
scanf("%[^\n]",userInput);
}

/******************
* Function Name:sortOptions
* Input: pointer to char[](string) and pointer to char [][](string array)
* Output: none(void)
* Function Operation: sorts the input into the rows of the array in lexicographic order (first is the clue and then the words)
******************/
void sortOptions(char *userInput,char (*wordOptions)[WORDLENGTH])
{
//delimiters for the strtok function
char delim[]=":,";
//pointer for strtok function
char *token;
token=strtok(userInput,delim);
//counter for the division of the user input into different rows in the 2d array
int count=0;

//dividing the strings to diffrent rows (first row is clue and after that all the words.)
while (token!=NULL)
{
strcpy(*(wordOptions+count),token);
token=strtok(NULL,delim);
count++;
}

//temp for the bubble sort swap
char temp[WORDLENGTH];
   for (int i = 1; i < WORDNUM; ++i) {
        
        
      for (int j = i+1; j < WORDNUM; ++j) {
         
         // swapping strings if they are not in the lexicographical order
         if (strcmp(*(wordOptions+j),"") && strcmp(*(wordOptions+i),*(wordOptions+j)) > 0)
        {
            strcpy(temp,*(wordOptions+i));
            strcpy(*(wordOptions+i),*(wordOptions+j));
            strcpy(*(wordOptions+j), temp);
        }
      }
   }
   
      }

/******************
* Function Name: printOptions
* Input: 2d char array (an array of strings)
* Output:none (void)
* Function Operation:prints the options of words to choose from the user input
******************/
int printOptions(char (*wordOptions)[WORDLENGTH])
{
//index for the word selected by user.
int choiceOutput=0;
printf("choose an option:\n");
//prints all the words in the words array with their indexes (already in lexicographic order), no empty words.
for (int i = 1; i < WORDNUM; i++)
{
    if (!strcmp(*(wordOptions+i),"\0"))
    {
     break;   
    }
    printf("%d: %s\n",i,*(wordOptions+i));
}

//get the chosen word index from the user. 
scanf("%d",&choiceOutput);
return choiceOutput;
}

/******************
* Function Name: gamePrintWord
* Input: char array (stirng) gameWord, char array lettersGuessed
* Output: int leftToGuess(valid values 0-20)
* Function Operation:gets the word of the game and the letters the user aleready guessed and prints the word with hidden
                     letters (the ones he did not gueess).returns the number of hidden letters.
******************/
int gamePrintWord(char *gameWord,char* lettersGuessed)
{
    //the word length,a flag for the conditionals and isLeftToGuess as a return variable(0/1)
    int printSize = (int)strlen(gameWord),flag=0,isLeftToGuess=0;
    //how many letters to check in the for loop.
    int guessedCharsNum = (int)strlen(lettersGuessed);
    //the variable that stores the word with hidden unguessed letters and spaces.
    char hiddenLetters[WORDLENGTH] = "";
    //first for to go over the entire word.
    for (int i = 0; i <= printSize; i++)
    {
         //puts space if there is space in the word.
        if (*(gameWord + i) == (char)' ')
        {
            hiddenLetters[i] = (char)' ';
            flag = 1;
            
        }
        //puts '\0' at the end of the word(if it gets there.)
        if (i == printSize)
        {
            hiddenLetters[i] = '\0';
            flag = 1;
        }
         //if there is no space and it is not the end of the word 
        else
        {   //check if the user already input that letter
            for (int j = 0; j < guessedCharsNum; j++)
            {
                if (*(gameWord + i) == *(lettersGuessed + j))
                {
                    hiddenLetters[i] = *(lettersGuessed + j);
                    flag = 1;
                    //if he guessed it already it stops going over the other characters
                    break;
                }
            }
            //if any of the above did not happen put a blank '_' in the word.
            if (!flag)
            {
                hiddenLetters[i] = '_';
                isLeftToGuess=1;
            }
            flag = 0;
        }
    }
    //if the game did not stop
   if(isLeftToGuess)
      printf("%s\n",hiddenLetters);
   //returns if the user got the entire word
   return isLeftToGuess;
}
/******************
* Function Name:printGame
* Input:pointer to char array(gameWord),int LifeCount(0-5),int isleftToGuess(0-21)
* Output:none (void)
* Function Operation: prints the face according to the life count of the player,also prints a messege if the game is over.
******************/
void printGame(char *gameword,int lifeCount,int isLeftToGuess)
{
//if the game did not end
if(isLeftToGuess)
{
printf(" _________________\n");
switch (lifeCount)
{
case 0:
printf("|                |\n|                |\n|                |\n|                |\n|                |\n|________________|\n");
   break;
case 1:
printf("|                |\n|  **            |\n|  **            |\n|                |\n|                |\n|________________|\n");
   break;
case 2:
printf("|                |\n|  **        **  |\n|  **        **  |\n|                |\n|                |\n|________________|\n");
   break;
case 3:
printf("|  --            |\n|  **        **  |\n|  **        **  |\n|                |\n|                |\n|________________|\n");
   break;
case 4:
printf("|  --        --  |\n|  **        **  |\n|  **        **  |\n|                |\n|                |\n|________________|\n");
   break;
//5 is the last live of the player in the assignment
case 5:
printf("|  --        --  |\n|  **        **  |\n|  **        **  |\n|                |\n| \\/\\/\\/\\/\\/\\/\\  |\n|________________|\n");
printf("The word is %s, GAME OVER!\n",gameword);
   break;
   default:
      break;

}
}
}
/******************
* Function Name:getGameLetter
* Input:char array LettersGuessed,int clueFlag(0/1),int isLeftToGuess(0-21)
* Output:char userGuess
* Function Operation:prints the request of input from the user ,the clue option(if not used before),and the letters the user used,
                     gets the input from the user and returns it
******************/
char gameGetLetter(char* lettersGueesed,int clueFlag,int isLeftToGuess)
{
char userGuess='\0';
//if the game is not over
if (isLeftToGuess)
{
//if the user did not already ask for a clue
if (!clueFlag)
{
   printf("do you want a clue? press -> *\n");
}
printf("The letters that you already tried:");
//prints the letters with seperating ',' and spaces (except the end)
for (int i = 0; i < strlen(lettersGueesed); i++)
{
   if (i==0)
   {
       printf(" %c",*(lettersGueesed+i));
   }
   
   else if (*(lettersGueesed+i)!='\0')
   {
      printf(", %c",*(lettersGueesed+i));
   }
}

printf("\nplease choose a letter:\n");
//get user guess
scanf(" %c",&userGuess);
}
return userGuess;
}
/******************
* Function Name:main
* Input:none
* Output:none(void)
* Function Operation:calls the functions and runs the game.
******************/
void main()
{
//number of hidden letters (also used as a boolean)
int leftToGuess=1;
//a flag to know if a clue was asked
int clueFlag=0;
//the char variable for the user guess input
char gameChar='\0';
//life of the user(can go up to 5)
int lifeCount=0;
//counter for the index of the guessedChars
int gameCount=0;
/*pointers for the strchr check(ptrToGuessedChar checks if the user already guessed that character,ptrToWord Checks if the user
ptrToWord Checks if the user had a correct guess
*/
char *ptrToGuessedChar,*ptrToWord;
//first user input variable (long string)
char userInput[SIZE]="";
//variable for the word the user chose to play
char gameWord[WORDLENGTH]={""};
//array that stores the users guesses.
char guessedChars[WORDLENGTH]="";
//the array that stores the word options for the game and the clue in lexicographic order
char wordOptions[WORDNUM][WORDLENGTH] ={""};
//pointer to the wordOptions array
char (*pointToWordArray)[WORDLENGTH] = wordOptions;

//get the clue and words from the user into userInput char array
getUserInput(userInput);
//sorts the words into an array in lexicographic order
sortOptions(userInput,pointToWordArray);
//get the desired word index from the user into the chosenWordIndex int variable
int chosenWordIndex=printOptions(wordOptions);
//copy the word from the array into the gameWord char array
strcpy(gameWord,wordOptions[chosenWordIndex]);

//loop that handles the game
do
{
//prints the form of the game
printGame(gameWord,lifeCount,leftToGuess);
//prints the hidden words and gets the value of hidden characters into leftToGuess
leftToGuess=gamePrintWord(gameWord,guessedChars);
//get a guess from the user
gameChar=gameGetLetter(guessedChars,clueFlag,leftToGuess);

//checks the user guess and acts accordingly
ptrToGuessedChar=strchr(guessedChars,gameChar);
ptrToWord=strchr(gameWord,gameChar);
//if the game is over
if(!leftToGuess)
{
   printf("The word is %s, good job!\n",gameWord);
   break;
}
//if the user asked a clue
else if (gameChar=='*'&&!clueFlag)
{
   printf("the clue is: %s.\n",*(wordOptions));
   clueFlag++;   
}
//if the user typed a character he already trid
else if(ptrToGuessedChar!=NULL&&gameChar!='*')
{
printf("You've already tried that letter.\n");

}
//if the it's a valid guess(the char is in the game word)
else if (ptrToWord!=NULL)
{
   //enter the guess into the guessedChars array
   guessedChars[gameCount]=gameChar;
   //go to the next index of the array
   gameCount++; 
}
//if the guess is wrong
else
{
   if (gameChar!='*')
   {
   //enter the guess into the guessedChars array
   guessedChars[gameCount]=gameChar;
   //go to the next index of the array
   gameCount++;
   //adds to life counter(changes game drawing)
   lifeCount++; 
   }
}

}while (lifeCount<LIVES);  //LIVES is predefined.
//if the game ended sends the printGame function with the value of the end of the game
if (lifeCount==LIVES)
{
   printGame(gameWord,lifeCount,leftToGuess);

}
}
