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
#include "Helpers.C"
#include <TSystem.h>
#include <TLatex.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>

using namespace std;





void plot_isoMVA_eff_pt(){


  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  /*ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext1_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext2_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext3_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");*/

  vector<TH1F*> h_gen;
  h_gen.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt","MC_weight*(abs(genpart_pdg)>1000 && genpart_pt>30 && abs(genpart_eta)<2.3)",22,20,240));

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","MC_weight*(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT)",22,20,240));
  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","MC_weight*(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)",22,20,240));
  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","MC_weight*(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)",22,20,240));
  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","MC_weight*(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT)",22,20,240));

  TLegend* leg=new TLegend(0.2,0.65,0.5,0.87);
  leg->SetHeader("Iso. MVA #DeltaR=0.3");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Loose");
  leg_entry.push_back("Medium");
  leg_entry.push_back("Tight");
  leg_entry.push_back("Very tight");


  vector<TGraphAsymmErrors*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TGraphAsymmErrors());    
    h_eff[i]->Divide(h[i],h_gen[0]);
    h_eff[i]->SetLineColor(i+1);
    h_eff[i]->SetMarkerColor(i+1);
    if(i>3){
      h_eff[i]->SetLineColor(i+2);
      h_eff[i]->SetMarkerColor(i+2);
    }
    h_eff[i]->SetMarkerStyle(20+i);
    h_eff[i]->SetLineWidth(2);
    h_eff[i]->SetFillColor(0);
    leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h_eff[0]->SetMaximum(0.8);
  h_eff[0]->SetMinimum(0.);
  h_eff[0]->GetXaxis()->SetRangeUser(20,260);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}(gen)");
  h_eff[0]->GetYaxis()->SetTitle("TauID efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("AP");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("sameP");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(25,0.81,"CMS Preliminary, Simulation 13 TeV ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="tauh_eff_isoMVA_ttH_pt";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}






void plot_isoMVA_quark_mistag_pt(){


  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  /*ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext1_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext2_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext3_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");*/

  vector<TH1F*> h_gen;
  h_gen.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt","MC_weight*(abs(genpart_pdg)<5 && genpart_pt>30 && abs(genpart_eta)<2.3)",13,20,150));

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","MC_weight*(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])<5 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT)",13,20,150));
  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","MC_weight*(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])<5 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)",13,20,150));
  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","MC_weight*(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])<5 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT)",13,20,150));
  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","MC_weight*(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])<5 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT)",13,20,150));

  TLegend* leg=new TLegend(0.2,0.65,0.5,0.87);
  leg->SetHeader("Iso. MVA #DeltaR=0.3");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Loose");
  leg_entry.push_back("Medium");
  leg_entry.push_back("Tight");
  leg_entry.push_back("Very tight");


  vector<TGraphAsymmErrors*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TGraphAsymmErrors());    
    h_eff[i]->Divide(h[i],h_gen[0]);
    h_eff[i]->SetLineColor(i+1);
    h_eff[i]->SetMarkerColor(i+1);
    if(i>3){
      h_eff[i]->SetLineColor(i+2);
      h_eff[i]->SetMarkerColor(i+2);
    }
    h_eff[i]->SetMarkerStyle(20+i);
    h_eff[i]->SetLineWidth(2);
    h_eff[i]->SetFillColor(0);
    leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  h_eff[0]->SetMaximum(0.5);
  h_eff[0]->SetMinimum(0.00005);
  h_eff[0]->GetXaxis()->SetRangeUser(20,260);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}(gen)");
  h_eff[0]->GetYaxis()->SetTitle("Quark mistag rate");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("AP");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("sameP");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(22,0.55,"CMS Preliminary, Simulation 13 TeV ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="quark_mistag_isoMVA_ttH_pt";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}






void ttH_acceptance_tauh_efficiency(){

  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_ttH_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");

  TH1F* h_denom = single_plot(ttH_files,"HTauTauTree","1","MC_weight",3,0,3);
  float denom = h_denom->Integral();

  /*TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ ")",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ ")",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ ")",3,0,3));

  float sigma_ttH = 0.5085 * 0.0627 * 1000;
  cout<<sigma_ttH*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;*/

  /*TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  


  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

 

  float sigma_ttH = 0.5085 * 0.0627 * 1000;
  
  cout<<"No charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttH*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttH*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttH*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttH*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;

  cout<<"With charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttH*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttH*h[5]->Integral()/denom<<" fb"<<endl;
  cout<<h[5]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttH*h[6]->Integral()/denom<<" fb"<<endl;
  cout<<h[6]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttH*h[7]->Integral()/denom<<" fb"<<endl;
  cout<<h[7]->GetEntries()<<" entries"<<endl;*/



  /*TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[1]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonTight3[0])",3,0,3));
  h[1]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonTight3[0])",3,0,3)); 


  float sigma_ttH = 0.5085 * 0.0627 * 1000;
  
  cout<<"Loose anti-mu ttH: "<<sigma_ttH*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-mu ttH: "<<sigma_ttH*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;*/

  TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));

  float sigma_ttH = 0.5085 * 0.0627 * 1000;
  
  cout<<"VLoose anti-ele: "<<sigma_ttH*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Loose anti-ele: "<<sigma_ttH*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Medium anti-ele: "<<sigma_ttH*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-ele: "<<sigma_ttH*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;
  cout<<"VTight anti-ele: "<<sigma_ttH*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;

  return;


}





