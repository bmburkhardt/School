//team.h
//Bryan Burkhardt
//12 Sep 2016
//
//Assignment 1 for CS311 Fall 2016
//Header for class Team

#ifndef FILE_TEAM_H_INCLUDED
#define FILE_TEAM_H_INCLUDED

#include <string>
using std::string;
#include <ostream>
using std::ostream;


// *********************************************************
// class Team - class definition
// *********************************************************

// class Team
// Invariants:
//      0 <= wins_

class Team
{
    
// ****** Team: ctors, and dctor ******
public:
    
    // Default ctor
    // Sets name to blank
    // Sets wins to 0
    // Pre: None.
    // Post: None.
    Team()
    {
        name_="";
        wins_=0;
    }
    
    // Ctor from data
    // Sets name as defined
    // Sets wins as defined
    // Pre:
            // 0 <= wins
    //Post:
            // Name and wins are represented as defined
    Team(string name, int wins)
    {
        name_=name;
        wins_=wins;
    }
    
    // The Big Five: Use compiler-generated version.
    ~Team() = default;
    Team(const Team &) = default;
    Team(Team &&) = default;
    Team & operator=(const Team &) = default;
    Team & operator=(Team &&) = default;
    
// ****** Team: General public functions ******
public:
    
    // getName
    // Pre: None.
    // Post:
    //      returns name_ of *this
    string getName() const
    {
        return name_;
    }
    
    // getWins
    // Pre: None.
    // Post: returns wins_ of *this
    int getWins() const
    {
        return wins_;
    }
    
    // setName
    // Pre: name==string
    // Post:
    //      name_ set as passed to function.
    void setName(string name)
    {
        name_=name;
    }
    
    // setWins
    // Pre: 0 <= wins
    // Post:
    //      wins_ set as passed to function.
    void setWins(int wins)
    {
        wins_=wins;
    }
    // toString
    // returns string represented as: "name_ [wins: wins_]"
    // Pre: None.
    // Post:
    //      Returns string as described.
    string toString() const;
    
// ****** Team: General public operators ******
public:
    
    // op++ (pre)
    // Pre: None.
    // Post:
    //      wins_ incremented by 1 win
    //      Return is *this
    Team & operator++()
    {
        ++wins_;
        return *this;
    }
    
    // op++ (post)
    // Pre: None.
    // Post:
    //      wins_ incremented by 1 win
    //      Return is former value of *this
    Team operator++(int dummy)
    {
        Team save = *this;
        ++*this;
        return save;
    }
    
    // op-- (pre)
    // Pre: None.
    // Post:
    //      wins_ decremented by 1 win
    //      if(wins<=0) then wins_ set to 0
    //      Return is *this
    Team & operator--()
    {
        if(wins_<=0)
        {
            wins_=0;
        }
        else
        {
            --wins_;
        }
        return *this;
    }
    
    // op-- (post)
    // Pre: None.
    // Post:
    //      wins_ decremented by 1 win
    //      Return is former value of *this
    Team operator --(int dummy)
    {
        Team save = *this;
        --*this;
        return save;
    }
    
// ****** Team: Private data members ******
private:
    string name_; // Team name
    unsigned int wins_; // 0 <= wins_
}; // End class Team

// *********************************************************
// class Team - Declarations of associated global operators
// *********************************************************

// op== (Team, Team)
// Pre: None.
// Post:
//      Return is true if lhs && rhs represent wins_ and name_
bool operator==(const Team &lhs, const Team &rhs);

// op!= (Team, Team)
// Pre: None.
// Post:
//      Return is false if lhs && rhs represent different wins_ || name_
bool operator!=(const Team &lhs, const Team &rhs);

// op<< (ostream, Team)
// outputs the given Team as same format as Team::toString()
// Pre: None.
// Post:
        //Output to the given stream done as described.
        //Return is the given stream.
ostream & operator<<(ostream &out, const Team &rhs);


#endif //#ifndef FILE_TEAM_H_INCLUDED
