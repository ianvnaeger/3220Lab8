#include <iostream>
#include <cstring>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class message {
	protected: 
		string msg;
		int length;
	
	public: 
		message( void );
		message( string );
		~message( void );
		void printInfo( void ); 	
};
// message class, is base for morse code class

class morseCodeMessage : public message{ 
	public:
		string *TrnsMsg;
		string mcm;
		int index; 
		morseCodeMessage(void);
		~morseCodeMessage(void);
		morseCodeMessage( string );
		void translate(void);
		void printInfo(void);
};
// morse code class

class messageStack 
{
	public:
		message *ptrStack[10];
		message *startStack;
		messageStack(void);
		//~messageStack(void);
		void push( message );
		void push( morseCodeMessage); 
		void pop(void);
		void printStack();
		//int stacktop();
		int num_of_objs;
		int k;
};
// class for stack

message::message(void)
{
	cout<<"Enter a word:"<<endl;
	cin>>msg;
	length = msg.length();
}// default constructor

message::message( string input )
{
	msg = input;
	length = msg.length();
}// constructor with and input

message::~message(void)
{
	//Nothing to deallocate
}// destructor with nothing, because no memory needs to be cleared

void message::printInfo(void)
{
	cout<<"Normal Word: "<<msg<<endl;
}// prints the og message

morseCodeMessage::morseCodeMessage(void) : message()
{
	TrnsMsg = new string[ length ];
	translate( ); 
}// defaultly constructs morse code, and calls translate

morseCodeMessage::morseCodeMessage( string input ) : message( input )
{
	TrnsMsg = new string[ length ];
	translate( ); 
}// constructs morse code with input, and calls translate

morseCodeMessage::~morseCodeMessage( void )
{
	delete[] TrnsMsg;
}// destructor for morse code


void morseCodeMessage::printInfo(void)
{
	cout<<"Normal Word: "<<msg<<endl;
	cout<<"Morse Code: "<<mcm<<endl;
}// prints both normal message and morse code

void morseCodeMessage::translate(void) 
{
	int i, j, k, check;
	string spacing = " ";
	string letters = "abcdefghijklmnopqrstuvwxyz123456789";
	string morse[36] =  {
	".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",
	".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--..",    ".----","..---", 
	"...--","....-",".....","-....","--...","---..","----.","-----" };	

	for( k=0; k < length; k++)
	{
		check = isupper( msg[k] );
		if( check == 1 )
		{
			msg[k] = (char)tolower(msg[k]);
		}
	}

	for( i=0; i < length; i++)
	{
		index = letters.find( msg[i] );
		TrnsMsg[i] = morse[index]; 
	}

	for( j=0; j < length; j++)
	{
		mcm.append(TrnsMsg[j]);
		mcm.append(spacing);
	}
	
}// changes everything to lower case, finds the letter in morse array, then adds morse code to arrray

void messageStack::printStack(){
	int j = 0;
	cout << "\n---STACK---\n" << endl;
	while(j < k)
	{
		cout << "Element " << j+1 << ":" << endl;
		ptrStack[j]->printInfo();
		j++;
	}
	cout << "\n\n" << endl;
}// prints out the stack

messageStack::messageStack(){
	k = 0;
	startStack = NULL;
}// default constructor for stack

void messageStack::push(message input)
{
	if(startStack == NULL);
	else{
		startStack = &input;
	}
	if(num_of_objs >= 10) return;
	else{
		ptrStack[k] = new message(input);
		k++;
	}
} // pushes normal message to stack

void messageStack::push(morseCodeMessage input)
{
	if(startStack == NULL);
	else{
		startStack = &input;
	}
	if(num_of_objs >= 10) return;
	else{
		ptrStack[k] = new morseCodeMessage(input);
		k++;
	}
} // pushes morse code to stack

void messageStack::pop()
{
	if(k == 0){
		cout << "Theres nothing to pop!" << endl;
		return;
	}
	delete ptrStack[k-1];
	k--;
} // pops and locks things from the stack



int main(void)
{
	message msg1;
	message msg2("Two");
	morseCodeMessage msg3;
	morseCodeMessage msg4("Four");
	
	cout<<endl<<"Printing Message 1..."<<endl;
	msg1.printInfo();
	
	cout<<endl<<"Printing Message 2..."<<endl;
	msg2.printInfo();
	
	cout<<endl<<"Printing Message 3..."<<endl;
	msg3.printInfo();
	
	cout<<endl<<"Printing Message 4..."<<endl;
	msg4.printInfo();
//	Demonstrates none stack portion of the lab
	
	int userSelect = 1000;
	int norVmor;
	messageStack msg5;
	
	while (userSelect != 0)
	{
		cout << "\n0: Exit\n1:PUSH message \n2:POP a message\n3: DISPLAY the stack" << endl;
		cin >> userSelect;
		switch(userSelect)
		{
			case 0:
				return 0;
				break;
			case 1:
				cout << "1. Normal message \n2. Morse Code" << endl;
				cin >> norVmor;
				if(norVmor == 1) 
				{	
					message tempMsg;
					msg5.push(tempMsg);
				}
				else 
				{
					morseCodeMessage tempMsg;
					msg5.push(tempMsg);
				}
				break;
			case 2:
				msg5.pop();
				break;
			case 3: 
				msg5.printStack();
				break;
			default:
				break;
		}
	}
// Demonstrates stack portion of the lab 
	return 0;
	
}