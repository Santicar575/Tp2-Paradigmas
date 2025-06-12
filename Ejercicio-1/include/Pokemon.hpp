#pragma once
#include <iostream>
#include <fstream>

class Pokemon
{
private:
  std::string name;
  int experience;

public:
  Pokemon(std::string name, int experience = 0);

  // Retorna el nombre del Pokemon
  std::string getName() const;

  // Retorna los puntos de experiencia Pokemon
  int getExperience() const;

  void serializar(std::ofstream& outfile);

  void deserializar(std::ifstream& infile);

  bool operator==(const Pokemon &other) const;

  friend std::ostream &operator<<(std::ostream &os, const Pokemon &p);
};

// Functor para hash personalizado
struct Pokehash
{
  std::size_t operator()(const Pokemon &p) const;
};