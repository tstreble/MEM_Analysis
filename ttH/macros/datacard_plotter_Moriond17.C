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
#include <TGraphAsymmErrors.h>

//float luminosity = 35900; //12.9 fb-1
float luminosity = 35900;

using namespace std;


void plot_2lSS(TString datacardname, TString varname, TString plotname, int lumi=0){

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

  TH1F h_Rares = h_fakes;
  h_Rares.Add( (TH1F*)f->Get("x_Rares") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
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

  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);

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


  TLegend* leg=new TLegend(0.6,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  leg->AddEntry(&h_Rares,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);

  cout<<"Bkg="<<h_ttW.Integral()<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttW.Integral(i,i)<<endl;

  cout<<"Sig="<<h_ttH_only.Integral()<<endl;
  for(int i=1;i<h_ttH_only.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttH_only.Integral(i,i)<<endl;


  cout<<"S/sqrt(S+B)"<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++){
    float sig = h_ttH_only.Integral(i,i)/sqrt(h_ttW.Integral(i,i)+h_ttH_only.Integral(i,i));
    cout<<"Bin"<<i<<"="<<sig<<endl;
    //if(sig>0.15)
    //h_data_obs.SetBinContent(i,-10);
  }
  //h_data_obs.SetMinimum(0.5);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  gPad->SetTicks();

  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  //h_ttH.SetMaximum(1.5*max(h_ttH.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  //(&h_data_obs)->Draw("esame");
  (&h_ttH)->Draw("sameaxis");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());

  
  /*TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");*/
  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  if(lumi==0)
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));
  else
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",lumi/1000.));

  h_ttH.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), h_ttH.GetMaximum(), 0.01, h_ttH.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  //Convert absolute range
  double a = (h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1)-h_ttH.GetBinLowEdge(1))/(0.9-0.15);
  double b = h_ttH.GetBinLowEdge(1)-a*0.15;

  pad2->Range(b,-0.3*2/0.7,a+b,2.);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();

  // Define the ratio plot
  TGraphAsymmErrors *h_ratio=new TGraphAsymmErrors();
  h_ratio->Divide(&h_data_obs,&h_ttH,"pois");
  //h_ratio->Divide(&h_ttH,&h_ttH,"pois");

  //TH1F *h_ratio = (TH1F*)h_data_obs.Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  //h_ratio->Sumw2();
  //h_ratio->SetStats(0);      // No statistics on lower plot
  //h_ratio->Divide(&h_ttW);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->SetLineColor(1);
  h_ratio->SetLineWidth(2);
  h_ratio->SetMarkerStyle(20);

  /*for(int i=0;i<h_ratio->GetN();i++){
    double x,y;
    h_ratio->GetPoint(i,x,y);
    if(y==0){
      h_ratio->RemovePoint(i);
      i--;
    }
    }*/
  
  //h_ratio->Draw("ape0");       // Draw the ratio plot

  TGraphAsymmErrors *h_ratio_MC=new TGraphAsymmErrors();
  h_ratio_MC->Divide(&h_ttH,&h_ttH,"pois");
  h_ratio_MC->SetMinimum(0.);  // Define Y ..
  h_ratio_MC->SetMaximum(2.);
  h_ratio_MC->SetLineWidth(0);
  h_ratio_MC->SetFillStyle(3003);  
  //h_ratio_MC->Draw("e2same"); 
  h_ratio_MC->Draw("ae2"); 

  // Y axis histo_emul plot settings
  h_ttH.GetYaxis()->SetTitleSize(20);
  h_ttH.GetYaxis()->SetTitleFont(43);
  h_ttH.GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio_MC->SetTitle(""); // Remove the ratio title
  
  h_ratio_MC->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio_MC->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio_MC->GetYaxis()->SetNdivisions(505);
  h_ratio_MC->GetYaxis()->SetTitleSize(20);
  h_ratio_MC->GetYaxis()->SetTitleFont(43);
  h_ratio_MC->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio_MC->GetXaxis()->SetTitleSize(20);
  h_ratio_MC->GetXaxis()->SetTitleFont(43);
  h_ratio_MC->GetXaxis()->SetTitleOffset(4.);
  h_ratio_MC->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio_MC->GetXaxis()->SetLabelSize(15);
  h_ratio_MC->GetXaxis()->SetTitle(varname);
  h_ratio_MC->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));



  h_ratio->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(20);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle(varname);
  h_ratio->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));

  TLine* line = new TLine(h_data_obs.GetBinLowEdge(1), 1., h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1),1.);
  line->Draw("same");



  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}





void plot_2lSS_faketau(TString datacardname, TString varname, TString plotname, int lumi=0){

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

  TH1F h_Rares = h_fakes;
  h_Rares.Add( (TH1F*)f->Get("x_Rares_gentau") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
  h_WZ.Add( (TH1F*)f->Get("x_EWK_gentau") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_ttZ = h_WZ;
  h_ttZ.Add( (TH1F*)f->Get("x_TTZ_gentau") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("x_TTW_gentau") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hww_gentau") );
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hzz_gentau") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("x_ttH_htt_gentau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH_gentau");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);

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


  TLegend* leg=new TLegend(0.6,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  leg->AddEntry(&h_Rares,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);

  cout<<"Bkg="<<h_ttW.Integral()<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttW.Integral(i,i)<<endl;

  cout<<"Sig="<<h_ttH_only.Integral()<<endl;
  for(int i=1;i<h_ttH_only.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttH_only.Integral(i,i)<<endl;


  cout<<"S/sqrt(S+B)"<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++){
    float sig = h_ttH_only.Integral(i,i)/sqrt(h_ttW.Integral(i,i)+h_ttH_only.Integral(i,i));
    cout<<"Bin"<<i<<"="<<sig<<endl;
    //if(sig>0.15)
    //h_data_obs.SetBinContent(i,-10);
  }
  //h_data_obs.SetMinimum(0.5);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  gPad->SetTicks();

  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  //h_ttH.SetMaximum(1.5*max(h_ttH.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("esame");
  (&h_ttH)->Draw("sameaxis");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());

  
  /*TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");*/
  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  if(lumi==0)
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));
  else
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",lumi/1000.));

  h_ttH.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), h_ttH.GetMaximum(), 0.01, h_ttH.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  //Convert absolute range
  double a = (h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1)-h_ttH.GetBinLowEdge(1))/(0.9-0.15);
  double b = h_ttH.GetBinLowEdge(1)-a*0.15;

  pad2->Range(b,-0.3*2/0.7,a+b,2.);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();

  // Define the ratio plot
  TGraphAsymmErrors *h_ratio=new TGraphAsymmErrors();
  h_ratio->Divide(&h_data_obs,&h_ttH,"pois");
  //h_ratio->Divide(&h_ttH,&h_ttH,"pois");

  //TH1F *h_ratio = (TH1F*)h_data_obs.Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  //h_ratio->Sumw2();
  //h_ratio->SetStats(0);      // No statistics on lower plot
  //h_ratio->Divide(&h_ttW);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->SetLineColor(1);
  h_ratio->SetLineWidth(2);
  h_ratio->SetMarkerStyle(20);

  /*for(int i=0;i<h_ratio->GetN();i++){
    double x,y;
    h_ratio->GetPoint(i,x,y);
    if(y==0){
      h_ratio->RemovePoint(i);
      i--;
    }
    }*/
  
  h_ratio->Draw("ape0");       // Draw the ratio plot

  TGraphAsymmErrors *h_ratio_MC=new TGraphAsymmErrors();
  h_ratio_MC->Divide(&h_ttH,&h_ttH,"pois");
  h_ratio_MC->SetMinimum(0.);  // Define Y ..
  h_ratio_MC->SetMaximum(2.);
  h_ratio_MC->SetLineWidth(0);
  h_ratio_MC->SetFillStyle(3003);  
  h_ratio_MC->Draw("e2same"); 
  //h_ratio_MC->Draw("ae2"); 

  // Y axis histo_emul plot settings
  h_ttH.GetYaxis()->SetTitleSize(20);
  h_ttH.GetYaxis()->SetTitleFont(43);
  h_ttH.GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio_MC->SetTitle(""); // Remove the ratio title
  
  h_ratio_MC->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio_MC->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio_MC->GetYaxis()->SetNdivisions(505);
  h_ratio_MC->GetYaxis()->SetTitleSize(20);
  h_ratio_MC->GetYaxis()->SetTitleFont(43);
  h_ratio_MC->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio_MC->GetXaxis()->SetTitleSize(20);
  h_ratio_MC->GetXaxis()->SetTitleFont(43);
  h_ratio_MC->GetXaxis()->SetTitleOffset(4.);
  h_ratio_MC->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio_MC->GetXaxis()->SetLabelSize(15);
  h_ratio_MC->GetXaxis()->SetTitle(varname);
  h_ratio_MC->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));



  h_ratio->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(20);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle(varname);
  h_ratio->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));

  TLine* line = new TLine(h_data_obs.GetBinLowEdge(1), 1., h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1),1.);
  line->Draw("same");



  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}




