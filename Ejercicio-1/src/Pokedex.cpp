#include "Pokedex.hpp"
#include <fstream>
#include <iostream>

void Pokedex::agregar(Pokemon &p, PokemonInfo &info)
{
  auto it = data.find(p);
  if (it != data.end())
  {
    std::cout << "Este pokemon ya se encuentra registrado en tu pokedex" << std::endl;
    return;
  };
  data.emplace(p, info);
  if(linkedFile.first){
    saveNew(p, info);
  }
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

void Pokedex::serializarCompleta()
{
  // se intenta abrir el archivo linkeado
  std::ofstream outfile_linked(linkedFile.second, std::ios::binary);
  if (!outfile_linked)
  {
    std::cerr << "No se pudo abrir el archivo: " << linkedFile.second << std::endl;
    return;
  }

  // Se guarda la cantidad de pokemones guardados, y luego se serializa cada pokemon y su info
  size_t numEncontrados = data.size();
  outfile_linked.write(reinterpret_cast<char *>(&numEncontrados), sizeof(size_t));

  for (auto &pokemon : data)
  {
    pokemon.first.serializar(outfile_linked);
    pokemon.second.serializar(outfile_linked);
  }
}

void Pokedex::deserializar()
{
  std::ifstream infile(linkedFile.second, std::ios::binary);
  if (!infile)
  {
    std::cerr << "No se pudo abrir el archivo: " << linkedFile.second << std::endl;
    return;
  }

  size_t numEncontrados = 0;
  infile.read(reinterpret_cast<char *>(&numEncontrados), sizeof(size_t));

  for (size_t i = 0; i < numEncontrados; ++i)
  {
    // Inicialización con valores temporales que serán sobreescritos

    std::unordered_map<std::string, int> tempMap;
    std::array<int, 3> tempArr;
    PokemonInfo info("", "", tempMap, tempArr);
    Pokemon p("", 0);

    p.deserializar(infile);
    info.deserializar(infile);

    data.emplace(p, info);
  }
}

void Pokedex::saveNew(Pokemon &p, PokemonInfo &info)
{
  // se intenta abrir el archivo linkeado
  // Abrir el archivo en modo append binario para agregar el nuevo Pokemon y su info
  std::ofstream outfile(linkedFile.second, std::ios::app | std::ios::binary);
  if (!outfile)
  {
    std::cerr << "No se pudo abrir el archivo: " << linkedFile.second << std::endl;
    return;
  }
  // Serializar el nuevo Pokemon y su info al final del archivo
  p.serializar(outfile);
  info.serializar(outfile);

  //Se debe actualizar el contador al principio del archivo
  size_t nuevoNumEncontrados = data.size();
  // Se abre el archivo para poder leer (no trunca) y escribir en modo binario
  std::fstream file(linkedFile.second, std::ios::in | std::ios::out | std::ios::binary);
  if (file)
  {
    // Se ubica el puntero de escritura en el principio del archivo (donde se guarda el tamaño de la pokedex)
    file.seekp(0, std::ios::beg);
    // Se actualiza el tamaño de la pokedex
    file.write(reinterpret_cast<char *>(&nuevoNumEncontrados), sizeof(size_t));
  }
}

Pokedex::Pokedex(std::string filePath)
{
  // se intenta leer el archivo
  std::ifstream infile(filePath);
  if (!infile)
  {
    // Si el archivo no existe, se crea
    std::ofstream outfile(filePath);
    if (!outfile)
    {
      std::cerr << "No se pudo crear el archivo: " << filePath << std::endl;
    }
    else
    {
      std::cout << std::endl << "Al no encontrarse el archivo, se creará para poder almacenar los datos de la pokedex." << std::endl;
      std::cout << "Archivo creado: " << filePath << std::endl << std::endl;
      linkedFile.first = true;
      linkedFile.second = filePath;
    }
    return;
  }
  // Si se encuentra el archivo, el mismo se linkea a la pokedex y se leen sus datos
  else
  {
    linkedFile.first = true;
    linkedFile.second = filePath;
    deserializar();
    std::cout << "La pokedex se encuentra linkeada con el archivo " << filePath << std::endl;
  }
}
