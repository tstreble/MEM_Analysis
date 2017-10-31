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
#include <TGaxis.h>

float luminosity = 12900; //12.9 fb-1

using namespace std;


void plot_2lSS(TString datacardname, TString varname, TString plotname){

  TFile* f = TFile::Open(datacardname);

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

  TH1F h_WZ = h_fakes;
  h_WZ.Add( (TH1F*)f->Get("x_EWK") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_ttZ = h_WZ;
  h_ttZ.Add( (TH1F*)f->Get("x_TTZ") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("x_TTW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hww") );
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hzz") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("x_ttH_htt") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 


  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  //TH1F h_data_obs = *(TH1F*)f->Get("x_data_obs");
  TH1F h_data_obs = h_ttH;
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();


  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle(varname);
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
  (&h_WZ)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  //(&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());

  
  TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");


  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  cout<<"Bkg="<<h_ttW.Integral()<<endl;
  cout<<"Bin1="<<h_ttW.Integral(1,1)<<endl;
  cout<<"Bin2="<<h_ttW.Integral(2,2)<<endl;
  cout<<"Bin3="<<h_ttW.Integral(3,3)<<endl;
  cout<<"Bin4="<<h_ttW.Integral(4,4)<<endl;
  cout<<"Bin5="<<h_ttW.Integral(5,5)<<endl;
  cout<<"Bin6="<<h_ttW.Integral(6,6)<<endl;
  cout<<"Bin7="<<h_ttW.Integral(7,7)<<endl;
  cout<<"Bin8="<<h_ttW.Integral(8,8)<<endl;
  cout<<"Bin9="<<h_ttW.Integral(9,9)<<endl;
  cout<<"Bin10="<<h_ttW.Integral(10,10)<<endl;


  return;


}



void plot_1l2tau(TString datacardname, TString varname, TString plotname){

  TFile* f = TFile::Open(datacardname);

  TH1F h_fakes = *(TH1F*)f->Get("x_fakes_data");
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_WZ = h_fakes;
  h_WZ.Add( (TH1F*)f->Get("x_EWK") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_ttZ = h_WZ;
  h_ttZ.Add( (TH1F*)f->Get("x_TTZ") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("x_TTW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  /*TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hww") );
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hzz") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);*/

  TH1F h_ttH = h_ttW;
  h_ttH.Add( (TH1F*)f->Get("x_ttH") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);
  h_ttH_only.Scale(10);

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);


  TH1F h_data_obs = *(TH1F*)f->Get("x_data_obs");
  //TH1F h_data_obs = h_ttH;
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();

  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_ttH,"ttH");
  //leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  //leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_ttH_only,"ttH signal x 10");
  
  h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  //(&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_ttH_only)->Draw("histsame");


  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());

  
  TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");


  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  cout<<"Bkg="<<h_ttW.Integral()<<endl;
  cout<<"Bin1="<<h_ttW.Integral(1,1)<<endl;
  cout<<"Bin2="<<h_ttW.Integral(2,2)<<endl;
  cout<<"Bin3="<<h_ttW.Integral(3,3)<<endl;
  cout<<"Bin4="<<h_ttW.Integral(4,4)<<endl;
  cout<<"Bin5="<<h_ttW.Integral(5,5)<<endl;
  cout<<"Bin6="<<h_ttW.Integral(6,6)<<endl;
  cout<<"Bin7="<<h_ttW.Integral(7,7)<<endl;
  cout<<"Bin8="<<h_ttW.Integral(8,8)<<endl;
  cout<<"Bin9="<<h_ttW.Integral(9,9)<<endl;
  cout<<"Bin10="<<h_ttW.Integral(10,10)<<endl;


  return;


}





