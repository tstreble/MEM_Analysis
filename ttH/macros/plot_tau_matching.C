#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <THStack.h>
#include <iostream>
#include <TLegend.h>
#include <TLatex.h>
#include <Helpers.C>
#include <vector>

using namespace std;


  TString base_cut_mumu="n_recomu_mvasel==2 && n_recoele_mvasel==0 && recomu_ismvasel[0]==1 && recomu_ismvasel[1]==1 && recomu_charge[0]*recomu_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";
  TString base_cut_ee="n_recomu_mvasel==0 && n_recoele_mvasel==2 && recoele_ismvasel[0]==1 && recoele_ismvasel[1]==1 && recoele_charge[0]*recoele_charge[1]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recoele_charge[0]<0";
  TString base_cut_emu="n_recomu_mvasel==1 && n_recoele_mvasel==1 && n_recomu_mvasel[0]==1 && recoele_ismvasel[0]==1 && recomu_charge[0]*recoele_charge[0]>0 && n_recoPFJet>=4 && ((recoPFJet_CSVsort_CSVscore[0]>0.8) || (recoPFJet_CSVsort_CSVscore[0]>0.46 && recoPFJet_CSVsort_CSVscore[1]>0.46)) && n_recotauh>=1 && recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recotauh_charge[0]*recomu_charge[0]<0";




