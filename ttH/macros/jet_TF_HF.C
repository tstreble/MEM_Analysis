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





void plot_E_bin_nodRveto(bool low_E){

  TString file_VBF="/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen.root";

  TString var="recoPFJet30_e";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])<5) && abs(recoPFJet30_eta)>3";  

  vector<TString> E_cut;
  vector<TString> leg_entry;

  if(low_E){    
    for(int i=500; i<1750; i+=250){
      E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+20));
      leg_entry.push_back(Form("%i<E_{q}<%i GeV",i,i+20));
    }
  }
  else{
    for(int i=1750; i<3000; i+=250){
      E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+20));
      leg_entry.push_back(Form("%i<E_{q}<%i GeV",i,i+20));
    }
  }
 

  vector<TH1F*> h;
  for(int i=0;i<E_cut.size();i++)
    h.push_back(single_plot(file_VBF,"HTauTauTree",var,cut+E_cut[i],250,0,2500));

  		

  TLegend* leg=new TLegend(0.4,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->SetHeader("#splitline{p_{T}(reco)>30 GeV, |#eta(reco)|>3}{No 2nd parton veto}");

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    if(i>3)
      h[i]->SetLineColor(i+2);
    if(i>7)
      h[i]->SetLineColor(i-7);       
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(0.16);
  h[0]->GetXaxis()->SetTitle("E_{reco} [GeV]");
  h[0]->GetXaxis()->SetTitleOffset(1.1);
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f GeV",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Light jet energy resolution VBF sample");


  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  vector<TF1*> fit;
  for(int i=0;i<E_cut.size();i++){
    TF1* f=new TF1("f","10/([1]*sqrt(2*pi))*exp(-0.5*((x-[0])/[1])**2)",30*cosh(3),2500);
    fit.push_back(f);
    fit[i]->SetParameter(0,h[i]->GetMean());
    fit[i]->SetParameter(1,h[i]->GetRMS());
    fit[i]->SetParLimits(0,0,2500);
    //f->Draw("same");
    h[i]->Fit(fit[i],"R0");
    fit[i]->SetLineColor(h[i]->GetLineColor());
    fit[i]->Draw("same");
    //fit.push_back(f);
  }


  TString filename="jet_Ebin_HF_nodRveto";
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

  TString var="recoPFJet30_e";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])<5) && abs(recoPFJet30_eta)>3";  

  vector<TString> E_cut;
  vector<float> bin_mean;
  vector<float> bin_width;

  for(int i=30; i<120; i+=5){
    //for(int i=30; i<65; i+=5){
    E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+5));
    bin_mean.push_back(i+2.5);
    bin_width.push_back(2.5);
  }
  for(int i=120; i<250; i+=10){
    E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+10));   
    bin_mean.push_back(i+5);
    bin_width.push_back(5);
  }
  for(int i=250; i<2500; i+=20){
    //for(int i=950; i<2000; i+=100){
    E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+20));   
    bin_mean.push_back(i+10);
    bin_width.push_back(10);
  }
 

  vector<TH1F*> h_nodRveto;
  vector<TF1*> fit_nodRveto;

  TGraphErrors* mean_nodRveto=new TGraphErrors();
  TGraphErrors* sigma_nodRveto=new TGraphErrors();

  for(int i=0;i<E_cut.size();i++){
    h_nodRveto.push_back(single_plot(file_VBF,"HTauTauTree",var,cut+E_cut[i],250,0,2500));
    h_nodRveto[i]->Sumw2();
    h_nodRveto[i]->Scale(1/h_nodRveto[i]->Integral());

    TF1* f2=new TF1("f2","10/([1]*sqrt(2*pi))*exp(-0.5*((x-[0])/[1])**2)",30*cosh(3),2500);
    fit_nodRveto.push_back(f2);
    fit_nodRveto[i]->SetParameter(0,h_nodRveto[i]->GetMean());
    fit_nodRveto[i]->SetParLimits(0,0,2500);
    fit_nodRveto[i]->SetParameter(1,h_nodRveto[i]->GetRMS());
    h_nodRveto[i]->Fit(fit_nodRveto[i],"R0");

    if(fit_nodRveto[i]->GetParameter(0)>0){
      mean_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(0));
      mean_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(0));
      sigma_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(1));
      sigma_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(1));
    }

  }

  mean_nodRveto->SetMarkerStyle(21);
  mean_nodRveto->SetFillColor(0);
  sigma_nodRveto->SetMarkerStyle(21);
  sigma_nodRveto->SetFillColor(0);

  /*TLegend* leg=new TLegend(0.3,0.6,0.5,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(mean_dRveto,"2nd parton veto");
  leg->AddEntry(mean_nodRveto,"No veto");*/


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  mean_nodRveto->GetYaxis()->SetRangeUser(0,2500);
  mean_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  mean_nodRveto->GetYaxis()->SetTitle("#mu [GeV]");
  mean_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  mean_nodRveto->SetTitle("Light jet TF mean");

  mean_nodRveto->Draw("AP");
  //leg->Draw("same");

  TString filename="mean_jetTF_HF";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  TCanvas* c2=new TCanvas("c2","c2",650,600);
  c2->SetLeftMargin(0.15);

  sigma_nodRveto->GetYaxis()->SetRangeUser(0,200);
  sigma_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  sigma_nodRveto->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  sigma_nodRveto->SetTitle("Light jet TF width");

  /*TLegend* leg2=new TLegend(0.3,0.6,0.5,0.8);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.035);
  leg2->SetFillColor(0);
  leg2->AddEntry(sigma_dRveto,"2nd parton veto");
  leg2->AddEntry(sigma_nodRveto,"No veto");*/

  sigma_nodRveto->Draw("AP");
  //leg2->Draw("same");
 

  TString filename2="sigma_jetTF_HF";
  c2->SaveAs("../plots/pdf/"+filename2+".pdf");
  c2->SaveAs("../plots/png/"+filename2+".png");


  TFile* f_new = TFile::Open("jetTF_VBF_HF.root","RECREATE");
  mean_nodRveto->SetName("mean_nodRveto");
  mean_nodRveto->Write();
  sigma_nodRveto->SetName("sigma_nodRveto");
  sigma_nodRveto->Write();
  f_new->Close();

  return;

}





