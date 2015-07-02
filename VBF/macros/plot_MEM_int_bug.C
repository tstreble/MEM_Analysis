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




void plot_MEM_VBF_int_1D(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/","genTree","-log(MEM_VBF_Integrand[0])","MEM_VBF_Integrand[0]>0",100,-10,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/","genTree","-log(MEM_VBF_Integrand[0])","MEM_VBF_Integrand[0]>0",100,-10,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/","genTree","-log(MEM_VBF_Integrand_bug[0])","MEM_VBF_Integrand_bug[0]>0",100,-10,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/","genTree","-log(MEM_VBF_Integrand_bug[0])","MEM_VBF_Integrand_bug[0]>0",100,-10,50));

  vector<TString> leg_entry;
  leg_entry.push_back("VBF sample");
  leg_entry.push_back("DY sample");
  leg_entry.push_back("VBF sample with bug");
  leg_entry.push_back("DY sample with bug");

  TLegend* leg=new TLegend(0.45,0.6,0.75,0.85);
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
  h[0]->GetXaxis()->SetTitle("-log(I)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Full integrand distribution");

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="MEM_VBF_1D_bug";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_MEM_VBF_int_matched_1D(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/","genTree","-log(MEM_VBF_Integrand[0])","MEM_VBF_Integrand[0]>0&&ipair_recoPFJet30_matched==0",100,-10,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/","genTree","-log(MEM_VBF_Integrand[0])","MEM_VBF_Integrand[0]>0&&ipair_recoPFJet30_matched==0",100,-10,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/","genTree","-log(MEM_VBF_Integrand_bug[0])","MEM_VBF_Integrand_bug[0]>0&&ipair_recoPFJet30_matched==0",100,-10,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/","genTree","-log(MEM_VBF_Integrand_bug[0])","MEM_VBF_Integrand_bug[0]>0&&ipair_recoPFJet30_matched==0",100,-10,50));

  vector<TString> leg_entry;
  leg_entry.push_back("VBF sample");
  leg_entry.push_back("DY sample");
  leg_entry.push_back("VBF sample with bug");
  leg_entry.push_back("DY sample with bug");

  TLegend* leg=new TLegend(0.45,0.6,0.75,0.85);
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
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("-log(I)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Full integrand distribution with matching of leading jets");

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="MEM_VBF_1D_matched_bug";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_MEM_VBF_int_2D(TString sample){

  TString file;
  if(sample=="VBF")
    file="/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/";
  else if(sample=="DY")
    file="/data_CMS/cms/strebler/DY_Samples/ntuples_converted/";

  TH2F* h=single_plot2D(file,"genTree","-log(MEM_VBF_Integrand[0])","-log(MEM_VBF_Integrand_bug[0])","MEM_VBF_Integrand[0]>0&&MEM_VBF_Integrand_bug[0]>0",100,-10,50,100,-10,50);
  h->SetStats(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  h->GetYaxis()->SetTitle("-log(I) with bug");
  h->GetYaxis()->SetTitleOffset(1.7);
  h->GetXaxis()->SetTitle("-log(I) without bug");

  h->SetTitle("Effect of the bug in the "+sample+" sample");
  h->Scale(1/h->Integral());
  h->Draw("colz");

  TString filename="MEM_VBF_2D_bug_"+sample;
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}


