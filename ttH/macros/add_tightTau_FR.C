#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>
#include <TList.h>


using namespace std;



void add_tightTau_FR_2lSS(TString filein, TString fileout){


  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(fileout,"RECREATE");

  TChain* tree = new TChain("HTauTauTree_2lSS");
  tree->Add(filein);
  
  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<tree->GetEntries()<<endl;
    
  //Old branches
  vector<int>* _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<float>* _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT;

  tree->SetBranchAddress("recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT);


  TTree* HTauTauTree_2lSS=tree->GetTree()->CloneTree(0);
  TTree* HTauTauTree_2lSS_lepMVA_CR_1=tree->GetTree()->CloneTree(0);
  HTauTauTree_2lSS_lepMVA_CR_1->SetNameTitle("HTauTauTree_2lSS_lepMVA_CR_1","HTauTauTree_2lSS_lepMVA_CR_1");


  //New branches
  float _event_weight_ttH_v2;
  int _category_v2;

  HTauTauTree_2lSS->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  HTauTauTree_2lSS->Branch("category_v2",&_category_v2,"category_v2/I");
  HTauTauTree_2lSS_lepMVA_CR_1->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  HTauTauTree_2lSS_lepMVA_CR_1->Branch("category_v2",&_category_v2,"category_v2/I");

  
  for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
  
      _event_weight_ttH_v2 = 0;
      _category_v2 = 0;

      tree->GetEntry(i);

      if((*_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]){
	_event_weight_ttH_v2 = 1;
	_category_v2 = 11;
	HTauTauTree_2lSS->Fill();
      }
      else{
	float weight_tau = (*_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(*_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]);
	_event_weight_ttH_v2 = weight_tau;
	_category_v2 = 41;
	HTauTauTree_2lSS_lepMVA_CR_1->Fill();
      }
  
  }


  
  
  TChain* tree2 = new TChain("HTauTauTree_2lSS_lepMVA_CR");
  tree2->Add(filein);

  nentries = tree2->GetEntries();
  cout<<"nentries="<<tree2->GetEntries()<<endl;

  vector<int>* _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<float>* _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  float _event_weight_ttH;
  int _category;

  tree2->SetBranchAddress("recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree2->SetBranchAddress("category",&_category);

  TTree* HTauTauTree_2lSS_lepMVA_CR_2=tree2->GetTree()->CloneTree(0);
  HTauTauTree_2lSS_lepMVA_CR_2->SetNameTitle("HTauTauTree_2lSS_lepMVA_CR_2","HTauTauTree_2lSS_lepMVA_CR_2");

  HTauTauTree_2lSS_lepMVA_CR_2->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  HTauTauTree_2lSS_lepMVA_CR_2->Branch("category_v2",&_category_v2,"category_v2/I");

  
  for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _event_weight_ttH = 0;
      _category = 0;
      
      _event_weight_ttH_v2 = 0;
      _category_v2 = 0;
  
      tree2->GetEntry(i);

      if(_category!=41) continue;

      _category_v2 = 41;

      if(!(*_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]){

	float weight_tau_old = (*_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(*_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]);
      	float weight_tau_new = (*_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(*_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]);
	_event_weight_ttH_v2 = _event_weight_ttH * weight_tau_new / weight_tau_old;

      }

      else{

	if((*_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0])
	  _event_weight_ttH_v2 = _event_weight_ttH;
	else{
	  float weight_tau_new = (*_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(*_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]);
	  _event_weight_ttH_v2 = _event_weight_ttH * (-1.) * weight_tau_new;
	}

      }

      HTauTauTree_2lSS_lepMVA_CR_2->Fill();

  }


  f_new->cd();
    
  HTauTauTree_2lSS->Write();


  TList *list = new TList();
  list->Add(HTauTauTree_2lSS_lepMVA_CR_1);
  list->Add(HTauTauTree_2lSS_lepMVA_CR_2);
  TTree *HTauTauTree_2lSS_lepMVA_CR_merge = TTree::MergeTrees(list);
  HTauTauTree_2lSS_lepMVA_CR_merge->SetNameTitle("HTauTauTree_2lSS_lepMVA_CR","HTauTauTree_2lSS_lepMVA_CR");
  HTauTauTree_2lSS_lepMVA_CR_merge->Write();

  
  f_new->Close();


  return;



}








