#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>

using namespace std;

void add_tau_gen_match(TString filein, TString fileout, TString treename){

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
  vector<int> _recotauh_sel_genMatchInd;
  
  tree_new->Branch("recotauh_sel_genMatchInd",&_recotauh_sel_genMatchInd);


  //Old branches

  vector<bool>* _recotauh_sel_isGenMatched;
  vector<float>* _recotauh_sel_px;
  vector<float>* _recotauh_sel_py;
  vector<float>* _recotauh_sel_pz;
  vector<float>* _recotauh_sel_e;

  vector<float>* _gentauh_px;
  vector<float>* _gentauh_py;
  vector<float>* _gentauh_pz;
  vector<float>* _gentauh_e;

  vector<int>* _genlep_pdg;
  vector<int>* _genlep_flags;
  vector<float>* _genlep_px;
  vector<float>* _genlep_py;
  vector<float>* _genlep_pz;
  vector<float>* _genlep_e;


  tree->SetBranchAddress("recotauh_sel_isGenMatched",&_recotauh_sel_isGenMatched);
  tree->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
  tree->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
  tree->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
  tree->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);
  
  tree->SetBranchAddress("gentauh_px",&_gentauh_px);
  tree->SetBranchAddress("gentauh_py",&_gentauh_py);
  tree->SetBranchAddress("gentauh_pz",&_gentauh_pz);
  tree->SetBranchAddress("gentauh_e",&_gentauh_e);

  tree->SetBranchAddress("genlep_pdg",&_genlep_pdg);
  tree->SetBranchAddress("genlep_flags",&_genlep_flags);
  tree->SetBranchAddress("genlep_px",&_genlep_px);
  tree->SetBranchAddress("genlep_py",&_genlep_py);
  tree->SetBranchAddress("genlep_pz",&_genlep_pz);
  tree->SetBranchAddress("genlep_e",&_genlep_e);

   for(int i=0;i<nentries;i++){

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _recotauh_sel_genMatchInd.clear();

    _recotauh_sel_isGenMatched = 0;
    _recotauh_sel_px = 0;
    _recotauh_sel_py = 0;
    _recotauh_sel_pz = 0;
    _recotauh_sel_e = 0;
    
    _gentauh_px = 0;
    _gentauh_py = 0;
    _gentauh_pz = 0;
    _gentauh_e = 0;
    
    _genlep_pdg = 0;
    _genlep_flags = 0;
    _genlep_px = 0;
    _genlep_py = 0;
    _genlep_pz = 0;
    _genlep_e = 0;

    tree->GetEntry(i);
    

    for(unsigned int i_tau=0;i_tau<(*_recotauh_sel_isGenMatched).size();i_tau++){
          
      int genMatchInd = -1;

      if((*_recotauh_sel_isGenMatched)[i_tau]){

	TLorentzVector tauh((*_recotauh_sel_px)[i_tau],(*_recotauh_sel_py)[i_tau],(*_recotauh_sel_pz)[i_tau],(*_recotauh_sel_e)[i_tau]);

	for(int i_gen=0; i_gen<(*_gentauh_px).size(); i_gen++){

	  TLorentzVector gen((*_gentauh_px)[i_gen],(*_gentauh_py)[i_gen],(*_gentauh_pz)[i_gen],(*_gentauh_e)[i_gen]);

	  if(gen.DeltaR(tauh)<0.2){
	    genMatchInd = 5;
	    break;
	  }

	}

	if(genMatchInd<0){

	  for(int i_gen=0; i_gen<(*_genlep_px).size(); i_gen++){

	    TLorentzVector gen((*_genlep_px)[i_gen],(*_genlep_py)[i_gen],(*_genlep_pz)[i_gen],(*_genlep_e)[i_gen]);

	    if(gen.DeltaR(tauh)<0.2){
	      if(abs((*_genlep_pdg)[i_gen])==11){
		if((*_genlep_flags)[i_gen]&1) genMatchInd = 1;
		else if(((*_genlep_flags)[i_gen]>>5)&1) genMatchInd = 3;
	      }
	      else if(abs((*_genlep_pdg)[i_gen])==13){
		if((*_genlep_flags)[i_gen]&1) genMatchInd = 2;
		else if(((*_genlep_flags)[i_gen]>>5)&1) genMatchInd = 4;
	      }
	      break;
	    }
	    
	  }
	  
	}
	
      }

      _recotauh_sel_genMatchInd.push_back(genMatchInd);

    }


    tree_new->Fill();
    

  }
  
  f_new->cd();

  tree_new->Write();
  f_new->Close();


  return;

}
      
  








