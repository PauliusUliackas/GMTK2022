#pragma once

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>
#include <iostream>

class Functions
{
private:
    
public:
    Functions(/* args */);
    ~Functions();
    static void init();
    static int Random(int min, int max);
};