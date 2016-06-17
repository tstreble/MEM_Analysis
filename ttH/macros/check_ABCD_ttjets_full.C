#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <THStack.h>
#include <iostream>
#include <TLegend.h>
#include <Helpers.C>
#include <vector>
#include <TLatex.h>
#include <TGraphErrors.h>
#include <TGaxis.h>

using namespace std;


TString cut_A_SS="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))";

TString cut_A_SS_mumu="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1) && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13)";

TString cut_A_OS="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))";

TString cut_A_OS_mumu="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1) && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13)";

TString cut_B_ee="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11)";

TString cut_B_emu="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)||(abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11)))";

TString cut_B_mumu="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13)";

TString cut_F_ee="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11)";

TString cut_F_emu="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)||(abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11)))";

TString cut_F_mumu="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13)";

TString cut_E_ee="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11)";

TString cut_E_emu="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)||(abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11)))";

TString cut_E_mumu="MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13)";

TString cut_C_ee="MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11)";

TString cut_C_emu="MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)||(abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11)))";

TString cut_C_mumu="MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13)";

TString cut_D_ee="MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11)";

TString cut_D_emu="MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)||(abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11)))";

TString cut_D_mumu="MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13)";

float OS_B_ee=2.6e-2;
float OS_C_ee=64.2e-2;
float OS_D_ee=64.2e-2;

float OS_B_emu=1.3e-2;
float OS_C_emu=56.9e-2;
float OS_D_emu=2.6e-2;


