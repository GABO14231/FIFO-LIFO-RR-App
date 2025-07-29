#pragma once // Means the file will be compiled once.

//========================
//====== Libraries =======
//========================
#include <iostream>

//=========================
//====== Namespaces =======
//=========================
using namespace std;

//===========================
//====== Header Files =======
//===========================
#include "Main.h"

//========================
//====== Functions =======
//========================
bool checkForZero()
{
    for (int i = 0; i < arr.size(); i++)
        if (arr[i].tf == 0) {return true; break;}
    return false;
}

void findRunningTime()
{
    for (int i = 0; i < arr.size(); i++) arr[i].T = arr[i].tf - arr[i].ti;
}

void findWaitingTime()
{
    for (int i = 0; i < arr.size(); i++) arr[i].E = arr[i].T - arr[i].t;
}

void findTimeIndex()
{
    for (int i = 0; i < arr.size(); i++) arr[i].I = ((float)arr[i].t / arr[i].T);
}

void calculateAverages()
{
    for (int i = 0; i < arr.size(); i++)
    {
        t_avg += arr[i].T;
        e_avg += arr[i].E;
        i_avg += arr[i].I;
    }

    t_avg = (float)t_avg / arr.size();
    e_avg = (float)e_avg / arr.size();
    i_avg = i_avg / arr.size();
}