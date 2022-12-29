#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include "Screen.c"

void Refresh_Feed(Post *headpost);
int Check_Command(char *command);
void Show_Commands(User *user);

#endif