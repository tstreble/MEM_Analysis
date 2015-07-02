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


void plot_comput_time(TString sample){

  vector<TH1F*> h;
 
  if(sample=="DY"){
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/Official_ntuples_MEv1_19_04_15_DY.root","T","CompTimeVBF","",100,0,300));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/Official_ntuples_MEv2_20_04_15_DY.root","T","CompTimeVBF","",100,0,300));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/Official_ntuples_MEv1_19_04_15_DY.root","T","CompTimeDY","",100,0,300));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/Official_ntuples_MEv2_20_04_15_DY.root","T","CompTimeDY","",100,0,300));
  }
  else if(sample=="VBF"){
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/Official_ntuples_MEv2_20_04_15_VBF.root","T","CompTimeVBF","",100,0,100));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/Official_ntuples_MEv3_21_04_15_VBF.root","T","CompTimeVBF","",100,0,100));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/Official_ntuples_MEv2_20_04_15_VBF.root","T","CompTimeDY","",100,0,100));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/Official_ntuples_MEv3_21_04_15_VBF.root","T","CompTimeDY","",100,0,100));
  }

  vector<TString> leg_entry;
  if(sample=="DY"){
    leg_entry.push_back(Form("#splitline{Sig weight full ME}{<t>=%.2f sec}",h[0]->GetMean()));
    leg_entry.push_back(Form("#splitline{Sig weight ME v2}{<t>=%.2f sec}",h[1]->GetMean()));
    leg_entry.push_back(Form("#splitline{Bkg weight full ME}{<t>=%.2f sec}",h[2]->GetMean()));
    leg_entry.push_back(Form("#splitline{Bkg weight ME v2}{<t>=%.2f sec}",h[3]->GetMean()));
  }
  else if(sample=="VBF"){
    leg_entry.push_back(Form("#splitline{Sig weight ME v2}{<t>=%.2f sec}",h[0]->GetMean()));
    leg_entry.push_back(Form("#splitline{Sig weight ME v3}{<t>=%.2f sec}",h[1]->GetMean()));
    leg_entry.push_back(Form("#splitline{Bkg weight ME v2}{<t>=%.2f sec}",h[2]->GetMean()));
    leg_entry.push_back(Form("#splitline{Bkg weight ME v3}{<t>=%.2f sec}",h[3]->GetMean()));
  }


  TLegend* leg=new TLegend(0.5,0.4,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetFillColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetFillStyle(3004);
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Time [sec]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f sec",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Computation time in the "+sample+" sample with 4k points");

  h[0]->Draw("histE");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("samehistE");
  }
  
  leg->Draw("same");


  TString filename="comp_time_"+sample;
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_weights(TString sample){

  vector<TH1F*> h;
 
  if(sample=="DY"){
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/Official_ntuples_MEv1_19_04_15_DY.root","T","-log(IntegralVBF)","",55,-25,30));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/Official_ntuples_MEv2_20_04_15_DY.root","T","-log(IntegralVBF)","",55,-25,30));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/Official_ntuples_MEv1_19_04_15_DY.root","T","-log(IntegralDY)","",55,-25,30));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/Official_ntuples_MEv2_20_04_15_DY.root","T","-log(IntegralDY)","",55,-25,30));
  }


  else if(sample=="VBF"){
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/Official_ntuples_MEv2_20_04_15_VBF.root","T","-log(IntegralVBF)","",55,-25,30));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/Official_ntuples_MEv3_21_04_15_VBF.root","T","-log(IntegralVBF)","",55,-25,30));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/Official_ntuples_MEv2_20_04_15_VBF.root","T","-log(IntegralDY)","",55,-25,30));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/Official_ntuples_MEv3_21_04_15_VBF.root","T","-log(IntegralDY)","",55,-25,30));
  }


  vector<TString> leg_entry;
  if(sample=="DY"){
    leg_entry.push_back("Sig weight full ME");
    leg_entry.push_back("Sig weight ME v2");
    leg_entry.push_back("Bkg weight full ME");
    leg_entry.push_back("Bkg weight ME v2");
  }
  else if(sample=="VBF"){
    leg_entry.push_back("Sig weight ME v2");
    leg_entry.push_back("Sig weight ME v3");
    leg_entry.push_back("Bkg weight ME v2");
    leg_entry.push_back("Bkg weight ME v3");
  }

  TLegend* leg=new TLegend(0.55,0.4,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetFillColor(0);
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
  h[0]->GetXaxis()->SetTitle("-log(W)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Weight distribution in the "+sample+" sample");

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="weights_"+sample;
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_LR(TString sample){

  vector<TH1F*> h;

  if(sample=="DY"){
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/Official_ntuples_MEv1_19_04_15_DY.root","T","IntegralVBF/(IntegralVBF+0.0003*IntegralDY)","",20,0,1));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/ntuples_converted/Official_ntuples_MEv2_20_04_15_DY.root","T","IntegralVBF/(IntegralVBF+0.0003*IntegralDY)","",20,0,1));
  }


  else if(sample=="VBF"){
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/Official_ntuples_MEv2_20_04_15_VBF.root","T","IntegralVBF/(IntegralVBF+0.0003*IntegralDY)","",20,0,1));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/Official_ntuples_MEv3_21_04_15_VBF.root","T","IntegralVBF/(IntegralVBF+0.0003*IntegralDY)","",20,0,1));
  }


  vector<TString> leg_entry;
  if(sample=="DY"){
    leg_entry.push_back("Full ME");
    leg_entry.push_back("ME v2");
  }
  else if(sample=="VBF"){
    leg_entry.push_back("ME v2");
    leg_entry.push_back("ME v3");
  }

  TLegend* leg=new TLegend(0.55,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetFillColor(0);
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
  h[0]->GetXaxis()->SetTitle("w_{s}/(w_{s}+0.0003w_{b})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Likelihood ratio in the "+sample+" sample");

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="LR_"+sample;
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_weights_2D(TString sample){

  TString file1;
  TString file2;

  if(sample=="DY"){
    file1="/data_CMS/cms/strebler/DY_Samples/ntuples_converted/Official_ntuples_MEv1_19_04_15_DY.root";
    file2="/data_CMS/cms/strebler/DY_Samples/ntuples_converted/Official_ntuples_MEv2_20_04_15_DY.root";
  }

  else if(sample=="VBF"){
    file1="/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/Official_ntuples_MEv2_20_04_15_VBF.root";
    file2="/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/Official_ntuples_MEv3_21_04_15_VBF.root";
  }


  TChain * tree1 = new TChain("T");
  tree1->Add(file1);
  TChain * tree2 = new TChain("T");
  tree2->Add(file2);

  float _IntegralVBF_v1;
  float _IntegralVBF_v2;
  float _IntegralDY_v1;
  float _IntegralDY_v2;


  tree1->SetBranchAddress("IntegralVBF",&_IntegralVBF_v1);
  tree2->SetBranchAddress("IntegralVBF",&_IntegralVBF_v2);
  tree1->SetBranchAddress("IntegralDY",&_IntegralDY_v1);
  tree2->SetBranchAddress("IntegralDY",&_IntegralDY_v2);

  TH2F* hVBF=new TH2F("hVBF","hVBF",45,-20,25,45,-20,25);
  TH2F* hDY=new TH2F("hDY","hDY",35,-25,10,35,-25,10);
  
  Long64_t nentries = tree1->GetEntries();

  for (int i=0;i<nentries;i++) {
    _IntegralVBF_v1 = 0;
    _IntegralVBF_v2 = 0;
    _IntegralDY_v1 = 0;
    _IntegralDY_v2 = 0;

    tree1->GetEntry(i);
    tree2->GetEntry(i);

    hVBF->Fill(-log(_IntegralVBF_v1),-log(_IntegralVBF_v2));
    hDY->Fill(-log(_IntegralDY_v1),-log(_IntegralDY_v2));
	    
  }

  hVBF->SetStats(0);
  hVBF->Scale(1/hVBF->Integral());
  if(sample=="DY"){
    hVBF->GetXaxis()->SetTitle("-log(W_{s}) full ME");
    hVBF->GetYaxis()->SetTitle("-log(W_{s}) ME v2");
  }
  else if(sample=="VBF"){
    hVBF->GetXaxis()->SetTitle("-log(W_{s}) ME v2");
    hVBF->GetYaxis()->SetTitle("-log(W_{s}) ME v3");
  }
  hDY->GetXaxis()->SetTitleOffset(1.1);
  hVBF->SetTitle("Signal weight distribution in the "+sample+" sample");

  TCanvas* c=new TCanvas("c","c",650,600);
  //c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  hVBF->Draw("colz");

  TString filenameVBF="2D_sig_weights_"+sample;
  c->SaveAs("../plots/pdf/"+filenameVBF+".pdf");
  c->SaveAs("../plots/png/"+filenameVBF+".png");

  hDY->SetStats(0);
  hDY->Scale(1/hDY->Integral());
  if(sample=="DY"){
    hDY->GetXaxis()->SetTitle("-log(W_{b}) full ME");
    hDY->GetYaxis()->SetTitle("-log(W_{b}) ME v2");
  }
  else if(sample=="VBF"){
    hDY->GetXaxis()->SetTitle("-log(W_{b}) ME v2");
    hDY->GetYaxis()->SetTitle("-log(W_{b}) ME v3");
  }
  hDY->GetXaxis()->SetTitleOffset(1.1);
  hDY->SetTitle("Background weight distribution in the "+sample+" sample");

  hDY->Draw("colz");

  TString filenameDY="2D_bkg_weights_"+sample;
  c->SaveAs("../plots/pdf/"+filenameDY+".pdf");
  c->SaveAs("../plots/png/"+filenameDY+".png");

  return;

}

