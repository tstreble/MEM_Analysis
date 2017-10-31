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


void plot_1l2tau_ttbar_MVA(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_PU_newtrig_BDT_1l2tau.root";
  //TString file_ttjets_SLfromT="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromT_split_PU_newtrig_BDT_1l2tau.root";
  TString file_ttjets_SLfromTbar="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split_PU_newtrig_BDT_1l2tau.root";
  //TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_ext_split_PU_newtrig_BDT_1l2tau.root";

  TString cut = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==20 && isTrig_1l_v2)";

  TH1F* h_ttH=single_plot(file_ttH,"HTauTauTree_1l_2tau","MVA_1l2tau_ttbar",cut,50,-1,1);
  //TH1F* h_ttjets_SLfromT=single_plot(file_ttjets_SLfromT,"HTauTauTree_1l_2tau","MVA_1l2tau_ttbar",cut,50,-1,1);
  TH1F* h_ttjets_SLfromTbar=single_plot(file_ttjets_SLfromTbar,"HTauTauTree_1l_2tau","MVA_1l2tau_ttbar",cut,50,-1,1);
  //TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"HTauTauTree_1l_2tau","MVA_1l2tau_ttbar",cut,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  /*float XS_ttjets_SLfromT = 182. / (2*182. + 87.3);
  float XS_ttjets_SLfromTbar = XS_ttjets_SLfromT;
  float XS_ttjets_DL = 87.3 / (2*182. + 87.3);
  h_ttjets_SLfromT->Scale(XS_ttjets_SLfromT/h_ttjets_SLfromT->Integral());
  h_ttjets_SLfromTbar->Scale(XS_ttjets_SLfromTbar/h_ttjets_SLfromTbar->Integral());
  h_ttjets_DL->Scale(XS_ttjets_DL/h_ttjets_DL->Integral());*/
  h_ttjets_SLfromTbar->Scale(1/h_ttjets_SLfromTbar->Integral());

  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttjets_SLfromTbar->SetLineWidth(2);
  h_ttjets_SLfromTbar->SetLineColor(kRed);

  /*h_ttjets_SLfromT->SetFillColor(kRed-9);
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
  h_ttjets->Add(h_ttjets_SLfromTbar,"hist");*/

  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  //leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");
  leg->AddEntry(h_ttjets_SLfromTbar,"t#bar{t} SL");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttjets_SLfromTbar->SetMaximum(1.2*max(h_ttjets_SLfromTbar->GetMaximum(),h_ttH->GetMaximum()));
  h_ttjets_SLfromTbar->SetStats(0);
  h_ttjets_SLfromTbar->Draw("");
  h_ttH->Draw("same");
  leg->Draw("same");

  h_ttjets_SLfromTbar->GetXaxis()->SetTitle("1l2#tau ttH vs t#bar{t} MVA");
  h_ttjets_SLfromTbar->GetYaxis()->SetTitle("a. u.");
  h_ttjets_SLfromTbar->GetYaxis()->SetTitleOffset(1.65);
  h_ttjets_SLfromTbar->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttjets_SLfromTbar->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_1l2tau_ttH_ttbar";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttbar_MVA_noMEM_ttH(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==41 && isTrig_1l_v2)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_noMEM_ttbar",cut_sig,50,-1,1);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T","MVA_2lSS1tau_noMEM_ttbar",cut_bkg,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttjets_DL->Scale(1/h_ttjets_DL->Integral());

  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttjets_DL->SetLineWidth(2);
  h_ttjets_DL->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  //leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttH->GetMaximum()));
  h_ttH->SetStats(0);
  //h_ttjets_DL->Draw("");
  h_ttH->Draw("");
  leg->Draw("same");

  h_ttH->GetXaxis()->SetTitle("2lSS1#tau ttH vs t#bar{t} MVA");
  h_ttH->GetYaxis()->SetTitle("a. u.");
  h_ttH->GetYaxis()->SetTitleOffset(1.65);
  h_ttH->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttH->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttbar_2lSS1tau_noMEM_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttbar_MVA_noMEM_ttbar_DL(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==41 && isTrig_1l_v2)";
  //TString cut_bkg = "category==41 && isTrig_1l_v2";  

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_noMEM_ttbar",cut_sig,50,-1,1);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T","MVA_2lSS1tau_noMEM_ttbar",cut_bkg,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttjets_DL->Scale(1/h_ttjets_DL->Integral());

  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttjets_DL->SetLineWidth(2);
  h_ttjets_DL->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  //leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttjets_DL->SetMaximum(1.2*max(h_ttjets_DL->GetMaximum(),h_ttH->GetMaximum()));
  h_ttjets_DL->SetStats(0);
  h_ttjets_DL->Draw("");
  //h_ttH->Draw("");
  leg->Draw("same");

  h_ttjets_DL->GetXaxis()->SetTitle("2lSS1#tau ttH vs t#bar{t} MVA");
  h_ttjets_DL->GetYaxis()->SetTitle("a. u.");
  h_ttjets_DL->GetYaxis()->SetTitleOffset(1.65);
  h_ttjets_DL->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttjets_DL->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttbar_2lSS1tau_noMEM_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}





