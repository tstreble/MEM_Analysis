#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <Helpers.C>
#include <vector>
#include <TLatex.h>
#include <THStack.h>
#include <TGraphErrors.h>

using namespace std;


void plot_2lSS_ttbar_MVA(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_ttH_byLooseIsolationMVArun2v1DBdR03oldDMwLT_skimmed.root";
  TString file_ttjets_SLfromT="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT_skimmed.root";
  TString file_ttjets_SLfromTbar="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromTbar_byLooseIsolationMVArun2v1DBdR03oldDMwLT_skimmed.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT_skimmed.root";

  TH1F* h_ttH=single_plot(file_ttH,"HTauTauTree","MVA_2lSS_ttbar","MC_weight",20,-1,1);
  TH1F* h_ttjets_SLfromT=single_plot(file_ttjets_SLfromT,"HTauTauTree","MVA_2lSS_ttbar","MC_weight",20,-1,1);
  TH1F* h_ttjets_SLfromTbar=single_plot(file_ttjets_SLfromTbar,"HTauTauTree","MVA_2lSS_ttbar","MC_weight",20,-1,1);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"HTauTauTree","MVA_2lSS_ttbar","MC_weight",20,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  float XS_ttjets_SLfromT = 182. / (2*182. + 87.3);
  float XS_ttjets_SLfromTbar = XS_ttjets_SLfromT;
  float XS_ttjets_DL = 87.3 / (2*182. + 87.3);
  h_ttjets_SLfromT->Scale(XS_ttjets_SLfromT/h_ttjets_SLfromT->Integral());
  h_ttjets_SLfromTbar->Scale(XS_ttjets_SLfromTbar/h_ttjets_SLfromTbar->Integral());
  h_ttjets_DL->Scale(XS_ttjets_DL/h_ttjets_DL->Integral());

  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttjets_SLfromT->SetFillColor(kRed-9);
  h_ttjets_SLfromT->SetLineColor(kRed-9);
  h_ttjets_SLfromT->SetLineWidth(0);

  h_ttjets_SLfromTbar->SetFillColor(kRed-9);
  h_ttjets_SLfromTbar->SetLineColor(kRed-9);
  h_ttjets_SLfromTbar->SetLineWidth(0);

  h_ttjets_DL->SetFillColor(kRed+1);
  h_ttjets_DL->SetLineColor(kRed+1);
  h_ttjets_DL->SetLineWidth(0);

  THStack* h_ttjets = new THStack("h_ttjets","");
  h_ttjets->Add(h_ttjets_DL,"hist");
  h_ttjets->Add(h_ttjets_SLfromT,"hist");
  h_ttjets->Add(h_ttjets_SLfromTbar,"hist");

  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH, H->#tau#tau");
  leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");
  leg->AddEntry(h_ttjets_SLfromT,"t#bar{t} lepton+jets");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttjets->SetMaximum(1.2*max(h_ttjets->GetMaximum(),h_ttH->GetMaximum()));
  h_ttjets->Draw("");
  h_ttH->Draw("same");
  leg->Draw("same");

  h_ttjets->GetXaxis()->SetTitle("2lSS ttH vs t#bar{t} MVA");
  h_ttjets->GetYaxis()->SetTitle("a. u.");
  h_ttjets->GetYaxis()->SetTitleOffset(1.65);
  h_ttjets->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.2*1.07*h_ttjets->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  TString filename="MVA_2lSS_ttH_ttbar";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}





TGraphErrors* ROC_2lSS_MVA(){


  TString file_ttH="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_ttH_byLooseIsolationMVArun2v1DBdR03oldDMwLT_skimmed.root";
  TString file_ttjets_SLfromT="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT_skimmed.root";
  TString file_ttjets_SLfromTbar="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromTbar_byLooseIsolationMVArun2v1DBdR03oldDMwLT_skimmed.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT_skimmed.root";

  TH1F* h_ttH=single_plot(file_ttH,"HTauTauTree","MVA_2lSS_ttbar","MC_weight",100,-1,1);
  TH1F* h_ttjets_SLfromT=single_plot(file_ttjets_SLfromT,"HTauTauTree","MVA_2lSS_ttbar","MC_weight",100,-1,1);
  TH1F* h_ttjets_SLfromTbar=single_plot(file_ttjets_SLfromTbar,"HTauTauTree","MVA_2lSS_ttbar","MC_weight",100,-1,1);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"HTauTauTree","MVA_2lSS_ttbar","MC_weight",100,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  float XS_ttjets_SLfromT = 182. / (2*182. + 87.3);

  float XS_ttjets_SLfromTbar = XS_ttjets_SLfromT;
  float XS_ttjets_DL = 87.3 / (2*182. + 87.3);
  h_ttjets_SLfromT->Scale(XS_ttjets_SLfromT/h_ttjets_SLfromT->Integral());
  h_ttjets_SLfromTbar->Scale(XS_ttjets_SLfromTbar/h_ttjets_SLfromTbar->Integral());
  h_ttjets_DL->Scale(XS_ttjets_DL/h_ttjets_DL->Integral());

  TH1F* h_ttjets = h_ttjets_SLfromT;
  h_ttjets->Add(h_ttjets_SLfromTbar);
  h_ttjets->Add(h_ttjets_DL);


  TGraphErrors* ROC=new TGraphErrors();

  for(int i=0; i<100; i++){

    float x = h_ttH->Integral(0,i);
    float y = h_ttjets->Integral(0,i);
    ROC->SetPoint(i,x,y);

  }


  return ROC;

}




void plot_ROC(vector<TGraphErrors*> ROC, vector<TString> leg_entry, bool save=false, TString filename=""){

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetGridx();
  c->SetGridy();

  ROC[0]->GetXaxis()->SetTitle("ttH efficiency");
  ROC[0]->GetYaxis()->SetTitle("t#bar{t} efficiency");
  ROC[0]->GetXaxis()->SetRangeUser(0,1);
  ROC[0]->GetYaxis()->SetRangeUser(0,1);
  ROC[0]->GetYaxis()->SetTitleOffset(1.65);

  TLegend* leg=new TLegend(0.55,0.3,0.85,0.5);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  for(unsigned int i=0; i<ROC.size(); i++){
    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    ROC[i]->SetLineColor(i+1);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->Draw("APL");
  for(unsigned int i=1; i<ROC.size(); i++)
    ROC[i]->Draw("samePL");
  leg->Draw("same");
  
  TLatex *texl = new TLatex(0.01,1.01,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  if(save){
    c->SaveAs("../plots/pdf/"+filename+".pdf");
    c->SaveAs("../plots/png/"+filename+".png");
  }

  return;

}





void plot_ROC_test(){

  vector<TGraphErrors*> ROC;
  ROC.push_back(ROC_2lSS_MVA());

  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");

  plot_ROC(ROC,leg_entry);  
  return;

}
