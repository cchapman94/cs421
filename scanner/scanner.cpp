
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: **10 
//=====================================================

// --------- DFAs ---------------------------------

//Purpose: check to see if it's a vowel
//Done by: Daniel Caballero
bool vowelCheck(char c)
{
  switch(c){
  case 'a':
  case 'i':
  case 'I':
  case 'u':
  case 'e':
  case 'E':
  case 'o':
    //cout<<"vowel check"<<endl;
    return true;
    break;
  default:
    return false;
  }
}

//Purpose: Check consonant Pairs
//Done by Daniel Caballero
bool checkConsPairs(string s, int &charpos, int& state)
{
  
  char c = s[charpos];
  //  cout<<s[charpos]<<" ss"<<endl;
  switch (c) 
    {
    case 'b':
    case 'm':
    case 'k':
    case 'n':
    case 'h':
    case 'p':
    case 'r':
    case 'y':
    case 'g':
      if (vowelCheck(s[charpos+1]))
	{
	  state=6;
	  return true;
	}
      else if (s[charpos+1]== 'y')
	{
	  state=4;
	  charpos++;
	  return true;
	}
    
      break;
    case 's':
      if (vowelCheck(s[charpos+1]))
        {
	  //	  cout<< endl << s[charpos+1];
          state=6;
          return true;
        }
      else if (s[charpos+1]== 'h')
        {
          state=4;
          charpos++;
          return true;
        }
      break;
    case 't':
      if (vowelCheck(s[charpos+1]))
        {
          state=6;
          return true;
        }
      else if (s[charpos+1]== 's')
        {
          state=4;
          charpos++;
          return true;
        }
      break;
    default:
      return false;
    }
  return false;
}




