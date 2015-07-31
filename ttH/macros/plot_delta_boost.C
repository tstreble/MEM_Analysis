#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <Helpers.C>
#include <TF1.h>
#include <TF2.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TLatex.h>
#include <TVector3.h>
#include <TLorentzVector.h>


#include "Helpers_RecoVegas_ttH.C"





void plot_delta_boost_f_nult_costheta_phi(TString sample, int ientry,bool save=false){

  TString file;
  if(sample=="ttH")
    file="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root";
  
  TFile* f = TFile::Open(file);
  TTree* tree = (TTree*) f->Get("HTauTauTree");

  float tl_px;
  float tl_py;
  float tl_pz;
  float tl_e;
  float th_px;
  float th_py;
  float th_pz;
  float th_e;
  float taul_px;
  float taul_py;
  float taul_pz;
  float taul_e;
  float tauh_px;
  float tauh_py;
  float tauh_pz;
  float tauh_e;

  float ltau_px;
  float ltau_py;
  float ltau_pz;
  float ltau_e;
  float pi_px;
  float pi_py;
  float pi_pz;
  float pi_e;
  float bl_px;
  float bl_py;
  float bl_pz;
  float bl_e;
  float lt_px;
  float lt_py;
  float lt_pz;
  float lt_e;
  float bh_px;
  float bh_py;
  float bh_pz;
  float bh_e;
  float q_px;
  float q_py;
  float q_pz;
  float q_e;
  float qbar_px;
  float qbar_py;
  float qbar_pz;
  float qbar_e;

  float nult_px;
  float nult_py;
  float nult_pz;
  float nult_e;

  float gamma2_MH125;

  tree->SetBranchAddress("gentl_px",&tl_px);
  tree->SetBranchAddress("gentl_py",&tl_py);
  tree->SetBranchAddress("gentl_pz",&tl_pz);
  tree->SetBranchAddress("gentl_e", &tl_e);
  tree->SetBranchAddress("genth_px",&th_px);
  tree->SetBranchAddress("genth_py",&th_py);
  tree->SetBranchAddress("genth_pz",&th_pz);
  tree->SetBranchAddress("genth_e", &th_e);
  tree->SetBranchAddress("gentaulep_fromH_px",&taul_px);
  tree->SetBranchAddress("gentaulep_fromH_py",&taul_py);
  tree->SetBranchAddress("gentaulep_fromH_pz",&taul_pz);
  tree->SetBranchAddress("gentaulep_fromH_e", &taul_e);
  tree->SetBranchAddress("gentauhad_fromH_px",&tauh_px);
  tree->SetBranchAddress("gentauhad_fromH_py",&tauh_py);
  tree->SetBranchAddress("gentauhad_fromH_pz",&tauh_pz);
  tree->SetBranchAddress("gentauhad_fromH_e", &tauh_e);

  tree->SetBranchAddress("genltau_px",&ltau_px);
  tree->SetBranchAddress("genltau_py",&ltau_py);
  tree->SetBranchAddress("genltau_pz",&ltau_pz);
  tree->SetBranchAddress("genltau_e", &ltau_e);
  tree->SetBranchAddress("genpi_px",&pi_px);
  tree->SetBranchAddress("genpi_py",&pi_py);
  tree->SetBranchAddress("genpi_pz",&pi_pz);
  tree->SetBranchAddress("genpi_e", &pi_e);
  tree->SetBranchAddress("genbl_px",&bl_px);
  tree->SetBranchAddress("genbl_py",&bl_py);
  tree->SetBranchAddress("genbl_pz",&bl_pz);
  tree->SetBranchAddress("genbl_e", &bl_e);
  tree->SetBranchAddress("genlt_px",&lt_px);
  tree->SetBranchAddress("genlt_py",&lt_py);
  tree->SetBranchAddress("genlt_pz",&lt_pz);
  tree->SetBranchAddress("genlt_e", &lt_e);
  tree->SetBranchAddress("genbh_px",&bh_px);
  tree->SetBranchAddress("genbh_py",&bh_py);
  tree->SetBranchAddress("genbh_pz",&bh_pz);
  tree->SetBranchAddress("genbh_e", &bh_e);
  tree->SetBranchAddress("genq1_px",&q_px);
  tree->SetBranchAddress("genq1_py",&q_py);
  tree->SetBranchAddress("genq1_pz",&q_pz);
  tree->SetBranchAddress("genq1_e", &q_e);
  tree->SetBranchAddress("genq2_px",&qbar_px);
  tree->SetBranchAddress("genq2_py",&qbar_py);
  tree->SetBranchAddress("genq2_pz",&qbar_pz);
  tree->SetBranchAddress("genq2_e", &qbar_e);

  tree->SetBranchAddress("gennult_px",&nult_px);
  tree->SetBranchAddress("gennult_py",&nult_py);
  tree->SetBranchAddress("gennult_pz",&nult_pz);
  tree->SetBranchAddress("gennult_e", &nult_e);

  //tree->SetBranchAddress("gamma2_MH125",&gamma2_MH125);


  tree->GetEntry(ientry);

  /*while(gamma2_MH125<0){
    ientry++;
    tree->GetEntry(ientry);
    }*/

  //TH2F* h=new TH2F("h","h",2000,-1,1,1000,-TMath::Pi(),TMath::Pi());
  TH2F* h=new TH2F("h","h",1000,-5,5,1000,-TMath::Pi(),TMath::Pi());

  TLorentzVector taul_tlv(taul_px,taul_py,taul_pz,taul_e);
  TLorentzVector tauh_tlv(tauh_px,tauh_py,tauh_pz,tauh_e);
  TLorentzVector tl_tlv(tl_px,tl_py,tl_pz,tl_e);
  TLorentzVector th_tlv(th_px,th_py,th_pz,th_e);

  float tau_lep_P=taul_tlv.P();
  float cosThetaTauTau=TMath::Cos(taul_tlv.Angle(tauh_tlv.Vect()));
  float mtautau2=125*125;

  TLorentzVector ltau_tlv(ltau_px,ltau_py,ltau_pz,ltau_e);
  TLorentzVector pi_tlv(pi_px,pi_py,pi_pz,pi_e);
  TLorentzVector b_lep_tlv(bl_px,bl_py,bl_pz,bl_e);
  TLorentzVector lt_tlv(lt_px,lt_py,lt_pz,lt_e);
  TLorentzVector b_had_tlv(bh_px,bh_py,bh_pz,bh_e);
  TLorentzVector q_tlv(q_px,q_py,q_pz,q_e);
  TLorentzVector qbar_tlv(qbar_px,qbar_py,qbar_pz,qbar_e);

  TLorentzVector q1_tlv=q_tlv;
  TLorentzVector q2_tlv=qbar_tlv;
  if(qbar_tlv.Pt()>q_tlv.Pt()){
    q1_tlv=qbar_tlv;
    q2_tlv=q_tlv;
  }

  TLorentzVector nult_tlv(nult_px,nult_py,nult_pz,nult_e);


  map<TString,TLorentzVector> LV_MC;
  LV_MC["ltau"]=ltau_tlv;
  LV_MC["pi"]=pi_tlv;
  LV_MC["b_lep"]=b_lep_tlv;
  LV_MC["lt"]=lt_tlv;
  LV_MC["b_had"]=b_had_tlv;
  LV_MC["q1"]=q1_tlv;
  LV_MC["q2"]=q2_tlv;


  //for(float cosThetaNu=-1;cosThetaNu<=1;cosThetaNu+=0.001){
  for(float etaNu=-5;etaNu<=5;etaNu+=0.01){

    float cosThetaNu=cos(2*atan(exp(-etaNu)));

    for(float phiNu=-TMath::Pi();phiNu<=TMath::Pi();phiNu+=2*TMath::Pi()/1000.){

      map<TString,TLorentzVector> LV_Vegas = LV_RecoVegas(LV_MC,mtautau2,tau_lep_P,cosThetaTauTau,q1_tlv.E(),cosThetaNu,phiNu);

      TLorentzVector t_lep_reco=LV_Vegas["t_lep_reco"];
      TLorentzVector t_had_reco=LV_Vegas["t_had_reco"];
      //TLorentzVector tau_lep_reco=LV_Vegas["tau_lep_reco"];
      //TLorentzVector tau_had_reco=LV_Vegas["tau_had_reco"];

      TLorentzVector tau_lep_reco=taul_tlv;
      TLorentzVector tau_had_reco=tauh_tlv;


      if(tau_had_reco.Pt()>0 && t_lep_reco.Pt()>0 && t_had_reco.Pt()>0){
	float boost_Vegas=(t_lep_reco+t_had_reco+tau_lep_reco+tau_had_reco).Pt();
	//h->Fill(cosThetaNu,phiNu,boost_Vegas);
	h->Fill(etaNu,phiNu,boost_Vegas);

      }
      
    }

  }


  TCanvas* c=new TCanvas("c","c",650,600);

  h->Draw("colz");
  h->SetStats(0);


  TGraph* lt_gr=new TGraph();
  TGraph* blep_gr=new TGraph();
  TGraph* tlep_gr=new TGraph();
  TGraph* nult_gr=new TGraph();

  /*lt_gr->SetPoint(0,lt_tlv.CosTheta(),lt_tlv.Phi());
  blep_gr->SetPoint(0,b_lep_tlv.CosTheta(),b_lep_tlv.Phi());
  tlep_gr->SetPoint(0,tl_tlv.CosTheta(),tl_tlv.Phi());
  nult_gr->SetPoint(0,nult_tlv.CosTheta(),nult_tlv.Phi());*/
  lt_gr->SetPoint(0,lt_tlv.Eta(),lt_tlv.Phi());
  blep_gr->SetPoint(0,b_lep_tlv.Eta(),b_lep_tlv.Phi());
  tlep_gr->SetPoint(0,tl_tlv.Eta(),tl_tlv.Phi());
  nult_gr->SetPoint(0,nult_tlv.Eta(),nult_tlv.Phi());

  lt_gr->SetMarkerColor(2);
  blep_gr->SetMarkerColor(3);
  tlep_gr->SetMarkerColor(5);
  nult_gr->SetMarkerColor(6);

  lt_gr->SetMarkerSize(2);
  blep_gr->SetMarkerSize(2);
  tlep_gr->SetMarkerSize(2);
  nult_gr->SetMarkerSize(2);

  lt_gr->SetMarkerStyle(2);
  blep_gr->SetMarkerStyle(2);
  tlep_gr->SetMarkerStyle(2);
  nult_gr->SetMarkerStyle(2);

  lt_gr->SetLineWidth(2);
  blep_gr->SetLineWidth(2);
  tlep_gr->SetLineWidth(2);
  nult_gr->SetLineWidth(2);

  lt_gr->Draw("sameP");
  blep_gr->Draw("sameP");
  tlep_gr->Draw("sameP");
  nult_gr->Draw("sameP");


  if(save){
    TString filename=Form("delta_boost_cosThetaNu_phiNu_ievent%i",ientry);
    filename+="_"+sample;
    c->SaveAs("../pdf/"+filename+".pdf");
    c->SaveAs("../png/"+filename+".png");
  }

  return;

}