void plot_2lSS_syst(TString datacardname, TString varname, TString plotname, int lumi=0, TString syst="tauESUp"){

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

  TH1F h_Rares = h_fakes;
  h_Rares.Add( (TH1F*)f->Get("x_Rares_CMS_ttHl_"+syst) );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
  h_WZ.Add( (TH1F*)f->Get("x_EWK") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_ttZ = h_WZ;
  h_ttZ.Add( (TH1F*)f->Get("x_TTZ_CMS_ttHl_"+syst) );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);


  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("x_TTW_CMS_ttHl_"+syst) );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);


  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hww_CMS_ttHl_"+syst) );
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hzz_CMS_ttHl_"+syst) );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);


  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("x_ttH_htt_CMS_ttHl_"+syst) );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 


  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);

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


  TLegend* leg=new TLegend(0.6,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  leg->AddEntry(&h_Rares,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);

  cout<<"Bkg="<<h_ttW.Integral()<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttW.Integral(i,i)<<endl;

  cout<<"Sig="<<h_ttH_only.Integral()<<endl;
  for(int i=1;i<h_ttH_only.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttH_only.Integral(i,i)<<endl;


  cout<<"S/sqrt(S+B)"<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++){
    float sig = h_ttH_only.Integral(i,i)/sqrt(h_ttW.Integral(i,i)+h_ttH_only.Integral(i,i));
    cout<<"Bin"<<i<<"="<<sig<<endl;
    //if(sig>0.15)
    //h_data_obs.SetBinContent(i,-10);
  }
  //h_data_obs.SetMinimum(0.5);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  gPad->SetTicks();

  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  //h_ttH.SetMaximum(1.5*max(h_ttH.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  //(&h_data_obs)->Draw("esame");
  (&h_ttH)->Draw("sameaxis");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());

  
  /*TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");*/
  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  if(lumi==0)
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));
  else
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",lumi/1000.));

  h_ttH.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), h_ttH.GetMaximum(), 0.01, h_ttH.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  //Convert absolute range
  double a = (h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1)-h_ttH.GetBinLowEdge(1))/(0.9-0.15);
  double b = h_ttH.GetBinLowEdge(1)-a*0.15;

  pad2->Range(b,-0.3*2/0.7,a+b,2.);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();

  // Define the ratio plot
  TGraphAsymmErrors *h_ratio=new TGraphAsymmErrors();
  h_ratio->Divide(&h_data_obs,&h_ttH,"pois");
  //h_ratio->Divide(&h_ttH,&h_ttH,"pois");

  //TH1F *h_ratio = (TH1F*)h_data_obs.Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  //h_ratio->Sumw2();
  //h_ratio->SetStats(0);      // No statistics on lower plot
  //h_ratio->Divide(&h_ttW);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->SetLineColor(1);
  h_ratio->SetLineWidth(2);
  h_ratio->SetMarkerStyle(20);

  /*for(int i=0;i<h_ratio->GetN();i++){
    double x,y;
    h_ratio->GetPoint(i,x,y);
    if(y==0){
      h_ratio->RemovePoint(i);
      i--;
    }
    }*/
  
  //h_ratio->Draw("ape0");       // Draw the ratio plot

  TGraphAsymmErrors *h_ratio_MC=new TGraphAsymmErrors();
  h_ratio_MC->Divide(&h_ttH,&h_ttH,"pois");
  h_ratio_MC->SetMinimum(0.);  // Define Y ..
  h_ratio_MC->SetMaximum(2.);
  h_ratio_MC->SetLineWidth(0);
  h_ratio_MC->SetFillStyle(3003);  
  //h_ratio_MC->Draw("e2same"); 
  h_ratio_MC->Draw("ae2"); 

  // Y axis histo_emul plot settings
  h_ttH.GetYaxis()->SetTitleSize(20);
  h_ttH.GetYaxis()->SetTitleFont(43);
  h_ttH.GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio_MC->SetTitle(""); // Remove the ratio title
  
  h_ratio_MC->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio_MC->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio_MC->GetYaxis()->SetNdivisions(505);
  h_ratio_MC->GetYaxis()->SetTitleSize(20);
  h_ratio_MC->GetYaxis()->SetTitleFont(43);
  h_ratio_MC->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio_MC->GetXaxis()->SetTitleSize(20);
  h_ratio_MC->GetXaxis()->SetTitleFont(43);
  h_ratio_MC->GetXaxis()->SetTitleOffset(4.);
  h_ratio_MC->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio_MC->GetXaxis()->SetLabelSize(15);
  h_ratio_MC->GetXaxis()->SetTitle(varname);
  h_ratio_MC->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));



  h_ratio->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(20);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle(varname);
  h_ratio->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));

  TLine* line = new TLine(h_data_obs.GetBinLowEdge(1), 1., h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1),1.);
  line->Draw("same");



  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}






void plot_2lSS_inverted(TString datacardname, TString varname, TString plotname, int lumi=0){

  TFile* f = TFile::Open(datacardname);

  TH1F h_ttH_boson = *(TH1F*)f->Get("x_ttH_hww");
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hzz") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("x_ttH_htt") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  TH1F h_flips = h_ttH;
  h_flips.Add( (TH1F*)f->Get("x_flips_data"));
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

  TH1F h_Rares = h_fakes;
  h_Rares.Add( (TH1F*)f->Get("x_Rares") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
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



  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);

  TH1F h_ttW_error = h_ttW;
  h_ttW_error.SetFillColor(1);
  h_ttW_error.SetLineWidth(0);
  h_ttW_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("x_data_obs");
  //TH1F h_data_obs = h_ttH;
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();


  TLegend* leg=new TLegend(0.6,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  leg->AddEntry(&h_Rares,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_flips_lines,"Flips");
  
  h_ttW.GetXaxis()->SetTitle(varname);
  h_ttW.GetYaxis()->SetTitle("Events");
  h_ttW.GetYaxis()->SetTitleOffset(1.65);
  h_ttW.SetTitle("");
  h_ttW.SetStats(0);

  /*cout<<"Bkg="<<h_ttW.Integral()<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttW.Integral(i,i)<<endl;

  cout<<"Sig="<<h_ttH_only.Integral()<<endl;
  for(int i=1;i<h_ttH_only.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttH_only.Integral(i,i)<<endl;


  cout<<"S/sqrt(S+B)"<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++){
    float sig = h_ttH_only.Integral(i,i)/sqrt(h_ttW.Integral(i,i)+h_ttH_only.Integral(i,i));
    cout<<"Bin"<<i<<"="<<sig<<endl;
    //if(sig>0.15)
    //h_data_obs.SetBinContent(i,-10);
  }
  //h_data_obs.SetMinimum(0.5);*/


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  gPad->SetTicks();

  //h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  h_ttW.SetMaximum(1.5*max(h_ttW.GetMaximum(),h_ttW.GetMaximum()));
 
  (&h_ttW)->Draw("hist");
  (&h_ttZ)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); 
  (&h_ttH)->Draw("histsame");
  (&h_ttH_boson)->Draw("histsame");

  (&h_ttW_error)->Draw("e2same");
  //(&h_data_obs)->Draw("esame");
  (&h_ttW)->Draw("sameaxis");
  leg->Draw("same");

  h_ttW.GetYaxis()->SetRangeUser(0,1.3*h_ttW.GetMaximum());

  
  /*TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");*/
  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  if(lumi==0)
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));
  else
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",lumi/1000.));

  h_ttW.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_ttW.GetBinLowEdge(1), 0.01, h_ttW.GetBinLowEdge(1), h_ttW.GetMaximum(), 0.01, h_ttW.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  //Convert absolute range
  double a = (h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1)-h_ttW.GetBinLowEdge(1))/(0.9-0.15);
  double b = h_ttW.GetBinLowEdge(1)-a*0.15;

  pad2->Range(b,-0.3*2/0.7,a+b,2.);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();

  // Define the ratio plot
  TGraphAsymmErrors *h_ratio=new TGraphAsymmErrors();
  h_ratio->Divide(&h_data_obs,&h_ttW,"pois");
  //h_ratio->Divide(&h_ttH,&h_ttH,"pois");

  //TH1F *h_ratio = (TH1F*)h_data_obs.Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  //h_ratio->Sumw2();
  //h_ratio->SetStats(0);      // No statistics on lower plot
  //h_ratio->Divide(&h_ttW);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->SetLineColor(1);
  h_ratio->SetLineWidth(2);
  h_ratio->SetMarkerStyle(20);

  /*for(int i=0;i<h_ratio->GetN();i++){
    double x,y;
    h_ratio->GetPoint(i,x,y);
    if(y==0){
      h_ratio->RemovePoint(i);
      i--;
    }
    }*/
  
  //h_ratio->Draw("ape0");       // Draw the ratio plot

  TGraphAsymmErrors *h_ratio_MC=new TGraphAsymmErrors();
  h_ratio_MC->Divide(&h_ttW,&h_ttW,"pois");
  h_ratio_MC->SetMinimum(0.);  // Define Y ..
  h_ratio_MC->SetMaximum(2.);
  h_ratio_MC->SetLineWidth(0);
  h_ratio_MC->SetFillStyle(3003);  
  //h_ratio_MC->Draw("e2same"); 
  h_ratio_MC->Draw("ae2"); 

  // Y axis histo_emul plot settings
  h_ttW.GetYaxis()->SetTitleSize(20);
  h_ttW.GetYaxis()->SetTitleFont(43);
  h_ttW.GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio_MC->SetTitle(""); // Remove the ratio title
  
  h_ratio_MC->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( h_ttW.GetBinLowEdge(1), 0.01, h_ttW.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio_MC->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio_MC->GetYaxis()->SetNdivisions(505);
  h_ratio_MC->GetYaxis()->SetTitleSize(20);
  h_ratio_MC->GetYaxis()->SetTitleFont(43);
  h_ratio_MC->GetYaxis()->SetTitleOffset(1.5);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio_MC->GetXaxis()->SetTitleSize(20);
  h_ratio_MC->GetXaxis()->SetTitleFont(43);
  h_ratio_MC->GetXaxis()->SetTitleOffset(4.);
  h_ratio_MC->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio_MC->GetXaxis()->SetLabelSize(15);
  h_ratio_MC->GetXaxis()->SetTitle(varname);
  h_ratio_MC->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));

  TLine* line = new TLine(h_data_obs.GetBinLowEdge(1), 1., h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1),1.);
  line->Draw("same");



  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}




void plot_2lSS_ttbar_MC(TString datacardname, TString varname, TString plotname){

  TFile* f = TFile::Open(datacardname);

  /*TH1F h_flips = *(TH1F*)f->Get("x_flips_data");
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
  h_fakes_lines.SetFillStyle(3004);*/

  TH1F h_ttbar_DL = *(TH1F*)f->Get("x_ttbar_DL");
  h_ttbar_DL.SetFillColor(13);
  h_ttbar_DL.SetLineColor(kBlack);

  TH1F h_ttbar_SL = h_ttbar_DL;
  h_ttbar_SL.Add( (TH1F*)f->Get("x_ttbar_SL") );
  h_ttbar_SL.SetFillColor(16);
  h_ttbar_SL.SetLineColor(kBlack);

  TH1F h_Rares = h_ttbar_SL;
  h_Rares.Add( (TH1F*)f->Get("x_Rares") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
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

  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);

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


  TLegend* leg=new TLegend(0.6,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  leg->AddEntry(&h_Rares,"Rares");
  //leg->AddEntry(&h_fakes_lines,"Fakes");
  //leg->AddEntry(&h_flips_lines,"Flips");
  leg->AddEntry(&h_ttbar_SL,"t#bar{t} SL");
  leg->AddEntry(&h_ttbar_DL,"t#bar{t} DL");
  
  h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);

  cout<<"Bkg="<<h_ttW.Integral()<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttW.Integral(i,i)<<endl;

  cout<<"Sig="<<h_ttH_only.Integral()<<endl;
  for(int i=1;i<h_ttH_only.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttH_only.Integral(i,i)<<endl;


  cout<<"S/sqrt(S+B)"<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++){
    float sig = h_ttH_only.Integral(i,i)/sqrt(h_ttW.Integral(i,i)+h_ttH_only.Integral(i,i));
    cout<<"Bin"<<i<<"="<<sig<<endl;
    //if(sig>0.15)
    //h_data_obs.SetBinContent(i,-10);
  }
  h_data_obs.SetMinimum(0.5);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  gPad->SetTicks();

  h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  /*(&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  (&h_flips)->Draw("histsame"); 
  (&h_flips_lines)->Draw("histsame"); */
  (&h_ttbar_SL)->Draw("histsame"); 
  (&h_ttbar_DL)->Draw("histsame"); 

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("esame");
  (&h_ttH)->Draw("sameaxis");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());

  
  /*TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");*/
  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));

  h_ttH.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.01, 0, h_ttH.GetMaximum(), 0.01, h_ttH.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();


   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  //Convert absolute range
  double a = (h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1)-h_ttH.GetBinLowEdge(1))/(0.9-0.15);
  double b = h_ttH.GetBinLowEdge(1)-a*0.15;

  pad2->Range(b,-0.3*2/0.7,a+b,2.);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();

  // Define the ratio plot
  TGraphAsymmErrors *h_ratio=new TGraphAsymmErrors();
  h_ratio->Divide(&h_data_obs,&h_ttH,"pois");

  //TH1F *h_ratio = (TH1F*)h_data_obs.Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  //h_ratio->Sumw2();
  //h_ratio->SetStats(0);      // No statistics on lower plot
  //h_ratio->Divide(&h_ttW);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->SetLineColor(1);
  h_ratio->SetLineWidth(2);
  h_ratio->SetMarkerStyle(20);

 for(int i=0;i<h_ratio->GetN();i++){
    double x,y;
    h_ratio->GetPoint(i,x,y);
    if(y==0){
      h_ratio->RemovePoint(i);
      i--;
    }
  }

  h_ratio->Draw("ape0");       // Draw the ratio plot
  

  // Y axis histo_emul plot settings
  h_ttH.GetYaxis()->SetTitleSize(20);
  h_ttH.GetYaxis()->SetTitleFont(43);
  h_ttH.GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(20);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle(varname);
  h_ratio->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));

  TLine* line = new TLine(h_data_obs.GetBinLowEdge(1), 1., h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1),1.);
  line->Draw("same");


  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}






