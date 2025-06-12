#include <queue>
#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <condition_variable>

#define CANT_SENSORES 3
#define CANT_TAREAS_POR_SENSOR 5
#define TIEMPO_CREACION_TAREA 175
#define CANT_ROBOTS 3
#define TIEMPO_PROCESAMIENTO 250

// Estructura para representar una tarea
struct Tarea {
    int idSensor;
    int idTarea;
    std::string descripcion;
    Tarea(int idSensor, int idTarea, const std::string& descripcion)
        : idSensor(idSensor), idTarea(idTarea), descripcion(descripcion) {};
};

void safePrint(std::string text, std::mutex& printMutex);
void sensor(int idSensor, std::queue<Tarea>& tareas, std::condition_variable& cv, std::mutex& printMutex, std::mutex& queueMutex, std::mutex& cantSensoresMutex, int& sensoresTerminados, bool& terminado);
void robot(int idRobot, std::queue<Tarea>& tareas, std::condition_variable& cv, std::mutex& printMutex, std::mutex& queueMutex, bool& terminado);

int main(){
    std::queue<Tarea> tareas;

    int sensoresTerminados = 0;

    std::condition_variable cv;

    std::mutex printMutex;
    std::mutex queueMutex;
    std::mutex cantSensoresMutex;

    bool terminado = false;

    // Creo los hilos de sensores y robots
    std::vector<std::jthread> sensores;
    for(int i=1; i <= CANT_SENSORES; i++){
        sensores.emplace_back(sensor, i, std::ref(tareas), std::ref(cv), std::ref(printMutex), std::ref(queueMutex), std::ref(cantSensoresMutex), std::ref(sensoresTerminados), std::ref(terminado));
    }

    std::vector<std::jthread> robots;
    for(int i=1; i <= CANT_ROBOTS; i++){
        robots.emplace_back(robot, i, std::ref(tareas), std::ref(cv), std::ref(printMutex), std::ref(queueMutex), std::ref(terminado));
    }

    return 0;
}

// Función para imprimir de forma segura en la consola, evitando race conditions
void safePrint(std::string text, std::mutex& printMutex){
    std::lock_guard<std::mutex> lock(printMutex);
    std::cout<<text<<std::endl;
}


void sensor(int idSensor, std::queue<Tarea>& tareas, std::condition_variable& cv, std::mutex& printMutex, std::mutex& queueMutex, std::mutex& cantSensoresMutex, int& sensoresTerminados, bool& terminado){
    int nroTarea;
    for(int i=1; i <= CANT_TAREAS_POR_SENSOR; i++){
        {
            // Genero una tarea y la agrego a la cola
            nroTarea = idSensor*10+i;
            // Uso un lock_guard para asegurar que la cola de tareas se modifique de forma segura sin producir race conditions
            std::lock_guard<std::mutex> lock(queueMutex);
            tareas.push(Tarea(idSensor, nroTarea, "Tarea nro "+std::to_string(nroTarea)));
            safePrint("[Sensor " + std::to_string(idSensor) + "] Agrego: Tarea nro " + std::to_string(nroTarea), printMutex);
        }
        // Notifico a un robot que hay una nueva tarea
        cv.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(TIEMPO_CREACION_TAREA));
    }
    {
        // Una vez que el sensor termina de crear tareas, incrementa el contador de sensores terminados
        std::lock_guard<std::mutex> lock(cantSensoresMutex);
        sensoresTerminados++;
        if(sensoresTerminados == CANT_SENSORES){
            // Si todos los sensores han terminado, notifico a los robots que ya se terminó la creación de tareas
            terminado = true;
            cv.notify_all();
        }
    }
}

void robot(int idRobot, std::queue<Tarea>& tareas, std::condition_variable& cv, std::mutex& printMutex, std::mutex& queueMutex, bool& terminado){
    while(true){
        // Espero a que haya tareas disponibles o que los sensores hayan terminado
        std::unique_lock<std::mutex> ul(queueMutex);
        // Uso una condición variable para esperar a que haya tareas o que se indique que se ha terminado
        cv.wait(ul, [&tareas, &terminado] {
            return !tareas.empty() || terminado;
        });
        // Si hay tareas, las proceso
         // Si no hay tareas y los sensores han terminado, salgo del bucle
        if(!tareas.empty()){
            // Guardo la tarea a procesar y la elimino de la cola
            Tarea tarea = tareas.front();
            tareas.pop();
            safePrint("[ROBOT " + std::to_string(idRobot) + "] Procesando:", printMutex);
            safePrint("\tTarea ID: " + std::to_string(tarea.idTarea) + ", Sensor ID: " + std::to_string(tarea.idSensor) + ", Descripcion: " + tarea.descripcion, printMutex);
            //Desbloqueo el mutex para que los sensores puedan seguir creando tareas
            ul.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(TIEMPO_PROCESAMIENTO));
        }else if(terminado){
            safePrint("[ROBOT " + std::to_string(idRobot) + "] Terminado", printMutex);
            break;
        }
    }
}