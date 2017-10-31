#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <iostream>

using namespace std;

void efficiency_cut(TString filename){

  TChain * tree = new TChain("HTauTauTree");
  tree->Add(filename);
  Long64_t nentries = tree->GetEntries();


  //Old branches used
  
  int _n_recolep_mvasel;
  int _n_recolep_fakeable;
  int _n_recotauh;
  int _n_recoPFJet;
  int _n_recoPFJet_btag_medium;
  int _n_recoPFJet_btag_loose;

  vector<bool>* _recolep_ismvasel;
  vector<bool>* _recolep_eleconv_misshits;
  vector<bool>* _recolep_tightcharge;
  vector<float>* _recolep_conept;
  vector<int>* _recolep_pdg;
  vector<int>* _recolep_charge;
  vector<int>* _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT;

  float _MC_weight;

  tree->SetBranchAddress("n_recolep_mvasel",&_n_recolep_mvasel);
  tree->SetBranchAddress("n_recolep_fakeable",&_n_recolep_fakeable);
  tree->SetBranchAddress("n_recotauh",&_n_recotauh);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("n_recoPFJet_btag_medium",&_n_recoPFJet_btag_medium);
  tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);

  tree->SetBranchAddress("recolep_ismvasel",&_recolep_ismvasel);
  tree->SetBranchAddress("recolep_eleconv_misshits",&_recolep_eleconv_misshits);
  tree->SetBranchAddress("recolep_tightcharge",&_recolep_tightcharge);
  tree->SetBranchAddress("recolep_conept",&_recolep_conept);
  tree->SetBranchAddress("recolep_pdg",&_recolep_pdg);
  tree->SetBranchAddress("recolep_charge",&_recolep_charge);
  tree->SetBranchAddress("recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  
  tree->SetBranchAddress("MC_weight",&_MC_weight);


  int n_cuts = 7;
  vector<TH1F*> h;
  for(int i=0; i<n_cuts; i++)
    h.push_back( new TH1F("h","h",3,0,3) );
  
  cout<<"nentries="<<nentries<<endl;
  for(unsigned int i=0;i<nentries;i++){
    if(i%10000==0) cout<<"i="<<i<<endl;


    _n_recolep_mvasel = 0;
    _n_recolep_fakeable = 0;
    _n_recotauh = 0;
    _n_recoPFJet = 0;
    _n_recoPFJet_btag_medium = 0;
    _n_recoPFJet_btag_loose = 0;

    _recolep_ismvasel = 0;
    _recolep_eleconv_misshits = 0;
    _recolep_tightcharge = 0;
    _recolep_conept = 0;
    _recolep_pdg = 0;
    _recolep_charge = 0;
    _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
    
    _MC_weight = 0;
    
    tree->GetEntry(i);

    h[0]->Fill(1,_MC_weight);

    if(_n_recolep_fakeable>=2 && (*_recolep_conept)[0]>25 && (((*_recolep_conept)[1]>10 && abs((*_recolep_pdg)[1])==13) || ((*_recolep_conept)[1]>15 && abs((*_recolep_pdg)[1])==11)) ) 
      h[1]->Fill(1,_MC_weight);
    else continue;

    if(_n_recolep_mvasel==2 && (*_recolep_ismvasel)[0] && (*_recolep_ismvasel)[1] && (*_recolep_eleconv_misshits)[0] && (*_recolep_eleconv_misshits)[1]) 
      h[2]->Fill(1,_MC_weight);
    else continue;

    if((*_recolep_charge)[0]*(*_recolep_charge)[1]>0)
      h[3]->Fill(1,_MC_weight);
    else continue;

    bool tau = false;
    for(unsigned int i_tau=0;i_tau<(*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT).size();i_tau++){
      if((*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau]>0.5){
	tau = true;
	break;
      }
    }
    if(tau)
      h[4]->Fill(1,_MC_weight);
    else continue;

    //if(_n_recoPFJet>=4)
    if(_n_recoPFJet>=3)
      h[5]->Fill(1,_MC_weight);
    else continue;

    if(_n_recoPFJet_btag_medium>=1 || _n_recoPFJet_btag_loose>=2)
      h[6]->Fill(1,_MC_weight);
    else continue;


  }

  cout<<h[0]->Integral()<<endl;
  cout<<"Fakeable leptons"<<endl;
  cout<<"Abs. eff.="<<h[1]->Integral()/h[0]->Integral()<<endl;
  cout<<"Tight leptons"<<endl;
  cout<<"Abs. eff.="<<h[2]->Integral()/h[0]->Integral()<<" rel. eff.="<<h[2]->Integral()/h[1]->Integral()<<endl;
  cout<<"Same-sign leptons"<<endl;
  cout<<"Abs. eff.="<<h[3]->Integral()/h[0]->Integral()<<" rel. eff.="<<h[3]->Integral()/h[2]->Integral()<<endl;
  cout<<"Tau"<<endl;
  cout<<"Abs. eff.="<<h[4]->Integral()/h[0]->Integral()<<" rel. eff.="<<h[4]->Integral()/h[3]->Integral()<<endl;
  cout<<"Jets"<<endl;
  cout<<"Abs. eff.="<<h[5]->Integral()/h[0]->Integral()<<" rel. eff.="<<h[5]->Integral()/h[4]->Integral()<<endl;
  cout<<"b-Jets"<<endl;
  cout<<"Abs. eff.="<<h[6]->Integral()/h[0]->Integral()<<" rel. eff.="<<h[6]->Integral()/h[5]->Integral()<<endl;
  cout<<h[6]->Integral()<<endl;

  return;


}








