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

using namespace std;


void plot_nPFJet30_untag_Wtag_cat_2CSVM(){

  vector<TH1F*> h;

  TH1F* h_2lOS=single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","n_pair_Wtag_recoPFJet30_untag","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814 && n_recoPFJet30_untag>1",20,0,20);

  TH1F* h_2lSS=single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","n_pair_Wtag_recoPFJet30_untag","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814 && n_recoPFJet30_untag>1",20,0,20);
    
  h.push_back(h_2lOS);
  h.push_back(h_2lSS);
  
  vector<TString> leg_entry;
  leg_entry.push_back("2 lep. OS, #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. SS, #geq 1 #tau_{h}");


  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetHeader("2 CSVM + #geq 2 untag. jets");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetBottomMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->GetXaxis()->SetTitle("n(pairs)");
  h[0]->SetTitle("Number of pair of untagged jets with 60<m_{jj}<100 GeV");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");



  TString filename="nPFJet30_untag_Wtag_cat_2CSVM_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_nPFJet30_untag_Wtag_cat_1CSVM_1CSVL(){

  vector<TH1F*> h;

  TH1F* h_2lOS=single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","n_pair_Wtag_recoPFJet30_untag","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 && n_recoPFJet30_untag>1",20,0,20);

  TH1F* h_2lSS=single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","n_pair_Wtag_recoPFJet30_untag","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 && n_recoPFJet30_untag>1",20,0,20);
    
  h.push_back(h_2lOS);
  h.push_back(h_2lSS);
  
  vector<TString> leg_entry;
  leg_entry.push_back("2 lep. OS, #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. SS, #geq 1 #tau_{h}");


  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetHeader("1 CSVM + 1CSVL + #geq 2 untag. jets");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetBottomMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->GetXaxis()->SetTitle("n(pairs)");
  h[0]->SetTitle("Number of pair of untagged jets with 60<m_{jj}<100 GeV");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");



  TString filename="nPFJet30_untag_Wtag_cat_1CSVM_1CSVL_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_2D_n_untag_nWtag_2lSS_2CSVM(){

  TH2F* h=single_plot2D("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","n_recoPFJet30_untag","n_pair_Wtag_recoPFJet30_untag","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814",20,0,20,20,0,20);


  h->SetStats(0);
  h->Scale(1/h->Integral());
 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetRightMargin(0.2);
  h->GetXaxis()->SetTitle("n(untag. jets)");
  h->GetYaxis()->SetTitle("n(W-tag. pairs)");
  h->GetZaxis()->SetTitle("Fraction of events");
  h->GetZaxis()->SetTitleOffset(1.3);
  h->SetTitle("Number of untagged jets vs number of W-tag pairs");

  h->Draw("colz");

  TLegend* leg=new TLegend(0.15,0.65,0.35,0.85);
  leg->SetHeader("#splitline{2 lep. SS, #geq 1 #tau_{h}}{2 CSVM}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->Draw("same");

  TString filename="2D_n_untag_nWtag_2lSS_2CSVM_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_2D_n_untag_nWtag_2lSS_1CSVM_1CSVL(){

  TH2F* h=single_plot2D("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","n_recoPFJet30_untag","n_pair_Wtag_recoPFJet30_untag","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423",20,0,20,20,0,20);


  h->SetStats(0);
  h->Scale(1/h->Integral());
 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetRightMargin(0.2);
  h->GetXaxis()->SetTitle("n(untag. jets)");
  h->GetYaxis()->SetTitle("n(W-tag. pairs)");
  h->GetZaxis()->SetTitle("Fraction of events");
  h->GetZaxis()->SetTitleOffset(1.3);
  h->SetTitle("Number of untagged jets vs number of W-tag pairs");

  h->Draw("colz");

  TLegend* leg=new TLegend(0.5,0.6,0.7,0.75);
  leg->SetHeader("#splitline{2 lep. SS, #geq 1 #tau_{h}}{1 CSVM + 1 CSVL}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->Draw("same");

  TString filename="2D_n_untag_nWtag_2lSS_1CSVM_1CSVL_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_2D_n_untag_nWtag_2lOS_2CSVM(){

  TH2F* h=single_plot2D("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","n_recoPFJet30_untag","n_pair_Wtag_recoPFJet30_untag","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814",20,0,20,20,0,20);


  h->SetStats(0);
  h->Scale(1/h->Integral());
 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetRightMargin(0.2);
  h->GetXaxis()->SetTitle("n(untag. jets)");
  h->GetYaxis()->SetTitle("n(W-tag. pairs)");
  h->GetZaxis()->SetTitle("Fraction of events");
  h->GetZaxis()->SetTitleOffset(1.3);
  h->SetTitle("Number of untagged jets vs number of W-tag pairs");

  h->Draw("colz");

  TLegend* leg=new TLegend(0.5,0.75,0.75,0.85);
  leg->SetHeader("#splitline{2 lep. OS, #geq 1 #tau_{h}}{2 CSVM}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->Draw("same");

  TString filename="2D_n_untag_nWtag_2lOS_2CSVM_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_2D_n_untag_nWtag_2lOS_1CSVM_1CSVL(){

  TH2F* h=single_plot2D("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","n_recoPFJet30_untag","n_pair_Wtag_recoPFJet30_untag","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423",20,0,20,20,0,20);


  h->SetStats(0);
  h->Scale(1/h->Integral());
 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetRightMargin(0.2);
  h->GetXaxis()->SetTitle("n(untag. jets)");
  h->GetYaxis()->SetTitle("n(W-tag. pairs)");
  h->GetZaxis()->SetTitle("Fraction of events");
  h->GetZaxis()->SetTitleOffset(1.3);
  h->SetTitle("Number of untagged jets vs number of W-tag pairs");

  h->Draw("colz");

  TLegend* leg=new TLegend(0.5,0.55,0.7,0.7);
  leg->SetHeader("#splitline{2 lep. OS, #geq 1 #tau_{h}}{1 CSVM + 1 CSVL}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->Draw("same");

  TString filename="2D_n_untag_nWtag_2lOS_1CSVM_1CSVL_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_btag_Wtag_cat(){

  TH1F* h_norm=(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","n_recoPFJet30","n_recolep>1&&n_recotauh>0",15,0,15));

  vector<TH1F*> h;

  //Cat.1 - 2 CSVM
  TH1F* h_2lOS=single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","0","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814 && n_pair_Wtag_recoPFJet30_untag>0",14,0,14);
  //Cat.1 - 1 CSVM + 1 CSVL
  h_2lOS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","1","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 &&  recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 && n_pair_Wtag_recoPFJet30_untag>0",14,0,14) );
  //Cat.2 - 2 CSVM
  h_2lOS->Add(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","2","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814 && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag>1",14,0,14));
  //Cat.2 - 1 CSVM + 1 CSVL
  h_2lOS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","3","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 &&  recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag>1",14,0,14) );
  //Cat.3 - 2 CSVM
  h_2lOS->Add(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","4","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814 && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag==1",14,0,14));
  //Cat.3 - 1 CSVM + 1 CSVL
  h_2lOS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","5","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 &&  recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag==1",14,0,14) );



  //Cat.1 - 2 CSVM
  TH1F* h_2lSS=single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","6","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814 && n_pair_Wtag_recoPFJet30_untag>0",14,0,14);
  //Cat.1 - 1 CSVM + 1 CSVL
  h_2lSS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","7","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 &&  recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 && n_pair_Wtag_recoPFJet30_untag>0",14,0,14) );
  //Cat.2 - 2 CSVM
  h_2lSS->Add(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","8","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814 && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag>1",14,0,14));
  //Cat.2 - 1 CSVM + 1 CSVL
  h_2lSS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","9","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 &&  recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag>1",14,0,14) );
  //Cat.3 - 2 CSVM
  h_2lSS->Add(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","10","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814 && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag==1",14,0,14));
  //Cat.3 - 1 CSVM + 1 CSVL
  h_2lSS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","11","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 &&  recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 && n_pair_Wtag_recoPFJet30_untag==0 && n_recoPFJet30_untag==1",14,0,14) );



  //Cat.3l - 2 CSVM
  TH1F* h_3l=single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","12","n_recolep>2&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814",14,0,14);
  //Cat.3l - 1 CSVM + 1 CSVL
  h_3l->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_dRveto.root","HTauTauTree","13","n_recolep>2&&n_recotauh>0 &&  recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423",14,0,14) );

  h.push_back(h_2lOS);
  h.push_back(h_2lSS);
  h.push_back(h_3l);
  
  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. OS, #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. SS, #geq 1 #tau_{h}");
  leg_entry.push_back("#geq 3 lep., #geq 1 #tau_{h}");


  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h[i]->Integral());
    h[i]->Scale(1/h_norm->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetBottomMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->GetXaxis()->SetLabelSize(0.);
  h[0]->GetXaxis()->SetNdivisions(7);
  h[0]->SetTitle("Categories for ttH, H->#tau#tau, with #geq 2l and #geq 1#tau_{h} in the final state");


  TPad *pad1 = new TPad("pad1", "pad1", 0, 0, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();      


  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");      

  vector<TString> cat;
  cat.push_back("Cat.1");
  cat.push_back("Cat.2");
  cat.push_back("Cat.3");
  cat.push_back("Cat.1");
  cat.push_back("Cat.2");
  cat.push_back("Cat.3");
  cat.push_back("Cat.3l");

 

  Float_t x, y;
  y = gPad->GetUymin()-0.001;
  TLatex t;

  t.SetTextAngle(60);
  t.SetTextSize(0.03);
  t.SetTextAlign(33);
  for (unsigned int i=0;i<cat.size();i++) {
    x = 0.5*(h[0]->GetXaxis()->GetBinCenter(2*i+1)+h[0]->GetXaxis()->GetBinCenter(2*i+2));
    t.DrawLatex(x,y,cat[i]);
  }



  TString filename="btag_Wtag_cat_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}

