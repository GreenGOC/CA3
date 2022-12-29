#include <stdio.h>
#include <stdbool.h>

#include "Structure.h"

#define LIKE 1
#define DISLIKE 2
#define SIGNUP 3
#define LOGIN 4
#define LOGOUT 5
#define POST 6
#define DELETE 7
#define INFO 8
#define QUIT 9
#define SHOW 10
#define COMMENT 11
#define REMOVE_ACCOUNT 12
#define REPOST 13
#define FIND 14
#define NOT_TEXT 0
#define TEXT 1

void Refresh_Feed(Post *headpost)
{
    system("cls");
    printf("\nRefreshing Feed...");
    printf("\n_______________________________\n");
    headpost = headpost->next_post;
    while (headpost != NULL)
    {
        Show_Post(headpost);
        printf("\n.................................\n");
        headpost = headpost->next_post;
    }
}
int Check_Command(char *command)
{
    char *commands[] = {
        "like", "dislike", "signup", "login", "logout", "post", "delete", "info", "quit", "show", "comment", "remove", "repost","find"};
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; commands[i][j] != '\0' && command[j] != '\0'; j++)
        {
            char ch1 = *(*(commands + i) + j);
            char ch2 = command[j];
            if (ch2 != ch1 && ch1 - ch2 != 32)
                break;
            if (command[j + 1] == '\0' && (ch1 == ch2 || ch1 - ch2 == 32))
                return i + 1;
        }
    }
    return 0;
}
void Show_Commands(User *user)
{
    if (user == NULL)
    {
        printf("\nPost     Delete     Like     Dislike     Info  |  Login    Signup    Quit");
    }
    else
    {
        printf("\nPost     Delete     Like     Dislike     Info  |  %s      Logout    Remove account     Quit", user->username);
    }
    printf("\nShow     Comment    Repost   Find\n");
    printf("\n     Command : ");
}