void ttH_acceptance_tauh_efficiency_fakeable(){

  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_ttH_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");

  TH1F* h_denom = single_plot(ttH_files,"HTauTauTree","1","MC_weight",3,0,3);
  float denom = h_denom->Integral();

  /*TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ ")",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ ")",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ ")",3,0,3));

  float sigma_ttH = 0.5085 * 0.0627 * 1000;
  cout<<sigma_ttH*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;*/

  TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  


  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

 

  float sigma_ttH = 0.5085 * 0.0627 * 1000;
  
  cout<<"No charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttH*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttH*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttH*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttH*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;

  cout<<"With charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttH*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttH*h[5]->Integral()/denom<<" fb"<<endl;
  cout<<h[5]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttH*h[6]->Integral()/denom<<" fb"<<endl;
  cout<<h[6]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttH*h[7]->Integral()/denom<<" fb"<<endl;
  cout<<h[7]->GetEntries()<<" entries"<<endl;



  /*TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[1]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonTight3[0])",3,0,3));
  h[1]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonTight3[0])",3,0,3)); 


  float sigma_ttH = 0.5085 * 0.0627 * 1000;
  
  cout<<"Loose anti-mu ttH: "<<sigma_ttH*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-mu ttH: "<<sigma_ttH*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;*/

  /*TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));

  h.push_back(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttH_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));

  float sigma_ttH = 0.5085 * 0.0627 * 1000;
  
  cout<<"VLoose anti-ele: "<<sigma_ttH*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Loose anti-ele: "<<sigma_ttH*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Medium anti-ele: "<<sigma_ttH*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-ele: "<<sigma_ttH*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;
  cout<<"VTight anti-ele: "<<sigma_ttH*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;*/

  return;


}








void ttjets_SL_fromT_acceptance_tauh_efficiency(){



  vector<TString> ttjets_files;
  ttjets_files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");

 
  TH1F* h_denom = single_plot(ttjets_files,"HTauTauTree","1","MC_weight",3,0,3);
  float denom = h_denom->Integral();

  /*TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ ")",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ ")",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ ")",3,0,3));

  float sigma_ttjets_SL = 182 * 1000;
  cout<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;*/


  /*TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  


  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));



  float sigma_ttjets_SL = 182 * 1000;
 
  cout<<"No charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttjets_SL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttjets_SL*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttjets_SL*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;

  cout<<"With charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttjets_SL*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttjets_SL*h[5]->Integral()/denom<<" fb"<<endl;
  cout<<h[5]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttjets_SL*h[6]->Integral()/denom<<" fb"<<endl;
  cout<<h[6]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttjets_SL*h[7]->Integral()/denom<<" fb"<<endl;
  cout<<h[7]->GetEntries()<<" entries"<<endl;*/

  /*TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonTight3[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonTight3[0])",3,0,3)); 


  float sigma_ttjets_SL = 182 * 1000;
  
  cout<<"Loose anti-mu: "<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-mu: "<<sigma_ttjets_SL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;*/

  TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));


  float sigma_ttjets_SL = 182 * 1000;
  
  cout<<"VLoose anti-ele: "<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Loose anti-ele: "<<sigma_ttjets_SL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Medium anti-ele: "<<sigma_ttjets_SL*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-ele: "<<sigma_ttjets_SL*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;
  cout<<"VTight anti-ele: "<<sigma_ttjets_SL*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;


  return;



}