void plot_2lSS_ttbar_MVA_MEM_LR_ttH(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==41 && isTrig_1l_v2)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_MEM_LR_ttbar",cut_sig,50,-1,1);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T","MVA_2lSS1tau_MEM_LR_ttbar",cut_bkg,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttjets_DL->Scale(1/h_ttjets_DL->Integral());

  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttjets_DL->SetLineWidth(2);
  h_ttjets_DL->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  //leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttH->GetMaximum()));
  h_ttH->SetStats(0);
  //h_ttjets_DL->Draw("");
  h_ttH->Draw("");
  leg->Draw("same");

  h_ttH->GetXaxis()->SetTitle("2lSS1#tau ttH vs t#bar{t} MVA");
  h_ttH->GetYaxis()->SetTitle("a. u.");
  h_ttH->GetYaxis()->SetTitleOffset(1.65);
  h_ttH->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttH->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttbar_2lSS1tau_MEM_LR_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttbar_MVA_MEM_LR_ttbar_DL(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==41 && isTrig_1l_v2)";
  //TString cut_bkg = "category==41 && isTrig_1l_v2";  

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_MEM_LR_ttbar",cut_sig,50,-1,1);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T","MVA_2lSS1tau_MEM_LR_ttbar",cut_bkg,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttjets_DL->Scale(1/h_ttjets_DL->Integral());

  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttjets_DL->SetLineWidth(2);
  h_ttjets_DL->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  //leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttjets_DL->SetMaximum(1.2*max(h_ttjets_DL->GetMaximum(),h_ttH->GetMaximum()));
  h_ttjets_DL->SetStats(0);
  h_ttjets_DL->Draw("");
  //h_ttH->Draw("");
  leg->Draw("same");

  h_ttjets_DL->GetXaxis()->SetTitle("2lSS1#tau ttH vs t#bar{t} MVA");
  h_ttjets_DL->GetYaxis()->SetTitle("a. u.");
  h_ttjets_DL->GetYaxis()->SetTitleOffset(1.65);
  h_ttjets_DL->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttjets_DL->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttbar_2lSS1tau_MEM_LR_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttbar_MVA_MEM_weights_ttH(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==41 && isTrig_1l_v2)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_MEM_weights_ttbar",cut_sig,50,-1,1);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T","MVA_2lSS1tau_MEM_weights_ttbar",cut_bkg,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttjets_DL->Scale(1/h_ttjets_DL->Integral());

  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttjets_DL->SetLineWidth(2);
  h_ttjets_DL->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  //leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttH->GetMaximum()));
  h_ttH->SetStats(0);
  //h_ttjets_DL->Draw("");
  h_ttH->Draw("");
  leg->Draw("same");

  h_ttH->GetXaxis()->SetTitle("2lSS1#tau ttH vs t#bar{t} MVA");
  h_ttH->GetYaxis()->SetTitle("a. u.");
  h_ttH->GetYaxis()->SetTitleOffset(1.65);
  h_ttH->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttH->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttbar_2lSS1tau_MEM_weights_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttbar_MVA_MEM_weights_ttbar_DL(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==41 && isTrig_1l_v2)";
  //TString cut_bkg = "category==41 && isTrig_1l_v2";  

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_MEM_weights_ttbar",cut_sig,50,-1,1);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T","MVA_2lSS1tau_MEM_weights_ttbar",cut_bkg,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttjets_DL->Scale(1/h_ttjets_DL->Integral());

  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttjets_DL->SetLineWidth(2);
  h_ttjets_DL->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  //leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttjets_DL->SetMaximum(1.2*max(h_ttjets_DL->GetMaximum(),h_ttH->GetMaximum()));
  h_ttjets_DL->SetStats(0);
  h_ttjets_DL->Draw("");
  //h_ttH->Draw("");
  leg->Draw("same");

  h_ttjets_DL->GetXaxis()->SetTitle("2lSS1#tau ttH vs t#bar{t} MVA");
  h_ttjets_DL->GetYaxis()->SetTitle("a. u.");
  h_ttjets_DL->GetYaxis()->SetTitleOffset(1.65);
  h_ttjets_DL->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttjets_DL->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttbar_2lSS1tau_MEM_weights_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}








