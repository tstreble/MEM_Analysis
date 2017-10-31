#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>
#include <THStack.h>
#include <TLatex.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
#include <iostream>
#include <TGaxis.h>
#include <TGraphAsymmErrors.h>




void plot_mu_comb(){

  double mu_1l2tau = -1.525;
  double mu_1l2tau_m1s = 1.723;
  double mu_1l2tau_p1s = 1.758;
  cout<<"Mu 1l2tau = "<<mu_1l2tau<<" +"<<mu_1l2tau_p1s<<"/-"<<mu_1l2tau_m1s<<endl;

  double mu_2lss = +1.613;  
  double mu_2lss_m1s = 0.512;
  double mu_2lss_p1s = 0.577;
  cout<<"Mu 2lss = "<<mu_2lss<<" +"<<mu_2lss_p1s<<"/-"<<mu_2lss_m1s<<endl;

  double mu_2lss1tau = +0.941;
  double mu_2lss1tau_m1s = 0.674;
  double mu_2lss1tau_p1s = 0.797;
  cout<<"Mu 2lss1tau = "<<mu_2lss1tau<<" +"<<mu_2lss1tau_p1s<<"/-"<<mu_2lss1tau_m1s<<endl;

  double mu_3l = +0.819;
  double mu_3l_m1s = 0.706;
  double mu_3l_p1s = 0.766;
  cout<<"Mu 3l = "<<mu_3l<<" +"<<mu_3l_p1s<<"/-"<<mu_3l_m1s<<endl;

  double mu_3l1tau = +1.340;
  double mu_3l1tau_m1s = 1.071;
  double mu_3l1tau_p1s = 1.423;
  cout<<"Mu 3l1tau = "<<mu_3l1tau<<" +"<<mu_3l1tau_p1s<<"/-"<<mu_3l1tau_m1s<<endl;

  double mu_4l = +0.567;
  double mu_4l_m1s = 1.568;
  double mu_4l_p1s = 2.289;
  cout<<"Mu 4l = "<<mu_4l<<" +"<<mu_4l_p1s<<"/-"<<mu_4l_m1s<<endl;

  double mu_comb = 1.226;
  double mu_comb_m1s = 0.430;
  double mu_comb_m1s_stat = 0.247;
  double mu_comb_p1s = 0.454;
  double mu_comb_p1s_stat = 0.257;
  cout<<"Mu comb = "<<mu_comb<<" +"<<mu_comb_p1s<<"/-"<<mu_comb_m1s<<endl;

  double y_1l2tau = 8.25;
  double y_2lss = 6.75;
  double y_2lss1tau = 5.25;
  double y_3l = 3.75;
  double y_3l1tau = 2.25;
  double y_4l = 0.75;
  double y_comb=4.5;


  TGraphAsymmErrors* gr_mu_1l2tau=new TGraphAsymmErrors();
  gr_mu_1l2tau->SetPoint(0,mu_1l2tau,y_1l2tau);
  gr_mu_1l2tau->SetPointError(0,mu_1l2tau_m1s,mu_1l2tau_p1s,0,0); 
  gr_mu_1l2tau->SetLineWidth(3);
  gr_mu_1l2tau->SetLineColor(kRed);
  gr_mu_1l2tau->SetMarkerStyle(21);
  gr_mu_1l2tau->SetMarkerSize(1.5);

  TGraphAsymmErrors* gr_mu_2lss=new TGraphAsymmErrors();
  gr_mu_2lss->SetPoint(0,mu_2lss,y_2lss);
  gr_mu_2lss->SetPointError(0,mu_2lss_m1s,mu_2lss_p1s,0,0); 
  gr_mu_2lss->SetLineWidth(3);
  gr_mu_2lss->SetLineColor(kRed);
  gr_mu_2lss->SetMarkerStyle(21);
  gr_mu_2lss->SetMarkerSize(1.5);


  TGraphAsymmErrors* gr_mu_2lss1tau=new TGraphAsymmErrors();
  gr_mu_2lss1tau->SetPoint(0,mu_2lss1tau,y_2lss1tau);
  gr_mu_2lss1tau->SetPointError(0,mu_2lss1tau_m1s,mu_2lss1tau_p1s,0,0); 
  gr_mu_2lss1tau->SetLineWidth(3);
  gr_mu_2lss1tau->SetLineColor(kRed);
  gr_mu_2lss1tau->SetMarkerStyle(21);
  gr_mu_2lss1tau->SetMarkerSize(1.5);


  TGraphAsymmErrors* gr_mu_3l=new TGraphAsymmErrors();
  gr_mu_3l->SetPoint(0,mu_3l,y_3l);
  gr_mu_3l->SetPointError(0,mu_3l_m1s,mu_3l_p1s,0,0); 
  gr_mu_3l->SetLineWidth(3);
  gr_mu_3l->SetLineColor(kRed);
  gr_mu_3l->SetMarkerStyle(21);
  gr_mu_3l->SetMarkerSize(1.5);


  TGraphAsymmErrors* gr_mu_3l1tau=new TGraphAsymmErrors();
  gr_mu_3l1tau->SetPoint(0,mu_3l1tau,y_3l1tau);
  gr_mu_3l1tau->SetPointError(0,mu_3l1tau_m1s,mu_3l1tau_p1s,0,0); 
  gr_mu_3l1tau->SetLineWidth(3);
  gr_mu_3l1tau->SetLineColor(kRed);
  gr_mu_3l1tau->SetMarkerStyle(21);
  gr_mu_3l1tau->SetMarkerSize(1.5);


  TGraphAsymmErrors* gr_mu_4l=new TGraphAsymmErrors();
  gr_mu_4l->SetPoint(0,mu_4l,y_4l);
  gr_mu_4l->SetPointError(0,mu_4l_m1s,mu_4l_p1s,0,0); 
  gr_mu_4l->SetLineWidth(3);
  gr_mu_4l->SetLineColor(kRed);
  gr_mu_4l->SetMarkerStyle(21);
  gr_mu_4l->SetMarkerSize(1.5);


  TGraphAsymmErrors* gr_mu_comb_stat=new TGraphAsymmErrors();
  gr_mu_comb_stat->SetPoint(0,mu_comb,y_comb);
  gr_mu_comb_stat->SetPointError(0,mu_comb_m1s_stat,mu_comb_p1s_stat,y_comb,y_comb);
  gr_mu_comb_stat->SetLineWidth(2);
  gr_mu_comb_stat->SetMarkerSize(0);
  gr_mu_comb_stat->SetFillColor(kCyan);

  TGraphAsymmErrors* gr_mu_comb_syst=new TGraphAsymmErrors();
  gr_mu_comb_syst->SetPoint(0,mu_comb,y_comb);
  gr_mu_comb_syst->SetPointError(0,mu_comb_m1s,mu_comb_p1s,y_comb,y_comb);
  gr_mu_comb_syst->SetLineWidth(2);
  gr_mu_comb_syst->SetMarkerSize(0);
  gr_mu_comb_syst->SetFillColor(kGreen);

  TGraphAsymmErrors* gr_mu_comb=new TGraphAsymmErrors();
  gr_mu_comb->SetPoint(0,mu_comb,y_comb);
  gr_mu_comb->SetPointError(0,0,0,y_comb,y_comb);
  gr_mu_comb->SetLineWidth(3);
  gr_mu_comb->SetMarkerSize(0);

    
  TCanvas* c=new TCanvas("c","c",750,700);
  c->SetLeftMargin(0.25);
  c->SetBottomMargin(0.15);

  gStyle->SetEndErrorSize(0);
  gr_mu_comb_syst->Draw("AE2");
  gr_mu_comb_stat->Draw("E2same");
  gr_mu_comb->Draw("Psame");
  gr_mu_1l2tau->Draw("Psame");
  gr_mu_2lss->Draw("Psame");
  gr_mu_2lss1tau->Draw("Psame");
  gr_mu_3l->Draw("Psame");
  gr_mu_3l1tau->Draw("Psame");
  gr_mu_4l->Draw("Psame");
  gPad->RedrawAxis();
  
  gr_mu_comb_syst->GetXaxis()->SetLimits(-3.5,3.5);
  gr_mu_comb_syst->GetYaxis()->SetRangeUser(0,11);
  gr_mu_comb_syst->GetYaxis()->SetLabelSize(0);
  gr_mu_comb_syst->GetYaxis()->SetTickSize(0);
  gr_mu_comb_syst->GetXaxis()->SetTitle("Best fit #mu(t#bar{t}H)");
  gr_mu_comb_syst->GetXaxis()->SetTitleOffset(1.5);


  double luminosity=35900;
  TLatex tex;
  tex.SetTextSize(0.035);
  tex.DrawLatexNDC(0.26,0.91,"CMS");
  tex.DrawLatexNDC(0.67,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));

  tex.SetTextSize(0.035);
  tex.DrawLatex(-5.5,y_1l2tau+0.3,"1l + 2#tau_{h}");
  tex.DrawLatex(-5.5,y_1l2tau-0.4,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_1l2tau,mu_1l2tau_p1s,mu_1l2tau_m1s));
  tex.DrawLatex(-5.5,y_2lss+0.3,"2lss");
  tex.DrawLatex(-5.5,y_2lss-0.4,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_2lss,mu_2lss_p1s,mu_2lss_m1s));
  tex.DrawLatex(-5.5,y_2lss1tau+0.3,"2lss + 1#tau_{h}");
  tex.DrawLatex(-5.5,y_2lss1tau-0.4,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_2lss1tau,mu_2lss1tau_p1s,mu_2lss1tau_m1s));
  tex.DrawLatex(-5.5,y_3l+0.3,"3l");
  tex.DrawLatex(-5.5,y_3l-0.4,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_3l,mu_3l_p1s,mu_3l_m1s));
  tex.DrawLatex(-5.5,y_3l1tau+0.3,"3l + 1#tau_{h}");
  tex.DrawLatex(-5.5,y_3l1tau-0.4,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_3l1tau,mu_3l1tau_p1s,mu_3l1tau_m1s));
  tex.DrawLatex(-5.5,y_4l+0.3,"4l");
  tex.DrawLatex(-5.5,y_4l-0.4,Form("#bf{#mu = %.2f ^{+%.2f}_{-%.2f}}",mu_4l,mu_4l_p1s,mu_4l_m1s));

  double mu_comb_m1s_syst=sqrt(mu_comb_m1s*mu_comb_m1s-mu_comb_m1s_stat*mu_comb_m1s_stat);
  double mu_comb_p1s_syst=sqrt(mu_comb_p1s*mu_comb_p1s-mu_comb_p1s_stat*mu_comb_p1s_stat);

  tex.SetTextSize(0.04);
  tex.DrawLatex(-3.0,10,Form("#mu = %.2f ^{+%.2f}_{-%.2f}  #bf{#left[ {}^{+%.2f}_{-%.2f}(stat.) {}^{+%.2f}_{-%.2f}(syst.)#right]}",mu_comb,mu_comb_p1s,mu_comb_m1s,mu_comb_p1s_stat,mu_comb_m1s_stat,mu_comb_p1s_syst,mu_comb_m1s_syst));
  
  c->SaveAs("../plots/pdf/mu_ttH_obs.pdf");
  c->SaveAs("../plots/png/mu_ttH_obs.png");

  return;


}
