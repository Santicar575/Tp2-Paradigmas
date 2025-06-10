#pragma once
#include <unordered_map>
#include "Pokemon.hpp"
#include "PokemonInfo.hpp"

class Pokedex
{
private:
  std::unordered_map<Pokemon, PokemonInfo> data;
public:
  void mostrar(Pokemon) const;
};