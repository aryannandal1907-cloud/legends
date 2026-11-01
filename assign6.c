#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX 100

// Character Stack structure using Array
struct CharStack {
    int top;
    char items[MAX];
};

// Integer Stack structure using Array
struct IntStack {
    int top;
    int items[MAX];
};

// --- Character Stack Functions ---
void initCharStack(struct CharStack* s) {
    s->top = -1;
}

int isCharFull(struct CharStack* s) {
    return s->top == MAX - 1;
}

int isCharEmpty(struct CharStack* s) {
    return s->top == -1;
}

void pushChar(struct CharStack* s, char val) {
    if (isCharFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->items[++(s->top)] = val;
}

char popChar(struct CharStack* s) {
    if (isCharEmpty(s)) {
        return '\0';
    }
    return s->items[(s->top)--];
}

char peekChar(struct CharStack* s) {
    if (isCharEmpty(s)) {
        return '\0';
    }
    return s->items[s->top];
}

// --- Integer Stack Functions ---
void initIntStack(struct IntStack* s) {
    s->top = -1;
}

int isIntFull(struct IntStack* s) {
    return s->top == MAX - 1;
}

int isIntEmpty(struct IntStack* s) {
    return s->top == -1;
}

void pushInt(struct IntStack* s, int val) {
    if (isIntFull(s)) {
        printf("Stack Overflow!\n");
        return;
    }
    s->items[++(s->top)] = val;
}

int popInt(struct IntStack* s) {
    if (isIntEmpty(s)) {
        return 0;
    }
    return s->items[(s->top)--];
}

// --- Operators and Precedence ---
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Convert Infix to Postfix
void infixToPostfix(char* infix, char* postfix) {
    struct CharStack s;
    initCharStack(&s);
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char c = infix[i];

        // Skip spaces and commas
        if (c == ' ' || c == ',') {
            i++;
            continue;
        }

        // If operand (alphanumeric), add to output
        if (isalnum(c)) {
            postfix[j++] = c;
        }
        else if (c == '(') {
            pushChar(&s, c);
        }
        else if (c == ')') {
            while (!isCharEmpty(&s) && peekChar(&s) != '(') {
                postfix[j++] = popChar(&s);
            }
            if (!isCharEmpty(&s) && peekChar(&s) == '(') {
                popChar(&s); // Remove '('
            }
        }
        else if (isOperator(c)) {
            while (!isCharEmpty(&s) && precedence(peekChar(&s)) >= precedence(c)) {
                if (c == '^' && peekChar(&s) == '^')
                    break;
                postfix[j++] = popChar(&s);
            }
            pushChar(&s, c);
        }
        i++;
    }

    while (!isCharEmpty(&s)) {
        postfix[j++] = popChar(&s);
    }
    postfix[j] = '\0';
}

// Evaluate Postfix Expression
int evaluatePostfix(char* postfix) {
    struct IntStack s;
    initIntStack(&s);
    int i = 0;

    while (postfix[i] != '\0') {
        char c = postfix[i];

        if (isdigit(c)) {
            pushInt(&s, c - '0'); // Convert character digit to integer value
        }
        else if (isalpha(c)) {
            printf("Error: Evaluation requires numeric operands (0-9), found variable '%c'.\n", c);
            return -99999;
        }
        else if (isOperator(c)) {
            if (isIntEmpty(&s)) {
                printf("Error: Invalid postfix expression.\n");
                return -99999;
            }
            int val2 = popInt(&s);
            if (isIntEmpty(&s)) {
                printf("Error: Invalid postfix expression.\n");
                return -99999;
            }
            int val1 = popInt(&s);
            int result = 0;

            switch (c) {
                case '+': result = val1 + val2; break;
                case '-': result = val1 - val2; break;
                case '*': result = val1 * val2; break;
                case '/': 
                    if (val2 == 0) {
                        printf("Error: Division by zero!\n");
                        return -99999;
                    }
                    result = val1 / val2; 
                    break;
                case '^': result = (int)pow(val1, val2); break;
            }
            pushInt(&s, result);
        }
        i++;
    }

    if (isIntEmpty(&s)) {
        printf("Error: Invalid expression.\n");
        return -99999;
    }
    return popInt(&s);
}

// --- Main Menu Driver ---
int main() {
    char infix[MAX] = "";
    char postfix[MAX] = "";
    int choice;
    int hasInfix = 0;
    int hasPostfix = 0;

    do {
        printf("\n=========================================\n");
        printf("   STACK-BASED INFIX/POSTFIX CALCULATOR  \n");
        printf("=========================================\n");
        printf("1. Enter Infix Expression\n");
        printf("2. Convert Infix to Postfix\n");
        printf("3. Evaluate Postfix Expression\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter infix expression (e.g., 5,+,3,*,2 or (5+3)*2): ");
                fgets(infix, sizeof(infix), stdin);
                infix[strcspn(infix, "\n")] = 0; // remove trailing newline
                hasInfix = 1;
                hasPostfix = 0;
                printf("Infix expression saved successfully!\n");
                break;

            case 2:
                if (!hasInfix) {
                    printf("Please enter an infix expression first (Option 1).\n");
                    break;
                }
                infixToPostfix(infix, postfix);
                hasPostfix = 1;
                printf("Postfix Expression: %s\n", postfix);
                break;

            case 3:
                if (!hasPostfix) {
                    if (!hasInfix) {
                        printf("Please enter an infix expression first (Option 1).\n");
                        break;
                    }
                    infixToPostfix(infix, postfix);
                    hasPostfix = 1;
                }
                printf("Postfix Expression: %s\n", postfix);
                int evalResult = evaluatePostfix(postfix);
                if (evalResult != -99999) {
                    printf("Evaluation Result: %d\n", evalResult);
                }
                break;

            case 4:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice! Please choose between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}
