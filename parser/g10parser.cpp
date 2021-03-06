#include<iostream>
#include<fstream>
#include<string>
#include <stdlib.h>
#include <stdio.h>
#include"scanner.cpp"
using namespace std;

//Global Variables
bool token_available = false; 
tokentype saved_token;
string saved_lexeme;
ofstream errorfile; 
string choice; 

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
// i.e. Done by: Julian Conner

enum parser_function { STORY, S, AFTER_SUBJECT, AFTER_NOUN, AFTER_OBEJCT, VERB1, TENSE, NOUN, BE };
string parserName[30] = { "story", "s", "after subject", "after noun", "after obejct", "verb", "tense", "noun", "be" };


void syntaxError1(tokentype expected)
{
  cout << endl << "SYNTAX ERROR: expected " << tokenName[expected] << " but found " << saved_lexeme << endl;


}

void syntaxError2(parser_function function)
{
  cout << endl << "SYNTAX ERROR: unexpected " << saved_lexeme << " found in " << parserName[function] << endl;
  exit(1);
}


// ** Need the updated match and next_token (with 2 global vars)
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:Daniel Caballero

tokentype next_token()
{
  if (!token_available)   // if there is no saved token yet
    { 
      scanner(saved_token, saved_lexeme);  // call scanner to grab a new token
      token_available = true; // mark that fact that you have saved it
    }
  return saved_token;    // return the saved token

}

bool match(tokentype expected)
{
  if (next_token() != expected)  // mismatch has occurred with the next token
    { // calls a syntax error function here to  generate a syntax error message here and do recovery
    syntaxError1(expected);
    

    //Extra Credit: skip token or assume correct token was there
    //done by: Chantell Chapman
    if (errorfile.is_open())
    {
      errorfile << "SYNTAX ERROR: expected " << tokenName[expected] << " but found " << saved_lexeme << "\n"; 
    }

    cout << "Skip or replace the token? (s or r) ";
    cin >> choice;

  
    if (choice == "s") 
    {
      token_available = false;
      match(expected);
    }

    else if (choice == "r")
    {
      token_available = false;
      cout << "Matched " << tokenName[expected] << endl;
    }
    
    
    }//end of if (next_token() != expected)
  
  else  // match has occurred
    {   token_available = false;  // eat up the token
      cout << "Matched " << tokenName[expected] << endl;

      return true;              // say there was a match
    }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// i.e. Grammar: 
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

//Done by: Julian Conner
// 10. Grammar: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
void tense()
{
    cout << "Processing <tense> " << endl;
   
    switch (next_token()) 
   {
      case VERBPAST:
  match(VERBPAST);
  break;
      case VERBPASTNEG:
  match(VERBPASTNEG);
  break;
      case VERB:
  match(VERB);
  break;
      case VERBNEG:
  match(VERBNEG);
  break;          
      default:
       syntaxError2(TENSE);     

    }
}

// Done By : Julian Conner
// 9. Grammar: <be> ::= IS | WAS
void be()
{

   cout << "Processing <be>" << endl;
  
   switch (next_token())
  {
    case IS:
      match(IS);
      break;
    case WAS:
      match(WAS);
      break;    
    default:
      syntaxError2(BE);
  }

}

// Done By : Julian Conner
// 8. Grammar: <verb> ::= WORD2
void verb()
{

  cout << "Processing <verb>" << endl;
  match(WORD2);
  
}

//Done by:Daniel Caballero
// 7. Grammar: <noun> ::= WORD1 | PRONOUN
void noun()
{
  cout << "Processing <noun>" << endl;

  switch(next_token())
    {
    case WORD1:
      match(WORD1);
      break;
    case PRONOUN:
      match(PRONOUN);
      break;
    default:
      syntaxError2(NOUN);

    }//end Swtich
}//end noun

//Done by:Daniel Caballero
// 6. Grammar: <after_object> ::= <noun> DESTINATION <verb> <tense> PERIOD | <verb> <tense> PERIOD
void after_object()
{
  cout << "Processing <afterObject>" << endl; 

    switch(next_token())
      {
      case WORD1: case PRONOUN: 
  noun();     
  match(DESTINATION);
  verb();
  tense();
  match(PERIOD);
  break;
      case WORD2:
  verb();     
  tense();
  match(PERIOD);
  break;
      default:
  syntaxError2(AFTER_OBEJCT);
    
      }//end swtich

}//end after object


//Done by:Daniel Caballero
// Grammar: <after noun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <after obejct>
void after_noun()
{
  cout << "Processing <afterNoun>" << endl;
  switch(next_token())
    {
    case IS: case WAS:

      be();
      match(PERIOD);
      break;
    case DESTINATION:
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;
    case OBJECT:
      match(OBJECT);
      after_object();
      break;

    default:
      syntaxError2(AFTER_NOUN);

    }//end switch

}//end after_noun


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

//Done by: Chantell Chapman
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

//Done by: Chantell Chapman
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
//write error messages to error.txt
  cout << "Would you like to trace error messages? (y or n)"; //ask user if they want to trace error messages
  cin >> choice; //get user input
  if (choice == "y")
  {
      errorfile.open("errors.txt", ios::app); //errors.text of messages
  }

  //** calls the <story> to start parsing
  story();
  //** closes the input file 
  errorfile.close(); //close errors file
  fin.close();

}// end
//** require no other input files!
//** syntax error EC requires producing errors.text of messages
