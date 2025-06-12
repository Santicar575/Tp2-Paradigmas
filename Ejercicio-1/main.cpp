#include <iostream>
#include "Pokemon.hpp"
#include "PokemonInfo.hpp"
#include "Pokedex.hpp"
#include <string>

using namespace std;

int main()
{

  Pokemon Squirtle("Squirtle", 100);
  PokemonInfo SquirtleInfo("Agua", "Una tortuga pequeña que lanza chorros de agua.",
  {{"Pistola Agua", 4}, {"Hidrobomba", 6}, {"Danza Lluvia", 5}},
  {0, 400, 1000});

  Pokemon Bulbasaur("Bulbasaur", 270);
  PokemonInfo BulbasaurInfo("Planta", "Tiene una semilla en su lomo que crece con el tiempo",
  {{"Latigazo", 4}, {"Hoja Afilada", 6}, {"Rayo Solar", 5}},
  {0, 300, 1100});

  Pokemon Charmander("Charmander", 633);
  PokemonInfo CharmanderInfo("Fuego", "Una lagartija con una llama en su cola",
  {{"Ascuas", 4}, {"Lanzallamas", 6}, {"Giro Fuego", 5}},
  {0, 250, 1300});
  
  cout << string(100, '=') << endl << "Se creará una Pokedex vinculada al archivo datapokedex.bin" << endl << "y se agregarán los Pokemones Squirtle, Bulbasaur y Charmander." << endl << string(100, '=') << endl;

  Pokedex pokedex("datapokedex.bin");
  
  pokedex.agregar(Squirtle, SquirtleInfo);
  pokedex.agregar(Bulbasaur, BulbasaurInfo);
  pokedex.agregar(Charmander, CharmanderInfo);
  
  Pokemon squirtle("Squirtle", 870);
  Pokemon pikachu("Pikachu", 390);
  pokedex.mostrar(squirtle);
  pokedex.mostrar(pikachu);
  cout<<endl;

  pokedex.mostrarTodos();
  
  Pokemon HIJODELVIENTO = Pokemon("HIJODELVIENTO", 633);
  PokemonInfo HIJODELVIENTOInfo = PokemonInfo("Fuego", "Una lagartija con una llama en su cola",
  {{"Ascuas", 4}, {"Lanzallamas", 6}, {"Giro Fuego", 5}},
  {0, 250, 1300});
  pokedex.agregar(HIJODELVIENTO, HIJODELVIENTOInfo);

  Pokedex pimpumpam("datapokedex.bin");

  cout<< endl<< string(100, 'W') << endl;

  pimpumpam.mostrarTodos();

  return 0;
}