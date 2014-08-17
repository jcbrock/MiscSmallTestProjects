#ifndef CIRCULARB_H
#define CIRCULARB_H

//#include "CircularA.h" //causes Circular dependency

class CircularA;

class CircularB
{
public:
    CircularA* foo;
};

#endif