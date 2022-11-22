#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Term { // term class that is going to store each term of polynomial
    private:
    int coeff;
    int exp;
    public:
    Term(string); // constructor for an input of a string
    Term() {coeff = 0; exp = 0; }; // blank constructor
    void print(); // print
    int get_exp() { return exp; } // get exp 
    void set_exp(int e) { exp = e; } // set exp
    int get_coeff() { return coeff; } // get coeff
    void set_coeff(int n) { coeff = n; } // set coeff
};

void Term::print() { // printing the terms of the polynomial
    if(this->get_coeff()==1){ // is the coeff = 1 just print the "x" and the coeff
        cout<<"x"<<this->get_exp()<<" +"; // getting coeff of polynomial
    }else if(this->get_exp()==0){ // if the exp = 0 just print the coeff
        cout<<" "<<this->get_coeff(); // not printing x with coeff
    }else if(this->get_exp()==1){ // if the exp = 1 just print the x with no exp num behind it
        cout<<" "<<this->get_coeff()<<"x +"; // printing coeff with x
    }else{ // print the coeff "x" exp if no conditions are met above
        cout<<" "<<this->get_coeff()<<"x"<<this->get_exp()<<" +";
    }
}

Term::Term(string input) { // constructor if there is a string sent in
    int coeff; 
    int exp;
    int x_index=input.find("x"); // finds the "x" withing the string input
    int len=input.length(); // finds the length of the input

    if(x_index==0){ // if there is just an "x" in the input
        set_coeff(1); // coeff of "x" will equal 1
    }else if(x_index==-1){ // if there is no "x" within the term
        coeff=input[0]-'0'; // convert the coeff to an int
        set_coeff(coeff); // setting coeff
    }else{
        set_coeff(stoi(input.substr(0,x_index))); // grabbing the coeff between the start and index of "x"
    }

    if(x_index==-1){ // if there is no "x" in the term
        set_exp(0); // set the exp to 0
    }else if(x_index==len-1){ // if the "x" is the last item in the term
        set_exp(1); // set the exp to 1
    }else{
        if((len==2)&&(x_index==0)){ // if the x is the first term
            exp=stoi(input.substr(len-x_index-1)); // grabbing the number behind the "x"
            set_exp(exp); // setting the exp to this number^
        }else{
            exp=stoi(input.substr(len-x_index)); // grabbing the number behind the "x" 
            set_exp(exp); // setting the exp to this number^
        }
    }
}

class Polynomial { // class for the whole polynomial together
    private:
    vector<Term> terms; // vector to store the whole polynomial
    public:
    void simplify(); // simplify the polynomial
    void read(); // read in the polynomial
};

void Polynomial::read() { // read in the polynomial
    string str;
    char op;
    bool done = false;

    while (!done) {
        cin >> str; // one term
        cin >> op;  // +
        if (cin.eof()) {
            done = true;
        }
        Term Term(str); // making the term just read in
        terms.push_back(Term); // sending that term into the vector to make polynomial
    }
}

bool compare(Term t1, Term t2) { // comparing two exponents
    return t1.get_exp() > t2.get_exp(); // checking wich exponents are bigger
}

void Polynomial::simplify() { // simplifying the polynomial
    vector<Term> tempV; // creating a temp vector
    int size; // size of the vector
    sort(terms.begin(), terms.end(), compare); // sorting the vector from largest to smallest by exp
    
    size=terms.size(); // finds the size of vector
   for(int i=0;i<size;i++){ // goes through the whole vector
        int coeff=0; // total of all coeff with same exp
        int exp=terms[i].get_exp(); // finding the exp from the term the loop is on
        for(int x=0;x<size;x++){  //going over the vector again
            if(exp==terms[x].get_exp()){ // if exponents are the same
                coeff+=terms[x].get_coeff(); // add them together
            }
        }
        terms[i].set_coeff(coeff); // setting the first occurance of the exp to the new total
   }


   tempV.push_back(Term()); // adding a term into the temp vector
   tempV[0].set_coeff(terms[0].get_coeff()); // setting the coeff of the first term (always the total.. doesn't need to be in loop)
   tempV[0].set_exp(terms[0].get_exp()); // setting the exp of the first term 

    int tempIndex=1;

   for(int i=0;i<size-1;i++){ // going over the whole vector
        int exp=terms[i].get_exp(); // getting the exp for each term

        if(terms[i+1].get_exp()!=exp){ // checking to see if there is an exp change
            tempV.push_back(Term()); // make a new term in the temp vector
            tempV[tempIndex].set_coeff(terms[i+1].get_coeff()); // setting the coeff for the next term in the temp vector
            tempV[tempIndex].set_exp(terms[i+1].get_exp()); // setting the exp for the next term in the temp vector
            tempIndex++;
        }
   }
   terms=tempV; // setting the original vector to the temp vector
   for(Term t: terms){ // going to print each element in the polynomial
        t.print(); // sending the term to print function
   }
   cout<<endl; // format for printing
}

int main(void) {
    // you don't need to add anything else to main

    Polynomial poly;
    poly.read();
    poly.simplify();
    return(0);
}
