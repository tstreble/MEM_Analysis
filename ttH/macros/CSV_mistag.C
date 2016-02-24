#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TH3F.h>
#include <iostream>
#include <TLegend.h>
#include <TBranch.h>
#include <TClonesArray.h>
#include <TChain.h>
#include <TMath.h>
#include <TF1.h>
//#include "Helpers.C"
#include <TSystem.h>
#include <TLatex.h>
#include <TGraphErrors.h>
#include "Helpers_ROCcurve.C"

using namespace std;




void plot_CSV(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","recoPFJet30_CSVscore","abs(genpart_pdg[recoPFJet30_i_closest_genpart])==5 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30",50,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","recoPFJet30_CSVscore","(abs(genpart_pdg[recoPFJet30_i_closest_genpart])<4 || abs(genpart_pdg[recoPFJet30_i_closest_genpart])==21) && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30",50,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","recoPFJet30_CSVscore","abs(genpart_pdg[recoPFJet30_i_closest_genpart])==4 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30",50,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","recoPFJet30_CSVscore","abs(genpart_pdg[recoPFJet30_i_closest_genpart])>1000 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30",50,0,1));

  vector<TString> leg_entry;
  leg_entry.push_back("b quarks");
  leg_entry.push_back("udsg");
  leg_entry.push_back("c quarks");
  leg_entry.push_back("#tau_{h}");


  TLegend* leg=new TLegend(0.25,0.45,0.85,0.85);
  leg->SetHeader("#splitline{p_{T}(jet)>30 GeV, |#eta(jet)|<3}{#DeltaR(gen,jet)<0.3, p_{T}(gen)>30 GeV}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetBinContent(1,h[i]->GetBinContent(0)+h[i]->GetBinContent(1));
    h[i]->SetBinContent(100,h[i]->GetBinContent(100)+h[i]->GetBinContent(101));
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    //h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("CSVv2 b-tagger");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of objects / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("ttH, H->#tau#tau events");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="CSV_ttH_dRveto_gen";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_CSV_tauDM(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","recoPFJet30_CSVscore","abs(genpart_pdg[recoPFJet30_i_closest_genpart])==5 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30",50,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","recoPFJet30_CSVscore","recoPFJet30_dR_closest_tau<0.3 && recotauh_pt[recoPFJet30_i_closest_tau]>30 && recotauh_decayMode[recoPFJet30_i_closest_tau]==0 && abs(genpart_pdg[recoPFJet30_i_closest_genpart])>1000 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30",50,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","recoPFJet30_CSVscore","recoPFJet30_dR_closest_tau<0.3 && recotauh_pt[recoPFJet30_i_closest_tau]>30 && recotauh_decayMode[recoPFJet30_i_closest_tau]==1 && abs(genpart_pdg[recoPFJet30_i_closest_genpart])>1000 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30",50,0,1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","recoPFJet30_CSVscore","recoPFJet30_dR_closest_tau<0.3 && recotauh_pt[recoPFJet30_i_closest_tau]>30 && recotauh_decayMode[recoPFJet30_i_closest_tau]==10 && abs(genpart_pdg[recoPFJet30_i_closest_genpart])>1000 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30",50,0,1));
 

  vector<TString> leg_entry;
  leg_entry.push_back("b quarks");
  leg_entry.push_back("#tau_{h} 1 prong");
  leg_entry.push_back("#tau_{h} 1 prong + #pi^{0}'s");
  leg_entry.push_back("#tau_{h} 3 prongs");


  TLegend* leg=new TLegend(0.25,0.45,0.85,0.85);
  leg->SetHeader("#splitline{p_{T}(jet)>30 GeV, |#eta(jet)|<3}{#DeltaR(gen,#tau_{h})<0.3, p_{T}(#tau_{h})>30 GeV}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetBinContent(1,h[i]->GetBinContent(0)+h[i]->GetBinContent(1));
    h[i]->SetBinContent(100,h[i]->GetBinContent(100)+h[i]->GetBinContent(101));
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    //h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("CSVv2 b-tagger");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of objects / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("ttH, H->#tau#tau events");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="CSV_ttH_dRveto_gen_tauDM";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}



void plot_ROC_CSV(){

  TString file="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root";

  TString cut_sig="abs(genpart_pdg[recoPFJet30_i_closest_genpart])==5 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30";

  vector<TString> cuts_bkg;
  cuts_bkg.push_back("(abs(genpart_pdg[recoPFJet30_i_closest_genpart])<4 || abs(genpart_pdg[recoPFJet30_i_closest_genpart])==21) && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30");
  cuts_bkg.push_back("(abs(genpart_pdg[recoPFJet30_i_closest_genpart])==4) && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30");
  cuts_bkg.push_back("abs(genpart_pdg[recoPFJet30_i_closest_genpart])>1000 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30 && recoPFJet30_dR_closest_tau<0.3 && recotauh_pt[recoPFJet30_i_closest_tau]>30 && recotauh_decayMode[recoPFJet30_i_closest_tau]==0");
  cuts_bkg.push_back("abs(genpart_pdg[recoPFJet30_i_closest_genpart])>1000 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30 && recoPFJet30_dR_closest_tau<0.3 && recotauh_pt[recoPFJet30_i_closest_tau]>30 && recotauh_decayMode[recoPFJet30_i_closest_tau]==1");
  cuts_bkg.push_back("abs(genpart_pdg[recoPFJet30_i_closest_genpart])>1000 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30 && recoPFJet30_dR_closest_tau<0.3 && recotauh_pt[recoPFJet30_i_closest_tau]>30 && recotauh_decayMode[recoPFJet30_i_closest_tau]==10");

  vector<TGraphErrors*> ROC;
  for(unsigned int i=0; i<cuts_bkg.size();i++)
    ROC.push_back(get_ROC_CSV(file,file,"HTauTauTree",cut_sig,cut_sig,cuts_bkg[i],cuts_bkg[i],100,true));
		  
  vector<TString> leg_entry;
  leg_entry.push_back("udsg");
  leg_entry.push_back("c quarks");
  leg_entry.push_back("#tau_{h} 1 prong");
  leg_entry.push_back("#tau_{h} 1 prong + #pi^{0}'s");
  leg_entry.push_back("#tau_{h} 3 prongs");

  TLegend* leg=new TLegend(0.2,0.6,0.45,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0;i<ROC.size();i++){
    ROC[i]->SetLineColor(i+1);
    if(i>3)
      ROC[i]->SetLineColor(i+2);
    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->GetXaxis()->SetTitle("Signal efficiency");
  ROC[0]->GetYaxis()->SetTitle("Mistag rate");
    
  ROC[0]->GetYaxis()->SetTitleOffset(1.7);
  ROC[0]->SetMinimum(0.0001);
  //ROC[0]->SetTitle("ROC curves");
  ROC[0]->SetMaximum(1);
  
  
  vector<TString> CSV_WP_cuts;
  CSV_WP_cuts.push_back(" && recoPFJet30_CSVscore>0.423");
  CSV_WP_cuts.push_back(" && recoPFJet30_CSVscore>0.814");
  CSV_WP_cuts.push_back(" && recoPFJet30_CSVscore>0.941");

  
  vector<TString> leg_entry2;
  leg_entry2.push_back("Loose WP");
  leg_entry2.push_back("Medium WP");
  leg_entry2.push_back("Tight WP");


  TLegend* leg2=new TLegend(0.63,0.13,0.87,0.38);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.04);
  leg2->SetFillColor(0);

  vector<TGraphErrors*> CSV_WP;
  float Nsig=single_plot(file,"HTauTauTree","1",cut_sig,3,0,3)->Integral();

  for(unsigned int i=0; i<CSV_WP_cuts.size(); i++){

    float nsig_acc=single_plot(file,"HTauTauTree","1",cut_sig+CSV_WP_cuts[i],3,0,3)->Integral();
    float sigeff=nsig_acc/Nsig;

    for(unsigned int j=0; j<ROC.size(); j++){

      float Nbkg=single_plot(file,"HTauTauTree","1",cuts_bkg[j],3,0,3)->Integral();
      float nbkg_acc=single_plot(file,"HTauTauTree","1",cuts_bkg[j]+CSV_WP_cuts[i],3,0,3)->Integral();
      float mistag_rate=nbkg_acc/Nbkg;

      cout<<sigeff<<" , "<<mistag_rate<<endl;
      
      TGraphErrors* WP=new TGraphErrors();
      WP->SetPoint(0,sigeff,mistag_rate);
      WP->SetMarkerColor(ROC[j]->GetLineColor());
      WP->SetMarkerStyle(20+i);
      WP->SetMarkerSize(1.7);
      WP->SetFillColor(0);
      CSV_WP.push_back(WP);
      if(j==0)
	leg2->AddEntry(WP,leg_entry2[i]);

    }

  }
      

 


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  gPad->SetTickx();
  gPad->SetTicky();

  ROC[0]->GetXaxis()->SetLimits(0.,1.);


  ROC[0]->Draw();
  for(unsigned int i=1; i<ROC.size();i++){
    ROC[i]->Draw("same");
  }
  for(unsigned int i=0; i<CSV_WP.size();i++){
    CSV_WP[i]->Draw("sameP");
  }

  leg->Draw("same");
  leg2->Draw("same");

  TLatex *texl = new TLatex(30,0.051,"CMS #bf{#it{Simulation 13 TeV t#bar{t}}H, H->#tau#tau}");
  texl->SetTextSize(0.04);
  texl->Draw("same");  

  TString filename="ROC_CSV_tau";
  filename+="_log";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_CSV_mistag_rate_pt(){

  TString file="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root"; 

  vector<TString> cuts_bkg;
  cuts_bkg.push_back("(abs(genpart_pdg[recoPFJet30_i_closest_genpart])<4 || abs(genpart_pdg[recoPFJet30_i_closest_genpart])==21) && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30");
  cuts_bkg.push_back("(abs(genpart_pdg[recoPFJet30_i_closest_genpart])==4) && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30");
  cuts_bkg.push_back("abs(genpart_pdg[recoPFJet30_i_closest_genpart])>1000 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30 && recoPFJet30_dR_closest_tau<0.3 && recotauh_pt[recoPFJet30_i_closest_tau]>30 && recotauh_decayMode[recoPFJet30_i_closest_tau]==0");
  cuts_bkg.push_back("abs(genpart_pdg[recoPFJet30_i_closest_genpart])>1000 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30 && recoPFJet30_dR_closest_tau<0.3 && recotauh_pt[recoPFJet30_i_closest_tau]>30 && recotauh_decayMode[recoPFJet30_i_closest_tau]==1");
  cuts_bkg.push_back("abs(genpart_pdg[recoPFJet30_i_closest_genpart])>1000 && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30 && recoPFJet30_dR_closest_tau<0.3 && recotauh_pt[recoPFJet30_i_closest_tau]>30 && recotauh_decayMode[recoPFJet30_i_closest_tau]==10");

  vector<TH1F*> h_denom;
  for(unsigned int i=0;i<cuts_bkg.size();i++)
    h_denom.push_back(single_plot(file,"HTauTauTree","recoPFJet30_pt",cuts_bkg[i] + "&& recoPFJet30_pt<200",18,20,200));


  vector<TH1F*> h;
  for(unsigned int i=0;i<cuts_bkg.size();i++)
    h.push_back(single_plot(file,"HTauTauTree","recoPFJet30_pt",cuts_bkg[i] + " && recoPFJet30_CSVscore>0.814 && recoPFJet30_pt<200",18,20,200));


  TLegend* leg=new TLegend(0.35,0.15,0.65,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("udsg");
  leg_entry.push_back("c quarks");
  leg_entry.push_back("#tau_{h} 1 prong");
  leg_entry.push_back("#tau_{h} 1 prong + #pi^{0}'s");
  leg_entry.push_back("#tau_{h} 3 prongs");

  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",18,20,200));
    h_eff[i]->Divide(h[i],h_denom[i]);
    h_eff[i]->SetLineColor(i+1);
    h_eff[i]->SetMarkerColor(i+1);
    if(i>3){
      h_eff[i]->SetLineColor(i+2);
      h_eff[i]->SetMarkerColor(i+2);
    }
    h_eff[i]->SetMarkerStyle(20+i);
    h_eff[i]->SetLineWidth(2);
    h_eff[i]->SetStats(0);
    leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  h_eff[0]->SetMaximum(1);
  h_eff[0]->SetMinimum(0.001);
  h_eff[0]->GetXaxis()->SetRangeUser(20,210);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}(jet) [GeV]");
  h_eff[0]->GetYaxis()->SetTitle("Mistag rate");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(25,1.2,"CMS #bf{#it{Simulation 13 TeV ttH, H->#tau#tau}}");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="mistag_rate_CSV_ttH_pt";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}








void plot_CSV_mistag_rate_pt_new(){

  TString file="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root"; 

  vector<TString> cuts_bkg;
  cuts_bkg.push_back("(abs(genpart_pdg[recoPFJet30_i_closest_genpart])==5) && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30");
  cuts_bkg.push_back("(abs(genpart_pdg[recoPFJet30_i_closest_genpart])>1000) && recoPFJet30_dR_closest_genpart<0.3 && genpart_pt[recoPFJet30_i_closest_genpart]>30");



  vector<TH1F*> h_denom;
  for(unsigned int i=0;i<cuts_bkg.size();i++){
    h_denom.push_back(single_plot(file,"HTauTauTree","recoPFJet30_pt",cuts_bkg[i] + "&& recoPFJet30_pt<200",18,20,200));
    h_denom.push_back(single_plot(file,"HTauTauTree","recoPFJet30_pt",cuts_bkg[i] + "&& recoPFJet30_pt<200",18,20,200));
  }


  vector<TH1F*> h;
  for(unsigned int i=0;i<cuts_bkg.size();i++){
    h.push_back(single_plot(file,"HTauTauTree","recoPFJet30_pt",cuts_bkg[i] + " && recoPFJet30_CSVscore>0.814 && recoPFJet30_pt<200",18,20,200));
    h.push_back(single_plot(file,"HTauTauTree","recoPFJet30_pt",cuts_bkg[i] + " && recoPFJet30_CSVscore>0.814 && recoPFJet30_dR_closest_tau>0.5 && recoPFJet30_pt<200",18,20,200));
  }


  TLegend* leg=new TLegend(0.35,0.15,0.65,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("b quark");
  leg_entry.push_back("b quark + #tau veto");
  leg_entry.push_back("#tau");
  leg_entry.push_back("#tau + #tau veto");

  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",18,20,200));
    h_eff[i]->Divide(h[i],h_denom[i]);
    h_eff[i]->SetLineColor(i+1);
    h_eff[i]->SetMarkerColor(i+1);
    if(i>3){
      h_eff[i]->SetLineColor(i+2);
      h_eff[i]->SetMarkerColor(i+2);
    }
    h_eff[i]->SetMarkerStyle(20+i);
    h_eff[i]->SetLineWidth(2);
    h_eff[i]->SetStats(0);
    leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  h_eff[0]->SetMaximum(1);
  h_eff[0]->SetMinimum(0.001);
  h_eff[0]->GetXaxis()->SetRangeUser(20,210);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}(jet) [GeV]");
  h_eff[0]->GetYaxis()->SetTitle("Mistag rate");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(25,1.2,"CMS #bf{#it{Simulation 13 TeV ttH, H->#tau#tau}}");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="mistag_rate_CSV_ttH_pt_new";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}