void plot_2lSS_ttbar_MVA_MEM_LR_ttH_nomiss(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==0)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==41 && isTrig_1l_v2 && integration_type==0)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_noMEM_ttbar",cut_sig,10,-1,1);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T","MVA_2lSS1tau_noMEM_ttbar",cut_bkg,10,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttjets_DL->Scale(1/h_ttjets_DL->Integral());

  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttjets_DL->SetLineWidth(2);
  h_ttjets_DL->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttjets_DL->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttjets_DL->GetMaximum()));
  h_ttjets_DL->SetStats(0);
  h_ttjets_DL->Draw("");
  h_ttH->Draw("same");
  leg->Draw("same");

  h_ttjets_DL->GetXaxis()->SetTitle("2lSS1#tau ttH vs t#bar{t} MVA");
  h_ttjets_DL->GetYaxis()->SetTitle("a. u.");
  h_ttjets_DL->GetYaxis()->SetTitleOffset(1.65);
  h_ttjets_DL->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttjets_DL->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttbar_2lSS1tau_MEM_LR_nomiss";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttbar_MVA_MEM_LR_ttH_missing(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==1)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==41 && isTrig_1l_v2 && integration_type==1)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_noMEM_ttbar",cut_sig,10,-1,1);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T","MVA_2lSS1tau_noMEM_ttbar",cut_bkg,10,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttjets_DL->Scale(1/h_ttjets_DL->Integral());

  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttjets_DL->SetLineWidth(2);
  h_ttjets_DL->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttjets_DL->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttjets_DL->GetMaximum()));
  h_ttjets_DL->SetStats(0);
  h_ttjets_DL->Draw("");
  h_ttH->Draw("same");
  leg->Draw("same");

  h_ttjets_DL->GetXaxis()->SetTitle("2lSS1#tau ttH vs t#bar{t} MVA");
  h_ttjets_DL->GetYaxis()->SetTitle("a. u.");
  h_ttjets_DL->GetYaxis()->SetTitleOffset(1.65);
  h_ttjets_DL->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttjets_DL->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttbar_2lSS1tau_MEM_LR_missing";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttbar_MEM_LR_nomiss(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==0)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==41 && isTrig_1l_v2 && integration_type==0)";

  TString var = "Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))";

  TH1F* h_ttH=single_plot(file_ttH,"T",var,cut_sig,10,0,1);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T",var,cut_bkg,10,0,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttjets_DL->Scale(1/h_ttjets_DL->Integral());

  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttjets_DL->SetLineWidth(2);
  h_ttjets_DL->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttjets_DL->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttjets_DL->GetMaximum()));
  h_ttjets_DL->SetStats(0);
  h_ttjets_DL->Draw("");
  h_ttH->Draw("same");
  leg->Draw("same");

  h_ttjets_DL->GetXaxis()->SetTitle("ttH vs t#bar{t} MEM LR");
  h_ttjets_DL->GetYaxis()->SetTitle("a. u.");
  h_ttjets_DL->GetYaxis()->SetTitleOffset(1.65);
  h_ttjets_DL->SetTitle("");

  TLatex *texl = new TLatex(0.01,1.01*h_ttjets_DL->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_ttbar_2lSS1tau_nomiss";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttbar_MEM_LR_missing(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttjets_DL="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==1)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==41 && isTrig_1l_v2 && integration_type==1)";

  TString var = "Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))";

  TH1F* h_ttH=single_plot(file_ttH,"T",var,cut_sig,10,0,1);
  TH1F* h_ttjets_DL=single_plot(file_ttjets_DL,"T",var,cut_bkg,10,0,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttjets_DL->Scale(1/h_ttjets_DL->Integral());

  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttjets_DL->SetLineWidth(2);
  h_ttjets_DL->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttjets_DL,"t#bar{t} DL");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttjets_DL->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttjets_DL->GetMaximum()));
  h_ttjets_DL->SetStats(0);
  h_ttjets_DL->Draw("");
  h_ttH->Draw("same");
  leg->Draw("same");

  h_ttjets_DL->GetXaxis()->SetTitle("ttH vs t#bar{t} MEM LR");
  h_ttjets_DL->GetYaxis()->SetTitle("a. u.");
  h_ttjets_DL->GetYaxis()->SetTitleOffset(1.65);
  h_ttjets_DL->SetTitle("");

  TLatex *texl = new TLatex(0.01,1.01*h_ttjets_DL->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_ttbar_2lSS1tau_missing";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}












void plot_2lSS_ttV_MVA_noMEM_ttH(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_noMEM_ttV",cut_sig,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttH->GetMaximum()));
  h_ttH->SetStats(0);
  h_ttH->Draw("");
  leg->Draw("same");

  h_ttH->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttH->GetYaxis()->SetTitle("a. u.");
  h_ttH->GetYaxis()->SetTitleOffset(1.65);
  h_ttH->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttH->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_noMEM_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttV_MVA_noMEM_ttV(){

  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";


  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";

  TH1F* h_ttZ=single_plot(file_ttZ,"T","MVA_2lSS1tau_noMEM_ttV",cut_sig,50,-1,1);
  TH1F* h_ttW=single_plot(file_ttW,"T","MVA_2lSS1tau_noMEM_ttV",cut_sig,50,-1,1);

  h_ttZ->Scale(7.24780/h_ttZ->Integral());
  h_ttW->Scale(5.84580/h_ttW->Integral());
  h_ttZ->Add(h_ttW);
  h_ttZ->Scale(1/(7.24780+5.84580));
  

  h_ttZ->SetLineWidth(2);
  h_ttZ->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttZ,"ttV");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttZ->SetMaximum(1.2*max(h_ttZ->GetMaximum(),h_ttZ->GetMaximum()));
  h_ttZ->SetStats(0);
  h_ttZ->Draw("");
  leg->Draw("same");

  h_ttZ->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttZ->GetYaxis()->SetTitle("a. u.");
  h_ttZ->GetYaxis()->SetTitleOffset(1.65);
  h_ttZ->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttZ->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_noMEM_ttV";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}









void plot_2lSS_ttV_MVA_noMEM_ttW(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_noMEM_ttV",cut_sig,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kGreen);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttW");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttH->GetMaximum()));
  h_ttH->SetStats(0);
  h_ttH->Draw("");
  leg->Draw("same");

  h_ttH->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttH->GetYaxis()->SetTitle("a. u.");
  h_ttH->GetYaxis()->SetTitleOffset(1.65);
  h_ttH->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttH->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_noMEM_ttW";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}








