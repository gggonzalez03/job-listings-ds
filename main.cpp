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
using namespace std;


const string username = "Fawzan";
const string password = "12345";

bool login();
void displayMenu();
void displayJobListings();
void search(); // Calls searchById() and searchByDate()
void searchById();
void searchByDate();
void add(); // Calls addJob() and addJobs();
void addJob();
void addJobs();
void del(); // Calls deleteJob() and deleteOldestJob()
void deleteJob();
void deleteOldestJob();
void logout();

int generateID();
int getTodaysDate();

void readJobs(BinarySearchTree<Job> &jobs, string fileName);


int main() {
    string choice;
    
    while (*choice.c_str() != 'L')
    {
        displayMenu();
        
        cout << "Enter choice: ";
        getline(cin, choice);
        
        switch(*choice.c_str())
        {
            case 'D':
                displayJobListings();
                break;
            case 'S':
                search();
                break;
            case 'A':
                add();
                break;
            case 'R':
                del();
                break;
            default:
                break;
        }
    }
}

void displayMenu()
{
    cout << "D - Display Job Listings" << endl;
    cout << "S - Search Job Listings" << endl;
    cout << "A - Add Job Listings" << endl;
    cout << "R - Delete Job Listings" << endl;
    cout << "L - Logout" << endl;
}

void displayJobListings()
{
    cout << "Display listings" << endl;
}

void search()
{
    string choice = "";
    
    cout << "P - Search job by ID" << endl;
    cout << "SK = Search job by date" << endl;
    
    cout << "Enter choice: ";
    getline(cin, choice);
    
    if (choice == "P")
        searchById();
    else if (choice == "SK")
        searchByDate();
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }
}

void searchById()
{
    string id = "";
    
    cout << "Enter 5 digit ID (ex. 12423): ";
    getline(cin, id);
    
    cout << "Search the list using " << id << " " << endl;
}

void searchByDate()
{
    string date = "";
    
    cout << "Enter date (mm/dd/yyy): ";
    getline(cin, date);
    
    // TODO:
    // Convert date to integer
    
    cout << "Search the list by date: " << date;
}

void add()
{
    string choice = "";
    
    cout << "J - Add single entry" << endl;
    cout << "F - Add listings using a file" << endl;
    
    cout << "Enter choice: ";
    getline(cin, choice);

    
    if (choice == "J")
        addJob();
    else if (choice == "F")
        addJobs();
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }
}

void addJob()
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

void addJobs()
{
    string fileName = "";
    cout << "Enter the name of the txt file containing the job listings: ";
    getline(cin, fileName);
    
    BinarySearchTree<Job> *jobs = new BinarySearchTree<Job>();
    
    readJobs(*jobs, fileName);
    
    
}

void del()
{
    string choice = "";
    
    cout << "J - Add single entry" << endl;
    cout << "L - Add listings using a file" << endl;
    
    cout << "Enter choice: ";
    getline(cin, choice);

    
    if (choice == "J")
        deleteJob();
    else if (choice == "L")
        deleteOldestJob();
    else
    {
        cout << "Invalid choice." << endl;
        return;
    }
}

void deleteJob()
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

void deleteOldestJob()
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
        
    }
    infile.close();
}

