// Created and modified by Ging Gonzalez and Fawzan Khan

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

bool login();
// Display the menu for the users
void displayMenu();
// Display a submenu for displaying data from the trees and the hash table
void displayJobListings(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &);
// Display a submenu for searching
void search(BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable); // Calls searchById() and searchByDate()
void searchById(HashTable<string, Job> &hashTable); // Hash table
void searchByDate(BinarySearchTree<Job> &jobs2); // Secondary tree
// Display a submenu for inserting/adding
void add(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable); // Calls addJob() and addJobs();
void addJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable);
void addJobs(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable);
// Display a submenu for deleting/removing
void del(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable); // Calls deleteJob() and deleteOldestJob()
void deleteJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable);
void deleteOldestJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable);
// Logout will save the updated items in a text file
// And also print statistics
void logout(HashTable<string, Job> &);

// display function to pass to BST/HashTable traverse functions
void display(Job &anItem);
void prettyPrint(Job &anItem);
bool compareID(const Job &, const Job &);
bool compareDate(const Job &, const Job &);
bool equality(const Job &, const Job&);
void printIndentedItem(int depth, Job &job);
void printAndSave(ofstream&, Job&);

// Helper functions
int generateID(HashTable<string, Job> &hashTable);
int getTodaysDate();
int findNextPrime(int);

// File operation functions
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
    // Initialize with the next prime number of itemsCount * 2
    HashTable<string, Job> *hashTable = new HashTable<string, Job>(findNextPrime(itemCount * 2), 4);


    // Insert the items from the queue to the hash table
    Job *job = new Job();
    while (!jobQueue->isEmpty())
    {
        jobQueue->dequeue(*job);
        hashTable->insertGoodHash(job->getID(), *job);
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
                displayJobListings(*jobs, *jobs2, *hashTable);
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
    cout << anItem << endl;
}

void prettyPrint(Job & anItem)
{
    cout << " " << anItem.getID() << " " << anItem.getName() << " " << anItem.getCompany() << " " << anItem.getLocation() << " " << anItem.getDate() << endl;
}

// Compare id such that lower ids are printed first
bool compareID(const Job &a, const Job &b)
{
    if (a.getID() > b.getID())
        return true;
    return false;
}

// Compare date such that the latest first are listed
bool compareDate(const Job &a, const Job &b)
{
    if (a.getDate() > b.getDate())
        return true;
    return false;
}

bool equality(const Job &a, const Job &b)
{
    if (a.getDate() == b.getDate())
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
    prettyPrint(job);
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

void displayJobListings(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable)
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
            printHeader("Unsorted Jobs List");
            cout << left << setw(6) << "ID" << left << setw(50) << "JOB TITLE" << setw(40) << "COMPANY" << setw(20) << "LOCATION" << setw(8) << "DATE" << endl;
            hashTable.printTable(display);
            break;
        case 'P':
            printHeader("Sorted by ID");
            cout << left << setw(6) << "ID" << left << setw(50) << "JOB TITLE" << setw(40) << "COMPANY" << setw(20) << "LOCATION" << setw(8) << "DATE" << endl;
            jobs.inOrder(display);
            break;
        case 'S':
            printHeader("Sorted by Date");
            cout << left << setw(6) << "ID" << left << setw(50) << "JOB TITLE" << setw(40) << "COMPANY" << setw(20) << "LOCATION" << setw(8) << "DATE" << endl;
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

    Job *job = new Job();
    job->setID(id);

    printHeader("Search By ID");

    if (hashTable.searchTable(id, *job))
        prettyPrint(*job);
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
    hashTable.insertGoodHash(newJob->getID(), *newJob);

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
    cout << "Enter job id to delete: ";
    getline(cin, id);

    Job *job = new Job();
    job->setID(id);

    // Deletes from hashtable, jobs, and jobs2
    if (hashTable.remove(job->getID(), *job))
    {
        jobs.remove(*job);

        jobs2.removeByNonUniqueID(*job, equality);
        cout << *job << endl;
    }
    else
        cout << "Not found." << endl;
    delete job;
}

void deleteOldestJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<string, Job> &hashTable)
{

    printHeader("Delete Oldest Job");

    Job *oldestJob = new Job();

    // will set oldestJob to the smallest/oldest
    jobs2.findSmallest(*oldestJob);

    if (hashTable.remove(oldestJob->getID(), *oldestJob))
    {
        jobs.remove(*oldestJob);
        jobs2.remove(*oldestJob);
        cout << *oldestJob << endl;
    }
    delete oldestJob;
}

void logout(HashTable<string, Job> &hashTable)
{
    writeFile(hashTable, "updatedJobs.txt");

    // print statistics
    printHeader("Load Factor");
    cout << "Hash table load factor: " << hashTable.getLoadFactor() * 100 << "%" << endl;
    cout << "Hash table collisions: " << hashTable.getCollisionCount() << endl;
    cout << endl;
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

int findNextPrime(int start) {
    int i, j, count;
    for (i = start + 1; 1; i++)
    {
        count = 0;
        for (j = 2;j < i; j++)
            if (i%j == 0)
            {
                count++;
                break;
            }
        if (count == 0)
            return i;
    }
}
