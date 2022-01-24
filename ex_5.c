/******************
* Oz Shlomi Amoyal
* ex_5
******************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LASTMENUOPTION 6
typedef struct {
    char** translations;
    struct Word* next;
} Word;

typedef struct {
    char** languages;
    int numOfLanguages;
    Word* wordList;
} Dictionary;

/******************
* Function Name: destroyDictWordList
* Input: Dictionary*(a specific Dictionary from the dictionaries array)
* Output: none(void)
* Function Operation: frees entire linked list of words from a specific dictionary
******************/
void destroyDictWordList(Dictionary* dict)
{
    //use of 2 pointers to delete the entire linked,list
    Word* current = dict->wordList;
    Word* next = NULL;
    //if current is NULL it means the list is all freed
    while (current != NULL)
    {
        next = (Word*)current->next;
        if (current->translations != NULL)
        {
            for (int i = 0; i < dict->numOfLanguages; i++)
            {
                free(current->translations[i]);
            }
            free((current->translations));
        }
        free(current);
        current = next;
    }
    //for dangling pointer case
    dict->wordList = NULL;
}
/******************
* Function Name:destroyDic
* Input: Dictionary*(a specific Dictionary from the dictionaries array)
* Output:none (void)
* Function Operation: the function frees a specific dictionary from the dictionaries array, with all his components
******************/
void destroyDic(Dictionary* dict)
{
    //a loop to free all the languages is the languages array in Dictionary struct
    for (int i = 0; i < dict->numOfLanguages; i++)
    {
        free(dict->languages[i]);
    }
    free(dict->languages);
    //call to free the linked list of words
    destroyDictWordList(dict);
    //free the selected Dictionary struct
    free(dict);

}
/******************
* Function Name: addWordToList
* Input: Dictionary** dict(pointer to the array of dictionaries),Word* addedWord(the word to add),int dictIndex(index of dictionary)
* Output: Dictionary **(a pointer to a dictionaries array)
* Function Operation: gets a dictionaries array, and index of selcted dictionary and a word to add to it and adds it to
                    the end of the linked list of the wordlist in the selcted dictionary
******************/
Dictionary** addWordToList(Dictionary** dict, Word* addedWord, int dictIndex)
{
    //to prevent invalid read of memory
    if (addedWord == NULL)
        return NULL;

    //if the selected Dictionary wordlist is empty, the added word is the first word in the list
    if (dict[dictIndex]->wordList == NULL)
    {
        dict[dictIndex]->wordList = addedWord;
        return dict;
    }
    //a pointer that moves along the word list until he get's to the end of it
    Word* ptrToWord = dict[dictIndex]->wordList;
    while (ptrToWord->next != NULL)
    {
        ptrToWord = (Word*)ptrToWord->next;
    }
    //the 'next' value of the last pointed word in the list is NULL and we tell him to point to our word
    ptrToWord->next = (struct Word*)(addedWord);

    return dict;

}
/******************
* Function Name:getMenuInput
* Input:none
* Output:int userInput
* Function Operation:the function prints the menu and gets an int input from the user, and returns it
******************/
int getMenuInput()
{
    int userInput = 0;
    printf("Welcome to the dictionaries manager!\nChoose an option:\n1. Create a new dictionary.\n"
        "2. Add a word to a dictionary.\n3. Delete a word from a dictionary.\n4. Find a word in a dictionary.\n"
        "5. Delete a dictionary.\n6. Exit.\n");
    scanf("%d", &userInput);
    return userInput;
}
/******************
* Function Name: dynamicInput
* Input: none
* Output: char*(pointer to a dynamic string)
* Function Operation: gets an input from the user and returns it in a string in it's length(+1 for the null char)
******************/
char* dynamicInput()
{
    //char variable to get the user input
    char input = '\0';
    //first allocation of space
    char* output = (char*)malloc(sizeof(char));
    //backup variable for allocation faliure
    char* tmp = output;
    int length = 1, index = 0;
    //get first char from the user (ignore white spaces)
    scanf(" %c", &input);
    //the loop continues to allocate memory and enter the user input into it up to a '\n' char
    while (input != '\n')
    {
        length++;
        tmp = realloc(output, sizeof(char) * length);
        //in case of falire in allocation
        if (tmp == NULL)
        {
            free(output);
            printf("input fail");
            return NULL;
        }
        output = tmp;
        output[index] = input;
        index++;
        //get the next char
        scanf("%c", &input);
    }
    //last array slot is the null char
    output[index] = '\0';
    return output;
}
/******************
* Function Name: printSingleDict
* Input: Dictionary** dict(the dictionaries array), int dictIndex(the selected dictionary to print)
* Output: none(void)
* Function Operation: prints the selected dictionary languages with ', ' seperating(except the last one)
******************/
void printSingleDict(Dictionary** dict, int dictIndex)
{
    for (int j = 0; j < dict[dictIndex]->numOfLanguages; j++)
    {
        //if it's the last language
        if (j == (dict[dictIndex]->numOfLanguages - 1))
            printf("%s", dict[dictIndex]->languages[j]);
        else
            printf("%s,", dict[dictIndex]->languages[j]);

    }
}
/******************
* Function Name: printDictionaries
* Input:Dictionary** dict(the dictionaries array),int numOfDicts (the number of dictionaries in the array)
* Output: none(void)
* Function Operation: prints all the dictionaries in order with index numbers at the beggining of each line
******************/
void printDictionaries(Dictionary** dict, int numOfDict)
{

    for (int i = 0; i < numOfDict; i++)
    {
        //print the index of the dictionary
        printf("%d. ", i + 1);
        //a loop that prints the dictionary languages
        for (int j = 0; j < dict[i]->numOfLanguages; j++)
        {
            if (j == (dict[i]->numOfLanguages - 1))
                printf("%s", dict[i]->languages[j]);
            else
                printf("%s,", dict[i]->languages[j]);

        }
        printf("\n");

    }
}
/******************
* Function Name: addWordToDic
* Input:Dictionary** dict(the dictionaries array),int numOfDictionaries(number of dictionaries currently in the array)
* Output:Dictionary **ptrToDict(a Pointer to a dictionaries array)
* Function Operation: adds a word and it's translations from the user into a selected dictionary from the dictionary array
******************/
Dictionary** addWordToDic(Dictionary** dict, int numOfDictionaries)
{
    printf("Choose a dictionary:\n");
    printDictionaries(dict, numOfDictionaries);
    int userInput = 0;
    char* wordInput = NULL;
    Word* ptrWord = NULL;
    Dictionary** ptrToDict = NULL;

    scanf("%d", &userInput);
    //if the input from the user is not valid
    if (userInput > numOfDictionaries)
        return NULL;
    //variable that stores the index of selected dictionary in the array
    int iDict = userInput - 1;
    printf("Enter a word in ");
    //prints the languages of the dictionary the user chose
    printSingleDict(dict, iDict);
    printf(":\n");
    //get the input from the user with the dynamicInput function
    wordInput = dynamicInput();
    //if the wordInput did not allocate properly
    if (wordInput == NULL)
        return NULL;

    char** backupPtr = NULL;
    //delimiter for the strtok function to divide the input into words
    char delim[] = { "," };
    char* ptr = strtok(wordInput, delim);
    char** transPtr = NULL;
    //counter for the number of translations
    int countTrans = 0;
    char* trans = NULL;
    /* this while loop goes on for as long as there are words to seperate from the userInput string
    it allocates each word memory in the heap and adds the pointer to it into an array of strings */
    while (ptr != NULL)
    {   //alocating a space for the word
        trans = malloc((strlen(ptr) + 1) * sizeof(char));
        //if allocation fails it realeases all the memory that was allocated in the procces and returns NULL
        if (trans == NULL)
        {
            for (int i = 0; i < countTrans; ++i)
            {
                free(transPtr[i]);
            }
            free(transPtr);
            free(wordInput);
            return NULL;
        }
        //copy the words from the strtok pointer into the allocated memory
        strcpy(trans, ptr);
        /* now here is the allocation of the string array. if the counter is zero it allocates memory
        if the counter is more it reallocates the memory and adds one more space for the new pointer of string
        */
        if (countTrans == 0)
        {
            backupPtr = malloc((countTrans + 1) * sizeof(char*));
            if (backupPtr == NULL)
            {
                for (int i = 0; i < countTrans; ++i)
                {
                    free(transPtr[i]);
                }
                free(transPtr);
                free(wordInput);
                return NULL;
            }
            transPtr = backupPtr;
        }
        backupPtr = realloc(transPtr, (countTrans + 1) * sizeof(char*));
        //if allocation fails it realeases all the memory that was allocated in the procces and returns NULL
        if (backupPtr == NULL)
        {
            if (countTrans > 0)
            {
                for (int i = 0; i < countTrans; ++i)
                {
                    free(transPtr[i]);
                }
                free(transPtr);

            }
            free(wordInput);
            return NULL;
        }
        //if allocation succeds it adds the pointer of string to the array of pointers for translation strings
        transPtr = backupPtr;
        transPtr[countTrans] = trans;
        trans = NULL;
        //move over to the next strtok and add one to the counter
        ptr = strtok(NULL, ",");
        countTrans++;
    }
    //allocation of memory for the word itself
    ptrWord = (Word*)malloc(sizeof(Word));
    //if allocation fails it realeases all the memory that was allocated in the procces and returns NULL
    if (ptrWord == NULL)
    {
        for (int i = 0; i < countTrans; ++i)
        {
            free(transPtr[i]);
        }
        free(transPtr);
        free(wordInput);
        return NULL;
    }
    //initialize the word and put the traslations array pointer in the word memory
    ptrWord->next = NULL;
    ptrWord->translations = transPtr;

    //call to the function that adds the word we just created into the end of the wordlist in the selected dictionary
    ptrToDict = addWordToList(dict, ptrWord, iDict);
    //if allocation fails it realeases all the memory that was allocated in the procces and returns NULL
    if (ptrToDict == NULL)
    {
        for (int i = 0; i < countTrans; ++i)
        {
            free(ptrWord->translations[i]);
        }
        free(ptrWord->translations);
        free(ptrWord);
        return NULL;
    }
    //free the userInput string memory and return a pointer to dictionaries array
    free(wordInput);
    return ptrToDict;
}
/******************
* Function Name: deleteWord
* Input: Dictionary** dict(pointer to dictionaries array), int numOfDictionaries(number of dictionaries currently in the array)
* Output: int(value 1 if there was a problem in the procces and 0 if the word was deleted or the deletion was canceled)
* Function Operation: user selectes a dictionary to delete a word from and inputs a word to delete
                      and the function removes it from the wordlist linked list
******************/
int deleteWord(Dictionary** dict, int numOfDictionaries)
{
    printf("Choose a dictionary:\n");
    printDictionaries(dict, numOfDictionaries);
    int dictChoice = 0;
    scanf("%d", &dictChoice);
    //if chosen dictionary is not a valid value
    if (dictChoice > numOfDictionaries)
    {
        printf("The deletion of the word has failed!\n");
        return 1;
    }
    //the index for the array (counting from zero)
    dictChoice--;

    //prints the request for a word in the language of the dictionary
    printf("Enter a word in %s:\n", dict[dictChoice]->languages[0]);
    //get a dynamic string input from the user with the dynamicInput function
    char* wordToDelete = dynamicInput();
    //if the allocation of the dynamicInput function faild it returns 1(delete failed)
    if (wordToDelete == NULL)
        return 1;
    //validate the user wants to delete the word
    printf("Are you sure? (y/n)\n");
    char isSureToDelete = '\0';
    //get validation char from the user
    scanf(" %c", &isSureToDelete);
    //if user inputs anything but 'y' it realeases all the memory that was allocated in the procces and returns NULL
    if (isSureToDelete != 'y')
    {
        printf("The deletion of the word has been canceled.\n");
        free(wordToDelete);
        return 0;
    }
    //pointer to go over the wordlist in the selected dictionary
    Word* ptr = dict[dictChoice]->wordList;
    //if first word in the list is the word to be deleted.
    if (ptr != NULL && strcmp(ptr->translations[0], wordToDelete) == 0)
    {
        //wordlist starts from the next word and memory is freed
        dict[dictChoice]->wordList = (Word*)ptr->next;
        for (int i = 0; i < dict[dictChoice]->numOfLanguages; i++)
        {
            free(ptr->translations[i]);
        }
        free(ptr->translations);
        free(ptr);
        free(wordToDelete);
        printf("The word has been deleted successfully!\n");
        return 0;
    }

    Word* prev = NULL;
    //the loop goes over the linked list and checks if the word exists in it
    while (ptr != NULL && strcmp(wordToDelete, ptr->translations[0]) != 0)
    {
        prev = ptr;
        ptr = (Word*)ptr->next;
    }
    //if word is not found it frees the string memory and returns 1(failure to delete)
    if (ptr == NULL)
    {
        free(wordToDelete);
        return 1;
    }
    //if the word is found it changes the pointer from the word before it and frees the memory of the word
    prev->next = ptr->next;
    for (int i = 0; i < dict[dictChoice]->numOfLanguages; i++)
    {
        free(ptr->translations[i]);
    }
    free(ptr->translations);
    free(ptr);
    free(wordToDelete);
    printf("The word has been deleted successfully!\n");
    wordToDelete = NULL;
    return 0;
}
/******************
* Function Name: printTranslations
* Input:Dictionary** dict(pointer to dictionaries array), Word* wordToPrint(the word to print),int dictIndex(index of dictionary)
* Output:int (0 if print is valid and 1 if not)
* Function Operation: gets a word to print and and index of dictionary and prints the translation language and word.
******************/
int printTranslations(Dictionary** dict, Word* wordToPrint, int dictIndex)
{
    printf("The translations are:\n");
    for (int i = 1; i < dict[dictIndex]->numOfLanguages; ++i)
    {
        if (i == (dict[dictIndex]->numOfLanguages - 1))
        {
            printf("%s: %s\n", dict[dictIndex]->languages[i], wordToPrint->translations[i]);
            return 0;
        }
        printf("%s: %s, ", dict[dictIndex]->languages[i], wordToPrint->translations[i]);
    }
    //if the for loop did not enter (unlikely)
    return 1;
}
/******************
* Function Name:searchWord
* Input:Dictionary** dict(pointer to array of dictionaries), int numOfDictionaries(number of dictionaries currently in array)
* Output:int(0 if search completed, 1 if there is an allocation error or invalid input for dictionary index)
* Function Operation: get a dictionary selection and word from the user and print the translations of the word in the dictionary languages,
                      if there are no languages it notifys to the user.
******************/
int searchWord(Dictionary** dict, int numOfDictionaries)
{
    printf("Choose a dictionary:\n");
    printDictionaries(dict, numOfDictionaries);
    int dictChoice = 0;
    scanf("%d", &dictChoice);
    //if the index is invalid
    if (dictChoice > numOfDictionaries)
    {
        printf("The deletion of the word has failed!\n");
        return 1;
    }
    //index for the array (counting starts from 0)
    dictChoice--;

    printf("Enter a word in %s:\n", dict[dictChoice]->languages[0]);
    char* wordToSearch = dynamicInput();
    //if an allocation error occured
    if (wordToSearch == NULL)
        return 1;
    Word* pWord = dict[dictChoice]->wordList;
    //if first word in the list is the word searched.
    if (pWord != NULL && strcmp(pWord->translations[0], wordToSearch) == 0)
    {
        printTranslations(dict, pWord, dictChoice);
        free(wordToSearch);
        return 0;
    }
    //looking for the word in the wordlist linked list
    while (pWord != NULL && strcmp(wordToSearch, pWord->translations[0]) != 0)
    {
        pWord = (Word*)pWord->next;
    }
    //if the word is not in the dictionary wordlist
    if (pWord == NULL)
    {
        printf("There are no translations for \"%s\" in this dictionary.\n", wordToSearch);
        free(wordToSearch);
        return 0;
    }
    //if the word is found in the wordlist
    printTranslations(dict, pWord, dictChoice);
    free(wordToSearch);
    return 0;
}
/******************
* Function Name: createNewDict
* Input: char** langs(array of pointers to strings with languages of the dictionary,
         int numOfLangs(number of languages in the dictionary)
* Output: Dictionary * new(pointer to a new dictionary)
* Function Operation: allocates a memory for the new dictionary and initializes it with the input it gets (languages and number)
******************/
Dictionary* createNewDict(char** langs, int numOfLangs)
{
    //allocation of memory for the new dictionary
    Dictionary* new = malloc(sizeof(Dictionary));
    //if allocation fails
    if(new==NULL)
        return NULL;
    //initialize the dictionary with the inputs
    new->wordList = NULL;
    new->numOfLanguages = numOfLangs;
    new->languages = langs;
    return new;
}
/******************
* Function Name: newDict
* Input: Dictionary** dict(pointer to array of dictionaries)int numOfDictionaries(number of dictionaries in the array)
* Output: Dictionary** newDictPtr(pointer to array of dictionaries)
* Function Operation: gets a definition of new dictionary from the user and adds it to the dictionaries array
                    with languages in an array of strings and number of languages in it.
******************/
Dictionary** newDict(Dictionary** dict, int numOfDictionaries)
{
    int flag = 0;
    int langCount = 0;
    int wordLengthCount = 0;
    printf("Define a new dictionary:\n");
    char* newDictLangs = dynamicInput();
    //if allocation fails
    if (newDictLangs==NULL)
    {
        return NULL;
    }
    
    //index variable
    int iDict = numOfDictionaries;
    //add one dictionary to counter of dictionaries
    numOfDictionaries++;
    //delimiter for strtok function
    char delim[] = { "," };
    char* ptr = strtok(newDictLangs, delim);
    char* tmp = NULL;
    char** lngTmp2 = NULL;
    //allocate a memory for the languages array of pointers
    char** lngTmp = malloc(sizeof(char*));
    //using strtok to divide the languages into seperate strings.
    while (ptr != NULL)
    {
        wordLengthCount = (int)(strlen(ptr) + 1);
        //allocating memory for the language string
        tmp = (char*)malloc(wordLengthCount * sizeof(char));
        //if allocation fails it realeases all the memory that was allocated in the procces and returns NULL
        if (tmp == NULL)
        {
            for (int i = 0; i < langCount; i++)
            {
                free(lngTmp[i]);
            }
            free(lngTmp);
            free(newDictLangs);
            return NULL;
        }
        //copy the language into the memory allocated string
        strcpy(tmp, ptr);
        //add null char at the end
        tmp[wordLengthCount - 1] = '\0';
        //reallocation of memory for the language string pointer
        lngTmp2 = (char**)realloc(lngTmp, (langCount + 1) * sizeof(char*));
        //if allocation fails it realeases all the memory that was allocated in the procces and returns NULL
        if (lngTmp2 == NULL)
        {
            for (int i = 0; i < langCount; i++)
            {
                free(lngTmp[i]);
            }
            free(lngTmp);
            free(newDictLangs);
            return NULL;
        }
        lngTmp = lngTmp2;
        //enter the pointer to the new language to the array of pointers to languages strings
        lngTmp[langCount] = tmp;
        //add 1 to the language counter
        langCount++;
        //move over to the next language with strtok
        ptr = strtok(NULL, delim);
    }
    //use the function to allocate memory for the new dictionary
    Dictionary* ptrToNewDic = createNewDict(lngTmp, langCount);
    //if allocation fails it realeases all the memory that was allocated in the procces and returns NULL
    if (ptrToNewDic == NULL)
    {
         for (int i = 0; i < langCount; i++)
            {
                free(lngTmp[i]);
            }
        free(lngTmp);
        free(newDictLangs);
        return NULL;
    }
    //reallocation of memory to add pointer of new dictionary to the dictionary array
    Dictionary** ptrToDicArr = (Dictionary**)realloc(dict, (sizeof(Dictionary*) * numOfDictionaries));
    //if allocation fails it realeases all the memory that was allocated in the procces and returns NULL
    if (ptrToDicArr == NULL)
    {
        for (int i = 0; i < langCount; i++)
            {
                free(lngTmp[i]);
            }
        free(lngTmp);
        free(ptrToNewDic);
        free(newDictLangs);
        return NULL;
    }
    //enter the pointer of the new dictionary to the dictionaries array
    ptrToDicArr[iDict] = ptrToNewDic;
    free(newDictLangs);
    printf("The dictionary has been created successfully!\n");
    return ptrToDicArr;

}
/******************
* Function Name: removeDictFromArray
* Input:Dictionary** dict(pointer to array of dictionaries), int index(index of dictionary), 
        int numOfDicts(number of dictionaries currently in the array)
* Output:Dictionary **newDictPtr(pointer to dictionaries array)
* Function Operation: removes a selected dictionary from the array and returns a pointer to the array
                    if the new number of dictionaries is zero it reallocates memory to the dictionaries array
                    if the allocation fails it puts the pointer to the last dictionary in the
                    last the one to the last slot in the array
******************/
Dictionary** removeDictFromArray(Dictionary** dict, int index, int numOfDicts)
{
    Dictionary** newDictPtr = NULL;
    //use the destroyDic to free all allocated memory of the selected dictionary
    destroyDic(dict[index]);
    //move the pointers after the index of the deleted dictionary in the dictionaries array one slot backwards
    for (int i = index; i < numOfDicts - 1; ++i)
    {
        dict[i] = dict[i + 1];
    }
    //reduce by one the number of dictionaries
    numOfDicts--;
    //if no dictionaries allocate memory to the dictionaries array
    if (numOfDicts == 0)
    {
        newDictPtr = malloc(sizeof(Dictionary*));
        return newDictPtr;
    }
    //reallocation of memory (remove one slot from the array)
    newDictPtr = realloc(dict, numOfDicts * sizeof(Dictionary*));
    //if reallocation fails copy the last dictionary pointer into the last slot in the dictionaries array
    if (newDictPtr == NULL)
    {
        newDictPtr = dict;
        dict[numOfDicts] = dict[numOfDicts - 1];
        return newDictPtr;
    }
    return newDictPtr;
}

