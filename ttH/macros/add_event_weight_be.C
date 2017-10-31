#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TF1.h>
#include <TH2.h>


using namespace std;




void add_event_weight_be(TString filein, TString fileout, vector<TString> treename, bool isMC){


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
    vector<float> *_recolep_sel_conept;
    vector<float> *_recolep_sel_pt;
    vector<float> *_recolep_sel_eta;
    vector<bool> *_recolep_sel_ismvasel;
    vector<int> *_recolep_sel_charge;    


    tree->SetBranchAddress("category",&_category);
    
    tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
    tree->SetBranchAddress("recolep_sel_conept",&_recolep_sel_conept);
    tree->SetBranchAddress("recolep_sel_pt",&_recolep_sel_pt);
    tree->SetBranchAddress("recolep_sel_eta",&_recolep_sel_eta);
    tree->SetBranchAddress("recolep_sel_ismvasel",&_recolep_sel_ismvasel);
    tree->SetBranchAddress("recolep_sel_charge",&_recolep_sel_charge);


    TTree* tree_new=tree->GetTree()->CloneTree(0);
    
    //New branches
    float _event_weight_ttH_ele_be1_v2;
    float _event_weight_ttH_ele_be2_v2;
    float _event_weight_ttH_mu_be1_v2;
    float _event_weight_ttH_mu_be2_v2;

    tree_new->Branch("event_weight_ttH_ele_be1_v2",&_event_weight_ttH_ele_be1_v2,"event_weight_ttH_ele_be1_v2/F");
    tree_new->Branch("event_weight_ttH_ele_be2_v2",&_event_weight_ttH_ele_be2_v2,"event_weight_ttH_ele_be2_v2/F");
    tree_new->Branch("event_weight_ttH_mu_be1_v2",&_event_weight_ttH_mu_be1_v2,"event_weight_ttH_mu_be1_v2/F");
    tree_new->Branch("event_weight_ttH_mu_be2_v2",&_event_weight_ttH_mu_be2_v2,"event_weight_ttH_mu_be2_v2/F");

 
    TFile* f_fakerate = TFile::Open("fake_rate_weights/FR_data_ttH_mva_M17b.root");
    TH2F* h_fakerate_mu = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb");
    h_fakerate_mu->SetDirectory(0);
    TH2F* h_fakerate_el = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb");
    h_fakerate_el->SetDirectory(0);
    
 
    TH2F* h_fakerate_mu_data_b1 = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb_b1");
    h_fakerate_mu_data_b1->SetDirectory(0);
    TH2F* h_fakerate_el_data_b1 = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb_b1");
    h_fakerate_el_data_b1->SetDirectory(0);

    TH2F* h_fakerate_mu_data_b2 = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb_b2");
    h_fakerate_mu_data_b2->SetDirectory(0);
    TH2F* h_fakerate_el_data_b2 = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb_b2");
    h_fakerate_el_data_b2->SetDirectory(0);

    TH2F* h_fakerate_mu_data_ec1 = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb_ec1");
    h_fakerate_mu_data_ec1->SetDirectory(0);
    TH2F* h_fakerate_el_data_ec1 = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb_ec1");
    h_fakerate_el_data_ec1->SetDirectory(0);

    TH2F* h_fakerate_mu_data_ec2 = (TH2F*)f_fakerate->Get("FR_mva075_mu_data_comb_ec2");
    h_fakerate_mu_data_ec2->SetDirectory(0);
    TH2F* h_fakerate_el_data_ec2 = (TH2F*)f_fakerate->Get("FR_mva075_el_data_comb_ec2");
    h_fakerate_el_data_ec2->SetDirectory(0);

    f_fakerate->Close();
    

    vector<float> _recolep_sel_fakerate_v2;
    vector<float> _recolep_sel_fakerate_be1_v2;
    vector<float> _recolep_sel_fakerate_be2_v2;
    


    for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _category = 0;

      _recolep_sel_pdg = 0;
      _recolep_sel_ismvasel = 0;
      _recolep_sel_conept = 0;
      _recolep_sel_pt = 0;
      _recolep_sel_eta = 0;
      _recolep_sel_charge = 0;

      _recolep_sel_fakerate_v2.clear();
      _recolep_sel_fakerate_be1_v2.clear();
      _recolep_sel_fakerate_be2_v2.clear();

      _event_weight_ttH_ele_be1_v2 = 0;
      _event_weight_ttH_ele_be2_v2 = 0;
      _event_weight_ttH_mu_be1_v2 = 0;
      _event_weight_ttH_mu_be2_v2 = 0;

      
      tree->GetEntry(i);


      for(unsigned int i_lep=0;i_lep<(*_recolep_sel_pdg).size();i_lep++){

	float FR = 0;
	float conept = (*_recolep_sel_conept)[i_lep];

	if(abs((*_recolep_sel_pdg)[i_lep])==11){

	  int bin_FR = h_fakerate_el->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	  FR = h_fakerate_el->GetBinContent(bin_FR);
	  _recolep_sel_fakerate_v2.push_back(FR);

	  if(abs((*_recolep_sel_eta)[i_lep])<1.479){
	    bin_FR = h_fakerate_el_data_b1->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	    FR = h_fakerate_el_data_b1->GetBinContent(bin_FR);
	    _recolep_sel_fakerate_be1_v2.push_back(FR);

	    bin_FR = h_fakerate_el_data_b2->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	    FR = h_fakerate_el_data_b2->GetBinContent(bin_FR);
	    _recolep_sel_fakerate_be2_v2.push_back(FR);

	  }
	  else{
	    bin_FR = h_fakerate_el_data_ec2->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	    FR = h_fakerate_el_data_ec2->GetBinContent(bin_FR);
	    _recolep_sel_fakerate_be1_v2.push_back(FR);

	    bin_FR = h_fakerate_el_data_ec1->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	    FR = h_fakerate_el_data_ec1->GetBinContent(bin_FR);
	    _recolep_sel_fakerate_be2_v2.push_back(FR);
	  }


	}

	else if(abs((*_recolep_sel_pdg)[i_lep])==13){

	  int bin_FR = h_fakerate_mu->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	  FR = h_fakerate_mu->GetBinContent(bin_FR);
	  _recolep_sel_fakerate_v2.push_back(FR);

	  if(abs((*_recolep_sel_eta)[i_lep])<1.2){
	    bin_FR = h_fakerate_mu_data_b1->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	    FR = h_fakerate_mu_data_b1->GetBinContent(bin_FR);
	    _recolep_sel_fakerate_be1_v2.push_back(FR);

	    bin_FR = h_fakerate_mu_data_b2->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	    FR = h_fakerate_mu_data_b2->GetBinContent(bin_FR);
	    _recolep_sel_fakerate_be2_v2.push_back(FR);

	  }
	  else{
	    bin_FR = h_fakerate_mu_data_ec2->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	    FR = h_fakerate_mu_data_ec2->GetBinContent(bin_FR);
	    _recolep_sel_fakerate_be1_v2.push_back(FR);

	    bin_FR = h_fakerate_mu_data_ec1->FindBin(min(conept,float(99.)), abs((*_recolep_sel_eta)[i_lep]));
	    FR = h_fakerate_mu_data_ec1->GetBinContent(bin_FR);
	    _recolep_sel_fakerate_be2_v2.push_back(FR);
	  }


	}


      }


      _event_weight_ttH_ele_be1_v2 = 1;
      _event_weight_ttH_ele_be2_v2 = 1;
      _event_weight_ttH_mu_be1_v2 = 1;
      _event_weight_ttH_mu_be2_v2 = 1;

      
      if(_category==11 || _category==41 || _category==16 || _category==46){
       
	int n_fake = 0;

	for(unsigned int i_lep=0;i_lep<_recolep_sel_fakerate_v2.size();i_lep++){

	  if(!(*_recolep_sel_ismvasel)[i_lep]){
	  
	    float lep_weight = _recolep_sel_fakerate_v2[i_lep]/(1-_recolep_sel_fakerate_v2[i_lep]);

	  
	    if(abs((*_recolep_sel_pdg)[i_lep])==11){

	      _event_weight_ttH_ele_be1_v2 *= _recolep_sel_fakerate_be1_v2[i_lep]/(1-_recolep_sel_fakerate_be1_v2[i_lep]);
	      _event_weight_ttH_ele_be2_v2 *= _recolep_sel_fakerate_be2_v2[i_lep]/(1-_recolep_sel_fakerate_be2_v2[i_lep]);        

	      _event_weight_ttH_mu_be1_v2 *= lep_weight;
	      _event_weight_ttH_mu_be2_v2 *= lep_weight;

	    }
	    
	    else if(abs((*_recolep_sel_pdg)[i_lep])==13){

	      _event_weight_ttH_ele_be1_v2 *= lep_weight;
	      _event_weight_ttH_ele_be2_v2 *= lep_weight;
 
	      _event_weight_ttH_mu_be1_v2 *= _recolep_sel_fakerate_be1_v2[i_lep]/(1-_recolep_sel_fakerate_be1_v2[i_lep]);
	      _event_weight_ttH_mu_be2_v2 *= _recolep_sel_fakerate_be2_v2[i_lep]/(1-_recolep_sel_fakerate_be2_v2[i_lep]);         

	    }
	    
	    n_fake++;
	  }
	  
	}
	

	if(n_fake>0 && n_fake%2==0){
	 
          _event_weight_ttH_ele_be1_v2 *= -1;
          _event_weight_ttH_ele_be2_v2 *= -1;   
          _event_weight_ttH_mu_be1_v2 *= -1;
          _event_weight_ttH_mu_be2_v2 *= -1;  
	  
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







void full_proc_MEM_be(){


    vector<TString> dataset;
    dataset.push_back("DoubleEG_2016B");
    dataset.push_back("DoubleEG_2016C");
    dataset.push_back("DoubleEG_2016D");
    dataset.push_back("DoubleEG_2016E");
    dataset.push_back("DoubleEG_2016F");
    dataset.push_back("DoubleEG_2016G");
    dataset.push_back("DoubleEG_2016Hv2");
    dataset.push_back("DoubleEG_2016Hv3");
    dataset.push_back("DoubleMu_2016B");
    dataset.push_back("DoubleMu_2016C");
    dataset.push_back("DoubleMu_2016D");
    dataset.push_back("DoubleMu_2016E");
    dataset.push_back("DoubleMu_2016F");
    dataset.push_back("DoubleMu_2016G");
    dataset.push_back("DoubleMu_2016Hv2");
    dataset.push_back("DoubleMu_2016Hv3");
    dataset.push_back("MuonEG_2016B");
    dataset.push_back("MuonEG_2016C");
    dataset.push_back("MuonEG_2016D");
    dataset.push_back("MuonEG_2016E");
    dataset.push_back("MuonEG_2016F");
    dataset.push_back("MuonEG_2016G");
    dataset.push_back("MuonEG_2016Hv2");
    dataset.push_back("MuonEG_2016Hv3");
    dataset.push_back("SingleEle_2016B");
    dataset.push_back("SingleEle_2016C");
    dataset.push_back("SingleEle_2016D");
    dataset.push_back("SingleEle_2016E");
    dataset.push_back("SingleEle_2016F");
    dataset.push_back("SingleEle_2016G");
    dataset.push_back("SingleEle_2016Hv2");
    dataset.push_back("SingleEle_2016Hv3");
    dataset.push_back("SingleMu_2016B");
    dataset.push_back("SingleMu_2016C");
    dataset.push_back("SingleMu_2016D");
    dataset.push_back("SingleMu_2016E");
    dataset.push_back("SingleMu_2016F");
    dataset.push_back("SingleMu_2016G");
    dataset.push_back("SingleMu_2016Hv2");
    dataset.push_back("SingleMu_2016Hv3");

    vector<TString> type;
    //type.push_back("2lSS");
    type.push_back("2lSS_lepMVA_CR");
    //type.push_back("2lOS_CR");

    vector<TString> treename;
    treename.push_back("T");

    for(unsigned int i=0;i<dataset.size();i++){
      for(unsigned int j=0;j<type.size();j++){
	if(dataset[i].Contains("2016Hv3") && type[j]=="2lSS") continue;
	
	TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/"+dataset[i]+"_split_"+type[j]+"_MEM_NBadMu_trig_weight_new.root";
	TString fileout = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/"+dataset[i]+"_split_"+type[j]+"_MEM_NBadMu_trig_weight_new_be.root";
	add_event_weight_be(file,fileout,treename,false);
      }
    }


    type.clear();
    type.push_back("2lSS_lepMVA_CR");

  for(unsigned int i=0;i<type.size();i++){

    TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/ttHJet_split_"+type[i]+"_MEM";
    add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttG_split_"+type[i]+"_MEM";
  add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);


    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_"+type[i]+"_MEM";
  add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttW_split_"+type[i]+"_MEM";
  add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/WZ_split_"+type[i]+"_MEM";
  add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/WZ_powheg_split_"+type[i]+"_MEM";
  add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/ttWW_split_"+type[i]+"_MEM";
  add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/THQ_split_"+type[i]+"_MEM";
  add_event_weight_be(file+"_btagSF_trig_lepTauSF_new_MCtHq.root",
			file+"_btagSF_trig_lepTauSF_new_MCtHq_be.root",
			treename,true); 

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/THW_split_"+type[i]+"_MEM";
    add_event_weight_be(file+"_btagSF_trig_lepTauSF_new_MCtHq.root",
			file+"_btagSF_trig_lepTauSF_new_MCtHq_be.root",
			treename,true); 

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_lowmass_split_"+type[i]+"_MEM";
 add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/ZZ_split_"+type[i]+"_MEM";
 add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/TTTT_split_"+type[i]+"_MEM";
 add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/tZq_split_"+type[i]+"_MEM";
 add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WWW_split_"+type[i]+"_MEM";
 add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WWZ_split_"+type[i]+"_MEM";
 add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WZZ_split_"+type[i]+"_MEM";
 add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/ZZZ_split_"+type[i]+"_MEM";
 add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WpWp_split_"+type[i]+"_MEM";
 add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			file+"_btagSF_trig_lepTauSF_new_be.root",
			treename,true);


  }


}


