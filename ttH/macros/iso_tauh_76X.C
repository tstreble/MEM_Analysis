#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <Helpers.C>
#include <vector>
#include <TLatex.h>
#include <TGraphErrors.h>

using namespace std;










void plot_efficiency_iso_tauh_76X(){

  TH1F* h_ttH = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_dRveto_gen_iso70_skimmed.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]","MC_weight*PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]>0.5)",200,0,20);
  h_ttH->Scale(1/h_ttH->Integral(0,201));

  TH1F* h_ttH_byLooseComb = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_dRveto_gen_iso70_skimmed.root","HTauTauTree"," (tauID[genpi_i_daughter_matched]>>3)&1","MC_weight*PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]>0.5)",4,-1,3);
  h_ttH_byLooseComb->Scale(1/h_ttH_byLooseComb->Integral(0,5));

  TH1F* h_ttH_byLooseCombdR03 = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_dRveto_gen_iso70_skimmed.root","HTauTauTree","(tauID[genpi_i_daughter_matched]>>21)&1","MC_weight*PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]>0.5)",4,-1,3);
  h_ttH_byLooseCombdR03->Scale(1/h_ttH_byLooseCombdR03->Integral(0,5));

  TH1F* h_ttH_byLooseMVAdR03 = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_dRveto_gen_iso70_skimmed.root","HTauTauTree","(tauID[genpi_i_daughter_matched]>>24)&1","MC_weight*PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1  && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]>0.5)",4,-1,3);
  h_ttH_byLooseMVAdR03->Scale(1/h_ttH_byLooseMVAdR03->Integral(0,5));


  TLegend* leg=new TLegend(0.47,0.13,0.85,0.51);
  leg->SetHeader("#splitline{p_{T}>30 GeV , |#eta|<2.1}{#DeltaR(gen,reco)<0.3}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  TGraphErrors* gr_ttH=new TGraphErrors();
  TGraphErrors* gr_ttH_byLooseComb=new TGraphErrors();
  TGraphErrors* gr_ttH_byLooseCombdR03=new TGraphErrors();
  TGraphErrors* gr_ttH_byLooseMVAdR03=new TGraphErrors();

  int bin_down=h_ttH->FindBin(0);
  int i=0;

  int bin_cut=h_ttH_byLooseComb->FindBin(1);

  float eff_ttH_byLooseComb=h_ttH_byLooseComb->Integral(bin_cut,bin_cut);
  float eff_ttH_byLooseCombdR03=h_ttH_byLooseCombdR03->Integral(bin_cut,bin_cut);
  float eff_ttH_byLooseMVAdR03=h_ttH_byLooseMVAdR03->Integral(bin_cut,bin_cut);


  for(float iso=0; iso<21; iso+=0.1){

    int bin_up=h_ttH->FindBin(iso);
    float eff_ttH=h_ttH->Integral(bin_down,bin_up);

    gr_ttH->SetPoint(i,iso,eff_ttH);
    gr_ttH_byLooseComb->SetPoint(i,iso,eff_ttH_byLooseComb);
    gr_ttH_byLooseCombdR03->SetPoint(i,iso,eff_ttH_byLooseCombdR03);
    gr_ttH_byLooseMVAdR03->SetPoint(i,iso,eff_ttH_byLooseMVAdR03);
    i++;

    if(iso==2.5){
      cout<<eff_ttH<<endl;
    }

  }


  gr_ttH->SetLineColor(1);
  gr_ttH->SetMarkerColor(1);  
  gr_ttH->SetLineWidth(2);
  gr_ttH->SetFillColor(0);
  leg->AddEntry(gr_ttH,"Comb. iso. #Delta#beta corr. raw");

  gr_ttH_byLooseComb->SetLineColor(2);
  gr_ttH_byLooseComb->SetMarkerColor(2);  
  gr_ttH_byLooseComb->SetLineWidth(2);
  gr_ttH_byLooseComb->SetFillColor(0);
  leg->AddEntry(gr_ttH_byLooseComb,"#splitline{Comb. iso. #Delta#beta corr.}{Loose WP}");

  gr_ttH_byLooseCombdR03->SetLineColor(3);
  gr_ttH_byLooseCombdR03->SetMarkerColor(3);  
  gr_ttH_byLooseCombdR03->SetLineWidth(2);
  gr_ttH_byLooseCombdR03->SetFillColor(0);
  leg->AddEntry(gr_ttH_byLooseCombdR03,"#splitline{Comb. iso. #Delta#beta corr.}{#DeltaR0.3 Loose WP}");

  gr_ttH_byLooseMVAdR03->SetLineColor(4);
  gr_ttH_byLooseMVAdR03->SetMarkerColor(4);  
  gr_ttH_byLooseMVAdR03->SetLineWidth(2);
  gr_ttH_byLooseMVAdR03->SetFillColor(0);
  leg->AddEntry(gr_ttH_byLooseMVAdR03,"#splitline{MVA iso. #DeltaR0.3}{Loose WP}");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  gr_ttH->GetXaxis()->SetRangeUser(0,19);
  gr_ttH->GetYaxis()->SetRangeUser(0,1);
  gr_ttH->GetXaxis()->SetTitle("iso. [GeV]");
  gr_ttH->GetYaxis()->SetTitle("TauID efficiecy");
  gr_ttH->GetYaxis()->SetTitleOffset(1.65);
  gr_ttH->SetTitle("");

  gr_ttH->Draw("APL");
  gr_ttH_byLooseComb->Draw("PLsame");
  gr_ttH_byLooseCombdR03->Draw("PLsame");
  gr_ttH_byLooseMVAdR03->Draw("PLsame");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.5,1.02,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="iso_tauh_efficiency_ttH_dRveto_76X";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}












