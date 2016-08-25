#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include "Helpers.C"
#include <vector>
#include <TLatex.h>
#include <THStack.h>
#include <TGraphErrors.h>
#include <TF1.h>

using namespace std;





void plot_lepfake_pt_genb_bin(){

  TString file_ttbar="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;

  TLegend* leg=new TLegend(0.4,0.5,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
 
  int i=0;
  for(unsigned int j=30;j<150;j+=20){

    h.push_back(single_plot(file_ttbar,"HTauTauTree","recolep_pt[genb_i_closest_recolep]",Form("genb_dR_closest_recolep<0.2 && recolep_leptonMVA[genb_i_closest_recolep]<0.75 && genb_pt>%i && genb_pt<%i",j,j+10),15,0,150));
    h[i]->SetLineWidth(2);
    h[i]->SetLineColor(i+1);
    if(i>3)
      h[i]->SetLineColor(i+2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());

    TF1* f=new TF1("f","gaus",20,200);
    f->SetLineColor(h[i]->GetLineColor());

    h[i]->Fit(f);

    leg->AddEntry(h[i],Form("%i<p_{T}(b)<%i GeV",j,j+10));
    i++;

  }
  
  
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
      
  h=sort_histo(h);

  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("p_{T}(reco. lep.)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="lepfake_pt_genb_bin";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}







void plot_mean_sigma_fakelepTF(){

  TString file_ttbar="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  TString var="recolep_pt[genb_i_closest_recolep]";
  TString cut="genb_dR_closest_recolep<0.2 && recolep_leptonMVA[genb_i_closest_recolep]<0.75";  

  vector<TString> pT_cut;
  vector<float> bin_mean;
  vector<float> bin_width;

  for(int i=30; i<250; i+=10){
    pT_cut.push_back(Form("&& genb_pt>%i && genb_pt<%i",i,i+10));   
    bin_mean.push_back(i+5);
    bin_width.push_back(5);
  }
 

  TGraphErrors* mean=new TGraphErrors();
  TGraphErrors* sigma=new TGraphErrors();
  /*TGraphErrors* mean_ele_E=new TGraphErrors();
  TGraphErrors* sigma_ele_E=new TGraphErrors();
  TGraphErrors* mean_mu_B=new TGraphErrors();
  TGraphErrors* sigma_mu_B=new TGraphErrors();
  TGraphErrors* mean_mu_E=new TGraphErrors();
  TGraphErrors* sigma_mu_E=new TGraphErrors();*/


  for(int i=0;i<pT_cut.size();i++){
    TH1F* h = single_plot(file_ttbar,"HTauTauTree",var,cut+pT_cut[i],15,0,150);
    h->Sumw2();
    h->Scale(1/h->Integral());
  
    TF1* f=new TF1("f","gaus",20,150);
    f->SetParameter(1,h->GetMean());
    f->SetParameter(2,h->GetRMS());

    h->Fit(f,"R0");

    mean->SetPoint(i,bin_mean[i],f->GetParameter(1));
    mean->SetPointError(i,bin_width[i],f->GetParError(1));
    sigma->SetPoint(i,bin_mean[i],f->GetParameter(2));
    sigma->SetPointError(i,bin_width[i],f->GetParError(2));


  }

  /*for(int i=0;i<pT_cut.size();i++){
    TH1F* h_ele_E = single_plot(file_ttbar,"HTauTauTree",var,cut+pT_cut[i]+" && abs(recolep_pdg[genb_i_closest_recolep])==11 && abs(recolep_eta[genb_i_closest_recolep])>1.5",15,0,150);    
    h_ele_E->Sumw2();
    h_ele_E->Scale(1/h_ele_E->Integral());
  
    TF1* f=new TF1("f","gaus",20,150);
    f->SetParameter(1,h_ele_E->GetMean());
    f->SetParameter(2,h_ele_E->GetRMS());

    h_ele_E->Fit(f,"R0");

    mean_ele_E->SetPoint(i,bin_mean[i],f->GetParameter(1));
    mean_ele_E->SetPointError(i,bin_width[i],f->GetParError(1));
    sigma_ele_E->SetPoint(i,bin_mean[i],f->GetParameter(2));
    sigma_ele_E->SetPointError(i,bin_width[i],f->GetParError(2));


  }


  for(int i=0;i<pT_cut.size();i++){
    TH1F* h_mu_B = single_plot(file_ttbar,"HTauTauTree",var,cut+pT_cut[i]+" && abs(recolep_pdg[genb_i_closest_recolep])==13 && abs(recolep_eta[genb_i_closest_recolep])<1.5",15,0,150);    
    h_mu_B->Sumw2();
    h_mu_B->Scale(1/h_mu_B->Integral());
  
    TF1* f=new TF1("f","gaus",20,150);
    f->SetParameter(1,h_mu_B->GetMean());
    f->SetParameter(2,h_mu_B->GetRMS());

    h_mu_B->Fit(f,"R0");

    mean_mu_B->SetPoint(i,bin_mean[i],f->GetParameter(1));
    mean_mu_B->SetPointError(i,bin_width[i],f->GetParError(1));
    sigma_mu_B->SetPoint(i,bin_mean[i],f->GetParameter(2));
    sigma_mu_B->SetPointError(i,bin_width[i],f->GetParError(2));


  }

  for(int i=0;i<pT_cut.size();i++){
    TH1F* h_mu_E = single_plot(file_ttbar,"HTauTauTree",var,cut+pT_cut[i]+" && abs(recolep_pdg[genb_i_closest_recolep])==13 && abs(recolep_eta[genb_i_closest_recolep])>1.5",15,0,150);    
    h_mu_E->Sumw2();
    h_mu_E->Scale(1/h_mu_E->Integral());
  
    TF1* f=new TF1("f","gaus",20,150);
    f->SetParameter(1,h_mu_E->GetMean());
    f->SetParameter(2,h_mu_E->GetRMS());

    h_mu_E->Fit(f,"R0");

    mean_mu_E->SetPoint(i,bin_mean[i],f->GetParameter(1));
    mean_mu_E->SetPointError(i,bin_width[i],f->GetParError(1));
    sigma_mu_E->SetPoint(i,bin_mean[i],f->GetParameter(2));
    sigma_mu_E->SetPointError(i,bin_width[i],f->GetParError(2));


    }*/


  mean->SetMarkerStyle(20);
  //mean->SetMarkerColor(2);
  mean->SetFillColor(0);
  sigma->SetMarkerStyle(20);
  //sigma->SetMarkerColor(2);
  sigma->SetFillColor(0);  

  /*mean_ele_E->SetMarkerStyle(21);
  mean_ele_E->SetMarkerColor(2);
  mean_ele_E->SetFillColor(0);
  sigma_ele_E->SetMarkerStyle(21);
  sigma_ele_E->SetMarkerColor(2);
  sigma_ele_E->SetFillColor(0);  

  mean_mu_B->SetMarkerStyle(20);
  mean_mu_B->SetMarkerColor(3);
  mean_mu_B->SetFillColor(0);
  sigma_mu_B->SetMarkerStyle(20);
  sigma_mu_B->SetMarkerColor(3);
  sigma_mu_B->SetFillColor(0);  

  mean_mu_E->SetMarkerStyle(21);
  mean_mu_E->SetMarkerColor(3);
  mean_mu_E->SetFillColor(0);
  sigma_ele_E->SetMarkerStyle(21);
  sigma_ele_E->SetMarkerColor(3);
  sigma_ele_E->SetFillColor(0); */ 


  /*TLegend* leg=new TLegend(0.3,0.6,0.5,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(mean_ele_B,"Electron barrel");
  leg->AddEntry(mean_ele_E,"Electron endcaps");
  leg->AddEntry(mean_mu_B,"Muon barrel");
  leg->AddEntry(mean_mu_E,"Muon endcaps");*/

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  mean->GetYaxis()->SetRangeUser(0,350);
  mean->GetXaxis()->SetTitle("p_{T}(b) [GeV]");
  mean->GetYaxis()->SetTitle("#mu [GeV]");
  mean->GetYaxis()->SetTitleOffset(1.6);
  mean->SetTitle("Fake lep TF mean");

  mean->Draw("AP");
  /*mean_ele_E->Draw("Psame");
  mean_mu_B->Draw("Psame");
  mean_mu_E->Draw("Psame");
  leg->Draw("same");*/


  TString filename="mean_fakelepTF_pT";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  TCanvas* c2=new TCanvas("c2","c2",650,600);
  c2->SetLeftMargin(0.15);

  sigma->GetYaxis()->SetRangeUser(0,200);
  sigma->GetXaxis()->SetTitle("p_{T}(b) [GeV]");
  sigma->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma->GetYaxis()->SetTitleOffset(1.6);
  sigma->SetTitle("Fake lep TF width");

  /*TLegend* leg2=new TLegend(0.3,0.6,0.5,0.8);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.035);
  leg2->SetFillColor(0);
  leg2->AddEntry(sigma_ele_B,"Electron barrel");*/

  sigma->Draw("AP");
  /*sigma_ele_E->Draw("Psame");
  sigma_mu_B->Draw("Psame");
  sigma_mu_E->Draw("Psame");
  leg2->Draw("same");*/
 
  TString filename2="sigma_fakelepTF_pT";
  c2->SaveAs("../plots/pdf/"+filename2+".pdf");
  c2->SaveAs("../plots/png/"+filename2+".png");


  TFile* f_new = TFile::Open("fakelepTF_pT_ttbar_DL.root","RECREATE");
  mean->SetName("mean");
  mean->Write();
  sigma->SetName("sigma");
  sigma->Write();
  /*mean_ele_E->SetName("mean_ele_E");
  mean_ele_E->Write();
  sigma_ele_E->SetName("sigma_ele_E");
  sigma_ele_E->Write();
  mean_mu_B->SetName("mean_mu_B");
  mean_mu_B->Write();
  sigma_mu_B->SetName("sigma_mu_B");
  sigma_mu_B->Write();
  mean_mu_E->SetName("mean_mu_E");
  mean_mu_E->Write();
  sigma_mu_E->SetName("sigma_mu_E");
  sigma_mu_E->Write();*/
  f_new->Close();

  return;



}










void plot_mean_fit(){

  TFile* f = TFile::Open("fakelepTF_pT_ttbar_DL.root");
  TGraphErrors* mean = (TGraphErrors*)f->Get("mean");


  TF1* TF_mean=new TF1("mean", "[0]+[1]*x",50,190);
  TF_mean->SetParameter(0,-7.0);
  TF_mean->SetParameter(1,1.0);
  mean->Fit(TF_mean,"R0");
  TF_mean->SetLineColor(2);

  TLegend* leg=new TLegend(0.2,0.55,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(mean,"#mu");
  leg->AddEntry(TF_mean,Form("TF #mu: %.2f + %.2f p_{T}",TF_mean->GetParameter(0),TF_mean->GetParameter(1)));



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  mean->GetYaxis()->SetRangeUser(0,350);
  mean->GetXaxis()->SetTitle("E_{b} [GeV]");
  mean->GetYaxis()->SetTitle("#mu [GeV]");
  mean->GetYaxis()->SetTitleOffset(1.6);
  mean->SetTitle("Fake lepton TF mean");

  mean->Draw("AP");
  TF_mean->Draw("SAME");

  leg->Draw("same");

  TString filename="mean_fakelepTF_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}





void plot_sigma_fit(){

  TFile* f = TFile::Open("fakelepTF_pT_ttbar_DL.root");
  TGraphErrors* sigma = (TGraphErrors*)f->Get("sigma");  

  TF1* TF_sigma=new TF1("sigma", "TMath::Sqrt(([0]**2+([1]*TMath::Sqrt(x))**2)+([2]*x)**2)",50,190);
  TF_sigma->SetParameter(0,0);
  TF_sigma->SetParameter(1,0);
  TF_sigma->SetParameter(2,0.1);
  sigma->Fit(TF_sigma,"R0");
  TF_sigma->SetLineColor(2);


  TLegend* leg=new TLegend(0.25,0.6,0.5,0.8);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(sigma,"#sigma");
  leg->AddEntry(TF_sigma,Form("TF #sigma: %.2f #oplus %.2f #sqrt{p_{T}} #oplus %.2f p_{T}",TF_sigma->GetParameter(0),TF_sigma->GetParameter(1),TF_sigma->GetParameter(2)));
  //leg->AddEntry(TF_sigma,"TF #sigma");
 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  sigma->GetYaxis()->SetRangeUser(0,100);
  sigma->GetXaxis()->SetTitle("E_{b} [GeV]");
  sigma->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma->GetYaxis()->SetTitleOffset(1.6);
  sigma->SetTitle("Fake lepton TF width");

  sigma->Draw("AP");
  //old_TF_sigma1->Draw("SAME");
  //old_TF_sigma2->Draw("SAME");
  TF_sigma->Draw("SAME");

  leg->Draw("same");

  TString filename="sigma_fakelepTF_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}
