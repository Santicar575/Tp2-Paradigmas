#include "PokemonInfo.hpp"
#include <string>

PokemonInfo::PokemonInfo(std::string tipo, std::string descripcion, std::unordered_map<std::string, int> ataques, std::array<int, 3> experienciaNivel) : tipo(tipo), descripcion(descripcion), ataquesDisponibles(ataques), experienciaProximoNivel(experienciaNivel) {};

std::string PokemonInfo::getTipo() const { return tipo; }

// Retorna la descripción del Pokémon
std::string PokemonInfo::getDescripcion() const { return descripcion; }

// Retorna el mapa de ataques disponibles del Pokémon
std::unordered_map<std::string, int> PokemonInfo::getAtaquesDisponibles() const { return ataquesDisponibles; }

// Retorna el array de experiencia necesaria para los próximos niveles
std::array<int, 3> PokemonInfo::getExperienciaProximoNivel() const { return experienciaProximoNivel; }

std::ostream &operator<<(std::ostream &os, const PokemonInfo &p)
{
  os << "| Tipo: " << p.getTipo() << std::endl
     << std::string(100, '-') << std::endl
     << "| Descripción: " << p.getDescripcion() << std::endl
     << std::string(100, '-') << std::endl
     << "| Ataques disponibles: ";
  for (const auto &ataque : p.getAtaquesDisponibles())
  {
    os << ataque.first << " (daño: " << ataque.second << ") ";
  }
  os << std::endl <<  std::string(100, '-') << std::endl;
  os << "| Experiencia para próximos niveles: ";
  auto exp = p.getExperienciaProximoNivel();
  for (size_t i = 0; i < exp.size(); ++i)
  {
    os << exp[i];
    if (i < exp.size() - 1)
      os << ", ";
  }
  os << std::endl
     << std::string(100, '-') << std::endl;
  return os;
}