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
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recolep","PUReweight*MC_weight",10,0,10));
  
  vector<TString> ttjets_files;
  for(unsigned int i=1; i<10; i++)
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i.root",i));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","n_recolep","PUReweight*MC_weight*aMCatNLOweight",10,0,10));
 
  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("tt+jets");


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


  TString filename="n_lep_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_n_tauh(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recotauh","PUReweight*MC_weight",10,0,10));

  vector<TString> ttjets_files;
  for(unsigned int i=1; i<10; i++)
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i.root",i));

  h.push_back(single_plot(ttjets_files,"HTauTauTree","n_recotauh","PUReweight*MC_weight*aMCatNLOweight",10,0,10));
 
  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("tt+jets");

 

  TLegend* leg=new TLegend(0.55,0.7,0.85,0.85);
  leg->SetHeader("p_{T}>30 GeV, |#eta|<2.1");
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
  h[0]->GetXaxis()->SetTitle("n(#tau_{h})");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Number of #tau_{h}");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_tauh_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_n_lep_tauh(){

  TH2F* h=single_plot2D("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recolep","n_recotauh","PUReweight*MC_weight",10,0,10,10,0,10);
  
  /*vector<TString> leg_entry;
  leg_entry.push_back("Leptons p_{T}>24 GeV");
 

  TLegend* leg=new TLegend(0.5,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);*/

  h->SetStats(0);
  //h->Scale(1/h->Integral());
 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetRightMargin(0.2);
  h->GetXaxis()->SetTitle("n(lep)");
  h->GetYaxis()->SetTitle("n(#tau_{h})");
  h->GetZaxis()->SetTitle("a.u.");
  h->GetZaxis()->SetTitleOffset(1.3);
  h->SetTitle("Number of lep and #tau_{h} in the ttH sample");

  h->Draw("colz");
  gPad->SetLogz();


  TString filename="n_lep_tauh_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_n_lep_tauh_ttjets(){

  vector<TString> ttjets_files;
  for(unsigned int i=1; i<10; i++){
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i.root",i));
  }

  TH2F* h=single_plot2D(ttjets_files,"HTauTauTree","n_recolep","n_recotauh","PUReweight*MC_weight*aMCatNLOweight*(n_recolep<5 && n_recotauh<5)",10,0,10,10,0,10);
  //TH2F* h=single_plot2D(ttjets_files,"HTauTauTree","n_recolep","n_recotauh","",10,0,10,10,0,10);
  
  /*vector<TString> leg_entry;
  leg_entry.push_back("Leptons p_{T}>24 GeV");
 

  TLegend* leg=new TLegend(0.5,0.65,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);*/

  h->SetStats(0);
  //h->Scale(1/h->Integral());
 
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetRightMargin(0.2);
  h->GetXaxis()->SetTitle("n(lep)");
  h->GetYaxis()->SetTitle("n(#tau_{h})");
  h->GetZaxis()->SetTitle("a.u.");
  h->GetZaxis()->SetTitleOffset(1.3);
  h->SetTitle("Number of lep and #tau_{h} in the tt+jets sample");

  h->Draw("colz");
  gPad->SetLogz();


  TString filename="n_lep_tauh_ttjets_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_n_PFjets30(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*(n_recolep>1&&n_recotauh>0)",15,0,15));

  vector<TString> ttjets_files;
  for(unsigned int i=1; i<10; i++){
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i.root",i));
  }

  h.push_back(single_plot(ttjets_files,"HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*aMCatNLOweight*(n_recolep>1&&n_recotauh>0)",15,0,15));

  vector<TString> leg_entry;
  leg_entry.push_back("ttH");
  leg_entry.push_back("tt+jets");

  TLegend* leg=new TLegend(0.5,0.5,0.85,0.85);
  leg->SetHeader("#splitline{#geq 2 lep., #geq 1 #tau_{h}}{p_{T}>30 GeV, |#eta|<3}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    float norm=h[i]->Integral();
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    h[i]->Scale(1/norm);
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("n(jets)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Number of jets");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_PFJet30_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_n_PFjets30_cat(){

  vector<TH1F*> h;
 
  TH1F* h_norm=(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*(n_recolep>1&&n_recotauh>0)",18,0,18));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0)",18,0,18));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0)",18,0,18));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*(n_recolep>2&&n_recotauh>0)",18,0,18));
  
  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back(Form("2 lep. OS, #geq 1 #tau_{h} (%.0f%)",100*h[0]->Integral()/h_norm->Integral()));
  leg_entry.push_back(Form("2 lep. SS, #geq 1 #tau_{h} (%.0f%)",100*h[1]->Integral()/h_norm->Integral()));
  leg_entry.push_back(Form("#geq 3 lep., #geq 1 #tau_{h} (%.0f%)",100*h[2]->Integral()/h_norm->Integral()));


  TLegend* leg=new TLegend(0.5,0.6,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("n(jets)");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Number of jets in ttH sample");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_PFJet30_cat_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_n_PFjets30_cat_ttjets(){

  vector<TString> ttjets_files;
  for(unsigned int i=1; i<10; i++){
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i.root",i));
  }

  vector<TH1F*> h;
 
  TH1F* h_norm=(single_plot(ttjets_files,"HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*aMCatNLOweight*(n_recolep>1&&n_recotauh>0)",18,0,18));
  h.push_back(single_plot(ttjets_files,"HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*aMCatNLOweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0)",18,0,18));
  h.push_back(single_plot(ttjets_files,"HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*aMCatNLOweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0)",18,0,18));
  //h.push_back(single_plot(ttjets_files,"HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*aMCatNLOweight*(n_recolep>2&&n_recotauh>0)",18,0,18));
  
  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back(Form("2 lep. OS, #geq 1 #tau_{h} (%.0f%)",100*h[0]->Integral()/h_norm->Integral()));
  leg_entry.push_back(Form("2 lep. SS, #geq 1 #tau_{h} (%.0f%)",100*h[1]->Integral()/h_norm->Integral()));
  //leg_entry.push_back(Form("#geq 3 lep., #geq 1 #tau_{h} (%.0f%)",100*h[2]->Integral()/h_norm->Integral()));


  TLegend* leg=new TLegend(0.5,0.6,0.75,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("n(jets)");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Number of jets in tt+jets sample");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_PFJet30_cat_ttjets_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_n_PFjets30_btag_medium_cat(){

  vector<TH1F*> h;
 
  TH1F* h_norm=(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*(n_recolep>1&&n_recotauh>0)",18,0,18));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30_btag_medium","PUReweight*MC_weight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30_btag_medium","PUReweight*MC_weight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30_btag_medium","PUReweight*MC_weight*(n_recolep>2&&n_recotauh>0)",5,0,5));
  
  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back(Form("2 lep. OS, #geq 1 #tau_{h} (%.0f%)",100*h[0]->Integral()/h_norm->Integral()));
  leg_entry.push_back(Form("2 lep. SS, #geq 1 #tau_{h} (%.0f%)",100*h[1]->Integral()/h_norm->Integral()));
  leg_entry.push_back(Form("#geq 3 lep., #geq 1 #tau_{h} (%.0f%)",100*h[2]->Integral()/h_norm->Integral()));


  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetHeader("b-tag = CSVM #xi>0.814");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("n(jets)");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Number of b-tagged jets with p_{T}>30 GeV");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_PFJet30_btag_medium_cat_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_n_PFjets30_btag_medium_cat_ttjets(){

  vector<TString> ttjets_files;
  for(unsigned int i=1; i<10; i++){
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i.root",i));
  }

  vector<TH1F*> h;
 
  TH1F* h_norm=(single_plot(ttjets_files,"HTauTauTree","n_recoPFJet30_btag_medium","PUReweight*MC_weight*aMCatNLOweight*(n_recolep>1&&n_recotauh>0)",18,0,18));
  h.push_back(single_plot(ttjets_files,"HTauTauTree","n_recoPFJet30_btag_medium","PUReweight*MC_weight*aMCatNLOweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0)",5,0,5));
  h.push_back(single_plot(ttjets_files,"HTauTauTree","n_recoPFJet30_btag_medium","PUReweight*MC_weight*aMCatNLOweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0)",5,0,5));

  
  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back(Form("2 lep. OS, #geq 1 #tau_{h} (%.0f%)",100*h[0]->Integral()/h_norm->Integral()));
  leg_entry.push_back(Form("2 lep. SS, #geq 1 #tau_{h} (%.0f%)",100*h[1]->Integral()/h_norm->Integral()));


  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetHeader("b-tag = CSVM #xi>0.814");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("n(jets)");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Number of b-tagged jets with p_{T}>30 GeV");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_PFJet30_btag_medium_cat_ttjets_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_n_PFjets30_btag_loose_cat(){

  vector<TH1F*> h;
 
  TH1F* h_norm=(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*(n_recolep>1&&n_recotauh>0)",18,0,18));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30_btag_loose","PUReweight*MC_weight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0)",7,0,7));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30_btag_loose","PUReweight*MC_weight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0)",7,0,7));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recoPFJet30_btag_loose","PUReweight*MC_weight*(n_recolep>2&&n_recotauh>0)",7,0,7));
  
  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back(Form("2 lep. OS, #geq 1 #tau_{h} (%.0f%)",100*h[0]->Integral()/h_norm->Integral()));
  leg_entry.push_back(Form("2 lep. SS, #geq 1 #tau_{h} (%.0f%)",100*h[1]->Integral()/h_norm->Integral()));
  leg_entry.push_back(Form("#geq 3 lep., #geq 1 #tau_{h} (%.0f%)",100*h[2]->Integral()/h_norm->Integral()));


  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetHeader("b-tag = CSVL  #xi>0.423");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->GetXaxis()->SetTitle("n(jets)");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Number of b-tagged jets with p_{T}>30 GeV");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_PFJet30_btag_loose_cat_ttH_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_n_PFjets30_btag_loose_cat_ttjets(){

  vector<TString> ttjets_files;
  for(unsigned int i=1; i<10; i++){
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i.root",i));
  }

  vector<TH1F*> h;
 
  TH1F* h_norm=(single_plot(ttjets_files,"HTauTauTree","n_recoPFJet30","PUReweight*MC_weight*aMCatNLOweight*(n_recolep>1&&n_recotauh>0)",18,0,18));
  h.push_back(single_plot(ttjets_files,"HTauTauTree","n_recoPFJet30_btag_loose","PUReweight*MC_weight*aMCatNLOweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]<0&&n_recotauh>0)",7,0,7));
  h.push_back(single_plot(ttjets_files,"HTauTauTree","n_recoPFJet30_btag_loose","PUReweight*MC_weight*aMCatNLOweight*(n_recolep==2&&recolep_charge[0]*recolep_charge[1]>0&&n_recotauh>0)",7,0,7));

  
  vector<TString> leg_entry;
  //leg_entry.push_back("#geq 2 lep., #geq 1 #tau_{h}");
  leg_entry.push_back(Form("2 lep. OS, #geq 1 #tau_{h} (%.0f%)",100*h[0]->Integral()/h_norm->Integral()));
  leg_entry.push_back(Form("2 lep. SS, #geq 1 #tau_{h} (%.0f%)",100*h[1]->Integral()/h_norm->Integral()));



  TLegend* leg=new TLegend(0.5,0.65,0.75,0.85);
  leg->SetHeader("b-tag = CSVL  #xi>0.423");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
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
  h[0]->SetMinimum(0);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("n(jets)");
  //h[0]->GetYaxis()->SetTitle(Form("Fraction of events with #geq 2 lep., #geq 1 #tau_{h} / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Number of b-tagged jets with p_{T}>30 GeV");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_PFJet30_btag_loose_cat_ttjets_dRveto";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}
