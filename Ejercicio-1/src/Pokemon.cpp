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

bool Pokemon::operator==(const Pokemon &other) const
{
  // Compara por nombres
  return name == other.name;
}

std::size_t Pokehash::operator()(const Pokemon &p) const
{
  // hashea segun el nombre
  return std::hash<std::string>()(p.getName());
}

std::ostream &operator<<(std::ostream &os, const Pokemon &p)
{
  os << "========== || " << p.name << ", Experiencia: " << p.experience << " || ==========" << std::endl;
  return os;
}