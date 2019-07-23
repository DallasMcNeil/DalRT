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

/// A group of objects and other groups, with an extent
class Group
{
public:
    
    /// Add a sub group to this group
    void AddSubGroup(Group *group);
    
    /// Remove a sub group to this group, returns if it existed
    bool RemoveSubGroup(Group *group);
    
    /// Get the list of groups in this group
    std::vector<Group*> GetSubGroups();

    /// Add an object to this group
    void AddObject(Object *object);
    
    /// Remove an object to this group, returns if it existed
    bool RemoveObject(Object *object);
    
    /// Get the list of objects in this group
    std::vector<Object*> GetObjects();

    /// Get the extent of the entire group
    Extent* GetExtent();
    
private:
    void CalculateExtent();
    
    bool extentDirty = true;
    Extent extent;
    std::vector<Group*> subGroups;
    std::vector<Object*> objects;
};
    
}

#endif /* Group_hpp */
