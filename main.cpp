/*
Monroe Shindelar and JJ Abides
Professor Rob Nash
CSS 342: Data Structures, Algorithms, and Discrete Math
November 23, 2016
Transaction Processing: main

This is an example main for the transaction processing assignment.
This program is supposed to make a lose firm out of a text file, and
then takes commands out of a text file and use those commands on the 
clients of the lose firm. First a manager object is enstantiated. Then
an ifstream file is made using the file that holds the data of the clients.
If we cant find the file, then we return false and break out of the main. If
we do find the file, then we pass it to the generateFirm function so that the
tree may be populated with the clients in the file. Then we create another
ifstream object and pass it the file that holds all of the transactions that the
firm will be processing this day. If we cant find the file, we output that to the
console and then break out of the main. If we do find the file, then we pass that
ifstream object to the takeTransactions function where all of the transactions in 
the file will be put into a transaction queue. Then the perform transactions function
is called so that all the functions that were enqueued can be performed. At the end when
all the transactions have been performed and the transaction queue is empty, we can print
the results of the manager class to the console, which will print the status of each client
in the tree.
*/

#include "manager.h"
using namespace std;

int main() {
	Manager theBank;; //make a new manager object.
    ifstream firmFile("HW5data.txt"); //make an ifstream object with the file hw5data.txt
    if(!firmFile) { //check to see if we found the file
        cout << "File could not be opened" << endl; //if we didnt, tell the user we couldnt find the file
        return 1;  //break out of the main
    }
    theBank.generateFirm(firmFile); //generate the firm using the ifstream we created
    firmFile.close(); //close the firm file ifstream
    ifstream commands("HW5command.txt"); //make an ifstream using the file hw5commands.txt
    if(!commands) { //check to see if we found the file
        cout << "File could not be opened" << endl; //if we couldnt find the file tell the user
        return 1; //break out of the main
    }
    theBank.takeTransactions(commands); //call take transactions and give it the commands ifstream
    commands.close(); //close the commands ifstream
    theBank.performTransactions(); //call perform transactions
    cout << theBank << endl; //print out the data of the manager class
    return 0;
};
 