void ttjets_SL_fromT_acceptance_tauh_efficiency_fakeable(){



  vector<TString> ttjets_files;
  ttjets_files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");

 
  TH1F* h_denom = single_plot(ttjets_files,"HTauTauTree","1","MC_weight",3,0,3);
  float denom = h_denom->Integral();

  /*TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ ")",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ ")",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ ")",3,0,3));

  float sigma_ttjets_SL = 182 * 1000;
  cout<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;*/


  TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  


  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));



  float sigma_ttjets_SL = 182 * 1000;
 
  cout<<"No charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttjets_SL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttjets_SL*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttjets_SL*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;

  cout<<"With charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttjets_SL*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttjets_SL*h[5]->Integral()/denom<<" fb"<<endl;
  cout<<h[5]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttjets_SL*h[6]->Integral()/denom<<" fb"<<endl;
  cout<<h[6]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttjets_SL*h[7]->Integral()/denom<<" fb"<<endl;
  cout<<h[7]->GetEntries()<<" entries"<<endl;

  /*TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && n_recomu_fakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonTight3[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonTight3[0])",3,0,3)); 


  float sigma_ttjets_SL = 182 * 1000;
  
  cout<<"Loose anti-mu: "<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-mu: "<<sigma_ttjets_SL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;*/

  /*TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));


  float sigma_ttjets_SL = 182 * 1000;
  
  cout<<"VLoose anti-ele: "<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Loose anti-ele: "<<sigma_ttjets_SL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Medium anti-ele: "<<sigma_ttjets_SL*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-ele: "<<sigma_ttjets_SL*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;
  cout<<"VTight anti-ele: "<<sigma_ttjets_SL*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;*/


  return;



}







void ttjets_SL_fromTbar_acceptance_tauh_efficiency(){


  vector<TString> ttjets_files;
  ttjets_files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromTbar_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");

 
  TH1F* h_denom = single_plot(ttjets_files,"HTauTauTree","1","MC_weight",3,0,3);
  float denom = h_denom->Integral();

  /*TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ ")",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ ")",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ ")",3,0,3));

  float sigma_ttjets_SL = 182 * 1000;
  cout<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;*/

  /*TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  


  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));



  float sigma_ttjets_SL = 182 * 1000;
 
  cout<<"No charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttjets_SL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttjets_SL*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttjets_SL*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;

  cout<<"With charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttjets_SL*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttjets_SL*h[5]->Integral()/denom<<" fb"<<endl;
  cout<<h[5]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttjets_SL*h[6]->Integral()/denom<<" fb"<<endl;
  cout<<h[6]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttjets_SL*h[7]->Integral()/denom<<" fb"<<endl;
  cout<<h[7]->GetEntries()<<" entries"<<endl;*/

  /*TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonTight3[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonTight3[0])",3,0,3)); 


  float sigma_ttjets_SL = 182 * 1000;
  
  cout<<"Loose anti-mu: "<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-mu: "<<sigma_ttjets_SL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;*/

  TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));


  float sigma_ttjets_SL = 182 * 1000;
  
  cout<<"VLoose anti-ele: "<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Loose anti-ele: "<<sigma_ttjets_SL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Medium anti-ele: "<<sigma_ttjets_SL*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-ele: "<<sigma_ttjets_SL*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;
  cout<<"VTight anti-ele: "<<sigma_ttjets_SL*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;


  return;



}






void ttjets_SL_fromTbar_acceptance_tauh_efficiency_fakeable(){


  vector<TString> ttjets_files;
  ttjets_files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromTbar_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");

 
  TH1F* h_denom = single_plot(ttjets_files,"HTauTauTree","1","MC_weight",3,0,3);
  float denom = h_denom->Integral();

  /*TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ ")",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ ")",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ ")",3,0,3));

  float sigma_ttjets_SL = 182 * 1000;
  cout<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;*/

  /*TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  


  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));



  float sigma_ttjets_SL = 182 * 1000;
 
  cout<<"No charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttjets_SL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttjets_SL*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttjets_SL*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;

  cout<<"With charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttjets_SL*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttjets_SL*h[5]->Integral()/denom<<" fb"<<endl;
  cout<<h[5]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttjets_SL*h[6]->Integral()/denom<<" fb"<<endl;
  cout<<h[6]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttjets_SL*h[7]->Integral()/denom<<" fb"<<endl;
  cout<<h[7]->GetEntries()<<" entries"<<endl;*/

  /*TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonTight3[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonTight3[0])",3,0,3)); 


  float sigma_ttjets_SL = 182 * 1000;
  
  cout<<"Loose anti-mu: "<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-mu: "<<sigma_ttjets_SL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;*/

  TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));


  float sigma_ttjets_SL = 182 * 1000;
  
  cout<<"VLoose anti-ele: "<<sigma_ttjets_SL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Loose anti-ele: "<<sigma_ttjets_SL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Medium anti-ele: "<<sigma_ttjets_SL*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-ele: "<<sigma_ttjets_SL*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;
  cout<<"VTight anti-ele: "<<sigma_ttjets_SL*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;


  return;



}








