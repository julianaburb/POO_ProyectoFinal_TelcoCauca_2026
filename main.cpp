// PROYECTO INTEGRADOR TELCOCAUCA - MAIN FINAL
// Todo se ejecuta de corrido y separado por partes, una por cada modulo de la guia.
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <functional>   // std::ref

// Modulo 1
#include "Tecnico.h"
#include "Antena.h"
#include "Torre.h"
// Modulo 2
#include "NodoRedInteligente.h"
#include "ExcepcionNodoRed.h"
// Modulo 3
#include "DispositivoComunicacion.h"
#include "RouterWiFi.h"
#include "GatewayLoRa.h"
#include "SwitchFibra.h"
// Modulo 4
#include "SupervisorRed.h"
#include "EventoIngenieria2027.h"
#include "Registro.h"
// Modulo 5
#include "ServidorCentral.h"
#include "ClienteTCP.h"
#include "TelemetriaUDP.h"

int main() {
    std::cout << "\n==================== PARTE 1: INFRAESTRUCTURA FISICA ====================\n";

    Tecnico tecnico1(1, "Carlos Munoz", "Radiofrecuencia");
    Tecnico tecnico2(2, "Laura Gomez", "Fibra optica");

    Antena antena1(101, 3500.0, "5G");
    Antena antena2(102, 1900.0, "4G");
    Antena antena3(103, 3700.0, "5G");

    // Asociacion 1:1, cada antena tiene un tecnico responsable
    antena1.asignarResponsable(&tecnico1);
    antena2.asignarResponsable(&tecnico2);
    antena3.asignarResponsable(&tecnico1);

    // Asociacion 1:N, una torre guarda varias antenas en un std::vector<Antena*>
    Torre torre(1, "Popayan - Cerro de las Tres Cruces", 45.0);
    torre.agregarAntena(&antena1);
    torre.agregarAntena(&antena2);
    torre.agregarAntena(&antena3);

    tecnico1.mostrarInformacion();
    tecnico2.mostrarInformacion();
    torre.mostrarReporteTorre();

    std::cout << "\n==================== PARTE 2: NODO DE RED INTELIGENTE ====================\n";

    // Primero dos nodos validos. Van en un try porque el constructor puede lanzar ExcepcionNodoRed.
    try {
        NodoRedInteligente n1("192.168.1.20", "AA:BB:CC:DD:EE:01", true, "Temperatura", 35.5, 1, 120, 40.0);
        NodoRedInteligente n2("192.168.1.21", "AA:BB:CC:DD:EE:02", true, "Humedad",     60.0, 2,  80, 25.5);

        // operador << sobrecargado como funcion amiga
        std::cout << "\n> Nodo 1:\n" << n1;
        std::cout << "\n> Nodo 2:\n" << n2;

        // operador + : suma la carga de procesamiento (40 + 25.5 = 65.5)
        NodoRedInteligente suma = n1 + n2;
        std::cout << "\n> Resultado de n1 + n2 (carga sumada):\n" << suma;
    }
    catch (const ExcepcionNodoRed& e) {
        std::cout << "[ExcepcionNodoRed] " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "[Error general] " << e.what() << std::endl;
    }

    // Errores forzados que pide la guia: lectura fuera de rango e IP vacia.
    // Cada uno en su propio try para que el primero no impida mostrar el segundo.
    std::cout << "\n> Error forzado 1: lectura fuera de rango (120)\n";
    try {
        NodoRedInteligente malo1("192.168.1.30", "AA:BB:CC:DD:EE:03", true, "Temperatura", 120.0, 3, 50, 10.0);
    }
    catch (const ExcepcionNodoRed& e) {   // primero la especifica
        std::cout << "[ExcepcionNodoRed capturada] " << e.what() << std::endl;
    }
    catch (const std::exception& e) {     // despues la general
        std::cout << "[Error general] " << e.what() << std::endl;
    }

    std::cout << "\n> Error forzado 2: direccion IP vacia\n";
    try {
        NodoRedInteligente malo2("", "AA:BB:CC:DD:EE:04", true, "Humedad", 50.0, 4, 30, 15.0);
    }
    catch (const ExcepcionNodoRed& e) {
        std::cout << "[ExcepcionNodoRed capturada] " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "[Error general] " << e.what() << std::endl;
    }

    std::cout << "\n==================== PARTE 3 Y 4: SUPERVISION POLIMORFICA + EVENTOS 2027 (HILOS EN PARALELO) ====================\n";

    // vector de punteros a la clase base, con punteros para que no haya slicing
    std::vector<DispositivoComunicacion*> red;
    red.push_back(new RouterWiFi("192.168.10.1"));
    red.push_back(new GatewayLoRa("192.168.10.2"));
    red.push_back(new SwitchFibra("192.168.10.3"));
    red.push_back(new RouterWiFi(""));   // IP vacia a proposito -> ExcepcionNodoRed en el hilo
    red.push_back(nullptr);              // puntero nulo a proposito -> invalid_argument en el hilo

    std::vector<EventoIngenieria2027*> agenda;
    agenda.push_back(new EventoIngenieria2027(
        "NVIDIA GTC 2027",
        "15 al 18 de marzo de 2027",
        "San Jose, California (EE.UU.) - San Jose McEnery Convention Center",
        "IA y computacion acelerada: infraestructura de IA, IA agentica, CUDA, IA fisica y robotica",
        2027));
    agenda.push_back(new EventoIngenieria2027(
        "ITW Global 2027 (International Telecoms Week)",
        "10 al 13 de mayo de 2027",
        "National Harbor, Maryland (EE.UU.) - Gaylord National Resort & Convention Center",
        "Conectividad e infraestructura digital: operadores, data centers, nube y redes para la era de la IA",
        2027));
    agenda.push_back(new EventoIngenieria2027(
        "Telco Transformation LATAM 2027 (Conecta Latam)",
        "Agosto de 2027 (proyectado, fecha oficial por confirmar)",
        "Rio de Janeiro, Brasil (sede de las ediciones 2025 y 2026)",
        "Transformacion de operadores: IA, OpenRAN, automatizacion de redes, IoT, nube y ciberseguridad",
        2027));

    int transmisionesExitosas = 0;   // lo tocan todos los hilos de supervision (protegido con mtx_contador)
    int eventosMostrados = 0;        // solo lo toca el hilo de eventos
    SupervisorRed supervisor;

    // la agenda arranca primero en su propio hilo y corre al mismo tiempo que la supervision
    std::thread hiloEventos(procesarAgendaEventos2027, std::ref(agenda), std::ref(eventosMostrados));

    // un hilo por dispositivo: (&Clase::metodo, &instancia, parametros)
    // con std::ref el hilo modifica el contador del main y no una copia
    std::vector<std::thread> hilosSupervision;
    for (DispositivoComunicacion* dev : red) {
        hilosSupervision.push_back(std::thread(&SupervisorRed::supervisar, &supervisor, dev,
                                               std::ref(transmisionesExitosas)));
    }

    // join a todos antes de seguir (si un thread se destruye sin join el programa se cae)
    for (auto& t : hilosSupervision) {
        if (t.joinable()) {
            t.join();
        }
    }
    hiloEventos.join();

    registrarEventoSeguro("Transmisiones exitosas: " + std::to_string(transmisionesExitosas)
                          + " de " + std::to_string(red.size()) + " dispositivos");
    registrarEventoSeguro("Eventos 2027 registrados: " + std::to_string(eventosMostrados));

    std::cout << "\n==================== PARTE 5: CLIENTE-SERVIDOR TCP ====================\n";

    // el servidor va en un hilo porque accept() bloquea esperando clientes
    std::thread hiloServidor(iniciarServidorTCP);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));   // tiempo para socket, bind y listen

    // tramas de los 3 clientes: el nodo inteligente, el router y el gateway
    std::vector<std::string> tramas;
    try {
        NodoRedInteligente nodoEstacion("192.168.1.20", "AA:BB:CC:DD:EE:01", true, "Temperatura", 35.5, 1, 120, 40.0);
        tramas.push_back(nodoEstacion.serializar());
    }
    catch (const std::exception& e) {
        registrarEventoSeguro(std::string("[Error creando nodo] ") + e.what());
    }
    for (std::size_t i = 0; i < 2 && i < red.size(); ++i) {
        if (red[i] != nullptr) {                       // misma guarda contra nullptr de la Parte 3
            tramas.push_back(red[i]->serializar());    // serializar() es el metodo de ITransmisible
        }
    }

    // cada cliente en su propio hilo, los 3 se conectan al mismo tiempo
    // y el servidor tiene que atenderlos en paralelo (un hilo por cliente)
    std::vector<std::thread> hilosClientes;
    for (const std::string& t : tramas) {
        hilosClientes.push_back(std::thread([t]() {
            try {
                enviarTramaTCP(t);
            }
            catch (const std::exception& e) {
                registrarEventoSeguro(std::string("[Error cliente TCP] ") + e.what());
            }
        }));
    }
    for (auto& h : hilosClientes) {
        if (h.joinable()) {
            h.join();
        }
    }
    hiloServidor.join();   // el servidor termina despues de atender a los clientes

    // Error forzado: el servidor ya se apago, asi que el connect debe fallar y capturarse
    std::cout << "\n> Error forzado: cliente intentando conectarse sin servidor\n";
    try {
        enviarTramaTCP("SENSOR|9|192.168.1.99|20");
    }
    catch (const std::runtime_error& e) {
        std::cout << "[runtime_error capturado] " << e.what() << std::endl;
    }

    std::cout << "\n==================== PARTE 6: TELEMETRIA UDP ====================\n";

    // el receptor va en un hilo porque recvfrom bloquea mientras espera
    std::thread hiloReceptor([]() {
        try { recibirTelemetriaUDP(2); }
        catch (const ExcepcionRedUDP& e) { registrarEventoSeguro(std::string("[ExcepcionRedUDP] ") + e.what()); }
        catch (const std::exception& e)  { registrarEventoSeguro(std::string("[Error general] ") + e.what()); }
    });
    std::this_thread::sleep_for(std::chrono::milliseconds(500));   // tiempo para el bind

    try {
        NodoRedInteligente sensor1("192.168.1.20", "AA:BB:CC:DD:EE:01", true, "Temperatura", 35.5, 1, 120, 40.0);
        NodoRedInteligente sensor2("192.168.1.21", "AA:BB:CC:DD:EE:02", true, "Humedad", 60.0, 2, 80, 25.5);
        enviarTelemetriaUDP(sensor1);
        enviarTelemetriaUDP(sensor2);
    }
    catch (const std::exception& e) {
        registrarEventoSeguro(std::string("[Error emisor UDP] ") + e.what());
    }
    hiloReceptor.join();

    // Error forzado: receptor esperando sin que nadie envie -> timeout a los 3 s
    std::cout << "\n> Error forzado: receptor UDP sin emisor (timeout de 3 s)\n";
    try {
        recibirTelemetriaUDP(1);
    }
    catch (const ExcepcionRedUDP& e) {
        std::cout << "[ExcepcionRedUDP capturada] " << e.what() << std::endl;
    }
    // liberar memoria al final, porque la Parte 5 todavia usa red[0] y red[1]
    // y aca ya terminaron todos los hilos
    for (std::size_t i = 0; i < red.size(); ++i) {
        if (red[i] != nullptr) {
            delete red[i];   // como el destructor es virtual, tambien se llama el de la hija
        }
        red[i] = nullptr;
    }
    red.clear();

    for (std::size_t i = 0; i < agenda.size(); ++i) {
        if (agenda[i] != nullptr) {
            delete agenda[i];
        }
        agenda[i] = nullptr;
    }
    agenda.clear();

    // aca ya solo queda el hilo principal, por eso el cout va sin mutex
    std::cout << "\nSistema TelcoCauca finalizado correctamente." << std::endl;
    return 0;
}
