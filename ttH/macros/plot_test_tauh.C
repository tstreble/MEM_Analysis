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

using namespace std;




void plot_n_tauh(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_recotauh","",6,0,6));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen.root","HTauTauTree","n_gentauh30_eta21","",6,0,6));
  
  vector<TString> leg_entry;
  leg_entry.push_back("Reco.");
  leg_entry.push_back("Gen.");


  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
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
  h[0]->SetTitle("ttH, H->#tau#tau events");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_tauh_ttH_dRveto_gen";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_n_tauh_skim(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","n_recotauh","",6,0,6));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","n_gentauh30_eta21","",6,0,6));
  
  vector<TString> leg_entry;
  leg_entry.push_back("Reco.");
  leg_entry.push_back("Gen.");


  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
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
  h[0]->SetTitle("ttH, t->bqq, t->bl#nu, H->l#tau_{h} events");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="n_tauh_ttH_dRveto_genskimm";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_dR_tauh_match(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","genpi_dR_daughter_matched","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_i_daughter_matched>-1 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",50,0,0.1));


  
  vector<TString> leg_entry;
  //leg_entry.push_back("Reco. p_{T}>30 GeV, |#eta|<2.1");


  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
  leg->SetHeader("#splitline{p_{T}>30 GeV , |#eta|<2.1}{gen. + reco.");
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
  h[0]->GetXaxis()->SetTitle("#DeltaR(gen,reco)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("ttH, t->bqq, t->bl#nu, H->l#tau_{h} events");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  //leg->Draw("same");


  TString filename="dR_tauh_matched_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_pT_res_tauh_match(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","(sqrt(daughters_px[genpi_i_daughter_matched]**2+daughters_py[genpi_i_daughter_matched]**2) - genpi_pt) / genpi_pt","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",50,-1,1));


  
  vector<TString> leg_entry;


  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
  leg->SetHeader("#splitline{p_{T}>30 GeV , |#eta|<2.1}{gen. + reco., #DeltaR<0.3}");
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
  h[0]->GetXaxis()->SetTitle("(p_{T}(reco)-p_{T}(gen))/p_{T}(gen)");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("ttH, t->bqq, t->bl#nu, H->l#tau_{h} events");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  //leg->Draw("same");


  TString filename="pT_res_tauh_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_mass_tauh_match(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt((genpi_e)**2-(genpi_px)**2-(genpi_py)**2-(genpi_pz)**2)","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1)",50,0,2));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt(daughters_e[genpi_i_daughter_matched]**2-daughters_px[genpi_i_daughter_matched]**2-daughters_py[genpi_i_daughter_matched]**2-daughters_pz[genpi_i_daughter_matched]**2)","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",50,0,2));


  
  vector<TString> leg_entry;
  leg_entry.push_back("Gen.");
  leg_entry.push_back("Reco.");


  TLegend* leg=new TLegend(0.4,0.65,0.85,0.85);
  leg->SetHeader("#splitline{p_{T}>30 GeV , |#eta|<2.1}{gen. + reco., #DeltaR<0.3}");
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
  h[0]->GetXaxis()->SetTitle("m [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("ttH, t->bqq, t->bl#nu, H->l#tau_{h} events");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="mass_tauh_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_quality_tauh_match(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_againstMuonTight3[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_againstElectronMediumMVA5[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]<1.5","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","(daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]<1.5)*daughters_againstElectronMediumMVA5[genpi_i_daughter_matched]*daughters_againstMuonTight3[genpi_i_daughter_matched]*daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));
  
  vector<TString> leg_entry;
  leg_entry.push_back("Decay mode finding");
  leg_entry.push_back("Anti-#mu tight 3");
  leg_entry.push_back("Anti-e medium MVA 5");
  leg_entry.push_back("#splitline{Comb. iso. #Delta#beta}{corr. 3 hits < 1.5}");
  leg_entry.push_back("All");

  TLegend* leg=new TLegend(0.47,0.3,0.85,0.75);
  leg->SetHeader("#splitline{p_{T}>30 GeV , |#eta|<2.1}{gen. + reco., #DeltaR<0.3}");
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


  TString filename="quality_tauh_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_isoflag_tauh_match(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]<1.5","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_byTightCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_byMediumCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));

  
  vector<TString> leg_entry;
  leg_entry.push_back("#splitline{Comb. iso. #Delta#beta}{corr. 3 hits < 1.5}");
  leg_entry.push_back("#splitline{Tight comb. iso.}{#Delta#beta corr. 3 hits}");
  leg_entry.push_back("#splitline{Medium comb. iso.}{#Delta#beta corr. 3 hits}");
  leg_entry.push_back("#splitline{Loose comb. iso.}{#Delta#beta corr. 3 hits}");

  TLegend* leg=new TLegend(0.47,0.3,0.85,0.75);
  leg->SetHeader("#splitline{p_{T}>30 GeV , |#eta|<2.1}{gen. + reco., #DeltaR<0.3}");
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
  h[0]->GetXaxis()->SetTitle("flag");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("ttH, t->bqq, t->bl#nu, H->l#tau_{h} events");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="isoflag_tauh_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



void plot_iso_tauh_match(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen_skimmed.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",50,0,20));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",50,0,20));

  
  vector<TString> leg_entry;
  leg_entry.push_back("VBF");
  leg_entry.push_back("ttH");


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
  h[0]->GetXaxis()->SetTitle("isolation [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Combined isolation #Delta#beta corrected raw 3 hits");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="iso_tauh_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