void plot_2lSS_ttV_MVA_MEM_LR_ttH(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_MEM_LR_ttV",cut_sig,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttH->GetMaximum()));
  h_ttH->SetStats(0);
  h_ttH->Draw("");
  leg->Draw("same");

  h_ttH->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttH->GetYaxis()->SetTitle("a. u.");
  h_ttH->GetYaxis()->SetTitleOffset(1.65);
  h_ttH->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttH->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_MEM_LR_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttV_MVA_MEM_LR_ttZ(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_MEM_LR_ttV",cut_sig,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttZ");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttH->GetMaximum()));
  h_ttH->SetStats(0);
  h_ttH->Draw("");
  leg->Draw("same");

  h_ttH->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttH->GetYaxis()->SetTitle("a. u.");
  h_ttH->GetYaxis()->SetTitleOffset(1.65);
  h_ttH->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttH->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_MEM_LR_ttZ";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}









void plot_2lSS_ttV_MVA_MEM_LR_ttW(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_MEM_LR_ttV",cut_sig,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kGreen);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttW");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttH->GetMaximum()));
  h_ttH->SetStats(0);
  h_ttH->Draw("");
  leg->Draw("same");

  h_ttH->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttH->GetYaxis()->SetTitle("a. u.");
  h_ttH->GetYaxis()->SetTitleOffset(1.65);
  h_ttH->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttH->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_MEM_LR_ttW";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttV_MVA_MEM_weights_ttH(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_MEM_weights_ttV",cut_sig,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttH->GetMaximum()));
  h_ttH->SetStats(0);
  h_ttH->Draw("");
  leg->Draw("same");

  h_ttH->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttH->GetYaxis()->SetTitle("a. u.");
  h_ttH->GetYaxis()->SetTitleOffset(1.65);
  h_ttH->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttH->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_MEM_weights_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttV_MVA_MEM_weights_ttZ(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_MEM_weights_ttV",cut_sig,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttZ");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttH->GetMaximum()));
  h_ttH->SetStats(0);
  h_ttH->Draw("");
  leg->Draw("same");

  h_ttH->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttH->GetYaxis()->SetTitle("a. u.");
  h_ttH->GetYaxis()->SetTitleOffset(1.65);
  h_ttH->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttH->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_MEM_weights_ttZ";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}









