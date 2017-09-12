#ifndef Crypto_h
#define Crypto_h

#include <iostream>
#include <cstring>
using namespace std;


char * encryptCaesar(char message[], int shift);
int size(char arry[]);
char * decryptCaesar(char message[], int shift);

/*
char * decryptSub(char message[], char key[]);
char * encryptSub(char message[], char key[]);
int getSize(char arry[]);
void fillArrayWithSpace(char arry[], const int SIZE);
int numOfSeq(char message[], const int INDX);
char * decryptMorse(char message[]);
char * encryptMorse(char message[]);
*/





#endif /* Crypto_h */
