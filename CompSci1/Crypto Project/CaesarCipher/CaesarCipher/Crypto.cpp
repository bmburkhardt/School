

#include "Crypto.h"
#include <iostream>
#include <cstring>

using namespace std;

int size(char arry[])
{
    int count = 0;
    while (arry[count] != '\0')
    {
        count++;
    }
    return count;
}


//Caesar encryption function
char * encryptCaesar(char message[], int shift)
{
    //New char pointer array with size of array being accepted in function that will be returned
    char * rv = new char[size(message)];
    
    //For loop that runs through the message that is being encrypted
    for(int i = 0; i < size(message); ++i)
    {
        if (message[i] == 32) //Ensures that "spaces" in the char array remain spaces
        {
            rv[i] = 32;
        }
        else
        {
            int count = 0;
            //This while loop encrypts the message as long as the shift doesn't cause the value to go over 90("Z") on the ASCII
            //table.
            while((count <= shift) && ((count + message[i]) <= 90))
            {
                rv[i] = (message[i] + count);
                count ++;
            }
            //If the shift causes value to go over 90 on ASCII table, this if statement starts the value back at 65("A")
            if(((count + message[i]) >90) && (count <= shift))
            {
                rv[i] = (65+((shift-count)));
            }
        }
    }
    //Returns the new encrypted pointer array
    return rv;
}


//Caesar decryption function
char * decryptCaesar(char message[], int shift)
{
    //New char pointer array with size of array being accepted in function that will be returned
    char * rv = new char[size(message)];
    
    //For loop that runs through the message that is being decrypted
    for(int i = 0; i < size(message); ++i)
    {
        if (message[i] == 32) //Ensures that "spaces" in the char array remain spaces
        {
            rv[i] = 32;
        }
        else
        {
            int count = 0;
            //This while loop decrypts the message as long as the shift doesn't cause the value to go over 65("A") on the ASCII
            //table.
            while((count <= shift) && ((message[i]-count) > 65))
            {
                rv[i] = (message[i] - count);
                count ++;
            }
            //If the shift causes value to go below 65 on ASCII table, this if statement starts the value back at 90("Z")
            if((message[i]-count) <= 65)
            {
                rv[i] = (90-((shift-count)-1));
            }
            
        }
    }
    //Returns the new encrypted pointer array
    return rv;
}

//********************************************************************************
//
//
//
//FOLLOWING CODE ARE BLANK FUNCTIONS AND ADAM'S CODE SO CRYPTOTEST.CPP WOULD RUN
//
//
//********************************************************************************


