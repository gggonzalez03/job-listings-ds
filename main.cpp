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

int generateID();
int getTodaysDate();

void readJobs(BinarySearchTree<Job> &jobs, string fileName);


int main() {
    string choice;
    
    // List of jobs that is based on the primary key (unique id)
    BinarySearchTree<Job> *jobs = new BinarySearchTree<Job>();
    
    // List of jobs that is based on the secondary key (date)
    BinarySearchTree<Job> *jobs2 = new BinarySearchTree<Job>();
    
    // The hash table for the primary tree
    HashTable<int, Job> *hashTable = new HashTable<int, Job>();
    
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
    
    jobs->inOrder(display);
}

void display(Job & anItem)
{
    cout << anItem.getID() << " " << anItem.getName() << " " << anItem.getCompany() << endl;
}

void displayMenu()
{
    cout << "D - Display Job Listings" << endl;
    cout << "S - Search Job Listings" << endl;
    cout << "A - Add Job Listings" << endl;
    cout << "R - Delete Job Listings" << endl;
    cout << "L - Logout" << endl;
}

void displayJobListings(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2)
{
    cout << "Display listings" << endl;
    
    // TODO:
    // Add list as unsorted data
    // sorted by primary key
    // sorted by secondary key
    // Special print, indented list
}

void search(BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
{
    string choice = "";
    
    cout << "P - Search job by ID" << endl;
    cout << "SK = Search job by date" << endl;
    
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
    
    cout << "Search the list using " << id << " " << endl;
}

void searchByDate(BinarySearchTree<Job> &jobs2)
{
    string date = "";
    
    cout << "Enter date (mm/dd/yyy): ";
    getline(cin, date);
    
    // TODO:
    // Convert date to integer
    
    cout << "Search the list by date: " << date;
}

void add(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
{
    string choice = "";
    
    cout << "J - Add single entry" << endl;
    cout << "F - Add listings using a file" << endl;
    
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

void addJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
{
    string entry = "";
    cout << "Enter job information (ex. Title Company City): ";
    getline(cin, entry);
    
    // TODO:
    // Take the input and concatenate such that these
    // variables are set appropriately
    string title = "";
    string company = "";
    string city = "";
    
    // TODO:
    
    // int id = generateID();
    
    // int date = getTodaysDate();
    
    // TODO:
    // Create Job class object using values from the user and generated id and date
    // Job newJob = new Job(id, title, date, city);
    
    // TODO:
    // Call add node function from BST to actually add the entry into the tree (primary tree)
    // Call add node function for secondary tree
    // Call insert to Hash Table
}

void addJobs(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
{
    string fileName = "";
    cout << "Enter the name of the txt file containing the job listings: ";
    getline(cin, fileName);
    
    readJobs(jobs, fileName);
    readJobs(jobs2, fileName);
    
    // TODO:
    // Add to hash table
}

void del(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
{
    string choice = "";
    
    cout << "J - Add single entry" << endl;
    cout << "L - Add listings using a file" << endl;
    
    cout << "Enter choice: ";
    getline(cin, choice);

    
    if (choice == "J")
        deleteJob(jobs, jobs2, hashTable);
    else if (choice == "L")
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
    
    cout << "Enter job id to delete: ";
    getline(cin, id);
    
    // TODO:
    // Delete in BST (Primary and Secondary)
    // Delete in Hash table
    
    // This could be inside if(deleteEntry(id)) where deleteEntry() returns boolean
    cout << "Deleted successfully" << endl;
}

void deleteOldestJob(BinarySearchTree<Job> &jobs, BinarySearchTree<Job> &jobs2, HashTable<int, Job> &hashTable)
{
    // TODO:
    // Delete in BST (Primary and Secondary)
    // Delete in Hash table
    cout << "Oldest job deleted.";
}

void logout()
{
    return;
}

// TODO:
// Doesnt return false
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
    else
    {
        cout << "Please enter valid username and password." << endl;
        login();
    }
    
    return false;
}

void readJobs(BinarySearchTree<Job> &jobs, string fileName)
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
    cout << "Reading file " << fileName << endl;
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

