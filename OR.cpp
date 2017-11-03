#include "OR.h"

// class OR : public Connector {
//  public:

// Pushes back an "|" character into the connector vector.
void OR::setConVector(char* Or) {
    connectors.push_back(Or);
}

// Verifies that the && has been executed.
bool OR::execute() {

}