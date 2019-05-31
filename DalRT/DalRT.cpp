//
//  DalRT.cpp
//  DalRT
//
//  Created by Dallas McNeil on 1/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include <iostream>
#include "DalRT.hpp"
#include "DalRTPriv.hpp"

void DalRT::HelloWorld(const char * s)
{
    DalRTPriv *theObj = new DalRTPriv;
    theObj->HelloWorldPriv(s);
    delete theObj;
};

void DalRTPriv::HelloWorldPriv(const char * s) 
{
    std::cout << s << std::endl;
};

