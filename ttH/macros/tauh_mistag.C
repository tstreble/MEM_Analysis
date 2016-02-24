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

using namespace std;




void plot_fake_flavor(){


  vector<TString> ttjets_files;
  for(unsigned int i=1; i<10; i++)
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i.root",i));


  vector<TH1F*> h;

  h.push_back(single_plot(ttjets_files,"HTauTauTree","abs(genpart_pdg[recotauh_i_closest_genpart[0]])*(abs(genpart_pdg[recotauh_i_closest_genpart[0]])<1000) + 30*(abs(genpart_pdg[recotauh_i_closest_genpart[0]])>1000)","PUReweight*MC_weight*aMCatNLOweight*(n_recotauh>0 && n_recolep>1 && recotauh_dR_closest_genpart[0]<0.3)",35,0,35));



  TLegend* leg=new TLegend(0.35,0.6,0.85,0.85);
  leg->SetHeader("#splitline{#splitline{tt+jets, n(lep)#geq2, n(#tau_{h})#geq1}{#DeltaR(gen,reco)<0.3}}{#splitline{#splitline{p_{T}(reco)>30 GeV, |#eta(reco)|<2.1}{#Delta#beta-corr. iso.<1.5 GeV, oldDM>0.5}}{antiMu tight3, anti-e VLoose MVA5}}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

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
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Flavor");
  h[0]->GetYaxis()->SetTitle("Fraction of events");
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Flavor of closest gen. part for reco. #tau_{h}");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="flavor_fake_ttjets";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_flavor(){


  vector<TString> ttjets_files;
  for(unsigned int i=1; i<10; i++)
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i.root",i));


  vector<TH1F*> h;

  h.push_back(single_plot(ttjets_files,"HTauTauTree","abs(genpart_pdg)*(abs(genpart_pdg)<1000) + 30*(abs(genpart_pdg)>1000)","PUReweight*MC_weight*aMCatNLOweight*(n_recotauh>0 && n_recolep>1)",35,0,35));



  TLegend* leg=new TLegend(0.35,0.6,0.85,0.85);
  leg->SetHeader("#splitline{#splitline{tt+jets, n(lep)#geq2, n(#tau_{h})#geq1}{}}{#splitline{#splitline{p_{T}(reco)>30 GeV, |#eta(reco)|<2.1}{#Delta#beta-corr. iso.<1.5 GeV, oldDM>0.5}}{antiMu tight3, anti-e VLoose MVA5}}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

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
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Flavor");
  h[0]->GetYaxis()->SetTitle("Fraction of events");
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Flavor of gen. part");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="flavor_ttjets";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_flavor_mistag_rate(){


  vector<TString> ttjets_files;
  for(unsigned int i=1; i<2; i++)
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i_old.root",i));


  TH1F* h_gen=single_plot(ttjets_files,"HTauTauTree","abs(genpart_pdg)","(abs(genpart_pdg)<6 || abs(genpart_pdg)==21) && genpart_pt>30 && abs(genpart_eta)<2.1",24,0,24);

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","abs(genpart_pdg[recotauh_i_closest_genpart])","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])<6 || abs(genpart_pdg[recotauh_i_closest_genpart])==21) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1",24,0,24));

  TLegend* leg=new TLegend(0.2,0.65,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);


  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",24,0,24));
    h_eff[i]->Divide(h[i],h_gen);
    h_eff[i]->SetLineColor(i+1);
    h_eff[i]->SetMarkerColor(i+1);
    if(i>3){
      h_eff[i]->SetLineColor(i+2);
      h_eff[i]->SetMarkerColor(i+2);
    }
    h_eff[i]->SetMarkerStyle(20+i);
    h_eff[i]->SetLineWidth(2);
    h_eff[i]->SetStats(0);
    //leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  h_eff[0]->SetMaximum(0.01);
  h_eff[0]->GetXaxis()->SetTitle("Flavor");
  h_eff[0]->GetYaxis()->SetTitle("Expected #tau efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("same");
  }
  
  //leg->Draw("same");

  TLatex *texl = new TLatex(0.5,0.011,"CMS #bf{#it{Simulation 13 TeV t#bar{t}}}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  TString filename="mistag_rate_tauh_ttjets";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}






void plot_flavor_mistag_rate_2lep(){


  vector<TString> ttjets_files;
  for(unsigned int i=1; i<2; i++)
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i_old.root",i));


  TH1F* h_gen=single_plot(ttjets_files,"HTauTauTree","abs(genpart_pdg)","(abs(genpart_pdg)<6 || abs(genpart_pdg)==21) && genpart_pt>30 && abs(genpart_eta)<2.1 && n_recolep>1",24,0,24);

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","abs(genpart_pdg[recotauh_i_closest_genpart])","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])<6 || abs(genpart_pdg[recotauh_i_closest_genpart])==21) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1 && n_recolep>1",24,0,24));

  TLegend* leg=new TLegend(0.5,0.65,0.7,0.87);
  leg->SetHeader("n(lep)#geq2");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);


  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",24,0,24));
    h_eff[i]->Divide(h[i],h_gen);
    h_eff[i]->SetLineColor(i+1);
    h_eff[i]->SetMarkerColor(i+1);
    if(i>3){
      h_eff[i]->SetLineColor(i+2);
      h_eff[i]->SetMarkerColor(i+2);
    }
    h_eff[i]->SetMarkerStyle(20+i);
    h_eff[i]->SetLineWidth(2);
    h_eff[i]->SetStats(0);
    //leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  h_eff[0]->SetMaximum(0.01);
  h_eff[0]->GetXaxis()->SetTitle("Flavor");
  h_eff[0]->GetYaxis()->SetTitle("Expected #tau efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(0.5,0.011,"CMS #bf{#it{Simulation 13 TeV t#bar{t}}}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  TString filename="mistag_rate_tauh_ttjets_2lep";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}







void plot_flavor_mistag_rate_pt(){


  vector<TString> ttjets_files;
  for(unsigned int i=1; i<2; i++)
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i_old.root",i));

  vector<TH1F*> h_gen;
  h_gen.push_back(single_plot(ttjets_files,"HTauTauTree","genpart_pt","(abs(genpart_pdg)<5) && genpart_pt>30 && abs(genpart_eta)<2.1",22,20,240));
  h_gen.push_back(single_plot(ttjets_files,"HTauTauTree","genpart_pt","(abs(genpart_pdg)==5) && genpart_pt>30 && abs(genpart_eta)<2.1",22,20,240));
  h_gen.push_back(single_plot(ttjets_files,"HTauTauTree","genpart_pt","(abs(genpart_pdg)==21) && genpart_pt>30 && abs(genpart_eta)<2.1",22,20,240));

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])<5) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1",22,20,240));
  h.push_back(single_plot(ttjets_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])==5) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1",22,20,240));
  h.push_back(single_plot(ttjets_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])==21) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1",22,20,240));

  TLegend* leg=new TLegend(0.2,0.65,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Light quarks");
  leg_entry.push_back("b quarks");
  leg_entry.push_back("Gluons");

  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",22,20,240));
    h_eff[i]->Divide(h[i],h_gen[i]);
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
  h_eff[0]->SetMaximum(0.05);
  h_eff[0]->SetMinimum(0.0001);
  h_eff[0]->GetXaxis()->SetRangeUser(20,260);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}(gen)");
  h_eff[0]->GetYaxis()->SetTitle("Expected #tau efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(30,0.051,"CMS #bf{#it{Simulation 13 TeV t#bar{t}}}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  TString filename="mistag_rate_tauh_ttjets_pt";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}







void plot_flavor_mistag_rate_pt_2lep(){


  vector<TString> ttjets_files;
  for(unsigned int i=1; i<2; i++)
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i_old.root",i));

  vector<TH1F*> h_gen;
  h_gen.push_back(single_plot(ttjets_files,"HTauTauTree","genpart_pt","(abs(genpart_pdg)<5) && genpart_pt>30 && abs(genpart_eta)<2.1 && n_recolep>1",22,20,240));
  h_gen.push_back(single_plot(ttjets_files,"HTauTauTree","genpart_pt","(abs(genpart_pdg)==5) && genpart_pt>30 && abs(genpart_eta)<2.1 && n_recolep>1",22,20,240));
  h_gen.push_back(single_plot(ttjets_files,"HTauTauTree","genpart_pt","(abs(genpart_pdg)==21) && genpart_pt>30 && abs(genpart_eta)<2.1 && n_recolep>1",22,20,240));

  vector<TH1F*> h;
  h.push_back(single_plot(ttjets_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])<5) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1 && n_recolep>1",22,20,240));
  h.push_back(single_plot(ttjets_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])==5) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1 && n_recolep>1",22,20,240));
  h.push_back(single_plot(ttjets_files,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg)==21) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1 && n_recolep>1",22,20,240));

  TLegend* leg=new TLegend(0.2,0.65,0.5,0.87);
  leg->SetHeader("n(lep)#geq2");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Light quarks");
  leg_entry.push_back("b quarks");
  leg_entry.push_back("Gluons");

  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",22,20,240));
    h_eff[i]->Divide(h[i],h_gen[i]);
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
  h_eff[0]->SetMaximum(0.02);
  h_eff[0]->SetMinimum(0.0001);
  h_eff[0]->GetXaxis()->SetRangeUser(20,260);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}(gen)");
  h_eff[0]->GetYaxis()->SetTitle("Expected #tau efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(30,0.021,"CMS #bf{#it{Simulation 13 TeV t#bar{t}}}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  TString filename="mistag_rate_tauh_ttjets_pt_2lep";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}





void plot_fake_flavor_SS(){


  vector<TString> ttjets_files;
  for(unsigned int i=1; i<10; i++)
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i.root",i));


  vector<TH1F*> h;

  h.push_back(single_plot(ttjets_files,"HTauTauTree","abs(genpart_pdg[recotauh_i_closest_genpart[0]])*(abs(genpart_pdg[recotauh_i_closest_genpart[0]])<1000) + 30*(abs(genpart_pdg[recotauh_i_closest_genpart[0]])>1000)","PUReweight*MC_weight*aMCatNLOweight*(n_recotauh>0 && n_recolep==2 && recolep_charge[0]*recolep_charge[1]==1 && recotauh_dR_closest_genpart[0]<0.3)",35,0,35));



  TLegend* leg=new TLegend(0.35,0.6,0.85,0.85);
  leg->SetHeader("#splitline{#splitline{tt+jets, 2 lep. SS, n(#tau_{h})#geq1}{#DeltaR(gen,reco)<0.3}}{#splitline{#splitline{p_{T}(reco)>30 GeV, |#eta(reco)|<2.1}{#Delta#beta-corr. iso.<1.5 GeV, oldDM>0.5}}{antiMu tight3, anti-e VLoose MVA5}}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

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
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Flavor");
  h[0]->GetYaxis()->SetTitle("Fraction of events");
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Flavor of closest gen. part for reco. #tau_{h}");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="flavor_fake_ttjets_2lSS";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_fake_flavor_SS_4j(){


  vector<TString> ttjets_files;
  for(unsigned int i=1; i<10; i++)
    ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i.root",i));


  vector<TH1F*> h;

  h.push_back(single_plot(ttjets_files,"HTauTauTree","abs(genpart_pdg[recotauh_i_closest_genpart[0]])*(abs(genpart_pdg[recotauh_i_closest_genpart[0]])<1000) + 30*(abs(genpart_pdg[recotauh_i_closest_genpart[0]])>1000)","PUReweight*MC_weight*aMCatNLOweight*(n_recotauh>0 && n_recolep==2 && recotauh_dR_closest_genpart[0]<0.3 && n_recoPFJet30>=4 && n_recoPFJet30_btag_medium>=1)",35,0,35));

  cout<<"h[0]->GetEntries()="<<h[0]->GetEntries()<<endl;

  TLegend* leg=new TLegend(0.35,0.6,0.85,0.85);
  leg->SetHeader("#splitline{tt+jets, 2 lep. SS, n(#tau_{h})#geq1}{n(jets)#geq4, n(CSVM)#geq1}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

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
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("Flavor");
  h[0]->GetYaxis()->SetTitle("Fraction of events");
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Flavor of closest gen. part for reco. #tau_{h}");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="flavor_fake_ttjets_2lSS";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_flavor_mistag_rate_pt_iso50(){


  /*vector<TString> ttjets_files;
  for(unsigned int i=1; i<2; i++)
  ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i_old.root",i));*/

  TString ttH_file="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_iso50.root";

  vector<TH1F*> h_gen;
  h_gen.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt","(abs(genpart_pdg)<5) && genpart_pt>30 && abs(genpart_eta)<2.1",22,20,240));
  h_gen.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt","(abs(genpart_pdg)==5) && genpart_pt>30 && abs(genpart_eta)<2.1",22,20,240));
  h_gen.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt","(abs(genpart_pdg)==21) && genpart_pt>30 && abs(genpart_eta)<2.1",22,20,240));
  h_gen.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt","(abs(genpart_pdg)>1000) && genpart_pt>30 && abs(genpart_eta)<2.1",22,20,240));

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])<5) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1",22,20,240));
  h.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])==5) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1",22,20,240));
  h.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])==21) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1",22,20,240));
  h.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])>1000) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1",22,20,240));

  TLegend* leg=new TLegend(0.2,0.65,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Light quarks");
  leg_entry.push_back("b quarks");
  leg_entry.push_back("Gluons");
  leg_entry.push_back("#tau_{h}");

  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",22,20,240));
    h_eff[i]->Divide(h[i],h_gen[i]);
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
  h_eff[0]->SetMinimum(0.0001);
  h_eff[0]->GetXaxis()->SetRangeUser(20,260);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}(gen)");
  h_eff[0]->GetYaxis()->SetTitle("Expected #tau efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(30,1.1,"CMS #bf{#it{Simulation 13 TeV ttH}}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  TString filename="mistag_rate_tauh_ttH_pt_iso50";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}







void plot_flavor_mistag_rate_pt_ttH(){


  /*vector<TString> ttjets_files;
  for(unsigned int i=1; i<2; i++)
  ttjets_files.push_back(Form("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/TTJets_prod_27082015/ntuple_TTJets_dRveto_gen_%i_old.root",i));*/

  TString ttH_file="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root";

  vector<TH1F*> h_gen;
  h_gen.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt","(abs(genpart_pdg)<5) && genpart_pt>30 && abs(genpart_eta)<2.1",22,20,240));
  h_gen.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt","(abs(genpart_pdg)==5) && genpart_pt>30 && abs(genpart_eta)<2.1",22,20,240));
  h_gen.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt","(abs(genpart_pdg)==21) && genpart_pt>30 && abs(genpart_eta)<2.1",22,20,240));
  //h_gen.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt","(abs(genpart_pdg)>1000) && genpart_pt>30 && abs(genpart_eta)<2.1",22,20,240));

  vector<TH1F*> h;
  h.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])<5) && genpart_pt[recotauh_i_closest_genpart]>30 && genpart_pt[recotauh_i_closest_genpart]<240 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1",22,20,240));
  h.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])==5) && genpart_pt[recotauh_i_closest_genpart]>30 && genpart_pt[recotauh_i_closest_genpart]<240 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1",22,20,240));
  h.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])==21) && genpart_pt[recotauh_i_closest_genpart]>30 && genpart_pt[recotauh_i_closest_genpart]<240 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1",22,20,240));
  //h.push_back(single_plot(ttH_file,"HTauTauTree","genpart_pt[recotauh_i_closest_genpart]","n_recotauh>0 && recotauh_dR_closest_genpart<0.3 && (abs(genpart_pdg[recotauh_i_closest_genpart])>1000) && genpart_pt[recotauh_i_closest_genpart]>30 && abs(genpart_eta[recotauh_i_closest_genpart])<2.1",22,20,240));

  TLegend* leg=new TLegend(0.2,0.65,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);

  vector<TString> leg_entry;
  leg_entry.push_back("Light quarks");
  leg_entry.push_back("b quarks");
  leg_entry.push_back("Gluons");
  //leg_entry.push_back("#tau_{h}");

  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",22,20,240));
    h_eff[i]->Divide(h[i],h_gen[i]);
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
  h_eff[0]->SetMaximum(0.05);
  h_eff[0]->SetMinimum(0.0001);
  h_eff[0]->GetXaxis()->SetRangeUser(20,260);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}(gen)");
  h_eff[0]->GetYaxis()->SetTitle("Expected #tau efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);


  h_eff[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(30,0.06,"CMS #bf{#it{Simulation 13 TeV ttH, H->#tau#tau}}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  TString filename="mistag_rate_tauh_ttH_pt";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;
  
  

}

