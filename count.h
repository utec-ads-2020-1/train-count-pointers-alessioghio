#ifndef COUNT_H_INCLUDED
#define COUNT_H_INCLUDED
void count(int **p[]);
#endif

#define MAX_SIZE_PTRARRAY 512
#define MAX_NUM_PTR 512
#define MAX_NUM_INTVAR 512

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isZero (int** i) { return i==0; }

void count(int **p[]){
    vector<int**> ptrVec(p, p + MAX_SIZE_PTRARRAY);
    ptrVec.erase(remove_if(ptrVec.begin(), ptrVec.end(), isZero), ptrVec.end()); // Remove all zeros (all the spaces that are not being used and nullptr from previous array)
    // travel across through the first level array, and go to the integers in the third level through the pointers
    int ptrVecSize = ptrVec.size();
    vector<pair<int, int>> indexes1; // first level pointers that point to the same address
    vector<pair<int, int*>> countAddr; // Counter with addresses of the second lvl
    for(int i = 0; i < ptrVecSize; i++){
        for(int j = i+1; j < ptrVecSize; j++){
            if(ptrVec[i] == ptrVec[j]){
                indexes1.push_back(make_pair(i,j)); // First determine which pointers of the 1 lvl are pointing to the same lvl 2 pointers
            }
        }
        countAddr.push_back(make_pair(1,*ptrVec[i]));
    }
    for (int i = 0; i < indexes1.size(); i++){ // increase the count of the repeated pointers and remove duplicates
        countAddr[indexes1[i].first].first++;
        countAddr.erase(countAddr.begin() + indexes1[i].second);
    }
    vector<pair<int, int>> counter; // counter of frist level pointers that can reach teh same integer and their vector indexes
    vector<int> indexes2; // second level pointers that point to the same address
    vector<int> lvl3ints; // third level array values
    for(int i = 0; i < countAddr.size(); i++){
        for(int j = i+1; j < countAddr.size(); j++){
            if (countAddr[i].second == countAddr[j].second){
                countAddr[i].first++;
                indexes2.push_back(j);
            }
        }
        counter.push_back(make_pair(countAddr[i].first,i));
        lvl3ints.push_back(*countAddr[i].second);
    }
    for (int i = 0; i < indexes2.size(); i++){ 
        counter.erase(counter.begin() + indexes2[i]); // remove duplicates
        lvl3ints.erase(lvl3ints.begin() + indexes2[i]); // remove duplicates
    }
    
    // print the integers in increasing order of the numbers of the first level pointers that can reach them
    sort(counter.begin(), counter.end());
    counter.push_back(make_pair(0,0)); // Append a 0,0 pair to avoid out of range problems
    for (int i = 0; i < lvl3ints.size(); i++){
        // If two integers have the same numbers of the first level pointers that can reach them, print the smaller integer first
        if(counter[i].first == counter[i+1].first){
            
        }
        // print the integers and the number of first level pointers that can reach them
        cout << lvl3ints[counter[i].second] << " " << counter[i].first << endl;
    }
    
    

    cout << "Debug time";
    
    
    
}