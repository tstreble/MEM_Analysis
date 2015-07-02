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

void plot_CSV0(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVscore[0]","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0",23,0,1.1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVscore[0]","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0",23,0,1.1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVscore[0]","n_recolep>2&&n_recotauh>0",23,0,1.1));

  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. OS, #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. SS, #geq 1 #tau_{h}");
  leg_entry.push_back("#geq 3 lep., #geq 1 #tau_{h}");


  TLegend* leg=new TLegend(0.3,0.65,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h_norm->Integral());
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("CSV b-tag");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("CSV b-tagger distribution for leading jet");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="CSV0_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



void plot_CSV1(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVscore[1]","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0",23,0,1.1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVscore[1]","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0",23,0,1.1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVscore[1]","n_recolep>2&&n_recotauh>0",23,0,1.1));

  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. OS, #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. SS, #geq 1 #tau_{h}");
  leg_entry.push_back("#geq 3 lep., #geq 1 #tau_{h}");


  TLegend* leg=new TLegend(0.3,0.65,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h_norm->Integral());
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("CSV b-tag");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("CSV b-tagger distribution for subleading jet");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="CSV1_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



void plot_CSVmax0(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVsort_CSVscore[0]","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0&&recoPFJet30_CSVsort_CSVscore[0]>0",23,0,1.1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVsort_CSVscore[0]","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0&&recoPFJet30_CSVsort_CSVscore[0]>0",23,0,1.1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVsort_CSVscore[0]","n_recolep>2&&n_recotauh>0&&recoPFJet30_CSVsort_CSVscore[0]>0",23,0,1.1));

  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. OS, #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. SS, #geq 1 #tau_{h}");
  leg_entry.push_back("#geq 3 lep., #geq 1 #tau_{h}");


  TLegend* leg=new TLegend(0.3,0.65,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h_norm->Integral());
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("CSV b-tag");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("CSV b-tagger distribution for jet with highest CSV b-tag");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="CSVmax0_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_CSVmax1(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVsort_CSVscore[1]","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0&&recoPFJet30_CSVsort_CSVscore[1]>0",23,0,1.1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVsort_CSVscore[1]","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0&&recoPFJet30_CSVsort_CSVscore[1]>0",23,0,1.1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVsort_CSVscore[1]","n_recolep>2&&n_recotauh>0&&recoPFJet30_CSVsort_CSVscore[1]>0",23,0,1.1));

  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. OS, #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. SS, #geq 1 #tau_{h}");
  leg_entry.push_back("#geq 3 lep., #geq 1 #tau_{h}");


  TLegend* leg=new TLegend(0.3,0.65,0.6,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h_norm->Integral());
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("CSV b-tag");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("CSV b-tagger distribution for jet with 2^{nd} highest CSV b-tag");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="CSVmax1_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_CSVmax2(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVsort_CSVscore[2]","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0&&recoPFJet30_CSVsort_CSVscore[2]>0",23,0,1.1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVsort_CSVscore[2]","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0&&recoPFJet30_CSVsort_CSVscore[2]>0",23,0,1.1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","recoPFJet30_CSVsort_CSVscore[2]","n_recolep>2&&n_recotauh>0&&recoPFJet30_CSVsort_CSVscore[2]>0",23,0,1.1));

  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. OS, #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. SS, #geq 1 #tau_{h}");
  leg_entry.push_back("#geq 3 lep., #geq 1 #tau_{h}");


  TLegend* leg=new TLegend(0.4,0.65,0.7,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h_norm->Integral());
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("CSV b-tag");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("CSV b-tagger distribution for jet with 3^{rd} highest CSV b-tag");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="CSVmax2_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}