/*
char * decryptSub(char message[], char key[]){
    char * ptr = new char[255];
    return ptr;
}
char * encryptSub(char message[], char key[]){
    char * ptr = new char[255];
    return ptr;
}


int getSize(char arry[]){
    int size = 0;
    for (int i = 0; i < 255; ++i){
        if (arry[i] == 0){
            return size;
        }else {
            size++;
        }
    }
    return size;
}

void fillArrayWithSpace(char arry[], const int SIZE){
    for (int i = 0; i < SIZE; ++i){
        arry[i] = ' ';
    }
}

int numOfSeq(char message[], const int INDX){
    int num = 0;
    for (int i = 0; i < INDX; ++i){
        if (message[i] == 32 && message[i + 1] == 32 && message[i + 2] == 32 && message[i + 3] == 32 && message[i + 4]){
            num++;
            i += 3;
        }else if (message[i] == 32){
            num++;
        }
    }
    return num +1;
}

char * decryptMorse(char message[]){
    const int SIZE = getSize(message);
    char * transPtr = new char[SIZE];
    int indx = 0;
    for (int i = 0; i <= numOfSeq(message, SIZE); ++i){
        if (message[indx] == 32 && message[indx + 1] == 32 && message[indx + 2] == 32 && message[indx + 2] == 32){
            transPtr[i] = ' ';
            indx += 4;
        }else if (message[indx] == 45 && message[indx + 1] == 45 && message[indx + 2] == 46 && message[indx + 3] == 46){
            transPtr[i] = 'Z';
            indx += 5;
        }else if (message[indx] == 45 && message[indx + 1] == 46 && message[indx + 2] == 45 && message[indx + 3] == 45){
            transPtr[i] = 'Y';
            indx += 5;
        }else if (message[indx] == 45 && message[indx + 1] == 46 && message[indx + 2] == 46 && message[indx + 3] == 45){
            transPtr[i] = 'X';
            indx += 5;
        }else if (message[indx] == 46 && message[indx + 1] == 46 && message[indx + 2] == 46 && message[indx + 3] == 45){
            transPtr[i] = 'V';
            indx += 5;
        }else if (message[indx] == 45 && message[indx + 1] == 45 && message[indx + 2] == 46 && message[indx + 3] == 45){
            transPtr[i] = 'Q';
            indx += 5;
        }else if (message[indx] == 46 && message[indx + 1] == 45 && message[indx + 2] == 45 && message[indx + 3] == 46){
            transPtr[i] = 'P';
            indx += 5;
        }else if (message[indx] == 46 && message[indx + 1] == 45 && message[indx + 2] == 46 && message[indx + 3] == 46){
            transPtr[i] = 'L';
            indx += 5;
        }else if (message[indx] == 46 && message[indx + 1] == 45 && message[indx + 2] == 45 && message[indx + 3] == 45){
            transPtr[i] = 'J';
            indx += 5;
        }else if (message[indx] == 46 && message[indx + 1] == 46 && message[indx + 2] == 46 && message[indx + 3] == 46){
            transPtr[i] = 'H';
            indx += 5;
        }else if (message[indx] == 46 && message[indx + 1] == 46 && message[indx + 2] == 45 && message[indx + 3] == 46){
            transPtr[i] = 'F';
            indx += 5;
        }else if (message[indx] == 45 && message[indx + 1] == 46 && message[indx + 2] == 45 && message[indx + 3] == 46){
            transPtr[i] = 'C';
            indx += 5;
        }else if (message[indx] == 45 && message[indx + 1] == 46 && message[indx + 2] == 46 && message[indx + 3] == 46){
            transPtr[i] = 'B';
            indx += 5;
        }else if (message[indx] == 46 && message[indx + 1] == 45 && message[indx + 2] == 45){
            transPtr[i] = 'W';
            indx += 4;
        }else if (message[indx] == 46 && message[indx + 1] == 46 && message[indx + 2] == 45){
            transPtr[i] = 'U';
            indx += 4;
        }else if (message[indx] == 46 && message[indx + 1] == 46 && message[indx + 2] == 46){
            transPtr[i] = 'S';
            indx += 4;
        }else if (message[indx] == 46 && message[indx + 1] == 45 && message[indx + 2] == 46){
            transPtr[i] = 'R';
            indx += 4;
        }else if (message[indx] == 45 && message[indx + 1] == 46 && message[indx + 2] == 45){
            transPtr[i] = 'K';
            indx += 4;
        }else if (message[indx] == 45 && message[indx + 1] == 45 && message[indx + 2] == 46){
            transPtr[i] = 'G';
            indx += 4;
        }else if (message[indx] == 45 && message[indx + 1] == 46 && message[indx + 2] == 46){
            transPtr[i] = 'D';
            indx += 4;
        }else if (message[indx] == 45 && message[indx + 1] == 45 && message[indx + 2] == 45){
            transPtr[i] = 'O';
            indx += 4;
        }else if (message[indx] == 45 && message[indx + 1] == 46){
            transPtr[i] = 'N';
            indx += 3;
        }else if (message[indx] == 46 && message[indx + 1] == 46){
            transPtr[i] = 'I';
            indx += 3;
        }else if (message[indx] == 46 && message[indx + 1] == 45){
            transPtr[i] = 'A';
            indx += 3;
        }else if (message[indx] == 45 && message[indx + 1] == 45){
            transPtr[i] = 'M';
            indx += 3;
        }else if (message[indx] == 45){
            transPtr[i] = 'T';
            indx += 2;
        }else if (message[indx] == 46){
            transPtr[i] = 'E';
            indx += 2;
        }
    }
    transPtr[indx-1] == '\0';
    return transPtr;
}

char * encryptMorse(char message[]){
    const int SIZE = getSize(message);
    char * transPtr = new char[SIZE * 6];
    int indx = 0;
    fillArrayWithSpace(transPtr, SIZE * 6);
    for (int i = 0; i < SIZE; ++i){
        if (message[i] == 65 || message[i] == 97){
            transPtr[i + indx] = '.';
            transPtr[i + indx + 1] = '-';
            indx += 2;
        }else if (message[i] == 66 || message[i] == 98){
            transPtr[i + indx] = '-';
            transPtr[i + indx + 1] = '.';
            transPtr[i + indx + 2] = '.';
            transPtr[i + indx + 3] = '.';
            indx += 4;
        }else if (message[i] == 67 || message[i] == 99){
            transPtr[i + indx] = '-';
            transPtr[i + indx + 1] = '.';
            transPtr[i + indx + 2] = '-';
            transPtr[i + indx + 3] = '.';
            indx += 4;
        }else if (message[i] == 68 || message[i] == 100){
            transPtr[i + indx] = '-';
            transPtr[i + indx + 1] = '.';
            transPtr[i + indx + 2] = '.';
            indx += 3;
        }else if (message[i] == 69 || message[i] == 101){
            transPtr[i + indx] = '.';
            indx += 1;
        }else if (message[i] == 70 || message[i] == 102){
            transPtr[i + indx] = '.';
            transPtr[i + indx + 1] = '.';
            transPtr[i + indx + 2] = '-';
            transPtr[i + indx + 3] = '.';
            indx += 4;
        }else if (message[i] == 71 || message[i] == 103){
            transPtr[i + indx] = '-';
            transPtr[i + indx + 1] = '-';
            transPtr[i + indx + 2] = '.';
            indx += 3;
        }else if (message[i] == 72 || message[i] == 104){
            transPtr[i + indx] = '.';
            transPtr[i + indx + 1] = '.';
            transPtr[i + indx + 2] = '.';
            transPtr[i + indx + 3] = '.';
            indx += 4;
        }else if (message[i] == 73 || message[i] == 105){
            transPtr[i + indx] = '.';
            transPtr[i + indx + 1] = '.';
            indx += 2;
        }else if (message[i] == 74 || message[i] == 106){
            transPtr[i + indx] = '.';
            transPtr[i + indx + 1] = '-';
            transPtr[i + indx + 2] = '-';
            transPtr[i + indx + 3] = '-';
            indx += 4;
        }else if (message[i] == 75 || message[i] == 107){
            transPtr[i + indx] = '-';
            transPtr[i + indx + 1] = '.';
            transPtr[i + indx + 2] = '-';
            indx += 3;
        }else if (message[i] == 76 || message[i] == 108){
            transPtr[i + indx] = '.';
            transPtr[i + indx + 1] = '-';
            transPtr[i + indx + 2] = '.';
            transPtr[i + indx + 3] = '.';
            indx += 4;
        }else if (message[i] == 77 || message[i] == 109){
            transPtr[i + indx] = '-';
            transPtr[i + indx + 1] = '-';
            indx += 2;
        }else if (message[i] == 78 || message[i] == 110){
            transPtr[i + indx] = '-';
            transPtr[i + indx + 1] = '.';
            indx += 2;
        }else if (message[i] == 79 || message[i] == 111){
            transPtr[i + indx] = '-';
            transPtr[i + indx + 1] = '-';
            transPtr[i + indx + 2] = '-';
            indx += 3;
        }else if (message[i] == 80 || message[i] == 112){
            transPtr[i + indx] = '.';
            transPtr[i + indx + 1] = '-';
            transPtr[i + indx + 2] = '-';
            transPtr[i + indx + 3] = '.';
            indx += 4;
        }else if (message[i] == 81 || message[i] == 113){
            transPtr[i + indx] = '-';
            transPtr[i + indx + 1] = '-';
            transPtr[i + indx + 2] = '.';
            transPtr[i + indx + 3] = '-';
            indx += 4;
        }else if (message[i] == 82 || message[i] == 114){
            transPtr[i + indx] = '.';
            transPtr[i + indx + 1] = '-';
            transPtr[i + indx + 2] = '.';
            indx += 3;
        }else if (message[i] == 83 || message[i] == 115){
            transPtr[i + indx] = '.';
            transPtr[i + indx + 1] = '.';
            transPtr[i + indx + 2] = '.';
            indx += 3;
        }else if (message[i] == 84 || message[i] == 116){
            transPtr[i + indx] = '-';
            indx += 1;
        }else if (message[i] == 85 || message[i] == 117){
            transPtr[i + indx] = '.';
            transPtr[i + indx + 1] = '.';
            transPtr[i + indx + 2] = '-';
            indx += 3;
        }else if (message[i] == 86 || message[i] == 118){
            transPtr[i + indx] = '.';
            transPtr[i + indx + 1] = '.';
            transPtr[i + indx + 2] = '.';
            transPtr[i + indx + 3] = '-';
            indx += 4;
        }else if (message[i] == 87 || message[i] == 119){
            transPtr[i + indx] = '.';
            transPtr[i + indx + 1] = '-';
            transPtr[i + indx + 2] = '-';
            indx += 3;
        }else if (message[i] == 88 || message[i] == 120){
            transPtr[i + indx] = '-';
            transPtr[i + indx + 1] = '.';
            transPtr[i + indx + 2] = '.';
            transPtr[i + indx + 3] = '-';
            indx += 4;
        }else if (message[i] == 89 || message[i] == 121){
            transPtr[i + indx] = '-';
            transPtr[i + indx + 1] = '.';
            transPtr[i + indx + 2] = '-';
            transPtr[i + indx + 3] = '-';
            indx += 4;
        }else if (message[i] == 90 || message[i] == 122){
            transPtr[i + indx] = '-';
            transPtr[i + indx + 1] = '-';
            transPtr[i + indx + 2] = '.';
            transPtr[i + indx + 3] = '.';
            indx += 4;
        }else if (message[i] == 32){
            transPtr[i + indx] = ' ';
            transPtr[i + indx + 1] = ' ';
            transPtr[i + indx + 2] = ' ';
            indx += 3;
        }
        
    }
    transPtr[SIZE + indx] = '\0';
    return transPtr;
}
*/