void plot(TString datacardname, TString varname, TString plotname){

  TFile* f = TFile::Open(datacardname);

  TH1F h_fakes = *(TH1F*)f->Get("x_fakes_data");
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_WZ = h_fakes;
  h_WZ.Add( (TH1F*)f->Get("x_WZ") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_ttZ = h_WZ;
  h_ttZ.Add( (TH1F*)f->Get("x_TTZ") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("x_TTW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hww") );
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hzz") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("x_ttH_htt") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  /*TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);
  h_ttH_only.Scale(10);*/

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);


  //TH1F h_data_obs = *(TH1F*)f->Get("h_data_obs");
  TH1F h_data_obs = h_ttH;
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();

  TLegend* leg=new TLegend(0.65,0.6,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  //leg->AddEntry(&h_ttH_only,"ttH signal x 10");
  
  h_ttH.GetXaxis()->SetTitle(varname);
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
  (&h_WZ)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  //(&h_ttH_only)->Draw("histsame");


  (&h_ttH_error)->Draw("e2same");
  //(&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());

  
  TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");


  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  cout<<"Bkg="<<h_ttW.Integral()<<endl;
  cout<<"Bin1="<<h_ttW.Integral(1,1)<<endl;
  cout<<"Bin2="<<h_ttW.Integral(2,2)<<endl;
  cout<<"Bin3="<<h_ttW.Integral(3,3)<<endl;
  cout<<"Bin4="<<h_ttW.Integral(4,4)<<endl;
  cout<<"Bin5="<<h_ttW.Integral(5,5)<<endl;
  cout<<"Bin6="<<h_ttW.Integral(6,6)<<endl;
  cout<<"Bin7="<<h_ttW.Integral(7,7)<<endl;
  cout<<"Bin8="<<h_ttW.Integral(8,8)<<endl;
  cout<<"Bin9="<<h_ttW.Integral(9,9)<<endl;
  cout<<"Bin10="<<h_ttW.Integral(10,10)<<endl;


  return;


}






void plot_MVA_2lSS(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_10_2016/datacards/datacard_MVA_2lSS_allcat_syst_12.9fb_102016.root",
       "MVA(ttH vs ttV/t#bar{t})",
       "MVA_2lSS_ttV_ttbar_datacard_12.9fb_102016");


}





void plot_njet_1l2tau(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_10_2016/datacards/datacard_njet_1l2tau_syst_12.9fb.root",
       "# jets",
       "njet_1l2tau_datacard_12.9fb");


}




void plot_MVA_3l(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_10_2016/datacards/datacard_MVA_3l1tau_syst_12.9fb.root",
	  "MVA(ttH vs ttV/t#bar{t})",
	  "MVA_3l1tau_ttV_ttbar_datacard_12.9fb");


}







void plot_MVA_2lSS_112016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MVA_2lSS_allcat_syst_12.9fb_112016.root",
       "MVA(ttH vs ttV/t#bar{t})",
       "MVA_2lSS_ttV_ttbar_datacard_12.9fb_112016");


}






void plot_MVA_2lSS_nofaketau_112016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MVA_2lSS_allcat_syst_nofaketau_12.9fb_112016.root",
       "MVA(ttH vs ttV/t#bar{t})",
       "MVA_2lSS_ttV_ttbar_datacard_nofaketau_12.9fb_112016");


}






void plot_MEM_nomiss_2lSS_112016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_12.9fb_112016.root",
       "MEM_LR",
       "MEM_LR_2lSS_nomiss_datacard_12.9fb_112016");


}





void plot_MEM_missing_2lSS_112016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_12.9fb_112016.root",
       "MEM_LR",
       "MEM_LR_2lSS_missing_datacard_12.9fb_112016");


}






void plot_njet_1l2tau_112016(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_njet_1l2tau_syst_12.9fb_112016.root",
       "# jets",
       "njet_1l2tau_datacard_12.9fb");


}




void plot_mvis_1l2tau_112016(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_mvis_1l2tau_syst_12.9fb_112016.root",
       "m_{vis}(#tau#tau)",
       "mvis_1l2tau_datacard_12.9fb");


}




void plot_MVA_3l_112016(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MVA_3l1tau_syst_12.9fb_112016.root",
	  "MVA(ttH vs ttV/t#bar{t})",
	  "MVA_3l1tau_ttV_ttbar_datacard_12.9fb");


}







void plot_MEM_nomiss_nofaketau_2lSS_112016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_12.9fb_112016.root",
       "MEM_LR",
       "MEM_LR_2lSS_nomiss_datacard_nofaketau_12.9fb_112016");


}





void plot_MEM_missing_nofaketau_2lSS_112016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_12.9fb_112016.root",
       "MEM_LR",
       "MEM_LR_2lSS_missing_datacard_nofaketau_12.9fb_112016");


}




void plot_MEM_nomiss_missing_nofaketau_2lSS_112016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_missing_nofaketau_12.9fb_112016.root",
       "MEM_LR",
       "MEM_LR_2lSS_nomiss_missing_datacard_nofaketau_12.9fb_112016");


}



void plot_MVA_3l_nofaketau_112016(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MVA_3l1tau_syst_nofaketau_12.9fb_112016.root",
	  "MVA(ttH vs ttV/t#bar{t})",
	  "MVA_3l1tau_ttV_ttbar_nofaketau_datacard_12.9fb");


}

