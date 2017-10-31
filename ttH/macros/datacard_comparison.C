#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>
#include <THStack.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <iostream>
#include <TPad.h>
#include <TGaxis.h>
#include <TLine.h>

using namespace std;


float luminosity = 12900; //12.9 fb-1


void plot_ttH(){

  TString file_CERN="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacards_CERN/datacard_CERN_2lss_1tau_4fb.root";
  TString file_LLR="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_pt25.root";

  TFile* f_CERN = TFile::Open(file_CERN);
  TH1F* h_CERN = (TH1F*)f_CERN->Get("x_ttH");
  h_CERN->SetDirectory(0);
  f_CERN->Close();
  h_CERN->SetFillColor(kRed);

  TFile* f_LLR = TFile::Open(file_LLR);
  TH1F* h_LLR = (TH1F*)f_LLR->Get("h_ttH");
  h_LLR->SetDirectory(0);
  f_LLR->Close();
  h_LLR->SetLineColor(1);
  h_LLR->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad


  h_LLR->SetMinimum(0);
  h_LLR->SetMaximum(1.3*h_LLR->GetMaximum());

  h_LLR->GetXaxis()->SetTitle("MVA(ttH,ttbar/ttV) bin");
  h_LLR->GetYaxis()->SetTitle("Events");
  h_LLR->GetYaxis()->SetTitleOffset(1.5);
  h_LLR->SetTitle("");
  h_LLR->SetStats(0);

  h_LLR->Draw();
  h_CERN->Draw("histsame");
  h_LLR->Draw("same");

  TLegend* leg=new TLegend(0.5,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->SetHeader(Form("Yield CERN/LLR = %f",h_CERN->Integral()/h_LLR->Integral()));
  leg->AddEntry(h_CERN,"CERN");
  leg->AddEntry(h_LLR,"LLR");
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_LLR->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0.5, 0.001, 0.5, h_LLR->GetMaximum(), 0.001,h_LLR->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  TLatex *texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");


  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)(h_LLR)->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_CERN);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_LLR->GetYaxis()->SetTitleSize(20);
  h_LLR->GetYaxis()->SetTitleFont(43);
  h_LLR->GetYaxis()->SetTitleOffset(1.4);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0.5, 0.01, 0.5, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/CERN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.4);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(18);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(3.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);

  TLine* line=new TLine(0.5,1.,7.5,1.);
  line->SetLineStyle(7);
  line->Draw("same");


  TString filename="MVA_2lSS_ttH_ttbar_datacard_comparison_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}






void plot_ttW(){

  TString file_CERN="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacards_CERN/datacard_CERN_2lss_1tau_4fb.root";
  TString file_LLR="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_pt25.root";

  TFile* f_CERN = TFile::Open(file_CERN);
  TH1F* h_CERN = (TH1F*)f_CERN->Get("x_TTW");
  h_CERN->SetDirectory(0);
  f_CERN->Close();
  h_CERN->SetFillColor(kSpring-6);

  TFile* f_LLR = TFile::Open(file_LLR);
  TH1F* h_LLR = (TH1F*)f_LLR->Get("h_ttW");
  h_LLR->SetDirectory(0);
  f_LLR->Close();
  h_LLR->SetLineColor(1);
  h_LLR->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx()         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad


  h_LLR->SetMinimum(0);
  h_LLR->SetMaximum(1.3*h_LLR->GetMaximum());

  h_LLR->GetXaxis()->SetTitle("MVA(ttH,ttbar/ttV) bin");
  h_LLR->GetYaxis()->SetTitle("Events");
  h_LLR->GetYaxis()->SetTitleOffset(1.5);
  h_LLR->SetTitle("");
  h_LLR->SetStats(0);

  h_LLR->Draw();
  h_CERN->Draw("histsame");
  h_LLR->Draw("same");

  TLegend* leg=new TLegend(0.5,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->SetHeader(Form("Yield CERN/LLR = %f",h_CERN->Integral()/h_LLR->Integral()));
  leg->AddEntry(h_CERN,"CERN");
  leg->AddEntry(h_LLR,"LLR");
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_LLR->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0.5, 0.001, 0.5, h_LLR->GetMaximum(), 0.001,h_LLR->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  TLatex *texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttW %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");


  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)(h_LLR)->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_CERN);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_LLR->GetYaxis()->SetTitleSize(20);
  h_LLR->GetYaxis()->SetTitleFont(43);
  h_LLR->GetYaxis()->SetTitleOffset(1.4);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0.5, 0.01, 0.5, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/CERN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.4);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(18);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(3.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);

  TLine* line=new TLine(0.5,1.,7.5,1.);
  line->SetLineStyle(7);
  line->Draw("same");


  TString filename="MVA_2lSS_ttH_ttbar_datacard_comparison_ttW";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}






