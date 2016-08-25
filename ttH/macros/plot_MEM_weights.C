#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include "Helpers.C"
#include <vector>
#include <TLatex.h>
#include <THStack.h>
#include <TGraphErrors.h>

using namespace std;




void plot_ttH_weight(){

  TString file_ttH_tautau="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/ttH/ttH_Htautau_split_2lSS_MEM_160622.root";


  TString file_ttjets_SLfromT="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root";
  TString file_ttjets_SLfromTbar="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root";

  TH1F* h_ttH_tautau=single_plot(file_ttH_tautau,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","MC_weight*(category==11)",32,-100,60);


  TH1F* h_ttjets_SLfromT=single_plot(file_ttjets_SLfromT,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","MC_weight*event_weight_ttH*(category==41)",32,-100,60);
  TH1F* h_ttjets_SLfromTbar=single_plot(file_ttjets_SLfromTbar,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","MC_weight*event_weight_ttH*(category==41)",32,-100,60);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","MC_weight*event_weight_ttH*(category==41)",32,-100,60);

  h_ttH_tautau->Scale(1/h_ttH_tautau->Integral());

  float XS_ttjets_SLfromT_eff = 182.*1.675208e-07;
  float XS_ttjets_SLfromTbar_eff = 182.*1.672702e-07;
  float XS_ttjets_DL_eff = 87.3*1.312176e-06;
  
  float XS_ttjets_eff = XS_ttjets_SLfromT_eff + XS_ttjets_SLfromTbar_eff + XS_ttjets_DL_eff;

  h_ttjets_SLfromT->Scale((XS_ttjets_SLfromT_eff/XS_ttjets_eff)*1./h_ttjets_SLfromT->Integral());
  h_ttjets_SLfromTbar->Scale((XS_ttjets_SLfromTbar_eff/XS_ttjets_eff)*1./h_ttjets_SLfromTbar->Integral());
  h_ttjets_DL->Scale((XS_ttjets_DL_eff/XS_ttjets_eff)*1./h_ttjets_DL->Integral());


  h_ttH_tautau->SetLineWidth(2);
  h_ttH_tautau->SetLineColor(kBlue);

  h_ttjets_SLfromT->SetFillColor(kRed-9);
  h_ttjets_SLfromT->SetLineColor(kRed-9);
  h_ttjets_SLfromT->SetLineWidth(0);

  h_ttjets_SLfromTbar->SetFillColor(kRed-9);
  h_ttjets_SLfromTbar->SetLineColor(kRed-9);
  h_ttjets_SLfromTbar->SetLineWidth(0);

  h_ttjets_DL->SetFillColor(kRed+1);
  h_ttjets_DL->SetLineColor(kRed+1);
  h_ttjets_DL->SetLineWidth(0);


  THStack* h_ttjets = new THStack("h_ttjets","");
  h_ttjets->Add(h_ttjets_DL,"hist");
  h_ttjets->Add(h_ttjets_SLfromT,"hist");
  h_ttjets->Add(h_ttjets_SLfromTbar,"hist");


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH_tautau,"ttH, H->#tau#tau");
  leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");
  leg->AddEntry(h_ttjets_SLfromT,"t#bar{t} l+jets");
  leg->SetHeader("2lSS + 1#tau_{h} category");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttjets->SetMaximum(1.5*max(h_ttjets->GetMaximum(),h_ttH_tautau->GetMaximum()));
  h_ttjets->Draw("");
  h_ttH_tautau->Draw("same");
  leg->Draw("same");

  h_ttjets->GetXaxis()->SetTitle("log(w(ttH))");
  h_ttjets->GetYaxis()->SetTitle("a. u.");
  h_ttjets->GetYaxis()->SetTitleOffset(1.65);
  h_ttjets->SetTitle("");

  TLatex *texl = new TLatex(-99,1.5*1.07*h_ttH_tautau->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="ttH_weight";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_ttbar_SL_weight(){

  TString file_ttH_tautau="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/ttH/ttH_Htautau_split_2lSS_MEM_160622.root";


  TString file_ttjets_SLfromT="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root";
  TString file_ttjets_SLfromTbar="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root";

  TH1F* h_ttH_tautau=single_plot(file_ttH_tautau,"T","log(Integral_ttbar_SL)*(Integral_ttbar_SL>0) -99*(Integral_ttbar_SL==0)","MC_weight*(category==11)",32,-100,60);


  TH1F* h_ttjets_SLfromT=single_plot(file_ttjets_SLfromT,"T","log(Integral_ttbar_SL)*(Integral_ttbar_SL>0) -99*(Integral_ttbar_SL==0)","MC_weight*event_weight_ttH*(category==41)",32,-100,60);
  TH1F* h_ttjets_SLfromTbar=single_plot(file_ttjets_SLfromTbar,"T","log(Integral_ttbar_SL)*(Integral_ttbar_SL>0) -99*(Integral_ttbar_SL==0)","MC_weight*event_weight_ttH*(category==41)",32,-100,60);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T","log(Integral_ttbar_SL)*(Integral_ttbar_SL>0) -99*(Integral_ttbar_SL==0)","MC_weight*event_weight_ttH*(category==41)",32,-100,60);

  h_ttH_tautau->Scale(1/h_ttH_tautau->Integral());

  float XS_ttjets_SLfromT_eff = 182.*1.675208e-07;
  float XS_ttjets_SLfromTbar_eff = 182.*1.672702e-07;
  float XS_ttjets_DL_eff = 87.3*1.312176e-06;
  
  float XS_ttjets_eff = XS_ttjets_SLfromT_eff + XS_ttjets_SLfromTbar_eff + XS_ttjets_DL_eff;

  h_ttjets_SLfromT->Scale((XS_ttjets_SLfromT_eff/XS_ttjets_eff)*1./h_ttjets_SLfromT->Integral());
  h_ttjets_SLfromTbar->Scale((XS_ttjets_SLfromTbar_eff/XS_ttjets_eff)*1./h_ttjets_SLfromTbar->Integral());
  h_ttjets_DL->Scale((XS_ttjets_DL_eff/XS_ttjets_eff)*1./h_ttjets_DL->Integral());


  h_ttH_tautau->SetLineWidth(2);
  h_ttH_tautau->SetLineColor(kBlue);

  h_ttjets_SLfromT->SetFillColor(kRed-9);
  h_ttjets_SLfromT->SetLineColor(kRed-9);
  h_ttjets_SLfromT->SetLineWidth(0);

  h_ttjets_SLfromTbar->SetFillColor(kRed-9);
  h_ttjets_SLfromTbar->SetLineColor(kRed-9);
  h_ttjets_SLfromTbar->SetLineWidth(0);

  h_ttjets_DL->SetFillColor(kRed+1);
  h_ttjets_DL->SetLineColor(kRed+1);
  h_ttjets_DL->SetLineWidth(0);


  THStack* h_ttjets = new THStack("h_ttjets","");
  h_ttjets->Add(h_ttjets_DL,"hist");
  h_ttjets->Add(h_ttjets_SLfromT,"hist");
  h_ttjets->Add(h_ttjets_SLfromTbar,"hist");


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH_tautau,"ttH, H->#tau#tau");
  leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");
  leg->AddEntry(h_ttjets_SLfromT,"t#bar{t} l+jets");
  leg->SetHeader("2lSS + 1#tau_{h} category");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttjets->SetMaximum(1.5*max(h_ttjets->GetMaximum(),h_ttH_tautau->GetMaximum()));
  h_ttjets->Draw("");
  h_ttH_tautau->Draw("same");
  leg->Draw("same");

  h_ttjets->GetXaxis()->SetTitle("log(w(t#bar{t} l+jets))");
  h_ttjets->GetYaxis()->SetTitle("a. u.");
  h_ttjets->GetYaxis()->SetTitleOffset(1.65);
  h_ttjets->SetTitle("");

  TLatex *texl = new TLatex(-99,1.5*1.07*h_ttjets->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="ttbar_SL_weight";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_ttbar_DL_weight(){

  TString file_ttH_tautau="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/ttH/ttH_Htautau_split_2lSS_MEM_160622.root";


  TString file_ttjets_SLfromT="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root";
  TString file_ttjets_SLfromTbar="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root";

  TH1F* h_ttH_tautau=single_plot(file_ttH_tautau,"T","log(Integral_ttbar_DL)*(Integral_ttbar_DL>0) -99*(Integral_ttbar_DL==0)","MC_weight*(category==11)",32,-100,60);


  TH1F* h_ttjets_SLfromT=single_plot(file_ttjets_SLfromT,"T","log(Integral_ttbar_DL)*(Integral_ttbar_DL>0) -99*(Integral_ttbar_DL==0)","MC_weight*event_weight_ttH*(category==41)",32,-100,60);
  TH1F* h_ttjets_SLfromTbar=single_plot(file_ttjets_SLfromTbar,"T","log(Integral_ttbar_DL)*(Integral_ttbar_DL>0) -99*(Integral_ttbar_DL==0)","MC_weight*event_weight_ttH*(category==41)",32,-100,60);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T","log(Integral_ttbar_DL)*(Integral_ttbar_DL>0) -99*(Integral_ttbar_DL==0)","MC_weight*event_weight_ttH*(category==41)",32,-100,60);

  h_ttH_tautau->Scale(1/h_ttH_tautau->Integral());

  float XS_ttjets_SLfromT_eff = 182.*1.675208e-07;
  float XS_ttjets_SLfromTbar_eff = 182.*1.672702e-07;
  float XS_ttjets_DL_eff = 87.3*1.312176e-06;
  
  float XS_ttjets_eff = XS_ttjets_SLfromT_eff + XS_ttjets_SLfromTbar_eff + XS_ttjets_DL_eff;

  h_ttjets_SLfromT->Scale((XS_ttjets_SLfromT_eff/XS_ttjets_eff)*1./h_ttjets_SLfromT->Integral());
  h_ttjets_SLfromTbar->Scale((XS_ttjets_SLfromTbar_eff/XS_ttjets_eff)*1./h_ttjets_SLfromTbar->Integral());
  h_ttjets_DL->Scale((XS_ttjets_DL_eff/XS_ttjets_eff)*1./h_ttjets_DL->Integral());


  h_ttH_tautau->SetLineWidth(2);
  h_ttH_tautau->SetLineColor(kBlue);

  h_ttjets_SLfromT->SetFillColor(kRed-9);
  h_ttjets_SLfromT->SetLineColor(kRed-9);
  h_ttjets_SLfromT->SetLineWidth(0);

  h_ttjets_SLfromTbar->SetFillColor(kRed-9);
  h_ttjets_SLfromTbar->SetLineColor(kRed-9);
  h_ttjets_SLfromTbar->SetLineWidth(0);

  h_ttjets_DL->SetFillColor(kRed+1);
  h_ttjets_DL->SetLineColor(kRed+1);
  h_ttjets_DL->SetLineWidth(0);


  THStack* h_ttjets = new THStack("h_ttjets","");
  h_ttjets->Add(h_ttjets_DL,"hist");
  h_ttjets->Add(h_ttjets_SLfromT,"hist");
  h_ttjets->Add(h_ttjets_SLfromTbar,"hist");


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH_tautau,"ttH, H->#tau#tau");
  leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");
  leg->AddEntry(h_ttjets_SLfromT,"t#bar{t} l+jets");
  leg->SetHeader("2lSS + 1#tau_{h} category");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttjets->SetMaximum(1.5*max(h_ttjets->GetMaximum(),h_ttH_tautau->GetMaximum()));
  h_ttjets->Draw("");
  h_ttH_tautau->Draw("same");
  leg->Draw("same");

  h_ttjets->GetXaxis()->SetTitle("log(w(t#bar{t} l+#tau))");
  h_ttjets->GetYaxis()->SetTitle("a. u.");
  h_ttjets->GetYaxis()->SetTitleOffset(1.65);
  h_ttjets->SetTitle("");

  TLatex *texl = new TLatex(-99,1.5*1.07*h_ttjets->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="ttbar_SL_weight";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}









void plot_ttH_weight2(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root";
  TString file_ttbar_DL="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160706.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160706.root";


  vector<TH1F*> h;
  h.push_back(single_plot(file_ttH,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","(category==11 && genH_decayMode[1]<=1)",32,-100,60));
  h.push_back(single_plot(file_ttbar_DL,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","event_weight_ttH*(category==41)",32,-100,60));
  h.push_back(single_plot(file_ttW,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","(category==11)",32,-100,60));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH, H->#tau#tau->l+#tau_{h}");
  leg_entry.push_back("t#bar{t} DL");
  leg_entry.push_back("ttW");

  TLegend* leg=new TLegend(0.25,0.7,0.55,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->SetHeader("2lSS + 1#tau_{h} category");


  for(unsigned int i=0; i<h.size(); i++){
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetStats(0);
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->SetTitle("");
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h=sort_histo(h);



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("log(w(ttH))");
  h[0]->GetYaxis()->SetTitle("a. u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw();
  for(unsigned int i=1;i<h.size();i++)
    h[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="ttH_weight2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}








void plot_ttbar_DL_weight2(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root";
  //TString file_ttbar_DL="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160706.root";
  //TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160706.root";
  TString file_ttbar_DL="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160708.root";


  vector<TH1F*> h;
  h.push_back(single_plot(file_ttH,"T","log(Integral_ttbar_DL)*(Integral_ttbar_DL>0) -99*(Integral_ttbar_DL==0)","(category==11 && genH_decayMode[1]<=1)",32,-100,60));
  h.push_back(single_plot(file_ttbar_DL,"T","log(Integral_ttbar_DL)*(Integral_ttbar_DL>0) -99*(Integral_ttbar_DL==0)","event_weight_ttH*(category==41)",32,-100,60));
  h.push_back(single_plot(file_ttW,"T","log(Integral_ttbar_DL)*(Integral_ttbar_DL>0) -99*(Integral_ttbar_DL==0)","(category==11)",32,-100,60));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH, H->#tau#tau->l+#tau_{h}");
  leg_entry.push_back("t#bar{t} DL");
  leg_entry.push_back("ttW");

  TLegend* leg=new TLegend(0.25,0.7,0.55,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->SetHeader("2lSS + 1#tau_{h} category");


  for(unsigned int i=0; i<h.size(); i++){
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetStats(0);
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->SetTitle("");
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h=sort_histo(h);



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("log(w(t#bar{t} l+#tau))");
  h[0]->GetYaxis()->SetTitle("a. u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw();
  for(unsigned int i=1;i<h.size();i++)
    h[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="ttbar_DL_weight2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_ttW_weight(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root";
  TString file_ttbar_DL="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160706.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160706.root";


  vector<TH1F*> h;
  h.push_back(single_plot(file_ttH,"T","log(Integral_ttW)*(Integral_ttW>0) -99*(Integral_ttW==0)","(category==11 && genH_decayMode[1]<=1)",32,-100,60));
  h.push_back(single_plot(file_ttbar_DL,"T","log(Integral_ttW)*(Integral_ttW>0) -99*(Integral_ttW==0)","event_weight_ttH*(category==41)",32,-100,60));
  h.push_back(single_plot(file_ttW,"T","log(Integral_ttW)*(Integral_ttW>0) -99*(Integral_ttW==0)","(category==11)",32,-100,60));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH, H->#tau#tau->l+#tau_{h}");
  leg_entry.push_back("t#bar{t} DL");
  leg_entry.push_back("ttW");

  TLegend* leg=new TLegend(0.25,0.7,0.55,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->SetHeader("2lSS + 1#tau_{h} category");


  for(unsigned int i=0; i<h.size(); i++){
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetStats(0);
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->SetTitle("");
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h=sort_histo(h);



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("log(w(ttW))");
  h[0]->GetYaxis()->SetTitle("a. u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw();
  for(unsigned int i=1;i<h.size();i++)
    h[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="ttW_weight";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}






void plot_MVA_2lSS_ttbar(){

  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");

  TString file_ttbar_DL="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160706.root";
  //TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160706.root";
  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");



  vector<TH1F*> h;
  h.push_back(single_plot(files_ttH,"T","MVA_2lSS_ttbar","MC_weight*(category==11 && genH_decayMode[1]<=1 && recolep_sel_pt[0]>25)",10,-1,1));
  h.push_back(single_plot(file_ttbar_DL,"T","MVA_2lSS_ttbar","MC_weight*event_weight_ttH*(category==41 && recolep_sel_pt[0]>25)",10,-1,1));
  //h.push_back(single_plot(file_ttW,"T","MVA_2lSS_ttbar","(category==11)",20,-1,1));
 h.push_back(single_plot(files_data_fakes,"T","MVA_2lSS_ttbar","event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)",10,-1,1));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH, H->#tau#tau->l+#tau_{h}");
  leg_entry.push_back("t#bar{t} DL MC");
  leg_entry.push_back("Fakes data-driven");

  TLegend* leg=new TLegend(0.25,0.7,0.55,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->SetHeader("2lSS + 1#tau_{h} category");


  for(unsigned int i=0; i<h.size(); i++){
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetStats(0);
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->SetTitle("");
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h=sort_histo(h);



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(2.*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("MVA ttH vs t#bar{t}");
  h[0]->GetYaxis()->SetTitle("a. u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw();
  for(unsigned int i=1;i<h.size();i++)
    h[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(-0.99,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_2lSS_ttbar_weight2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_MVA_2lSS_ttV(){

  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160706.root";
  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttZ_split_2lSS_MEM_160720.root";


  vector<TH1F*> h;
  h.push_back(single_plot(files_ttH,"T","MVA_2lSS_ttV","MC_weight*(category==11 && genH_decayMode[1]<=1 && recolep_sel_pt[0]>25)",10,-1,1));
  h.push_back(single_plot(file_ttW,"T","MVA_2lSS_ttV","MC_weight*(category==11 && recolep_sel_pt[0]>25)",10,-1,1));
  h.push_back(single_plot(file_ttZ,"T","MVA_2lSS_ttV","MC_weight*(category==11 && recolep_sel_pt[0]>25)",10,-1,1));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH, H->#tau#tau->l+#tau_{h}");
  //leg_entry.push_back("t#bar{t} DL");
  leg_entry.push_back("ttW");
  leg_entry.push_back("ttZ");
  

  TLegend* leg=new TLegend(0.25,0.7,0.55,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->SetHeader("2lSS + 1#tau_{h} category");


  for(unsigned int i=0; i<h.size(); i++){
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetStats(0);
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->SetTitle("");
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h=sort_histo(h);



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.5*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("MVA ttH vs ttV");
  h[0]->GetYaxis()->SetTitle("a. u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw();
  for(unsigned int i=1;i<h.size();i++)
    h[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(-0.99,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_2lSS_ttV_weight";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}









void plot_ttH_weight_ttbar_nomiss(){


  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");

  TString file_ttbar_DL="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root";

  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");



  vector<TH1F*> h;
  h.push_back(single_plot(files_ttH,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","MC_weight*(category==11 && genH_decayMode[1]<=1 && recolep_sel_pt[0]>25 && integration_type==0)",40,-100,100));
  h.push_back(single_plot(file_ttbar_DL,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","MC_weight*event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && integration_type==0)",40,-100,100));
 h.push_back(single_plot(files_data_fakes,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig && integration_type==0)",40,-100,100));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH, H->#tau#tau->l+#tau_{h}");
  leg_entry.push_back("t#bar{t} DL MC");
  leg_entry.push_back("Fakes data-driven");

  TLegend* leg=new TLegend(0.25,0.6,0.55,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->SetHeader("#splitline{2lSS + 1#tau_{h} category}{No missing jet}");


  for(unsigned int i=0; i<h.size(); i++){
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetStats(0);
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->SetTitle("");
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h=sort_histo(h);



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(2.*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("log(w_{ttH})");
  h[0]->GetYaxis()->SetTitle("a. u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw();
  for(unsigned int i=1;i<h.size();i++)
    h[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="ttH_weight_ttbar_nomiss";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_ttH_weight_ttbar_miss(){

  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");

  TString file_ttbar_DL="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root";


  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");



  vector<TH1F*> h;
  h.push_back(single_plot(files_ttH,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","MC_weight*(category==11 && genH_decayMode[1]<=1 && recolep_sel_pt[0]>25 && integration_type==1)",40,-100,100));
  h.push_back(single_plot(file_ttbar_DL,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","MC_weight*event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && integration_type==1)",40,-100,100));
  h.push_back(single_plot(files_data_fakes,"T","log(Integral_ttH)*(Integral_ttH>0) -99*(Integral_ttH==0)","event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig && integration_type==1)",40,-100,100));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH, H->#tau#tau->l+#tau_{h}");
  leg_entry.push_back("t#bar{t} DL MC");
  leg_entry.push_back("Fakes data-driven");

  TLegend* leg=new TLegend(0.25,0.6,0.55,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->SetHeader("#splitline{2lSS + 1#tau_{h} category}{Missing jet}");


  for(unsigned int i=0; i<h.size(); i++){
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetStats(0);
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->SetTitle("");
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h=sort_histo(h);



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(2.*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("log(w_{ttH})");
  h[0]->GetYaxis()->SetTitle("a. u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw();
  for(unsigned int i=1;i<h.size();i++)
    h[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="ttH_weight_ttbar_miss";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}








void plot_ttbar_weight_ttbar_nomiss(){

  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");

  TString file_ttbar_DL="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root";

  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");



  vector<TH1F*> h;
  h.push_back(single_plot(files_ttH,"T","log(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) -99*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0)","MC_weight*(category==11 && genH_decayMode[1]<=1 && recolep_sel_pt[0]>25 && integration_type==0)",40,-100,100));
  h.push_back(single_plot(file_ttbar_DL,"T","log(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) -99*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0)","MC_weight*event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && integration_type==0)",40,-100,100));
  //h.push_back(single_plot(file_ttW,"T","MVA_2lSS_ttbar","(category==11)",20,-1,1));
 h.push_back(single_plot(files_data_fakes,"T","log(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) -99*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0)","event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig && integration_type==0)",40,-100,100));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH, H->#tau#tau->l+#tau_{h}");
  leg_entry.push_back("t#bar{t} DL MC");
  leg_entry.push_back("Fakes data-driven");

  TLegend* leg=new TLegend(0.25,0.6,0.55,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->SetHeader("#splitline{2lSS + 1#tau_{h} category}{No missing jet}");


  for(unsigned int i=0; i<h.size(); i++){
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetStats(0);
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->SetTitle("");
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h=sort_histo(h);



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(2.*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("log(w_{t#bar{t}})");
  h[0]->GetYaxis()->SetTitle("a. u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw();
  for(unsigned int i=1;i<h.size();i++)
    h[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="ttbar_weight_ttbar_nomiss";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_ttbar_weight_ttbar_miss(){

  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");

  TString file_ttbar_DL="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root";

  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");



  vector<TH1F*> h;
  h.push_back(single_plot(files_ttH,"T","log(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) -99*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0)","MC_weight*(category==11 && genH_decayMode[1]<=1 && recolep_sel_pt[0]>25 && integration_type==1)",40,-100,100));
  h.push_back(single_plot(file_ttbar_DL,"T","log(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) -99*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0)","MC_weight*event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && integration_type==1)",40,-100,100));
  //h.push_back(single_plot(file_ttW,"T","MVA_2lSS_ttbar","(category==11)",20,-1,1));
 h.push_back(single_plot(files_data_fakes,"T","log(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) -99*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0)","event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig && integration_type==1)",40,-100,100));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH, H->#tau#tau->l+#tau_{h}");
  leg_entry.push_back("t#bar{t} DL MC");
  leg_entry.push_back("Fakes data-driven");

  TLegend* leg=new TLegend(0.25,0.6,0.55,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->SetHeader("#splitline{2lSS + 1#tau_{h} category}{Missing jet}");


  for(unsigned int i=0; i<h.size(); i++){
    h[i]->Scale(1/h[i]->Integral());
    h[i]->SetStats(0);
    h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->SetTitle("");
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h=sort_histo(h);



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(2.*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("log(w_{t#bar{t}})");
  h[0]->GetYaxis()->SetTitle("a. u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw();
  for(unsigned int i=1;i<h.size();i++)
    h[i]->Draw("same");
  leg->Draw("same");


  TLatex *texl = new TLatex(-99,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="ttbar_weight_ttbar_miss";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}


