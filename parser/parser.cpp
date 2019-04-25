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

//Done by:
// 10. Grammar: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG


// 9. Grammar: <be> ::= IS | WAS


// 8. Grammar: <verb> ::= WORD2



//Done by:
// 7. Grammar: <noun> ::= WORD1 | PRONOUN


// 6. Grammar: <after_object> ::= <noun> DESTINATION <verb> <tense> PERIOD | <verb> <tense> PERIOD


// Grammar: <after noun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <after obejct>



//Done by: Chantell Chapman
// Grammar: <after subject>::= <verb> <tense> PERIOD | <noun> <after noun>
void after_subject() 
{
	cout << "Processing <afterSubject>" << endl;
	switch (next_token())
	{
	case WORD2:
		verb();
		tense();
		match(PERIOD);
		break;
	case WORD1: case PRONOUN:
		noun();
		after_noun();
		break;
	default:
		syntaxError2(AFTER_SUBJECT);
	}
}

// Grammar: <s>::= [CONNECTOR] <noun> SUBJECT <after subject>
void s() 
{
	cout << "Processing <s>" << endl;
	switch (next_token()) 
	{
	case CONNECTOR:
		match(CONNECTOR);
		noun();
		match(SUBJECT);
		after_subject();
		break;
	default:
		noun();
		match(SUBJECT);
		after_subject();
		break;
	}
}

// Grammar: <story> ::= <s> {<s>}
// stay in the loop as long as a possible start 
void story() 
{
	cout << "Processing <story>" << endl << endl;
	s();
	while (true)
  {
		if (next_token() == EOFM)
    {
			cout << endl << "Successfully parsed <story>." << endl;
			break;
		}
		s();
		
	}
}

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

