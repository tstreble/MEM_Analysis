#include <assert.h>
#include "TH2F.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TH2Poly.h"


TFile *_file_recoToLoose_leptonSF_mu1_b = NULL;
TFile *_file_recoToLoose_leptonSF_mu1_e = NULL;
TFile *_file_recoToLoose_leptonSF_mu2 = NULL;
TFile *_file_recoToLoose_leptonSF_mu3 = NULL;
TGraphAsymmErrors *_histo_recoToLoose_leptonSF_mu1_b = NULL;
TGraphAsymmErrors *_histo_recoToLoose_leptonSF_mu1_e = NULL;
TH2F *_histo_recoToLoose_leptonSF_mu2 = NULL;
TGraphAsymmErrors *_histo_recoToLoose_leptonSF_mu3 = NULL;
TFile *_file_recoToLoose_leptonSF_el = NULL;
TH2F *_histo_recoToLoose_leptonSF_el1 = NULL;
TH2F *_histo_recoToLoose_leptonSF_el2 = NULL;
TH2F *_histo_recoToLoose_leptonSF_el3 = NULL;
TFile *_file_recoToLoose_leptonSF_gsf = NULL;
TH2F *_histo_recoToLoose_leptonSF_gsf = NULL;

float _get_recoToLoose_leptonSF_ttH(int pdgid, float pt, float eta, int nlep, float var=0){

  if (var!=0 && abs(pdgid)!=11) assert(0); // NOT IMPLEMENTED

  if (!_histo_recoToLoose_leptonSF_mu1_b) {
    _file_recoToLoose_leptonSF_mu1_b = new TFile("lepSF/mu_ttH_presel_barrel.root","read");
    _file_recoToLoose_leptonSF_mu1_e = new TFile("lepSF/mu_ttH_presel_endcap.root","read");
    _file_recoToLoose_leptonSF_mu2 = new TFile("lepSF/MuonID_Z_RunBCD_prompt80X_7p65_looseID.root","read");
    _file_recoToLoose_leptonSF_mu3 = new TFile("lepSF/ratios_HIP_trkEff.root","read");
    _histo_recoToLoose_leptonSF_mu1_b = (TGraphAsymmErrors*)(_file_recoToLoose_leptonSF_mu1_b->Get("ratio"));
    _histo_recoToLoose_leptonSF_mu1_e = (TGraphAsymmErrors*)(_file_recoToLoose_leptonSF_mu1_e->Get("ratio"));
    _histo_recoToLoose_leptonSF_mu2 = (TH2F*)(_file_recoToLoose_leptonSF_mu2->Get("pt_abseta_ratio_MC_NUM_LooseID_DEN_genTracks_PAR_pt_spliteta_bin1"));
    _histo_recoToLoose_leptonSF_mu3 = (TGraphAsymmErrors*)(_file_recoToLoose_leptonSF_mu3->Get("ratio_eta"));
  }
  if (!_histo_recoToLoose_leptonSF_el1) {
    _file_recoToLoose_leptonSF_el = new TFile("lepSF/el_scaleFactors_20160724.root","read");
    _histo_recoToLoose_leptonSF_el1 = (TH2F*)(_file_recoToLoose_leptonSF_el->Get("GsfElectronToFOID2D"));
    _histo_recoToLoose_leptonSF_el2 = (TH2F*)(_file_recoToLoose_leptonSF_el->Get("MVAVLooseElectronToMini4"));
    _histo_recoToLoose_leptonSF_el3 = (TH2F*)(_file_recoToLoose_leptonSF_el->Get("MVAVLooseElectronToConvIHit1"));
  }
  if (!_histo_recoToLoose_leptonSF_gsf) {
    _file_recoToLoose_leptonSF_gsf = new TFile("lepSF/el_scaleFactors_gsf.root","read");
    _histo_recoToLoose_leptonSF_gsf = (TH2F*)(_file_recoToLoose_leptonSF_gsf->Get("EGamma_SF2D"));
  }

  if (abs(pdgid)==13){

    TGraphAsymmErrors *hist1 = (fabs(eta)<1.2) ? _histo_recoToLoose_leptonSF_mu1_b : _histo_recoToLoose_leptonSF_mu1_e;
    float pt1 = std::max(float(hist1->GetXaxis()->GetXmin()+1e-5), std::min(float(hist1->GetXaxis()->GetXmax()-1e-5), pt));
    float out = hist1->Eval(pt1);

    TH2F *hist = _histo_recoToLoose_leptonSF_mu2;
    int ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
    int etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(fabs(eta))));
    out *= hist->GetBinContent(ptbin,etabin);

    hist1 = _histo_recoToLoose_leptonSF_mu3;
    float eta1 = std::max(float(hist1->GetXaxis()->GetXmin()+1e-5), std::min(float(hist1->GetXaxis()->GetXmax()-1e-5), eta));
    out *= hist1->Eval(eta1);

    return out;

  }
  if (abs(pdgid)==11){
    TH2F *hist = _histo_recoToLoose_leptonSF_el1;
    int ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
    int etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(fabs(eta))));
    float out = hist->GetBinContent(ptbin,etabin)+var*hist->GetBinError(ptbin,etabin);
    hist = _histo_recoToLoose_leptonSF_el2;
    ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
    etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(fabs(eta))));
    out *= hist->GetBinContent(ptbin,etabin)+var*hist->GetBinError(ptbin,etabin);
    hist = _histo_recoToLoose_leptonSF_el3;
    ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
    etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(fabs(eta))));
    out *= hist->GetBinContent(ptbin,etabin)+var*hist->GetBinError(ptbin,etabin);

    hist = _histo_recoToLoose_leptonSF_gsf;
    etabin = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(eta))); // careful, different convention
    ptbin  = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(pt)));
    out *= hist->GetBinContent(etabin,ptbin);

    return out;
  }

  assert(0);
  return -999;

}