void plot_tau_matching_ttH(){

  TString Wquark_matching = "(recotauh_dR_closest_genpart[0]<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart[0]])<5 && genpart_TopMothInd[recotauh_i_closest_genpart[0]]>=0 && genpart_WMothInd[recotauh_i_closest_genpart[0]]>=0)";
  TString ele_matching = "(recotauh_dR_closest_genpart[0]<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart[0]])==11)";
  TString mu_matching = "(recotauh_dR_closest_genpart[0]<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart[0]])==13)";
  TString tau_matching = "(recotauh_dR_closest_genpart[0]<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart[0]])>1000)";
  TString dummy_matching="(!"+Wquark_matching+" && !"+tau_matching+" && !"+ele_matching+" && !"+mu_matching+")";

  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_ttH_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");


  /*vector<TString> files_ttjets_SL;
  files_ttjets_SL.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  files_ttjets_SL.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromTbar_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");

  vector<TString> files_ttjets_DL;
  files_ttjets_DL.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");*/

  vector<TH1F*> h;
  h.push_back(single_plot(files_ttH,"HTauTauTree","0","MC_weight*("+base_cut_mumu+"&&"+dummy_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttH,"HTauTauTree","0","MC_weight*("+base_cut_emu+"&&"+dummy_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttH,"HTauTauTree","0","MC_weight*("+base_cut_ee+"&&"+dummy_matching +")",5,0,5));

  h[0]->Add(single_plot(files_ttH,"HTauTauTree","1","MC_weight*("+base_cut_mumu+"&&"+Wquark_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttH,"HTauTauTree","1","MC_weight*("+base_cut_emu+"&&"+Wquark_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttH,"HTauTauTree","1","MC_weight*("+base_cut_ee+"&&"+Wquark_matching +")",5,0,5));

  h[0]->Add(single_plot(files_ttH,"HTauTauTree","2","MC_weight*("+base_cut_mumu+"&&"+mu_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttH,"HTauTauTree","2","MC_weight*("+base_cut_emu+"&&"+mu_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttH,"HTauTauTree","2","MC_weight*("+base_cut_ee+"&&"+mu_matching +")",5,0,5));

  h[0]->Add(single_plot(files_ttH,"HTauTauTree","3","MC_weight*("+base_cut_mumu+"&&"+ele_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttH,"HTauTauTree","3","MC_weight*("+base_cut_emu+"&&"+ele_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttH,"HTauTauTree","3","MC_weight*("+base_cut_ee+"&&"+ele_matching +")",5,0,5));

  h[0]->Add(single_plot(files_ttH,"HTauTauTree","4","MC_weight*("+base_cut_mumu+"&&"+tau_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttH,"HTauTauTree","4","MC_weight*("+base_cut_emu+"&&"+tau_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttH,"HTauTauTree","4","MC_weight*("+base_cut_ee+"&&"+tau_matching +")",5,0,5));


  /*TLegend* leg=new TLegend(0.2,0.55,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#splitline{2lSS, #leq 1#tau_{h} OS}{#leq 3 jets, 1CSVM + 1CSVL}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttH 2 tight leptons");
  leg_entry.push_back("tt+jets 2 tight leptons");
  leg_entry.push_back("tt+jets tight+loose leptons");*/


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    //leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.);
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Matching index");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  /*for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
    }*/
  


  //leg->Draw("same");

  TLatex *texl = new TLatex(0.1,1.02*h[0]->GetMaximum(),"CMS Preliminary, Simulation 13 TeV ttH, H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tau_matching_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_tau_matching_ttjets_SL(){

  TString Wquark_matching = "(recotauh_dR_closest_genpart[0]<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart[0]])<5 && genpart_TopMothInd[recotauh_i_closest_genpart[0]]>=0 && genpart_WMothInd[recotauh_i_closest_genpart[0]]>=0)";
  TString ele_matching = "(recotauh_dR_closest_genpart[0]<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart[0]])==11)";
  TString mu_matching = "(recotauh_dR_closest_genpart[0]<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart[0]])==13)";
  TString tau_matching = "(recotauh_dR_closest_genpart[0]<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart[0]])>1000)";
  TString dummy_matching="(!"+Wquark_matching+" && !"+tau_matching+" && !"+ele_matching+" && !"+mu_matching+")";

  /*vector<TString> files_ttH;
    files_ttH.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_ttH_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");*/


  vector<TString> files_ttjets_SL;
  files_ttjets_SL.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  files_ttjets_SL.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromTbar_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");

  /*vector<TString> files_ttjets_DL;
  files_ttjets_DL.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");*/

  vector<TH1F*> h;
  h.push_back(single_plot(files_ttjets_SL,"HTauTauTree","0","MC_weight*("+base_cut_mumu+"&&"+dummy_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","0","MC_weight*("+base_cut_emu+"&&"+dummy_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","0","MC_weight*("+base_cut_ee+"&&"+dummy_matching +")",5,0,5));

  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","1","MC_weight*("+base_cut_mumu+"&&"+Wquark_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","1","MC_weight*("+base_cut_emu+"&&"+Wquark_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","1","MC_weight*("+base_cut_ee+"&&"+Wquark_matching +")",5,0,5));

  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","2","MC_weight*("+base_cut_mumu+"&&"+mu_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","2","MC_weight*("+base_cut_emu+"&&"+mu_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","2","MC_weight*("+base_cut_ee+"&&"+mu_matching +")",5,0,5));

  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","3","MC_weight*("+base_cut_mumu+"&&"+ele_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","3","MC_weight*("+base_cut_emu+"&&"+ele_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","3","MC_weight*("+base_cut_ee+"&&"+ele_matching +")",5,0,5));

  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","4","MC_weight*("+base_cut_mumu+"&&"+tau_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","4","MC_weight*("+base_cut_emu+"&&"+tau_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_SL,"HTauTauTree","4","MC_weight*("+base_cut_ee+"&&"+tau_matching +")",5,0,5));


  /*TLegend* leg=new TLegend(0.2,0.55,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#splitline{2lSS, #leq 1#tau_{h} OS}{#leq 3 jets, 1CSVM + 1CSVL}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttjets_SL 2 tight leptons");
  leg_entry.push_back("tt+jets 2 tight leptons");
  leg_entry.push_back("tt+jets tight+loose leptons");*/


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    //leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.);
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Matching index");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  /*for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
    }*/
  


  //leg->Draw("same");

  TLatex *texl = new TLatex(0.1,1.02*h[0]->GetMaximum(),"CMS Preliminary, Simulation 13 TeV tt, t->bqq, t->bl#nu");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tau_matching_ttjets_SL";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_tau_matching_ttjets_DL(){

  TString Wquark_matching = "(recotauh_dR_closest_genpart[0]<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart[0]])<5 && genpart_TopMothInd[recotauh_i_closest_genpart[0]]>=0 && genpart_WMothInd[recotauh_i_closest_genpart[0]]>=0)";
  TString ele_matching = "(recotauh_dR_closest_genpart[0]<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart[0]])==11)";
  TString mu_matching = "(recotauh_dR_closest_genpart[0]<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart[0]])==13)";
  TString tau_matching = "(recotauh_dR_closest_genpart[0]<0.2 && abs(genpart_pdg[recotauh_i_closest_genpart[0]])>1000)";
  TString dummy_matching="(!"+Wquark_matching+" && !"+tau_matching+" && !"+ele_matching+" && !"+mu_matching+")";

  /*vector<TString> files_ttH;
    files_ttH.push_back("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_ttH_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");*/


  /*vector<TString> files_ttjets_SL;
  files_ttjets_SL.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");
  files_ttjets_SL.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_SLfromTbar_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");*/

  vector<TString> files_ttjets_DL;
  files_ttjets_DL.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/ntuple_TTJets_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root");

  vector<TH1F*> h;
  h.push_back(single_plot(files_ttjets_DL,"HTauTauTree","0","MC_weight*("+base_cut_mumu+"&&"+dummy_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","0","MC_weight*("+base_cut_emu+"&&"+dummy_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","0","MC_weight*("+base_cut_ee+"&&"+dummy_matching +")",5,0,5));

  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","1","MC_weight*("+base_cut_mumu+"&&"+Wquark_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","1","MC_weight*("+base_cut_emu+"&&"+Wquark_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","1","MC_weight*("+base_cut_ee+"&&"+Wquark_matching +")",5,0,5));

  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","2","MC_weight*("+base_cut_mumu+"&&"+mu_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","2","MC_weight*("+base_cut_emu+"&&"+mu_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","2","MC_weight*("+base_cut_ee+"&&"+mu_matching +")",5,0,5));

  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","3","MC_weight*("+base_cut_mumu+"&&"+ele_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","3","MC_weight*("+base_cut_emu+"&&"+ele_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","3","MC_weight*("+base_cut_ee+"&&"+ele_matching +")",5,0,5));

  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","4","MC_weight*("+base_cut_mumu+"&&"+tau_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","4","MC_weight*("+base_cut_emu+"&&"+tau_matching +")",5,0,5));
  h[0]->Add(single_plot(files_ttjets_DL,"HTauTauTree","4","MC_weight*("+base_cut_ee+"&&"+tau_matching +")",5,0,5));


  /*TLegend* leg=new TLegend(0.2,0.55,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->SetHeader("#splitline{2lSS, #leq 1#tau_{h} OS}{#leq 3 jets, 1CSVM + 1CSVL}");

  vector<TString> leg_entry;
  leg_entry.push_back("ttjets_DL 2 tight leptons");
  leg_entry.push_back("tt+jets 2 tight leptons");
  leg_entry.push_back("tt+jets tight+loose leptons");*/


  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/h[i]->Integral());
    //leg->AddEntry(h[i],leg_entry[i]);
  }



  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.);
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Matching index");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("");

  h[0]->Draw("");
  /*for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
    }*/
  


  //leg->Draw("same");

  TLatex *texl = new TLatex(0.1,1.02*h[0]->GetMaximum(),"CMS Preliminary, Simulation 13 TeV tt, t->bl#nu, t->bl#nu");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="tau_matching_ttjets_DL";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



