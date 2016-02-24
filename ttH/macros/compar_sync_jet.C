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

#include <Helpers.C>


void compar(){

  TString log_file = "log_NDNebr_jet.txt";
  std::ifstream infile(log_file);

  TChain * tree = new TChain("HTauTauTree");
  tree->Add("/home/llr/cms/strebler/CMSSW_7_4_12_leptonMVA/src/LLRHiggsTauTau/NtupleProducer/test/syncNtuple_ttH_iso25.root");
  int nEntries = tree->GetEntries();

  int _EventNumber;
  int _n_recomu;
  int _n_recoele;
  int _n_recotauh;
  int _n_recoPFJet30;

  vector<float>* _recoPFJet30_pt;

  tree->SetBranchAddress("EventNumber",&_EventNumber);
  tree->SetBranchAddress("n_recomu",&_n_recomu);
  tree->SetBranchAddress("n_recoele",&_n_recoele);
  tree->SetBranchAddress("n_recotauh",&_n_recotauh);
  tree->SetBranchAddress("n_recoPFJet30",&_n_recoPFJet30);

  tree->SetBranchAddress("recoPFJet30_pt",&_recoPFJet30_pt);

  int i=0;
  int nEntry=0;
  string line;
  while(getline(infile,line)){   
    if(i==0){
      i++;
      continue;
    }

    std::istringstream iss(line);
    vector<float> var;
    for(unsigned int j=0;j<17;j++)
      var.push_back(-1);


    iss >> var[0] >> var[1] >> var[2] >> var[3] >> var[4] >> var[5] >> var[6] >> var[7] >> var[8];


    _n_recomu = 0;
    _n_recoele = 0;
    _n_recotauh = 0;
    _n_recoPFJet30 = 0;

    _recoPFJet30_pt = 0;

    int nEntry_init = nEntry;

    //while(_EventNumber!=var[0] && nEntry!=nEntry_init-1){
    while(_n_recoPFJet30==0){
      tree->GetEntry(nEntry);
      nEntry++;
      if(nEntry>nEntries)
	nEntry = 0;
    }

    if(nEntry==nEntry_init-1)
      cout<<"Problem"<<endl;


    if(var[4]<1){
      cout<<"Different Event"<<endl;
      cout<<"NDNebr "<<var[0]<<endl;
      cout<<"LLR "<<_EventNumber<<endl;
      return;
    }
  }


  cout<<"Congratulations! You are synced!"<<endl;

  return;


}





TH1F* histo_fromlog(TString log_file, int varnumber, int nbin, float min, float max){

  TH1F* h=new TH1F("h","h",nbin,min,max);
  
  std::ifstream infile(log_file);


  int i=0;
  string line;
  while(getline(infile,line)){   
    
    if(i==0){
      i++;
      continue;
    }

    std::istringstream iss(line);
    vector<float> var;
    for(unsigned int j=0;j<17;j++)
      var.push_back(-1);


    iss >> var[0] >> var[1] >> var[2] >> var[3] >> var[4] >> var[5] >> var[6] >> var[7] >> var[8];


    h->Fill(var[varnumber]);


  }

  return h;


}








