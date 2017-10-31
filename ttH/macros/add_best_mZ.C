#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>


void add_best_mZ(TString filein, TString fileout, vector<TString> treename){



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

    vector<float>* _recolep_e;
    vector<float>* _recolep_px;
    vector<float>* _recolep_py;
    vector<float>* _recolep_pz;
    
    tree->SetBranchAddress("recolep_px",&_recolep_px);
    tree->SetBranchAddress("recolep_py",&_recolep_py);
    tree->SetBranchAddress("recolep_pz",&_recolep_pz);
    tree->SetBranchAddress("recolep_e",&_recolep_e);


    TTree* tree_new=tree->GetTree()->CloneTree(0);

    float _best_mZ;
    tree_new->Branch("best_mZ",&_best_mZ,"best_mZ/F");


    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _best_mZ = -10;

      _recolep_px = 0;
      _recolep_py = 0;
      _recolep_pz = 0;
      _recolep_e = 0;
      

       tree->GetEntry(i);

       

       for(unsigned int i_lep0=0;i_lep0<(*_recolep_px).size();i_lep0++){

	 TLorentzVector lep0((*_recolep_px)[i_lep0],(*_recolep_py)[i_lep0],(*_recolep_pz)[i_lep0],(*_recolep_e)[i_lep0]);
   
	 for(unsigned int i_lep1=0;i_lep1<(*_recolep_px).size();i_lep1++){
	   TLorentzVector lep1((*_recolep_px)[i_lep1],(*_recolep_py)[i_lep1],(*_recolep_pz)[i_lep1],(*_recolep_e)[i_lep1]);
      
	   float Mll =  (lep0+lep1).M();
	   if(_best_mZ<0 || fabs(Mll-91.2)<fabs(_best_mZ-91.2))
	     _best_mZ = Mll;	      

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





void test(){

  vector<TString> treename;
  treename.push_back("HTauTauTree_3l_ttZ_CR"); 

  TString filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_ttHJet_Hnonbb_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_ttHJet_Hnonbb_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);
  
  filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);
  
  filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttG_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttG_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_ZZ_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_ZZ_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_tZq_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_tZq_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_TTTT_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_TTTT_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WWW_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WWW_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WWZ_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WWZ_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WZZ_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WZZ_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_ZZZ_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_ZZZ_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);

  filein = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WpWp_split_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
  fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WpWp_split_bestMZ.root";
  add_best_mZ(filein, fileout, treename);
  
  treename.push_back("HTauTauTree_3l_ttZ_lepMVA_CR"); 

  vector<TString> dataset;
  dataset.push_back("DoubleEG");
  dataset.push_back("MuonEG");
  dataset.push_back("DoubleMu");
  dataset.push_back("SingleMu");
  dataset.push_back("SingleEle");

  vector<TString> era;
  era.push_back("2016B");
  era.push_back("2016C");
  era.push_back("2016D");
  era.push_back("2016E");
  era.push_back("2016F");
  era.push_back("2016G");
  era.push_back("2016Hv2");
  era.push_back("2016Hv3");
  
  for(unsigned int i=0; i<dataset.size();i++){
    for(unsigned int j=0; j<era.size();j++){
      
      TString filein="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_"+dataset[i]+"_"+era[j]+"_split_trig_weight_new_BDT_1l2tau.root";
      TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_"+dataset[i]+"_"+era[j]+"_split_bestMZ.root";
      add_best_mZ(filein,fileout,treename);

    }
  }




}
