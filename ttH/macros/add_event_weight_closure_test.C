#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include "PUReweight.cc"


using namespace std;




void add_event_weight(TString filein, TString fileout, vector<TString> treename){


  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(fileout,"RECREATE");
  
  for(unsigned int i_tree=0;i_tree<treename.size();i_tree++){

    TChain * tree = new TChain(treename[i_tree]);
    tree->Add(filein);
    
    Long64_t nentries = tree->GetEntries();
    cout<<"nentries="<<tree->GetEntries()<<endl;

    int _category;
    
    vector<int> *_recolep_sel_pdg;
    vector<bool> *_recolep_sel_ismvasel;
    vector<float> *_recolep_sel_fakerate;
    vector<float> *_recolep_sel_fakerate_QCD_MC;
    vector<float> *_recolep_sel_fakerate_ttbar_MC;

    vector<int> *_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
    vector<int> *_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT;
    vector<float> *_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
    vector<float> *_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT;

    tree->SetBranchAddress("category",&_category);
    
    tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
    tree->SetBranchAddress("recolep_sel_ismvasel",&_recolep_sel_ismvasel);
    tree->SetBranchAddress("recolep_sel_fakerate",&_recolep_sel_fakerate);
    tree->SetBranchAddress("recolep_sel_fakerate_QCD_MC",&_recolep_sel_fakerate_QCD_MC);
    tree->SetBranchAddress("recolep_sel_fakerate_ttbar_MC",&_recolep_sel_fakerate_ttbar_MC);

    tree->SetBranchAddress("recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
    tree->SetBranchAddress("recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT);
    tree->SetBranchAddress("recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
    tree->SetBranchAddress("recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT);

    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    //New branches
    float _event_weight_ttH_ele_FR_QCD_MC;
    float _event_weight_ttH_ele_FR_TT_MC;
    float _event_weight_ttH_mu_FR_QCD_MC;
    float _event_weight_ttH_mu_FR_TT_MC;

    tree_new->Branch("event_weight_ttH_ele_FR_QCD_MC",&_event_weight_ttH_ele_FR_QCD_MC,"event_weight_ttH_ele_FR_QCD_MC/F");
    tree_new->Branch("event_weight_ttH_ele_FR_TT_MC",&_event_weight_ttH_ele_FR_TT_MC,"event_weight_ttH_ele_FR_TT_MC/F");
    tree_new->Branch("event_weight_ttH_mu_FR_QCD_MC",&_event_weight_ttH_mu_FR_QCD_MC,"event_weight_ttH_mu_FR_QCD_MC/F");
    tree_new->Branch("event_weight_ttH_mu_FR_TT_MC",&_event_weight_ttH_mu_FR_TT_MC,"event_weight_ttH_mu_FR_TT_MC/F");


    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _category = 0;

      _recolep_sel_pdg = 0;
      _recolep_sel_ismvasel = 0;
      _recolep_sel_fakerate = 0;
      _recolep_sel_fakerate_QCD_MC = 0;
      _recolep_sel_fakerate_ttbar_MC = 0;

      _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;

      _event_weight_ttH_ele_FR_QCD_MC = 1;
      _event_weight_ttH_ele_FR_TT_MC = 1;
      _event_weight_ttH_mu_FR_QCD_MC = 1;
      _event_weight_ttH_mu_FR_TT_MC = 1;
      
      tree->GetEntry(i);

      int n_fake = 0;

      if(!(*_recolep_sel_ismvasel)[0]){

	n_fake++;
	
	if(abs((*_recolep_sel_pdg)[0])==11){
	  _event_weight_ttH_ele_FR_QCD_MC *= (*_recolep_sel_fakerate_QCD_MC)[0]/(1-(*_recolep_sel_fakerate_QCD_MC)[0]);
	  _event_weight_ttH_ele_FR_TT_MC *= (*_recolep_sel_fakerate_ttbar_MC)[0]/(1-(*_recolep_sel_fakerate_ttbar_MC)[0]);
	  _event_weight_ttH_mu_FR_QCD_MC *= (*_recolep_sel_fakerate)[0]/(1-(*_recolep_sel_fakerate)[0]);
	  _event_weight_ttH_mu_FR_TT_MC *= (*_recolep_sel_fakerate)[0]/(1-(*_recolep_sel_fakerate)[0]);
	}

	else if(abs((*_recolep_sel_pdg)[0])==13){
	  _event_weight_ttH_ele_FR_QCD_MC *= (*_recolep_sel_fakerate)[0]/(1-(*_recolep_sel_fakerate)[0]);
	  _event_weight_ttH_ele_FR_TT_MC *= (*_recolep_sel_fakerate)[0]/(1-(*_recolep_sel_fakerate)[0]);
	  _event_weight_ttH_mu_FR_QCD_MC *= (*_recolep_sel_fakerate_QCD_MC)[0]/(1-(*_recolep_sel_fakerate_QCD_MC)[0]);
	  _event_weight_ttH_mu_FR_TT_MC *= (*_recolep_sel_fakerate_ttbar_MC)[0]/(1-(*_recolep_sel_fakerate_ttbar_MC)[0]);
	}

      }

      if((*_recolep_sel_ismvasel).size()>1){

	if(!(*_recolep_sel_ismvasel)[1]){
	  
	  n_fake++;

	  if(abs((*_recolep_sel_pdg)[1])==11){
	    _event_weight_ttH_ele_FR_QCD_MC *= (*_recolep_sel_fakerate_QCD_MC)[1]/(1-(*_recolep_sel_fakerate_QCD_MC)[1]);
	    _event_weight_ttH_ele_FR_TT_MC *= (*_recolep_sel_fakerate_ttbar_MC)[1]/(1-(*_recolep_sel_fakerate_ttbar_MC)[1]);
	    _event_weight_ttH_mu_FR_QCD_MC *= (*_recolep_sel_fakerate)[1]/(1-(*_recolep_sel_fakerate)[1]);
	    _event_weight_ttH_mu_FR_TT_MC *= (*_recolep_sel_fakerate)[1]/(1-(*_recolep_sel_fakerate)[1]);
	  }

	  else if(abs((*_recolep_sel_pdg)[1])==13){
	    _event_weight_ttH_ele_FR_QCD_MC *= (*_recolep_sel_fakerate)[1]/(1-(*_recolep_sel_fakerate)[1]);
	    _event_weight_ttH_ele_FR_TT_MC *= (*_recolep_sel_fakerate)[1]/(1-(*_recolep_sel_fakerate)[1]);
	    _event_weight_ttH_mu_FR_QCD_MC *= (*_recolep_sel_fakerate_QCD_MC)[1]/(1-(*_recolep_sel_fakerate_QCD_MC)[1]);
	    _event_weight_ttH_mu_FR_TT_MC *= (*_recolep_sel_fakerate_ttbar_MC)[1]/(1-(*_recolep_sel_fakerate_ttbar_MC)[1]);
	  }

	}

      }


      if((*_recolep_sel_ismvasel).size()>2){

	if(!(*_recolep_sel_ismvasel)[2]){
	  
	  n_fake++;

	  if(abs((*_recolep_sel_pdg)[2])==11){
	    _event_weight_ttH_ele_FR_QCD_MC *= (*_recolep_sel_fakerate_QCD_MC)[2]/(1-(*_recolep_sel_fakerate_QCD_MC)[2]);
	    _event_weight_ttH_ele_FR_TT_MC *= (*_recolep_sel_fakerate_ttbar_MC)[2]/(1-(*_recolep_sel_fakerate_ttbar_MC)[2]);
	    _event_weight_ttH_mu_FR_QCD_MC *= (*_recolep_sel_fakerate)[2]/(1-(*_recolep_sel_fakerate)[2]);
	    _event_weight_ttH_mu_FR_TT_MC *= (*_recolep_sel_fakerate)[2]/(1-(*_recolep_sel_fakerate)[2]);
	  }

	  else if(abs((*_recolep_sel_pdg)[2])==13){
	    _event_weight_ttH_ele_FR_QCD_MC *= (*_recolep_sel_fakerate)[2]/(1-(*_recolep_sel_fakerate)[2]);
	    _event_weight_ttH_ele_FR_TT_MC *= (*_recolep_sel_fakerate)[2]/(1-(*_recolep_sel_fakerate)[2]);
	    _event_weight_ttH_mu_FR_QCD_MC *= (*_recolep_sel_fakerate_QCD_MC)[2]/(1-(*_recolep_sel_fakerate_QCD_MC)[2]);
	    _event_weight_ttH_mu_FR_TT_MC *= (*_recolep_sel_fakerate_ttbar_MC)[2]/(1-(*_recolep_sel_fakerate_ttbar_MC)[2]);
	  }

	}

      }      

      if(_category==50){

	if(!(*_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]){

	  n_fake++;

	  float weight_tau = (*_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(*_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]);
	  _event_weight_ttH_ele_FR_QCD_MC *= weight_tau;
	  _event_weight_ttH_ele_FR_TT_MC *= weight_tau;
	  _event_weight_ttH_mu_FR_QCD_MC *= weight_tau;
	  _event_weight_ttH_mu_FR_TT_MC *= weight_tau;

	}

	if(!(*_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT)[1]){

	  n_fake++;
	
	  float weight_tau = (*_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[1]/(1-(*_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[1]);
	  _event_weight_ttH_ele_FR_QCD_MC *= weight_tau;
	  _event_weight_ttH_ele_FR_TT_MC *= weight_tau;
	  _event_weight_ttH_mu_FR_QCD_MC *= weight_tau;
	  _event_weight_ttH_mu_FR_TT_MC *= weight_tau;

	}

      }
    
      else if(_category==41 || _category==46){

	if(!(*_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]){

	  n_fake++;

	  float weight_tau = (*_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(*_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]);
	  _event_weight_ttH_ele_FR_QCD_MC *= weight_tau;
	  _event_weight_ttH_ele_FR_TT_MC *= weight_tau;
	  _event_weight_ttH_mu_FR_QCD_MC *= weight_tau;
	  _event_weight_ttH_mu_FR_TT_MC *= weight_tau;

	}

      }


      if(n_fake>0 && n_fake%2==0){
	_event_weight_ttH_ele_FR_QCD_MC *=-1;
	_event_weight_ttH_ele_FR_TT_MC *=-1;
	_event_weight_ttH_mu_FR_QCD_MC *=-1;
	_event_weight_ttH_mu_FR_QCD_MC *=-1;

      }

      
      tree_new->Fill();

    }

   
    f_new->cd();
    
    tree_new->Write();


  }

  f_new->Close();


  return;

}






void test(){

  vector<TString> treename;
  //treename.push_back("HTauTauTree_2lSS_lepMVA_CR");
  //treename.push_back("HTauTauTree_3l_lepMVA_CR");
  treename.push_back("T");

  //TString filein = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split_bTagSF_CSVshape_PU.root";
  //TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split_bTagSF_CSVshape_PU_FR_clos.root";
  TString filein = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/TTbar/TTbar_DL_split_2lSS_lepMVA_CR_MEM_PU.root";
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/TTbar/TTbar_DL_split_2lSS_lepMVA_CR_MEM_PU_FR_clos.root";
  
  add_event_weight(filein,fileout,treename);




}
