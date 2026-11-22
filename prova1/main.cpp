#include "macro.hpp"

int main() {
    //calibration("Dati/calibrazione.csv");
    //expfit("Dati/germanio.csv");
    //Range Germanio 100-250    Range Silicio  450-610
    lnfit("Dati/germanio.csv", 100, 200);
    Test_fit("Dati/germanio.csv");
}