void compar_EventNumber_jet(){

  TChain * tree = new TChain("HTauTauTree");
  tree->Add("/home/llr/cms/strebler/CMSSW_7_4_12_leptonMVA/src/LLRHiggsTauTau/NtupleProducer/test/syncNtuple_ttH_iso25.root");

  TH1F* h = new TH1F("h","h",500000,0,500000);
  tree->Draw("EventNumber>>h","n_recoPFJet30>=1","goff");

  TH1F* h_sync = histo_fromlog("log_IPHC_jet.txt",0,500000,0,500000);


  h->SetTitle("EventNumber");
  h->SetLineColor(1);
  h->SetLineWidth(2);
  h->SetStats(0);
  h->SetMaximum(2);

  h_sync->SetLineColor(kOrange-2);
  h_sync->SetFillColor(kOrange-2);
  
  
  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(h,"LLR");
  leg->AddEntry(h_sync,"IPHC");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  h->GetYaxis()->SetTitle("Number of events");
  h->GetXaxis()->SetTitle("EventNumber");
  
  h->Draw();
  cout<<h->GetEntries()<<endl;;
  h_sync->Draw("same");
  cout<<h_sync->GetEntries()<<endl;;
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.5, 0, h->GetMaximum(), 0.5,h->GetMaximum(),510,"");
  axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis->SetLabelSize(15);
  axis->Draw();
  
   // lower plot will be in pad
  c->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  
  // Define the ratio plot
  TH1F *h_ratio = (TH1F*)h->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.9);  // Define Y ..
  h_ratio->SetMaximum(1.1); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_sync);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw("histp");       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h->GetYaxis()->SetTitleSize(20);
  h->GetYaxis()->SetTitleFont(43);
  h->GetYaxis()->SetTitleOffset(1.5);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.91, 0, 1.09, 0.91, 1.09, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/IPHC");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(20);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(3.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);


  TString plotname="sync/EventNumber_jet_IPHC";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;

}









void compar_pt_jet(){

  TChain * tree = new TChain("HTauTauTree");
  tree->Add("/home/llr/cms/strebler/CMSSW_7_4_12_leptonMVA/src/LLRHiggsTauTau/NtupleProducer/test/syncNtuple_ttH_iso25.root");

  TH1F* h = new TH1F("h","h",200,0,1000);
  tree->Draw("recoPFJet30_pt[0]>>h","n_recoPFJet30>=1","goff");

  TH1F* h_sync = histo_fromlog("log_NDNebr_jet.txt",1,200,0,1000);

  h_sync->SetTitle("Leading Jet pT");
  h_sync->SetStats(0);
  h_sync->SetMaximum(1.25*h_sync->GetMaximum());

  h_sync->SetLineColor(kOrange-2);
  h_sync->SetFillColor(kOrange-2);

  h->SetLineColor(1);
  h->SetLineWidth(2);
  
  
  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(h,"LLR");
  leg->AddEntry(h_sync,"ND/Nebr.");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);


  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  h_sync->GetYaxis()->SetTitle(Form("Number of events / %.2f GeV",binning(h)));
  h->GetXaxis()->SetTitle("p_{T} [GeV]");
  
  h_sync->Draw();
  cout<<h_sync->GetEntries()<<endl;;
  h->Draw("same");
  cout<<h->GetEntries()<<endl;;
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_sync->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.5, 0, h_sync->GetMaximum(), 0.5,h_sync->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.9);  // Define Y ..
  h_ratio->SetMaximum(1.1); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_sync);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw("histp");       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_sync->GetYaxis()->SetTitleSize(20);
  h_sync->GetYaxis()->SetTitleFont(43);
  h_sync->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.91, 0, 1.09, 0.91, 1.09, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/NDN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);


  TString plotname="sync/pt_jet_NDN";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;

}










