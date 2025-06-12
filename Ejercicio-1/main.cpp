#include <iostream>
#include "Pokemon.hpp"
#include "PokemonInfo.hpp"
#include "Pokedex.hpp"

int main()
{

  Pokemon Squirtle = Pokemon("Squirtle", 100);
  PokemonInfo SquirtleInfo = PokemonInfo("Agua", "Una tortuga pequeña que lanza chorros de agua.",
  {{"Pistola Agua", 4}, {"Hidrobomba", 6}, {"Danza Lluvia", 5}},
  {0, 400, 1000});

  Pokemon Bulbasaur = Pokemon("Bulbasaur", 270);
  PokemonInfo BulbasaurInfo = PokemonInfo("Planta", "Tiene una semilla en su lomo que crece con el tiempo",
  {{"Latigazo", 4}, {"Hoja Afilada", 6}, {"Rayo Solar", 5}},
  {0, 300, 1100});

  Pokemon Charmander = Pokemon("Charmander", 633);
  PokemonInfo CharmanderInfo = PokemonInfo("Fuego", "Una lagartija con una llama en su cola",
  {{"Ascuas", 4}, {"Lanzallamas", 6}, {"Giro Fuego", 5}},
  {0, 250, 1300});

  Pokedex pokedex;

  pokedex.agregar(Squirtle, SquirtleInfo);
  pokedex.agregar(Bulbasaur, BulbasaurInfo);
  pokedex.agregar(Charmander, CharmanderInfo);

  Pokemon squirtle = Pokemon("Squirtle", 870);
  Pokemon pikachu = Pokemon("Pikachu", 390);

  pokedex.mostrar(squirtle);
  pokedex.mostrar(pikachu);
  std::cout<<std::endl;

  pokedex.mostrarTodos();

  return 0;
}