void ttjets_DL_acceptance_tauh_efficiency(){


  vector<TString> ttjets_files;
  ttjets_files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");

 
  TH1F* h_denom = single_plot(ttjets_files,"HTauTauTree","1","MC_weight",3,0,3);
  float denom = h_denom->Integral();

  /*TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ ")",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ ")",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ ")",3,0,3));


  float sigma_ttjets_DL = 87.3 * 1000;
  cout<<sigma_ttjets_DL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;*/

  /*TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  


  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));



  float sigma_ttjets_DL = 87.3 * 1000;
 
  cout<<"No charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttjets_DL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttjets_DL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttjets_DL*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttjets_DL*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;

  cout<<"With charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttjets_DL*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttjets_DL*h[5]->Integral()/denom<<" fb"<<endl;
  cout<<h[5]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttjets_DL*h[6]->Integral()/denom<<" fb"<<endl;
  cout<<h[6]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttjets_DL*h[7]->Integral()/denom<<" fb"<<endl;
  cout<<h[7]->GetEntries()<<" entries"<<endl;*/


  /*TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonTight3[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonTight3[0])",3,0,3)); 


  float sigma_ttjets_DL = 87.3 * 1000;
  
  cout<<"Loose anti-mu: "<<sigma_ttjets_DL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-mu: "<<sigma_ttjets_DL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;*/

  TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && recomu_ismvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));


  float sigma_ttjets_DL = 87.3 * 1000;
  
  cout<<"VLoose anti-ele: "<<sigma_ttjets_DL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Loose anti-ele: "<<sigma_ttjets_DL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Medium anti-ele: "<<sigma_ttjets_DL*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-ele: "<<sigma_ttjets_DL*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;
  cout<<"VTight anti-ele: "<<sigma_ttjets_DL*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;

  return;



}







void ttjets_DL_acceptance_tauh_efficiency_fakeable(){


  vector<TString> ttjets_files;
  ttjets_files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");

 
  TH1F* h_denom = single_plot(ttjets_files,"HTauTauTree","1","MC_weight",3,0,3);
  float denom = h_denom->Integral();

  /*TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46))";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ ")",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ ")",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ ")",3,0,3));


  float sigma_ttjets_DL = 87.3 * 1000;
  cout<<sigma_ttjets_DL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;*/

  TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])",3,0,3));
  


  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[5]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[6]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0)",3,0,3));
  h[7]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0)",3,0,3));



  float sigma_ttjets_DL = 87.3 * 1000;
 
  cout<<"No charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttjets_DL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttjets_DL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttjets_DL*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttjets_DL*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;

  cout<<"With charge requirement"<<endl;
  cout<<"Loose Iso ttH: "<<sigma_ttjets_DL*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;
  cout<<"Medium Iso ttH: "<<sigma_ttjets_DL*h[5]->Integral()/denom<<" fb"<<endl;
  cout<<h[5]->GetEntries()<<" entries"<<endl;
  cout<<"Tight Iso ttH: "<<sigma_ttjets_DL*h[6]->Integral()/denom<<" fb"<<endl;
  cout<<h[6]->GetEntries()<<" entries"<<endl;
  cout<<"VTight Iso ttH: "<<sigma_ttjets_DL*h[7]->Integral()/denom<<" fb"<<endl;
  cout<<h[7]->GetEntries()<<" entries"<<endl;


  /*TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && recomu_isfakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstMuonLoose3[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstMuonTight3[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstMuonTight3[0])",3,0,3)); 


  float sigma_ttjets_DL = 87.3 * 1000;
  
  cout<<"Loose anti-mu: "<<sigma_ttjets_DL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-mu: "<<sigma_ttjets_DL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;*/

  /*TString base_cut_mumu="n_recomu_fakeable==2 && n_recoele_fakeable==0 && recomu_isfakeable[0]==1 && recomu_isfakeable[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_fakeable==0 && n_recoele_fakeable==2 && recoele_isfakeable[0]==1 && recoele_isfakeable[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_fakeable==1 && n_recoele_fakeable==1 && n_recomu_fakeable[0]==1 && recoele_isfakeable[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));
  h[0]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));
  h[1]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronLooseMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));
  h[2]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronMediumMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));
  h[3]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronTightMVA6[0])",3,0,3));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_mumu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_ee+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));
  h[4]->Add(single_plot(ttjets_files,"HTauTauTree","1","MC_weight*("+base_cut_emu+ "&& recotauh_againstElectronVTightMVA6[0])",3,0,3));


  float sigma_ttjets_DL = 87.3 * 1000;
  
  cout<<"VLoose anti-ele: "<<sigma_ttjets_DL*h[0]->Integral()/denom<<" fb"<<endl;
  cout<<h[0]->GetEntries()<<" entries"<<endl;
  cout<<"Loose anti-ele: "<<sigma_ttjets_DL*h[1]->Integral()/denom<<" fb"<<endl;
  cout<<h[1]->GetEntries()<<" entries"<<endl;
  cout<<"Medium anti-ele: "<<sigma_ttjets_DL*h[2]->Integral()/denom<<" fb"<<endl;
  cout<<h[2]->GetEntries()<<" entries"<<endl;
  cout<<"Tight anti-ele: "<<sigma_ttjets_DL*h[3]->Integral()/denom<<" fb"<<endl;
  cout<<h[3]->GetEntries()<<" entries"<<endl;
  cout<<"VTight anti-ele: "<<sigma_ttjets_DL*h[4]->Integral()/denom<<" fb"<<endl;
  cout<<h[4]->GetEntries()<<" entries"<<endl;*/

  return;



}




