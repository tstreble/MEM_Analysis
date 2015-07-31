#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <Helpers.C>
#include <vector>

using namespace std;

void plot_etajet(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto_gen.root","HTauTauTree","asinh(jets_pz/sqrt(jets_px**2+jets_py**2))","",100,-5,5));
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h_norm->Integral());
    h[i]->Scale(1/h[i]->Integral());
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("#eta(jet)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("#eta distribution of the jets in the ttH, H->#tau#tau sample");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  TString filename="etajet_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}