void compar_eta_jet(){

  TChain * tree = new TChain("HTauTauTree");
  tree->Add("/home/llr/cms/strebler/CMSSW_7_4_12_leptonMVA/src/LLRHiggsTauTau/NtupleProducer/test/syncNtuple_ttH_iso25.root");

  TH1F* h = new TH1F("h","h",75,-3,3);
  tree->Draw("recoPFJet30_eta[0]>>h","n_recoPFJet30>=1","goff");

  TH1F* h_sync = histo_fromlog("log_NDNebr_jet.txt",2,75,-3,3);

  h_sync->SetTitle("Leading Jet #eta");
  h_sync->SetStats(0);
  h_sync->SetMaximum(1.25*h_sync->GetMaximum());

  h_sync->SetLineColor(kOrange-2);
  h_sync->SetFillColor(kOrange-2);

  h->SetLineColor(1);
  h->SetLineWidth(2);
  
  
  TLegend* leg=new TLegend(0.7,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(h,"LLR");
  leg->AddEntry(h_sync,"ND/Nebr.");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);


  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  h_sync->GetYaxis()->SetTitle(Form("Number of events / %.2f",binning(h)));
  h->GetXaxis()->SetTitle("#eta");
  
  h_sync->Draw();
  cout<<h_sync->GetEntries()<<endl;;
  h->Draw("same");
  cout<<h->GetEntries()<<endl;;
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_sync->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( -3, 0.5, -3, h_sync->GetMaximum(), 0.5,h_sync->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.9);  // Define Y ..
  h_ratio->SetMaximum(1.1); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_sync);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw("histp");       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_sync->GetYaxis()->SetTitleSize(20);
  h_sync->GetYaxis()->SetTitleFont(43);
  h_sync->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( -3, 0.91, -3, 1.09, 0.91, 1.09, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/NDN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);


  TString plotname="sync/eta_jet_NDN";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;

}








void compar_phi_jet(){

  TChain * tree = new TChain("HTauTauTree");
  tree->Add("/home/llr/cms/strebler/CMSSW_7_4_12_leptonMVA/src/LLRHiggsTauTau/NtupleProducer/test/syncNtuple_ttH_iso25.root");

  TH1F* h = new TH1F("h","h",80,-3.2,3.2);
  tree->Draw("recoPFJet30_phi[0]>>h","n_recoPFJet30>=1","goff");

  TH1F* h_sync = histo_fromlog("log_NDNebr_jet.txt",3,80,-3.2,3.2);

  h_sync->SetTitle("Leading Jet #phi");
  h_sync->SetStats(0);
  h_sync->SetMaximum(1.25*h_sync->GetMaximum());

  h_sync->SetLineColor(kOrange-2);
  h_sync->SetFillColor(kOrange-2);

  h->SetLineColor(1);
  h->SetLineWidth(2);
  
  
  TLegend* leg=new TLegend(0.7,0.75,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(h,"LLR");
  leg->AddEntry(h_sync,"ND/Nebr.");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);


  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  h_sync->GetYaxis()->SetTitle(Form("Number of events / %.2f",binning(h)));
  h->GetXaxis()->SetTitle("#phi");
  
  h_sync->Draw();
  cout<<h_sync->GetEntries()<<endl;;
  h->Draw("same");
  cout<<h->GetEntries()<<endl;;
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_sync->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( -3.2, 0.5, -3.2, h_sync->GetMaximum(), 0.5,h_sync->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.9);  // Define Y ..
  h_ratio->SetMaximum(1.1); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_sync);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw("histp");       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_sync->GetYaxis()->SetTitleSize(20);
  h_sync->GetYaxis()->SetTitleFont(43);
  h_sync->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( -3.2, 0.91, -3.2, 1.09, 0.91, 1.09, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/NDN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);


  TString plotname="sync/phi_jet_NDN";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;

}











void compar_E_jet(){

  TChain * tree = new TChain("HTauTauTree");
  tree->Add("/home/llr/cms/strebler/CMSSW_7_4_12_leptonMVA/src/LLRHiggsTauTau/NtupleProducer/test/syncNtuple_ttH_iso25.root");

  TH1F* h = new TH1F("h","h",200,0,1000);
  tree->Draw("recoPFJet30_e[0]>>h","n_recoPFJet30>=1","goff");

  TH1F* h_sync = histo_fromlog("log_NDNebr_jet.txt",4,200,0,1000);

  h_sync->SetTitle("Leading Jet Energy");
  h_sync->SetStats(0);
  h_sync->SetMaximum(1.25*h_sync->GetMaximum());

  h_sync->SetLineColor(kOrange-2);
  h_sync->SetFillColor(kOrange-2);

  h->SetLineColor(1);
  h->SetLineWidth(2);
  
  
  TLegend* leg=new TLegend(0.7,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(h,"LLR");
  leg->AddEntry(h_sync,"ND/nebr.");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);


  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  h_sync->GetYaxis()->SetTitle(Form("Number of events / %.2f GeV",binning(h)));
  h->GetXaxis()->SetTitle("E [GeV]");
  
  h_sync->Draw();
  cout<<h_sync->GetEntries()<<endl;;
  h->Draw("same");
  cout<<h->GetEntries()<<endl;;
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_sync->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.5, 0, h_sync->GetMaximum(), 0.5,h_sync->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.9);  // Define Y ..
  h_ratio->SetMaximum(1.1); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_sync);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw("histp");       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_sync->GetYaxis()->SetTitleSize(20);
  h_sync->GetYaxis()->SetTitleFont(43);
  h_sync->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.91, 0, 1.09, 0.91, 1.09, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/NDN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);


  TString plotname="sync/E_jet_NDN";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;

}







