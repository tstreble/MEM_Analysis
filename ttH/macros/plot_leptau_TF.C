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



double CrystalBall(double* x, double* par){ //http://en.wikipedia.org/wiki/Crystal_Ball_function
  double xcur = x[0];
  double alpha = par[0];
  double n = par[1];
  double mu = par[2];
  double sigma = par[3];
  double N = par[4];
  TF1* exp = new TF1("exp","exp(x)",-1e20,1e20); 
  double A; double B;
  if (alpha < 0){
    A = pow((n/(-1*alpha)),n)*exp->Eval((-1)*alpha*alpha/2);
    B = n/(-1*alpha) + alpha;
  }
  else {
    A = pow((n/alpha),n)*exp->Eval((-1)*alpha*alpha/2);
    B = n/alpha - alpha;
  }

  double f;
  if ((xcur-mu)/sigma < alpha)
    f = N*exp->Eval((-1)*(xcur-mu)*(xcur-mu)/ (2*sigma*sigma));
  else
    f = N*A*pow((B + (xcur-mu)/sigma),(-1*n));
  delete exp;

  return f;
}



double BreitWigner(double* x, double* par){

  double xcur = x[0];
  double I = par[0];
  double mu = par[1];
  double sigma = par[2];


  double f = I/(1+pow((xcur-mu)/sigma,2));

  return f;

}




