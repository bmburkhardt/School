//team.cpp
//Bryan Burkhardt
//12 Sep 2016
//
//Assignment 1 for CS311 Fall 2016
//Source for class Team

#include "team.h"
#include <string>
using std::string;
#include <ostream>
using std::ostream;
#include <sstream>
using std::ostringstream;

// *********************************************************
// class Team - Definitions of member functions
// *********************************************************

// Team::toString
// (see header for docs.)
string Team::toString() const
{
    ostringstream rv;
    rv << name_ << " [wins: " << wins_ << "]";
    return rv.str();
    
}

// *********************************************************
// class Team - Definitions of associated global operators
// *********************************************************

// op== (Team, Team)
// (see header for docs.)
bool operator==(const Team &lhs, const Team &rhs)
{
    return ((lhs.getName()==rhs.getName()) && (lhs.getWins()==rhs.getWins()));
}

// op != (Team, Team)
// (see header for docs.)
bool operator !=(const Team &lhs, const Team &rhs)
{
    return !(lhs==rhs);
}

// op<< (ostream, Team)
// (see header for docs.)
ostream & operator<<(ostream &out, const Team &rhs)
{
    out<<rhs.toString();
    return out;
}