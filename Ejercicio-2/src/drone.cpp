#include "drone.hpp"

std::mutex Drone::printMutex;

Drone::Drone(int droneId, int rz, int lz) : 
    id(droneId),
    rightZone(rz),
    leftZone(lz) {}

void Drone::safePrint(std::string text){
    // Bloquea simultaneamente las zonas laterales para evitar interferencia con drones vecinos.
    // std::lock garantiza que no haya interbloqueo entre multiples hilos.
    printMutex.lock();
    std::cout << text << std::endl;
    printMutex.unlock();
}

void Drone::takeOff(std::vector<std::mutex>& zones){
    safePrint("Dron " + std::to_string(id) + " esperando para despegar...");

    // hago un lock de los mutex de las zonas a la derecha e izquierda
    // Utilizo std::lock para evitar deadlocks, ya que bloquea ambos mutex al mismo tiempo
    std::lock(zones[rightZone],zones[leftZone]);

    safePrint("Dron " + std::to_string(id) + " despegando...");
    std::this_thread::sleep_for(std::chrono::seconds(SECONDS_TO_REACH_10_M));
    safePrint("Dron " + std::to_string(id) + " alcanzó altura de 10m");

    // Desbloqueo los mutex de las zonas a la derecha e izquierda para permitir que otros drones puedan despegar
    zones[rightZone].unlock();
    zones[leftZone].unlock();
}