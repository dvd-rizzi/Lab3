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

void expfit(TString data, double infvoltage, double topvoltage) {
    TGraphErrors *dati = new TGraphErrors(data, "%lg %lg %lg %lg*");
    TF1 *exp = new TF1("exponential", "[0]*exp(x/([1]))");
    exp->SetParNames("I_0", "etaV_T");
    exp->SetParameter(0, 1e-3);
    exp->SetParameter(1, 26.0);
    exp->SetRange(infvoltage, topvoltage);
    dati->Fit(exp, "R");
    TCanvas *c2 = new TCanvas("c2", "Caratteristica");//, 800, 600);
    dati->Draw("AP");
    dati->SetMarkerStyle(20);
    dati->SetLineColor(4);
    dati->SetMarkerColor(4);
    dati->SetTitle("");
    dati->GetXaxis()->SetTitle("Tensione (mV)");
    dati->GetYaxis()->SetTitle("Corrente (mA)");
    exp->Draw("same");
    c2->SetGrid();
    c2->SetLogy();
    c2->SaveAs("Immagini/caratteristica.pdf");
}

void lnfit_ger(TString data,double infvoltage, double topvoltage) {
    double v, i, v_err, i_err;
    std::vector<double> voltage;
    std::vector<double> lncurrent;
    std::vector<double> voltage_err;
    std::vector<double> current_err;

    std::ifstream mydata(data.Data());
    if (!mydata.is_open()) {
        Error("lnfit", "Impossibile aprire %s", data.Data());
        return;
    }

    while (mydata >> v >> i >> v_err >> i_err) {
        if (v < infvoltage || v > topvoltage) continue;

        voltage.push_back(v);
        lncurrent.push_back(std::log(i));
        voltage_err.push_back(v_err);
        current_err.push_back(i_err);
    }

    TGraphErrors *dati = new TGraphErrors(
        voltage.size(),
        lncurrent.data(),
        voltage.data(),
        current_err.data(),
        voltage_err.data()
    );

    TF1 *ln = new TF1("logfit", "-[1]*log([0]) + [1]*x");
    ln->SetParNames("I_0", "etaV_T_Ger");
    ln->SetParameter(0, 5e-3);
    ln->SetParameter(1, 25.5);
    // ln->SetParLimits(0, 1e-9, 1.0);
    //ln->SetParLimits(1, 20, 30);

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
    c3->SaveAs("Immagini/Caratteristica_ln_ger.pdf");
}

void lnfit_sil(TString data,double infvoltage, double topvoltage) {
    double v, i, v_err, i_err;
    std::vector<double> voltage;
    std::vector<double> lncurrent;
    std::vector<double> voltage_err;
    std::vector<double> current_err;

    std::ifstream mydata(data.Data());
    if (!mydata.is_open()) {
        Error("lnfit", "Impossibile aprire %s", data.Data());
        return;
    }

    while (mydata >> v >> i >> v_err >> i_err) {
        if (v < infvoltage || v > topvoltage) continue;

        voltage.push_back(v);
        lncurrent.push_back(std::log(i));
        voltage_err.push_back(v_err);
        current_err.push_back(0.0);
    }

    TGraphErrors *dati = new TGraphErrors(
        voltage.size(),
        lncurrent.data(),
        voltage.data(),
        current_err.data(),
        voltage_err.data()
    );

    TF1 *ln = new TF1("logfit", "-[1]*log([0]) + [1]*x");
    ln->SetParNames("I_0", "etaV_T_Sil");
    ln->SetParameter(0, 5e-3);
    ln->SetParameter(1, 53.0);
    // ln->SetParLimits(0, 1e-9, 1.0);
    //ln->SetParLimits(1, 45, 60);

    dati->Fit(ln);

    TCanvas *c5 = new TCanvas("c5", "Caratteristica_ln", 800, 600);
    dati->SetMarkerStyle(20);
    dati->SetLineColor(4);
    dati->SetMarkerColor(4);
    dati->SetTitle("");
    dati->GetXaxis()->SetTitle("ln(Corrente / 1 mA)");
    dati->GetYaxis()->SetTitle("Tensione (mV)");
    dati->Draw("AP");

    ln->SetLineColor(2);
    ln->Draw("same");

    c5->SetGrid();
    c5->SaveAs("Immagini/Caratteristica_ln_sil.pdf");
}


