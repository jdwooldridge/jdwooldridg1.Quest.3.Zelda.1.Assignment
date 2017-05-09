#pragma once

//#include <iostream>

#include "ObjectFactory.h"

#ifndef _MEMORY_
    #include <memory>
#endif
#ifndef _MAP_
    #include <map>
#endif

class GameAssetLibrary
{
public:
    GameAssetLibrary();
    ~GameAssetLibrary();
    bool Initialize();
    std::shared_ptr<ObjectFactory> Search(std::string);

private:
    std::map<std::string, std::shared_ptr<ObjectFactory>> library;
};