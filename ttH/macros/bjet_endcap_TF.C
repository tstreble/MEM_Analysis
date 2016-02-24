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

  TString file_TTJets="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_pfMET_prod_24072015/ntuple_TTJets_dRveto_gen.root";

  TString var="recoPFJet30_e";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && abs(genpart_pdg[recoPFJet30_i_closest_genpart])==5 && abs(recoPFJet30_eta)>1.5 && abs(recoPFJet30_eta)<3";    

  vector<TString> E_cut;
  vector<TString> leg_entry;

  if(low_E){
    for(int i=40; i<120; i+=20){
      E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+5));
      leg_entry.push_back(Form("%i<E_{q}<%i GeV",i,i+5));
    }
  }
  else{
    for(int i=120; i<250; i+=30){
      E_cut.push_back(Form("&& genpart_e[recoPFJet30_i_closest_genpart]>%i && genpart_e[recoPFJet30_i_closest_genpart]<%i",i,i+10));
      leg_entry.push_back(Form("%i<E_{q}<%i GeV",i,i+10));
    }
  }
 

  vector<TH1F*> h;

  for(int i=0;i<E_cut.size();i++){
    h.push_back(single_plot(file_TTJets,"HTauTauTree",var,cut+E_cut[i],90,0,360));
  }

  		

  TLegend* leg=new TLegend(0.4,0.5,0.85,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->SetHeader("#splitline{p_{T}(reco)>30 GeV, 1.5<|#eta(reco)|<3}{No 2nd parton veto}");

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
  //h[0]->SetMaximum(1.2*h[0]->GetMaximum());
  h[0]->SetMaximum(0.28);
  h[0]->GetXaxis()->SetTitle("E_{reco} [GeV]");
  h[0]->GetXaxis()->SetTitleOffset(1.1);
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f GeV",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("b-jet energy resolution tt+jets sample");


  h[0]->Draw();
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");

  vector<TF1*> fit;
  for(int i=0;i<E_cut.size();i++){
    //TF1* f=new TF1("f","gaus*(x>30)",0,360);
    TF1* f=new TF1("f","4*(1/([1]*sqrt(2*pi))) * exp(-0.5*((x-[0])/[1])**2)",30*cosh(1.5),360);
    fit.push_back(f);
    //fit[i]->SetParameter(0,h[i]->GetMaximum());
    fit[i]->SetParameter(0,h[i]->GetMean());
    fit[i]->SetParameter(1,h[i]->GetRMS());
    fit[i]->SetParLimits(0,0,500);

    //f->Draw("same");
    h[i]->Fit(fit[i],"R0");
    fit[i]->SetLineColor(h[i]->GetLineColor());
    fit[i]->SetLineStyle(7);
    fit[i]->Draw("same");
    //fit.push_back(f);
  }


  vector<TF1*> fit_double;
  for(int i=0;i<E_cut.size();i++){
    TF1* f=new TF1("f","4*([0] * (1/([2]*sqrt(2*pi))) * exp(-0.5*((x-[1])/[2])**2) + (1-[0]) *  (1/([4]*sqrt(2*pi))) * exp(-0.5*((x-[3])/[4])**2))",30*cosh(1.5),360);
    fit_double.push_back(f);
    fit_double[i]->SetParameter(0,1);
    fit_double[i]->SetParameter(1,h[i]->GetMean());
    fit_double[i]->SetParameter(2,h[i]->GetRMS());
    fit_double[i]->SetParameter(3,h[i]->GetMean());
    fit_double[i]->SetParameter(4,h[i]->GetRMS());
    fit_double[i]->SetParLimits(0,0,1);
    fit_double[i]->FixParameter(0,0.60);

    fit_double[i]->SetParLimits(1,0,500);
    fit_double[i]->SetParLimits(2,0,500);
    fit_double[i]->SetParLimits(3,0,500);
    fit_double[i]->SetParLimits(4,0,500);

    h[i]->Fit(fit_double[i],"R0");
    fit_double[i]->SetLineColor(h[i]->GetLineColor());
    fit_double[i]->Draw("same");
    //fit.push_back(f);
  }


  TString filename="bjet_Ebin_endcap_nodRveto";
  if(low_E)
    filename+="_low_E";
  else
    filename+="_high_E";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}





