#include "macro.hpp"

int main() {
    //calibration("Dati/calibrazione.csv");
    //Range Germanio 100-250    Range Silicio  450-610
    expfit("Dati/germanio.csv", 100, 150);
    lnfit_ger("Dati/germanio.csv", 100, 150);
    lnfit_sil("Dati/silicio.csv", 450, 600);
    //Test_fit("Dati/germanio.csv");
    double_exp("Dati/silicio.csv", "Dati/germanio.csv");
}


