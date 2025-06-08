#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <string>

#define SECONDS_TO_REACH_10_M 5

class Drone{
    private:
        int id;
        int rightZone;
        int leftZone;
        static std::mutex printMutex;
        // Funcion para imprimir de forma segura (sin interferencias de otros hilos)
        void safePrint(std::string text);
    public:
        // Constructor que recibe el id del dron, la zona a la derecha y la zona a la izquierda
        Drone(int droneId, int rz, int lz);
        // Funcion que simula el despegue del dron
        // Toma los mutex de las zonas a la derecha e izquierda, simula el despegue y libera los mutex
        void takeOff(std::vector<std::mutex>& zones);
        ~Drone() = default;
};
