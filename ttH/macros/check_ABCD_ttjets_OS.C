#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <THStack.h>
#include <iostream>
#include <TLegend.h>
#include <Helpers.C>
#include <vector>
#include <TLatex.h>
#include <TGraphErrors.h>
#include <TGaxis.h>

using namespace std;





void plot_tauh_pt_OS_B(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_B_SS = single_plot(files,"HTauTauTree","recotauh_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",15,0,150);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","recotauh_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",15,0,150);

  TH1F* h_F = single_plot(files,"HTauTauTree","recotauh_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",15,0,150);
  h_F->Scale(h_B_OS->Integral()/h_F->Integral());
 
  h_B_SS->SetLineWidth(2);
  h_B_SS->SetLineColor(kBlue+2);

  h_B_OS->SetLineWidth(2);
  h_B_OS->SetLineColor(kBlue-4);

  THStack* h_B = new THStack("h_B","");
  h_B->Add(h_B_OS);
  h_B->Add(h_B_SS);

  h_F->SetFillColor(kRed+1);
  h_F->SetLineColor(kRed+1);
  h_F->SetLineWidth(0);
  h_F->SetMaximum(15*h_B->GetMaximum());
  h_F->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_B_OS,"#splitline{#leq 1 #tau_{h}, SS loose + tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_B_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_F,"#splitline{#leq 1 #tau_{h}, OS loose + tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_F->Draw("");
  h_B->Draw("same");
  leg->Draw("same");

  h_F->GetYaxis()->SetTitle("a. u.");
  h_F->GetYaxis()->SetTitleOffset(1.65);
  h_F->SetTitle("");
  h_F->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.07*h_F->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_B_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_F2 = (*h_F);
  h_F2.Sumw2();
  h_ratio->Divide(&h_F2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_F->GetYaxis()->SetTitleSize(20);
  h_F->GetYaxis()->SetTitleFont(43);
  h_F->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(B)/F");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(#tau_{h}) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="tauh_pt_check_ABCD_OS_B";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_tauh_pt_OS_A(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A_SS = single_plot(files,"HTauTauTree","recotauh_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",15,0,150);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","recotauh_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",15,0,150);

  TH1F* h_E = single_plot(files,"HTauTauTree","recotauh_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",15,0,150);
  h_E->Scale(h_A_OS->Integral()/h_E->Integral());
 
  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);

  h_E->SetFillColor(kRed+1);
  h_E->SetLineColor(kRed+1);
  h_E->SetLineWidth(0);
  h_E->SetMaximum(15*h_A->GetMaximum());
  h_E->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_E,"#splitline{#leq 1 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_E->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_E->GetYaxis()->SetTitle("a. u.");
  h_E->GetYaxis()->SetTitleOffset(1.65);
  h_E->SetTitle("");
  h_E->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.07*h_E->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_E2 = (*h_E);
  h_E2.Sumw2();
  h_ratio->Divide(&h_E2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_E->GetYaxis()->SetTitleSize(20);
  h_E->GetYaxis()->SetTitleFont(43);
  h_E->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(A)/E");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(#tau_{h}) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="tauh_pt_check_ABCD_OS_A";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_tauh_eta_OS_B(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_B_SS = single_plot(files,"HTauTauTree","recotauh_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","recotauh_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_F = single_plot(files,"HTauTauTree","recotauh_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",12,-2.4,2.4);
  h_F->Scale(h_B_OS->Integral()/h_F->Integral());
 
  h_B_SS->SetLineWidth(2);
  h_B_SS->SetLineColor(kBlue+2);

  h_B_OS->SetLineWidth(2);
  h_B_OS->SetLineColor(kBlue-4);

  THStack* h_B = new THStack("h_B","");
  h_B->Add(h_B_OS);
  h_B->Add(h_B_SS);

  h_F->SetFillColor(kRed+1);
  h_F->SetLineColor(kRed+1);
  h_F->SetLineWidth(0);
  h_F->SetMaximum(350*h_B->GetMaximum());
  h_F->SetMinimum(5);
  h_F->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.55,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_B_OS,"#splitline{#leq 1 #tau_{h}, SS loose + tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_B_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_F,"#splitline{#leq 1 #tau_{h}, OS loose + tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_F->Draw("");
  h_B->Draw("same");
  leg->Draw("same");

  h_F->GetYaxis()->SetTitle("a. u.");
  h_F->GetYaxis()->SetTitleOffset(1.65);
  h_F->SetTitle("");
  h_F->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.07*h_F->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_B_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_F2 = (*h_F);
  h_F2.Sumw2();
  h_ratio->Divide(&h_F2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_F->GetYaxis()->SetTitleSize(20);
  h_F->GetYaxis()->SetTitleFont(43);
  h_F->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(B)/F");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(#tau_{h})");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="tauh_eta_check_ABCD_OS_B";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_tauh_eta_OS_A(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A_SS = single_plot(files,"HTauTauTree","recotauh_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","recotauh_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_E = single_plot(files,"HTauTauTree","recotauh_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",12,-2.4,2.4);
  h_E->Scale(h_A_OS->Integral()/h_E->Integral());
 
  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);

  h_E->SetFillColor(kRed+1);
  h_E->SetLineColor(kRed+1);
  h_E->SetLineWidth(0);
  h_E->SetMaximum(50*h_A->GetMaximum());
  h_E->SetMinimum(0.5);
  h_E->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_E,"#splitline{#leq 1 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_E->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_E->GetYaxis()->SetTitle("a. u.");
  h_E->GetYaxis()->SetTitleOffset(1.65);
  h_E->SetTitle("");
  h_E->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.07*h_E->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_E2 = (*h_E);
  h_E2.Sumw2();
  h_ratio->Divide(&h_E2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_E->GetYaxis()->SetTitleSize(20);
  h_E->GetYaxis()->SetTitleFont(43);
  h_E->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(A)/E");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(#tau_{h})");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="tauh_eta_check_ABCD_OS_A";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_jet0_pt_OS_B(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_B_SS = single_plot(files,"HTauTauTree","recoPFJet_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,400);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","recoPFJet_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,400);

  TH1F* h_F = single_plot(files,"HTauTauTree","recoPFJet_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",20,0,400);
  h_F->Scale(h_B_OS->Integral()/h_F->Integral());
 
  h_B_SS->SetLineWidth(2);
  h_B_SS->SetLineColor(kBlue+2);

  h_B_OS->SetLineWidth(2);
  h_B_OS->SetLineColor(kBlue-4);

  THStack* h_B = new THStack("h_B","");
  h_B->Add(h_B_OS);
  h_B->Add(h_B_SS);

  h_F->SetFillColor(kRed+1);
  h_F->SetLineColor(kRed+1);
  h_F->SetLineWidth(0);
  h_F->SetMaximum(100*h_B->GetMaximum());
  h_F->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_B_OS,"#splitline{#leq 1 #tau_{h}, SS loose + tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_B_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_F,"#splitline{#leq 1 #tau_{h}, OS loose + tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_F->Draw("");
  h_B->Draw("same");
  leg->Draw("same");

  h_F->GetYaxis()->SetTitle("a. u.");
  h_F->GetYaxis()->SetTitleOffset(1.65);
  h_F->SetTitle("");
  h_F->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.07*h_F->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_B_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_F2 = (*h_F);
  h_F2.Sumw2();
  h_ratio->Divide(&h_F2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_F->GetYaxis()->SetTitleSize(20);
  h_F->GetYaxis()->SetTitleFont(43);
  h_F->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(B)/F");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(lead. jet) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet0_pt_check_ABCD_OS_B";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void plot_jet0_pt_OS_A(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A_SS = single_plot(files,"HTauTauTree","recoPFJet_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,400);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","recoPFJet_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,400);

  TH1F* h_E = single_plot(files,"HTauTauTree","recoPFJet_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",20,0,400);
  h_E->Scale(h_A_OS->Integral()/h_E->Integral());
 
  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);

  h_E->SetFillColor(kRed+1);
  h_E->SetLineColor(kRed+1);
  h_E->SetLineWidth(0);
  h_E->SetMaximum(15*h_A->GetMaximum());
  h_E->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_E,"#splitline{#leq 1 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_E->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_E->GetYaxis()->SetTitle("a. u.");
  h_E->GetYaxis()->SetTitleOffset(1.65);
  h_E->SetTitle("");
  h_E->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.07*h_E->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_E2 = (*h_E);
  h_E2.Sumw2();
  h_ratio->Divide(&h_E2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_E->GetYaxis()->SetTitleSize(20);
  h_E->GetYaxis()->SetTitleFont(43);
  h_E->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(A)/E");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(lead. jet) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet0_pt_check_ABCD_OS_A";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_jet0_pt_OS_C(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_C_SS = single_plot(files,"HTauTauTree","recoPFJet_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,400);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","recoPFJet_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,400);

  TH1F* h_G = single_plot(files,"HTauTauTree","recoPFJet_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",20,0,400);
  h_G->Scale(h_C_OS->Integral()/h_G->Integral());
 
  h_C_SS->SetLineWidth(2);
  h_C_SS->SetLineColor(kBlue+2);

  h_C_OS->SetLineWidth(2);
  h_C_OS->SetLineColor(kBlue-4);

  THStack* h_C = new THStack("h_C","");
  h_C->Add(h_C_OS);
  h_C->Add(h_C_SS);

  h_G->SetFillColor(kRed+1);
  h_G->SetLineColor(kRed+1);
  h_G->SetLineWidth(0);
  h_G->SetMaximum(1.2*h_C->GetMaximum());
  h_G->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_C_OS,"#splitline{0 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_C_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_G,"#splitline{0 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_G->Draw("");
  h_C->Draw("same");
  leg->Draw("same");

  h_G->GetYaxis()->SetTitle("a. u.");
  h_G->GetYaxis()->SetTitleOffset(1.65);
  h_G->SetTitle("");
  h_G->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.02*h_G->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_G->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_G->GetBinLowEdge(1), 0.01*h_G->GetMaximum(), h_G->GetBinLowEdge(1), h_G->GetMaximum(), 0.01*h_G->GetMaximum(),h_G->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_C_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_G2 = (*h_G);
  h_G2.Sumw2();
  h_ratio->Divide(&h_G2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_G->GetYaxis()->SetTitleSize(20);
  h_G->GetYaxis()->SetTitleFont(43);
  h_G->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(C)/G");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(lead. jet) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet0_pt_check_ABCD_OS_C";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_jet0_eta_OS_B(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_B_SS = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_F = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",12,-2.4,2.4);
  h_F->Scale(h_B_OS->Integral()/h_F->Integral());
 
  h_B_SS->SetLineWidth(2);
  h_B_SS->SetLineColor(kBlue+2);

  h_B_OS->SetLineWidth(2);
  h_B_OS->SetLineColor(kBlue-4);

  THStack* h_B = new THStack("h_B","");
  h_B->Add(h_B_OS);
  h_B->Add(h_B_SS);

  h_F->SetFillColor(kRed+1);
  h_F->SetLineColor(kRed+1);
  h_F->SetLineWidth(0);
  h_F->SetMaximum(350*h_B->GetMaximum());
  h_F->SetMinimum(5);
  h_F->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.55,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_B_OS,"#splitline{#leq 1 #tau_{h}, SS loose + tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_B_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_F,"#splitline{#leq 1 #tau_{h}, OS loose + tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_F->Draw("");
  h_B->Draw("same");
  leg->Draw("same");

  h_F->GetYaxis()->SetTitle("a. u.");
  h_F->GetYaxis()->SetTitleOffset(1.65);
  h_F->SetTitle("");
  h_F->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.07*h_F->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_B_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_F2 = (*h_F);
  h_F2.Sumw2();
  h_ratio->Divide(&h_F2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_F->GetYaxis()->SetTitleSize(20);
  h_F->GetYaxis()->SetTitleFont(43);
  h_F->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(B)/F");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(lead. jet)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet0_eta_check_ABCD_OS_B";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_jet0_eta_OS_A(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A_SS = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_E = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",12,-2.4,2.4);
  h_E->Scale(h_A_OS->Integral()/h_E->Integral());
 
  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);

  h_E->SetFillColor(kRed+1);
  h_E->SetLineColor(kRed+1);
  h_E->SetLineWidth(0);
  h_E->SetMaximum(50*h_A->GetMaximum());
  h_E->SetMinimum(0.5);
  h_E->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_E,"#splitline{#leq 1 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_E->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_E->GetYaxis()->SetTitle("a. u.");
  h_E->GetYaxis()->SetTitleOffset(1.65);
  h_E->SetTitle("");
  h_E->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.07*h_E->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_E2 = (*h_E);
  h_E2.Sumw2();
  h_ratio->Divide(&h_E2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_E->GetYaxis()->SetTitleSize(20);
  h_E->GetYaxis()->SetTitleFont(43);
  h_E->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(A)/E");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(lead. jet)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet0_eta_check_ABCD_OS_A";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_jet0_eta_OS_C(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_C_SS = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_G = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",12,-2.4,2.4);
  h_G->Scale(h_C_OS->Integral()/h_G->Integral());
 
  h_C_SS->SetLineWidth(2);
  h_C_SS->SetLineColor(kBlue+2);

  h_C_OS->SetLineWidth(2);
  h_C_OS->SetLineColor(kBlue-4);

  THStack* h_C = new THStack("h_C","");
  h_C->Add(h_C_OS);
  h_C->Add(h_C_SS);

  h_G->SetFillColor(kRed+1);
  h_G->SetLineColor(kRed+1);
  h_G->SetLineWidth(0);
  //h_G->SetMaximum(15*h_C->GetMaximum());
  //h_G->SetMinimum(2.);
  h_G->SetMaximum(1.75*h_C->GetMaximum());
  h_G->SetMinimum(0.);
  
  h_G->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_C_OS,"#splitline{0 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_C_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_G,"#splitline{0 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_G->Draw("");
  h_C->Draw("same");
  leg->Draw("same");

  h_G->GetYaxis()->SetTitle("a. u.");
  h_G->GetYaxis()->SetTitleOffset(1.65);
  h_G->SetTitle("");
  h_G->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.02*h_G->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_G->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_G->GetBinLowEdge(1), 0.01*h_G->GetMaximum(), h_G->GetBinLowEdge(1), h_G->GetMaximum(), 0.01*h_G->GetMaximum(),h_G->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_C_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_G2 = (*h_G);
  h_G2.Sumw2();
  h_ratio->Divide(&h_G2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_G->GetYaxis()->SetTitleSize(20);
  h_G->GetYaxis()->SetTitleFont(43);
  h_G->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(C)/G");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(lead. jet)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet0_eta_check_ABCD_OS_C";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_jet0_eta_OS_C_ee(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_C_SS = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1) && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11)",12,-2.4,2.4);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1) && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11)",12,-2.4,2.4);

  TH1F* h_G = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11)",12,-2.4,2.4);
  h_G->Scale(h_C_OS->Integral()/h_G->Integral());
 
  h_C_SS->SetLineWidth(2);
  h_C_SS->SetLineColor(kBlue+2);

  h_C_OS->SetLineWidth(2);
  h_C_OS->SetLineColor(kBlue-4);

  THStack* h_C = new THStack("h_C","");
  h_C->Add(h_C_OS);
  h_C->Add(h_C_SS);

  h_G->SetFillColor(kRed+1);
  h_G->SetLineColor(kRed+1);
  h_G->SetLineWidth(0);
  //h_G->SetMaximum(15*h_C->GetMaximum());
  //h_G->SetMinimum(2.);
  h_G->SetMaximum(1.5*h_C->GetMaximum());
  h_G->SetMinimum(0.);
  
  h_G->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetHeader("Dielectron channel");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_C_OS,"#splitline{0 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_C_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_G,"#splitline{0 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_G->Draw("");
  h_C->Draw("same");
  leg->Draw("same");

  h_G->GetYaxis()->SetTitle("a. u.");
  h_G->GetYaxis()->SetTitleOffset(1.65);
  h_G->SetTitle("");
  h_G->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.07*h_G->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_C_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_G2 = (*h_G);
  h_G2.Sumw2();
  h_ratio->Divide(&h_G2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_G->GetYaxis()->SetTitleSize(20);
  h_G->GetYaxis()->SetTitleFont(43);
  h_G->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(C)/G");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(lead. jet)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet0_eta_check_ABCD_OS_C_ee";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_genb_eta_OS_C(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_C_SS = single_plot(files,"HTauTauTree","genb_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1) && n_genb==2 && genb_pt[0]>genb_pt[1])",15,-3.,3.);

  h_C_SS->Add(single_plot(files,"HTauTauTree","genb_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1 && n_genb==2 && genb_pt[1]>genb_pt[0]))",15,-3.,3.));

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","genb_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1) && n_genb==2 && genb_pt[0]>genb_pt[1])",15,-3.,3.);

  h_C_OS->Add(single_plot(files,"HTauTauTree","genb_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1) && n_genb==2 && genb_pt[1]>genb_pt[0])",15,-3.,3.));

  TH1F* h_G = single_plot(files,"HTauTauTree","genb_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)  && n_genb==2 && genb_pt[0]>genb_pt[1])",15,-3.,3.);
  h_G->Add(single_plot(files,"HTauTauTree","genb_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)  && n_genb==2 && genb_pt[1]>genb_pt[0])",15,-3.,3.));
  h_G->Scale(h_C_OS->Integral()/h_G->Integral());
 
  h_C_SS->SetLineWidth(2);
  h_C_SS->SetLineColor(kBlue+2);

  h_C_OS->SetLineWidth(2);
  h_C_OS->SetLineColor(kBlue-4);

  THStack* h_C = new THStack("h_C","");
  h_C->Add(h_C_OS);
  h_C->Add(h_C_SS);

  h_G->SetFillColor(kRed+1);
  h_G->SetLineColor(kRed+1);
  h_G->SetLineWidth(0);
  //h_G->SetMaximum(15*h_C->GetMaximum());
  //h_G->SetMinimum(2.);
  h_G->SetMaximum(1.5*h_C->GetMaximum());
  h_G->SetMinimum(0.);
  
  h_G->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_C_OS,"#splitline{0 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_C_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_G,"#splitline{0 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_G->Draw("");
  h_C->Draw("same");
  leg->Draw("same");

  h_G->GetYaxis()->SetTitle("a. u.");
  h_G->GetYaxis()->SetTitleOffset(1.65);
  h_G->SetTitle("");
  h_G->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.07*h_G->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_C_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_G2 = (*h_G);
  h_G2.Sumw2();
  h_ratio->Divide(&h_G2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_G->GetYaxis()->SetTitleSize(20);
  h_G->GetYaxis()->SetTitleFont(43);
  h_G->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(C)/G");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(lead. b quark)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="genb0_eta_check_ABCD_OS_C";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_jet1_pt_OS_B(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_B_SS = single_plot(files,"HTauTauTree","recoPFJet_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,400);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","recoPFJet_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,400);

  TH1F* h_F = single_plot(files,"HTauTauTree","recoPFJet_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",20,0,400);
  h_F->Scale(h_B_OS->Integral()/h_F->Integral());
 
  h_B_SS->SetLineWidth(2);
  h_B_SS->SetLineColor(kBlue+2);

  h_B_OS->SetLineWidth(2);
  h_B_OS->SetLineColor(kBlue-4);

  THStack* h_B = new THStack("h_B","");
  h_B->Add(h_B_OS);
  h_B->Add(h_B_SS);

  h_F->SetFillColor(kRed+1);
  h_F->SetLineColor(kRed+1);
  h_F->SetLineWidth(0);
  h_F->SetMaximum(100*h_B->GetMaximum());
  h_F->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_B_OS,"#splitline{#leq 1 #tau_{h}, SS loose + tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_B_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_F,"#splitline{#leq 1 #tau_{h}, OS loose + tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_F->Draw("");
  h_B->Draw("same");
  leg->Draw("same");

  h_F->GetYaxis()->SetTitle("a. u.");
  h_F->GetYaxis()->SetTitleOffset(1.65);
  h_F->SetTitle("");
  h_F->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.07*h_F->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_B_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_F2 = (*h_F);
  h_F2.Sumw2();
  h_ratio->Divide(&h_F2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_F->GetYaxis()->SetTitleSize(20);
  h_F->GetYaxis()->SetTitleFont(43);
  h_F->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(B)/F");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(sublead. jet) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet1_pt_check_ABCD_OS_B";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void plot_jet1_pt_OS_A(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A_SS = single_plot(files,"HTauTauTree","recoPFJet_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,400);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","recoPFJet_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,400);

  TH1F* h_E = single_plot(files,"HTauTauTree","recoPFJet_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",20,0,400);
  h_E->Scale(h_A_OS->Integral()/h_E->Integral());
 
  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);

  h_E->SetFillColor(kRed+1);
  h_E->SetLineColor(kRed+1);
  h_E->SetLineWidth(0);
  h_E->SetMaximum(15*h_A->GetMaximum());
  h_E->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_E,"#splitline{#leq 1 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_E->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_E->GetYaxis()->SetTitle("a. u.");
  h_E->GetYaxis()->SetTitleOffset(1.65);
  h_E->SetTitle("");
  h_E->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.07*h_E->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_E2 = (*h_E);
  h_E2.Sumw2();
  h_ratio->Divide(&h_E2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_E->GetYaxis()->SetTitleSize(20);
  h_E->GetYaxis()->SetTitleFont(43);
  h_E->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(A)/E");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(sublead. jet) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet1_pt_check_ABCD_OS_A";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_jet1_pt_OS_C(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_C_SS = single_plot(files,"HTauTauTree","recoPFJet_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,400);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","recoPFJet_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,400);

  TH1F* h_G = single_plot(files,"HTauTauTree","recoPFJet_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",20,0,400);
  h_G->Scale(h_C_OS->Integral()/h_G->Integral());
 
  h_C_SS->SetLineWidth(2);
  h_C_SS->SetLineColor(kBlue+2);

  h_C_OS->SetLineWidth(2);
  h_C_OS->SetLineColor(kBlue-4);

  THStack* h_C = new THStack("h_C","");
  h_C->Add(h_C_OS);
  h_C->Add(h_C_SS);

  h_G->SetFillColor(kRed+1);
  h_G->SetLineColor(kRed+1);
  h_G->SetLineWidth(0);
  h_G->SetMaximum(1.2*h_C->GetMaximum());
  h_G->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_C_OS,"#splitline{0 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_C_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_G,"#splitline{0 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_G->Draw("");
  h_C->Draw("same");
  leg->Draw("same");

  h_G->GetYaxis()->SetTitle("a. u.");
  h_G->GetYaxis()->SetTitleOffset(1.65);
  h_G->SetTitle("");
  h_G->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.02*h_G->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_G->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_G->GetBinLowEdge(1), 0.01*h_G->GetMaximum(), h_G->GetBinLowEdge(1), h_G->GetMaximum(), 0.01*h_G->GetMaximum(),h_G->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_C_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_G2 = (*h_G);
  h_G2.Sumw2();
  h_ratio->Divide(&h_G2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_G->GetYaxis()->SetTitleSize(20);
  h_G->GetYaxis()->SetTitleFont(43);
  h_G->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(C)/G");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(sublead. jet) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet1_pt_check_ABCD_OS_C";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_jet1_eta_OS_B(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_B_SS = single_plot(files,"HTauTauTree","recoPFJet_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","recoPFJet_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_F = single_plot(files,"HTauTauTree","recoPFJet_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",12,-2.4,2.4);
  h_F->Scale(h_B_OS->Integral()/h_F->Integral());
 
  h_B_SS->SetLineWidth(2);
  h_B_SS->SetLineColor(kBlue+2);

  h_B_OS->SetLineWidth(2);
  h_B_OS->SetLineColor(kBlue-4);

  THStack* h_B = new THStack("h_B","");
  h_B->Add(h_B_OS);
  h_B->Add(h_B_SS);

  h_F->SetFillColor(kRed+1);
  h_F->SetLineColor(kRed+1);
  h_F->SetLineWidth(0);
  h_F->SetMaximum(350*h_B->GetMaximum());
  h_F->SetMinimum(5);
  h_F->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.55,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_B_OS,"#splitline{#leq 1 #tau_{h}, SS loose + tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_B_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_F,"#splitline{#leq 1 #tau_{h}, OS loose + tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_F->Draw("");
  h_B->Draw("same");
  leg->Draw("same");

  h_F->GetYaxis()->SetTitle("a. u.");
  h_F->GetYaxis()->SetTitleOffset(1.65);
  h_F->SetTitle("");
  h_F->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.07*h_F->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_B_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_F2 = (*h_F);
  h_F2.Sumw2();
  h_ratio->Divide(&h_F2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_F->GetYaxis()->SetTitleSize(20);
  h_F->GetYaxis()->SetTitleFont(43);
  h_F->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(B)/F");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(sublead. jet)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet1_eta_check_ABCD_OS_B";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_jet1_eta_OS_A(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A_SS = single_plot(files,"HTauTauTree","recoPFJet_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","recoPFJet_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_E = single_plot(files,"HTauTauTree","recoPFJet_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",12,-2.4,2.4);
  h_E->Scale(h_A_OS->Integral()/h_E->Integral());
 
  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);

  h_E->SetFillColor(kRed+1);
  h_E->SetLineColor(kRed+1);
  h_E->SetLineWidth(0);
  h_E->SetMaximum(50*h_A->GetMaximum());
  h_E->SetMinimum(0.5);
  h_E->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_E,"#splitline{#leq 1 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_E->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_E->GetYaxis()->SetTitle("a. u.");
  h_E->GetYaxis()->SetTitleOffset(1.65);
  h_E->SetTitle("");
  h_E->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.07*h_E->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_E2 = (*h_E);
  h_E2.Sumw2();
  h_ratio->Divide(&h_E2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_E->GetYaxis()->SetTitleSize(20);
  h_E->GetYaxis()->SetTitleFont(43);
  h_E->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(A)/E");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(sublead. jet)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet1_eta_check_ABCD_OS_A";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_jet1_eta_OS_C(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_C_SS = single_plot(files,"HTauTauTree","recoPFJet_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","recoPFJet_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_G = single_plot(files,"HTauTauTree","recoPFJet_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",12,-2.4,2.4);
  h_G->Scale(h_C_OS->Integral()/h_G->Integral());
 
  h_C_SS->SetLineWidth(2);
  h_C_SS->SetLineColor(kBlue+2);

  h_C_OS->SetLineWidth(2);
  h_C_OS->SetLineColor(kBlue-4);

  THStack* h_C = new THStack("h_C","");
  h_C->Add(h_C_OS);
  h_C->Add(h_C_SS);

  h_G->SetFillColor(kRed+1);
  h_G->SetLineColor(kRed+1);
  h_G->SetLineWidth(0);
  //h_G->SetMaximum(15*h_C->GetMaximum());
  //h_G->SetMinimum(2.);
  h_G->SetMaximum(1.5*h_C->GetMaximum());
  h_G->SetMinimum(0.);
  
  h_G->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_C_OS,"#splitline{0 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_C_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_G,"#splitline{0 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_G->Draw("");
  h_C->Draw("same");
  leg->Draw("same");

  h_G->GetYaxis()->SetTitle("a. u.");
  h_G->GetYaxis()->SetTitleOffset(1.65);
  h_G->SetTitle("");
  h_G->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.02*h_G->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_G->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_G->GetBinLowEdge(1), 0.01*h_G->GetMaximum(), h_G->GetBinLowEdge(1), h_G->GetMaximum(), 0.01*h_G->GetMaximum(), h_G->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_C_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_G2 = (*h_G);
  h_G2.Sumw2();
  h_ratio->Divide(&h_G2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_G->GetYaxis()->SetTitleSize(20);
  h_G->GetYaxis()->SetTitleFont(43);
  h_G->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(C)/G");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(sublead. jet)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet1_eta_check_ABCD_OS_C";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



void plot_MET_OS_B(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_B_SS = single_plot(files,"HTauTauTree","met","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,400);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","met","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,400);

  TH1F* h_F = single_plot(files,"HTauTauTree","met","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",20,0,400);
  h_F->Scale(h_B_OS->Integral()/h_F->Integral());
 
  h_B_SS->SetLineWidth(2);
  h_B_SS->SetLineColor(kBlue+2);

  h_B_OS->SetLineWidth(2);
  h_B_OS->SetLineColor(kBlue-4);

  THStack* h_B = new THStack("h_B","");
  h_B->Add(h_B_OS);
  h_B->Add(h_B_SS);

  h_F->SetFillColor(kRed+1);
  h_F->SetLineColor(kRed+1);
  h_F->SetLineWidth(0);
  h_F->SetMaximum(100*h_B->GetMaximum());
  h_F->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_B_OS,"#splitline{#leq 1 #tau_{h}, SS loose + tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_B_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_F,"#splitline{#leq 1 #tau_{h}, OS loose + tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_F->Draw("");
  h_B->Draw("same");
  leg->Draw("same");

  h_F->GetYaxis()->SetTitle("a. u.");
  h_F->GetYaxis()->SetTitleOffset(1.65);
  h_F->SetTitle("");
  h_F->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.07*h_F->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_B_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_F2 = (*h_F);
  h_F2.Sumw2();
  h_ratio->Divide(&h_F2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_F->GetYaxis()->SetTitleSize(20);
  h_F->GetYaxis()->SetTitleFont(43);
  h_F->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(B)/F");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("MET [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="MET_check_ABCD_OS_B";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void plot_MET_OS_A(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A_SS = single_plot(files,"HTauTauTree","met","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,400);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","met","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,400);

  TH1F* h_E = single_plot(files,"HTauTauTree","met","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",20,0,400);
  h_E->Scale(h_A_OS->Integral()/h_E->Integral());
 
  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);

  h_E->SetFillColor(kRed+1);
  h_E->SetLineColor(kRed+1);
  h_E->SetLineWidth(0);
  h_E->SetMaximum(15*h_A->GetMaximum());
  h_E->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_E,"#splitline{#leq 1 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_E->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_E->GetYaxis()->SetTitle("a. u.");
  h_E->GetYaxis()->SetTitleOffset(1.65);
  h_E->SetTitle("");
  h_E->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.07*h_E->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_E2 = (*h_E);
  h_E2.Sumw2();
  h_ratio->Divide(&h_E2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_E->GetYaxis()->SetTitleSize(20);
  h_E->GetYaxis()->SetTitleFont(43);
  h_E->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(A)/E");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("MET [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="MET_check_ABCD_OS_A";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_MET_OS_C(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_C_SS = single_plot(files,"HTauTauTree","met","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,400);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","met","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,400);

  TH1F* h_G = single_plot(files,"HTauTauTree","met","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",20,0,400);
  h_G->Scale(h_C_OS->Integral()/h_G->Integral());
 
  h_C_SS->SetLineWidth(2);
  h_C_SS->SetLineColor(kBlue+2);

  h_C_OS->SetLineWidth(2);
  h_C_OS->SetLineColor(kBlue-4);

  THStack* h_C = new THStack("h_C","");
  h_C->Add(h_C_OS);
  h_C->Add(h_C_SS);

  h_G->SetFillColor(kRed+1);
  h_G->SetLineColor(kRed+1);
  h_G->SetLineWidth(0);
  h_G->SetMaximum(1.2*h_C->GetMaximum());
  h_G->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_C_OS,"#splitline{0 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_C_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_G,"#splitline{0 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_G->Draw("");
  h_C->Draw("same");
  leg->Draw("same");

  h_G->GetYaxis()->SetTitle("a. u.");
  h_G->GetYaxis()->SetTitleOffset(1.65);
  h_G->SetTitle("");
  h_G->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.02*h_G->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_G->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_G->GetBinLowEdge(1), 0.01*h_G->GetMaximum(), h_G->GetBinLowEdge(1), h_G->GetMaximum(), 0.01*h_G->GetMaximum(),h_G->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_C_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_G2 = (*h_G);
  h_G2.Sumw2();
  h_ratio->Divide(&h_G2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_G->GetYaxis()->SetTitleSize(20);
  h_G->GetYaxis()->SetTitleFont(43);
  h_G->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(C)/G");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("MET [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="MET_check_ABCD_OS_C";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_lep0_pt_OS_B(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_B_SS = single_plot(files,"HTauTauTree","recolep_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,200);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","recolep_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,200);

  TH1F* h_F = single_plot(files,"HTauTauTree","recolep_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",20,0,200);
  h_F->Scale(h_B_OS->Integral()/h_F->Integral());
 
  h_B_SS->SetLineWidth(2);
  h_B_SS->SetLineColor(kBlue+2);

  h_B_OS->SetLineWidth(2);
  h_B_OS->SetLineColor(kBlue-4);

  THStack* h_B = new THStack("h_B","");
  h_B->Add(h_B_OS);
  h_B->Add(h_B_SS);

  h_F->SetFillColor(kRed+1);
  h_F->SetLineColor(kRed+1);
  h_F->SetLineWidth(0);
  h_F->SetMaximum(100*h_B->GetMaximum());
  h_F->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_B_OS,"#splitline{#leq 1 #tau_{h}, SS loose + tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_B_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_F,"#splitline{#leq 1 #tau_{h}, OS loose + tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_F->Draw("");
  h_B->Draw("same");
  leg->Draw("same");

  h_F->GetYaxis()->SetTitle("a. u.");
  h_F->GetYaxis()->SetTitleOffset(1.65);
  h_F->SetTitle("");
  h_F->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.07*h_F->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_B_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_F2 = (*h_F);
  h_F2.Sumw2();
  h_ratio->Divide(&h_F2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_F->GetYaxis()->SetTitleSize(20);
  h_F->GetYaxis()->SetTitleFont(43);
  h_F->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(B)/F");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(lead. lep.) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep0_pt_check_ABCD_OS_B";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_lep0_pt_OS_A(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A_SS = single_plot(files,"HTauTauTree","recolep_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,200);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","recolep_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,200);

  TH1F* h_E = single_plot(files,"HTauTauTree","recolep_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",20,0,200);
  h_E->Scale(h_A_OS->Integral()/h_E->Integral());
 
  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);

  h_E->SetFillColor(kRed+1);
  h_E->SetLineColor(kRed+1);
  h_E->SetLineWidth(0);
  h_E->SetMaximum(50*h_A->GetMaximum());
  h_E->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_E,"#splitline{#leq 1 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_E->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_E->GetYaxis()->SetTitle("a. u.");
  h_E->GetYaxis()->SetTitleOffset(1.65);
  h_E->SetTitle("");
  h_E->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.07*h_E->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_E2 = (*h_E);
  h_E2.Sumw2();
  h_ratio->Divide(&h_E2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_E->GetYaxis()->SetTitleSize(20);
  h_E->GetYaxis()->SetTitleFont(43);
  h_E->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(A)/E");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(lead. lep.) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep0_pt_check_ABCD_OS_A";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_lep0_pt_OS_C(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_C_SS = single_plot(files,"HTauTauTree","recolep_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,200);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","recolep_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,200);

  TH1F* h_G = single_plot(files,"HTauTauTree","recolep_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",20,0,200);
  h_G->Scale(h_C_OS->Integral()/h_G->Integral());
 
  h_C_SS->SetLineWidth(2);
  h_C_SS->SetLineColor(kBlue+2);

  h_C_OS->SetLineWidth(2);
  h_C_OS->SetLineColor(kBlue-4);

  THStack* h_C = new THStack("h_C","");
  h_C->Add(h_C_OS);
  h_C->Add(h_C_SS);

  h_G->SetFillColor(kRed+1);
  h_G->SetLineColor(kRed+1);
  h_G->SetLineWidth(0);
  h_G->SetMaximum(1.2*h_C->GetMaximum());
  h_G->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_C_OS,"#splitline{0 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_C_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_G,"#splitline{0 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_G->Draw("");
  h_C->Draw("same");
  leg->Draw("same");

  h_G->GetYaxis()->SetTitle("a. u.");
  h_G->GetYaxis()->SetTitleOffset(1.65);
  h_G->SetTitle("");
  h_G->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.02*h_G->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_G->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_G->GetBinLowEdge(1), 0.01*h_G->GetMaximum(), h_G->GetBinLowEdge(1), h_G->GetMaximum(), 0.01*h_G->GetMaximum(),h_G->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_C_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_G2 = (*h_G);
  h_G2.Sumw2();
  h_ratio->Divide(&h_G2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_G->GetYaxis()->SetTitleSize(20);
  h_G->GetYaxis()->SetTitleFont(43);
  h_G->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(C)/G");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(lead. lep.) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep0_pt_check_ABCD_OS_C";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_lep1_pt_OS_B(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_B_SS = single_plot(files,"HTauTauTree","recolep_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,200);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","recolep_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,200);

  TH1F* h_F = single_plot(files,"HTauTauTree","recolep_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",20,0,200);
  h_F->Scale(h_B_OS->Integral()/h_F->Integral());
 
  h_B_SS->SetLineWidth(2);
  h_B_SS->SetLineColor(kBlue+2);

  h_B_OS->SetLineWidth(2);
  h_B_OS->SetLineColor(kBlue-4);

  THStack* h_B = new THStack("h_B","");
  h_B->Add(h_B_OS);
  h_B->Add(h_B_SS);

  h_F->SetFillColor(kRed+1);
  h_F->SetLineColor(kRed+1);
  h_F->SetLineWidth(0);
  h_F->SetMaximum(100*h_B->GetMaximum());
  h_F->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_B_OS,"#splitline{#leq 1 #tau_{h}, SS loose + tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_B_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_F,"#splitline{#leq 1 #tau_{h}, OS loose + tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_F->Draw("");
  h_B->Draw("same");
  leg->Draw("same");

  h_F->GetYaxis()->SetTitle("a. u.");
  h_F->GetYaxis()->SetTitleOffset(1.65);
  h_F->SetTitle("");
  h_F->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.07*h_F->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_B_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_F2 = (*h_F);
  h_F2.Sumw2();
  h_ratio->Divide(&h_F2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_F->GetYaxis()->SetTitleSize(20);
  h_F->GetYaxis()->SetTitleFont(43);
  h_F->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(B)/F");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(sublead. lep.) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep1_pt_check_ABCD_OS_B";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_lep1_pt_OS_A(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A_SS = single_plot(files,"HTauTauTree","recolep_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,200);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","recolep_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,200);

  TH1F* h_E = single_plot(files,"HTauTauTree","recolep_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",20,0,200);
  h_E->Scale(h_A_OS->Integral()/h_E->Integral());
 
  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);

  h_E->SetFillColor(kRed+1);
  h_E->SetLineColor(kRed+1);
  h_E->SetLineWidth(0);
  h_E->SetMaximum(50*h_A->GetMaximum());
  h_E->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_E,"#splitline{#leq 1 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_E->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_E->GetYaxis()->SetTitle("a. u.");
  h_E->GetYaxis()->SetTitleOffset(1.65);
  h_E->SetTitle("");
  h_E->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.07*h_E->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_E2 = (*h_E);
  h_E2.Sumw2();
  h_ratio->Divide(&h_E2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_E->GetYaxis()->SetTitleSize(20);
  h_E->GetYaxis()->SetTitleFont(43);
  h_E->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,5.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(A)/E");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(sublead. lep.) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep1_pt_check_ABCD_OS_A";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_lep1_pt_OS_C(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_C_SS = single_plot(files,"HTauTauTree","recolep_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",20,0,200);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","recolep_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",20,0,200);

  TH1F* h_G = single_plot(files,"HTauTauTree","recolep_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",20,0,200);
  h_G->Scale(h_C_OS->Integral()/h_G->Integral());
 
  h_C_SS->SetLineWidth(2);
  h_C_SS->SetLineColor(kBlue+2);

  h_C_OS->SetLineWidth(2);
  h_C_OS->SetLineColor(kBlue-4);

  THStack* h_C = new THStack("h_C","");
  h_C->Add(h_C_OS);
  h_C->Add(h_C_SS);

  h_G->SetFillColor(kRed+1);
  h_G->SetLineColor(kRed+1);
  h_G->SetLineWidth(0);
  h_G->SetMaximum(1.2*h_C->GetMaximum());
  h_G->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_C_OS,"#splitline{0 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_C_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_G,"#splitline{0 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_G->Draw("");
  h_C->Draw("same");
  leg->Draw("same");

  h_G->GetYaxis()->SetTitle("a. u.");
  h_G->GetYaxis()->SetTitleOffset(1.65);
  h_G->SetTitle("");
  h_G->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(0.5,1.02*h_G->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_G->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_G->GetBinLowEdge(1), 0.01*h_G->GetMaximum(), h_G->GetBinLowEdge(1), h_G->GetMaximum(), 0.01*h_G->GetMaximum(),h_G->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_C_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_G2 = (*h_G);
  h_G2.Sumw2();
  h_ratio->Divide(&h_G2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_G->GetYaxis()->SetTitleSize(20);
  h_G->GetYaxis()->SetTitleFont(43);
  h_G->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(C)/G");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("p_{T}(sublead. lep.) [GeV]");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep1_pt_check_ABCD_OS_C";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_lep0_eta_OS_B(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_B_SS = single_plot(files,"HTauTauTree","recolep_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","recolep_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_F = single_plot(files,"HTauTauTree","recolep_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",12,-2.4,2.4);
  h_F->Scale(h_B_OS->Integral()/h_F->Integral());
 
  h_B_SS->SetLineWidth(2);
  h_B_SS->SetLineColor(kBlue+2);

  h_B_OS->SetLineWidth(2);
  h_B_OS->SetLineColor(kBlue-4);

  THStack* h_B = new THStack("h_B","");
  h_B->Add(h_B_OS);
  h_B->Add(h_B_SS);

  h_F->SetFillColor(kRed+1);
  h_F->SetLineColor(kRed+1);
  h_F->SetLineWidth(0);
  h_F->SetMaximum(350*h_B->GetMaximum());
  h_F->SetMinimum(5);
  h_F->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.55,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_B_OS,"#splitline{#leq 1 #tau_{h}, SS loose + tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_B_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_F,"#splitline{#leq 1 #tau_{h}, OS loose + tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_F->Draw("");
  h_B->Draw("same");
  leg->Draw("same");

  h_F->GetYaxis()->SetTitle("a. u.");
  h_F->GetYaxis()->SetTitleOffset(1.65);
  h_F->SetTitle("");
  h_F->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.07*h_F->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_B_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_F2 = (*h_F);
  h_F2.Sumw2();
  h_ratio->Divide(&h_F2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_F->GetYaxis()->SetTitleSize(20);
  h_F->GetYaxis()->SetTitleFont(43);
  h_F->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(B)/F");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(lead. lep.)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep0_eta_check_ABCD_OS_B";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_lep0_eta_OS_A(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A_SS = single_plot(files,"HTauTauTree","recolep_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","recolep_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_E = single_plot(files,"HTauTauTree","recolep_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",12,-2.4,2.4);
  h_E->Scale(h_A_OS->Integral()/h_E->Integral());
 
  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);

  h_E->SetFillColor(kRed+1);
  h_E->SetLineColor(kRed+1);
  h_E->SetLineWidth(0);
  h_E->SetMaximum(50*h_A->GetMaximum());
  h_E->SetMinimum(0.5);
  h_E->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_E,"#splitline{#leq 1 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_E->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_E->GetYaxis()->SetTitle("a. u.");
  h_E->GetYaxis()->SetTitleOffset(1.65);
  h_E->SetTitle("");
  h_E->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.07*h_E->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_E2 = (*h_E);
  h_E2.Sumw2();
  h_ratio->Divide(&h_E2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_E->GetYaxis()->SetTitleSize(20);
  h_E->GetYaxis()->SetTitleFont(43);
  h_E->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(A)/E");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(lead. lep.)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep0_eta_check_ABCD_OS_A";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_lep0_eta_OS_C(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_C_SS = single_plot(files,"HTauTauTree","recolep_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","recolep_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_G = single_plot(files,"HTauTauTree","recolep_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",12,-2.4,2.4);
  h_G->Scale(h_C_OS->Integral()/h_G->Integral());
 
  h_C_SS->SetLineWidth(2);
  h_C_SS->SetLineColor(kBlue+2);

  h_C_OS->SetLineWidth(2);
  h_C_OS->SetLineColor(kBlue-4);

  THStack* h_C = new THStack("h_C","");
  h_C->Add(h_C_OS);
  h_C->Add(h_C_SS);

  h_G->SetFillColor(kRed+1);
  h_G->SetLineColor(kRed+1);
  h_G->SetLineWidth(0);
  //h_G->SetMaximum(15*h_C->GetMaximum());
  //h_G->SetMinimum(2.);
  h_G->SetMaximum(1.75*h_C->GetMaximum());
  h_G->SetMinimum(0.);
  
  h_G->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_C_OS,"#splitline{0 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_C_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_G,"#splitline{0 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_G->Draw("");
  h_C->Draw("same");
  leg->Draw("same");

  h_G->GetYaxis()->SetTitle("a. u.");
  h_G->GetYaxis()->SetTitleOffset(1.65);
  h_G->SetTitle("");
  h_G->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.02*h_G->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_G->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_G->GetBinLowEdge(1), 0.01*h_G->GetMaximum(), h_G->GetBinLowEdge(1), h_G->GetMaximum(), 0.01*h_G->GetMaximum(),h_G->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_C_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_G2 = (*h_G);
  h_G2.Sumw2();
  h_ratio->Divide(&h_G2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_G->GetYaxis()->SetTitleSize(20);
  h_G->GetYaxis()->SetTitleFont(43);
  h_G->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(C)/G");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(lead. lep.)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep0_eta_check_ABCD_OS_C";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_lep1_eta_OS_B(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_B_SS = single_plot(files,"HTauTauTree","recolep_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","recolep_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_F = single_plot(files,"HTauTauTree","recolep_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",12,-2.4,2.4);
  h_F->Scale(h_B_OS->Integral()/h_F->Integral());
 
  h_B_SS->SetLineWidth(2);
  h_B_SS->SetLineColor(kBlue+2);

  h_B_OS->SetLineWidth(2);
  h_B_OS->SetLineColor(kBlue-4);

  THStack* h_B = new THStack("h_B","");
  h_B->Add(h_B_OS);
  h_B->Add(h_B_SS);

  h_F->SetFillColor(kRed+1);
  h_F->SetLineColor(kRed+1);
  h_F->SetLineWidth(0);
  h_F->SetMaximum(350*h_B->GetMaximum());
  h_F->SetMinimum(5);
  h_F->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.55,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_B_OS,"#splitline{#leq 1 #tau_{h}, SS loose + tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_B_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_F,"#splitline{#leq 1 #tau_{h}, OS loose + tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_F->Draw("");
  h_B->Draw("same");
  leg->Draw("same");

  h_F->GetYaxis()->SetTitle("a. u.");
  h_F->GetYaxis()->SetTitleOffset(1.65);
  h_F->SetTitle("");
  h_F->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.07*h_F->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_B_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_F2 = (*h_F);
  h_F2.Sumw2();
  h_ratio->Divide(&h_F2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_F->GetYaxis()->SetTitleSize(20);
  h_F->GetYaxis()->SetTitleFont(43);
  h_F->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(B)/F");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(sublead. lep.)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep1_eta_check_ABCD_OS_B";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_lep1_eta_OS_A(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A_SS = single_plot(files,"HTauTauTree","recolep_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","recolep_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_E = single_plot(files,"HTauTauTree","recolep_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]<0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",12,-2.4,2.4);
  h_E->Scale(h_A_OS->Integral()/h_E->Integral());
 
  h_A_SS->SetLineWidth(2);
  h_A_SS->SetLineColor(kBlue+2);

  h_A_OS->SetLineWidth(2);
  h_A_OS->SetLineColor(kBlue-4);

  THStack* h_A = new THStack("h_A","");
  h_A->Add(h_A_OS);
  h_A->Add(h_A_SS);

  h_E->SetFillColor(kRed+1);
  h_E->SetLineColor(kRed+1);
  h_E->SetLineWidth(0);
  h_E->SetMaximum(50*h_A->GetMaximum());
  h_E->SetMinimum(0.5);
  h_E->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_A_OS,"#splitline{#leq 1 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_A_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_E,"#splitline{#leq 1 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  pad1->SetLogy();

  h_E->Draw("");
  h_A->Draw("same");
  leg->Draw("same");

  h_E->GetYaxis()->SetTitle("a. u.");
  h_E->GetYaxis()->SetTitleOffset(1.65);
  h_E->SetTitle("");
  h_E->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.07*h_E->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  /*h_F->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_F->GetBinLowEdge(1), 0.01*h_F->GetMaximum(), h_F->GetBinLowEdge(1), 1.25*1.05*h_F->GetMaximum(), 0.01*h_F->GetMaximum(),1.25*1.05*h_F->GetMaximum(),510,"G");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();*/

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_A_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_E2 = (*h_E);
  h_E2.Sumw2();
  h_ratio->Divide(&h_E2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_E->GetYaxis()->SetTitleSize(20);
  h_E->GetYaxis()->SetTitleFont(43);
  h_E->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(A)/E");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(sublead. lep.)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep1_eta_check_ABCD_OS_A";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_lep1_eta_OS_C(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_C_SS = single_plot(files,"HTauTauTree","recolep_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==1 && recolep_goodsign[1]==1))",12,-2.4,2.4);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","recolep_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65) && (recolep_goodsign[0]==-1 || recolep_goodsign[1]==-1))",12,-2.4,2.4);

  TH1F* h_G = single_plot(files,"HTauTauTree","recolep_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && (recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65))",12,-2.4,2.4);
  h_G->Scale(h_C_OS->Integral()/h_G->Integral());
 
  h_C_SS->SetLineWidth(2);
  h_C_SS->SetLineColor(kBlue+2);

  h_C_OS->SetLineWidth(2);
  h_C_OS->SetLineColor(kBlue-4);

  THStack* h_C = new THStack("h_C","");
  h_C->Add(h_C_OS);
  h_C->Add(h_C_SS);

  h_G->SetFillColor(kRed+1);
  h_G->SetLineColor(kRed+1);
  h_G->SetLineWidth(0);
  //h_G->SetMaximum(15*h_C->GetMaximum());
  //h_G->SetMinimum(2.);
  h_G->SetMaximum(1.75*h_C->GetMaximum());
  h_G->SetMinimum(0.);
  
  h_G->Sumw2(false);

  TLegend* leg=new TLegend(0.45,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillStyle(0);
  leg->AddEntry(h_C_OS,"#splitline{0 #tau_{h}, 2 SS tight leptons}{with charge mismeas.}");
  leg->AddEntry(h_C_SS,"No charge mismeas. (stacked)");
  leg->AddEntry(h_G,"#splitline{0 #tau_{h}, 2 OS tight leptons}{rescaled to SS region}");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  //pad1->SetLogy();

  h_G->Draw("");
  h_C->Draw("same");
  leg->Draw("same");

  h_G->GetYaxis()->SetTitle("a. u.");
  h_G->GetYaxis()->SetTitleOffset(1.65);
  h_G->SetTitle("");
  h_G->SetStats(0);
  gPad->Modified();


  TLatex *texl = new TLatex(-2.3,1.02*h_G->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_G->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h_G->GetBinLowEdge(1), 0.01*h_G->GetMaximum(), h_G->GetBinLowEdge(1), h_G->GetMaximum(), 0.01*h_G->GetMaximum(),h_G->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();

  // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.15);
  pad2->SetBottomMargin(0.25);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h_C_OS->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  TH1F h_G2 = (*h_G);
  h_G2.Sumw2();
  h_ratio->Divide(&h_G2);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h_G->GetYaxis()->SetTitleSize(20);
  h_G->GetYaxis()->SetTitleFont(43);
  h_G->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("OS(C)/G");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  h_ratio->GetYaxis()->CenterTitle();

  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);
  h_ratio->GetXaxis()->SetTitle("#eta(sublead. lep.)");

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep1_eta_check_ABCD_OS_C";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}

