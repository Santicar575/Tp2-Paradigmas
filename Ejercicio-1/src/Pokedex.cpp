#include "Pokedex.hpp"

void Pokedex::agregar(Pokemon &p, PokemonInfo &info)
{
  auto it = data.find(p);
  if (it != data.end())
  {
    std::cout << "Este pokemon ya se encuentra registrado en tu pokedex" << std::endl;
    return;
  };
  data.emplace(p, info);
};

void Pokedex::mostrar(const Pokemon &p) const
{
  auto it = data.find(p);
  if (it != data.end())
  {
    std::cout << it->first << it->second << std::endl;
  }
  else
  {
    std::cout << "¡Pokemon desconocido!" << std::endl;
  }
}

void Pokedex::mostrarTodos() const
{
  for (const auto &par : data)
  {
    mostrar(par.first);
  }
}
