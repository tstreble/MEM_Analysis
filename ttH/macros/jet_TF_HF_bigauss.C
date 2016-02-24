#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <iostream>
#include <TLegend.h>
#include <TBranch.h>
#include <TClonesArray.h>
#include <TChain.h>
#include <TMath.h>
#include <TF1.h>
#include "Helpers.C"
#include <TSystem.h>
#include <TLatex.h>
#include <TGraphErrors.h>

using namespace std;



double double_gauss(double* x, double* par){
  double xcur = x[0];
  double mu1 = par[0];
  double sigma1 = par[1];
  double mu2 = par[2];
  double sigma2 = par[3];
  double frac = par[4];
  double bin_width = par[5];

  TF1* f=new TF1("f","[5]*([0] * (1/([2]*sqrt(2*pi))) * exp(-0.5*((x-[1])/[2])**2) + (1-[0]) *  (1/([4]*sqrt(2*pi))) * exp(-0.5*((x-[3])/[4])**2))",-2e10,2e10);
  f->SetParameter(0,frac);
  f->SetParameter(1,mu1);
  f->SetParameter(2,sigma1);
  f->SetParameter(3,mu2);
  f->SetParameter(4,sigma2);
  f->SetParameter(5,bin_width);

  return f->Eval(xcur);
}





double double_gauss_order(double* x, double* par){
  double xcur = x[0];
  double mu1 = par[0];
  double sigma1 = par[1];
  double mu2 = par[2];
  double sigma2 = par[3];
  double frac = par[4];

  if(sigma2>sigma1){
    mu1 = par[3];
    sigma1 = par[4];
    mu2 = par[0];
    sigma2 = par[1];
    frac = 1-par[4];
  }

  TF1* f=new TF1("f","20*([0] * (1/([2]*sqrt(2*pi))) * exp(-0.5*((x-[1])/[2])**2) + (1-[0]) *  (1/([4]*sqrt(2*pi))) * exp(-0.5*((x-[3])/[4])**2))",-2e10,2e10);
  f->SetParameter(0,frac);
  f->SetParameter(1,mu1);
  f->SetParameter(2,sigma1);
  f->SetParameter(3,mu2);
  f->SetParameter(4,sigma2);

  return f->Eval(xcur);
}



double double_gauss_samemu(double* x, double* par){
  double xcur = x[0];
  double mu1 = par[0];
  double sigma1 = par[1];
  double sigma2 = par[2];
  double frac = par[3];

  TF1* f=new TF1("f","20*([0] * (1/([2]*sqrt(2*pi))) * exp(-0.5*((x-[1])/[2])**2) + (1-[0]) *  (1/([3]*sqrt(2*pi))) * exp(-0.5*((x-[1])/[3])**2))",-2e10,2e10);
  f->SetParameter(0,frac);
  f->SetParameter(1,mu1);
  f->SetParameter(2,sigma1);
  f->SetParameter(3,sigma2);

  return f->Eval(xcur);
}





