#pragma once
#include <unordered_map>
#include "Pokemon.hpp"
#include "PokemonInfo.hpp"

class Pokedex
{
private:
  std::unordered_map<Pokemon, PokemonInfo, Pokehash> data;
  std::pair<bool, std::string> linkedFile;
  void deserializar();

public:
  // por default, pair inicializa linkedFile como <false, "">
  Pokedex() = default; 

  // sobrecarga para pokedex asociada a un archivo
  Pokedex(std::string filePath);

  void agregar(Pokemon &p, PokemonInfo &info);
  void saveNew(Pokemon &p, PokemonInfo &info);
  void mostrar(const Pokemon &) const;
  void mostrarTodos() const;

  void serializarCompleta();
};