void plot_ttZ(){

  TString file_CERN="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacards_CERN/datacard_CERN_2lss_1tau_4fb.root";
  TString file_LLR="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_pt25.root";

  TFile* f_CERN = TFile::Open(file_CERN);
  TH1F* h_CERN = (TH1F*)f_CERN->Get("x_TTZ");
  h_CERN->SetDirectory(0);
  f_CERN->Close();
  h_CERN->SetFillColor(kSpring-5);

  TFile* f_LLR = TFile::Open(file_LLR);
  TH1F* h_LLR = (TH1F*)f_LLR->Get("h_ttZ");
  h_LLR->Add( (TH1F*)f_LLR->Get("h_TTLL_lowmass") );
  h_LLR->Add( (TH1F*)f_LLR->Get("h_ttG") );
  h_LLR->SetDirectory(0);
  f_LLR->Close();
  h_LLR->SetLineColor(1);
  h_LLR->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx()         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad


  h_LLR->SetMinimum(0);
  h_LLR->SetMaximum(1.3*h_LLR->GetMaximum());

  h_LLR->GetXaxis()->SetTitle("MVA(ttH,ttbar/ttV) bin");
  h_LLR->GetYaxis()->SetTitle("Events");
  h_LLR->GetYaxis()->SetTitleOffset(1.5);
  h_LLR->SetTitle("");
  h_LLR->SetStats(0);

  h_LLR->Draw();
  h_CERN->Draw("histsame");
  h_LLR->Draw("same");

  TLegend* leg=new TLegend(0.5,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->SetHeader(Form("Yield CERN/LLR = %f",h_CERN->Integral()/h_LLR->Integral()));
  leg->AddEntry(h_CERN,"CERN");
  leg->AddEntry(h_LLR,"LLR");
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_LLR->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0.5, 0.001, 0.5, h_LLR->GetMaximum(), 0.001,h_LLR->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  TLatex *texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttZ %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");


  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)(h_LLR)->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_CERN);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_LLR->GetYaxis()->SetTitleSize(20);
  h_LLR->GetYaxis()->SetTitleFont(43);
  h_LLR->GetYaxis()->SetTitleOffset(1.4);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0.5, 0.01, 0.5, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/CERN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.4);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(18);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(3.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);

  TLine* line=new TLine(0.5,1.,7.5,1.);
  line->SetLineStyle(7);
  line->Draw("same");


  TString filename="MVA_2lSS_ttH_ttbar_datacard_comparison_ttZ";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}







