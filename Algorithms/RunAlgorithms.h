#pragma once // Means the file will be compiled once.

//========================
//====== Libraries =======
//========================
#include <iostream>
#include <chrono>

//=========================
//====== Namespaces =======
//=========================
using namespace std;
using namespace std::chrono;

//===========================
//====== Header Files =======
//===========================
#include "FIFO.h"
#include "LIFO.h"
#include "RR.h"

//========================
//====== Functions =======
//========================
void runAlgorithms(int num, microseconds &time)
{
    high_resolution_clock::time_point start, end;

    switch (num)
    {
        case 0:
            start = high_resolution_clock::now();
            FIFO();
            end = high_resolution_clock::now();
            time = duration_cast<microseconds>(end - start);
            break;
        case 1:
            start = high_resolution_clock::now();
            LIFO();
            end = high_resolution_clock::now();
            time = duration_cast<microseconds>(end - start);
            break;
        case 2:
            start = high_resolution_clock::now();
            RR();
            end = high_resolution_clock::now();
            time = duration_cast<microseconds>(end - start);
            break;
    }
}