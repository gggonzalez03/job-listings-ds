// Created and modified by Ging Gonzalez and Fawzan Khan

#ifndef Job_h
#define Job_h
using std::string;
using std::ostream;

class Job
{
private:
    string name;
    string id;
    string company;
    int date;
    string location;
public:
    // Constructors
    Job();
    Job(string, string, string, int, string);
    // Setters
    void setName(string);
    void setID(string);
    void setCompany(string);
    void setDate(int);
    void setLocation(string);
    // Getters
    string getName() const;
    string getID() const;
    string getCompany() const;
    int getDate() const;
    string getLocation() const;
    // Overloaded operators
    void operator = (const Job&);
    bool operator == (const Job&);
    bool operator != (const Job&);
    bool operator < (const Job&) const;
    bool operator > (const Job&) const;
    friend ostream& operator<<(ostream&, const Job&);
};

#endif /* Job_h */