void add_tightTau_FR_3l(TString filein, TString fileout){


  TFile* f_new = TFile::Open(fileout);
  if(f_new!=0){
    cout<<fileout<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(fileout,"RECREATE");

  TChain* tree = new TChain("HTauTauTree_3l");
  tree->Add(filein);
  
  Long64_t nentries = tree->GetEntries();
  cout<<"nentries="<<tree->GetEntries()<<endl;
    
  //Old branches
  vector<int>* _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<float>* _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  int _category;

  tree->SetBranchAddress("recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree->SetBranchAddress("category",&_category);

  TTree* HTauTauTree_3l=tree->GetTree()->CloneTree(0);
  TTree* HTauTauTree_3l_lepMVA_CR_1=tree->GetTree()->CloneTree(0);
  HTauTauTree_3l_lepMVA_CR_1->SetNameTitle("HTauTauTree_3l_lepMVA_CR_1","HTauTauTree_3l_lepMVA_CR_1");


  //New branches
  float _event_weight_ttH_v2;
  int _category_v2;

  HTauTauTree_3l->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  HTauTauTree_3l->Branch("category_v2",&_category_v2,"category_v2/I");
  HTauTauTree_3l_lepMVA_CR_1->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  HTauTauTree_3l_lepMVA_CR_1->Branch("category_v2",&_category_v2,"category_v2/I");

  
  for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
  
      _event_weight_ttH_v2 = 0;
      _category_v2 = 0;

      tree->GetEntry(i);
      
      if(_category!=16) continue;

      if((*_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]){
	_event_weight_ttH_v2 = 1;
	_category_v2 = 16;
	HTauTauTree_3l->Fill();
      }
      else{
	float weight_tau = (*_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(*_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]);
	_event_weight_ttH_v2 = weight_tau;
	_category_v2 = 46;
	HTauTauTree_3l_lepMVA_CR_1->Fill();
      }
  
  }


  
  
  TChain* tree2 = new TChain("HTauTauTree_3l_lepMVA_CR");
  tree2->Add(filein);

  nentries = tree2->GetEntries();
  cout<<"nentries="<<tree2->GetEntries()<<endl;

  vector<int>* _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<float>* _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  float _event_weight_ttH;

  vector<float>* _recotauh_sel_px;
  vector<float>* _recotauh_sel_py;
  vector<float>* _recotauh_sel_pz;
  vector<float>* _recotauh_sel_e;

  vector<float>* _recotauh_px;
  vector<float>* _recotauh_py;
  vector<float>* _recotauh_pz;
  vector<float>* _recotauh_e;
  vector<float>* _recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<float>* _recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT;


  tree2->SetBranchAddress("recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree2->SetBranchAddress("category",&_category);

  tree2->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
  tree2->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
  tree2->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
  tree2->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);

  tree2->SetBranchAddress("recotauh_px",&_recotauh_px);
  tree2->SetBranchAddress("recotauh_py",&_recotauh_py);
  tree2->SetBranchAddress("recotauh_pz",&_recotauh_pz);
  tree2->SetBranchAddress("recotauh_e",&_recotauh_e);

  tree2->SetBranchAddress("recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT);


  TTree* HTauTauTree_3l_lepMVA_CR_2=tree2->GetTree()->CloneTree(0);
  HTauTauTree_3l_lepMVA_CR_2->SetNameTitle("HTauTauTree_3l_lepMVA_CR_2","HTauTauTree_3l_lepMVA_CR_2");

  HTauTauTree_3l_lepMVA_CR_2->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  HTauTauTree_3l_lepMVA_CR_2->Branch("category_v2",&_category_v2,"category_v2/I");

  
  for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _event_weight_ttH = 0;
      _category = 0;
      
      _event_weight_ttH_v2 = 0;
      _category_v2 = 0;

      _recotauh_sel_px = 0;
      _recotauh_sel_py = 0;
      _recotauh_sel_pz = 0;
      _recotauh_sel_e = 0;
      
      _recotauh_px = 0;
      _recotauh_py = 0;
      _recotauh_pz = 0;
      _recotauh_e = 0;
      _recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT = 0;

  
      tree2->GetEntry(i);

      if(_category!=46) continue;

      _category_v2 = 46;


      float medium_FR = 0;
      float tight_FR = 0;
      
      TLorentzVector tau_sel((*_recotauh_sel_px)[0], (*_recotauh_sel_py)[0], (*_recotauh_sel_pz)[0], (*_recotauh_sel_e)[0]);


      for(unsigned int i_tau=0;i_tau<(*_recotauh_px).size();i_tau++){

	TLorentzVector tau((*_recotauh_px)[0], (*_recotauh_py)[0], (*_recotauh_pz)[0], (*_recotauh_e)[0]);
	float dR = tau.DeltaR(tau_sel);

	if(dR<0.01){
	  medium_FR = (*_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau];
	  tight_FR = (*_recotauh_fakerate_byTightIsolationMVArun2v1DBdR03oldDMwLT)[i_tau];
	  break;
	}

      }


      if(!(*_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]){
	
	float weight_tau_old = medium_FR/(1-medium_FR);
	float weight_tau_new = tight_FR/(1-tight_FR);
	_event_weight_ttH_v2 = _event_weight_ttH * weight_tau_new / weight_tau_old;

      }

      else{

	if((*_recotauh_sel_byTightIsolationMVArun2v1DBdR03oldDMwLT)[0]){
	  _event_weight_ttH_v2 = _event_weight_ttH;
	}
	else{
	  float weight_tau_new = tight_FR/(1-tight_FR);
	  _event_weight_ttH_v2 = _event_weight_ttH * (-1.) * weight_tau_new;
	}

      }

      HTauTauTree_3l_lepMVA_CR_2->Fill();

  }


  f_new->cd();
    
  HTauTauTree_3l->Write();


  TList *list = new TList();
  list->Add(HTauTauTree_3l_lepMVA_CR_1);
  list->Add(HTauTauTree_3l_lepMVA_CR_2);
  TTree *HTauTauTree_3l_lepMVA_CR_merge = TTree::MergeTrees(list);
  HTauTauTree_3l_lepMVA_CR_merge->SetNameTitle("HTauTauTree_3l_lepMVA_CR","HTauTauTree_3l_lepMVA_CR");
  HTauTauTree_3l_lepMVA_CR_merge->Write();

  
  f_new->Close();


  return;



}






void test(){

  TString filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU_lepSF.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_TightTau_2lSS.root"; 
  add_tightTau_FR_2lSS(filein,fileout);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_TightTau_2lSS.root"; 
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);


 filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);




  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);



  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split_TightTau_2lSS.root";
  add_tightTau_FR_2lSS(filein,fileout);



}











void test_3l(){

  TString filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU_lepSF.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_TightTau_3l.root"; 
  add_tightTau_FR_3l(filein,fileout);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_TightTau_3l.root"; 
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);


 filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);




  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);



  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split_TightTau_3l.root";
  add_tightTau_FR_3l(filein,fileout);



}
