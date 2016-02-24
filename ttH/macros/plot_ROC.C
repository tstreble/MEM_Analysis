#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TLatex.h>
#include "Helpers_ROCcurve.C"


void plot_ROC(bool plot_log=true){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_Samples/MEM_samples/ttH_miss_160111.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/TTJets_Samples/MEM_samples/ttjets_miss_160108.root");


  vector<TGraphErrors*> ROC;
  for(unsigned int i=0; i<file_sig.size();i++){
    ROC.push_back(get_ROC_LR_ttjets(file_sig[i],file_bkg[i],"T","recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && Integral_ttH>=0","recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && Integral_ttH>=0","recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && Integral_ttH>=0","recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && Integral_ttH>=0",10,plot_log,1e-9,"MC_weight","MC_weight"));
    ROC.push_back(get_ROC_LR_ttjets(file_sig[i],file_bkg[i],"T","recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && Integral_ttH>=0 && integration_type==0","recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && Integral_ttH>=0 && integration_type==0","recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && Integral_ttH>=0 && integration_type==0","recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && Integral_ttH>=0 && integration_type==0",10,plot_log,1e-9,"MC_weight","MC_weight"));
    ROC.push_back(get_ROC_LR_ttjets(file_sig[i],file_bkg[i],"T","recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && Integral_ttH>=0 && integration_type==1","recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && Integral_ttH>=0 && integration_type==1","recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && Integral_ttH>=0 && integration_type==1","recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && Integral_ttH>=0 && integration_type==1",10,plot_log,1e-9,"MC_weight","MC_weight"));
    
  }
    

  
  vector<TString> leg_entry;
  leg_entry.push_back("Inclusive");
  leg_entry.push_back("w/o miss. jet");
  leg_entry.push_back("w/ miss. jet");


  TLegend* leg=new TLegend(0.2,0.2,0.5,0.5);
  if(plot_log)
    leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("2lSS, 1CSVM + 1CSVL");


  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);

    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  if(plot_log)
     ROC[0]->GetYaxis()->SetTitle("Mistag rate");
  else
     ROC[0]->GetYaxis()->SetTitle("Background rejection");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0);
  //ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  if(plot_log)
    c->SetLogy();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  leg->Draw("same");
  
  TLatex *texl = new TLatex(0.01,1.02,"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="ROC_LR_ttjets";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}

