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

//float luminosity = 36800; //12.9 fb-1
float luminosity = 35900;

using namespace std;


/*void plot_2lSS(TString datacardname, TString varname, TString plotname, int lumi=0, float mu=1.0){

  TFile* f = TFile::Open(datacardname);

  TH1F h_flips = *(TH1F*)f->Get("ch2_postfit/flips_data");
  h_flips.Add( (TH1F*)f->Get("ch3_postfit/flips_data") );

  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get("ch2_postfit/fakes_data") );
  h_fakes.Add( (TH1F*)f->Get("ch3_postfit/fakes_data") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_Rares = h_fakes;
  h_Rares.Add( (TH1F*)f->Get("ch2_postfit/Rares_gentau") );
  h_Rares.Add( (TH1F*)f->Get("ch2_postfit/Rares_faketau") );
  h_Rares.Add( (TH1F*)f->Get("ch3_postfit/Rares_gentau") );
  h_Rares.Add( (TH1F*)f->Get("ch3_postfit/Rares_faketau") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
  h_WZ.Add( (TH1F*)f->Get("ch2_postfit/EWK_gentau") );
  h_WZ.Add( (TH1F*)f->Get("ch2_postfit/EWK_faketau") );
  h_WZ.Add( (TH1F*)f->Get("ch3_postfit/EWK_gentau") );
  h_WZ.Add( (TH1F*)f->Get("ch3_postfit/EWK_faketau") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_ttZ = h_WZ;
  h_ttZ.Add( (TH1F*)f->Get("ch2_postfit/TTZ_gentau") );
  h_ttZ.Add( (TH1F*)f->Get("ch2_postfit/TTZ_faketau") );
  h_ttZ.Add( (TH1F*)f->Get("ch3_postfit/TTZ_gentau") );
  h_ttZ.Add( (TH1F*)f->Get("ch3_postfit/TTZ_faketau") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get("ch2_postfit/TTW_gentau") );
  h_ttW.Add( (TH1F*)f->Get("ch2_postfit/TTW_faketau") );
  h_ttW.Add( (TH1F*)f->Get("ch3_postfit/TTW_gentau") );
  h_ttW.Add( (TH1F*)f->Get("ch3_postfit/TTW_faketau") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get("ch2_postfit/ttH_hww_gentau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch2_postfit/ttH_hww_faketau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch2_postfit/ttH_hzz_gentau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch2_postfit/ttH_hzz_faketau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch3_postfit/ttH_hww_gentau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch3_postfit/ttH_hww_faketau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch3_postfit/ttH_hzz_gentau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch3_postfit/ttH_hzz_faketau") , mu);
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get("ch2_postfit/ttH_htt_gentau") , mu);  
  h_ttH.Add( (TH1F*)f->Get("ch2_postfit/ttH_htt_faketau") , mu);  
  h_ttH.Add( (TH1F*)f->Get("ch3_postfit/ttH_htt_gentau") , mu);
  h_ttH.Add( (TH1F*)f->Get("ch3_postfit/ttH_htt_faketau") , mu);    
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 


  TH1F h_ttH_only = *(TH1F*)f->Get("ch2_postfit/TotalSig");
  h_ttH_only.Add( (TH1F*)f->Get("ch3_postfit/TotalSig") );
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get("ch2_postfit/data_obs");
  h_data_obs.Add( (TH1F*)f->Get("ch3_postfit/data_obs") );
  //TH1F h_data_obs = h_ttH;
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  cout<<h_data_obs.Integral()<<endl;

  f->Close();


  TLegend* leg=new TLegend(0.5,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  if(mu==1.){
    leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
    leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  }
  else{
    leg->AddEntry(&h_ttH,Form("ttH H#rightarrow#tau#tau x %.2f",mu));
    leg->AddEntry(&h_ttH_boson,Form("ttH H#rightarrowWW/ZZ x %.2f",mu));
  }
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"EWK");
  leg->AddEntry(&h_Rares,"Other");
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

  
  TLatex *texl = new TLatex(h_ttH.GetBinLowEdge(1),1.01*h_ttH.GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");
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

  for(int i=0;i<h_ratio->GetN();i++){
    double x,y;
    h_ratio->GetPoint(i,x,y);
    if(y==0){
      h_ratio->RemovePoint(i);
      i--;
    }
    }
  
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
*/




