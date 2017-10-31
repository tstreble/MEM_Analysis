#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <THStack.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>
#include <Helpers.C>
#include <vector>
#include <TF1.h>




void plot_z_electrons(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","abs(genpart_pdg)==11 && genpart_TauMothInd>=0 && genpart_TauGenDecayMode[genpart_TauMothInd]==1 && ((genpart_flags>>4)&1) && ((genpart_flags>>9)&1) && genpart_HMothInd[genpart_TauMothInd]>=0 && n_gentau==2",100,0,1.));

  TLegend* leg=new TLegend(0.5,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Monte-Carlo");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(1);
    h[i]->SetLineWidth(0);
    h[i]->SetMarkerSize(1);
    h[i]->SetMarkerStyle(20);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }

  //h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E(e)/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of #tau leptons / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  /*for(int i=0; i<h.size();i--){
    h[i]->Draw("histsame");
    }*/
  
  TF1* f =new TF1("f","[0]*(1-x)*(5+5*x-4*x*x)",0,1);
  //h[0]->Fit(f);
  f->SetParameter(0,h[0]->GetBinWidth(1)/3.);
  f->SetLineColor(kRed);
  f->Draw("same");
  leg->AddEntry(f,"Transfer function");

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, Simulation #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="taulep_z_electrons";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}










void plot_z_muons(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","abs(genpart_pdg)==13 && genpart_TauMothInd>=0 && genpart_TauGenDecayMode[genpart_TauMothInd]==0 && ((genpart_flags>>4)&1) && ((genpart_flags>>9)&1) && genpart_HMothInd[genpart_TauMothInd]>=0 && n_gentau==2",100,0,1.));

  TLegend* leg=new TLegend(0.5,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Monte-Carlo");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(1);
    h[i]->SetLineWidth(0);
    h[i]->SetMarkerSize(1);
    h[i]->SetMarkerStyle(20);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }

  //h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E(#mu)/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of #tau leptons / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  /*for(int i=0; i<h.size();i--){
    h[i]->Draw("histsame");
    }*/
  
  TF1* f =new TF1("f","[0]*(1-x)*(5+5*x-4*x*x)",0,1);
  //h[0]->Fit(f);
  f->SetParameter(0,h[0]->GetBinWidth(1)/3.);
  f->SetLineColor(kRed);
  f->Draw("same");
  leg->AddEntry(f,"Transfer function");

  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, Simulation #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="taulep_z_muons";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}

