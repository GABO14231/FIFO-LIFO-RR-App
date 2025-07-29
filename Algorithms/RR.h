#pragma once // Means the file will be compiled once.

//========================
//====== Libraries =======
//========================
#include <iostream>
#include <iomanip>

//=========================
//====== Namespaces =======
//=========================
using namespace std;

//===========================
//====== Header Files =======
//===========================
#include "../Main.h"
#include "../Calculations.h"

//========================
//====== Functions =======
//========================
bool allProcessesFinished()
{
    for (const auto &p : arr) if (p.tf == 0) return false;
    return true;
}

void findFinalTimeRR()
{
    queue<int> readyQueue;
    vector<int> remainingTime(arr.size());
    clockCheck = 0;

    for (int i = 0; i < arr.size(); ++i)
    {
        remainingTime[i] = arr[i].t;
        arr[i].tf = 0;
    }

    while (!allProcessesFinished())
    {
        bool processExecutedThisCycle = false;
        for (int i = 0; i < arr.size(); ++i)
        {
            if (arr[i].ti <= clockCheck && arr[i].tf == 0)
            {
                bool inQueue = false;
                std::queue<int> tempQueue = readyQueue;
                while (!tempQueue.empty())
                {
                    if (tempQueue.front() == i)
                    {
                        inQueue = true;
                        break;
                    }
                    tempQueue.pop();
                }
                if (!inQueue) readyQueue.push(i);
            }
        }

        if (!readyQueue.empty())
        {
            int currentProcessIndex = readyQueue.front();
            readyQueue.pop();
            if (arr[currentProcessIndex].tf == 0)
            {
                int timeSlice = std::min(remainingTime[currentProcessIndex], quantum);
                remainingTime[currentProcessIndex] -= timeSlice;
                clockCheck += timeSlice;
                clockCount();
                processExecutedThisCycle = true;

                if (remainingTime[currentProcessIndex] == 0) arr[currentProcessIndex].tf = clockCheck;
                else readyQueue.push(currentProcessIndex);
            }
        }

        if (!processExecutedThisCycle && readyQueue.empty())
        {
            int nextArrivalTime = -1;
            for (int i = 0; i < arr.size(); ++i)
                if (arr[i].tf == 0)
                    if (nextArrivalTime == -1 || arr[i].ti < nextArrivalTime) nextArrivalTime = arr[i].ti;

            if (nextArrivalTime != -1 && nextArrivalTime > clockCheck)
            {
                clockCheck = nextArrivalTime;
                clockCount();
            }
            else if (nextArrivalTime == -1 && allProcessesFinished()) break;
            else
            {
                clockCheck++;
                clockCount();
            }
        }
    }
}

void RR()
{
    findFinalTimeRR();
    findRunningTime();
    findWaitingTime();
    findTimeIndex();
    calculateAverages();

    cout << "Processes\t" << "Ti\t" << "t\t" << "Tf\t" << "T\t" << "E\t" << "I\n";

    for (int i = 0; i < arr.size(); i++)
        cout << arr[i].processes << "\t\t" << arr[i].ti << "\t" << arr[i].t << "\t" << arr[i].tf << "\t"
            << arr[i].T << "\t" << arr[i].E << "\t" << setprecision(4) << arr[i].I << endl;

    cout << "Averages" << "\t\t\t\t" << setprecision(4) << t_avg << "\t" << e_avg << "\t" << i_avg << endl << endl;
    cout << "Effectiveness: " << (i_avg * 100) << '%' << endl << endl;

    cout << "Clock: ";

    for (int i = 0; i < (clock_values.size() - 1); i++) cout << clock_values[i] << ", ";

    cout << clock_values[clock_values.size() - 1] << endl;

    effective[2] = (i_avg * 100);
    clock_values.clear();
}