void plot_Rares(){

  TString file_CERN="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacards_CERN/datacard_CERN_2lss_1tau_4fb.root";
  TString file_LLR="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_pt25.root";

  TFile* f_CERN = TFile::Open(file_CERN);
  TH1F* h_CERN = (TH1F*)f_CERN->Get("x_Rares");
  h_CERN->Add( (TH1F*)f_CERN->Get("x_WWss") );

  h_CERN->SetDirectory(0);
  f_CERN->Close();
  h_CERN->SetFillColor(kAzure+10);

  TFile* f_LLR = TFile::Open(file_LLR);
  TH1F* h_LLR = (TH1F*)f_LLR->Get("h_ZZZ");
  h_LLR->Add( (TH1F*)f_LLR->Get("h_WZZ") );
  h_LLR->Add( (TH1F*)f_LLR->Get("h_WWZ") );
  h_LLR->Add( (TH1F*)f_LLR->Get("h_tZq") );
  h_LLR->Add( (TH1F*)f_LLR->Get("h_TTTT") );
  h_LLR->Add( (TH1F*)f_LLR->Get("h_WpWp") );


  h_LLR->SetDirectory(0);
  f_LLR->Close();
  h_LLR->SetLineColor(1);
  h_LLR->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx()         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad


  h_LLR->SetMinimum(0);
  h_LLR->SetMaximum(1.3*h_LLR->GetMaximum());

  h_LLR->GetXaxis()->SetTitle("MVA(ttH,ttbar/ttV) bin");
  h_LLR->GetYaxis()->SetTitle("Events");
  h_LLR->GetYaxis()->SetTitleOffset(1.5);
  h_LLR->SetTitle("");
  h_LLR->SetStats(0);

  h_LLR->Draw();
  h_CERN->Draw("histsame");
  h_LLR->Draw("same");

  TLegend* leg=new TLegend(0.5,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->SetHeader(Form("Yield CERN/LLR = %f",h_CERN->Integral()/h_LLR->Integral()));
  leg->AddEntry(h_CERN,"CERN");
  leg->AddEntry(h_LLR,"LLR");
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_LLR->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0.5, 0.001, 0.5, h_LLR->GetMaximum(), 0.001,h_LLR->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  TLatex *texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Simulation %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");


  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)(h_LLR)->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_CERN);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_LLR->GetYaxis()->SetTitleSize(20);
  h_LLR->GetYaxis()->SetTitleFont(43);
  h_LLR->GetYaxis()->SetTitleOffset(1.4);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0.5, 0.01, 0.5, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/CERN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.4);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(18);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(3.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);

  TLine* line=new TLine(0.5,1.,7.5,1.);
  line->SetLineStyle(7);
  line->Draw("same");


  TString filename="MVA_2lSS_ttH_ttbar_datacard_comparison_Rares";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}



void plot_fakes(){

  TString file_CERN="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacards_CERN/datacard_CERN_2lss_1tau_4fb.root";
  TString file_LLR="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_pt25.root";

  TFile* f_CERN = TFile::Open(file_CERN);
  TH1F* h_CERN = (TH1F*)f_CERN->Get("x_fakes_data");
  h_CERN->SetDirectory(0);
  f_CERN->Close();
  h_CERN->SetFillColor(kBlack);
  h_CERN->SetFillStyle(3004);


  TFile* f_LLR = TFile::Open(file_LLR);
  TH1F* h_LLR = (TH1F*)f_LLR->Get("h_fakes");
  h_LLR->SetDirectory(0);
  f_LLR->Close();
  h_LLR->SetLineColor(1);
  h_LLR->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx()         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad


  h_LLR->SetMinimum(0);
  h_LLR->SetMaximum(1.3*h_LLR->GetMaximum());

  h_LLR->GetXaxis()->SetTitle("MVA(ttH,ttbar/ttV) bin");
  h_LLR->GetYaxis()->SetTitle("Events");
  h_LLR->GetYaxis()->SetTitleOffset(1.5);
  h_LLR->SetTitle("");
  h_LLR->SetStats(0);

  h_LLR->Draw();
  h_CERN->Draw("histsame");
  h_LLR->Draw("same");

  TLegend* leg=new TLegend(0.5,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->SetHeader(Form("Yield CERN/LLR = %f",h_CERN->Integral()/h_LLR->Integral()));
  leg->AddEntry(h_CERN,"CERN");
  leg->AddEntry(h_LLR,"LLR");
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_LLR->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0.5, 0.001, 0.5, h_LLR->GetMaximum(), 0.001,h_LLR->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  TLatex *texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Data %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");


  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)(h_LLR)->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_CERN);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_LLR->GetYaxis()->SetTitleSize(20);
  h_LLR->GetYaxis()->SetTitleFont(43);
  h_LLR->GetYaxis()->SetTitleOffset(1.4);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0.5, 0.01, 0.5, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/CERN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.4);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(18);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(3.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);

  TLine* line=new TLine(0.5,1.,7.5,1.);
  line->SetLineStyle(7);
  line->Draw("same");


  TString filename="MVA_2lSS_ttH_ttbar_datacard_comparison_fakes";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}






