/* Name: Samiksha Pradhan
   Course: CS 372
   Program: Infix to Postfix & Evaluation
   Description:  Evaluate postfix expressions. */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;
ifstream infile;
ofstream outfile;

const int CAPACITY = 40; // max no of elements that can be stored
typedef float ElementType;

class List
{
private:
    ElementType myAry[CAPACITY];
    int pos; // current index
    int used; // next index or the length of the list or the no. of elements or no. of used indices
public:
    List() // default constructor
    {
        used = 0;
        pos = 0;
        /*for(int i=0; i<used; i++)
        {
            myAry[i] = 0;
        }*/
    }
    List(List &l) // copy constructor: use it only after the first object is filled with data
    {
        pos = 0;
        used = l.size();
        if (used > 0)
        {
            for(int i=0; i<used; i++)
            {
                l.setPos(i);
                myAry[i] = l.getElement();
            }
        }
    }
    void display()
    {
        for(int i=0; i<used; i++)
         {
             cout << myAry[i] << " ";
             outfile << myAry[i] << " ";
         }
    }
    bool empty()
    {
        return (used == 0);
    }
    void first() // first makes current position at the beginning of the list
    {
        pos = 0;
    }
    void last() // last makes current position at the end of the list
    {
        if(used != 0) // otherwise, if no list, then pos = -1
        {
            pos = used - 1;
        }
    }
    void prev() // places current position at the previous element in the list
    {
        if((pos - 1) >= 0)
        {
            pos--;
        }
    }
    void next() // places current position at the next element in the list
    {
        if((pos + 1) < used) // if 5 elements, then used = 6
        {
            pos++;
        }
    }
    int getPos()
    {
        if(pos < used)
            return pos;
    }
    void setPos(int value)
    {
        if(pos>=0 && pos<used)
            pos = value;
    }
    void insertBefore(ElementType v)
    {
        if(used == 0)
        {
            myAry[0] = v;
            pos = 0;
            used = 1;
        }
        else if( (used+1) <= CAPACITY)
        {
            for(int i=used; i>pos; i--)
            {
            myAry[i] = myAry[i-1];
            }
            myAry[pos] = v;
            used++;
        }
        else if( (used+1) > CAPACITY)
        {
            cout << "Full capacity!!\n";
            outfile << "Full capacity!!\n";
        }
    }
    void insertAfter(ElementType v)
    {
        if(used == 0)
        {
            myAry[0] = v;
            pos = 0;
            used = 1;
        }
        else if( (used+1) <= CAPACITY)
        {
            for(int i=used; i>pos; i--)
            {
                myAry[i] = myAry[i-1];
            }
            myAry[pos+1] = v;
            pos++;
            used++;
        }
        else if( (used+1) > CAPACITY)
        {
            cout << "Full Capacity!!\n";
            outfile << "Full Capacity!!\n";
        }
    }
    ElementType getElement()
    {
        if(pos < used)
            return myAry[pos];
    }
    int size()
    {
        return used;
    }
    void replace(int v)
    {
        if(pos < used)
            myAry[pos] = v;
    }
    void erase()
    {
        if(used == 0)
        {
            return;
        }
        else if(used == 1 && pos == 0)
        {
            pos = 0;
            used = 0;
        }
        else if(pos == (used-1))
        {
            pos--;
            used--;
        }
        else if(pos < (used-1))
        {
            for(int i=pos; i<(used-1); i++)
            {
                myAry[i] = myAry[i+1];
            }
            used--;
        }
    }
    void clear()
    {
        used = 0;
        pos = 0;
    }
    friend ostream &operator <<(ostream &out, const List &l)
    {
        if (l.used == 0)
        {
            cout << "{ }";
            outfile << "{ }";
        }
        else
        {
        cout << "{ ";
        outfile << "{ ";
        for(int i=0; i<((l.used)-1); i++)
        {
            cout << l.myAry[i] << ", ";
            outfile << l.myAry[i] << ", ";
        }
        cout << l.myAry[(l.used)-1] << " }";
        outfile << l.myAry[(l.used)-1] << " }";
        }
    }
    friend bool operator ==(const List &a, const List &b)
    {
        if(a.used != b.used)
            return false;
        else
        {
            int count = 0;
            for(int i = 0; i<a.used; i++)
            {
                if(a.myAry[i] == b.myAry[i])
                    count++;
            }
            if(count == a.used)
                return true;
        }
    }
    friend bool operator !=(const List &a, const List &b)
    {
        if (a==b)
            return false;
        else
            return true;
    }
    friend void operator +=(List &a, List &b) // adds items of another list to a list
    {                        // no const because a needs to change
        if( (a.size() + b.size()) <= CAPACITY )
        {
            for(int i=0; i<b.size(); i++)
            {
                a.myAry[a.used] = b.myAry[i];
                (a.used)++;
            }
        }
    }
    friend List operator +(List &a, List &b) // returns a new list with the items of two lists
    {                                        // no const because += is used which doesn't take const
        if( (a.size() + b.size()) <= CAPACITY )
        {
            List answer;
            answer += a;
            answer += b;
            return answer;
        }
    }
    void operator =(List &b) // like copy constructor // does't need friend, but a = b works
    {                        // no const because not friend
        if (b.size() == 0)
            used =0;
        else if ((b.size()>0) && (b.size()<=CAPACITY))
        {
            used = b.used; // don't forget //
            for(int i=0; i<b.size(); i++)
            {
                b.setPos(i);
                myAry[i] = b.getElement();
            }
        }
    }
};
//////////////////////////////STACK CLASS//////////////////////////////////////////////////////////////////////////////////////////////////
class stack
{
private:
    List myStack;
public:
    void push(ElementType v)
    {
        myStack.last();
        myStack.insertAfter(v); // checks if full
    }
    void pop()
    {
        myStack.last();
        myStack.erase(); //checks if empty
    }
    bool empty()
    {
        return myStack.empty();
    }
    int size()
    {
        return myStack.size();
    }
    ElementType top()
    {
        myStack.last();
        return myStack.getElement();
    }
    void showStack() // display output
    {
        cout << myStack; // << is overloaded to display List so don't do output << or it will print twice
    }
    ElementType max()
    {
        if(myStack.size()>0 && myStack.size()<=CAPACITY)
        {
            myStack.setPos(0);
            ElementType m = myStack.getElement(); // data in index 0
            for(int i=0; i<myStack.size(); i++)
            {
                myStack.setPos(i);
                if (m < myStack.getElement())
                    m = myStack.getElement();
            }
            return m;
        }
    }
};
//////////////// QUEUE   /////////////////////////////////////////////////////////////////////////////////////////////////////
class Q
{
private:
    List myQ;
public:
    void enq(ElementType v)
    {
        if(myQ.size() <= CAPACITY)
        {
            myQ.last();
            myQ.insertAfter(v); // checks if full
        }
    }
    void deq()
    {
        if(myQ.size() != 0)
        {
            myQ.first();
            myQ.erase(); // checks if full
        }
    }
    void showQ() // display output
    {
        for(int i=0; i<myQ.size(); i++) // myAry is private to List class. so cannot use
        {
            myQ.setPos(i);
            cout << myQ.getElement() << " ";
            outfile << myQ.getElement() << " ";
        }
    }
    int size()
    {
        return myQ.size();
    }
    ElementType front()
    {
        myQ.first();
        return myQ.getElement();
    }

};
///////Functions////////////////////////////////////////////////////////////////////////////////////////////////////
bool ValidOperator(ElementType token)
{
    return (token=='+' || token=='-' || token=='*' || token=='/' || token=='^');
}
bool ValidOperand(ElementType token)
{
    return ( !(ValidOperator(token)) && token!='(' && token!=')' );
}
int InfixPriority(ElementType token)
{
    if(token == '^' || token == '(') // () goes first
    return 3;
    else if(token == '*' || token == '/')
    return 2;
    else if(token == '+' || token == '-')
    return 1;
    else
    return 0;
}
StackPriority(ElementType token)
{
    if(token == '^')
    return 3;
    else if(token == '*' || token == '/')
    return 2;
    else if(token == '+' || token == '-')
    return 1;
    else  // () should not be in he postfix expression
    return 0;
}