void plot_deltaE_nodRveto(){

  TString file_VBF="/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen.root";

  TString var="recoPFJet30_e-genpart_e[recoPFJet30_i_closest_genpart]";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])<5) && abs(recoPFJet30_eta)>3";
 
  TH1F* h =single_plot(file_VBF,"HTauTauTree",var,cut,150,-2000,1000);
  	       
  TLegend* leg=new TLegend(0.17,0.8,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  h->SetLineColor(1);    
  h->SetLineWidth(2);
  h->Sumw2();
  h->SetStats(0);
  h->Scale(1/h->Integral());

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h->SetMinimum(0);
  h->SetMaximum(1.2*h->GetMaximum());
  h->GetXaxis()->SetTitle("E_{reco}-E_{gen} [GeV]");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle(Form("Fraction of events / %.2f GeV",binning(h)));
  h->GetYaxis()->SetTitleOffset(1.7);
  h->SetTitle("Light jets from quarks VBF sample");

  h->Draw();

  TF1* f=new TF1("f","20*([0] * (1/([2]*sqrt(2*pi))) * exp(-0.5*((x-[1])/[2])**2) + (1-[0]) *  (1/([4]*sqrt(2*pi))) * exp(-0.5*((x-[3])/[4])**2))",-2000,1000);
  f->SetParameter(0,0.66);
  f->SetParameter(1,h->GetMean());
  f->SetParameter(2,h->GetRMS());
  f->SetParameter(3,h->GetMean());
  f->SetParameter(4,h->GetRMS());
  f->SetParLimits(0,0,1);

  h->Fit(f,"R0");
  f->Draw("same");

  leg->SetHeader(Form("#splitline{p_{T}(reco)>30 GeV, |#eta(reco)|>3}{f(#DeltaE)=%.2fG_{1}+%.2fG_{2}}",f->GetParameter(0),1-f->GetParameter(0)));
  leg->Draw("same");


  TString filename="jet_bigauss_deltaE_HF_nodRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}






void plot_deltaE_gluon_nodRveto(){

  TString file_VBF="/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen.root";

  TString var="recoPFJet30_e-genpart_e[recoPFJet30_i_closest_genpart]";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])==21) && abs(recoPFJet30_eta)>3";    

 
  TH1F* h =single_plot(file_VBF,"HTauTauTree",var,cut,100,-2000,2000);
  	       
  TLegend* leg=new TLegend(0.17,0.8,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  h->SetLineColor(1);    
  h->SetLineWidth(2);
  h->Sumw2();
  h->SetStats(0);
  h->Scale(1/h->Integral());

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h->SetMinimum(0);
  h->SetMaximum(1.2*h->GetMaximum());
  h->GetXaxis()->SetTitle("E_{reco}-E_{gen} [GeV]");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle(Form("Fraction of events / %.2f GeV",binning(h)));
  h->GetYaxis()->SetTitleOffset(1.7);
  h->SetTitle("Light jets from gluons VBF sample");

  h->Draw();


  TString filename="jet_bigauss_gluon_deltaE_HF_nodRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}








void plot_E_bin_nodRveto(bool low_E){

  TString file_VBF="/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen.root";

  TString var_E="recoPFJet30_e";
  TString var_deltaE="recoPFJet30_e-genpart_e[recoPFJet30_i_closest_genpart]";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])<5) && abs(recoPFJet30_eta)>3";  

  vector<TString> E_cut;
  vector<TString> leg_entry;
  vector<float> E_mean_bin;

  if(low_E){    
    for(int i=500; i<1750; i+=250){
      E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+20));
      leg_entry.push_back(Form("%i<E_{q}<%i GeV",i,i+20));
      E_mean_bin.push_back(i+10);
    }
  }
  else{
    for(int i=1750; i<3000; i+=250){
      E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+20));
      leg_entry.push_back(Form("%i<E_{q}<%i GeV",i,i+20));
      E_mean_bin.push_back(i+10);
    }
  }


  vector<TH1F*> h_E;
  vector<TH1F*> h_deltaE;

  for(int i=0;i<E_cut.size();i++){
    h_E.push_back(single_plot(file_VBF,"HTauTauTree",var_E,cut+E_cut[i],125,0,2500));
    h_deltaE.push_back(single_plot(file_VBF,"HTauTauTree",var_deltaE,cut+E_cut[i],150,-2000,1000));
  }
  		

  TLegend* leg=new TLegend(0.4,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->SetHeader("p_{T}(reco)>30 GeV, |#eta(reco)|>3");

  for(unsigned int i=0; i<h_E.size();i++){
    h_E[i]->SetLineColor(i+1);
    if(i>3)
      h_E[i]->SetLineColor(i+2);
    if(i>7)
      h_E[i]->SetLineColor(i-7);       
    h_E[i]->SetLineWidth(2);
    h_E[i]->Sumw2();
    h_E[i]->SetStats(0);
    h_E[i]->Scale(1/h_E[i]->Integral());
    h_deltaE[i]->Scale(1/h_deltaE[i]->Integral());
    leg->AddEntry(h_E[i],leg_entry[i]);
  }


  h_E=sort_histo(h_E);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_E[0]->SetMinimum(0);
  h_E[0]->SetMaximum(0.16);
  h_E[0]->GetXaxis()->SetTitle("E_{reco} [GeV]");
  h_E[0]->GetXaxis()->SetTitleOffset(1.1);
  h_E[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f GeV",binning(h_E[0])));
  h_E[0]->GetYaxis()->SetTitleOffset(1.7);
  h_E[0]->SetTitle("Light jet energy resolution VBF sample");


  h_E[0]->Draw();
  for(unsigned int i=1; i<h_E.size();i++){
    h_E[i]->Draw("same");
  }
  
  leg->Draw("same");


  vector<TF1*> fit;
  for(int i=0;i<E_cut.size();i++){
    TF1* f=new TF1("f","20/([1]*sqrt(2*pi))*exp(-0.5*((x-[0])/[1])**2)",0,2500);
    fit.push_back(f);
    fit[i]->SetParameter(0,h_E[i]->GetMean());
    fit[i]->SetParameter(1,h_E[i]->GetRMS());
    fit[i]->SetParLimits(0,0,5000);
    h_E[i]->Fit(fit[i],"R0");
    fit[i]->SetLineColor(h_E[i]->GetLineColor());
    fit[i]->SetLineStyle(7);
    fit[i]->Draw("same");
  }

  vector<TF1*> fit_double;
  for(int i=0;i<E_cut.size();i++){

    TF1* f=new TF1("f",double_gauss,-2000,1000,6);
    f->SetParameter(0,h_deltaE[i]->GetMean());
    f->SetParameter(1,h_deltaE[i]->GetRMS());
    f->SetParameter(2,h_deltaE[i]->GetMean());
    f->SetParameter(3,h_deltaE[i]->GetRMS());
    f->FixParameter(4,0.501);
    f->FixParameter(5,binning(h_deltaE[i]));
    h_deltaE[i]->Fit(f,"R0");

    TF1* f2=new TF1("f2",double_gauss,0,2500,6);
    f2->SetParameter(0,f->GetParameter(0)+E_mean_bin[i]);
    f2->SetParameter(1,f->GetParameter(1));
    f2->SetParameter(2,f->GetParameter(2)+E_mean_bin[i]);
    f2->SetParameter(3,f->GetParameter(3));
    f2->SetParameter(4,f->GetParameter(4));
    f2->SetParameter(5,binning(h_E[i]));
    fit_double.push_back(f2);

    fit_double[i]->SetLineColor(h_E[i]->GetLineColor());
    fit_double[i]->Draw("same");  



  }


  TString filename="jet_bigauss_Ebin_HF_nodRveto";
  if(low_E)
    filename+="_low_E";
  else
    filename+="_high_E";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}












void plot_mean_sigma_jetTF(){

  TString file_VBF="/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen.root";

  TString var="recoPFJet30_e-genpart_e[recoPFJet30_i_closest_genpart]";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])<5) && abs(recoPFJet30_eta)>3";  

  vector<TString> E_cut;
  vector<float> bin_mean;
  vector<float> bin_width;

  //for(int i=30; i<120; i+=5){
  /*for(int i=30; i<65; i+=5){
    E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+5));
    bin_mean.push_back(i+2.5);
    bin_width.push_back(2.5);
  }
  for(int i=120; i<250; i+=10){
    E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+10));   
    bin_mean.push_back(i+5);
    bin_width.push_back(5);
    }*/
  for(int i=250; i<2500; i+=20){
    //for(int i=950; i<2000; i+=100){
    E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+20));   
    bin_mean.push_back(i+10);
    bin_width.push_back(10);
  }
 

  TGraphErrors* frac_nodRveto=new TGraphErrors();
  TGraphErrors* mean1_nodRveto=new TGraphErrors();
  TGraphErrors* sigma1_nodRveto=new TGraphErrors();
  TGraphErrors* mean2_nodRveto=new TGraphErrors();
  TGraphErrors* sigma2_nodRveto=new TGraphErrors();

  for(int i=0;i<E_cut.size();i++){
    TH1F* h_nodRveto = single_plot(file_VBF,"HTauTauTree",var,cut+E_cut[i],150,-2000,1000);
    
    h_nodRveto->Sumw2();
    h_nodRveto->Scale(1/h_nodRveto->Integral());
  
    TF1* f=new TF1("f",double_gauss,-2000,1000,6);
    f->SetParameter(0,h_nodRveto->GetMean());
    f->SetParameter(1,h_nodRveto->GetRMS());
    f->SetParameter(2,h_nodRveto->GetMean());
    f->SetParameter(3,h_nodRveto->GetRMS());
    //f->FixParameter(4,0.501);

    f->SetParameter(4,0.501);
    f->SetParLimits(4,0,1);

    f->FixParameter(5,binning(h_nodRveto));

    if(i>0){
      double x,y;
      sigma1_nodRveto->GetPoint(i-1,x,y);      
      f->SetParameter(1,y);
      sigma2_nodRveto->GetPoint(i-1,x,y);      
      f->SetParameter(3,y);
      frac_nodRveto->GetPoint(i-1,x,y);
      f->SetParameter(4,y);
    }

    h_nodRveto->Fit(f,"R0");

    if(f->GetParameter(1)>f->GetParameter(3)){
      frac_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(4));
      frac_nodRveto->SetPointError(i,bin_width[i],f->GetParError(4));
      mean1_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(0)+bin_mean[i]);
      mean1_nodRveto->SetPointError(i,bin_width[i],f->GetParError(0));
      sigma1_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(1));
      sigma1_nodRveto->SetPointError(i,bin_width[i],f->GetParError(1));
      mean2_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(2)+bin_mean[i]);
      mean2_nodRveto->SetPointError(i,bin_width[i],f->GetParError(2));
      sigma2_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(3));
      sigma2_nodRveto->SetPointError(i,bin_width[i],f->GetParError(3));
    }
    else{
      frac_nodRveto->SetPoint(i,bin_mean[i],1-f->GetParameter(4));
      frac_nodRveto->SetPointError(i,bin_width[i],f->GetParError(4));
      mean2_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(0)+bin_mean[i]);
      mean2_nodRveto->SetPointError(i,bin_width[i],f->GetParError(0));
      sigma2_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(1));
      sigma2_nodRveto->SetPointError(i,bin_width[i],f->GetParError(1));
      mean1_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(2)+bin_mean[i]);
      mean1_nodRveto->SetPointError(i,bin_width[i],f->GetParError(2));
      sigma1_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(3));
      sigma1_nodRveto->SetPointError(i,bin_width[i],f->GetParError(3));
    }

    delete h_nodRveto;
    delete f;

  }

  frac_nodRveto->SetMarkerStyle(20);
  frac_nodRveto->SetFillColor(0);

  mean1_nodRveto->SetMarkerStyle(20);
  mean1_nodRveto->SetFillColor(0);
  sigma1_nodRveto->SetMarkerStyle(20);
  sigma1_nodRveto->SetFillColor(0);  

  mean2_nodRveto->SetMarkerStyle(21);
  mean2_nodRveto->SetFillColor(0);
  sigma2_nodRveto->SetMarkerStyle(21);
  sigma2_nodRveto->SetFillColor(0);

  TCanvas* c0=new TCanvas("c0","c0",650,600);
  c0->SetLeftMargin(0.15);

  frac_nodRveto->GetYaxis()->SetRangeUser(0,1);
  frac_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  frac_nodRveto->GetYaxis()->SetTitle("f");
  frac_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  frac_nodRveto->SetTitle("Light jet TF relative normalization");

  frac_nodRveto->Draw("AP");

  TString filename0="frac_jetTF_bigauss_HF";
  c0->SaveAs("../plots/pdf/"+filename0+".pdf");
  c0->SaveAs("../plots/png/"+filename0+".png");

  TLegend* leg=new TLegend(0.3,0.6,0.5,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(mean1_nodRveto,"1st Gaussian");
  leg->AddEntry(mean2_nodRveto,"2nd Gaussian");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  mean1_nodRveto->GetYaxis()->SetRangeUser(0,2500);
  mean1_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitle("#mu [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  mean1_nodRveto->SetTitle("Light jet TF means");

  mean1_nodRveto->Draw("AP");
  mean2_nodRveto->Draw("Psame");  
  leg->Draw("same");


  TString filename="mean_jetTF_bigauss_HF";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  TCanvas* c2=new TCanvas("c2","c2",650,600);
  c2->SetLeftMargin(0.15);

  sigma1_nodRveto->GetYaxis()->SetRangeUser(0,750);
  sigma1_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  sigma1_nodRveto->SetTitle("Light jet TF widths");

  TLegend* leg2=new TLegend(0.3,0.6,0.5,0.8);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.035);
  leg2->SetFillColor(0);
  leg2->AddEntry(sigma1_nodRveto,"1st Gaussian");
  leg2->AddEntry(sigma2_nodRveto,"2nd Gaussian");

  sigma1_nodRveto->Draw("AP");
  sigma2_nodRveto->Draw("Psame");  
  leg2->Draw("same");
 

  TString filename2="sigma_jetTF_bigauss_HF";
  c2->SaveAs("../plots/pdf/"+filename2+".pdf");
  c2->SaveAs("../plots/png/"+filename2+".png");


  TFile* f_new = TFile::Open("jetTF_bigauss_HF_TTjets.root","RECREATE");
  frac_nodRveto->SetName("frac_nodRveto");
  frac_nodRveto->Write();
  mean1_nodRveto->SetName("mean1_nodRveto");
  mean1_nodRveto->Write();
  mean2_nodRveto->SetName("mean2_nodRveto");
  mean2_nodRveto->Write();
  sigma1_nodRveto->SetName("sigma1_nodRveto");
  sigma1_nodRveto->Write();
  sigma2_nodRveto->SetName("sigma2_nodRveto");
  sigma2_nodRveto->Write();
  f_new->Close();

  return;



}





