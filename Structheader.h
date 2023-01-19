#include "SecHe.h"
typedef struct Post
{
    char* SenderID;
    char* PrimaryKey;
    int PostID;
    int Likes;
    char* Text;

    struct Post* Next;
} Post;
int CreatePostNum(Post* dummy);
int SendPost(Post* dummy, char *senderID, char *text);
int SendToLikedPost(Post* dummy, char *senderID, int postid);
int DelPost(Post *dummy, int postid);
int EditPost(Post *dummy, int postid, char *text);
void PrintPost(Post* post); 
char* CreatePostP_KEY(char* senderid, int postid);

typedef struct User
{
    char* Username;
    char* Password;
    Post* PostsDummy;
    Post* LikedPostsDummy;
    struct User* Next;
} User;
User* LastUser(User *first);
int SignUpUser(User* dummy, char* username, char* password);
void DelPosts(User* user);
int DelAccount(User* dummy, char* username);
Post* FindPost(Post* dummy, int id, SearchFlag flag);
User* SearchUser(User* dummy, char *username, SearchFlag flag);
int LikePost(User* dummy, char* senderId, int postId);
void InfoUser(User* user, UserPrintFlag flag);