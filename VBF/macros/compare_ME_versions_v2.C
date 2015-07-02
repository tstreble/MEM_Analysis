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
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv2_150520.root","T","CompTimeVBF","CompTimeVBF>=0",100,0,100));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv2_150520.root","T","CompTimeDY","CompTimeDY>=0",100,0,100));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv3_150521.root","T","CompTimeVBF","CompTimeVBF>=0",100,0,100));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv3_150521.root","T","CompTimeDY","CompTimeDY>=0",100,0,100));
  }

  else if(sample=="VBF"){
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv2_150520.root","T","CompTimeVBF","CompTimeVBF>=0",100,0,100));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv2_150520.root","T","CompTimeDY","CompTimeDY>=0",100,0,100));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv3_150521.root","T","CompTimeVBF","CompTimeVBF>=0",100,0,100));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv3_150521.root","T","CompTimeDY","CompTimeDY>=0",100,0,100));

  }

  vector<TString> leg_entry;
  leg_entry.push_back(Form("#splitline{Sig weight ME v2}{<t>=%.2f sec}",h[0]->GetMean()));
  leg_entry.push_back(Form("#splitline{Bkg weight ME v2}{<t>=%.2f sec}",h[1]->GetMean()));
  leg_entry.push_back(Form("#splitline{Sig weight ME v3}{<t>=%.2f sec}",h[2]->GetMean()));
  leg_entry.push_back(Form("#splitline{Bkg weight ME v3}{<t>=%.2f sec}",h[3]->GetMean()));



  TLegend* leg=new TLegend(0.5,0.4,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetFillColor(i+1);
    h[i]->SetLineWidth(2);
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


  TString filename="comp_time_"+sample+"_v2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_bkg_weights(TString sample){

  vector<TH1F*> h;
 
  if(sample=="DY"){
  
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/Htautau_ntuples_20_05_15_dy2Jets_GluonBugFix.root","T","-log(IntegralDY)","IntegralDY>0",55,-20,35));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv2_150520.root","T","-log(IntegralDY)","IntegralDY>0",55,-20,35));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv3_150521.root","T","-log(IntegralDY)","IntegralDY>0",55,-20,35));
   
   
  }


  else if(sample=="VBF"){
   
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/Htautau_ntuples_20_05_15_vbf_GluonBugFix.root","T","-log(IntegralDY)","IntegralDY>0",55,-20,35));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv2_150520.root","T","-log(IntegralDY)","IntegralDY>0",55,-20,35));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv3_150521.root","T","-log(IntegralDY)","IntegralDY>0",55,-20,35));

  }


  vector<TString> leg_entry;

  leg_entry.push_back("Full ME");
  leg_entry.push_back("ME v2");
  leg_entry.push_back("ME v3");


  TLegend* leg=new TLegend(0.55,0.4,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetFillColor(0);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("-log(W_{b})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Background weight distribution in the "+sample+" sample");

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="bkg_weights_"+sample+"_v2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_sig_weights(TString sample){

  vector<TH1F*> h;
 
  if(sample=="DY"){
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/Htautau_ntuples_20_05_15_dy2Jets_GluonBugFix.root","T","-log(IntegralVBF)","IntegralVBF>0",55,-20,35));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv2_150520.root","T","-log(IntegralVBF)","IntegralVBF>0",55,-20,35));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv3_150521.root","T","-log(IntegralVBF)","IntegralVBF>0",55,-20,35));
   
   
  }


  else if(sample=="VBF"){
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/Htautau_ntuples_20_05_15_vbf_GluonBugFix.root","T","-log(IntegralVBF)","IntegralVBF>0",55,-20,35));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv2_150520.root","T","-log(IntegralVBF)","IntegralVBF>0",55,-20,35));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv3_150521.root","T","-log(IntegralVBF)","IntegralVBF>0",55,-20,35));


  }


  vector<TString> leg_entry;
  leg_entry.push_back("Full ME");
  leg_entry.push_back("ME v2");
  leg_entry.push_back("ME v3");


  TLegend* leg=new TLegend(0.55,0.4,0.85,0.85);
  if(sample=="DY")
    leg=new TLegend(0.25,0.4,0.45,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetFillColor(0);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("-log(W_{s})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Signal weight distribution in the "+sample+" sample");

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="sig_weights_"+sample+"_v2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_LR(TString sample){

  vector<TH1F*> h;

  if(sample=="DY"){
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/Htautau_ntuples_20_05_15_dy2Jets_GluonBugFix.root","T","IntegralVBF/(IntegralVBF+0.0003*IntegralDY)","IntegralVBF>=0&&IntegralDY>=0",20,0,1));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv2_150520.root","T","IntegralVBF/(IntegralVBF+0.0003*IntegralDY)","IntegralVBF>=0&&IntegralDY>=0",20,0,1));
    h.push_back(single_plot("/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv3_150521.root","T","IntegralVBF/(IntegralVBF+0.0003*IntegralDY)","IntegralVBF>=0&&IntegralDY>=0",20,0,1));

  }


  else if(sample=="VBF"){
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/Htautau_ntuples_20_05_15_vbf_GluonBugFix.root","T","IntegralVBF/(IntegralVBF+0.00026*IntegralDY)","IntegralVBF>=0&&IntegralDY>=0",20,0,1));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv2_150520.root","T","IntegralVBF/(IntegralVBF+0.00026*IntegralDY)","IntegralVBF>=0&&IntegralDY>=0",20,0,1));
    h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv3_150521.root","T","IntegralVBF/(IntegralVBF+0.00026*IntegralDY)","IntegralVBF>=0&&IntegralDY>=0",20,0,1));

  }


  vector<TString> leg_entry;
  leg_entry.push_back("Full ME");
  leg_entry.push_back("ME v2");
  leg_entry.push_back("ME v3");
  
  TLegend* leg=new TLegend(0.55,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetFillColor(0);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("w_{s}/(w_{s}+0.00026w_{b})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->GetXaxis()->SetTitleOffset(1.1);

  h[0]->SetTitle("Likelihood ratio in the "+sample+" sample");

  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="LR_"+sample+"_v2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_weights_2D_v2(TString sample){

  TString file1;
  TString file2;

  if(sample=="DY"){
    file1="/data_CMS/cms/strebler/DY_Samples/MEM_samples/Htautau_ntuples_20_05_15_dy2Jets_GluonBugFix.root";
    file2="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv2_150520.root";
  }

  else if(sample=="VBF"){
    file1="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/Htautau_ntuples_20_05_15_vbf_GluonBugFix.root";
    file2="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv2_150520.root";
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

  TH2F* hVBF=new TH2F("hVBF","hVBF",35,-5,30,35,-5,30);
  TH2F* hDY=new TH2F("hDY","hDY",35,-15,20,35,-15,20);
  
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
  hVBF->GetXaxis()->SetTitle("-log(W_{s}) full ME");
  hVBF->GetYaxis()->SetTitle("-log(W_{s}) ME v2");
 
  hVBF->GetXaxis()->SetTitleOffset(1.1);
  hVBF->SetTitle("Signal weight distribution in the "+sample+" sample");

  TCanvas* c=new TCanvas("c","c",650,600);
  //c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  hVBF->Draw("colz");

  TString filenameVBF="2D_sig_weights_"+sample+"_v2";
  c->SaveAs("../plots/pdf/"+filenameVBF+".pdf");
  c->SaveAs("../plots/png/"+filenameVBF+".png");

  hDY->SetStats(0);
  hDY->Scale(1/hDY->Integral());
  hDY->GetXaxis()->SetTitle("-log(W_{b}) full ME");
  hDY->GetYaxis()->SetTitle("-log(W_{b}) ME v2");
  
  hDY->GetXaxis()->SetTitleOffset(1.1);
  hDY->SetTitle("Background weight distribution in the "+sample+" sample");

  hDY->Draw("colz");

  TString filenameDY="2D_bkg_weights_"+sample+"_v2";
  c->SaveAs("../plots/pdf/"+filenameDY+".pdf");
  c->SaveAs("../plots/png/"+filenameDY+".png");

  return;

}




void plot_weights_2D_v3(TString sample){

  TString file1;
  TString file2;

  if(sample=="DY"){
    file1="/data_CMS/cms/strebler/DY_Samples/MEM_samples/Htautau_ntuples_20_05_15_dy2Jets_GluonBugFix.root";
    file2="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv3_150521.root";
  }

  else if(sample=="VBF"){
    file1="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/Htautau_ntuples_20_05_15_vbf_GluonBugFix.root";
    file2="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv3_150521.root";
  }


  TChain * tree1 = new TChain("T");
  tree1->Add(file1);
  TChain * tree2 = new TChain("T");
  tree2->Add(file2);

  float _IntegralVBF_v1;
  float _IntegralVBF_v3;
  float _IntegralDY_v1;
  float _IntegralDY_v3;


  tree1->SetBranchAddress("IntegralVBF",&_IntegralVBF_v1);
  tree2->SetBranchAddress("IntegralVBF",&_IntegralVBF_v3);
  tree1->SetBranchAddress("IntegralDY",&_IntegralDY_v1);
  tree2->SetBranchAddress("IntegralDY",&_IntegralDY_v3);

  TH2F* hVBF=new TH2F("hVBF","hVBF",35,-5,30,35,-5,30);
  TH2F* hDY=new TH2F("hDY","hDY",35,-15,20,35,-15,20);
  
  Long64_t nentries = tree1->GetEntries();

  for (int i=0;i<nentries;i++) {
    _IntegralVBF_v1 = 0;
    _IntegralVBF_v3 = 0;
    _IntegralDY_v1 = 0;
    _IntegralDY_v3 = 0;

    tree1->GetEntry(i);
    tree2->GetEntry(i);

    hVBF->Fill(-log(_IntegralVBF_v1),-log(_IntegralVBF_v3));
    hDY->Fill(-log(_IntegralDY_v1),-log(_IntegralDY_v3));
	    
  }

  hVBF->SetStats(0);
  hVBF->Scale(1/hVBF->Integral());
  hVBF->GetXaxis()->SetTitle("-log(W_{s}) full ME");
  hVBF->GetYaxis()->SetTitle("-log(W_{s}) ME v3");
 
  hVBF->GetXaxis()->SetTitleOffset(1.1);
  hVBF->SetTitle("Signal weight distribution in the "+sample+" sample");

  TCanvas* c=new TCanvas("c","c",650,600);
  //c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  hVBF->Draw("colz");

  TString filenameVBF="2D_sig_weights_"+sample+"_v3";
  c->SaveAs("../plots/pdf/"+filenameVBF+".pdf");
  c->SaveAs("../plots/png/"+filenameVBF+".png");

  hDY->SetStats(0);
  hDY->Scale(1/hDY->Integral());
  hDY->GetXaxis()->SetTitle("-log(W_{b}) full ME");
  hDY->GetYaxis()->SetTitle("-log(W_{b}) ME v3");
  
  hDY->GetXaxis()->SetTitleOffset(1.1);
  hDY->SetTitle("Background weight distribution in the "+sample+" sample");

  hDY->Draw("colz");

  TString filenameDY="2D_bkg_weights_"+sample+"_v3";
  c->SaveAs("../plots/pdf/"+filenameDY+".pdf");
  c->SaveAs("../plots/png/"+filenameDY+".png");

  return;

}





void plot_LR_2D_v2(TString sample){

  TString file1;
  TString file2;

  if(sample=="DY"){
    file1="/data_CMS/cms/strebler/DY_Samples/MEM_samples/Htautau_ntuples_20_05_15_dy2Jets_GluonBugFix.root";
    file2="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv2_150520.root";
  }

  else if(sample=="VBF"){
    file1="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/Htautau_ntuples_20_05_15_vbf_GluonBugFix.root";
    file2="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv2_150520.root";
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

  TH2F* h=new TH2F("h","h",50,0,1,50,0,1);
  
  Long64_t nentries = tree1->GetEntries();

  for (int i=0;i<nentries;i++) {
    _IntegralVBF_v1 = 0;
    _IntegralVBF_v2 = 0;
    _IntegralDY_v1 = 0;
    _IntegralDY_v2 = 0;

    tree1->GetEntry(i);
    tree2->GetEntry(i);

    double LR_v1=_IntegralVBF_v1/(_IntegralVBF_v1+0.00026*_IntegralDY_v1);
    double LR_v2=_IntegralVBF_v2/(_IntegralVBF_v2+0.00026*_IntegralDY_v2);

    h->Fill(LR_v1,LR_v2);
	    
  }

  h->SetStats(0);
  h->Scale(1/h->Integral());
  h->GetXaxis()->SetTitle("LR full");
  h->GetYaxis()->SetTitle("LR v2");
 
  h->GetXaxis()->SetTitleOffset(1.1);
  h->SetTitle("LR distribution in the "+sample+" sample");

  TCanvas* c=new TCanvas("c","c",650,600);
  //c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  h->Draw("colz");

  TString filename="2D_LR_"+sample+"_v2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}













void plot_delta_weights_v2(TString sample){

  TString file1;
  TString file2;
  TString file3;

  if(sample=="DY"){
    file1="/data_CMS/cms/strebler/DY_Samples/MEM_samples/Htautau_ntuples_20_05_15_dy2Jets_GluonBugFix.root";
    file2="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv2_150520.root";
    file3="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv3_150521.root";

  }

  else if(sample=="VBF"){
    file1="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/Htautau_ntuples_20_05_15_vbf_GluonBugFix.root";
    file2="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv2_150520.root";
    file3="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv3_150521.root";

  }


  TChain * tree1 = new TChain("T");
  tree1->Add(file1);
  TChain * tree2 = new TChain("T");
  tree2->Add(file2);
  TChain * tree3 = new TChain("T");
  tree3->Add(file3);

  float _IntegralVBF_v1;
  float _IntegralVBF_v2;
  float _IntegralVBF_v3;
  float _IntegralDY_v1;
  float _IntegralDY_v2;
  float _IntegralDY_v3;


  tree1->SetBranchAddress("IntegralVBF",&_IntegralVBF_v1);
  tree2->SetBranchAddress("IntegralVBF",&_IntegralVBF_v2);
  tree3->SetBranchAddress("IntegralVBF",&_IntegralVBF_v3);

  tree1->SetBranchAddress("IntegralDY",&_IntegralDY_v1);
  tree2->SetBranchAddress("IntegralDY",&_IntegralDY_v2);
  tree3->SetBranchAddress("IntegralDY",&_IntegralDY_v3);


  TH1F* hVBF_v2=new TH1F("hVBF_v2","hVBF_v2",100,-1,1);
  TH1F* hDY_v2=new TH1F("hDY_v2","hDY_v2",100,-1,1);

  TH1F* hVBF_v3=new TH1F("hVBF_v3","hVBF_v3",100,-1,1);
  TH1F* hDY_v3=new TH1F("hDY_v3","hDY_v3",100,-1,1);
  
  Long64_t nentries = tree1->GetEntries();

  for (int i=0;i<nentries;i++) {
    _IntegralVBF_v1 = 0;
    _IntegralVBF_v2 = 0;
    _IntegralVBF_v3 = 0;

    _IntegralDY_v1 = 0;
    _IntegralDY_v2 = 0;
    _IntegralDY_v3 = 0;


    tree1->GetEntry(i);
    tree2->GetEntry(i);
    tree3->GetEntry(i);


    hVBF_v2->Fill((_IntegralVBF_v1-_IntegralVBF_v2)/_IntegralVBF_v1);
    hDY_v2->Fill((_IntegralDY_v1-_IntegralDY_v2)/_IntegralDY_v1);
    
    hVBF_v3->Fill((_IntegralVBF_v1-_IntegralVBF_v3)/_IntegralVBF_v1);
    hDY_v3->Fill((_IntegralDY_v1-_IntegralDY_v3)/_IntegralDY_v1);
	    
  }

  vector<TH1F*> h;
  h.push_back(hVBF_v2);
  h.push_back(hDY_v2);
  h.push_back(hVBF_v3);
  h.push_back(hDY_v3);


  vector<TString> leg_entry;
  leg_entry.push_back("Sig weight ME v2");
  leg_entry.push_back("Bkg weight ME v2");
  leg_entry.push_back("Sig weight ME v3");
  leg_entry.push_back("Bkg weight ME v3");


  TLegend* leg=new TLegend(0.25,0.4,0.55,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    //h[i]->SetFillColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    //h[i]->SetFillStyle(3004);
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("(W_{full}-W_{simpl})/W_{full}");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Relative variation of the weights in the "+sample+" sample");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="delta_weights_"+sample;
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_delta_LR_v2(TString sample){

  TString file1;
  TString file2;
  TString file3;

  if(sample=="DY"){
    file1="/data_CMS/cms/strebler/DY_Samples/MEM_samples/Htautau_ntuples_20_05_15_dy2Jets_GluonBugFix.root";
    file2="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv2_150520.root";
    file3="/data_CMS/cms/strebler/DY_Samples/MEM_samples/DY_2jets_1prong_MEv3_150521.root";

  }

  else if(sample=="VBF"){
    file1="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/Htautau_ntuples_20_05_15_vbf_GluonBugFix.root";
    file2="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv2_150520.root";
    file3="/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_1prong_MEv3_150521.root";

  }


  TChain * tree1 = new TChain("T");
  tree1->Add(file1);
  TChain * tree2 = new TChain("T");
  tree2->Add(file2);
  TChain * tree3 = new TChain("T");
  tree3->Add(file3);

  float _IntegralVBF_v1;
  float _IntegralVBF_v2;
  float _IntegralVBF_v3;
  float _IntegralDY_v1;
  float _IntegralDY_v2;
  float _IntegralDY_v3;


  tree1->SetBranchAddress("IntegralVBF",&_IntegralVBF_v1);
  tree2->SetBranchAddress("IntegralVBF",&_IntegralVBF_v2);
  tree3->SetBranchAddress("IntegralVBF",&_IntegralVBF_v3);

  tree1->SetBranchAddress("IntegralDY",&_IntegralDY_v1);
  tree2->SetBranchAddress("IntegralDY",&_IntegralDY_v2);
  tree3->SetBranchAddress("IntegralDY",&_IntegralDY_v3);


  TH1F* h_v2=new TH1F("hVBF_v2","hVBF_v2",50,-2.,2.);
  TH1F* h_v3=new TH1F("hVBF_v3","hVBF_v3",50,-2.,2.);
  
  Long64_t nentries = tree1->GetEntries();

  for (int i=0;i<nentries;i++) {
    _IntegralVBF_v1 = 0;
    _IntegralVBF_v2 = 0;
    _IntegralVBF_v3 = 0;

    _IntegralDY_v1 = 0;
    _IntegralDY_v2 = 0;
    _IntegralDY_v3 = 0;


    tree1->GetEntry(i);
    tree2->GetEntry(i);
    tree3->GetEntry(i);

    double LR_v1=_IntegralVBF_v1/(_IntegralVBF_v1+0.00026*_IntegralDY_v1);
    double LR_v2=_IntegralVBF_v2/(_IntegralVBF_v2+0.00026*_IntegralDY_v2);
    double LR_v3=_IntegralVBF_v3/(_IntegralVBF_v3+0.00026*_IntegralDY_v3);

    h_v2->Fill((LR_v1-LR_v2)/LR_v1);
    h_v3->Fill((LR_v1-LR_v3)/LR_v1);
  
	    
  }

  vector<TH1F*> h;
  h.push_back(h_v2);
  h.push_back(h_v3);


  vector<TString> leg_entry;
  leg_entry.push_back("v2");
  leg_entry.push_back("v3");


  TLegend* leg=new TLegend(0.7,0.7,0.8,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    //h[i]->SetFillColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    //h[i]->SetFillStyle(3004);
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("(LR_{full}-LR_{simpl})/LR_{full}");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->GetXaxis()->SetTitleOffset(1.1);

  h[0]->SetTitle(sample+" sample");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="delta_LR_"+sample;
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}
