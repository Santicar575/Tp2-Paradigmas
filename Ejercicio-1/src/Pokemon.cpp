#include "Pokemon.hpp"
#include <iostream>

Pokemon::Pokemon(std::string name, int experience) : name(name), experience(experience) {}

std::string Pokemon::getName() const
{
  return name;
};

int Pokemon::getExperience() const
{
  return experience;
};