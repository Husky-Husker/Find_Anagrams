#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


void Loop(int i, int max, string &prefix, string &rest, string &permutations);

void printPermutations(string prefix, string rest, string &permutations, int size, const string dict[]);

bool Findword(int i, int max, string word, const string dict[]) //returns true if the word exists in string array dict
{
    if(i>=max)
        return false;
    else if(word == dict[i])
        return true;
    else
        return Findword(i+1, max, word, dict);
}
//act as a loop to run through the prefix word being passed from Print Permutations. erases the last character of prefix then adds it to rest. Then recursively calls Printpermutations to find the rest of the anagram. Uses Loop for other permutations. Only anagrams that exist is dict are then added to the corresponding string which holds all of the valid permutations
void Loop(int i, int max, string &prefix, string &rest, string &permutations, int size, const string dict[])
{
    if (i >= max)
        return;
    char a = prefix[i];
    rest = rest +a;
    prefix.erase(i,1);
    printPermutations( prefix, rest, permutations,size, dict);
    prefix.insert(i , 1, a);
    rest.erase(rest.length()-1, 1);
    Loop(i + 1, max,prefix, rest, permutations, size, dict);
}


void printPermutations(string prefix, string rest, string &permutations, int size, const string dict[])
{
    if (prefix == "") {
        if(Findword(0, size , rest, dict)==true)
            permutations = permutations+ rest;
    }
    else
        Loop(0, prefix.size(), prefix, rest, permutations, size, dict);
    
}

void Loop1(int i,int max, istream &dictfile, string dict[], int &count) //fills in the dict array with words from .txt file. returns/ends when its more than the max number of words or the file is empty
{
    if(i>=max || dictfile.eof() == true)
        return;
    
    string word;
    getline(dictfile,word);
    dict[i] = word;
    count++;
    Loop1(i+1, max, dictfile, dict, count);
    
}



//uses Loop1 to load the words into dict. Has a counter variable that counts the total number of words entered

int loadWords(istream &dictfile, string dict[])
{
    int count = 0;
    Loop1(0,MAXDICTWORDS, dictfile, dict, count);
    return count;
}


void Fillresult( int dictsize, string permutations,const string dict[], string result[], int &count, string word)
//using the string of permutations from PrintPermutation, it isolates each permutation and checks whether it already exists in results. if it doesnt then add to results array
{
    if(permutations =="" ||count >= MAXRESULTS)
        return;
    if( Findword(0,count, permutations.substr(0,word.size()), result) ==false)
    {
        result[count] = permutations.substr(0,word.size());
        count++;
    }
    Fillresult( dictsize, permutations.substr(word.size()), dict, result, count, word);
    
    
}
//fill string permutations with PrintPermutation Then calls helper function Fillresult to fill the actual result array
int recBlends(string word, const string dict[], int size, string results[])
{
    
    
    string permutations;
    printPermutations(word , "", permutations, size, dict);
    int count =0;
    Fillresult(size, permutations, dict, results, count, word);
    return count;
}


//prints what is in the results array
void showResults(const string results[], int size)
{
    
    if(size ==0)
        return;
    cout << results[size-1] << endl;
    showResults(results, size-1);
}

int main()
{
    
    
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    nwords = loadWords(dictfile, dict);
    
    cout << "Please enter a string for an anagram: ";
    getline(cin, word);
    
    int numMatches = recBlends(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        showResults(results, numMatches);
    
   
    
    return 0;
    
    
    
}
