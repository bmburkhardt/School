// team_test.cpp
// Glenn G. Chappell
// 6 Sep 2016
//
// For CS 311 Fall 2016
// Test program for class Team
// For Assignment 1, Exercise A
// Uses the "Catch" unit-testing framework
// Requires catch.hpp, team.h, team.cpp

#include "team.h"          // For class Team
#include "team.h"          // Double inclusion test

#define CATCH_CONFIG_MAIN  // We want Catch to write function main
#include "catch.hpp"       // For the "Catch" unit-testing framework

// Additional includes for this test program
#include <string>
using std::string;
#include <sstream>
using std::ostringstream;
#include <cstddef>
using std::size_t;


// *********************************************************************
// Helper Functions/Classes for This Test Program
// *********************************************************************


// class TypeCheck
// This class exists in order to have static member function "check",
// which takes a parameter of a given type, by reference. Objects of
// type TypeCheck<T> cannot be created.
// Usage:
//     TypeCheck<MyType>::check(x)
//      returns true if the type of x is (MyType) or (const MyType),
//      otherwise false.
// Invariants: None.
// Requirements on Types: None.
template<typename T>
class TypeCheck {

private:

    // No default ctor
    TypeCheck() = delete;

    // Uncopyable. Do not define copy/move ctor/assn.
    TypeCheck(const TypeCheck &) = delete;
    TypeCheck(TypeCheck &&) = delete;
    TypeCheck<T> & operator=(const TypeCheck &) = delete;
    TypeCheck<T> & operator=(TypeCheck &&) = delete;

    // Compiler-generated dctor is used (but irrelevant).
    ~TypeCheck() = default;

public:

    // check
    // The function and function template below simulate a single function
    // that takes a single parameter, and returns true iff the parameter has
    // type T or (const T).

    // check (reference-to-const T)
    // Pre: None.
    // Post:
    //     Return is true.
    // Does not throw (No-Throw Guarantee)
    static bool check(const T & param)
    { return true; }

    // check (reference-to-const non-T)
    // Pre: None.
    // Post:
    //     Return is false.
    // Requirements on types: None.
    // Does not throw (No-Throw Guarantee)
    template <typename OtherType>
    static bool check(const OtherType & param)
    { return false; }

};  // End class TypeCheck


// *********************************************************************
// Test Cases
// *********************************************************************


TEST_CASE( "Function return types are correct",
           "[types]" )
{
    Team t1;
    Team t2;

    // Copy assn returns Team
    SECTION( "Copy assn returns Team" )
    {
        REQUIRE( TypeCheck<Team>::check(t1 = t2) );
    }

    SECTION( "Team::getName returns string" )
    {
        REQUIRE( TypeCheck<string>::check(t1.getName()) );
    }
    
    SECTION( "Team::getWins returns int" )
    {
        REQUIRE( TypeCheck<int>::check(t1.getWins()) );
    }

    SECTION( "Team::toString returns string" )
    {
        REQUIRE( TypeCheck<string>::check(t1.toString()) );
    }

    SECTION( "Team::operator++ [pre] returns Team" )
    {
        REQUIRE( TypeCheck<Team>::check(++t1) );
    }
    
    SECTION( "Team::operator++ [post] returns Team" )
    {
        REQUIRE( TypeCheck<Team>::check(t1++) );
    }

    SECTION( "Team::operator-- [pre] returns Team" )
    {
        REQUIRE( TypeCheck<Team>::check(--t1) );
    }
    
    SECTION( "Team::operator-- [post] returns Team" )
    {
        REQUIRE( TypeCheck<Team>::check(t1--) );
    }
    
    SECTION( "operator==(Team,Team) returns bool" )
    {
        REQUIRE( TypeCheck<bool>::check(t1 == t2) );
    }
    
    SECTION( "operator!=(Team,Team) returns bool" )
    {
        REQUIRE( TypeCheck<bool>::check(t1 != t2) );
    }
    
    SECTION( "operator<<(ostream,Team) returns ostream" )
    {
        ostringstream ostr;
        REQUIRE( TypeCheck<ostream>::check(ostr << t1) );
    }
}


