#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>


void add_low_mass_veto(TString filein, TString fileout, vector<TString> treename){


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

    vector<float>* _recomu_e;
    vector<float>* _recomu_px;
    vector<float>* _recomu_py;
    vector<float>* _recomu_pz;

    vector<float>* _recoele_e;
    vector<float>* _recoele_px;
    vector<float>* _recoele_py;
    vector<float>* _recoele_pz;
    
    tree->SetBranchAddress("recomu_px",&_recomu_px);
    tree->SetBranchAddress("recomu_py",&_recomu_py);
    tree->SetBranchAddress("recomu_pz",&_recomu_pz);
    tree->SetBranchAddress("recomu_e",&_recomu_e);

    tree->SetBranchAddress("recoele_px",&_recoele_px);
    tree->SetBranchAddress("recoele_py",&_recoele_py);
    tree->SetBranchAddress("recoele_pz",&_recoele_pz);
    tree->SetBranchAddress("recoele_e",&_recoele_e);


    TTree* tree_new=tree->GetTree()->CloneTree(0);

    bool _low_mass_lep;
    tree_new->Branch("low_mass_lep",&_low_mass_lep,"low_mass_lep/O");

    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _low_mass_lep = 0;

      _recomu_e = 0;
      _recomu_px = 0;
      _recomu_py = 0;
      _recomu_pz = 0;
       
      _recoele_e = 0;
      _recoele_px = 0;
      _recoele_py = 0;
      _recoele_pz = 0;

      tree->GetEntry(i);

      vector<TLorentzVector> loose_leptons;
      
      for(unsigned int i_mu=0; i_mu<(*_recomu_e).size(); i_mu++){
	TLorentzVector mu((*_recomu_px)[i_mu], (*_recomu_py)[i_mu], (*_recomu_pz)[i_mu], (*_recomu_e)[i_mu]);
	loose_leptons.push_back(mu);
      }
      
      for(unsigned int i_ele=0; i_ele<(*_recoele_e).size(); i_ele++){
	TLorentzVector ele((*_recoele_px)[i_ele], (*_recoele_py)[i_ele], (*_recoele_pz)[i_ele], (*_recoele_e)[i_ele]);
	loose_leptons.push_back(ele);
      }
      
      for(unsigned int i_lep=0; i_lep<loose_leptons.size(); i_lep++){
	TLorentzVector lep1 = loose_leptons[i_lep];
	for(unsigned int i_lep2=i_lep+1; i_lep2<loose_leptons.size(); i_lep2++){
	  TLorentzVector lep2 = loose_leptons[i_lep2];
	  if((lep1+lep2).M()<12){
	    //lep1.Print();
	    //lep2.Print();
	    _low_mass_lep=true;
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




void test_lowmass(){

  vector<TString> treename;
  treename.push_back("HTauTauTree_1l_2tau");
  treename.push_back("HTauTauTree_1l_2tau_fake_CR");

  TString filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_ttHJet_Hnonbb_split_BDT_1l2tau_btagSF_trig_lepTauSF_new.root";  
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_ttHJet_Hnonbb_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto.root";  

  add_low_mass_veto(filein,fileout,treename);
  

}
