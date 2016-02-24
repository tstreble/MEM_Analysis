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


void plot_iso_tauh(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_iso15.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpart_i_closest_daughter]","PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",50,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_iso15.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpart_i_closest_daughter]","PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)<6)",50,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_iso15.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpart_i_closest_daughter]","PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)==21)",50,0,20));


  vector<TString> leg_entry;
  leg_entry.push_back("#tau_{h}");
  leg_entry.push_back("Quark");
  leg_entry.push_back("Gluon");


  TLegend* leg=new TLegend(0.47,0.55,0.85,0.85);
  leg->SetHeader("#splitline{p_{T}>30 GeV , |#eta|<2.1}{gen. + reco., #DeltaR<0.3}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
    h[i]->SetMarkerSize(0);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLogy();
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  //h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("iso. [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");

  TLatex *texl = new TLatex(0.5,1.24*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="iso_tauh_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_iso_tauh_significance(){

  TH1F* h_sig = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_iso15.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpart_i_closest_daughter]","PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",200,0,20);
  TH1F* h_sig_denom = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_iso15.root","HTauTauTree","1","PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",3,0,3);

  TH1F* h_bkg = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_iso15.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpart_i_closest_daughter]","PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",200,0,20);
  TH1F* h_bkg_denom = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_iso15.root","HTauTauTree","1","PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",3,0,3);

  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;

  TGraphErrors* gr=new TGraphErrors();
  
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
      
    //ROC->SetPointError(n,ex,ey);
    n++;

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
 
  gr->GetXaxis()->SetTitle("iso. [GeV]");
  gr->GetYaxis()->SetTitle("S/#sqrt{S+B} [arbitrary scale]");
  gr->GetYaxis()->SetTitleOffset(1.6);
  gr->SetLineWidth(2);

  gr->Draw("APL");

  TLatex *texl = new TLatex(0.5,1250,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="iso_tauh_significance_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_iso_tauh_significance_new(){

  TString filename_root="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_12_2015/ntuple_ttH_dRveto_gen_iso70.root";

  TH1F* h_sig = single_plot(filename_root,"HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpart_i_closest_daughter]","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",200,0,20);
  TH1F* h_sig_denom = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && abs(genpart_pdg)>1000)",3,0,3);

  TH1F* h_bkg = single_plot(filename_root,"HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpart_i_closest_daughter]","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",200,0,20);
  TH1F* h_bkg_denom = single_plot(filename_root,"HTauTauTree","1","MC_weight*PUReweight*(genpart_pt>30 && abs(genpart_eta)<2.1 && genpart_dR_closest_daughter<0.3 && abs(PDGIdDaughters[genpart_i_closest_daughter])==15 && daughters_pt[genpart_i_closest_daughter]>30 && abs(daughters_eta[genpart_i_closest_daughter])<2.1 && (abs(genpart_pdg)<6 || abs(genpart_pdg)==21))",3,0,3);

  double N_sig=h_sig_denom->Integral();
  cout<<"N_sig="<<N_sig<<endl;
  double N_bkg=h_bkg_denom->Integral();
  cout<<"N_bkg="<<N_bkg<<endl;

  TGraphErrors* gr=new TGraphErrors();
  
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
      
    //ROC->SetPointError(n,ex,ey);
    n++;

  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
 
  gr->GetXaxis()->SetTitle("iso. [GeV]");
  gr->GetYaxis()->SetTitle("S/#sqrt{S+B} [arbitrary scale]");
  gr->GetYaxis()->SetTitleOffset(1.6);
  gr->SetLineWidth(2);

  gr->Draw("APL");

  TLatex *texl = new TLatex(0.5,1272,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");



  TString filename="iso_tauh_significance_ttH_dRveto_new";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void plot_efficiency_iso_tauh(){

  TH1F* h_VBF = single_plot("/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen_skimmed.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",400,0,160);
  h_VBF->Scale(1/h_VBF->Integral(0,401));

  TH1F* h_ttH = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",400,0,160);
  h_ttH->Scale(1/h_ttH->Integral(0,401));



  TLegend* leg=new TLegend(0.47,0.55,0.85,0.85);
  leg->SetHeader("#splitline{p_{T}>30 GeV , |#eta|<2.1}{gen. + reco., #DeltaR<0.3}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  TGraphErrors* gr_VBF=new TGraphErrors();
  TGraphErrors* gr_ttH=new TGraphErrors();

  int bin_down=h_VBF->FindBin(0);
  int i=0;

  for(float iso=0; iso<161; iso+=0.5){

    int bin_up=h_VBF->FindBin(iso);
    float eff_VBF=h_VBF->Integral(bin_down,bin_up);
    float eff_ttH=h_ttH->Integral(bin_down,bin_up);

    gr_VBF->SetPoint(i,iso,eff_VBF);
    gr_ttH->SetPoint(i,iso,eff_ttH);
    i++;

  }

  gr_VBF->SetLineColor(1);
  gr_VBF->SetMarkerColor(1);  
  gr_VBF->SetLineWidth(2);
  gr_VBF->SetFillColor(0);
  leg->AddEntry(gr_VBF,"VBF");

  gr_ttH->SetLineColor(2);
  gr_ttH->SetMarkerColor(2);  
  gr_ttH->SetLineWidth(2);
  gr_ttH->SetFillColor(0);
  leg->AddEntry(gr_ttH,"ttH");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  gr_VBF->GetYaxis()->SetRangeUser(0,1);
  gr_VBF->GetXaxis()->SetRangeUser(0,160);
  gr_VBF->GetXaxis()->SetTitle("iso. [GeV]");
  gr_VBF->GetYaxis()->SetTitle("TauID efficiecy");
  gr_VBF->GetYaxis()->SetTitleOffset(1.65);
  gr_VBF->SetTitle("");

  gr_VBF->Draw("APL");
  gr_ttH->Draw("PLsame");
  leg->Draw("same");


  TString filename="iso_tauh_efficiency_VBF_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_efficiency_iso_tauh_zoom(){

  TH1F* h_VBF = single_plot("/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen_skimmed.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",200,0,20);
  h_VBF->Scale(1/h_VBF->Integral(0,201));

  TH1F* h_ttH = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",200,0,20);
  h_ttH->Scale(1/h_ttH->Integral(0,201));



  TLegend* leg=new TLegend(0.47,0.25,0.85,0.5);
  leg->SetHeader("#splitline{p_{T}>30 GeV , |#eta|<2.1}{gen. + reco., #DeltaR<0.3}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  TGraphErrors* gr_VBF=new TGraphErrors();
  TGraphErrors* gr_ttH=new TGraphErrors();

  int bin_down=h_VBF->FindBin(0);
  int i=0;

  for(float iso=0; iso<21; iso+=0.1){

    int bin_up=h_VBF->FindBin(iso);
    float eff_VBF=h_VBF->Integral(bin_down,bin_up);
    float eff_ttH=h_ttH->Integral(bin_down,bin_up);

    gr_VBF->SetPoint(i,iso,eff_VBF);
    gr_ttH->SetPoint(i,iso,eff_ttH);
    i++;

    if(iso==1.5){
      cout<<eff_VBF<<endl;
      cout<<eff_ttH<<endl;
    }

  }

  gr_VBF->SetLineColor(1);
  gr_VBF->SetMarkerColor(1);  
  gr_VBF->SetLineWidth(2);
  gr_VBF->SetFillColor(0);
  leg->AddEntry(gr_VBF,"VBF");

  gr_ttH->SetLineColor(2);
  gr_ttH->SetMarkerColor(2);  
  gr_ttH->SetLineWidth(2);
  gr_ttH->SetFillColor(0);
  leg->AddEntry(gr_ttH,"ttH");

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  gr_VBF->GetXaxis()->SetRangeUser(0,19);
  gr_VBF->GetYaxis()->SetRangeUser(0,1);
  gr_VBF->GetXaxis()->SetTitle("iso. [GeV]");
  gr_VBF->GetYaxis()->SetTitle("TauID efficiecy");
  gr_VBF->GetYaxis()->SetTitleOffset(1.65);
  gr_VBF->SetTitle("");

  gr_VBF->Draw("APL");
  gr_ttH->Draw("PLsame");
  leg->Draw("same");

  TLatex *texl = new TLatex(0.5,1.02,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="iso_tauh_efficiency_VBF_ttH_dRveto_zoom";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}

