#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <THStack.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>
#include "Helpers.C"
#include <vector>
#include <TF1.h>


void plot_tauh_mass(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
  h.push_back(single_plot(file,"HTauTauTree","sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0",40,0,2.));
  h.push_back(single_plot(file,"HTauTauTree","sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4",40,0,2.));
  h[1]->Add(h[0]);
  h.push_back(single_plot(file,"HTauTauTree","sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=10 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=14",40,0,2.));
  h[2]->Add(h[1]);


  TLegend* leg=new TLegend(0.5,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("1-prong");
  leg_entry.push_back("1-prong + #pi^{0}'s");
  leg_entry.push_back("3-prong");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[2]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  h[0]->SetFillColor(kRed-7);
  h[1]->SetLineColor(kGreen);
  h[1]->SetFillColor(kGreen-7);
  h[2]->SetLineColor(kBlue);
  h[2]->SetFillColor(kBlue-7);

  //h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[2]->SetMaximum(1.25*h[2]->GetMaximum());
  //h[2]->SetMinimum(0);
  h[2]->GetXaxis()->SetTitle("m_{vis}(#tau_{h}) [GeV]");
  h[2]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[2]->GetYaxis()->SetTitleOffset(1.7);
  h[2]->SetTitle("");

  h[2]->Draw("hist");
  for(int i=h.size()-1; i>=0;i--){
    h[i]->Draw("histsame");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[2]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_mass";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_z_decayMode(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.3",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10",100,0,1.));



  TLegend* leg=new TLegend(0.5,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("1-prong");
  leg_entry.push_back("1-prong + #pi^{0}'s");
  leg_entry.push_back("3-prong");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  //h[0]->SetFillColor(kRed-7);
  h[1]->SetLineColor(kGreen);
  //h[1]->SetFillColor(kGreen-7);
  h[2]->SetLineColor(kBlue);
  //h[2]->SetFillColor(kBlue-7);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_z_decayMode_Htautau(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.3 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,1.));



  TLegend* leg=new TLegend(0.25,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("1-prong");
  leg_entry.push_back("1-prong + #pi^{0}'s");
  leg_entry.push_back("3-prong");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  //h[0]->SetFillColor(kRed-7);
  h[1]->SetLineColor(kGreen);
  //h[1]->SetFillColor(kGreen-7);
  h[2]->SetLineColor(kBlue);
  //h[2]->SetFillColor(kBlue-7);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_Htautau";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_z_decayMode_HWW(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.3 && genpart_HZDecayMode[genpart_HMothInd]==8",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]==8",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10 && genpart_HZDecayMode[genpart_HMothInd]==8",100,0,1.));



  TLegend* leg=new TLegend(0.25,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("1-prong");
  leg_entry.push_back("1-prong + #pi^{0}'s");
  leg_entry.push_back("3-prong");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  //h[0]->SetFillColor(kRed-7);
  h[1]->SetLineColor(kGreen);
  //h[1]->SetFillColor(kGreen-7);
  h[2]->SetLineColor(kBlue);
  //h[2]->SetFillColor(kBlue-7);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_HWW";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_z_decayMode_VBF(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/VBF/ntuple_VBF_HTauTau_*.root";

  vector<TH1F*> h;
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.3",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10",100,0,1.));



  TLegend* leg=new TLegend(0.5,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("1-prong");
  leg_entry.push_back("1-prong + #pi^{0}'s");
  leg_entry.push_back("3-prong");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  //h[0]->SetFillColor(kRed-7);
  h[1]->SetLineColor(kGreen);
  //h[1]->SetFillColor(kGreen-7);
  h[2]->SetLineColor(kBlue);
  //h[2]->SetFillColor(kBlue-7);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_VBF";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_z_decayMode_VBF_charge_split(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/VBF/ntuple_VBF_HTauTau_*.root";

  vector<TH1F*> h;
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.3 && genpart_pdg[genpart_TauMothInd]==15",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.3 && genpart_pdg[genpart_TauMothInd]==-15",100,0,1.));




  TLegend* leg=new TLegend(0.5,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("1-prong #tau^{-}");
  leg_entry.push_back("1-prong #tau^{+}");

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  //h[0]->SetFillColor(kRed-7);
  h[1]->SetLineColor(kGreen);
  //h[1]->SetFillColor(kGreen-7);
  //h[2]->SetLineColor(kBlue);
  //h[2]->SetFillColor(kBlue-7);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_VBF_charge_split";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_z_decayMode_ttZ(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttV/ntuple_ttZ_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.3",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10",100,0,1.));



  TLegend* leg=new TLegend(0.5,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("1-prong");
  leg_entry.push_back("1-prong + #pi^{0}'s");
  leg_entry.push_back("3-prong");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  //h[0]->SetFillColor(kRed-7);
  h[1]->SetLineColor(kGreen);
  //h[1]->SetFillColor(kGreen-7);
  h[2]->SetLineColor(kBlue);
  //h[2]->SetFillColor(kBlue-7);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_ttZ";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_z_decayMode_1prong(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && genpart_pt[genpart_TauMothInd]<50",20,0,1.));
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && genpart_pt[genpart_TauMothInd]>50 && genpart_pt[genpart_TauMothInd]<100",20,0,1.));
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && genpart_pt[genpart_TauMothInd]>100 && genpart_pt[genpart_TauMothInd]<150",20,0,1.));
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && genpart_pt[genpart_TauMothInd]>150 && genpart_pt[genpart_TauMothInd]<200",20,0,1.));
 



  TLegend* leg=new TLegend(0.5,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("p_{T}(#tau)<50 GeV");
  leg_entry.push_back("50<p_{T}(#tau)<100 GeV");
  leg_entry.push_back("100<p_{T}(#tau)<150 GeV");
  leg_entry.push_back("150<p_{T}(#tau)<200 GeV");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kBlack);
  h[1]->SetLineColor(kRed);
  h[2]->SetLineColor(kGreen);
  h[3]->SetLineColor(kBlue);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_1prong";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_z_decayMode_1prong_VBF(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/VBF/ntuple_VBF_HTauTau_*.root";

  vector<TH1F*> h;
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && genpart_pt[genpart_TauMothInd]<50",20,0,1.));
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && genpart_pt[genpart_TauMothInd]>50 && genpart_pt[genpart_TauMothInd]<100",20,0,1.));
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && genpart_pt[genpart_TauMothInd]>100 && genpart_pt[genpart_TauMothInd]<150",20,0,1.));
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && genpart_pt[genpart_TauMothInd]>150 && genpart_pt[genpart_TauMothInd]<200",20,0,1.));
 



  TLegend* leg=new TLegend(0.5,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("p_{T}(#tau)<50 GeV");
  leg_entry.push_back("50<p_{T}(#tau)<100 GeV");
  leg_entry.push_back("100<p_{T}(#tau)<150 GeV");
  leg_entry.push_back("150<p_{T}(#tau)<200 GeV");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kBlack);
  h[1]->SetLineColor(kRed);
  h[2]->SetLineColor(kGreen);
  h[3]->SetLineColor(kBlue);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_1prong_VBF";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_z_decayMode_1prong2(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && abs(genpart_eta[genpart_TauMothInd])<0.5",20,0,1.));
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && abs(genpart_eta[genpart_TauMothInd])>0.5 && abs(genpart_eta[genpart_TauMothInd])<1.0",20,0,1.));
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && abs(genpart_eta[genpart_TauMothInd])>1.0 && abs(genpart_eta[genpart_TauMothInd])<1.5",20,0,1.));
 h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && abs(genpart_eta[genpart_TauMothInd])>1.5 && abs(genpart_eta[genpart_TauMothInd])<2.0",20,0,1.));
 



  TLegend* leg=new TLegend(0.5,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("|#eta(#tau)|<0.5");
  leg_entry.push_back("0.5<|#eta(#tau)|<1.0");
  leg_entry.push_back("1.0<|#eta(#tau)|<1.5");
  leg_entry.push_back("1.5<|#eta(#tau)|<2.0");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kBlack);
  h[1]->SetLineColor(kRed);
  h[2]->SetLineColor(kGreen);
  h[3]->SetLineColor(kBlue);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_1prong2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}












void plot_z_decayMode_1prong_LR(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.3 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.3 && genpart_HZDecayMode[genpart_HMothInd]==8",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==0 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.3 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,1.));
  h[2]->Scale(2/h[2]->Integral());
  h[1]->Scale(1/h[1]->Integral());
  h[2]->Add(h[1],-1);  
  

  TLegend* leg=new TLegend(0.25,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("1-prong unpolarized");
  leg_entry.push_back("1-prong #tau_{L}");
  leg_entry.push_back("1-prong #tau_{R}");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  h[1]->SetLineColor(kGreen);
  h[2]->SetLineColor(kBlue);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_1prong_LR";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_z_decayMode_1prongpi0_LR(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]==8",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,1.));
  h[2]->Scale(2/h[2]->Integral());
  h[1]->Scale(1/h[1]->Integral());
  h[2]->Add(h[1],-1);  
  

  TLegend* leg=new TLegend(0.25,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("1-prong+#pi^{0}'s unpolarized");
  leg_entry.push_back("1-prong+#pi^{0}'s #tau_{L}");
  leg_entry.push_back("1-prong+#pi^{0}'s #tau_{R}");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  h[1]->SetLineColor(kGreen);
  h[2]->SetLineColor(kBlue);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_1prongpi0_LR";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}










void plot_z_decayMode_3prong_LR(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10 && genpart_HZDecayMode[genpart_HMothInd]==8",100,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,1.));
  h[2]->Scale(2/h[2]->Integral());
  h[1]->Scale(1/h[1]->Integral());
  h[2]->Add(h[1],-1);  
  

  TLegend* leg=new TLegend(0.25,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("3-prong unpolarized");
  leg_entry.push_back("3-prong #tau_{L}");
  leg_entry.push_back("3-prong #tau_{R}");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  h[1]->SetLineColor(kGreen);
  h[2]->SetLineColor(kBlue);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_3prong_LR";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}











void plot_z_decayMode_1prongpi0_mvis_bin(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]<=2 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>0.45 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.55",50,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]<=2 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>0.65 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.75",50,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]<=2 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>0.85 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.95",50,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]<=2 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>1.05 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<1.15",50,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]<=2 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>1.25 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<1.35",50,0,1.));

  vector<TF1*> f;
  f.push_back(new TF1("f0","0.02/(1-(0.5*0.5)/(1.777*1.777))*(x>((0.5*0.5)/(1.777*1.777)))",0,1));
  f.push_back(new TF1("f0","0.02/(1-(0.7*0.7)/(1.777*1.777))*(x>((0.7*0.7)/(1.777*1.777)))",0,1));
  f.push_back(new TF1("f0","0.02/(1-(0.9*0.9)/(1.777*1.777))*(x>((0.9*0.9)/(1.777*1.777)))",0,1));
  f.push_back(new TF1("f0","0.02/(1-(1.1*1.1)/(1.777*1.777))*(x>((1.1*1.1)/(1.777*1.777)))",0,1));
  f.push_back(new TF1("f0","0.02/(1-(1.3*1.3)/(1.777*1.777))*(x>((1.3*1.3)/(1.777*1.777)))",0,1));
	      

  TLegend* leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{1-prong + #pi^{0}'s}");

  vector<TString> leg_entry;
  leg_entry.push_back("0.45<m_{vis}(#tau_{h})<0.55 GeV");
  leg_entry.push_back("0.65<m_{vis}(#tau_{h})<0.75 GeV");
  leg_entry.push_back("0.85<m_{vis}(#tau_{h})<0.95 GeV");
  leg_entry.push_back("1.05<m_{vis}(#tau_{h})<1.15 GeV");
  leg_entry.push_back("1.25<m_{vis}(#tau_{h})<1.35 GeV");

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetLineColor(i+1);
    if(i>3)
      h[i]->SetLineColor(i+2);
    f[i]->SetLineColor(h[i]->GetLineColor());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.5*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
    f[i]->Draw("same");
  }


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_1prongpi0_mvis_bin";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void plot_z_decayMode_3prong_mvis_bin(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10 && genpart_HZDecayMode[genpart_HMothInd]<=2 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>0.65 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.75",50,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10 && genpart_HZDecayMode[genpart_HMothInd]<=2 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>0.85 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.95",50,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10 && genpart_HZDecayMode[genpart_HMothInd]<=2 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>1.05 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<1.15",50,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10 && genpart_HZDecayMode[genpart_HMothInd]<=2 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>1.25 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<1.35",50,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10 && genpart_HZDecayMode[genpart_HMothInd]<=2 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>1.45 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<1.55",50,0,1.));

  vector<TF1*> f;
  f.push_back(new TF1("f0","0.02/(1-(0.7*0.7)/(1.777*1.777))*(x>((0.7*0.7)/(1.777*1.777)))",0,1));
  f.push_back(new TF1("f0","0.02/(1-(0.9*0.9)/(1.777*1.777))*(x>((0.9*0.9)/(1.777*1.777)))",0,1));
  f.push_back(new TF1("f0","0.02/(1-(1.1*1.1)/(1.777*1.777))*(x>((1.1*1.1)/(1.777*1.777)))",0,1));
  f.push_back(new TF1("f0","0.02/(1-(1.3*1.3)/(1.777*1.777))*(x>((1.3*1.3)/(1.777*1.777)))",0,1));
  f.push_back(new TF1("f0","0.02/(1-(1.5*1.5)/(1.777*1.777))*(x>((1.5*1.5)/(1.777*1.777)))",0,1));

  TLegend* leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{3-prong}");

  vector<TString> leg_entry;
  leg_entry.push_back("0.65<m_{vis}(#tau_{h})<0.75 GeV");
  leg_entry.push_back("0.85<m_{vis}(#tau_{h})<0.95 GeV");
  leg_entry.push_back("1.05<m_{vis}(#tau_{h})<1.15 GeV");
  leg_entry.push_back("1.25<m_{vis}(#tau_{h})<1.35 GeV");
  leg_entry.push_back("1.45<m_{vis}(#tau_{h})<1.55 GeV");

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetLineColor(i+1);
    if(i>3)
      h[i]->SetLineColor(i+2);
    f[i]->SetLineColor(h[i]->GetLineColor());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.5*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
    f[i]->Draw("same");
  }


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_3prong_mvis_bin";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_z_decayMode_1prongpi0_mvis_bin_HWW(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_0_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]==8 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>0.45 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.55",50,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]==8 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>0.65 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.75",50,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]==8 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>0.85 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<0.95",50,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]==8 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>1.05 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<1.15",50,0,1.));
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]==8 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)>1.25 && sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)<1.35",50,0,1.));

  vector<TF1*> f;
  f.push_back(new TF1("f0","0.02/(1-(0.5*0.5)/(1.777*1.777))*(x>((0.5*0.5)/(1.777*1.777)))",0,1));
  f.push_back(new TF1("f0","0.02/(1-(0.7*0.7)/(1.777*1.777))*(x>((0.7*0.7)/(1.777*1.777)))",0,1));
  f.push_back(new TF1("f0","0.02/(1-(0.9*0.9)/(1.777*1.777))*(x>((0.9*0.9)/(1.777*1.777)))",0,1));
  f.push_back(new TF1("f0","0.02/(1-(1.1*1.1)/(1.777*1.777))*(x>((1.1*1.1)/(1.777*1.777)))",0,1));
  f.push_back(new TF1("f0","0.02/(1-(1.3*1.3)/(1.777*1.777))*(x>((1.3*1.3)/(1.777*1.777)))",0,1));
	      

  TLegend* leg=new TLegend(0.2,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{1-prong + #pi^{0}'s}");

  vector<TString> leg_entry;
  leg_entry.push_back("0.45<m_{vis}(#tau_{h})<0.55 GeV");
  leg_entry.push_back("0.65<m_{vis}(#tau_{h})<0.75 GeV");
  leg_entry.push_back("0.85<m_{vis}(#tau_{h})<0.95 GeV");
  leg_entry.push_back("1.05<m_{vis}(#tau_{h})<1.15 GeV");
  leg_entry.push_back("1.25<m_{vis}(#tau_{h})<1.35 GeV");

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetLineColor(i+1);
    if(i>3)
      h[i]->SetLineColor(i+2);
    f[i]->SetLineColor(h[i]->GetLineColor());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.5*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
    f[i]->Draw("same");
  }


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_1prongpi0_mvis_bin_HWW";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}












void plot_z_decayMode_1prongpi0_Htautau(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,1.));
  

  TH1F* h_mass=single_plot(file,"HTauTauTree","sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]>=1 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]<=4 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,2.);


  TH2F* h_2D = new TH2F("h_2D","h_2D",100,0,1,100,0,2.);
  for(unsigned int i=0;i<100;i++){
    for(unsigned int j=0;j<100;j++){

      float nentries_mass=h_mass->GetBinContent(j);
      int i_bin2D=h_2D->FindBin(i/100.+5e-3,2*j/100.+5e-3);
      float mass = 2*j/100.;
      if(i/100.>=((mass*mass)/(1.777*1.777)))
	h_2D->SetBinContent(i_bin2D,nentries_mass/(1-(mass*mass)/(1.777*1.777)));
      else{
	h_2D->SetBinContent(i_bin2D,0);
	if(i/100.>0.5 && i<100.<0.6 && 2*j/100.>0.5 && 2*j/100.<0.7)
	  cout<<i<<","<<j<<endl;
      }
    }
  }



  h.push_back((TH1F*)h_2D->ProjectionX());

  TLegend* leg=new TLegend(0.25,0.6,0.5,0.87);
  leg->SetHeader("#bf{1-prong+#pi^{0}'s}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Monte-Carlo");
  leg_entry.push_back("#splitline{Transfer function}{prediction}");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kBlack);
  h[1]->SetLineColor(kRed);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_1prongpi0_Htautau";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}











