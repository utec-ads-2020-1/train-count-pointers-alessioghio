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
                countAddr[i].first++; // increase counter
                indexes2.push_back(j); // determine which pointers of the 2 lvl are pointing to the same lvl 3 integers
            }
        }
        counter.push_back(make_pair(countAddr[i].first,i));
        lvl3ints.push_back(*countAddr[i].second);
    }
    for (int i = 0; i < indexes2.size(); i++){ 
        counter.erase(counter.begin() + indexes2[i]); // remove duplicates
        lvl3ints.erase(lvl3ints.begin() + indexes2[i]); // remove duplicates
    }
    // You must print the integers in increasing order of the numbers of the first level pointers that can reach them
    sort(counter.begin(), counter.end());
    vector<pair<int, int>> result;// lvl3 integer value and its counter
    for (int i = 0; i < lvl3ints.size(); i++){
        result.push_back(make_pair(lvl3ints[counter[i].second], counter[i].first));
    }
    //  If two integers have the same numbers of the first level pointers that can reach them, print the smaller integer first
    int idx = 0;
    while ((result[idx].second == result[idx+1].second) && (idx < lvl3ints.size()-1)){
        if(result[idx].first > result[idx+1].first){
            int temp = result[idx].first;
            result[idx].first = result[idx+1].first;
            result[idx+1].first = temp;
            idx = 0;
        }else{
            idx++;
        }
    }
    // Print the integers and the number of first level pointers that can reach them
    for(int i = 0; i < result.size(); i++){
        cout << result[i].first << " " << result[i].second << endl;
    }
    
}