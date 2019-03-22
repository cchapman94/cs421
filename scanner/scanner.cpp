#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: **10 
//=====================================================

// --------- DFAs ---------------------------------

// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by:
// ** RE:
bool word(string s)
{
	int state = 0;
	int charpos = 0;

	while (s[charpos] != '\0')
	{
		if (state == 0 && s[charpos] == 'a')
			state = 1;
		else
		if (state == 1 && s[charpos] == 'b')
			state = 2;
		else
		if (state == 2 && s[charpos] == 'b')
			state = 2;
		else
			return(false);
		charpos++;
	}//end of while

	// where did I end up????
	if (state == 2) return(true);  // end in a final state
	else return(false);
}

// ** Add the PERIOD DFA here
// ** Done by: Chantell Chapman
bool periodDFA(string s)
{
	/*
	if (s[0] == '.')
		return true;
	else
		return false;
	*/

	int state = 0;
	int charpos = 0;

	while (s[charpos] != '\0') {
		if (state == 0 && (s[charpos] == '.'))
			state = 1;
		else
			return (false);
		charpos++;
	}

	if (state == 1) return (true);
	else return (false);
}


// -----  Tables -------------------------------------

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype { WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM, ERROR };//enum tokentype { ERROR, };

// ** string tokenName[30] = { }; for the display names oftokens - must be in the same order as the tokentype.
string tokenName[30] = { "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM", "ERROR" };

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this.
// ** a.out should work without any additional files.


string reservedwords[20][2] =
{
  {	"masu", "VERB"},
  { "masen", "VERBNEG"},
  {	"mashita", "VERBPAST"},
  { "masendeshita", "VERBPASTNEG"},
  {	"desu", "IS"},
  {  "deshita", "WAS"},
  {	"o", "OBJECT"},
  {  "wa", "SUBJECT"},
  {	"ni", "DESTINATION"},
  {  "watashi", "PRONOUN"},
  {	"anata", "PRONOUN"},
  {	"kare", "PRONOUN"},
  {	"kanojo", "PRONOUN"},
  { "sore", "PRONOUN"},
  { "mata", "CONNECTOR"},
  {"soshite", "CONNECTOR"},
  {"shikashi", "CONNECTOR"},
  {	"dakara", "CONNECTOR"},
  {	"eofm", "EOFM"}

};

// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Julian Conner,
int scanner(tokentype& a, string& w)
{

  string currentWord; // To store the word for readability during processing
  string endOfFileWord = reservedwords[18][0]; // Used for readability
  bool isEndOfFile; 

	// ** Grab the next word from the file via fin
	// 1. If it is eofm, return right now.   
  isEndOfFile = fin.eof();

  // Check if the file stream is empty
  if( isEndOfFile ) {
    a = EOFM;
    w = endOfFileWord;
    
    return -1;
  }

  
  // Get the next word for processing
  fin >> currentWord;

  // To return the word by reference 
  w = currentWord;

  // Check if the last word is the end of file message
  isEndOfFile = currentWord.compare( endOfFileWord) == 0;

  if( isEndOfFile ){

    a = EOFM;

    return 0;
  }

        
	/*
	2. Call the token functions one after another (if-then-else)
	And generate a lexical error message if both DFAs failed.
	Let the token_type be ERROR in that case.
 
	*/

  /*
	4. Return the token type & string  (pass by reference)
	*/

  // Check if its a valid word
  if( word( currentWord )  ) {

  /*
	3. Then, make sure WORDs are checked against the reservedwords list
	If not reserved, token_type is WORD1 or WORD2.
  */

    // FOR DANIEL : (Note : The test labels all words as errors because there's no implementation here for the word check yet. It works for periods and end of files. )

    }

    // Check if its a period
    else if ( periodDFA( currentWord ) ) {

      a = PERIOD;
  }

    // If the word wasn't a valid token, show a lexical error
  else {

    a = ERROR;
    cout << "LEXICAL ERROR : \"" << currentWord << "\" is not a valid token."
         << endl;
  }


   
}//the end of scanner



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Rika
int main()
{
	tokentype thetype;
	string theword;
	string filename;

	cout << "Enter the input file name: ";
	cin >> filename;

	fin.open(filename.c_str());

	// the loop continues until eofm is returned.
	while (true)
	{
		scanner(thetype, theword);  // call the scanner
		if (theword == "eofm") break;  // stop now

		cout << "Type is:" << tokenName[thetype] << endl;
		cout << "Word is:" << theword << endl;
	}

	cout << "End of file is encountered." << endl;
	fin.close();

}// end
