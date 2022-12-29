#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>

#include "Helper.h"
#include "Structure.h"

#define LIKE 1
#define DISLIKE 2

void Show_Post(Post *headpost)   
{
    printf("\n         User :               %s", headpost->username);
    printf("\n         Post ID:             #%d", headpost->post_id);
    printf("\n         %d people have liked it!", headpost->like_count);
    printf("\n\n         Text: %s\n", headpost->post_text);
}
void Show_Full_Post(Post *headpost, char *username, int post_id)
{
    system("cls");    
    if (username == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        return;
    }
    headpost = Find_Post(headpost, username, post_id);
    if (headpost == NULL)
    {
        Error_Handler(POST_NOT_FOUND);
        return;
    }
    headpost = headpost->next_post;
    printf("\n         User :               %s", headpost->username);
    printf("\n         Post ID:             #%d", headpost->post_id);
    printf("\n         %d people have liked it!", headpost->like_count);
    printf("\n\n         Text: %s\n", headpost->post_text);
    printf("     Liked by : ");
    Like *liker = headpost->liked_user;
    while (liker != NULL)
    {
        printf("%s  -  ", liker->username);
        liker = liker->next_like;
    }
    printf("\n     Comments: \n");
    Comment *commentor = headpost->comment;
    while (commentor != NULL)
    {
        printf("\n%s : \n %s\n", commentor->username, commentor->text);
        commentor = commentor->next_comment;
    }
}
void New_Post(Post *headpost, User *current_user, char *text)
{
    system("cls");
    if (current_user == NULL)
    {
        Error_Handler(NOT_LOGGED_IN);
        free(text);
        return;
    }
    if (text == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        return;
    }
    Post *new_post = (Post *)malloc(sizeof(Post));
    if (new_post == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        free(text);
        return;
    }
    new_post->username = current_user->username;
    new_post->like_count = 0;
    new_post->next_post = NULL;
    new_post->post_text = text;
    new_post->comment = NULL;
    new_post->liked_user = NULL;
    int id = 1;
    while (headpost->next_post != NULL)
    {
        headpost = headpost->next_post;
        id = headpost->post_id;
    }
    new_post->post_id = id+1;
    headpost->next_post = new_post;
    printf("You have created a new post :");
    Show_Post(new_post);
}
void Delete_Post(User *current_user, Post *headpost, int post_id)
{
    system("cls");
    if (current_user == NULL)
    {
        Error_Handler(NOT_LOGGED_IN);
        return;
    }
    headpost = Find_Post(headpost, current_user->username, post_id);
    if (headpost == NULL)
    {
        Error_Handler(POST_NOT_FOUND);
        return;
    }
    Post *temp = headpost->next_post;
    headpost->next_post = temp->next_post;
    printf("You have deleted this post: ");
    Show_Post(temp);
    Like *like = temp->liked_user;
    while (like != NULL && like->next_like != NULL)
    {
        Like *tempL = like->next_like;
        like->next_like = tempL->next_like;
        free(tempL);
    }
    if (like != NULL)
        free(like);
    Comment *comment = temp->comment;
    while (comment != NULL && comment->next_comment != NULL)
    {
        Comment *tempC = comment->next_comment;
        comment->next_comment = tempC->next_comment;
        free(tempC->text);
        free(tempC);
    }
    if (comment != NULL)
        free(comment);
    free(temp);
}
bool Has_Liked(Post *post, char *username)
{
    Like *liker = post->liked_user;
    while (liker != NULL)
    {
        if (Compare_String(liker->username, username))
        {
            return true;
        }
        liker = liker->next_like;
    }
    return false;
}
void Like_Dislike_Post(User *headuser, Post *headpost, User *current_user, char *username, int post_id, short code)
{
    system("cls");
    if (current_user == NULL)
    {
        Error_Handler(NOT_LOGGED_IN);
        return;
    }
    User *liked_user = NULL;
    if (username == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        return;
    }
    fflush(stdin);
    liked_user = Find_User(headuser, username);
    if (liked_user == NULL)
    {
        Error_Handler(USER_NOT_FOUND);
        return;
    }
    headpost = Find_Post(headpost, username, post_id);
    if (headpost == NULL)
    {
        Error_Handler(POST_NOT_FOUND);
        return;
    }
    headpost = headpost->next_post;
    bool has_liked = false;
    has_liked = Has_Liked(headpost, current_user->username);
    Like *liker = headpost->liked_user;
    if (code == DISLIKE)
    {
        if (!has_liked)
        {
            Error_Handler(POST_NOT_LIKED);
            return;
        }
        while (Compare_String(liker->username, current_user->username) && (liker->next_like != NULL && Compare_String(liker->next_like->username, current_user->username)))
        {
            liker = liker->next_like;
        }
        if (Compare_String(liker->username, current_user->username))
        {
            headpost->liked_user = liker->next_like;
            free(liker);
        }
        else
        {
            if (liker->next_like == NULL)
            {
                headpost->liked_user = NULL;
                free(liker);
            }
            else
            {
                Like *temp = liker->next_like;
                liker->next_like = liker->next_like->next_like;
                free(temp);
            }
        }
        printf("You disliked this post: \n");
        Show_Post(headpost);
        headpost->like_count -= 1;
    }
    else
    {
        if (has_liked)
        {
            Error_Handler(POST_ALREADY_LIKED);
            return;
        }
        Like *like = (Like *)malloc(sizeof(Like));
        if (like == NULL)
        {
            Error_Handler(UNKNOWN_ERROR);
            return;
        }
        like->username = current_user->username;
        like->next_like = NULL;
        if (liker == NULL)
        {
            headpost->liked_user = like;
        }
        else
        {
            while (liker->next_like != NULL)
            {
                liker = liker->next_like;
            }
            liker->next_like = like;
        }
        printf("You liked this post: \n");
        Show_Post(headpost);
        headpost->like_count += 1;
    }
}
void New_Comment(Post *headpost, User *current_user, User *headuser, char *username, char *text, int post_id)
{
    system("cls");
    if (username == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        free(text);
        return;
    }
    if (text == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        free(username);
        return;
    }
    if (current_user == NULL)
    {
        Error_Handler(NOT_LOGGED_IN);
        free(text);
        free(username);
        return;
    }
    User *receiver = Find_User(headuser, username);
    if (receiver == NULL)
    {
        Error_Handler(USER_NOT_FOUND);
        free(username);
        free(text);
        return;
    }
    headpost = Find_Post(headpost, username, post_id);
    if (headpost == NULL)
    {
        Error_Handler(POST_NOT_FOUND);
        free(username);
        free(text);
        return;
    }
    headpost = headpost->next_post;
    Comment *comment = (Comment *)malloc(sizeof(Comment));
    if (comment == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        free(text);
        free(username);
        return;
    }
    comment->text = text;
    comment->username = current_user->username;
    comment->next_comment = NULL;
    Comment *last_comment = headpost->comment;
    if (last_comment == NULL)
    {
        headpost->comment = comment;
    }
    else
    {
        while (last_comment->next_comment != NULL)
        {
            last_comment = last_comment->next_comment;
        }
        last_comment->next_comment = comment;
    }
    printf("You have sent a new comment to this post: ");
    Show_Post(headpost);
    printf("\n Comment : %s", comment->text);
}
void Post_Again(User *headuser, Post *headpost, User *current_user, char *username, int post_id)
{
    system("cls");
    if (username == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        return;
    }
    if (current_user == NULL)
    {
        Error_Handler(NOT_LOGGED_IN);
        free(username);
        return;
    }
    User *liked_user = NULL;
    fflush(stdin);
    liked_user = Find_User(headuser, username);
    if (liked_user == NULL)
    {
        Error_Handler(USER_NOT_FOUND);
        free(username);
        return;
    }
    headpost = Find_Post(headpost, username, post_id);
    if (headpost == NULL)
    {
        Error_Handler(POST_NOT_FOUND);
        free(username);
        return;
    }
    headpost = headpost->next_post;
    Post *new_post = (Post *)malloc(sizeof(Post));
    if (new_post == NULL)
    {
        Error_Handler(UNKNOWN_ERROR);
        free(username);
        return;
    }
    int id = 2;
    new_post->username = current_user->username;
    new_post->like_count = 0;
    new_post->next_post = NULL;
    new_post->post_text = headpost->post_text;
    Comment *copyright = (Comment *)malloc(sizeof(Comment));
    copyright->next_comment = NULL;
    copyright->username = headpost->username;
    copyright->text = "--| Posted first by this user |--";
    new_post->comment = copyright;
    new_post->liked_user = NULL;
    while (headpost->next_post != NULL)
    {
        headpost = headpost->next_post;
        id++;
    }
    new_post->post_id = id;
    headpost->next_post = new_post;
    printf("You have reposted this post :");
    Show_Post(headpost);
}
void Show_Info(User *current_user, Post *headpost)
{
    system("cls");
    if (current_user == NULL)
    {
        Error_Handler(NOT_LOGGED_IN);
        return;
    }
    printf("Username :     %s\n", current_user->username);
    printf("User ID :      %d\n", current_user->user_id);
    printf("Posts you have sent: \n");
    while (headpost != NULL)
    {
        if (Compare_String(headpost->username,current_user->username))
        {
            Show_Post(headpost);
            printf(".......................\n");
        }
        headpost = headpost->next_post;
    }
}
void Show_User_Info(User* headuser,Post* headpost,char* username){
    system("cls");
    headuser = Find_User(headuser,username);
    if(headuser == NULL){
        Error_Handler(USER_NOT_FOUND);
        return;
    }
    printf("Username :     %s\n", headuser->username);
    printf("User ID :      %d\n", headuser->user_id);
    printf("Posts sent by user: \n");
    while (headpost != NULL)
    {
        if (Compare_String(headpost->username,headuser->username))
        {
            Show_Post(headpost);
            printf(".......................\n");
        }
        headpost = headpost->next_post;
    }
}