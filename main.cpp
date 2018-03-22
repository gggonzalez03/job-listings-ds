//
//  main.cpp
//  JobListings
//
//  Created by Ging Gonzalez on 3/17/18.
//  Copyright © 2018 Ging Gonzalez. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <ctime>

#include "Job.h"
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "Queue.h"
using namespace std;


const string username = "Fawzan";
const string password = "12345";


// TODO:
// Add parameters to functions such that they accomodate both primary and secondary trees and the hash table
bool login();
void displayMenu();
void displayJobListings(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2);
void search(BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable); // Calls searchById() and searchByDate()
void searchById(HashTable<string, Job> &hashTable); // Hash table
void searchByDate(BinarySearchTree<Job> &jobs2); // Secondary tree
// Should take both primary and secondary tree
void add(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable); // Calls addJob() and addJobs();
void addJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable);
void addJobs(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable);
void del(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable); // Calls deleteJob() and deleteOldestJob()
void deleteJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable);
void deleteOldestJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable);
void logout(HashTable<string, Job> &);

// display function to pass to BST traverse functions
void display(Job &anItem);
bool compareID(const Job &, const Job &);
bool compareDate(const Job &, const Job &);
void printIndentedItem(int depth, Job &job);
void printAndSave(ofstream&, Job&);

int generateID(HashTable<string, Job> &hashTable);
int getTodaysDate();

int readFile(BinarySearchTree<Job> &, BinarySearchTree<Job> &, Queue<Job> &, string fileName);
void writeFile(HashTable<string, Job> &, string);

// Simple helper functions
void printHeader(string title);

int main() {

    // Ask the user for un and pw until a valid combination is entered
    // while (!login()) { }

    // Only start assigning variable after successful login
    string choice;

    // List of jobs that is based on the primary key (unique id)
    BinarySearchTree<Job> *jobs = new BinarySearchTree<Job>(compareID);

    // List of jobs that is based on the secondary key (date)
    BinarySearchTree<Job> *jobs2 = new BinarySearchTree<Job>(compareDate);

    // Queue that will be used to save the entries in the order they were added
    // This will be used to insert items to the hash table without re opening the input file
    Queue<Job> *jobQueue = new Queue<Job>();
    
    // read the jobs into the trees
    // And also fill up the queue and return the itemsCount
    int itemCount = readFile(*jobs, *jobs2, *jobQueue, "jobs.txt");
    
    // The hash table for the primary tree
    // TODO:
    // GetNextPrime of the itemCount and assign it as the table size
    HashTable<string, Job> *hashTable = new HashTable<string, Job>(itemCount * 2 + 3, 4);
    
    
    // Insert the items from the queue to the hash table
    Job *job = new Job();
    while (!jobQueue->isEmpty())
    {
        jobQueue->dequeue(*job);
        hashTable->insertBadHash(job->getID(), *job);
    }
    
    delete job;
    delete jobQueue;

    // Start the asking the user for choices of operations
    while (*choice.c_str() != 'L')
    {
        displayMenu();

        cout << "Enter choice: ";
        getline(cin, choice);

        switch(*choice.c_str())
        {
            case 'D':
                displayJobListings(*jobs, *jobs2);
                break;
            case 'S':
                search(*jobs2, *hashTable);
                break;
            case 'A':
                add(*jobs, *jobs2, *hashTable);
                break;
            case 'R':
                del(*jobs, *jobs2, *hashTable);
                break;
            case 'L':
                logout(*hashTable);
                break;
            default:
                break;
        }
    }
}

void display(Job & anItem)
{
    cout << anItem.getID() << " "
    << anItem.getName() << " "
    << anItem.getCompany() << " "
    << anItem.getLocation() << " "
    << anItem.getDate() << " "
    << endl;
}

// Compare id such that lower ids are printed first
bool compareID(const Job &a, const Job &b)
{
    if (a.getID() > b.getID())
        return true;
    return false;
}

// TODO:
// Verify that this is legal in BSTs. This BST has the larger values on the left side of the tree
// Compare date such that the latest first are listed
bool compareDate(const Job &a, const Job &b)
{
    if (a.getDate() > b.getDate())
        return true;
    return false;
}

// Prints an item that is indented (this is a function to be passed in printTree)
void printIndentedItem(int depth, Job &job)
{
    for (int i = 0; i < depth; i++) {
        cout << "   ";
    }

    cout << depth << ". ";
    display(job);
    cout << endl;
}

