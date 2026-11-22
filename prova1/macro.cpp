#include "macro.hpp"

void calibration(TString data) {
  TGraphErrors *dati = new TGraphErrors(data, "%lg %lg %lg");
  TF1 *linear = new TF1("linear_function", "[0]*x + [1]");
  linear->SetParameters(1, 0);
  linear->SetParNames("coeff_ang", "offset");
  linear->SetTitle("dati di calibrazione");
  dati->Fit(linear);
  TCanvas *c1 = new TCanvas("c1", "Retta di calibrazione", 800, 600);
  dati->Draw("AP");
  dati->SetMarkerStyle(20);
  dati->SetLineColor(4);
  dati->SetMarkerColor(4);
  dati->SetTitle("");
  dati->GetXaxis()->SetTitle("Multimetro (mV)");
  dati->GetYaxis()->SetTitle("Oscilloscopio (mV)");
  linear->Draw("same");
  c1->SetGrid();
  c1->SaveAs("Immagini/calibrazione.pdf");
}

void expfit(TString data) {
    TGraphErrors *dati = new TGraphErrors(data, "%lg %lg %lg %lg*");
    TF1 *exp = new TF1("exponential", "[0]*exp(x/([1]))");
    exp->SetParNames("I_0", "etaV_T");
    exp->SetParameter(0, 1e-3);
    exp->SetParameter(1, 26.0);
    exp->SetRange(100, 250);
    dati->Fit(exp, "R");
    TCanvas *c2 = new TCanvas("c2", "Caratteristica", 800, 600);
    dati->Draw("AP");
    dati->SetMarkerStyle(20);
    dati->SetLineColor(4);
    dati->SetMarkerColor(4);
    dati->SetTitle("");
    dati->GetXaxis()->SetTitle("Tensione (mV)");
    dati->GetYaxis()->SetTitle("Corrente (mA)");
    gPad->SetLogy();
    exp->SetRange(0, 360);
    exp->Draw("same");
    c2->SetGrid();
    c2->SaveAs("Immagini/caratteristica.pdf");
}

void lnfit(TString data,double infvoltage, double topvoltage) {
    double v, i, v_err, fondo;
    std::vector<double> voltage;
    std::vector<double> lncurrent;
    std::vector<double> voltage_err;
    std::vector<double> i_err;

    std::ifstream mydata(data.Data());
    if (!mydata.is_open()) {
        Error("lnfit", "Impossibile aprire %s", data.Data());
        return;
    }

    while (mydata >> v >> i >> v_err >> fondo) {
        if (v < infvoltage || v > topvoltage) continue;

        voltage.push_back(v);
        lncurrent.push_back(std::log(i));
        voltage_err.push_back(v_err);
        i_err.push_back(0.0);
    }

    TGraphErrors *dati = new TGraphErrors(
        voltage.size(),
        lncurrent.data(),
        voltage.data(),
        i_err.data(),
        voltage_err.data()
    );

    TF1 *ln = new TF1("logfit", "-[1]*log([0]) + [1]*x");
    ln->SetParNames("I_0", "etaV_T");
    ln->SetParameter(0, 5e-3);
    ln->SetParameter(1, 27.0);
    // ln->SetParLimits(0, 1e-9, 1.0);
    // ln->SetParLimits(1, 1.0, 200.0);

    dati->Fit(ln);

    TCanvas *c3 = new TCanvas("c3", "Caratteristica_ln", 800, 600);
    dati->SetMarkerStyle(20);
    dati->SetLineColor(4);
    dati->SetMarkerColor(4);
    dati->SetTitle("");
    dati->GetXaxis()->SetTitle("ln(Corrente / 1 mA)");
    dati->GetYaxis()->SetTitle("Tensione (mV)");
    dati->Draw("AP");

    ln->SetLineColor(2);
    ln->Draw("same");

    c3->SetGrid();
    c3->SaveAs("Immagini/Caratteristica_ln.pdf");
}