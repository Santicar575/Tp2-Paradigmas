#include "drone.hpp"

#define DRONES_AMOUNT 5

int main(){
    // Creo un vector de mutexes, uno por zona
    std::vector<std::mutex> zones(DRONES_AMOUNT);

    // Creo un vector de threads
    std::vector<std::thread> threads;

    // Creo los drones y los lanzo en threads
    // Cada dron tiene un id, una zona a la derecha y una a la izquierda
    for(int i=0; i<DRONES_AMOUNT; i++){
        threads.emplace_back([i, &zones](){
            // El dron i tiene como zona a la derecha i y a la izquierda i+1 (circular)
            // Si i es el último dron, su zona a la izquierda será 0 (manejado por el operador %)
            Drone d(i, i, (i + 1) % DRONES_AMOUNT);
            d.takeOff(zones);
        });
    }

    for (auto& t : threads) t.join();
    
    return 0;
}
