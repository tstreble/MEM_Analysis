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




void plot_lim(){

  double lim_1l2tau_m2s = 1.7152;
  double lim_1l2tau_m1s = 2.3369;
  double lim_1l2tau = 3.3906;
  double lim_1l2tau_p1s = 5.0800;
  double lim_1l2tau_p2s = 7.4296;
  cout<<"Exp. lim. 1l2tau="<<lim_1l2tau<<" (+"<<lim_1l2tau_p1s-lim_1l2tau<<") (-"<<lim_1l2tau-lim_1l2tau_m1s<<")"<<endl;

  double lim_2lss1tau_m2s = 0.6415;
  double lim_2lss1tau_m1s = 0.8891;
  double lim_2lss1tau = 1.3086;
  double lim_2lss1tau_p1s = 1.9710;
  double lim_2lss1tau_p2s = 2.8889;
  cout<<"Exp. lim. 2lss1tau="<<lim_2lss1tau<<" (+"<<lim_2lss1tau_p1s-lim_2lss1tau<<") (-"<<lim_2lss1tau-lim_2lss1tau_m1s<<")"<<endl;


  double lim_3l1tau_m2s = 1.2187;
  double lim_3l1tau_m1s = 1.7324;
  double lim_3l1tau = 2.6328;
  double lim_3l1tau_p1s = 4.2070;
  double lim_3l1tau_p2s = 6.4923;
  cout<<"Exp. lim. 3l1tau="<<lim_3l1tau<<" (+"<<lim_3l1tau_p1s-lim_3l1tau<<") (-"<<lim_3l1tau-lim_3l1tau_m1s<<")"<<endl;


  double lim_comb_m2s = 0.5506;
  double lim_comb_m1s = 0.7565;
  double lim_comb = 1.1055;
  double lim_comb_p1s = 1.6475;
  double lim_comb_p2s = 2.3907;
  
  cout<<"Exp. lim. comb.="<<lim_comb<<" (+"<<lim_comb_p1s-lim_comb<<") (-"<<lim_comb-lim_comb_m1s<<")"<<endl;


  TGraphAsymmErrors* exp_1l2tau_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_1l2tau_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_1l2tau=new TGraphAsymmErrors();
  
  exp_1l2tau_2s->SetPoint(0,lim_1l2tau,4);
  exp_1l2tau_2s->SetPointError(0,lim_1l2tau-lim_1l2tau_m2s,lim_1l2tau_p2s-lim_1l2tau,0.35,0.35);
  exp_1l2tau_1s->SetPoint(0,lim_1l2tau,4);
  exp_1l2tau_1s->SetPointError(0,lim_1l2tau-lim_1l2tau_m1s,lim_1l2tau_p1s-lim_1l2tau,0.35,0.35);
  exp_1l2tau->SetPoint(0,lim_1l2tau,4);
  exp_1l2tau->SetPointError(0,0,0,0.35,0.35);

  exp_1l2tau->SetLineWidth(2);
  exp_1l2tau->SetLineStyle(2);
  exp_1l2tau->SetMarkerSize(0);
  

  exp_1l2tau_1s->SetFillColor(kGreen+1);
  exp_1l2tau_2s->SetFillColor(kOrange);


  TGraphAsymmErrors* exp_2lss1tau_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_2lss1tau_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_2lss1tau=new TGraphAsymmErrors();
  
  exp_2lss1tau_2s->SetPoint(0,lim_2lss1tau,3);
  exp_2lss1tau_2s->SetPointError(0,lim_2lss1tau-lim_2lss1tau_m2s,lim_2lss1tau_p2s-lim_2lss1tau,0.35,0.35);
  exp_2lss1tau_1s->SetPoint(0,lim_2lss1tau,3);
  exp_2lss1tau_1s->SetPointError(0,lim_2lss1tau-lim_2lss1tau_m1s,lim_2lss1tau_p1s-lim_2lss1tau,0.35,0.35);
  exp_2lss1tau->SetPoint(0,lim_2lss1tau,3);
  exp_2lss1tau->SetPointError(0,0,0,0.35,0.35);

  exp_2lss1tau->SetLineWidth(2);
  exp_2lss1tau->SetLineStyle(2);
  exp_2lss1tau->SetMarkerSize(0);
  exp_2lss1tau_1s->SetFillColor(kGreen+1);
  exp_2lss1tau_2s->SetFillColor(kOrange);


  TGraphAsymmErrors* exp_3l1tau_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_3l1tau_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_3l1tau=new TGraphAsymmErrors();
  
  exp_3l1tau_2s->SetPoint(0,lim_3l1tau,2);
  exp_3l1tau_2s->SetPointError(0,lim_3l1tau-lim_3l1tau_m2s,lim_3l1tau_p2s-lim_3l1tau,0.35,0.35);
  exp_3l1tau_1s->SetPoint(0,lim_3l1tau,2);
  exp_3l1tau_1s->SetPointError(0,lim_3l1tau-lim_3l1tau_m1s,lim_3l1tau_p1s-lim_3l1tau,0.35,0.35);
  exp_3l1tau->SetPoint(0,lim_3l1tau,2);
  exp_3l1tau->SetPointError(0,0,0,0.35,0.35);
      
  exp_3l1tau->SetLineWidth(2);
  exp_3l1tau->SetLineStyle(2);
  exp_3l1tau->SetMarkerSize(0);
  exp_3l1tau_1s->SetFillColor(kGreen+1);
  exp_3l1tau_2s->SetFillColor(kOrange);


  TGraphAsymmErrors* exp_comb_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_comb_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_comb=new TGraphAsymmErrors();
  
  exp_comb_2s->SetPoint(0,lim_comb,0.75);
  exp_comb_2s->SetPointError(0,lim_comb-lim_comb_m2s,lim_comb_p2s-lim_comb,0.35,0.35);
  exp_comb_1s->SetPoint(0,lim_comb,0.75);
  exp_comb_1s->SetPointError(0,lim_comb-lim_comb_m1s,lim_comb_p1s-lim_comb,0.35,0.35);
  exp_comb->SetPoint(0,lim_comb,0.75);
  exp_comb->SetPointError(0,0,0,0.35,0.35);
      
  exp_comb->SetLineWidth(2);
  exp_comb->SetLineStyle(2);
  exp_comb->SetMarkerSize(0);
  exp_comb_1s->SetFillColor(kGreen+1);
  exp_comb_2s->SetFillColor(kOrange);

  
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.25);
  c->SetBottomMargin(0.15);
  //c->SetLogx();
  gStyle->SetEndErrorSize(0);

  exp_1l2tau_2s->Draw("AE2");
  exp_1l2tau_1s->Draw("E2same");
  exp_1l2tau->Draw("Psame");

  exp_2lss1tau_2s->Draw("E2same");
  exp_2lss1tau_1s->Draw("E2same");
  exp_2lss1tau->Draw("Psame");

  exp_3l1tau_2s->Draw("E2same");
  exp_3l1tau_1s->Draw("E2same");
  exp_3l1tau->Draw("Psame");

  exp_comb_2s->Draw("E2same");
  exp_comb_1s->Draw("E2same");
  exp_comb->Draw("Psame");

  //exp_1l2tau_2s->GetXaxis()->SetLimits(0.5,50);
  exp_1l2tau_2s->GetXaxis()->SetLimits(0.,10);
  exp_1l2tau_2s->GetYaxis()->SetRangeUser(0,4.5);
  exp_1l2tau_2s->GetYaxis()->SetLabelSize(0);
  exp_1l2tau_2s->GetYaxis()->SetTickSize(0);

  exp_1l2tau_2s->GetXaxis()->SetTitle("95% CL upper limit on #mu=#sigma/#sigma_{SM}(m_{H}=125 GeV)");
  exp_1l2tau_2s->GetXaxis()->SetTitleOffset(1.5);


  //double luminosity=36814;
  double luminosity=35900;
  TLatex tex;
  tex.SetTextSize(0.035);
  tex.DrawLatexNDC(0.26,0.91,"CMS #bf{#it{Preliminary}}");
  tex.DrawLatexNDC(0.67,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));

  tex.SetTextSize(0.03);
  /*tex.DrawLatex(0.22,4,"1l + 2#tau_{h}");
  tex.DrawLatex(0.2,3,"2lss + 1#tau_{h}");
  tex.DrawLatex(0.22,2,"3l + 1#tau_{h}");
  tex.DrawLatex(0.2,0.75,"Combined");*/
  tex.DrawLatex(-2.,4,"1l + 2#tau_{h}");
  tex.DrawLatex(-2.5,3,"2lss + 1#tau_{h}");
  tex.DrawLatex(-2.,2,"3l + 1#tau_{h}");
  tex.DrawLatex(-2.5,0.75,"Combined");

  TGraphAsymmErrors* sd1=new TGraphAsymmErrors();
  sd1->SetFillColor(kGreen+1);
  sd1->SetLineStyle(2);
  sd1->SetLineWidth(2);

  TGraphAsymmErrors* sd2=new TGraphAsymmErrors();
  sd2->SetFillColor(kOrange);
  sd2->SetLineStyle(2);
  sd2->SetLineWidth(2);

  TGraphAsymmErrors* obs=new TGraphAsymmErrors();
  obs->SetLineWidth(2);
  obs->SetMarkerStyle(21);
  obs->SetFillStyle(0);


  TLegend* leg=new TLegend(0.6,0.2,0.85,0.4);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillStyle(0);
  leg->AddEntry(sd1,"Expected #pm 1 s.d.");
  leg->AddEntry(sd2,"Expected #pm 2 s.d.");
  leg->AddEntry(obs,"Observed","LP");
  leg->Draw("same");

  //TLine* line = new TLine(0.5, 0.5*2.75, 5, 0.5*2.75);
  TLine* line = new TLine(0., 0.5*2.75, 5, 0.5*2.75);
  //line->SetLineStyle(2);
  line->SetLineWidth(2);  
  line->Draw("same");


  c->SaveAs("../plots/pdf/limits_ttH_htt.pdf");
  c->SaveAs("../plots/png/limits_ttH_htt.png");

  return;

}







