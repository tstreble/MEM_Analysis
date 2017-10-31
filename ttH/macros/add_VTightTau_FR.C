#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <iostream>
#include <TLorentzVector.h>
#include <TList.h>
#include <TGraphAsymmErrors.h>
#include <TF1.h>


using namespace std;





float fakerate_from_TGraph(TGraphAsymmErrors* graph, float pt){

  int n = graph->GetN();

  double x, y;
  graph->GetPoint(0,x,y);
  if(pt<x)
    return y;

  graph->GetPoint(n-1,x,y);
  if(pt>x)
    return y;
  

  for(int i=0; i<n;i++){

    graph->GetPoint(i,x,y);
    double err_low_x = graph->GetErrorXlow(i);
    double err_high_x = graph->GetErrorXhigh(i);

    if( (x-err_low_x) < pt && pt < (x+err_high_x) )
      return y;

  }

  return -1.;

}






void add_VTightTau_FR_2lSS(TString filein, TString fileout, bool Data=false){



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
  vector<float>* _recotauh_sel_px;
  vector<float>* _recotauh_sel_py;
  vector<float>* _recotauh_sel_pz;
  vector<float>* _recotauh_sel_e;

  vector<int>* _PDGIdDaughters;
  vector<float>* _daughters_px;
  vector<float>* _daughters_py;
  vector<float>* _daughters_pz;
  vector<float>* _daughters_e;
  vector<Long64_t> *_tauID;


  tree->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
  tree->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
  tree->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
  tree->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);

  tree->SetBranchAddress("PDGIdDaughters",&_PDGIdDaughters);
  tree->SetBranchAddress("daughters_px",&_daughters_px);
  tree->SetBranchAddress("daughters_py",&_daughters_py);
  tree->SetBranchAddress("daughters_pz",&_daughters_pz);
  tree->SetBranchAddress("daughters_e",&_daughters_e);
  tree->SetBranchAddress("tauID",&_tauID);


  TTree* HTauTauTree_2lSS=tree->GetTree()->CloneTree(0);
  TTree* HTauTauTree_2lSS_lepMVA_CR_1=tree->GetTree()->CloneTree(0);
  HTauTauTree_2lSS_lepMVA_CR_1->SetNameTitle("HTauTauTree_2lSS_lepMVA_CR_1","HTauTauTree_2lSS_lepMVA_CR_1");


  //New branches
  vector<int> _recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<float> _recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT;

  float _event_weight_ttH_v2;
  int _category_v2;

  HTauTauTree_2lSS->Branch("recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  HTauTauTree_2lSS->Branch("recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  HTauTauTree_2lSS->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  HTauTauTree_2lSS->Branch("category_v2",&_category_v2,"category_v2/I");

  HTauTauTree_2lSS_lepMVA_CR_1->Branch("recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  HTauTauTree_2lSS_lepMVA_CR_1->Branch("recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  HTauTauTree_2lSS_lepMVA_CR_1->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  HTauTauTree_2lSS_lepMVA_CR_1->Branch("category_v2",&_category_v2,"category_v2/I");


  TFile* f_fakerate_tau = TFile::Open("fake_rate_weights/FR_tau_2016.root");
  TGraphAsymmErrors* gr_fakerate_tau_Vtight_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVTight/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");
  TGraphAsymmErrors* gr_fakerate_tau_Vtight_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVTight/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");
  TF1* f_dataMC_fakerate_tau_Vtight_barrel = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVTight/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt");
  TF1* f_dataMC_fakerate_tau_Vtight_endcaps = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVTight/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt");  

  
  for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _recotauh_sel_px = 0;
      _recotauh_sel_py = 0;
      _recotauh_sel_pz = 0;
      _recotauh_sel_e = 0;
      
      _PDGIdDaughters = 0;
      _daughters_px = 0;
      _daughters_py = 0;
      _daughters_pz = 0;
      _daughters_e = 0;
      _tauID = 0;

      _recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
      _recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
  
      _event_weight_ttH_v2 = 0;
      _category_v2 = 0;

      tree->GetEntry(i);

      
      for(unsigned int i_tau=0; i_tau<(*_recotauh_sel_px).size(); i_tau++){

	TLorentzVector tau((*_recotauh_sel_px)[i_tau],(*_recotauh_sel_py)[i_tau],(*_recotauh_sel_pz)[i_tau],(*_recotauh_sel_e)[i_tau]);

	for(unsigned int i_dau=0; i_dau<(*_daughters_px).size(); i_dau++){
	  
	  if(abs((*_PDGIdDaughters)[i_dau])!=15) continue;

	  TLorentzVector dau((*_daughters_px)[i_dau],(*_daughters_py)[i_dau],(*_daughters_pz)[i_dau],(*_daughters_e)[i_dau]);
	  float dR=dau.DeltaR(tau);
	 
	  if(dR<0.01){
	    _recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT.push_back(((*_tauID)[i_dau]>>29)&1);
	    
	    float fakerate_Vtight = 0;
	    if(fabs(tau.Eta())<1.479){
	      fakerate_Vtight = fakerate_from_TGraph(gr_fakerate_tau_Vtight_barrel,tau.Pt());
	      fakerate_Vtight *= f_dataMC_fakerate_tau_Vtight_barrel->Eval(tau.Pt());
	    }
	    else{
	      fakerate_Vtight = fakerate_from_TGraph(gr_fakerate_tau_Vtight_endcaps,tau.Pt());
	      fakerate_Vtight *= f_dataMC_fakerate_tau_Vtight_endcaps->Eval(tau.Pt());
	    }

	    _recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT.push_back(fakerate_Vtight);
	    break;

	  }

	}

      }


      if(_recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0]){
	_event_weight_ttH_v2 = 1;
	_category_v2 = 11;
	HTauTauTree_2lSS->Fill();
      }
      else{
	float weight_tau = (_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0]);
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

  tree2->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
  tree2->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
  tree2->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
  tree2->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);

  tree2->SetBranchAddress("PDGIdDaughters",&_PDGIdDaughters);
  tree2->SetBranchAddress("daughters_px",&_daughters_px);
  tree2->SetBranchAddress("daughters_py",&_daughters_py);
  tree2->SetBranchAddress("daughters_pz",&_daughters_pz);
  tree2->SetBranchAddress("daughters_e",&_daughters_e);
  tree2->SetBranchAddress("tauID",&_tauID);

  tree2->SetBranchAddress("recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree2->SetBranchAddress("category",&_category);

  f_new->cd();
  TTree* HTauTauTree_2lSS_lepMVA_CR_2=tree2->GetTree()->CloneTree(0);
  HTauTauTree_2lSS_lepMVA_CR_2->SetNameTitle("HTauTauTree_2lSS_lepMVA_CR_2","HTauTauTree_2lSS_lepMVA_CR_2");

  HTauTauTree_2lSS_lepMVA_CR_2->Branch("recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  HTauTauTree_2lSS_lepMVA_CR_2->Branch("recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  HTauTauTree_2lSS_lepMVA_CR_2->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  HTauTauTree_2lSS_lepMVA_CR_2->Branch("category_v2",&_category_v2,"category_v2/I");

  
  for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _recotauh_sel_px = 0;
      _recotauh_sel_py = 0;
      _recotauh_sel_pz = 0;
      _recotauh_sel_e = 0;
      
      _PDGIdDaughters = 0;
      _daughters_px = 0;
      _daughters_py = 0;
      _daughters_pz = 0;
      _daughters_e = 0;
      _tauID = 0;

      _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _event_weight_ttH = 0; 
      _category = 0;

      _recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
      _recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
  
      _event_weight_ttH_v2 = 0;
      _category_v2 = 0;

      tree2->GetEntry(i);

      if(_category!=41) continue;
      _category_v2 = 41;
      

      for(unsigned int i_tau=0; i_tau<(*_recotauh_sel_px).size(); i_tau++){

	TLorentzVector tau((*_recotauh_sel_px)[i_tau],(*_recotauh_sel_py)[i_tau],(*_recotauh_sel_pz)[i_tau],(*_recotauh_sel_e)[i_tau]);

	for(unsigned int i_dau=0; i_dau<(*_daughters_px).size(); i_dau++){
	  
	  if(abs((*_PDGIdDaughters)[i_dau])!=15) continue;

	  TLorentzVector dau((*_daughters_px)[i_dau],(*_daughters_py)[i_dau],(*_daughters_pz)[i_dau],(*_daughters_e)[i_dau]);
	  float dR=dau.DeltaR(tau);
	 
	  if(dR<0.01){
	    _recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT.push_back(((*_tauID)[i_dau]>>29)&1);
	    
	    float fakerate_Vtight = 0;
	    if(fabs(tau.Eta())<1.479){
	      fakerate_Vtight = fakerate_from_TGraph(gr_fakerate_tau_Vtight_barrel,tau.Pt());
	      fakerate_Vtight *= f_dataMC_fakerate_tau_Vtight_barrel->Eval(tau.Pt());
	    }
	    else{
	      fakerate_Vtight = fakerate_from_TGraph(gr_fakerate_tau_Vtight_endcaps,tau.Pt());
	      fakerate_Vtight *= f_dataMC_fakerate_tau_Vtight_endcaps->Eval(tau.Pt());
	    }

	    _recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT.push_back(fakerate_Vtight);
	    break;

	  }

	}

	}



      if(!(*_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]){

	float weight_tau_old = (*_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(*_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]);
      	float weight_tau_new = (_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0]);
	_event_weight_ttH_v2 = _event_weight_ttH * weight_tau_new / weight_tau_old;

      }

      else{

	if((_recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0])
	  _event_weight_ttH_v2 = _event_weight_ttH;
	else{
	  float weight_tau_new = (_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0]);
	  _event_weight_ttH_v2 = _event_weight_ttH * (-1.) * weight_tau_new;
	}

	}

      HTauTauTree_2lSS_lepMVA_CR_2->Fill();

  }


  f_new->cd();


  if(Data){
  TChain* tree3 = new TChain("HTauTauTree_2lOS_CR");
  tree3->Add(filein);

  nentries = tree3->GetEntries();
  cout<<"nentries="<<tree3->GetEntries()<<endl;


  tree3->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
  tree3->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
  tree3->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
  tree3->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);
      
  tree3->SetBranchAddress("PDGIdDaughters",&_PDGIdDaughters);
  tree3->SetBranchAddress("daughters_px",&_daughters_px);
  tree3->SetBranchAddress("daughters_py",&_daughters_py);
  tree3->SetBranchAddress("daughters_pz",&_daughters_pz);
  tree3->SetBranchAddress("daughters_e",&_daughters_e);
  tree3->SetBranchAddress("tauID",&_tauID);
      
  tree3->SetBranchAddress("category",&_category);

  f_new->cd();
  TTree* HTauTauTree_2lOS_CR=tree3->GetTree()->CloneTree(0);

  HTauTauTree_2lOS_CR->Branch("recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT);

  
  for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _recotauh_sel_px = 0;
      _recotauh_sel_py = 0;
      _recotauh_sel_pz = 0;
      _recotauh_sel_e = 0;
      
      _PDGIdDaughters = 0;
      _daughters_px = 0;
      _daughters_py = 0;
      _daughters_pz = 0;
      _daughters_e = 0;
      _tauID = 0;
 
      _category = 0;

      _recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT.clear();      

      tree3->GetEntry(i);


      if(_category!=-11) continue;  

      for(unsigned int i_tau=0; i_tau<(*_recotauh_sel_px).size(); i_tau++){

	TLorentzVector tau((*_recotauh_sel_px)[i_tau],(*_recotauh_sel_py)[i_tau],(*_recotauh_sel_pz)[i_tau],(*_recotauh_sel_e)[i_tau]);

	for(unsigned int i_dau=0; i_dau<(*_daughters_px).size(); i_dau++){
	  
	  if(abs((*_PDGIdDaughters)[i_dau])!=15) continue;

	  TLorentzVector dau((*_daughters_px)[i_dau],(*_daughters_py)[i_dau],(*_daughters_pz)[i_dau],(*_daughters_e)[i_dau]);
	  float dR=dau.DeltaR(tau);
	 
	  if(dR<0.01){
	    _recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT.push_back(((*_tauID)[i_dau]>>29)&1);
	    
	    break;

	  }

	}

      }


      if(_recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0])
	HTauTauTree_2lOS_CR->Fill();

  }
  
  f_new->cd();
  HTauTauTree_2lOS_CR->Write();

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








