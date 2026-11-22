#include "macro.hpp"

int main() {
    calibration("Dati/calibrazione.csv");
    //expfit("Dati/germanio.csv");
    //Range Germanio 100-250    Range Silicio 
    lnfit("Dati/silicio.csv", 490, 610);
}


