/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> a = {1,2,3,4,5,6};
    vector<int> b = {7,8,9,1,1,3,1,1};
    
    int cutoffAtTimeOfReplacement = 0;
    int cutoff = 0;
    
    //cutoff depth of 3
    // c=3, 2 
    //cutoff = 3;
    //a = {1,2};
    //b = {1,2,9};
    //cutoffAtTimeOfReplacement = 2;
    
    //cutoff depth of 2
    //cutoff = 2;
    //a = {1,2};
    //b = {1,5};
    //cutoffAtTimeOfReplacement = 1;
    
    //cutoff depth of 2
    a = {1};
    b = {1, 3};
    cutoffAtTimeOfReplacement = 2;
    
    //cutoff depth of 5
    //a = {1,2,3};
    //b = {1,4};
    //cutoffAtTimeOfReplacement = 3;
    
    //cutoff of 5
    //a = {1,2,3};
    //b = {4};
    //cutoffAtTimeOfReplacement = 3;
    
    int level = a.size() - cutoffAtTimeOfReplacement;
    cout << "level: " <<  level << endl;
    
    if (a.size() >= b.size())
    {
        auto last = copy(b.begin(), b.end(), a.begin() + level);
        cout << "a after copy" << endl;
        for(auto i : a){
            cout << i << " ";
        }
        cout << endl;
    }
    else 
    {
        auto last = copy(b.begin(), b.end(), a.begin() + level);
        cout << "a after copy" << endl;
        for(auto i : a){
            cout << i << " ";
        }
        cout << endl;
    
        int difference = b.size() - a.size();
        cout << "difference: " << difference << endl;
    
        a.insert(last, b.end() - difference, b.end());
    
        cout << "copy version: ";
        for(auto i : a){
            cout << i << " ";
        }
        cout << endl;     
    }
   
    return 0;
}

