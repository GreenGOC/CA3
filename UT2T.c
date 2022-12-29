#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <conio.h>

#include "FileProcess.h"
#include "LoginSignup.h"
#include "Post.h"
#include "Screen.h"

int main()
{
    User *headuser = (User *)malloc(sizeof(User)); /*Signing up first user (Can't be done by function )*/
    headuser->username = "Developer";
    headuser->password = "NULL";
    headuser->user_id = 0;
    headuser->next_user = NULL;
    User *current_user = NULL;
    Post *headpost = (Post *)malloc(sizeof(Post)); /* Creating a headpost (Can't be done by function)*/
    headpost->username = headuser->username;
    headpost->like_count = 0;
    headpost->post_text = "The program was created in 2022/12/21";
    headpost->post_id = 0;
    headpost->next_post = NULL;
    headpost->comment = NULL;
    headpost->liked_user = NULL;
    printf("Hello\nWelcome to UT2T\n\n");
    getch(); /*Waiting for user respond*/
    int command_number = 0;
    Fetch_From_File(headuser, headpost);
    while (1)
    {
        Refresh_Feed(headpost);
        Show_Commands(current_user);
        char *command = NULL;
        int post_id = 0;
        char *username = NULL;
        char *password = NULL;
        char *text = NULL;
        Get_String(&command, NOT_TEXT);
        int command_number = Check_Command(command);
        switch (command_number)
        {
        case LIKE:
            Get_String(&username, NOT_TEXT);
            scanf("%d", &post_id);
            Like_Dislike_Post(headuser, headpost, current_user, username, post_id, LIKE);
            free(username);
            break;
        case DISLIKE:
            Get_String(&username, NOT_TEXT);
            scanf("%d", &post_id);
            Like_Dislike_Post(headuser, headpost, current_user, username, post_id, DISLIKE);
            free(username);
            break;
        case SIGNUP:
            Get_String(&username, NOT_TEXT);
            Get_String(&password, NOT_TEXT);
            Signup(headuser, &current_user, username, password);
            break;
        case LOGIN:
            Get_String(&username, NOT_TEXT);
            Get_String(&password, NOT_TEXT);
            Login(headuser, &current_user, username, password);
            free(username);
            free(password);
            break;
        case LOGOUT:
            Logout(&current_user);
            break;
        case POST:
            Get_String(&text, TEXT);
            New_Post(headpost, current_user, text);
            break;
        case DELETE:
            scanf("%d", &post_id);
            Delete_Post(current_user, headpost, post_id);
            break;
        case INFO:
            Show_Info(current_user, headpost);
            break;
        case QUIT:
            Save_To_File(headuser, headpost);
            printf("\n\n See you later!\n");
            fflush(stdin);
            getchar();
            exit(1);
        case SHOW:
            Get_String(&username, NOT_TEXT);
            scanf("%d", &post_id);
            Show_Full_Post(headpost, username, post_id);
            free(username);
            break;
        case COMMENT:
            Get_String(&username, NOT_TEXT);
            scanf("%d ", &post_id);
            Get_String(&text, TEXT);
            New_Comment(headpost, current_user, headuser, username, text, post_id);
            break;
        case REMOVE_ACCOUNT:
            Remove_Account(headuser, &current_user);
            break;
        case REPOST:
            Get_String(&username, NOT_TEXT);
            scanf("%d", &post_id);
            Post_Again(headuser, headpost, current_user, username, post_id);
            free(username);
            break;
        case FIND:
            Get_String(&username,NOT_TEXT);
            Show_User_Info(headuser,headpost,username);
            free(username);
            break;
        default:
            system("cls");
            printf("Unknown Command!");
            break;
        }
        fflush(stdin);
        free(command);
        press_enter();
    }
}