/******************
* Function Name: deleteDict
* Input: Dictionary** dict(pointer to dictionaries array) int numOfDicts(number of dictionaries currently in array)
* Output: Dictionary** newDictPtr(pointer to dictionaries array)
* Function Operation:gets from the desired dictionary to delete, makes sure he wants to delete it, and removes it from the
                    array of dictionaries and free the memory allocated to him
******************/
Dictionary** deleteDict(Dictionary** dict, int numOfDicts)
{
    printf("Choose a dictionary:\n");
    printDictionaries(dict, numOfDicts);
    int userInput = 0;
    scanf("%d", &userInput);
    //if the user input is invalid
    if (userInput > numOfDicts)
        return NULL;
    //reduce the user input to use as index (counting starts from 0)
    userInput--;
    printf("Are you sure? (y/n)\n");
    char isSureToDelete = '\0';
    scanf(" %c", &isSureToDelete);
    //make sure the user wants to delete the dictionary
    if (isSureToDelete != 'y')
    {
        printf("The deletion of the dictionary has been canceled.\n");
        return NULL;
    }
    //use the function to remove the chosen dictionary from the dictionaries array
    Dictionary** newDictPtr = removeDictFromArray(dict, userInput, numOfDicts);
    //if the alloctaion faild
    if (newDictPtr == NULL)
        printf("The deletion of the dictionary has failed!");
    return newDictPtr;
}
/******************
* Function Name:allDictsFree
* Input:Dictionary** dict(pointer to the dictionaries array), int numOfDicts(number of dictionaries currently in the array)
* Output:Dictionary** dict(pointer to the dictionaries array)
* Function Operation:
******************/
Dictionary** allDictsFree(Dictionary** dict, int numOfDicts)
{   
    //if the pointer is not null and the array is not empty from dictionaries
    if (dict != NULL && numOfDicts != 0)
    {
        //use the destroyDic function to free all dictionaries allocated memory
        for (int i = 0; i < numOfDicts; ++i)
        {
            destroyDic(dict[i]);
        }
        return dict;
    }
}