void plot_iso_tauh_significance_76X(){

  TString filename_root="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_dRveto_gen_iso70.root";

  TH1F* h_sig = single_plot(filename_root,"HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpart_i_closest_daughter]","MC_weight*PUReweight*( abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && genpart_pt>30 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",200,0,20);
  TH1F* h_sig_byLooseComb = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && (tauID[genpart_i_closest_daughter]>>3)&1 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",3,0,3);
  TH1F* h_sig_byLooseCombdR03 = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && (tauID[genpart_i_closest_daughter]>>21)&1 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",3,0,3);
  TH1F* h_sig_byLooseMVAdR03 = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && (tauID[genpart_i_closest_daughter]>>24)&1 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",3,0,3);

  TH1F* h_sig_denom = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",3,0,3);

  TH1F* h_bkg = single_plot(filename_root,"HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpart_i_closest_daughter]","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",200,0,20);
  TH1F* h_bkg_byLooseComb = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && (tauID[genpart_i_closest_daughter]>>3)&1 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",3,0,3);
  TH1F* h_bkg_byLooseCombdR03 = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && (tauID[genpart_i_closest_daughter]>>21)&1 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",3,0,3);
  TH1F* h_bkg_byLooseMVAdR03 = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && (tauID[genpart_i_closest_daughter]>>24)&1 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",3,0,3);

  TH1F* h_bkg_denom = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",3,0,3);

  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;

  double n_sig_acc_byLooseComb=h_sig_byLooseComb->Integral();
  double n_bkg_acc_byLooseComb=h_bkg_byLooseComb->Integral();
  double signif_byLooseComb=n_sig_acc_byLooseComb/sqrt(n_sig_acc_byLooseComb+n_bkg_acc_byLooseComb);
  cout<<"byLooseComb S/v(S+B)="<<signif_byLooseComb<<endl;

  double n_sig_acc_byLooseCombdR03=h_sig_byLooseCombdR03->Integral();
  double n_bkg_acc_byLooseCombdR03=h_bkg_byLooseCombdR03->Integral();
  double signif_byLooseCombdR03=n_sig_acc_byLooseCombdR03/sqrt(n_sig_acc_byLooseCombdR03+n_bkg_acc_byLooseCombdR03);
  cout<<"byLooseCombdR03 S/v(S+B)="<<signif_byLooseCombdR03<<endl;


  double n_sig_acc_byLooseMVAdR03=h_sig_byLooseMVAdR03->Integral();
  double n_bkg_acc_byLooseMVAdR03=h_bkg_byLooseMVAdR03->Integral();
  double signif_byLooseMVAdR03=n_sig_acc_byLooseMVAdR03/sqrt(n_sig_acc_byLooseMVAdR03+n_bkg_acc_byLooseMVAdR03);
  cout<<"byLooseMVAdR03 S/v(S+B)="<<signif_byLooseMVAdR03<<endl;



  TGraphErrors* gr=new TGraphErrors();
  TGraphErrors* gr_byLooseComb=new TGraphErrors();
  TGraphErrors* gr_byLooseCombdR03=new TGraphErrors();
  TGraphErrors* gr_byLooseMVAdR03=new TGraphErrors();

  int binlow_sig=h_sig->FindBin(0);
  int binlow_bkg=h_bkg->FindBin(0);

  int n=0;

  for(double x=0.1;x<20;x+=0.1){
    int binup_sig=h_sig->FindBin(x);
    int binup_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);
    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;

    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    gr->SetPoint(n,x,n_sig_acc/sqrt(n_sig_acc+n_bkg_acc));
    gr_byLooseComb->SetPoint(n,x,signif_byLooseComb);
    gr_byLooseCombdR03->SetPoint(n,x,signif_byLooseCombdR03);
    gr_byLooseMVAdR03->SetPoint(n,x,signif_byLooseMVAdR03);
      
    n++;

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
 
  gr_byLooseMVAdR03->GetXaxis()->SetTitle("iso. [GeV]");
  gr_byLooseMVAdR03->GetYaxis()->SetTitle("S/#sqrt{S+B} [arbitrary scale]");
  gr_byLooseMVAdR03->GetYaxis()->SetTitleOffset(1.6);
  gr_byLooseMVAdR03->GetYaxis()->SetRangeUser(900.,1750.);

  
  gr->SetLineWidth(2);
  gr->SetFillColor(0);

  gr_byLooseComb->SetLineColor(2);
  gr_byLooseComb->SetLineWidth(2);
  gr_byLooseComb->SetFillColor(0);

  gr_byLooseCombdR03->SetLineColor(3);
  gr_byLooseCombdR03->SetLineWidth(2);
  gr_byLooseCombdR03->SetFillColor(0);

  gr_byLooseMVAdR03->SetLineColor(4);
  gr_byLooseMVAdR03->SetLineWidth(2);
  gr_byLooseMVAdR03->SetFillColor(0);



  gr_byLooseMVAdR03->Draw("APL");
  gr_byLooseComb->Draw("samePL");
  gr_byLooseCombdR03->Draw("samePL");
  gr->Draw("samePL");

  TLegend* leg=new TLegend(0.47,0.13,0.85,0.51);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  leg->AddEntry(gr,"Comb. iso. #Delta#beta corr. raw");
  leg->AddEntry(gr_byLooseComb,"#splitline{Comb. iso. #Delta#beta corr.}{Loose WP}");
  leg->AddEntry(gr_byLooseCombdR03,"#splitline{Comb. iso. #Delta#beta corr.}{#DeltaR0.3 Loose WP}");
  leg->AddEntry(gr_byLooseMVAdR03,"#splitline{MVA iso. #DeltaR0.3}{Loose WP}");
  leg->Draw("same");
  

  TLatex *texl = new TLatex(0.5,1752,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="iso_tauh_significance_ttH_dRveto_76X";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}










void plot_iso_tauh_significance_MVAdR03_76X(){

  TString filename_root="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_dRveto_gen_iso70.root";

  TH1F* h_sig = single_plot(filename_root,"HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpart_i_closest_daughter]","MC_weight*PUReweight*( abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && genpart_pt>30 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",200,0,20);
  TH1F* h_sig_byLooseMVAdR03 = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && (tauID[genpart_i_closest_daughter]>>24)&1 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",3,0,3);
  TH1F* h_sig_byMediumMVAdR03 = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && (tauID[genpart_i_closest_daughter]>>25)&1 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",3,0,3);
  TH1F* h_sig_byTightMVAdR03 = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && (tauID[genpart_i_closest_daughter]>>26)&1 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",3,0,3);
  TH1F* h_sig_denom = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",3,0,3);

  TH1F* h_bkg = single_plot(filename_root,"HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpart_i_closest_daughter]","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",200,0,20);
  TH1F* h_bkg_byLooseMVAdR03 = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && (tauID[genpart_i_closest_daughter]>>24)&1 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",3,0,3);
  TH1F* h_bkg_byMediumMVAdR03 = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && (tauID[genpart_i_closest_daughter]>>25)&1 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",3,0,3);
  TH1F* h_bkg_byTightMVAdR03 = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && daughters_decayModeFindingOldDMs[genpart_i_closest_daughter]>0.5 && (tauID[genpart_i_closest_daughter]>>26)&1 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",3,0,3);

  TH1F* h_bkg_denom = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",3,0,3);

  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;

  double n_sig_acc_byLooseMVAdR03=h_sig_byLooseMVAdR03->Integral();
  double n_bkg_acc_byLooseMVAdR03=h_bkg_byLooseMVAdR03->Integral();
  double signif_byLooseMVAdR03=n_sig_acc_byLooseMVAdR03/sqrt(n_sig_acc_byLooseMVAdR03+n_bkg_acc_byLooseMVAdR03);
  cout<<"byLooseMVAdR03 S/v(S+B)="<<signif_byLooseMVAdR03<<endl;

  double n_sig_acc_byMediumMVAdR03=h_sig_byMediumMVAdR03->Integral();
  double n_bkg_acc_byMediumMVAdR03=h_bkg_byMediumMVAdR03->Integral();
  double signif_byMediumMVAdR03=n_sig_acc_byMediumMVAdR03/sqrt(n_sig_acc_byMediumMVAdR03+n_bkg_acc_byMediumMVAdR03);
  cout<<"byMediumMVAdR03 S/v(S+B)="<<signif_byMediumMVAdR03<<endl;

  double n_sig_acc_byTightMVAdR03=h_sig_byTightMVAdR03->Integral();
  double n_bkg_acc_byTightMVAdR03=h_bkg_byTightMVAdR03->Integral();
  double signif_byTightMVAdR03=n_sig_acc_byTightMVAdR03/sqrt(n_sig_acc_byTightMVAdR03+n_bkg_acc_byTightMVAdR03);
  cout<<"byTightMVAdR03 S/v(S+B)="<<signif_byTightMVAdR03<<endl;


  TGraphErrors* gr=new TGraphErrors();
  TGraphErrors* gr_byLooseMVAdR03=new TGraphErrors();
  TGraphErrors* gr_byMediumMVAdR03=new TGraphErrors();
  TGraphErrors* gr_byTightMVAdR03=new TGraphErrors();

  int binlow_sig=h_sig->FindBin(0);
  int binlow_bkg=h_bkg->FindBin(0);

  int n=0;

  for(double x=0.1;x<20;x+=0.1){
    int binup_sig=h_sig->FindBin(x);
    int binup_bkg=h_bkg->FindBin(x);

    double n_sig_acc=h_sig->Integral(binlow_sig,binup_sig);
    double n_bkg_acc=h_bkg->Integral(binlow_bkg,binup_bkg);
    double sigeff=n_sig_acc/N_sig;
    double bkgfake=n_bkg_acc/N_bkg;

    double ex=sqrt(sigeff*(1-sigeff)/N_sig);
    double ey=sqrt(bkgfake*(1-bkgfake)/N_bkg);

    gr->SetPoint(n,x,n_sig_acc/sqrt(n_sig_acc+n_bkg_acc));
    gr_byLooseMVAdR03->SetPoint(n,x,signif_byLooseMVAdR03);
    gr_byMediumMVAdR03->SetPoint(n,x,signif_byMediumMVAdR03);
    gr_byTightMVAdR03->SetPoint(n,x,signif_byTightMVAdR03);
      
    n++;

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
 
  gr_byLooseMVAdR03->GetXaxis()->SetTitle("iso. [GeV]");
  gr_byLooseMVAdR03->GetYaxis()->SetTitle("S/#sqrt{S+B} [arbitrary scale]");
  gr_byLooseMVAdR03->GetYaxis()->SetTitleOffset(1.6);
  gr_byLooseMVAdR03->GetYaxis()->SetRangeUser(900.,1750.);

  
  gr->SetLineWidth(2);
  gr->SetFillColor(0);

  gr_byLooseMVAdR03->SetLineColor(2);
  gr_byLooseMVAdR03->SetLineWidth(2);
  gr_byLooseMVAdR03->SetFillColor(0);

  gr_byMediumMVAdR03->SetLineColor(3);
  gr_byMediumMVAdR03->SetLineWidth(2);
  gr_byMediumMVAdR03->SetFillColor(0);

  gr_byTightMVAdR03->SetLineColor(4);
  gr_byTightMVAdR03->SetLineWidth(2);
  gr_byTightMVAdR03->SetFillColor(0);

  gr_byLooseMVAdR03->Draw("APL");
  gr_byMediumMVAdR03->Draw("samePL");
  gr_byTightMVAdR03->Draw("samePL");
  gr->Draw("samePL");

  TLegend* leg=new TLegend(0.47,0.13,0.85,0.51);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  leg->AddEntry(gr,"Comb. iso. #Delta#beta corr. raw");
  leg->AddEntry(gr_byLooseMVAdR03,"#splitline{MVA iso. #DeltaR0.3}{Loose WP}");
  leg->AddEntry(gr_byMediumMVAdR03,"#splitline{MVA iso. #DeltaR0.3}{Medium WP}");
  leg->AddEntry(gr_byTightMVAdR03,"#splitline{MVA iso. #DeltaR0.3}{Tight WP}");
  leg->Draw("same");
  

  TLatex *texl = new TLatex(0.5,1752,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="iso_tauh_significance_ttH_dRveto_MVAdR03_76X";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}


