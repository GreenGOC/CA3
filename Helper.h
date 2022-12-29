#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED


#include "Helper.c"

bool Compare_String(char *string1, char *string2);
Post *Find_Post(Post *headpost, char *username, int post_id);
void Error_Handler(int error);
void Get_String(char **text, short is_text);
int String_To_Int(char *input);
void press_enter();
User *Find_User(User *headuser, char *username);

#endif