//
//  Job.h
//  TeamProject8JobSearch
//
//  Created by Ging Gonzalez on 2/28/18.
//  Copyright © 2018 Ging Gonzalez. All rights reserved.
//

#ifndef Job_h
#define Job_h
using std::string;

class Job
{
private:
    string name;
    string id;
    string company;
    int date;
    string location;
public:

    Job()
    {
        name = "";
        id = "";
        company = "";
        date = 0;
        location = "";
    };

    Job(string id, string name, string company, int date, string location)
    {
        this->name = name;
        this->id = id;
        this->date = date;
        this->location = location;
    }

    // Setters
    void setName(string name) {this->name = name;};
    void setID(string id) {this->id = id;};
    void setCompany(string company) {this->company = company;};
    void setDate(int date) {this->date = date;};
    void setLocation(string location) {this->location = location;};


    // Getters
    string getName() const {return name;};
    string getID() const {return id;};
    string getCompany() const {return company;};
    int getDate() const {return date;};
    string getLocation() const {return location;};


    // Overloaded operators
    void operator = (const Job &job ) {
        name = job.name;
        id = job.id;
        date = job.date;
        location = job.location;
    }

    bool operator == (const Job &job ) {
        if (name != job.name || id != job.id || date != job.date || location != job.location)
            return false;
        return true;
    }

    bool operator != (const Job &job ) {
        if (name != job.name || id != job.id || date != job.date || location != job.location)
            return true;
        return false;
    }

    bool operator < (const Job& job) const {
        if(id < job.id)
            return true;
        return false;
    }

    bool operator > (const Job& job) const {
        if(id > job.id)
            return true;
        return false;
    }
};

#endif /* Job_h */
