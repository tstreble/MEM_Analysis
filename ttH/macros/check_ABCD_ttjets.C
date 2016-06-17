#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <Helpers.C>
#include <vector>
#include <TLatex.h>
#include <TGraphErrors.h>
#include <TGaxis.h>

using namespace std;



float C_over_D(vector<TString> files){

  TH1F* h_C = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",3,0,3);

  TH1F* h_D = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",3,0,3);

  cout<<"Recomputed"<<endl;
  cout<<"h_C="<<h_C->Integral()<<endl;;
  cout<<"h_D="<<h_D->Integral()<<endl;;

  return h_C->Integral()/h_D->Integral();

  //return 4.55486513674259186e-02;

}




void plot_tauh_pt(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");


  TH1F* h_A = single_plot(files,"HTauTauTree","recotauh_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",20,0,200);

  TH1F* h_B = single_plot(files,"HTauTauTree","recotauh_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",20,0,200);


 
  vector<TH1F*> h;
  h.push_back(h_A);
  h.push_back(h_B);

  vector<TString> leg_entry;
  leg_entry.push_back("2 MVA tight lep.");
  leg_entry.push_back("1 MVA tight + 1 MVA loose lep.");

  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");


  TLatex *texl = new TLatex(0.5,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h[0]->GetBinLowEdge(1), 0.01*h[0]->GetMaximum(), h[0]->GetBinLowEdge(1), h[0]->GetMaximum(), 0.01*h[0]->GetMaximum(),h[0]->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h_A->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_B);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,1.2*h_ratio->GetMaximum());

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("A/B");
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

  TString filename="tauh_pt_check_ABCD";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_tauh_pt_norm(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");


  TH1F* h_A = single_plot(files,"HTauTauTree","recotauh_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",20,0,200);

  TH1F* h_B = single_plot(files,"HTauTauTree","recotauh_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",20,0,200);

  float extrap_factor = C_over_D(files);

 
  vector<TH1F*> h;
  h.push_back(h_A);
  h.push_back(h_B);

  vector<TString> leg_entry;
  leg_entry.push_back("MC");
  leg_entry.push_back("Extrapolation");

  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    //h[i]->Scale(1/h[i]->Integral());
    if(i==1)
      h[i]->Scale(extrap_factor);
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("p_{T}(#tau_{h}) [GeV]");
  h_A->GetXaxis()->SetTitle("p_{T}(#tau_{h}) [GeV]");
  h[0]->GetYaxis()->SetTitle("a.u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");


  TLatex *texl = new TLatex(0.5,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h[0]->GetBinLowEdge(1), 0.01*h[0]->GetMaximum(), h[0]->GetBinLowEdge(1), h[0]->GetMaximum(), 0.01*h[0]->GetMaximum(),h[0]->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h_A->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_B);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,1.2*h_ratio->GetMaximum());

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("MC/Extrap.");
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

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="tauh_pt_check_ABCD_norm";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_tauh_eta(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");


  TH1F* h_A = single_plot(files,"HTauTauTree","recotauh_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",12,-2.4,2.4);

  TH1F* h_B = single_plot(files,"HTauTauTree","recotauh_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",12,-2.4,2.4);


 
  vector<TH1F*> h;
  h.push_back(h_A);
  h.push_back(h_B);

  vector<TString> leg_entry;
  leg_entry.push_back("2 MVA tight lep.");
  leg_entry.push_back("1 MVA tight + 1 MVA loose lep.");

  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  h[0]->SetMaximum(1.75*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("#eta(#tau_{h})");
  h_A->GetXaxis()->SetTitle("#eta(#tau_{h})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");


  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1)+0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h[0]->GetBinLowEdge(1), 0.01*h[0]->GetMaximum(), h[0]->GetBinLowEdge(1), h[0]->GetMaximum(), 0.01*h[0]->GetMaximum(),h[0]->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h_A->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_B);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("A/B");
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

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="tauh_eta_check_ABCD";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_tauh_eta_norm(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");


  TH1F* h_A = single_plot(files,"HTauTauTree","recotauh_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",12,-2.4,2.4);

  TH1F* h_B = single_plot(files,"HTauTauTree","recotauh_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",12,-2.4,2.4);

  float extrap_factor = C_over_D(files);

  vector<TH1F*> h;
  h.push_back(h_A);
  h.push_back(h_B);

  vector<TString> leg_entry;
  leg_entry.push_back("MC");
  leg_entry.push_back("Extrapolation");

  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    if(i==1)
      h[i]->Scale(extrap_factor);
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  h[0]->SetMaximum(1.75*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("#eta(#tau_{h})");
  h[0]->GetYaxis()->SetTitle("a.u.");
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");


  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1)+0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h[0]->GetBinLowEdge(1), 0.01*h[0]->GetMaximum(), h[0]->GetBinLowEdge(1), h[0]->GetMaximum(), 0.01*h[0]->GetMaximum(),h[0]->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h_A->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_B);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.99*h_ratio->GetMaximum(), 0.1, 0.99*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("MC/Extrap.");
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

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="tauh_eta_check_ABCD_norm";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_jet0_pt(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");


  TH1F* h_A = single_plot(files,"HTauTauTree","recoPFJet_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",20,0,400);

  TH1F* h_B = single_plot(files,"HTauTauTree","recoPFJet_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",20,0,400);


 
  vector<TH1F*> h;
  h.push_back(h_A);
  h.push_back(h_B);

  vector<TString> leg_entry;
  leg_entry.push_back("2 MVA tight lep.");
  leg_entry.push_back("1 MVA tight + 1 MVA loose lep.");

  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  h[0]->SetMaximum(1.75*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("p_{T}(lead. jet) [GeV]");
  h_A->GetXaxis()->SetTitle("p_{T}(lead. jet) [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");


  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1)+0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h[0]->GetBinLowEdge(1), 0.01*h[0]->GetMaximum(), h[0]->GetBinLowEdge(1), h[0]->GetMaximum(), 0.01*h[0]->GetMaximum(),h[0]->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h_A->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_B);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,1.2*h_ratio->GetMaximum());

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.95*h_ratio->GetMaximum(), 0.1, 0.95*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("A/B");
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

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet0_pt_check_ABCD";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_jet0_eta(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_old.root");


  TH1F* h_A = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",12,-2.4,2.4);

  TH1F* h_B = single_plot(files,"HTauTauTree","recoPFJet_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",12,-2.4,2.4);


 
  vector<TH1F*> h;
  h.push_back(h_A);
  h.push_back(h_B);

  vector<TString> leg_entry;
  leg_entry.push_back("2 MVA tight lep.");
  leg_entry.push_back("1 MVA tight + 1 MVA loose lep.");

  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  h[0]->SetMaximum(1.75*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("#eta(lead. jet)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");


  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1)+0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h[0]->GetBinLowEdge(1), 0.01*h[0]->GetMaximum(), h[0]->GetBinLowEdge(1), h[0]->GetMaximum(), 0.01*h[0]->GetMaximum(),h[0]->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h_A->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_B);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,3.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.95*h_ratio->GetMaximum(), 0.1, 0.95*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("A/B");
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

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet0_eta_check_ABCD";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_jet0_CSV(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_old.root");


  TH1F* h_A = single_plot(files,"HTauTauTree","recoPFJet_CSVscore[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",10,0,1);

  TH1F* h_B = single_plot(files,"HTauTauTree","recoPFJet_CSVscore[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",10,0,1);


 
  vector<TH1F*> h;
  h.push_back(h_A);
  h.push_back(h_B);

  vector<TString> leg_entry;
  leg_entry.push_back("2 MVA tight lep.");
  leg_entry.push_back("1 MVA tight + 1 MVA loose lep.");

  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  h[0]->SetMaximum(1.75*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("CSV(lead. jet)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");


  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1)+0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h[0]->GetBinLowEdge(1), 0.01*h[0]->GetMaximum(), h[0]->GetBinLowEdge(1), h[0]->GetMaximum(), 0.01*h[0]->GetMaximum(),h[0]->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h_A->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_B);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.95*h_ratio->GetMaximum(), 0.1, 0.95*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("A/B");
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

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="jet0_CSV_check_ABCD";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}










