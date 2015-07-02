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

#include "compute_ME.C"
#include "Helpers_RecoVegas_VBF.C"


#include <vector>
#ifdef __MAKECINT__
#pragma link C++ class vector<double>+;
#pragma link C++ class vector<vector<int> >+;

#endif


using namespace std;



void convert_tree(TString sample){

  TString dir_in;
  TString dir_out;
  TString file;    

  if(sample=="VBF"){
    file="ntuple_VBF.root";
    dir_in="/data_CMS/cms/strebler/VBF_Samples/VBF_8TeV_PU20_Jetak5_JEC_L1FastL2L3_METmtx_MET_15_12_14_CRAB3_v5/";
    dir_out="/data_CMS/cms/strebler/VBF_Samples/ntuples_converted/";
  }
  else if(sample=="DY"){
    file="ntuple_DY.root";
    dir_in="/data_CMS/cms/strebler/DY_Samples/DY2JetsToLL_M-50_8TeV_PU_20_Jetak5_JEC_L1FastL2L3_MET_Charge_09_03_15_v6/";
    dir_out="/data_CMS/cms/strebler/DY_Samples/ntuples_converted/";
  }


  vector<TString> list;
  list.push_back(dir_in+"*.root");	

  TChain * tree = new TChain("demo/genTree");
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }

  //TFile* f = TFile::Open("/data_CMS/cms/strebler/"+dir_in+file);
  //TTree* tree = (TTree*) f->Get("demo/genTree");


  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(dir_out+file);
  if(f_new!=0){
    cout<<"/data_CMS/cms/strebler/"+dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(dir_out+file,"RECREATE");


  TTree* tree_new=tree->GetTree()->CloneTree(0);
  //TTree* tree_new=tree->CloneTree(0);

  //New branches
  vector<int> _genlepID;
  vector<double> _genlep_energy;
  vector<double> _genlep_px;
  vector<double> _genlep_py;
  vector<double> _genlep_pz;
  vector<double> _genlep_pt;
  vector<double> _genlep_eta;
  vector<double> _genlep_phi;
 
  vector<double> _genpi_energy;
  vector<double> _genpi_px;
  vector<double> _genpi_py;
  vector<double> _genpi_pz;
  vector<double> _genpi_pt;
  vector<double> _genpi_eta;
  vector<double> _genpi_phi;

  int _nrecoPFJet30;
  vector<double> _recoPFJet30_energy;
  vector<double> _recoPFJet30_pt;
  vector<double> _recoPFJet30_px;
  vector<double> _recoPFJet30_py;
  vector<double> _recoPFJet30_pz;
  vector<double> _recoPFJet30_eta;
  vector<double> _recoPFJet30_phi;

  vector<int> _genHardScat_Quark_iclosest_recoPFJet30;
  vector<double> _genHardScat_Quark_dRmin_recoPFJet30;
  vector<int> _recoPFJet30_iclosest_genHardScat_Quark;
  vector<double> _recoPFJet30_dRmin_genHardScat_Quark;

  int _npair_recoPFJet30;
  vector<vector<int> > _index_pair_recoPFJet30;
  int _ipair_recoPFJet30_matched;
  vector <double> _MEM_VBF_Integrand;
  double _MEM_VBF_Integrand_recoPFJet30_matched;

  vector <double> _MEM_VBF_Integrand_bug;



  tree_new->Branch("genlepID",&_genlepID);
  tree_new->Branch("genlep_energy",&_genlep_energy);
  tree_new->Branch("genlep_px",&_genlep_px);
  tree_new->Branch("genlep_py",&_genlep_py);
  tree_new->Branch("genlep_pz",&_genlep_pz);
  tree_new->Branch("genlep_pt",&_genlep_pt);
  tree_new->Branch("genlep_eta",&_genlep_eta);
  tree_new->Branch("genlep_phi",&_genlep_phi);

  tree_new->Branch("genpi_energy",&_genpi_energy);
  tree_new->Branch("genpi_px",&_genpi_px);
  tree_new->Branch("genpi_py",&_genpi_py);
  tree_new->Branch("genpi_pz",&_genpi_pz);
  tree_new->Branch("genpi_pt",&_genpi_pt);
  tree_new->Branch("genpi_eta",&_genpi_eta);
  tree_new->Branch("genpi_phi",&_genpi_phi);

  tree_new->Branch("nrecoPFJet30",&_nrecoPFJet30,"_nrecoPFJet30/I");
  tree_new->Branch("recoPFJet30_energy",&_recoPFJet30_energy);
  tree_new->Branch("recoPFJet30_pt",&_recoPFJet30_pt);
  tree_new->Branch("recoPFJet30_px",&_recoPFJet30_px);
  tree_new->Branch("recoPFJet30_py",&_recoPFJet30_py);
  tree_new->Branch("recoPFJet30_pz",&_recoPFJet30_pz);
  tree_new->Branch("recoPFJet30_eta",&_recoPFJet30_eta);
  tree_new->Branch("recoPFJet30_phi",&_recoPFJet30_phi);

  tree_new->Branch("genHardScat_Quark_iclosest_recoPFJet30",&_genHardScat_Quark_iclosest_recoPFJet30);
  tree_new->Branch("genHardScat_Quark_dRmin_recoPFJet30",&_genHardScat_Quark_dRmin_recoPFJet30);
  tree_new->Branch("recoPFJet30_iclosest_genHardScat_Quark",&_recoPFJet30_iclosest_genHardScat_Quark);
  tree_new->Branch("recoPFJet30_dRmin_genHardScat_Quark",&_recoPFJet30_dRmin_genHardScat_Quark);

  tree_new->Branch("npair_recoPFJet30",&_npair_recoPFJet30,"_npair_recoPFJet30/I");
  tree_new->Branch("index_pair_recoPFJet30",&_index_pair_recoPFJet30);
  tree_new->Branch("ipair_recoPFJet30_matched",&_ipair_recoPFJet30_matched,"_ipair_recoPFJet30_matched/I");
  tree_new->Branch("MEM_VBF_Integrand",&_MEM_VBF_Integrand);
  tree_new->Branch("MEM_VBF_Integrand_recoPFJet30_matched",&_MEM_VBF_Integrand_recoPFJet30_matched,"_MEM_VBF_Integrand_recoPFJet30_matched/D");

  tree_new->Branch("MEM_VBF_Integrand_bug",&_MEM_VBF_Integrand_bug);


  //Old branches used
  vector<double> *_recoPFJet_energy;
  vector<double> *_recoPFJet_pt;
  vector<double> *_recoPFJet_px;
  vector<double> *_recoPFJet_py;
  vector<double> *_recoPFJet_pz;
  vector<double> *_recoPFJet_eta;
  vector<double> *_recoPFJet_phi;

  vector<double> *_genHardScat_Quark_energy;
  vector<double> *_genHardScat_Quark_px;
  vector<double> *_genHardScat_Quark_py;
  vector<double> *_genHardScat_Quark_pz;

  vector<double> *_genHardScat_Tau_energy;
  vector<double> *_genHardScat_Tau_px;
  vector<double> *_genHardScat_Tau_py;
  vector<double> *_genHardScat_Tau_pz;
  vector<int> *_genHardScat_Tau_DecayMode;

  vector<vector<double> > *_genPion_Tau_energy;
  vector<vector<double> > *_genPion_Tau_px;
  vector<vector<double> > *_genPion_Tau_py;
  vector<vector<double> > *_genPion_Tau_pz;

  vector<double> *_gentrueMET_energy;
  vector<double> *_gentrueMET_px;  
  vector<double> *_gentrueMET_py;
  vector<double> *_gentrueMET_pz;

  vector<double> *_recoPFMETunc_CovMtxInv;


  tree->SetBranchAddress("recoPFJet_energy",&_recoPFJet_energy);
  tree->SetBranchAddress("recoPFJet_pt",&_recoPFJet_pt);
  tree->SetBranchAddress("recoPFJet_px",&_recoPFJet_px);
  tree->SetBranchAddress("recoPFJet_py",&_recoPFJet_py);
  tree->SetBranchAddress("recoPFJet_pz",&_recoPFJet_pz);
  tree->SetBranchAddress("recoPFJet_eta",&_recoPFJet_eta);
  tree->SetBranchAddress("recoPFJet_phi",&_recoPFJet_phi);

  tree->SetBranchAddress("genHardScat_Quark_energy",&_genHardScat_Quark_energy);
  tree->SetBranchAddress("genHardScat_Quark_px",&_genHardScat_Quark_px);
  tree->SetBranchAddress("genHardScat_Quark_py",&_genHardScat_Quark_py);
  tree->SetBranchAddress("genHardScat_Quark_pz",&_genHardScat_Quark_pz);

  tree->SetBranchAddress("genHardScat_Tau_energy",&_genHardScat_Tau_energy);
  tree->SetBranchAddress("genHardScat_Tau_px",&_genHardScat_Tau_px);
  tree->SetBranchAddress("genHardScat_Tau_py",&_genHardScat_Tau_py);
  tree->SetBranchAddress("genHardScat_Tau_pz",&_genHardScat_Tau_pz);
  tree->SetBranchAddress("genHardScat_Tau_DecayMode",&_genHardScat_Tau_DecayMode);
  
  tree->SetBranchAddress("genPion_Tau_energy",&_genPion_Tau_energy);
  tree->SetBranchAddress("genPion_Tau_px",&_genPion_Tau_px);
  tree->SetBranchAddress("genPion_Tau_py",&_genPion_Tau_py);
  tree->SetBranchAddress("genPion_Tau_pz",&_genPion_Tau_pz);

  tree->SetBranchAddress("gentrueMET_energy",&_gentrueMET_energy);
  tree->SetBranchAddress("gentrueMET_px",&_gentrueMET_px);
  tree->SetBranchAddress("gentrueMET_py",&_gentrueMET_py);
  tree->SetBranchAddress("gentrueMET_pz",&_gentrueMET_pz);
  tree->SetBranchAddress("recoPFMETunc_CovMtxInv",&_recoPFMETunc_CovMtxInv);


  string it1="/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/ct11pdfcpp/ct10nn.00.pds";
  cteqpdf ct10nn;
  ct10nn.setct11(it1);
  
  CPPProcess_uu_to_uuH process_uu_to_uuH;
  CPPProcess_ud_to_udH process_ud_to_udH;
  CPPProcess_uc_to_ucH process_uc_to_ucH;
  CPPProcess_us_to_usH process_us_to_usH;
  CPPProcess_us_to_dcH process_us_to_dcH;
  CPPProcess_uubar_to_uubarH process_uubar_to_uubarH;
  CPPProcess_uubar_to_ddbarH process_uubar_to_ddbarH;
  CPPProcess_udbar_to_udbarH process_udbar_to_udbarH;
  CPPProcess_ucbar_to_ucbarH process_ucbar_to_ucbarH;
  CPPProcess_ucbar_to_dsbarH process_ucbar_to_dsbarH;
  CPPProcess_usbar_to_usbarH process_usbar_to_usbarH;
  CPPProcess_dd_to_ddH process_dd_to_ddH;
  CPPProcess_ds_to_dsH process_ds_to_dsH;
  CPPProcess_ddbar_to_ddbarH process_ddbar_to_ddbarH;
  CPPProcess_ddbar_to_uubarH process_ddbar_to_uubarH;
  CPPProcess_dsbar_to_dsbarH process_dsbar_to_dsbarH;
  CPPProcess_dsbar_to_ucbarH process_dsbar_to_ucbarH;
  
  process_uu_to_uuH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_ud_to_udH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_uc_to_ucH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_us_to_usH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_us_to_dcH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_uubar_to_uubarH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_uubar_to_ddbarH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_udbar_to_udbarH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_ucbar_to_ucbarH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_ucbar_to_dsbarH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_usbar_to_usbarH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_dd_to_ddH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_ds_to_dsH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_ddbar_to_ddbarH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_ddbar_to_uubarH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_dsbar_to_dsbarH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  process_dsbar_to_ucbarH.initProc("/home/llr/cms/strebler/MG5_aMC_v2_2_1/Plots/macro/macro_MG/param_card.dat");
  
  cout<<"nentries="<<nentries<<endl;

  //nentries=100;
  for (int i=0;i<nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _genlepID.clear();
    _genlep_energy.clear();
    _genlep_px.clear();
    _genlep_py.clear();
    _genlep_pz.clear();
    _genlep_pt.clear();
    _genlep_eta.clear();
    _genlep_phi.clear();

    _genpi_energy.clear();
    _genpi_px.clear();
    _genpi_py.clear();
    _genpi_pz.clear();
    _genpi_pt.clear();
    _genpi_eta.clear();
    _genpi_phi.clear();

    _nrecoPFJet30=0;
    _recoPFJet30_energy.clear();
    _recoPFJet30_pt.clear();
    _recoPFJet30_px.clear();
    _recoPFJet30_py.clear();
    _recoPFJet30_pz.clear();
    _recoPFJet30_eta.clear();
    _recoPFJet30_phi.clear();
    
    _genHardScat_Quark_iclosest_recoPFJet30.clear();
    _genHardScat_Quark_dRmin_recoPFJet30.clear();
    _recoPFJet30_iclosest_genHardScat_Quark.clear();
    _recoPFJet30_dRmin_genHardScat_Quark.clear();

    _npair_recoPFJet30=0;
    _index_pair_recoPFJet30.clear();
    _ipair_recoPFJet30_matched=-1;
    _MEM_VBF_Integrand.clear();
    _MEM_VBF_Integrand_recoPFJet30_matched=-1;

    _MEM_VBF_Integrand_bug.clear();


    _recoPFJet_energy=0;
    _recoPFJet_pt=0;
    _recoPFJet_px=0;
    _recoPFJet_py=0;
    _recoPFJet_pz=0;
    _recoPFJet_eta=0;
    _recoPFJet_phi=0;

    _genHardScat_Quark_energy=0;
    _genHardScat_Quark_px=0;
    _genHardScat_Quark_py=0;
    _genHardScat_Quark_pz=0;

    _genHardScat_Tau_energy=0;
    _genHardScat_Tau_px=0;
    _genHardScat_Tau_py=0;
    _genHardScat_Tau_pz=0;
    _genHardScat_Tau_DecayMode=0;
    
    _genPion_Tau_energy=0;
    _genPion_Tau_px=0;
    _genPion_Tau_py=0;
    _genPion_Tau_pz=0;

    _gentrueMET_energy=0;
    _gentrueMET_px=0;  
    _gentrueMET_py=0;
    _gentrueMET_pz=0;

    _recoPFMETunc_CovMtxInv=0;

    tree->GetEntry(i);
   
    //Only two taus for now
    if((*_genHardScat_Tau_DecayMode).size()!=2)
      continue;	

    //Only mu+1-prong for now
    if( !( ( (*_genHardScat_Tau_DecayMode)[0]==13 && (*_genHardScat_Tau_DecayMode)[1]==0) || ((*_genHardScat_Tau_DecayMode)[1]==13 && (*_genHardScat_Tau_DecayMode)[0]==0) ) )
       continue;

    if( (*_genPion_Tau_energy)[0].size()!=1 ||  (*_genPion_Tau_energy)[1].size()!=1){
	cout<<"We have a problem!"<<endl;
	return;
      }






    //Taus + decay product

    TLorentzVector taulep_tlv;
    TLorentzVector tauhad_tlv;
    TLorentzVector genlep_tlv;
    TLorentzVector genpi_tlv;
    
    if((*_genHardScat_Tau_DecayMode)[0]==13){

      taulep_tlv.SetPxPyPzE( (*_genHardScat_Tau_px)[0], (*_genHardScat_Tau_py)[0], (*_genHardScat_Tau_pz)[0], (*_genHardScat_Tau_energy)[0] );

      _genlepID.push_back(13);
      
      genlep_tlv.SetPxPyPzE( (*_genPion_Tau_px)[0][0], (*_genPion_Tau_py)[0][0],  (*_genPion_Tau_pz)[0][0],  (*_genPion_Tau_energy)[0][0]);
     
      _genlep_energy.push_back(genlep_tlv.E());
      _genlep_px.push_back(genlep_tlv.Px());
      _genlep_py.push_back(genlep_tlv.Py());
      _genlep_pz.push_back(genlep_tlv.Pz());
      _genlep_pt.push_back(genlep_tlv.Pt());
      _genlep_eta.push_back(genlep_tlv.Eta());
      _genlep_phi.push_back(genlep_tlv.Phi());
      
    }

    else if((*_genHardScat_Tau_DecayMode)[0]==0){
      
      tauhad_tlv.SetPxPyPzE( (*_genHardScat_Tau_px)[0], (*_genHardScat_Tau_py)[0], (*_genHardScat_Tau_pz)[0], (*_genHardScat_Tau_energy)[0]);

      genpi_tlv.SetPxPyPzE( (*_genPion_Tau_px)[0][0], (*_genPion_Tau_py)[0][0],  (*_genPion_Tau_pz)[0][0],  (*_genPion_Tau_energy)[0][0]);
     
      _genpi_energy.push_back(genpi_tlv.E());
      _genpi_px.push_back(genpi_tlv.Px());
      _genpi_py.push_back(genpi_tlv.Py());
      _genpi_pz.push_back(genpi_tlv.Pz());
      _genpi_pt.push_back(genpi_tlv.Pt());
      _genpi_eta.push_back(genpi_tlv.Eta());
      _genpi_phi.push_back(genpi_tlv.Phi());
      
    }


    if((*_genHardScat_Tau_DecayMode)[1]==13){

      taulep_tlv.SetPxPyPzE( (*_genHardScat_Tau_px)[1], (*_genHardScat_Tau_py)[1], (*_genHardScat_Tau_pz)[1], (*_genHardScat_Tau_energy)[1]);

      _genlepID.push_back(13);
      
      genlep_tlv.SetPxPyPzE( (*_genPion_Tau_px)[1][0], (*_genPion_Tau_py)[1][0],  (*_genPion_Tau_pz)[1][0],  (*_genPion_Tau_energy)[1][0]);
     
      _genlep_energy.push_back(genlep_tlv.E());
      _genlep_px.push_back(genlep_tlv.Px());
      _genlep_py.push_back(genlep_tlv.Py());
      _genlep_pz.push_back(genlep_tlv.Pz());
      _genlep_pt.push_back(genlep_tlv.Pt());
      _genlep_eta.push_back(genlep_tlv.Eta());
      _genlep_phi.push_back(genlep_tlv.Phi());
      
    }

    else if((*_genHardScat_Tau_DecayMode)[1]==0){
      
      tauhad_tlv.SetPxPyPzE( (*_genHardScat_Tau_px)[1], (*_genHardScat_Tau_py)[1], (*_genHardScat_Tau_pz)[1], (*_genHardScat_Tau_energy)[1]);

      genpi_tlv.SetPxPyPzE( (*_genPion_Tau_px)[1][0], (*_genPion_Tau_py)[1][0],  (*_genPion_Tau_pz)[1][0],  (*_genPion_Tau_energy)[1][0]);
     
      _genpi_energy.push_back(genpi_tlv.E());
      _genpi_px.push_back(genpi_tlv.Px());
      _genpi_py.push_back(genpi_tlv.Py());
      _genpi_pz.push_back(genpi_tlv.Pz());
      _genpi_pt.push_back(genpi_tlv.Pt());
      _genpi_eta.push_back(genpi_tlv.Eta());
      _genpi_phi.push_back(genpi_tlv.Phi());
      
    }



    //MET + MET covariance matrix

    TLorentzVector genMET_tlv((*_gentrueMET_px)[0],(*_gentrueMET_py)[0],(*_gentrueMET_pz)[0],(*_gentrueMET_energy)[0]);

    vector<vector<double> > MET_cov_matrix;
    vector<double> dummy;
    dummy.push_back(0);
    dummy.push_back(0);
    MET_cov_matrix.push_back(dummy);
    MET_cov_matrix.push_back(dummy);
    MET_cov_matrix[0][0]= (*_recoPFMETunc_CovMtxInv)[0];
    MET_cov_matrix[0][1]= (*_recoPFMETunc_CovMtxInv)[1];
    MET_cov_matrix[1][0]= (*_recoPFMETunc_CovMtxInv)[2];
    MET_cov_matrix[1][1]= (*_recoPFMETunc_CovMtxInv)[3];


    ///Jet + quarks matching + MEM


    int genHardScat_Quark0_iclosest_recoPFJet30=-1;
    int genHardScat_Quark1_iclosest_recoPFJet30=-1;
    double genHardScat_Quark0_dRmin_recoPFJet30=-9999;
    double genHardScat_Quark1_dRmin_recoPFJet30=-9999;

    TLorentzVector q0_tlv((*_genHardScat_Quark_px)[0],(*_genHardScat_Quark_py)[0],(*_genHardScat_Quark_pz)[0],(*_genHardScat_Quark_energy)[0]);
    TLorentzVector q1_tlv((*_genHardScat_Quark_px)[1],(*_genHardScat_Quark_py)[1],(*_genHardScat_Quark_pz)[1],(*_genHardScat_Quark_energy)[1]);
   

    for(unsigned int j=0; j<(*_recoPFJet_energy).size();j++){
      if((*_recoPFJet_pt)[j]<30)
	break;
      
      _nrecoPFJet30++;
      _recoPFJet30_energy.push_back((*_recoPFJet_energy)[j]);
      _recoPFJet30_pt.push_back((*_recoPFJet_pt)[j]);
      _recoPFJet30_px.push_back((*_recoPFJet_px)[j]);
      _recoPFJet30_py.push_back((*_recoPFJet_py)[j]);
      _recoPFJet30_pz.push_back((*_recoPFJet_pz)[j]);
      _recoPFJet30_eta.push_back((*_recoPFJet_eta)[j]);
      _recoPFJet30_phi.push_back((*_recoPFJet_phi)[j]);
      
      TLorentzVector jet_tlv(_recoPFJet30_px[j],_recoPFJet30_py[j],_recoPFJet30_pz[j],_recoPFJet30_energy[j]);

      double q0_dR_PFJet30=q0_tlv.DeltaR(jet_tlv);
      double q1_dR_PFJet30=q1_tlv.DeltaR(jet_tlv);

      if(q0_dR_PFJet30<q1_dR_PFJet30){
	_recoPFJet30_iclosest_genHardScat_Quark.push_back(0);
	_recoPFJet30_dRmin_genHardScat_Quark.push_back(q0_dR_PFJet30);
      }
      else{
	_recoPFJet30_iclosest_genHardScat_Quark.push_back(1);
	_recoPFJet30_dRmin_genHardScat_Quark.push_back(q1_dR_PFJet30);
      }


      if(genHardScat_Quark0_iclosest_recoPFJet30==-1 || q0_dR_PFJet30<genHardScat_Quark0_dRmin_recoPFJet30){
	genHardScat_Quark0_iclosest_recoPFJet30=j;
	genHardScat_Quark0_dRmin_recoPFJet30=q0_dR_PFJet30;
      }
     
      if(genHardScat_Quark1_iclosest_recoPFJet30==-1 || q1_dR_PFJet30<genHardScat_Quark1_dRmin_recoPFJet30){
	genHardScat_Quark1_iclosest_recoPFJet30=j;
	genHardScat_Quark1_dRmin_recoPFJet30=q1_dR_PFJet30;
      }
      
      //Pair indexing

      for(unsigned int k=j+1; k<(*_recoPFJet_energy).size();k++){
	if((*_recoPFJet_pt)[k]<30)
	  break;

	_npair_recoPFJet30++;
	vector<int> pair_indices;
	pair_indices.push_back(j);
	pair_indices.push_back(k);
	_index_pair_recoPFJet30.push_back(pair_indices);

	//weight computation at MC-truth

	map<TString,TLorentzVector> LV;
	TLorentzVector jet1_tlv=jet_tlv;	
	TLorentzVector jet2_tlv((*_recoPFJet_px)[k],(*_recoPFJet_py)[k],(*_recoPFJet_pz)[k],(*_recoPFJet_energy)[k]);

	LV["jet1"]=jet1_tlv;
	LV["jet2"]=jet2_tlv;
	LV["lep"]=genlep_tlv;
	LV["pi"]=genpi_tlv;
	LV["MET"]=genMET_tlv;

	double mtautau2=125*125;
	double tau_lep_P=taulep_tlv.P();
	double costheta_tautau=TMath::Cos(taulep_tlv.Angle(tauhad_tlv.Vect()));
	double q1_E=jet1_tlv.E();
	double q2_E=jet2_tlv.E();

	map<TString,double> output_MEM_VBF=Full_ME_VBF_TF_Vegas(1,
								ct10nn,
								process_uu_to_uuH,
								process_ud_to_udH,
								process_uc_to_ucH,
								process_us_to_usH,
								process_us_to_dcH,
								process_uubar_to_uubarH,
								process_uubar_to_ddbarH,
								process_udbar_to_udbarH,
								process_ucbar_to_ucbarH,
								process_ucbar_to_dsbarH,
								process_usbar_to_usbarH,
								process_dd_to_ddH,
								process_ds_to_dsH,
								process_ddbar_to_ddbarH,
								process_ddbar_to_uubarH,
								process_dsbar_to_dsbarH,
								process_dsbar_to_ucbarH,
								LV,
								MET_cov_matrix,
								mtautau2,
								tau_lep_P,
								costheta_tautau,
								q1_E,
								q2_E);

	
	_MEM_VBF_Integrand.push_back(output_MEM_VBF["Integrand"]);
	
	
	map<TString,TLorentzVector> LV_bug=LV;
	LV_bug["jet2"]=LV["jet1"];
	
	map<TString,double> output_MEM_VBF_bug=Full_ME_VBF_TF_Vegas(1,
								ct10nn,
								process_uu_to_uuH,
								process_ud_to_udH,
								process_uc_to_ucH,
								process_us_to_usH,
								process_us_to_dcH,
								process_uubar_to_uubarH,
								process_uubar_to_ddbarH,
								process_udbar_to_udbarH,
								process_ucbar_to_ucbarH,
								process_ucbar_to_dsbarH,
								process_usbar_to_usbarH,
								process_dd_to_ddH,
								process_ds_to_dsH,
								process_ddbar_to_ddbarH,
								process_ddbar_to_uubarH,
								process_dsbar_to_dsbarH,
								process_dsbar_to_ucbarH,
								LV_bug,
								MET_cov_matrix,
								mtautau2,
								tau_lep_P,
								costheta_tautau,
								q1_E,
								q1_E);

	_MEM_VBF_Integrand_bug.push_back(output_MEM_VBF_bug["Integrand"]);


      }

    }

    _genHardScat_Quark_iclosest_recoPFJet30.push_back(genHardScat_Quark0_iclosest_recoPFJet30);
    _genHardScat_Quark_iclosest_recoPFJet30.push_back(genHardScat_Quark1_iclosest_recoPFJet30);
    _genHardScat_Quark_dRmin_recoPFJet30.push_back(genHardScat_Quark0_dRmin_recoPFJet30);
    _genHardScat_Quark_dRmin_recoPFJet30.push_back(genHardScat_Quark1_dRmin_recoPFJet30);



    if(genHardScat_Quark0_dRmin_recoPFJet30<0.5 && genHardScat_Quark1_dRmin_recoPFJet30<0.5){

      for(int j=0;j<_npair_recoPFJet30;j++){
      
	if( (_index_pair_recoPFJet30[j][0]==genHardScat_Quark0_iclosest_recoPFJet30 && _index_pair_recoPFJet30[j][1]==genHardScat_Quark1_iclosest_recoPFJet30) || (_index_pair_recoPFJet30[j][1]==genHardScat_Quark0_iclosest_recoPFJet30 && _index_pair_recoPFJet30[j][0]==genHardScat_Quark1_iclosest_recoPFJet30) ){
	  _ipair_recoPFJet30_matched=j;
	  break;
	}
      
      }

      _MEM_VBF_Integrand_recoPFJet30_matched=_MEM_VBF_Integrand[_ipair_recoPFJet30_matched];

    }



    tree_new->Fill();

  }

  tree_new->Write();
  f_new->Close();

  //tree->AddFriend("genTree","/data_CMS/cms/strebler/"+dir_out+file);

  return;

}





