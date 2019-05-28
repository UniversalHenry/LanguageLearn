// Computing Introduction Course
// Chapter 9
// Exercise 2
// Header seq.h

#ifndef SEQ
#define SEQ
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Label
{
    char c[100];
    int n = 0;
    int len = 0;
} label;

void setLabel(const char *c)
{
    int i;
    for (i = 0; c[i] != '\0'; i++)
        label.c[i] = c[i];
    label.c[i + 1] = '\0';
    label.len = i;
}

void setInitNumber(int n = 0)
{
    if (label.len == 0)
        setLabel("label ");
    label.n = n;
}

char *GetNextLabel()
{
    if (label.len == 0)
        setInitNumber();
    itoa(label.n, &label.c[label.len], 10);
    label.n++;
    return label.c;
}

#endif