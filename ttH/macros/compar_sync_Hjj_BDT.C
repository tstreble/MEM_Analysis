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
#include <TLatex.h>
#include "Helpers.C"




void compar(){

  TString log_file = "2lSS_SR_Hjj_BDT_80X_Summer16_IHEP.txt";
  std::ifstream infile(log_file);

  TChain * tree = new TChain("syncTree_2lSS");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root");
  int nEntries = tree->GetEntries();

  float _jet0_HjBDT;

  tree->SetBranchAddress("jet0_HjBDT",&_jet0_HjBDT);

  //int i=0;
  int nEntry=0;
  string line;
  while(getline(infile,line)){
    /*if(i==0){
 *       i++;
 *             continue;
 *                 }*/

    std::istringstream iss(line);
    vector<float> var;
    for(unsigned int j=0;j<14;j++)
      var.push_back(-1);


    iss >> var[0] >> var[1] >> var[2] >> var[3] >> var[4] >> var[5] >> var[6] >> var[7] >> var[8] >> var[9] >> var[10] >> var[11] >> var[12] >> var[13];

    int event_log = var[0];

    _jet0_HjBDT = 0;

    tree->GetEntry(nEntry);

   if(abs(_jet0_HjBDT-var[6])>1e-6){
      cout<<"Different"<<endl;
      cout<<"Event #"<<var[0]<<endl;
      cout<<"IHEP has "<<var[6]<<endl;
      cout<<"LLR has "<<_jet0_HjBDT<<endl;
      
      return;
    }

    nEntry++;

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
    


    std::istringstream iss(line);
    vector<float> var;
    for(unsigned int j=0;j<14;j++)
      var.push_back(-1);


    iss >> var[0] >> var[1] >> var[2] >> var[3] >> var[4] >> var[5] >> var[6] >> var[7] >> var[8] >> var[9] >> var[10] >> var[11] >> var[12] >> var[13];


    h->Fill(var[varnumber]);

    i++;

  }

  return h;


}








void compar_Hj_BDT(){

  TChain * tree = new TChain("syncTree_2lSS");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root");

  TH1F* h = new TH1F("h","h",100,-1,1.000001);
  tree->Draw("jet0_HjBDT>>h","","goff");

  TH1F* h_sync = histo_fromlog("2lSS_SR_Hjj_BDT_80X_Summer16_IHEP.txt",6,100,-1,1.000001);

  h_sync->SetTitle("Leading jet Hj BDT");
  h_sync->SetStats(0);
  h_sync->SetMaximum(1.25*h_sync->GetMaximum());

  h_sync->SetLineColor(kOrange-2);
  h_sync->SetFillColor(kOrange-2);

  h->SetLineColor(1);
  h->SetLineWidth(2);
  
  for(unsigned int i=0; i<5000000;i++){
    int LLR = h->GetBinContent(i);
    int IHEP = h_sync->GetBinContent(i);
    if(LLR!=IHEP){
      cout<<"i="<<i<<endl;
      cout<<"LLR="<<LLR<<endl;
      cout<<"IHEP="<<IHEP<<endl;
    }
  }
  
  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(h,"LLR");
  leg->AddEntry(h_sync,"IHEP");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);


  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  h_sync->GetYaxis()->SetTitle(Form("Number of events / %.2f",binning(h)));
  h->GetXaxis()->SetTitle("BDT");
  
  h_sync->Draw();
  cout<<h_sync->GetEntries()<<endl;;
  h->Draw("same");
  cout<<h->GetEntries()<<endl;;
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_sync->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( -1, 0.5, -1, h_sync->GetMaximum(), 0.5,h_sync->GetMaximum(),510,"");
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
  TGaxis *axis2 = new TGaxis( -1, 0.91, -1, 1.09, 0.91, 1.09, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/IHEP");
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


  TString plotname="sync/Hj_BDT_IHEP";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;

}







void compar_Hjj_BDT(){

  TChain * tree = new TChain("syncTree_2lSS");
  tree->Add("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/syncNtuples/syncNtuple_event_ttW_multilep.root");

  TH1F* h = new TH1F("h","h",100,-1,1.00001);
  tree->Draw("jet01_HjjBDT>>h","","goff");

  TH1F* h_sync = histo_fromlog("2lSS_SR_Hjj_BDT_80X_Summer16_IHEP.txt",13,100,-1,1.00001);

  h_sync->SetTitle("Leading jets Hjj BDT");
  h_sync->SetStats(0);
  h_sync->SetMaximum(1.25*h_sync->GetMaximum());

  h_sync->SetLineColor(kOrange-2);
  h_sync->SetFillColor(kOrange-2);

  h->SetLineColor(1);
  h->SetLineWidth(2);
  
  for(unsigned int i=0; i<5000000;i++){
    int LLR = h->GetBinContent(i);
    int IHEP = h_sync->GetBinContent(i);
    if(LLR!=IHEP){
      cout<<"i="<<i<<endl;
      cout<<"LLR="<<LLR<<endl;
      cout<<"IHEP="<<IHEP<<endl;
    }
  }
  
  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  leg->AddEntry(h,"LLR");
  leg->AddEntry(h_sync,"IHEP");
  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);


  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetLeftMargin(0.15);
  pad1->SetGridx();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  h_sync->GetYaxis()->SetTitle(Form("Number of events / %.2f",binning(h)));
  h->GetXaxis()->SetTitle("BDT");
  
  h_sync->Draw();
  cout<<h_sync->GetEntries()<<endl;;
  h->Draw("same");
  cout<<h->GetEntries()<<endl;;
  leg->Draw("same");

  // Do not draw the Y axis label on the upper plot and redraw a small
  // axis instead, in order to avoid the first label (0) to be clipped.
  h_sync->GetYaxis()->SetLabelSize(0.);
  TGaxis *axis = new TGaxis( -1, 0.5, -1, h_sync->GetMaximum(), 0.5,h_sync->GetMaximum(),510,"");
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
  TGaxis *axis2 = new TGaxis( -1, 0.91, -1, 1.09, 0.91, 1.09, 505,"");
  axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  axis2->SetLabelSize(15);
  axis2->Draw();
  
  // Y axis ratio plot settings
  h_ratio->GetYaxis()->SetTitle("LLR/IHEP");
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


  TString plotname="sync/Hjj_BDT_IHEP";
  c->SaveAs("../plots/pdf/"+plotname+".pdf");
  c->SaveAs("../plots/png/"+plotname+".png");

  return;

}





