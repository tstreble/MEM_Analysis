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

  TF1* f=new TF1("f","4*([0] * (1/([2]*sqrt(2*pi))) * exp(-0.5*((x-[1])/[2])**2) + (1-[0]) *  (1/([4]*sqrt(2*pi))) * exp(-0.5*((x-[3])/[4])**2))",-2e10,2e10);
  f->SetParameter(0,frac);
  f->SetParameter(1,mu1);
  f->SetParameter(2,sigma1);
  f->SetParameter(3,mu2);
  f->SetParameter(4,sigma2);

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

  TF1* f=new TF1("f","4*([0] * (1/([2]*sqrt(2*pi))) * exp(-0.5*((x-[1])/[2])**2) + (1-[0]) *  (1/([4]*sqrt(2*pi))) * exp(-0.5*((x-[3])/[4])**2))",-2e10,2e10);
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

  TF1* f=new TF1("f","4*([0] * (1/([2]*sqrt(2*pi))) * exp(-0.5*((x-[1])/[2])**2) + (1-[0]) *  (1/([3]*sqrt(2*pi))) * exp(-0.5*((x-[1])/[3])**2))",-2e10,2e10);
  f->SetParameter(0,frac);
  f->SetParameter(1,mu1);
  f->SetParameter(2,sigma1);
  f->SetParameter(3,sigma2);

  return f->Eval(xcur);
}





void plot_deltapT_nodRveto(){

  TString file_TTJets="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_pfMET_prod_24072015/ntuple_TTJets_dRveto_gen.root";

  TString var="recoPFJet30_pt-genpart_pt[recoPFJet30_i_closest_genpart]";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])==5) && abs(recoPFJet30_eta)>1.5 && abs(recoPFJet30_eta)<3 && genpart_pt[recoPFJet30_i_closest_genpart]>20";    

 
  TH1F* h =single_plot(file_TTJets,"HTauTauTree",var,cut,100,-200,200);
  	       
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
  h->SetMaximum(0.18);
  h->GetXaxis()->SetTitle("p_{Treco}-p_{Tgen} [GeV]");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle(Form("Fraction of events / %.2f GeV",binning(h)));
  h->GetYaxis()->SetTitleOffset(1.7);
  h->SetTitle("b-jets from quarks tt+jets sample");

  h->Draw();

  TF1* f=new TF1("f","4*([0] * (1/([2]*sqrt(2*pi))) * exp(-0.5*((x-[1])/[2])**2) + (1-[0]) *  (1/([4]*sqrt(2*pi))) * exp(-0.5*((x-[3])/[4])**2))",-200,200);
  f->SetParameter(0,1);
  f->SetParameter(1,h->GetMean());
  f->SetParameter(2,h->GetRMS());
  f->SetParameter(3,h->GetMean());
  f->SetParameter(4,h->GetRMS());
  f->SetParLimits(0,0,1);

  h->Fit(f,"R0");
  f->Draw("same");

  TF1* g=new TF1("g","4*(1/([1]*sqrt(2*pi))) * exp(-0.5*((x-[0])/[1])**2)",-200,200);
  g->SetParameter(0,h->GetMean());
  g->SetParameter(1,h->GetRMS());
  g->SetLineStyle(7);

  h->Fit(g,"R0");
  //g->Draw("same");

  leg->SetHeader(Form("#splitline{p_{T}(reco)>30 GeV, 1.5<|#eta(reco)|<3}{f(#Deltap_{T})=%.2fG_{1}+%.2fG_{2}}",f->GetParameter(0),1-f->GetParameter(0)));
  leg->Draw("same");


  TString filename="bjet_bigauss_deltapT_endcap_nodRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}