void plot_antiMu_eff_pt(){


  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  //ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext1_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  /*ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext2_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext3_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");*/

  vector<TH1F*> h_gen;
  h_gen.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT)",22,20,240));

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstMuonLoose3)",22,20,240));

  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstMuonTight3)",22,20,240));


  TLegend* leg=new TLegend(0.2,0.65,0.5,0.87);
  //leg->SetHeader("Iso. MVA #DeltaR=0.3");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Loose");
  leg_entry.push_back("Tight");

  vector<TGraphAsymmErrors*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TGraphAsymmErrors());    
    h_eff[i]->Divide(h[i],h_gen[0]);
    h_eff[i]->SetLineColor(i+1);
    h_eff[i]->SetMarkerColor(i+1);
    if(i>3){
      h_eff[i]->SetLineColor(i+2);
      h_eff[i]->SetMarkerColor(i+2);
    }
    h_eff[i]->SetMarkerStyle(20+i);
    h_eff[i]->SetLineWidth(2);
    h_eff[i]->SetFillColor(0);
    leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h_eff[0]->SetMaximum(1.1);
  h_eff[0]->SetMinimum(0.8);
  h_eff[0]->GetXaxis()->SetRangeUser(20,260);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}(gen)");
  h_eff[0]->GetYaxis()->SetTitle("Anti-#mu efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("AP");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("sameP");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(25,1.105,"CMS Preliminary, Simulation 13 TeV ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="tauh_eff_antimu_ttH_pt";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}








