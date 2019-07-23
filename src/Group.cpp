//
//  Group.cpp
//  DalRT
//
//  Created by Dallas McNeil on 9/6/19.
//  Copyright © 2019 Dallas McNeil. All rights reserved.
//

#include "Group.hpp"

namespace DalRT {
        
    void Group::AddSubGroup(Group *group)
    {
        subGroups.push_back(group);
        extentDirty = true;
    }

    bool Group::RemoveSubGroup(Group *group)
    {
        for (int i=0; i<subGroups.size(); i++)
        {
            if (subGroups[i] == group)
            {
                subGroups.erase(subGroups.begin() + i);
                extentDirty = true;
                return true;
            }
        }
        return false;
    }
        
    std::vector<Group*> Group::GetSubGroups()
    {
        return subGroups;
    }

    void Group::AddObject(Object *object)
    {
        objects.push_back(object);
        extentDirty = true;
    }

    bool Group::RemoveObject(Object *object)
    {
        for (int i=0; i<objects.size(); i++)
        {
            if (objects[i] == object)
            {
                objects.erase(objects.begin() + i);
                extentDirty = true;
                return true;
            }
        }
        return false;
    }
        
    std::vector<Object*> Group::GetObjects()
    {
        return objects;
    }
        
    void Group::CalculateExtent()
    {
        extent.Reset();
        
        for (int i=0; i<subGroups.size(); i++)
        {
            extent.Extend(subGroups[i]->GetExtent());
        }
        for (int i=0; i<objects.size(); i++)
        {
            extent.Extend(objects[i]->GetExtent());
        }
        extentDirty = false;
    }
        
    Extent* Group::GetExtent()
    {
        if (extentDirty)
        {
            CalculateExtent();
        }
        return &extent;
    }

}


