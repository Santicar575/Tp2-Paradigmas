#include "PokemonInfo.hpp"

std::string PokemonInfo::getTipo() const { return tipo; }

// Retorna la descripción del Pokémon
std::string PokemonInfo::getDescripcion() const { return descripcion; }

// Retorna el mapa de ataques disponibles del Pokémon
std::unordered_map<std::string, int> PokemonInfo::getAtaquesDisponibles() const { return ataquesDisponibles; }

// Retorna el array de experiencia necesaria para los próximos niveles
std::array<int, 3> PokemonInfo::getExperienciaProximoNivel() const { return experienciaProximoNivel; }