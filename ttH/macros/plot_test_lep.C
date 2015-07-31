#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <Helpers.C>
#include <vector>

using namespace std;



void plot_n_lep(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","n_recolep","",10,0,10));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","n_genlep20_eta21","",10,0,10));
 
  vector<TString> leg_entry;
  leg_entry.push_back("Reco");
  leg_entry.push_back("Gen");

  TLegend* leg=new TLegend(0.5,0.65,0.85,0.85);
  leg->SetHeader("p_{T}>20 GeV, |#eta|<2.1");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("n(lep)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Number of leptons");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_lep_ttH_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_dR_lep_match(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","genlt_dR_daughter_matched","PUReweight*(genlt_pt>20 && abs(genlt_eta)<2.1 && genlt_i_daughter_matched>-1 && daughters_pt[genlt_i_daughter_matched]>20 && abs(daughters_eta[genlt_i_daughter_matched])<2.1)",50,0,0.1));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","genltau_dR_daughter_matched","PUReweight*(genltau_pt>20 && abs(genltau_eta)<2.1 && genltau_i_daughter_matched>-1 && daughters_pt[genltau_i_daughter_matched]>20 && abs(daughters_eta[genltau_i_daughter_matched])<2.1)",50,0,0.1));


  
  vector<TString> leg_entry;
  leg_entry.push_back("Lepton from top");
  leg_entry.push_back("Lepton from #tau");

  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
  leg->SetHeader("p_{T}>20 GeV, |#eta|<2.1 gen. + reco.");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("#DeltaR(gen,reco)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("ttH, t->bqq, t->bl#nu, H->l#tau_{h} events");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="dR_lep_matched_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_quality_lep_match(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","combreliso[genlt_i_daughter_matched]<0.1","PUReweight*(genlt_pt>20 && abs(genlt_eta)<2.1 && genlt_dR_daughter_matched<0.3 && daughters_pt[genlt_i_daughter_matched]>20 && abs(daughters_eta[genlt_i_daughter_matched])<2.1)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","combreliso[genltau_i_daughter_matched]<0.1","PUReweight*(genltau_pt>20 && abs(genltau_eta)<2.1 && genltau_dR_daughter_matched<0.3 && daughters_pt[genltau_i_daughter_matched]>20 && abs(daughters_eta[genltau_i_daughter_matched])<2.1)",5,0,5));
  
  vector<TString> leg_entry;
  leg_entry.push_back("Iso. lepton from top");
  leg_entry.push_back("Iso. lepton from #tau");


  TLegend* leg=new TLegend(0.47,0.3,0.85,0.75);
  leg->SetHeader("#splitline{p_{T}>20 GeV, |#eta|<2.1}{gen + reco #DeltaR<0.3}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    if(i>3)
      h[i]->SetLineColor(i+2);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("flag");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("ttH, t->bqq, t->bl#nu, H->l#tau_{h} events");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="quality_lep_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_iso_lep_match(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen_skimmed.root","HTauTauTree","combreliso[genltau_i_daughter_matched]","PUReweight*(genltau_pt>30 && abs(genltau_eta)<2.1 && genltau_dR_daughter_matched<0.3 && daughters_pt[genltau_i_daughter_matched]>30 && abs(daughters_eta[genltau_i_daughter_matched])<2.1)",50,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","combreliso[genlt_i_daughter_matched]","PUReweight*(genlt_pt>20 && abs(genlt_eta)<2.1 && genlt_dR_daughter_matched<0.3 && daughters_pt[genlt_i_daughter_matched]>20 && abs(daughters_eta[genlt_i_daughter_matched])<2.1)",50,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","combreliso[genltau_i_daughter_matched]","PUReweight*(genltau_pt>30 && abs(genltau_eta)<2.1 && genltau_dR_daughter_matched<0.3 && daughters_pt[genltau_i_daughter_matched]>30 && abs(daughters_eta[genltau_i_daughter_matched])<2.1)",50,0,20));

  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF");
  leg_entry.push_back("ttH lep. from top");
  leg_entry.push_back("ttH lep. from #tau");


  TLegend* leg=new TLegend(0.47,0.6,0.85,0.85);
  leg->SetHeader("#splitline{p_{T}>30 GeV , |#eta|<2.1}{gen. + reco., #DeltaR<0.3}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLogy();
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  //h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("rel. iso.");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Relative isolation of the leptons");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="iso_lep_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}
