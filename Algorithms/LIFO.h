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
void findFinalTimeLIFO()
{
    do
    {
        clockCount();
        bool process_ran_in_this_pass = false;
        for (int i = arr.size() - 1; i >= 0;)
        {
            if (clockCheck >= arr[i].ti)
            {
                if (arr[i].tf == 0)
                {
                    arr[i].tf = clockCheck + arr[i].t;
                    clockCheck = arr[i].tf;
                    clockCount();
                    process_ran_in_this_pass = true;
                    i = arr.size() - 1;
                }
                else i--;
            }
            else i--;
        }
        if (!process_ran_in_this_pass && checkForZero()) clockCheck++;

    } while (checkForZero());

    clockCheck = 0;
}

void LIFO()
{
    findFinalTimeLIFO();
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

    effective[1] = (i_avg * 100);
    clock_values.clear();
}