#include "SEMICOLON.h"

// class SEMICOLON : public Connector {
//  public:

// Pushes back a ";" character into the connector vector.
void SEMICOLON::setConVector(char* Semicolon) {
    connectors.push_back(Semicolon);
}

// Verifies that the && has been executed.
bool SEMICOLON::execute() {
    return false;
}
