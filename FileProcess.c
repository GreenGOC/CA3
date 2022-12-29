#include <stdio.h>
#include <stdbool.h>

#include "Helper.h"
#include "Structure.h"

char *Get_String_From_File(FILE *input)
{
    char *string = (char *)malloc(sizeof(char));
    *(string) = ' ';
    int length = 0;
    char temp[1] = {' '};
    while (true)
    {
        fread(temp, sizeof(char), 1, input);
        length++;
        string = (char *)realloc(string, sizeof(char) * length);
        string[length - 1] = '\0';
        switch (temp[0])
        {
        case '\n':
        case EOF:
            return string;
        default:
            string[length - 1] = temp[0];
            break;
        }
    }
}
void Fetch_From_File(User *headuser, Post *headpost)
{
    FILE *users = fopen("users.txt", "r");
    if (users == NULL)
    {
        printf("\nUnable to fetch data!\n");
        return;
    }
    while (1)
    {
        char *username = Get_String_From_File(users);
        if (Compare_String(username, "|"))
        {
            free(username);
            break;
        }
        User *user = (User *)malloc(sizeof(User));
        user->username = username;
        user->password = Get_String_From_File(users);
        user->user_id = String_To_Int(Get_String_From_File(users));
        user->next_user = NULL;
        headuser->next_user = user;
        headuser = headuser->next_user;
    }
    fclose(users);
    FILE *posts = fopen("posts.txt", "r");
    if (posts == NULL)
    {
        printf("\nUnable to fetch data!\n");
        return;
    }
    while (1)
    {
        char *username = Get_String_From_File(posts);
        if (Compare_String(username, "|"))
        {
            free(username);
            break;
        }
        Post *post = (Post *)malloc(sizeof(Post));
        post->username = username;
        post->post_id = String_To_Int(Get_String_From_File(posts));
        post->post_text = Get_String_From_File(posts);
        post->next_post = NULL;
        post->liked_user = NULL;
        post->comment = NULL;
        int like_count = 0;
        while (1)
        {
            char *liked_user = Get_String_From_File(posts);
            if (Compare_String(liked_user, "|"))
            {
                free(liked_user);
                break;
            }
            Like *like = (Like *)malloc(sizeof(Like));
            like->username = liked_user;
            like->next_like = NULL;
            like_count++;
            if (post->liked_user == NULL)
            {
                post->liked_user = like;
            }
            else
            {
                Like *likes = post->liked_user;
                while (likes->next_like != NULL)
                {
                    likes = likes->next_like;
                }
                likes->next_like = like;
            }
        }
        post->like_count = like_count;
        while (1)
        {
            char *comment_user = Get_String_From_File(posts);
            if (Compare_String(comment_user, "|"))
            {
                free(comment_user);
                break;
            }
            Comment *comment = (Comment *)malloc(sizeof(Comment));
            comment->username = comment_user;
            comment->text = Get_String_From_File(posts);
            comment->next_comment = NULL;
            if (post->comment == NULL)
            {
                post->comment = comment;
            }
            else
            {
                Comment *comments = post->comment;
                while (comments->next_comment != NULL)
                {
                    comments = comments->next_comment;
                }
                comments->next_comment = comment;
            }
        }
        headpost->next_post = post;
        headpost = headpost->next_post;
    }
    fclose(posts);
}
void Save_To_File(User *headuser, Post *headpost)
{
    FILE *users = fopen("users.txt", "w");
    if (users == NULL)
    {
        printf("Unable to save to file! All posts and users are gone :(");
        return;
    }
    headuser = headuser->next_user;
    while (headuser != NULL)
    {
        fprintf(users, "%s\n%s\n%d\n", headuser->username, headuser->password, headuser->user_id);
        headuser = headuser->next_user;
    }
    fputs("|\n", users);
    fclose(users);
    FILE *posts = fopen("posts.txt", "w");
    if (posts == NULL)
    {
        printf("Unable to save to file! All posts and users are gone :(");
        return;
    }
    headpost = headpost->next_post;
    while (headpost != NULL)
    {
        fprintf(posts, "%s\n%d\n%s\n", headpost->username, headpost->post_id, headpost->post_text);
        Like *likes = headpost->liked_user;
        while (likes != NULL)
        {
            fprintf(posts, "%s\n", likes->username);
            likes = likes->next_like;
        }
        fprintf(posts, "|\n");
        Comment *comments = headpost->comment;
        while (comments != NULL)
        {
            fprintf(posts, "%s\n%s\n", comments->username, comments->text);
            comments = comments->next_comment;
        }
        headpost = headpost->next_post;
        fprintf(posts, "|\n");
    }
    fprintf(posts, "|\n");
}