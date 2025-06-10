#pragma once
#include <iostream>
// #include <string>

class Pokemon
{
private:
  std::string name;
  int experience;
public:
  // Retorna el nombre del Pokemon
  std::string getName() const;

  // Retorna los puntos de experiencia Pokemon
  int getExperience() const;
};