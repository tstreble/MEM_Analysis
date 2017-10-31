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

float luminosity = 36800; //12.9 fb-1

using namespace std;





void plot_3l_split(TString datacardname, TString varname, TString plotname){

  TFile* f = TFile::Open(datacardname);

  TH1F h_ttV = *(TH1F*)f->Get("x_TTZ");
  h_ttV.Add((TH1F*)f->Get("x_TTW"));
  h_ttV.SetLineColor(kGreen);
  h_ttV.SetLineWidth(2);
  h_ttV.Scale(1/h_ttV.Integral());

  TH1F h_ttbar = *(TH1F*)f->Get("x_fakes_data");
  h_ttbar.SetLineColor(kBlack);
  h_ttbar.SetLineWidth(2);
  h_ttbar.Scale(1/h_ttbar.Integral());

  TH1F h_ttH_only = *(TH1F*)f->Get("x_ttH");
  h_ttH_only.SetLineColor(kRed);
  h_ttH_only.SetLineWidth(2);
  h_ttH_only.Scale(1/h_ttH_only.Integral());

  TLegend* leg=new TLegend(0.25,0.5,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(&h_ttH_only,"ttH");
  leg->AddEntry(&h_ttV,"ttV");
  leg->AddEntry(&h_ttbar,"t#bar{t}");

  
  h_ttH_only.GetXaxis()->SetTitle(varname);
  h_ttH_only.GetYaxis()->SetTitle("a.u.");
  h_ttH_only.GetYaxis()->SetTitleOffset(1.65);
  h_ttH_only.SetTitle("");
  h_ttH_only.SetStats(0);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  gPad->SetTicks();

  h_ttH_only.SetMaximum(1.5*max(max(h_ttH_only.GetMaximum(),h_ttV.GetMaximum()),h_ttbar.GetMaximum()));
  h_ttH_only.SetMinimum(0);
  (&h_ttH_only)->Draw("hist");
  (&h_ttV)->Draw("histsame");
  (&h_ttbar)->Draw("histsame");
 
  leg->Draw("same");

  TLatex tex;
  tex.SetTextSize(0.04);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  tex.DrawLatexNDC(0.65,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));

  h_ttH_only.GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_ttH_only.GetBinLowEdge(1), 0.01, h_ttH_only.GetBinLowEdge(1), h_ttH_only.GetMaximum(), 0.01, h_ttH_only.GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();


  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}




void plot_MVA_3l_ttbar_122016(){

  plot_3l_split("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MVA_3l_ttbar_nofaketau_36.8fb.root",
	    "MVA(ttH vs t#bar{t})",
	    "3l1tau_Moriond/MVA_3l_ttbar_36.8fb_122016");

}




void plot_MVA_3l_ttV_122016(){

  plot_3l_split("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MVA_3l_ttV_nofaketau_36.8fb.root",
	    "MVA(ttH vs ttV)",
	    "3l1tau_Moriond/MVA_3l_ttV_36.8fb_122016");

}
