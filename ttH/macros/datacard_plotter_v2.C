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


void plot(TString datacardname, TString varname, TString plotname){

  TFile* f = TFile::Open(datacardname);

  /*TH1F h_flips = *(TH1F*)f->Get("h_flips");
  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);*/

  //TH1F h_fakes = h_flips;
  //h_fakes.Add( (TH1F*)f->Get("h_fakes") );
  TH1F h_fakes = *(TH1F*)f->Get("h_fakes");
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_ttZ = h_fakes;
  //TH1F h_ttZ = h_flips;
  h_ttZ.Add( (TH1F*)f->Get("h_TTZ") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("h_ttW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_hww") );
  h_ttH_boson.Add( (TH1F*)f->Get("h_ttH_hzz") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("h_ttH_htt") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 


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
  leg->AddEntry(&h_fakes_lines,"Fakes");
  //leg->AddEntry(&h_flips_lines,"Flips");
  
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
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  //(&h_flips)->Draw("histsame"); 
  //(&h_flips_lines)->Draw("histsame"); 

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



void plot_CERN(TString datacardname, TString varname, TString plotname){

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

  TH1F h_ttZ = h_fakes;
  //TH1F h_ttZ = h_flips;
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
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("same");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());

  
  TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.03);
  texl->Draw("same");


  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}





void plot_MEM_LR_ttH_vs_fakes_nomiss_092016(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MEM_ttH_vs_fakes_2lSS_nomiss_12.9fb.root",
       "MEM LR(ttH vs t#bar{t})",
       "MEM_LR_ttH_vs_fakes_nomiss_datacard_092016");


}







void plot_MEM_LR_ttH_vs_fakes_missing_092016(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MEM_ttH_vs_fakes_2lSS_missing_12.9fb.root",
       "MEM LR(ttH vs t#bar{t})",
       "MEM_LR_ttH_vs_fakes_missing_datacard_092016");


}






void plot_MEM_LR_ttH_vs_full_bkg_nomiss_092016(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_12.9fb.root",
       "MEM LR(ttH vs t#bar{t} + ttZ)",
       "MEM_LR_ttH_vs_full_bkg_nomiss_datacard_092016");


}







void plot_MEM_LR_ttH_vs_full_bkg_missing_092016(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_12.9fb.root",
       "MEM LR(ttH vs t#bar{t} + ttZ)",
       "MEM_LR_ttH_vs_full_bkg_missing_datacard_092016");


}






void plot_MEM_LR_ttH_vs_full_bkg_nomiss_constB_092016(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_12.9fb_constB.root",
       "MEM LR(ttH vs t#bar{t} + ttZ)",
       "MEM_LR_ttH_vs_full_bkg_nomiss_datacard_constB_092016");


}







void plot_MEM_LR_ttH_vs_full_bkg_missing_constB_092016(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_12.9fb_constB.root",
       "MEM LR(ttH vs t#bar{t} + ttZ)",
       "MEM_LR_ttH_vs_full_bkg_missing_datacard_constB_092016");


}






void plot_MEM_LR_ttH_vs_full_bkg_nomiss_log_092016(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_12.9fb_log.root",
       "-log(1-MEM LR(ttH vs t#bar{t} + ttZ))",
       "MEM_LR_ttH_vs_full_bkg_nomiss_log_datacard_092016");


}







void plot_MEM_LR_ttH_vs_full_bkg_missing_log_092016(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_12.9fb_log.root",
       "-log(1-MEM LR(ttH vs t#bar{t} + ttZ))",
       "MEM_LR_ttH_vs_full_bkg_missing_log_datacard_092016");


}




void plot_MVA_2lSS_ttV(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MVA_2lSS_ttV_2lSS_1tau_syst_12.9fb.root",
       "MVA(ttH vs ttV)",
       "MVA_2lSS_ttV_datacard");


}




void plot_MVA_2lSS_ttbar(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MVA_2lSS_ttbar_2lSS_1tau_syst_12.9fb.root",
       "MVA(ttH vs t#bar{t})",
       "MVA_2lSS_ttbar_datacard");


}





void plot_MVA_2lSS_ttV_ttbar(){

  plot("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MVA_2lSS_1tau_syst_12.9fb.root",
       "MVA(ttH vs ttV/t#bar{t})",
       "MVA_2lSS_ttV_ttbar_datacard_12.9fb");


}






void plot_MVA_2lSS_ttV_ttbar_CERN(){

  plot_CERN("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacards_CERN/decay_channel_split_datacards_hig16022_12p9fb.r7063/ttH_2lss_1tau.input.root",
       "MVA(ttH vs ttV/t#bar{t})",
       "MVA_2lSS_ttV_ttbar_datacard_12.9fb_CERN");


}