void plot_deltaE_nodRveto(){

  TString file_TTJets="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_pfMET_prod_24072015/ntuple_TTJets_dRveto_gen.root";

  TString var="recoPFJet30_e-genpart_e[recoPFJet30_i_closest_genpart]";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && abs(genpart_pdg[recoPFJet30_i_closest_genpart])==5 && 1.5<abs(recoPFJet30_eta) && abs(recoPFJet30_eta)<3";    

 
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
  h->SetMaximum(0.08);
  h->GetXaxis()->SetTitle("E_{reco}-E_{gen} [GeV]");
  h->GetXaxis()->SetTitleOffset(1.1);
  h->GetYaxis()->SetTitle(Form("Fraction of events / %.2f GeV",binning(h)));
  h->GetYaxis()->SetTitleOffset(1.7);
  h->SetTitle("b-jet energy resolution tt+jets sample");

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

  leg->SetHeader(Form("#splitline{p_{T}(reco)>30 GeV, 1.5<|#eta(reco)|<3}{f(#DeltaE)=%.2fG_{1}+%.2fG_{2}}",f->GetParameter(0),1-f->GetParameter(0)));
  leg->Draw("same");


  TString filename="bjet_deltaE_endcap_nodRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}








void plot_mean_sigma_jetTF(){

  TString file_TTJets="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_pfMET_prod_24072015/ntuple_TTJets_dRveto_gen.root";

  TString var="recoPFJet30_e";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])==5) && abs(recoPFJet30_eta)>1.5 && abs(recoPFJet30_eta)<3";  

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
 

  vector<TH1F*> h_nodRveto;
  vector<TF1*> fit_nodRveto;
  TGraphErrors* frac_nodRveto=new TGraphErrors();
  TGraphErrors* mean1_nodRveto=new TGraphErrors();
  TGraphErrors* sigma1_nodRveto=new TGraphErrors();
  TGraphErrors* mean2_nodRveto=new TGraphErrors();
  TGraphErrors* sigma2_nodRveto=new TGraphErrors();

  for(int i=0;i<E_cut.size();i++){
    h_nodRveto.push_back(single_plot(file_TTJets,"HTauTauTree",var,cut+E_cut[i],90,0,360));
    h_nodRveto[i]->Sumw2();
    h_nodRveto[i]->Scale(1/h_nodRveto[i]->Integral());


    TF1* f=new TF1("f","4*([0] * (1/([2]*sqrt(2*pi))) * exp(-0.5*((x-[1])/[2])**2) + (1-[0]) *  (1/([4]*sqrt(2*pi))) * exp(-0.5*((x-[3])/[4])**2))",30*cosh(1.5),360);
    fit_nodRveto.push_back(f);
    fit_nodRveto[i]->SetParameter(0,1);
    fit_nodRveto[i]->SetParameter(1,h_nodRveto[i]->GetMean());
    fit_nodRveto[i]->SetParameter(2,h_nodRveto[i]->GetRMS());
    fit_nodRveto[i]->SetParameter(3,h_nodRveto[i]->GetMean());
    fit_nodRveto[i]->SetParameter(4,h_nodRveto[i]->GetRMS());
    fit_nodRveto[i]->SetParLimits(0,0,1);
    fit_nodRveto[i]->FixParameter(0,0.60);

    fit_nodRveto[i]->SetParLimits(1,0,500);
    fit_nodRveto[i]->SetParLimits(2,0,500);
    fit_nodRveto[i]->SetParLimits(3,0,500);
    fit_nodRveto[i]->SetParLimits(4,0,500);
    h_nodRveto[i]->Fit(fit_nodRveto[i],"R0");
   
    if(fit_nodRveto[i]->GetParameter(0)>0.5){
      frac_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(0));
      frac_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(0));    
      mean1_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(1));
      mean1_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(1));
      sigma1_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(2));
      sigma1_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(2));
      mean2_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(3));
      mean2_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(3));
      sigma2_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(4));
      sigma2_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(4));
    }
    else{
      frac_nodRveto->SetPoint(i,bin_mean[i],1-fit_nodRveto[i]->GetParameter(0));
      frac_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(0));    
      mean2_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(1));
      mean2_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(1));
      sigma2_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(2));
      sigma2_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(2));
      mean1_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(3));
      mean1_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(3));
      sigma1_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(4));
      sigma1_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(4));
    }


  }

  frac_nodRveto->SetMarkerStyle(20);

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
  frac_nodRveto->SetTitle("b-jet TF relat. normalization");
  frac_nodRveto->Draw("AP");

  TString filename0="frac_bjetTF_endcap";
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
  mean1_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitle("#mu [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  mean1_nodRveto->SetTitle("b-jet TF means");

  mean1_nodRveto->Draw("AP");
  mean2_nodRveto->Draw("Psame");  
  leg->Draw("same");


  TString filename="mean_bjetTF_endcap";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  TCanvas* c2=new TCanvas("c2","c2",650,600);
  c2->SetLeftMargin(0.15);

  sigma1_nodRveto->GetYaxis()->SetRangeUser(0,200);
  sigma1_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
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
 

  TString filename2="sigma_bjetTF_endcap";
  c2->SaveAs("../plots/pdf/"+filename2+".pdf");
  c2->SaveAs("../plots/png/"+filename2+".png");


  TFile* f_new = TFile::Open("bjetTF_endcap_TTjets.root","RECREATE");
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

  TFile* f = TFile::Open("bjetTF_endcap_TTjets.root");
  TGraphErrors* mean1_nodRveto = (TGraphErrors*)f->Get("mean1_nodRveto");
  TGraphErrors* mean2_nodRveto = (TGraphErrors*)f->Get("mean2_nodRveto");
  
  /*TF1* old_TF_mean1=new TF1("mean_old1", "[0]+[1]*x",0,350);
  old_TF_mean1->FixParameter(0,-7.0);
  old_TF_mean1->FixParameter(1,1.0);
  TF1* old_TF_mean2=new TF1("mean_old2", "[0]+[1]*x",0,350);
  old_TF_mean2->FixParameter(0,9.8);
  old_TF_mean2->FixParameter(1,0.85);
  old_TF_mean2->SetLineColor(4);*/


  TF1* new_TF_mean1=new TF1("mean_new1", "[0]+[1]*x",140,250);
  new_TF_mean1->SetParameter(0,-7.0);
  new_TF_mean1->SetParameter(1,1.0);
  mean1_nodRveto->Fit(new_TF_mean1,"R0");
  new_TF_mean1->SetLineColor(2);

  TF1* new_TF_mean2=new TF1("mean_new2", "[0]+[1]*x",140,250);
  new_TF_mean2->SetParameter(0,9.8);
  new_TF_mean2->SetParameter(1,0.85);
  mean2_nodRveto->Fit(new_TF_mean2,"R0");
  new_TF_mean2->SetLineColor(3);

  TLegend* leg=new TLegend(0.3,0.55,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(mean1_nodRveto,"#mu_{1}");
  leg->AddEntry(mean2_nodRveto,"#mu_{2}");
  //leg->AddEntry(old_TF_mean1,"Old TF #mu_{1}");
  leg->AddEntry(new_TF_mean1,"New TF #mu_{1}");
  //leg->AddEntry(old_TF_mean2,"Old TF #mu_{2}");
  leg->AddEntry(new_TF_mean2,"New TF #mu_{2}");
  leg->SetHeader("p_{T}(reco)>30 GeV, 1.5<|#eta(reco)|<3");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  mean1_nodRveto->GetYaxis()->SetRangeUser(0,350);
  mean1_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitle("#mu [GeV]");
  mean1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  mean1_nodRveto->SetTitle("b-jet TF mean");

  mean1_nodRveto->Draw("AP");
  mean2_nodRveto->Draw("Psame");  
  //old_TF_mean1->Draw("SAME");
  //old_TF_mean2->Draw("SAME");
  new_TF_mean1->Draw("SAME");
  new_TF_mean2->Draw("SAME");

  leg->Draw("same");

  TString filename="mean_bjetTF_endcap_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}





void plot_sigma_fit(){

  TFile* f = TFile::Open("bjetTF_endcap_TTjets.root");
  TGraphErrors* sigma1_nodRveto = (TGraphErrors*)f->Get("sigma1_nodRveto");
  TGraphErrors* sigma2_nodRveto = (TGraphErrors*)f->Get("sigma2_nodRveto");
  
  /*TF1* old_TF_sigma1=new TF1("sigma_old1", "TMath::Sqrt(([0]**2+([1]*TMath::Sqrt(x))**2)+([2]*x)**2)",0,350);
  old_TF_sigma1->FixParameter(0,0);
  old_TF_sigma1->FixParameter(1,1.7);
  old_TF_sigma1->FixParameter(2,0);
  TF1* old_TF_sigma2=new TF1("sigma_old2", "TMath::Sqrt(([0]**2+([1]*TMath::Sqrt(x))**2)+([2]*x)**2)",0,350);
  old_TF_sigma2->FixParameter(0,0);
  old_TF_sigma2->FixParameter(1,0.28);
  old_TF_sigma2->FixParameter(2,0.25);
  old_TF_sigma2->SetLineColor(4);*/


  TF1* new_TF_sigma1=new TF1("sigma_new1", "TMath::Sqrt(([0]**2+([1]*TMath::Sqrt(x))**2)+([2]*x)**2)",140,250);
  new_TF_sigma1->SetParameter(0,0);
  new_TF_sigma1->SetParameter(1,1.7);
  new_TF_sigma1->SetParameter(2,0);
  sigma1_nodRveto->Fit(new_TF_sigma1,"R0");
  new_TF_sigma1->SetLineColor(2);

  TF1* new_TF_sigma2=new TF1("sigma_new2", "TMath::Sqrt(([0]**2+([1]*TMath::Sqrt(x))**2)+([2]*x)**2)",140,250);
  new_TF_sigma2->SetParameter(0,0);
  new_TF_sigma2->SetParameter(1,0.28);
  new_TF_sigma2->SetParameter(2,0.25);
  sigma2_nodRveto->Fit(new_TF_sigma2,"R0");
  new_TF_sigma2->SetLineColor(3);

  TLegend* leg=new TLegend(0.5,0.5,0.8,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(sigma1_nodRveto,"#sigma_{1}");
  leg->AddEntry(sigma2_nodRveto,"#sigma_{2}");
  //leg->AddEntry(old_TF_sigma1,"Old TF #sigma_{1}");
  leg->AddEntry(new_TF_sigma1,"New TF #sigma_{1}");
  //leg->AddEntry(old_TF_sigma2,"Old TF #sigma_{2}");
  leg->AddEntry(new_TF_sigma2,"New TF #sigma_{2}");
  leg->SetHeader("#splitline{p_{T}(reco)>30 GeV,}{1.5<|#eta(reco)|<3}");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  sigma1_nodRveto->GetYaxis()->SetRangeUser(0,100);
  sigma1_nodRveto->GetXaxis()->SetTitle("E_{q} [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma1_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  sigma1_nodRveto->SetTitle("b-jet TF width");

  sigma1_nodRveto->Draw("AP");
  sigma2_nodRveto->Draw("Psame");  
  //old_TF_sigma1->Draw("SAME");
  //old_TF_sigma2->Draw("SAME");
  new_TF_sigma1->Draw("SAME");
  new_TF_sigma2->Draw("SAME");

  leg->Draw("same");

  TString filename="sigma_bjetTF_endcap_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}
