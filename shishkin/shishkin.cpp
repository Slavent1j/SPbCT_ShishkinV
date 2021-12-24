#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "MathFuncsDll.lib")
#pragma comment(lib, "netapi32.lib")

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <Windows.h>
#include <Lm.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <csignal>
#include <conio.h>
#include "MathFuncsDll.h" //Разработка приложения, использующего DLL

using namespace std;

void push(char* &stack, int size, char a) // описание класса вектор ввида массива 
{
    char* new_stack = new char[size + 1];
    for (int i = 0; i < size; ++i)
        new_stack[i] = stack[i];
    delete[] stack;
    stack = new_stack;
    stack[size] = a;
};

int comp1(const void* a, const void* b)
{
    return (*(char*)a - *(char*)b);
}

int comp2(const void* a, const void* b)
{
    return (*(char*)b - *(char*)a);
}

int main()
{
    const int size = 10;

    string str;
    char* stack = new char[3];
    int i = 0, k = 0;
    char output[size][size];

    std::ofstream erase("log.txt", std::ios::out);
    erase.close();
    std::ofstream out("log.txt", std::ios::app);
    ifstream file("text.txt");

    if (file.is_open() != true)
    {
        return 0;
    }

    while (getline(file, str)) {
        const char* cstr = str.c_str();
        push(stack, i, str[0]);
        i++;
        i = MathFuncs::MyMathFuncs::clamp(i, 0, 100);// из библиотеки метод clamp 
    }
    str = "";
    k = i;
    i = 0;

    for (int i = 0; i < k; ++i)
        cout << stack[i] << " ";
    cout << endl;

    qsort(stack, k, sizeof(char), comp1);

    for (int i = 0; i < k; ++i)
        cout << stack[i] << " ";
    cout << endl;

    int m = 0;
    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            output[j][i] = stack[i + m];
        }
        m += size;
    }
    cout << endl;
    qsort(output, k, sizeof(char), comp2);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
        {
            std::cout << " " << output[i][j];
            if (out.is_open())
                out << output[i][j];
        }
        std::cout << std::endl;
        out << endl;
    }



    out.close();
    file.close();

    delete[] stack;
}
