#pragma once
#include <iostream>
#include <memory>

class GameAssetLibrary 
{
public:
	GameAssetLibrary();
	~GameAssetLibrary();
	std::unique_ptr<Object> Search(std::string);
	
private:
	map<std::string, std::unique_ptr<ObjectFactory>> library;


};
