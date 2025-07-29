/*****************************************************/
/* This program will try to schedule a series of     */
/* user provided processes with the FIFO, LIFO and   */
/* RR algorithms, and see which one is the most      */
/* efficient and which one is the fastest as well.   */
/* Code by: Gabriel Morazan.                         */
/* Date: June 29th, 2024 (29/06/2024)                */
/*****************************************************/

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
#include "Main.h"
#include "Algorithms/RunAlgorithms.h"

int main()
{
    int choice;
    microseconds fifo_time, lifo_time, rr_time;

    do
    {
        cout << "Do you want to insert the times manually, or read them from a file?" << endl
            << "(NOTE: The file must be named 'Times.txt')" << endl << endl
            << "(0 = Insert manually, 1 = Read from file): ";
        cin >> choice;

        if ((choice != 0) && (choice != 1)) cout << "ERROR: Select a valid option!";
    }
    while ((choice != 0) && (choice != 1));
    
    switch (choice)
    {
        case 0:
            insertData();
            break;
        case 1:
            readFile();
            break;
    }

    if (!arr.empty())
    {
        cout << endl << "Running FIFO algorithm first. Press Enter to continue.";
        clearScreen();

        runAlgorithms(0, fifo_time);
        clearData();

        cout << endl << "Running LIFO algorithm next. Press Enter to continue.";
        clearScreen();

        runAlgorithms(1, lifo_time);
        clearData();

        cout << endl << "Running RR algorithm next. Press Enter to continue.";
        clearScreen();

        cout << "What is the value of the quantum to use?: ";
        cin >> quantum;
        cout << ("\033c");

        runAlgorithms(2, rr_time);
        clearData();

        cout << endl << "RR algorithm finished. Press Enter to continue.";
        clearScreen();

        cout << "FIFO Effectiveness: " << effective[0] << '%' << endl << "LIFO Effectiveness: " << effective[1]
            << '%' << endl << "RR Effectiveness: " << effective[2] << '%' << endl << endl;

        if ((effective[0] > effective[1]) && (effective[0] > effective[2]))
            cout << "FIFO is the most effective algorithm." << endl;
        else if ((effective[1] > effective[0]) && (effective[1] > effective[2]))
            cout << "LIFO is the most effective algorithm." << endl;
        else if ((effective[2] > effective[0]) && (effective[2] > effective[1]))
            cout << "RR is the most effective algorithm." << endl;

        cout << endl << "FIFO Duration: " << fifo_time.count() << " μs" << endl << "LIFO Duration: "
            << lifo_time.count() << " μs" << endl << "RR Duration: " << rr_time.count() << " μs" << endl << endl;

        if ((fifo_time.count() < lifo_time.count()) && (fifo_time.count() < rr_time.count()))
            cout << "FIFO is the fastest algorithm." << endl;
        else if ((lifo_time.count() < fifo_time.count()) && (lifo_time.count() < rr_time.count()))
            cout << "LIFO is the fastest algorithm." << endl;
        else if ((rr_time.count() < fifo_time.count()) && (rr_time.count() < lifo_time.count()))
            cout << "RR is the fastest algorithm." << endl;

        cout << endl;
    }
    else cout << "ERROR: No activities are available to schedule!" << endl << "Exiting program...";

    return 0;
}