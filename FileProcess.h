#ifndef FILEPROCESSOR_H_INCLUDED
#define FILEPROCESSOR_H_INCLUDED

#include "FileProcess.c"
char *Get_String_From_File(FILE *input);
void Fetch_From_File(User *headuser, Post *headpost);
void Save_To_File(User *headuser, Post *headpost);

#endif