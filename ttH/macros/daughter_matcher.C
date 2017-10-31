#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>

using namespace std;

void add_daughter_match(TString filein, TString fileout, TString treename){

  TChain * tree = new TChain(treename);
  tree->Add(filein);

  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<tree->GetEntries()<<endl;

  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  f_new = TFile::Open(fileout,"RECREATE");


  TTree* tree_new=tree->GetTree()->CloneTree(0);

  //New branches
  vector<int> _genlep_i_closest_daughter;
  vector<float> _genlep_dR_closest_daughter;
  vector<float> _daughters_leptonMVA;
  
  tree_new->Branch("genlep_i_closest_daughter",&_genlep_i_closest_daughter);
  tree_new->Branch("genlep_dR_closest_daughter",&_genlep_dR_closest_daughter);
  tree_new->Branch("daughters_leptonMVA",&_daughters_leptonMVA);
  
  
  //Old branches
  vector<int>* _genlep_pdg;
  vector<float>* _genlep_px;
  vector<float>* _genlep_py;
  vector<float>* _genlep_pz;
  vector<float>* _genlep_e;

  vector<int>* _PDGIdDaughters;
  vector<float>* _daughters_px;
  vector<float>* _daughters_py;
  vector<float>* _daughters_pz;
  vector<float>* _daughters_e;

  vector<float>* _recomu_px;
  vector<float>* _recomu_py;
  vector<float>* _recomu_pz;
  vector<float>* _recomu_e;
  vector<float>* _recomu_leptonMVA;

  vector<float>* _recoele_px;
  vector<float>* _recoele_py;
  vector<float>* _recoele_pz;
  vector<float>* _recoele_e;
  vector<float>* _recoele_leptonMVA;


  tree->SetBranchAddress("genlep_pdg",&_genlep_pdg);
  tree->SetBranchAddress("genlep_px",&_genlep_px);
  tree->SetBranchAddress("genlep_py",&_genlep_py);
  tree->SetBranchAddress("genlep_pz",&_genlep_pz);
  tree->SetBranchAddress("genlep_e",&_genlep_e);

  tree->SetBranchAddress("PDGIdDaughters",&_PDGIdDaughters);
  tree->SetBranchAddress("daughters_px",&_daughters_px);
  tree->SetBranchAddress("daughters_py",&_daughters_py); 
  tree->SetBranchAddress("daughters_pz",&_daughters_pz); 
  tree->SetBranchAddress("daughters_e",&_daughters_e); 

  tree->SetBranchAddress("recomu_px",&_recomu_px);
  tree->SetBranchAddress("recomu_py",&_recomu_py);
  tree->SetBranchAddress("recomu_pz",&_recomu_pz);
  tree->SetBranchAddress("recomu_e",&_recomu_e);
  tree->SetBranchAddress("recomu_leptonMVA",&_recomu_leptonMVA); 

  tree->SetBranchAddress("recoele_px",&_recoele_px);
  tree->SetBranchAddress("recoele_py",&_recoele_py);
  tree->SetBranchAddress("recoele_pz",&_recoele_pz);
  tree->SetBranchAddress("recoele_e",&_recoele_e);
  tree->SetBranchAddress("recoele_leptonMVA",&_recoele_leptonMVA); 


  for(int i=0;i<nentries;i++){

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _genlep_i_closest_daughter.clear();
    _genlep_dR_closest_daughter.clear();
    _daughters_leptonMVA.clear();
        
    _genlep_pdg = 0;
    _genlep_px = 0;
    _genlep_py = 0;
    _genlep_pz = 0;
    _genlep_e = 0;
    
    _PDGIdDaughters = 0;
    _daughters_px = 0;
    _daughters_py = 0;
    _daughters_pz = 0;
    _daughters_e = 0;

    _recomu_px = 0;
    _recomu_py = 0;
    _recomu_pz = 0;
    _recomu_e = 0;
    _recomu_leptonMVA = 0;

    _recoele_px = 0;
    _recoele_py = 0;
    _recoele_pz = 0;
    _recoele_e = 0;    
    _recoele_leptonMVA = 0;
    

    tree->GetEntry(i);


    for(unsigned int i_gen=0; i_gen<(*_genlep_pdg).size(); i_gen++){
      
      TLorentzVector genlep((*_genlep_px)[i_gen],(*_genlep_py)[i_gen],(*_genlep_pz)[i_gen],(*_genlep_e)[i_gen]);


      float dR_min = 5.0;
      int i_dau_gen = -1;

      for(unsigned int i_dau=0; i_dau<(*_PDGIdDaughters).size();i_dau++){

	if(abs((*_genlep_pdg)[i_gen])!=abs((*_PDGIdDaughters)[i_dau])) continue;

	TLorentzVector daughter((*_daughters_px)[i_dau],(*_daughters_py)[i_dau],(*_daughters_pz)[i_dau],(*_daughters_e)[i_dau]);

	float dR = daughter.DeltaR(genlep);

	if(dR<dR_min){
	  dR_min = dR;
	  i_dau_gen = i_dau;
	}

      }

      _genlep_i_closest_daughter.push_back(i_dau_gen);
      _genlep_dR_closest_daughter.push_back(dR_min);

    }


    for(unsigned int i_dau=0; i_dau<(*_PDGIdDaughters).size();i_dau++){

      float leptonMVA=-999.;

      TLorentzVector daughter((*_daughters_px)[i_dau],(*_daughters_py)[i_dau],(*_daughters_pz)[i_dau],(*_daughters_e)[i_dau]);

      if(abs((*_PDGIdDaughters)[i_dau])==13){

	for(unsigned int i_mu=0;i_mu<(*_recomu_leptonMVA).size();i_mu++){

	  TLorentzVector mu((*_recomu_px)[i_mu],(*_recomu_py)[i_mu],(*_recomu_pz)[i_mu],(*_recomu_e)[i_mu]);
	  
	  if(mu.DeltaR(daughter)<0.01){
	    leptonMVA = (*_recomu_leptonMVA)[i_mu];
	    break;
	  }

	}

      }	    

      else if(abs((*_PDGIdDaughters)[i_dau])==11){

	for(unsigned int i_ele=0;i_ele<(*_recoele_leptonMVA).size();i_ele++){

	  TLorentzVector ele((*_recoele_px)[i_ele],(*_recoele_py)[i_ele],(*_recoele_pz)[i_ele],(*_recoele_e)[i_ele]);
	  
	  if(ele.DeltaR(daughter)<0.01){
	    leptonMVA = (*_recoele_leptonMVA)[i_ele];
	    break;
	  }

	}

      }	  

      
      _daughters_leptonMVA.push_back(leptonMVA);

    }

    


    tree_new->Fill();
    

  }
  
  f_new->cd();

  tree_new->Write();
  f_new->Close();


  return;

}