void plot_lim_obs(){

  double lim_1l2tau_m2s = 1.7152;
  double lim_1l2tau_m1s = 2.3369;
  double lim_1l2tau = 3.3906;
  double lim_1l2tau_p1s = 5.0800;
  double lim_1l2tau_p2s = 7.4296;
  cout<<"Exp. lim. 1l2tau="<<lim_1l2tau<<" (+"<<lim_1l2tau_p1s-lim_1l2tau<<") (-"<<lim_1l2tau-lim_1l2tau_m1s<<")"<<endl;

  double lim_2lss1tau_m2s = 0.6415;
  double lim_2lss1tau_m1s = 0.8891;
  double lim_2lss1tau = 1.3086;
  double lim_2lss1tau_p1s = 1.9710;
  double lim_2lss1tau_p2s = 2.8889;
  cout<<"Exp. lim. 2lss1tau="<<lim_2lss1tau<<" (+"<<lim_2lss1tau_p1s-lim_2lss1tau<<") (-"<<lim_2lss1tau-lim_2lss1tau_m1s<<")"<<endl;


  double lim_3l1tau_m2s = 1.2187;
  double lim_3l1tau_m1s = 1.7324;
  double lim_3l1tau = 2.6328;
  double lim_3l1tau_p1s = 4.2070;
  double lim_3l1tau_p2s = 6.4923;
  cout<<"Exp. lim. 3l1tau="<<lim_3l1tau<<" (+"<<lim_3l1tau_p1s-lim_3l1tau<<") (-"<<lim_3l1tau-lim_3l1tau_m1s<<")"<<endl;


  double lim_comb_m2s = 0.5506;
  double lim_comb_m1s = 0.7565;
  double lim_comb = 1.1055;
  double lim_comb_p1s = 1.6475;
  double lim_comb_p2s = 2.3907;
  
  cout<<"Exp. lim. comb.="<<lim_comb<<" (+"<<lim_comb_p1s-lim_comb<<") (-"<<lim_comb-lim_comb_m1s<<")"<<endl;


  double lim_obs_1l2tau = 2.6199;
  cout<<"Obs. lim. 1l2tau="<<lim_obs_1l2tau<<endl;
  double lim_obs_2lss1tau = 2.2924;
  cout<<"Obs. lim. 2lss1tau="<<lim_obs_2lss1tau<<endl;
  double lim_obs_3l1tau = 4.0613;
  cout<<"Obs. lim. 3l1tau="<<lim_obs_3l1tau<<endl;
  double lim_obs_comb = 1.9653;
  cout<<"Obs. lim. comb.="<<lim_obs_comb<<endl;


  TGraphAsymmErrors* exp_1l2tau_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_1l2tau_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_1l2tau=new TGraphAsymmErrors();
  TGraphAsymmErrors* obs_1l2tau=new TGraphAsymmErrors();
  
  exp_1l2tau_2s->SetPoint(0,lim_1l2tau,4);
  exp_1l2tau_2s->SetPointError(0,lim_1l2tau-lim_1l2tau_m2s,lim_1l2tau_p2s-lim_1l2tau,0.35,0.35);
  exp_1l2tau_1s->SetPoint(0,lim_1l2tau,4);
  exp_1l2tau_1s->SetPointError(0,lim_1l2tau-lim_1l2tau_m1s,lim_1l2tau_p1s-lim_1l2tau,0.35,0.35);
  exp_1l2tau->SetPoint(0,lim_1l2tau,4);
  exp_1l2tau->SetPointError(0,0,0,0.35,0.35);
  obs_1l2tau->SetPoint(0,lim_obs_1l2tau,4);
  obs_1l2tau->SetPointError(0,0,0,0.35,0.35);

  exp_1l2tau->SetLineWidth(2);
  exp_1l2tau->SetLineStyle(2);
  exp_1l2tau->SetMarkerSize(0);

  obs_1l2tau->SetLineWidth(2);
  obs_1l2tau->SetMarkerStyle(21);
  obs_1l2tau->SetFillStyle(0);

  exp_1l2tau_1s->SetFillColor(kGreen+1);
  exp_1l2tau_2s->SetFillColor(kOrange);


  TGraphAsymmErrors* exp_2lss1tau_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_2lss1tau_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_2lss1tau=new TGraphAsymmErrors();
  TGraphAsymmErrors* obs_2lss1tau=new TGraphAsymmErrors();

  exp_2lss1tau_2s->SetPoint(0,lim_2lss1tau,3);
  exp_2lss1tau_2s->SetPointError(0,lim_2lss1tau-lim_2lss1tau_m2s,lim_2lss1tau_p2s-lim_2lss1tau,0.35,0.35);
  exp_2lss1tau_1s->SetPoint(0,lim_2lss1tau,3);
  exp_2lss1tau_1s->SetPointError(0,lim_2lss1tau-lim_2lss1tau_m1s,lim_2lss1tau_p1s-lim_2lss1tau,0.35,0.35);
  exp_2lss1tau->SetPoint(0,lim_2lss1tau,3);
  exp_2lss1tau->SetPointError(0,0,0,0.35,0.35);
  obs_2lss1tau->SetPoint(0,lim_obs_2lss1tau,3);
  obs_2lss1tau->SetPointError(0,0,0,0.35,0.35);

  exp_2lss1tau->SetLineWidth(2);
  exp_2lss1tau->SetLineStyle(2);
  exp_2lss1tau->SetMarkerSize(0);

  obs_2lss1tau->SetLineWidth(2);
  obs_2lss1tau->SetMarkerStyle(21);
  obs_2lss1tau->SetFillStyle(0);

  exp_2lss1tau_1s->SetFillColor(kGreen+1);
  exp_2lss1tau_2s->SetFillColor(kOrange);


  TGraphAsymmErrors* exp_3l1tau_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_3l1tau_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_3l1tau=new TGraphAsymmErrors();
  TGraphAsymmErrors* obs_3l1tau=new TGraphAsymmErrors();
  
  exp_3l1tau_2s->SetPoint(0,lim_3l1tau,2);
  exp_3l1tau_2s->SetPointError(0,lim_3l1tau-lim_3l1tau_m2s,lim_3l1tau_p2s-lim_3l1tau,0.35,0.35);
  exp_3l1tau_1s->SetPoint(0,lim_3l1tau,2);
  exp_3l1tau_1s->SetPointError(0,lim_3l1tau-lim_3l1tau_m1s,lim_3l1tau_p1s-lim_3l1tau,0.35,0.35);
  exp_3l1tau->SetPoint(0,lim_3l1tau,2);
  exp_3l1tau->SetPointError(0,0,0,0.35,0.35);
  obs_3l1tau->SetPoint(0,lim_obs_3l1tau,2);
  obs_3l1tau->SetPointError(0,0,0,0.35,0.35);
      
  exp_3l1tau->SetLineWidth(2);
  exp_3l1tau->SetLineStyle(2);
  exp_3l1tau->SetMarkerSize(0);

  obs_3l1tau->SetLineWidth(2);
  obs_3l1tau->SetMarkerStyle(21);
  obs_3l1tau->SetFillStyle(0);

  exp_3l1tau_1s->SetFillColor(kGreen+1);
  exp_3l1tau_2s->SetFillColor(kOrange);


  TGraphAsymmErrors* exp_comb_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_comb_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_comb=new TGraphAsymmErrors();
  TGraphAsymmErrors* obs_comb=new TGraphAsymmErrors();

  exp_comb_2s->SetPoint(0,lim_comb,0.75);
  exp_comb_2s->SetPointError(0,lim_comb-lim_comb_m2s,lim_comb_p2s-lim_comb,0.35,0.35);
  exp_comb_1s->SetPoint(0,lim_comb,0.75);
  exp_comb_1s->SetPointError(0,lim_comb-lim_comb_m1s,lim_comb_p1s-lim_comb,0.35,0.35);
  exp_comb->SetPoint(0,lim_comb,0.75);
  exp_comb->SetPointError(0,0,0,0.35,0.35);
  obs_comb->SetPoint(0,lim_obs_comb,0.75);
  obs_comb->SetPointError(0,0,0,0.35,0.35);
      
  exp_comb->SetLineWidth(2);
  exp_comb->SetLineStyle(2);
  exp_comb->SetMarkerSize(0);

  obs_comb->SetLineWidth(2);
  obs_comb->SetMarkerStyle(21);
  obs_comb->SetFillStyle(0);

  exp_comb_1s->SetFillColor(kGreen+1);
  exp_comb_2s->SetFillColor(kOrange);

  
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.25);
  c->SetBottomMargin(0.15);
  //c->SetLogx();
  gStyle->SetEndErrorSize(0);

  exp_1l2tau_2s->Draw("AE2");
  exp_1l2tau_1s->Draw("E2same");
  exp_1l2tau->Draw("Psame");
  obs_1l2tau->Draw("Psame");

  exp_2lss1tau_2s->Draw("E2same");
  exp_2lss1tau_1s->Draw("E2same");
  exp_2lss1tau->Draw("Psame");
  obs_2lss1tau->Draw("Psame");

  exp_3l1tau_2s->Draw("E2same");
  exp_3l1tau_1s->Draw("E2same");
  exp_3l1tau->Draw("Psame");
  obs_3l1tau->Draw("Psame");

  exp_comb_2s->Draw("E2same");
  exp_comb_1s->Draw("E2same");
  exp_comb->Draw("Psame");
  obs_comb->Draw("Psame");

  //exp_1l2tau_2s->GetXaxis()->SetLimits(0.5,50);
  exp_1l2tau_2s->GetXaxis()->SetLimits(0.,10);
  exp_1l2tau_2s->GetYaxis()->SetRangeUser(0,4.5);
  exp_1l2tau_2s->GetYaxis()->SetLabelSize(0);
  exp_1l2tau_2s->GetYaxis()->SetTickSize(0);

  exp_1l2tau_2s->GetXaxis()->SetTitle("95% CL upper limit on #mu=#sigma/#sigma_{SM}(m_{H}=125 GeV)");
  exp_1l2tau_2s->GetXaxis()->SetTitleOffset(1.5);


  //double luminosity=36814;
  double luminosity=35900;
  TLatex tex;
  tex.SetTextSize(0.035);
  tex.DrawLatexNDC(0.26,0.91,"CMS #bf{#it{Preliminary}}");
  tex.DrawLatexNDC(0.67,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));

  tex.SetTextSize(0.03);
  /*tex.DrawLatex(0.22,4,"1l + 2#tau_{h}");
  tex.DrawLatex(0.2,3,"2lss + 1#tau_{h}");
  tex.DrawLatex(0.22,2,"3l + 1#tau_{h}");
  tex.DrawLatex(0.2,0.75,"Combined");*/
  tex.DrawLatex(-2.,4,"1l + 2#tau_{h}");
  tex.DrawLatex(-2.5,3,"2lss + 1#tau_{h}");
  tex.DrawLatex(-2.,2,"3l + 1#tau_{h}");
  tex.DrawLatex(-2.5,0.75,"Combined");

  TGraphAsymmErrors* sd1=new TGraphAsymmErrors();
  sd1->SetFillColor(kGreen+1);
  sd1->SetLineStyle(2);
  sd1->SetLineWidth(2);

  TGraphAsymmErrors* sd2=new TGraphAsymmErrors();
  sd2->SetFillColor(kOrange);
  sd2->SetLineStyle(2);
  sd2->SetLineWidth(2);

  TGraphAsymmErrors* obs=new TGraphAsymmErrors();
  obs->SetLineWidth(2);
  obs->SetMarkerStyle(21);
  obs->SetFillStyle(0);


  TLegend* leg=new TLegend(0.6,0.2,0.85,0.4);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillStyle(0);
  leg->AddEntry(sd1,"Expected #pm 1 s.d.");
  leg->AddEntry(sd2,"Expected #pm 2 s.d.");
  leg->AddEntry(obs,"Observed","LP");
  leg->Draw("same");

  //TLine* line = new TLine(0.5, 0.5*2.75, 5, 0.5*2.75);
  TLine* line = new TLine(0., 0.5*2.75, 5, 0.5*2.75);
  //line->SetLineStyle(2);
  line->SetLineWidth(2);  
  line->Draw("same");


  c->SaveAs("../plots/pdf/limits_ttH_htt_obs.pdf");
  c->SaveAs("../plots/png/limits_ttH_htt_obs.png");

  return;

}










