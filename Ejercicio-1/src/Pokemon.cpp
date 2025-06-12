#include "Pokemon.hpp"
#include <iostream>
#include <fstream>
constexpr int SPACES_BEFORE = 10;

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
  os << std::string(SPACES_BEFORE, ' ') << "========== || " << p.name << ", Experiencia: " << p.experience << " || ==========" << std::endl;
  return os;
}

void Pokemon::serializar(std::ofstream &outfile) const
{
  // Para serializar strings primero se guarda el largo, luego el contenido
  size_t largoName = name.size();
  outfile.write(reinterpret_cast<const char *>(&largoName), sizeof(largoName));
  outfile.write(name.c_str(), largoName);

  outfile.write(reinterpret_cast<const char *>(&experience), sizeof(experience));
}

void Pokemon::deserializar(std::ifstream &infile)
{
  // para deserializar strings, primero se obtiene el largo, se resizea el destinatario, luego se lee esa cantidad de caracteres
  size_t largoName;
  infile.read(reinterpret_cast<char *>(&largoName), sizeof(largoName));
  name.resize(largoName);
  infile.read(&name[0], largoName);

  infile.read(reinterpret_cast<char *>(&experience), sizeof(experience));
}