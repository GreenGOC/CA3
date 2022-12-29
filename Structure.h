#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

typedef struct like
{
    char *username;
    struct like *next_like;
} Like;
typedef struct comment
{
    char *text;
    char *username;
    struct comment *next_comment;
} Comment;
typedef struct post
{
    char *username;
    int post_id;
    int like_count;
    char *post_text;
    Comment *comment;
    Like *liked_user;
    struct post *next_post;
} Post;
typedef struct user
{
    char *username;
    char *password;
    int user_id;
    struct user *next_user;
} User;

#endif