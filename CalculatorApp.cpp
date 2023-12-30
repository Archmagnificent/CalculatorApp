#include <iostream>
#include <array>

namespace ooc //Namespace containing all of the data relating to the order of operations
{
    enum Operators
    {
        exponents,
        multiply,
        divide,
        add,
        subtract,
        max_operators
    };

    std::array<char, max_operators> operators          { '^', '*', '/', '+', '-'};  //An array storing operators
    std::array<int, max_operators>  operatorPrecedence {1, 2, 3, 4, 5};             //An array storing operators order

    bool operatorHigher(char left, char right) //Function that uses previous and currently chosen operator to determine whether the left or right operation should be calculated first
    {
        int leftPrecedence  {};
        int rightPrecedence {};
        int counter         { 0 };
        for(char op : operators)
        {
            if(left == op)
            {
                leftPrecedence = operatorPrecedence[counter];
            }
            counter++;
        }
        counter = 0;
        for (char op : operators)
        {
            if (right == op)
            {
                rightPrecedence = operatorPrecedence[counter];
            }
            counter++;
        }

        if(leftPrecedence <= rightPrecedence)
        {
            return false;
        }
        else { return true; }
    }

}

struct Token //Struct used for storing the value of the equation in a [number] [operator] [number] format
{
public :
    double left {};
    double right{};
    char op     {};
};

class Calculator
{
private:
    Token left{};
    Token right{};

public:
    void start() //Main function used to continuosely calculate 
    {
        /*The user First inputs the values and operator for the lefft side of the calculation
        then the loop starts, during which the user starts providing the values for the right side
        Depending on the operator chosen : #1 the program will calculate the left side calculation and set its left value to the solution to then assing a new right value
                                           #2 the program will calculate the right side calculation and set the left side's calculation's right value to its solution */
        left.left = inputValue();
        left.op = inputOperator();
        left.right = inputValue();
        bool loop{ true };
        //The loop will continue until the user inputs the '=' symbol
        while (loop)
        {
            char tempOp = inputOperator();
            if (tempOp == '=')
            {
                printValue(calculate(left.left, left.op, left.right));
                loop = false;
                //If the user inputs the '=' operator, the loop stops and returns to the main funciton.
            }
            else if (ooc::operatorHigher(left.op, tempOp))
            {
                right.left = left.right;
                right.right = inputValue();
                right.op = tempOp;
                left.right = calculate(right.left, tempOp, right.right);
            }
            else
            {
                left.left = calculate(left.left, left.op, left.right);
                left.op = tempOp;
                left.right = inputValue();
            }
        }
        std::cout << "\n";
    }

    double calculate(double left, char op, double right)
    {
        switch (op)
        {
        case '*': return left * right;
            break;
        case '/': return left / right;
            break;
        case '+': return left + right;
            break;
        case '-': return left - right;
            break;
        case '^': return exponentiation(left, right);
            break;
        }
    }
    //Function used to get the exponentation of a value
    double exponentiation(double base, double power)
    {
        double initBase{ base };
        for (int i{ 1 }; i < power; i++)
        {
            base = base * initBase;
        }
        return base;
    }


    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    double inputValue()
    {
        while (true) // Loop until user enters a valid input
        {
            std::cout << "Enter a decimal number: ";
            double x{};
            std::cin >> x;

            // Check for failed extraction
            if (!std::cin) // if the previous extraction failed
            {
                if (std::cin.eof()) // if the stream was closed
                {
                    exit(0); // shut down the program now
                }

                // let's handle the failure
                std::cin.clear(); // put us back in 'normal' operation mode
                ignoreLine();     // and remove the bad input

                std::cout << "Oops, that input is invalid.  Please try again.\n";
            }
            else
            {
                ignoreLine(); // remove any extraneous input
                return x;
            }
        }
    }
    char inputOperator()
    {
        while (true) // Loop until user enters a valid input
        {
            std::cout << "Enter an Operator : ";
            char operation{};
            std::cin >> operation;

            if (!std::cin) // if the previous extraction failed
            {
                if (std::cin.eof()) // if the stream was closed
                {
                    exit(0); // shut down the program now
                }

                // let's handle the failure
                std::cin.clear(); // put us back in 'normal' operation mode
            }

            ignoreLine(); // remove any extraneous input

            // Check whether the user entered meaningful input
            switch (operation)
            {
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
            case '=':
                return operation; // return it to the caller
            default: // otherwise tell the user what went wrong
                std::cout << "Invalid Input. Please try again.\n";
            }
        } // and try again
    }

    void printValue(double value)
    {
        std::cout <<  "The Solution is : " << value << '\n';
    }
};

void interface()
{
    std::cout << "---------------------------------------------------- \n";
    std::cout << "Welcum to my retarded attempt at making a calculator \n";
    std::cout << "---------------------------------------------------- \n";
    std::cout << "\n";
    std::cout << "---------------------------------------------------- \n";
    std::cout << "     [ x^y ] [ () ] [ * ] [ / ]  [ + ]  [ - ] \n";
    std::cout << "---------------------------------------------------- \n";
    std::cout << "       '^'    '('    '*'   '/'    '+'    '-'  \n";
    std::cout << "---------------------------------------------------- \n";
}


int main()
{
    interface();
    Calculator calc{};
    while(true)
    {
        calc.start();

    }
    return 0;
}