void plot_mean_sigma_jetTF_fixfrac(){

  TString file_VBF="/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen.root";

  TString var="recoPFJet30_e-genpart_e[recoPFJet30_i_closest_genpart]";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])<5) && abs(recoPFJet30_eta)>3";  

  vector<TString> E_cut;
  vector<float> bin_mean;
  vector<float> bin_width;

  //for(int i=30; i<120; i+=5){
  /*for(int i=30; i<65; i+=5){
    E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+5));
    bin_mean.push_back(i+2.5);
    bin_width.push_back(2.5);
  }
  for(int i=120; i<250; i+=10){
    E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+10));   
    bin_mean.push_back(i+5);
    bin_width.push_back(5);
    }*/
  for(int i=250; i<2500; i+=20){
    //for(int i=950; i<2000; i+=100){
    E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+20));   
    bin_mean.push_back(i+10);
    bin_width.push_back(10);
  }
 

  TGraphErrors* frac_nodRveto=new TGraphErrors();
  TGraphErrors* mean1_nodRveto=new TGraphErrors();
  TGraphErrors* sigma1_nodRveto=new TGraphErrors();
  TGraphErrors* mean2_nodRveto=new TGraphErrors();
  TGraphErrors* sigma2_nodRveto=new TGraphErrors();

  for(int i=0;i<E_cut.size();i++){
    TH1F* h_nodRveto = single_plot(file_VBF,"HTauTauTree",var,cut+E_cut[i],150,-2000,1000);
    
    h_nodRveto->Sumw2();
    h_nodRveto->Scale(1/h_nodRveto->Integral());
  
    TF1* f=new TF1("f",double_gauss,-2000,1000,6);
    f->SetParameter(0,h_nodRveto->GetMean());
    f->SetParameter(1,h_nodRveto->GetRMS());
    f->SetParameter(2,h_nodRveto->GetMean());
    f->SetParameter(3,h_nodRveto->GetRMS());
    f->FixParameter(4,0.501);

    //f->SetParameter(4,0.501);
    //f->SetParLimits(4,0,1);

    f->FixParameter(5,binning(h_nodRveto));

    if(i>0){
      double x,y;
      sigma1_nodRveto->GetPoint(i-1,x,y);      
      f->SetParameter(1,y);
      sigma2_nodRveto->GetPoint(i-1,x,y);      
      f->SetParameter(3,y);
      //frac_nodRveto->GetPoint(i-1,x,y);
      //f->SetParameter(4,y);
    }

    h_nodRveto->Fit(f,"R0");

    if(f->GetParameter(1)>f->GetParameter(3)){
      frac_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(4));
      frac_nodRveto->SetPointError(i,bin_width[i],f->GetParError(4));
      mean1_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(0)+bin_mean[i]);
      mean1_nodRveto->SetPointError(i,bin_width[i],f->GetParError(0));
      sigma1_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(1));
      sigma1_nodRveto->SetPointError(i,bin_width[i],f->GetParError(1));
      mean2_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(2)+bin_mean[i]);
      mean2_nodRveto->SetPointError(i,bin_width[i],f->GetParError(2));
      sigma2_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(3));
      sigma2_nodRveto->SetPointError(i,bin_width[i],f->GetParError(3));
    }
    else{
      frac_nodRveto->SetPoint(i,bin_mean[i],1-f->GetParameter(4));
      frac_nodRveto->SetPointError(i,bin_width[i],f->GetParError(4));
      mean2_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(0)+bin_mean[i]);
      mean2_nodRveto->SetPointError(i,bin_width[i],f->GetParError(0));
      sigma2_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(1));
      sigma2_nodRveto->SetPointError(i,bin_width[i],f->GetParError(1));
      mean1_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(2)+bin_mean[i]);
      mean1_nodRveto->SetPointError(i,bin_width[i],f->GetParError(2));
      sigma1_nodRveto->SetPoint(i,bin_mean[i],f->GetParameter(3));
      sigma1_nodRveto->SetPointError(i,bin_width[i],f->GetParError(3));
    }

    delete h_nodRveto;
    delete f;

  }

  frac_nodRveto->SetMarkerStyle(20);
  frac_nodRveto->SetFillColor(0);

  mean1_nodRveto->SetMarkerStyle(20);
  mean1_nodRveto->SetFillColor(0);
  sigma1_nodRveto->SetMarkerStyle(20);
  sigma1_nodRveto->SetFillColor(0);  

  mean2_nodRveto->SetMarkerStyle(21);
  mean2_nodRveto->SetFillColor(0);
  sigma2_nodRveto->SetMarkerStyle(21);
  sigma2_nodRveto->SetFillColor(0);

  TLegend* leg=new TLegend(0.3,0.6,0.5,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(mean1_nodRveto,"1st Gaussian");
  leg->AddEntry(mean2_nodRveto,"2nd Gaussian");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  mean1_nodRveto->GetYaxis()->SetRangeUser(0,2500);
  mean1_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitle("#mu [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  mean1_nodRveto->SetTitle("Light jet TF means");

  mean1_nodRveto->Draw("AP");
  mean2_nodRveto->Draw("Psame");  
  leg->Draw("same");


  TString filename="mean_jetTF_bigauss_HF";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  TCanvas* c2=new TCanvas("c2","c2",650,600);
  c2->SetLeftMargin(0.15);

  sigma1_nodRveto->GetYaxis()->SetRangeUser(0,750);
  sigma1_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  sigma1_nodRveto->SetTitle("Light jet TF widths");

  TLegend* leg2=new TLegend(0.3,0.6,0.5,0.8);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.035);
  leg2->SetFillColor(0);
  leg2->AddEntry(sigma1_nodRveto,"1st Gaussian");
  leg2->AddEntry(sigma2_nodRveto,"2nd Gaussian");

  sigma1_nodRveto->Draw("AP");
  sigma2_nodRveto->Draw("Psame");  
  leg2->Draw("same");
 

  TString filename2="sigma_jetTF_bigauss_HF";
  c2->SaveAs("../plots/pdf/"+filename2+".pdf");
  c2->SaveAs("../plots/png/"+filename2+".png");


  TFile* f_new = TFile::Open("jetTF_bigauss_fixfrac_HF_TTjets.root","RECREATE");
  frac_nodRveto->SetName("frac_nodRveto");
  frac_nodRveto->Write();
  mean1_nodRveto->SetName("mean1_nodRveto");
  mean1_nodRveto->Write();
  mean2_nodRveto->SetName("mean2_nodRveto");
  mean2_nodRveto->Write();
  sigma1_nodRveto->SetName("sigma1_nodRveto");
  sigma1_nodRveto->Write();
  sigma2_nodRveto->SetName("sigma2_nodRveto");
  sigma2_nodRveto->Write();
  f_new->Close();

  return;



}





