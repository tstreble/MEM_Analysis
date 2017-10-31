#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>
#include "leptonSF.cc"


using namespace std;



void add_correct_1lSF(TString filein, TString fileout, vector<TString> treename){
  
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
    
    
    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    //New branches
    float _triggerSF_weight_v2;
    float _triggerSF_weight_v2_up;
    float _triggerSF_weight_v2_down;
    
    float _leptonSF_ttH_weight_v2;

    tree_new->Branch("triggerSF_weight_v2",&_triggerSF_weight_v2,"triggerSF_weight_v2/F");
    tree_new->Branch("triggerSF_weight_v2_up",&_triggerSF_weight_v2_up,"triggerSF_weight_v2_up/F");
    tree_new->Branch("triggerSF_weight_v2_down",&_triggerSF_weight_v2_down,"triggerSF_weight_v2_down/F");

    tree_new->Branch("leptonSF_ttH_weight_v2",&_leptonSF_ttH_weight_v2,"leptonSF_ttH_weight_v2/F");

    //Old branches
    vector<int>* _recolep_sel_pdg;
    vector<float>* _recolep_sel_pt;
    vector<float>* _recolep_sel_eta;
    
    tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
    tree->SetBranchAddress("recolep_sel_pt",&_recolep_sel_pt);
    tree->SetBranchAddress("recolep_sel_eta",&_recolep_sel_eta);

  
    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _recolep_sel_pdg = 0;
      _recolep_sel_pt = 0;
      _recolep_sel_eta = 0;

      _triggerSF_weight_v2 = 1;
      _triggerSF_weight_v2_up = 1;
      _triggerSF_weight_v2_down = 1;
      
      _leptonSF_ttH_weight_v2 = 1;
            
      tree->GetEntry(i);
      
      _triggerSF_weight_v2 = triggerSF_ttH_1l((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0]);
      _triggerSF_weight_v2_up = triggerSF_ttH_1l((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0], +1.);
      _triggerSF_weight_v2_down = triggerSF_ttH_1l((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0], -1.);

      _leptonSF_ttH_weight_v2 = leptonSF_ttH((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3);


      tree_new->Fill();
      
    }
    
    f_new->cd();
    
    tree_new->Write();
    
  }



  f_new->Close();


  return;

}
     
    


void add_syst_2ltrigSF(TString filein, TString fileout, vector<TString> treename){
  
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
    
    
    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    //New branches
    float _triggerSF_weight_up;
    float _triggerSF_weight_down;
 
    tree_new->Branch("triggerSF_weight_up",&_triggerSF_weight_up,"triggerSF_weight_up/F");
    tree_new->Branch("triggerSF_weight_down",&_triggerSF_weight_down,"triggerSF_weight_down/F");


    //Old branches
    vector<int>* _recolep_sel_pdg;
    
    tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
 

  
    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _recolep_sel_pdg = 0;

      _triggerSF_weight_up = 1;
      _triggerSF_weight_down = 1;
                  
      tree->GetEntry(i);
      
      if(abs((*_recolep_sel_pdg)[0])==11 && abs((*_recolep_sel_pdg)[1])==11){
	_triggerSF_weight_up = 1.04;
	_triggerSF_weight_down = 1.0;
      }
      else if(abs((*_recolep_sel_pdg)[0])==11 || abs((*_recolep_sel_pdg)[1])==11){
	_triggerSF_weight_up = 1.03;
	_triggerSF_weight_down = 1.01;
      }
      else if(abs((*_recolep_sel_pdg)[0])==13 && abs((*_recolep_sel_pdg)[1])==13){
	_triggerSF_weight_up = 1.02;
	_triggerSF_weight_down = 1.0;
      }


      tree_new->Fill();
      
    }
    
    f_new->cd();
    
    tree_new->Write();
    
  }



  f_new->Close();


  return;

}
     
    





