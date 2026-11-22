#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <TString.h>
#include "TGraph.h"
#include "TGraphErrors.h"
#include <TCanvas.h>
#include <TF1.h>
#include <TFile.h>
#include <TFitResult.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TROOT.h>
#include <TRandom.h>
#include <TStyle.h>
#include <TMath.h>


void calibration(TString dataset);

void expfit(TString dataset);

void lnfit (TString data, double infvoltage ,double topvoltage);

void Test_fit (TString data);