void plot_1l2tau(TString datacardname, TString varname, TString plotname, bool plot_sigx10=false, int lumi=0){

  TFile* f = TFile::Open(datacardname);

  TH1F h_ttH = *(TH1F*)f->Get("x_ttH");
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack);
 
  TH1F h_ttW = h_ttH;
  h_ttW.Add( (TH1F*)f->Get("x_TTW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttZ = h_ttW;
  h_ttZ.Add( (TH1F*)f->Get("x_TTZ") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_WZ = h_ttZ;
  h_WZ.Add( (TH1F*)f->Get("x_EWK") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_Rares = h_WZ;
  h_Rares.Add( (TH1F*)f->Get("x_Rares") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_fakes = h_Rares;
  h_fakes.Add( (TH1F*)f->Get("x_fakes_data"));
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_ttH_error = h_fakes;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);
  h_ttH_only.Scale(10);

  /*TH1F h_fakes = *(TH1F*)f->Get("x_fakes_data");
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_Rares = h_fakes;
  h_Rares.Add( (TH1F*)f->Get("x_Rares") );
  h_Rares.Add( (TH1F*)f->Get("x_WWss") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
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
  h_ttH_error.SetFillStyle(3003);*/


  TH1F h_data_obs = *(TH1F*)f->Get("x_data_obs");
  //TH1F h_data_obs = h_ttH;
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();

  TLegend* leg=new TLegend(0.7,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH");
  //leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  leg->AddEntry(&h_Rares,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  if(plot_sigx10)
    leg->AddEntry(&h_ttH_only,"ttH signal x 10");
  
  /*h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);*/

  h_fakes.GetXaxis()->SetTitle(varname);
  h_fakes.GetYaxis()->SetTitle("Events");
  h_fakes.GetYaxis()->SetTitleSize(20);
  h_fakes.GetYaxis()->SetTitleFont(43);
  h_fakes.GetYaxis()->SetTitleOffset(1.5);
  h_fakes.SetTitle("");
  h_fakes.SetStats(0);


  cout<<"Bkg="<<h_ttW.Integral()<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttW.Integral(i,i)<<endl;

  cout<<"Sig="<<h_ttH_only.Integral()<<endl;
  for(int i=1;i<h_ttH_only.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttH_only.Integral(i,i)<<endl;

  cout<<"S/sqrt(S+B)"<<endl;
  for(int i=1;i<=h_ttW.GetNbinsX();i++){
    float sig = 0.1*h_ttH_only.Integral(i,i)/sqrt(h_ttW.Integral(i,i)+0.1*h_ttH_only.Integral(i,i));
    cout<<"Bin"<<i<<"="<<sig<<endl;
    //if(varname.Contains("m_{vis}(#tau#tau)") && sig>0.15)
    //if(varname.Contains("m_{vis}(#tau#tau)") && i>=6 && i<=12)
    //h_data_obs.SetBinContent(i,0);
    //else if(varname.Contains("BDT") && i>=7)
    if(varname.Contains("Transformed"))
      h_data_obs.SetBinContent(i,0);
    else if(varname.Contains("BDT") && i>=3)
      h_data_obs.SetBinContent(i,0);    
    //if(h_data_obs.GetBinContent(i)==0)
    //h_data_obs.SetBinContent(i,-10);
  }
  //h_data_obs.SetMinimum(0.5);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  gPad->SetTicks();
  gPad->SetLogy();

  //h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  /*(&h_ttH)->Draw("hist");
  //(&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  if(plot_sigx10)
  (&h_ttH_only)->Draw("histsame");*/

  

  //h_fakes.SetMaximum(1.2*max(h_data_obs.GetMaximum(),h_fakes.GetMaximum()));
  h_fakes.SetMaximum(150*max(h_data_obs.GetMaximum(),h_fakes.GetMaximum()));
  h_fakes.SetMinimum(5e-2);  
  (&h_fakes)->Draw("hist");
  (&h_fakes_lines)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttH)->Draw("histsame"); 
  if(plot_sigx10)
    (&h_ttH_only)->Draw("histsame");

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("esame");
  //(&h_ttH)->Draw("sameaxis");
  (&h_fakes)->Draw("sameaxis");
  leg->Draw("same");

  //h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());
  h_fakes.GetYaxis()->SetRangeUser(h_fakes.GetMinimum(),1.3*h_fakes.GetMaximum());
  
  //TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  //tex1->Draw("same");
  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  if(lumi==0)
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));
  else
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",lumi/1000.));
    

  //h_ttH.GetYaxis()->SetLabelSize(0.);
  //TGaxis *axis = new TGaxis( 0, 0.01, 0, h_ttH.GetMaximum(), 0.01, h_ttH.GetMaximum(),510,"");
  h_fakes.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_fakes.GetBinLowEdge(1), 0.01, h_fakes.GetBinLowEdge(1), h_fakes.GetMaximum(), 0.01, h_fakes.GetMaximum(),510,"G");
  //TGaxis *axis = new TGaxis( 0, 0.01, 0, h_fakes.GetMaximum(), 0.01, h_fakes.GetMaximum(),510);
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  //Convert absolute range
  double a = (h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1)-h_ttH.GetBinLowEdge(1))/(0.9-0.15);
  double b = h_ttH.GetBinLowEdge(1)-a*0.15;

  pad2->Range(b,-0.3*2/0.7,a+b,2.);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();  
  gPad->SetLogy(0);

  // Define the ratio plot
  TGraphAsymmErrors *h_ratio=new TGraphAsymmErrors();
  //h_ratio->Divide(&h_data_obs,&h_ttH,"pois");
  h_ratio->Divide(&h_data_obs,&h_fakes,"pois");

  //TH1F *h_ratio = (TH1F*)h_data_obs.Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  //h_ratio->Sumw2();
  //h_ratio->SetStats(0);      // No statistics on lower plot
  //h_ratio->Divide(&h_ttW);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->SetLineColor(1);
  h_ratio->SetLineWidth(2);
  h_ratio->SetMarkerStyle(20);

  /*for(int i=0;i<h_ratio->GetN();i++){
    double x,y;
    h_ratio->GetPoint(i,x,y);
    if(y==0){
      h_ratio->RemovePoint(i);
      i--;
    }
  }*/


  h_ratio->Draw("ape0");       // Draw the ratio plot


  TGraphAsymmErrors *h_ratio_MC=new TGraphAsymmErrors();
  h_ratio_MC->Divide(&h_fakes,&h_fakes,"pois");
  h_ratio_MC->SetLineWidth(0);
  h_ratio_MC->SetFillStyle(3003);  
  h_ratio_MC->Draw("e2same"); 

  // Y axis histo_emul plot settings
  h_ttH.GetYaxis()->SetTitleSize(20);
  h_ttH.GetYaxis()->SetTitleFont(43);
  h_ttH.GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(20);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle(varname);
  h_ratio->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));

  TLine* line = new TLine(h_data_obs.GetBinLowEdge(1), 1., h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1),1.);
  line->Draw("same");



  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");


  return;


}





