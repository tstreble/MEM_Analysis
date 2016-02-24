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




void plot_mean_sigma_jetTF(){

  TString file_TTJets="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_pfMET_prod_24072015/ntuple_TTJets_dRveto_gen.root";

  TString var="recoPFJet30_pt";
  TString cut="recoPFJet30_dR_closest_genpart<0.4 && (abs(genpart_pdg[recoPFJet30_i_closest_genpart])<5) && abs(recoPFJet30_eta)>1.5  && abs(recoPFJet30_eta)<3 && genpart_pt[recoPFJet30_i_closest_genpart]>20";  

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
 

  vector<TH1F*> h_nodRveto;
  vector<TF1*> fit_nodRveto;
  vector<TH1F*> h_dRveto;
  vector<TF1*> fit_dRveto;

  TGraphErrors* mean_nodRveto=new TGraphErrors();
  TGraphErrors* sigma_nodRveto=new TGraphErrors();
  TGraphErrors* mean_dRveto=new TGraphErrors();
  TGraphErrors* sigma_dRveto=new TGraphErrors();

  for(unsigned int i=0;i<pT_cut.size();i++){
    h_nodRveto.push_back(single_plot(file_TTJets,"HTauTauTree",var,cut+pT_cut[i],90,0,360));
    h_dRveto.push_back(single_plot(file_TTJets,"HTauTauTree",var,cut+pT_cut[i]+" && recoPFJet30_dR_2nd_closest_genpart>0.4",90,0,360));

    
    h_nodRveto[i]->Sumw2();
    h_nodRveto[i]->Scale(1/h_nodRveto[i]->Integral());
    h_dRveto[i]->Sumw2();
    h_dRveto[i]->Scale(1/h_dRveto[i]->Integral());

    TF1* f=new TF1("f","4/([1]*sqrt(2*pi))*exp(-0.5*((x-[0])/[1])**2)",30,360);
    fit_dRveto.push_back(f);
    fit_dRveto[i]->SetParameter(0,h_dRveto[i]->GetMean());
    fit_dRveto[i]->SetParLimits(0,0,500);
    fit_dRveto[i]->SetParameter(1,h_dRveto[i]->GetRMS());
    h_dRveto[i]->Fit(fit_dRveto[i],"R0");

    mean_dRveto->SetPoint(i,bin_mean[i],fit_dRveto[i]->GetParameter(0));
    mean_dRveto->SetPointError(i,bin_width[i],fit_dRveto[i]->GetParError(0));
    sigma_dRveto->SetPoint(i,bin_mean[i],fit_dRveto[i]->GetParameter(1));
    sigma_dRveto->SetPointError(i,bin_width[i],fit_dRveto[i]->GetParError(1));


    TF1* f2=new TF1("f2","4/([1]*sqrt(2*pi))*exp(-0.5*((x-[0])/[1])**2)",30,360);
    fit_nodRveto.push_back(f2);
    fit_nodRveto[i]->SetParameter(0,h_nodRveto[i]->GetMean());
    fit_nodRveto[i]->SetParLimits(0,0,500);
    fit_nodRveto[i]->SetParameter(1,h_nodRveto[i]->GetRMS());
    h_nodRveto[i]->Fit(fit_nodRveto[i],"R0");

    mean_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(0));
    mean_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(0));
    sigma_nodRveto->SetPoint(i,bin_mean[i],fit_nodRveto[i]->GetParameter(1));
    sigma_nodRveto->SetPointError(i,bin_width[i],fit_nodRveto[i]->GetParError(1));

  }

  mean_dRveto->SetMarkerStyle(20);
  mean_dRveto->SetFillColor(0);
  sigma_dRveto->SetMarkerStyle(20);
  sigma_dRveto->SetFillColor(0);

  mean_nodRveto->SetMarkerStyle(21);
  mean_nodRveto->SetFillColor(0);
  sigma_nodRveto->SetMarkerStyle(21);
  sigma_nodRveto->SetFillColor(0);

  TLegend* leg=new TLegend(0.3,0.6,0.5,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(mean_dRveto,"2nd parton veto");
  leg->AddEntry(mean_nodRveto,"No veto");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  mean_nodRveto->GetYaxis()->SetRangeUser(0,350);
  mean_nodRveto->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  mean_nodRveto->GetYaxis()->SetTitle("#mu [GeV]");
  mean_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  mean_nodRveto->SetTitle("Light jet TF mean");

  mean_nodRveto->Draw("AP");
  mean_dRveto->Draw("Psame");  
  leg->Draw("same");

  TString filename="mean_jetTF_pT_endcap";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  TCanvas* c2=new TCanvas("c2","c2",650,600);
  c2->SetLeftMargin(0.15);

  sigma_nodRveto->GetYaxis()->SetRangeUser(0,200);
  sigma_nodRveto->GetXaxis()->SetTitle("p_{T}(gen) [GeV]");
  sigma_nodRveto->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  sigma_nodRveto->SetTitle("Light jet TF width");

  TLegend* leg2=new TLegend(0.3,0.6,0.5,0.8);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.035);
  leg2->SetFillColor(0);
  leg2->AddEntry(sigma_dRveto,"2nd parton veto");
  leg2->AddEntry(sigma_nodRveto,"No veto");

  sigma_nodRveto->Draw("AP");
  sigma_dRveto->Draw("Psame");  
  leg2->Draw("same");
 

  TString filename2="sigma_jetTF_pT_endcap";
  c2->SaveAs("../plots/pdf/"+filename2+".pdf");
  c2->SaveAs("../plots/png/"+filename2+".png");


  TFile* f_new = TFile::Open("jetTF_pT_endcap_TTjets.root","RECREATE");
  mean_nodRveto->SetName("mean_nodRveto");
  mean_nodRveto->Write();
  sigma_nodRveto->SetName("sigma_nodRveto");
  sigma_nodRveto->Write();
  f_new->Close();

  return;

}