void plot_z_decayMode_3prong_Htautau(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_10_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;
  h.push_back(single_plot(file,"HTauTauTree","genpart_e/genpart_e[genpart_TauMothInd]","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,1.));
  

  TH1F* h_mass=single_plot(file,"HTauTauTree","sqrt(genpart_e**2-genpart_px**2-genpart_py**2-genpart_pz**2)","genpart_TauMothInd>=0 && abs(genpart_pdg)==66615 && genpart_TauGenDetailedDecayMode[genpart_TauMothInd]==10 && genpart_HZDecayMode[genpart_HMothInd]<=2",100,0,2.);


  TH2F* h_2D = new TH2F("h_2D","h_2D",100,0,1,100,0,2.);
  for(unsigned int i=0;i<100;i++){
    for(unsigned int j=0;j<100;j++){

      float nentries_mass=h_mass->GetBinContent(j);
      int i_bin2D=h_2D->FindBin(i/100.+5e-3,2*j/100.+5e-3);
      float mass = 2*j/100.;
      if(i/100.>=((mass*mass)/(1.777*1.777)))
	h_2D->SetBinContent(i_bin2D,nentries_mass/(1-(mass*mass)/(1.777*1.777)));
      else{
	h_2D->SetBinContent(i_bin2D,0);
	if(i/100.>0.5 && i<100.<0.6 && 2*j/100.>0.5 && 2*j/100.<0.7)
	  cout<<i<<","<<j<<endl;
      }
    }
  }



  h.push_back((TH1F*)h_2D->ProjectionX());

  TLegend* leg=new TLegend(0.25,0.6,0.5,0.87);
  leg->SetHeader("#bf{3-prong}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Monte-Carlo");
  leg_entry.push_back("#splitline{Transfer function}{prediction}");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kBlack);
  h[1]->SetLineColor(kRed);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("z=E_{vis}(#tau_{h})/E(#tau)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(int i=0; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tauh_z_decayMode_3prong_Htautau";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}


