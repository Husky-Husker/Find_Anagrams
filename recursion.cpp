#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <string>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


void Loop(int i, int max, string &prefix, string &rest);

void printPermutations(string prefix, string rest);


void Loop(int i, int max, string &prefix, string &rest)
{
    if (i >= max)
        return;
    char a = prefix[i];
    rest = rest +a;
    prefix.erase(i,1);
    printPermutations( prefix,  rest);
    prefix.insert(i , 1, a);
    rest.erase(rest.length()-1, 1);
    Loop(i + 1, max,prefix, rest);
}

void printPermutations(string prefix, string rest)
{
    if (prefix == "") {
        cout << rest << endl;
    }
    else
    {
        Loop(0, prefix.size(), prefix, rest);
        
        /*For each character in rest {
            Add the character to the end of prefix.
            Remove character from rest.
            Use recursion to generate permutations with the
            updated values for prefix and rest.
                }
         */
    }
    
}

void Loop1(int i,int max, istream &dictfile, string dict[], int &count)
{
    if(i>=max || dictfile.eof() == true)
        return;
    string word;
    getline(dictfile,word);
    dict[i] = word;
    count++;
    Loop1(i+1, max, dictfile, dict, count);
    
}




int loadWords(istream &dictfile, string dict[])
{
    int count = 0;
    Loop1(0,MAXDICTWORDS, dictfile, dict, count);
    return count;
}

int recBlends(string word, const string dict[], int size, string results[])
{
    return 0;
}


void showResults(const string results[], int size)
{
    
}
int main()
{
    printPermutations("Marty" , "");

    
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
    return nwords;
    /*
    cout << "Please enter a string for an anagram: ";
    cin >> word;
    
    int numMatches = recBlends(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        showResults(results, numMatches);
     */
}
