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


void plot_leptonMVA(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_dRveto_gen_iso70.root");
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_ext1_dRveto_gen_iso70.root");
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_ext2_dRveto_gen_iso70.root");
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_ext3_dRveto_gen_1_iso70.root");
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_ext3_dRveto_gen_2_iso70.root");
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_ext3_dRveto_gen_3_iso70.root");
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_ext3_dRveto_gen_4_iso70.root");

  vector<TH1F*> h;
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA","PUReweight*MC_weight*(recolep_TopMothInd>=0 && gentop_decayMode[recolep_TopMothInd]<=2)",100,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA","PUReweight*MC_weight*(recolep_TopMothInd>=0 && gentop_decayMode[recolep_TopMothInd]>=3)",100,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA","PUReweight*MC_weight*(recolep_HMothInd>=0)",100,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA","PUReweight*MC_weight*(recolep_TopMothInd<0&&recolep_HMothInd<0)",100,-1,1));
 


  vector<TString> leg_entry;
  leg_entry.push_back("Leptons from t->bl#nu decay");
  leg_entry.push_back("Leptons from t->b#tau#nu, #tau->l decay");
  leg_entry.push_back("Leptons from H->#tau#tau decay");
  leg_entry.push_back("Other reco. leptons");


  TLegend* leg=new TLegend(0.3,0.6,0.85,0.85);
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
  h[0]->GetXaxis()->SetTitle("Lepton MVA");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");

  TLatex *texl = new TLatex(-0.99,1.24*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="leptonMVA_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_leptonMVA_presel(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_dRveto_gen_iso70.root");
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_ext1_dRveto_gen_iso70.root");
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_ext2_dRveto_gen_iso70.root");
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_ext3_dRveto_gen_1_iso70.root");
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_ext3_dRveto_gen_2_iso70.root");
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_ext3_dRveto_gen_3_iso70.root");
  files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_ttH_ext3_dRveto_gen_4_iso70.root");

  vector<TH1F*> h;
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA","PUReweight*MC_weight*(recolep_TopMothInd>=0 && gentop_decayMode[recolep_TopMothInd]<=2 && n_recolep>=2 && n_recotauh>=1 && recoPFJet_btag_CSVscore[0]>0.814 && recoPFJet_btag_CSVscore[1]>0.423 && n_recoPFJet>=3 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0)",100,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA","PUReweight*MC_weight*(recolep_TopMothInd>=0 && gentop_decayMode[recolep_TopMothInd]>=3 && n_recolep>=2 && n_recotauh>=1 && recoPFJet_btag_CSVscore[0]>0.814 && recoPFJet_btag_CSVscore[1]>0.423 && n_recoPFJet>=3 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0)",100,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA","PUReweight*MC_weight*(recolep_HMothInd>=0 && n_recolep>=2 && n_recotauh>=1 && recoPFJet_btag_CSVscore[0]>0.814 && recoPFJet_btag_CSVscore[1]>0.423 && n_recoPFJet>=3 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0)",100,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA","PUReweight*MC_weight*(recolep_TopMothInd<0&&recolep_HMothInd<0 && n_recolep>=2 && n_recotauh>=1 && recoPFJet_btag_CSVscore[0]>0.814 && recoPFJet_btag_CSVscore[1]>0.423 && n_recoPFJet>=3 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0)",100,-1,1));
 


  vector<TString> leg_entry;
  leg_entry.push_back("Leptons from t->bl#nu decay");
  leg_entry.push_back("Leptons from t->b#tau#nu, #tau->l decay");
  leg_entry.push_back("Leptons from H->#tau#tau decay");
  leg_entry.push_back("Other reco. leptons");


  TLegend* leg=new TLegend(0.3,0.5,0.85,0.85);
  leg->SetHeader("#splitline{2 SS lep. + #geq1 #tau_{h}}{+#geq 3 jets + 1 CSVM + 1 CSVL}");
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
  //c->SetLogy();
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Lepton MVA");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");

  TLatex *texl = new TLatex(-0.99,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="leptonMVA_ttH_presel";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_leptonMVA_ttjets(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");

  vector<TH1F*> h;
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46)",20,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46)",20,-1,1));

  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46)",20,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46)",20,-1,1));
 


  vector<TString> leg_entry;
  leg_entry.push_back("Lead. lep., #leq 1 #tau_{h}");
  leg_entry.push_back("Sublead. lep., #leq 1 #tau_{h}");
  leg_entry.push_back("Lead. lep., 0 #tau_{h}");
  leg_entry.push_back("Sublead. lep., 0 #tau_{h}");


  TLegend* leg=new TLegend(0.3,0.5,0.85,0.85);
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
  h[0]->GetXaxis()->SetTitle("Lepton MVA");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");

  TLatex *texl = new TLatex(-0.99,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="leptonMVA_ttjets";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_leptonMVA_ttjets_max(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");

  vector<TH1F*> h;
  h.push_back(single_plot(files,"HTauTauTree","max(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46)",20,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","min(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46)",20,-1,1));

  h.push_back(single_plot(files,"HTauTauTree","max(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46)",20,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","min(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46)",20,-1,1));
 


  vector<TString> leg_entry;
  leg_entry.push_back("Max. lepton MVA, #leq 1 #tau_{h}");
  leg_entry.push_back("Min. lepton MVA, #leq 1 #tau_{h}");
  leg_entry.push_back("Max. lepton MVA, 0 #tau_{h}");
  leg_entry.push_back("Min. lepton MVA, 0 #tau_{h}");


  TLegend* leg=new TLegend(0.3,0.5,0.85,0.85);
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
  h[0]->GetXaxis()->SetTitle("Lepton MVA");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");

  TLatex *texl = new TLatex(-0.99,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="leptonMVA_ttjets_max";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_leptonMVA_ttjets_max_mumu(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");

  vector<TH1F*> h;
  h.push_back(single_plot(files,"HTauTauTree","max(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13)",20,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","min(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13)",20,-1,1));

  h.push_back(single_plot(files,"HTauTauTree","max(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13)",20,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","min(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13)",20,-1,1));
 


  vector<TString> leg_entry;
  leg_entry.push_back("Max. lepton MVA, #leq 1 #tau_{h}");
  leg_entry.push_back("Min. lepton MVA, #leq 1 #tau_{h}");
  leg_entry.push_back("Max. lepton MVA, 0 #tau_{h}");
  leg_entry.push_back("Min. lepton MVA, 0 #tau_{h}");


  TLegend* leg=new TLegend(0.3,0.5,0.85,0.85);
  leg->SetHeader("Dimuon channel");
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
  h[0]->GetXaxis()->SetTitle("Lepton MVA");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");

  TLatex *texl = new TLatex(-0.99,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="leptonMVA_ttjets_max_mumu";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_leptonMVA_ttjets_max_ee(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");

  vector<TH1F*> h;
  h.push_back(single_plot(files,"HTauTauTree","max(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11)",20,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","min(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11)",20,-1,1));

  h.push_back(single_plot(files,"HTauTauTree","max(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11)",20,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","min(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11)",20,-1,1));
 


  vector<TString> leg_entry;
  leg_entry.push_back("Max. lepton MVA, #leq 1 #tau_{h}");
  leg_entry.push_back("Min. lepton MVA, #leq 1 #tau_{h}");
  leg_entry.push_back("Max. lepton MVA, 0 #tau_{h}");
  leg_entry.push_back("Min. lepton MVA, 0 #tau_{h}");


  TLegend* leg=new TLegend(0.3,0.5,0.85,0.85);
  leg->SetHeader("Dielectron channel");
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
  h[0]->GetXaxis()->SetTitle("Lepton MVA");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");

  TLatex *texl = new TLatex(-0.99,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="leptonMVA_ttjets_max_ee";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_leptonMVA_ttjets_max_emu(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");

  vector<TH1F*> h;
  h.push_back(single_plot(files,"HTauTauTree","max(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)||(abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)))",20,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","min(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recolep_charge[1]>0 && recolep_charge[0]*recotauh_charge[0]<0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)||(abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)))",20,-1,1));

  h.push_back(single_plot(files,"HTauTauTree","max(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)||(abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)))",20,-1,1));
  h.push_back(single_plot(files,"HTauTauTree","min(recolep_leptonMVA[0],recolep_leptonMVA[1])","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)||(abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)))",20,-1,1));
 


  vector<TString> leg_entry;
  leg_entry.push_back("Max. lepton MVA, #leq 1 #tau_{h}");
  leg_entry.push_back("Min. lepton MVA, #leq 1 #tau_{h}");
  leg_entry.push_back("Max. lepton MVA, 0 #tau_{h}");
  leg_entry.push_back("Min. lepton MVA, 0 #tau_{h}");


  TLegend* leg=new TLegend(0.3,0.5,0.85,0.85);
  leg->SetHeader("e#mu channel");
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
  h[0]->GetXaxis()->SetTitle("Lepton MVA");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");

  TLatex *texl = new TLatex(-0.99,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="leptonMVA_ttjets_max_emu";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_leptonMVA_ttjets_max_ee_pt(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");

  vector<TH1F*> h;
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[0]<recolep_leptonMVA[1] && recolep_pt[0]<30)",20,-1,1));
  h[0]->Add(single_plot(files,"HTauTauTree","recolep_leptonMVA[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[1]<recolep_leptonMVA[0] && recolep_pt[1]<30)",20,-1,1));

  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[0]<recolep_leptonMVA[1] && recolep_pt[0]>30 && recolep_pt[0]<60)",20,-1,1));
  h[1]->Add(single_plot(files,"HTauTauTree","recolep_leptonMVA[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[1]<recolep_leptonMVA[0] && recolep_pt[1]>30 && recolep_pt[1]<60)",20,-1,1));

  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[0]<recolep_leptonMVA[1] && recolep_pt[0]>60)",20,-1,1));
  h[2]->Add(single_plot(files,"HTauTauTree","recolep_leptonMVA[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[1]<recolep_leptonMVA[0] && recolep_pt[1]>60)",20,-1,1));
 


  vector<TString> leg_entry;
  leg_entry.push_back("Min. lepton MVA, p_{T}<30 GeV");
  leg_entry.push_back("Min. lepton MVA, 30<p_{T}<60 GeV");
  leg_entry.push_back("Min. lepton MVA, p_{T}>60 GeV");


  TLegend* leg=new TLegend(0.3,0.5,0.85,0.85);
  leg->SetHeader("Dielectron channel, 0 #tau_{h}");
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
  h[0]->GetXaxis()->SetTitle("Lepton MVA");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");

  TLatex *texl = new TLatex(-0.99,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="leptonMVA_ttjets_max_ee_pt";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_leptonMVA_ttjets_max_mumu_pt(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed.root");

  vector<TH1F*> h;
  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && recolep_leptonMVA[0]<recolep_leptonMVA[1] && recolep_pt[0]<30)",20,-1,1));
  h[0]->Add(single_plot(files,"HTauTauTree","recolep_leptonMVA[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && recolep_leptonMVA[1]<recolep_leptonMVA[0] && recolep_pt[1]<30)",20,-1,1));

  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && recolep_leptonMVA[0]<recolep_leptonMVA[1] && recolep_pt[0]>30 && recolep_pt[0]<60)",20,-1,1));
  h[1]->Add(single_plot(files,"HTauTauTree","recolep_leptonMVA[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && recolep_leptonMVA[1]<recolep_leptonMVA[0] && recolep_pt[1]>30 && recolep_pt[1]<60)",20,-1,1));

  h.push_back(single_plot(files,"HTauTauTree","recolep_leptonMVA[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && recolep_leptonMVA[0]<recolep_leptonMVA[1] && recolep_pt[0]>60)",20,-1,1));
  h[2]->Add(single_plot(files,"HTauTauTree","recolep_leptonMVA[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && recolep_leptonMVA[1]<recolep_leptonMVA[0] && recolep_pt[1]>60)",20,-1,1));
 


  vector<TString> leg_entry;
  leg_entry.push_back("Min. lepton MVA, p_{T}<30 GeV");
  leg_entry.push_back("Min. lepton MVA, 30<p_{T}<60 GeV");
  leg_entry.push_back("Min. lepton MVA, p_{T}>60 GeV");


  TLegend* leg=new TLegend(0.3,0.5,0.85,0.85);
  leg->SetHeader("Dimuon channel, 0 #tau_{h}");
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
  h[0]->GetXaxis()->SetTitle("Lepton MVA");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.65);
  h[0]->SetTitle("");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  leg->Draw("same");

  TLatex *texl = new TLatex(-0.99,1.01*h[0]->GetMaximum(),"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="leptonMVA_ttjets_max_mumu_pt";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}
