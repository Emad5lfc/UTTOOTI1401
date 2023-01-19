#define true 1  
#define false 0 
#include "Structheader.h"
int main()
{
    User *dummy = malloc(sizeof(User));
    dummy->Next = NULL;

    char *Username = NULL;
    char *Password = NULL;
    int LoginFlag = 0;

    do
    {
        system("cls");

        char *command;
        printf("Enter our command:\n");
        command = GetInput(Both);

        if (strcmpi(command, "exit") == 0)
        {
            FILE *useroutput = fopen("Users.txt", "w");
            FILE *postsoutput = fopen("Posts.txt", "w");
            User *current = dummy->Next;
            while (current != NULL)
            {
                fprintf(useroutput, "%s %s\n", current->Username, current->Password);
                Post *posts = current->PostsDummy;
                if (posts == NULL)
                {
                    current = current->Next;
                    continue;
                }
                posts = posts->Next;
                while (posts != NULL)
                {
                    fprintf(postsoutput, "%s %s %d\n", posts->Text, posts->SenderID, posts->Likes);
                    posts = posts->Next;
                }
                fprintf(postsoutput, "%s\n", "=======================");
                current = current->Next;
            }

            fclose(useroutput);
            fclose(postsoutput);
            system("cls");
            return Exit();
        }

        else if (strcmpi(command, "help") == 0)
        {
            printf("%s\n\n", "Welcome to Ut Tuti \x1\n"
                             "Here's the list of commands you can use:\n\n"
                             "1. signup <new user name> <password>\n"
                             "example: signup hamid 12#t\n\n"
                             "2. login <user name> <password>\n"
                             "example: login Emad Emad5lfc\n\n"
                             "3. post <text>\n"
                             "example: post Argentina is the winner of the world cup!!\n\n"
                             "4. like <user name> <post ID>\n"
                             "example: like Mamad 7\n\n"
                             "5. logout\n"
                             "example: logout\n\n"
                             "6. delete <post_id>\n"
                             "example: delete 3\n\n"
                             "7. info\n"
                             "example: info\n\n"
                             "8. find_user <username>\n"
                             "example: find_user javad\n\n"
                             "9. help\n"
                             "example: help\n\n"
                             "10. exit\n"
                             "example: exit\n\n");
                             getch();
        }

        if (strcmpi(command, "signup") == 0)
        {
            if (LoginFlag == 0)
            {
                Username = GetInput(Both);
                Password = GetInput(Both); /* take username and password */
                if (!SignUpUser(dummy, Username, Password))
                {
                    printf("Failed to signup user\nThis could be due to lack of memory or repeated username! Try again in\n");
                    getch();
                    fflush(stdin);
                    free(command);
                    continue;
                }
                system("cls");
                printf("Welcome...\n\nYour username: %s\nYour password: %s\n", Username, Password);
                getch();
                LoginFlag = 1;
            }
            else
            {
                printf("You're already logged in\nLog out first\n");
                getch();
            }
        }

        else if (strcmpi(command, "logout") == 0)
        {
            if (LoginFlag == 1)
            {
                free(Username);
                free(Password);
                LoginFlag = 0;
                printf("Logged out successfully...\n");
                getch();
            }
            else
            {
                printf("You're not logged in yet\nLog in or sign up first\n");
                getch();
            }
        }

        else if (strcmpi(command, "login") == 0)
        {
            if (LoginFlag == 0)
            {
                Username = GetInput(Both);
                Password = GetInput(Both);
                User *user = SearchUser(dummy, Username, CurrentElement);
                if (user == NULL)
                {
                    printf("USERNAME NOT FOUND!\n Try a correct username in\n");
                    getch();
                    free(Username);
                    free(Password);
                    system("cls");
                    fflush(stdin);
                    free(command);
                    continue;
                }
                if (strcmpi(user->Password, Password) != 0)
                {
                    printf("WRONG PASSWORD\nTry again with the correct password in\n");
                    getch();
                    free(Username);
                    free(Password);
                    fflush(stdin);
                    free(command);
                    continue;
                }
                LoginFlag = 1;
                printf("Welcome...\n\nYour username: %s\nYour password: %s", Username, Password);
                getch();
                sleep(4);
                LoginFlag = 1;
            }
            else
            {
                printf("You're already logged in\nLog out first");
                getch();
            }
        }

        else if (strcmpi(command, "post") == 0)
        {
            if (LoginFlag == 1)
            {
                char *text = GetInput(Enter);
                if (!SendPost(SearchUser(dummy, Username, CurrentElement)->PostsDummy, Username, text))
                {
                    printf("Failed to send post\nThis could be due to lack of memory\nTry again in\n");
                    getch();
                }
                else
                {
                    printf("Post sent successfully\n");
                    getch();
                }
            }
            else
            {
                printf("You're not logged in yet\nLog in or sign up first");
                getch();
            }
        }

        else if (strcmpi(command, "info") == 0)
        {
            if (LoginFlag == 1)
            {
                InfoUser(SearchUser(dummy, Username, CurrentElement), ShowPassword);
                puts("");
            }
            else
            {
                printf("You're not logged in yet\nLog in or sign up first\n");
                getch();
            }
        }

        else if (strcmpi(command, "find_user") == 0)
        {
            if (LoginFlag == 1)
            {
                char *un = GetInput(Both);
                User *us = SearchUser(dummy, un, CurrentElement);
                if (us == NULL)
                {
                    printf("Username not found...");
                    getch();
                }
                else
                {
                    InfoUser(us, HidePassword);
                    getch();
                    puts("\n");
                }
            }
            else
            {
                printf("You're not logged in yet\nLog in or sign up first");
                getch();
            }
        }

        if (strcmpi(command, "delete") == 0)
        {
            if (LoginFlag == 1)
            {
                char *c_id = GetInput(Both);
                int id = atoi(c_id);
                Post *post = FindPost(SearchUser(dummy, Username, CurrentElement)->PostsDummy, id, CurrentElement);
                if (post == NULL)
                {
                    printf("Post ID not found...");
                    getch();
                }
                else
                {
                    printf("Post Removed Successfully");
                    getch();
                }
            }
            else
            {
                printf("You're not logged in yet\nLog in or sign up first");
                getch();
            }
        }

        if (strcmpi(command, "like") == 0)
        {
            if (LoginFlag == 1)
            {
                char *likeuser = GetInput(Both);
                char *likepostid = GetInput(Both);
                User *user = SearchUser(dummy, likeuser, CurrentElement);
            }
        }
        {
            fflush(stdin);
            free(command);
            continue;
        }

        fflush(stdin);
        free(command); /*there is no longer any need for its old data. to prevent memory leak.*/
    } while (true);
    return 0;
}