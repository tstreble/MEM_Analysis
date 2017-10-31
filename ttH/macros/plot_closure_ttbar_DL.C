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
#include <TGaxis.h>
#include <TLine.h>

using namespace std;




void plot_pT_lead_lep(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS","recolep_sel_pt[0]","MC_weight*(category==11 && !isGenMatched)",20,0.,200));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS_lepMVA_CR","recolep_sel_pt[0]","MC_weight*event_weight_ttH*(category==41)",20,0.,200));

  vector<TString> leg_entry;
  leg_entry.push_back("Signal region");
  leg_entry.push_back("Fake extrapolation");

  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<h.size();i++){
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h[0]->SetLineColor(kOrange-2);
  h[0]->SetFillColor(kOrange-2);
  h[0]->SetStats(0);
  h[0]->SetTitle("");

  h[1]->SetLineColor(1);
  h[1]->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  for(unsigned int i=0;i<h.size();i++){
    h[i]->SetMaximum(1.25*h[0]->GetMaximum());
    h[i]->GetXaxis()->SetTitle("Leading lepton p_{T} [GeV]");
    h[i]->GetYaxis()->SetTitle("a.u.");
    h[i]->GetYaxis()->SetTitleOffset(1.7);
  }

  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1),1.01*h[0]->GetMaximum(),"CMS Preliminary, Simulation t#bar{t} DL #sqrt{s}=13 TeV");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  h[0]->Draw("hist");
  h[1]->Draw("same");
  leg->Draw("same");
  texl->Draw("same");
  
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.01, 0, h[0]->GetMaximum(), 0.01, h[0]->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();
  
   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h[1]->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h[0]);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.01, 0, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Extrap./SR");
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


  TLine* line = new TLine(0., 1., 200.,1.);
  line->Draw("same");

  TString plotname="lead_lep_pT_fake_extrap";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}





void plot_pT_sublead_lep(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS","recolep_sel_pt[1]","MC_weight*(category==11 && !isGenMatched)",20,0.,100));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS_lepMVA_CR","recolep_sel_pt[1]","MC_weight*event_weight_ttH*(category==41)",20,0.,100));

  vector<TString> leg_entry;
  leg_entry.push_back("Signal region");
  leg_entry.push_back("Fake extrapolation");

  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<h.size();i++){
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h[0]->SetLineColor(kOrange-2);
  h[0]->SetFillColor(kOrange-2);
  h[0]->SetStats(0);
  h[0]->SetTitle("");

  h[1]->SetLineColor(1);
  h[1]->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  for(unsigned int i=0;i<h.size();i++){
    h[i]->SetMaximum(1.25*h[0]->GetMaximum());
    h[i]->GetXaxis()->SetTitle("Subleading lepton p_{T} [GeV]");
    h[i]->GetYaxis()->SetTitle("a.u.");
    h[i]->GetYaxis()->SetTitleOffset(1.7);
  }

  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1),1.01*h[0]->GetMaximum(),"CMS Preliminary, Simulation t#bar{t} DL #sqrt{s}=13 TeV");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  h[0]->Draw("hist");
  h[1]->Draw("same");
  leg->Draw("same");
  texl->Draw("same");
  
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.01, 0, h[0]->GetMaximum(), 0.01, h[0]->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();
  
   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h[1]->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h[0]);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.01, 0, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Extrap./SR");
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


  TLine* line = new TLine(0., 1., 100.,1.);
  line->Draw("same");

  TString plotname="sublead_lep_pT_fake_extrap";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}






void plot_pT_tauh(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS","recotauh_sel_pt[0]","MC_weight*(category==11 && !isGenMatched)",20,0.,200));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS_lepMVA_CR","recotauh_sel_pt[0]","MC_weight*event_weight_ttH*(category==41)",20,0.,200));

  vector<TString> leg_entry;
  leg_entry.push_back("Signal region");
  leg_entry.push_back("Fake extrapolation");

  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<h.size();i++){
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h[0]->SetLineColor(kOrange-2);
  h[0]->SetFillColor(kOrange-2);
  h[0]->SetStats(0);
  h[0]->SetTitle("");

  h[1]->SetLineColor(1);
  h[1]->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  for(unsigned int i=0;i<h.size();i++){
    h[i]->SetMaximum(1.25*h[0]->GetMaximum());
    h[i]->GetXaxis()->SetTitle("p_{T}(#tau_{h}) [GeV]");
    h[i]->GetYaxis()->SetTitle("a.u.");
    h[i]->GetYaxis()->SetTitleOffset(1.7);
  }

  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1),1.01*h[0]->GetMaximum(),"CMS Preliminary, Simulation t#bar{t} DL #sqrt{s}=13 TeV");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  h[0]->Draw("hist");
  h[1]->Draw("same");
  leg->Draw("same");
  texl->Draw("same");
  
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.01, 0, h[0]->GetMaximum(), 0.01, h[0]->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();
  
   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h[1]->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h[0]);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.01, 0, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Extrap./SR");
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


  TLine* line = new TLine(0., 1., 200.,1.);
  line->Draw("same");

  TString plotname="tau_pT_fake_extrap";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}