void plot_lep0_pt(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");


  TH1F* h_A = single_plot(files,"HTauTauTree","recolep_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",20,0,400);

  TH1F* h_B = single_plot(files,"HTauTauTree","recolep_pt[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",20,0,400);


 
  vector<TH1F*> h;
  h.push_back(h_A);
  h.push_back(h_B);

  vector<TString> leg_entry;
  leg_entry.push_back("2 MVA tight lep.");
  leg_entry.push_back("1 MVA tight + 1 MVA loose lep.");

  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  h[0]->SetMaximum(1.75*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");


  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1)+0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h[0]->GetBinLowEdge(1), 0.01*h[0]->GetMaximum(), h[0]->GetBinLowEdge(1), h[0]->GetMaximum(), 0.01*h[0]->GetMaximum(),h[0]->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h_A->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_B);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,1.2*h_ratio->GetMaximum());

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.95*h_ratio->GetMaximum(), 0.1, 0.95*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("A/B");
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

  TString filename="lep0_pt_check_ABCD";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void plot_lep0_eta(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_old.root");


  TH1F* h_A = single_plot(files,"HTauTauTree","recolep_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",12,-2.4,2.4);

  TH1F* h_B = single_plot(files,"HTauTauTree","recolep_eta[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",12,-2.4,2.4);


 
  vector<TH1F*> h;
  h.push_back(h_A);
  h.push_back(h_B);

  vector<TString> leg_entry;
  leg_entry.push_back("2 MVA tight lep.");
  leg_entry.push_back("1 MVA tight + 1 MVA loose lep.");

  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  h[0]->SetMaximum(2.*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("#eta(lead. lep.)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");


  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1)+0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h[0]->GetBinLowEdge(1), 0.01*h[0]->GetMaximum(), h[0]->GetBinLowEdge(1), h[0]->GetMaximum(), 0.01*h[0]->GetMaximum(),h[0]->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h_A->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_B);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.95*h_ratio->GetMaximum(), 0.1, 0.95*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("A/B");
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

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep0_eta_check_ABCD";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_lep1_pt(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_old.root");


  TH1F* h_A = single_plot(files,"HTauTauTree","recolep_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",20,0,200);

  TH1F* h_B = single_plot(files,"HTauTauTree","recolep_pt[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",20,0,200);


 
  vector<TH1F*> h;
  h.push_back(h_A);
  h.push_back(h_B);

  vector<TString> leg_entry;
  leg_entry.push_back("2 MVA tight lep.");
  leg_entry.push_back("1 MVA tight + 1 MVA loose lep.");

  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  h[0]->SetMaximum(1.75*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("p_{T}(sublead. lep.) [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");


  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1)+0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h[0]->GetBinLowEdge(1), 0.01*h[0]->GetMaximum(), h[0]->GetBinLowEdge(1), h[0]->GetMaximum(), 0.01*h[0]->GetMaximum(),h[0]->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h_A->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_B);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,15.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.95*h_ratio->GetMaximum(), 0.1, 0.95*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("A/B");
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

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep1_pt_check_ABCD";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void plot_lep1_eta(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_old.root");


  TH1F* h_A = single_plot(files,"HTauTauTree","recolep_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",12,-2.4,2.4);

  TH1F* h_B = single_plot(files,"HTauTauTree","recolep_eta[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",12,-2.4,2.4);


 
  vector<TH1F*> h;
  h.push_back(h_A);
  h.push_back(h_B);

  vector<TString> leg_entry;
  leg_entry.push_back("2 MVA tight lep.");
  leg_entry.push_back("1 MVA tight + 1 MVA loose lep.");

  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  h[0]->SetMaximum(2.*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("#eta(sublead. lep.)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");


  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1)+0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h[0]->GetBinLowEdge(1), 0.01*h[0]->GetMaximum(), h[0]->GetBinLowEdge(1), h[0]->GetMaximum(), 0.01*h[0]->GetMaximum(),h[0]->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h_A->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_B);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,2.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.95*h_ratio->GetMaximum(), 0.1, 0.95*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("A/B");
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

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="lep1_eta_check_ABCD";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_MET(){


  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_old.root");


  TH1F* h_A = single_plot(files,"HTauTauTree","met","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",20,0,200);

  TH1F* h_B = single_plot(files,"HTauTauTree","met","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65) || (recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) )",20,0,200);


 
  vector<TH1F*> h;
  h.push_back(h_A);
  h.push_back(h_B);

  vector<TString> leg_entry;
  leg_entry.push_back("2 MVA tight lep.");
  leg_entry.push_back("1 MVA tight + 1 MVA loose lep.");

  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }

  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  //pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad

  h[0]->SetMaximum(1.75*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("MET [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");


  TLatex *texl = new TLatex(h[0]->GetBinLowEdge(1)+0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h[0]->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( h[0]->GetBinLowEdge(1), 0.01*h[0]->GetMaximum(), h[0]->GetBinLowEdge(1), h[0]->GetMaximum(), 0.01*h[0]->GetMaximum(),h[0]->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h_A->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  //h_ratio->SetMinimum(0.);  // Define Y ..
  //h_ratio->SetMaximum(2.); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_B);
  //h_ratio->SetMarkerStyle(20);
  h_ratio->Draw();       // Draw the ratio plot

  // Y axis histo_emul plot settings
  h[0]->GetYaxis()->SetTitleSize(20);
  h[0]->GetYaxis()->SetTitleFont(43);
  h[0]->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  h_ratio->GetYaxis()->SetRangeUser(0.,3.);

  TGaxis *axis2 = new TGaxis( h_ratio->GetBinLowEdge(1), 0.1, h_ratio->GetBinLowEdge(1), 0.95*h_ratio->GetMaximum(), 0.1, 0.95*h_ratio->GetMaximum(), 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("A/B");
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

  TLine *line = new TLine(h_ratio->GetXaxis()->GetXmin(), 1, h_ratio->GetXaxis()->GetXmax(), 1);
  line->SetLineStyle(2);
  line->Draw("same");

  TString filename="MET_check_ABCD";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}


