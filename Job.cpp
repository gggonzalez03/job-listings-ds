#include <iostream>
#include <iomanip>
#include "Job.h"

using std::setw;
using std::left;

Job::Job()
{
  name = "";
  id = "";
  company = "";
  date = 0;
  location = "";
}

Job::Job(string id, string name, string company, int date, string location)
{
  this->name = name;
  this->id = id;
  this->date = date;
  this->company = company;
  this->location = location;
}

// Setters
void Job::setName(string name) {this->name = name;};
void Job::setID(string id) {this->id = id;};
void Job::setCompany(string company) {this->company = company;};
void Job::setDate(int date) {this->date = date;};
void Job::setLocation(string location) {this->location = location;};


// Getters
string Job::getName() const {return name;};
string Job::getID() const {return id;};
string Job::getCompany() const {return company;};
int Job::getDate() const {return date;};
string Job::getLocation() const {return location;};


// Overloaded operators
void Job::operator = (const Job &job ) {
  name = job.name;
  id = job.id;
  date = job.date;
  company = job.company;
  location = job.location;
}

bool Job::operator == (const Job &job ) {
  if (id != job.id)
  return false;
  return true;
}

bool Job::operator != (const Job &job ) {
  if (id != job.id)
  return true;
  return false;
}

bool Job::operator < (const Job& job) const {
  if(id < job.id)
  return true;
  return false;
}

bool Job::operator > (const Job& job) const {
  if(id > job.id)
  return true;
  return false;
}

ostream& operator<<(ostream& s, const Job& j) {
  s << left << setw(6) << j.getID() << left << setw(50) << j.getName() << setw(40) << j.getCompany() << setw(20) << j.getLocation() << setw(8) << j.getDate();
  return s;
}