int main()
{   //flag for cases the user tries to use an unavailable option
    int tryAgainFlag=0;
    //flag for cases the functions fails
    int flag = 0;
    //variable to store the current number of dictionaries in the array
    int numOfDictionaries = 0;
    int menuInput = 0;
    //allocate a memory for the dictionaries array
    Dictionary** tmpPtrToNewDict = (Dictionary**)malloc(sizeof(Dictionary*));
    //if alloctaion fails
    if(tmpPtrToNewDict==NULL)
        return 1;
    Dictionary** dictionaries = tmpPtrToNewDict;
    tmpPtrToNewDict=NULL;
    
    while(menuInput != LASTMENUOPTION){   
        //get input from the user
        if(!tryAgainFlag)
            menuInput = getMenuInput();
        else
        tryAgainFlag=0;
        //switch to manage the menu with the input from the user that calls to the functions
        switch (menuInput)
        {
        case 1: //create new dictionaries
            tmpPtrToNewDict = newDict(dictionaries, numOfDictionaries);
            //if allocation fails
            if (tmpPtrToNewDict == NULL)
            {
                printf("The creation of the dictionary has failed!");
                break;
            }
            dictionaries = tmpPtrToNewDict;
            //add one to the dictionaries counter
            numOfDictionaries++;
            tmpPtrToNewDict = NULL;
            break;
        case 2: //add word to dictionary
            if (numOfDictionaries == 0)
            {
                printf("This option is not available right now, try again:\n");
                tryAgainFlag=1;
                scanf("%d",&menuInput);
                break;
            }

            tmpPtrToNewDict = addWordToDic(dictionaries, numOfDictionaries);
            //if allocation fails
            if (tmpPtrToNewDict == NULL)
            {
                printf("The addition of the word has failed!\n");
                break;
            }

            dictionaries = tmpPtrToNewDict;
            printf("The word has been added successfully!\n");
            tmpPtrToNewDict = NULL;
            break;
        case 3: //delete word from dictionary
        if (numOfDictionaries == 0)
            {
                printf("This option is not available right now, try again:\n");
                tryAgainFlag=1;
                scanf("%d",&menuInput);
                break;
            }
            flag = deleteWord(dictionaries, numOfDictionaries);
            //if there was a problem in the delete function
            if (flag)
                printf("The deletion of the word has failed!\n");
            break;
            printf("The word has been added successfully!\n");
        case 4: //find a word in dictionary
            if (numOfDictionaries == 0)
            {
                printf("This option is not available right now, try again:\n");
                tryAgainFlag=1;
                scanf("%d",&menuInput);
                break;
            }
            flag = searchWord(dictionaries, numOfDictionaries);
            //if there was a problem in the search function
            if (flag)
                printf("The search has failed successfully!\n");
            break;
        case 5: //delete a dictionary
            if (numOfDictionaries == 0)
            {
                printf("This option is not available right now, try again:\n");
                tryAgainFlag=1;
                scanf("%d",&menuInput);
                break;
            }

            tmpPtrToNewDict = deleteDict(dictionaries, numOfDictionaries);
            //if alloction faild in the delete proccess
            if (tmpPtrToNewDict == NULL)
                break;

            printf("The dictionary has been deleted successfully!\n");
            dictionaries = tmpPtrToNewDict;
            //lower the dictionaries counter by one
            numOfDictionaries--;
            //if there are no dictionaries allocate memory again 
            if (numOfDictionaries == 0)
            {
                free(tmpPtrToNewDict);
                tmpPtrToNewDict = (Dictionary**)malloc(sizeof(Dictionary*));
                if (tmpPtrToNewDict != NULL)
                    dictionaries = tmpPtrToNewDict;
            }

            tmpPtrToNewDict = NULL;
            break;
        case 6: //exit(free all and close program)
            dictionaries = allDictsFree(dictionaries, numOfDictionaries);
            //after all memory is freed, free the dictionaries array memory and exit
            free(dictionaries);
            break;
        default:
            printf("Wrong option, try again:\n");
            break;
        }
    }
    printf("Bye!\n");
    return 0;
}
