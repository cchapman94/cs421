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

//beginning of scanner
//=====================================================
// File scanner.cpp 
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
    //    cout<< endl << s[charpos+1];
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
    //    cout<<"\t"<<vowelCheck(s[charpos])<<endl;
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
  
  cout << "Scanner called using word: " << w << endl;


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
    cout << "LEXICAL ERROR: \"" << currentWord << "\" is not a valid token."
         << endl;
  }


   return 0;
}//the end of scanner

//beginning of parser 
//=================================================
// File parser.cpp 
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
  for (int i = 0; i < 47; i++) 
  {
    if (saved_lexeme == Jap[i]) 
    {
      saved_E_word = Eng[i];
      return;
    }
  }
  saved_E_word = saved_lexeme;
  return;
}


//Done by: Julian Conner
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)

void gen(string line_type)
{

if(line_type == "TENSE")

{
  translatedfile << "TENSE: " << tokenName[saved_token] << endl <<endl;
}

else 
{
  translatedfile << line_type << ": " << saved_E_word << endl;
}

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

// Done By : Daniel Caballero
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
//Done by: Julian Conner
// Grammar: <after_object> ::= <noun> #getEword# DESTINATION #gen("TO")# <verb> #getEword# #gen("ACTION")# 
//                            <tense> #gen("TENSE")# PERIOD 
//                             | <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD
void after_object()
{
  cout << "Processing <afterObject>" << endl; 

  switch(next_token())
    {
    case WORD1: case PRONOUN: 
      noun();     
      getEword();
      match(DESTINATION);
      gen("TO");
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;
     
    case WORD2:
      verb();     
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;
     
    default:
      syntaxError2(AFTER_OBEJCT);
    
    }//end swtich

}//end after object


//Done by: Daniel Caballero
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
      gen("DESCRIPTION");
      gen("TENSE");
      match(PERIOD);
      break;

    case DESTINATION:
      match(DESTINATION);
      gen("TO");
      verb();
      getEword();
      gen("ACTION");
      tense();
      gen("TENSE");
      match(PERIOD);
      break;

    case OBJECT:
      match(OBJECT);
      gen("OBJECT");
      after_object();
      break;

    default:
      syntaxError2(AFTER_NOUN);

    }//end switch

}//end after_noun


//Done by: Chantell Chapman
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

    default:
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
  //closes error file for EC
  errorfile.close();
  //** closes the input file 
  dictionary.close();
  //** closes traslated.txt
  translatedfile.close();

  //** Closes the input file stream
  fin.close();
}// end