void compar_CSV_jet(){

  TChain * tree = new TChain("HTauTauTree");
  tree->Add("/home/llr/cms/strebler/CMSSW_7_4_12_leptonMVA/src/LLRHiggsTauTau/NtupleProducer/test/syncNtuple_ttH_iso25.root");

  TH1F* h = new TH1F("h","h",100,0,1);
  tree->Draw("recoPFJet30_CSVscore[0]>>h","n_recoPFJet30>=1","goff");

  TH1F* h_sync = histo_fromlog("log_NDNebr_jet.txt",5,100,0,1);

  h_sync->SetTitle("Leading Jet CSV score");
  h_sync->SetStats(0);
  h_sync->SetMaximum(1.25*h_sync->GetMaximum());

  h_sync->SetLineColor(kOrange-2);
  h_sync->SetFillColor(kOrange-2);

  h->SetLineColor(1);
  h->SetLineWidth(2);
  
  
  TLegend* leg=new TLegend(0.7,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(h,"LLR");
  leg->AddEntry(h_sync,"ND/nebr.");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);


  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  h_sync->GetYaxis()->SetTitle(Form("Number of events / %.2f",binning(h)));
  h->GetXaxis()->SetTitle("CSV");
  
  h_sync->Draw();
  cout<<h_sync->GetEntries()<<endl;;
  h->Draw("same");
  cout<<h->GetEntries()<<endl;;
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_sync->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.5, 0, h_sync->GetMaximum(), 0.5,h_sync->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.9);  // Define Y ..
  h_ratio->SetMaximum(1.1); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_sync);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw("histp");       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_sync->GetYaxis()->SetTitleSize(20);
  h_sync->GetYaxis()->SetTitleFont(43);
  h_sync->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.91, 0, 1.09, 0.91, 1.09, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/NDN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);


  TString plotname="sync/CSV_jet_NDN";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;

}








void compar_MET(){

  TChain * tree = new TChain("HTauTauTree");
  tree->Add("/home/llr/cms/strebler/CMSSW_7_4_12_leptonMVA/src/LLRHiggsTauTau/NtupleProducer/test/syncNtuple_ttH_iso25.root");

  TH1F* h = new TH1F("h","h",100,0,500);
  tree->Draw("met>>h","n_recoPFJet30>=1","goff");

  TH1F* h_sync = histo_fromlog("log_NDNebr_jet.txt",6,100,0,500);

  h_sync->SetTitle("Missing ET");
  h_sync->SetStats(0);
  h_sync->SetMaximum(1.25*h_sync->GetMaximum());

  h_sync->SetLineColor(kOrange-2);
  h_sync->SetFillColor(kOrange-2);

  h->SetLineColor(1);
  h->SetLineWidth(2);
  
  
  TLegend* leg=new TLegend(0.7,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(h,"LLR");
  leg->AddEntry(h_sync,"ND/nebr.");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);


  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  h_sync->GetYaxis()->SetTitle(Form("Number of events / %.2f GeV",binning(h)));
  h->GetXaxis()->SetTitle("MET [GeV]");
  
  h_sync->Draw();
  cout<<h_sync->GetEntries()<<endl;;
  h->Draw("same");
  cout<<h->GetEntries()<<endl;;
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_sync->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( 0, 0.5, 0, h_sync->GetMaximum(), 0.5,h_sync->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.9);  // Define Y ..
  h_ratio->SetMaximum(1.1); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_sync);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw("histp");       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_sync->GetYaxis()->SetTitleSize(20);
  h_sync->GetYaxis()->SetTitleFont(43);
  h_sync->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( 0, 0.91, 0, 1.09, 0.91, 1.09, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/NDN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);


  TString plotname="sync/MET_NDN";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;

}



