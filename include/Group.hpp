//
//  Group.hpp
//  DalRT
//
//  Created by Dallas McNeil on 9/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#ifndef Group_hpp
#define Group_hpp

#include "Object.hpp"
#include "Extent.hpp"
#include <vector>

namespace DalRT {

class Group
{
public:
//    void AddSubGroup(Group *group);
//    bool RemoveSubGroup(Group *group);
//
//    void AddObject(Object *object);
//    bool RemoveObject(Object *object);
//
//    Extent* GetExtent();
    
private:
    void CalculateExtent();
    
    bool extentDirty;
    Extent extent;
    std::vector<Group*> subGroups;
    std::vector<Object*> objects;
};
    
}

#endif /* Group_hpp */