void plot_1l2tau_ttbar_MC(TString datacardname, TString varname, TString plotname, bool plot_sigx10=false, int lumi=0){

  TFile* f = TFile::Open(datacardname);

  TH1F h_ttH = *(TH1F*)f->Get("x_ttH");
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack);
 
  TH1F h_ttW = h_ttH;
  h_ttW.Add( (TH1F*)f->Get("x_TTW") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttZ = h_ttW;
  h_ttZ.Add( (TH1F*)f->Get("x_TTZ") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_WZ = h_ttZ;
  h_WZ.Add( (TH1F*)f->Get("x_EWK") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_Rares = h_WZ;
  h_Rares.Add( (TH1F*)f->Get("x_Rares") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  /*TH1F h_fakes = h_Rares;
  h_fakes.Add( (TH1F*)f->Get("x_fakes_data"));
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);*/


  TH1F h_ttbar_SL = h_Rares;
  h_ttbar_SL.Add( (TH1F*)f->Get("x_ttbar_SL_fromT") );
  h_ttbar_SL.Add( (TH1F*)f->Get("x_ttbar_SL_fromTbar") );
  h_ttbar_SL.SetFillColor(16);
  h_ttbar_SL.SetLineColor(kBlack);

  TH1F h_ttbar_DL = h_ttbar_SL;
  h_ttbar_DL.Add( (TH1F*)f->Get("x_ttbar_DL") );
  h_ttbar_DL.SetFillColor(13);
  h_ttbar_DL.SetLineColor(kBlack);

  TH1F h_ttH_error = h_ttbar_SL;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);
  h_ttH_only.Scale(10);


  TH1F h_data_obs = *(TH1F*)f->Get("x_data_obs");
  //TH1F h_data_obs = h_ttH;
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();

  TLegend* leg=new TLegend(0.7,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH");
  //leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  leg->AddEntry(&h_Rares,"Rares");
  //leg->AddEntry(&h_fakes_lines,"Fakes");
  leg->AddEntry(&h_ttbar_SL,"ttbar SL");
  leg->AddEntry(&h_ttbar_DL,"ttbar DL");

  if(plot_sigx10)
    leg->AddEntry(&h_ttH_only,"ttH signal x 10");
  
  /*h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);*/

  h_ttbar_DL.GetXaxis()->SetTitle(varname);
  h_ttbar_DL.GetYaxis()->SetTitle("Events");
  h_ttbar_DL.GetYaxis()->SetTitleSize(20);
  h_ttbar_DL.GetYaxis()->SetTitleFont(43);
  h_ttbar_DL.GetYaxis()->SetTitleOffset(1.5);
  h_ttbar_DL.SetTitle("");
  h_ttbar_DL.SetStats(0);


  cout<<"Bkg="<<h_ttW.Integral()<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttW.Integral(i,i)<<endl;

  cout<<"Sig="<<h_ttH_only.Integral()<<endl;
  for(int i=1;i<h_ttH_only.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttH_only.Integral(i,i)<<endl;

  cout<<"S/sqrt(S+B)"<<endl;
  for(int i=1;i<=h_ttW.GetNbinsX();i++){
    float sig = 0.1*h_ttH_only.Integral(i,i)/sqrt(h_ttW.Integral(i,i)+0.1*h_ttH_only.Integral(i,i));
    cout<<"Bin"<<i<<"="<<sig<<endl;
    //if(varname.Contains("m_{vis}(#tau#tau)") && sig>0.15)
    if(varname.Contains("m_{vis}(#tau#tau)") && i>=6 && i<=12)
      h_data_obs.SetBinContent(i,0);
    //else if(varname.Contains("BDT") && i>=7)
    else if(varname.Contains("BDT") && i>=3)
      h_data_obs.SetBinContent(i,0);
    //if(h_data_obs.GetBinContent(i)==0)
    //h_data_obs.SetBinContent(i,-10);
  }
  //h_data_obs.SetMinimum(0.5);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  gPad->SetTicks();
  gPad->SetLogy();

  //h_ttH.SetMaximum(1.5*max(h_data_obs.GetMaximum(),h_ttH.GetMaximum()));
  /*(&h_ttH)->Draw("hist");
  //(&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  if(plot_sigx10)
  (&h_ttH_only)->Draw("histsame");*/

  

  //h_fakes.SetMaximum(1.2*max(h_data_obs.GetMaximum(),h_fakes.GetMaximum()));
  h_ttbar_DL.SetMaximum(100*max(h_data_obs.GetMaximum(),h_ttbar_DL.GetMaximum()));
  h_ttbar_DL.SetMinimum(2e-2);  
  //(&h_fakes)->Draw("hist");
  //(&h_fakes_lines)->Draw("histsame");
  (&h_ttbar_DL)->Draw("hist");
  (&h_ttbar_SL)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttH)->Draw("histsame"); 
  if(plot_sigx10)
    (&h_ttH_only)->Draw("histsame");

  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("esame");
  //(&h_ttH)->Draw("sameaxis");
  (&h_ttbar_DL)->Draw("sameaxis");
  leg->Draw("same");

  //h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());
  h_ttbar_DL.GetYaxis()->SetRangeUser(h_ttbar_DL.GetMinimum(),1.3*h_ttbar_DL.GetMaximum());
  
  //TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  //tex1->Draw("same");
  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  if(lumi==0)
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));
  else
    tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",lumi/1000.));
    

  //h_ttH.GetYaxis()->SetLabelSize(0.);
  //TGaxis *axis = new TGaxis( 0, 0.01, 0, h_ttH.GetMaximum(), 0.01, h_ttH.GetMaximum(),510,"");
  h_ttbar_DL.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_ttbar_DL.GetBinLowEdge(1), 0.01, h_ttbar_DL.GetBinLowEdge(1), h_ttbar_DL.GetMaximum(), 0.01, h_ttbar_DL.GetMaximum(),510,"G");
  //TGaxis *axis = new TGaxis( 0, 0.01, 0, h_fakes.GetMaximum(), 0.01, h_fakes.GetMaximum(),510);
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  //Convert absolute range
  double a = (h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1)-h_ttH.GetBinLowEdge(1))/(0.9-0.15);
  double b = h_ttH.GetBinLowEdge(1)-a*0.15;

  pad2->Range(b,-0.3*2/0.7,a+b,2.);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();  
  gPad->SetLogy(0);

  // Define the ratio plot
  TGraphAsymmErrors *h_ratio=new TGraphAsymmErrors();
  //h_ratio->Divide(&h_data_obs,&h_ttH,"pois");
  h_ratio->Divide(&h_data_obs,&h_ttbar_DL,"pois");

  //TH1F *h_ratio = (TH1F*)h_data_obs.Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  //h_ratio->Sumw2();
  //h_ratio->SetStats(0);      // No statistics on lower plot
  //h_ratio->Divide(&h_ttW);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->SetLineColor(1);
  h_ratio->SetLineWidth(2);
  h_ratio->SetMarkerStyle(20);

  /*for(int i=0;i<h_ratio->GetN();i++){
    double x,y;
    h_ratio->GetPoint(i,x,y);
    if(y==0){
      h_ratio->RemovePoint(i);
      i--;
    }
  }*/

  h_ratio->Draw("ape0");       // Draw the ratio plot
  
  TGraphAsymmErrors *h_ratio_MC=new TGraphAsymmErrors();
  h_ratio_MC->Divide(&h_ttbar_DL,&h_ttbar_DL,"pois");
  h_ratio_MC->SetLineWidth(0);
  h_ratio_MC->SetFillStyle(3003);  
  h_ratio_MC->Draw("e2same"); 

  // Y axis histo_emul plot settings
  h_ttH.GetYaxis()->SetTitleSize(20);
  h_ttH.GetYaxis()->SetTitleFont(43);
  h_ttH.GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(20);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle(varname);
  h_ratio->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));

  TLine* line = new TLine(h_data_obs.GetBinLowEdge(1), 1., h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1),1.);
  line->Draw("same");



  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");


  return;


}








void plot_3l(TString datacardname, TString varname, TString plotname){

  TFile* f = TFile::Open(datacardname);

  TH1F h_fakes = *(TH1F*)f->Get("x_fakes_data");
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_Rares = h_fakes;
  h_Rares.Add( (TH1F*)f->Get("x_Rares") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
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

  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);

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

  TLegend* leg=new TLegend(0.6,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  //leg->AddEntry(&h_Rares,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  
  h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);

  cout<<"Bkg="<<h_ttW.Integral()<<endl;
  for(int i=0;i<=h_ttW.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttW.Integral(i,i)<<endl;

  cout<<"Sig="<<h_ttH_only.Integral()<<endl;
  for(int i=0;i<=h_ttH_only.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttH_only.Integral(i,i)<<endl;


  cout<<"S/sqrt(S+B)"<<endl;
  for(int i=0;i<=h_ttW.GetNbinsX();i++){
    float sig = h_ttH_only.Integral(i,i)/sqrt(h_ttW.Integral(i,i)+h_ttH_only.Integral(i,i));
    cout<<"Bin"<<i<<"="<<sig<<endl;
  }


  cout<<"S/B"<<endl;
  for(int i=0;i<=h_ttW.GetNbinsX();i++){
    float sig = h_ttH_only.Integral(i,i)/h_ttW.Integral(i,i);
    cout<<"Bin"<<i<<"="<<sig<<endl;
  }
  h_data_obs.SetMinimum(0.5);
  h_data_obs.SetBinErrorOption(TH1::kPoisson);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  gPad->SetTicks();

  h_ttH.SetMaximum(1.5*(max(h_data_obs.GetMaximum(),h_ttH.GetMaximum())+h_data_obs.GetBinError(1)));
  //h_ttH.SetMaximum(1.5*(max(h_ttH.GetMaximum(),h_ttH.GetMaximum())));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_fakes)->Draw("histsame"); 
  (&h_fakes_lines)->Draw("histsame"); 
  //(&h_ttH_only)->Draw("histsame");


  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("esame");
  (&h_ttH)->Draw("sameaxis");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());
  
  /*TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");*/
  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));


  h_ttH.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), h_ttH.GetMaximum(), 0.01, h_ttH.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  //Convert absolute range
  double a = (h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1)-h_ttH.GetBinLowEdge(1))/(0.9-0.15);
  double b = h_ttH.GetBinLowEdge(1)-a*0.15;

  pad2->Range(b,-0.3*2/0.7,a+b,2.);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();

  // Define the ratio plot
  TGraphAsymmErrors *h_ratio=new TGraphAsymmErrors();
  h_ratio->Divide(&h_data_obs,&h_ttH,"pois");
  //h_ratio->Divide(&h_ttH,&h_ttH,"pois");

  //TH1F *h_ratio = (TH1F*)h_data_obs.Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  //h_ratio->Sumw2();
  //h_ratio->SetStats(0);      // No statistics on lower plot
  //h_ratio->Divide(&h_ttW);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->SetLineColor(1);
  h_ratio->SetLineWidth(2);
  h_ratio->SetMarkerStyle(20);

  /*for(int i=0;i<h_ratio->GetN();i++){
    double x,y;
    h_ratio->GetPoint(i,x,y);  
    if(y==0){
      h_ratio->RemovePoint(i);
      i--;
    }
    }*/

  h_ratio->Draw("ape0");       // Draw the ratio plot
  
  TGraphAsymmErrors *h_ratio_MC=new TGraphAsymmErrors();
  h_ratio_MC->Divide(&h_ttH,&h_ttH,"pois");
  h_ratio_MC->SetMinimum(0.);  // Define Y ..
  h_ratio_MC->SetMaximum(2.);
  h_ratio_MC->SetLineWidth(0);
  h_ratio_MC->SetFillStyle(3003);  
  h_ratio_MC->Draw("e2same"); 
  //h_ratio_MC->Draw("ae2"); 

  // Y axis histo_emul plot settings
  h_ttH.GetYaxis()->SetTitleSize(20);
  h_ttH.GetYaxis()->SetTitleFont(43);
  h_ttH.GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio_MC->SetTitle(""); // Remove the ratio title
  
  h_ratio_MC->GetYaxis()->SetLabelSize(0.);
  h_ratio->SetTitle(""); // Remove the ratio title
  	 
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio_MC->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio_MC->GetYaxis()->SetNdivisions(505);
  h_ratio_MC->GetYaxis()->SetTitleSize(20);
  h_ratio_MC->GetYaxis()->SetTitleFont(43);
  h_ratio_MC->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio_MC->GetXaxis()->SetTitleSize(20);
  h_ratio_MC->GetXaxis()->SetTitleFont(43);
  h_ratio_MC->GetXaxis()->SetTitleOffset(4.);
  h_ratio_MC->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio_MC->GetXaxis()->SetLabelSize(15);
  h_ratio_MC->GetXaxis()->SetTitle(varname);
  h_ratio_MC->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));



  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(20);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle(varname);
  h_ratio->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));



  TLine* line = new TLine(h_data_obs.GetBinLowEdge(1), 1., h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1),1.);
  line->Draw("same");

  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");



  return;


}







