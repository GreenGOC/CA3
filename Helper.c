#include <stdbool.h>
#include <stdio.h>

#include "Structure.h"

#define USER_NOT_FOUND 101
#define POST_NOT_FOUND 102
#define POST_ALREADY_LIKED 103
#define POST_NOT_LIKED 104
#define NOT_LOGGED_IN 105
#define PASSWORD_INCORRECT 106
#define DUPLICATE_USERNAME 107
#define UNKNOWN_ERROR 108

bool Compare_String(char *string1, char *string2)
{
    int index = 0;
    while (*(string1 + index) != '\0' && *(string2 + index) != '\0')
    {
        if (*(string1 + index) != *(string2 + index))
        {
            return false;
        }
        index++;
    }
    if (*(string1 + index) == *(string2 + index))
    {
        return true;
    }
    return false;
}
Post *Find_Post(Post *headpost, char *username, int post_id)
{
    int count = 0;
    if (headpost->next_post == NULL)
        return NULL;
    while (headpost->next_post != NULL)
    {

        if (Compare_String(headpost->next_post->username, username))
        {
            count++;
        }
        if (count == post_id)
            break;
        headpost = headpost->next_post;
    }
    if (count != post_id || post_id == 0)
    {
        return NULL;
    }
    return headpost;
}
void Error_Handler(int error)
{
    switch (error)
    {
    case POST_NOT_LIKED:
        printf("Operation Failed! You haven't liked this post.\n");
        break;
    case POST_ALREADY_LIKED:
        printf("Operation Failed! You have already liked this post.\n");
        break;
    case USER_NOT_FOUND:
        printf("Operation Failed! Username not found.\n");
        break;
    case POST_NOT_FOUND:
        printf("Operation Failed! Invalid post id.\n");
        break;
    case PASSWORD_INCORRECT:
        printf("Operation Failed! Invalid password.\n");
        break;
    case DUPLICATE_USERNAME:
        printf("Operation Failed! Username is taken by another member.\n");
        break;
    case NOT_LOGGED_IN:
        printf("Operation Failed! You haven't logged in.\n");
        break;
    case UNKNOWN_ERROR:
        printf("Operation Failed! Unknown error.\n");
        break;
    }
}
void Get_String(char **text, short is_text)
{
    *text = (char *)malloc(sizeof(char));
    int length = 0;
    for (;; length++)
    {
        *text = (char *)realloc(*text, length + 1);
        if ((*text) == NULL)
        {
            Error_Handler(UNKNOWN_ERROR);
            return;
        }
        (*text)[length] = getchar();
        if (((is_text == 0) && ((*text)[length] == ' ')) || ((*text)[length] == '\n'))
            break;
    }
    (*text)[length] = '\0';
}
int String_To_Int(char *input)
{
    int num = 0;
    for (int i = 0; *(input + i) != '\0'; i++)
    {
        num = 10 * num + (int)(*(input + i)) - 48;
    }
    return num;
}

void press_enter()
{
    fflush(stdin);
    printf("\nPress enter to continue...");
    getchar();
    fflush(stdin);
}
User *Find_User(User * headuser, char * username)
{
    while (headuser != NULL && !Compare_String(headuser->username, username))
    {
        headuser = headuser->next_user;
    }
    if (headuser == NULL)
    {
        return NULL;
    }
    else
    {
        return headuser;
    }
}