void plot_2lSS_ttV_MVA_MEM_weights_ttW(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";

  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_MEM_weights_ttV",cut_sig,50,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kGreen);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttW");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttH->GetMaximum()));
  h_ttH->SetStats(0);
  h_ttH->Draw("");
  leg->Draw("same");

  h_ttH->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttH->GetYaxis()->SetTitle("a. u.");
  h_ttH->GetYaxis()->SetTitleOffset(1.65);
  h_ttH->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttH->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_MEM_weights_ttW";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}








void plot_2lSS_ttV_MVA_MEM_weights_ttV(){

  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";


  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2)";

  TH1F* h_ttZ=single_plot(file_ttZ,"T","MVA_2lSS1tau_MEM_weights_ttV",cut_sig,50,-1,1);
  TH1F* h_ttW=single_plot(file_ttW,"T","MVA_2lSS1tau_MEM_weights_ttV",cut_sig,50,-1,1);

  h_ttZ->Scale(7.24780/h_ttZ->Integral());
  h_ttW->Scale(5.84580/h_ttW->Integral());
  h_ttZ->Add(h_ttW);
  h_ttZ->Scale(1/(7.24780+5.84580));
  

  h_ttZ->SetLineWidth(2);
  h_ttZ->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttZ,"ttV");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttZ->SetMaximum(1.2*max(h_ttZ->GetMaximum(),h_ttZ->GetMaximum()));
  h_ttZ->SetStats(0);
  h_ttZ->Draw("");
  leg->Draw("same");

  h_ttZ->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttZ->GetYaxis()->SetTitle("a. u.");
  h_ttZ->GetYaxis()->SetTitleOffset(1.65);
  h_ttZ->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttZ->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_MEM_weights_ttV";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}









