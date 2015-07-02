#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include "Helpers_ROCcurve.C"


void plot_cutROC_3D(){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_150608.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_MEv2_VBF4D_DY5D_150608.root");

  vector<TGraphErrors*> plots=get_cutvalues_ROC_3D(file_sig[0],file_bkg[0],"T","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0","IntegralDY>=0&&IntegralVBF>=0",50);


  for(unsigned int i=0;i<plots.size();i++){
    plots[i]->SetLineColor(2);
    plots[i]->SetLineWidth(2);
    plots[i]->SetFillColor(0);
    plots[i]->GetXaxis()->SetTitle("Signal efficiency");
  
    plots[i]->GetYaxis()->SetTitleOffset(1.7);
    plots[i]->SetMinimum(0);
    plots[i]->SetTitle("Cut values in function of the signal efficiency");
    plots[i]->GetXaxis()->SetLimits(0.,1.);


  }

  plots[0]->GetYaxis()->SetTitle("Cut on SVfitMass [GeV]");
  plots[1]->GetYaxis()->SetTitle("Cut on #Delta#eta");
  plots[2]->GetYaxis()->SetTitle("Cut on M_{jj} [GeV]");

 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetGrid();

  plots[0]->Draw();
  TString filename="ROC3D_cutvalues_SVFit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetGrid();
  plots[1]->Draw();
  filename="ROC3D_cutvalues_Deta";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetGrid();
  plots[2]->Draw();
  filename="ROC3D_cutvalues_Mjj";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;





}







void plot_cutROC_3D_DYEmb(){

  vector<TString> file_sig;
  file_sig.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleVBFH125_MuTau_nominal.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/home/llr/cms/mastrolorenzo/CMS-MEM-GSL-MachineMPI_5D/CMS-MEM/nTuple_Htautau_withMEM/nTupleRun2012ABCD_Embedded8TeV.root");

  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = "HLTTau*HLTMu*SFTau*SFMu*weightDecayMode*HLTBugTauData*embeddingWeight";
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";

  vector<TGraphErrors*> plots=get_cutvalues_ROC_3D(file_sig[0],file_bkg[0],"T",weight_VBF+"*("+cut_VBF+")",weight_VBF+"*("+cut_VBF+")",weight_DY+"*("+cut_DY+")",weight_DY+"*("+cut_DY+")",50);


  for(unsigned int i=0;i<plots.size();i++){
    plots[i]->SetLineColor(2);
    plots[i]->SetLineWidth(2);
    plots[i]->SetFillColor(0);
    plots[i]->GetXaxis()->SetTitle("Signal efficiency");
  
    plots[i]->GetYaxis()->SetTitleOffset(1.7);
    plots[i]->SetMinimum(0);
    plots[i]->SetTitle("Cut values in function of the signal efficiency");
    plots[i]->GetXaxis()->SetLimits(0.,1.);


  }

  plots[0]->GetYaxis()->SetTitle("Cut on SVfitMass [GeV]");
  plots[1]->GetYaxis()->SetTitle("Cut on #Delta#eta");
  plots[2]->GetYaxis()->SetTitle("Cut on M_{jj} [GeV]");

 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetGrid();

  plots[0]->Draw();
  TString filename="ROC3D_cutvalues_SVFit_DYEmb";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetGrid();
  plots[1]->Draw();
  filename="ROC3D_cutvalues_Deta_DYEmb";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetGrid();
  plots[2]->Draw();
  filename="ROC3D_cutvalues_Mjj_DYEmb";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;





}
