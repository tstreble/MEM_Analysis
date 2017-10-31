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

using namespace std;


void plot_weight_ttH(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/MEM_samples/ttH_160104.root","T","log(Integral_ttH)*(Integral_ttH>0) -100*(Integral_ttH==0)","MC_weight*(Integral_ttH>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/TTJets_Samples/MEM_samples/ttjets_160105.root","T","log(Integral_ttH)*(Integral_ttH>0) -100*(Integral_ttH==0)","MC_weight*(Integral_ttH>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttW_Samples/MEM_samples/ttW_160104.root","T","log(Integral_ttH)*(Integral_ttH>0) -100*(Integral_ttH==0)","MC_weight*(Integral_ttH>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttZ_Samples/MEM_samples/ttZ_160105.root","T","log(Integral_ttH)*(Integral_ttH>0) -100*(Integral_ttH==0)","MC_weight*(Integral_ttH>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));

  
  TLegend* leg=new TLegend(0.3,0.4,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("#splitline{2lSS, 1CSVM + 1CSVL}{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("tt+jets");
  leg_entry.push_back("ttW");
  leg_entry.push_back("ttZ");

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("log(w_{ttH})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="weight_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_weight_ttjets(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/MEM_samples/ttH_160104.root","T","log(Integral_ttjets)*(Integral_ttjets>0) -100*(Integral_ttjets==0)","MC_weight*(Integral_ttjets>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/TTJets_Samples/MEM_samples/ttjets_160105.root","T","log(Integral_ttjets)*(Integral_ttjets>0) -100*(Integral_ttjets==0)","MC_weight*(Integral_ttjets>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttW_Samples/MEM_samples/ttW_160104.root","T","log(Integral_ttjets)*(Integral_ttjets>0) -100*(Integral_ttjets==0)","MC_weight*(Integral_ttjets>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttZ_Samples/MEM_samples/ttZ_160105.root","T","log(Integral_ttjets)*(Integral_ttjets>0) -100*(Integral_ttjets==0)","MC_weight*(Integral_ttjets>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  


  TLegend* leg=new TLegend(0.3,0.4,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("#splitline{2lSS, 1CSVM + 1CSVL}{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("tt+jets");
  leg_entry.push_back("ttW");
  leg_entry.push_back("ttZ");

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("log(w_{ttj})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="weight_ttjets";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_weight_ttW(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/MEM_samples/ttH_160104.root","T","log(Integral_ttW)*(Integral_ttW>0) -100*(Integral_ttW==0)","MC_weight*(Integral_ttW>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/TTJets_Samples/MEM_samples/ttjets_160105.root","T","log(Integral_ttW)*(Integral_ttW>0) -100*(Integral_ttW==0)","MC_weight*(Integral_ttW>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttW_Samples/MEM_samples/ttW_160104.root","T","log(Integral_ttW)*(Integral_ttW>0) -100*(Integral_ttW==0)","MC_weight*(Integral_ttW>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttZ_Samples/MEM_samples/ttZ_160105.root","T","log(Integral_ttW)*(Integral_ttW>0) -100*(Integral_ttW==0)","MC_weight*(Integral_ttW>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));

  
  TLegend* leg=new TLegend(0.3,0.4,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("#splitline{2lSS, 1CSVM + 1CSVL}{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("tt+jets");
  leg_entry.push_back("ttW");
  leg_entry.push_back("ttZ");

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("log(w_{ttW})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="weight_ttW";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void plot_weight_ttZ(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/MEM_samples/ttH_160104.root","T","log(Integral_ttZ)*(Integral_ttZ>0) -100*(Integral_ttZ==0)","MC_weight*(Integral_ttZ>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/TTJets_Samples/MEM_samples/ttjets_160105.root","T","log(Integral_ttZ)*(Integral_ttZ>0) -100*(Integral_ttZ==0)","MC_weight*(Integral_ttZ>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttW_Samples/MEM_samples/ttW_160104.root","T","log(Integral_ttZ)*(Integral_ttZ>0) -100*(Integral_ttZ==0)","MC_weight*(Integral_ttZ>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttZ_Samples/MEM_samples/ttZ_160105.root","T","log(Integral_ttZ)*(Integral_ttZ>0) -100*(Integral_ttZ==0)","MC_weight*(Integral_ttZ>=0 && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",75,-100,50));

  
  TLegend* leg=new TLegend(0.3,0.4,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("#splitline{2lSS, 1CSVM + 1CSVL}{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("tt+jets");
  leg_entry.push_back("ttW");
  leg_entry.push_back("ttZ");

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("log(w_{ttZ})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="weight_ttZ";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}










void plot_LR_ttjets(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/MEM_samples/ttH_miss_160111.root","T","Integral_ttH/(Integral_ttH+1e-9*Integral_ttjets)","MC_weight*(recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && integration_type==0)",10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/MEM_samples/ttH_miss_160111.root","T","Integral_ttH/(Integral_ttH+1e-9*Integral_ttjets)","MC_weight*(recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && integration_type==1)",10,0,1));

  h.push_back(single_plot("/data_CMS/cms/strebler/TTJets_Samples/MEM_samples/ttjets_miss_160108.root","T","Integral_ttH/(Integral_ttH+1e-9*Integral_ttjets)","MC_weight*(recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && integration_type==0)",10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/TTJets_Samples/MEM_samples/ttjets_miss_160108.root","T","Integral_ttH/(Integral_ttH+1e-9*Integral_ttjets)","MC_weight*(recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423 && integration_type==1)",10,0,1));

  //h.push_back(single_plot("/data_CMS/cms/strebler/ttZ_Samples/MEM_samples/ttZ_160105.root","T","Integral_ttH/(Integral_ttH+1e-9*Integral_ttjets)","MC_weight*((Integral_ttH>0||Integral_ttjets>0) && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",50,0,1));

  THStack* hsig = new THStack("hsig","hsig");
  float sig_norm=h[0]->Integral()+h[1]->Integral();
  
  h[0]->Scale(1/sig_norm);
  h[0]->SetLineColor(kBlue);
  h[0]->SetLineWidth(2);


  h[1]->Scale(1/sig_norm);
  h[1]->SetLineColor(kBlue+2);
  h[1]->SetLineWidth(2);

  hsig->Add(h[0]);
  hsig->Add(h[1]);

  THStack* hbkg = new THStack("hbkg","hbkg");
  float bkg_norm=h[2]->Integral()+h[3]->Integral();
  
  h[2]->Scale(1/bkg_norm);
  h[2]->SetFillColor(kGreen-2);
  h[2]->SetLineColor(kGreen-2);

  h[3]->Scale(1/bkg_norm);
  h[3]->SetFillColor(kGreen-1);
  h[3]->SetLineColor(kGreen-1);

  hbkg->Add(h[2]);
  hbkg->Add(h[3]);

  TLegend* leg=new TLegend(0.3,0.4,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("2lSS, 1CSVM + 1CSVL");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH w/o miss. jet");
  leg_entry.push_back("ttH w/ miss. jet");
  leg_entry.push_back("tt+jets w/o miss. jet");
  leg_entry.push_back("tt+jets w/ miss. jet");


  for(unsigned int i=0; i<h.size();i++){
    /*h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());*/
    leg->AddEntry(h[i],leg_entry[i]);
  }


  //h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  hbkg->SetMaximum(1.25*hsig->GetMaximum());
  //hbkg->SetMinimum(0);

  hbkg->Draw("hist");
  hsig->Draw("same");

  hbkg->GetXaxis()->SetTitle("w_{ttH})/(w_{ttH}+1e-9w_{ttj})");
  hbkg->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  hbkg->GetYaxis()->SetTitleOffset(1.7);
  hbkg->SetTitle("");

  c->Modified();

  
  /*for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
    }*/
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.02,0.79,"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_ttjets";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_LR_ttW(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/MEM_samples/ttH_160104.root","T","Integral_ttH/(Integral_ttH+1e-7*Integral_ttW)","MC_weight*((Integral_ttH>0||Integral_ttW>0) && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",50,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/TTJets_Samples/MEM_samples/ttjets_160105.root","T","Integral_ttH/(Integral_ttH+1e-7*Integral_ttW)","MC_weight*((Integral_ttH>0||Integral_ttW>0) && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",50,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttW_Samples/MEM_samples/ttW_160104.root","T","Integral_ttH/(Integral_ttH+1e-7*Integral_ttW)","MC_weight*((Integral_ttH>0||Integral_ttW>0) && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",50,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttZ_Samples/MEM_samples/ttZ_160105.root","T","Integral_ttH/(Integral_ttH+1e-7*Integral_ttW)","MC_weight*((Integral_ttH>0||Integral_ttW>0) && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",50,0,1));

  
  TLegend* leg=new TLegend(0.3,0.4,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("#splitline{2lSS, 1CSVM + 1CSVL}{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("tt+jets");
  leg_entry.push_back("ttW");
  leg_entry.push_back("ttZ");

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("w_{ttH})/(w_{ttH}+1e-7w_{ttW})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_ttW";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void plot_LR_ttZ(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/MEM_samples/ttH_160104.root","T","Integral_ttH/(Integral_ttH+Integral_ttZ)","MC_weight*((Integral_ttH>0||Integral_ttZ>0) && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",50,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/TTJets_Samples/MEM_samples/ttjets_160105.root","T","Integral_ttH/(Integral_ttH+Integral_ttZ)","MC_weight*((Integral_ttH>0||Integral_ttZ>0) && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",50,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttW_Samples/MEM_samples/ttW_160104.root","T","Integral_ttH/(Integral_ttH+Integral_ttZ)","MC_weight*((Integral_ttH>0||Integral_ttZ>0) && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",50,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttZ_Samples/MEM_samples/ttZ_160105.root","T","Integral_ttH/(Integral_ttH+Integral_ttZ)","MC_weight*((Integral_ttH>0||Integral_ttZ>0) && recoPFJet30_btag_CSVscore[0]>0.814 && recoPFJet30_btag_CSVscore[1]>0.423)",50,0,1));

  
  TLegend* leg=new TLegend(0.3,0.4,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->SetHeader("#splitline{2lSS, 1CSVM + 1CSVL}{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("tt+jets");
  leg_entry.push_back("ttW");
  leg_entry.push_back("ttZ");

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("w_{ttH})/(w_{ttH}+w_{ttZ})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_ttZ";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}










void plot_LR_full_bkg_ttZ_nomiss_14092016(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root","T","Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root","T","Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));


  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root","T","Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root","T","Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));


  
  TLegend* leg=new TLegend(0.3,0.5,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH MEM LR ttH vs t#bar{t}");
  leg_entry.push_back("ttZ MEM LR ttH vs t#bar{t}");
  leg_entry.push_back("ttH MEM LR ttH vs t#bar{t} + ttZ");
  leg_entry.push_back("ttZ MEM LR ttH vs t#bar{t} + ttZ");

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_ttZ_nomiss_14092016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void plot_LR_full_bkg_ttZ_missing_14092016(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root","T","Integral_ttH/(Integral_ttH+1e-13*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)",10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root","T","Integral_ttH/(Integral_ttH+1e-13*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)",10,0,1));


  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root","T","Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-3*Integral_ttZ+0.1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)",10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root","T","Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-3*Integral_ttZ+0.1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)",10,0,1));


  
  TLegend* leg=new TLegend(0.3,0.5,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH MEM LR ttH vs t#bar{t}");
  leg_entry.push_back("ttZ MEM LR ttH vs t#bar{t}");
  leg_entry.push_back("ttH MEM LR ttH vs t#bar{t} + ttZ");
  leg_entry.push_back("ttZ MEM LR ttH vs t#bar{t} + ttZ");

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_ttZ_missing_14092016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_LR_full_bkg_ttH_matching_14092016(){

  vector<TH1F*> h;

  h.push_back(single_plot("test_MEM_dR.root","T","Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)","(category==11 && isTrig && integration_type==0 && n_matched_jet_old==4)",10,0,1));
  h.push_back(single_plot("test_MEM_dR.root","T","Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)","(category==11 && isTrig && integration_type==0 && n_matched_jet_old<4)",10,0,1));


  
  TLegend* leg=new TLegend(0.3,0.5,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH 4 jets matched");
  leg_entry.push_back("ttH 4 jets not matched");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_matching_14092016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_LR_full_bkg_ttH_DM_nomiss_14092016(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root","T","Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && genH_decayMode[1]<=5)",10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root","T","Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && genH_decayMode[1]>5)",10,0,1));


  
  TLegend* leg=new TLegend(0.3,0.5,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH H#rightarrow#tau#tau");
  leg_entry.push_back("ttH H#rightarrowWW/ZZ");

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_DM_nomiss_14092016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_LR_full_bkg_ttH_fullmatch_matching_14092016(){

  vector<TH1F*> h;

  h.push_back(single_plot("test_full_perm.root","T","Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)","(category==11 && isTrig && integration_type==0 && n_matched_jet_old==4)",10,0,1));
  h.push_back(single_plot("test_full_perm.root","T","Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)","(category==11 && isTrig && integration_type==0 && n_matched_jet_old<4)",10,0,1));


  
  TLegend* leg=new TLegend(0.3,0.5,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH 4 jets matched");
  leg_entry.push_back("ttH 4 jets not matched");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_matching_full_perm_14092016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}










void plot_LR_ttZ_Ztautau_nomiss_15102016(){

  TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root";
  TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root";


  vector<TH1F*> h;
  h.push_back(single_plot(filename_ttH,"T","Integral_ttH/(Integral_ttH+0.5*Integral_ttZ)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+0.5*Integral_ttZ)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && genZ_decayMode[0]<=5)",10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("ttZ, Z#rightarrow#tau#tau");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_ttZ_Ztautau_nomiss_15102016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_LR_ttZ_Ztautau_missing_15102016(){

  TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root";
  TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root";


  vector<TH1F*> h;
  h.push_back(single_plot(filename_ttH,"T","Integral_ttH/(Integral_ttH+0.05*Integral_ttZ)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+0.05*Integral_ttZ)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1 && genZ_decayMode[0]<=5)",10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("ttZ, Z#rightarrow#tau#tau");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_ttZ_Ztautau_missing_15102016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_LR_ttZ_Zll_nomiss_15102016(){

  TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root";
  TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root";


  vector<TH1F*> h;
  h.push_back(single_plot(filename_ttH,"T","Integral_ttH/(Integral_ttH+1.*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+1.*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))",10,0,1));
  //h.push_back(single_plot(filename_ttH,"T","Integral_ttH/(Integral_ttH+1.*Integral_ttZ_Zll)","PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  //h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+1.*Integral_ttZ_Zll)","PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))",10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("ttZ, Z#rightarrowll");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_ttZ_Zll_nomiss_15102016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_LR_ttZ_Zll_missing_15102016(){

  TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root";
  TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root";


  vector<TH1F*> h;
  h.push_back(single_plot(filename_ttH,"T","Integral_ttH/(Integral_ttH+0.1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+0.1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1 && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))",10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("ttZ, Z#rightarrowll");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_ttZ_Zll_missing_15102016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void plot_LR_ttbar_DL_nomiss_15102016(){

  TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root";
  TString filename_ttbar = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/ttbar_DL_*.root";


  vector<TH1F*> h;
  h.push_back(single_plot(filename_ttH,"T","Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  h.push_back(single_plot(filename_ttbar,"T","Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))","event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && isTrig && integration_type==0)",10,0,1));
  //h.push_back(single_plot(filename_ttbar,"T","Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))","PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && isTrig && integration_type==0)",10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("Fake lepton background (MC)");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_ttbar_DL_nomiss_15102016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_LR_ttbar_DL_missing_15102016(){

  TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root";
  TString filename_ttbar = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/ttbar_DL_*.root";

  vector<TH1F*> h;
  h.push_back(single_plot(filename_ttH,"T","Integral_ttH/(Integral_ttH+1e-12*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)",10,0,1));
  h.push_back(single_plot(filename_ttbar,"T","Integral_ttH/(Integral_ttH+1e-12*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))","event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && isTrig && integration_type==1)",10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("Fake lepton background (MC)");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_ttbar_DL_missing_15102016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_LR_full_bkg_nomiss_15102016(){

  TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root";
  TString filename_ttbar = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/ttbar_DL_*.root";
  TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root";


  vector<TH1F*> h;
  h.push_back(single_plot(filename_ttH,"T","Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && genZ_decayMode[0]<=5)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))",10,0,1));
  h.push_back(single_plot(filename_ttbar,"T","Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)","event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && isTrig && integration_type==0)",10,0,1));


  /*h.push_back(single_plot(filename_ttH,"T","Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)","PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)","PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && genZ_decayMode[0]<=5)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)","PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))",10,0,1));
  h.push_back(single_plot(filename_ttbar,"T","Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)","PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && isTrig && integration_type==0)",10,0,1));*/
 
 

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("ttZ, Z#rightarrowll");
  leg_entry.push_back("Fake lepton background (MC)");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_full_bkg_nomiss_15102016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_LR_full_bkg_missing_15102016(){

  TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root";
  TString filename_ttbar = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/ttbar_DL_*.root";
  TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root";

  vector<TH1F*> h;
  /*h.push_back(single_plot(filename_ttH,"T","Integral_ttH/(Integral_ttH+1e-14*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+1e-14*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1 && genZ_decayMode[0]<=5)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+1e-14*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1 && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))",10,0,1));
  h.push_back(single_plot(filename_ttbar,"T","Integral_ttH/(Integral_ttH+1e-14*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)","event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && isTrig && integration_type==1)",10,0,1));*/
 

  h.push_back(single_plot(filename_ttH,"T","Integral_ttH/(Integral_ttH+5e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+5e-1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+5e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+5e-1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1 && genZ_decayMode[0]<=5)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T","Integral_ttH/(Integral_ttH+5e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+5e-1*Integral_ttZ_Zll)","MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1 && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))",10,0,1));
  h.push_back(single_plot(filename_ttbar,"T","Integral_ttH/(Integral_ttH+5e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+5e-1*Integral_ttZ_Zll)","event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && isTrig && integration_type==1)",10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("ttZ, Z#rightarrowll");
  leg_entry.push_back("Fake lepton background (MC)");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttH_full_bkg_missing_15102016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}










void plot_LR_ttH_nomiss_fullperm_25102016(){

  TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttH/*.root";
  TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttV/ttZ_split_2lSS_MEM_160927.root";
  TString filename_ttH_new = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttH/*.root";
  TString filename_ttZ_new = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttV/ttZ_split_2lSS_MEM_full_perm_161003.root";

  TString var="Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)";

  vector<TH1F*> h;
  h.push_back(single_plot(filename_ttH,"T",var,"MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  //h.push_back(single_plot(filename_ttZ,"T",var,"MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  h.push_back(single_plot(filename_ttH_new,"T",var,"MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  //h.push_back(single_plot(filename_ttZ_new,"T",var,"MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
 
 

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH old");
  //leg_entry.push_back("ttZ old");
  leg_entry.push_back("ttH full perm");
  //leg_entry.push_back("ttZ full perm");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle("a.u.");
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_fullperm_ttH_nomiss_25102016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_LR_ttZ_nomiss_fullperm_25102016(){

  TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttH/*.root";
  TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttV/ttZ_split_2lSS_MEM_160927.root";
  TString filename_ttH_new = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttH/*.root";
  TString filename_ttZ_new = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttV/ttZ_split_2lSS_MEM_full_perm_161003.root";

  TString var="Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)";

  vector<TH1F*> h;
  //h.push_back(single_plot(filename_ttH,"T",var,"MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  //h.push_back(single_plot(filename_ttZ,"T",var,"MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  h.push_back(single_plot(filename_ttZ,"T",var,"PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  //h.push_back(single_plot(filename_ttH_new,"T",var,"MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  //h.push_back(single_plot(filename_ttZ_new,"T",var,"MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
  h.push_back(single_plot(filename_ttZ_new,"T",var,"PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)",10,0,1));
 

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  //leg_entry.push_back("ttH old");
  leg_entry.push_back("ttZ old");
  //leg_entry.push_back("ttH full perm");
  leg_entry.push_back("ttZ full perm");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle("a.u.");
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Simulation Preliminary, #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_fullperm_ttZ_nomiss_25102016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}










void plot_LR_full_bkg_nomiss_ttH_122016(){

  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)";
  TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)";
  //TString weight = "(category==11 && isTrig && integration_type==0)";


  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T",var,weight,10,0,1));


  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("#points nominal / 10");
  leg_entry.push_back("#points nominal / 4");
  leg_entry.push_back("#points nominal / 2");
  leg_entry.push_back("#points nominal");
  leg_entry.push_back("#points nominal * 2");
  leg_entry.push_back("#points nominal / 100");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_nomiss_ttH_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}










void plot_LR_full_bkg_missing_ttH_122016(){

  TString var = "Integral_ttH/(Integral_ttH+1e-14*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)";
  TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  //TString weight = "(category==11 && isTrig && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root","T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("#points nominal / 10");
  leg_entry.push_back("#points nominal / 4");
  leg_entry.push_back("#points nominal / 2");
  leg_entry.push_back("#points nominal");
  leg_entry.push_back("#points nominal * 2");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_missing_ttH_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_LR_full_bkg_nomiss_ttZ_122016(){

  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)";
  TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)";
  //TString weight = "(category==11 && isTrig && integration_type==0)";


  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.1_161205.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.25_161205.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.5_161203.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x2_161203.root","T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("#points nominal / 10");
  leg_entry.push_back("#points nominal / 4");
  leg_entry.push_back("#points nominal / 2");
  leg_entry.push_back("#points nominal");
  leg_entry.push_back("#points nominal * 2");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}Z");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_nomiss_ttZ_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_LR_full_bkg_missing_ttZ_122016(){

  TString var = "Integral_ttH/(Integral_ttH+1e-14*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)";
  TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  //TString weight = "(category==11 && isTrig && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.1_161205.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.25_161205.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.5_161203.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117.root","T",var,weight,10,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x2_161203.root","T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("#points nominal / 10");
  leg_entry.push_back("#points nominal / 4");
  leg_entry.push_back("#points nominal / 2");
  leg_entry.push_back("#points nominal");
  leg_entry.push_back("#points nominal * 2");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+2);
    if(i>2)
      h[i]->SetLineColor(i+3);
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}Z");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_missing_ttZ_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}














void plot_LR_full_bkg_nomiss_ttH_MEMsyst_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root";


  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1e-1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1e-1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";


  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)";
  TString weight = "(category==11 && isTrig && integration_type==0)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal");
  leg_entry.push_back("MEM syst up, #points nominal");
  leg_entry.push_back("MEM syst down, #points nominal");
  leg_entry.push_back("Nominal, #points nominal*2");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_nomiss_ttH_MEMsyt_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_LR_full_bkg_missing_ttH_MEMsyst_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";


  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal");
  leg_entry.push_back("MEM syst up, #points nominal");
  leg_entry.push_back("MEM syst down, #points nominal");
  leg_entry.push_back("Nominal, #points nominal*2");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_missing_ttH_MEMsyt_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_LR_full_bkg_nomiss_ttZ_MEMsyst_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x2_161203.root";


  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1e-1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1e-1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";


  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)";
  TString weight = "(category==11 && isTrig && integration_type==0)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal");
  leg_entry.push_back("MEM syst up, #points nominal");
  leg_entry.push_back("MEM syst down, #points nominal");
  leg_entry.push_back("Nominal, #points nominal*2");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}Z");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_nomiss_ttZ_MEMsyt_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_LR_full_bkg_missing_ttZ_MEMsyst_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x2_161203.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";


  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal");
  leg_entry.push_back("MEM syst up, #points nominal");
  leg_entry.push_back("MEM syst down, #points nominal");
  leg_entry.push_back("Nominal, #points nominal*2");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}Z");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_missing_ttZ_MEMsyt_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_LR_full_bkg_nomiss_ttH_MEMsyst_nbr_points_x025_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204_MEMsyst.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1e-1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1e-1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";



  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==0)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal");
  leg_entry.push_back("MEM syst up");
  leg_entry.push_back("MEM syst down");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_nomiss_ttH_MEMsyt_nbr_points_x025_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}













void plot_LR_full_bkg_missing_ttH_MEMsyst_nbr_points_x025_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204_MEMsyst.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";


  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal");
  leg_entry.push_back("MEM syst up");
  leg_entry.push_back("MEM syst down");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_missing_ttH_MEMsyt_nbr_points_x025_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}











void plot_LR_full_bkg_nomiss_ttH_MEMsyst2_nbr_points_x025_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1e-1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1e-1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";



  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==0)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal/4");
  leg_entry.push_back("MEM syst up, #points nominal/4");
  leg_entry.push_back("MEM syst down, #points nominal/4");
  leg_entry.push_back("Nominal, #points nominal");



  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_nomiss_ttH_MEMsyt2_nbr_points_x025_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}













void plot_LR_full_bkg_missing_ttH_MEMsyst2_nbr_points_x025_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";


  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));
  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal/4");
  leg_entry.push_back("MEM syst up, #points nominal/4");
  leg_entry.push_back("MEM syst down, #points nominal/4");
  leg_entry.push_back("Nominal, #points nominal");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_missing_ttH_MEMsyt2_nbr_points_x025_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}












void plot_LR_full_bkg_nomiss_ttZ_MEMsyst2_nbr_points_x025_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.25_161205_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1e-1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1e-1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";



  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==0)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal/4");
  leg_entry.push_back("MEM syst up, #points nominal/4");
  leg_entry.push_back("MEM syst down, #points nominal/4");
  leg_entry.push_back("Nominal, #points nominal");



  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}Z");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_nomiss_ttZ_MEMsyt2_nbr_points_x025_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}













void plot_LR_full_bkg_missing_ttZ_MEMsyst2_nbr_points_x025_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.25_161205_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";


  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));
  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal/4");
  leg_entry.push_back("MEM syst up, #points nominal/4");
  leg_entry.push_back("MEM syst down, #points nominal/4");
  leg_entry.push_back("Nominal, #points nominal");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}Z");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_missing_ttZ_MEMsyt2_nbr_points_x025_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}













void plot_LR_full_bkg_nomiss_ttH_MEMsyst_nbr_points_x001_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.01_161205_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1e-1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1e-1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";



  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==0)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal/100");
  leg_entry.push_back("MEM syst up, #points nominal/100");
  leg_entry.push_back("MEM syst down, #points nominal/100");
  leg_entry.push_back("Nominal, #points nominal");



  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_nomiss_ttH_MEMsyt_nbr_points_x001_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}













void plot_LR_full_bkg_missing_ttH_MEMsyst_nbr_points_x001_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.01_161205_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";


  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));
  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal/100");
  leg_entry.push_back("MEM syst up, #points nominal/100");
  leg_entry.push_back("MEM syst down, #points nominal/100");
  leg_entry.push_back("Nominal, #points nominal");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_missing_ttH_MEMsyt_nbr_points_x001_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}












void plot_LR_full_bkg_nomiss_ttZ_MEMsyst_nbr_points_x001_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.01_161205_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1e-1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1e-1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";



  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==0)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal/100");
  leg_entry.push_back("MEM syst up, #points nominal/100");
  leg_entry.push_back("MEM syst down, #points nominal/100");
  leg_entry.push_back("Nominal, #points nominal");



  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}Z");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_nomiss_ttZ_MEMsyt_nbr_points_x001_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}













void plot_LR_full_bkg_missing_ttZ_MEMsyst_nbr_points_x001_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.01_161205_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";


  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));
  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal/100");
  leg_entry.push_back("MEM syst up, #points nominal/100");
  leg_entry.push_back("MEM syst down, #points nominal/100");
  leg_entry.push_back("Nominal, #points nominal");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}Z");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_missing_ttZ_MEMsyt_nbr_points_x001_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_LR_full_bkg_nomiss_ttH_MEMsyst_nbr_points_x01_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1e-1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1e-1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";



  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==0)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal/10");
  leg_entry.push_back("MEM syst up, #points nominal/10");
  leg_entry.push_back("MEM syst down, #points nominal/10");
  leg_entry.push_back("Nominal, #points nominal");



  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_nomiss_ttH_MEMsyt_nbr_points_x01_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}













void plot_LR_full_bkg_missing_ttH_MEMsyst_nbr_points_x01_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";


  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));
  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal/10");
  leg_entry.push_back("MEM syst up, #points nominal/10");
  leg_entry.push_back("MEM syst down, #points nominal/10");
  leg_entry.push_back("Nominal, #points nominal");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}H");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_missing_ttH_MEMsyt_nbr_points_x01_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}













void plot_LR_full_bkg_nomiss_ttZ_MEMsyst_nbr_points_x01_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.1_161205_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1e-1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1e-1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-17*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1e-1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";



  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==0)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal/10");
  leg_entry.push_back("MEM syst up, #points nominal/10");
  leg_entry.push_back("MEM syst down, #points nominal/10");
  leg_entry.push_back("Nominal, #points nominal");



  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}Z");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_nomiss_ttZ_MEMsyt_nbr_points_x01_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}













void plot_LR_full_bkg_missing_ttZ_MEMsyst_nbr_points_x01_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.1_161205_MEMsyst.root";
  TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117.root";

  TString var = "Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+1*Integral_ttZ_Zll)";
  TString var_up = "(Integral_ttH+StdErr_ttH)/((Integral_ttH+StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep-StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau-StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ-StdErr_ttZ)+1*(Integral_ttZ_Zll-StdErr_ttZ_Zll))";
  TString var_down = "(Integral_ttH-StdErr_ttH)/((Integral_ttH-StdErr_ttH)+1e-15*(Integral_ttbar_DL_fakelep_tlep+StdErr_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau+StdErr_ttbar_DL_fakelep_ttau)+5e-2*(Integral_ttZ+StdErr_ttZ)+1*(Integral_ttZ_Zll+StdErr_ttZ_Zll))";


  //TString weight = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)";
  TString weight = "(category==11 && isTrig && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot(file,"T",var,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_up,weight,10,0,1));
  h.push_back(single_plot(file,"T",var_down,weight,10,0,1));
  h.push_back(single_plot(file2,"T",var,weight,10,0,1));
  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("Nominal, #points nominal/10");
  leg_entry.push_back("MEM syst up, #points nominal/10");
  leg_entry.push_back("MEM syst down, #points nominal/10");
  leg_entry.push_back("Nominal, #points nominal");


  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}Z");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_missing_ttZ_MEMsyt_nbr_points_x01_122016";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}















void plot_LR_full_bkg_nomiss_GPU(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig.root";
  TString file_ttH_GPU="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttH/test_ttH.root";
  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM.root";
  TString file_ttZ_GPU="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttV/test_ttZ.root";


  TString var = "Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)";

  TString weight = "(category==11 && integration_type==0)";


  vector<TH1F*> h;
  h.push_back(single_plot(file_ttH,"T",var,weight,50,0,1));
  h.push_back(single_plot(file_ttZ,"T",var,weight,50,0,1));
  h.push_back(single_plot(file_ttH_GPU,"T",var,weight,50,0,1));
  h.push_back(single_plot(file_ttZ_GPU,"T",var,weight,50,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{No missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH MPI");
  leg_entry.push_back("ttZ MPI");
  leg_entry.push_back("ttH GPU");
  leg_entry.push_back("ttZ GPU");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Number of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_nomiss_GPU";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_LR_full_bkg_missing_GPU(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig.root";
  TString file_ttH_GPU="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttH/test_ttH.root";
  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM.root";
  TString file_ttZ_GPU="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttV/test_ttZ.root";


  TString var = "Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)";

  TString weight = "(category==11 && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot(file_ttH,"T",var,weight,50,0,1));
  h.push_back(single_plot(file_ttZ,"T",var,weight,50,0,1));
  h.push_back(single_plot(file_ttH_GPU,"T",var,weight,50,0,1));
  h.push_back(single_plot(file_ttZ_GPU,"T",var,weight,50,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH MPI");
  leg_entry.push_back("ttZ MPI");
  leg_entry.push_back("ttH GPU");
  leg_entry.push_back("ttZ GPU");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("MEM LR");
  h[0]->GetYaxis()->SetTitle(Form("Number of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_full_bkg_missing_GPU";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}











void plot_LR_ttbar_missing_GPU(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig.root";
  TString file_ttH_GPU="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttH/test_ttH.root";
  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM.root";
  TString file_ttZ_GPU="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttV/test_ttZ.root";


  TString var = "Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))";

  TString weight = "(category==11 && integration_type==1)";


  vector<TH1F*> h;
  h.push_back(single_plot(file_ttH,"T",var,weight,50,0,1));
  h.push_back(single_plot(file_ttZ,"T",var,weight,50,0,1));
  h.push_back(single_plot(file_ttH_GPU,"T",var,weight,50,0,1));
  h.push_back(single_plot(file_ttZ_GPU,"T",var,weight,50,0,1));

  
  TLegend* leg=new TLegend(0.3,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#bf{Missing jet}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH MPI");
  leg_entry.push_back("ttZ MPI");
  leg_entry.push_back("ttH GPU");
  leg_entry.push_back("ttZ GPU");


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  //h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("MEM LR (t#bar{t})");
  h[0]->GetYaxis()->SetTitle(Form("Number of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  


  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="LR_ttbar_missing_GPU";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




