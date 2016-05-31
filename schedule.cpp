/*****************************************
 ** File:    sched.cpp
 ** Project: CMSC 202 Project 1, Spring 2016
 ** Author:  Hemang Bhatt
 ** Date:    02/20/15
 ** Section: 12
 ** E-mail:  hb6@umbc.edu
 **
 **   This file contains the main driver program for Project 1.
 ** This program includes the header file for specified activity data, and
 ** schedules maximum possible activities using greedy algorithm and displays
 ** the results in the format (hh:mm).
 **
 ***********************************************/

//  Activity Scheduling

#include <iostream>
#include <iomanip>
#include <string>
#include "sched.hpp"

using namespace std;



// sort() - sorts an array of floats returning sorted indices
// On return, indx[] is an array of indices such that data[indx[0]],
// data[indx[1]], ..., data[indx[len-1]] is data[] in ascending order.
//
// Parameters
//    data[] - float array of data to be ordered
//    indx[] - int array, same length as data[], to hold indices
//    len - int specifying the length of data[] and indx[]

void sort(float data[], int indx[], int len);

// sched() - schedules events given start and end times, and indx[] from sort
// Returns number of events scheduled; on return, scheduled[] contains
// indices of scheduled events (e.g. startTime[scheduled[0]] is the start
// time of the first schedled event).
//
// Parameters
//    startTime[] - float array of event start times
//    endTime[] - float array of event end times
//    indx[] - array of indices that orders the end times
//    scheduled[] - int array to hold indices of scheduled events
//    len - int specifying the length of the arrays
// Returns
//    int value specifying number of events scheduled

int sched(float startTime[], float endTime[], int indx[], int scheduled[], int len);

// printEvent() - prints an event to the console
// Converts float start and end times to hh:mm format and prints times
// along with description.  E.g. Study Session from 12.5 to 13.25 should
// print as "12:30 - 13:15 Study Session"
//
// Parameters
//    startTime - float event start time
//    endTime - float event end time
//    description - string event description

void printEvent(float startTime, float endTime, string description);

// MAIN PROGRAM

int main() {
    
    int indx[NUM_EVENTS];
    int scheduledEvents[NUM_EVENTS];
    int numSched;
    
    // Sort by event ending times
    sort(endTime, indx, NUM_EVENTS);
    
    // Call greedy scheduling algorithm
    numSched = sched(startTime, endTime, indx, scheduledEvents, NUM_EVENTS);
    
    // Display scheduled events
    for (int i = 0; i < numSched; i++)
        printEvent(startTime[scheduledEvents[i]], endTime[scheduledEvents[i]],
                   description[scheduledEvents[i]]);
    
    return 0;
}

//
// FUNCTION IMPLEMENTATIONS
//
void sort(float data[], int indx[], int len) {
    
    // create index array
    for (int i = 0; i < len; i++)
        indx[i] = i;
    
    // sort indices of the indx array using bubble sort
    
    for (int x = 0; x < len; x++) {
        
        for (int y = 0; y < (len - 1); y++) {
            
            // if higher value than swape
            if (data[indx[y]] > data[indx[y + 1]]) {
                
                int temp = indx[y];
                
                indx[y] = indx[y + 1];
                
                indx[y + 1] = temp;
            }
        }
    }

}

// This function schedules the event using greedy algorithm giving first preference to the event who ends first.
int sched(float startTime[], float endTime[], int indx[], int scheduled[], int \
          len) {
    
    // register the first event
    int counter = 0;
    scheduled[counter] = indx[counter];
    
    for (int eventNum = 1; eventNum < len; eventNum++) {
        
        // Register the event if start time of event is after than end time of
        // previous event
        if (startTime[indx[eventNum]] >= endTime[scheduled[counter]]) {
            scheduled[(counter + 1)] = indx[eventNum];
            counter++;
        }
    }
    return ++counter; // increase by 1 one for the first event
}

// This function prints time using hh:mm format with discription
void printEvent(float startTime, float endTime, string description) {
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    // set floting point precision 2
    cout.precision(2);
    
    // fill 0 if one digit
    // Find minutes using (time - int(time)) * 60
    // set width of hours using setw()
    cout << std::setw(2) << std::setfill('0') << int(startTime) << ":"
    << std::setw(2) << std::setfill('0') << int((((startTime) - int(startTime)) * 60)) << " - "
    << std::setw(2) << std::setfill('0') << int(endTime) << ":"
    << std::setw(2) << std::setfill('0') << int((((endTime) - int(endTime)) * 60 ))
    << " " << description << endl;
}

