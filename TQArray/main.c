//
//  main.c
//  TQArray
//
//  Created by ztq on 2017/11/25.
//  Copyright © 2017年 ztq. All rights reserved.
//

#include "TQArray.h"

void myDestroyInt(int a)
{
    a = -1;
}

void myPrintInt(int a)
{
    printf("printf data : %d \n",a);
}

void myPrintChar(char a)
{
    printf("printf data : %c \n",a);
}

void myPrintString(char a[])
{
    printf("printf data : %s \n",a);
}

void intDataTest()
{
    printf("\n========= int ========\n\n");
    
    int myIntData;
    TQArray intArray = TQArrayCreate(10);
    
    for (int i = 0; i < 20; i++) {
        
        if (TQArrayInsertAtIndex(intArray, i, i)) {
            TQArrayGetByIndex(intArray, i, &myIntData);
            printf("insert success --> index : %d, data : %d\n",i, myIntData);
        } else {
            printf("insert failure --> index : %d\n",i);
        }
    }
    
    TQArrayAppend(intArray, 21);
    printf("TQArrayLength : %d\n",TQArrayLength(intArray));
    TQArrayDelete(intArray, 19, myDestroyInt);
    printf("TQArrayLength : %d\n",TQArrayLength(intArray));
    printf("\n");
    
    TQArrayPrintf(intArray, myPrintInt);
}

void charDataTest()
{
    printf("\n========= char ========\n\n");
    
    char myCharData;
    char charData = 'a';
    TQArray charArray = TQArrayCreate(10);
    
    for (int i = 0; i < 20; i++) {
        
        if (TQArrayInsertAtIndex(charArray, i, charData++)) {
            TQArrayGetByIndex(charArray, i, &myCharData);
            printf("insert success --> index : %d, data : %c\n",i, myCharData);
        } else {
            printf("insert failure --> index : %d\n",i);
        }
    }
    
    printf("\n");

    TQArrayPrintf(charArray, myPrintChar);
    
}

void stringDataTest()
{
    printf("\n========= string ========\n\n");
    
    char *stringData = "abcdefg";
    TQArray stringArray = TQArrayCreate(10);
    
    char *myStringData;
    for (int i = 0; i < 20; i++) {
        
        if (TQArrayInsertAtIndex(stringArray, i, stringData)) {
            TQArrayGetByIndex(stringArray, i, &myStringData);
            printf("insert success --> index : %d, data : %s\n",i, myStringData);
        } else {
            printf("insert failure --> index : %d\n",i);
        }
    }
    
    printf("\n");
    
    TQArrayPrintf(stringArray, myPrintString);
}

int main(int argc, const char * argv[]) {
   
    intDataTest();
//    charDataTest();
//    stringDataTest();
    
    return 0;
}

