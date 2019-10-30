#pragma once
#include <string>

struct Bag
{
	int id;			// Progressive, Primary Key.
	std::string name;	// wchar???
	int amount;		// Quantity
	int price;	    // Buying price. May differ from planet to planet.
};