void add_correct_SF(TString filein, TString fileout, vector<TString> treename){
  
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
    
    
   //Old branches
    vector<int>* _recolep_sel_pdg;
    vector<float>* _recolep_sel_pt;
    vector<float>* _recolep_sel_eta;
    vector<bool>* _recolep_sel_ismvasel;

    vector<bool>* _recotauh_sel_isGenMatched;
    int _category;

    
    tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
    tree->SetBranchAddress("recolep_sel_pt",&_recolep_sel_pt);
    tree->SetBranchAddress("recolep_sel_eta",&_recolep_sel_eta);
    tree->SetBranchAddress("recolep_sel_ismvasel",&_recolep_sel_ismvasel);

    tree->SetBranchAddress("recotauh_sel_isGenMatched",&_recotauh_sel_isGenMatched);

    tree->SetBranchAddress("category",&_category);



    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    //New branches
    float _triggerSF_weight_v2;
    float _triggerSF_weight_v2_up;
    float _triggerSF_weight_v2_down;
    
    float _leptonSF_ttH_weight_v2;
    float _tauSF_weight;

    tree_new->Branch("triggerSF_weight_v2",&_triggerSF_weight_v2,"triggerSF_weight_v2/F");
    tree_new->Branch("triggerSF_weight_v2_up",&_triggerSF_weight_v2_up,"triggerSF_weight_v2_up/F");
    tree_new->Branch("triggerSF_weight_v2_down",&_triggerSF_weight_v2_down,"triggerSF_weight_v2_down/F");

    tree_new->Branch("leptonSF_ttH_weight_v2",&_leptonSF_ttH_weight_v2,"leptonSF_ttH_weight_v2/F");
    tree_new->Branch("tauSF_weight",&_tauSF_weight,"tauSF_weight/F");


  
    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _recolep_sel_pdg = 0;
      _recolep_sel_pt = 0;
      _recolep_sel_eta = 0;
      _recolep_sel_ismvasel = 0;

      _recotauh_sel_isGenMatched = 0;   

      _category=0;

      _triggerSF_weight_v2 = 1;
      _triggerSF_weight_v2_up = 1;
      _triggerSF_weight_v2_down = 1;
      
      _leptonSF_ttH_weight_v2 = 1;
      _tauSF_weight = 1;

      tree->GetEntry(i);
      
      if(_category==20 || _category==50){
      
	_triggerSF_weight_v2 = triggerSF_ttH_1l((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0]);
	_triggerSF_weight_v2_up = triggerSF_ttH_1l((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0], +1.);
	_triggerSF_weight_v2_down = triggerSF_ttH_1l((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0], -1.);
	
	if((*_recolep_sel_ismvasel)[0])
	  _leptonSF_ttH_weight_v2 = leptonSF_ttH((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3);
	else
	  _leptonSF_ttH_weight_v2 = _get_recoToLoose_leptonSF_ttH((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],3);
	
	_tauSF_weight = (1-0.1*(*_recotauh_sel_isGenMatched)[0])*(1-0.1*(*_recotauh_sel_isGenMatched)[1]);
	
      }


      else if(_category==11 || _category==41){

	if((*_recolep_sel_ismvasel)[0])
	  _leptonSF_ttH_weight_v2 *= leptonSF_ttH((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2);
	else
	  _leptonSF_ttH_weight_v2 *= _get_recoToLoose_leptonSF_ttH((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2);

	if((*_recolep_sel_ismvasel)[1])
	  _leptonSF_ttH_weight_v2 *= leptonSF_ttH((*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2);
	else
	  _leptonSF_ttH_weight_v2 *= _get_recoToLoose_leptonSF_ttH((*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2);
		
	_tauSF_weight = (1-0.1*(*_recotauh_sel_isGenMatched)[0]);

      }


      else if(_category==16 || _category==46){

	if((*_recolep_sel_ismvasel)[0])
	  _leptonSF_ttH_weight_v2 *= leptonSF_ttH((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2);
	else
	  _leptonSF_ttH_weight_v2 *= _get_recoToLoose_leptonSF_ttH((*_recolep_sel_pdg)[0],(*_recolep_sel_pt)[0],(*_recolep_sel_eta)[0],2);
	

	if((*_recolep_sel_ismvasel)[1])
	  _leptonSF_ttH_weight_v2 *= leptonSF_ttH((*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2);
	else
	  _leptonSF_ttH_weight_v2 *= _get_recoToLoose_leptonSF_ttH((*_recolep_sel_pdg)[1],(*_recolep_sel_pt)[1],(*_recolep_sel_eta)[1],2);


	if((*_recolep_sel_ismvasel)[2])
	  _leptonSF_ttH_weight_v2 *= leptonSF_ttH((*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],2);
	else
	  _leptonSF_ttH_weight_v2 *= _get_recoToLoose_leptonSF_ttH((*_recolep_sel_pdg)[2],(*_recolep_sel_pt)[2],(*_recolep_sel_eta)[2],2);

	_tauSF_weight = (1-0.1*(*_recotauh_sel_isGenMatched)[0]);

      }

      tree_new->Fill();
      
    }
    
    f_new->cd();
    
    tree_new->Write();
    
  }



  f_new->Close();


  return;

}
     
    






void test_2l(){

  vector<TString> treename;
  treename.push_back("HTauTauTree_2lSS");
  treename.push_back("HTauTauTree_2lSS_lepMVA_CR");

  /*add_syst_2ltrigSF("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape.root",
		    "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_trig2l.root",
		    treename);


  add_syst_2ltrigSF("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_bTagSF_CSVshape.root",
		    "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_bTagSF_CSVshape_trig2l.root",
		    treename);

  add_syst_2ltrigSF("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_bTagSF_CSVshape.root",
		    "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_bTagSF_CSVshape_trig2l.root",
		    treename);

  add_syst_2ltrigSF("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bTagSF_CSVshape.root",
		    "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bTagSF_CSVshape_trig2l.root",
		    treename);*/


  add_syst_2ltrigSF("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split_bTagSF_CSVshape.root",
		    "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split_bTagSF_CSVshape_trig2l.root",
		    treename);

 


}




void test_1l(){

  vector<TString> treename;
  treename.push_back("HTauTauTree_1l_2tau");

  add_correct_1lSF("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_PU.root",
		   "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_PU_trig1l.root",		    
		    treename);


  /*add_correct_1lSF("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_bTagSF_CSVshape_PU.root",
		    "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_bTagSF_CSVshape_PU_trig1l.root",
		    treename);

  add_correct_1lSF("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_bTagSF_CSVshape_PU.root",
		    "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_bTagSF_CSVshape_PU_trig1l.root",
		    treename);

  add_correct_1lSF("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bTagSF_CSVshape_PU.root",
		    "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bTagSF_CSVshape_PU_trig1l.root",
		    treename);*/



}








void test(){

  vector<TString> treename;
  treename.push_back("HTauTauTree_1l_2tau");
  treename.push_back("HTauTauTree_1l_2tau_fake_CR");
  treename.push_back("HTauTauTree_2lSS");
  treename.push_back("HTauTauTree_2lSS_lepMVA_CR");
  treename.push_back("HTauTauTree_3l");
  treename.push_back("HTauTauTree_3l_lepMVA_CR");

  TString filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU_lepSF.root";
  
  add_correct_SF(filein,
		 fileout,		    
		 treename);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_bTagSF_CSVshape_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_bTagSF_CSVshape_PU_lepSF.root";

  add_correct_SF(filein,
		 fileout,		    
		 treename);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bTagSF_CSVshape_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bTagSF_CSVshape_PU_lepSF.root";

  add_correct_SF(filein,
		 fileout,		    
		 treename);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_bTagSF_CSVshape_PU_lepSF.root";

  add_correct_SF(filein,
		 fileout,		    
		 treename);



}