TEST_CASE( "Functions take const objects (passes if it compiles)",
           "[types]" )
{
    SECTION( "Taking const Team arguments" )
    {
        const Team tc1;
        const Team tc2;

        string s;
        int w;
        s = tc1.getName();       // Team::getName
        w = tc1.getWins();       // Team::getWins
        s = tc1.toString();      // Team::toString

        Team t3 = tc1;           // Copy ctor
        t3 = tc1;                // Copy assn

        bool b1 = (tc1 == tc2);  // op==(Team,Team)
        bool b2 = (tc1 != tc2);  // op!=(Team,Team)
        ostringstream ostr;
        ostr << tc1;             // op<<(ostring,Team)

        REQUIRE( 0 == 0 );       // Section passes if it compiles
    }

    SECTION( "Taking const string arguments" )
    {
        const string s;

        Team t(s, 0);            // Data ctor
        t.setName(s);            // Team::setName

        REQUIRE( 0 == 0 );       // Section passes if it compiles
    }
}


TEST_CASE( "Default-constructed Team object: blank name, 0 wins",
           "[objs]" )
{
    Team t1;

    REQUIRE( t1.getName() == "" );
    REQUIRE( t1.getWins() == 0 );

    SECTION( "Set name" )
    {
        t1.setName("abc");

        REQUIRE( t1.getName() == "abc" );
        REQUIRE( t1.getWins() == 0 );
    }

    SECTION( "Set wins" )
    {
        t1.setWins(20);

        REQUIRE( t1.getName() == "" );
        REQUIRE( t1.getWins() == 20 );
    }

    SECTION( "Set name, wins" )
    {
        t1.setName("def");
        t1.setWins(30);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getWins() == 30 );
    }

    SECTION( "Set wins, name" )
    {
        t1.setWins(40);
        t1.setName("ghi");

        REQUIRE( t1.getName() == "ghi" );
        REQUIRE( t1.getWins() == 40 );
    }
}


TEST_CASE( "Data-constructed Team object",
           "[objs]" )
{
    Team t1("xyz", 100);

    REQUIRE( t1.getName() == "xyz" );
    REQUIRE( t1.getWins() == 100 );

    SECTION( "Set name" )
    {
        t1.setName("abc");

        REQUIRE( t1.getName() == "abc" );
        REQUIRE( t1.getWins() == 100 );
    }

    SECTION( "Set wins" )
    {
        t1.setWins(20);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getWins() == 20 );
    }

    SECTION( "Set name, wins" )
    {
        t1.setName("def");
        t1.setWins(30);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getWins() == 30 );
    }

    SECTION( "Set wins, name" )
    {
        t1.setWins(40);
        t1.setName("ghi");

        REQUIRE( t1.getName() == "ghi" );
        REQUIRE( t1.getWins() == 40 );
    }
}


TEST_CASE( "Copied Team objects",
           "[objs]" )
{
    SECTION( "Copy-constructed Team object" )
    {
        Team t1("xyz", 100);
        Team t2 = t1;

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getWins() == 100 );
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getWins() == 100 );

        t2.setName("abc");
        t2.setWins(10);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getWins() == 100 );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getWins() == 10 );

        t1.setName("def");
        t1.setWins(20);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getWins() == 20 );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getWins() == 10 );
    }

    SECTION( "Copy-assigned Team object" )
    {
        Team t1("xyz", 100);
        Team t2;
        t2 = t1;

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getWins() == 100 );
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getWins() == 100 );

        t2.setName("abc");
        t2.setWins(10);

        REQUIRE( t1.getName() == "xyz" );
        REQUIRE( t1.getWins() == 100 );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getWins() == 10 );

        t1.setName("def");
        t1.setWins(20);

        REQUIRE( t1.getName() == "def" );
        REQUIRE( t1.getWins() == 20 );
        REQUIRE( t2.getName() == "abc" );
        REQUIRE( t2.getWins() == 10 );
    }
}


