#include "SecHe.h"
char* InputString(InputBreak breaker)
{
    char* res = calloc(1,sizeof (char)); /* creates a dynamic array with length of 1 */
    res[0] = '\0';
    int pos = 0; /* saves the position where new characters have to be inserted */
    char t; /* the character that gets scanned (it's used to pop characters stored in stack) */
    do
    {
        scanf("%c",&t);
        res[pos] = t; /* put inputed character at the end of the array */
        pos++;
        res = (char*)realloc(res,(pos+1)*sizeof (char)); /* increases array's size for inserting more characters if needed */
    }
    while( ( (breaker == Space) && (t != ' ') ) || ( (breaker == Enter) && (t != '\n') ) || ( (breaker == Both) && ( (t != ' ') && (t != '\n') ) ) );
    res = (char*)realloc(res,(pos)*sizeof (char)); /* no need for res[pos] so I resize res to drop it */
    res[pos-1] = '\0'; /* closes the end of the string, replacing \n with \0 */
    return res;
}


/*
  Description: InputString (the function above) will accept empty values, therefore, this function is used as a successor
  for it, running the function above as long as the value is empty.
  Inputs:
    type of input stopping flag
  Output:
    the dynamic array mentioned in description
  Side Effects:
    -
*/
char *GetInput(InputBreak breaker)
{
    char* res;
    res = InputString(breaker);
    while(res[0] == '\0')
    {
        free(res);
        res = InputString(breaker);
    }
    return res;
}


/*
  Description: Ends the program with an approppriate message.
  ** The function can only be used in collaboration with an exiting command like return in main or function exit(int) elsewhere
  Inputs:
    -
  Output:
    number 1 as an integer
  Side Effects:
    The whole console surface will be cleared and a message will be shown
*/
int Exit()
{
    system("cls");
    printf("\n\n%60s\n%60s%c\n","Bye...   ","See you again",1);
    return 1;
}


/*
  Description: Prints a message with a delay before proceeding the rest of the program
  Inputs:
    1. the message you want to show (str)
    2. delay period (delay)
    3. countdown flag to specify whether or not show time left before proceeding the rest (ctflag)
    4. message to be shown if the countdown is being shown (DelayMsg)
    5. whether or not clear the console before delay period
    6. whether or not clear the console before delay period
  Output:
    -
  Side Effects:
    Under certain conditions, the function might clear the whole console
*/
void DelayedStringPrint(char *str, int delay, CountdownFlag ctflag, char* DelayMsg, int BeforeClearFlag, int AfterClearFlag)
{
    if(ctflag == Hide)
    {
        if(BeforeClearFlag)
            system("cls");
        puts(str);
        sleep(delay);
        if(AfterClearFlag)
            system("cls");
        return;
    }

    for(int i=delay;i>0;i--)
    {
        system("cls");
        printf("%s\n%s %d...",str,DelayMsg,i);
        sleep(1);
    }

}


/*
  Description: Calculates the count of a number's digits
  Inputs:
    1. a number
  Outputs:
    the count of the number's digits
  Side Effects:
    -
*/
int DigitCount(int n)
{
    int res=0;
    do
    {
        res++;
        n = n/10;
    }
    while(n>0);
    return res;
}