void convert_tree_jet_forward(TString sample_in, TString sample_out){


  vector<TString> list;
  list.push_back(sample_in);	

  TChain * tree = new TChain("T");
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }


  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(sample_out);
  if(f_new!=0){
    cout<<sample_out<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(sample_out,"RECREATE");

  //Old branches used
  int _nJets30;
  float _ptAll[20];
  float _etaAll[20];
  float _phiAll[20];

  tree->SetBranchAddress("nJets30",&_nJets30);
  tree->SetBranchAddress("ptAll",_ptAll);
  tree->SetBranchAddress("etaAll",_etaAll);
  tree->SetBranchAddress("phiAll",_phiAll);

  TTree* tree_new=tree->GetTree()->CloneTree(0);

  //New branches
  float _pt1_forw_jet;
  float _pt2_forw_jet;
  float _eta1_forw_jet;
  float _eta2_forw_jet;
  float _phi1_forw_jet;
  float _phi2_forw_jet;
  float _Deta_forw_jet;
  float _Dphi_forw_jet;
  float _Mjj_forw_jet;
  int _lead_forw_jet_flag;


  tree_new->Branch("pt1_forw_jet",&_pt1_forw_jet,"pt1_forw_jet/F");
  tree_new->Branch("pt2_forw_jet",&_pt2_forw_jet,"pt2_forw_jet/F");
  tree_new->Branch("eta1_forw_jet",&_eta1_forw_jet,"eta1_forw_jet/F");
  tree_new->Branch("eta2_forw_jet",&_eta2_forw_jet,"eta2_forw_jet/F");
  tree_new->Branch("phi1_forw_jet",&_phi1_forw_jet,"phi1_forw_jet/F");
  tree_new->Branch("phi2_forw_jet",&_phi2_forw_jet,"phi2_forw_jet/F");
  tree_new->Branch("Deta_forw_jet",&_Deta_forw_jet,"Deta_forw_jet/F");
  tree_new->Branch("Mjj_forw_jet",&_Mjj_forw_jet,"Mjj_forw_jet/F");
  tree_new->Branch("lead_forw_jet_flag",&_lead_forw_jet_flag,"lead_forw_jet_flag/I");



  //nentries=100;
  for (int i=0;i<nentries;i++) {

    _pt1_forw_jet=-9999;
    _pt2_forw_jet=-9999;
    _eta1_forw_jet=-9999;
    _eta2_forw_jet=-9999;
    _phi1_forw_jet=-9999;
    _phi2_forw_jet=-9999;
    _Deta_forw_jet=-9999;
    _Dphi_forw_jet=-9999;
    _Mjj_forw_jet=-9999;
    _lead_forw_jet_flag=-9999;

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    tree->GetEntry(i);
 
    double eta_min=9999;
    double eta_max=-9999;

    TLorentzVector forw_jet1;
    TLorentzVector forw_jet2;
    int i_forw_jet1=-1;
    int i_forw_jet2=-1;

    if(_nJets30>0){

      for(int i_jet=0; i_jet<_nJets30;i_jet++){
		
	if(_etaAll[i_jet]>eta_max){
	  eta_max=_etaAll[i_jet];
	  forw_jet1.SetPtEtaPhiM(_ptAll[i_jet],_etaAll[i_jet],_phiAll[i_jet],0);
	  i_forw_jet1=i_jet;
	}
	if(_etaAll[i_jet]<eta_min){
	  eta_min=_etaAll[i_jet];
	  forw_jet2.SetPtEtaPhiM(_ptAll[i_jet],_etaAll[i_jet],_phiAll[i_jet],0);
	  i_forw_jet2=i_jet;
	}
	
      }

      _pt1_forw_jet = forw_jet1.Pt();
      _pt2_forw_jet = forw_jet2.Pt();
      _eta1_forw_jet = forw_jet1.Eta();
      _eta2_forw_jet = forw_jet2.Eta();
      _phi1_forw_jet = forw_jet1.Phi();
      _phi2_forw_jet = forw_jet2.Phi();
      _Deta_forw_jet = abs(forw_jet1.Eta() - forw_jet2.Eta());
      _Dphi_forw_jet = forw_jet1.DeltaPhi(forw_jet2);
      _Mjj_forw_jet = (forw_jet1+forw_jet2).M();
      _lead_forw_jet_flag = (i_forw_jet1==0 && i_forw_jet2==1) || (i_forw_jet2==0 && i_forw_jet1==1);

    }     

    tree_new->Fill();

  }

  tree_new->Write();
  f_new->Close();


  return;

}
