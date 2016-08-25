#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>
#include <THStack.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
#include <iostream>

float luminosity = 4000; //4.0 fb-1

using namespace std;


void plot_MVA_2lSS_ttbar(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_ttbar.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);
  

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_ZZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WWZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_tZq") );
  h_RaresEW.Add( (TH1F*)f->Get("h_TTTT") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);

  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_WZ") );
  h_Diboson.Add( (TH1F*)f->Get("h_ZZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);

  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_ttZ") );
  h_ttZ.Add( (TH1F*)f->Get("h_TTLL_lowmass") );
  h_ttZ.Add( (TH1F*)f->Get("h_ttG") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);  

  f->Close();



  TLegend* leg=new TLegend(0.25,0.6,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  
  h_ttH.GetXaxis()->SetTitle("MVA(ttH,tt)");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame");
 
  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");



  
  TLatex *texl = new TLatex(-0.99,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_2lSS_ttH_ttbar_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}








void plot_MVA_2lSS_ttV(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_ttV.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);
  
  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_ZZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WWZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_tZq") );
  h_RaresEW.Add( (TH1F*)f->Get("h_TTTT") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);
  
  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_WZ") );
  h_Diboson.Add( (TH1F*)f->Get("h_ZZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);

  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_ttZ") );
  h_ttZ.Add( (TH1F*)f->Get("h_TTLL_lowmass") );
  h_ttZ.Add( (TH1F*)f->Get("h_ttG") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle("MVA(ttH,ttV)");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame");

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(-0.99,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_2lSS_ttH_ttV_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}








void plot_MVA_2lSS_ttbar_ttV(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_pt25.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  //gStyle->SetHatchesLineWidth(2);

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_ZZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WWZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_tZq") );
  h_RaresEW.Add( (TH1F*)f->Get("h_TTTT") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);

  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_WZ") );
  h_Diboson.Add( (TH1F*)f->Get("h_ZZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);
  
  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_ttZ") );
  h_ttZ.Add( (TH1F*)f->Get("h_TTLL_lowmass") );
  h_ttZ.Add( (TH1F*)f->Get("h_ttG") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  /*TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); */

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_boson") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("h_ttH_tautau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  //leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");

  
  h_ttH.GetXaxis()->SetTitle("MVA(ttH,ttbar/ttV) bin");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(0.51,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_2lSS_ttH_ttbar_ttV_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}






void plot_MVA_2lSS_ttbar_ttV_fakes_MC(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_pt25.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes_MC") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  cout<<h_fakes.Integral()-h_flips.Integral()<<endl;

  //gStyle->SetHatchesLineWidth(2);

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_ZZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WWZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_tZq") );
  h_RaresEW.Add( (TH1F*)f->Get("h_TTTT") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);

  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_WZ") );
  h_Diboson.Add( (TH1F*)f->Get("h_ZZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);
  
  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_ttZ") );
  h_ttZ.Add( (TH1F*)f->Get("h_TTLL_lowmass") );
  h_ttZ.Add( (TH1F*)f->Get("h_ttG") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  /*TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); */

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_boson") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("h_ttH_tautau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  //leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");

  
  h_ttH.GetXaxis()->SetTitle("MVA(ttH,ttbar/ttV) bin");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(0.51,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_2lSS_ttH_ttbar_ttV_fakes_MC_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}







void plot_MVA_2lSS_ttbar_ttV_CERN(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacards_CERN/datacard_CERN_2lss_1tau_4fb.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("x_flips_data");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("x_fakes_data") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  //gStyle->SetHatchesLineWidth(2);

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("x_Rares") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);

  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("x_WZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);
  
  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("x_TTZ") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("x_TTW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("x_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("x_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");

  
  h_ttH.GetXaxis()->SetTitle("MVA(ttH,ttbar/ttV) bin");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(0.51,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MVA_2lSS_ttH_ttbar_ttV_datacard_CERN";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}







void plot_MEM_LR_nomiss(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_nomiss.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  //gStyle->SetHatchesLineWidth(2);

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_ZZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WWZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_tZq") );
  h_RaresEW.Add( (TH1F*)f->Get("h_TTTT") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);

  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_WZ") );
  h_Diboson.Add( (TH1F*)f->Get("h_ZZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);
  
  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_ttZ") );
  h_ttZ.Add( (TH1F*)f->Get("h_TTLL_lowmass") );
  h_ttZ.Add( (TH1F*)f->Get("h_ttG") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_boson") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("h_ttH_tautau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  /*TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack);*/

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  //leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle("MEM LR(ttH vs t#bar{t})");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(0.01,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_nomiss_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}









void plot_MEM_LR_missingjet(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_missingjet.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  //gStyle->SetHatchesLineWidth(2);

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_ZZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WWZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_tZq") );
  h_RaresEW.Add( (TH1F*)f->Get("h_TTTT") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);
  
  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_WZ") );
  h_Diboson.Add( (TH1F*)f->Get("h_ZZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);

  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_ttZ") );
  h_ttZ.Add( (TH1F*)f->Get("h_TTLL_lowmass") );
  h_ttZ.Add( (TH1F*)f->Get("h_ttG") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_boson") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("h_ttH_tautau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  /*TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); */

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  //leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle("MEM LR(ttH vs t#bar{t})");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(0.01,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_missingjet_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}








void plot_MEM_LR_incl(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  //gStyle->SetHatchesLineWidth(2);

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_Rares") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);
  
  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_Diboson") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);

  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_TTZ") ); 
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  /*TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); */

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_boson") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("h_ttH_tautau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack);

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  //leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle("MEM LR(ttH vs t#bar{t})");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(0.01,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_incl_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}







void plot_MEM_LR_nomiss_tauOS(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_nomiss_tauOS.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  //gStyle->SetHatchesLineWidth(2);

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_ZZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WWZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_tZq") );
  h_RaresEW.Add( (TH1F*)f->Get("h_TTTT") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);

  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_WZ") );
  h_Diboson.Add( (TH1F*)f->Get("h_ZZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);
  
  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_ttZ") );
  h_ttZ.Add( (TH1F*)f->Get("h_TTLL_lowmass") );
  h_ttZ.Add( (TH1F*)f->Get("h_ttG") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_boson") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("h_ttH_tautau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  /*TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack);*/

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  //leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle("MEM LR(ttH vs t#bar{t})");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(0.01,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_nomiss_tauOS_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}









void plot_MEM_LR_missingjet_tauOS(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_missingjet_tauOS.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  //gStyle->SetHatchesLineWidth(2);

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_ZZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WWZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_tZq") );
  h_RaresEW.Add( (TH1F*)f->Get("h_TTTT") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);
  
  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_WZ") );
  h_Diboson.Add( (TH1F*)f->Get("h_ZZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);

  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_ttZ") );
  h_ttZ.Add( (TH1F*)f->Get("h_TTLL_lowmass") );
  h_ttZ.Add( (TH1F*)f->Get("h_ttG") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_boson") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("h_ttH_tautau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  /*TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); */

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  //leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle("MEM LR(ttH vs t#bar{t})");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(0.01,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_missingjet_tauOS_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}









void plot_MEM_LR_nomiss_log(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_nomiss_log.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  //gStyle->SetHatchesLineWidth(2);

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_ZZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WWZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_tZq") );
  h_RaresEW.Add( (TH1F*)f->Get("h_TTTT") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);

  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_WZ") );
  h_Diboson.Add( (TH1F*)f->Get("h_ZZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);
  
  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_ttZ") );
  h_ttZ.Add( (TH1F*)f->Get("h_TTLL_lowmass") );
  h_ttZ.Add( (TH1F*)f->Get("h_ttG") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_boson") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("h_ttH_tautau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  /*TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack);*/

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  //leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle("MEM LR(ttH vs t#bar{t})");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(0.01,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_nomiss_log_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}









void plot_MEM_LR_missingjet_log(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_missingjet_log.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  //gStyle->SetHatchesLineWidth(2);

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_ZZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WWZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_tZq") );
  h_RaresEW.Add( (TH1F*)f->Get("h_TTTT") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);
  
  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_WZ") );
  h_Diboson.Add( (TH1F*)f->Get("h_ZZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);

  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_ttZ") );
  h_ttZ.Add( (TH1F*)f->Get("h_TTLL_lowmass") );
  h_ttZ.Add( (TH1F*)f->Get("h_ttG") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_boson") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("h_ttH_tautau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  /*TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); */

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  //leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle("MEM LR(ttH vs t#bar{t})");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(0.01,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_missingjet_log_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}








void plot_MEM_LR_nomiss_fakes_MC(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_nomiss.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes_MC") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  //gStyle->SetHatchesLineWidth(2);

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_ZZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WWZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_tZq") );
  h_RaresEW.Add( (TH1F*)f->Get("h_TTTT") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);

  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_WZ") );
  h_Diboson.Add( (TH1F*)f->Get("h_ZZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);
  
  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_ttZ") );
  h_ttZ.Add( (TH1F*)f->Get("h_TTLL_lowmass") );
  h_ttZ.Add( (TH1F*)f->Get("h_ttG") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_boson") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("h_ttH_tautau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  /*TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack);*/

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  //leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle("MEM LR(ttH vs t#bar{t})");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(0.01,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_nomiss_fakes_MC_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}









void plot_MEM_LR_missingjet_fakes_MC(){

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_missingjet.root";

  TFile* f = TFile::Open(file);

  TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("h_fakes_MC") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  //gStyle->SetHatchesLineWidth(2);

  TH1F h_RaresEW = h_fakes;
  h_RaresEW.Add( (TH1F*)f->Get("h_WpWp") );
  h_RaresEW.Add( (TH1F*)f->Get("h_ZZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WZZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_WWZ") );
  h_RaresEW.Add( (TH1F*)f->Get("h_tZq") );
  h_RaresEW.Add( (TH1F*)f->Get("h_TTTT") );
  h_RaresEW.SetFillColor(kAzure+10);
  h_RaresEW.SetLineColor(kBlack);
  
  TH1F h_Diboson = h_RaresEW;
  h_Diboson.Add( (TH1F*)f->Get("h_WZ") );
  h_Diboson.Add( (TH1F*)f->Get("h_ZZ") );
  h_Diboson.SetFillColor(kViolet-5);
  h_Diboson.SetLineColor(kBlack);

  TH1F h_ttZ = h_Diboson;
  h_ttZ.Add( (TH1F*)f->Get("h_ttZ") );
  h_ttZ.Add( (TH1F*)f->Get("h_TTLL_lowmass") );
  h_ttZ.Add( (TH1F*)f->Get("h_ttG") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_boson") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("h_ttH_tautau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  /*TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("h_ttH") );
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); */

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();



  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  //leg->AddEntry(&h_ttH,"ttH");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_Diboson,"WZ");
  leg->AddEntry(&h_RaresEW,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle("MEM LR(ttH vs t#bar{t})");
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_Diboson)->Draw("histsame");
  (&h_RaresEW)->Draw("histsame"); 
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());




  
  TLatex *texl = new TLatex(0.01,1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_LR_missingjet_fakes_MC_datacard";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}