void plot_3l_ttZ_CR(TString datacardname, TString varname, TString plotname){

  TFile* f = TFile::Open(datacardname);

  TH1F h_fakes = *(TH1F*)f->Get("x_fakes_data");
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_Rares = h_fakes;
  h_Rares.Add( (TH1F*)f->Get("x_Rares") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
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

  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);

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

  TLegend* leg=new TLegend(0.6,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  leg->AddEntry(&h_Rares,"Rares");
  leg->AddEntry(&h_fakes,"Fakes");
  
  h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);

  cout<<"Bkg="<<h_ttW.Integral()<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttW.Integral(i,i)<<endl;

  cout<<"Sig="<<h_ttH_only.Integral()<<endl;
  for(int i=1;i<h_ttH_only.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttH_only.Integral(i,i)<<endl;


  cout<<"S/sqrt(S+B)"<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++){
    float sig = 0.1*h_ttH_only.Integral(i,i)/sqrt(h_ttW.Integral(i,i)+0.1*h_ttH_only.Integral(i,i));
    cout<<"Bin"<<i<<"="<<sig<<endl;
    //if(sig>0.15)
    //h_data_obs.SetBinContent(i,-10);
  }
  h_data_obs.SetMinimum(0.5);
  h_data_obs.SetBinErrorOption(TH1::kPoisson);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  gPad->SetTicks();
  gPad->SetLogy();

  //h_ttH.SetMaximum(1.5*(max(h_data_obs.GetMaximum(),h_ttH.GetMaximum())+h_data_obs.GetBinError(1)));
  //h_ttH.SetMaximum(1.5*(max(h_ttH.GetMaximum(),h_ttH.GetMaximum())));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_fakes)->Draw("histsame");
  (&h_fakes_lines)->Draw("histsame");
  //(&h_ttH_only)->Draw("histsame");


  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("esame");
  (&h_ttH)->Draw("sameaxis");
  leg->Draw("same");

  //h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());
  h_ttH.GetYaxis()->SetRangeUser(1e-1,1e3);
  
  /*TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");*/
  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));


  h_ttH.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), h_ttH.GetMaximum(), 0.01, h_ttH.GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();


   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  //Convert absolute range
  double a = (h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1)-h_ttH.GetBinLowEdge(1))/(0.9-0.15);
  double b = h_ttH.GetBinLowEdge(1)-a*0.15;

  pad2->Range(b,-0.3*2/0.7,a+b,2.);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();

  // Define the ratio plot
  TGraphAsymmErrors *h_ratio=new TGraphAsymmErrors();
  h_ratio->Divide(&h_data_obs,&h_ttH,"pois");
  //h_ratio->Divide(&h_ttH,&h_ttH,"pois");

  //TH1F *h_ratio = (TH1F*)h_data_obs.Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  //h_ratio->Sumw2();
  //h_ratio->SetStats(0);      // No statistics on lower plot
  //h_ratio->Divide(&h_ttW);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->SetLineColor(1);
  h_ratio->SetLineWidth(2);
  h_ratio->SetMarkerStyle(20);

  /*for(int i=0;i<h_ratio->GetN();i++){
    double x,y;
    h_ratio->GetPoint(i,x,y);  
    if(y==0){
      h_ratio->RemovePoint(i);
      i--;
    }
    }*/

  h_ratio->Draw("ape0");       // Draw the ratio plot
  
  TGraphAsymmErrors *h_ratio_MC=new TGraphAsymmErrors();
  h_ratio_MC->Divide(&h_ttH,&h_ttH,"pois");
  h_ratio_MC->SetMinimum(0.);  // Define Y ..
  h_ratio_MC->SetMaximum(2.);
  h_ratio_MC->SetLineWidth(0);
  h_ratio_MC->SetFillStyle(3003);  
  h_ratio_MC->Draw("e2same"); 
  //h_ratio_MC->Draw("ae2"); 

  // Y axis histo_emul plot settings
  h_ttH.GetYaxis()->SetTitleSize(20);
  h_ttH.GetYaxis()->SetTitleFont(43);
  h_ttH.GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio_MC->SetTitle(""); // Remove the ratio title
  
  h_ratio_MC->GetYaxis()->SetLabelSize(0.);
  h_ratio->SetTitle(""); // Remove the ratio title
  	 
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio_MC->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio_MC->GetYaxis()->SetNdivisions(505);
  h_ratio_MC->GetYaxis()->SetTitleSize(20);
  h_ratio_MC->GetYaxis()->SetTitleFont(43);
  h_ratio_MC->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio_MC->GetXaxis()->SetTitleSize(20);
  h_ratio_MC->GetXaxis()->SetTitleFont(43);
  h_ratio_MC->GetXaxis()->SetTitleOffset(4.);
  h_ratio_MC->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio_MC->GetXaxis()->SetLabelSize(15);
  h_ratio_MC->GetXaxis()->SetTitle(varname);
  h_ratio_MC->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));



  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(20);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle(varname);
  h_ratio->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));



  TLine* line = new TLine(h_data_obs.GetBinLowEdge(1), 1., h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1),1.);
  line->Draw("same");

  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");




  return;


}






void plot_3l_ttZ_CR_faketau(TString datacardname, TString varname, TString plotname){

  TFile* f = TFile::Open(datacardname);

  TH1F h_fakes = *(TH1F*)f->Get("x_fakes_data");
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_Rares = h_fakes;
  h_Rares.Add( (TH1F*)f->Get("x_Rares_gentau") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
  h_WZ.Add( (TH1F*)f->Get("x_EWK_gentau") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_ttZ = h_WZ;
  h_ttZ.Add( (TH1F*)f->Get("x_TTZ_gentau") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("x_TTW_gentau") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hww_gentau") );
  h_ttH_boson.Add( (TH1F*)f->Get("x_ttH_hzz_gentau") );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("x_ttH_htt_gentau") );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH_gentau");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);

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

  TLegend* leg=new TLegend(0.6,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
  leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"WZ");
  leg->AddEntry(&h_Rares,"Rares");
  leg->AddEntry(&h_fakes,"Fakes");
  
  h_ttH.GetXaxis()->SetTitle(varname);
  h_ttH.GetYaxis()->SetTitle("Events");
  h_ttH.GetYaxis()->SetTitleOffset(1.65);
  h_ttH.SetTitle("");
  h_ttH.SetStats(0);

  cout<<"Bkg="<<h_ttW.Integral()<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttW.Integral(i,i)<<endl;

  cout<<"Sig="<<h_ttH_only.Integral()<<endl;
  for(int i=1;i<h_ttH_only.GetNbinsX();i++)
    cout<<"Bin"<<i<<"="<<h_ttH_only.Integral(i,i)<<endl;


  cout<<"S/sqrt(S+B)"<<endl;
  for(int i=1;i<h_ttW.GetNbinsX();i++){
    float sig = 0.1*h_ttH_only.Integral(i,i)/sqrt(h_ttW.Integral(i,i)+0.1*h_ttH_only.Integral(i,i));
    cout<<"Bin"<<i<<"="<<sig<<endl;
    //if(sig>0.15)
    //h_data_obs.SetBinContent(i,-10);
  }
  h_data_obs.SetMinimum(0.5);
  h_data_obs.SetBinErrorOption(TH1::kPoisson);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  gPad->SetTicks();

  h_ttH.SetMaximum(1.5*(max(h_data_obs.GetMaximum(),h_ttH.GetMaximum())+h_data_obs.GetBinError(1)));
  //h_ttH.SetMaximum(1.5*(max(h_ttH.GetMaximum(),h_ttH.GetMaximum())));
  (&h_ttH)->Draw("hist");
  (&h_ttH_boson)->Draw("histsame");
  (&h_ttW)->Draw("histsame");
  (&h_ttZ)->Draw("histsame");
  (&h_WZ)->Draw("histsame");
  (&h_Rares)->Draw("histsame");
  (&h_fakes)->Draw("histsame");
  (&h_fakes_lines)->Draw("histsame");
  //(&h_ttH_only)->Draw("histsame");


  (&h_ttH_error)->Draw("e2same");
  (&h_data_obs)->Draw("esame");
  (&h_ttH)->Draw("sameaxis");
  leg->Draw("same");

  h_ttH.GetYaxis()->SetRangeUser(0,1.3*h_ttH.GetMaximum());
  
  /*TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");*/
  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  tex.DrawLatexNDC(0.72,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));


  h_ttH.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), h_ttH.GetMaximum(), 0.01, h_ttH.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();


   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  
  //Convert absolute range
  double a = (h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1)-h_ttH.GetBinLowEdge(1))/(0.9-0.15);
  double b = h_ttH.GetBinLowEdge(1)-a*0.15;

  pad2->Range(b,-0.3*2/0.7,a+b,2.);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  gStyle->SetEndErrorSize(0);
  gPad->SetTicks();

  // Define the ratio plot
  TGraphAsymmErrors *h_ratio=new TGraphAsymmErrors();
  h_ratio->Divide(&h_data_obs,&h_ttH,"pois");
  //h_ratio->Divide(&h_ttH,&h_ttH,"pois");

  //TH1F *h_ratio = (TH1F*)h_data_obs.Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  //h_ratio->Sumw2();
  //h_ratio->SetStats(0);      // No statistics on lower plot
  //h_ratio->Divide(&h_ttW);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->SetLineColor(1);
  h_ratio->SetLineWidth(2);
  h_ratio->SetMarkerStyle(20);

  /*for(int i=0;i<h_ratio->GetN();i++){
    double x,y;
    h_ratio->GetPoint(i,x,y);  
    if(y==0){
      h_ratio->RemovePoint(i);
      i--;
    }
    }*/

  h_ratio->Draw("ape0");       // Draw the ratio plot
  
  TGraphAsymmErrors *h_ratio_MC=new TGraphAsymmErrors();
  h_ratio_MC->Divide(&h_ttH,&h_ttH,"pois");
  h_ratio_MC->SetMinimum(0.);  // Define Y ..
  h_ratio_MC->SetMaximum(2.);
  h_ratio_MC->SetLineWidth(0);
  h_ratio_MC->SetFillStyle(3003);  
  h_ratio_MC->Draw("e2same"); 
  //h_ratio_MC->Draw("ae2"); 

  // Y axis histo_emul plot settings
  h_ttH.GetYaxis()->SetTitleSize(20);
  h_ttH.GetYaxis()->SetTitleFont(43);
  h_ttH.GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio_MC->SetTitle(""); // Remove the ratio title
  
  h_ratio_MC->GetYaxis()->SetLabelSize(0.);
  h_ratio->SetTitle(""); // Remove the ratio title
  	 
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( h_ttH.GetBinLowEdge(1), 0.01, h_ttH.GetBinLowEdge(1), 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio_MC->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio_MC->GetYaxis()->SetNdivisions(505);
  h_ratio_MC->GetYaxis()->SetTitleSize(20);
  h_ratio_MC->GetYaxis()->SetTitleFont(43);
  h_ratio_MC->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio_MC->GetXaxis()->SetTitleSize(20);
  h_ratio_MC->GetXaxis()->SetTitleFont(43);
  h_ratio_MC->GetXaxis()->SetTitleOffset(4.);
  h_ratio_MC->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio_MC->GetXaxis()->SetLabelSize(15);
  h_ratio_MC->GetXaxis()->SetTitle(varname);
  h_ratio_MC->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));



  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Data/Pred.");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(20);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle(varname);
  h_ratio->GetXaxis()->SetLimits(h_data_obs.GetBinLowEdge(1),h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1));



  TLine* line = new TLine(h_data_obs.GetBinLowEdge(1), 1., h_data_obs.GetBinLowEdge(h_data_obs.GetNbinsX()+1),1.);
  line->Draw("same");

  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");




  return;


}







void plot_min_mvis_2lSS_nofaketau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_min_mvis_2lss1tau_syst_35.9fb_012017.root",
       "Min(m_{vis}(l#tau))",
       "min_mvis_datacard_nofaketau_359fb");


}




void plot_MVA_2lSS_nofaketau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MVA_2lSS_allcat_syst_nofaketau_35.9fb.root",
       "MVA(ttH vs ttV/t#bar{t})",
       "MVA_2lSS_ttV_ttbar_datacard_nofaketau_359fb");


}





void plot_MVA_2lSS_ttbar_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MVA_2lSS_ttbar_syst_nofaketau_35.9fb.root",
       "MVA(ttH vs t#bar{t})",
       "MVA_2lSS_ttbar_datacard_nofaketau_359fb");


}




void plot_MVA_2lSS_ttV_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MVA_2lSS_ttV_syst_nofaketau_35.9fb.root",
       "MVA(ttH vs ttV)",
       "MVA_2lSS_ttV_datacard_nofaketau_359fb");


}




/*void plot_MVA_3l_nofaketau_012017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MVA_3l_syst_nofaketau_35.9fb.root",
       "MVA(ttH vs ttV/t#bar{t})",
       "3l1tau_Moriond/MVA_3l_ttV_ttbar_datacard_nofaketau_359fb");


       }*/






void plot_MVA_3l_nofaketau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MVA_3l_syst_nofaketau_35.9fb_022017.root",
       "MVA(ttH vs ttV/t#bar{t})",
       "3l1tau_Moriond/MVA_3l_ttV_ttbar_datacard_nofaketau_359fb_022017");


}