TFile *_file_looseToTight_leptonSF_mu_2lss = NULL;
TH2F *_histo_looseToTight_leptonSF_mu_2lss = NULL;
TFile *_file_looseToTight_leptonSF_el_2lss = NULL;
TH2F *_histo_looseToTight_leptonSF_el_2lss = NULL;
TFile *_file_looseToTight_leptonSF_mu_3l = NULL;
TH2F *_histo_looseToTight_leptonSF_mu_3l = NULL;
TFile *_file_looseToTight_leptonSF_el_3l = NULL;
TH2F *_histo_looseToTight_leptonSF_el_3l = NULL;

float _get_looseToTight_leptonSF_ttH(int pdgid, float pt, float eta, int nlep, float var){

  if (var!=0) assert(0); // NOT IMPLEMENTED

  if (!_histo_looseToTight_leptonSF_mu_2lss) {
    _file_looseToTight_leptonSF_mu_2lss = new TFile("lepSF/lepMVAEffSF_m_2lss.root","read");
    _histo_looseToTight_leptonSF_mu_2lss = (TH2F*)(_file_looseToTight_leptonSF_mu_2lss->Get("sf"));
  }
  if (!_histo_looseToTight_leptonSF_el_2lss) {
    _file_looseToTight_leptonSF_el_2lss = new TFile("lepSF/lepMVAEffSF_e_2lss.root","read");
    _histo_looseToTight_leptonSF_el_2lss = (TH2F*)(_file_looseToTight_leptonSF_el_2lss->Get("sf"));
  }
  if (!_histo_looseToTight_leptonSF_mu_3l) {
    _file_looseToTight_leptonSF_mu_3l = new TFile("lepSF/lepMVAEffSF_m_3l.root","read");
    _histo_looseToTight_leptonSF_mu_3l = (TH2F*)(_file_looseToTight_leptonSF_mu_3l->Get("sf"));
  }
  if (!_histo_looseToTight_leptonSF_el_3l) {
    _file_looseToTight_leptonSF_el_3l = new TFile("lepSF/lepMVAEffSF_e_3l.root","read");
    _histo_looseToTight_leptonSF_el_3l = (TH2F*)(_file_looseToTight_leptonSF_el_3l->Get("sf"));
  }

  TH2F *hist = 0;
  if (abs(pdgid)==13) hist = (nlep>2) ? _histo_looseToTight_leptonSF_mu_3l : _histo_looseToTight_leptonSF_mu_2lss;
  else if (abs(pdgid)==11) hist = (nlep>2) ? _histo_looseToTight_leptonSF_el_3l : _histo_looseToTight_leptonSF_el_2lss;
  assert(hist);
  int ptbin  = std::max(1, std::min(hist->GetNbinsX(), hist->GetXaxis()->FindBin(pt)));
  int etabin = std::max(1, std::min(hist->GetNbinsY(), hist->GetYaxis()->FindBin(fabs(eta))));
  return hist->GetBinContent(ptbin,etabin);

}

float leptonSF_ttH(int pdgid, float pt, float eta, int nlep, float var=0){

  float recoToLoose = _get_recoToLoose_leptonSF_ttH(pdgid,pt,eta,nlep,var);
  float looseToTight = _get_looseToTight_leptonSF_ttH(pdgid,pt,eta,nlep,var);
  float res = recoToLoose*looseToTight;
  assert (res>0);
  return res;

}

