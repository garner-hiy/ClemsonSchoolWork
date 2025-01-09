#include <string>
#include <stack>
#include <iostream>

using namespace std;

//Calculates a postfix expression with integer operands using a stack
//The expression is represented using an array of strings
//Each string is either an operand or operator symbol
//Operator symbols:
//"+" addition
//"-" subtraction
//"*" multiplication
//"/" divison
//"%" remainder
//Example expression: "8", "5", "-" evaluates to a result of 3:
//1: push 8, 2: push 5,
//3: "-"-> pop top two values, earlier value is the left-side operand: 8 - 5
//The result of the operation (8-5) is 3, push 3 onto stack
//After evaluation of the expression, the final result should be
//the only value on the stack, return 0 if the stack is
//non-empty after popping the result
//Return 0 if expression is zero-length or if there are insufficient operands
//for an operation
//The STL Stack class can be used
//To easily convert a numeric string to an int you may use the stoi() function
//which takes a string as a parameter and returns a string
int calculatePostfixExpression(string expression[], int length)
{
    stack <int> a;
    if(length == 0)
        return 0;
    for(int i = 0; i < length; i++){
        if(isdigit(expression[i][0])){
            a.push(stoi(expression[i]));
        }
        else{
            if(a.size() == 1 || a.empty()){
                return 0;
            }
            int temp = a.top();
            a.pop();
            int temp2 = a.top();
            a.pop();    

            switch(expression[i][0]){
                case '+':
                    a.push(temp + temp2);
                    break;
                case '-':
                    a.push(temp2 - temp);
                    break;
                case '*':
                    a.push(temp * temp2);
                    break;
                case '/':
                    a.push(temp2 / temp);
                    break;
                case '%':
                    a.push(temp2 % temp);
                    break;
            }     
        }
    }
    int tempLast = a.top();
    a.pop();
    if(a.empty()){
        return tempLast;
    }
    else{
        return 0;
    }
}