void plot_leptau_pt_genele_bin(){

  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;

  TLegend* leg=new TLegend(0.4,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
 
  int i=0;
  for(unsigned int j=30;j<100;j+=20){

    

    h.push_back(single_plot(file_ttZ,"HTauTauTree","recotauh_pt",Form("recotauh_dR_closest_genpart<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart])==11 && genpart_pt[recotauh_i_closest_genpart]>%i && genpart_pt[recotauh_i_closest_genpart]<%i",j,j+10),15,0,150));
    h[i]->SetLineWidth(2);
    h[i]->SetLineColor(i+1);
    if(i>3)
      h[i]->SetLineColor(i+2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());

    /*TF1* f=new TF1("f","gaus",-100,100);
    f->SetLineColor(h[i]->GetLineColor());

    h[i]->Fit(f);*/

    TF1* BW = new TF1("BW",BreitWigner,0,150,3);
    BW->SetParameters(h[i]->GetMaximum(),h[i]->GetMean(),h[i]->GetRMS());
    BW->SetLineColor(h[i]->GetLineColor());
    h[i]->Fit(BW);

    leg->AddEntry(h[i],Form("%i<p_{T}(e)<%i GeV",j,j+10));
    i++;

  }
  

  
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
      
  h=sort_histo(h);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.5*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("p_{T}(reco. #tau_{h})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of reco. #tau_{h} / %.2f [GeV]",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TLatex *texl = new TLatex(1,1.01*h[0]->GetMaximum(),"CMS Preliminary, Simulation #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");



  TString filename="leptau_pt_genele_bin";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}






void plot_leptau_pt_genmu_bin(){

  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  vector<TH1F*> h;

  TLegend* leg=new TLegend(0.55,0.6,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);
 
  int i=0;
  for(unsigned int j=30;j<100;j+=20){    

    h.push_back(single_plot(file_ttZ,"HTauTauTree","recotauh_pt",Form("recotauh_dR_closest_genpart<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart])==13 && genpart_pt[recotauh_i_closest_genpart]>%i && genpart_pt[recotauh_i_closest_genpart]<%i",j,j+20),20,0,200));
    h[i]->SetLineWidth(2);
    h[i]->SetLineColor(i+1);
    if(i>3)
      h[i]->SetLineColor(i+2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());

    /*TF1* f=new TF1("f","gaus",-100,100);
    f->SetLineColor(h[i]->GetLineColor());

    h[i]->Fit(f);*/

    /*TF1* BW = new TF1("BW",BreitWigner,0,200,3);
    BW->SetParameters(h[i]->GetMaximum(),h[i]->GetMean(),h[i]->GetRMS());
    BW->SetLineColor(h[i]->GetLineColor());
    h[i]->Fit(BW);*/

    TF1* cryst = new TF1("cryst",CrystalBall,20,200,5);
    cryst->SetParameters(1,1,j,10,h[i]->Integral());
    cryst->SetParLimits(2,j-5,j+20);
    cryst->FixParameter(0,1.2);
    cryst->SetLineColor(h[i]->GetLineColor());
    h[i]->Fit(cryst,"R");

    leg->AddEntry(h[i],Form("%i<p_{T}(#mu)<%i GeV",j,j+20));
    i++;

  }
  

  
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
      
  h=sort_histo(h);

  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.5*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("p_{T}(reco. #tau_{h})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of reco. #tau_{h} / %.2f [GeV]",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TLatex *texl = new TLatex(1,1.01*h[0]->GetMaximum(),"CMS Preliminary, Simulation #sqrt{s}=13 TeV");
  texl->SetTextSize(0.03);
  texl->Draw("same");



  TString filename="leptau_pt_genmu_bin";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;


}





void plot_mean_sigma_eletauTF(){


  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  TString var="recotauh_pt";
  TString cut="recotauh_dR_closest_genpart<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart])==11";

  vector<TString> pT_cut;
  vector<float> bin_mean;
  vector<float> bin_width;


  for(int i=30; i<120; i+=10){
    pT_cut.push_back(Form("&& genpart_pt[recotauh_i_closest_genpart]>%i && genpart_pt[recotauh_i_closest_genpart]<%i",i,i+10));   
    bin_mean.push_back(i+5);
    bin_width.push_back(5);
  }


  TGraphErrors* mean=new TGraphErrors();
  TGraphErrors* sigma=new TGraphErrors();

  for(int i=0;i<pT_cut.size();i++){
    TH1F* h = single_plot(file_ttZ,"HTauTauTree",var,cut+pT_cut[i],20,0,200);
    h->Sumw2();
    h->Scale(1/h->Integral());
    
    TF1* f = new TF1("BW",BreitWigner,0,200,3);
    f->SetParameters(h->GetMaximum(),h->GetMean(),h->GetRMS());
    h->Fit(f);

    h->Fit(f,"R0");

    mean->SetPoint(i,bin_mean[i],f->GetParameter(1));
    mean->SetPointError(i,bin_width[i],f->GetParError(1));
    sigma->SetPoint(i,bin_mean[i],f->GetParameter(2));
    sigma->SetPointError(i,bin_width[i],f->GetParError(2));

  }

  mean->SetMarkerStyle(20);
  mean->SetFillColor(0);
  sigma->SetMarkerStyle(20);
  sigma->SetFillColor(0);  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  mean->GetYaxis()->SetRangeUser(0,150);
  mean->GetXaxis()->SetTitle("p_{T}(e) [GeV]");
  mean->GetYaxis()->SetTitle("#mu [GeV]");
  mean->GetYaxis()->SetTitleOffset(1.6);
  mean->SetTitle("e#rightarrow#tau_{h} TF mean");

  mean->Draw("AP");

  TString filename="mean_eletauTF_pT";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  TCanvas* c2=new TCanvas("c2","c2",650,600);
  c2->SetLeftMargin(0.15);

  sigma->GetYaxis()->SetRangeUser(0,40);
  sigma->GetXaxis()->SetTitle("p_{T}(e) [GeV]");
  sigma->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma->GetYaxis()->SetTitleOffset(1.6);
  sigma->SetTitle("e#rightarrow#tau_{h} TF width");

  sigma->Draw("AP");

 
  TString filename2="sigma_eletauTF_pT";
  c2->SaveAs("../plots/pdf/"+filename2+".pdf");
  c2->SaveAs("../plots/png/"+filename2+".png");


  TFile* f_new = TFile::Open("eletauTF_pT_ttZ.root","RECREATE");
  mean->SetName("mean");
  mean->Write();
  sigma->SetName("sigma");
  sigma->Write();
 
  f_new->Close();

  return;


}







void plot_mean_fit_ele(){

  TFile* f = TFile::Open("eletauTF_pT_ttZ.root");
  TGraphErrors* mean = (TGraphErrors*)f->Get("mean");


  TF1* TF_mean=new TF1("mean", "[0]+[1]*x",30,120);
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

  mean->GetYaxis()->SetRangeUser(0,150);
  mean->GetXaxis()->SetTitle("p_{T}(e) [GeV]");
  mean->GetYaxis()->SetTitle("#mu [GeV]");
  mean->GetYaxis()->SetTitleOffset(1.6);
  mean->SetTitle("e#rightarrow#tau_{h} TF mean");

  mean->Draw("AP");
  TF_mean->Draw("SAME");

  leg->Draw("same");

  TString filename="mean_eletauTF_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}





void plot_sigma_fit_ele(){

  TFile* f = TFile::Open("eletauTF_pT_ttZ.root");
  TGraphErrors* sigma = (TGraphErrors*)f->Get("sigma");


  TF1* TF_sigma=new TF1("sigma", "[0]+[1]*x",30,110);
  TF_sigma->SetParameter(0,-7.0);
  TF_sigma->SetParameter(1,1.0);
  sigma->Fit(TF_sigma,"R0");
  TF_sigma->SetLineColor(2);

  TLegend* leg=new TLegend(0.2,0.55,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(sigma,"#sigma");
  leg->AddEntry(TF_sigma,Form("TF #sigma: %.2f + %.2f p_{T}",TF_sigma->GetParameter(0),TF_sigma->GetParameter(1)));



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  sigma->GetYaxis()->SetRangeUser(0,40);
  sigma->GetXaxis()->SetTitle("p_{T}(e) [GeV]");
  sigma->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma->GetYaxis()->SetTitleOffset(1.6);
  sigma->SetTitle("e#rightarrow#tau_{h} TF width");

  sigma->Draw("AP");
  TF_sigma->Draw("SAME");

  leg->Draw("same");

  TString filename="sigma_eletauTF_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}








void plot_alpha_n_mean_sigma_mutauTF(){


  TString file_ttZ="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

  TString var="recotauh_pt";
  TString cut="recotauh_dR_closest_genpart<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart])==13";

  vector<TString> pT_cut;
  vector<float> bin_mean;
  vector<float> bin_width;


  for(int i=30; i<120; i+=20){
    pT_cut.push_back(Form("&& genpart_pt[recotauh_i_closest_genpart]>%i && genpart_pt[recotauh_i_closest_genpart]<%i",i,i+20));   
    bin_mean.push_back(i+10);
    bin_width.push_back(10);
  }


  TGraphErrors* alpha=new TGraphErrors();
  TGraphErrors* n=new TGraphErrors();
  TGraphErrors* mean=new TGraphErrors();
  TGraphErrors* sigma=new TGraphErrors();

  for(int i=0;i<pT_cut.size();i++){
    TH1F* h = single_plot(file_ttZ,"HTauTauTree",var,cut+pT_cut[i],20,0,200);
    h->Sumw2();
    h->Scale(1/h->Integral());

    TF1* f = new TF1("cryst",CrystalBall,20,200,5);
    f->SetParameters(1,1,20*i+30,10,h->Integral());
    f->SetParLimits(2,20*i+25,20*i+50);
    f->FixParameter(0,1.2);
    h->Fit(f,"R0");

    alpha->SetPoint(i,bin_mean[i],f->GetParameter(0));
    alpha->SetPointError(i,bin_width[i],f->GetParError(0));
    n->SetPoint(i,bin_mean[i],f->GetParameter(1));
    n->SetPointError(i,bin_width[i],f->GetParError(1));
    mean->SetPoint(i,bin_mean[i],f->GetParameter(2));
    mean->SetPointError(i,bin_width[i],f->GetParError(2));
    sigma->SetPoint(i,bin_mean[i],f->GetParameter(3));
    sigma->SetPointError(i,bin_width[i],f->GetParError(3));

  }


  alpha->SetMarkerStyle(20);
  alpha->SetFillColor(0);
  n->SetMarkerStyle(20);
  n->SetFillColor(0);  
  mean->SetMarkerStyle(20);
  mean->SetFillColor(0);
  sigma->SetMarkerStyle(20);
  sigma->SetFillColor(0);  

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  alpha->GetYaxis()->SetRangeUser(0,5);
  alpha->GetXaxis()->SetTitle("p_{T}(e) [GeV]");
  alpha->GetYaxis()->SetTitle("#alpha");
  alpha->GetYaxis()->SetTitleOffset(1.6);
  alpha->SetTitle("#mu#rightarrow#tau_{h} TF #alpha");

  alpha->Draw("AP");

  TString filename="alpha_mutauTF_pT";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  TCanvas* c2=new TCanvas("c2","c2",650,600);
  c2->SetLeftMargin(0.15);

  n->GetYaxis()->SetRangeUser(0,5);
  n->GetXaxis()->SetTitle("p_{T}(e) [GeV]");
  n->GetYaxis()->SetTitle("n");
  n->GetYaxis()->SetTitleOffset(1.6);
  n->SetTitle("#mu#rightarrow#tau_{h} TF n");

  n->Draw("AP");

  TString filename2="n_mutauTF_pT";
  c2->SaveAs("../plots/pdf/"+filename2+".pdf");
  c2->SaveAs("../plots/png/"+filename2+".png");

  TCanvas* c3=new TCanvas("c3","c3",650,600);
  c3->SetLeftMargin(0.15);

  mean->GetYaxis()->SetRangeUser(0,150);
  mean->GetXaxis()->SetTitle("p_{T}(e) [GeV]");
  mean->GetYaxis()->SetTitle("#mu [GeV]");
  mean->GetYaxis()->SetTitleOffset(1.6);
  mean->SetTitle("#mu#rightarrow#tau_{h} TF mean");

  mean->Draw("AP");

  TString filename3="mean_eletauTF_pT";
  c3->SaveAs("../plots/pdf/"+filename3+".pdf");
  c3->SaveAs("../plots/png/"+filename3+".png");

  TCanvas* c4=new TCanvas("c4","c4",650,600);
  c4->SetLeftMargin(0.15);

  sigma->GetYaxis()->SetRangeUser(0,40);
  sigma->GetXaxis()->SetTitle("p_{T}(e) [GeV]");
  sigma->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma->GetYaxis()->SetTitleOffset(1.6);
  sigma->SetTitle("#mu#rightarrow#tau_{h} TF width");

  sigma->Draw("AP");

 
  TString filename4="sigma_eletauTF_pT";
  c4->SaveAs("../plots/pdf/"+filename4+".pdf");
  c4->SaveAs("../plots/png/"+filename4+".png");


  TFile* f_new = TFile::Open("mutauTF_pT_ttZ.root","RECREATE");
  alpha->SetName("alpha");
  alpha->Write();
  n->SetName("n");
  n->Write();
  mean->SetName("mean");
  mean->Write();
  sigma->SetName("sigma");
  sigma->Write();
 
  f_new->Close();

  return;


}








void plot_mean_fit_mu(){

  TFile* f = TFile::Open("mutauTF_pT_ttZ.root");
  TGraphErrors* mean = (TGraphErrors*)f->Get("mean");


  TF1* TF_mean=new TF1("mean", "[0]+[1]*x",30,130);
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

  mean->GetYaxis()->SetRangeUser(0,150);
  mean->GetXaxis()->SetTitle("p_{T}(#mu) [GeV]");
  mean->GetYaxis()->SetTitle("#mu [GeV]");
  mean->GetYaxis()->SetTitleOffset(1.6);
  mean->SetTitle("#mu#rightarrow#tau_{h} TF mean");

  mean->Draw("AP");
  TF_mean->Draw("SAME");

  leg->Draw("same");

  TString filename="mean_mutauTF_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}





void plot_sigma_fit_mu(){

  TFile* f = TFile::Open("mutauTF_pT_ttZ.root");
  TGraphErrors* sigma = (TGraphErrors*)f->Get("sigma");


  TF1* TF_sigma=new TF1("sigma", "[0]+[1]*x",30,130);
  TF_sigma->SetParameter(0,-7.0);
  TF_sigma->SetParameter(1,1.0);
  sigma->Fit(TF_sigma,"R0");
  TF_sigma->SetLineColor(2);

  TLegend* leg=new TLegend(0.2,0.55,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(sigma,"#sigma");
  leg->AddEntry(TF_sigma,Form("TF #sigma: %.2f + %.2f p_{T}",TF_sigma->GetParameter(0),TF_sigma->GetParameter(1)));



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  sigma->GetYaxis()->SetRangeUser(0,40);
  sigma->GetXaxis()->SetTitle("p_{T}(#mu) [GeV]");
  sigma->GetYaxis()->SetTitle("#sigma [GeV]");
  sigma->GetYaxis()->SetTitleOffset(1.6);
  sigma->SetTitle("#mu#rightarrow#tau_{h} TF width");

  sigma->Draw("AP");
  TF_sigma->Draw("SAME");

  leg->Draw("same");

  TString filename="sigma_mutauTF_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}







void plot_n_fit_mu(){

  TFile* f = TFile::Open("mutauTF_pT_ttZ.root");
  TGraphErrors* n = (TGraphErrors*)f->Get("n");


  TF1* TF_n=new TF1("n", "[0]+[1]*x",30,130);
  TF_n->SetParameter(0,2);
  TF_n->SetParameter(1,-0.02);
  n->Fit(TF_n,"R0");
  TF_n->SetLineColor(2);

  TLegend* leg=new TLegend(0.2,0.55,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  leg->AddEntry(n,"n");
  leg->AddEntry(TF_n,Form("TF n: %.2f + %.4f p_{T}",TF_n->GetParameter(0),TF_n->GetParameter(1)));


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);

  n->GetYaxis()->SetRangeUser(0,5);
  n->GetXaxis()->SetTitle("p_{T}(#mu) [GeV]");
  n->GetYaxis()->SetTitle("n");
  n->GetYaxis()->SetTitleOffset(1.6);
  n->SetTitle("#mu#rightarrow#tau_{h} TF n");

  n->Draw("AP");  
  TF_n->Draw("SAME");

  leg->Draw("same");

  TString filename="n_mutauTF_fit";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");


  return;

}