void plot_antiMu_mu_mistag_pt(){


  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext1_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  /*ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext2_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext3_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");*/

  vector<TH1F*> h_gen;
  h_gen.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==13 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT)",10,20,120));

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==13 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstMuonLoose3)",10,20,120));

  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==13 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstMuonTight3)",10,20,120));


  TLegend* leg=new TLegend(0.2,0.65,0.5,0.87);
  //leg->SetHeader("Iso. MVA #DeltaR=0.3");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Loose");
  leg_entry.push_back("Tight");

  vector<TGraphAsymmErrors*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TGraphAsymmErrors());    
    h_eff[i]->Divide(h[i],h_gen[0]);
    h_eff[i]->SetLineColor(i+1);
    h_eff[i]->SetMarkerColor(i+1);
    if(i>3){
      h_eff[i]->SetLineColor(i+2);
      h_eff[i]->SetMarkerColor(i+2);
    }
    h_eff[i]->SetMarkerStyle(20+i);
    h_eff[i]->SetLineWidth(2);
    h_eff[i]->SetFillColor(0);
    leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  h_eff[0]->SetMaximum(1.);
  h_eff[0]->SetMinimum(1e-4);
  h_eff[0]->GetXaxis()->SetRangeUser(20,260);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}(gen)");
  h_eff[0]->GetYaxis()->SetTitle("Muon mistag rate");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("AP");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("sameP");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(22,1.2,"CMS Preliminary, Simulation 13 TeV ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="mu_mistag_antimu_ttH_pt";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}








void plot_antiEle_eff_pt(){


  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  //ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext1_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  /*ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext2_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext3_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");*/

  vector<TH1F*> h_gen;
  h_gen.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT)",22,20,240));

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstElectronVLooseMVA6)",22,20,240));

  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstElectronLooseMVA6)",22,20,240));

  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstElectronMediumMVA6)",22,20,240));

  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstElectronTightMVA6)",22,20,240));

  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])>1000 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstElectronVTightMVA6)",22,20,240));

  TLegend* leg=new TLegend(0.6,0.25,0.75,0.5);
  //leg->SetHeader("Iso. MVA #DeltaR=0.3");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Very loose");
  leg_entry.push_back("Loose");
  leg_entry.push_back("Medium");
  leg_entry.push_back("Tight");
  leg_entry.push_back("Very tight");

  vector<TGraphAsymmErrors*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TGraphAsymmErrors());    
    h_eff[i]->Divide(h[i],h_gen[0]);
    h_eff[i]->SetLineColor(i+1);
    h_eff[i]->SetMarkerColor(i+1);
    if(i>3){
      h_eff[i]->SetLineColor(i+2);
      h_eff[i]->SetMarkerColor(i+2);
    }
    h_eff[i]->SetMarkerStyle(20+i);
    h_eff[i]->SetLineWidth(2);
    h_eff[i]->SetFillColor(0);
    leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  //c->SetLogy();
  h_eff[0]->SetMaximum(1.);
  h_eff[0]->SetMinimum(0.5);
  h_eff[0]->GetXaxis()->SetRangeUser(20,260);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}(gen)");
  h_eff[0]->GetYaxis()->SetTitle("Anti-electron efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("AP");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("sameP");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(25,1.01,"CMS Preliminary, Simulation 13 TeV ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="tauh_eff_antiele_ttH_pt";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}








void plot_antiEle_ele_mistag_rate_pt(){


  vector<TString> ttH_files;
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext1_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  /*ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext2_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  ttH_files.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_03_2016/ntuple_ttH_ext3_dRveto_gen_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");*/

  vector<TH1F*> h_gen;
  h_gen.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==11 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT)",10,20,120));

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==11 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstElectronVLooseMVA6)",10,20,120));

  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==11 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstElectronLooseMVA6)",10,20,120));

  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==11 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstElectronMediumMVA6)",10,20,120));

  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==11 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstElectronTightMVA6)",10,20,120));

  h.push_back(single_plot(ttH_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","(n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && abs(genpart_pdg[recotauh_i_closest_genpart])==11 && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.3 && recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT && recotauh_againstElectronVTightMVA6)",10,20,120));

  TLegend* leg=new TLegend(0.6,0.25,0.75,0.5);
  //leg->SetHeader("Iso. MVA #DeltaR=0.3");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Very loose");
  leg_entry.push_back("Loose");
  leg_entry.push_back("Medium");
  leg_entry.push_back("Tight");
  leg_entry.push_back("Very tight");

  vector<TGraphAsymmErrors*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TGraphAsymmErrors());    
    h_eff[i]->Divide(h[i],h_gen[0]);
    h_eff[i]->SetLineColor(i+1);
    h_eff[i]->SetMarkerColor(i+1);
    if(i>3){
      h_eff[i]->SetLineColor(i+2);
      h_eff[i]->SetMarkerColor(i+2);
    }
    h_eff[i]->SetMarkerStyle(20+i);
    h_eff[i]->SetLineWidth(2);
    h_eff[i]->SetFillColor(0);
    leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  h_eff[0]->SetMaximum(1.);
  h_eff[0]->SetMinimum(1e-5);
  h_eff[0]->GetXaxis()->SetRangeUser(20,260);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}(gen)");
  h_eff[0]->GetYaxis()->SetTitle("Electron mistag rate");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("AP");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("sameP");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(22,1.2,"CMS Preliminary, Simulation 13 TeV ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="ele_mistag_antiele_ttH_pt";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
    

}


