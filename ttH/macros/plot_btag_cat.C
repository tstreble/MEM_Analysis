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


void plot_btag_cat(){

  vector<TH1F*> h;

  //2 CSVM
  TH1F* h_2lOS=single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","0","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814",5,0,5);
  //1 CSVM + 1 CSVL
  h_2lOS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","1","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 &&  recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423",5,0,5) );
  //1 CSVM + 0 CSVL
  h_2lOS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","2","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.423",5,0,5) );
  //2 CSVL
  h_2lOS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","3","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]<0.814 && recoPFJet30_CSVsort_CSVscore[0]>0.423 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423",5,0,5) );
  //<2 CSVL
  h_2lOS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","4","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]<0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.423",5,0,5) );


  //2 CSVM
  TH1F* h_2lSS=single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","0","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814",5,0,5);
  //1 CSVM + 1 CSVL
  h_2lSS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","1","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423",5,0,5) );
  //1 CSVM + 0 CSVL
  h_2lSS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","2","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.423",5,0,5) );
  //2 CSVL
  h_2lSS->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","3","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]<0.814 && recoPFJet30_CSVsort_CSVscore[0]>0.423 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423",5,0,5) );
  //<2 CSVL
  h_2lSS->Add(  single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","4","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]<0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.423",5,0,5) );
  
  //2 CSVM
  TH1F* h_3l=single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","0","n_recolep>2&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814",5,0,5);
  //1 CSVM + 1 CSVL
  h_3l->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","1","n_recolep>2&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423",5,0,5) );
  //1 CSVM + 0 CSVL
  h_3l->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","2","n_recolep>2&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.423",5,0,5) );
  //2 CSVL
  h_3l->Add( single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","3","n_recolep>2&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]<0.814 && recoPFJet30_CSVsort_CSVscore[0]>0.423 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423",5,0,5) );
  //<2 CSVL
  h_3l->Add(  single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","4","n_recolep>2&&n_recotauh>0 && recoPFJet30_CSVsort_CSVscore[0]<0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.423",5,0,5) );


  h.push_back(h_2lOS);
  h.push_back(h_2lSS);
  h.push_back(h_3l);
  
  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. OS, #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. SS, #geq 1 #tau_{h}");
  leg_entry.push_back("#geq 3 lep., #geq 1 #tau_{h}");


  TLegend* leg=new TLegend(0.55,0.65,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
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
  h[0]->GetXaxis()->SetLabelSize(0.);
  h[0]->GetXaxis()->SetNdivisions(5);
  h[0]->SetTitle("b-tag categories");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");

  vector<TString> cat;
  cat.push_back("2 CSVM");
  cat.push_back("#splitline{1 CSVM}{+ 1 CSVL}");
  cat.push_back("#splitline{1 CSVM}{+ 0 CSVL}");
  cat.push_back("2 CSVL");
  cat.push_back("<2 CSVL");


  Float_t x, y;
  y = gPad->GetUymin() - 0.01;
  TLatex t;

  t.SetTextAngle(60);
  t.SetTextSize(0.03);
  t.SetTextAlign(33);
  for (unsigned int i=0;i<cat.size();i++) {
    x = h[0]->GetXaxis()->GetBinCenter(i+1);
    t.DrawLatex(x,y,cat[i]);
  }



  TString filename="btag_cat_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_n_PFjets30_untag_2CSVM(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","n_recoPFJet30-2","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0  && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814",18,0,18));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","n_recoPFJet30-2","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0  && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814",18,0,18));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","n_recoPFJet30-2","n_recolep>2&&n_recotauh>0  && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814",18,0,18));
  
  vector<TString> leg_entry;
  leg_entry.push_back("2 lep. OS, #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. SS, #geq 1 #tau_{h}");
  leg_entry.push_back("#geq 3 lep., #geq 1 #tau_{h}");


  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
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
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("n(jets)");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Number of untagged jets in 2 CSVM category");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_PFJet30_untag_2CSVM_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_n_PFjets30_untag_1CSVM_1CSVL(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","n_recoPFJet30-2","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0  && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 ",18,0,18));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","n_recoPFJet30-2","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0  && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 ",18,0,18));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","n_recoPFJet30-2","n_recolep>2&&n_recotauh>0  && recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423 ",18,0,18));
  
  vector<TString> leg_entry;
  leg_entry.push_back("2 lep. OS, #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. SS, #geq 1 #tau_{h}");
  leg_entry.push_back("#geq 3 lep., #geq 1 #tau_{h}");


  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
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
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("n(jets)");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Number of untagged jets in 1 CSVM + 1 CSVL category");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_PFJet30_untag_1CSVM_1CSVL_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_n_PFjets30_untag_nobtag(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","n_recoPFJet30-2","n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0  && !(recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814) && !(recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423)",18,0,18));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","n_recoPFJet30-2","n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0  && !(recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814) && !(recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423)",18,0,18));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ntuple_ttH_nodRveto.root","HTauTauTree","n_recoPFJet30-2","n_recolep>2&&n_recotauh>0  && !(recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.814) && !(recoPFJet30_CSVsort_CSVscore[0]>0.814 && recoPFJet30_CSVsort_CSVscore[1]<0.814 && recoPFJet30_CSVsort_CSVscore[1]>0.423)",18,0,18));
  
  vector<TString> leg_entry;
  leg_entry.push_back("2 lep. OS, #geq 1 #tau_{h}");
  leg_entry.push_back("2 lep. SS, #geq 1 #tau_{h}");
  leg_entry.push_back("#geq 3 lep., #geq 1 #tau_{h}");


  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
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
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("n(jets)");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Number of untagged jets in no b-tag category");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_PFJet30_untag_nobtag_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