// ** MYTOKEN DFA to be replaced by the WORD DFA
// ** Done by:Daniel Caballero, Julian Conner
// ** RE: (vowel | vowel n | consonant vowel | consonant vowel n | consonant-pair vowel | consonant-pair vowel n)^+
bool word(string s)
{
  int state = 0;
  int charpos = 0;
  int tempState=0;
  while (s[charpos] != '\0')
    {
      if ( ( (state== 6) && (s[charpos+1] == 'n')) )
	state =6;    
      else if ( state == 6 && s[charpos] == 'n' )
	state = 0;
      else if ( state == 6) {
	state = 0;
      }
      else if (state == 0 && s[charpos] == 't')
        state = 3;
      else if (state == 0 && s[charpos] == 's')
        state = 2;
      else if (state == 0 && s[charpos] == 'c')
        state = 1;
      else if ((state == 0) && (vowelCheck(s[charpos])==true))
	{
	  if( s[charpos+1] == 'n'){
	  //	  cout<<"\t"<<vowelCheck(s[charpos])<<endl;
	  state=6;
	  }

	  else {
	    state = 0;
	  }
	}
      else if ((state == 0) && (checkConsPairs(s,charpos,tempState)==true))
        state=tempState;
      else if (state == 0 && s[charpos] == 'j')
        state = 5;
      else if(state == 0 && s[charpos] == 'z')
        state = 5;
      else if (state == 0 && s[charpos] == 'd')
        state = 5;
      else if (state == 0 && s[charpos] == 'w')
        state = 5;
      else if(state == 0 && s[charpos] == 'y')
	state =5;

      // q0 to qY(state 4) by bmknhpr
      else if ( state == 0 && ( s[charpos] == 'b' || s[charpos] == 'm'
				|| s[charpos] == 'k' || s[charpos] == 'n'
				|| s[charpos] == 'h' || s[charpos] == 'p'
				|| s[charpos] == 'r' )  ){

		  state = 4;
      }
      else if (state ==5 && vowelCheck(s[charpos]))
      
	{

	  if( s[charpos+1] == 'n'){
	  state=6;
	  }

	  else {

	    state = 0;
		}

	}
      else if (state ==5 && s[charpos]=='s')
	state =6;
      else if (state ==5 && s[charpos]=='a')
	state=6;
      else if (state == 4 && vowelCheck(s[charpos]))
	{
	  if( s[charpos+1] == 'n'){
	  state=6;
	  }

	  else {

	    state = 0;
		}

	}
      else if (state == 4 && s[charpos]== 'y')
	state =5;
      else if (state == 3 && s[charpos] == 's')
	state=5;
      else if (state == 3 && vowelCheck(s[charpos]))
	{
	  if( s[charpos+1] == 'n'){
	  state=6;
	  }

	  else {

	    state = 0;
		}
	} 
     else if (state == 2 && s[charpos] == 'h')
	state=5;
      else if (state == 2 && vowelCheck(s[charpos]))
	{
	  if( s[charpos + 1] == 'n'){

	    state = 6;
	  }

	  else {
		state = 0;
		}

	}      
      else if (state == 1 && s[charpos] == 'h')
	state=5;
      else 
	return(false);
      charpos++;
      //cout<<state<<endl;
    }//end of while

  // where did I end up????
  if ((state == 6) || (state == 0)) return(true);  // end in a final state
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

const int rIndexA=19;
const int rIndexB=2;
string reservedWords[rIndexA][rIndexB] =
  {
    {"masu", "VERB"},
    { "masen", "VERBNEG"},
    {"mashita", "VERBPAST"},
    { "masendeshita", "VERBPASTNEG"},
    {"desu", "IS"},
    {  "deshita", "WAS"},
    {"o", "OBJECT"},
    {  "wa", "SUBJECT"},
    {"ni", "DESTINATION"},
    {  "watashi", "PRONOUN"},
    {"anata", "PRONOUN"},
    {"kare", "PRONOUN"},
    {"kanojo", "PRONOUN"},
    { "sore", "PRONOUN"},
    { "mata", "CONNECTOR"},
    {"soshite", "CONNECTOR"},
    {"shikashi", "CONNECTOR"},
    {"dakara", "CONNECTOR"},
    {"eofm", "EOFM"}

  };

// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Julian Conner,
int scanner(tokentype& a, string& w)
{

  string currentWord; // To store the word for readability during processing
  string endOfFileWord = reservedWords[18][0]; // Used for readability
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
    //START Daniel Section
    bool reservedFlag=false;
    for (int i=0;i<rIndexA;i++){
      if (currentWord==reservedWords[i][0]){
	if (reservedWords[i][1]==tokenName[3])
	  a=VERB;
	else if (reservedWords[i][1]==tokenName[4])
	  a=VERBNEG;
	else if (reservedWords[i][1]==tokenName[5])
	  a=VERBPAST;
	else if (reservedWords[i][1]==tokenName[6])
	  a=VERBPASTNEG;
	else if (reservedWords[i][1]==tokenName[7])
	  a=IS;
	else if (reservedWords[i][1]==tokenName[8])
	  a=WAS;
	else if (reservedWords[i][1]==tokenName[9])
	  a=OBJECT;
	else if (reservedWords[i][1]==tokenName[10])
	  a=SUBJECT;
	else if (reservedWords[i][1]==tokenName[11])
	  a=DESTINATION;
	else if (reservedWords[i][1]==tokenName[12])
	  a=PRONOUN;
	else if (reservedWords[i][1]==tokenName[13])
	  a=CONNECTOR;
	reservedFlag=true;
	  }
    }
    if (((currentWord[currentWord.length()-1] <=90)) && ((currentWord[currentWord.length()-1]>=65)&& reservedFlag==false))//uppercase
	a=WORD2;
    else if (reservedFlag==false) 
	a=WORD1;	
	  
    

  }//end DANIEL SECTION

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
      cout << "Word is:" << theword << endl<<endl;
    }

  cout << "End of file is encountered." << endl;
  fin.close();

}// end
