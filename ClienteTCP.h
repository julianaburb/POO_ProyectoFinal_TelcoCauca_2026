#ifndef CLIENTETCP_H
#define CLIENTETCP_H
#include <string>

// Cliente TCP (estacion base): se conecta al ServidorCentral con connect,
// le manda una trama con send y espera la respuesta (ACK) con recv.
// Si algo falla lanza std::runtime_error.
void enviarTramaTCP(const std::string& trama);

#endif