void plot_2lSS_ttZ_MEM_LR_nomiss(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";


  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==0)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==0)";

  TString var = "Integral_ttH/(Integral_ttH+0.5*Integral_ttZ+1.0*Integral_ttZ_Zll)";

  TH1F* h_ttH=single_plot(file_ttH,"T",var,cut_sig,10,0,1);
  TH1F* h_ttZ=single_plot(file_ttZ,"T",var,cut_bkg,10,0,1);
  TH1F* h_ttW=single_plot(file_ttW,"T",var,cut_bkg,10,0,1);


  h_ttH->Scale(1/h_ttH->Integral());
  h_ttZ->Scale(1/h_ttZ->Integral());
  h_ttW->Scale(1/h_ttW->Integral());


  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttZ->SetLineWidth(2);
  h_ttZ->SetLineColor(kRed);
  h_ttW->SetLineWidth(2);
  h_ttW->SetLineColor(kGreen);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttZ,"ttZ");
  leg->AddEntry(h_ttW,"ttW");


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttZ->SetMaximum(1.2*max(max(h_ttH->GetMaximum(),h_ttZ->GetMaximum()),h_ttW->GetMaximum()));
  h_ttZ->SetStats(0);
  h_ttZ->Draw("");
  h_ttH->Draw("same");
  h_ttW->Draw("same");
  leg->Draw("same");

  h_ttZ->GetXaxis()->SetTitle("ttH vs ttZ MEM LR");
  h_ttZ->GetYaxis()->SetTitle("a. u.");
  h_ttZ->GetYaxis()->SetTitleOffset(1.65);
  h_ttZ->SetTitle("");

  TLatex *texl = new TLatex(0.01,1.01*h_ttZ->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_ttZ_2lSS1tau_nomiss";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}









void plot_2lSS_ttZ_MEM_LR_missing(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";


  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==1)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==1)";

  TString var = "Integral_ttH/(Integral_ttH+0.05*Integral_ttZ+0.1*Integral_ttZ_Zll)";

  TH1F* h_ttH=single_plot(file_ttH,"T",var,cut_sig,10,0,1);
  TH1F* h_ttZ=single_plot(file_ttZ,"T",var,cut_bkg,10,0,1);
  TH1F* h_ttW=single_plot(file_ttW,"T",var,cut_bkg,10,0,1);


  h_ttH->Scale(1/h_ttH->Integral());
  h_ttZ->Scale(1/h_ttZ->Integral());
  h_ttW->Scale(1/h_ttW->Integral());


  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttZ->SetLineWidth(2);
  h_ttZ->SetLineColor(kRed);
  h_ttW->SetLineWidth(2);
  h_ttW->SetLineColor(kGreen);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttZ,"ttZ");
  leg->AddEntry(h_ttW,"ttW");


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttZ->SetMaximum(1.2*max(max(h_ttH->GetMaximum(),h_ttZ->GetMaximum()),h_ttW->GetMaximum()));
  h_ttZ->SetStats(0);
  h_ttZ->Draw("");
  h_ttH->Draw("same");
  h_ttW->Draw("same");
  leg->Draw("same");

  h_ttZ->GetXaxis()->SetTitle("ttH vs ttZ MEM LR");
  h_ttZ->GetYaxis()->SetTitle("a. u.");
  h_ttZ->GetYaxis()->SetTitleOffset(1.65);
  h_ttZ->SetTitle("");

  TLatex *texl = new TLatex(0.01,1.01*h_ttZ->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_ttZ_2lSS1tau_missing";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}











void plot_2lSS_MVA_ttV_nomiss(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";


  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==0)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==0)";

  TString var = "MVA_2lSS1tau_noMEM_ttV";

  TH1F* h_ttH=single_plot(file_ttH,"T",var,cut_sig,10,-1,1);
  TH1F* h_ttZ=single_plot(file_ttZ,"T",var,cut_bkg,10,-1,1);
  TH1F* h_ttW=single_plot(file_ttW,"T",var,cut_bkg,10,-1,1);


  h_ttH->Scale(1/h_ttH->Integral());
  h_ttZ->Scale(1/h_ttZ->Integral());
  h_ttW->Scale(1/h_ttW->Integral());


  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttZ->SetLineWidth(2);
  h_ttZ->SetLineColor(kRed);
  h_ttW->SetLineWidth(2);
  h_ttW->SetLineColor(kGreen);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttZ,"ttZ");
  leg->AddEntry(h_ttW,"ttW");


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttZ->SetMaximum(1.2*max(max(h_ttH->GetMaximum(),h_ttZ->GetMaximum()),h_ttW->GetMaximum()));
  h_ttZ->SetStats(0);
  h_ttZ->Draw("");
  h_ttH->Draw("same");
  h_ttW->Draw("same");
  leg->Draw("same");

  h_ttZ->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttZ->GetYaxis()->SetTitle("a. u.");
  h_ttZ->GetYaxis()->SetTitleOffset(1.65);
  h_ttZ->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttZ->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_nomiss";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}






