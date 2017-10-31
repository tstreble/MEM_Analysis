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


void plot_lepMVA(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split.root";

  TString var_ele = "recoele_leptonMVA";
  TString var_mu = "recomu_leptonMVA";
  
  int nbin = 20;
  float xmin= -1.;
  float xmax = 1.;

  TH1F* h_prompt = single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_ele,"recoele_isGenMatched",nbin,xmin,xmax);
  h_prompt->Add( single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_mu,"recomu_isGenMatched",nbin,xmin,xmax) );

  TH1F* h_fake = single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_ele,"!recoele_isGenMatched",nbin,xmin,xmax);
  h_fake->Add( single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_mu,"!recomu_isGenMatched",nbin,xmin,xmax) );

  vector<TH1F*> h;
  h.push_back(h_prompt);
  h.push_back(h_fake);

  TLegend* leg=new TLegend(0.5,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Prompt");
  leg_entry.push_back("Non-prompt");

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  h[1]->SetLineColor(kBlack);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Lepton MVA");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");


  h[0]->Draw();
  for(int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  

  leg->Draw("same");

  TLatex *texl = new TLatex(xmin+0.01*(xmax-xmin),1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="lepton_MVA";
  c->SaveAs("../plots/pdf/lepton_var/"+filename+".pdf");
  c->SaveAs("../plots/png/lepton_var/"+filename+".png");

  return;

}





void plot_miniRelIso(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split.root";

  TString var_ele = "recoele_miniRelIso";
  TString var_mu = "recomu_miniRelIso";
  
  int nbin = 20;
  float xmin= 0;
  float xmax = 0.4;

  TH1F* h_prompt = single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_ele,"recoele_isGenMatched",nbin,xmin,xmax);
  h_prompt->Add( single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_mu,"recomu_isGenMatched",nbin,xmin,xmax) );

  TH1F* h_fake = single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_ele,"!recoele_isGenMatched",nbin,xmin,xmax);
  h_fake->Add( single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_mu,"!recomu_isGenMatched",nbin,xmin,xmax) );

  vector<TH1F*> h;
  h.push_back(h_prompt);
  h.push_back(h_fake);

  TLegend* leg=new TLegend(0.5,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Prompt");
  leg_entry.push_back("Non-prompt");

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  h[1]->SetLineColor(kBlack);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Rel. isolation");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");


  h[0]->Draw();
  for(int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  

  leg->Draw("same");

  TLatex *texl = new TLatex(xmin+0.01*(xmax-xmin),1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="lepton_miniRelIso";
  c->SaveAs("../plots/pdf/lepton_var/"+filename+".pdf");
  c->SaveAs("../plots/png/lepton_var/"+filename+".png");

  return;

}






void plot_jetPtRatio(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split.root";

  TString var_ele = "recoele_jetPtRatio";
  TString var_mu = "recomu_jetPtRatio";
  
  int nbin = 24;
  float xmin= 0;
  float xmax = 1.2;

  TH1F* h_prompt = single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_ele,"recoele_isGenMatched",nbin,xmin,xmax);
  h_prompt->Add( single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_mu,"recomu_isGenMatched",nbin,xmin,xmax) );

  TH1F* h_fake = single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_ele,"!recoele_isGenMatched",nbin,xmin,xmax);
  h_fake->Add( single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_mu,"!recomu_isGenMatched",nbin,xmin,xmax) );

  vector<TH1F*> h;
  h.push_back(h_prompt);
  h.push_back(h_fake);

  TLegend* leg=new TLegend(0.3,0.65,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Prompt");
  leg_entry.push_back("Non-prompt");

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  h[1]->SetLineColor(kBlack);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Lepton jet p_{T} ratio");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");


  h[0]->Draw();
  for(int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  

  leg->Draw("same");

  TLatex *texl = new TLatex(xmin+0.01*(xmax-xmin),1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="lepton_jetPtRatio";
  c->SaveAs("../plots/pdf/lepton_var/"+filename+".pdf");
  c->SaveAs("../plots/png/lepton_var/"+filename+".png");

  return;

}







void plot_jetPtRel(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split.root";

  TString var_ele = "recoele_jetPtRel*(recoele_jetPtRel<30)+29.99*(recoele_jetPtRel>30)";
  TString var_mu = "recomu_jetPtRel*(recomu_jetPtRel<30)+29.99*(recomu_jetPtRel>30)";
  
  int nbin = 30;
  float xmin= 0;
  float xmax = 30.;

  TH1F* h_prompt = single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_ele,"recoele_isGenMatched",nbin,xmin,xmax);
  h_prompt->Add( single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_mu,"recomu_isGenMatched",nbin,xmin,xmax) );

  TH1F* h_fake = single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_ele,"!recoele_isGenMatched",nbin,xmin,xmax);
  h_fake->Add( single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_mu,"!recomu_isGenMatched",nbin,xmin,xmax) );

  vector<TH1F*> h;
  h.push_back(h_prompt);
  h.push_back(h_fake);

  TLegend* leg=new TLegend(0.5,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Prompt");
  leg_entry.push_back("Non-prompt");

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  h[1]->SetLineColor(kBlack);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Lepton jet rel. p_{T} [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f GeV",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");


  h[0]->Draw();
  for(int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  

  leg->Draw("same");

  TLatex *texl = new TLatex(xmin+0.01*(xmax-xmin),1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="lepton_jetPtRel";
  c->SaveAs("../plots/pdf/lepton_var/"+filename+".pdf");
  c->SaveAs("../plots/png/lepton_var/"+filename+".png");

  return;

}






void plot_jetCSV(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split.root";

  TString var_ele = "0.01*(recoele_jetCSV<0) + recoele_jetCSV*(recoele_jetCSV>0 && recoele_jetCSV<1) + 0.99*(recoele_jetCSV>1)";
  TString var_mu = "0.01*(recomu_jetCSV<0) + recomu_jetCSV*(recomu_jetCSV>0 && recomu_jetCSV<1) + 0.99*(recomu_jetCSV>1)";
  
  int nbin = 20;
  float xmin= 0;
  float xmax = 1.;

  TH1F* h_prompt = single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_ele,"recoele_isGenMatched",nbin,xmin,xmax);
  h_prompt->Add( single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_mu,"recomu_isGenMatched",nbin,xmin,xmax) );

  TH1F* h_fake = single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_ele,"!recoele_isGenMatched",nbin,xmin,xmax);
  h_fake->Add( single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_mu,"!recomu_isGenMatched",nbin,xmin,xmax) );

  vector<TH1F*> h;
  h.push_back(h_prompt);
  h.push_back(h_fake);

  TLegend* leg=new TLegend(0.5,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Prompt");
  leg_entry.push_back("Non-prompt");

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  h[1]->SetLineColor(kBlack);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("CSV btag");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");


  h[0]->Draw();
  for(int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  

  leg->Draw("same");

  TLatex *texl = new TLatex(xmin+0.01*(xmax-xmin),1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="lepton_jetCSV";
  c->SaveAs("../plots/pdf/lepton_var/"+filename+".pdf");
  c->SaveAs("../plots/png/lepton_var/"+filename+".png");

  return;

}







void plot_jetNtracks(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split.root";

  TString var_ele = "recoele_jetNDauChargedMVASel*(recoele_jetNDauChargedMVASel<6)+ 5*(recoele_jetNDauChargedMVASel>5)";
  TString var_mu = "recomu_jetNDauChargedMVASel*(recomu_jetNDauChargedMVASel<6)+ 5*(recomu_jetNDauChargedMVASel>5)";
  
  int nbin = 6;
  float xmin= -0.5;
  float xmax = 5.5;

  TH1F* h_prompt = single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_ele,"recoele_isGenMatched",nbin,xmin,xmax);
  h_prompt->Add( single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_mu,"recomu_isGenMatched",nbin,xmin,xmax) );

  TH1F* h_fake = single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_ele,"!recoele_isGenMatched",nbin,xmin,xmax);
  h_fake->Add( single_plot(file,"HTauTauTree_2lSS_lepMVA_CR",var_mu,"!recomu_isGenMatched",nbin,xmin,xmax) );

  vector<TH1F*> h;
  h.push_back(h_prompt);
  h.push_back(h_fake);

  TLegend* leg=new TLegend(0.5,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Prompt");
  leg_entry.push_back("Non-prompt");

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }
  
  h[0]->SetLineColor(kRed);
  h[1]->SetLineColor(kBlack);

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Number of jet tracks");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");


  h[0]->Draw();
  for(int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  

  leg->Draw("same");

  TLatex *texl = new TLatex(xmin+0.01*(xmax-xmin),1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="lepton_jetNtracks";
  c->SaveAs("../plots/pdf/lepton_var/"+filename+".pdf");
  c->SaveAs("../plots/png/lepton_var/"+filename+".png");

  return;

}





void plot_all(){

  plot_lepMVA();
  plot_miniRelIso();
  plot_jetPtRatio();
  plot_jetPtRel();
  plot_jetCSV();
  plot_jetNtracks();

}