/*void plot_MVA_3l_ttbar_012017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MVA_3l_ttbar_nofaketau_35.9fb.root",
       "MVA(ttH vs t#bar{t})",
       "3l1tau_Moriond/MVA_3l_ttbar_datacard_nofaketau_359fb");


}


void plot_MVA_3l_ttV_012017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MVA_3l_ttV_nofaketau_35.9fb.root",
       "MVA(ttH vs ttV)",
       "3l1tau_Moriond/MVA_3l_ttV_datacard_nofaketau_359fb");


       }*/





void plot_MVA_3l_ttbar_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MVA_3l_ttbar_nofaketau_35.9fb_022017.root",
       "MVA(ttH vs t#bar{t})",
       "3l1tau_Moriond/MVA_3l_ttbar_datacard_nofaketau_359fb_022017");


}


void plot_MVA_3l_ttV_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MVA_3l_ttV_nofaketau_35.9fb_022017.root",
       "MVA(ttH vs ttV)",
       "3l1tau_Moriond/MVA_3l_ttV_datacard_nofaketau_359fb_022017");


}


 
void plot_MEM_int_type_2lSS_nofaketau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_int_type_2lSS_nofaketau_35.9fb.root",
            "MEM subcategory",
            "MEM_int_type_2lSS_datacard_359fb_012017");

}



void plot_MEM_int_type_2lSS_nofaketau_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_int_type_2lSS_nofaketau_35.9fb_012017.root",
            "MEM subcategory",
            "2lss1tau_Moriond/MEM_int_type_2lSS_datacard_359fb_022017");

}




void plot_MEM_int_type_2lss1tau_SStau_CR_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_int_type_2lss1tau_syst_35.9fb_SStau_CR_022017.root",
	      "MEM subcategory",
	      "MEM_int_type_2lss1tau_datacard_SStau_CR_359fb");

}




void plot_n_recotauh_2lss1tau_SStau_CR_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_recotauh_2lSS_SStau_CR_syst_35.9fb_022017.root",
	      "Number of fakeable #tau_{h}",
	      "n_tau_2lss1tau_datacard_SStau_CR_359fb");

}






void plot_n_recotauh_2lss1tau_SStau_CR_faketau_022017(){

  plot_2lSS_faketau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_recotauh_2lSS_SStau_CR_faketau_syst_35.9fb_022017.root",
	      "Number of fakeable #tau_{h}",
	      "n_tau_2lss1tau_datacard_SStau_CR_faketau_359fb");

}




void plot_MEM_2lSS_nofaketau_nomiss_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_2lSS_nomiss_datacard_359fb_012017");

}



void plot_MEM_2lSS_nofaketau_nomiss_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_012017.root",
            "MEM_LR",
            "2lss1tau_Moriond/MEM_LR_2lSS_nomiss_datacard_359fb_022017");

}


void plot_MEM_2lSS_nofaketau_missing_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root",
            "MEM_LR",
            "2lss1tau_Moriond/MEM_LR_2lSS_missing_datacard_359fb_022017");

}




void plot_MEM_2lSS_nofaketau_missing_022017_TESUp(){

  plot_2lSS_syst("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root",
            "MEM_LR",
		 "MEM_LR_2lSS_missing_datacard_359fb_022017_TESUp",0,"tauESUp");

}


void plot_MEM_2lSS_nofaketau_missing_022017_TESDown(){

  plot_2lSS_syst("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root",
            "MEM_LR",
		 "MEM_LR_2lSS_missing_datacard_359fb_022017_TESDown",0,"tauESDown");

}





void plot_MEM_2lSS_nofaketau_missing_022017_JESUp(){

  plot_2lSS_syst("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root",
            "MEM_LR",
		 "MEM_LR_2lSS_missing_datacard_359fb_022017_JESUp",0,"JESUp");

}


void plot_MEM_2lSS_nofaketau_missing_022017_JESDown(){

  plot_2lSS_syst("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_012017.root",
            "MEM_LR",
		 "MEM_LR_2lSS_missing_datacard_359fb_022017_JESDown",0,"JESDown");

}






void plot_transfMEM_2lSS_nofaketau_nomiss_022017(){

  plot_2lSS_inverted("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_transfBDT_2lSS_nomiss_nofaketau_35.9fb_012017.root",
            "Transformed MEM LR",
            "transfMEM_LR_2lSS_nomiss_datacard_359fb_022017");

}


void plot_transfMEM_2lSS_nofaketau_missing_022017(){

  plot_2lSS_inverted("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_transfBDT_2lSS_missing_nofaketau_35.9fb_012017.root",
            "Transformed MEM LR",
            "transfMEM_LR_2lSS_missing_datacard_359fb_022017");

}



void plot_MEM_2lSS_nofaketau_nomiss_112016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb.root",
	    "MEM_LR",
	    "MEM_LR_2lSS_nomiss_datacard_359fb_012017");

}






void plot_MEM_ttH_weight_2lSS_nofaketau_nomiss_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_weight_2lSS_nomiss_nofaketau_35.9fb.root",
	    "log(w(ttH))",
	    "MEM_ttH_weight_2lSS_nomiss_datacard_35.9fb_012017");

}






void plot_MEM_ttH_weight_2lSS_nofaketau_missing_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_weight_2lSS_missing_nofaketau_35.9fb.root",
	    "log(w(ttH))",
	    "MEM_ttH_weight_2lSS_missing_datacard_359fb_012017");

}


void plot_MEM_2lSS_nofaketau_missing_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_2lSS_missing_datacard_359fb_012017");

}


void plot_MEM_2lSS_nofaketau_missing_SStau_CR_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_SStau_CR_012017.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_2lSS_missing_datacard_359fb_SStau_CR_012017");

}




void plot_MEM_2lSS_nofaketau_nomiss_missing_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_missing_nofaketau_35.9fb.root",
       "MEM_LR",
       "MEM_LR_2lSS_nomiss_missing_datacard_359fb_012017");


}




void plot_BDT_2lSS1tau_2Dbin_nofaketau(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MVA_2Dbin_2lSS1tau_nofaketau_35.9fb_012017.root",
	    "BDT(ttH vs ttV/t#bar{t}) bin",
	    "BDT_2lSS1tau_2Dbin_datacard_359fb_012017");

}




void plot_BDT_MEM_LR_2lSS1tau_2Dbin_nofaketau(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MVA_MEM_LR_2Dbin_2lSS1tau_nofaketau_35.9fb_012017.root",
	    "BDT(ttH vs ttV/t#bar{t}) bin",
	    "BDT_MEM_LR_2lSS1tau_2Dbin_datacard_359fb_012017");

}



void plot_mvis_1l2tau_ICHEP_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_mvis_1l2tau_syst_12.9fb_012017.root",
	      "m_{vis}(#tau#tau)",
	      "mvis_1l2tau_datacard_12.9fb_012017");

}





void plot_mvis_1l2tau_112016(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_mvis_1l2tau_syst_12.9fb_112016.root",
	      "m_{vis}(#tau#tau)",
	      "mvis_1l2tau_datacard_12.9fb",true,12900);

}








/*void plot_mvis_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_mvis_1l2tau_syst_35.9fb_pt30_012017.root",
	      "m_{vis}(#tau#tau) [GeV]",
	      "1l2tau_Moriond/mvis_1l2tau_datacard_359fb");

}*/




void plot_mvis_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_mvis_1l2tau_syst_35.9fb_pt30_012017.root",
	      "m_{vis}(#tau#tau) [GeV]",
	      "1l2tau_Moriond/mvis_1l2tau_datacard_359fb");

}




void plot_mvis_1l2tau_022017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_mvis_1l2tau_syst_35.9fb_012017.root",
	      "m_{vis}(#tau#tau) [GeV]",
	      "mvis_1l2tau_datacard_359fb_022017");

}




void plot_BDT_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_BDT_1l2tau_syst_35.9fb_pt30_012017.root",
	      "BDT output",
	      "1l2tau_Moriond/BDT_1l2tau_datacard_359fb_012017");

}





void plot_BDT_1l2tau_022017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_BDT_1l2tau_syst_35.9fb_012017.root",
	      "BDT output",
	      "1l2tau_Moriond/BDT_1l2tau_datacard_359fb_022017");

}





void plot_BDT_1l2tau_022017_ttbar_MC(){

  plot_1l2tau_ttbar_MC("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_BDT_1l2tau_syst_35.9fb_012017.root",
	      "BDT output",
	      "BDT_1l2tau_datacard_359fb_022017_ttbar_MC");

}






void plot_BDT_1l2tau_40bins_022017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_BDT_1l2tau_syst_35.9fb_012017_40bins.root",
	      "BDT output",
	      "BDT_1l2tau_datacard_359fb_022017_40bins");

}



void plot_BDT_1l2tau_40bins_ttbarMC_022017(){

  plot_1l2tau_ttbar_MC("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_BDT_1l2tau_syst_35.9fb_012017_40bins.root",
	      "BDT output",
	      "BDT_1l2tau_datacard_359fb_022017_40bins_ttbar_MC");

}





void plot_transfBDT_1l2tau_022017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_transfBDT_1l2tau_syst_35.9fb_012017.root",
	      "Transformed BDT output",
	      "transfBDT_1l2tau_datacard_359fb_022017");

}





void plot_transfBDT_1l2tau_022017_ttbar_MC(){

  plot_1l2tau_ttbar_MC("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_transfBDT_1l2tau_syst_35.9fb_012017.root",
	      "Transformed BDT output",
	      "transfBDT_1l2tau_datacard_359fb_022017_ttbar_MC");

}







void plot_BDT_1l2tau_022017_mergelast(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_BDT_1l2tau_syst_35.9fb_012017_mergelast.root",
	      "BDT output",
	      "BDT_1l2tau_datacard_359fb_022017_mergelast");

}




void plot_BDT_1l2tau_022017_altlast(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_BDT_1l2tau_syst_35.9fb_012017_altlast.root",
	      "BDT output",
	      "BDT_1l2tau_datacard_359fb_022017_altlast");

}





void plot_mvis_1l2tau_012017_ttbar_MC(){

  plot_1l2tau_ttbar_MC("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_mvis_1l2tau_syst_35.9fb_012017.root",
	      "m_{vis}(#tau#tau) [GeV]",
	      "1l2tau_Moriond/mvis_1l2tau_ttbar_MC_datacard_359fb", true);

}




void plot_nvtx_1l2tau_012017_ttbar_MC(){

  plot_1l2tau_ttbar_MC("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_nvtx_1l2tau_syst_35.9fb_012017.root",
	      "N(vertex)",
	      "1l2tau_Moriond/nvtx_1l2tau_ttbar_MC_datacard_359fb", true);

}




void plot_nvtx_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_nvtx_1l2tau_syst_35.9fb_012017.root",
	      "N(vertex)",
	      "1l2tau_Moriond/nvtx_1l2tau_datacard_359fb", true);

}



void plot_n_fakelep_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_fakelep_1l2tau_syst_35.9fb_012017.root",
	      "Number of fakeable leptons",
	      "1l2tau_Moriond/n_fakelep_1l2tau_datacard_359fb");

}




void plot_n_fakeele_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_fakeele_1l2tau_syst_35.9fb_012017.root",
	      "Number of fakeable electrons",
	      "1l2tau_Moriond/n_fakeele_1l2tau_datacard_359fb");

}