void add_tau_gen_match2(TString filein, TString fileout, TString treename){

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




  //Old branches

  vector<int>* _recolep_sel_pdg;
  vector<float>* _recolep_sel_px;
  vector<float>* _recolep_sel_py;
  vector<float>* _recolep_sel_pz;
  vector<float>* _recolep_sel_e;

  vector<float>* _recotauh_px;
  vector<float>* _recotauh_py;
  vector<float>* _recotauh_pz;
  vector<float>* _recotauh_e;
  vector<int>* _recotauh_againstMuonLoose3;
  vector<int>* _recotauh_againstElectronLooseMVA6;

  vector<float>* _recotauh_sel_px;
  vector<float>* _recotauh_sel_py;
  vector<float>* _recotauh_sel_pz;
  vector<float>* _recotauh_sel_e;

  vector<int>* _gentau_flags;
  vector<int>* _gentauh_TauMothInd;
  vector<float>* _gentauh_px;
  vector<float>* _gentauh_py;
  vector<float>* _gentauh_pz;
  vector<float>* _gentauh_e;
  vector<float>* _gentauh_pt;

  vector<int>* _genlep_pdg;
  vector<int>* _genlep_flags;
  vector<float>* _genlep_px;
  vector<float>* _genlep_py;
  vector<float>* _genlep_pz;
  vector<float>* _genlep_e;
  vector<float>* _genlep_pt;

  int _category;


  tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
  tree->SetBranchAddress("recolep_sel_px",&_recolep_sel_px);
  tree->SetBranchAddress("recolep_sel_py",&_recolep_sel_py);
  tree->SetBranchAddress("recolep_sel_pz",&_recolep_sel_pz);
  tree->SetBranchAddress("recolep_sel_e",&_recolep_sel_e);

  tree->SetBranchAddress("recotauh_px",&_recotauh_px);
  tree->SetBranchAddress("recotauh_py",&_recotauh_py);
  tree->SetBranchAddress("recotauh_pz",&_recotauh_pz);
  tree->SetBranchAddress("recotauh_e",&_recotauh_e);
  tree->SetBranchAddress("recotauh_againstMuonLoose3",&_recotauh_againstMuonLoose3);
  tree->SetBranchAddress("recotauh_againstElectronLooseMVA6",&_recotauh_againstElectronLooseMVA6);

  tree->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
  tree->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
  tree->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
  tree->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);
  
  tree->SetBranchAddress("gentau_flags",&_gentau_flags);
  tree->SetBranchAddress("gentauh_TauMothInd",&_gentauh_TauMothInd);
  tree->SetBranchAddress("gentauh_px",&_gentauh_px);
  tree->SetBranchAddress("gentauh_py",&_gentauh_py);
  tree->SetBranchAddress("gentauh_pz",&_gentauh_pz);
  tree->SetBranchAddress("gentauh_e",&_gentauh_e);
  tree->SetBranchAddress("gentauh_pt",&_gentauh_pt);

  tree->SetBranchAddress("genlep_pdg",&_genlep_pdg);
  tree->SetBranchAddress("genlep_flags",&_genlep_flags);
  tree->SetBranchAddress("genlep_px",&_genlep_px);
  tree->SetBranchAddress("genlep_py",&_genlep_py);
  tree->SetBranchAddress("genlep_pz",&_genlep_pz);
  tree->SetBranchAddress("genlep_e",&_genlep_e);
  tree->SetBranchAddress("genlep_pt",&_genlep_pt);

  tree->SetBranchAddress("category",&_category);




  TTree* tree_new=tree->GetTree()->CloneTree(0);

  //New branches
  vector<bool> _recolep_sel_isGenMatched;
  vector<int> _recolep_sel_genMatchInd;
  vector<bool> _recotauh_sel_isGenMatched;
  vector<int> _recotauh_sel_genMatchInd;
  bool _isGenMatched;

  vector<int> _recotauh_sel_againstMuonLoose3;
  vector<int> _recotauh_sel_againstElectronLooseMVA6;

  tree_new->Branch("recolep_sel_isGenMatched",&_recolep_sel_isGenMatched);
  tree_new->Branch("recolep_sel_genMatchInd",&_recolep_sel_genMatchInd);  
  tree_new->Branch("recotauh_sel_isGenMatched",&_recotauh_sel_isGenMatched);
  tree_new->Branch("recotauh_sel_genMatchInd",&_recotauh_sel_genMatchInd);
  tree_new->Branch("isGenMatched",&_isGenMatched);

  tree_new->Branch("recotauh_sel_againstMuonLoose3",&_recotauh_sel_againstMuonLoose3);
  tree_new->Branch("recotauh_sel_againstElectronLooseMVA6",&_recotauh_sel_againstElectronLooseMVA6);




  for(int i=0;i<nentries;i++){

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _recolep_sel_genMatchInd.clear();
    _recolep_sel_isGenMatched.clear();
    _recotauh_sel_genMatchInd.clear();
    _recotauh_sel_isGenMatched.clear();
    _isGenMatched = 0;

    _recotauh_sel_againstMuonLoose3.clear();
    _recotauh_sel_againstElectronLooseMVA6.clear();

    _recolep_sel_pdg = 0;
    _recolep_sel_px = 0;
    _recolep_sel_py = 0;
    _recolep_sel_pz = 0;
    _recolep_sel_e = 0;

    _recotauh_sel_px = 0;
    _recotauh_sel_py = 0;
    _recotauh_sel_pz = 0;
    _recotauh_sel_e = 0;

    _recotauh_px = 0;
    _recotauh_py = 0;
    _recotauh_pz = 0;
    _recotauh_e = 0;
    _recotauh_againstMuonLoose3 = 0;
    _recotauh_againstElectronLooseMVA6 = 0;

    _gentau_flags = 0;
    _gentauh_TauMothInd = 0;
    _gentauh_px = 0;
    _gentauh_py = 0;
    _gentauh_pz = 0;
    _gentauh_e = 0;
    _gentauh_pt = 0;
    
    _genlep_pdg = 0;
    _genlep_flags = 0;
    _genlep_px = 0;
    _genlep_py = 0;
    _genlep_pz = 0;
    _genlep_e = 0;
    _genlep_pt = 0;

    _category = 0;

    tree->GetEntry(i); 

    
    for(unsigned int i_lep=0;i_lep<(*_recolep_sel_px).size();i_lep++){

      TLorentzVector lep((*_recolep_sel_px)[i_lep],(*_recolep_sel_py)[i_lep],(*_recolep_sel_pz)[i_lep],(*_recolep_sel_e)[i_lep]);

      float dR = 1.0;
      int genMatchInd = -1;

      for(int i_gen=0; i_gen<(*_genlep_px).size(); i_gen++){

	if( !( abs((*_genlep_pdg)[i_gen])==abs((*_recolep_sel_pdg)[i_lep]) && (*_genlep_pt)[i_gen]>8 && ((*_genlep_flags)[i_gen]&1 || ((*_genlep_flags)[i_gen]>>5)&1) ) ) continue;
		
	TLorentzVector gen((*_genlep_px)[i_gen],(*_genlep_py)[i_gen],(*_genlep_pz)[i_gen],(*_genlep_e)[i_gen]);
	
	dR = lep.DeltaR(gen);
	if(dR<0.2){
	  if(abs((*_genlep_pdg)[i_gen])==11){
	    if((*_genlep_flags)[i_gen]&1) genMatchInd = 1;
	    else if(((*_genlep_flags)[i_gen]>>5)&1) genMatchInd = 3;
	  }
	  else if(abs((*_genlep_pdg)[i_gen])==13){
	    if((*_genlep_flags)[i_gen]&1) genMatchInd = 2;
	    else if(((*_genlep_flags)[i_gen]>>5)&1) genMatchInd = 4;
	  }	    
	  break;
	}
	
      }

      _recolep_sel_isGenMatched.push_back(dR<0.2);
      _recolep_sel_genMatchInd.push_back(genMatchInd);
      
    }
    


    for(unsigned int i_tau=0;i_tau<(*_recotauh_sel_px).size();i_tau++){

      float dR = 1.0;
      int genMatchInd = -1;

      TLorentzVector tauh((*_recotauh_sel_px)[i_tau],(*_recotauh_sel_py)[i_tau],(*_recotauh_sel_pz)[i_tau],(*_recotauh_sel_e)[i_tau]);

      for(int i_gen=0; i_gen<(*_gentauh_px).size(); i_gen++){

	if( !( (*_gentauh_pt)[i_gen]>15 && (*_gentau_flags)[(*_gentauh_TauMothInd)[i_gen]]&1) ) continue;

	TLorentzVector gen((*_gentauh_px)[i_gen],(*_gentauh_py)[i_gen],(*_gentauh_pz)[i_gen],(*_gentauh_e)[i_gen]);
	dR = gen.DeltaR(tauh);

	if(dR<0.2){
	  genMatchInd = 5;
	  break;
	}

      }


      if(dR>0.2){

	for(int i_gen=0; i_gen<(*_genlep_px).size(); i_gen++){

	  if( !( (*_genlep_pt)[i_gen]>8 && ((*_genlep_flags)[i_gen]&1 || ((*_genlep_flags)[i_gen]>>5)&1) ) ) continue;
	  
	  TLorentzVector gen((*_genlep_px)[i_gen],(*_genlep_py)[i_gen],(*_genlep_pz)[i_gen],(*_genlep_e)[i_gen]);	  
	  dR = gen.DeltaR(tauh);

	  if(dR<0.2){
	    if(abs((*_genlep_pdg)[i_gen])==11){
	      if((*_genlep_flags)[i_gen]&1) genMatchInd = 1;
	      else if(((*_genlep_flags)[i_gen]>>5)&1) genMatchInd = 3;
	    }
	    else if(abs((*_genlep_pdg)[i_gen])==13){
	      if((*_genlep_flags)[i_gen]&1) genMatchInd = 2;
	      else if(((*_genlep_flags)[i_gen]>>5)&1) genMatchInd = 4;
	    }	    
	    break;
	  }
	    
	}
	  
      }
	
      _recotauh_sel_isGenMatched.push_back(dR<0.2);
      _recotauh_sel_genMatchInd.push_back(genMatchInd);

    }


    if(_category==11)
      _isGenMatched = _recolep_sel_isGenMatched[0] && _recolep_sel_isGenMatched[1] && _recotauh_sel_isGenMatched[0];    

      
    for(unsigned int i_sel=0;i_sel<(*_recotauh_sel_px).size();i_sel++){

      TLorentzVector tauh_sel((*_recotauh_sel_px)[i_sel],(*_recotauh_sel_py)[i_sel],(*_recotauh_sel_pz)[i_sel],(*_recotauh_sel_e)[i_sel]);


      for(unsigned int i_tau=0;i_tau<(*_recotauh_px).size();i_tau++){
    
	TLorentzVector tauh((*_recotauh_px)[i_tau],(*_recotauh_py)[i_tau],(*_recotauh_pz)[i_tau],(*_recotauh_e)[i_tau]);

	if(tauh.DeltaR(tauh_sel)<0.01){
	  _recotauh_sel_againstMuonLoose3.push_back((*_recotauh_againstMuonLoose3)[i_tau]);
	  _recotauh_sel_againstElectronLooseMVA6.push_back((*_recotauh_againstElectronLooseMVA6)[i_tau]);
	  break;
	}

      }

    }



    tree_new->Fill();
    

  }
  
  f_new->cd();

  tree_new->Write();
  f_new->Close();


  return;

}
      
  