void plot_mean_fit(){

  TFile* f = TFile::Open("jetTF_pT_endcap_TTjets.root");
  TGraphErrors* mean_nodRveto = (TGraphErrors*)f->Get("mean_nodRveto");

  TF1* new_TF_mean=new TF1("mean_new", "[0]+[1]*x",30,250);
  new_TF_mean->SetParameter(0,2.325);
  new_TF_mean->SetParameter(1,1.014);
  mean_nodRveto->Fit(new_TF_mean,"R0");
  new_TF_mean->SetLineColor(3);

  TLegend* leg=new TLegend(0.3,0.6,0.5,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  //leg->AddEntry(mean_dRveto,"2nd parton veto");
  leg->AddEntry(mean_nodRveto,"Fitted mean");
  leg->AddEntry(new_TF_mean,Form("New TF #mu: %.2f + %.2f p_{T}",new_TF_mean->GetParameter(0),new_TF_mean->GetParameter(1)));
  leg->SetHeader("p_{T}(reco)>30 GeV, 1.5<|#eta(reco)|<3");


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  mean_nodRveto->GetYaxis()->SetRangeUser(0,350);
  mean_nodRveto->GetXaxis()->SetTitle("p_{T} [GeV]");
  mean_nodRveto->GetYaxis()->SetTitle("#mu [GeV]");
  mean_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  mean_nodRveto->SetTitle("Light jet TF mean");

  mean_nodRveto->Draw("AP");  
  new_TF_mean->Draw("SAME");
  leg->Draw("same");

  TString filename="mean_jetTF_endcap_pT_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}





void plot_sigma_fit(){

  TFile* f = TFile::Open("jetTF_pT_endcap_TTjets.root");
  TGraphErrors* sigma_nodRveto = (TGraphErrors*)f->Get("sigma_nodRveto");

  TF1* new_form_TF_sigma=new TF1("res_new_form", "TMath::Sqrt(([0]**2+([1]*TMath::Sqrt(x))**2)+([2]*x)**2)",30,250);
  new_form_TF_sigma->SetParameter(0,0);
  new_form_TF_sigma->SetParameter(1,1.52);
  new_form_TF_sigma->SetParameter(2,0.026); 
  sigma_nodRveto->Fit(new_form_TF_sigma,"R0");
  new_form_TF_sigma->SetLineColor(3);

  TLegend* leg=new TLegend(0.3,0.6,0.5,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(sigma_nodRveto,"Fitted width");
  leg->AddEntry(new_form_TF_sigma,Form("New TF #sigma: %.2f #oplus %.2f #sqrt{p_{T}} #oplus %.2f p_{T}",new_form_TF_sigma->GetParameter(0),new_form_TF_sigma->GetParameter(1),new_form_TF_sigma->GetParameter(2)));
  leg->SetHeader("p_{T}(reco)>30 GeV, 1.5<|#eta(reco)|<3");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  sigma_nodRveto->GetYaxis()->SetRangeUser(0,100);
  sigma_nodRveto->GetXaxis()->SetTitle("p_{T} [GeV]");
  sigma_nodRveto->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma_nodRveto->GetYaxis()->SetTitleOffset(1.6);
  sigma_nodRveto->SetTitle("Light jet TF width");

  sigma_nodRveto->Draw("AP");  
  new_form_TF_sigma->Draw("SAME");
  leg->Draw("same");

  TString filename="sigma_jetTF_endcap_pT_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}