TFile *file_triggerSF_ttH = NULL;
TH2Poly* t2poly_triggerSF_ttH_mm = NULL;
TH2Poly* t2poly_triggerSF_ttH_ee = NULL;
TH2Poly* t2poly_triggerSF_ttH_em = NULL;
TH2Poly* t2poly_triggerSF_ttH_3l = NULL;


float triggerSF_ttH(int pdgid1, float pt1, int pdgid2, float pt2, int nlep, float var=0){
  if (!file_triggerSF_ttH) {
    file_triggerSF_ttH = new TFile("lepSF/trig_eff_map_v4.root");
    t2poly_triggerSF_ttH_mm = (TH2Poly*)(file_triggerSF_ttH->Get("SSuu2DPt_effic"));
    t2poly_triggerSF_ttH_ee = (TH2Poly*)(file_triggerSF_ttH->Get("SSee2DPt__effic"));
    t2poly_triggerSF_ttH_em = (TH2Poly*)(file_triggerSF_ttH->Get("SSeu2DPt_effic"));
    t2poly_triggerSF_ttH_3l = (TH2Poly*)(file_triggerSF_ttH->Get("__3l2DPt_effic"));

    if (!(t2poly_triggerSF_ttH_mm && t2poly_triggerSF_ttH_ee && t2poly_triggerSF_ttH_em && t2poly_triggerSF_ttH_3l)) {
	std::cout << "Impossible to load trigger scale factors!" << std::endl;
	file_triggerSF_ttH->ls();
	file_triggerSF_ttH = NULL;
    }
  }
  TH2Poly* hist = NULL;
  if (nlep==2){
    if (abs(pdgid1)==13 && abs(pdgid2)==13) hist = t2poly_triggerSF_ttH_mm;
    else if (abs(pdgid1)==11 && abs(pdgid2)==11) hist = t2poly_triggerSF_ttH_ee;
    else hist = t2poly_triggerSF_ttH_em;
  }
  else if (nlep==3) hist = t2poly_triggerSF_ttH_3l;
  else std::cout << "Wrong options to trigger scale factors" << std::endl;
  pt1 = std::max(float(hist->GetXaxis()->GetXmin()+1e-5), std::min(float(hist->GetXaxis()->GetXmax()-1e-5), pt1));
  pt2 = std::max(float(hist->GetYaxis()->GetXmin()+1e-5), std::min(float(hist->GetYaxis()->GetXmax()-1e-5), pt2));
  int bin = hist->FindBin(pt1,pt2);
  float eff = hist->GetBinContent(bin) + var * hist->GetBinError(bin);

  if (nlep>2) return eff;
  int cat = (abs(pdgid1)==11) + (abs(pdgid2)==11);
  if (cat==2) return eff*1.02;
  else if (cat==1) return eff*1.02;
  else return eff*1.01;


}





TFile *file_triggerSF_ttH_e = NULL;
TFile *file_triggerSF_ttH_m = NULL;
TH2F* h_triggerSF_ttH_e = NULL;
TH2F* h_triggerSF_ttH_m = NULL;


float triggerSF_ttH_1l(int pdgid, float pt, float eta, float var=0){
 
  if (!(file_triggerSF_ttH_e && file_triggerSF_ttH_m)) {
    file_triggerSF_ttH_e = new TFile("lepSF/ElTriggerPerformance_Sep27.root");
    h_triggerSF_ttH_e = (TH2F*)(file_triggerSF_ttH_e->Get("electrontrig_sf_eta_pt"));
    file_triggerSF_ttH_m = new TFile("lepSF/MuonTriggerPerformance_Sep06.root");
    h_triggerSF_ttH_m = (TH2F*)(file_triggerSF_ttH_m->Get("muontrig_sf_abseta_pt"));

    if (!(h_triggerSF_ttH_e && h_triggerSF_ttH_m)) {
      std::cout << "Impossible to load trigger scale factors!" << std::endl;
      file_triggerSF_ttH_e->ls();
      file_triggerSF_ttH_e = NULL;
      file_triggerSF_ttH_m->ls();
      file_triggerSF_ttH_m = NULL;
    }
  }

  TH2F* hist = NULL;
  if (abs(pdgid)==13) hist = h_triggerSF_ttH_m;
  else if (abs(pdgid)==11) hist = h_triggerSF_ttH_e;

  float searchPt = TMath::Min(pt,float(499.0));
  float searchEta = eta;
  if(abs(pdgid)==13) searchEta = fabs(eta);
  int bin = hist->FindBin(searchEta, searchPt);
  float nomval = hist->GetBinContent(bin);
  float error = hist->GetBinError(bin);
  float SF = nomval + var*error;
  return SF;

}
  
