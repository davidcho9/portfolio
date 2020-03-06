/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinarySearch.h
 * Author: David
 *
 * Created on February 9, 2019, 8:37 AM
 */

#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H
#include "SearchableVector.h"

class BinarySearch{
public:
    int search(SearchableVector* searchableVector){
        int left = 0;
        int right = searchableVector->getSize();
        while(left <= right){
            int middle = (left + right) / 2;
            if(searchableVector->compareAt(middle) == 0){
                return middle;
            }
            else if(searchableVector->compareAt(middle) == 1){
                right = middle - 1;
            }
            else{
                left = middle + 1;
            }
        }
        return -1;
    }
};



#endif /* BINARYSEARCH_H */

