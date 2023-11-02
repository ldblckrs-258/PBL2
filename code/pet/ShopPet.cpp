#include "./ShopPet.h"
#include <iostream>

ShopPet::ShopPet() : price(0) {}
int ShopPet::getPrice() const { return price; }
std::string ShopPet::getHistory() const { return history; }

void ShopPet::setPrice(int newPrice) { price = newPrice; }
void ShopPet::setHistory(const std:: string &newHistory) { history = newHistory; }
