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

void plot_comput_time(){

  vector<TH1F*> h;

  TString weight_VBF = "puWeight*HLTweightTau*HLTweightMu*SFTau*SFMu*weightDecayMode*HLTBugWeightTau*sampleWeight*weightHepNupDY*TauSpinnerWeight*weightHepNupHighStatW";
  TString weight_DY = weight_VBF;
  TString cut_VBF = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTx==1 && HLTmatch==1)";
  TString cut_DY = "pt1>30 && pt2>30 && ptL1>20 && ptL2>30 && (isPFMuon && isTightMuon) && tightestHPSMVA3oldDMwLTWP>2 && decayModeFindingOldDM>0.5 && tightestAntiMuMVAWP>1 && tightestAntiECutWP > 0 && combRelIsoLeg1DBetav2<0.10 && (muFlag!=1 && vetoEventOld==0) && diTauNSVfitMass>50. && diTauCharge==0 && MtLeg1MVA<30. && (HLTxMu17Mu8>0.5)";


  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_0_180_diTauVisMass_150707.root","T","CompTimeVBF", weight_VBF+" * ("+cut_VBF+")",100,0,100)); 
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719.root","outTreePtOrd","CompTimeVBF", weight_VBF+" * ("+cut_VBF+")",100,0,100)); 
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_0_180_diTauVisMass_150707.root","T","CompTimeDY", weight_VBF+" * ("+cut_VBF+")",100,0,100)); 
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_180_diTauVisMass_3jetperm_150719.root","outTreePtOrd","CompTimeDY", weight_VBF+" * ("+cut_VBF+")",100,0,100)); 


  vector<TString> leg_entry;
  leg_entry.push_back("VBF weight default");
  leg_entry.push_back("VBF weight 3 jets perm");
  leg_entry.push_back("DY weight default");
  leg_entry.push_back("DY weight 3 jets perm");

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  //leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5");


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

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("t [s]");
  h[0]->GetXaxis()->SetTitleOffset(1.1);
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f s",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Computing time distribution in the VBF sample");

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="comp_time_VBF_3jet_perm";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



