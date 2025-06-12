#pragma once

#include <iostream>
#include <unordered_map>
#include <array>

class PokemonInfo
{
private:
  std::string tipo;
  std::string descripcion;
  std::unordered_map<std::string, int> ataquesDisponibles;
  std::array<int, 3> experienciaProximoNivel;

public:
  PokemonInfo(std::string tipo, std::string descripcion, std::unordered_map<std::string, int> ataques, std::array<int, 3> experienciaNivel);

  // Retorna el tipo del Pokémon
  std::string getTipo() const;

  // Retorna la descripción del Pokémon
  std::string getDescripcion() const;

  // Retorna el mapa de ataques disponibles del Pokémon
  std::unordered_map<std::string, int> getAtaquesDisponibles() const;

  // Retorna el array de experiencia necesaria para los próximos niveles
  std::array<int, 3> getExperienciaProximoNivel() const;

  void serializar(std::ofstream& outfile);

  void deserializar(std::ifstream& infile);

  friend std::ostream &operator<<(std::ostream &os, const PokemonInfo &p);
};