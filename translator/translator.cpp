#include<iostream>
#include<fstream>
#include<string>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

// INSTRUCTION:  copy and edit your parser.cpp to create this file.
// cp ../ParserFiles/parser.cpp .
// Complete all ** parts.
// --------------------------------------------------------

//=================================================
// File translator.cpp written by Group Number: **10
//=================================================


// ----- Changes to the parser.cpp ---------------------

// ** Declare dictionary that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation
// Do not change the format or content of lexicon.txt 

// ** Additions to parser.cpp here:
//    getEword - using the current lexeme, look up the English word
//               in the Lexicon if it is there -- save the result   
//               in saved_E_word
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)

// ** Be sure to put the name of the programmer above each function

// ** Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 
// ** Each non-terminal function should be calling
//    getEword and/or gen now.


//----File parser.cpp that needs to be updated------------
bool token_available = false; 
tokentype saved_token;
string saved_lexeme;
ofstream errorfile; 
string choice; 
string saved_E_word;
ofstream translatedfile;
string Jap[47];
string Eng[47];

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



//** Additions to parser.cpp here:

//Done by: Daniel Caballero
//    getEword - using the current lexeme, look up the English word
//               in the Lexicon if it is there -- save the result   
//               in saved_E_word

void getEword()
{
  int i=0;
  while(i<Jap.size()){
    if(Jap[i]==saved_lexeme){
      saved_lexeme=Eng[i];
      break;
    }//end if
    i++;
  }//end while
return;

}




//Done by: 
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)

void gen(string line_type)
{

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

// ** Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 
// ** Each non-terminal function should be calling
//    getEword and/or gen now.

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

//--------start updating to new grammer rules here------------
//Done by:
// (OLD) Grammar: <after_object> ::= <noun> DESTINATION <verb> <tense> PERIOD | <verb> <tense> PERIOD

// Grammar: <after_object> ::= <noun> #getEword# DESTINATION #gen("TO")# <verb> #getEword# #gen("ACTION")# 
//<tense> #gen("TENSE")# PERIOD 
//                             | <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD
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


//Done by: Daniel Caballero
// (OLD) Grammar: <after noun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <after obejct>
// Grammar: <after noun> ::= <be> #gen("DESCRIPTION")# #gen("TENSE")# PERIOD | DESTINATION #gen("TO") 
//     <verb> #getEword# #gen("ACTION)# <tense> #gen("TENSE")# PERIOD 
//                           | OBJECT #gen("OBJECT")# <after obejct>
void after_noun()
{
  cout << "Processing <afterNoun>" << endl;

  switch(next_token())
    {
    case IS: case WAS:

      be();
      gen(DESCRIPTION);
      gen(TENSE);
      match(PERIOD);
      break;

    case DESTINATION:
      match(DESTINATION);
      gen(TO);
      verb();
      getEword();
      gen(ACTION);
      tense();
      gen(TENSE);
      match(PERIOD);
      break;

    case OBJECT:
      match(OBJECT);
      gen(OBJECT);
      after_object();
      break;

    default:
      syntaxError2(AFTER_NOUN);

    }//end switch

}//end after_noun


//Done by: Chantell Chapman
// (OLD) Grammar: <after subject>::= <verb> <tense> PERIOD | <noun> <after noun>
// Grammar: <after subject>::= <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD |
//                             <noun> #getEWord# <after noun>
void after_subject() 
{
  cout << "Processing <afterSubject>" << endl;

  switch (next_token())
    {
    case WORD2:
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;

    case WORD1: case PRONOUN:
      noun();
      getEword();
      after_noun();
      break;

    default:
      syntaxError2(AFTER_SUBJECT);
    }
}

//Done by: Chantell Chapman
// (OLD)Grammar: <s>::= [CONNECTOR] <noun> SUBJECT <after subject>
// Grammar: <s>::= [CONNECTOR #getEword# #gen("CONNECTOR")#] <noun> #getEword# SUBJECT
//                 #gen("ACTOR")# <after subject>
void s() 
{
  cout << "Processing <s>" << endl;
  
  switch (next_token()) 
    {
    case CONNECTOR:
      match(CONNECTOR);
      getEword();
      gen("CONNECTOR");
      noun();
      getEword();

      match(SUBJECT);
      gen("ACTOR");
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



// -------------------------------------------

// The final test driver to start the translator
// Done by  **Chantell Chapman
int main()
{
  //** opens the lexicon.txt file and reads it in
  //** closes lexicon.txt 
  ifstream dictionary;
  dictionary.open("lexicon.txt");

  for(int i =0; i < 47; i++)
    {
      dictionary >> Jap[i]; //Japanese words
      dictionary >> Eng[i]; //English words
    }

  //** opens the output file translated.txt
  translatedfile.open("translated.txt");

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
  //closes error file for EC
  errorfile.close();
  //** closes the input file 
  dictionary.close();
  //** closes traslated.txt
  translatedfile.close();

}// end