void plot_mean_fit(){

  TFile* f = TFile::Open("jetTF_VBF_HF.root");
  TGraphErrors* mean_nodRveto = (TGraphErrors*)f->Get("mean_nodRveto");
  
  TF1* old_TF_mean=new TF1("mean_old", "[0]+[1]*x",0,3000);
  old_TF_mean->FixParameter(0,55.99);
  old_TF_mean->FixParameter(1,0.975);

  TF1* new_TF_mean=new TF1("mean_new", "[0]+[1]*x",530,2000);
  new_TF_mean->SetParameter(0,55.99);
  new_TF_mean->SetParameter(1,0.975);
  mean_nodRveto->Fit(new_TF_mean,"R0");
  new_TF_mean->SetLineColor(3);

  TLegend* leg=new TLegend(0.3,0.6,0.5,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(mean_nodRveto,"Fitted mean");
  leg->AddEntry(old_TF_mean,"Old TF");
  leg->AddEntry(new_TF_mean,"New TF");
  leg->SetHeader("p_{T}(reco)>30 GeV, |#eta(reco)|>3");


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  mean_nodRveto->GetYaxis()->SetRangeUser(0,2500);
  mean_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  mean_nodRveto->GetYaxis()->SetTitle("#mu [GeV]");
  mean_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  mean_nodRveto->SetTitle("Light jet TF mean HF");

  mean_nodRveto->Draw("AP");  
  old_TF_mean->Draw("SAME");
  new_TF_mean->Draw("SAME");
  leg->Draw("same");

  TString filename="mean_jetTF_fit_HF";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}





void plot_sigma_fit(){

  TFile* f = TFile::Open("jetTF_VBF_HF.root");
  TGraphErrors* sigma_nodRveto = (TGraphErrors*)f->Get("sigma_nodRveto");
  
  TF1* old_TF_sigma=new TF1("res_old", "([0]+[1]*TMath::Sqrt(x))+[2]*x",0,3000);
  old_TF_sigma->FixParameter(0,31.56);
  old_TF_sigma->FixParameter(1,1.477);
  old_TF_sigma->FixParameter(2,0.07832);  

  TF1* new_TF_sigma=new TF1("res_new", "TMath::Sqrt(([0]**2+([1]*TMath::Sqrt(x))**2)+([2]*x)**2)",530,2000);
  new_TF_sigma->SetParameter(0,31.56);
  new_TF_sigma->SetParameter(1,1.477);
  new_TF_sigma->SetParameter(2,0.07832); 
  sigma_nodRveto->Fit(new_TF_sigma,"R0");
  new_TF_sigma->SetLineColor(3);

  TLegend* leg=new TLegend(0.3,0.6,0.65,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(sigma_nodRveto,"Fitted width");
  leg->AddEntry(old_TF_sigma,"Old TF");
  leg->AddEntry(new_TF_sigma,"New TF");
  leg->SetHeader("p_{T}(reco)>30 GeV, |#eta(reco)|>3");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  sigma_nodRveto->GetYaxis()->SetRangeUser(0,400);
  sigma_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  sigma_nodRveto->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  sigma_nodRveto->SetTitle("Light jet TF width HF");

  sigma_nodRveto->Draw("AP");  
  old_TF_sigma->Draw("SAME");
  new_TF_sigma->Draw("SAME");
  leg->Draw("same");

  TString filename="sigma_jetTF_fit_HF";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}
