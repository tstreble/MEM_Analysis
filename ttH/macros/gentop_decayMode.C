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
#include <TGraphErrors.h>

using namespace std;





void plot_gentop_decayMode_ee_0tauh_1L1T(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");

  TH2F* h = single_plot2D(files,"HTauTauTree","gentop_decayMode[0]","gentop_decayMode[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",6,0,6,8,0,8); 
  h->Scale(1/h->Integral());

  h->SetStats(0);
  h->SetTitle("");

  TLegend* leg=new TLegend(0.35,0.75,0.85,0.85);
  leg->SetHeader("#splitline{Dielectron channel}{0 #tau_{h}, 1 loose + 1 tight lepton}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  h->SetMaximum(1.25*h->GetMaximum());
  h->GetXaxis()->SetTitle("DM(top #0)");
  h->GetYaxis()->SetTitle("DM(top #1)");

  h->Draw("colz");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.1,8.1,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="gentop_decayMode_ee_0tauh_1L1T";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



void plot_gentop_decayMode_ee_0tauh_2T(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");

  TH2F* h = single_plot2D(files,"HTauTauTree","gentop_decayMode[0]","gentop_decayMode[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",6,0,6,8,0,8); 
  h->Scale(1/h->Integral());

  h->SetStats(0);
  h->SetTitle("");

  TLegend* leg=new TLegend(0.35,0.75,0.85,0.85);
  leg->SetHeader("#splitline{Dielectron channel}{0 #tau_{h}, 2 tight leptons}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  h->SetMaximum(1.25*h->GetMaximum());
  h->GetXaxis()->SetTitle("DM(top #0)");
  h->GetYaxis()->SetTitle("DM(top #1)");

  h->Draw("colz");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.1,8.1,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="gentop_decayMode_ee_notauh_1L1T";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_gentop_decayMode_ee_1tauh_1L1T(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");

  TH2F* h = single_plot2D(files,"HTauTauTree","gentop_decayMode[0]","gentop_decayMode[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recotauh_charge[0]*recolep_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",6,0,6,8,0,8); 
  h->Scale(1/h->Integral());

  h->SetStats(0);
  h->SetTitle("");

  TLegend* leg=new TLegend(0.35,0.75,0.85,0.85);
  leg->SetHeader("#splitline{Dielectron channel}{#leq 1 #tau_{h}, 1 loose + 1 tight lepton}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  h->SetMaximum(1.25*h->GetMaximum());
  h->GetXaxis()->SetTitle("DM(top #0)");
  h->GetYaxis()->SetTitle("DM(top #1)");

  h->Draw("colz");

  TLatex *texl = new TLatex(0.1,8.1,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="gentop_decayMode_ee_1tauh_1L1T";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_gentop_decayMode_ee_1tauh_2T(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");

  TH2F* h = single_plot2D(files,"HTauTauTree","gentop_decayMode[0]","gentop_decayMode[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recotauh_charge[0]*recolep_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",6,0,6,8,0,8); 
  h->Scale(1/h->Integral());

  h->SetStats(0);
  h->SetTitle("");

  TLegend* leg=new TLegend(0.35,0.75,0.85,0.85);
  leg->SetHeader("#splitline{Dielectron channel}{#leq 1 #tau_{h}, 2 tight leptons}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  h->SetMaximum(1.25*h->GetMaximum());
  h->GetXaxis()->SetTitle("DM(top #0)");
  h->GetYaxis()->SetTitle("DM(top #1)");

  h->Draw("colz");

  TLatex *texl = new TLatex(0.1,8.1,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="gentop_decayMode_ee_1tauh_2T";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}
