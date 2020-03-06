/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   IntegerVectorSearchable.h
 * Author: David
 *
 * Created on February 9, 2019, 8:22 AM
 */

#ifndef INTEGERVECTORSEARCHABLE_H
#define INTEGERVECTORSEARCHABLE_H
#include <vector>
#include<iostream>
#include "SearchableVector.h"
using namespace std;

class IntegerVectorSearchable: public SearchableVector {
protected:
    vector<int> m_IntegerVectorSearchable;
    int Query;
public:
    void insertInteger(int i){
        m_IntegerVectorSearchable.push_back(i);
    }
    virtual unsigned int getSize() const {
        return m_IntegerVectorSearchable.size();
    }
    virtual int compareAt(int i) const {
        if(m_IntegerVectorSearchable[i] == Query){
            return 0;
        }
        else if(m_IntegerVectorSearchable[i] < Query){
            return -1;
        }
        else{
            return 1;
        }
    }
    void setQuery(int q){
        Query = q;
    }
    virtual void print() const{
        for(int i = 0; i < getSize(); i++){
            cout << m_IntegerVectorSearchable[i] << "; ";
        }
        cout << endl;
    }
   
};


#endif /* INTEGERVECTORSEARCHABLE_H */

