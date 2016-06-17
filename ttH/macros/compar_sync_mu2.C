#include <fstream>
#include <iostream>
#include <sstream>
#include <TString.h>
#include <TFile.h>
#include <TChain.h>
#include <TBranch.h>
#include <TH1F.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TGaxis.h>






void compar_pt_mu(){

  TString file1= "/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_02_2016/syncNtuple.root";
  TString file2= "/data_CMS/cms/strebler/ttH_Samples/syncNtuples/MiniAODv2_prod_02_2016/syncNtuple.root";

  TChain * tree1 = new TChain("syncTree");
  tree1->Add(file1);
  TH1F* h1 = new TH1F("h1","h1",100,0,500);
  tree1->Draw("mu0_pt>>h1","n_presel_mu>=1","goff");

  TChain * tree2 = new TChain("syncTree");
  tree2->Add(file2);
  TH1F* h2 = new TH1F("h2","h2",100,0,500);
  tree2->Draw("mu0_pt>>h2","n_presel_mu>=1","goff");


  h1->SetTitle("Leading Muon pT");
  h1->SetStats(0);
  h1->SetMaximum(1.25*h1->GetMaximum());

  h1->SetLineColor(kOrange-2);
  h1->SetFillColor(kOrange-2);

  h2->SetLineColor(1);
  h2->SetLineWidth(2);
  
  
  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(h1,"1");
  leg->AddEntry(h2,"2");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);


  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  h1->GetYaxis()->SetTitle("Number of events / 5 GeV");
  h2->GetXaxis()->SetTitle("p_{T} [GeV]");
  
  h1->Draw();
  h2->Draw("same");
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h1->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.5, 0, h1->GetMaximum(), 0.5,h1->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();
  
   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h1->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.9);  // Define Y ..
  h_ratio->SetMaximum(1.1); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h2);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw("histp");       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h1->GetYaxis()->SetTitleSize(20);
  h1->GetYaxis()->SetTitleFont(43);
  h1->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.91, 0, 1.09, 0.91, 1.09, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("1/2");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);


  TString plotname="sync_pt_mu0";
  c->SaveAs(plotname+".pdf");
  c->SaveAs(plotname+".png");

  return;

}
