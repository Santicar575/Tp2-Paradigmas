#include "PokemonInfo.hpp"
#include <string>
#include <fstream>
constexpr int SPACES_BEFORE = 10;

PokemonInfo::PokemonInfo(std::string tipo, std::string descripcion, std::unordered_map<std::string, int> ataques, std::array<int, 3> experienciaNivel) : tipo(tipo), descripcion(descripcion), ataquesDisponibles(ataques), experienciaProximoNivel(experienciaNivel) {};

// retorna el tipo de pokemon
std::string PokemonInfo::getTipo() const { return tipo; }

// Retorna la descripción del Pokémon
std::string PokemonInfo::getDescripcion() const { return descripcion; }

// Retorna el mapa de ataques disponibles del Pokémon
std::unordered_map<std::string, int> PokemonInfo::getAtaquesDisponibles() const { return ataquesDisponibles; }

// Retorna el array de experiencia necesaria para los próximos niveles
std::array<int, 3> PokemonInfo::getExperienciaProximoNivel() const { return experienciaProximoNivel; }

std::ostream &operator<<(std::ostream &os, const PokemonInfo &p)
{
  // Se imprimen uno a uno los atributos de la PokemonInfo
  os << std::string(SPACES_BEFORE, ' ') << "| Tipo: " << p.getTipo() << std::endl
     << std::string(SPACES_BEFORE, ' ') << std::string(100, '-') << std::endl
     << std::string(SPACES_BEFORE, ' ') << "| Descripción: " << p.getDescripcion() << std::endl
     << std::string(SPACES_BEFORE, ' ') << std::string(100, '-') << std::endl
     << std::string(SPACES_BEFORE, ' ') << "| Ataques disponibles: ";
  for (const auto &ataque : p.getAtaquesDisponibles())
  {
    os << ataque.first << " (daño: " << ataque.second << ") ";
  }
  os << std::endl
     << std::string(SPACES_BEFORE, ' ') << std::string(100, '-') << std::endl;
  os << std::string(SPACES_BEFORE, ' ') << "| Experiencia requerida para cada nivel: ";
  auto exp = p.getExperienciaProximoNivel();
  for (size_t i = 0; i < exp.size(); ++i)
  {
    os << exp[i];
    os << " (nivel "<<i<<")";
    if (i < exp.size() - 1)
      os << ", ";
  }
  os << std::endl
     << std::string(SPACES_BEFORE, ' ') << std::string(100, '-') << std::endl;
  return os;
}

void PokemonInfo::serializar(std::ofstream &outfile)
{
  // Para serializar strings primero se guarda el largo, luego el contenido
  size_t largoTipo = tipo.size();
  outfile.write(reinterpret_cast<char *>(&largoTipo), sizeof(largoTipo));
  outfile.write(tipo.c_str(), largoTipo);

  size_t largoDescripcion = descripcion.size();
  outfile.write(reinterpret_cast<char *>(&largoDescripcion), sizeof(largoDescripcion));
  outfile.write(descripcion.c_str(), largoDescripcion);

  // serializa el numero de ataques primero, luego se serializan los contenidos de cada ataque
  size_t numAtaques = ataquesDisponibles.size();
  outfile.write(reinterpret_cast<char *>(&numAtaques), sizeof(numAtaques));
  for (const auto &ataque : ataquesDisponibles)
  {
    size_t largoNombre = ataque.first.size();
    outfile.write(reinterpret_cast<char *>(&largoNombre), sizeof(largoNombre));
    outfile.write(ataque.first.c_str(), largoNombre);
    outfile.write(reinterpret_cast<const char *>(&ataque.second), sizeof(ataque.second));
  }

  outfile.write(reinterpret_cast<const char *>(experienciaProximoNivel.data()), experienciaProximoNivel.size() * sizeof(int));
}

void PokemonInfo::deserializar(std::ifstream &infile)
{
  // para deserializar strings, primero se obtiene el largo, se resizea el destinatario, luego se lee esa cantidad de caracteres
  size_t largoTipo;
  infile.read(reinterpret_cast<char *>(&largoTipo), sizeof(largoTipo));
  tipo.resize(largoTipo);
  infile.read(&tipo[0], largoTipo);

  size_t largoDescripcion;
  infile.read(reinterpret_cast<char *>(&largoDescripcion), sizeof(largoDescripcion));
  descripcion.resize(largoDescripcion);
  infile.read(&descripcion[0], largoDescripcion);

  // Para reconstruir el diccionario primero se obtiene el largo, luego uno por uno los contenidos.
  size_t numAtaques;
  infile.read(reinterpret_cast<char *>(&numAtaques), sizeof(numAtaques));
  ataquesDisponibles.clear();
  for (size_t i = 0; i < numAtaques; ++i)
  {
    size_t largoNombre;
    infile.read(reinterpret_cast<char *>(&largoNombre), sizeof(largoNombre));
    std::string nombreAtaque(largoNombre, '\0');
    infile.read(&nombreAtaque[0], largoNombre);
    int danio;
    infile.read(reinterpret_cast<char *>(&danio), sizeof(danio));
    // se agrega al diccionario el elemento con su valor correspondiente
    ataquesDisponibles[nombreAtaque] = danio;
  }

  infile.read(reinterpret_cast<char *>(experienciaProximoNivel.data()), experienciaProximoNivel.size() * sizeof(int));
}