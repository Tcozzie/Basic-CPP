#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

class Address {
// class members todo
private:
int classID;
char ID;
string host,network;

public:
    void setID(char in){ID=in;} // set the class ID
    char getID() const {return ID;} // get the class ID
    void setHost(string in){host=in;} // set the host 
    string getHost() const {return host;} // get the host
    void setNetwork(string in){network=in;} // set the network 
    string getNetwork() const {return network;} // get the network

    friend istream &operator>>(istream&, Address&); // overriding input 
    friend ostream &operator<<(ostream&, const Address&); // overriding output
};

istream& operator>>(istream &input, Address &A) { // overriding input
    // todo
    string temp; 
    input >> temp;
    int pos1,pos2,pos3,len;
    len=temp.size(); // gets the length of the string
    if(len==0){}else{ // if the length isnt 0
        pos1=temp.find("."); // finds where the first period is
        pos2=temp.find(".",pos1+1); // finds where the second period is
        pos3=temp.find(".",pos2+1); // finds where the third period is
        int classID=stoi(temp.substr(0,pos1)); // gets the class id for the address
        if(classID<=127){ // if class id is smaller then 127
            A.setID('A'); // sets class id to A
            A.setNetwork(to_string(classID)); // sets network id
            A.setHost(temp.substr(pos1+1,len-pos1-1)); // sets host id
        }else if((classID>=128)&&(classID<=191)){ // if the classID is larger then 128 and smaller then 191
            A.setID('B'); // sets id to B
            A.setNetwork(temp.substr(0,pos2)); // sets network 
            A.setHost(temp.substr(pos2+1,len-pos1-1)); // sets host
        }else if((classID>=192)&&(classID<=223)){ // if the class id is bigger then 192 and smaller then 223
            A.setID('C'); // sets class id to C
            A.setNetwork(temp.substr(0,pos3)); // sets network
            A.setHost(temp.substr(pos3+1,len-pos1-1)); // sets host
        } 
    }
    return input; // returns the input stream

}

ostream& operator<<(ostream &output, const Address &A) { // overrides output 
    output<<"Network: "<<A.getNetwork()<<" Host: "<<A.getHost()<<endl; // custom output
    return output; // returns output
}


int main(void) {
    // create three vectors of type Address, one for each class
    vector<Address> classA; // class A vector
    vector<Address> classB; // class B vector
    vector<Address> classC; // class C vector

    // open the file
    ifstream instream; // open input stream
    instream.open("/public/lab7/addresses.txt"); // open file
    
    string prev; // previous to be entered into a vector
    Address a; // iteerator
    while (instream >> a) { // going through the whole instream
        if(a.getID()=='A'){ //if ID is A push back to A vector
            if(prev!=a.getNetwork()){classA.push_back(a);} // checks for duplicates
        }else if(a.getID()=='B'){ // if ID is B push back to B vector
            if(prev!=a.getNetwork()){classB.push_back(a);} // checks for duplicates
        }else if(a.getID()=='C'){ // if ID is C push back to C vector
            if(prev!=a.getNetwork()){classC.push_back(a);} // check for duplicates
        }
        prev=a.getNetwork(); // sets the previous one put in vector (for duplicates)
    }
    instream.close(); // close the input stream
    
    // sorts classA vetor
    sort(classA.begin(),classA.end(),[](const Address &a,const Address &b){
        return stoi(a.getNetwork()) < stoi(b.getNetwork());
    });
    // sorts the classB vector
    sort(classB.begin(),classB.end(),[](const Address &a,const Address &b){
        return stoi(a.getNetwork())<stoi(b.getNetwork());
    });
    // sorts the classC vector
    sort(classC.begin(),classC.end(),[](const Address &a,const Address &b){
        return stoi(a.getNetwork())<stoi(b.getNetwork());
    });
    // printing class A vector
    cout<<"Class A has "<<classA.size()<< " network addresses:"<<endl;
    for(Address a:classA){
        cout<<a;
    }
    // printing class B vector
    cout<<"Class B has "<<classB.size()<<" network addresses:"<<endl;
    for(Address a:classB){
        cout<<a;
    }
    // printing class C vector
    cout<<"Class C has "<<classC.size()<<" network addresses:"<<endl;
    for(Address a:classC){
        cout<<a;
    }

    return(0);
}