float evaluate(string exp)
{
stack ansStack;
for (int i=0; i<exp.length(); i++)
    {
        if (isdigit(exp[i]))
            ansStack.push(exp[i]-'0'); // char into num

        // If the scanned character is an operator, pop two
        // elements from stack apply the operator
        else
        {
            float val1 = ansStack.top();
            ansStack.pop();
            float val2 = ansStack.top();
            ansStack.pop();
            switch (exp[i])
            {
            case '+': ansStack.push(val2 + val1); break;
            case '-': ansStack.push(val2 - val1); break;
            case '*': ansStack.push(val2 * val1); break;
            case '/': ansStack.push(val2 / val1); break;
            case '^': ansStack.push((pow(val2,val1))); break;
            }
        }
    }
    return ansStack.top();
}
///////Main/////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
  {
      infile.open("Postfix Expressions.txt");
        if(!infile)
        {
            cout << "File not found." << endl;
            return 0;
        }
    outfile.open("Postfix Evaluation Output.txt");

    string exp;


while(getline(infile,exp))
{
    cout << "Postfix Expression: " << exp << endl;
    outfile << "Postfix Expression: " << endl;
    cout << "\t Solution = " << evaluate(exp) << "\n" << endl;
    outfile << "\t Solution = " << evaluate(exp) << "\n" << endl;
} // close while infile

    cout << "\n\n";
    infile.close();
	outfile.close();
	return 0;
  }
