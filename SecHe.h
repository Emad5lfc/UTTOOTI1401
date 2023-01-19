#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>

typedef enum InputBreak
{
    Space,
    Enter,
    Both
} InputBreak;

typedef enum SearchFlag
{
    CurrentElement,
    PreviousElement
}SearchFlag;

typedef enum CountdownFlag
{
    Show,
    Hide
} CountdownFlag; 


typedef enum UserPrintFlag
{
    ShowPassword,
    HidePassword,
    ShowStars
} UserPrintFlag;


char* InputString(InputBreak breaker);

char* GetInput(InputBreak breaker);

int Exit();

void DelayedStringPrint(char* str, int delay, CountdownFlag ctflag, char *DelayMsg, int BeforeClearFlag, int AfterClearFlag);

int DigitCount(int n);