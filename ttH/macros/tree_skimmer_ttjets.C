#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>

#include <iostream>
#include <TLegend.h>
#include <TBranch.h>
#include <TClonesArray.h>
#include <TChain.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TVector3.h>


#include <vector>
#ifdef __MAKECINT__
#pragma link C++ class vector<double>+;
#pragma link C++ class vector<vector<int> >+;

#endif


using namespace std;




void skim_tree(TString file){

  TString file_in="ntuple_TTJets_";
  file_in+=file;
  file_in+="_byLooseIsolationMVArun2v1DBdR03oldDMwLT";
  if(file=="ttH")
    file_in="ntuple_ttH_byLooseIsolationMVArun2v1DBdR03oldDMwLT";
  TString file_out=file_in;
  file_in+=".root";
  file_out+="_skimmed.root";
  TString dir="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_04_2016/";
  if(file=="ttH")
    dir="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_04_2016/";

  TChain * tree = new TChain("HTauTauTree");
  tree->Add(dir+file_in);

  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(dir+file_out);
  if(f_new!=0){
    cout<<dir+file_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(dir+file_out,"RECREATE");



  //Old branches used
  int _n_recotauh;
  vector<int>* _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int>* _recotauh_charge;
  int _n_recomu_mvasel;
  int _n_recomu_fakeable;
  vector<bool>* _recomu_ismvasel;
  vector<bool>* _recomu_isfakeable;
  vector<int>* _recomu_charge;
  int _n_recoele_mvasel;
  int _n_recoele_fakeable;
  vector<bool>* _recoele_ismvasel;
  vector<bool>* _recoele_isfakeable;
  vector<int>* _recoele_charge;
  int _n_recoPFJet;
  int _n_recoPFJet_btag_medium;
  int _n_recoPFJet_btag_loose;

  vector<float>* _recoele_px;
  vector<float>* _recoele_py;
  vector<float>* _recoele_pz;
  vector<float>* _recoele_e;

  vector<float>* _recomu_px;
  vector<float>* _recomu_py;
  vector<float>* _recomu_pz;
  vector<float>* _recomu_e;

  tree->SetBranchAddress("n_recotauh",&_n_recotauh);
  tree->SetBranchAddress("recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_charge",&_recotauh_charge);
  tree->SetBranchAddress("n_recomu_mvasel",&_n_recomu_mvasel);
  tree->SetBranchAddress("n_recomu_fakeable",&_n_recomu_fakeable);
  tree->SetBranchAddress("recomu_ismvasel",&_recomu_ismvasel);
  tree->SetBranchAddress("recomu_isfakeable",&_recomu_isfakeable);
  tree->SetBranchAddress("recomu_charge",&_recomu_charge);
  tree->SetBranchAddress("n_recoele_mvasel",&_n_recoele_mvasel);
  tree->SetBranchAddress("n_recoele_fakeable",&_n_recoele_fakeable);
  tree->SetBranchAddress("recoele_ismvasel",&_recoele_ismvasel);
  tree->SetBranchAddress("recoele_isfakeable",&_recoele_isfakeable);
  tree->SetBranchAddress("recoele_charge",&_recoele_charge);
  tree->SetBranchAddress("n_recoPFJet",&_n_recoPFJet);
  tree->SetBranchAddress("n_recoPFJet_btag_medium",&_n_recoPFJet_btag_medium);
  tree->SetBranchAddress("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose);

  tree->SetBranchAddress("recoele_px",&_recoele_px);
  tree->SetBranchAddress("recoele_py",&_recoele_py);
  tree->SetBranchAddress("recoele_pz",&_recoele_pz);
  tree->SetBranchAddress("recoele_e",&_recoele_e);
  
  tree->SetBranchAddress("recomu_px",&_recomu_px);
  tree->SetBranchAddress("recomu_py",&_recomu_py);
  tree->SetBranchAddress("recomu_pz",&_recomu_pz);
  tree->SetBranchAddress("recomu_e",&_recomu_e);
  


  TTree* tree_new=tree->GetTree()->CloneTree(0);

  //New branches
  
  int _event_type;

  vector<int> _recolep_MEM_pdg;
  vector<int> _recolep_MEM_charge;
  vector<float> _recolep_MEM_px;
  vector<float> _recolep_MEM_py;
  vector<float> _recolep_MEM_pz;
  vector<float> _recolep_MEM_e;
  vector<float> _recolep_MEM_pt;
  vector<float> _recolep_MEM_eta;
  vector<float> _recolep_MEM_phi;

  tree_new->Branch("event_type",&_event_type,"event_type/I");

  tree_new->Branch("recolep_MEM_pdg",&_recolep_MEM_pdg);
  tree_new->Branch("recolep_MEM_charge",&_recolep_MEM_charge);
  tree_new->Branch("recolep_MEM_px",&_recolep_MEM_px);
  tree_new->Branch("recolep_MEM_py",&_recolep_MEM_py);
  tree_new->Branch("recolep_MEM_pz",&_recolep_MEM_pz);
  tree_new->Branch("recolep_MEM_e",&_recolep_MEM_e);
  tree_new->Branch("recolep_MEM_pt",&_recolep_MEM_pt);
  tree_new->Branch("recolep_MEM_eta",&_recolep_MEM_eta);
  tree_new->Branch("recolep_MEM_phi",&_recolep_MEM_phi);

  cout<<"nentries="<<nentries<<endl;


  for (int i=0;i<nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _n_recotauh = 0;
    _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
    _recotauh_charge = 0;
    _n_recomu_mvasel = 0;
    _n_recomu_fakeable = 0;
    _recomu_ismvasel = 0;
    _recomu_isfakeable = 0;
    _recomu_charge = 0;
    _n_recoele_mvasel = 0;
    _n_recoele_fakeable = 0;
    _recoele_ismvasel = 0;
    _recoele_isfakeable = 0;
    _recoele_charge = 0;
    _n_recoPFJet = 0;
    _n_recoPFJet_btag_medium = 0;
    _n_recoPFJet_btag_loose = 0;
    
    _recoele_px = 0;
    _recoele_py = 0;
    _recoele_pz = 0;
    _recoele_e = 0;
    
    _recomu_px = 0;
    _recomu_py = 0;
    _recomu_pz = 0;
    _recomu_e = 0;

    _event_type = -1;

    _recolep_MEM_pdg.clear();
    _recolep_MEM_charge.clear();
    _recolep_MEM_px.clear();
    _recolep_MEM_py.clear();
    _recolep_MEM_pz.clear();
    _recolep_MEM_pt.clear();
    _recolep_MEM_eta.clear();
    _recolep_MEM_phi.clear();

    
    tree->GetEntry(i);

    bool tightEvent = _n_recotauh>=1 && (*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]>0.5
		      && ( ( _n_recomu_mvasel==2 && _n_recoele_mvasel==0 && (*_recomu_ismvasel)[0]==1  && (*_recomu_ismvasel)[1]==1 && (*_recomu_charge)[0]*(*_recomu_charge)[1]>0 && (*_recomu_charge)[0]*(*_recotauh_charge)[0]<0 )
	                || ( _n_recomu_mvasel==0 &&_n_recoele_mvasel==2 && (*_recoele_ismvasel)[0]==1  && (*_recoele_ismvasel)[1]==1 && (*_recoele_charge)[0]*(*_recoele_charge)[1]>0 && (*_recoele_charge)[0]*(*_recotauh_charge)[0]<0 )
        	        || ( _n_recomu_mvasel==1 && (*_recomu_ismvasel)[0]==1 && _n_recoele_mvasel==1 && (*_recoele_ismvasel)[1]==1 && (*_recomu_charge)[0]*(*_recoele_charge)[0]>0 && (*_recomu_charge)[0]*(*_recotauh_charge)[0]<0 ) )
           	      && _n_recoPFJet>=3
		      && (_n_recoPFJet_btag_medium == 1 || _n_recoPFJet_btag_loose == 2 );

    bool looseEvent = !tightEvent
		      && _n_recotauh>=1 && (*_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]>0.5
		      && ( ( _n_recomu_mvasel==1 && (*_recomu_ismvasel)[0]==1 && _n_recoele_mvasel==0 && (*_recomu_charge)[0]*(*_recotauh_charge)[0]<0 && _n_recomu_fakeable>=2 && (*_recomu_isfakeable)[1]==1 && (*_recomu_charge)[0]*(*_recomu_charge)[1]>0 )
			|| ( _n_recomu_mvasel==0 && _n_recoele_mvasel==1 && (*_recoele_ismvasel)[0]==1 && (*_recoele_charge)[0]*(*_recotauh_charge)[0]<0 && _n_recoele_fakeable>=2 && (*_recoele_isfakeable)[1]==1 && (*_recoele_charge)[0]*(*_recoele_charge)[1]>0)
			|| ( _n_recomu_mvasel==1 && (*_recomu_ismvasel)[0]==1 && _n_recoele_mvasel==0 && (*_recomu_charge)[0]*(*_recotauh_charge)[0]<0 && _n_recoele_fakeable>=1 && (*_recoele_isfakeable)[0]==1 && (*_recomu_charge)[0]*(*_recoele_charge)[0]>0)
			|| ( _n_recomu_mvasel==0 && _n_recoele_mvasel==1 && (*_recoele_ismvasel)[0]==1 && (*_recoele_charge)[0]*(*_recotauh_charge)[0]<0 && _n_recomu_fakeable>=1 && (*_recomu_isfakeable)[0]==1 && (*_recomu_charge)[0]*(*_recoele_charge)[0]>0) )
		      && _n_recoPFJet>=3
                      && (_n_recoPFJet_btag_medium == 1 || _n_recoPFJet_btag_loose == 2 );


    if(tightEvent)
      _event_type = 1;
    else if(looseEvent)
      _event_type = 0;
    else
      continue;

    int lep1_pdg = 0;
    int lep1_charge = 0;
    TLorentzVector lep1;
    
    int lep2_pdg = 0;
    int lep2_charge = 0;
    TLorentzVector lep2;

    
    if(tightEvent){

      if( _n_recomu_mvasel==2 ){

	lep1.SetPxPyPzE( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );
	lep1_charge = (*_recomu_charge)[0];
	lep1_pdg = (*_recomu_charge)[0]*(-13);

	lep2.SetPxPyPzE( (*_recomu_px)[1], (*_recomu_py)[1], (*_recomu_pz)[1], (*_recomu_e)[1] );
	lep2_charge = (*_recomu_charge)[1];
	lep2_pdg = (*_recomu_charge)[1]*(-13);
	
      }

      else if( _n_recoele_mvasel==2 ){
      
	lep1.SetPxPyPzE( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );
	lep1_charge = (*_recoele_charge)[0];
	lep1_pdg = (*_recoele_charge)[0]*(-11);

	lep2.SetPxPyPzE( (*_recoele_px)[1], (*_recoele_py)[1], (*_recoele_pz)[1], (*_recoele_e)[1] );
	lep2_charge = (*_recoele_charge)[1];
	lep2_pdg = (*_recoele_charge)[1]*(-11);

      }

      else if( _n_recoele_mvasel==1 && _n_recomu_mvasel==1 ){
      
	TLorentzVector mu( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );
	TLorentzVector ele( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );

	if(mu.Pt()>ele.Pt()){
	  
	  lep1.SetPxPyPzE( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );
	  lep1_charge = (*_recomu_charge)[0];
	  lep1_pdg = (*_recomu_charge)[0]*(-13);

	  lep2.SetPxPyPzE( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );
	  lep2_charge = (*_recoele_charge)[0];
	  lep2_pdg = (*_recoele_charge)[0]*(-11);

	}

	else{
	 
	  lep2.SetPxPyPzE( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );
	  lep2_charge = (*_recomu_charge)[0];
	  lep2_pdg = (*_recomu_charge)[0]*(-13);

	  lep1.SetPxPyPzE( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );
	  lep1_charge = (*_recoele_charge)[0];
	  lep1_pdg = (*_recoele_charge)[0]*(-11);

	}

      }

    }


    else if(looseEvent){

      if( _n_recomu_mvasel==1 ){

	lep1.SetPxPyPzE( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );
	lep1_charge = (*_recomu_charge)[0];
	lep1_pdg = (*_recomu_charge)[0]*(-13);

	if( _n_recomu_fakeable>=2 && _n_recoele_fakeable==0){
	  lep2.SetPxPyPzE( (*_recomu_px)[1], (*_recomu_py)[1], (*_recomu_pz)[1], (*_recomu_e)[1] );
	  lep2_charge = (*_recomu_charge)[1];
	  lep2_pdg = (*_recomu_charge)[1]*(-13);
	}

	else if( _n_recoele_fakeable>=1 && _n_recomu_fakeable==1){
	  lep2.SetPxPyPzE( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );
	  lep2_charge = (*_recoele_charge)[0];
	  lep2_pdg = (*_recoele_charge)[0]*(-11);
	}
	  
	else if( _n_recomu_fakeable>=2 && _n_recoele_fakeable>=1){
	  
	  if((*_recomu_isfakeable)[1]==1 && (*_recomu_charge)[0]*(*_recomu_charge)[1]>0 && !((*_recoele_isfakeable)[0]==1 && (*_recomu_charge)[0]*(*_recoele_charge)[0]>0) ){
	    lep2.SetPxPyPzE( (*_recomu_px)[1], (*_recomu_py)[1], (*_recomu_pz)[1], (*_recomu_e)[1] );
	    lep2_charge = (*_recomu_charge)[1];
	    lep2_pdg = (*_recomu_charge)[1]*(-13);
	  }

	  else if(!((*_recomu_isfakeable)[1]==1 && (*_recomu_charge)[0]*(*_recomu_charge)[1]>0) && (*_recoele_isfakeable)[0]==1 && (*_recomu_charge)[0]*(*_recoele_charge)[0]>0 ){
            lep2.SetPxPyPzE( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );
	    lep2_charge = (*_recoele_charge)[0];
	    lep2_pdg = (*_recoele_charge)[0]*(-11);
          }

	  else if((*_recomu_isfakeable)[1]==1 && (*_recomu_charge)[0]*(*_recomu_charge)[1]>0 && (*_recoele_isfakeable)[0]==1 && (*_recomu_charge)[0]*(*_recoele_charge)[0]>0){

	    TLorentzVector mu( (*_recomu_px)[1], (*_recomu_py)[1], (*_recomu_pz)[1], (*_recomu_e)[1] );
	    TLorentzVector ele( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );

	    if(mu.Pt()>ele.Pt()){
	      lep2 = mu;
	      lep2_charge = (*_recomu_charge)[1];
	      lep2_pdg = (*_recomu_charge)[1]*(-13);
            }
	    else{
	      lep2 = ele;
	      lep2_charge = (*_recoele_charge)[0];
	      lep2_pdg = (*_recoele_charge)[0]*(-11);
            }
 	  
	  }

	}

      }



      else if( _n_recoele_mvasel==1 ){

	lep1.SetPxPyPzE( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );
	lep1_charge = (*_recoele_charge)[0];
	lep1_pdg = (*_recoele_charge)[0]*(-11);

	if( _n_recoele_fakeable>=2 && _n_recomu_fakeable==0){
          lep2.SetPxPyPzE( (*_recoele_px)[1], (*_recoele_py)[1], (*_recoele_pz)[1], (*_recoele_e)[1] );
	  lep2_charge = (*_recoele_charge)[1];
	  lep2_pdg = (*_recoele_charge)[1]*(-11);
        }

	else if( _n_recomu_fakeable>=1 && _n_recoele_fakeable==1){
	  lep2.SetPxPyPzE( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );
	  lep2_charge = (*_recomu_charge)[0];
	  lep2_pdg = (*_recomu_charge)[0]*(-13);
	}

	else if( _n_recomu_fakeable>=1 && _n_recoele_fakeable>=2){

	  if( (*_recoele_isfakeable)[1]==1 && (*_recoele_charge)[0]*(*_recoele_charge)[1]>0 && !((*_recomu_isfakeable)[0]==1 && (*_recoele_charge)[0]*(*_recomu_charge)[0]>0) ){
	    lep2.SetPxPyPzE( (*_recoele_px)[1], (*_recoele_py)[1], (*_recoele_pz)[1], (*_recoele_e)[1] );
	    lep2_charge = (*_recoele_charge)[1];
	    lep2_pdg = (*_recoele_charge)[1]*(-11);
	  }

	  else if( !((*_recoele_isfakeable)[1]==1 && (*_recoele_charge)[0]*(*_recoele_charge)[1]>0) && (*_recomu_isfakeable)[0]==1 && (*_recoele_charge)[0]*(*_recomu_charge)[0]>0 ){
	    lep2.SetPxPyPzE( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );
	    lep2_charge = (*_recomu_charge)[0];
	    lep2_pdg = (*_recomu_charge)[0]*(-13);
	  }

	  else if((*_recoele_isfakeable)[1]==1 && (*_recoele_charge)[0]*(*_recoele_charge)[1]>0 && (*_recomu_isfakeable)[0]==1 && (*_recoele_charge)[0]*(*_recomu_charge)[0]>0){
	    
	    TLorentzVector mu( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );
	    TLorentzVector ele( (*_recoele_px)[1], (*_recoele_py)[1], (*_recoele_pz)[1], (*_recoele_e)[1] );

	    if(mu.Pt()>ele.Pt()){
	      lep2 = mu;
	      lep2_charge = (*_recomu_charge)[0];
	      lep2_pdg = (*_recomu_charge)[0]*(-13);
	    }
	    else{
	      lep2 = ele;
	      lep2_charge = (*_recoele_charge)[1];
	      lep2_pdg = (*_recoele_charge)[1]*(-11);
	    }

	  }

	}

      }

    }

    _recolep_MEM_pdg.push_back(lep1_pdg);
    _recolep_MEM_charge.push_back(lep1_charge);
    _recolep_MEM_px.push_back(lep1.Px());
    _recolep_MEM_py.push_back(lep1.Py());
    _recolep_MEM_pz.push_back(lep1.Pz());
    _recolep_MEM_e.push_back(lep1.E());
    _recolep_MEM_pt.push_back(lep1.Pt());
    _recolep_MEM_eta.push_back(lep1.Eta());
    _recolep_MEM_phi.push_back(lep1.Phi());

    _recolep_MEM_pdg.push_back(lep2_pdg);
    _recolep_MEM_charge.push_back(lep2_charge);
    _recolep_MEM_px.push_back(lep2.Px());
    _recolep_MEM_py.push_back(lep2.Py());
    _recolep_MEM_pz.push_back(lep2.Pz());
    _recolep_MEM_e.push_back(lep2.E());
    _recolep_MEM_pt.push_back(lep2.Pt());
    _recolep_MEM_eta.push_back(lep2.Eta());
    _recolep_MEM_phi.push_back(lep2.Phi());
      

    tree_new->Fill();

  }

  tree_new->Write();
  f_new->Close();


  return;

}
