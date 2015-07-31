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





void plot_MET2D_ttH(){

  vector<TH2F*> h;

  h.push_back(single_plot2D("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","PFMET","genMET","PUReweight",100,0,1000,100,0,1000));

  for(unsigned int i=0; i<h.size();i++){
 
    h[i]->SetStats(0);
 
  }



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->GetXaxis()->SetTitle("Reco. MET [GeV]");
  h[0]->GetYaxis()->SetTitle("Gen. MET [GeV]");
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("ttH, t->bqq, t->bl#nu, H->l#tau_{h} events");

  h[0]->Draw("colz");
  


  TString filename="MET_2D_ttH_gen_skim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_MET2D_VBF(){

  vector<TH2F*> h;

  h.push_back(single_plot2D("/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen_skimmed.root","HTauTauTree","PFMET","genMET","PUReweight*(@METx.size()>0)",100,0,500,100,0,500));

  for(unsigned int i=0; i<h.size();i++){
 
    h[i]->SetStats(0);
 
  }



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->GetXaxis()->SetTitle("Reco. MET [GeV]");
  h[0]->GetYaxis()->SetTitle("Gen. MET [GeV]");
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("VBF H->l#tau_{h} events");

  h[0]->Draw("colz");
  


  TString filename="MET_2D_VBF_gen_skim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_MET2D_phi_VBF(){

  vector<TH2F*> h;

  h.push_back(single_plot2D("/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen_skimmed.root","HTauTauTree","PFMET_phi","genMET_phi","PUReweight*(@METx.size()>0)",100,-3.2,3.2,100,-3.2,3.2));

  for(unsigned int i=0; i<h.size();i++){
 
    h[i]->SetStats(0);
 
  }



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->GetXaxis()->SetTitle("Reco. MET #phi");
  h[0]->GetYaxis()->SetTitle("Gen. MET #phi");
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("VBF H->l#tau_{h} events");

  h[0]->Draw("colz");
  


  TString filename="METphi_2D_VBF_gen_skim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_MET(){

  vector<TH1F*> h;
 
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/MEM_samples/VBF_MEv2_VBF4D_DY5D_150608.root","T","MEt","",100,0,1000));
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen_skimmed.root","HTauTauTree","genMET","PUReweight",100,0,1000));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","genMET","PUReweight",100,0,1000));
  h.push_back(single_plot("/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen_skimmed.root","HTauTauTree","PFMET","PUReweight*(@METx.size()>0)",100,0,1000));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","PFMET","PUReweight*(@METx.size()>0)",100,0,1000));
  
  vector<TString> leg_entry;
  leg_entry.push_back("Reco. MET VBF #mu#tau 8 TeV");
  leg_entry.push_back("Gen. MET VBF l#tau 13 TeV");
  leg_entry.push_back("Gen. MET ttH 13 TeV");
  leg_entry.push_back("Reco. MET VBF l#tau 13 TeV");
  leg_entry.push_back("Reco. MET ttH 13 TeV");

  TLegend* leg=new TLegend(0.4,0.5,0.85,0.85);
  //leg->SetHeader("p_{T}>30 GeV, |#eta|<2.1");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    if(i>3)
      h[i]->SetLineColor(i+2);
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
  h[0]->SetMinimum(0);
  h[0]->GetXaxis()->SetTitle("MET [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("MET distribution");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="MET_VBF_ttH_gen_skim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_delta_MET2D_VBF(){

  vector<TH2F*> h;

  h.push_back(single_plot2D("/data_CMS/cms/strebler/VBF_Samples/Ntuples_RunII/ntuples_converted/ntuple_VBF_dRveto_gen_skimmed.root","HTauTauTree","PFMET*cos(PFMET_phi)-genMET*cos(genMET_phi)","PFMET*sin(PFMET_phi)-genMET*sin(genMET_phi)","PUReweight",100,-2000,2000,100,-2000,2000));

  for(unsigned int i=0; i<h.size();i++){
 
    h[i]->SetStats(0);
 
  }



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->GetXaxis()->SetTitle("#DeltaMET_{X} [GeV]");
  h[0]->GetYaxis()->SetTitle("#DeltaMET_{Y} [GeV]");
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("13 TeV VBF H->l#tau_{h} events");

  h[0]->Draw("colz");
  


  TString filename="deltaMET_2D_VBF_gen_skim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_delta_MET2D_VBF_8TeV(){

  vector<TH2F*> h;

  h.push_back(single_plot2D("/home/llr/cms/mastrolorenzo/MELA_TauTransferFuncion/CMSSW_6_2_11/src/HtautauMC/VbfHttMCAnalyzer/test/ntuple/VBF_8TeV_PU20_Jetak5_JEC_L1FastL2L3_METmtx_MET_15_12_14_CRAB3_v5/ntuple_VBF_8TeV_JEC_METCorrtype1_1.root","demo/genTree","recoPFMET_px-gentrueMET_px","recoPFMET_py-gentrueMET_py","",100,-200,200,100,-200,200));

  for(unsigned int i=0; i<h.size();i++){
 
    h[i]->SetStats(0);
 
  }



  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->GetXaxis()->SetTitle("#DeltaMET_{X} [GeV]");
  h[0]->GetYaxis()->SetTitle("#DeltaMET_{Y} [GeV]");
  h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("8 TeV VBF events");

  h[0]->Draw("colz");
  


  TString filename="deltaMET_2D_VBF_8TeV_gen_skim";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}

