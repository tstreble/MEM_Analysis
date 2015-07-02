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

void plot_z_taulep(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/VBF_8TeV_PU20_Jetak5_JEC_L1FastL2L3_METmtx_MET_15_12_14_CRAB3_v5/","demo/genTree","genPion_Tau_energy[0][0]/genHardScat_Tau_energy[0]","genHardScat_Tau_DecayMode[0]==13&&genHardScat_Tau_energy[0]>10&&genHardScat_Tau_energy[0]<20",20,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/VBF_8TeV_PU20_Jetak5_JEC_L1FastL2L3_METmtx_MET_15_12_14_CRAB3_v5/","demo/genTree","genPion_Tau_energy[0][0]/genHardScat_Tau_energy[0]","genHardScat_Tau_DecayMode[0]==13&&genHardScat_Tau_energy[0]>60&&genHardScat_Tau_energy[0]<80",20,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/VBF_8TeV_PU20_Jetak5_JEC_L1FastL2L3_METmtx_MET_15_12_14_CRAB3_v5/","demo/genTree","genPion_Tau_energy[0][0]/genHardScat_Tau_energy[0]","genHardScat_Tau_DecayMode[0]==13&&genHardScat_Tau_energy[0]>180&&genHardScat_Tau_energy[0]<200",20,0,1));

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




void plot_z_inv_taulep(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/VBF_8TeV_PU20_Jetak5_JEC_L1FastL2L3_METmtx_MET_15_12_14_CRAB3_v5/","demo/genTree","genHardScat_Tau_energy[0]/genPion_Tau_energy[0][0]","genHardScat_Tau_DecayMode[0]==13&&genPion_Tau_energy[0][0]>30&&genPion_Tau_energy[0][0]<40",30,0,30));
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/VBF_8TeV_PU20_Jetak5_JEC_L1FastL2L3_METmtx_MET_15_12_14_CRAB3_v5/","demo/genTree","genHardScat_Tau_energy[0]/genPion_Tau_energy[0][0]","genHardScat_Tau_DecayMode[0]==13&&genPion_Tau_energy[0][0]>60&&genPion_Tau_energy[0][0]<80",30,0,30));
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/VBF_8TeV_PU20_Jetak5_JEC_L1FastL2L3_METmtx_MET_15_12_14_CRAB3_v5/","demo/genTree","genHardScat_Tau_energy[0]/genPion_Tau_energy[0][0]","genHardScat_Tau_DecayMode[0]==13&&genPion_Tau_energy[0][0]>180&&genPion_Tau_energy[0][0]<200",30,0,30));

  vector<TString> leg_entry;
  leg_entry.push_back("30<E_{#mu}<40 GeV");
  leg_entry.push_back("60<E_{#mu}<80 GeV");
  leg_entry.push_back("180<E_{#mu}<200 GeV");

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
  h[0]->GetXaxis()->SetTitle("E_{#tau}/E_{#mu}");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("E_{#tau}/E_{#mu} distribution for #tau's from the VBF sample");

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="z_in_taul_VBF";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}
