#pragma once
#include <unordered_map>
#include "Pokemon.hpp"
#include "PokemonInfo.hpp"

class Pokedex
{
private:
  std::unordered_map<Pokemon, PokemonInfo, Pokehash> data;

public:
  Pokedex() = default;
  void agregar(Pokemon &p, PokemonInfo &info);
  void mostrar(const Pokemon &) const;
  void mostrarTodos() const;
};