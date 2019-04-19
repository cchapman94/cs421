#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// INSTRUCTION:  Complete all ** parts.
// You may use any method to connect this file to scanner.cpp
// that you had written.  
// You can copy scanner.cpp here by cp ../ScannerFiles/scanner.cpp . and do 
// cat scanner.cpp parser.cpp > myparser.cpp
// -----------------------------------------------------

//=================================================
// File parser.cpp written by Group Number: **10
//=================================================

// ----- Utility and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:



// ** Need the updated match and next_token (with 2 global vars)
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:


// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// i.e. Grammar: 
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:


//---------------------------------------

// The new test driver to start the parser
// Done by:  **Chantell Chapman
int main()
{
  string filename; 

  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

//-----syntax error EC------

//ask user if they want to trace error messages
//get user input
  //if file 
  errorfile.open("errors.txt", ios::app); //errors.text of messages

  //** calls the <story> to start parsing
    story();
//** closes the input file 
  errorfile.close(); //close errors file
  fin.close();

}// end
//** require no other input files!
//** syntax error EC requires producing errors.text of messages

