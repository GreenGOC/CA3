#ifndef POST_H_INCLUDED
#define POST_H_INCLUDED

#include "Post.c"

void Show_Post(Post *headpost);
void Show_Full_Post(Post *headpost, char *username, int post_id);
void New_Post(Post *headpost, User *current_user, char *text);
void Delete_Post(User *current_user, Post *headpost, int post_id);
bool Has_Liked(Post *post, char *username);
void Like_Dislike_Post(User *headuser, Post *headpost, User *current_user, char *username, int post_id, short code);
void New_Comment(Post *headpost, User *current_user, User *headuser, char *username, char *text, int post_id);
void Post_Again(User *headuser, Post *headpost, User *current_user, char *username, int post_id);
void Show_Info(User *current_user, Post *headpost);
void Show_User_Info(User* headuser,Post* headpost,char* username);

#endif