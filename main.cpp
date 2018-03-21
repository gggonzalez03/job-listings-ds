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
using namespace std;


const string username = "Fawzan";
const string password = "12345";


// TODO:
// Add parameters to functions such that they accomodate both primary and secondary trees and the hash table
bool login();
void displayMenu();
void displayJobListings(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2);
void search(BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable); // Calls searchById() and searchByDate()
void searchById(HashTable<int, Job> &hashTable); // Hash table
void searchByDate(BinarySearchTree<Job> &jobs2); // Secondary tree
// Should take both primary and secondary tree
void add(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable); // Calls addJob() and addJobs();
void addJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable);
void addJobs(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable);
void del(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable); // Calls deleteJob() and deleteOldestJob()
void deleteJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable);
void deleteOldestJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable);
void logout();

// display function to pass to BST traverse functions
void display(Job &anItem);
bool compareID(const Job &, const Job &);
bool compareDate(const Job &, const Job &);
void printIndentedItem(int depth, Job &job);

int generateID(HashTable<int, Job> &hashTable);
int getTodaysDate();

void readJobsIntoBinarySearchTree(BinarySearchTree<Job> &jobs, string fileName);
void readJobsIntoArray(Job *jobs, string fileName);

// Simple helper functions
void printHeader(string title);

int main() {
    
    // Ask the user for un and pw until a valid combination is entered
    // while (!login()) { }
    
    // Only start assigning variable after successful login
    string choice;

    // Unsorted list
    Job *unsortedJobs = new Job[25];

    // List of jobs that is based on the primary key (unique id)
    BinarySearchTree<Job> *jobs = new BinarySearchTree<Job>(compareID);

    // List of jobs that is based on the secondary key (date)
    BinarySearchTree<Job> *jobs2 = new BinarySearchTree<Job>(compareDate);

    // The hash table for the primary tree
    HashTable<int, Job> *hashTable = new HashTable<int, Job>();


    readJobsIntoArray(unsortedJobs, "jobs.txt");

    // read the jobs into the trees
    readJobsIntoBinarySearchTree(*jobs, "jobs.txt");
    readJobsIntoBinarySearchTree(*jobs2, "jobs.txt");

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

void search(BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
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

void searchById(HashTable<int, Job> &hashTable)
{
    string id = "";

    cout << "Enter 5 digit ID (ex. 12423): ";
    getline(cin, id);

    printHeader("Search by ID Result");
    printHeader("TO BE IMPLEMENTED");
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
}

void add(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
{
    string choice = "";

    cout << endl;
    cout << "J - Add single entry" << endl;
    cout << "F - Add listings using a file" << endl;
    cout << endl;

    cout << "Enter choice: ";
    getline(cin, choice);


    if (choice == "J")
        addJob(jobs, jobs2, hashTable);
    else if (choice == "F")
        addJobs(jobs, jobs2, hashTable);
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }
}
// updated by Fawzan
void addJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
{
    //    string entry = "";
    //    cout << "Enter job information (ex. Title Company City): ";
    //    getline(cin, entry);

    // TODO:
    // Take the input and concatenate such that these
    // variables are set appropriately
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
    int id = generateID(hashTable);

    int date = getTodaysDate();

    // Create Job class object using values from the user and generated id and date
    Job *newJob = new Job(id, title, company, date, city);

    // Call add node function from BST to actually add the entry into the tree (primary tree)
    jobs.insert(*newJob);
    // Call add node function for secondary tree
    jobs2.insert(*newJob);
    // Call insert to Hash Table
    // hashTable.insertGoodHash(newJob->getID(), *newJob);
}

void addJobs(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
{
    printHeader("Add Jobs With A File");
    string fileName = "";
    cout << "Enter the name of the txt file containing the job listings: ";
    getline(cin, fileName);

    readJobsIntoBinarySearchTree(jobs, fileName);
    readJobsIntoBinarySearchTree(jobs2, fileName);

    // TODO:
    // Add to hash table
}

void del(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
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

void deleteJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
{
    string id = "";
    printHeader("Delete A Job By ID");
    printHeader("TO BE IMPLEMENTED");
    cout << "Enter job id to delete: ";
    getline(cin, id);
    
    Job *job = new Job();
    job->setID(stoi(id));
    
    jobs.remove(*job);
    
    // TODO:
    // Return the whole object from the hash table when it's deleted there
    // Then, use that object to pass in jobs2.removeByNonUniqueID(jobobjecthere)

    // TODO:
    // Delete in BST (Primary and Secondary)
    // Delete in Hash table

    // This could be inside if(deleteEntry(id)) where deleteEntry() returns boolean
}

void deleteOldestJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
{
    // TODO:
    // Delete in BST (Primary and Secondary)
    // Delete in Hash table
    printHeader("Delete Oldest Job");
    printHeader("TO BE IMPLEMENTED");
}

void logout()
{
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

void readJobsIntoBinarySearchTree(BinarySearchTree<Job> &jobs, string fileName)
{

    string title = "";
    string company = "";
    string city = "";
    int id = 0;
    int date = 0;

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

        // TODO:
        // Insert in hash
        // Insert in secondary tree (sorted by date)

    }
    infile.close();
}

void readJobsIntoArray(Job *jobs, string fileName)
{
    string title = "";
    string company = "";
    string city = "";
    int id = 0;
    int date = 0;

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
    int index = 0;

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

        // Insert the address
        *(jobs + index) = *job;

        index++;
    }
    infile.close();
}
// updated by Fawzan
// Generates 4 digit ID and searches HashTable to see if ID already exists
int generateID(HashTable<int, Job> &hashTable) {
        srand((unsigned int)time(NULL));
        int newID = 0;
        newID = rand() % 2000 + 1000;
    //    while(hashTable->searchTable(newID) != NULL) {
    //        newID = rand() % 2000 + 1000;
    //    }
    //    return newID;
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