void compar_MET_phi(){

  TChain * tree = new TChain("HTauTauTree");
  tree->Add("/home/llr/cms/strebler/CMSSW_7_4_12_leptonMVA/src/LLRHiggsTauTau/NtupleProducer/test/syncNtuple_ttH_iso25.root");

  TH1F* h = new TH1F("h","h",100,-3.2,3.2);
  tree->Draw("metphi>>h","n_recoPFJet30>=1","goff");

  TH1F* h_sync = histo_fromlog("log_NDNebr_jet.txt",7,100,-3.2,3.2);

  h_sync->SetTitle("Missing ET #phi");
  h_sync->SetStats(0);
  h_sync->SetMaximum(1.25*h_sync->GetMaximum());

  h_sync->SetLineColor(kOrange-2);
  h_sync->SetFillColor(kOrange-2);

  h->SetLineColor(1);
  h->SetLineWidth(2);
  
  
  TLegend* leg=new TLegend(0.7,0.75,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(h,"LLR");
  leg->AddEntry(h_sync,"ND/nebr.");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);


  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  h_sync->GetYaxis()->SetTitle(Form("Number of events / %.2f",binning(h)));
  h->GetXaxis()->SetTitle("MET #phi");
  
  h_sync->Draw();
  cout<<h_sync->GetEntries()<<endl;;
  h->Draw("same");
  cout<<h->GetEntries()<<endl;;
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_sync->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( -3.2, 0.5, -3.2, h_sync->GetMaximum(), 0.5,h_sync->GetMaximum(),510,"");
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
  TH1F *h_ratio = (TH1F*)h->Clone("h_ratio");
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetMinimum(0.9);  // Define Y ..
  h_ratio->SetMaximum(1.1); // .. range
  h_ratio->Sumw2();
  h_ratio->SetStats(0);      // No statistics on lower plot
  h_ratio->Divide(h_sync);
  h_ratio->SetMarkerStyle(20);
  h_ratio->Draw("histp");       // Draw the ratio plot
  
  // Y axis histo_emul plot settings
  h_sync->GetYaxis()->SetTitleSize(20);
  h_sync->GetYaxis()->SetTitleFont(43);
  h_sync->GetYaxis()->SetTitleOffset(1.45);
  
  // Ratio plot (h_ratio) settings
  h_ratio->SetTitle(""); // Remove the ratio title
  
  h_ratio->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis2 = new TGaxis( -3.2, 0.91, -3.2, 1.09, 0.91, 1.09, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/NDN");
  h_ratio->GetYaxis()->SetNdivisions(505);
  h_ratio->GetYaxis()->SetTitleSize(20);
  h_ratio->GetYaxis()->SetTitleFont(43);
  h_ratio->GetYaxis()->SetTitleOffset(1.5);
  //h_ratio->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  //h_ratio->GetYaxis()->SetLabelSize(15);

  
  // X axis ratio plot settings
  h_ratio->GetXaxis()->SetTitleSize(17);
  h_ratio->GetXaxis()->SetTitleFont(43);
  h_ratio->GetXaxis()->SetTitleOffset(4.);
  h_ratio->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  h_ratio->GetXaxis()->SetLabelSize(15);


  TString plotname="sync/MET_phi_NDN";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;

}



