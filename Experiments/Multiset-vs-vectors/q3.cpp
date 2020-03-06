/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: David
 *
 * Created on November 3, 2019, 12:44 AM
 */

#include <time.h>
#include <ctime>
#include <cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<unordered_set>

using namespace std;

/*
 * 
 */

//Taken from geeksforgeeks.org/binary-search
int binarySearch(vector<int> arr, int l, int r, int x) 
{ 
    while (l <= r) { 
        
        int m = l + (r - l) / 2; 
        
        // Check if x is present at mid 
        if (arr[m] == x) 
            return m; 
  
        // If x greater, ignore left half 
        if (arr[m] < x) 
            l = m + 1; 
  
        // If x is smaller, ignore right half 
        else
            r = m - 1; 
    } 
  
    // if we reach here, then element was 
    // not present 
    return l; 
} 

int main(int argc, char** argv) {

    srand(time(NULL));
    
    
    //multiset<int> b_tree;
    vector<int> random_numbers;
    
    constexpr int SAMPLE_SIZE = 1000;
    constexpr int NUM_LOOPS = 10;
    constexpr int RANGE = SAMPLE_SIZE*10;
    
    //Random numbers to insert into vector and multiset
    for (int i=0;i<SAMPLE_SIZE;i++){
        int random_number = rand() % RANGE;
        random_numbers.push_back(random_number);
    }
    
    //Binary tree insert
    clock_t s_time = clock();
    for(int i = 0; i < NUM_LOOPS; i++){
        multiset<int> b_tree;
        for(int j = 0; j < random_numbers.size(); j++){
            b_tree.insert(random_numbers[j]);
        }
    }
    clock_t f_time = clock() - s_time;
    cout << "Multiset Insert Time: "
         << ((double) f_time) / (double) CLOCKS_PER_SEC
         << " seconds" << endl;

    //Hash Table insert
    s_time = clock();
    for(int i = 0; i < NUM_LOOPS; i++){
        unordered_multiset<int> h_table;
        for(int j = 0; j < random_numbers.size(); j++){
            h_table.insert(random_numbers[j]);
        }
    }
    f_time = clock() - s_time;
    cout << "Unordered Multiset Insert Time: "
         << ((double) f_time) / (double) CLOCKS_PER_SEC
         << " seconds" << endl;
    
    
    //Vector insertion
    int index;
    s_time = clock();
    for(int i = 0; i < NUM_LOOPS; i++){
        vector<int> vec;
        vec.push_back(random_numbers[0]);
        for(int j = 1; j < random_numbers.size(); j++){
            index = binarySearch(vec,0, vec.size()-1, random_numbers[j]);
            vec.insert(vec.begin()+index, random_numbers[j]);
        }
    }
    f_time = clock() - s_time;
    cout << "Vector Insert Time: "
         << ((double) f_time) / (double) CLOCKS_PER_SEC
         << " seconds" << endl;
    
}

