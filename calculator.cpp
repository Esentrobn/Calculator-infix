
#include <iostream>
#include<exception>
#include<stdexcept>
#include <string>
#include "LinkedStack.cpp"

using namespace std;



// Simply determine if character is one of the four standard operators.
bool isOperator(char character) {
	if (character == '+' || character == '-' || character == '*' || character == '/') {
		return true;
	}
	return false;
}


// If the character is not an operator or a parenthesis, then it is assumed to be an operand.
bool isOperand(char character) {
	if (!isOperator(character) && character != '(' && character != ')') {
		return true;
	}
	return false;
}


// Compare operator precedence of main operators.
// Return 0 if equal, -1 if op2 is less than op1, and 1 if op2 is greater than op1.
int compareOperators(char op1, char op2) {
	if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-')) { return -1; }
	else if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) { return 1; }
	return 0;
}

//resset stack

bool resetS(StackInterface<char>* stackPtrT){
	while (!stackPtrT->isEmpty()) { //loop through the array
		stackPtrT->pop();
	}
	return true;
}
int main()
{

	cout << "\tThis program does infix calculation\n" << endl;

	StackInterface<char>* stackPtrT = new LinkedStack<char>(); //testing for well formed infix
	StackInterface<char>* stackPtr = new LinkedStack<char>(); // for converting infix to postfix
	StackInterface<char>* stackPtrE = new LinkedStack<char>(); //evaluating postfix
	char infix[100], repeat;
	// Get a pointer to our character array.
	char *cPtr = infix;
	double op1, op2, resl;
	bool correctEx = false, redo = false, difC = true;
	string postFixS = "";
	int x = 0, y = 1;
	/*try{
		cout<<y / x;
	}
	catch (exception e)
	{
		cout << "Something else was caught" << endl;
	}*/


	do{
		// reseting all stacks
		resetS(stackPtrT);
		resetS(stackPtr);
		resetS(stackPtrE);
		postFixS = "";
		do{
			difC = true;
			cPtr = &infix[0];// resetting the array 
			cout << "enter your Expression: ";
			cin >> infix;
			
			
			// checking if the parenthesis in the expression are balanced
			while (*cPtr != '\0') { //loop through the array
				if (*cPtr == '(')
					stackPtrT->push(*cPtr);
				else if (*cPtr == ')')
					stackPtrT->pop();
				cPtr++;
			}
			if (!stackPtrT->isEmpty())
			{
				cout << "please re";
				resetS(stackPtrT);
				correctEx = false;
				continue;
			}


			cPtr = &infix[0];// resetting the array 
			// check for characters specified other than requested
			while (*cPtr != '\0') {
				if (!isdigit(*cPtr) != 0 && !isOperator(*cPtr))
				{
					difC = false;
					break;
				}
				cPtr++;
			}
			
			if (!difC)
			{
				cout << "please re";
				resetS(stackPtrT);
				correctEx = false;
				continue;
			}

			


			cPtr = &infix[0];// resetting the array 
			// check for well-formed expression
			while (*cPtr != '\0') {
				if (isOperand(*cPtr))
					stackPtrT->push(*cPtr);
				else if (isOperator(*cPtr))
					stackPtrT->pop();
				cPtr++;
			}

			if (!stackPtrT->isEmpty())
			{
				if (isOperand(stackPtrT->peek()))
					correctEx = true;
			}
			else
			{
				cout << "please re";
				resetS(stackPtrT);
			}

		} while (!correctEx);
		cout << stackPtrT->search('6');
		cPtr = &infix[0];// resetting the array 
		// Loop through the array (one character at a time) until we reach the end of the string.
		while (*cPtr != '\0') {
			// If operand, simply add it to our postfix string.
			// If it is an operator, pop operators off our stack until it is empty, an open parenthesis or an operator with less than or equal precedence.
			if (isOperand(*cPtr)) { postFixS += *cPtr; }
			else if (isOperator(*cPtr)) {
				while (!stackPtr->isEmpty() && stackPtr->peek() != '(' && compareOperators(stackPtr->peek(), *cPtr) <= 0) {
					postFixS += stackPtr->peek();
					stackPtr->pop();
				}
				stackPtr->push(*cPtr);
			}
			// Simply push all open parenthesis onto our stack
			// When we reach a closing one, start popping off operators until we run into the opening parenthesis.
			else if (*cPtr == '(') { stackPtr->push(*cPtr); }
			else if (*cPtr == ')') {
				while (!stackPtr->isEmpty()) {
					if (stackPtr->peek() == '(') { stackPtr->pop(); break; }
					postFixS += stackPtr->peek();
					stackPtr->pop();
				}
			}

			// Advance our pointer to next character in string.
			cPtr++;
		}

		// After the input expression has been ran through, if there is any remaining operators left on the stack
		// pop them off and put them onto the postfix string.
		while (!stackPtr->isEmpty()) {
			postFixS += stackPtr->peek();
			stackPtr->pop();
		}


		// Show the postfix string at the end.
		cout << "Postfix Expression is: " << postFixS << endl;

		for (int i = 0; i < postFixS.length(); i++)
		{
			if (isOperand(postFixS[i]))
				stackPtrE->push(postFixS[i]);
			else{
				op1 = stackPtrE->peek() - '0';
				stackPtrE->pop();
				op2 = stackPtrE->peek() - '0';
				stackPtrE->pop();
				switch (postFixS[i])
				{
				case '+':
					resl = op2 + op1;
					break;
				case '-':
					resl = op2 - op1;
					break;
				case '*':
					resl = op2 * op1;
					break;
				case '/':
					resl = op2 / op1;
					break;
				}
				stackPtrE->push(resl + 48);
			}
		}
		cout << "The result is: " << stackPtrE->peek() - '0' << endl;

		cout << "\nWould you like to do another expression? \nif yes, enter y or Y; or hit any other key quit ";
		cin >> repeat;
		if (repeat == 'Y' || repeat == 'y')
			redo = true;
		else
			redo = false;
	} while (redo);
	return 0;
}