void add_VTightTau_FR_3l(TString filein, TString fileout){



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
  vector<float>* _recotauh_sel_px;
  vector<float>* _recotauh_sel_py;
  vector<float>* _recotauh_sel_pz;
  vector<float>* _recotauh_sel_e;

  vector<int>* _PDGIdDaughters;
  vector<float>* _daughters_px;
  vector<float>* _daughters_py;
  vector<float>* _daughters_pz;
  vector<float>* _daughters_e;
  vector<Long64_t> *_tauID;

  int _category;


  tree->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
  tree->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
  tree->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
  tree->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);

  tree->SetBranchAddress("PDGIdDaughters",&_PDGIdDaughters);
  tree->SetBranchAddress("daughters_px",&_daughters_px);
  tree->SetBranchAddress("daughters_py",&_daughters_py);
  tree->SetBranchAddress("daughters_pz",&_daughters_pz);
  tree->SetBranchAddress("daughters_e",&_daughters_e);
  tree->SetBranchAddress("tauID",&_tauID);
  tree->SetBranchAddress("category",&_category);


  TTree* HTauTauTree_3l=tree->GetTree()->CloneTree(0);
  TTree* HTauTauTree_3l_lepMVA_CR_1=tree->GetTree()->CloneTree(0);
  HTauTauTree_3l_lepMVA_CR_1->SetNameTitle("HTauTauTree_3l_lepMVA_CR_1","HTauTauTree_3l_lepMVA_CR_1");


  //New branches
  vector<int> _recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<float> _recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT;

  float _event_weight_ttH_v2;
  int _category_v2;

  HTauTauTree_3l->Branch("recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  HTauTauTree_3l->Branch("recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  HTauTauTree_3l->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  HTauTauTree_3l->Branch("category_v2",&_category_v2,"category_v2/I");

  HTauTauTree_3l_lepMVA_CR_1->Branch("recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  HTauTauTree_3l_lepMVA_CR_1->Branch("recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  HTauTauTree_3l_lepMVA_CR_1->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  HTauTauTree_3l_lepMVA_CR_1->Branch("category_v2",&_category_v2,"category_v2/I");


  TFile* f_fakerate_tau = TFile::Open("fake_rate_weights/FR_tau_2016.root");
  TGraphAsymmErrors* gr_fakerate_tau_Vtight_barrel = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVTight/absEtaLt1_5/jetToTauFakeRate_mc_hadTaus_pt");
  TGraphAsymmErrors* gr_fakerate_tau_Vtight_endcaps = (TGraphAsymmErrors*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVTight/absEta1_5to9_9/jetToTauFakeRate_mc_hadTaus_pt");
  TF1* f_dataMC_fakerate_tau_Vtight_barrel = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVTight/absEtaLt1_5/fitFunction_data_div_mc_hadTaus_pt");
  TF1* f_dataMC_fakerate_tau_Vtight_endcaps = (TF1*)f_fakerate_tau->Get("jetToTauFakeRate/dR03mvaVTight/absEta1_5to9_9/fitFunction_data_div_mc_hadTaus_pt");  

  
  for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _recotauh_sel_px = 0;
      _recotauh_sel_py = 0;
      _recotauh_sel_pz = 0;
      _recotauh_sel_e = 0;
      
      _PDGIdDaughters = 0;
      _daughters_px = 0;
      _daughters_py = 0;
      _daughters_pz = 0;
      _daughters_e = 0;
      _tauID = 0;

      _recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
      _recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
  
      _event_weight_ttH_v2 = 0;
      _category_v2 = 0;

      tree->GetEntry(i);

      if(_category!=16) continue;
      
      for(unsigned int i_tau=0; i_tau<(*_recotauh_sel_px).size(); i_tau++){

	TLorentzVector tau((*_recotauh_sel_px)[i_tau],(*_recotauh_sel_py)[i_tau],(*_recotauh_sel_pz)[i_tau],(*_recotauh_sel_e)[i_tau]);

	for(unsigned int i_dau=0; i_dau<(*_daughters_px).size(); i_dau++){
	  
	  if(abs((*_PDGIdDaughters)[i_dau])!=15) continue;

	  TLorentzVector dau((*_daughters_px)[i_dau],(*_daughters_py)[i_dau],(*_daughters_pz)[i_dau],(*_daughters_e)[i_dau]);
	  float dR=dau.DeltaR(tau);
	 
	  if(dR<0.01){
	    _recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT.push_back(((*_tauID)[i_dau]>>29)&1);
	    
	    float fakerate_Vtight = 0;
	    if(fabs(tau.Eta())<1.479){
	      fakerate_Vtight = fakerate_from_TGraph(gr_fakerate_tau_Vtight_barrel,tau.Pt());
	      fakerate_Vtight *= f_dataMC_fakerate_tau_Vtight_barrel->Eval(tau.Pt());
	    }
	    else{
	      fakerate_Vtight = fakerate_from_TGraph(gr_fakerate_tau_Vtight_endcaps,tau.Pt());
	      fakerate_Vtight *= f_dataMC_fakerate_tau_Vtight_endcaps->Eval(tau.Pt());
	    }

	    _recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT.push_back(fakerate_Vtight);
	    break;

	  }

	}

      }


      if(_recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0]){
	_event_weight_ttH_v2 = 1;
	_category_v2 = 16;
	HTauTauTree_3l->Fill();
      }
      else{
	float weight_tau = (_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0]);
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

  vector<float>* _recotauh_px;
  vector<float>* _recotauh_py;
  vector<float>* _recotauh_pz;
  vector<float>* _recotauh_e;
  vector<float>* _recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT;

  tree2->SetBranchAddress("recotauh_sel_px",&_recotauh_sel_px);
  tree2->SetBranchAddress("recotauh_sel_py",&_recotauh_sel_py);
  tree2->SetBranchAddress("recotauh_sel_pz",&_recotauh_sel_pz);
  tree2->SetBranchAddress("recotauh_sel_e",&_recotauh_sel_e);

  tree2->SetBranchAddress("PDGIdDaughters",&_PDGIdDaughters);
  tree2->SetBranchAddress("daughters_px",&_daughters_px);
  tree2->SetBranchAddress("daughters_py",&_daughters_py);
  tree2->SetBranchAddress("daughters_pz",&_daughters_pz);
  tree2->SetBranchAddress("daughters_e",&_daughters_e);
  tree2->SetBranchAddress("tauID",&_tauID);

  tree2->SetBranchAddress("recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree2->SetBranchAddress("event_weight_ttH",&_event_weight_ttH);
  tree2->SetBranchAddress("category",&_category);

  tree2->SetBranchAddress("recotauh_px",&_recotauh_px);
  tree2->SetBranchAddress("recotauh_py",&_recotauh_py);
  tree2->SetBranchAddress("recotauh_pz",&_recotauh_pz);
  tree2->SetBranchAddress("recotauh_e",&_recotauh_e);

  tree2->SetBranchAddress("recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT);

  f_new->cd();
  TTree* HTauTauTree_3l_lepMVA_CR_2=tree2->GetTree()->CloneTree(0);
  HTauTauTree_3l_lepMVA_CR_2->SetNameTitle("HTauTauTree_3l_lepMVA_CR_2","HTauTauTree_3l_lepMVA_CR_2");

  HTauTauTree_3l_lepMVA_CR_2->Branch("recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  HTauTauTree_3l_lepMVA_CR_2->Branch("recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  HTauTauTree_3l_lepMVA_CR_2->Branch("event_weight_ttH_v2",&_event_weight_ttH_v2,"event_weight_ttH_v2/F");
  HTauTauTree_3l_lepMVA_CR_2->Branch("category_v2",&_category_v2,"category_v2/I");

  
  for(int i=0;i<nentries;i++){
      
      if(i%10000==0)
	cout<<"i="<<i<<endl;

      _recotauh_sel_px = 0;
      _recotauh_sel_py = 0;
      _recotauh_sel_pz = 0;
      _recotauh_sel_e = 0;
      
      _PDGIdDaughters = 0;
      _daughters_px = 0;
      _daughters_py = 0;
      _daughters_pz = 0;
      _daughters_e = 0;
      _tauID = 0;

      _recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _recotauh_sel_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;
      _event_weight_ttH = 0; 
      _category = 0;

      _recotauh_px = 0;
      _recotauh_py = 0;
      _recotauh_pz = 0;
      _recotauh_e = 0;
      _recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT = 0;

      _recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
      _recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
  
      _event_weight_ttH_v2 = 0;
      _category_v2 = 0;

      tree2->GetEntry(i);

      if(_category!=46) continue;
      _category_v2 = 46;
      

      for(unsigned int i_tau=0; i_tau<(*_recotauh_sel_px).size(); i_tau++){

	TLorentzVector tau((*_recotauh_sel_px)[i_tau],(*_recotauh_sel_py)[i_tau],(*_recotauh_sel_pz)[i_tau],(*_recotauh_sel_e)[i_tau]);

	for(unsigned int i_dau=0; i_dau<(*_daughters_px).size(); i_dau++){
	  
	  if(abs((*_PDGIdDaughters)[i_dau])!=15) continue;

	  TLorentzVector dau((*_daughters_px)[i_dau],(*_daughters_py)[i_dau],(*_daughters_pz)[i_dau],(*_daughters_e)[i_dau]);
	  float dR=dau.DeltaR(tau);
	 
	  if(dR<0.01){
	    _recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT.push_back(((*_tauID)[i_dau]>>29)&1);
	    
	    float fakerate_Vtight = 0;
	    if(fabs(tau.Eta())<1.479){
	      fakerate_Vtight = fakerate_from_TGraph(gr_fakerate_tau_Vtight_barrel,tau.Pt());
	      fakerate_Vtight *= f_dataMC_fakerate_tau_Vtight_barrel->Eval(tau.Pt());
	    }
	    else{
	      fakerate_Vtight = fakerate_from_TGraph(gr_fakerate_tau_Vtight_endcaps,tau.Pt());
	      fakerate_Vtight *= f_dataMC_fakerate_tau_Vtight_endcaps->Eval(tau.Pt());
	    }

	    _recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT.push_back(fakerate_Vtight);
	    break;

	  }

	}

      }


      float medium_FR = 0;
      float tight_FR = _recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT[0]; 
      
      TLorentzVector tau_sel((*_recotauh_sel_px)[0], (*_recotauh_sel_py)[0], (*_recotauh_sel_pz)[0], (*_recotauh_sel_e)[0]);


      for(unsigned int i_tau=0;i_tau<(*_recotauh_px).size();i_tau++){

	TLorentzVector tau((*_recotauh_px)[0], (*_recotauh_py)[0], (*_recotauh_pz)[0], (*_recotauh_e)[0]);
	float dR = tau.DeltaR(tau_sel);

	if(dR<0.01){
	  medium_FR = (*_recotauh_fakerate_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[i_tau];
	  break;
	}

      }



      if(!(*_recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT)[0]){

	float weight_tau_old = medium_FR/(1-medium_FR);
	float weight_tau_new = tight_FR/(1-tight_FR);
	_event_weight_ttH_v2 = _event_weight_ttH * weight_tau_new / weight_tau_old;

      }

      else{

	if((_recotauh_sel_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0])
	  _event_weight_ttH_v2 = _event_weight_ttH;
	else{
	  float weight_tau_new = (_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0]/(1-(_recotauh_sel_fakerate_byVTightIsolationMVArun2v1DBdR03oldDMwLT)[0]);
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

  /*TString filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU_lepSF.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_VTightTau_2lSS.root"; 
  add_VTightTau_FR_2lSS(filein,fileout);*/


  /*filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_VTightTau_2lSS.root"; 
  add_VTightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout);*/


  TString filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);


 filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);




  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);



  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split_VTightTau_2lSS.root";
  add_VTightTau_FR_2lSS(filein,fileout,true);





}








void test_3l(){

  TString filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape_PU_lepSF.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_VTightTau_3l.root"; 
  add_VTightTau_FR_3l(filein,fileout);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_VTightTau_3l.root"; 
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_bTagSF_CSVshape_PU_lepSF.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);


 filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);




  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);



  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split_VTightTau_3l.root";
  add_VTightTau_FR_3l(filein,fileout);





}
