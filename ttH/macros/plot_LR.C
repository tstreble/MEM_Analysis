#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <THStack.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>
#include <Helpers.C>
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

