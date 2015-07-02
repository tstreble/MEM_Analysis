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

void plot_SVfit_Mjj(){

  TH2F* h=single_plot2D(TString file, TString tree_name, TString var1, TString var2, TString cut, int nbin1, float min1, float max1, int nbin2, float min2, float max2);

  vector<TString> leg_entry;
  leg_entry.push_back("10<E_{#tau}<20 GeV");
  leg_entry.push_back("60<E_{#tau}<80 GeV");
  leg_entry.push_back("180<E_{#tau}<200 GeV");

  TLegend* leg=new TLegend(0.5,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[0]->SetLineColor(1);
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("E_{#mu}/E_{#tau}");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("E_{#mu}/E_{#tau} distribution for #tau's from the VBF sample");

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="z_taul_VBF";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



