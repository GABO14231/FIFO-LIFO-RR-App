#pragma once // Means the file will be compiled once.

//========================
//====== Libraries =======
//========================
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <chrono>
#include <fstream>
#include <sstream>
#include <conio.h>

//=========================
//====== Namespaces =======
//=========================
using namespace std;
using namespace std::chrono;

//===============================
//====== Global Variables =======
//===============================
int clockCheck, quantum, counter;
float t_avg, e_avg, i_avg, effective[3];
string alphabet[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N",
    "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "A1", "B1", "C1", "D1", "E1", "F1",
    "G1", "H1", "I1", "J1", "K1", "L1", "M1", "N1", "O1", "P1", "Q1", "R1", "S1", "T1", "U1", "V1", 
    "W1", "X1", "Y1", "Z1"};

struct Processes
{
    string processes;
    int ti, t, tf, T, E;
    float I;
};

vector<Processes> arr;

vector<int> clock_values;

//========================
//====== Functions =======
//========================
void insertData()
{
    int n, ti, t;
    Processes p;

    cout << "How many processes are you going to run?: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "Process " << (i + 1) << ":" << endl;

        p.processes = alphabet[i];

        cout << "What is the Arrival Time (Ti): ";
        cin >> ti;
        p.ti = ti;

        cout << "What is the Execution Time (t): ";
        cin >> t;
        p.t = t;

        p.tf = 0;
        p.T = 0;
        p.E = 0;
        p.I = 0.00;

        arr.push_back(p);
        cout << ("\033c");
    }
}

void readFile()
{
    int n;
    string numbers;
    Processes p;
    ifstream inputFile("./Times.txt", ios::in);

    if (!inputFile)
    {
        cout << "ERROR: Could not find 'Times.txt'!" << endl;
        return;
    }

    cout << "How many processes are you going to run?: ";
    cin >> n;

    int temp_ti[n], temp_t[n];

    getline(inputFile, numbers);

    if (getline(inputFile, numbers))
    {
        istringstream ti(numbers);
        for (int i = 0; i < n; i++) ti >> temp_ti[i];
    }

    if (getline(inputFile, numbers))
    {
        istringstream t(numbers);
        for (int i = 0; i < n; i++) t >> temp_t[i];
    }

    inputFile.close();

    for (int i = 0; i < n; i++)
    {
        p.processes = alphabet[i];
        p.ti = temp_ti[i];
        p.t = temp_t[i];

        p.tf = 0;
        p.T = 0;
        p.E = 0;
        p.I = 0.00;

        arr.push_back(p);
    }
}

void clearData()
{
    for (int i = 0; i < arr.size(); i++)
    {
        arr[i].tf = 0;
        arr[i].T = 0;
        arr[i].E = 0;
        arr[i].I = 0.00;
    }

    t_avg = 0.00;
    e_avg = 0.00;
    i_avg = 0.00;
}

void clearScreen()
{
    getch();
    cout << endl;
    cout << ("\033c");
}

void clockCount()
{
    if (find(clock_values.begin(), clock_values.end(), clockCheck) == clock_values.end() || clock_values.empty())
        clock_values.push_back(clockCheck);
}