void plot_pT_bin_nodRveto(bool low_pT){

  TString file_TTJets="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_pfMET_prod_24072015/ntuple_TTJets_dRveto_gen.root";

  TString var_pT="recoPFJet30_pt";
  TString var_deltapT="recoPFJet30_pt-genpart_pt[recoPFJet30_i_closest_genpart]";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])==5) && abs(recoPFJet30_eta)>1.5 && abs(recoPFJet30_eta)<3 && genpart_pt[recoPFJet30_i_closest_genpart]>20";  

  vector<TString> pT_cut;
  vector<TString> leg_entry;
  vector<float> pT_mean_bin;

  if(low_pT){
    for(int i=40; i<120; i+=20){
    //for(int i=80; i<90; i+=20){

      pT_cut.push_back(Form("&& genpart_pt[recoPFJet30_i_closest_genpart]>%i && genpart_pt[recoPFJet30_i_closest_genpart]<%i",i,i+5));
      leg_entry.push_back(Form("%i<p_{T}(gen)<%i GeV",i,i+5));
      pT_mean_bin.push_back(i+2.5);
    }
  }
  else{
    for(int i=120; i<250; i+=30){
    //for(int i=120; i<180; i+=20){

      pT_cut.push_back(Form("&& genpart_pt[recoPFJet30_i_closest_genpart]>%i && genpart_pt[recoPFJet30_i_closest_genpart]<%i",i,i+10));
      leg_entry.push_back(Form("%i<p_{T}(gen)<%i GeV",i,i+10));
      pT_mean_bin.push_back(i+5);
    }
  }
 

  vector<TH1F*> h_pT;
  vector<TH1F*> h_deltapT;

  for(unsigned int i=0;i<pT_cut.size();i++){
    h_pT.push_back(single_plot(file_TTJets,"HTauTauTree",var_pT,cut+pT_cut[i],90,0,360));
    h_deltapT.push_back(single_plot(file_TTJets,"HTauTauTree",var_deltapT,cut+pT_cut[i],90,-180,180));
  }
  		

  TLegend* leg=new TLegend(0.4,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  //leg->SetHeader("#splitline{p_{T}(reco)>30 GeV, |#eta(reco)|<1.5}{No 2nd parton veto}");
  leg->SetHeader("p_{T}(reco)>30 GeV, 1.5<|#eta(reco)|<3");

  for(unsigned int i=0; i<h_pT.size();i++){
    h_pT[i]->SetLineColor(i+1);
    if(i>3)
      h_pT[i]->SetLineColor(i+2);
    if(i>7)
      h_pT[i]->SetLineColor(i-7);       
    h_pT[i]->SetLineWidth(2);
    h_pT[i]->Sumw2();
    h_pT[i]->SetStats(0);
    h_pT[i]->Scale(1/h_pT[i]->Integral());
    h_deltapT[i]->Scale(1/h_deltapT[i]->Integral());
    leg->AddEntry(h_pT[i],leg_entry[i]);
  }


  h_pT=sort_histo(h_pT);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h_pT[0]->SetMinimum(0);
  h_pT[0]->SetMaximum(0.3);
  h_pT[0]->GetXaxis()->SetTitle("p_{T}(reco) [GeV]");
  h_pT[0]->GetXaxis()->SetTitleOffset(1.1);
  h_pT[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f GeV",binning(h_pT[0])));
  h_pT[0]->GetYaxis()->SetTitleOffset(1.7);
  h_pT[0]->SetTitle("b-jet p_{T} resolution tt+jets sample");


  h_pT[0]->Draw();
  for(unsigned int i=1; i<h_pT.size();i++){
    h_pT[i]->Draw("same");
  }
  
  leg->Draw("same");


  vector<TF1*> fit;
  for(unsigned int i=0;i<pT_cut.size();i++){
    TF1* f=new TF1("f","4/([1]*sqrt(2*pi))*exp(-0.5*((x-[0])/[1])**2)",30,360);
    fit.push_back(f);
    fit[i]->SetParameter(0,h_pT[i]->GetMean());
    fit[i]->SetParameter(1,h_pT[i]->GetRMS());
    fit[i]->SetParLimits(0,0,500);
    h_pT[i]->Fit(fit[i],"R0");
    fit[i]->SetLineColor(h_pT[i]->GetLineColor());
    fit[i]->SetLineStyle(7);
    fit[i]->Draw("same");
  }

  vector<TF1*> fit_double;
  for(unsigned int i=0;i<pT_cut.size();i++){

    TF1* f=new TF1("f",double_gauss,-180,180,5);
    f->SetParameter(0,h_deltapT[i]->GetMean());
    f->SetParameter(1,h_deltapT[i]->GetRMS());
    f->SetParameter(2,h_deltapT[i]->GetMean());
    f->SetParameter(3,h_deltapT[i]->GetRMS());
    f->FixParameter(4,0.71);
    h_deltapT[i]->Fit(f,"R0");

    TF1* f2=new TF1("f2",double_gauss,30,360,5);
    f2->SetParameter(0,f->GetParameter(0)+pT_mean_bin[i]);
    f2->SetParameter(1,f->GetParameter(1));
    f2->SetParameter(2,f->GetParameter(2)+pT_mean_bin[i]);
    f2->SetParameter(3,f->GetParameter(3));
    f2->SetParameter(4,f->GetParameter(4));
    fit_double.push_back(f2);

    fit_double[i]->SetLineColor(h_pT[i]->GetLineColor());
    fit_double[i]->Draw("same");  



  }


  TString filename="bjet_bigauss_pTbin_endcap_nodRveto";
  if(low_pT)
    filename+="_low_pT";
  else
    filename+="_high_pT";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}












void plot_mean_sigma_jetTF(){

  TString file_TTJets="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_pfMET_prod_24072015/ntuple_TTJets_dRveto_gen.root";

  TString var="recoPFJet30_pt-genpart_pt[recoPFJet30_i_closest_genpart]";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])==5) && abs(recoPFJet30_eta)>1.5 && abs(recoPFJet30_eta)<3 && genpart_pt[recoPFJet30_i_closest_genpart]>20";  

  vector<TString> pT_cut;
  vector<float> bin_mean;
  vector<float> bin_width;

  /*for(int i=30; i<120; i+=5){
    //for(int i=40; i<120; i+=20){
    E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+5));
    bin_mean.push_back(i+2.5);
    bin_width.push_back(2.5);
    }*/
  for(int i=30; i<250; i+=10){
    pT_cut.push_back(Form("&& genpart_pt[recoPFJet30_i_closest_genpart]>%i && genpart_pt[recoPFJet30_i_closest_genpart]<%i",i,i+10));   
    bin_mean.push_back(i+5);
    bin_width.push_back(5);
  }
 

  //vector<TH1F*> h_nodRveto;
  //vector<TF1*> fit_nodRveto;

  TGraphErrors* frac_nodRveto=new TGraphErrors();
  TGraphErrors* mean1_nodRveto=new TGraphErrors();
  TGraphErrors* sigma1_nodRveto=new TGraphErrors();
  TGraphErrors* mean2_nodRveto=new TGraphErrors();
  TGraphErrors* sigma2_nodRveto=new TGraphErrors();

  for(unsigned int i=0;i<pT_cut.size();i++){
    TH1F* h_nodRveto = single_plot(file_TTJets,"HTauTauTree",var,cut+pT_cut[i],90,-180,180);
    
    h_nodRveto->Sumw2();
    h_nodRveto->Scale(1/h_nodRveto->Integral());
  
    TF1* f=new TF1("f",double_gauss,-180,180,5);
    f->SetParameter(0,h_nodRveto->GetMean());
    f->SetParameter(1,h_nodRveto->GetRMS());
    f->SetParameter(2,h_nodRveto->GetMean());
    f->SetParameter(3,h_nodRveto->GetRMS());
    //f->FixParameter(4,0.67);

    f->SetParameter(4,0.71);
    f->SetParLimits(4,0,1);

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
  frac_nodRveto->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  frac_nodRveto->GetYaxis()->SetTitle("f");
  frac_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  frac_nodRveto->SetTitle("b-jet TF relative normalization");

  frac_nodRveto->Draw("AP");

  TString filename0="frac_bjetTF_endcap_bigauss_pT";
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

  mean1_nodRveto->GetYaxis()->SetRangeUser(0,350);
  mean1_nodRveto->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitle("#mu [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  mean1_nodRveto->SetTitle("b-jet TF means");

  mean1_nodRveto->Draw("AP");
  mean2_nodRveto->Draw("Psame");  
  leg->Draw("same");


  TString filename="mean_bjetTF_endcap_bigauss_pT";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  TCanvas* c2=new TCanvas("c2","c2",650,600);
  c2->SetLeftMargin(0.15);

  sigma1_nodRveto->GetYaxis()->SetRangeUser(0,200);
  sigma1_nodRveto->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  sigma1_nodRveto->SetTitle("b-jet TF widths");

  TLegend* leg2=new TLegend(0.3,0.6,0.5,0.8);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.035);
  leg2->SetFillColor(0);
  leg2->AddEntry(sigma1_nodRveto,"1st Gaussian");
  leg2->AddEntry(sigma2_nodRveto,"2nd Gaussian");

  sigma1_nodRveto->Draw("AP");
  sigma2_nodRveto->Draw("Psame");  
  leg2->Draw("same");
 

  TString filename2="sigma_bjetTF_endcap_bigauss_pT";
  c2->SaveAs("../plots/pdf/"+filename2+".pdf");
  c2->SaveAs("../plots/png/"+filename2+".png");


  TFile* f_new = TFile::Open("bjetTF_endcap_bigauss_pT_TTjets.root","RECREATE");
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

  TString file_TTJets="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_pfMET_prod_24072015/ntuple_TTJets_dRveto_gen.root";

  TString var="recoPFJet30_pt-genpart_pt[recoPFJet30_i_closest_genpart]";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])==5) && abs(recoPFJet30_eta)>1.5 && abs(recoPFJet30_eta)<3 && genpart_pt[recoPFJet30_i_closest_genpart]>20";  

  vector<TString> pT_cut;
  vector<float> bin_mean;
  vector<float> bin_width;

  /*for(int i=30; i<120; i+=5){
    //for(int i=40; i<120; i+=20){
    E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+5));
    bin_mean.push_back(i+2.5);
    bin_width.push_back(2.5);
    }*/
  for(int i=30; i<250; i+=10){
    pT_cut.push_back(Form("&& genpart_pt[recoPFJet30_i_closest_genpart]>%i && genpart_pt[recoPFJet30_i_closest_genpart]<%i",i,i+10));   
    bin_mean.push_back(i+5);
    bin_width.push_back(5);
  }
 

  //vector<TH1F*> h_nodRveto;
  //vector<TF1*> fit_nodRveto;

  TGraphErrors* frac_nodRveto=new TGraphErrors();
  TGraphErrors* mean1_nodRveto=new TGraphErrors();
  TGraphErrors* sigma1_nodRveto=new TGraphErrors();
  TGraphErrors* mean2_nodRveto=new TGraphErrors();
  TGraphErrors* sigma2_nodRveto=new TGraphErrors();

  for(unsigned int i=0;i<pT_cut.size();i++){
    TH1F* h_nodRveto = single_plot(file_TTJets,"HTauTauTree",var,cut+pT_cut[i],90,-180,180);
    
    h_nodRveto->Sumw2();
    h_nodRveto->Scale(1/h_nodRveto->Integral());
  
    TF1* f=new TF1("f",double_gauss,-180,180,5);
    f->SetParameter(0,h_nodRveto->GetMean());
    f->SetParameter(1,h_nodRveto->GetRMS());
    f->SetParameter(2,h_nodRveto->GetMean());
    f->SetParameter(3,h_nodRveto->GetRMS());
    f->FixParameter(4,0.71);

    //f->SetParameter(4,0.67);
    //f->SetParLimits(4,0,1);

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

  mean1_nodRveto->GetYaxis()->SetRangeUser(0,350);
  mean1_nodRveto->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitle("#mu [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  mean1_nodRveto->SetTitle("b-jet TF means");

  mean1_nodRveto->Draw("AP");
  mean2_nodRveto->Draw("Psame");  
  leg->Draw("same");


  TString filename="mean_bjetTF_endcap_bigauss_pT_fixfrac";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  TCanvas* c2=new TCanvas("c2","c2",650,600);
  c2->SetLeftMargin(0.15);

  sigma1_nodRveto->GetYaxis()->SetRangeUser(0,200);
  sigma1_nodRveto->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  sigma1_nodRveto->SetTitle("b-jet TF widths");

  TLegend* leg2=new TLegend(0.3,0.6,0.5,0.8);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.035);
  leg2->SetFillColor(0);
  leg2->AddEntry(sigma1_nodRveto,"1st Gaussian");
  leg2->AddEntry(sigma2_nodRveto,"2nd Gaussian");

  sigma1_nodRveto->Draw("AP");
  sigma2_nodRveto->Draw("Psame");  
  leg2->Draw("same");
 

  TString filename2="sigma_bjetTF_endcap_bigauss_pT_fixfrac";
  c2->SaveAs("../plots/pdf/"+filename2+".pdf");
  c2->SaveAs("../plots/png/"+filename2+".png");


  TFile* f_new = TFile::Open("bjetTF_endcap_bigauss_pT_fixfrac_TTjets.root","RECREATE");
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

  TFile* f = TFile::Open("bjetTF_endcap_bigauss_pT_fixfrac_TTjets.root");
  TGraphErrors* mean1_nodRveto = (TGraphErrors*)f->Get("mean1_nodRveto");
  TGraphErrors* mean2_nodRveto = (TGraphErrors*)f->Get("mean2_nodRveto");

  TF1* new_TF_mean1=new TF1("mean_new1", "[0]+[1]*x",70,210);
  new_TF_mean1->SetParameter(0,2.325);
  new_TF_mean1->SetParameter(1,1.014);
  mean1_nodRveto->Fit(new_TF_mean1,"R0");
  new_TF_mean1->SetLineColor(3);

  TF1* new_TF_mean2=new TF1("mean_new2", "[0]+[1]*x",70,210);
  new_TF_mean2->SetParameter(0,2.325);
  new_TF_mean2->SetParameter(1,1.014);
  mean2_nodRveto->Fit(new_TF_mean2,"R0");
  new_TF_mean2->SetLineColor(4);

  TLegend* leg=new TLegend(0.2,0.55,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(mean1_nodRveto,"#mu_{1}");
  leg->AddEntry(mean2_nodRveto,"#mu_{2}");
  leg->AddEntry(new_TF_mean1,Form("New TF #mu_{1}: %.2f + %.2f p_{T}",new_TF_mean1->GetParameter(0),new_TF_mean1->GetParameter(1)));
  leg->AddEntry(new_TF_mean2,Form("New TF #mu_{2}: %.2f + %.2f p_{T}",new_TF_mean2->GetParameter(0),new_TF_mean2->GetParameter(1)));
  leg->SetHeader("p_{T}(reco)>30 GeV, 1.5<|#eta(reco)|<3");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  mean1_nodRveto->GetYaxis()->SetRangeUser(0,350);
  mean1_nodRveto->GetXaxis()->SetTitle("p_{T} [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitle("#mu [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  mean1_nodRveto->SetTitle("b-jet TF means");

  mean1_nodRveto->Draw("AP");
  mean2_nodRveto->Draw("Psame");  
  new_TF_mean1->Draw("SAME");
  new_TF_mean2->Draw("SAME");

  leg->Draw("same");

  TString filename="mean_bjetTF_endcap_bigauss_pT_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}



void plot_sigma_fit(){

  TFile* f = TFile::Open("bjetTF_endcap_bigauss_pT_fixfrac_TTjets.root");
  TGraphErrors* sigma1_nodRveto = (TGraphErrors*)f->Get("sigma1_nodRveto");
  TGraphErrors* sigma2_nodRveto = (TGraphErrors*)f->Get("sigma2_nodRveto");

  TF1* new_TF_sigma1=new TF1("sigma_new1", "TMath::Sqrt(([0]**2+([1]*TMath::Sqrt(x))**2)+([2]*x)**2)",70,210);
  new_TF_sigma1->SetParameter(0,0);
  new_TF_sigma1->SetParameter(1,1.52);
  new_TF_sigma1->SetParameter(2,0.026); 
  new_TF_sigma1->SetParLimits(2,0,500); 
  sigma1_nodRveto->Fit(new_TF_sigma1,"R0");
  new_TF_sigma1->SetLineColor(3);

  TF1* new_TF_sigma2=new TF1("sigma_new2", "TMath::Sqrt(([0]**2+([1]*TMath::Sqrt(x))**2)+([2]*x)**2)",70,210);
  new_TF_sigma2->SetParameter(0,0);
  new_TF_sigma2->SetParLimits(0,0,500); 
  new_TF_sigma2->SetParameter(1,1.52);
  new_TF_sigma2->SetParameter(2,0.026); 
  sigma2_nodRveto->Fit(new_TF_sigma2,"R0");
  new_TF_sigma2->SetLineColor(4);

  TLegend* leg=new TLegend(0.2,0.6,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(sigma1_nodRveto,"#sigma_{1}");
  leg->AddEntry(sigma2_nodRveto,"#sigma_{2}");
  leg->AddEntry(new_TF_sigma1,Form("New TF #sigma_{1}: %.2f #oplus %.2f #sqrt{p_{T}} #oplus %.2f p_{T}",new_TF_sigma1->GetParameter(0),new_TF_sigma1->GetParameter(1),new_TF_sigma1->GetParameter(2)));
  leg->AddEntry(new_TF_sigma2,Form("New TF #sigma_{2}: %.2f #oplus %.2f #sqrt{p_{T}} #oplus %.2f p_{T}",new_TF_sigma2->GetParameter(0),new_TF_sigma2->GetParameter(1),new_TF_sigma2->GetParameter(2)));
  leg->SetHeader("p_{T}(reco)>30 GeV, 1.5<|#eta(reco)|<3");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  sigma1_nodRveto->GetYaxis()->SetRangeUser(0,200);
  sigma1_nodRveto->GetXaxis()->SetTitle("p_{T} [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  sigma1_nodRveto->SetTitle("b-jet TF width");

  sigma1_nodRveto->Draw("AP");
  sigma2_nodRveto->Draw("Psame");  
  new_TF_sigma1->Draw("SAME");
  new_TF_sigma2->Draw("SAME");

  leg->Draw("same");

  TString filename="sigma_bjetTF_endcap_bigauss_pT_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