TEST_CASE( "String conversions",
           "[strings]" )
{
    Team t1;
    Team t2("xyz", 100);

    SECTION( "Team::toString" )
    {
        REQUIRE( t1.toString() == " [wins: 0]" );
        REQUIRE( t2.toString() == "xyz [wins: 100]" );
    }

    SECTION( "operator<<(ostream,Team)" )
    {
        ostringstream ostr1;
        ostr1 << t1;
        REQUIRE( ostr1.str() == " [wins: 0]" );
        ostringstream ostr2;
        ostr2 << t2;
        REQUIRE( ostr2.str() == "xyz [wins: 100]" );
    }
}


TEST_CASE( "Increment & decrement",
           "[operators]" )
{
    Team t1;
    Team t2("xyz", 10);

    SECTION( "Increment ordinary object" )
    {
        Team t3 = (++t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getWins() == 11 );
        REQUIRE( t3.getName() == "xyz" );
        REQUIRE( t3.getWins() == 11 );

        Team t4 = (t2++);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getWins() == 12);
        REQUIRE( t4.getName() == "xyz" );
        REQUIRE( t4.getWins() == 11 );

        ++(++t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getWins() == 14 );
    }

    SECTION( "Increment object with zero wins" )
    {
        ++t1;
        REQUIRE( t1.getName() == "" );
        REQUIRE( t1.getWins() == 1 );

        t1++;
        REQUIRE( t1.getName() == "" );
        REQUIRE( t1.getWins() == 2 );
    }

    SECTION( "Decrement ordinary object" )
    {
        Team t3 = (--t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getWins() == 9 );
        REQUIRE( t3.getName() == "xyz" );
        REQUIRE( t3.getWins() == 9 );

        Team t4 = (t2--);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getWins() == 8 );
        REQUIRE( t4.getName() == "xyz" );
        REQUIRE( t4.getWins() == 9 );

        --(--t2);
        REQUIRE( t2.getName() == "xyz" );
        REQUIRE( t2.getWins() == 6 );
    }

    SECTION( "Decrement object with zero wins" )
    {
        --t1;
        REQUIRE( t1.getName() == "" );
        REQUIRE( t1.getWins() == 0 );

        t1--;
        REQUIRE( t1.getName() == "" );
        REQUIRE( t1.getWins() == 0 );
    }
}


TEST_CASE( "Equality & inequality",
           "[operators]" )
{
    Team t1("abc", 10);  // Base value
    Team t2("abc", 10);  // Same
    Team t3("def", 10);  // Different name
    Team t4("abc", 20);  // Different wins
    Team t5("def", 20);  // Different name & wins

    SECTION( "Equality" )
    {
        REQUIRE( t1 == t1 );
        REQUIRE( t1 == t2 );
        REQUIRE( !(t1 == t3) );
        REQUIRE( !(t1 == t4) );
        REQUIRE( !(t1 == t5) );
    }

    SECTION( "Inequality" )
    {
        REQUIRE( !(t1 != t1) );
        REQUIRE( !(t1 != t2) );
        REQUIRE( t1 != t3 );
        REQUIRE( t1 != t4 );
        REQUIRE( t1 != t5 );
    }
}


TEST_CASE( "Large values",
           "[other]" )
{
    const size_t bigname_len = 1000001;
    string bigname = "";       // We make this into a long string
    for (size_t i = 0; i < bigname_len; ++i)
    {
        bigname.push_back('x');
    }

    int bigwins = 2147483641;  // Almost greatest 32-bit signed value

    ostringstream ostr;
    ostr << bigname << " [wins: " << bigwins << "]";
    string bigstringform = ostr.str();
                               // String form of Team(bigname, bigwins)

    SECTION( "Construction from large values" )
    {
        Team t1(bigname, bigwins);

        REQUIRE( t1.getName() == bigname );
        REQUIRE( t1.getWins() == bigwins );

        REQUIRE( t1.toString() == bigstringform );
    }

    SECTION( "Set functions, passing large values" )
    {
        Team t1;
        t1.setName(bigname);
        t1.setWins(bigwins);

        REQUIRE( t1.getName() == bigname );
        REQUIRE( t1.getWins() == bigwins );

        REQUIRE( t1.toString() == bigstringform );
    }
}