void plot_2lSS(TString datacardname, TString varname, TString plotname, int lumi=0, float mu=1.0, TString channel="ch2_postfit"){

  TFile* f = TFile::Open(datacardname);

  TH1F h_flips = *(TH1F*)f->Get(channel+"/flips_data");
  //h_flips.Add( (TH1F*)f->Get("ch3_postfit/flips_data") );

  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  h_fakes.Add( (TH1F*)f->Get(channel+"/fakes_data") );
  //h_fakes.Add( (TH1F*)f->Get("ch3_postfit/fakes_data") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_Rares = h_fakes;
  h_Rares.Add( (TH1F*)f->Get(channel+"/Rares_gentau") );
  h_Rares.Add( (TH1F*)f->Get(channel+"/Rares_faketau") );
  //h_Rares.Add( (TH1F*)f->Get("ch3_postfit/Rares_gentau") );
  //h_Rares.Add( (TH1F*)f->Get("ch3_postfit/Rares_faketau") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
  h_WZ.Add( (TH1F*)f->Get(channel+"/EWK_gentau") );
  h_WZ.Add( (TH1F*)f->Get(channel+"/EWK_faketau") );
  //h_WZ.Add( (TH1F*)f->Get("ch3_postfit/EWK_gentau") );
  //h_WZ.Add( (TH1F*)f->Get("ch3_postfit/EWK_faketau") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_ttZ = h_WZ;
  h_ttZ.Add( (TH1F*)f->Get(channel+"/TTZ_gentau") );
  h_ttZ.Add( (TH1F*)f->Get(channel+"/TTZ_faketau") );
  //h_ttZ.Add( (TH1F*)f->Get("ch3_postfit/TTZ_gentau") );
  //h_ttZ.Add( (TH1F*)f->Get("ch3_postfit/TTZ_faketau") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get(channel+"/TTW_gentau") );
  h_ttW.Add( (TH1F*)f->Get(channel+"/TTW_faketau") );
  //h_ttW.Add( (TH1F*)f->Get("ch3_postfit/TTW_gentau") );
  //h_ttW.Add( (TH1F*)f->Get("ch3_postfit/TTW_faketau") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get(channel+"/ttH_hww_gentau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get(channel+"/ttH_hww_faketau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get(channel+"/ttH_hzz_gentau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get(channel+"/ttH_hzz_faketau") , mu);
  /*h_ttH_boson.Add( (TH1F*)f->Get("ch3_postfit/ttH_hww_gentau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch3_postfit/ttH_hww_faketau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch3_postfit/ttH_hzz_gentau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch3_postfit/ttH_hzz_faketau") , mu);*/
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get(channel+"/ttH_htt_gentau") , mu);  
  h_ttH.Add( (TH1F*)f->Get(channel+"/ttH_htt_faketau") , mu);  
  //h_ttH.Add( (TH1F*)f->Get("ch3_postfit/ttH_htt_gentau") , mu);
  //h_ttH.Add( (TH1F*)f->Get("ch3_postfit/ttH_htt_faketau") , mu);    
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 


  TH1F h_ttH_only = *(TH1F*)f->Get(channel+"/TotalSig");
  //h_ttH_only.Add( (TH1F*)f->Get("ch3_postfit/TotalSig") );
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get(channel+"/data_obs");
  //h_data_obs.Add( (TH1F*)f->Get("ch3_postfit/data_obs") );
  //TH1F h_data_obs = h_ttH;
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  cout<<h_data_obs.Integral()<<endl;

  f->Close();


  TLegend* leg=new TLegend(0.5,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  /*if(mu==1.){
    leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
    leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  }
  else{*/
    leg->AddEntry(&h_ttH,Form("ttH H#rightarrow#tau#tau x %.2f",mu));
    leg->AddEntry(&h_ttH_boson,Form("ttH H#rightarrowWW/ZZ x %.2f",mu));
    //}
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"EWK");
  leg->AddEntry(&h_Rares,"Other");
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



  h_data_obs.SetBinErrorOption(TH1::kPoisson);

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