void Test_fit(TString data) {
    double v, i, v_err, fondo;
    std::vector<double> voltage;
    std::vector<double> current;
    std::vector<double> voltage_err;
    std::vector<double> i_err;

    std::ifstream mydata(data.Data());
    if (!mydata.is_open()) {
        Error("Test_fit", "Impossibile aprire il file %s", data.Data());
        return;
    }

    while (mydata >> v >> i >> v_err >> fondo) {
        voltage.push_back(v);
        current.push_back(i);
        voltage_err.push_back(v_err);
        i_err.push_back(0.0); // Errore su I trascurabile
    }

    TGraphErrors *dati = new TGraphErrors(
        voltage.size(),
        current.data(),
        voltage.data(),
        i_err.data(),
        voltage_err.data()
    );

    // Modello: V(I) = eta*V_T * ln(I / I_0 + 1) + I * R_s
    // [0] = eta*V_T (mV)
    // [1] = I_0 (mA)  -> 1e-3 mA = 1 uA
    // [2] = R_s (Ohm) -> poiché (mA) * (Ohm) = (mV)
    TF1 *f_diodo = new TF1("f_diodo", "[0]*log((x/[1]) + 1.0) + x*[2]", 0.0, 2.5);
    f_diodo->SetParNames("etaV_T", "I_0", "R_s");

    f_diodo->SetParameter(0, 40.0);   // ~40 mV
    f_diodo->SetParameter(1, 5e-3);   // ~5 uA = 0.005 mA
    f_diodo->SetParameter(2, 10.0);   // ~10 Ohm

    f_diodo->SetParLimits(0, 1.0, 150.0);
    f_diodo->SetParLimits(1, 1e-7, 1.0);
    f_diodo->SetParLimits(2, 0.0, 200.0);

    dati->Fit(f_diodo); // "M" migliora la ricerca del minimo con Minuit2

    //gStyle->SetOptFit(1111);
    TCanvas *c4 = new TCanvas("c4", "Fit Caratteristica Completa", 800, 600);
    c4->SetGrid();

    dati->SetTitle("");
    dati->SetMarkerStyle(20);
    dati->SetMarkerColor(kBlue + 1);
    dati->SetLineColor(kBlue + 1);
    dati->GetXaxis()->SetTitle("Corrente I (mA)");
    dati->GetYaxis()->SetTitle("Tensione V (mV)");
    dati->Draw("AP");

    f_diodo->SetLineColor(kRed);
    f_diodo->SetLineWidth(2);
    f_diodo->Draw("same");

    c4->SaveAs("Immagini/Test.pdf");
}


void double_exp(TString data1, TString data2) {
    TGraph *silicio  = new TGraph(data1, "%lg %lg");
    TGraph *germanio = new TGraph(data2, "%lg %lg");
    silicio->GetXaxis()->SetTitle("Voltaggio (V)");
    silicio->GetYaxis()->SetTitle("Corrente (mA)");
    silicio->GetYaxis()->SetRangeUser(0, 2.2);
    silicio->SetMarkerStyle(20);
    silicio->SetMarkerColor(kBlue + 1);
    silicio->SetLineColor(kBlue + 1);
    germanio->SetMarkerStyle(20);
    germanio->SetMarkerColor(kRed + 1);
    germanio->SetLineColor(kRed + 1);
    TCanvas *cc = new TCanvas("cc", "Curve caratteristiche", 800, 600);
    silicio->Draw("APL");
    germanio->Draw("PL same");
    cc->SetGrid();
    cc->SaveAs("Immagini/curve.pdf");
}