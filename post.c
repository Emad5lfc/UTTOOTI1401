#include "Structheader.h"

/*
  Description: Generates a unique post number. One that is bigger than them all.
  Inputs:
    1. Dummy of the posts linked list
  Output:
    The generated post ID
  Side Effects:
    -
*/
int CreatePostNum(Post* dummy)
{
    int res = 0;
    if(dummy == NULL)
        return res;
    if(dummy->Next == NULL)
        return res;
    Post* current = dummy->Next;
    while(current != NULL)
    {
        if(current->PostID >= res)
        {
            res = current->PostID;
        }
        current = current->Next;
    }
    res ++;
    return res;
}

int SendPost(Post* dummy, char* senderID, char* text)
{
    if(dummy == NULL)
    {
        return 0;
    }
    int id = CreatePostNum(dummy);
    Post* pst = malloc(sizeof (Post));
    pst->Next = NULL;
    pst->Likes = 0;
    pst->PostID = id;
    pst->Text = calloc(strlen(text)+1,sizeof (char));
    strcpy(pst->Text,text);
    pst->Text[strlen(text)] = '\0';

    pst->SenderID = calloc(strlen(senderID)+1,sizeof (char));
    strcpy(pst->SenderID,senderID);
    pst->SenderID[strlen(senderID)] = '\0';

    Post* current = dummy;
    while(current->Next != NULL)
    {
        current = current->Next;
    }
    pst->PrimaryKey = malloc((strlen(senderID)+DigitCount(id)+2)*sizeof (char));
    strcpy(pst->PrimaryKey,senderID);
    strcat(pst->PrimaryKey,"_");
    char* charid = malloc(DigitCount(id)+1);
    itoa(id,charid,10);
    strcat(pst->PrimaryKey,charid);
    pst->PrimaryKey[strlen(senderID)+DigitCount(id)+1] = '\0';
    current->Next = pst;
    free(charid);
    return 1;
}


/*
  Description: Sends a post to list of liked post, making it possible to find out which posts the user has liked
  Inputs:
    1. Dummy of that user's posts linked list
    2. ID of the sender user
    3. ID of the post
  Output:
    An integer that will be 0 if the operation fails and 1 otherwise
  Side Effects:
    One post with a primary key based on given information will be addedd to liked list of a user's liked posts
*/
int SendToLikedPost(Post* dummy, char *senderID, int postid)
{
    if(dummy == NULL)
    {
        return 0;
    }
    int id = postid;
    Post* pst = malloc(sizeof (Post));
    pst->Next = NULL;
    pst->SenderID = calloc(strlen(senderID)+1,sizeof (char));
    strcpy(pst->SenderID,senderID);
    pst->SenderID[strlen(senderID)] = '\0';

    Post* current = dummy;
    while(current->Next != NULL)
    {
        current = current->Next;
    }
    pst->PrimaryKey = malloc((strlen(senderID)+DigitCount(id)+2)*sizeof (char));
    strcpy(pst->PrimaryKey,senderID);
    strcat(pst->PrimaryKey,"_");
    char* charid = malloc(DigitCount(id)+1);
    itoa(id,charid,10);
    strcat(pst->PrimaryKey,charid);
    pst->PrimaryKey[strlen(senderID)+DigitCount(id)+1] = '\0';
    current->Next = pst;
    free(charid);
    return 1;
}


/*
  Description: Deletes a post
  Inputs:
    1. dummy of posts
    2. post id
  Output:
    1: if operation was successfuly done
    0: otherwise
  Side Effects:
    One post with the given text will be addedd to the linked list of the user
*/



/*
  Description: Prints a post, number of its likes, and its sender's ID
  Inputs:
    1. PrimaryKey of the post that is going to be printed
  Output:
    -
  Side Effects:
    The mentioned information will be printed
*/
void PrintPost(Post* post)
{
    printf("Post_ID: %d\nPost_Address: %s\nLikes: %d\nText: %s\n",post->PostID,post->PrimaryKey,post->Likes,post->Text);
}


/*
  Description: Generates post primary key
  Inputs:
    1. Sender ID
    2. Post ID
  Output:
    a dynamic char array containing generated PK(Primary Key)
  Side Effects:
    -
*/
char* CreatePostP_KEY(char* senderid, int postid)
{
    char* result = malloc(strlen(senderid)+DigitCount(postid)+2);
    strcpy(result,senderid);
    char* num = malloc((DigitCount(postid)+1)*sizeof (char));
    itoa(postid,num,10);
    strcat(result,"_");
    strcat(result,num);
    free(num);
    return result;
}
int DelPost(Post* dummy, int postid)
{
    Post* cur = FindPost(dummy,postid,PreviousElement);
    if(cur == NULL)
        return 0;
    Post* deleter = cur->Next;
    cur->Next = deleter->Next;
    free(deleter);
    return 1;
}