void plot_pT_lead_jet(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS","recoPFJet_pt[0]","MC_weight*(category==11 && !isGenMatched)",20,0.,400));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS_lepMVA_CR","recoPFJet_pt[0]","MC_weight*event_weight_ttH*(category==41)",20,0.,400));

  vector<TString> leg_entry;
  leg_entry.push_back("Signal region");
  leg_entry.push_back("Fake extrapolation");

  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<h.size();i++){
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }

  double d2N, d2D;
  double N = h[1]->IntegralAndError(0,h[1]->GetNbinsX(),d2N);
  double D = h[0]->IntegralAndError(0,h[0]->GetNbinsX(),d2D);

  cout<<"Extrap./SR="<<N/D<<" +/- "<<TMath::Sqrt(d2N/(D*D) + N*N/pow(D,4)*d2D)<<endl;


  h[0]->SetLineColor(kOrange-2);
  h[0]->SetFillColor(kOrange-2);
  h[0]->SetStats(0);
  h[0]->SetTitle("");

  h[1]->SetLineColor(1);
  h[1]->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  for(unsigned int i=0;i<h.size();i++){
    h[i]->SetMaximum(1.25*h[0]->GetMaximum());
    h[i]->GetXaxis()->SetTitle("Leading jet p_{T} [GeV]");
    h[i]->GetYaxis()->SetTitle("a.u.");
    h[i]->GetYaxis()->SetTitleOffset(1.7);
  }

  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1),1.01*h[0]->GetMaximum(),"CMS Preliminary, Simulation t#bar{t} DL #sqrt{s}=13 TeV");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  h[0]->Draw("hist");
  h[1]->Draw("same");
  leg->Draw("same");
  texl->Draw("same");
  
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.01, 0, h[0]->GetMaximum(), 0.01, h[0]->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();
  
   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h[1]->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h[0]);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.01, 0, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Extrap./SR");
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


  TLine* line = new TLine(0., 1., 400.,1.);
  line->Draw("same");

  TString plotname="lead_jet_pT_fake_extrap";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}






void plot_CSV_lead_jet(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS","recoPFJet_CSVscore[0]","MC_weight*(category==11 && !isGenMatched)",20,0.,1.));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS_lepMVA_CR","recoPFJet_CSVscore[0]","MC_weight*event_weight_ttH*(category==41)",20,0.,1.));

  vector<TString> leg_entry;
  leg_entry.push_back("Signal region");
  leg_entry.push_back("Fake extrapolation");

  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<h.size();i++){
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h[0]->SetLineColor(kOrange-2);
  h[0]->SetFillColor(kOrange-2);
  h[0]->SetStats(0);
  h[0]->SetTitle("");

  h[1]->SetLineColor(1);
  h[1]->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  for(unsigned int i=0;i<h.size();i++){
    h[i]->SetMaximum(1.25*h[0]->GetMaximum());
    h[i]->GetXaxis()->SetTitle("Leading jet CSV");
    h[i]->GetYaxis()->SetTitle("a.u.");
    h[i]->GetYaxis()->SetTitleOffset(1.7);
  }

  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1),1.01*h[0]->GetMaximum(),"CMS Preliminary, Simulation t#bar{t} DL #sqrt{s}=13 TeV");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  h[0]->Draw("hist");
  h[1]->Draw("same");
  leg->Draw("same");
  texl->Draw("same");
  
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.01, 0, h[0]->GetMaximum(), 0.01, h[0]->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();
  
   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h[1]->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h[0]);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.01, 0, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Extrap./SR");
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


  TLine* line = new TLine(0., 1., 1.,1.);
  line->Draw("same");

  TString plotname="lead_jet_CSV_fake_extrap";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}