void plot_n_fakemu_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_fakemu_1l2tau_syst_35.9fb_012017.root",
	      "Number of fakeable muons",
	      "1l2tau_Moriond/n_fakemu_1l2tau_datacard_359fb");

}




void plot_n_faketau_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_faketau_1l2tau_syst_35.9fb_012017.root",
	      "Number of fakeable #tau_{h}",
	      "1l2tau_Moriond/n_faketau_1l2tau_datacard_359fb");

}





void plot_n_jet_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_jet_1l2tau_syst_35.9fb_012017.root",
	      "N(jet, p_{T}>25 GeV)",
	      "1l2tau_Moriond/n_jet_1l2tau_datacard_359fb");

}


void plot_n_jet_CSVloose_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_jet_CSVloose_1l2tau_syst_35.9fb_012017.root",
	      "N(jet, p_{T}>25 GeV, CSVL)",
	      "1l2tau_Moriond/n_jet_CSVL_1l2tau_datacard_359fb");

}







void plot_n_jet_CSVmedium_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_jet_CSVmedium_1l2tau_syst_35.9fb_012017.root",
	      "N(jet, p_{T}>25 GeV, CSVM)",
	      "1l2tau_Moriond/n_jet_CSVM_1l2tau_datacard_359fb");

}




void plot_MET_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_ETmiss_1l2tau_syst_35.9fb_012017.root",
	      "E_{T}^{miss} [GeV]",
	      "1l2tau_Moriond/MET_1l2tau_datacard_359fb");

}





void plot_pT_lep_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_lep_1l2tau_syst_35.9fb_012017.root",
	      "Lepton p_{T} [GeV]",
	      "1l2tau_Moriond/pT_lep_1l2tau_datacard_359fb");

}




void plot_pT_ele_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_ele_1l2tau_syst_35.9fb_012017.root",
	      "Electron p_{T} [GeV]",
	      "1l2tau_Moriond/pT_ele_1l2tau_datacard_359fb");

}




void plot_pT_mu_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_mu_1l2tau_syst_35.9fb_012017.root",
	      "Muon p_{T} [GeV]",
	      "1l2tau_Moriond/pT_mu_1l2tau_datacard_359fb");

}



void plot_pT_lep_1l2tau_012017_ttbar_MC(){

  plot_1l2tau_ttbar_MC("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_lep_1l2tau_syst_35.9fb_012017.root",
	      "Lepton p_{T} [GeV]",
	      "1l2tau_Moriond/pT_lep_1l2tau_ttbar_MC_datacard_359fb");

}




void plot_pT_tau1_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_tau1_1l2tau_syst_35.9fb_012017.root",
	      "Leading #tau_{h} p_{T} [GeV]",
	      "1l2tau_Moriond/pT_tau1_1l2tau_datacard_359fb");

}




void plot_DM_tau1_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_DM_tau1_1l2tau_syst_35.9fb_012017.root",
	      "Leading #tau_{h} decay mode",
	      "1l2tau_Moriond/DM_tau1_1l2tau_datacard_359fb");

}




void plot_pT_tau2_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_tau2_1l2tau_syst_35.9fb_012017.root",
	      "Subleading #tau_{h} p_{T} [GeV]",
	      "1l2tau_Moriond/pT_tau2_1l2tau_datacard_359fb");


}




void plot_DM_tau2_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_DM_tau2_1l2tau_syst_35.9fb_012017.root",
	      "Subleading #tau_{h} decay mode",
	      "1l2tau_Moriond/DM_tau2_1l2tau_datacard_359fb");

}



void plot_pT_jet1_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_jet1_1l2tau_syst_35.9fb_012017.root",
	      "Leading jet p_{T} [GeV]",
	      "1l2tau_Moriond/pT_jet1_1l2tau_datacard_359fb");


}


void plot_pT_jet2_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_jet2_1l2tau_syst_35.9fb_012017.root",
	      "Subleading jet p_{T} [GeV]",
	      "1l2tau_Moriond/pT_jet2_1l2tau_datacard_359fb");


}


void plot_CSV_jet1_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_CSV_jet1_1l2tau_syst_35.9fb_012017.root",
	      "Leading jet CSV score",
	      "1l2tau_Moriond/CSV_jet1_1l2tau_datacard_359fb");

}



void plot_CSV_jet2_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_CSV_jet2_1l2tau_syst_35.9fb_012017.root",
	      "Subleading jet CSV score",
	      "1l2tau_Moriond/CSV_jet2_1l2tau_datacard_359fb");

}



void plot_pT_bjet1_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_bjet1_1l2tau_syst_35.9fb_012017.root",
	      "Highest-CSV jet p_{T} [GeV]",
	      "1l2tau_Moriond/pT_bjet1_1l2tau_datacard_359fb");

}



void plot_pT_bjet2_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_bjet2_1l2tau_syst_35.9fb_012017.root",
	      "2^{nd}-highest-CSV jet p_{T} [GeV]",
	      "1l2tau_Moriond/pT_bjet2_1l2tau_datacard_359fb");

}




void plot_mltau_1l2tau_012017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_mltau_1l2tau_syst_35.9fb_012017.root",
	      "Min(m_{vis}(lep,#tau_{h})) [GeV]",
	      "1l2tau_Moriond/mltau_1l2tau_datacard_359fb");

}


void plot_all_1l2tau(){

  //plot_mvis_1l2tau_012017();
  plot_BDT_1l2tau_022017();
  plot_n_fakelep_1l2tau_012017();
  plot_n_fakeele_1l2tau_012017();
  plot_n_fakemu_1l2tau_012017();
  plot_n_faketau_1l2tau_012017();
  plot_n_jet_1l2tau_012017();
  plot_n_jet_CSVloose_1l2tau_012017();
  plot_n_jet_CSVmedium_1l2tau_012017();
  plot_MET_1l2tau_012017();
  plot_pT_lep_1l2tau_012017();
  plot_pT_tau1_1l2tau_012017();
  plot_pT_tau2_1l2tau_012017();
  plot_pT_jet1_1l2tau_012017();
  plot_pT_jet2_1l2tau_012017();
  plot_pT_bjet1_1l2tau_012017();
  plot_pT_bjet2_1l2tau_012017();
  plot_CSV_jet1_1l2tau_012017();
  plot_CSV_jet2_1l2tau_012017();

}








void plot_n_fakelep_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_fakelep_2lss1tau_syst_35.9fb_012017.root",
	      "Number of fakeable leptons",
	      "2lss1tau_Moriond/n_fakelep_2lss1tau_datacard_359fb");

}



void plot_n_fakeele_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_fakeele_2lss1tau_syst_35.9fb_012017.root",
	      "Number of fakeable electrons",
	      "2lss1tau_Moriond/n_fakeele_2lss1tau_datacard_359fb");

}




void plot_n_fakeele_2lss1tau_012017_SStau_CR(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_fakeele_2lss1tau_syst_35.9fb_SStau_CR_022017.root",
	      "Number of fakeable electrons",
	      "2lss1tau_Moriond/n_fakeele_2lss1tau_datacard_359fb_SStau_CR");

}


void plot_n_fakemu_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_fakemu_2lss1tau_syst_35.9fb_012017.root",
	      "Number of fakeable muons",
	      "2lss1tau_Moriond/n_fakemu_2lss1tau_datacard_359fb");

}



void plot_n_faketau_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_faketau_2lss1tau_syst_35.9fb_012017.root",
	      "Number of fakeable #tau_{h}",
	      "2lss1tau_Moriond/n_faketau_2lss1tau_datacard_359fb");

}





void plot_n_jet_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_jet_2lss1tau_syst_35.9fb_012017.root",
	      "N(jet, p_{T}>25 GeV)",
	      "2lss1tau_Moriond/n_jet_2lss1tau_datacard_359fb");

}


void plot_n_jet_CSVloose_2lss1tau_012017(){

 plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_jet_CSVloose_2lss1tau_syst_35.9fb_012017.root",
	      "N(jet, p_{T}>25 GeV, CSVL)",
	      "2lss1tau_Moriond/n_jet_CSVL_2lss1tau_datacard_359fb");

}







void plot_n_jet_CSVmedium_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_jet_CSVmedium_2lss1tau_syst_35.9fb_012017.root",
	      "N(jet, p_{T}>25 GeV, CSVM)",
	      "2lss1tau_Moriond/n_jet_CSVM_2lss1tau_datacard_359fb");

}




void plot_MET_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_ETmiss_2lss1tau_syst_35.9fb_012017.root",
	      "E_{T}^{miss} [GeV]",
	      "2lss1tau_Moriond/MET_2lss1tau_datacard_359fb");

}





void plot_pT_lep1_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_lep1_2lss1tau_syst_35.9fb_012017.root",
	      "Leading lepton p_{T} [GeV]",
	      "2lss1tau_Moriond/pT_lep1_2lss1tau_datacard_359fb");

}




void plot_pT_lep1_2lss1tau_012017_ttbar_MC(){

  plot_2lSS_ttbar_MC("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_lep1_2lss1tau_syst_35.9fb_012017.root",
	      "Leading lepton p_{T} [GeV]",
	      "2lss1tau_Moriond/pT_lep1_2lss1tau_ttbar_MC_datacard_359fb");

}




void plot_pT_lep2_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_lep2_2lss1tau_syst_35.9fb_012017.root",
	      "Subleading lepton p_{T} [GeV]",
	      "2lss1tau_Moriond/pT_lep2_2lss1tau_datacard_359fb");

}




void plot_pT_tau_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_tau_2lss1tau_syst_35.9fb_012017.root",
	      "#tau_{h} p_{T} [GeV]",
	      "2lss1tau_Moriond/pT_tau_2lss1tau_datacard_359fb");

}



void plot_DM_tau_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_tau_DM_2lSS_nofaketau_35.9fb_012017.root",
	      "#tau_{h} decay mode",
	      "2lss1tau_Moriond/tau_DM_2lss1tau_datacard_359fb");

}





void plot_pT_tau_2lss1tau_SStau_CR_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_tau_2lss1tau_syst_35.9fb_SStau_CR_022017.root",
	      "#tau_{h} p_{T} [GeV]",
	      "pT_tau_2lss1tau_datacard_SStau_CR_359fb");

}




void plot_pT_jet1_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_jet1_2lss1tau_syst_35.9fb_012017.root",
	      "Leading jet p_{T} [GeV]",
	      "2lss1tau_Moriond/pT_jet1_2lss1tau_datacard_359fb");


}


void plot_pT_jet2_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_jet2_2lss1tau_syst_35.9fb_012017.root",
	      "Subleading jet p_{T} [GeV]",
	      "2lss1tau_Moriond/pT_jet2_2lss1tau_datacard_359fb");


}


void plot_CSV_jet1_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_CSV_jet1_2lss1tau_syst_35.9fb_012017.root",
	      "Leading jet CSV score",
	      "2lss1tau_Moriond/CSV_jet1_2lss1tau_datacard_359fb");

}



void plot_CSV_jet2_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_CSV_jet2_2lss1tau_syst_35.9fb_012017.root",
	      "Subleading jet CSV score",
	      "2lss1tau_Moriond/CSV_jet2_2lss1tau_datacard_359fb");

}



