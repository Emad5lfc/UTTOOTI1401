#include "Structheader.h"


/*
  Description: Finds address of last node in a linked list
  Input:
    1. any element in the list
  Output:
    PrimaryKey of the last element
  Side effects:
    -
*/
User* LastUser(User* last)
{
    while (last->Next != NULL)
    {
        last = last->Next;
    }
    return last;
}


/*
  Description: Adds a user with given features and 0 posts to Users List
  Input:
    1. dummy of users list
    2. number of users already signed up
    3. username of the user that's going to be added
    4. password of the user that's going to be added
  Output:
    -
  Side effects:
    one user will be added to user list
*/
int SignUpUser(User* dummy, char* username, char* password)
{
    User* current = dummy;
    if(dummy->Next != NULL)
    {
        do
        {
            current = current->Next;
            if(strcmp(current->Username,username) == 0)
            {
                return 0;
            }
        }
        while(current->Next != NULL);
    }
    current->Next = (User*)malloc(sizeof (User));
    current = current->Next;
    if(current == NULL)
    {
        return 0;
    }

    int user_size = 0;
    int pass_size = 0;
    while (username[user_size] != '\0')
    {
        user_size ++;
    }
    while (password[pass_size] != '\0')
    {
        pass_size ++;
    }
    current->Username = (char*)calloc(user_size+1, sizeof (char));
    current->Password = (char*)calloc(pass_size+1, sizeof (char));
    for(int i=0;i<=user_size;i++)
    {
        current->Username[i] = username[i];
    }
    for(int i=0;i<=pass_size;i++)
    {
        current->Password[i] = password[i];
    }
    current->PostsDummy = malloc(sizeof (Post));
    current->PostsDummy->Next = NULL;
    current->Next = NULL;
    current->LikedPostsDummy = malloc(sizeof (Post));
    current->LikedPostsDummy->Next = NULL;
    return 1;
}


/*
  Description: Deletes all posts of the user
  Inputs:
    pointer to the user
  Output:
    -
  Side Effects:
    -
*/
void DelPosts(User* user)
{
    if(user == NULL)
        return;
    Post* posts = user->PostsDummy;
    if(posts == NULL)
        return;
    posts = posts->Next;
    while(posts != NULL)
    {
        Post* nxt = posts->Next;
        free(posts);
        posts = nxt;
    }
    posts = user->LikedPostsDummy;
    if(posts == NULL)
        return;
    posts = posts->Next;
    while(posts != NULL)
    {
        Post* nxt = posts->Next;
        free(posts);
        posts = nxt;
    }
}


/*
  Description: Deletes a user's account and all its belongings including its posts
  Inputs:
    1. dummy of the users linked list
    2. username of the user about to get deleted
  Output:
    1: if the operation was done successfully
    0: otherwise
  Side Effects:
    -
*/
int DeleteAccount(User* dummy, char* username)
{
    if(dummy == NULL)
        return 0;
    if(dummy->Next == NULL)
        return 0;
    User* cur = dummy;
    while(cur->Next != NULL)
    {
        if(strcmp(cur->Next->Username,username) == 0 )
        {
            User* deleter = cur->Next;
            cur->Next = deleter->Next;
            DelPosts(deleter);
            free(deleter);
            return 1;
        }
        cur = cur->Next;
    }
    return 0;
}


/*
  Description: Finds user based on username
  Inputs:
    1. dummy of the users linked list
    2. username of the user about to get deleted
    3. Search Flag
  Output:
    NULL if the user doesn't exist
    address of the user if exists and flag is CurrentElement
    address of the previous user if exists and flag is PrevoiusElement
  Side Effects:
    -
*/
User* SearchUser(User* dummy,char* username , SearchFlag flag)
{
    if(dummy == NULL)
        return NULL;
    if(dummy->Next == NULL)
        return NULL;
    User* cur = dummy;
    while(cur->Next != NULL)
    {
        if(strcmp(cur->Next->Username,username) == 0)
        {
            if(flag == PreviousElement)
                return cur;
            return cur->Next;
        }
        cur = cur->Next;
    }
    return NULL;
}


/*
  Description: Finds a post using the same searching flag algorithm as FindUser
  Inputs:
    1. dummy of posts
    2. id of the post
    3. searching flag
  Output:
    same as FindUser, only post instead of user
  Side Effects:
    -
*/
Post* FindPost(Post* dummy, int id, SearchFlag flag)
{
    if(dummy == NULL)
        return NULL;
    if(dummy->Next == NULL)
        return NULL;
    Post* cur = dummy;
    while(cur->Next != NULL)
    {
        if( cur->Next->PostID == id)
        {
            if(flag == PreviousElement)
                return cur;
            return cur->Next;
        }
        cur = cur->Next;
    }
    return NULL;
}


/*
  Description: Finds address of last node in a linked list
  Input:
    1. dummy of the users linked list
    2. ID of the post's sender
    3. post's ID
  Output:
    1 if operation was performed successfully, 0 otherwise
  Side effects:
    the number of likes a post has will increase by 1
*/
int LikePost(User* dummy, char* senderId, int postId)
{
    User* user = SearchUser(dummy,senderId,CurrentElement);
    if(user == NULL)
        return 0;
    Post* post = FindPost(user->PostsDummy,postId,CurrentElement);
    if(post == NULL)
        return 0;
    post->Likes++;
    return 1;
}


/*
  Description: Prints a user's information
  Input:
    1. address of the mentioned user
  Output:
    -
  Side effects:
    information of the user might be printed
*/
void InfoUser(User* user, UserPrintFlag flag)
{
    if(user == NULL)
        return;
    printf("Username: %s\n",user->Username);
    if(flag == ShowPassword)
    {
        printf("Password: %s\n",user->Password);
    }
    else if(flag == ShowStars)
    {
        printf("Password: ");
        for(unsigned int i=0;i<strlen(user->Password);i++)
        {
            printf("%c",'*');
        }
        puts("");
    }
    Post* dum = user->PostsDummy;
    if(dum == NULL)
        return;
    printf("%30s%c%c\n","Posts",25,25);
    while(dum->Next != NULL)
    {
        PrintPost(dum->Next);
        dum = dum->Next;
        puts("=========================================================");
    }
}