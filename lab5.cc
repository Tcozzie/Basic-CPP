#include <iostream>
#include <string>
#include <vector>
using namespace std;

void error(string s){ // error message
    throw runtime_error("ERROR: "+s); // throws custom error message and ends the program
}

vector<string> convert(vector<int> inputVect,int length){ // converts numbers to words
    vector<string> ones{"One","Two","Three","Four","Five","Six","Seven","Eight","Nine"}; //each number as words
    vector<string> tens{"NA","Twenty","Thirty","Fourty","Fifty","Sixty","Seventy","Eighty","Ninety"}; // each tens place number as words
    vector<string> bigOnes{"Hundred","Thousand"}; // big numbers to words
    vector<string> finalout; // final vector of strings to be sent back to main function

    int inputIter=0; // iterator for indexing

    for(int i:inputVect){ // for every number in inputVect
        if(i==1&&length==2){ // if the second digit is a one
            error("Second digit cannot be 1"); // throw error & end program
        }
        
        if(length!=2){ // while the length doesnt equal two
            finalout.push_back(ones[inputVect[inputIter]-1]); // convert number to word
            if(length==4){ // if length equals 4
                finalout.push_back(bigOnes[1]); // push word "Thousand"
            }else if(length==3){ // if length equals 3
                finalout.push_back(bigOnes[0]); // push word "Hundred"
            }
        }else{ // if the length equals 2
            finalout.push_back(tens[inputVect[inputIter]-1]); // convert word into its equvilant tens placement
        }


        inputIter++;
        length--;
    }

    return finalout; // return final vector of ints converted to words
}


int main(int argc,char** argv){
    if(argc!=2){ // checks to make sure there are the correct number of arguments
    cout<<"Incorrect number of arguments"<<endl;
    return(1); // if there isn't the correct number of arguments. end program
    }
    
    string finalString; // final string for printing
    vector<int> input; // making the vector for the users input to be stored
    string inputString=argv[1]; // grabbing the users input
    int len=inputString.length(); // finding the length of the users input

    for(int i=0;i<len;i++){ // going through the whole input
        int userInput=argv[1][i]-'0'; // converting each char into an int
        input.push_back(userInput); // inputting each number into the vector as ints
    }
    

    vector<string> finalV=convert(input,len); // sends users input to be converted to words (sent as vector of ints)

    for(string i:finalV){ // going through each word
        finalString+=" "+i; // making final string for printing
    }

    cout<<"Number "<<argv[1]<<" is written as "<<finalString<<endl; // printing final message

    return(0);
}
