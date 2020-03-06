/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SearchableVector.h
 * Author: David
 *
 * Created on February 9, 2019, 8:13 AM
 */

#ifndef SEARCHABLEVECTOR_H
#define SEARCHABLEVECTOR_H

class SearchableVector {
public:
    virtual unsigned int getSize() const = 0;
    virtual int compareAt(int i) const = 0; 

};

#endif /* SEARCHABLEVECTOR_H */