void plot_2lSS_missing(TString datacardname, TString varname, TString plotname, int lumi=0, float mu=1.0){

  TFile* f = TFile::Open(datacardname);

  //TH1F h_flips = *(TH1F*)f->Get(channel+"/flips_data");
  TH1F h_flips = * (TH1F*)f->Get("ch3_postfit/flips_data");

  h_flips.SetFillColor(10);
  h_flips.SetLineColor(kBlack);
  TH1F h_flips_lines = h_flips;
  h_flips_lines.SetFillColor(kBlack);
  h_flips_lines.SetFillStyle(3007);

  TH1F h_fakes = h_flips;
  //h_fakes.Add( (TH1F*)f->Get(channel+"/fakes_data") );
  h_fakes.Add( (TH1F*)f->Get("ch3_postfit/fakes_data") );
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_Rares = h_fakes;
  //h_Rares.Add( (TH1F*)f->Get(channel+"/Rares_gentau") );
  //h_Rares.Add( (TH1F*)f->Get(channel+"/Rares_faketau") );
  h_Rares.Add( (TH1F*)f->Get("ch3_postfit/Rares_gentau") );
  h_Rares.Add( (TH1F*)f->Get("ch3_postfit/Rares_faketau") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
  //h_WZ.Add( (TH1F*)f->Get(channel+"/EWK_gentau") );
  //h_WZ.Add( (TH1F*)f->Get(channel+"/EWK_faketau") );
  h_WZ.Add( (TH1F*)f->Get("ch3_postfit/EWK_gentau") );
  h_WZ.Add( (TH1F*)f->Get("ch3_postfit/EWK_faketau") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_ttZ = h_WZ;
  //h_ttZ.Add( (TH1F*)f->Get(channel+"/TTZ_gentau") );
  //h_ttZ.Add( (TH1F*)f->Get(channel+"/TTZ_faketau") );
  h_ttZ.Add( (TH1F*)f->Get("ch3_postfit/TTZ_gentau") );
  h_ttZ.Add( (TH1F*)f->Get("ch3_postfit/TTZ_faketau") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  //h_ttW.Add( (TH1F*)f->Get(channel+"/TTW_gentau") );
  //h_ttW.Add( (TH1F*)f->Get(channel+"/TTW_faketau") );
  h_ttW.Add( (TH1F*)f->Get("ch3_postfit/TTW_gentau") );
  h_ttW.Add( (TH1F*)f->Get("ch3_postfit/TTW_faketau") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  /*h_ttH_boson.Add( (TH1F*)f->Get(channel+"/ttH_hww_gentau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get(channel+"/ttH_hww_faketau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get(channel+"/ttH_hzz_gentau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get(channel+"/ttH_hzz_faketau") , mu);*/
  h_ttH_boson.Add( (TH1F*)f->Get("ch3_postfit/ttH_hww_gentau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch3_postfit/ttH_hww_faketau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch3_postfit/ttH_hzz_gentau") , mu);
  h_ttH_boson.Add( (TH1F*)f->Get("ch3_postfit/ttH_hzz_faketau") , mu);
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  //h_ttH.Add( (TH1F*)f->Get(channel+"/ttH_htt_gentau") , mu);  
  //h_ttH.Add( (TH1F*)f->Get(channel+"/ttH_htt_faketau") , mu);  
  h_ttH.Add( (TH1F*)f->Get("ch3_postfit/ttH_htt_gentau") , mu);
  h_ttH.Add( (TH1F*)f->Get("ch3_postfit/ttH_htt_faketau") , mu);    
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 


  //TH1F h_ttH_only = *(TH1F*)f->Get(channel+"/TotalSig");
  TH1F h_ttH_only = * (TH1F*)f->Get("ch3_postfit/TotalSig");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  //TH1F h_data_obs = *(TH1F*)f->Get(channel+"/data_obs");
  TH1F h_data_obs = * (TH1F*)f->Get("ch3_postfit/data_obs");
  //TH1F h_data_obs = h_ttH;
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  cout<<h_data_obs.Integral()<<endl;

  f->Close();


  TLegend* leg=new TLegend(0.5,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  if(mu==1.){
    leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
    leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  }
  else{
    leg->AddEntry(&h_ttH,Form("ttH H#rightarrow#tau#tau x %.2f",mu));
    leg->AddEntry(&h_ttH_boson,Form("ttH H#rightarrowWW/ZZ x %.2f",mu));
  }
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"EWK");
  leg->AddEntry(&h_Rares,"Other");
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





void plot_1l2tau(TString datacardname, TString varname, TString plotname, bool plot_sigx10=false, int lumi=0, float mu=1.0, TString cat_name="ch1_postfit"){

  TFile* f = TFile::Open(datacardname);
  //TString cat_name = "ttH_1l_2tau_postfit";

  TH1F h_ttH = *(TH1F*)f->Get(cat_name+"/TotalSig");
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack);
  cout<<mu<<endl;
  cout<<h_ttH.Integral()<<endl;
  h_ttH.Scale(mu);
  cout<<h_ttH.Integral()<<endl;
 
  TH1F h_ttW = h_ttH;
  h_ttW.Add( (TH1F*)f->Get(cat_name+"/TTW_gentau") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttZ = h_ttW;
  h_ttZ.Add( (TH1F*)f->Get(cat_name+"/TTZ_gentau") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_WZ = h_ttZ;
  h_WZ.Add( (TH1F*)f->Get(cat_name+"/EWK_gentau") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_Rares = h_WZ;
  h_Rares.Add( (TH1F*)f->Get(cat_name+"/Rares_gentau") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_fakes = h_Rares;
  h_fakes.Add( (TH1F*)f->Get(cat_name+"/fakes_data"));
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_ttH_error = h_fakes;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_ttH_only = *(TH1F*)f->Get(cat_name+"/TotalSig");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);
  h_ttH_only.Scale(10);


  TH1F h_data_obs = *(TH1F*)f->Get(cat_name+"/data_obs");
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
  /*if(mu==1.)
    leg->AddEntry(&h_ttH,"ttH");
  else*/
    leg->AddEntry(&h_ttH,Form("ttH x %.2f",mu));
  //leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"EWK");
  leg->AddEntry(&h_Rares,"Other");
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
  for(int i=1;i<=h_data_obs.GetNbinsX();i++){
    float sig = 0.1*h_ttH_only.Integral(i,i)/sqrt(h_ttW.Integral(i,i)+0.1*h_ttH_only.Integral(i,i));
    cout<<"Bin"<<i<<"="<<sig<<endl;
    //if(varname.Contains("m_{vis}(#tau#tau)") && sig>0.15)
    if(varname.Contains("m_{vis}(#tau#tau)") && i>=6 && i<=12)
      h_data_obs.SetBinContent(i,0);
    if(varname.Contains("BDT") && i>=3){
      //h_data_obs.SetBinContent(i,0);
    }
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

  
  h_data_obs.SetBinErrorOption(TH1::kPoisson);


  h_fakes.SetMaximum(100*max(h_data_obs.GetMaximum(),h_fakes.GetMaximum()));
  h_fakes.SetMinimum(2e-2);  
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

  /*for(int i=0;i<=h_ratio->GetN();i++){
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











void plot_3l(TString datacardname, TString varname, TString plotname, int lumi=0, float mu=1., TString channel="ch4_postfit"){

  TFile* f = TFile::Open(datacardname);

  TH1F h_fakes = *(TH1F*)f->Get(channel+"/fakes_data");
  h_fakes.SetFillColor(10);
  h_fakes.SetLineColor(kBlack);
  TH1F h_fakes_lines = h_fakes;
  h_fakes_lines.SetFillColor(kBlack);
  h_fakes_lines.SetFillStyle(3004);

  TH1F h_Rares = h_fakes;
  h_Rares.Add( (TH1F*)f->Get(channel+"/Rares_gentau") );
  h_Rares.Add( (TH1F*)f->Get(channel+"/Rares_faketau") );
  h_Rares.SetFillColor(kCyan-7);
  h_Rares.SetLineColor(kBlack);

  TH1F h_WZ = h_Rares;
  h_WZ.Add( (TH1F*)f->Get(channel+"/EWK_gentau") );
  h_WZ.Add( (TH1F*)f->Get(channel+"/EWK_faketau") );
  h_WZ.SetFillColor(kViolet-4);
  h_WZ.SetLineColor(kBlack);

  TH1F h_ttZ = h_WZ;
  h_ttZ.Add( (TH1F*)f->Get(channel+"/TTZ_gentau") );
  h_ttZ.Add( (TH1F*)f->Get(channel+"/TTZ_faketau") );
  h_ttZ.SetFillColor(kSpring-5);
  h_ttZ.SetLineColor(kBlack);

  TH1F h_ttW = h_ttZ;
  h_ttW.Add( (TH1F*)f->Get(channel+"/TTW_gentau") );
  h_ttW.Add( (TH1F*)f->Get(channel+"/TTW_faketau") );
  h_ttW.SetFillColor(kSpring-6);
  h_ttW.SetLineColor(kBlack);

  TH1F h_ttH_boson = h_ttW;
  h_ttH_boson.Add( (TH1F*)f->Get(channel+"/ttH_hww_gentau") , mu );
  h_ttH_boson.Add( (TH1F*)f->Get(channel+"/ttH_hww_faketau") , mu );
  h_ttH_boson.Add( (TH1F*)f->Get(channel+"/ttH_hzz_gentau") , mu );
  h_ttH_boson.Add( (TH1F*)f->Get(channel+"/ttH_hzz_faketau") , mu );
  h_ttH_boson.SetFillColor(kOrange);
  h_ttH_boson.SetLineColor(kBlack);

  TH1F h_ttH = h_ttH_boson;
  h_ttH.Add( (TH1F*)f->Get(channel+"/ttH_htt_gentau") , mu );  
  h_ttH.Add( (TH1F*)f->Get(channel+"/ttH_htt_faketau") , mu );  
  h_ttH.SetFillColor(kRed);
  h_ttH.SetLineColor(kBlack); 

  TH1F h_ttH_only = *(TH1F*)f->Get(channel+"/TotalSig");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);

  TH1F h_ttH_error = h_ttH;
  h_ttH_error.SetFillColor(1);
  h_ttH_error.SetLineWidth(0);
  h_ttH_error.SetFillStyle(3003);

  TH1F h_data_obs = *(TH1F*)f->Get(channel+"/data_obs");
  //TH1F h_data_obs = h_ttH;
  h_data_obs.SetLineColor(1);
  h_data_obs.SetLineWidth(2);
  h_data_obs.SetMarkerStyle(20);

  f->Close();


  TLegend* leg=new TLegend(0.5,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_data_obs,"Data");
  /*if(mu==1.){
    leg->AddEntry(&h_ttH,"ttH H#rightarrow#tau#tau");
    leg->AddEntry(&h_ttH_boson,"ttH H#rightarrowWW/ZZ");
  }
  else{*/
    leg->AddEntry(&h_ttH,Form("ttH H#rightarrow#tau#tau x %.2f",mu));
    leg->AddEntry(&h_ttH_boson,Form("ttH H#rightarrowWW/ZZ x %.2f",mu));
    //}
  leg->AddEntry(&h_ttW,"ttW");
  leg->AddEntry(&h_ttZ,"ttZ");
  leg->AddEntry(&h_WZ,"EWK");
  //leg->AddEntry(&h_Rares,"Rares");
  leg->AddEntry(&h_fakes_lines,"Fakes");
  
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


  h_data_obs.SetBinErrorOption(TH1::kPoisson);


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








void plot_MVA_3l_nofaketau_postfit_122016(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/ttH_htt_2016_4cat_shapes.root",
       "MVA(ttH vs ttV/t#bar{t})",
       "3l1tau_Moriond/MVA_3l_ttV_ttbar_datacard_nofaketau_368fb_postfit");


}






void plot_MEM_2lSS_nofaketau_nomiss_missing_postfit_122016(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/ttH_htt_2016_4cat_shapes.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_2lSS_nomiss_missing_datacard_368fb_postfit_122016");

}






void plot_BDT_1l2tau_122016(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/ttH_htt_2016_4cat_shapes.root",
	      "BDT output",
	      "1l2tau_Moriond/BDT_1l2tau_datacard_368fb_postfit");

}








void plot_MVA_3l_nofaketau_prefit_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/ttH_htt_2016_4cat_shapes.root",
       "MVA(ttH vs ttV/t#bar{t})",
       "3l1tau_Moriond/MVA_3l_ttV_ttbar_datacard_nofaketau_359fb_prefit_022017",0,1.0,"ch4_prefit");


}




void plot_MVA_3l_nofaketau_postfit_022017(){

  plot_3l("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/ttH_htt_2016_4cat_shapes.root",
       "MVA(ttH vs ttV/t#bar{t})",
	  "3l1tau_Moriond/MVA_3l_ttV_ttbar_datacard_nofaketau_359fb_postfit_022017",0,1.0,"ch4_postfit");


}






void plot_MEM_2lSS_nofaketau_nomiss_missing_postfit_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/ttH_htt_2016_4cat_shapes.root",
	    "MEM_LR",
	    "2lss1tau_Moriond/MEM_LR_2lSS_nomiss_missing_datacard_359fb_postfit_022017",0,0.72);

}



void plot_MEM_2lSS_nofaketau_nomiss_postfit_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/ttH_htt_2016_4cat_shapes.root",
	    "MEM_LR",
		   "2lss1tau_Moriond/MEM_LR_2lSS_nomiss_datacard_359fb_postfit_022017",0,1.0,"ch2_postfit");

}



void plot_MEM_2lSS_nofaketau_nomiss_prefit_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/ttH_htt_2016_4cat_shapes.root",
	    "MEM_LR",
		   "2lss1tau_Moriond/MEM_LR_2lSS_nomiss_datacard_359fb_prefit_022017",0,1.0,"ch2_prefit");

}




