#include <stdio.h>
#include <stdlib.h>

#define MAX 100
int top = -1;
char stck[MAX];

struct stackNode{
    char data;
    struct stackNode *nextPtr;
};
typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

int isOperator(char c){
    /* determine if c is an operator */
    int determine;
    switch (c){
        case '^':
            determine = 3;
            break;
        case '*':
        case '/':
        case '%':
            determine = 2;
            break;
        case '+':
        case '-':
            determine = 1;
            break;
        default:
            determine = 0;
            break;
    }
    return determine;
}

int precedence(char operator1, char operator2){
    /* determine if the precedence of operator1 is less than (return -1), equal to (return 0), or greater than (return 1) the precednece of operator2 */
    int determine,
        precedence1 = isOperator(operator1),
        precedence2 = isOperator(operator2);
    if(((1 <= precedence1) && (precedence1 <= 3)) && ((1 <= precedence2) && (precedence2 <= 3))){
        if(precedence1 < precedence2){
            determine = -1;
        }
        else if(precedence1 == precedence2){
            determine = 0;
        }
        else if(precedence1 > precedence2){
            determine = 1;
        }
    }
    else{
        printf("either operator 1 or 2 are not operators.\n");
    }
    return determine;
}

void push(StackNodePtr *topPtr, char value){
    /* push a value on the stack */
    topPtr[++top]->data = value;
}

char pop(StackNodePtr *topPtr){
    /* pop a value off the stack */
    if(top > -1)
		return stck[top--];
	else
	{
		return 'f';
	}
}

char stackTop(StackNodePtr topPtr){
    /* return the top value of the stack without popping the stack */
    if(top > -1){
        return topPtr[top].data;
    }
	else{
		return 'f';
	}
}

int isEmpty(StackNodePtr topPtr){
    /* determine if the stack is empty */
    if(top == -1){
        return 1;
    }
	else{
        return 0;
    }
}

void convertToPostfix(char infix[], char postfix[]){
    /* convert the infix expression to postfix notation */
    StackNodePtr stack;

    int n = sizeof(*infix);
    int i,j=0;
	char res[MAX];
	for(i=0; i<n; i++){ 
		if(infix[i]=='0'||infix[i]=='1'||infix[i]=='2'||infix[i]=='3'||infix[i]=='4'||infix[i]=='5' ||infix[i]=='6'||infix[i]=='7'||infix[i]=='8'||infix[i]=='9'){
			res[j++]=infix[i];
		}
		else if(infix[i]=='('){
            push(&stack, infix[i]);
		}
		else if(infix[i]==')'){
			while(stackTop(&stack[top])!='(' && !isEmpty(&stack[top])){
				res[j++] = pop(&stack);
			}
			if(!isEmpty(&stack[top]) && stackTop(&stack[top]) != '('){
                return;
            }
			else{
                pop(&stack);
            }
		}
		else{
			while(!isEmpty(&stack[top]) && precedence(infix[i], '*') <= precedence(stackTop(&stack[top]))){
                res[j++]=pop();
            }
			push(stack[top], infix[i]);
		}
	}
	while(!isEmpty(stack[top])){
        res[j++] = pop(stack[top]);
    }
	for(i=0; i<j; i++){
        printf("%c",res[i]);
    }
}


void printStack(StackNodePtr topPtr){
    /* print the stack */
}

int main(void){
    char infix[] = "(6+2)*5-8/4\n\n", //"(1+2)*(3+4)" , "1+2*3+4" insert string without space
        postfix[];
	infixTopostfix(infix, postfix);
	return 0;
}