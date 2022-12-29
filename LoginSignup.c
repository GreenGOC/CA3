#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "Helper.h"
#include "Structure.h"

bool Login_Conflict()
{
    char choice = 'c';
    fflush(stdin);
    scanf("%c", &choice);
    while (choice != 'Y' && choice != 'y' && choice != 'n' && choice != 'N')
    {
        printf("\nUnknown command! (Y)es or (N)o ? ");
        fflush(stdin);
        scanf("%c", &choice);
    }
    if (choice == 'Y' || choice == 'y')
    {
        return true;
    }
    return false;
}
void Signup(User *headuser, User **current_user, char *username, char *password)
{
    system("cls");
    if (username == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        free(password);
        return;
    }
    if (password == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        free(username);
        return;
    }
    if (Find_User(headuser, username) != NULL)
    {
        Error_Handler(DUPLICATE_USERNAME);
        free(username);
        free(password);
        return;
    }
    User *user = (User *)malloc(sizeof(User));
    user->username = username;
    user->password = password;
    user->next_user = NULL;
    int id = 1;
    while (headuser->next_user != NULL)
    {
        headuser = headuser->next_user;
        id++;
    }
    user->user_id = id;
    headuser->next_user = user;
    printf("Operation Succeded! User %s have signed up.\n", user->username);
    if (*current_user != NULL)
    {
        printf("You are already logged in as %s, Would you like to log out? (Y)es (N)o : ", (*current_user)->username);
        if (Login_Conflict())
        {
            (*current_user) = user;
            printf("You have log out and signed in as %s\n", username);
        }
        else
        {
            printf("You decided to keep up with this account. ");
        }
    }
    else
    {
        (*current_user) = user;
    }
}
void Login(User *headuser, User **current_user, char *username, char *password)
{
    system("cls");
    if (username == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        return;
    }
    if (password == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        return;
    }
    User *user = Find_User(headuser, username);
    if (user == NULL)
    {
        Error_Handler(USER_NOT_FOUND);
        return;
    }
    if (Compare_String(password, user->password))
    {
        if ((*current_user) != NULL)
        {
            printf("You are already logged in as %s, Would you like to log out? (Y)es (N)o : ", (*current_user)->username);
            if (Login_Conflict())
            {
                printf("Operation Succeded! Logged in as %s", user->username);
                *current_user = user;
            }
        }
        else
        {
            printf("Operation Succeded! Logged in as %s", user->username);
            *current_user = user;
        }
    }
    else
    {
        Error_Handler(PASSWORD_INCORRECT);
        return;
    }
}
void Logout(User **current_user)
{
    system("cls");
    if (*current_user == NULL)
    {
        Error_Handler(NOT_LOGGED_IN);
        return;
    }
    printf("You have logged out from %s\n", (*current_user)->username);
    *current_user = NULL;
}
void Remove_Account(User *headuser, User **current_user)
{
    system("cls");
    if ((*current_user) == NULL)
    {
        Error_Handler(NOT_LOGGED_IN);
        return;
    }
    while (headuser->next_user != *current_user)
    {
        headuser = headuser->next_user;
    }
    printf("Are you sure you want to delete your account? (Y)es , (N)o : ");
    char choice = 'c';
    fflush(stdin);
    scanf("%c", &choice);
    while (choice != 'Y' && choice != 'y' && choice != 'n' && choice != 'N')
    {
        printf("\nUnknown command! (Y)es or (N)o?");
        fflush(stdin);
        scanf("%c", &choice);
    }
    if (choice == 'n' || choice == 'N')
    {
        printf("Operation Canceled!\n");
    }
    else
    {
        printf("User %s has gone for ever ):", (*current_user)->username);
        headuser->next_user = headuser->next_user->next_user;
        free((*current_user)->username);
        free((*current_user)->password);
        free(*current_user);
        (*current_user) = NULL;
    }
}