void plot_flips(){

  TString file_CERN="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacards_CERN/datacard_CERN_2lss_1tau_4fb.root";
  TString file_LLR="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_pt25.root";

  TFile* f_CERN = TFile::Open(file_CERN);
  TH1F* h_CERN = (TH1F*)f_CERN->Get("x_flips_data");
  h_CERN->SetDirectory(0);
  f_CERN->Close();
  h_CERN->SetFillColor(kBlack);
  h_CERN->SetFillStyle(3007);


  TFile* f_LLR = TFile::Open(file_LLR);
  TH1F* h_LLR = (TH1F*)f_LLR->Get("h_flips");
  h_LLR->SetDirectory(0);
  f_LLR->Close();
  h_LLR->SetLineColor(1);
  h_LLR->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx()         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad


  h_LLR->SetMinimum(0);
  h_LLR->SetMaximum(1.3*h_LLR->GetMaximum());

  h_LLR->GetXaxis()->SetTitle("MVA(ttH,ttbar/ttV) bin");
  h_LLR->GetYaxis()->SetTitle("Events");
  h_LLR->GetYaxis()->SetTitleOffset(1.5);
  h_LLR->SetTitle("");
  h_LLR->SetStats(0);

  h_LLR->Draw();
  h_CERN->Draw("histsame");
  h_LLR->Draw("same");

  TLegend* leg=new TLegend(0.5,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->SetHeader(Form("Yield CERN/LLR = %f",h_CERN->Integral()/h_LLR->Integral()));
  leg->AddEntry(h_CERN,"CERN");
  leg->AddEntry(h_LLR,"LLR");
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_LLR->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0.5, 0.001, 0.5, h_LLR->GetMaximum(), 0.001,h_LLR->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  TLatex *texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Data %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");


  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)(h_LLR)->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_CERN);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_LLR->GetYaxis()->SetTitleSize(20);
  h_LLR->GetYaxis()->SetTitleFont(43);
  h_LLR->GetYaxis()->SetTitleOffset(1.4);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0.5, 0.01, 0.5, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/CERN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.4);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(18);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(3.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);

  TLine* line=new TLine(0.5,1.,7.5,1.);
  line->SetLineStyle(7);
  line->Draw("same");


  TString filename="MVA_2lSS_ttH_ttbar_datacard_comparison_flips";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}



void plot_Diboson(){

  TString file_CERN="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacards_CERN/datacard_CERN_2lss_1tau_4fb.root";
  TString file_LLR="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_pt25.root";

  TFile* f_CERN = TFile::Open(file_CERN);
  TH1F* h_CERN = (TH1F*)f_CERN->Get("x_WZ");

  h_CERN->SetDirectory(0);
  f_CERN->Close();
  h_CERN->SetFillColor(kViolet-5);

  TFile* f_LLR = TFile::Open(file_LLR);
  TH1F* h_LLR = (TH1F*)f_LLR->Get("h_WZ");
  h_LLR->Add( (TH1F*)f_LLR->Get("h_ZZ") );

  h_LLR->SetDirectory(0);
  f_LLR->Close();
  h_LLR->SetLineColor(1);
  h_LLR->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx()         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad


  h_LLR->SetMinimum(0);
  h_LLR->SetMaximum(1.3*h_LLR->GetMaximum());

  h_LLR->GetXaxis()->SetTitle("MVA(ttH,ttbar/ttV) bin");
  h_LLR->GetYaxis()->SetTitle("Events");
  h_LLR->GetYaxis()->SetTitleOffset(1.5);
  h_LLR->SetTitle("");
  h_LLR->SetStats(0);

  h_LLR->Draw();
  h_CERN->Draw("histsame");
  h_LLR->Draw("same");

  TLegend* leg=new TLegend(0.5,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->SetHeader(Form("Yield CERN/LLR = %f",h_CERN->Integral()/h_LLR->Integral()));
  leg->AddEntry(h_CERN,"CERN");
  leg->AddEntry(h_LLR,"LLR");
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_LLR->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0.5, 0.001, 0.5, h_LLR->GetMaximum(), 0.001,h_LLR->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  TLatex *texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Simulation %.1f fb^{-1}",luminosity/1000.));
  texl->SetTextSize(0.04);
  texl->Draw("same");


  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)(h_LLR)->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_CERN);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_LLR->GetYaxis()->SetTitleSize(20);
  h_LLR->GetYaxis()->SetTitleFont(43);
  h_LLR->GetYaxis()->SetTitleOffset(1.4);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0.5, 0.01, 0.5, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/CERN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.4);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(18);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(3.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);

  TLine* line=new TLine(0.5,1.,7.5,1.);
  line->SetLineStyle(7);
  line->Draw("same");


  TString filename="MVA_2lSS_ttH_ttbar_datacard_comparison_Diboson";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}




