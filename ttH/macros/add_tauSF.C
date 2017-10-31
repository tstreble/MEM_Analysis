#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TF1.h>




using namespace std;



void add_tauSF(TString filein, TString fileout, vector<TString> treename, bool isMC){


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
    vector<float> *_recotauh_sel_pt;
    vector<float> *_recotauh_sel_eta;
    vector<bool> *_recotauh_sel_isGenMatched;
    
    tree->SetBranchAddress("category",&_category);
    tree->SetBranchAddress("recotauh_sel_pt",&_recotauh_sel_pt);
    tree->SetBranchAddress("recotauh_sel_eta",&_recotauh_sel_eta);
    tree->SetBranchAddress("recotauh_sel_isGenMatched",&_recotauh_sel_isGenMatched);


    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    //New branches
    float _tauSF_weight_v3;
    float _tauSF_weight_tauNormUp_v3;
    float _tauSF_weight_tauNormDown_v3;
    float _tauSF_weight_tauShapeUp_v3;
    float _tauSF_weight_tauShapeDown_v3;

    tree_new->Branch("tauSF_weight_v3",&_tauSF_weight_v3,"tauSF_weight_v3/F");
    tree_new->Branch("tauSF_weight_tauNormUp_v3",&_tauSF_weight_tauNormUp_v3,"tauSF_weight_tauNormUp_v3/F");
    tree_new->Branch("tauSF_weight_tauNormDown_v3",&_tauSF_weight_tauNormDown_v3,"tauSF_weight_tauNormDown_v3/F");
    tree_new->Branch("tauSF_weight_tauShapeUp_v3",&_tauSF_weight_tauShapeUp_v3,"tauSF_weight_tauShapeUp_v3/F");
    tree_new->Branch("tauSF_weight_tauShapeDown_v3",&_tauSF_weight_tauShapeDown_v3,"tauSF_weight_tauShapeDown_v3/F");   

    TFile* f_fakerate_tau = TFile::Open("fake_rate_weights/FR_tau_2016_M17.root");



    vector<TString> FR_tau_syst;
    FR_tau_syst.push_back("");
    FR_tau_syst.push_back("_par1Up");
    FR_tau_syst.push_back("_par1Down");
    FR_tau_syst.push_back("_par2Up");
    FR_tau_syst.push_back("_par2Down");

    vector<TF1*> f_dataMC_fakerate_tau_medium_barrel;
    vector<TF1*> f_dataMC_fakerate_tau_medium_endcaps;
    vector<TF1*> f_dataMC_fakerate_tau_tight_barrel;
    vector<TF1*> f_dataMC_fakerate_tau_tight_endcaps;

    for(unsigned int i=0;i<FR_tau_syst.size();i++){

      f_dataMC_fakerate_tau_medium_barrel.push_back( (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt" + FR_tau_syst[i]) );

  f_dataMC_fakerate_tau_medium_endcaps.push_back( (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaMedium/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt" + FR_tau_syst[i]) );

      f_dataMC_fakerate_tau_tight_barrel.push_back( (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaTight/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt" + FR_tau_syst[i]) );

      f_dataMC_fakerate_tau_tight_endcaps.push_back( (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaTight/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt" + FR_tau_syst[i]) );


    }

    f_fakerate_tau->Close();


    vector<float> _recotauh_sel_jetToTau_FR_byMedium_SF;
    vector<float> _recotauh_sel_jetToTau_FR_byTight_SF;
    vector<float> _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormUp;
    vector<float> _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormDown;
    vector<float> _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeUp;
    vector<float> _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeDown;

    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _category = 0;
      _recotauh_sel_pt = 0;
      _recotauh_sel_eta = 0;
      _recotauh_sel_isGenMatched = 0;

      _recotauh_sel_jetToTau_FR_byMedium_SF.clear();
      _recotauh_sel_jetToTau_FR_byTight_SF.clear();
      _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormUp.clear();
      _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormDown.clear();
      _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeUp.clear();
      _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeDown.clear();

      _tauSF_weight_v3 = 0;
      _tauSF_weight_tauNormUp_v3 = 0;
      _tauSF_weight_tauNormDown_v3 = 0;
      _tauSF_weight_tauShapeUp_v3 = 0;
      _tauSF_weight_tauShapeDown_v3 = 0;
      
      tree->GetEntry(i);



      for(unsigned int i_tau=0;i_tau<(*_recotauh_sel_pt).size();i_tau++){

	  
	  float jetToTau_FR_byMedium_SF = 0;
	  float jetToTau_FR_byTight_SF = 0;
	  float jetToTau_FR_byMedium_SF_tauNormUp = 0;
	  float jetToTau_FR_byMedium_SF_tauNormDown = 0;
	  float jetToTau_FR_byMedium_SF_tauShapeUp = 0;
	  float jetToTau_FR_byMedium_SF_tauShapeDown = 0;

	  float tau_pt = (*_recotauh_sel_pt)[i_tau];

	  if(fabs((*_recotauh_sel_eta)[i_tau])<1.479){

	    jetToTau_FR_byMedium_SF = f_dataMC_fakerate_tau_medium_barrel[0]->Eval(tau_pt);
	    jetToTau_FR_byTight_SF = f_dataMC_fakerate_tau_tight_barrel[0]->Eval(tau_pt); 
	    jetToTau_FR_byMedium_SF_tauNormUp = f_dataMC_fakerate_tau_medium_barrel[1]->Eval(tau_pt);
	    jetToTau_FR_byMedium_SF_tauNormDown = f_dataMC_fakerate_tau_medium_barrel[2]->Eval(tau_pt);
	    jetToTau_FR_byMedium_SF_tauShapeUp = f_dataMC_fakerate_tau_medium_barrel[3]->Eval(tau_pt);
	    jetToTau_FR_byMedium_SF_tauShapeDown = f_dataMC_fakerate_tau_medium_barrel[4]->Eval(tau_pt);	    	    

	  }

	  else{

	    jetToTau_FR_byMedium_SF = f_dataMC_fakerate_tau_medium_endcaps[0]->Eval(tau_pt);
	    jetToTau_FR_byTight_SF = f_dataMC_fakerate_tau_tight_endcaps[0]->Eval(tau_pt); 
	    jetToTau_FR_byMedium_SF_tauNormUp = f_dataMC_fakerate_tau_medium_endcaps[1]->Eval(tau_pt);
	    jetToTau_FR_byMedium_SF_tauNormDown = f_dataMC_fakerate_tau_medium_endcaps[2]->Eval(tau_pt);
	    jetToTau_FR_byMedium_SF_tauShapeUp = f_dataMC_fakerate_tau_medium_endcaps[3]->Eval(tau_pt);
	    jetToTau_FR_byMedium_SF_tauShapeDown = f_dataMC_fakerate_tau_medium_endcaps[4]->Eval(tau_pt);	    	    

	  }

	  _recotauh_sel_jetToTau_FR_byMedium_SF.push_back(jetToTau_FR_byMedium_SF);
	  _recotauh_sel_jetToTau_FR_byTight_SF.push_back(jetToTau_FR_byTight_SF);
	  _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormUp.push_back(jetToTau_FR_byMedium_SF_tauNormUp);
	  _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormDown.push_back(jetToTau_FR_byMedium_SF_tauNormDown);
	  _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeUp.push_back(jetToTau_FR_byMedium_SF_tauShapeUp);
	  _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeDown.push_back(jetToTau_FR_byMedium_SF_tauShapeDown);      

      }


      _tauSF_weight_v3 = 1;
      _tauSF_weight_tauNormUp_v3 = 1;
      _tauSF_weight_tauNormDown_v3 = 1;
      _tauSF_weight_tauShapeUp_v3 = 1;
      _tauSF_weight_tauShapeDown_v3 = 1;


      
      if(_category==20 || _category==50){	


	if(isMC){
	  if((*_recotauh_sel_isGenMatched)[0])
	    _tauSF_weight_v3 *= 0.95;
	  else
            _tauSF_weight_v3 *= _recotauh_sel_jetToTau_FR_byTight_SF[0];

	  if((*_recotauh_sel_isGenMatched)[1])
            _tauSF_weight_v3 *= 0.95;
	  else
	    _tauSF_weight_v3 *= _recotauh_sel_jetToTau_FR_byTight_SF[1];
	}

	_tauSF_weight_tauNormUp_v3 = _tauSF_weight_v3;
	_tauSF_weight_tauNormDown_v3 = _tauSF_weight_v3;
	_tauSF_weight_tauShapeUp_v3 = _tauSF_weight_v3;
	_tauSF_weight_tauShapeDown_v3 = _tauSF_weight_v3;


      }


      
      else if(_category==11 || _category==41 || _category==16 || _category==46){

	if(isMC){
	  if((*_recotauh_sel_isGenMatched)[0])
	    _tauSF_weight_v3 *= 0.95;
	  else{	    
	    _tauSF_weight_v3 *= _recotauh_sel_jetToTau_FR_byMedium_SF[0];
	    _tauSF_weight_tauNormUp_v3 *= _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormUp[0];
	    _tauSF_weight_tauNormDown_v3 *= _recotauh_sel_jetToTau_FR_byMedium_SF_tauNormDown[0];
	    _tauSF_weight_tauShapeUp_v3 *= _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeUp[0];
	    _tauSF_weight_tauShapeDown_v3 *= _recotauh_sel_jetToTau_FR_byMedium_SF_tauShapeDown[0];
	  }
        }
	
      }	
      
      tree_new->Fill();

    }

   
    f_new->cd();
    
    tree_new->Write();


  }

  f_new->Close();


  return;

}






/*void test(){

  TString filein="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/syncNtuple_ttH_tautau_split_2lSS_MEM_170301_btagSF_trig_lepTauSF_new.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/syncNtuple_ttH_tautau_split_2lSS_MEM_170301_btagSF_trig_lepTauSF_new_tauSF3.root";
  vector<TString> tree;
  tree.push_back("T");
  tree.push_back("HTauTauTree_1l_2tau");
  tree.push_back("HTauTauTree_1l_2tau_fake_CR");
  tree.push_back("HTauTauTree_2lSS");
  tree.push_back("HTauTauTree_2lSS_lepMVA_CR");
  tree.push_back("HTauTauTree_2lOS_CR");
  tree.push_back("HTauTauTree_3l");
  tree.push_back("HTauTauTree_3l_ttZ_CR");
  tree.push_back("HTauTauTree_3l_lepMVA_CR");


  add_tauSF(filein,fileout,tree,true);

  }*/
