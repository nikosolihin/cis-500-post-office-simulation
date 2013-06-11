// Project: Post Office Simulation
// Author:  Niko Solihin

#include <iostream>
#include <iomanip>          // for setting precision of average wait time
#include <ctime>            // for seeding rand()
#include <string>
#include "IntQueue.h"
#include "IntQueue.cpp"

using namespace std;

void runSimulation ( int lower, int upper );

int main () {

    // run the simulation for 3 times
    runSimulation( 1, 3 );
    cout << endl;
    runSimulation( 1, 4 );
    cout << endl;
    runSimulation( 1, 5 );

}

void runSimulation( int lower, int upper )
{
    // declare needed variables
    const int   WORK_TIME = 480;        // 8 hours (480 mins)
    int         totalCustomers = 0,
                currentMin = 1,         // first min of business hours
                arrivalTime = 1,        // assumes an early-bird customer
                lastArrivalTime,
                servingTime = 1,
                lowerServeTime = lower, // int lower
                upperServeTime = upper, // int upper
                waitTime = 0,
                totalWaitTime = 0;
    double      avgWaitTime = 0.00;
    bool        isAvailable = true;     // clerk availability

    stringstream waitTimes;

    // seed the random number generator
    srand((unsigned)time(0));

    // initialize the queue
    IntQueue postOffice;

    // initial message
    cout << "----------------------------------------------------------------" << endl;
    cout << "\nSimulating post-office activities and generating statistics for "
         << lower << "-" << upper << " mins of serving time..." << endl;

    // run simulation until closing time
    while ( currentMin < WORK_TIME ) {

        // enqueue a customer after certain minutes have passed
        if ( currentMin % arrivalTime == 0 ) {
            postOffice.enqueue(arrivalTime);

            // generate random arrival time for next customer
            arrivalTime += (rand() % 5) + 1;
        }

        // dequeue a customer if clerk is available
        if ( isAvailable && !postOffice.isEmpty() ) {
            postOffice.dequeue(lastArrivalTime);

            // count total number of served customers
            totalCustomers ++;

            // generate random serving time for clerk
            servingTime = (rand() % upperServeTime) + lowerServeTime;

            // serve the customer
            isAvailable = false;
        }

        // if clerk is busy, count waiting time
        if ( !isAvailable ) {
            waitTime ++;
            servingTime --;
        }

        // get clerk ready to serve the next customer
        if ( servingTime == 0 ) {
            isAvailable = true;
            totalWaitTime += waitTime;
            waitTimes << waitTime << ", ";

            // reset wait time since the clerk is now available
            waitTime = 0;
        }

        // increase digital clock
        currentMin ++;
    }

    avgWaitTime = static_cast<double>(totalWaitTime) / static_cast<double>(totalCustomers);

    cout << "\nTotal # of customers in 8 hours: " << totalCustomers << endl;
    cout << "Total waiting time: " << totalWaitTime << " minutes" << endl;
    cout << "Max waiting time in minutes per customer (in order of arrival): " << waitTimes.str() << endl;
    cout << "Average waiting time of customers: " << fixed << setprecision(2) << avgWaitTime << " minutes" << endl;
    cout << "\n----------------------------------------------------------------" << endl;
}