void plot_ttH_cat(TString cat, TString sample){

  //TString file_CERN="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacards_CERN/preliminary_cards_hig16022_4fb.r7029/"+cat+".input.root";
  //TString file_LLR="/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MVA_2lSS_allcat_syst.root";

  TString file_CERN="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacards_CERN/decay_channel_split_datacards_hig16022_12p9fb.r7063/"+cat+".input.root";
  TString file_LLR="/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MVA_2lSS_allcat_syst_12.9fb.root";

  TFile* f_CERN = TFile::Open(file_CERN);

  TString histoname = "x_"+sample;
  if(sample=="ttW")
    histoname="x_TTW";
  else if(sample=="fakes")
    histoname="x_fakes_data";
  else if(sample=="flips")
    histoname="x_flips_data";

  TH1F* h_CERN = (TH1F*)f_CERN->Get(histoname);
  h_CERN->SetDirectory(0);
  f_CERN->Close();
  if(sample=="ttH" || sample=="ttH_htt")
    h_CERN->SetFillColor(kRed);
  else if(sample=="ttH_hww")
    h_CERN->SetFillColor(kOrange);
  else if(sample=="ttH_hzz")
    h_CERN->SetFillColor(kOrange+2);
  else if(sample=="TTZ")
    h_CERN->SetFillColor(kSpring-5);
  else if(sample=="ttW")
    h_CERN->SetFillColor(kSpring-6);
  else if(sample=="fakes"){
    h_CERN->SetFillColor(kBlack);
    h_CERN->SetFillStyle(3004);
  }
  else if(sample=="flips"){
    h_CERN->SetFillColor(kBlack);
    h_CERN->SetFillStyle(3007);
  }

  TFile* f_LLR = TFile::Open(file_LLR);
  TH1F* h_LLR = (TH1F*)f_LLR->Get(cat+"/h_"+sample);
  h_LLR->SetDirectory(0);
  f_LLR->Close();
  h_LLR->SetLineColor(1);
  h_LLR->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  //pad1->SetGridx()         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad


  h_LLR->SetMinimum(0);
  h_LLR->SetMaximum(1.3*max(h_LLR->GetMaximum(),h_CERN->GetMaximum()));

  h_LLR->GetXaxis()->SetTitle("MVA(ttH,ttbar/ttV) bin");
  h_LLR->GetYaxis()->SetTitle("Events");
  h_LLR->GetYaxis()->SetTitleOffset(1.5);
  h_LLR->SetTitle("");
  h_LLR->SetStats(0);

  h_LLR->Draw();
  h_CERN->Draw("histsame");
  h_LLR->Draw("same");


  TLegend* leg=new TLegend(0.5,0.7,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->SetHeader(Form("Yield CMG/LLR = %f",h_CERN->Integral()/h_LLR->Integral()));
  leg->AddEntry(h_CERN,"CMG");
  leg->AddEntry(h_LLR,"LLR");
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_LLR->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0.5, 0.001, 0.5, h_LLR->GetMaximum(), 0.001,h_LLR->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();
  

  TLatex *texl;

  if(sample=="ttH")
    texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH %.1f fb^{-1}",luminosity/1000.));
  else if(sample=="ttH_htt")
    texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH H#rightarrow#tau#tau %.1f fb^{-1}",luminosity/1000.));
  else if(sample=="ttH_hww")
    texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH H#rightarrowWW %.1f fb^{-1}",luminosity/1000.));
  else if(sample=="ttH_hzz")
    texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH H#rightarrowZZ %.1f fb^{-1}",luminosity/1000.));
  else if(sample=="TTZ")
    texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttZ %.1f fb^{-1}",luminosity/1000.));
  else if(sample=="ttW")
    texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttW %.1f fb^{-1}",luminosity/1000.));
  else if(sample=="fakes" || sample=="flips")
    texl = new TLatex(0.51,1.01*h_LLR->GetMaximum(),Form("CMS Preliminary, #sqrt{s}=13 TeV, %.1f fb^{-1}",luminosity/1000.));


  texl->SetTextSize(0.04);
  texl->Draw("same");


  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)(h_LLR)->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_CERN);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_LLR->GetYaxis()->SetTitleSize(20);
  h_LLR->GetYaxis()->SetTitleFont(43);
  h_LLR->GetYaxis()->SetTitleOffset(1.4);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0.5, 0.01, 0.5, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/CMG");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.4);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(18);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(3.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);

  TLine* line=new TLine(0.5,1.,7.5,1.);
  line->SetLineStyle(7);
  line->Draw("same");


  TString filename="MVA_2lSS_ttH_ttbar_datacard_comparison_ttH_cat_"+cat+"_"+sample;
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

}



