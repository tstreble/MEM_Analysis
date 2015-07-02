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

void plot_BDT_3D(bool plot_log=false){

  vector<TH1F*> h;

  TString cut_VBF = "classID==0";
  TString cut_DY = "classID==1";
 
  h.push_back(single_plot("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root","TestTree","BDT", cut_VBF,20,-1,1)); 
  h.push_back(single_plot("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root","TestTree","BDT", cut_DY,20,-1,1)); 

  h.push_back(single_plot("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root","TrainTree","BDT", cut_VBF,20,-1,1)); 
  h.push_back(single_plot("/data_CMS/cms/strebler/BDT_rootfiles/BDT_3D_VBF_DYEmb.root","TrainTree","BDT", cut_DY,20,-1,1)); 

  vector<TString> leg_entry;
  leg_entry.push_back("VBF test");
  leg_entry.push_back("DY Embedded test");
  leg_entry.push_back("VBF train");
  leg_entry.push_back("DY Embedded train");

  TLegend* leg=new TLegend(0.37,0.67,0.65,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5");

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
  if(plot_log)
    c->SetLogy();

  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("BDT");
  h[0]->GetXaxis()->SetTitleOffset(1.1);
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("BDT output distribution");

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="BDT_3D_DYEmb";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



void plot_BDT_4DMEM(bool plot_log=false){

  vector<TH1F*> h;

  TString cut_VBF = "classID==0";
  TString cut_DY = "classID==1";
 
  h.push_back(single_plot("/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DYEmb.root","TestTree","BDT", cut_VBF,20,-1,1)); 
  h.push_back(single_plot("/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DYEmb.root","TestTree","BDT", cut_DY,20,-1,1)); 
  h.push_back(single_plot("/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DYEmb.root","TrainTree","BDT", cut_VBF,20,-1,1)); 
  h.push_back(single_plot("/data_CMS/cms/strebler/BDT_rootfiles/BDT_4DMEM_DY5D_VBF_DYEmb.root","TrainTree","BDT", cut_DY,20,-1,1)); 


  vector<TString> leg_entry;
  leg_entry.push_back("VBF test");
  leg_entry.push_back("DY Embedded test");
  leg_entry.push_back("VBF train");
  leg_entry.push_back("DY Embedded train");

  TLegend* leg=new TLegend(0.2,0.67,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("M_{jj}>150 GeV, #Delta#eta>1.5");

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
  if(plot_log)
    c->SetLogy();

  h[0]->SetMaximum(1.5*h[0]->GetMaximum());
  h[0]->SetMinimum(0);

  h[0]->GetXaxis()->SetTitle("BDT");
  h[0]->GetXaxis()->SetTitleOffset(1.1);
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("BDT output distribution");

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="BDT_4DMEM_DYEmb";
  if(plot_log)
    filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



