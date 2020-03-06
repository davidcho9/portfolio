/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: David
 *
 * Created on November 1, 2019, 1:50 AM
 */

#include <time.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h> 

using namespace std;

/*
 * 
 */

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int low, int high)  
{  
    int i, key, j;  
    for (i = low + 1; i < high; i++) 
    {  
        key = arr[i];  
        j = i - 1;  
  
        /* Move elements of arr[0..i-1], that are  
        greater than key, to one position ahead  
        of their current position */
        while (j >= 0 && arr[j] > key) 
        {  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }  
        arr[j + 1] = key;  
    }  
}  

//QUICK SORT FUNCTIONS START HERE
// A utility function to swap two elements  
void swap(int* a, int* b)  
{  
    int t = *a;  
    *a = *b;  
    *b = t;  
}  
  
/* This function takes last element as pivot, places  
the pivot element at its correct position in sorted  
array, and places all smaller (smaller than pivot)  
to left of pivot and all greater elements to right  
of pivot */
int partition (int arr[], int low, int high)  
{  
    int pivot = arr[high]; // pivot  
    int i = (low - 1); // Index of smaller element  
  
    for (int j = low; j <= high - 1; j++)  
    {  
        // If current element is smaller than the pivot  
        if (arr[j] < pivot)  
        {  
            i++; // increment index of smaller element  
            swap(&arr[i], &arr[j]);  
        }  
    }  
    swap(&arr[i + 1], &arr[high]);  
    return (i + 1);  
}  
  
/* The main function that implements QuickSort  
arr[] --> Array to be sorted,  
low --> Starting index,  
high --> Ending index */
void quickSort(int arr[], int low, int high)  
{  
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high);  
    }  
}

/* The main function that implements QuickSort  
arr[] --> Array to be sorted,  
low --> Starting index,  
high --> Ending index */
void hybridSort(int arr[], int low, int high)  
{  
    //CHANGE THIS FOR EXPERIMENTS
    if(high - low < 50){
        insertionSort(arr,low,high);
        return;
    }
    if (low < high)  
    {  
        /* pi is partitioning index, arr[p] is now  
        at right place */
        int pi = partition(arr, low, high);  
  
        // Separately sort elements before  
        // partition and after partition  
        hybridSort(arr, low, pi - 1);  
        hybridSort(arr, pi + 1, high);  
    }  
}



int main(int argc, char** argv) {

    //Seed for random number
    srand(time(NULL));
    
    constexpr int SAMPLE_SIZE = 300;
    constexpr int NUM_TESTS = 10000;
    constexpr int RANGE = SAMPLE_SIZE*10;
    
    int array[SAMPLE_SIZE];

    
    //Time testing for data allocation itself
    clock_t ds_time = clock();
    for(int j = 0; j < NUM_TESTS; j++){
        for (int i=0;i<SAMPLE_SIZE;i++){
            array[i] = rand() % RANGE;
        }
    }
    clock_t df_time = clock() - ds_time;
    
    cout << ((double) df_time) / (double) CLOCKS_PER_SEC << endl;
    
    //Actual time testing for quicksort
    clock_t s_time = clock();
    for(int j = 0; j < NUM_TESTS; j++){
        for (int i=0;i<SAMPLE_SIZE;i++){
            array[i] = rand() % RANGE;
        }
        quickSort(array,0,SAMPLE_SIZE);
    }
    clock_t f_time = clock() - s_time - df_time;
    cout << "Quick Sort Time: "
         << ((double) f_time) / (double) CLOCKS_PER_SEC
         << " seconds" << endl;
    
    //Time testing for insertion sort
    s_time = clock();
    for(int j = 0; j < NUM_TESTS; j++){
        for (int i=0;i<SAMPLE_SIZE;i++){
            array[i] = rand() % RANGE;
        }
        insertionSort(array,0, SAMPLE_SIZE);
    }
    f_time = clock() - s_time - df_time;
    cout << "Insertion Sort Time: "
         << ((double) f_time) / (double) CLOCKS_PER_SEC
         << " seconds" << endl;
    
    //Time testing for hybrid sort
    s_time = clock();
    for(int j = 0; j < NUM_TESTS; j++){
        for (int i=0;i<SAMPLE_SIZE;i++){
            array[i] = rand() % RANGE;
        }
        hybridSort(array,0, SAMPLE_SIZE);
    }
    f_time = clock() - s_time - df_time;
    cout << "Hybrid Sort Time: "
         << ((double) f_time) / (double) CLOCKS_PER_SEC
         << " seconds" << endl;
    
}