void plot_ttH_htt_all_cat(){


  plot_ttH_cat("ttH_2lss_1tau","ttH_htt");
  plot_ttH_cat("ttH_2lss_ee_0tau_neg","ttH_htt");
  plot_ttH_cat("ttH_2lss_ee_0tau_pos","ttH_htt");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_neg","ttH_htt");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_pos","ttH_htt");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_neg","ttH_htt");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_pos","ttH_htt");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_neg","ttH_htt");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_pos","ttH_htt");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_neg","ttH_htt");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_pos","ttH_htt");


}




void plot_ttH_hww_all_cat(){


  plot_ttH_cat("ttH_2lss_1tau","ttH_hww");
  plot_ttH_cat("ttH_2lss_ee_0tau_neg","ttH_hww");
  plot_ttH_cat("ttH_2lss_ee_0tau_pos","ttH_hww");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_neg","ttH_hww");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_pos","ttH_hww");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_neg","ttH_hww");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_pos","ttH_hww");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_neg","ttH_hww");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_pos","ttH_hww");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_neg","ttH_hww");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_pos","ttH_hww");


}




void plot_ttH_hzz_all_cat(){


  plot_ttH_cat("ttH_2lss_1tau","ttH_hzz");
  plot_ttH_cat("ttH_2lss_ee_0tau_neg","ttH_hzz");
  plot_ttH_cat("ttH_2lss_ee_0tau_pos","ttH_hzz");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_neg","ttH_hzz");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_pos","ttH_hzz");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_neg","ttH_hzz");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_pos","ttH_hzz");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_neg","ttH_hzz");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_pos","ttH_hzz");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_neg","ttH_hzz");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_pos","ttH_hzz");


}




void plot_ttZ_all_cat(){


  plot_ttH_cat("ttH_2lss_1tau","TTZ");
  plot_ttH_cat("ttH_2lss_ee_0tau_neg","TTZ");
  plot_ttH_cat("ttH_2lss_ee_0tau_pos","TTZ");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_neg","TTZ");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_pos","TTZ");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_neg","TTZ");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_pos","TTZ");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_neg","TTZ");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_pos","TTZ");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_neg","TTZ");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_pos","TTZ");


}





void plot_ttW_all_cat(){


  plot_ttH_cat("ttH_2lss_1tau","ttW");
  plot_ttH_cat("ttH_2lss_ee_0tau_neg","ttW");
  plot_ttH_cat("ttH_2lss_ee_0tau_pos","ttW");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_neg","ttW");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_pos","ttW");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_neg","ttW");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_pos","ttW");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_neg","ttW");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_pos","ttW");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_neg","ttW");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_pos","ttW");


}





void plot_Fakes_all_cat(){


  plot_ttH_cat("ttH_2lss_1tau","fakes");
  plot_ttH_cat("ttH_2lss_ee_0tau_neg","fakes");
  plot_ttH_cat("ttH_2lss_ee_0tau_pos","fakes");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_neg","fakes");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_pos","fakes");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_neg","fakes");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_pos","fakes");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_neg","fakes");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_pos","fakes");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_neg","fakes");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_pos","fakes");


}




void plot_flips_all_cat(){


  plot_ttH_cat("ttH_2lss_1tau","flips");
  plot_ttH_cat("ttH_2lss_ee_0tau_neg","flips");
  plot_ttH_cat("ttH_2lss_ee_0tau_pos","flips");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_neg","flips");
  plot_ttH_cat("ttH_2lss_em_0tau_bl_pos","flips");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_neg","flips");
  plot_ttH_cat("ttH_2lss_em_0tau_bt_pos","flips");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_neg","flips");
  plot_ttH_cat("ttH_2lss_mm_0tau_bl_pos","flips");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_neg","flips");
  plot_ttH_cat("ttH_2lss_mm_0tau_bt_pos","flips");


}
