void plot_2lSS_ttV_MVA_noMEM_ttV_nomiss(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";


  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==0)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_noMEM_ttV",cut_sig,10,-1,1);
  TH1F* h_ttZ=single_plot(file_ttZ,"T","MVA_2lSS1tau_noMEM_ttV",cut_sig,10,-1,1);
  TH1F* h_ttW=single_plot(file_ttW,"T","MVA_2lSS1tau_noMEM_ttV",cut_sig,10,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttZ->Scale(1.9571/h_ttZ->Integral());
  h_ttW->Scale(0.7722/h_ttW->Integral());
  h_ttZ->Add(h_ttW);
  h_ttZ->Scale(1/(1.9571+0.7722));
  
  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttZ->SetLineWidth(2);
  h_ttZ->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttZ,"ttV");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttZ->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttZ->GetMaximum()));
  h_ttZ->SetStats(0);
  h_ttZ->Draw("");
  h_ttH->Draw("same");
  leg->Draw("same");

  h_ttZ->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttZ->GetYaxis()->SetTitle("a. u.");
  h_ttZ->GetYaxis()->SetTitleOffset(1.65);
  h_ttZ->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttZ->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_noMEM_ttV_nomiss";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}






void plot_2lSS_ttV_MVA_noMEM_ttV_missing(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";


  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==1)";

  TH1F* h_ttH=single_plot(file_ttH,"T","MVA_2lSS1tau_noMEM_ttV",cut_sig,10,-1,1);
  TH1F* h_ttZ=single_plot(file_ttZ,"T","MVA_2lSS1tau_noMEM_ttV",cut_sig,10,-1,1);
  TH1F* h_ttW=single_plot(file_ttW,"T","MVA_2lSS1tau_noMEM_ttV",cut_sig,10,-1,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttZ->Scale(5.2907/h_ttZ->Integral());
  h_ttW->Scale(5.0736/h_ttW->Integral());
  h_ttZ->Add(h_ttW);
  h_ttZ->Scale(1/(5.2907+5.0736));
  
  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttZ->SetLineWidth(2);
  h_ttZ->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttZ,"ttV");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttZ->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttZ->GetMaximum()));
  h_ttZ->SetStats(0);
  h_ttZ->Draw("");
  h_ttH->Draw("same");
  leg->Draw("same");

  h_ttZ->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttZ->GetYaxis()->SetTitle("a. u.");
  h_ttZ->GetYaxis()->SetTitleOffset(1.65);
  h_ttZ->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttZ->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_noMEM_ttV_missing";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}








