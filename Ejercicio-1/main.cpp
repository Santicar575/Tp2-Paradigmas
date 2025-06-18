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
  
  cout << string(100, '=') << endl << "Se creará una Pokedex vinculada al archivo datapokedex.bin" << endl << "y se agregarán los Pokemones Squirtle, Bulbasaur y Charmander." << endl << "Notar que si ya se corrió el programa, los pokemones fueron recuperados del archivo y ya se encuentran registrados "<< endl << "(a menos que se haya borrado el archivo datapokedex.bin corriendo: make cleandata)." << endl << string(100, '=') << endl;

  Pokedex pokedex("datapokedex.bin");
  
  pokedex.agregar(Squirtle, SquirtleInfo);
  pokedex.agregar(Bulbasaur, BulbasaurInfo);
  pokedex.agregar(Charmander, CharmanderInfo);

  cout << endl << string(100, '=') << endl << "Se buscarán a los pokemones Squirtle (debe estar y mostrarse su info) y"<<endl<<"Pikachu, (debe imprimir Pokemon desconocido)." << endl << string(100, '=') << endl << endl;

  
  Pokemon squirtle("Squirtle", 870);
  Pokemon pikachu("Pikachu", 390);
  pokedex.mostrar(squirtle);
  pokedex.mostrar(pikachu);
  cout<<endl;

  cout << endl << string(100, '=') << endl << "Se mostrarán todos los pokemones utilizando el método mostrarTodos()" << endl << string(100, '=') << endl << endl;

  pokedex.mostrarTodos();
  
  cout << endl << string(100, '=') << endl << "Se creará una nueva Pokedex cargada desde el mismo archivo que la anterior." << endl << "Debe mostrar los mismos pokemones al llamar a mostrarTodos()." << endl << string(100, '=') << endl << endl;

  Pokedex nuevapokedex("datapokedex.bin");

  nuevapokedex.mostrarTodos();

  return 0;
}