void plot_pT_bjet1_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_bjet1_2lss1tau_syst_35.9fb_012017.root",
	      "Highest-CSV jet p_{T} [GeV]",
	      "2lss1tau_Moriond/pT_bjet1_2lss1tau_datacard_359fb");

}



void plot_pT_bjet2_2lss1tau_012017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_bjet2_2lss1tau_syst_35.9fb_012017.root",
	      "2^{nd}-highest-CSV jet p_{T} [GeV]",
	      "2lss1tau_Moriond/pT_bjet2_2lss1tau_datacard_359fb");

}



void plot_all_2lss1tau(){

  plot_n_fakelep_2lss1tau_012017();
  plot_n_fakeele_2lss1tau_012017();
  plot_n_fakemu_2lss1tau_012017();
  plot_n_faketau_2lss1tau_012017();
  plot_n_jet_2lss1tau_012017();
  plot_n_jet_CSVloose_2lss1tau_012017();
  plot_n_jet_CSVmedium_2lss1tau_012017();
  plot_MET_2lss1tau_012017();
  plot_pT_lep1_2lss1tau_012017();
  plot_pT_lep2_2lss1tau_012017();
  plot_pT_tau_2lss1tau_012017();
  plot_pT_jet1_2lss1tau_012017();
  plot_pT_jet2_2lss1tau_012017();
  plot_pT_bjet1_2lss1tau_012017();
  plot_pT_bjet2_2lss1tau_012017();
  plot_CSV_jet1_2lss1tau_012017();
  plot_CSV_jet2_2lss1tau_012017();
  plot_MEM_2lSS_nofaketau_nomiss_022017();
  plot_MEM_2lSS_nofaketau_missing_022017();
  plot_MEM_int_type_2lSS_nofaketau_022017();
    

}








void plot_n_fakelep_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_fakelep_3l1tau_syst_35.9fb_022017.root",
	      "Number of fakeable leptons",
	      "3l1tau_Moriond/n_fakelep_3l1tau_datacard_359fb");

}



void plot_n_fakeele_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_fakeele_3l1tau_syst_35.9fb_022017.root",
	      "Number of fakeable electrons",
	      "3l1tau_Moriond/n_fakeele_3l1tau_datacard_359fb");

}


void plot_n_fakemu_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_fakemu_3l1tau_syst_35.9fb_022017.root",
	      "Number of fakeable muons",
	      "3l1tau_Moriond/n_fakemu_3l1tau_datacard_359fb");

}



void plot_n_faketau_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_faketau_3l1tau_syst_35.9fb_022017.root",
	      "Number of fakeable #tau_{h}",
	      "3l1tau_Moriond/n_faketau_3l1tau_datacard_359fb");

}





void plot_n_jet_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_jet_3l1tau_syst_35.9fb_022017.root",
	      "N(jet, p_{T}>25 GeV)",
	      "3l1tau_Moriond/n_jet_3l1tau_datacard_359fb");

}


void plot_n_jet_CSVloose_3l1tau_022017(){

 plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_jet_CSVloose_3l1tau_syst_35.9fb_022017.root",
	      "N(jet, p_{T}>25 GeV, CSVL)",
	      "3l1tau_Moriond/n_jet_CSVL_3l1tau_datacard_359fb");

}







void plot_n_jet_CSVmedium_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_jet_CSVmedium_3l1tau_syst_35.9fb_022017.root",
	      "N(jet, p_{T}>25 GeV, CSVM)",
	      "3l1tau_Moriond/n_jet_CSVM_3l1tau_datacard_359fb");

}




void plot_MET_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_ETmiss_3l1tau_syst_35.9fb_022017.root",
	      "E_{T}^{miss} [GeV]",
	      "3l1tau_Moriond/MET_3l1tau_datacard_359fb");

}





void plot_pT_lep1_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_lep1_3l1tau_syst_35.9fb_022017.root",
	      "Leading lepton p_{T} [GeV]",
	      "3l1tau_Moriond/pT_lep1_3l1tau_datacard_359fb");

}




void plot_pT_lep1_3l_ttZ_CR_022017(){

  plot_3l_ttZ_CR("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_lep1_3l_ttZ_CR_syst_35.9fb_022017.root",
	      "Leading lepton p_{T} [GeV]",
	      "pT_lep1_3l_ttZ_CR_datacard_359fb");

}




void plot_min_mll_3l_ttZ_CR_022017(){

  plot_3l_ttZ_CR("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_min_mll_3l_ttZ_CR_syst_35.9fb_022017.root",
	      "min m(ll) [GeV]",
	      "min_mll_3l_ttZ_CR_datacard_359fb");

}


/*void plot_bestMZ_3l_ttZ_CR_022017(){

  plot_3l_ttZ_CR("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_bestMZ_3l_ttZ_CR_syst_35.9fb_022017.root",
	      "Best Z candidate mass [GeV]",
	      "bestMZ_3l_ttZ_CR_datacard_359fb");

	      }*/



void plot_bestMZ_3l_ttZ_CR_022017(){

  plot_3l_ttZ_CR("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_bestMZ_3l_ttZ_CR_syst_35.9fb_022017.root",
	      "Best Z candidate mass [GeV]",
	      "bestMZ_3l_ttZ_CR_datacard_359fb");

}




void plot_n_recotauh_3l_ttZ_CR_022017(){

  plot_3l_ttZ_CR("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_recotauh_3l_ttZ_CR_syst_35.9fb_022017.root",
	      "Number of fakeable #tau_{h}",
	      "n_recotauh_3l_ttZ_CR_datacard_359fb");

}



void plot_n_recotauh_3l_ttZ_CR_faketau_022017(){

  plot_3l_ttZ_CR_faketau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_n_recotauh_3l_ttZ_CR_faketau_syst_35.9fb_022017.root",
	      "Number of fakeable #tau_{h}",
	      "n_recotauh_3l_ttZ_CR_faketau_datacard_359fb");

}




void plot_bestMZ_3l1tau_ttZ_CR_022017(){

  plot_3l_ttZ_CR("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_bestMZ_3l1tau_ttZ_CR_syst_35.9fb_022017.root",
	      "Best Z candidate mass [GeV]",
	      "bestMZ_3l1tau_ttZ_CR_datacard_359fb");

}




void plot_min_mll_3l1tau_ttZ_CR_022017(){

  plot_3l_ttZ_CR("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_min_mll_3l1tau_ttZ_CR_syst_35.9fb_022017.root",
	      "min m(ll) [GeV]",
	      "min_mll_3l1tau_ttZ_CR_datacard_359fb");

}




void plot_pT_lep2_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_lep2_3l1tau_syst_35.9fb_022017.root",
	      "Subleading lepton p_{T} [GeV]",
	      "3l1tau_Moriond/pT_lep2_3l1tau_datacard_359fb");

}




void plot_pT_lep3_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_lep3_3l1tau_syst_35.9fb_022017.root",
	      "Trailing lepton p_{T} [GeV]",
	      "3l1tau_Moriond/pT_lep3_3l1tau_datacard_359fb");

}



void plot_pT_tau_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_tau_3l1tau_syst_35.9fb_022017.root",
	      "#tau_{h} p_{T} [GeV]",
	      "3l1tau_Moriond/pT_tau_3l1tau_datacard_359fb");

}


void plot_DM_tau_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_DM_tau_3l1tau_syst_35.9fb_022017.root",
	      "#tau_{h} decay mode",
	      "3l1tau_Moriond/DM_tau_3l1tau_datacard_359fb");

}




void plot_pT_jet1_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_jet1_3l1tau_syst_35.9fb_022017.root",
	      "Leading jet p_{T} [GeV]",
	      "3l1tau_Moriond/pT_jet1_3l1tau_datacard_359fb");


}


void plot_pT_jet2_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_jet2_3l1tau_syst_35.9fb_022017.root",
	      "Subleading jet p_{T} [GeV]",
	      "3l1tau_Moriond/pT_jet2_3l1tau_datacard_359fb");


}


void plot_CSV_jet1_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_CSV_jet1_3l1tau_syst_35.9fb_022017.root",
	      "Leading jet CSV score",
	      "3l1tau_Moriond/CSV_jet1_3l1tau_datacard_359fb");

}



void plot_CSV_jet2_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_CSV_jet2_3l1tau_syst_35.9fb_022017.root",
	      "Subleading jet CSV score",
	      "3l1tau_Moriond/CSV_jet2_3l1tau_datacard_359fb");

}



void plot_pT_bjet1_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_bjet1_3l1tau_syst_35.9fb_022017.root",
	      "Highest-CSV jet p_{T} [GeV]",
	      "3l1tau_Moriond/pT_bjet1_3l1tau_datacard_359fb");

}



void plot_pT_bjet2_3l1tau_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_pT_bjet2_3l1tau_syst_35.9fb_022017.root",
	      "2^{nd}-highest-CSV jet p_{T} [GeV]",
	      "3l1tau_Moriond/pT_bjet2_3l1tau_datacard_359fb");

}



void plot_all_3l1tau(){

  plot_n_fakelep_3l1tau_022017();
  plot_n_fakeele_3l1tau_022017();
  plot_n_fakemu_3l1tau_022017();
  plot_n_faketau_3l1tau_022017();
  plot_n_jet_3l1tau_022017();
  plot_n_jet_CSVloose_3l1tau_022017();
  plot_n_jet_CSVmedium_3l1tau_022017();
  plot_MET_3l1tau_022017();
  plot_pT_lep1_3l1tau_022017();
  plot_pT_lep2_3l1tau_022017();
  plot_pT_lep3_3l1tau_022017();
  plot_pT_tau_3l1tau_022017();
  plot_pT_jet1_3l1tau_022017();
  plot_pT_jet2_3l1tau_022017();
  plot_pT_bjet1_3l1tau_022017();
  plot_pT_bjet2_3l1tau_022017();
  plot_CSV_jet1_3l1tau_022017();
  plot_CSV_jet2_3l1tau_022017();
  plot_MVA_3l_nofaketau_022017();
  plot_MVA_3l_ttbar_022017();
  plot_MVA_3l_ttV_022017();
  

}







void plot_MEM_2lSS_nofaketau_nomiss_missing_022017_ee(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_missing_nofaketau_35.9fb_022017_ee.root",
       "MEM_LR",
       "MEM_LR_2lSS_nomiss_missing_datacard_359fb_022017_ee");


}






void plot_MEM_2lSS_nofaketau_nomiss_missing_022017_em(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_missing_nofaketau_35.9fb_022017_em.root",
       "MEM_LR",
       "MEM_LR_2lSS_nomiss_missing_datacard_359fb_022017_em");


}





void plot_MEM_2lSS_nofaketau_nomiss_missing_022017_mm(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_missing_nofaketau_35.9fb_022017_mm.root",
       "MEM_LR",
       "MEM_LR_2lSS_nomiss_missing_datacard_359fb_022017_mm");


}





void plot_MEM_2lSS_nofaketau_nomiss_missing_022017_plus(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_missing_nofaketau_35.9fb_022017_plus.root",
       "MEM_LR",
       "MEM_LR_2lSS_nomiss_missing_datacard_359fb_022017_plus");


}




void plot_MEM_2lSS_nofaketau_nomiss_missing_022017_minus(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_missing_nofaketau_35.9fb_022017_minus.root",
       "MEM_LR",
       "MEM_LR_2lSS_nomiss_missing_datacard_359fb_022017_minus");


}


