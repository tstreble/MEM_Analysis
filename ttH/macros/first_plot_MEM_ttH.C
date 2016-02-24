#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>
#include <Helpers.C>
#include <vector>

using namespace std;



void plot_weights(){

  TString filename_MEM="/data_CMS/cms/strebler/ttH_Samples/MEM_samples/test_ttH_skim.root";

  vector<TH1F*> h;
  h.push_back(single_plot(filename_MEM,"T","log(Integral_ttH)","Integral_ttH>0",50,0,50));
  h.push_back(single_plot(filename_MEM,"T","log(Integral_ttZ)","Integral_ttZ>0",50,0,50));
  h.push_back(single_plot(filename_MEM,"T","log(Integral_ttW)","Integral_ttW>0",50,0,50));
  h.push_back(single_plot(filename_MEM,"T","log(Integral_ttjets)","Integral_ttjets>0",50,0,50));

 

  vector<TString> leg_entry;
  leg_entry.push_back("ttH hypothesis");
  leg_entry.push_back("ttZ hypothesis");
  leg_entry.push_back("ttW hypothesis");
  leg_entry.push_back("tt+jets hypothesis");

  TLegend* leg=new TLegend(0.2,0.65,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(2*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("log(w_{#Omega})");
  h[0]->GetYaxis()->SetTitle(Form("Number of events / %.2f",binning(h[0])));
h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(1,8.1,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_weights_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot2D_weights(){

  TString filename_MEM="/data_CMS/cms/strebler/ttH_Samples/MEM_samples/test_ttH_skim.root";
 
  TH2F* h= single_plot2D(filename_MEM,"T","log(Integral_ttH)","log(Integral_ttZ)","Integral_ttH>0",25,0,25,50,0,50);
  h->SetStats(0);
  h->SetLineColor(2);

  TH2F* h2= single_plot2D(filename_MEM,"T","log(Integral_ttH)","log(Integral_ttW)","Integral_ttH>0",25,0,25,50,0,50);
  h2->SetStats(0);
  h2->SetLineColor(3);

  TH2F* h3= single_plot2D(filename_MEM,"T","log(Integral_ttH)","log(Integral_ttjets)","Integral_ttH>0",25,0,25,50,0,50);
  h3->SetStats(0);
  h3->SetLineColor(4);


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);
  h->GetXaxis()->SetTitle("log(w_{ttH})");
  h->GetYaxis()->SetTitle("log(w_{B})");

  h->SetTitle("");

  h->Draw("box");
  h2->Draw("box sames");
  h3->Draw("box sames");

  TLegend* leg=new TLegend(0.2,0.7,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);

  TH2F* hbis=new TH2F();
  hbis->SetLineColor(2);
  hbis->SetLineWidth(2);

  TH2F* h2bis=new TH2F();
  h2bis->SetLineColor(3);
  h2bis->SetLineWidth(2);

  TH2F* h3bis=new TH2F();
  h3bis->SetLineColor(4);
  h3bis->SetLineWidth(2);

  leg->AddEntry(hbis,"B = ttZ hypothesis");
  leg->AddEntry(h2bis,"B = ttW hypothesis");
  leg->AddEntry(h3bis,"B = tt+jets hypothesis");
  leg->Draw("same");

  TLatex *texl = new TLatex(1,51,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_weights_ttH_2D";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_ttH_weight_perm(){

  TString filename_MEM="/data_CMS/cms/strebler/ttH_Samples/MEM_samples/test_ttH_skim.root";

  vector<TH1F*> h;
  h.push_back(single_plot(filename_MEM,"T","Integral_perm_ttH[perm_gen_match]/Integral_ttH","Integral_ttH>0",20,0,1));
  h[0]->SetBinContent(20,h[0]->GetBinContent(20)+h[0]->GetBinContent(21));

  TH1F* h2=single_plot(filename_MEM,"T","Integral_perm_ttH[0]/Integral_ttH","Integral_ttH>0 && perm_gen_match!=0",20,0,1);
  h2->Add(single_plot(filename_MEM,"T","Integral_perm_ttH[1]/Integral_ttH","Integral_ttH>0 && perm_gen_match!=1",20,0,1));
  h2->Add(single_plot(filename_MEM,"T","Integral_perm_ttH[2]/Integral_ttH","Integral_ttH>0 && perm_gen_match!=2",20,0,1));
  h2->Add(single_plot(filename_MEM,"T","Integral_perm_ttH[3]/Integral_ttH","Integral_ttH>0 && perm_gen_match!=3",20,0,1));
  h2->SetBinContent(20,h2->GetBinContent(20)+h2->GetBinContent(21));
  h.push_back(h2);

  vector<TString> leg_entry;
  leg_entry.push_back("Good permutation");
  leg_entry.push_back("Bad permutation");

  TLegend* leg=new TLegend(0.35,0.35,0.7,0.6);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.2*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("w_{ttH}(perm)/#Sigma w_{ttH}");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of permutations / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(0.01,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="MEM_weights_perm_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_comp_time(){

  TString filename_MEM="/data_CMS/cms/strebler/ttH_Samples/MEM_samples/test_ttH_skim.root";

  vector<TH1F*> h;
  h.push_back(single_plot(filename_MEM,"T","CompTime_ttH","",50,0,500));
  h.push_back(single_plot(filename_MEM,"T","CompTime_ttZ","",50,0,500));
  h.push_back(single_plot(filename_MEM,"T","CompTime_ttW","",50,0,500));
  h.push_back(single_plot(filename_MEM,"T","CompTime_ttjets","",50,0,500));


  vector<TString> leg_entry;
  leg_entry.push_back("ttH hypothesis");
  leg_entry.push_back("ttZ hypothesis");
  leg_entry.push_back("ttW hypothesis");
  leg_entry.push_back("tt+jets hypothesis");

  TLegend* leg=new TLegend(0.25,0.5,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.5*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("t [s]");
  h[0]->GetYaxis()->SetTitle("Number of events");
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(1,1.02*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="CompTime_MEM_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}
