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




void add_perm_info(){

  TString file_in="/data_CMS/cms/strebler/TTJets_Samples/MEM_samples/ttbar_SLfromT_skim_MEM_160520.root";

  TString file_out="/data_CMS/cms/strebler/TTJets_Samples/MEM_samples/ttbar_SLfromT_skim_MEM_160520_perm.root";
  
  TChain * tree = new TChain("T");
  tree->Add(file_in);

  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(file_out);
  if(f_new!=0){
    cout<<file_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(file_out,"RECREATE");
  TTree* tree_new=tree->GetTree()->CloneTree(0);

  //Old branches used
  int _event_type;
  int _integration_type;

  int _n_recomu_mvasel;
  int _n_recomu_fakeable;
  int _n_recoele_mvasel;
  int _n_recoele_fakeable;

  vector<float>* _recomu_px;
  vector<float>* _recomu_py;
  vector<float>* _recomu_pz;
  vector<float>* _recomu_e;
  vector<int>* _recomu_charge;
  vector<bool>* _recomu_isfakeable;

  vector<float>* _recoele_px;
  vector<float>* _recoele_py;
  vector<float>* _recoele_pz;
  vector<float>* _recoele_e;
  vector<int>* _recoele_charge;
  vector<bool>* _recoele_isfakeable;

  vector<float>* _recoPFJet_btag_px;
  vector<float>* _recoPFJet_btag_py;
  vector<float>* _recoPFJet_btag_pz;
  vector<float>* _recoPFJet_btag_e;

  vector<float>* _recoPFJet_untag_Wtag_px;
  vector<float>* _recoPFJet_untag_Wtag_py;
  vector<float>* _recoPFJet_untag_Wtag_pz;
  vector<float>* _recoPFJet_untag_Wtag_e;

  vector<float>* _genlep_px;
  vector<float>* _genlep_py;
  vector<float>* _genlep_pz;
  vector<float>* _genlep_e;
  vector<int>* _genlep_TopMothInd;
  vector<int>* _genlep_WMothInd;

  vector<float>* _genb_px;
  vector<float>* _genb_py;
  vector<float>* _genb_pz;
  vector<float>* _genb_e;
  vector<int>* _genb_TopMothInd;

  vector<float>* _genq_px;
  vector<float>* _genq_py;
  vector<float>* _genq_pz;
  vector<float>* _genq_e;
  vector<int>* _genq_TopMothInd;
  vector<int>* _genq_WMothInd;

  tree->SetBranchAddress("event_type",&_event_type);
  tree->SetBranchAddress("integration_type",&_integration_type);

  tree->SetBranchAddress("n_recomu_mvasel",&_n_recomu_mvasel);
  tree->SetBranchAddress("n_recomu_fakeable",&_n_recomu_fakeable);
  tree->SetBranchAddress("n_recoele_mvasel",&_n_recoele_mvasel);
  tree->SetBranchAddress("n_recoele_fakeable",&_n_recoele_fakeable);

  tree->SetBranchAddress("recomu_px",&_recomu_px);
  tree->SetBranchAddress("recomu_py",&_recomu_py);
  tree->SetBranchAddress("recomu_pz",&_recomu_pz);
  tree->SetBranchAddress("recomu_e",&_recomu_e);
  
  tree->SetBranchAddress("recoele_px",&_recoele_px);
  tree->SetBranchAddress("recoele_py",&_recoele_py);
  tree->SetBranchAddress("recoele_pz",&_recoele_pz);
  tree->SetBranchAddress("recoele_e",&_recoele_e);

  tree->SetBranchAddress("recoPFJet_btag_px",&_recoPFJet_btag_px);
  tree->SetBranchAddress("recoPFJet_btag_py",&_recoPFJet_btag_py);
  tree->SetBranchAddress("recoPFJet_btag_pz",&_recoPFJet_btag_pz);
  tree->SetBranchAddress("recoPFJet_btag_e",&_recoPFJet_btag_e);

  tree->SetBranchAddress("recoPFJet_untag_Wtag_px",&_recoPFJet_untag_Wtag_px);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_py",&_recoPFJet_untag_Wtag_py);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_pz",&_recoPFJet_untag_Wtag_pz);
  tree->SetBranchAddress("recoPFJet_untag_Wtag_e",&_recoPFJet_untag_Wtag_e);

  tree->SetBranchAddress("genlep_px",&_genlep_px);
  tree->SetBranchAddress("genlep_py",&_genlep_py);
  tree->SetBranchAddress("genlep_pz",&_genlep_pz);
  tree->SetBranchAddress("genlep_e",&_genlep_e);
  tree->SetBranchAddress("genlep_TopMothInd",&_genlep_TopMothInd);
  tree->SetBranchAddress("genlep_WMothInd",&_genlep_WMothInd);

  tree->SetBranchAddress("genb_px",&_genb_px);
  tree->SetBranchAddress("genb_py",&_genb_py);
  tree->SetBranchAddress("genb_pz",&_genb_pz);
  tree->SetBranchAddress("genb_e",&_genb_e);
  tree->SetBranchAddress("genb_TopMothInd",&_genb_TopMothInd);  

  tree->SetBranchAddress("genq_px",&_genq_px);
  tree->SetBranchAddress("genq_py",&_genq_py);
  tree->SetBranchAddress("genq_pz",&_genq_pz);
  tree->SetBranchAddress("genq_e",&_genq_e);
  tree->SetBranchAddress("genq_TopMothInd",&_genq_TopMothInd);
  tree->SetBranchAddress("genq_WMothInd",&_genq_WMothInd);

  //New branches

  int _good_perm;

  tree_new->Branch("good_perm",&_good_perm);

  for(unsigned int i=0;i<nentries;i++){

    _good_perm = -1;
    
    _event_type = 0;
    _integration_type = 0;
  
    _n_recomu_mvasel = 0;
    _n_recomu_fakeable = 0;
    _n_recoele_mvasel = 0;
    _n_recoele_fakeable = 0;

    _recomu_px = 0;
    _recomu_py = 0;
    _recomu_pz = 0;
    _recomu_e = 0;
    _recomu_charge = 0;
    _recomu_isfakeable = 0;

    _recoele_px = 0;
    _recoele_py = 0;
    _recoele_pz = 0;
    _recoele_e = 0;
    _recoele_charge = 0;
    _recoele_isfakeable = 0;
  
    _recoPFJet_btag_px = 0;
    _recoPFJet_btag_py = 0;
    _recoPFJet_btag_pz = 0;
    _recoPFJet_btag_e = 0;
  
    _recoPFJet_untag_Wtag_px = 0;
    _recoPFJet_untag_Wtag_py = 0;
    _recoPFJet_untag_Wtag_pz = 0;
    _recoPFJet_untag_Wtag_e = 0;    

    _genlep_px = 0;
    _genlep_py = 0;
    _genlep_pz = 0;
    _genlep_e = 0;
    _genlep_TopMothInd = 0;
    _genlep_WMothInd = 0;

    _genb_px = 0;
    _genb_py = 0;
    _genb_pz = 0;
    _genb_e = 0;
    _genb_TopMothInd = 0;

    _genq_px = 0;
    _genq_py = 0;
    _genq_pz = 0;
    _genq_e = 0;
    _genq_TopMothInd = 0;
    _genq_WMothInd = 0;

    tree->GetEntry(i);

    TLorentzVector lep_top;

    for(unsigned int i_lep=0; i_lep<(*_genlep_TopMothInd).size(); i_lep++){
	
      if( (*_genlep_TopMothInd)[i_lep]==0 && (*_genlep_WMothInd)[i_lep]>=0 ){
	if(lep_top.Pt()>0)
	  cout<<"Lep already filled"<<endl;     
	lep_top.SetPxPyPzE((*_genlep_px)[i_lep], (*_genlep_py)[i_lep], (*_genlep_pz)[i_lep], (*_genlep_e)[i_lep]);
	break;
      }
      
    }

    cout<<"New event"<<endl;
    cout<<"Gen lep top"<<endl;
    lep_top.Print();
    
    
    TLorentzVector blep;
    TLorentzVector bhad;

    for(unsigned int i_b=0; i_b<(*_genb_TopMothInd).size(); i_b++){

      if( (*_genb_TopMothInd)[i_b]==0 ){
	if(blep.Pt()>0)
	  cout<<"blep alredy filled"<<endl;
	blep.SetPxPyPzE((*_genb_px)[i_b], (*_genb_py)[i_b], (*_genb_pz)[i_b], (*_genb_e)[i_b]);
      }

      else if( (*_genb_TopMothInd)[i_b]==1 ){
	if(bhad.Pt()>0){
	  continue;
	  cout<<"bhad alredy filled"<<endl;
	}
	bhad.SetPxPyPzE((*_genb_px)[i_b], (*_genb_py)[i_b], (*_genb_pz)[i_b], (*_genb_e)[i_b]);
      }

    }


    
    TLorentzVector q1;
    TLorentzVector q2;

    for(unsigned int i_q=0; i_q<(*_genq_TopMothInd).size();i_q++){

      if((*_genq_TopMothInd)[i_q]==1 && (*_genq_WMothInd)[i_q]>=0){
	if(q1.Pt()>0){
	  if(q2.Pt()>0)
	    cout<<"q2 already filled"<<endl;
	  q2.SetPxPyPzE((*_genq_px)[i_q], (*_genq_py)[i_q], (*_genq_pz)[i_q], (*_genq_e)[i_q]);
	  break;
	}
	else{
	  q1.SetPxPyPzE((*_genq_px)[i_q], (*_genq_py)[i_q], (*_genq_pz)[i_q], (*_genq_e)[i_q]);
	}
      }

    }


    if(_integration_type==0){

      TLorentzVector lep1;
      TLorentzVector lep2;

      cout<<"event_type="<<_event_type<<endl;

      if(_event_type==1){

	if(_n_recomu_mvasel==2){
	  lep1.SetPxPyPzE( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );
	  lep2.SetPxPyPzE( (*_recomu_px)[1], (*_recomu_py)[1], (*_recomu_pz)[1], (*_recomu_e)[1] );
	}

	else if( _n_recoele_mvasel==2 ){
	  lep1.SetPxPyPzE( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );
	  lep2.SetPxPyPzE( (*_recoele_px)[1], (*_recoele_py)[1], (*_recoele_pz)[1], (*_recoele_e)[1] );
	}

	else if( _n_recomu_mvasel==1 && _n_recoele_mvasel==1 ){
	  lep1.SetPxPyPzE( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );
	  lep2.SetPxPyPzE( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );
	  if(lep2.Pt()>lep1.Pt()){
	    TLorentzVector l=lep1;
	    lep1=lep2;
	    lep2=l;
	  }
	}

      }


      else if(_event_type==0){
	    
	cout<<"n_recomu_mvasel="<<_n_recomu_mvasel<<endl;
	cout<<"n_recoele_mvasel="<<_n_recoele_mvasel<<endl;

	if( _n_recomu_mvasel==1 ){
        
	  lep1.SetPxPyPzE( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );

	  if( _n_recomu_fakeable>=1 && _n_recoele_fakeable==0){
	    lep2.SetPxPyPzE( (*_recomu_px)[1], (*_recomu_py)[1], (*_recomu_pz)[1], (*_recomu_e)[1] );
	  }

	  else if( _n_recoele_fakeable>=1 && _n_recomu_fakeable==0){
	    lep2.SetPxPyPzE( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );
	  }

	  else if( _n_recomu_fakeable>=1 && _n_recoele_fakeable>=1){

	    if((*_recomu_isfakeable)[1]==1 && (*_recomu_charge)[0]*(*_recomu_charge)[1]>0 && !((*_recoele_isfakeable)[0]==1 && (*_recomu_charge)[0]*(*_recoele_charge)[0]>0) ){
	    lep2.SetPxPyPzE( (*_recomu_px)[1], (*_recomu_py)[1], (*_recomu_pz)[1], (*_recomu_e)[1] );
	    }

	    else if(!((*_recomu_isfakeable)[1]==1 && (*_recomu_charge)[0]*(*_recomu_charge)[1]>0) && (*_recoele_isfakeable)[0]==1 && (*_recomu_charge)[0]*(*_recoele_charge)[0]>0 ){
	      lep2.SetPxPyPzE( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );
	    }

	    else if((*_recomu_isfakeable)[1]==1 && (*_recomu_charge)[0]*(*_recomu_charge)[1]>0 && (*_recoele_isfakeable)[0]==1 && (*_recomu_charge)[0]*(*_recoele_charge)[0]>0){

	      TLorentzVector mu( (*_recomu_px)[1], (*_recomu_py)[1], (*_recomu_pz)[1], (*_recomu_e)[1] );
	      TLorentzVector ele( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );

	      if(mu.Pt()>ele.Pt())
		lep2 = mu;
	      else
		lep2 = ele;

	    }

	  }

	}	


	else if( _n_recoele_mvasel==1 ){
	  
	  lep1.SetPxPyPzE( (*_recoele_px)[0], (*_recoele_py)[0], (*_recoele_pz)[0], (*_recoele_e)[0] );

	  cout<<"n_recoele_fakeable="<<_n_recoele_fakeable<<" n_recomu_fakeable="<<_n_recomu_fakeable<<endl;

	  if( _n_recoele_fakeable>=1 && _n_recomu_fakeable==0){
	    lep2.SetPxPyPzE( (*_recoele_px)[1], (*_recoele_py)[1], (*_recoele_pz)[1], (*_recoele_e)[1] );
	  }

	  else if( _n_recomu_fakeable>=1 && _n_recoele_fakeable==0){
	    lep2.SetPxPyPzE( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );
	  }

	  else if( _n_recomu_fakeable>=1 && _n_recoele_fakeable>=1){ 

	    if((*_recoele_isfakeable)[1]==1 && (*_recoele_charge)[0]*(*_recoele_charge)[1]>0 && !((*_recomu_isfakeable)[0]==1 && (*_recoele_charge)[0]*(*_recomu_charge)[0]>0) ){
	      lep2.SetPxPyPzE( (*_recoele_px)[1], (*_recoele_py)[1], (*_recoele_pz)[1], (*_recoele_e)[1] );
	    }
	  
	    else if(!((*_recoele_isfakeable)[1]==1 && (*_recoele_charge)[0]*(*_recoele_charge)[1]>0) && (*_recomu_isfakeable)[0]==1 && (*_recoele_charge)[0]*(*_recomu_charge)[0]>0 ){
	      lep2.SetPxPyPzE( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );
	    }

	    else if((*_recoele_isfakeable)[1]==1 && (*_recoele_charge)[0]*(*_recoele_charge)[1]>0 && (*_recomu_isfakeable)[0]==1 && (*_recoele_charge)[0]*(*_recomu_charge)[0]>0){

	      TLorentzVector ele( (*_recoele_px)[1], (*_recoele_py)[1], (*_recoele_pz)[1], (*_recoele_e)[1] );
	      TLorentzVector mu( (*_recomu_px)[0], (*_recomu_py)[0], (*_recomu_pz)[0], (*_recomu_e)[0] );

	      if(ele.Pt()>mu.Pt())
		lep2 = ele;
	      else
		lep2 = mu;

	    }

	  }

	}

      }

    
      cout<<"Reco lep 1"<<endl;
      lep1.Print();
      cout<<"Reco lep 2"<<endl;
      lep2.Print();

    }


    tree_new->Fill();

  }

  tree_new->Write();
  f_new->Close();

  return;


}
