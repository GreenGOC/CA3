#ifndef LOGINSIGNUP_H_INCLUDED
#define LOGINSIGNUP_H_INCLUDED

#include "LoginSignup.c"

bool Login_Conflict();
void Signup(User *headuser, User **current_user, char *username, char *password);
void Login(User *headuser, User **current_user, char *username, char *password);
void Logout(User **current_user);
void Remove_Account(User *headuser, User **current_user);

#endif