void plot_pT_sublead_jet(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS","recoPFJet_pt[1]","MC_weight*(category==11 && !isGenMatched)",20,0.,300));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS_lepMVA_CR","recoPFJet_pt[1]","MC_weight*event_weight_ttH*(category==41)",20,0.,300));

  vector<TString> leg_entry;
  leg_entry.push_back("Signal region");
  leg_entry.push_back("Fake extrapolation");

  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<h.size();i++){
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h[0]->SetLineColor(kOrange-2);
  h[0]->SetFillColor(kOrange-2);
  h[0]->SetStats(0);
  h[0]->SetTitle("");

  h[1]->SetLineColor(1);
  h[1]->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  for(unsigned int i=0;i<h.size();i++){
    h[i]->SetMaximum(1.25*h[0]->GetMaximum());
    h[i]->GetXaxis()->SetTitle("Subleading jet p_{T} [GeV]");
    h[i]->GetYaxis()->SetTitle("a.u.");
    h[i]->GetYaxis()->SetTitleOffset(1.7);
  }

  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1),1.01*h[0]->GetMaximum(),"CMS Preliminary, Simulation t#bar{t} DL #sqrt{s}=13 TeV");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  h[0]->Draw("hist");
  h[1]->Draw("same");
  leg->Draw("same");
  texl->Draw("same");
  
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.01, 0, h[0]->GetMaximum(), 0.01, h[0]->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();
  
   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h[1]->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h[0]);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.01, 0, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Extrap./SR");
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


  TLine* line = new TLine(0., 1., 300.,1.);
  line->Draw("same");

  TString plotname="sublead_jet_pT_fake_extrap";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}








void plot_n_jet(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS","n_recoPFJet","MC_weight*(category==11 && !isGenMatched)",8,2.,10.));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS_lepMVA_CR","n_recoPFJet","MC_weight*event_weight_ttH*(category==41)",8,2.,10.));

  vector<TString> leg_entry;
  leg_entry.push_back("Signal region");
  leg_entry.push_back("Fake extrapolation");

  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<h.size();i++){
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h[0]->SetLineColor(kOrange-2);
  h[0]->SetFillColor(kOrange-2);
  h[0]->SetStats(0);
  h[0]->SetTitle("");

  h[1]->SetLineColor(1);
  h[1]->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  for(unsigned int i=0;i<h.size();i++){
    h[i]->SetMaximum(1.25*h[0]->GetMaximum());
    h[i]->GetXaxis()->SetTitle("N(jets)");
    h[i]->GetYaxis()->SetTitle("a.u.");
    h[i]->GetYaxis()->SetTitleOffset(1.7);
  }

  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1),1.01*h[0]->GetMaximum(),"CMS Preliminary, Simulation t#bar{t} DL #sqrt{s}=13 TeV");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  h[0]->Draw("hist");
  h[1]->Draw("same");
  leg->Draw("same");
  texl->Draw("same");
  
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 2., 0.01, 2., h[0]->GetMaximum(), 0.01, h[0]->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();
  
   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h[1]->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h[0]);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 2., 0.01, 2., 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Extrap./SR");
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


  TLine* line = new TLine(2., 1., 10.,1.);
  line->Draw("same");

  TString plotname="n_jet_fake_extrap";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}







void plot_PFMET(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS","PFMET","MC_weight*(category==11 && !isGenMatched)",20,0.,400.));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split.root","HTauTauTree_2lSS_lepMVA_CR","PFMET","MC_weight*event_weight_ttH*(category==41)",20,0.,400.));

  vector<TString> leg_entry;
  leg_entry.push_back("Signal region");
  leg_entry.push_back("Fake extrapolation");

  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<h.size();i++){
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }

  h[0]->SetLineColor(kOrange-2);
  h[0]->SetFillColor(kOrange-2);
  h[0]->SetStats(0);
  h[0]->SetTitle("");

  h[1]->SetLineColor(1);
  h[1]->SetLineWidth(2);

  TCanvas* c=new TCanvas("c","c",650,600);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetLeftMargin(0.15);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  for(unsigned int i=0;i<h.size();i++){
    h[i]->SetMaximum(1.25*h[0]->GetMaximum());
    h[i]->GetXaxis()->SetTitle("MET [GeV]");
    h[i]->GetYaxis()->SetTitle("a.u.");
    h[i]->GetYaxis()->SetTitleOffset(1.7);
  }

  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1),1.01*h[0]->GetMaximum(),"CMS Preliminary, Simulation t#bar{t} DL #sqrt{s}=13 TeV");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  h[0]->Draw("hist");
  h[1]->Draw("same");
  leg->Draw("same");
  texl->Draw("same");
  
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.01, 0, h[0]->GetMaximum(), 0.01, h[0]->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();
  
   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetLeftMargin(0.15);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.35);
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h[1]->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.);  // Define Y ..
  h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h[0]);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.01, 0, 1.99, 0.01, 1.99, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("Extrap./SR");
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


  TLine* line = new TLine(0., 1., 400.,1.);
  line->Draw("same");

  TString plotname="PFMET_fake_extrap";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;


}