void plot_2lSS_MVA_ttV_missing(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";


  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==1)";
  TString cut_bkg = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==1)";


  TString var = "MVA_2lSS1tau_noMEM_ttV";

  TH1F* h_ttH=single_plot(file_ttH,"T",var,cut_sig,10,-1,1);
  TH1F* h_ttZ=single_plot(file_ttZ,"T",var,cut_bkg,10,-1,1);
  TH1F* h_ttW=single_plot(file_ttW,"T",var,cut_bkg,10,-1,1);


  h_ttH->Scale(1/h_ttH->Integral());
  h_ttZ->Scale(1/h_ttZ->Integral());
  h_ttW->Scale(1/h_ttW->Integral());


  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttZ->SetLineWidth(2);
  h_ttZ->SetLineColor(kRed);
  h_ttW->SetLineWidth(2);
  h_ttW->SetLineColor(kGreen);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttZ,"ttZ");
  leg->AddEntry(h_ttW,"ttW");


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttZ->SetMaximum(1.2*max(max(h_ttH->GetMaximum(),h_ttZ->GetMaximum()),h_ttW->GetMaximum()));
  h_ttZ->SetStats(0);
  h_ttZ->Draw("");
  h_ttH->Draw("same");
  h_ttW->Draw("same");
  leg->Draw("same");

  h_ttZ->GetXaxis()->SetTitle("2lSS1#tau ttH vs ttV MVA");
  h_ttZ->GetYaxis()->SetTitle("a. u.");
  h_ttZ->GetYaxis()->SetTitleOffset(1.65);
  h_ttZ->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttZ->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_ttV_2lSS1tau_missing";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_2lSS_ttZ_MEM_LR_ttV_nomiss(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";


  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==0)";

  TString var = "Integral_ttH/(Integral_ttH+0.2*Integral_ttZ+0.4*Integral_ttZ_Zll)";


  TH1F* h_ttH=single_plot(file_ttH,"T",var,cut_sig,10,0,1);
  TH1F* h_ttZ=single_plot(file_ttZ,"T",var,cut_sig,10,0,1);
  TH1F* h_ttW=single_plot(file_ttW,"T",var,cut_sig,10,0,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttZ->Scale(1.9571/h_ttZ->Integral());
  h_ttW->Scale(0.7722/h_ttW->Integral());
  h_ttZ->Add(h_ttW);
  h_ttZ->Scale(1/(1.9571+0.7722));
  
  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttZ->SetLineWidth(2);
  h_ttZ->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttZ,"ttV");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttZ->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttZ->GetMaximum()));
  h_ttZ->SetStats(0);
  h_ttZ->Draw("");
  h_ttH->Draw("same");
  leg->Draw("same");

  h_ttZ->GetXaxis()->SetTitle("ttH vs ttZ MEM LR");
  h_ttZ->GetYaxis()->SetTitle("a. u.");
  h_ttZ->GetYaxis()->SetTitleOffset(1.65);
  h_ttZ->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttZ->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_ttZ_2lSS1tau_ttV_nomiss";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}





void plot_2lSS_ttZ_MEM_LR_ttV_missing(){

  TString file_ttH="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root";
  TString file_ttW="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root";


  TString cut_sig = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && isTrig_1l_v2 && integration_type==1)";

  TString var = "Integral_ttH/(Integral_ttH+0.1*Integral_ttZ+0.2*Integral_ttZ_Zll)";


  TH1F* h_ttH=single_plot(file_ttH,"T",var,cut_sig,10,0,1);
  TH1F* h_ttZ=single_plot(file_ttZ,"T",var,cut_sig,10,0,1);
  TH1F* h_ttW=single_plot(file_ttW,"T",var,cut_sig,10,0,1);

  h_ttH->Scale(1/h_ttH->Integral());
  h_ttZ->Scale(5.2907/h_ttZ->Integral());
  h_ttW->Scale(5.0736/h_ttW->Integral());
  h_ttZ->Add(h_ttW);
  h_ttZ->Scale(1/(5.2907+5.0736));
  
  h_ttH->SetLineWidth(2);
  h_ttH->SetLineColor(kBlue);

  h_ttZ->SetLineWidth(2);
  h_ttZ->SetLineColor(kRed);


  TLegend* leg=new TLegend(0.55,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_ttH,"ttH");
  leg->AddEntry(h_ttZ,"ttV");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttZ->SetMaximum(1.2*max(h_ttH->GetMaximum(),h_ttZ->GetMaximum()));
  h_ttZ->SetStats(0);
  h_ttZ->Draw("");
  h_ttH->Draw("same");
  leg->Draw("same");

  h_ttZ->GetXaxis()->SetTitle("ttH vs ttZ MEM LR");
  h_ttZ->GetYaxis()->SetTitle("a. u.");
  h_ttZ->GetYaxis()->SetTitleOffset(1.65);
  h_ttZ->SetTitle("");

  TLatex *texl = new TLatex(-0.99,1.01*h_ttZ->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_ttZ_2lSS1tau_ttV_missing";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}