void efficiency_cut2(TString filename){

  TChain * tree = new TChain("HTauTauTree");
  tree->Add(filename);
  Long64_t nentries = tree->GetEntries();


  //Old branches used
  int _n_recolep_fakeable;

  vector<float>* _genlep_pt;
  vector<float>* _genlep_eta;
  vector<float>* _genlep_dR_closest_daughter;
  vector<int>* _genlep_i_closest_daughter;

  vector<float>* _daughters_miniRelIsoCharged;
  vector<float>* _daughters_miniRelIsoNeutral;
  vector<float>* _SIP;
  vector<float>* _dxy;
  vector<float>* _dz;
  vector<float>* _daughters_leptonMVA;
  vector<float>* _daughters_jetBTagCSV;
  vector<float>* _daughters_jetPtRatio;

  vector<float>* _recolep_conept;
  vector<int>* _recolep_pdg;

  float _MC_weight;

  tree->SetBranchAddress("n_recolep_fakeable",&_n_recolep_fakeable);
  tree->SetBranchAddress("recolep_conept",&_recolep_conept);
  tree->SetBranchAddress("recolep_pdg",&_recolep_pdg);

  tree->SetBranchAddress("genlep_pt",&_genlep_pt);
  tree->SetBranchAddress("genlep_eta",&_genlep_eta);
  tree->SetBranchAddress("genlep_dR_closest_daughter",&_genlep_dR_closest_daughter);
  tree->SetBranchAddress("genlep_i_closest_daughter",&_genlep_i_closest_daughter);

  tree->SetBranchAddress("daughters_miniRelIsoCharged",&_daughters_miniRelIsoCharged);
  tree->SetBranchAddress("daughters_miniRelIsoNeutral",&_daughters_miniRelIsoNeutral);
  tree->SetBranchAddress("SIP",&_SIP);
  tree->SetBranchAddress("dxy",&_dxy);
  tree->SetBranchAddress("dz",&_dz);
  tree->SetBranchAddress("daughters_leptonMVA",&_daughters_leptonMVA);
  tree->SetBranchAddress("daughters_jetBTagCSV",&_daughters_jetBTagCSV);
  tree->SetBranchAddress("daughters_jetPtRatio",&_daughters_jetPtRatio);

  
  tree->SetBranchAddress("MC_weight",&_MC_weight);


  int n_cuts = 7;
  vector<TH1F*> h;
  for(int i=0; i<n_cuts; i++)
    h.push_back( new TH1F("h","h",3,0,3) );
  
  cout<<"nentries="<<nentries<<endl;
  for(unsigned int i=0;i<nentries;i++){
    if(i%10000==0) cout<<"i="<<i<<endl;

    _n_recolep_fakeable = 0;
    _recolep_conept = 0;
    _recolep_pdg = 0;
    
    _genlep_pt = 0;
    _genlep_eta = 0;
    _genlep_dR_closest_daughter = 0;
    _genlep_i_closest_daughter = 0;
    
    _daughters_miniRelIsoCharged = 0;
    _daughters_miniRelIsoNeutral = 0;
    _SIP = 0;
    _dxy = 0;
    _dz = 0;
    _daughters_leptonMVA = 0;
    _daughters_jetBTagCSV = 0;
    _daughters_jetPtRatio = 0;
    
    _MC_weight = 0;
    
    tree->GetEntry(i);

    h[0]->Fill(1,_MC_weight);

    if((*_genlep_pt)[0]>10 && (*_genlep_pt)[1]>10 && abs((*_genlep_eta)[0])<2.4 && abs((*_genlep_eta)[1])<2.4)
      h[1]->Fill(1,_MC_weight);
    else continue;

    if((*_genlep_dR_closest_daughter)[0]<0.3 && (*_genlep_dR_closest_daughter)[1]<0.3)
      h[2]->Fill(1,_MC_weight);
    else continue;

    int i_dau0 = (*_genlep_i_closest_daughter)[0];
    int i_dau1 = (*_genlep_i_closest_daughter)[1];

    if((*_SIP)[i_dau0]<8 && (*_SIP)[i_dau1]<8 && (*_dxy)[i_dau0]<0.05 && (*_dz)[i_dau0]<0.1 && (*_dxy)[i_dau1]<0.05 && (*_dz)[i_dau1]<0.1)
      h[3]->Fill(1,_MC_weight);
    else continue;

    if(((*_daughters_miniRelIsoCharged)[i_dau0]+(*_daughters_miniRelIsoNeutral)[i_dau0])<0.4 && ((*_daughters_miniRelIsoCharged)[i_dau1]+(*_daughters_miniRelIsoNeutral)[i_dau1])<0.4)
      h[4]->Fill(1,_MC_weight);
    else continue;

 
    if( (((*_daughters_leptonMVA)[i_dau0]>0.75 && (*_daughters_jetBTagCSV)[i_dau0]<0.8) || ((*_daughters_leptonMVA)[i_dau0]<0.75 && (*_daughters_jetBTagCSV)[i_dau0]<0.46)) && (((*_daughters_leptonMVA)[i_dau1]>0.75 && (*_daughters_jetBTagCSV)[i_dau1]<0.8) || ((*_daughters_leptonMVA)[i_dau1]<0.75 && (*_daughters_jetBTagCSV)[i_dau1]<0.46)) )
      h[5]->Fill(1,_MC_weight);
    else continue;
    
    if( _n_recolep_fakeable>=2 && (*_recolep_conept)[0]>25 && (((*_recolep_conept)[1]>10 && abs((*_recolep_pdg)[1])==13) || ((*_recolep_conept)[1]>15 && abs((*_recolep_pdg)[1])==11)))
      h[6]->Fill(1,_MC_weight);
    else continue;


  }

  cout<<h[0]->Integral()<<endl;
  cout<<"Gen cut"<<endl;
  cout<<"Abs. eff.="<<h[1]->Integral()/h[0]->Integral()<<endl;
  cout<<"Daughter match"<<endl;
  cout<<"Abs. eff.="<<h[2]->Integral()/h[0]->Integral()<<" rel. eff.="<<h[2]->Integral()/h[1]->Integral()<<endl;
  cout<<"SIP"<<endl;
  cout<<"Abs. eff.="<<h[3]->Integral()/h[0]->Integral()<<" rel. eff.="<<h[3]->Integral()/h[2]->Integral()<<endl;
  cout<<"Iso"<<endl;
  cout<<"Abs. eff.="<<h[4]->Integral()/h[0]->Integral()<<" rel. eff.="<<h[4]->Integral()/h[3]->Integral()<<endl;
  cout<<"Lep MVA"<<endl;
  cout<<"Abs. eff.="<<h[5]->Integral()/h[0]->Integral()<<" rel. eff.="<<h[5]->Integral()/h[4]->Integral()<<endl;
  cout<<"n_fakeable>=2"<<endl;
  cout<<"Abs. eff.="<<h[6]->Integral()/h[0]->Integral()<<" rel. eff.="<<h[6]->Integral()/h[5]->Integral()<<endl;
  cout<<h[6]->Integral()<<endl;

  return;


}







