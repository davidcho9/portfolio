/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: David
 *
 * Created on January 24, 2019, 12:16 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>




using namespace std;

class Shape{
public:
    virtual int computeArea(){}
    int xLocation;
    int yLocation;
    string Color;
    Shape(int a, int b, string c) : xLocation(a), yLocation(b), Color(c){}
    
    void printColor(){
        cout << Color << endl;
    }
};

class Square: public Shape{
protected:
    int edge;
public:
    Square(int a, int b, string c, int d) : Shape(a,b,c), edge(d){}
    
    virtual int computeArea(){
        if(edge <= 0){
            return 0;
        }
        int area = edge * edge;
        return area;
    }
};


class Circle: public Shape{
protected:
    int radius;
public:
    Circle(int a, int b, string c, int d) : Shape(a,b,c), radius(d){}
    
    virtual int computeArea(){
        if(radius <= 0){
            return 0;
        }
        int area = radius * radius * 3.14159265359;
        return area;
    }
};
    
    

int main(int argc, char** argv) {

    Square* S1 = new Square(1,1,"red",1);
    Square* S2 = new Square(2,2,"red",2);
    Square* S3 = new Square(5,5,"white",5);
    Square* S4 = new Square(6,6,"white", -1);
    Circle* C1 = new Circle(3,3,"black",3);
    Circle* C2 = new Circle(4,4,"black",4);
    vector<Shape*> container;
    
    container.push_back(S1);
    container.push_back(S2);
    container.push_back(S3);
    container.push_back(S4);
    container.push_back(C1);
    container.push_back(C2);
    
    vector<Shape>::size_type i = 0;
    for(i; i < container.size(); i++){
        cout << container[i]->computeArea() << endl;
        container[i]->printColor();
        cout << endl;
    }
}

