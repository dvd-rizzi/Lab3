#include "macro.hpp"

int main() {
    //calibration("Dati/calibrazione.csv");
    //Range Germanio 100-250    Range Silicio  450-610
    lnfit_ger("Dati/germanio.csv", 100, 200);
    lnfit_sil("Dati/silicio.csv", 400, 650);
    //Test_fit("Dati/germanio.csv");
}