void plot_lim_obs_comb(){

  double lim_1l2tau_m2s = 1.9523;
  double lim_1l2tau_m1s = 2.6600;
  double lim_1l2tau = 3.8594;
  double lim_1l2tau_p1s = 5.7823;
  double lim_1l2tau_p2s = 8.4567;
  cout<<"Exp. lim. 1l2tau="<<lim_1l2tau<<" (+"<<lim_1l2tau_p1s-lim_1l2tau<<") (-"<<lim_1l2tau-lim_1l2tau_m1s<<")"<<endl;

  double lim_2lss_m2s = 0.5194;
  double lim_2lss_m1s = 0.7001;
  double lim_2lss = 0.9961;
  double lim_2lss_p1s = 1.4368;
  double lim_2lss_p2s = 2.0152;
  cout<<"Exp. lim. 2lss="<<lim_2lss<<" (+"<<lim_2lss_p1s-lim_2lss<<") (-"<<lim_2lss-lim_2lss_m1s<<")"<<endl;


  double lim_2lss1tau_m2s = 0.6930;
  double lim_2lss1tau_m1s = 0.9562;
  double lim_2lss1tau = 1.4023;
  double lim_2lss1tau_p1s = 2.1234;
  double lim_2lss1tau_p2s = 3.0852;
  cout<<"Exp. lim. 2lss1tau="<<lim_2lss1tau<<" (+"<<lim_2lss1tau_p1s-lim_2lss1tau<<") (-"<<lim_2lss1tau-lim_2lss1tau_m1s<<")"<<endl;

  double lim_3l_m2s = 0.8085;
  double lim_3l_m1s = 1.1030;
  double lim_3l = 1.5859;
  double lim_3l_p1s = 2.3256;
  double lim_3l_p2s = 3.2912;
  cout<<"Exp. lim. 3l="<<lim_3l<<" (+"<<lim_3l_p1s-lim_3l<<") (-"<<lim_3l-lim_3l_m1s<<")"<<endl;

  double lim_3l1tau_m2s = 1.3496;
  double lim_3l1tau_m1s = 1.9009;
  double lim_3l1tau = 2.8672;
  double lim_3l1tau_p1s = 4.5015;
  double lim_3l1tau_p2s = 6.8407;
  cout<<"Exp. lim. 3l1tau="<<lim_3l1tau<<" (+"<<lim_3l1tau_p1s-lim_3l1tau<<") (-"<<lim_3l1tau-lim_3l1tau_m1s<<")"<<endl;

  double lim_4l_m2s = 2.3334;
  double lim_4l_m1s = 3.3424;
  double lim_4l = 5.1719;
  double lim_4l_p1s = 8.3466;
  double lim_4l_p2s = 13.1323;
  cout<<"Exp. lim. 4l="<<lim_4l<<" (+"<<lim_4l_p1s-lim_4l<<") (-"<<lim_4l-lim_4l_m1s<<")"<<endl;


  double lim_comb_m2s = 0.3811;
  double lim_comb_m1s = 0.5171;
  double lim_comb = 0.7363;
  double lim_comb_p1s = 1.0680;
  double lim_comb_p2s = 1.5026;
  
  cout<<"Exp. lim. comb.="<<lim_comb<<" (+"<<lim_comb_p1s-lim_comb<<") (-"<<lim_comb-lim_comb_m1s<<")"<<endl;


  double lim_sig_1l2tau = 4.9;
  cout<<"Exp. lim. mu=1 1l2tau="<<lim_sig_1l2tau<<endl;
  double lim_sig_2lss = 1.9;
  cout<<"Exp. lim. mu=1 2lss="<<lim_sig_2lss<<endl;
  double lim_sig_2lss1tau = 2.5;
  cout<<"Exp. lim. mu=1 2lss1tau="<<lim_sig_2lss1tau<<endl;
  double lim_sig_3l = 2.4;
  cout<<"Exp. lim. mu=1 3l="<<lim_sig_3l<<endl;
  double lim_sig_3l1tau = 4.0;
  cout<<"Exp. lim. mu=1 3l1tau="<<lim_sig_3l1tau<<endl;
  double lim_sig_4l = 6.4;
  cout<<"Exp. lim. mu=1 4l="<<lim_sig_3l1tau<<endl;
  double lim_sig_comb = 1.7;
  cout<<"Exp. lim. mu=1 comb.="<<lim_sig_comb<<endl;


  double lim_obs_1l2tau = 2.8795;
  cout<<"Obs. lim. 1l2tau="<<lim_obs_1l2tau<<endl;
  double lim_obs_2lss = 2.7323;
  cout<<"Obs. lim. 2lss="<<lim_obs_2lss<<endl;
  double lim_obs_2lss1tau = 2.4919;
  cout<<"Obs. lim. 2lss1tau="<<lim_obs_2lss1tau<<endl;
  double lim_obs_3l = 2.4380;
  cout<<"Obs. lim. 3l="<<lim_obs_3l<<endl;
  double lim_obs_3l1tau = 4.4480;
  cout<<"Obs. lim. 3l1tau="<<lim_obs_3l1tau<<endl;
  double lim_obs_4l = 6.1277;
  cout<<"Obs. lim. 4l="<<lim_obs_3l1tau<<endl;
  double lim_obs_comb = 2.0038;
  cout<<"Obs. lim. comb.="<<lim_obs_comb<<endl;

  
  double y_1l2tau = 9.;
  double y_2lss = 8.;
  double y_2lss1tau = 7.;
  double y_3l = 6.;
  double y_3l1tau = 5.;
  double y_4l = 4.;
  double y_comb = 2.;


  TGraphAsymmErrors* exp_1l2tau_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_1l2tau_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_1l2tau=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_sig_1l2tau=new TGraphAsymmErrors();
  TGraphAsymmErrors* obs_1l2tau=new TGraphAsymmErrors();
  
  exp_1l2tau_2s->SetPoint(0,lim_1l2tau,y_1l2tau);
  exp_1l2tau_2s->SetPointError(0,lim_1l2tau-lim_1l2tau_m2s,lim_1l2tau_p2s-lim_1l2tau,0.35,0.35);
  exp_1l2tau_1s->SetPoint(0,lim_1l2tau,y_1l2tau);
  exp_1l2tau_1s->SetPointError(0,lim_1l2tau-lim_1l2tau_m1s,lim_1l2tau_p1s-lim_1l2tau,0.35,0.35);
  exp_1l2tau->SetPoint(0,lim_1l2tau,y_1l2tau);
  exp_1l2tau->SetPointError(0,0,0,0.35,0.35);
  exp_sig_1l2tau->SetPoint(0,lim_sig_1l2tau,y_1l2tau);
  exp_sig_1l2tau->SetPointError(0,0,0,0.35,0.35);
  obs_1l2tau->SetPoint(0,lim_obs_1l2tau,y_1l2tau);
  obs_1l2tau->SetPointError(0,0,0,0.35,0.35);

  exp_1l2tau->SetLineWidth(2);
  exp_1l2tau->SetLineStyle(2);
  exp_1l2tau->SetMarkerSize(0);

  exp_sig_1l2tau->SetLineWidth(2);
  exp_sig_1l2tau->SetLineStyle(2);
  exp_sig_1l2tau->SetLineColor(kRed);
  exp_sig_1l2tau->SetMarkerSize(0);

  obs_1l2tau->SetLineWidth(2);
  obs_1l2tau->SetMarkerStyle(21);
  obs_1l2tau->SetFillStyle(0);

  exp_1l2tau_1s->SetFillColor(kGreen+1);
  exp_1l2tau_2s->SetFillColor(kOrange);


  TGraphAsymmErrors* exp_2lss_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_2lss_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_2lss=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_sig_2lss=new TGraphAsymmErrors();
  TGraphAsymmErrors* obs_2lss=new TGraphAsymmErrors();

  exp_2lss_2s->SetPoint(0,lim_2lss,y_2lss);
  exp_2lss_2s->SetPointError(0,lim_2lss-lim_2lss_m2s,lim_2lss_p2s-lim_2lss,0.35,0.35);
  exp_2lss_1s->SetPoint(0,lim_2lss,y_2lss);
  exp_2lss_1s->SetPointError(0,lim_2lss-lim_2lss_m1s,lim_2lss_p1s-lim_2lss,0.35,0.35);
  exp_2lss->SetPoint(0,lim_2lss,y_2lss);
  exp_2lss->SetPointError(0,0,0,0.35,0.35);
  exp_sig_2lss->SetPoint(0,lim_sig_2lss,y_2lss);
  exp_sig_2lss->SetPointError(0,0,0,0.35,0.35);
  obs_2lss->SetPoint(0,lim_obs_2lss,y_2lss);
  obs_2lss->SetPointError(0,0,0,0.35,0.35);

  exp_2lss->SetLineWidth(2);
  exp_2lss->SetLineStyle(2);
  exp_2lss->SetMarkerSize(0);

  exp_sig_2lss->SetLineWidth(2);
  exp_sig_2lss->SetLineStyle(2);
  exp_sig_2lss->SetLineColor(kRed);
  exp_sig_2lss->SetMarkerSize(0);

  obs_2lss->SetLineWidth(2);
  obs_2lss->SetMarkerStyle(21);
  obs_2lss->SetFillStyle(0);

  exp_2lss_1s->SetFillColor(kGreen+1);
  exp_2lss_2s->SetFillColor(kOrange);


  TGraphAsymmErrors* exp_2lss1tau_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_2lss1tau_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_2lss1tau=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_sig_2lss1tau=new TGraphAsymmErrors();
  TGraphAsymmErrors* obs_2lss1tau=new TGraphAsymmErrors();

  exp_2lss1tau_2s->SetPoint(0,lim_2lss1tau,y_2lss1tau);
  exp_2lss1tau_2s->SetPointError(0,lim_2lss1tau-lim_2lss1tau_m2s,lim_2lss1tau_p2s-lim_2lss1tau,0.35,0.35);
  exp_2lss1tau_1s->SetPoint(0,lim_2lss1tau,y_2lss1tau);
  exp_2lss1tau_1s->SetPointError(0,lim_2lss1tau-lim_2lss1tau_m1s,lim_2lss1tau_p1s-lim_2lss1tau,0.35,0.35);
  exp_2lss1tau->SetPoint(0,lim_2lss1tau,y_2lss1tau);
  exp_2lss1tau->SetPointError(0,0,0,0.35,0.35);
  exp_sig_2lss1tau->SetPoint(0,lim_sig_2lss1tau,y_2lss1tau);
  exp_sig_2lss1tau->SetPointError(0,0,0,0.35,0.35);
  obs_2lss1tau->SetPoint(0,lim_obs_2lss1tau,y_2lss1tau);
  obs_2lss1tau->SetPointError(0,0,0,0.35,0.35);

  exp_2lss1tau->SetLineWidth(2);
  exp_2lss1tau->SetLineStyle(2);
  exp_2lss1tau->SetMarkerSize(0);

  exp_sig_2lss1tau->SetLineWidth(2);
  exp_sig_2lss1tau->SetLineStyle(2);
  exp_sig_2lss1tau->SetLineColor(kRed);
  exp_sig_2lss1tau->SetMarkerSize(0);

  obs_2lss1tau->SetLineWidth(2);
  obs_2lss1tau->SetMarkerStyle(21);
  obs_2lss1tau->SetFillStyle(0);

  exp_2lss1tau_1s->SetFillColor(kGreen+1);
  exp_2lss1tau_2s->SetFillColor(kOrange);


  TGraphAsymmErrors* exp_3l_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_3l_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_3l=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_sig_3l=new TGraphAsymmErrors();
  TGraphAsymmErrors* obs_3l=new TGraphAsymmErrors();
  
  exp_3l_2s->SetPoint(0,lim_3l,y_3l);
  exp_3l_2s->SetPointError(0,lim_3l-lim_3l_m2s,lim_3l_p2s-lim_3l,0.35,0.35);
  exp_3l_1s->SetPoint(0,lim_3l,y_3l);
  exp_3l_1s->SetPointError(0,lim_3l-lim_3l_m1s,lim_3l_p1s-lim_3l,0.35,0.35);
  exp_3l->SetPoint(0,lim_3l,y_3l);
  exp_3l->SetPointError(0,0,0,0.35,0.35);
  exp_sig_3l->SetPoint(0,lim_sig_3l,y_3l);
  exp_sig_3l->SetPointError(0,0,0,0.35,0.35);
  obs_3l->SetPoint(0,lim_obs_3l,y_3l);
  obs_3l->SetPointError(0,0,0,0.35,0.35);
      
  exp_3l->SetLineWidth(2);
  exp_3l->SetLineStyle(2);
  exp_3l->SetMarkerSize(0);

  exp_sig_3l->SetLineWidth(2);
  exp_sig_3l->SetLineStyle(2);
  exp_sig_3l->SetLineColor(kRed);
  exp_sig_3l->SetMarkerSize(0);


  obs_3l->SetLineWidth(2);
  obs_3l->SetMarkerStyle(21);
  obs_3l->SetFillStyle(0);

  exp_3l_1s->SetFillColor(kGreen+1);
  exp_3l_2s->SetFillColor(kOrange);



  TGraphAsymmErrors* exp_3l1tau_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_3l1tau_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_3l1tau=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_sig_3l1tau=new TGraphAsymmErrors();
  TGraphAsymmErrors* obs_3l1tau=new TGraphAsymmErrors();
  
  exp_3l1tau_2s->SetPoint(0,lim_3l1tau,y_3l1tau);
  exp_3l1tau_2s->SetPointError(0,lim_3l1tau-lim_3l1tau_m2s,lim_3l1tau_p2s-lim_3l1tau,0.35,0.35);
  exp_3l1tau_1s->SetPoint(0,lim_3l1tau,y_3l1tau);
  exp_3l1tau_1s->SetPointError(0,lim_3l1tau-lim_3l1tau_m1s,lim_3l1tau_p1s-lim_3l1tau,0.35,0.35);
  exp_3l1tau->SetPoint(0,lim_3l1tau,y_3l1tau);
  exp_3l1tau->SetPointError(0,0,0,0.35,0.35);
  exp_sig_3l1tau->SetPoint(0,lim_sig_3l1tau,y_3l1tau);
  exp_sig_3l1tau->SetPointError(0,0,0,0.35,0.35);
  obs_3l1tau->SetPoint(0,lim_obs_3l1tau,y_3l1tau);
  obs_3l1tau->SetPointError(0,0,0,0.35,0.35);
      
  exp_3l1tau->SetLineWidth(2);
  exp_3l1tau->SetLineStyle(2);
  exp_3l1tau->SetMarkerSize(0);

  exp_sig_3l1tau->SetLineWidth(2);
  exp_sig_3l1tau->SetLineStyle(2);
  exp_sig_3l1tau->SetLineColor(kRed);
  exp_sig_3l1tau->SetMarkerSize(0);

  obs_3l1tau->SetLineWidth(2);
  obs_3l1tau->SetMarkerStyle(21);
  obs_3l1tau->SetFillStyle(0);

  exp_3l1tau_1s->SetFillColor(kGreen+1);
  exp_3l1tau_2s->SetFillColor(kOrange);

  TGraphAsymmErrors* exp_4l_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_4l_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_4l=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_sig_4l=new TGraphAsymmErrors();
  TGraphAsymmErrors* obs_4l=new TGraphAsymmErrors();
  
  exp_4l_2s->SetPoint(0,lim_4l,y_4l);
  exp_4l_2s->SetPointError(0,lim_4l-lim_4l_m2s,lim_4l_p2s-lim_4l,0.35,0.35);
  exp_4l_1s->SetPoint(0,lim_4l,y_4l);
  exp_4l_1s->SetPointError(0,lim_4l-lim_4l_m1s,lim_4l_p1s-lim_4l,0.35,0.35);
  exp_4l->SetPoint(0,lim_4l,y_4l);
  exp_4l->SetPointError(0,0,0,0.35,0.35);
  exp_sig_4l->SetPoint(0,lim_sig_4l,y_4l);
  exp_sig_4l->SetPointError(0,0,0,0.35,0.35);
  obs_4l->SetPoint(0,lim_obs_4l,y_4l);
  obs_4l->SetPointError(0,0,0,0.35,0.35);
      
  exp_4l->SetLineWidth(2);
  exp_4l->SetLineStyle(2);
  exp_4l->SetMarkerSize(0);

  exp_sig_4l->SetLineWidth(2);
  exp_sig_4l->SetLineStyle(2);
  exp_sig_4l->SetLineColor(kRed);
  exp_sig_4l->SetMarkerSize(0);

  obs_4l->SetLineWidth(2);
  obs_4l->SetMarkerStyle(21);
  obs_4l->SetFillStyle(0);

  exp_4l_1s->SetFillColor(kGreen+1);
  exp_4l_2s->SetFillColor(kOrange);



  TGraphAsymmErrors* exp_comb_2s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_comb_1s=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_comb=new TGraphAsymmErrors();
  TGraphAsymmErrors* exp_sig_comb=new TGraphAsymmErrors();
  TGraphAsymmErrors* obs_comb=new TGraphAsymmErrors();

  exp_comb_2s->SetPoint(0,lim_comb,y_comb);
  exp_comb_2s->SetPointError(0,lim_comb-lim_comb_m2s,lim_comb_p2s-lim_comb,1.25,1.25);
  exp_comb_1s->SetPoint(0,lim_comb,y_comb);
  exp_comb_1s->SetPointError(0,lim_comb-lim_comb_m1s,lim_comb_p1s-lim_comb,1.25,1.25);
  exp_comb->SetPoint(0,lim_comb,y_comb);
  exp_comb->SetPointError(0,0,0,1.25,1.25);
  exp_sig_comb->SetPoint(0,lim_sig_comb,y_comb);
  exp_sig_comb->SetPointError(0,0,0,1.25,1.25);
  obs_comb->SetPoint(0,lim_obs_comb,y_comb);
  obs_comb->SetPointError(0,0,0,1.25,1.25);
      
  exp_comb->SetLineWidth(2);
  exp_comb->SetLineStyle(2);
  exp_comb->SetMarkerSize(0);

  exp_sig_comb->SetLineWidth(2);
  exp_sig_comb->SetLineStyle(2);
  exp_sig_comb->SetLineColor(kRed);
  exp_sig_comb->SetMarkerSize(0);

  obs_comb->SetLineWidth(2);
  obs_comb->SetMarkerStyle(21);
  obs_comb->SetFillStyle(0);

  exp_comb_1s->SetFillColor(kGreen+1);
  exp_comb_2s->SetFillColor(kOrange);

  
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.25);
  c->SetBottomMargin(0.15);
  c->SetLogx();
  
  gStyle->SetEndErrorSize(0);

  exp_1l2tau_2s->Draw("AE2");
  exp_1l2tau_1s->Draw("E2same");
  exp_1l2tau->Draw("Psame");
  exp_sig_1l2tau->Draw("Psame");
  obs_1l2tau->Draw("Psame");

  exp_2lss_2s->Draw("E2same");
  exp_2lss_1s->Draw("E2same");
  exp_2lss->Draw("Psame");
  exp_sig_2lss->Draw("Psame");
  obs_2lss->Draw("Psame");

  exp_2lss1tau_2s->Draw("E2same");
  exp_2lss1tau_1s->Draw("E2same");
  exp_2lss1tau->Draw("Psame");
  exp_sig_2lss1tau->Draw("Psame");
  obs_2lss1tau->Draw("Psame");

  exp_3l_2s->Draw("E2same");
  exp_3l_1s->Draw("E2same");
  exp_3l->Draw("Psame");
  exp_sig_3l->Draw("Psame");
  obs_3l->Draw("Psame");

  exp_3l1tau_2s->Draw("E2same");
  exp_3l1tau_1s->Draw("E2same");
  exp_3l1tau->Draw("Psame");
  exp_sig_3l1tau->Draw("Psame");
  obs_3l1tau->Draw("Psame");

  exp_4l_2s->Draw("E2same");
  exp_4l_1s->Draw("E2same");
  exp_4l->Draw("Psame");
  exp_sig_4l->Draw("Psame");
  obs_4l->Draw("Psame");

  exp_comb_2s->Draw("E2same");
  exp_comb_1s->Draw("E2same");
  exp_comb->Draw("Psame");
  exp_sig_comb->Draw("Psame");
  obs_comb->Draw("Psame");

  //exp_1l2tau_2s->GetXaxis()->SetLimits(0.,15);
  exp_1l2tau_2s->GetXaxis()->SetLimits(3e-1,15);
  exp_1l2tau_2s->GetYaxis()->SetRangeUser(0,y_1l2tau+0.5);
  exp_1l2tau_2s->GetYaxis()->SetLabelSize(0);
  exp_1l2tau_2s->GetYaxis()->SetTickSize(0);

  exp_1l2tau_2s->GetXaxis()->SetTitle("95% CL upper limit on #mu=#sigma/#sigma_{SM}");
  exp_1l2tau_2s->GetXaxis()->SetTitleOffset(1.5);


  double luminosity=35900;
  TLatex tex;
  tex.SetTextSize(0.035);
  tex.DrawLatexNDC(0.26,0.91,"CMS");
  tex.DrawLatexNDC(0.67,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));

  tex.SetTextSize(0.04);
  /*tex.DrawLatex(-3,y_1l2tau-0.1,"1l + 2#tau_{h}");
  tex.DrawLatex(-3,y_2lss-0.1,"2lss");
  tex.DrawLatex(-3,y_2lss1tau-0.1,"2lss + 1#tau_{h}");
  tex.DrawLatex(-3,y_3l-0.1,"3l");
  tex.DrawLatex(-3,y_3l1tau-0.1,"3l + 1#tau_{h}");
  tex.DrawLatex(-3,y_4l-0.1,"4l");
  tex.DrawLatex(-4,y_comb+0.2,"Combined");
  tex.DrawLatex(-4,y_comb-0.3,"#bf{#mu<2.0 (0.7 exp)}");*/
  tex.DrawLatex(8e-2,y_1l2tau-0.1,"1l + 2#tau_{h}");
  tex.DrawLatex(8e-2,y_2lss-0.1,"2lss");
  tex.DrawLatex(8e-2,y_2lss1tau-0.1,"2lss + 1#tau_{h}");
  tex.DrawLatex(8e-2,y_3l-0.1,"3l");
  tex.DrawLatex(8e-2,y_3l1tau-0.1,"3l + 1#tau_{h}");
  tex.DrawLatex(8e-2,y_4l-0.1,"4l");
  tex.DrawLatex(8e-2,y_comb+0.2,"Combined");
  tex.DrawLatex(7e-2,y_comb-0.3,"#bf{#mu<2.0 (0.7 exp)}");


  TGraphAsymmErrors* sd1=new TGraphAsymmErrors();
  sd1->SetFillColor(kGreen+1);
  sd1->SetLineStyle(2);
  sd1->SetLineWidth(2);

  TGraphAsymmErrors* sd2=new TGraphAsymmErrors();
  sd2->SetFillColor(kOrange);
  sd2->SetLineStyle(2);
  sd2->SetLineWidth(2);

  TGraphAsymmErrors* sig=new TGraphAsymmErrors();
  sig->SetLineWidth(2);
  sig->SetLineStyle(2);
  sig->SetLineColor(kRed);
  sig->SetFillStyle(0);

  TGraphAsymmErrors* obs=new TGraphAsymmErrors();
  obs->SetLineWidth(2);
  obs->SetMarkerStyle(21);
  obs->SetFillStyle(0);


  TLegend* leg=new TLegend(0.6,0.2,0.85,0.4);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillStyle(0);
  leg->AddEntry(sd1,"Expected #pm 1 s.d.");
  leg->AddEntry(sd2,"Expected #pm 2 s.d.");
  leg->AddEntry(sig,"t#bar{t}H(#mu=1) injected","LP");
  leg->AddEntry(obs,"Observed","LP");
  leg->Draw("same");

  //TLine* line = new TLine(0.5, 0.5*2.75, 5, 0.5*2.75);
  //TLine* line = new TLine(0., 0.5*2.75, 5, 0.5*2.75);
  //line->SetLineStyle(2);
  //line->SetLineWidth(2);  
  //line->Draw("same");


  c->SaveAs("../plots/pdf/limits_ttH_obs.pdf");
  c->SaveAs("../plots/png/limits_ttH_obs.png");

  return;

}