void plot_mean_fit(){

  TFile* f = TFile::Open("jetTF_bigauss_fixfrac_HF_TTjets.root");
  TGraphErrors* mean1_nodRveto = (TGraphErrors*)f->Get("mean1_nodRveto");
  TGraphErrors* mean2_nodRveto = (TGraphErrors*)f->Get("mean2_nodRveto");
  
  TF1* old_TF_mean=new TF1("mean_old", "[0]+[1]*x",0,2500);
  old_TF_mean->FixParameter(0,2.325);
  old_TF_mean->FixParameter(1,1.014);

  TF1* new_TF_mean1=new TF1("mean_new1", "[0]+[1]*x",650,2000);
  new_TF_mean1->SetParameter(0,2.325);
  new_TF_mean1->SetParameter(1,1.014);
  mean1_nodRveto->Fit(new_TF_mean1,"R0");
  new_TF_mean1->SetLineColor(3);

  TF1* new_TF_mean2=new TF1("mean_new2", "[0]+[1]*x",650,2000);
  new_TF_mean2->SetParameter(0,2.325);
  new_TF_mean2->SetParameter(1,1.014);
  mean2_nodRveto->Fit(new_TF_mean2,"R0");
  new_TF_mean2->SetLineColor(4);

  TLegend* leg=new TLegend(0.2,0.6,0.7,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(mean1_nodRveto,"#mu_{1}");
  leg->AddEntry(mean2_nodRveto,"#mu_{2}");
  leg->AddEntry(old_TF_mean,"Old TF #mu");
  leg->AddEntry(new_TF_mean1,Form("New TF #mu_{1}: %.2f + %.2f E_{q}",new_TF_mean1->GetParameter(0),new_TF_mean1->GetParameter(1)));
  leg->AddEntry(new_TF_mean2,Form("New TF #mu_{2}: %.2f + %.2f E_{q}",new_TF_mean2->GetParameter(0),new_TF_mean2->GetParameter(1)));
  leg->SetHeader("p_{T}(reco)>30 GeV, |#eta(reco)|>3");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  mean1_nodRveto->GetYaxis()->SetRangeUser(0,2500);
  mean1_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitle("#mu [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  mean1_nodRveto->SetTitle("Light jet TF means");

  mean1_nodRveto->Draw("AP");
  mean2_nodRveto->Draw("Psame");  
  old_TF_mean->Draw("SAME");
  new_TF_mean1->Draw("SAME");
  new_TF_mean2->Draw("SAME");

  leg->Draw("same");

  TString filename="mean_jetTF_HF_bigauss_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}



void plot_sigma_fit(){

  TFile* f = TFile::Open("jetTF_bigauss_fixfrac_HF_TTjets.root");
  TGraphErrors* sigma1_nodRveto = (TGraphErrors*)f->Get("sigma1_nodRveto");
  TGraphErrors* sigma2_nodRveto = (TGraphErrors*)f->Get("sigma2_nodRveto");
  
  TF1* old_TF_sigma=new TF1("res_old", "([0]+[1]*TMath::Sqrt(x))+[2]*x",0,2500);
  old_TF_sigma->FixParameter(0,0);
  old_TF_sigma->FixParameter(1,1.442);
  old_TF_sigma->FixParameter(2,0.01979); 


  TF1* new_TF_sigma1=new TF1("sigma_new1", "TMath::Sqrt(([0]**2+([1]*TMath::Sqrt(x))**2)+([2]*x)**2)",650,2000);
  new_TF_sigma1->SetParameter(0,0);
  new_TF_sigma1->SetParameter(1,1.52);
  new_TF_sigma1->SetParameter(2,0.026); 
  sigma1_nodRveto->Fit(new_TF_sigma1,"R0");
  new_TF_sigma1->SetLineColor(3);

  TF1* new_TF_sigma2=new TF1("sigma_new2", "TMath::Sqrt(([0]**2+([1]*TMath::Sqrt(x))**2)+([2]*x)**2)",650,2000);
  new_TF_sigma2->SetParameter(0,0);
  new_TF_sigma2->SetParameter(1,1.52);
  new_TF_sigma2->SetParameter(2,0.026); 
  sigma2_nodRveto->Fit(new_TF_sigma2,"R0");
  new_TF_sigma2->SetLineColor(4);

  TLegend* leg=new TLegend(0.3,0.4,0.5,0.89);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(sigma1_nodRveto,"#sigma_{1}");
  leg->AddEntry(sigma2_nodRveto,"#sigma_{2}");
  leg->AddEntry(old_TF_sigma,"Old TF #sigma");
  leg->AddEntry(new_TF_sigma1,Form("#splitline{New TF #sigma_{1}:}{%.2f #oplus %.2f #sqrt{E_{q}} #oplus %.2f E_{q}}",new_TF_sigma1->GetParameter(0),new_TF_sigma1->GetParameter(1),new_TF_sigma1->GetParameter(2)));
  leg->AddEntry(new_TF_sigma2,Form("#splitline{New TF #sigma_{2}:}{%.2f #oplus %.2f #sqrt{E_{q}} #oplus %.2f E_{q}}",new_TF_sigma2->GetParameter(0),new_TF_sigma2->GetParameter(1),new_TF_sigma2->GetParameter(2)));
  leg->SetHeader("p_{T}(reco)>30 GeV, |#eta(reco)|>3");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  sigma1_nodRveto->GetYaxis()->SetRangeUser(0,1000);
  sigma1_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  sigma1_nodRveto->SetTitle("Light jet TF width");

  sigma1_nodRveto->Draw("AP");
  sigma2_nodRveto->Draw("Psame");  
  old_TF_sigma->Draw("SAME");
  new_TF_sigma1->Draw("SAME");
  new_TF_sigma2->Draw("SAME");

  leg->Draw("same");

  TString filename="sigma_jetTF_HF_bigauss_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}