void plot_quality_tauh_match2(){

  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","(daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]<1.5)*daughters_againstElectronMediumMVA5[genpi_i_daughter_matched]*daughters_againstMuonTight3[genpi_i_daughter_matched]*daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_againstElectronMediumMVA5[genpi_i_daughter_matched]*daughters_againstMuonTight3[genpi_i_daughter_matched]*daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","(daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]<1.5)*daughters_againstMuonTight3[genpi_i_daughter_matched]*daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","(daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]<1.5)*daughters_againstElectronMediumMVA5[genpi_i_daughter_matched]*daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","(daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits[genpi_i_daughter_matched]<1.5)*daughters_againstElectronMediumMVA5[genpi_i_daughter_matched]*daughters_againstMuonTight3[genpi_i_daughter_matched]","PUReweight*(genpi_pt>30 && abs(genpi_eta)<2.1 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>30 && abs(daughters_eta[genpi_i_daughter_matched])<2.1)",5,0,5));  

  vector<TString> leg_entry;
  leg_entry.push_back("All");
  leg_entry.push_back("All but iso");
  leg_entry.push_back("All but anti-e");
  leg_entry.push_back("All but anti-#mu");
  leg_entry.push_back("#splitline{All but decay mode}{finding}");

  TLegend* leg=new TLegend(0.47,0.3,0.85,0.75);
  leg->SetHeader("#splitline{p_{T}>30 GeV , |#eta|<2.1}{gen. + reco., #DeltaR<0.3}");
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


  TString filename="quality2_tauh_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_tau_reco_eff(){


  TH1F* h_gen = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","genpi_pt","PUReweight*(genpi_pt>20 && genpi_pt<120 && abs(genpi_eta)<2.3)",10,20,120);


  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","genpi_pt","PUReweight*(genpi_pt>20 && genpi_pt<120 && abs(genpi_eta)<2.3 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1)",10,20,120));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","genpi_pt","PUReweight*(genpi_pt>20 && genpi_pt<120 && abs(genpi_eta)<2.3 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1)",10,20,120));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","genpi_pt","PUReweight*(genpi_pt>20 && genpi_pt<120 && abs(genpi_eta)<2.3 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byMediumCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1)",10,20,120));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","genpi_pt","PUReweight*(genpi_pt>20 && genpi_pt<120 && abs(genpi_eta)<2.3 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byTightCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1)",10,20,120));

  vector<TString> leg_entry;
  leg_entry.push_back("No isolation");
  leg_entry.push_back("Cut-based isolation loose");
  leg_entry.push_back("Cut-based isolation medium");
  leg_entry.push_back("Cut-based isolation tight");

  TLegend* leg=new TLegend(0.2,0.65,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);


  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",10,20,120));
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
    leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_eff[0]->SetMaximum(1.19);
  h_eff[0]->SetMinimum(0);
  h_eff[0]->GetXaxis()->SetRangeUser(10,130);
  h_eff[0]->GetXaxis()->SetTitle("generated p_{T}^{#tau} [GeV]");
  h_eff[0]->GetYaxis()->SetTitle("Expected #tau efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);

  h_eff[0]->Draw("E");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("sameE");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(8,1.25,"CMS #bf{#it{Simulation 13 TeV ttH, t->bl#nu, t->bqq, H->#tau#tau->l#tau_{h}}}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  TString filename="eff_reco_tauh_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}





void plot_tau_anti_lep_eff(){

  TH1F* h_match = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_pt[genpi_i_daughter_matched]","PUReweight*(genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && daughters_pt[genpi_i_daughter_matched]<120 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1)",10,20,120);


  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_pt[genpi_i_daughter_matched]","PUReweight*(genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && daughters_pt[genpi_i_daughter_matched]<120 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1 && daughters_againstElectronVLooseMVA5[genpi_i_daughter_matched]==1)",10,20,120));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_pt[genpi_i_daughter_matched]","PUReweight*(genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && daughters_pt[genpi_i_daughter_matched]<120 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1 && daughters_againstMuonTight3[genpi_i_daughter_matched]==1)",10,20,120));

 


  vector<TString> leg_entry;
  leg_entry.push_back("Anti-e very loose MVA 5");
  leg_entry.push_back("Anti-#mu tight 3");

  TLegend* leg=new TLegend(0.2,0.3,0.5,0.5);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);


  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",10,20,120));
    h_eff[i]->Divide(h[i],h_match);
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
  h_eff[0]->SetMaximum(1.19);
  h_eff[0]->SetMinimum(0);
  h_eff[0]->GetXaxis()->SetRangeUser(10,130);
  h_eff[0]->GetXaxis()->SetTitle("reconstructed p_{T}^{#tau} [GeV]");
  h_eff[0]->GetYaxis()->SetTitle("Expected #tau efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);

  h_eff[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(8,1.25,"CMS #bf{#it{Simulation 13 TeV ttH, t->bl#nu, t->bqq, H->#tau#tau->l#tau_{h}}}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  TString filename="eff_anti_lep_tauh_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}






void plot_tau_anti_ele_eff(){

  TH1F* h_match = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_pt[genpi_i_daughter_matched]","PUReweight*(genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && daughters_pt[genpi_i_daughter_matched]<120 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1)",10,20,120);


  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_pt[genpi_i_daughter_matched]","PUReweight*(genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && daughters_pt[genpi_i_daughter_matched]<120 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1 && daughters_againstElectronVLooseMVA5[genpi_i_daughter_matched]==1)",10,20,120));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_pt[genpi_i_daughter_matched]","PUReweight*(genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && daughters_pt[genpi_i_daughter_matched]<120 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1 && daughters_againstElectronLooseMVA5[genpi_i_daughter_matched]==1)",10,20,120));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_pt[genpi_i_daughter_matched]","PUReweight*(genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && daughters_pt[genpi_i_daughter_matched]<120 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1 && daughters_againstElectronMediumMVA5[genpi_i_daughter_matched]==1)",10,20,120));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_pt[genpi_i_daughter_matched]","PUReweight*(genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && daughters_pt[genpi_i_daughter_matched]<120 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1 && daughters_againstElectronTightMVA5[genpi_i_daughter_matched]==1)",10,20,120));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_pt[genpi_i_daughter_matched]","PUReweight*(genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && daughters_pt[genpi_i_daughter_matched]<120 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1 && daughters_againstElectronVTightMVA5[genpi_i_daughter_matched]==1)",10,20,120));


  vector<TString> leg_entry;
  /*leg_entry.push_back(Form("Anti-e very loose MVA 5 <#epsilon>=%.3f",h[0]->Integral()/h_match->Integral()));
  leg_entry.push_back(Form("Anti-e loose MVA 5 <#epsilon>=%.3f",h[1]->Integral()/h_match->Integral()));
  leg_entry.push_back(Form("Anti-e medium MVA 5 <#epsilon>=%.3f",h[2]->Integral()/h_match->Integral()));
  leg_entry.push_back(Form("Anti-e tight MVA 5 <#epsilon>=%.3f",h[3]->Integral()/h_match->Integral()));
  leg_entry.push_back(Form("Anti-e very tight MVA 5 <#epsilon>=%.3f",h[4]->Integral()/h_match->Integral()));*/

  leg_entry.push_back("Anti-e very loose MVA 5");
  leg_entry.push_back("Anti-e loose MVA 5");
  leg_entry.push_back("Anti-e medium MVA 5");
  leg_entry.push_back("Anti-e tight MVA 5");
  leg_entry.push_back("Anti-e very tight MVA 5");

  TLegend* leg=new TLegend(0.2,0.2,0.5,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);


  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",10,20,120));
    h_eff[i]->Divide(h[i],h_match);
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
  h_eff[0]->SetMaximum(1.19);
  h_eff[0]->SetMinimum(0);
  h_eff[0]->GetXaxis()->SetRangeUser(10,130);
  h_eff[0]->GetXaxis()->SetTitle("reconstructed p_{T}^{#tau} [GeV]");
  h_eff[0]->GetYaxis()->SetTitle("Expected #tau efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);

  h_eff[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(8,1.25,"CMS #bf{#it{Simulation 13 TeV ttH, t->bl#nu, t->bqq, H->#tau#tau->l#tau_{h}}}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  TString filename="eff_anti_ele_tauh_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}






void plot_tau_anti_mu_eff(){

  TH1F* h_match = single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_pt[genpi_i_daughter_matched]","PUReweight*(genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && daughters_pt[genpi_i_daughter_matched]<120 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1)",10,20,120);


  vector<TH1F*> h;
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_pt[genpi_i_daughter_matched]","PUReweight*(genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && daughters_pt[genpi_i_daughter_matched]<120 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1 && daughters_againstMuonLoose3[genpi_i_daughter_matched]==1)",10,20,120));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","daughters_pt[genpi_i_daughter_matched]","PUReweight*(genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && daughters_pt[genpi_i_daughter_matched]<120 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && daughters_byLooseCombinedIsolationDeltaBetaCorr3Hits[genpi_i_daughter_matched]==1 && daughters_againstMuonTight3[genpi_i_daughter_matched]==1)",10,20,120));


  vector<TString> leg_entry;
  /*leg_entry.push_back(Form("Anti-#mu loose 3 <#epsilon>=%.3f",h[0]->Integral()/h_match->Integral()));
  leg_entry.push_back(Form("Anti-#mu tight 3 <#epsilon>=%.3f",h[1]->Integral()/h_match->Integral()));*/

  leg_entry.push_back("Anti-#mu loose 3");
  leg_entry.push_back("Anti-#mu tight 3");
 

  TLegend* leg=new TLegend(0.2,0.2,0.5,0.45);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);


  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",10,20,120));
    h_eff[i]->Divide(h[i],h_match);
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
  h_eff[0]->SetMaximum(1.05);
  h_eff[0]->SetMinimum(0.9);
  h_eff[0]->GetXaxis()->SetRangeUser(10,130);
  h_eff[0]->GetXaxis()->SetTitle("reconstructed p_{T}^{#tau} [GeV]");
  h_eff[0]->GetYaxis()->SetTitle("Expected #tau efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);

  h_eff[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("same");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(8,1.055,"CMS #bf{#it{Simulation 13 TeV ttH, t->bl#nu, t->bqq, H->#tau#tau->l#tau_{h}}}");
  texl->SetTextSize(0.04);
  texl->Draw("same");

  TString filename="eff_anti_mu_tauh_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}








void plot_tau_reco_eff2(){

  TString ttH_sample="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_skimmed/ttH/ntuple_ttH_Htautau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_skimmed.root";


  TH1F* h_gen = single_plot(ttH_sample,"HTauTauTree","genpi_pt","(genpi_pt>20 && genpi_pt<120 && abs(genpi_eta)<2.3)",10,20,120);


  vector<TH1F*> h;
  h.push_back(single_plot(ttH_sample,"HTauTauTree","genpi_pt","(genpi_pt>20 && genpi_pt<120 && abs(genpi_eta)<2.3 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1)",10,20,120));
  h.push_back(single_plot(ttH_sample,"HTauTauTree","genpi_pt","(genpi_pt>20 && genpi_pt<120 && abs(genpi_eta)<2.3 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && ((tauID[genpi_i_daughter_matched]>>3)&1)==1)",10,20,120));
  h.push_back(single_plot(ttH_sample,"HTauTauTree","genpi_pt","(genpi_pt>20 && genpi_pt<120 && abs(genpi_eta)<2.3 && genpi_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genpi_i_daughter_matched])==15 && daughters_pt[genpi_i_daughter_matched]>20 && abs(daughters_eta[genpi_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genpi_i_daughter_matched]==1 && ((tauID[genpi_i_daughter_matched]>>27)&1)==1)",10,20,120));


  vector<TString> leg_entry;
  leg_entry.push_back("No isolation");
  leg_entry.push_back("Cut-based #DeltaR=0.5 Loose WP");
  leg_entry.push_back("MVA-based #DeltaR=0.3 Medium WP");


  TLegend* leg=new TLegend(0.2,0.65,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);


  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",10,20,120));
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
    leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h_eff[0]->SetMaximum(1.19);
  h_eff[0]->SetMinimum(0);
  h_eff[0]->GetXaxis()->SetRangeUser(10,130);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}^{#tau}(gen) [GeV]");
  h_eff[0]->GetYaxis()->SetTitle("TauID efficiency");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);

  h_eff[0]->Draw("E");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("sameE");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(11,1.22,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="eff_reco_tauh_ttH_dRveto_genskim_2";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}







void plot_tau_mistag(){

  TString ttH_sample="/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_skimmed/ttH/ntuple_ttH_Htautau_byLooseIsolationMVArun2v1DBdR03oldDMwLT_skimmed.root";


  TH1F* h_gen = single_plot(ttH_sample,"HTauTauTree","genq1_pt","(genq1_pt>20 && genq1_pt<120 && abs(genq1_eta)<2.3)",10,20,120);


  vector<TH1F*> h;
  //h.push_back(single_plot(ttH_sample,"HTauTauTree","genq1_pt","(genq1_pt>20 && genq1_pt<120 && abs(genq1_eta)<2.3 && genq1_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genq1_i_daughter_matched])==15 && daughters_pt[genq1_i_daughter_matched]>20 && abs(daughters_eta[genq1_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genq1_i_daughter_matched]==1)",10,20,120));
  h.push_back(single_plot(ttH_sample,"HTauTauTree","genq1_pt","(genq1_pt>20 && genq1_pt<120 && abs(genq1_eta)<2.3 && genq1_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genq1_i_daughter_matched])==15 && daughters_pt[genq1_i_daughter_matched]>20 && abs(daughters_eta[genq1_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genq1_i_daughter_matched]==1 && ((tauID[genq1_i_daughter_matched]>>3)&1)==1)",10,20,120));
  h.push_back(single_plot(ttH_sample,"HTauTauTree","genq1_pt","(genq1_pt>20 && genq1_pt<120 && abs(genq1_eta)<2.3 && genq1_dR_daughter_matched<0.3 && abs(PDGIdDaughters[genq1_i_daughter_matched])==15 && daughters_pt[genq1_i_daughter_matched]>20 && abs(daughters_eta[genq1_i_daughter_matched])<2.3 && daughters_decayModeFindingOldDMs[genq1_i_daughter_matched]==1 && ((tauID[genq1_i_daughter_matched]>>27)&1)==1)",10,20,120));


  vector<TString> leg_entry;
  //leg_entry.push_back("No isolation");
  leg_entry.push_back("Cut-based #DeltaR=0.5 Loose WP");
  leg_entry.push_back("MVA-based #DeltaR=0.3 Medium WP");


  TLegend* leg=new TLegend(0.2,0.65,0.5,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);


  vector<TH1F*> h_eff;
  for(unsigned int i=0;i<h.size();i++){
    h_eff.push_back(new TH1F("h_eff","",10,20,120));
    h_eff[i]->Divide(h[i],h_gen);
    h_eff[i]->SetLineColor(i+2);
    h_eff[i]->SetMarkerColor(i+2);
    if(i>3){
      h_eff[i]->SetLineColor(i+3);
      h_eff[i]->SetMarkerColor(i+3);
    }
    h_eff[i]->SetMarkerStyle(20+i);
    h_eff[i]->SetLineWidth(2);
    h_eff[i]->SetStats(0);
    leg->AddEntry(h_eff[i],leg_entry[i]);
  }


  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetLogy();
  h_eff[0]->SetMaximum(9e-2);
  h_eff[0]->SetMinimum(9e-4);
  h_eff[0]->GetXaxis()->SetRangeUser(10,130);
  h_eff[0]->GetXaxis()->SetTitle("p_{T}^{q}(gen) [GeV]");
  h_eff[0]->GetYaxis()->SetTitle("TauID quark mistag rate");
  h_eff[0]->GetXaxis()->SetTitleOffset(1.2);
  h_eff[0]->GetYaxis()->SetTitleOffset(1.7);
  gPad->SetTicks(1,1);

  h_eff[0]->Draw("E");
  for(unsigned int i=1; i<h.size();i++){
    h_eff[i]->Draw("sameE");
  }
  
  leg->Draw("same");

  TLatex *texl = new TLatex(11,1e-1,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation ttH H->#tau#tau");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  TString filename="mistag_reco_tauh_ttH_dRveto_genskim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;



}