void plot_tauh_pt(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TString var = "recotauh_pt[0]";
  int nbin = 15;
  float min = 0;
  float max = 150;

  TH1F* h_A_SS   = single_plot(files,"HTauTauTree",var,cut_A_SS  ,nbin,min,max);
  TH1F* h_A_OS   = single_plot(files,"HTauTauTree",var,cut_A_OS  ,nbin,min,max);
  TH1F* h_E_ee   = single_plot(files,"HTauTauTree",var,cut_E_ee  ,nbin ,min,max);
  TH1F* h_E_emu  = single_plot(files,"HTauTauTree",var,cut_E_emu ,nbin ,min,max);
  TH1F* h_E_mumu = single_plot(files,"HTauTauTree",var,cut_E_mumu,nbin ,min,max);
  TH1F* h_B_ee   = single_plot(files,"HTauTauTree",var,cut_B_ee  ,nbin,min,max);
  TH1F* h_B_emu  = single_plot(files,"HTauTauTree",var,cut_B_emu ,nbin,min,max);
  TH1F* h_B_mumu = single_plot(files,"HTauTauTree",var,cut_B_mumu,nbin,min,max);
  TH1F* h_F_ee   = single_plot(files,"HTauTauTree",var,cut_B_ee  ,nbin,min,max);
  TH1F* h_F_emu  = single_plot(files,"HTauTauTree",var,cut_B_emu ,nbin,min,max);
  TH1F* h_F_mumu = single_plot(files,"HTauTauTree",var,cut_B_mumu,nbin,min,max);
  TH1F* h_C_ee   = single_plot(files,"HTauTauTree","1",cut_C_ee  ,3,0,3);
  TH1F* h_C_emu  = single_plot(files,"HTauTauTree","1",cut_C_emu ,3,0,3);
  TH1F* h_C_mumu = single_plot(files,"HTauTauTree","1",cut_C_mumu,3,0,3);
  TH1F* h_D_ee   = single_plot(files,"HTauTauTree","1",cut_D_ee  ,3,0,3);
  TH1F* h_D_emu  = single_plot(files,"HTauTauTree","1",cut_D_emu ,3,0,3);
  TH1F* h_D_mumu = single_plot(files,"HTauTauTree","1",cut_D_mumu,3,0,3);
  
  float B_C_D_ee = (h_B_ee->Integral()*h_C_ee->Integral()/h_D_ee->Integral());
  float B_C_D_emu = (h_B_emu->Integral()*h_C_emu->Integral()/h_D_emu->Integral());
  float B_C_D_mumu = (h_B_mumu->Integral()*h_C_mumu->Integral()/h_D_mumu->Integral());

  float norm_A_OS_ee =  B_C_D_ee * (OS_B_ee*OS_C_ee/OS_D_ee);
  float norm_A_OS_emu = B_C_D_emu * (OS_B_emu*OS_C_emu/OS_D_emu);
  //float norm_A_OS_mumu = 0;

  TH1F* h_A_OS_extrap_ee = h_E_ee;
  h_A_OS_extrap_ee->Scale(norm_A_OS_ee/h_A_OS_extrap_ee->Integral());
  TH1F* h_A_OS_extrap_emu = h_E_emu;
  h_A_OS_extrap_emu->Scale(norm_A_OS_emu/h_A_OS_extrap_emu->Integral());
  TH1F* h_A_OS_extrap_mumu = h_E_mumu;
  h_A_OS_extrap_mumu->Scale(norm_A_OS_emu/h_A_OS_extrap_emu->Integral());

  TH1F* h_A_OS_extrap = h_A_OS_extrap_ee;
  h_A_OS_extrap->Add(h_A_OS_extrap_emu);


  float norm_A_SS_ee =  B_C_D_ee * (1-OS_B_ee)*(1-OS_C_ee)/(1-OS_D_ee);
  float norm_A_SS_emu = B_C_D_emu * (1-OS_B_emu)*(1-OS_C_emu)/(1-OS_D_emu);
  float norm_A_SS_mumu = B_C_D_mumu;

  TH1F* h_shape_B_ee = h_B_ee;
  h_shape_B_ee->Scale(1/h_shape_B_ee->Integral());
  TH1F* h_shape_B_emu = h_B_emu;
  h_shape_B_emu->Scale(1/h_shape_B_emu->Integral());
  TH1F* h_shape_B_mumu = h_B_mumu;
  h_shape_B_mumu->Scale(1/h_shape_B_mumu->Integral());

  TH1F* h_shape_F_ee = h_F_ee;
  h_shape_F_ee->Scale(1/h_shape_F_ee->Integral());
  TH1F* h_shape_F_emu = h_F_emu;
  h_shape_F_emu->Scale(1/h_shape_F_emu->Integral());
  TH1F* h_shape_F_mumu = h_F_mumu;
  h_shape_F_mumu->Scale(1/h_shape_F_mumu->Integral());

  TH1F* h_A_SS_extrap_ee = h_shape_B_ee;
  h_A_SS_extrap_ee->Add(h_shape_F_ee,-OS_B_ee);
  h_A_SS_extrap_ee->Scale(norm_A_SS_ee);
  TH1F* h_A_SS_extrap_emu = h_shape_B_emu;
  h_A_SS_extrap_emu->Add(h_shape_F_ee,-OS_B_emu);
  h_A_SS_extrap_emu->Scale(norm_A_SS_emu);
  TH1F* h_A_SS_extrap_mumu = h_shape_B_mumu;
  //h_A_SS_extrap_mumu->Add(h_shape_F_mumu,-0);
  h_A_SS_extrap_mumu->Scale(norm_A_SS_mumu);

  TH1F* h_A_SS_extrap = h_A_SS_extrap_ee;
  h_A_SS_extrap->Add(h_A_SS_extrap_emu);
  h_A_SS_extrap->Add(h_A_SS_extrap_mumu);
  //TH1F* h_A_SS_extrap = h_A_SS_extrap_mumu;

  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);
  TH1F* h_A_sum = h_A_OS;
  h_A_sum->Add(h_A_SS);
  cout<<"A = "<<h_A_sum->Integral()<<endl;;


  h_A_OS_extrap->SetFillColor(kRed+1);
  h_A_OS_extrap->SetLineColor(kRed+1);
  h_A_OS_extrap->SetLineWidth(0);

  h_A_SS_extrap->SetFillColor(kRed-9);
  h_A_SS_extrap->SetLineColor(kRed-9);
  h_A_SS_extrap->SetLineWidth(0);

  THStack* h_A_extrap = new THStack("h_A_extrap","");
  h_A_extrap->Add(h_A_OS_extrap,"hist");
  h_A_extrap->Add(h_A_SS_extrap,"hist");
  TH1F* h_A_extrap_sum = h_A_OS_extrap;
  h_A_extrap_sum->Add(h_A_SS_extrap);
  //TH1F* h_A_extrap_sum = h_A_SS_extrap;

  cout<<"A extrap = "<<h_A_extrap_sum->Integral()<<endl;


  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_OS_extrap,"Extrapolation");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_A_SS_extrap,"Extrapolation");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_A_extrap->SetMaximum(1.2*std::max(h_A_extrap->GetMaximum(),h_A->GetMaximum()));
  h_A_extrap->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_A_extrap->GetYaxis()->SetTitle("a. u.");
  h_A_extrap->GetYaxis()->SetTitleOffset(1.65);
  h_A_extrap->SetTitle("");
  //h_A_extrap->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.2*1.07*h_A_extrap->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_A_extrap->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_A_SS->GetBinLowEdge(1), 0.01*h_A_extrap->GetMaximum(), h_A_SS->GetBinLowEdge(1), 1.2*1.05*h_A_extrap->GetMaximum(), 0.01*h_A_extrap->GetMaximum(),1.2*1.05*h_A_extrap->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_extrap_sum->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_A_sum);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_A_extrap->GetYaxis()->SetTitleSize(20);
  h_A_extrap->GetYaxis()->SetTitleFont(43);
  h_A_extrap->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Extrap./MC");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(#tau_{h}) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="tauh_pt_check_ABCD_full";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void plot_jet0_pt(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TString var = "recoPFJet_pt[0]";
  int nbin = 20;
  float min = 0;
  float max = 400;

  TH1F* h_A_SS   = single_plot(files,"HTauTauTree",var,cut_A_SS  ,nbin,min,max);
  TH1F* h_A_OS   = single_plot(files,"HTauTauTree",var,cut_A_OS  ,nbin,min,max);
  TH1F* h_E_ee   = single_plot(files,"HTauTauTree",var,cut_E_ee  ,nbin ,min,max);
  TH1F* h_E_emu  = single_plot(files,"HTauTauTree",var,cut_E_emu ,nbin ,min,max);
  TH1F* h_E_mumu = single_plot(files,"HTauTauTree",var,cut_E_mumu,nbin ,min,max);
  TH1F* h_B_ee   = single_plot(files,"HTauTauTree",var,cut_B_ee  ,nbin,min,max);
  TH1F* h_B_emu  = single_plot(files,"HTauTauTree",var,cut_B_emu ,nbin,min,max);
  TH1F* h_B_mumu = single_plot(files,"HTauTauTree",var,cut_B_mumu,nbin,min,max);
  TH1F* h_F_ee   = single_plot(files,"HTauTauTree",var,cut_B_ee  ,nbin,min,max);
  TH1F* h_F_emu  = single_plot(files,"HTauTauTree",var,cut_B_emu ,nbin,min,max);
  TH1F* h_F_mumu = single_plot(files,"HTauTauTree",var,cut_B_mumu,nbin,min,max);
  TH1F* h_C_ee   = single_plot(files,"HTauTauTree","1",cut_C_ee  ,3,0,3);
  TH1F* h_C_emu  = single_plot(files,"HTauTauTree","1",cut_C_emu ,3,0,3);
  TH1F* h_C_mumu = single_plot(files,"HTauTauTree","1",cut_C_mumu,3,0,3);
  TH1F* h_D_ee   = single_plot(files,"HTauTauTree","1",cut_D_ee  ,3,0,3);
  TH1F* h_D_emu  = single_plot(files,"HTauTauTree","1",cut_D_emu ,3,0,3);
  TH1F* h_D_mumu = single_plot(files,"HTauTauTree","1",cut_D_mumu,3,0,3);
  
  float B_C_D_ee = (h_B_ee->Integral()*h_C_ee->Integral()/h_D_ee->Integral());
  float B_C_D_emu = (h_B_emu->Integral()*h_C_emu->Integral()/h_D_emu->Integral());
  float B_C_D_mumu = (h_B_mumu->Integral()*h_C_mumu->Integral()/h_D_mumu->Integral());

  float norm_A_OS_ee =  B_C_D_ee * (OS_B_ee*OS_C_ee/OS_D_ee);
  float norm_A_OS_emu = B_C_D_emu * (OS_B_emu*OS_C_emu/OS_D_emu);
  //float norm_A_OS_mumu = 0;

  TH1F* h_A_OS_extrap_ee = h_E_ee;
  h_A_OS_extrap_ee->Scale(norm_A_OS_ee/h_A_OS_extrap_ee->Integral());
  TH1F* h_A_OS_extrap_emu = h_E_emu;
  h_A_OS_extrap_emu->Scale(norm_A_OS_emu/h_A_OS_extrap_emu->Integral());
  TH1F* h_A_OS_extrap_mumu = h_E_mumu;
  h_A_OS_extrap_mumu->Scale(norm_A_OS_emu/h_A_OS_extrap_emu->Integral());

  TH1F* h_A_OS_extrap = h_A_OS_extrap_ee;
  h_A_OS_extrap->Add(h_A_OS_extrap_emu);


  float norm_A_SS_ee =  B_C_D_ee * (1-OS_B_ee)*(1-OS_C_ee)/(1-OS_D_ee);
  float norm_A_SS_emu = B_C_D_emu * (1-OS_B_emu)*(1-OS_C_emu)/(1-OS_D_emu);
  float norm_A_SS_mumu = B_C_D_mumu;

  TH1F* h_shape_B_ee = h_B_ee;
  h_shape_B_ee->Scale(1/h_shape_B_ee->Integral());
  TH1F* h_shape_B_emu = h_B_emu;
  h_shape_B_emu->Scale(1/h_shape_B_emu->Integral());
  TH1F* h_shape_B_mumu = h_B_mumu;
  h_shape_B_mumu->Scale(1/h_shape_B_mumu->Integral());

  TH1F* h_shape_F_ee = h_F_ee;
  h_shape_F_ee->Scale(1/h_shape_F_ee->Integral());
  TH1F* h_shape_F_emu = h_F_emu;
  h_shape_F_emu->Scale(1/h_shape_F_emu->Integral());
  TH1F* h_shape_F_mumu = h_F_mumu;
  h_shape_F_mumu->Scale(1/h_shape_F_mumu->Integral());

  TH1F* h_A_SS_extrap_ee = h_shape_B_ee;
  h_A_SS_extrap_ee->Add(h_shape_F_ee,-OS_B_ee);
  h_A_SS_extrap_ee->Scale(norm_A_SS_ee);
  TH1F* h_A_SS_extrap_emu = h_shape_B_emu;
  h_A_SS_extrap_emu->Add(h_shape_F_ee,-OS_B_emu);
  h_A_SS_extrap_emu->Scale(norm_A_SS_emu);
  TH1F* h_A_SS_extrap_mumu = h_shape_B_mumu;
  //h_A_SS_extrap_mumu->Add(h_shape_F_mumu,-0);
  h_A_SS_extrap_mumu->Scale(norm_A_SS_mumu);

  TH1F* h_A_SS_extrap = h_A_SS_extrap_ee;
  h_A_SS_extrap->Add(h_A_SS_extrap_emu);
  h_A_SS_extrap->Add(h_A_SS_extrap_mumu);
  //TH1F* h_A_SS_extrap = h_A_SS_extrap_mumu;

  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);
  TH1F* h_A_sum = h_A_OS;
  h_A_sum->Add(h_A_SS);
  cout<<"A = "<<h_A_sum->Integral()<<endl;;


  h_A_OS_extrap->SetFillColor(kRed+1);
  h_A_OS_extrap->SetLineColor(kRed+1);
  h_A_OS_extrap->SetLineWidth(0);

  h_A_SS_extrap->SetFillColor(kRed-9);
  h_A_SS_extrap->SetLineColor(kRed-9);
  h_A_SS_extrap->SetLineWidth(0);

  THStack* h_A_extrap = new THStack("h_A_extrap","");
  h_A_extrap->Add(h_A_OS_extrap,"hist");
  h_A_extrap->Add(h_A_SS_extrap,"hist");
  TH1F* h_A_extrap_sum = h_A_OS_extrap;
  h_A_extrap_sum->Add(h_A_SS_extrap);
  //TH1F* h_A_extrap_sum = h_A_SS_extrap;

  cout<<"A extrap = "<<h_A_extrap_sum->Integral()<<endl;


  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_OS_extrap,"Extrapolation");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_A_SS_extrap,"Extrapolation");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_A_extrap->SetMaximum(1.2*std::max(h_A_extrap->GetMaximum(),h_A->GetMaximum()));
  h_A_extrap->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_A_extrap->GetYaxis()->SetTitle("a. u.");
  h_A_extrap->GetYaxis()->SetTitleOffset(1.65);
  h_A_extrap->SetTitle("");
  //h_A_extrap->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.2*1.07*h_A_extrap->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_A_extrap->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_A_SS->GetBinLowEdge(1), 0.01*h_A_extrap->GetMaximum(), h_A_SS->GetBinLowEdge(1), 1.2*1.05*h_A_extrap->GetMaximum(), 0.01*h_A_extrap->GetMaximum(),1.2*1.05*h_A_extrap->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_extrap_sum->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_A_sum);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_A_extrap->GetYaxis()->SetTitleSize(20);
  h_A_extrap->GetYaxis()->SetTitleFont(43);
  h_A_extrap->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Extrap./MC");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(lead. jet) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet0_pt_check_ABCD_full";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}