void plot_MEM_2lSS_nofaketau_missing_postfit_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/ttH_htt_2016_4cat_shapes.root",
	    "MEM_LR",
		    "2lss1tau_Moriond/MEM_LR_2lSS_missing_datacard_359fb_postfit_022017",0,1.0,"ch3_postfit");

}





void plot_MEM_2lSS_nofaketau_missing_prefit_022017(){

  plot_2lSS("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/ttH_htt_2016_4cat_shapes.root",
	    "MEM_LR",
		    "2lss1tau_Moriond/MEM_LR_2lSS_missing_datacard_359fb_prefit_022017",0,1.0,"ch3_prefit");

}





void plot_BDT_1l2tau_022017(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/ttH_htt_2016_4cat_shapes.root",
	      "BDT output",
	      "1l2tau_Moriond/BDT_1l2tau_datacard_359fb_postfit_022017",false,0,1.0,"ch1_postfit");

}




void plot_BDT_1l2tau_022017_prefit(){

  plot_1l2tau("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards/ttH_htt_2016_4cat_shapes.root",
	      "BDT output",
	      "1l2tau_Moriond/BDT_1l2tau_datacard_359fb_prefit_022017",false,0,1.0,"ch1_prefit");

}








void plot_BDT_1l2tau_022017_pseudodata_ttbar_MC(){

  plot_1l2tau("/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/ttH_htt_2016_4cat_shapes.root",
	      "BDT output",
	      "BDT_1l2tau_datacard_359fb_postfit_022017_pseudodata_ttbar_MC",false,0,1.37);

}