// Prints a header
void printHeader(string title)
{
    cout << "------------------------------------------------------------" << endl;
    cout << title << endl;
    cout << "------------------------------------------------------------" << endl;
}

void displayMenu()
{
    printHeader("Menu");
    cout << "D - Display Job Listings" << endl;
    cout << "S - Search Job Listings" << endl;
    cout << "A - Add Job Listings" << endl;
    cout << "R - Delete Job Listings" << endl;
    cout << "L - Logout" << endl;
    cout << endl;
}

void displayJobListings(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2)
{
    string choice = "";
    cout << endl;
    cout << "U - Print unsorted job list" << endl;
    cout << "P - Print jobs sorted by ID" << endl;
    cout << "S - Print jobs sorted by date" << endl;
    cout << "I - Print jobs as an indented list" << endl;
    cout << endl;

    cout << "Enter choice: ";
    getline(cin, choice);

    switch (*choice.c_str()) {
        case 'U':
            //            printUnsorted();
            printHeader("Unsorted Jobs List");
            printHeader("TO BE IMPLEMENTED");
            break;
        case 'P':
            printHeader("Sorted by ID");
            jobs.inOrder(display);
            break;
        case 'S':
            printHeader("Sorted by Date");
            jobs2.inOrder(display);
            break;
        case 'I':
            printHeader("Tree As Indented List");
            jobs.printTree(printIndentedItem, 1);
            break;
        default:
            break;
    }
}

void search(BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable)
{
    string choice = "";

    cout << endl;
    cout << "P - Search job by ID" << endl;
    cout << "SK - Search job by date" << endl;
    cout << endl;

    cout << "Enter choice: ";
    getline(cin, choice);

    if (choice == "P")
        searchById(hashTable);
    else if (choice == "SK")
        searchByDate(jobs2);
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }
}

void searchById(HashTable<string, Job> &hashTable)
{
    string id = "";
    cout << endl;
    cout << "Enter 5 digit ID (ex. 12423): ";
    getline(cin, id);

    // TODO:
    // This won't work until items are inserted in the hash table
    Job *job = new Job();
    job->setID(id);

    printHeader("Search By ID");

    if (hashTable.searchTable(id, *job))
        display(*job);
    else
        cout << "Job not found." << endl;
    
    delete job;
}
// updated by Fawzan
void searchByDate(BinarySearchTree<Job> &jobs2)
{
    string date = "";
    Job *job = new Job();

    cout << "Enter date (yyyymmdd): ";
    getline(cin, date);

    // Use this to search the tree
    int searchDate = stoi(date);

    job->setDate(searchDate);

    printHeader("Search by Date Results");
    jobs2.getEntries(*job, display);
    cout << endl;
    
    delete job;
}

void add(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable)
{
    string choice = "";

    cout << endl;
    cout << "J - Add single entry" << endl;
    cout << endl;

    cout << "Enter choice: ";
    getline(cin, choice);


    if (choice == "J")
        addJob(jobs, jobs2, hashTable);
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }
}
// updated by Fawzan
void addJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable)
{
    printHeader("Add A Job");
    string title = "";
    string company = "";
    string city = "";

    /****** Fawzan's Suggestion */

    cout << "Enter job information. \nTitle: ";
    getline(cin, title);
    cout <<"Company: ";
    getline(cin, company);
    cout << "City: ";
    getline(cin, city);

    // both generateID and getTodaysDate are ready to be implemented
    string id = to_string(generateID(hashTable));

    int date = getTodaysDate();

    // Create Job class object using values from the user and generated id and date
    Job *newJob = new Job(id, title, company, date, city);

    // Call add node function from BST to actually add the entry into the tree (primary tree)
    jobs.insert(*newJob);
    // Call add node function for secondary tree
    jobs2.insert(*newJob);
    // Call insert to Hash Table
    hashTable.insertBadHash(newJob->getID(), *newJob);
    
    delete newJob;
}

void del(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable)
{
    string choice = "";

    cout << endl;
    cout << "D - Delete a Job listing" << endl;
    cout << "O - Delete oldest Job listing" << endl;
    cout << endl;

    cout << "Enter choice: ";
    getline(cin, choice);


    if (choice == "D")
        deleteJob(jobs, jobs2, hashTable);
    else if (choice == "O")
        deleteOldestJob(jobs, jobs2, hashTable);
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }
}

void deleteJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable)
{
    string id = "";
    printHeader("Delete A Job By ID");
    printHeader("TO BE IMPLEMENTED");
    cout << "Enter job id to delete: ";
    getline(cin, id);

    Job *job = new Job();
    job->setID(id);

    jobs.remove(*job);

    // TODO:
    // Return the whole object from the hash table when it's deleted there
    // Then, use that object to pass in jobs2.removeByNonUniqueID(jobobjecthere)

    // TODO:
    // Delete in BST (Primary and Secondary)
    // Delete in Hash table

    // This could be inside if(deleteEntry(id)) where deleteEntry() returns boolean
    
    delete job;
}

void deleteOldestJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable)
{
    // TODO:
    // Delete in BST (Primary and Secondary)
    // Delete in Hash table
    printHeader("Delete Oldest Job");
    printHeader("TO BE IMPLEMENTED");

    Job *oldestJob = new Job();
    jobs2.findSmallest(*oldestJob);
    jobs.remove(*oldestJob);
    jobs2.remove(*oldestJob);

    // hashTable.remove(*oldestJob->getID(), *oldestJob);
    
    delete oldestJob;
}

void logout(HashTable<string, Job> &hashTable)
{
    // TODO:
    // Write data from the hash table
    writeFile(hashTable, "updatedJobs.txt");
    return;
}

bool login()
{
    string un;
    string pw;

    // Ask user for pw and username
    cout << "Enter username: ";
    getline(cin, un);
    cout << "Enter password: ";
    getline(cin, pw);


    if (un == username && pw == password)
    {
        return true;
    }

    cout << "Please enter valid username and password." << endl;

    return false;
}

int readFile(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, Queue<Job> &queue, string fileName)
{

    string title = "";
    string company = "";
    string city = "";
    string id = "";
    int date = 0;
    int itemsCount = 0;

    ifstream infile;
    infile.open(fileName);

    while(!infile)
    {
        cout << "Error opening " << fileName << " for reading\n";
        exit(111);
    }

    // TODO:
    // Read the file and insert items into the primaryTree, secondaryTree, and the hast table
    Job *job = nullptr;

    while(infile >> id)
    {
        infile.ignore();
        getline(infile, title, ';');
        infile.ignore();
        getline(infile, company, ';');
        infile.ignore();
        getline(infile, city, ';');
        infile.ignore();
        infile >> date;

        // Create a Job object
        job = new Job(id, title, company, date, city);

        // Insert the object
        jobs.insert(*job);
        
        // Insert in secondary tree (sorted by date)
        jobs2.insert(*job);
        
        // Insert in the queue
        queue.enqueue(*job);
        
        itemsCount++;
    }
    infile.close();
    
    delete job;
    
    return itemsCount;
}

void printAndSave(ofstream &ofs, Job &job)
{
    cout << job << endl;
    ofs << job;
    ofs << endl;
}

void writeFile(HashTable<string, Job> &hashTable, string fileName)
{
    ofstream ofs;

    // trunc allows the file to rewritten instead of appending in it
    ofs.open (fileName, ofstream::out | ofstream::trunc);

    if(ofs.fail())
    {
        cout << "Error saving to file " << fileName;
        exit(111);
    }
    
    printHeader("Hash Table Items");
    hashTable.traverseTable(printAndSave, ofs);

    ofs.close();
}

// updated by Fawzan
// Generates 4 digit ID and searches HashTable to see if ID already exists
int generateID(HashTable<string, Job> &hashTable) {
    // Seed the random number generator
    srand((unsigned int)time(NULL));
    
    int newID = 0;
    newID = rand() % 2000 + 1000;
    
    Job *temp = new Job();
    temp->setID(to_string(newID));

    while(hashTable.searchTable(temp->getID(), *temp)) {
        newID = rand() % 2000 + 1000;
        temp->setID(to_string(newID));
        cout << !hashTable.searchTable(temp->getID(), *temp) << " " << newID << endl;
    }
    
    delete temp;
    return newID;
}
// updated by Fawzan
// Generates the current days date (Today)
int getTodaysDate() {
    int day = 0;
    int month = 0;
    int year = 0;

    time_t now = time(0);
    struct tm* ptr2tm;
    ptr2tm = localtime(&now);

    day = ptr2tm->tm_mday;
    month = ptr2tm->tm_mon+1;
    year = ptr2tm->tm_year+1900;

    string d = to_string(day);
    string m = to_string(month);
    string y = to_string(year);
    string z = "0";
    string wholeDate = y + z + m + d;

    int todaysDate = stoi(wholeDate);

    return todaysDate;
}
