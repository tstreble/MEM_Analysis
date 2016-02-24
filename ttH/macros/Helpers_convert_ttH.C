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

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

#include <vector>
#ifdef __MAKECINT__
#pragma link C++ class vector<double>+;
#pragma link C++ class vector<vector<int> >+;

#endif


using namespace std;


bool pT_comparison_pairs(pair<int,TLorentzVector> pair1, pair<int,TLorentzVector> pair2){

  return (pair1.second).Pt()>(pair2.second).Pt();

}


bool CSV_comparison_pairs(pair<int,float> pair1, pair<int,float> pair2){

  return pair1.second>pair2.second;

}


pair<int,float> find_i_dRmin_closest(TLorentzVector obj1_tlv,
				     vector<float> obj2_px, vector<float> obj2_py, vector<float> obj2_pz, vector<float> obj2_e){

  int imin = -1;
  float dRmin = 100000;
   
  for(unsigned int i_obj2=0; i_obj2<obj2_e.size(); i_obj2++){

    TLorentzVector obj2_tlv( obj2_px[i_obj2], obj2_py[i_obj2], obj2_pz[i_obj2], obj2_e[i_obj2]);	
    float dR = obj1_tlv.DeltaR(obj2_tlv);
    if(dR<dRmin){
      dRmin=dR;
      imin=i_obj2;
    } 
	
  }

  pair<int,float> p=make_pair(imin,dRmin);

  return p;

}



float lepMVA_pt;
float lepMVA_eta;
float lepMVA_miniRelIsoCharged;
float lepMVA_miniRelIsoNeutral;
float lepMVA_jetPtRatio;
float lepMVA_jetPtRelv2;
float lepMVA_jetBTagCSV;
float lepMVA_sip3d;
float lepMVA_dxy;
float lepMVA_dz;
float lepMVA_mvaId;
float lepMVA_jetNDauChargedMVASel;



TMVA::Reader* BookLeptonMVAReaderMoriond16(std::string basePath, std::string weightFileName, std::string type)
{
   TMVA::Reader* reader = new TMVA::Reader("!Color:!Silent");

   reader->AddVariable("LepGood_pt",                                  &lepMVA_pt);
   reader->AddVariable("LepGood_eta",                                 &lepMVA_eta);
   reader->AddVariable("LepGood_jetNDauChargedMVASel",                &lepMVA_jetNDauChargedMVASel);
   reader->AddVariable("LepGood_miniRelIsoCharged",                   &lepMVA_miniRelIsoCharged);
   reader->AddVariable("LepGood_miniRelIsoNeutral",                   &lepMVA_miniRelIsoNeutral);
   reader->AddVariable("LepGood_jetPtRelv2",                          &lepMVA_jetPtRelv2);
   reader->AddVariable("min(LepGood_jetPtRatiov2,1.5)",               &lepMVA_jetPtRatio);
   reader->AddVariable("max(LepGood_jetBTagCSV,0)",                   &lepMVA_jetBTagCSV);
   reader->AddVariable("LepGood_sip3d",                               &lepMVA_sip3d);
   reader->AddVariable("log(abs(LepGood_dxy))",                       &lepMVA_dxy);
   reader->AddVariable("log(abs(LepGood_dz))",                        &lepMVA_dz);
   if( type == "ele" ) reader->AddVariable("LepGood_mvaIdSpring15",   &lepMVA_mvaId);
   else reader->AddVariable("LepGood_segmentCompatibility",           &lepMVA_mvaId);

   reader->BookMVA("BDTG method", basePath+"/"+weightFileName);

   return reader;
}



void convert_tree(TString sample, int iso_tau=70,
		  TString iso_type="",
		  int split=0, int i_split=0){

  TString dir_in;
  TString dir_out;
  TString file;    

  vector<TString> list;


  if(sample=="ttH"){
    file="ntuple_ttH_dRveto_gen";
    dir_in="/data_CMS/cms/strebler/ttH_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis.root");
  }

  else if(sample=="ttH_ext1"){
    file="ntuple_ttH_ext1_dRveto_gen";
    dir_in="/data_CMS/cms/strebler/ttH_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_ext1.root");
  }

  else if(sample=="ttH_ext2"){
    file="ntuple_ttH_ext2_dRveto_gen";
    dir_in="/data_CMS/cms/strebler/ttH_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_ext2.root");
  }

  else if(sample=="ttH_ext3"){
    file="ntuple_ttH_ext3_dRveto_gen";
    dir_in="/data_CMS/cms/strebler/ttH_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_ext3.root");
  }

  else if(sample=="ttW"){
    file="ntuple_ttW_dRveto_gen";
    dir_in="/data_CMS/cms/strebler/ttW_Samples/Htautau_framework_files/MiniAODv2_prod_12_2015/";
    dir_out="/data_CMS/cms/strebler/ttW_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
    list.push_back(dir_in+"HTauTauAnalysis.root");
  }

  if(sample=="ttZ"){
    file="ntuple_ttZ_dRveto_gen";
    dir_in="/data_CMS/cms/strebler/ttZ_Samples/Htautau_framework_files/MiniAODv2_prod_12_2015/";
    dir_out="/data_CMS/cms/strebler/ttZ_Samples/ntuples_converted/MiniAODv2_prod_12_2015/";
    list.push_back(dir_in+"HTauTauAnalysis.root");
  }


  else if(sample=="TTJets_1"){
    file="ntuple_TTJets_dRveto_gen_1";
    dir_in="/data_CMS/cms/strebler/TTJets_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_hadd_1.root");
  }

  else if(sample=="TTJets_1"){
    file="ntuple_TTJets_dRveto_gen_1";
    dir_in="/data_CMS/cms/strebler/TTJets_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_hadd_1.root");
  }

  else if(sample=="TTJets_2"){
    file="ntuple_TTJets_dRveto_gen_2";
    dir_in="/data_CMS/cms/strebler/TTJets_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_hadd_2.root");
  }

  else if(sample=="TTJets_3"){
    file="ntuple_TTJets_dRveto_gen_3";
    dir_in="/data_CMS/cms/strebler/TTJets_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_hadd_3.root");
  }

  else if(sample=="TTJets_4"){
    file="ntuple_TTJets_dRveto_gen_4";
    dir_in="/data_CMS/cms/strebler/TTJets_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_hadd_4.root");
  }

  else if(sample=="TTJets_5"){
    file="ntuple_TTJets_dRveto_gen_5";
    dir_in="/data_CMS/cms/strebler/TTJets_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_hadd_5.root");
  }


  else if(sample=="TTJets_6"){
    file="ntuple_TTJets_dRveto_gen_6";
    dir_in="/data_CMS/cms/strebler/TTJets_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_hadd_6.root");
  }

  else if(sample=="TTJets_7"){
    file="ntuple_TTJets_dRveto_gen_7";
    dir_in="/data_CMS/cms/strebler/TTJets_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_hadd_7.root");
  }

  else if(sample=="TTJets_8"){
    file="ntuple_TTJets_dRveto_gen_8";
    dir_in="/data_CMS/cms/strebler/TTJets_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_hadd_8.root");
  }

  else if(sample=="TTJets_9"){
    file="ntuple_TTJets_dRveto_gen_9";
    dir_in="/data_CMS/cms/strebler/TTJets_Samples/Htautau_framework_files/MiniAODv2_prod_02_2016/";
    dir_out="/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/";
    list.push_back(dir_in+"HTauTauAnalysis_hadd_9.root");
  }


  if(sample=="sync"){
    file="syncNtuple_ttH";
    dir_in="/home/llr/cms/strebler/CMSSW_7_6_3/src/LLRHiggsTauTau/NtupleProducer/test/";
    dir_out="/home/llr/cms/strebler/CMSSW_7_6_3/src/LLRHiggsTauTau/NtupleProducer/test/";
    list.push_back(dir_in+"HTauTauAnalysis.root");
  }

  if(split>0)
    file+=Form("_%i",i_split);

  if(iso_type=="")
    file+=Form("_iso%i",iso_tau);
  else
    file+="_"+iso_type;
  
  file+=".root";

  

  TChain * tree = new TChain("HTauTauTree/HTauTauTree");
  int nFiles = list.size();

  for(int i=0;i<nFiles;i++)
    {
      tree->Add(list[i]);
    }



  Long64_t nentries = tree->GetEntries();

  TFile* f_new = TFile::Open(dir_out+file);
  if(f_new!=0){
    cout<<dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }
  
  f_new = TFile::Open(dir_out+file,"RECREATE");

  TTree* tree_new=tree->GetTree()->CloneTree(0);
  //TTree* tree_new=tree->CloneTree(0);

  //New branches
  //int _EventNumber;
  //int _RunNumber;
  //int _lumi;
  //float _MC_weight;

  vector<float> _daughters_pt;
  vector<float> _daughters_eta;
  vector<float> _daughters_phi;
  vector<float> _daughters_dR_closest_jet;

  vector<float> _jets_pt;
  vector<float> _jets_eta;
  vector<float> _jets_phi;

  int _n_recolep;
  vector<int> _recolep_ID;
  vector<int> _recolep_charge;
  vector<float> _recolep_e;
  vector<float> _recolep_px;
  vector<float> _recolep_py;
  vector<float> _recolep_pz;
  vector<float> _recolep_pt;
  vector<float> _recolep_eta;
  vector<float> _recolep_phi;
  vector<float> _recolep_leptonMVA;
  vector<int> _recolep_TopMothInd;
  vector<int> _recolep_HMothInd;


  int _n_recomu;
  vector<int> _recomu_ID;
  vector<int> _recomu_charge;
  vector<float> _recomu_e;
  vector<float> _recomu_px;
  vector<float> _recomu_py;
  vector<float> _recomu_pz;
  vector<float> _recomu_pt;
  vector<float> _recomu_eta;
  vector<float> _recomu_phi;
  vector<float> _recomu_dxy;
  vector<float> _recomu_dz;
  vector<int>   _recomu_jetNDauChargedMVASel;
  vector<float> _recomu_miniRelIso;
  vector<float> _recomu_miniIsoCharged;
  vector<float> _recomu_miniIsoNeutral;
  vector<float> _recomu_sip3D;
  vector<float> _recomu_jetPtRel;
  vector<float> _recomu_jetCSV;
  vector<float> _recomu_jetPtRatio;
  vector<float> _recomu_lepMVA_mvaId;
  vector<float> _recomu_leptonMVA;

  int _n_recoele;
  vector<int> _recoele_ID;
  vector<int> _recoele_charge;
  vector<float> _recoele_e;
  vector<float> _recoele_px;
  vector<float> _recoele_py;
  vector<float> _recoele_pz;
  vector<float> _recoele_pt;
  vector<float> _recoele_eta;
  vector<float> _recoele_phi;
  vector<float> _recoele_dxy;
  vector<float> _recoele_dz;
  vector<int>   _recoele_jetNDauChargedMVASel;
  vector<float> _recoele_miniRelIso;
  vector<float> _recoele_miniIsoCharged;
  vector<float> _recoele_miniIsoNeutral;
  vector<float> _recoele_sip3D;
  vector<float> _recoele_jetPtRel;
  vector<float> _recoele_jetCSV;
  vector<float> _recoele_jetPtRatio;
  vector<float> _recoele_lepMVA_mvaId;
  vector<float> _recoele_leptonMVA;
 
  int _n_recotauh;
  vector<int> _recotauh_charge;
  vector<int> _recotauh_decayMode;
  vector<float> _recotauh_e;
  vector<float> _recotauh_px;
  vector<float> _recotauh_py;
  vector<float> _recotauh_pz;
  vector<float> _recotauh_pt;
  vector<float> _recotauh_eta;
  vector<float> _recotauh_phi;
  vector<float> _recotauh_dxy;
  vector<float> _recotauh_dz;
  vector<float> _recotauh_iso;
  
  vector<int> _recotauh_decayModeFindingOldDMs;
  vector<int> _recotauh_decayModeFindingNewDMs;
  vector<int> _recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits;
  vector<int> _recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits;
  vector<int> _recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits;
  vector<int> _recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int> _recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int> _recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03;
  vector<int> _recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int> _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int> _recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int> _recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT;
  vector<int> _recotauh_againstMuonLoose3;
  vector<int> _recotauh_againstMuonTight3;
  vector<int> _recotauh_againstElectronVLooseMVA6;
  vector<int> _recotauh_againstElectronLooseMVA6;
  vector<int> _recotauh_againstElectronMediumMVA6;
  vector<int> _recotauh_againstElectronTightMVA6;
  vector<int> _recotauh_againstElectronVTightMVA6;

  vector<int> _recotauh_i_closest_genpart;
  vector<float> _recotauh_dR_closest_genpart;

  int _n_recoPFJet;
  vector<float> _recoPFJet_e;
  vector<float> _recoPFJet_pt;
  vector<float> _recoPFJet_px;
  vector<float> _recoPFJet_py;
  vector<float> _recoPFJet_pz;
  vector<float> _recoPFJet_eta;
  vector<float> _recoPFJet_phi;
  vector<float> _recoPFJet_CSVscore;
  vector<int> _recoPFJet_Flavour;
  vector<int> _recoPFJet_i_closest_genpart;
  vector<float> _recoPFJet_dR_closest_genpart;
  vector<int> _recoPFJet_i_2nd_closest_genpart;
  vector<float> _recoPFJet_dR_2nd_closest_genpart;
  vector<int> _recoPFJet_i_closest_lep;
  vector<float> _recoPFJet_dR_closest_lep;
  vector<int> _recoPFJet_i_closest_tau;
  vector<float> _recoPFJet_dR_closest_tau;

  vector<float> _recoPFJet_CSVsort_e;
  vector<float> _recoPFJet_CSVsort_pt;
  vector<float> _recoPFJet_CSVsort_px;
  vector<float> _recoPFJet_CSVsort_py;
  vector<float> _recoPFJet_CSVsort_pz;
  vector<float> _recoPFJet_CSVsort_eta;
  vector<float> _recoPFJet_CSVsort_phi;
  vector<float> _recoPFJet_CSVsort_CSVscore;
  vector<int> _recoPFJet_CSVsort_Flavour;
  vector<int> _recoPFJet_CSVsort_i_closest_genb;
  vector<float> _recoPFJet_CSVsort_dR_closest_genb;
  vector<int> _recoPFJet_CSVsort_i_closest_gentauh;
  vector<float> _recoPFJet_CSVsort_dR_closest_gentauh;

  int _n_recoPFJet_btag_medium;  //# jets passing CSVM
  int _n_recoPFJet_btag_loose; //# jets passing CSVL
 
  //2 jets with highest CSV score
  vector<float> _recoPFJet_btag_e;
  vector<float> _recoPFJet_btag_pt;
  vector<float> _recoPFJet_btag_px;
  vector<float> _recoPFJet_btag_py;
  vector<float> _recoPFJet_btag_pz;
  vector<float> _recoPFJet_btag_eta;
  vector<float> _recoPFJet_btag_phi;
  vector<float> _recoPFJet_btag_CSVscore;
  vector<int> _recoPFJet_btag_Flavour; 

  //Other jets
  int _n_recoPFJet_untag;
  vector<float> _recoPFJet_untag_e;
  vector<float> _recoPFJet_untag_pt;
  vector<float> _recoPFJet_untag_px;
  vector<float> _recoPFJet_untag_py;
  vector<float> _recoPFJet_untag_pz;
  vector<float> _recoPFJet_untag_eta;
  vector<float> _recoPFJet_untag_phi;
  vector<float> _recoPFJet_untag_CSVscore;
  vector<int> _recoPFJet_untag_Flavour;

  int _n_pair_Wtag_recoPFJet_untag;  //# pair of jets passing W-tag in untagged jets

  //2 jets with invariant mass closest to mW
  float _recoPFJet_untag_best_mW; //invariant mass of the pair
  vector<float> _recoPFJet_untag_Wtag_e;
  vector<float> _recoPFJet_untag_Wtag_pt;
  vector<float> _recoPFJet_untag_Wtag_px;
  vector<float> _recoPFJet_untag_Wtag_py;
  vector<float> _recoPFJet_untag_Wtag_pz;
  vector<float> _recoPFJet_untag_Wtag_eta;
  vector<float> _recoPFJet_untag_Wtag_phi;
  vector<float> _recoPFJet_untag_Wtag_CSVscore;
  vector<int> _recoPFJet_untag_Wtag_Flavour; 

  vector<float> _mtop_had_perm;
  vector<float> _mblep_perm;
  vector<float> _mleptauh_perm;

  float _PFMET;
  float _PFMET_phi;
  float _PFMETx;
  float _PFMETy;

  float _PFMET_cov00;
  float _PFMET_cov01;
  float _PFMET_cov10;
  float _PFMET_cov11;


  //Gen information
  vector<float> _genpart_pt;
  vector<float> _genpart_eta;
  vector<float> _genpart_phi;
  vector<int> _genpart_i_closest_daughter;
  vector<float> _genpart_dR_closest_daughter;

  int _n_genlep;
  int _n_genlep10;
  int _n_genlep20;
  int _n_genlep20_eta21;
  int _n_genlep_fromTop;
  int _n_genlep_fromTau;
  vector<int> _genlep_pdg;
  vector<int> _genlep_charge;
  vector<float> _genlep_e;
  vector<float> _genlep_px;
  vector<float> _genlep_py;
  vector<float> _genlep_pz;
  vector<float> _genlep_pt;
  vector<float> _genlep_eta;
  vector<float> _genlep_phi;
  vector<int> _genlep_flags;  
  vector<int> _genlep_TauMothInd; //-1 if not from tau
  vector<int> _genlep_TopMothInd; //-1 if not from top
  vector<int> _genlep_WMothInd; //-1 if not from top

  int _n_gentauh;
  int _n_gentauh10;
  int _n_gentauh30;
  int _n_gentauh30_eta21;
  int _n_gentauh_fromTop;
  int _n_gentauh_fromTau;
  vector<int> _gentauh_charge;
  vector<float> _gentauh_e;
  vector<float> _gentauh_px;
  vector<float> _gentauh_py;
  vector<float> _gentauh_pz;
  vector<float> _gentauh_pt;
  vector<float> _gentauh_eta;
  vector<float> _gentauh_phi;
  vector<int> _gentauh_flags;  
  vector<int> _gentauh_TauMothInd;
  vector<int> _gentauh_TopMothInd;
  vector<int> _gentauh_WMothInd;

  int _n_gentau;
  int _n_gentau_fromTop;
  int _n_gentau_fromH;
  vector<int> _gentau_decayMode; //0 muon, 1 electron, 2 had
  vector<int> _gentau_charge;
  vector<float> _gentau_e;
  vector<float> _gentau_px;
  vector<float> _gentau_py;
  vector<float> _gentau_pz;
  vector<float> _gentau_pt;
  vector<float> _gentau_eta;
  vector<float> _gentau_phi;
  vector<int> _gentau_flags;  
  vector<int> _gentau_TopMothInd;
  vector<int> _gentau_WMothInd;
  vector<int> _gentau_HMothInd;

  int _n_genH;
  vector<int> _genH_decayMode; //0 mu+tauh, 1 e+tauh, 2 tauh+tauh, 3 mu+mu, 4 e+e, 5 e+mu
  vector<float> _genH_e;
  vector<float> _genH_px;
  vector<float> _genH_py;
  vector<float> _genH_pz;
  vector<float> _genH_pt;
  vector<float> _genH_eta;
  vector<float> _genH_phi;
  vector<int> _genH_flags;  


  int _n_gentop;
  vector<int> _gentop_pdg;
  vector<int> _gentop_decayMode;
  vector<float> _gentop_e;
  vector<float> _gentop_px;
  vector<float> _gentop_py;
  vector<float> _gentop_pz;
  vector<float> _gentop_pt;
  vector<float> _gentop_eta;
  vector<float> _gentop_phi;
  vector<int> _gentop_flags;  


  int _n_genW;
  int _n_genW_fromTop;
  vector<int> _genW_pdg;
  vector<int> _genW_decayMode;
  vector<float> _genW_e;
  vector<float> _genW_px;
  vector<float> _genW_py;
  vector<float> _genW_pz;
  vector<float> _genW_pt;
  vector<float> _genW_eta;
  vector<float> _genW_phi;
  vector<int> _genW_flags;  
  vector<int> _genW_TopMothInd;

  int _n_genb;
  int _n_genb10;
  int _n_genb_fromTop;
  vector<int> _genb_pdg;
  vector<float> _genb_e;
  vector<float> _genb_px;
  vector<float> _genb_py;
  vector<float> _genb_pz;
  vector<float> _genb_pt;
  vector<float> _genb_eta;
  vector<float> _genb_phi;
  vector<int> _genb_flags;  
  vector<int> _genb_TopMothInd;
  vector<int> _genb_WMothInd;

  int _n_genq;
  int _n_genq10;
  int _n_genq_fromTop;
  vector<int> _genq_pdg;
  vector<float> _genq_e;
  vector<float> _genq_px;
  vector<float> _genq_py;
  vector<float> _genq_pz;
  vector<float> _genq_pt;
  vector<float> _genq_eta;
  vector<float> _genq_phi;
  vector<int> _genq_flags;  
  vector<int> _genq_TopMothInd;
  vector<int> _genq_WMothInd;

  int _n_gennu;
  int _n_gennu_fromTop;
  int _n_gennu_fromTau;
  vector<int> _gennu_pdg;
  vector<float> _gennu_e;
  vector<float> _gennu_px;
  vector<float> _gennu_py;
  vector<float> _gennu_pz;
  vector<float> _gennu_pt;
  vector<float> _gennu_eta;
  vector<float> _gennu_phi;
  vector<int> _gennu_flags;  
  vector<int> _gennu_TauMothInd; //-1 if not from tau
  vector<int> _gennu_TopMothInd; //-1 if not from top
  vector<int> _gennu_WMothInd; //-1 if not from W
  
  tree_new->Branch("daughters_pt",&_daughters_pt);
  tree_new->Branch("daughters_eta",&_daughters_eta);
  tree_new->Branch("daughters_phi",&_daughters_phi);
  tree_new->Branch("daughters_dR_closest_jet",&_daughters_dR_closest_jet);

  tree_new->Branch("jets_pt",&_jets_pt);
  tree_new->Branch("jets_eta",&_jets_eta);
  tree_new->Branch("jets_phi",&_jets_phi);

  tree_new->Branch("n_recolep",&_n_recolep,"n_recolep/I");
  tree_new->Branch("recolep_ID",&_recolep_ID);
  tree_new->Branch("recolep_charge",&_recolep_charge);
  tree_new->Branch("recolep_e",&_recolep_e);
  tree_new->Branch("recolep_px",&_recolep_px);
  tree_new->Branch("recolep_py",&_recolep_py);
  tree_new->Branch("recolep_pz",&_recolep_pz);
  tree_new->Branch("recolep_pt",&_recolep_pt);
  tree_new->Branch("recolep_eta",&_recolep_eta);
  tree_new->Branch("recolep_phi",&_recolep_phi);
  tree_new->Branch("recolep_leptonMVA",&_recolep_leptonMVA);
  tree_new->Branch("recolep_TopMothInd",&_recolep_TopMothInd);
  tree_new->Branch("recolep_HMothInd",&_recolep_HMothInd);


  tree_new->Branch("n_recomu",&_n_recomu,"n_recomu/I");
  tree_new->Branch("recomu_ID",&_recomu_ID);
  tree_new->Branch("recomu_charge",&_recomu_charge);
  tree_new->Branch("recomu_e",&_recomu_e);
  tree_new->Branch("recomu_px",&_recomu_px);
  tree_new->Branch("recomu_py",&_recomu_py);
  tree_new->Branch("recomu_pz",&_recomu_pz);
  tree_new->Branch("recomu_pt",&_recomu_pt);
  tree_new->Branch("recomu_eta",&_recomu_eta);
  tree_new->Branch("recomu_phi",&_recomu_phi);
  tree_new->Branch("recomu_dxy",&_recomu_dxy);
  tree_new->Branch("recomu_dz",&_recomu_dz);
  tree_new->Branch("recomu_jetNDauChargedMVASel",&_recomu_jetNDauChargedMVASel);
  tree_new->Branch("recomu_miniRelIso",&_recomu_miniRelIso);
  tree_new->Branch("recomu_miniIsoCharged",&_recomu_miniIsoCharged);
  tree_new->Branch("recomu_miniIsoNeutral",&_recomu_miniIsoNeutral);
  tree_new->Branch("recomu_sip3D",&_recomu_sip3D);
  tree_new->Branch("recomu_jetPtRel",&_recomu_jetPtRel);
  tree_new->Branch("recomu_jetCSV",&_recomu_jetCSV);
  tree_new->Branch("recomu_jetPtRatio",&_recomu_jetPtRatio);
  tree_new->Branch("recomu_lepMVA_mvaId",&_recomu_lepMVA_mvaId);
  tree_new->Branch("recomu_leptonMVA",&_recomu_leptonMVA);


  tree_new->Branch("n_recoele",&_n_recoele,"n_recoele/I");
  tree_new->Branch("recoele_ID",&_recoele_ID);
  tree_new->Branch("recoele_charge",&_recoele_charge);
  tree_new->Branch("recoele_e",&_recoele_e);
  tree_new->Branch("recoele_px",&_recoele_px);
  tree_new->Branch("recoele_py",&_recoele_py);
  tree_new->Branch("recoele_pz",&_recoele_pz);
  tree_new->Branch("recoele_pt",&_recoele_pt);
  tree_new->Branch("recoele_eta",&_recoele_eta);
  tree_new->Branch("recoele_phi",&_recoele_phi);
  tree_new->Branch("recoele_dxy",&_recoele_dxy);
  tree_new->Branch("recoele_dz",&_recoele_dz);
  tree_new->Branch("recoele_jetNDauChargedMVASel",&_recoele_jetNDauChargedMVASel);
  tree_new->Branch("recoele_miniRelIso",&_recoele_miniRelIso);
  tree_new->Branch("recoele_miniIsoCharged",&_recoele_miniIsoCharged);
  tree_new->Branch("recoele_miniIsoNeutral",&_recoele_miniIsoNeutral);
  tree_new->Branch("recoele_sip3D",&_recoele_sip3D);
  tree_new->Branch("recoele_jetPtRel",&_recoele_jetPtRel);
  tree_new->Branch("recoele_jetCSV",&_recoele_jetCSV);
  tree_new->Branch("recoele_jetPtRatio",&_recoele_jetPtRatio);
  tree_new->Branch("recoele_lepMVA_mvaId",&_recoele_lepMVA_mvaId);
  tree_new->Branch("recoele_leptonMVA",&_recoele_leptonMVA);

  tree_new->Branch("n_recotauh",&_n_recotauh,"n_recotauh/I");
  tree_new->Branch("recotauh_decayMode",&_recotauh_decayMode);
  tree_new->Branch("recotauh_charge",&_recotauh_charge);
  tree_new->Branch("recotauh_e",&_recotauh_e);
  tree_new->Branch("recotauh_px",&_recotauh_px);
  tree_new->Branch("recotauh_py",&_recotauh_py);
  tree_new->Branch("recotauh_pz",&_recotauh_pz);
  tree_new->Branch("recotauh_pt",&_recotauh_pt);
  tree_new->Branch("recotauh_eta",&_recotauh_eta);
  tree_new->Branch("recotauh_phi",&_recotauh_phi);
  tree_new->Branch("recotauh_dxy",&_recotauh_dxy);
  tree_new->Branch("recotauh_dz",&_recotauh_dz);
  tree_new->Branch("recotauh_iso",&_recotauh_iso);

  tree_new->Branch("recotauh_decayModeFindingOldDMs",&_recotauh_decayModeFindingOldDMs);
  tree_new->Branch("recotauh_decayModeFindingNewDMs",&_recotauh_decayModeFindingNewDMs);
  tree_new->Branch("recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits",&_recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits);
  tree_new->Branch("recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits",&_recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits);
  tree_new->Branch("recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits",&_recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits);
  tree_new->Branch("recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03",&_recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03);
  tree_new->Branch("recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03",&_recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03);
  tree_new->Branch("recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03",&_recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03);
  tree_new->Branch("recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT);
  tree_new->Branch("recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT);
  tree_new->Branch("recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree_new->Branch("recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT",&_recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT);
  tree_new->Branch("recotauh_againstMuonLoose3",&_recotauh_againstMuonLoose3);
  tree_new->Branch("recotauh_againstMuonTight3",&_recotauh_againstMuonTight3);
  tree_new->Branch("recotauh_againstElectronVLooseMVA6",&_recotauh_againstElectronVLooseMVA6);
  tree_new->Branch("recotauh_againstElectronLooseMVA6",&_recotauh_againstElectronLooseMVA6);
  tree_new->Branch("recotauh_againstElectronMediumMVA6",&_recotauh_againstElectronMediumMVA6);
  tree_new->Branch("recotauh_againstElectronTightMVA6",&_recotauh_againstElectronTightMVA6);
  tree_new->Branch("recotauh_againstElectronVTightMVA6",&_recotauh_againstElectronVTightMVA6);

  tree_new->Branch("recotauh_i_closest_genpart",&_recotauh_i_closest_genpart);
  tree_new->Branch("recotauh_dR_closest_genpart",&_recotauh_dR_closest_genpart);

  tree_new->Branch("n_recoPFJet",&_n_recoPFJet,"n_recoPFJet/I");
  tree_new->Branch("recoPFJet_e",&_recoPFJet_e);
  tree_new->Branch("recoPFJet_pt",&_recoPFJet_pt);
  tree_new->Branch("recoPFJet_px",&_recoPFJet_px);
  tree_new->Branch("recoPFJet_py",&_recoPFJet_py);
  tree_new->Branch("recoPFJet_pz",&_recoPFJet_pz);
  tree_new->Branch("recoPFJet_eta",&_recoPFJet_eta);
  tree_new->Branch("recoPFJet_phi",&_recoPFJet_phi);
  tree_new->Branch("recoPFJet_CSVscore",&_recoPFJet_CSVscore);
  tree_new->Branch("recoPFJet_Flavour",&_recoPFJet_Flavour);
  tree_new->Branch("recoPFJet_i_closest_genpart",&_recoPFJet_i_closest_genpart);
  tree_new->Branch("recoPFJet_dR_closest_genpart",&_recoPFJet_dR_closest_genpart);
  tree_new->Branch("recoPFJet_i_2nd_closest_genpart",&_recoPFJet_i_2nd_closest_genpart);
  tree_new->Branch("recoPFJet_dR_2nd_closest_genpart",&_recoPFJet_dR_2nd_closest_genpart);
  tree_new->Branch("recoPFJet_i_closest_lep",&_recoPFJet_i_closest_lep);
  tree_new->Branch("recoPFJet_dR_closest_lep",&_recoPFJet_dR_closest_lep);
  tree_new->Branch("recoPFJet_i_closest_tau",&_recoPFJet_i_closest_tau);
  tree_new->Branch("recoPFJet_dR_closest_tau",&_recoPFJet_dR_closest_tau);
			     
  tree_new->Branch("recoPFJet_CSVsort_e",&_recoPFJet_CSVsort_e);
  tree_new->Branch("recoPFJet_CSVsort_pt",&_recoPFJet_CSVsort_pt);
  tree_new->Branch("recoPFJet_CSVsort_px",&_recoPFJet_CSVsort_px);
  tree_new->Branch("recoPFJet_CSVsort_py",&_recoPFJet_CSVsort_py);
  tree_new->Branch("recoPFJet_CSVsort_pz",&_recoPFJet_CSVsort_pz);
  tree_new->Branch("recoPFJet_CSVsort_eta",&_recoPFJet_CSVsort_eta);
  tree_new->Branch("recoPFJet_CSVsort_phi",&_recoPFJet_CSVsort_phi);
  tree_new->Branch("recoPFJet_CSVsort_CSVscore",&_recoPFJet_CSVsort_CSVscore);
  tree_new->Branch("recoPFJet_CSVsort_Flavour",&_recoPFJet_CSVsort_Flavour);
  tree_new->Branch("recoPFJet_CSVsort_i_closest_genb",&_recoPFJet_CSVsort_i_closest_genb);
  tree_new->Branch("recoPFJet_CSVsort_dR_closest_genb",&_recoPFJet_CSVsort_dR_closest_genb);
  tree_new->Branch("recoPFJet_CSVsort_i_closest_gentauh",&_recoPFJet_CSVsort_i_closest_gentauh);
  tree_new->Branch("recoPFJet_CSVsort_dR_closest_gentauh",&_recoPFJet_CSVsort_dR_closest_gentauh);

  tree_new->Branch("n_recoPFJet_btag_medium",&_n_recoPFJet_btag_medium,"n_recoPFJet_btag_medium/I");
  tree_new->Branch("n_recoPFJet_btag_loose",&_n_recoPFJet_btag_loose,"n_recoPFJet_btag_loose/I");
  tree_new->Branch("recoPFJet_btag_e",&_recoPFJet_btag_e);
  tree_new->Branch("recoPFJet_btag_pt",&_recoPFJet_btag_pt);
  tree_new->Branch("recoPFJet_btag_px",&_recoPFJet_btag_px);
  tree_new->Branch("recoPFJet_btag_py",&_recoPFJet_btag_py);
  tree_new->Branch("recoPFJet_btag_pz",&_recoPFJet_btag_pz);
  tree_new->Branch("recoPFJet_btag_eta",&_recoPFJet_btag_eta);
  tree_new->Branch("recoPFJet_btag_phi",&_recoPFJet_btag_phi);
  tree_new->Branch("recoPFJet_btag_CSVscore",&_recoPFJet_btag_CSVscore);
  tree_new->Branch("recoPFJet_btag_Flavour",&_recoPFJet_btag_Flavour);

  tree_new->Branch("n_recoPFJet_untag",&_n_recoPFJet_untag,"n_recoPFJet_untag/I");
  tree_new->Branch("recoPFJet_untag_e",&_recoPFJet_untag_e);
  tree_new->Branch("recoPFJet_untag_pt",&_recoPFJet_untag_pt);
  tree_new->Branch("recoPFJet_untag_px",&_recoPFJet_untag_px);
  tree_new->Branch("recoPFJet_untag_py",&_recoPFJet_untag_py);
  tree_new->Branch("recoPFJet_untag_pz",&_recoPFJet_untag_pz);
  tree_new->Branch("recoPFJet_untag_eta",&_recoPFJet_untag_eta);
  tree_new->Branch("recoPFJet_untag_phi",&_recoPFJet_untag_phi);
  tree_new->Branch("recoPFJet_untag_CSVscore",&_recoPFJet_untag_CSVscore);
  tree_new->Branch("recoPFJet_untag_Flavour",&_recoPFJet_untag_Flavour);


  tree_new->Branch("n_pair_Wtag_recoPFJet_untag",&_n_pair_Wtag_recoPFJet_untag,"n_pair_Wtag_recoPFJet_untag/I");  

  tree_new->Branch("recoPFJet_untag_best_mW",&_recoPFJet_untag_best_mW,"recoPFJet_untag_best_mW/F");  
  tree_new->Branch("recoPFJet_untag_Wtag_e",&_recoPFJet_untag_Wtag_e);
  tree_new->Branch("recoPFJet_untag_Wtag_pt",&_recoPFJet_untag_Wtag_pt);
  tree_new->Branch("recoPFJet_untag_Wtag_px",&_recoPFJet_untag_Wtag_px);
  tree_new->Branch("recoPFJet_untag_Wtag_py",&_recoPFJet_untag_Wtag_py);
  tree_new->Branch("recoPFJet_untag_Wtag_pz",&_recoPFJet_untag_Wtag_pz);
  tree_new->Branch("recoPFJet_untag_Wtag_eta",&_recoPFJet_untag_Wtag_eta);
  tree_new->Branch("recoPFJet_untag_Wtag_phi",&_recoPFJet_untag_Wtag_phi);
  tree_new->Branch("recoPFJet_untag_Wtag_CSVscore",&_recoPFJet_untag_Wtag_CSVscore);
  tree_new->Branch("recoPFJet_untag_Wtag_Flavour",&_recoPFJet_untag_Wtag_Flavour);

  tree_new->Branch("mtop_had_perm",&_mtop_had_perm);
  tree_new->Branch("mblep_perm",&_mblep_perm);
  tree_new->Branch("mleptauh_perm",&_mleptauh_perm);

  tree_new->Branch("PFMETx",&_PFMETx,"PFMETx/F");
  tree_new->Branch("PFMETy",&_PFMETy,"PFMETy/F");
  tree_new->Branch("PFMET",&_PFMET,"PFMET/F");
  tree_new->Branch("PFMET_phi",&_PFMET_phi,"PFMET_phi/F");

  tree_new->Branch("PFMET_cov00",&_PFMET_cov00,"PFMET_cov00/F");
  tree_new->Branch("PFMET_cov01",&_PFMET_cov01,"PFMET_cov01/F");
  tree_new->Branch("PFMET_cov10",&_PFMET_cov10,"PFMET_cov10/F");
  tree_new->Branch("PFMET_cov11",&_PFMET_cov11,"PFMET_cov11/F");

  tree_new->Branch("genpart_pt",&_genpart_pt);
  tree_new->Branch("genpart_eta",&_genpart_eta);
  tree_new->Branch("genpart_phi",&_genpart_phi);
  tree_new->Branch("genpart_i_closest_daughter",&_genpart_i_closest_daughter);
  tree_new->Branch("genpart_dR_closest_daughter",&_genpart_dR_closest_daughter);

  tree_new->Branch("n_genlep",&_n_genlep,"n_genlep/I");
  tree_new->Branch("n_genlep10",&_n_genlep10,"n_genlep10/I");
  tree_new->Branch("n_genlep20",&_n_genlep20,"n_genlep20/I");
  tree_new->Branch("n_genlep20_eta21",&_n_genlep20_eta21,"n_genlep20_eta21/I");
  tree_new->Branch("n_genlep_fromTop",&_n_genlep_fromTop,"n_genlep_fromTop/I");
  tree_new->Branch("n_genlep_fromTau",&_n_genlep_fromTau,"n_genlep_fromTau/I");
  tree_new->Branch("genlep_pdg",&_genlep_pdg);
  tree_new->Branch("genlep_charge",&_genlep_charge);
  tree_new->Branch("genlep_e",&_genlep_e);
  tree_new->Branch("genlep_px",&_genlep_px);
  tree_new->Branch("genlep_py",&_genlep_py);
  tree_new->Branch("genlep_pz",&_genlep_pz);
  tree_new->Branch("genlep_pt",&_genlep_pt);
  tree_new->Branch("genlep_eta",&_genlep_eta);
  tree_new->Branch("genlep_phi",&_genlep_phi);
  tree_new->Branch("genlep_flags",&_genlep_flags);
  tree_new->Branch("genlep_TauMothInd",&_genlep_TauMothInd);
  tree_new->Branch("genlep_TopMothInd",&_genlep_TopMothInd);
  tree_new->Branch("genlep_WMothInd",&_genlep_WMothInd);

  tree_new->Branch("n_gentauh",&_n_gentauh,"n_gentauh/I");
  tree_new->Branch("n_gentauh10",&_n_gentauh10,"n_gentauh10/I");
  tree_new->Branch("n_gentauh30",&_n_gentauh30,"n_gentauh30/I");
  tree_new->Branch("n_gentauh30_eta21",&_n_gentauh30_eta21,"n_gentauh30_eta21/I");
  tree_new->Branch("n_gentauh_fromTop",&_n_gentauh_fromTop,"n_gentauh_fromTop/I");
  tree_new->Branch("n_gentauh_fromTau",&_n_gentauh_fromTau,"n_gentauh_fromTau/I");
  tree_new->Branch("gentauh_charge",&_gentauh_charge);
  tree_new->Branch("gentauh_e",&_gentauh_e);
  tree_new->Branch("gentauh_px",&_gentauh_px);
  tree_new->Branch("gentauh_py",&_gentauh_py);
  tree_new->Branch("gentauh_pz",&_gentauh_pz);
  tree_new->Branch("gentauh_pt",&_gentauh_pt);
  tree_new->Branch("gentauh_eta",&_gentauh_eta);
  tree_new->Branch("gentauh_phi",&_gentauh_phi);
  tree_new->Branch("gentauh_flags",&_gentauh_flags);
  tree_new->Branch("gentauh_TauMothInd",&_gentauh_TauMothInd);
  tree_new->Branch("gentauh_TopMothInd",&_gentauh_TopMothInd);
  tree_new->Branch("gentauh_WMothInd",&_gentauh_WMothInd);

  tree_new->Branch("n_gentau",&_n_gentau,"n_gentau/I");
  tree_new->Branch("n_gentau_fromTop",&_n_gentau_fromTop,"n_gentau_fromTop/I");
  tree_new->Branch("n_gentau_fromH",&_n_gentau_fromH,"n_gentau_fromH/I");
  tree_new->Branch("gentau_decayMode",&_gentau_decayMode);
  tree_new->Branch("gentau_charge",&_gentau_charge);
  tree_new->Branch("gentau_e",&_gentau_e);
  tree_new->Branch("gentau_px",&_gentau_px);
  tree_new->Branch("gentau_py",&_gentau_py);
  tree_new->Branch("gentau_pz",&_gentau_pz);
  tree_new->Branch("gentau_pt",&_gentau_pt);
  tree_new->Branch("gentau_eta",&_gentau_eta);
  tree_new->Branch("gentau_phi",&_gentau_phi);
  tree_new->Branch("gentau_flags",&_gentau_flags);
  tree_new->Branch("gentau_TopMothInd",&_gentau_TopMothInd);
  tree_new->Branch("gentau_WMothInd",&_gentau_WMothInd);
  tree_new->Branch("gentau_HMothInd",&_gentau_HMothInd);

  tree_new->Branch("n_genH",&_n_genH,"n_genH/I");
  tree_new->Branch("genH_decayMode",&_genH_decayMode);
  tree_new->Branch("genH_e",&_genH_e);
  tree_new->Branch("genH_px",&_genH_px);
  tree_new->Branch("genH_py",&_genH_py);
  tree_new->Branch("genH_pz",&_genH_pz);
  tree_new->Branch("genH_pt",&_genH_pt);
  tree_new->Branch("genH_eta",&_genH_eta);
  tree_new->Branch("genH_phi",&_genH_phi);
  tree_new->Branch("genH_flags",&_genH_flags);

  tree_new->Branch("n_gentop",&_n_gentop,"n_gentop/I");
  tree_new->Branch("gentop_pdg",&_gentop_pdg);
  tree_new->Branch("gentop_decayMode",&_gentop_decayMode);
  tree_new->Branch("gentop_e",&_gentop_e);
  tree_new->Branch("gentop_px",&_gentop_px);
  tree_new->Branch("gentop_py",&_gentop_py);
  tree_new->Branch("gentop_pz",&_gentop_pz);
  tree_new->Branch("gentop_pt",&_gentop_pt);
  tree_new->Branch("gentop_eta",&_gentop_eta);
  tree_new->Branch("gentop_phi",&_gentop_phi);
  tree_new->Branch("gentop_flags",&_gentop_flags);

  tree_new->Branch("n_genW",&_n_genW,"n_genW/I");
  tree_new->Branch("n_genW_fromTop",&_n_genW_fromTop,"n_genW_fromTop/I");
  tree_new->Branch("genW_pdg",&_genW_pdg);
  tree_new->Branch("genW_decayMode",&_genW_decayMode);
  tree_new->Branch("genW_e",&_genW_e);
  tree_new->Branch("genW_px",&_genW_px);
  tree_new->Branch("genW_py",&_genW_py);
  tree_new->Branch("genW_pz",&_genW_pz);
  tree_new->Branch("genW_pt",&_genW_pt);
  tree_new->Branch("genW_eta",&_genW_eta);
  tree_new->Branch("genW_phi",&_genW_phi);
  tree_new->Branch("genW_flags",&_genW_flags);
  tree_new->Branch("genW_TopMothInd",&_genW_TopMothInd);

  tree_new->Branch("n_genb",&_n_genb,"n_genb/I");
  tree_new->Branch("n_genb10",&_n_genb10,"n_genb10/I");
  tree_new->Branch("n_genb_fromTop",&_n_genb_fromTop,"n_genb_fromTop/I");
  tree_new->Branch("genb_pdg",&_genb_pdg);
  tree_new->Branch("genb_e",&_genb_e);
  tree_new->Branch("genb_px",&_genb_px);
  tree_new->Branch("genb_py",&_genb_py);
  tree_new->Branch("genb_pz",&_genb_pz);
  tree_new->Branch("genb_pt",&_genb_pt);
  tree_new->Branch("genb_eta",&_genb_eta);
  tree_new->Branch("genb_phi",&_genb_phi);
  tree_new->Branch("genb_flags",&_genb_flags);
  tree_new->Branch("genb_TopMothInd",&_genb_TopMothInd);
  tree_new->Branch("genb_WMothInd",&_genb_WMothInd);

  tree_new->Branch("n_genq",&_n_genq,"n_genq/I");
  tree_new->Branch("n_genq10",&_n_genq10,"n_genq10/I");
  tree_new->Branch("n_genq_fromTop",&_n_genq_fromTop,"n_genq_fromTop/I");
  tree_new->Branch("genq_pdg",&_genq_pdg);
  tree_new->Branch("genq_e",&_genq_e);
  tree_new->Branch("genq_px",&_genq_px);
  tree_new->Branch("genq_py",&_genq_py);
  tree_new->Branch("genq_pz",&_genq_pz);
  tree_new->Branch("genq_pt",&_genq_pt);
  tree_new->Branch("genq_eta",&_genq_eta);
  tree_new->Branch("genq_phi",&_genq_phi);
  tree_new->Branch("genq_flags",&_genq_flags);
  tree_new->Branch("genq_TopMothInd",&_genq_TopMothInd);
  tree_new->Branch("genq_WMothInd",&_genq_WMothInd);

  tree_new->Branch("n_gennu",&_n_gennu,"n_gennu/I");
  tree_new->Branch("n_gennu_fromTop",&_n_gennu_fromTop,"n_gennu_fromTop/I");
  tree_new->Branch("n_gennu_fromTau",&_n_gennu_fromTau,"n_gennu_fromTau/I");
  tree_new->Branch("gennu_pdg",&_gennu_pdg);
  tree_new->Branch("gennu_e",&_gennu_e);
  tree_new->Branch("gennu_px",&_gennu_px);
  tree_new->Branch("gennu_py",&_gennu_py);
  tree_new->Branch("gennu_pz",&_gennu_pz);
  tree_new->Branch("gennu_pt",&_gennu_pt);
  tree_new->Branch("gennu_eta",&_gennu_eta);
  tree_new->Branch("gennu_phi",&_gennu_phi);
  tree_new->Branch("gennu_flags",&_gennu_flags);
  tree_new->Branch("gennu_TauMothInd",&_gennu_TauMothInd);
  tree_new->Branch("gennu_TopMothInd",&_gennu_TopMothInd);
  tree_new->Branch("gennu_WMothInd",&_gennu_WMothInd);


  //Old branches used
  vector<float> *_jets_e;
  vector<float> *_jets_px;
  vector<float> *_jets_py;
  vector<float> *_jets_pz;
  vector<int> *_jets_Flavour;
  vector<float> *_jets_PUJetID;
  vector<int> *_PFjetID;
  vector<float> *_bCSVscore;

  vector<float> *_dxy;
  vector<float> *_dz;
  vector<float> *_dxy_innerTrack;
  vector<float> *_dz_innerTrack;
  vector<float> *_SIP;
  vector<int> *_daughters_muonID;
  vector<int> *_daughters_eleMissingHits;
  vector<bool> *_daughters_passConversionVeto;

  vector<float> *_daughters_e;
  vector<float> *_daughters_px;
  vector<float> *_daughters_py;
  vector<float> *_daughters_pz;
  vector<int> *_PDGIdDaughters;
  vector<int> *_decayMode;
  vector<float> *_combreliso;
  vector<float> *_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits;
  vector<int> *_daughters_decayModeFindingOldDMs;
  vector<int> *_daughters_decayModeFindingNewDMs;
  //vector<int> *_daughters_againstMuonTight3;
  //vector<int> *_daughters_againstElectronVLooseMVA5;
  vector<Long64_t> *_tauID;

  vector<int> *_daughters_jetNDauChargedMVASel;
  vector<float> *_daughters_miniRelIsoCharged;
  vector<float> *_daughters_miniRelIsoNeutral;
  vector<float> *_daughters_jetPtRel;
  vector<float> *_daughters_jetPtRatio;
  vector<float> *_daughters_jetBTagCSV;
  vector<float> *_daughters_lepMVA_mvaId;

  
  vector<float> *_METx_vect;
  vector<float> *_METy_vect;

  vector<float> *_MET_cov00_vect;
  vector<float> *_MET_cov01_vect;
  vector<float> *_MET_cov10_vect;
  vector<float> *_MET_cov11_vect;

  vector<float> *_genpart_px;
  vector<float> *_genpart_py;
  vector<float> *_genpart_pz;
  vector<float> *_genpart_e;
  vector<int> *_genpart_pdg;
  vector<int> *_genpart_HMothInd;
  vector<int> *_genpart_TopMothInd;
  vector<int> *_genpart_WMothInd;
  vector<int> *_genpart_bMothInd;
  vector<int> *_genpart_TauMothInd;
  vector<int> *_genpart_TopDecayMode;
  vector<int> *_genpart_WDecayMode;
  vector<int> *_genpart_HZDecayMode;
  vector<int> *_genpart_TauGenDecayMode;
  vector<int> *_genpart_flags;

  tree->SetBranchAddress("jets_px",&_jets_px);
  tree->SetBranchAddress("jets_py",&_jets_py);
  tree->SetBranchAddress("jets_pz",&_jets_pz);
  tree->SetBranchAddress("jets_e",&_jets_e);
  tree->SetBranchAddress("jets_Flavour",&_jets_Flavour);
  tree->SetBranchAddress("jets_PUJetID",&_jets_PUJetID);
  tree->SetBranchAddress("PFjetID",&_PFjetID);
  tree->SetBranchAddress("bCSVscore",&_bCSVscore);

  tree->SetBranchAddress("dxy",&_dxy);
  tree->SetBranchAddress("dz",&_dz);
  tree->SetBranchAddress("dxy_innerTrack",&_dxy_innerTrack);
  tree->SetBranchAddress("dz_innerTrack",&_dz_innerTrack);
  tree->SetBranchAddress("SIP",&_SIP);
  tree->SetBranchAddress("daughters_muonID",&_daughters_muonID);
  tree->SetBranchAddress("daughters_eleMissingHits",&_daughters_eleMissingHits);
  tree->SetBranchAddress("daughters_passConversionVeto",&_daughters_passConversionVeto);

  tree->SetBranchAddress("daughters_px",&_daughters_px);
  tree->SetBranchAddress("daughters_py",&_daughters_py);
  tree->SetBranchAddress("daughters_pz",&_daughters_pz);
  tree->SetBranchAddress("daughters_e",&_daughters_e);
  tree->SetBranchAddress("PDGIdDaughters",&_PDGIdDaughters);
  tree->SetBranchAddress("decayMode",&_decayMode);
  tree->SetBranchAddress("combreliso",&_combreliso);
  tree->SetBranchAddress("daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits",&_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits);
  tree->SetBranchAddress("daughters_decayModeFindingOldDMs",&_daughters_decayModeFindingOldDMs);
  tree->SetBranchAddress("daughters_decayModeFindingNewDMs",&_daughters_decayModeFindingNewDMs);
  //tree->SetBranchAddress("daughters_againstMuonTight3",&_daughters_againstMuonTight3);
  //tree->SetBranchAddress("daughters_againstElectronVLooseMVA5",&_daughters_againstElectronVLooseMVA5);
  tree->SetBranchAddress("tauID",&_tauID);

  tree->SetBranchAddress("daughters_jetNDauChargedMVASel",&_daughters_jetNDauChargedMVASel);
  tree->SetBranchAddress("daughters_miniRelIsoCharged",&_daughters_miniRelIsoCharged);
  tree->SetBranchAddress("daughters_miniRelIsoNeutral",&_daughters_miniRelIsoNeutral);
  tree->SetBranchAddress("daughters_jetPtRel",&_daughters_jetPtRel);
  tree->SetBranchAddress("daughters_jetPtRatio",&_daughters_jetPtRatio);
  tree->SetBranchAddress("daughters_jetBTagCSV",&_daughters_jetBTagCSV);
  tree->SetBranchAddress("daughters_lepMVA_mvaId",&_daughters_lepMVA_mvaId);

  tree->SetBranchAddress("METx",&_METx_vect);
  tree->SetBranchAddress("METy",&_METy_vect);
  tree->SetBranchAddress("MET_cov00",&_MET_cov00_vect);
  tree->SetBranchAddress("MET_cov01",&_MET_cov01_vect);
  tree->SetBranchAddress("MET_cov10",&_MET_cov10_vect);
  tree->SetBranchAddress("MET_cov11",&_MET_cov11_vect);

  tree->SetBranchAddress("genpart_px",&_genpart_px);
  tree->SetBranchAddress("genpart_py",&_genpart_py);
  tree->SetBranchAddress("genpart_pz",&_genpart_pz);
  tree->SetBranchAddress("genpart_e",&_genpart_e);
  tree->SetBranchAddress("genpart_pdg",&_genpart_pdg);
  tree->SetBranchAddress("genpart_HMothInd",&_genpart_HMothInd);
  tree->SetBranchAddress("genpart_TopMothInd",&_genpart_TopMothInd);
  tree->SetBranchAddress("genpart_WMothInd",&_genpart_WMothInd);  
  tree->SetBranchAddress("genpart_bMothInd",&_genpart_bMothInd);    
  tree->SetBranchAddress("genpart_TauMothInd",&_genpart_TauMothInd);
  tree->SetBranchAddress("genpart_TopDecayMode",&_genpart_TopDecayMode);
  tree->SetBranchAddress("genpart_WDecayMode",&_genpart_WDecayMode);
  tree->SetBranchAddress("genpart_HZDecayMode",&_genpart_HZDecayMode);
  tree->SetBranchAddress("genpart_TauGenDecayMode",&_genpart_TauGenDecayMode);
  tree->SetBranchAddress("genpart_flags",&_genpart_flags);
  


  TMVA::Reader* mu_reader = BookLeptonMVAReaderMoriond16("lepMVA_weights", "/mu_BDTG.weights.xml", "mu");
  TMVA::Reader* ele_reader = BookLeptonMVAReaderMoriond16("lepMVA_weights", "/el_BDTG.weights.xml", "ele");



  //nentries=15;
  int skip_entries = 0;

  if(split>0){
    nentries/=split;
    skip_entries=(i_split-1)*nentries;    
  }

  cout<<"nentries="<<nentries<<endl;

  for (int i=skip_entries;i<skip_entries+nentries;i++) {
    
    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _daughters_pt.clear();
    _daughters_eta.clear();
    _daughters_phi.clear();
    _daughters_dR_closest_jet.clear();

    _jets_pt.clear();
    _jets_eta.clear();
    _jets_phi.clear();

    _n_recolep = 0;
    _recolep_ID.clear();
    _recolep_charge.clear();
    _recolep_e.clear();
    _recolep_px.clear();
    _recolep_py.clear();
    _recolep_pz.clear();
    _recolep_pt.clear();
    _recolep_eta.clear();
    _recolep_phi.clear();
    _recolep_leptonMVA.clear();
    _recolep_TopMothInd.clear();
    _recolep_HMothInd.clear();


    _n_recomu = 0;
    _recomu_ID.clear();
    _recomu_charge.clear();
    _recomu_e.clear();
    _recomu_px.clear();
    _recomu_py.clear();
    _recomu_pz.clear();
    _recomu_pt.clear();
    _recomu_eta.clear();
    _recomu_phi.clear();
    _recomu_dxy.clear();
    _recomu_dz.clear();
    _recomu_jetNDauChargedMVASel.clear();
    _recomu_miniRelIso.clear();
    _recomu_miniIsoCharged.clear();
    _recomu_miniIsoNeutral.clear();
    _recomu_sip3D.clear();
    _recomu_jetPtRel.clear();
    _recomu_jetCSV.clear();
    _recomu_jetPtRatio.clear();
    _recomu_lepMVA_mvaId.clear();
    _recomu_leptonMVA.clear();


    _n_recoele = 0;
    _recoele_ID.clear();
    _recoele_charge.clear();
    _recoele_e.clear();
    _recoele_px.clear();
    _recoele_py.clear();
    _recoele_pz.clear();
    _recoele_pt.clear();
    _recoele_eta.clear();
    _recoele_phi.clear();
    _recoele_dxy.clear();
    _recoele_dz.clear();
    _recoele_jetNDauChargedMVASel.clear();
    _recoele_miniRelIso.clear();
    _recoele_miniIsoCharged.clear();
    _recoele_miniIsoNeutral.clear();
    _recoele_sip3D.clear();
    _recoele_jetPtRel.clear();
    _recoele_jetCSV.clear();
    _recoele_jetPtRatio.clear();
    _recoele_lepMVA_mvaId.clear();
    _recoele_leptonMVA.clear();
 
    _n_recotauh = 0;
    _recotauh_charge.clear();
    _recotauh_decayMode.clear();
    _recotauh_e.clear();
    _recotauh_px.clear();
    _recotauh_py.clear();
    _recotauh_pz.clear();
    _recotauh_pt.clear();
    _recotauh_eta.clear();
    _recotauh_phi.clear();
    _recotauh_dxy.clear();
    _recotauh_dz.clear();
    _recotauh_iso.clear();

    _recotauh_decayModeFindingOldDMs.clear();
    _recotauh_decayModeFindingNewDMs.clear();
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits.clear();
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits.clear();
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits.clear();
    _recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03.clear();
    _recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03.clear();
    _recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03.clear();
    _recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT.clear();
    _recotauh_againstMuonLoose3.clear();
    _recotauh_againstMuonTight3.clear();
    _recotauh_againstElectronVLooseMVA6.clear();
    _recotauh_againstElectronLooseMVA6.clear();
    _recotauh_againstElectronMediumMVA6.clear();
    _recotauh_againstElectronTightMVA6.clear();
    _recotauh_againstElectronVTightMVA6.clear();

    _recotauh_i_closest_genpart.clear();
    _recotauh_dR_closest_genpart.clear();

    _n_recoPFJet = 0;
    _recoPFJet_e.clear();
    _recoPFJet_pt.clear();
    _recoPFJet_px.clear();
    _recoPFJet_py.clear();
    _recoPFJet_pz.clear();
    _recoPFJet_eta.clear();
    _recoPFJet_phi.clear();
    _recoPFJet_CSVscore.clear();    
    _recoPFJet_Flavour.clear(); 
    _recoPFJet_i_closest_genpart.clear();
    _recoPFJet_dR_closest_genpart.clear();
    _recoPFJet_i_2nd_closest_genpart.clear();
    _recoPFJet_dR_2nd_closest_genpart.clear();
    _recoPFJet_i_closest_lep.clear();
    _recoPFJet_dR_closest_lep.clear();
    _recoPFJet_i_closest_tau.clear();
    _recoPFJet_dR_closest_tau.clear();

    _recoPFJet_CSVsort_e.clear();
    _recoPFJet_CSVsort_pt.clear();
    _recoPFJet_CSVsort_px.clear();
    _recoPFJet_CSVsort_py.clear();
    _recoPFJet_CSVsort_pz.clear();
    _recoPFJet_CSVsort_eta.clear();
    _recoPFJet_CSVsort_phi.clear();
    _recoPFJet_CSVsort_CSVscore.clear();    
    _recoPFJet_CSVsort_Flavour.clear();   
    _recoPFJet_CSVsort_i_closest_genb.clear();
    _recoPFJet_CSVsort_dR_closest_genb.clear(); 
    _recoPFJet_CSVsort_i_closest_gentauh.clear();
    _recoPFJet_CSVsort_dR_closest_gentauh.clear(); 

    _n_recoPFJet_btag_medium = 0;
    _n_recoPFJet_btag_loose = 0;
    _recoPFJet_btag_e.clear();
    _recoPFJet_btag_pt.clear();
    _recoPFJet_btag_px.clear();
    _recoPFJet_btag_py.clear();
    _recoPFJet_btag_pz.clear();
    _recoPFJet_btag_eta.clear();
    _recoPFJet_btag_phi.clear();
    _recoPFJet_btag_CSVscore.clear();    
    _recoPFJet_btag_Flavour.clear();    

    _n_recoPFJet_untag = 0;
    _recoPFJet_untag_e.clear();
    _recoPFJet_untag_pt.clear();
    _recoPFJet_untag_px.clear();
    _recoPFJet_untag_py.clear();
    _recoPFJet_untag_pz.clear();
    _recoPFJet_untag_eta.clear();
    _recoPFJet_untag_phi.clear();
    _recoPFJet_untag_CSVscore.clear();    
    _recoPFJet_untag_Flavour.clear();

    _n_pair_Wtag_recoPFJet_untag = 0;
    _recoPFJet_untag_best_mW = 0;
    _recoPFJet_untag_Wtag_e.clear();
    _recoPFJet_untag_Wtag_pt.clear();
    _recoPFJet_untag_Wtag_px.clear();
    _recoPFJet_untag_Wtag_py.clear();
    _recoPFJet_untag_Wtag_pz.clear();
    _recoPFJet_untag_Wtag_eta.clear();
    _recoPFJet_untag_Wtag_phi.clear();
    _recoPFJet_untag_Wtag_CSVscore.clear();    
    _recoPFJet_untag_Wtag_Flavour.clear();    

    _mtop_had_perm.clear();
    _mblep_perm.clear();
    _mleptauh_perm.clear();

    _PFMETx = 0;
    _PFMETy = 0;
    _PFMET = 0;
    _PFMET_phi = 0;

    _PFMET_cov00 = 0;
    _PFMET_cov01 = 0;
    _PFMET_cov10 = 0;
    _PFMET_cov11 = 0;

    _genpart_pt.clear();
    _genpart_eta.clear();
    _genpart_phi.clear();
    _genpart_i_closest_daughter.clear();
    _genpart_dR_closest_daughter.clear();

    _n_genlep = 0;
    _n_genlep10 = 0;
    _n_genlep20 = 0;
    _n_genlep20_eta21 = 0;
    _n_genlep_fromTop = 0;
    _n_genlep_fromTau = 0;
    _genlep_pdg.clear();
    _genlep_charge.clear();
    _genlep_e.clear();
    _genlep_px.clear();
    _genlep_py.clear();
    _genlep_pz.clear();
    _genlep_pt.clear();
    _genlep_eta.clear();
    _genlep_phi.clear();
    _genlep_flags.clear();
    _genlep_TauMothInd.clear();
    _genlep_TopMothInd.clear();
    _genlep_WMothInd.clear();

    _n_gentauh = 0;
    _n_gentauh10 = 0;
    _n_gentauh30 = 0;
    _n_gentauh30_eta21 = 0;
    _n_gentauh_fromTop = 0;
    _n_gentauh_fromTau = 0;
    _gentauh_charge.clear();
    _gentauh_e.clear();
    _gentauh_px.clear();
    _gentauh_py.clear();
    _gentauh_pz.clear();
    _gentauh_pt.clear();
    _gentauh_eta.clear();
    _gentauh_phi.clear();
    _gentauh_flags.clear();
    _gentauh_TauMothInd.clear();
    _gentauh_TopMothInd.clear();
    _gentauh_WMothInd.clear();

    _n_gentau = 0;
    _n_gentau_fromTop = 0;
    _n_gentau_fromH = 0;
    _gentau_decayMode.clear();
    _gentau_charge.clear();
    _gentau_e.clear();
    _gentau_px.clear();
    _gentau_py.clear();
    _gentau_pz.clear();
    _gentau_pt.clear();
    _gentau_eta.clear();
    _gentau_phi.clear();
    _gentau_flags.clear();
    _gentau_TopMothInd.clear();
    _gentau_WMothInd.clear();
    _gentau_HMothInd.clear();

    _n_genH = 0;
    _genH_decayMode.clear();
    _genH_e.clear();
    _genH_px.clear();
    _genH_py.clear();
    _genH_pz.clear();
    _genH_pt.clear();
    _genH_eta.clear();
    _genH_phi.clear();
    _genH_flags.clear();

    _n_gentop = 0;
    _gentop_pdg.clear();
    _gentop_decayMode.clear();
    _gentop_e.clear();
    _gentop_px.clear();
    _gentop_py.clear();
    _gentop_pz.clear();
    _gentop_pt.clear();
    _gentop_eta.clear();
    _gentop_phi.clear();
    _gentop_flags.clear();

    _n_genW = 0;
    _n_genW_fromTop = 0;
    _genW_pdg.clear();
    _genW_decayMode.clear();
    _genW_e.clear();
    _genW_px.clear();
    _genW_py.clear();
    _genW_pz.clear();
    _genW_pt.clear();
    _genW_eta.clear();
    _genW_phi.clear();
    _genW_flags.clear();
    _genW_TopMothInd.clear();

    _n_genb = 0;
    _n_genb10 = 0;
    _n_genb_fromTop = 0;
    _genb_pdg.clear();
    _genb_e.clear();
    _genb_px.clear();
    _genb_py.clear();
    _genb_pz.clear();
    _genb_pt.clear();
    _genb_eta.clear();
    _genb_phi.clear();
    _genb_flags.clear();
    _genb_TopMothInd.clear();
    _genb_WMothInd.clear();

    _n_genq = 0;
    _n_genq10 = 0;
    _n_genq_fromTop = 0;
    _genq_pdg.clear();
    _genq_e.clear();
    _genq_px.clear();
    _genq_py.clear();
    _genq_pz.clear();
    _genq_pt.clear();
    _genq_eta.clear();
    _genq_phi.clear();
    _genq_flags.clear();
    _genq_TopMothInd.clear();
    _genq_WMothInd.clear();

    _n_gennu = 0;
    _n_gennu_fromTop = 0;
    _n_gennu_fromTau = 0;
    _gennu_pdg.clear();
    _gennu_e.clear();
    _gennu_px.clear();
    _gennu_py.clear();
    _gennu_pz.clear();
    _gennu_pt.clear();
    _gennu_eta.clear();
    _gennu_phi.clear();
    _gennu_flags.clear();
    _gennu_TauMothInd.clear();
    _gennu_TopMothInd.clear();
    _gennu_WMothInd.clear();


    _jets_e = 0;
    _jets_px = 0;
    _jets_py = 0;
    _jets_pz = 0;
    _jets_Flavour = 0;
    _jets_PUJetID = 0;
    _PFjetID = 0;
    _bCSVscore = 0;

    _dxy = 0;
    _dz = 0;
    _dxy_innerTrack = 0;
    _dz_innerTrack = 0;
    _SIP = 0;
    _daughters_muonID = 0;
    _daughters_eleMissingHits = 0;
    _daughters_passConversionVeto = 0;

    _daughters_e = 0;
    _daughters_px = 0;
    _daughters_py = 0;
    _daughters_pz = 0;
    _PDGIdDaughters = 0;
    _decayMode = 0;
    _combreliso = 0;
    _daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits = 0;
    _daughters_decayModeFindingOldDMs = 0;
    _daughters_decayModeFindingNewDMs = 0;
    //_daughters_againstMuonTight3 = 0;
    //_daughters_againstElectronVLooseMVA5 = 0;
    _tauID = 0;

    _daughters_jetNDauChargedMVASel = 0;
    _daughters_miniRelIsoCharged = 0;
    _daughters_miniRelIsoNeutral = 0;
    _daughters_jetPtRel = 0;
    _daughters_jetPtRatio = 0;
    _daughters_jetBTagCSV = 0;
    _daughters_lepMVA_mvaId = 0;

    _METx_vect = 0;
    _METy_vect = 0;
    _MET_cov00_vect = 0;
    _MET_cov01_vect = 0;
    _MET_cov10_vect = 0;
    _MET_cov11_vect = 0;

    _genpart_px = 0;
    _genpart_py = 0;
    _genpart_pz = 0;
    _genpart_e = 0;
    _genpart_pdg = 0;
    _genpart_HMothInd = 0;
    _genpart_TopMothInd = 0;
    _genpart_WMothInd = 0;
    _genpart_bMothInd = 0;
    _genpart_TauMothInd = 0;
    _genpart_HZDecayMode = 0;
    _genpart_TopDecayMode = 0;
    _genpart_WDecayMode = 0;
    _genpart_TauGenDecayMode = 0;
    _genpart_flags = 0;

    tree->GetEntry(i);

    
    ///Leptons   
    
    vector< pair<int,TLorentzVector> > reco_leptons;
    vector< pair<int,TLorentzVector> > reco_mus;
    vector< pair<int,TLorentzVector> > reco_eles;

   	
    for(unsigned int i_daughter=0; i_daughter<(*_daughters_e).size(); i_daughter++){
      int PDGId=(*_PDGIdDaughters)[i_daughter];
      TLorentzVector daughter ( (*_daughters_px)[i_daughter] , (*_daughters_py)[i_daughter] , (*_daughters_pz)[i_daughter] , (*_daughters_e)[i_daughter] );
      
      pair<int,TLorentzVector> daughter_pair = make_pair(i_daughter,daughter);
     
      _daughters_pt.push_back(daughter.Pt());
      _daughters_eta.push_back(daughter.Eta());
      _daughters_phi.push_back(daughter.Phi());      


      float dR_min=-1;
      for(unsigned int i_jet=0; i_jet<(*_jets_e).size(); i_jet++){
	TLorentzVector jet( (*_jets_px)[i_jet] , (*_jets_py)[i_jet] , (*_jets_pz)[i_jet] , (*_jets_e)[i_jet] );
	float dR = jet.DeltaR(daughter);
	if(dR_min<0 || dR<dR_min)
	  dR_min = dR;
      }
      _daughters_dR_closest_jet.push_back(dR_min);

      
      if( fabs(PDGId)==13 ){

	float dxy = (*_dxy_innerTrack)[i_daughter];
	float dz = (*_dz_innerTrack)[i_daughter];
	float miniRelIsoCharged = (*_daughters_miniRelIsoCharged)[i_daughter];
	float miniRelIsoNeutral = (*_daughters_miniRelIsoNeutral)[i_daughter];
	float miniRelIso = miniRelIsoCharged + miniRelIsoNeutral;
	float sip = (*_SIP)[i_daughter];
	bool looseID = (*_daughters_muonID)[i_daughter] & 1;

	if(daughter.Pt()>5 && fabs(daughter.Eta())<2.4 && fabs(dxy)<=0.05 && fabs(dz)<0.1 && miniRelIso<0.4 && sip < 8 && looseID){
	  reco_mus.push_back(daughter_pair);
	  reco_leptons.push_back(daughter_pair);
	}
      }

      

    }




    for(unsigned int i_daughter=0; i_daughter<(*_daughters_e).size(); i_daughter++){
      int PDGId=(*_PDGIdDaughters)[i_daughter];
      TLorentzVector daughter ( (*_daughters_px)[i_daughter] , (*_daughters_py)[i_daughter] , (*_daughters_pz)[i_daughter] , (*_daughters_e)[i_daughter] );
      
      pair<int,TLorentzVector> daughter_pair = make_pair(i_daughter,daughter);

      if( fabs(PDGId)==11 ){

	float dxy = (*_dxy)[i_daughter];
	float dz = (*_dz)[i_daughter];
	float miniRelIsoCharged = (*_daughters_miniRelIsoCharged)[i_daughter];
	float miniRelIsoNeutral = (*_daughters_miniRelIsoNeutral)[i_daughter];
	float miniRelIso = miniRelIsoCharged + miniRelIsoNeutral;
	float sip = (*_SIP)[i_daughter];
	
	float eleMVAnt = (*_daughters_lepMVA_mvaId)[i_daughter];
	bool VLooseIdEmuWP = false;
	if(fabs(daughter.Eta())<0.8)
	  VLooseIdEmuWP = (eleMVAnt>-0.7);
	else if(fabs(daughter.Eta())<1.479)
	  VLooseIdEmuWP = (eleMVAnt>-0.83);
	else
	  VLooseIdEmuWP = (eleMVAnt>-0.92);
	
	int eleMissingHits = (*_daughters_eleMissingHits)[i_daughter];
	bool passConversionVeto = (*_daughters_passConversionVeto)[i_daughter];
	
	if(daughter.Pt()>7 && fabs(daughter.Eta())<2.5 && fabs(dxy)<=0.05 && fabs(dz)<0.1 && miniRelIso<0.4 && sip < 8 && VLooseIdEmuWP && eleMissingHits<=1 && passConversionVeto){

	  bool dR_veto=false;
	
	  for(unsigned int i_mu=0; i_mu<reco_mus.size(); i_mu++){

	    TLorentzVector mu=reco_mus[i_mu].second;
	    float dR_ele_mu=mu.DeltaR(daughter);
	    if(dR_ele_mu<0.05){
	      dR_veto=true;
	      break;
	    }
	  }

	  if(dR_veto)
	    continue;

	  reco_eles.push_back(daughter_pair);
	  reco_leptons.push_back(daughter_pair);

	
	}

      }

    }


    sort(reco_leptons.begin(), reco_leptons.end(), pT_comparison_pairs);
    sort(reco_mus.begin(), reco_mus.end(), pT_comparison_pairs);
    sort(reco_eles.begin(), reco_eles.end(), pT_comparison_pairs);
       
    _n_recolep = reco_leptons.size();

    for(unsigned int i_lepton=0; i_lepton<reco_leptons.size(); i_lepton++){
      
      int i_daughter=reco_leptons[i_lepton].first;
      TLorentzVector lepton=reco_leptons[i_lepton].second;

      _recolep_ID.push_back( (*_PDGIdDaughters)[i_daughter] );
      _recolep_charge.push_back( (*_PDGIdDaughters)[i_daughter] > 0 ? -1 : 1 );
      _recolep_e.push_back( lepton.E() );
      _recolep_px.push_back( lepton.Px() );
      _recolep_py.push_back( lepton.Py() );
      _recolep_pz.push_back( lepton.Pz() );
      _recolep_pt.push_back( lepton.Pt() );
      _recolep_eta.push_back( lepton.Eta() );
      _recolep_phi.push_back( lepton.Phi() );
      
      lepMVA_pt = _recolep_pt[i_lepton];
      lepMVA_eta = _recolep_eta[i_lepton];
      lepMVA_jetNDauChargedMVASel = (*_daughters_jetNDauChargedMVASel)[i_daughter];
      lepMVA_miniRelIsoCharged = (*_daughters_miniRelIsoCharged)[i_daughter];
      lepMVA_miniRelIsoNeutral = (*_daughters_miniRelIsoNeutral)[i_daughter];
      lepMVA_jetPtRelv2 =  (*_daughters_jetPtRel)[i_daughter]; 
      lepMVA_jetPtRatio = std::min((*_daughters_jetPtRatio)[i_daughter],float(1.5));      
      lepMVA_jetBTagCSV = std::max((*_daughters_jetBTagCSV)[i_daughter],float(0.));
      lepMVA_sip3d = (*_SIP)[i_daughter];
      
      if(fabs(_recolep_ID[i_lepton])==13){
	lepMVA_dxy = log(fabs( (*_dxy_innerTrack)[i_daughter] ));
	lepMVA_dz = log(fabs( (*_dz_innerTrack)[i_daughter] ));
      }
      else if(fabs(_recolep_ID[i_lepton])==11){
	lepMVA_dxy = log(fabs( (*_dxy)[i_daughter] ));
	lepMVA_dz = log(fabs( (*_dz)[i_daughter] ));
      }

      lepMVA_mvaId = (*_daughters_lepMVA_mvaId)[i_daughter];

      if(fabs(_recolep_ID[i_lepton])==13)
	_recolep_leptonMVA.push_back( mu_reader->EvaluateMVA("BDTG method") );
      else if(fabs(_recolep_ID[i_lepton])==11)
	_recolep_leptonMVA.push_back( ele_reader->EvaluateMVA("BDTG method") );

      
    }


    _n_recomu = reco_mus.size();

    for(unsigned int i_mu=0; i_mu<reco_mus.size(); i_mu++){
      
      int i_daughter=reco_mus[i_mu].first;
      TLorentzVector muon=reco_mus[i_mu].second;

      _recomu_ID.push_back( (*_PDGIdDaughters)[i_daughter] );
      _recomu_charge.push_back( (*_PDGIdDaughters)[i_daughter] > 0 ? -1 : 1 );
      _recomu_e.push_back( muon.E() );
      _recomu_px.push_back( muon.Px() );
      _recomu_py.push_back( muon.Py() );
      _recomu_pz.push_back( muon.Pz() );
      _recomu_pt.push_back( muon.Pt() );
      _recomu_eta.push_back( muon.Eta() );
      _recomu_phi.push_back( muon.Phi() );

      _recomu_dxy.push_back( (*_dxy_innerTrack)[i_daughter] );
      _recomu_dz.push_back( (*_dz_innerTrack)[i_daughter] );
      _recomu_jetNDauChargedMVASel.push_back( (*_daughters_jetNDauChargedMVASel)[i_daughter] );
      _recomu_miniRelIso.push_back( (*_daughters_miniRelIsoCharged)[i_daughter] + (*_daughters_miniRelIsoNeutral)[i_daughter] );
      _recomu_miniIsoCharged.push_back( muon.Pt()*(*_daughters_miniRelIsoCharged)[i_daughter] );
      _recomu_miniIsoNeutral.push_back( muon.Pt()*(*_daughters_miniRelIsoNeutral)[i_daughter] );
      _recomu_sip3D.push_back( (*_SIP)[i_daughter] );
      
      if(_daughters_dR_closest_jet[i_daughter]<0.4){      
	_recomu_jetPtRel.push_back( (*_daughters_jetPtRel)[i_daughter] );
	_recomu_jetCSV.push_back( (*_daughters_jetBTagCSV)[i_daughter] );
	_recomu_jetPtRatio.push_back( (*_daughters_jetPtRatio)[i_daughter] );
      }
      else{
	_recomu_jetPtRel.push_back( 0. );
	_recomu_jetCSV.push_back( 0. );
	_recomu_jetPtRatio.push_back( 1. );
      }

      _recomu_lepMVA_mvaId.push_back( (*_daughters_lepMVA_mvaId)[i_daughter] );

      

      lepMVA_pt = _recomu_pt[i_mu];
      lepMVA_eta = _recomu_eta[i_mu];
      lepMVA_jetNDauChargedMVASel = _recomu_jetNDauChargedMVASel[i_mu];
      lepMVA_miniRelIsoCharged = _recomu_miniIsoCharged[i_mu]/lepMVA_pt;
      lepMVA_miniRelIsoNeutral = _recomu_miniIsoNeutral[i_mu]/lepMVA_pt;
      lepMVA_jetPtRelv2 = _recomu_jetPtRel[i_mu]; 
      lepMVA_jetPtRatio = std::min(_recomu_jetPtRatio[i_mu],float(1.5));      
      lepMVA_jetBTagCSV = std::max(_recomu_jetCSV[i_mu],float(0.));
      lepMVA_sip3d = _recomu_sip3D[i_mu];
      lepMVA_dxy = log(fabs(_recomu_dxy[i_mu]));
      lepMVA_dz = log(fabs(_recomu_dz[i_mu]));
      lepMVA_mvaId = _recomu_lepMVA_mvaId[i_mu];

      _recomu_leptonMVA.push_back( mu_reader->EvaluateMVA("BDTG method") );

    }



    _n_recoele = reco_eles.size();

    for(unsigned int i_ele=0; i_ele<reco_eles.size(); i_ele++){
      
      int i_daughter=reco_eles[i_ele].first;
      TLorentzVector elec=reco_eles[i_ele].second;

      _recoele_ID.push_back( (*_PDGIdDaughters)[i_daughter] );
      _recoele_charge.push_back( (*_PDGIdDaughters)[i_daughter] > 0 ? -1 : 1 );
      _recoele_e.push_back( elec.E() );
      _recoele_px.push_back( elec.Px() );
      _recoele_py.push_back( elec.Py() );
      _recoele_pz.push_back( elec.Pz() );
      _recoele_pt.push_back( elec.Pt() );
      _recoele_eta.push_back( elec.Eta() );
      _recoele_phi.push_back( elec.Phi() );
	  
      _recoele_dxy.push_back( (*_dxy)[i_daughter] );
      _recoele_dz.push_back( (*_dz)[i_daughter] );
      _recoele_jetNDauChargedMVASel.push_back( (*_daughters_jetNDauChargedMVASel)[i_daughter] );
      _recoele_miniRelIso.push_back( (*_daughters_miniRelIsoCharged)[i_daughter] + (*_daughters_miniRelIsoNeutral)[i_daughter] );
      _recoele_miniIsoCharged.push_back( elec.Pt()*(*_daughters_miniRelIsoCharged)[i_daughter] );
      _recoele_miniIsoNeutral.push_back( elec.Pt()*(*_daughters_miniRelIsoNeutral)[i_daughter] );
      _recoele_sip3D.push_back( (*_SIP)[i_daughter] );

      if(_daughters_dR_closest_jet[i_daughter]<0.4){      
	_recoele_jetPtRel.push_back( (*_daughters_jetPtRel)[i_daughter] );
	_recoele_jetCSV.push_back( (*_daughters_jetBTagCSV)[i_daughter] );
	_recoele_jetPtRatio.push_back( (*_daughters_jetPtRatio)[i_daughter] );
      }
      else{
	_recoele_jetPtRel.push_back( 0. );
	_recoele_jetCSV.push_back( 0. );
	_recoele_jetPtRatio.push_back( 1. );
      }

      _recoele_lepMVA_mvaId.push_back( (*_daughters_lepMVA_mvaId)[i_daughter] );


      lepMVA_pt = _recoele_pt[i_ele];
      lepMVA_eta = _recoele_eta[i_ele];
      lepMVA_jetNDauChargedMVASel = _recoele_jetNDauChargedMVASel[i_ele];
      lepMVA_miniRelIsoCharged = _recoele_miniIsoCharged[i_ele]/lepMVA_pt;
      lepMVA_miniRelIsoNeutral = _recoele_miniIsoNeutral[i_ele]/lepMVA_pt;
      lepMVA_jetPtRelv2 = _recoele_jetPtRel[i_ele]; 
      lepMVA_jetPtRatio = std::min(_recoele_jetPtRatio[i_ele],float(1.5));      
      lepMVA_jetBTagCSV = std::max(_recoele_jetCSV[i_ele],float(0.));
      lepMVA_sip3d = _recoele_sip3D[i_ele];
      lepMVA_dxy = log(fabs(_recoele_dxy[i_ele]));
      lepMVA_dz = log(fabs(_recoele_dz[i_ele]));
      lepMVA_mvaId = _recoele_lepMVA_mvaId[i_ele];

      _recoele_leptonMVA.push_back( ele_reader->EvaluateMVA("BDTG method") );


    }



    ///Taus   
    
    vector< pair<int,TLorentzVector> > reco_taus;
    
    for(unsigned int i_daughter=0; i_daughter<(*_daughters_e).size(); i_daughter++){
      int PDGId=(*_PDGIdDaughters)[i_daughter];
      TLorentzVector daughter ( (*_daughters_px)[i_daughter] , (*_daughters_py)[i_daughter] , (*_daughters_pz)[i_daughter] , (*_daughters_e)[i_daughter] );
      
      pair<int,TLorentzVector> daughter_pair = make_pair(i_daughter,daughter);
     
      float iso=(*_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits)[i_daughter];
      //int iso=(*_tauID)[i_daughter] & (1<<16); //byLooseCombinedIsolationDeltaBetaCorr3Hits = bit#16
   
      int byLooseCombinedIsolationDeltaBetaCorr3Hits = ((*_tauID)[i_daughter]>>3)&1;
      int byLooseCombinedIsolationDeltaBetaCorr3HitsdR03 = ((*_tauID)[i_daughter]>>21)&1;
      int byLooseIsolationMVArun2v1DBdR03oldDMwLT = ((*_tauID)[i_daughter]>>24)&1;

      int decayModeFinding=(*_daughters_decayModeFindingOldDMs)[i_daughter];
      //int decayModeFinding=(*_daughters_decayModeFindingNewDMs)[i_daughter];
      //int antiMu=(*_daughters_againstMuonTight3)[i_daughter];
      //int antiE=(*_daughters_againstElectronVLooseMVA5)[i_daughter];
      int antiMu=((*_tauID)[i_daughter]>>6) & 1; //againsMuonLoose3 = bit #7
      int antiE=((*_tauID)[i_daughter]>>8) & 1; //againsElectronVLooseMVA6 = bit #9

      float dxy = (*_dxy)[i_daughter];
      float dz = (*_dz)[i_daughter];
      
      bool iso_cut = iso<(0.1*iso_tau);
      if(iso_type=="byLooseCombinedIsolationDeltaBetaCorr3Hits" || sample=="sync")
	iso_cut = byLooseCombinedIsolationDeltaBetaCorr3Hits;
      else if(iso_type=="byLooseCombinedIsolationDeltaBetaCorr3HitsdR03")
	iso_cut = byLooseCombinedIsolationDeltaBetaCorr3HitsdR03;
      else if(iso_type=="byLooseIsolationMVArun2v1DBdR03oldDMwLT")
	iso_cut = byLooseIsolationMVArun2v1DBdR03oldDMwLT;
	  
      bool sync_cut=fabs(PDGId)==15 && daughter.Pt()>20 && fabs(daughter.Eta())<2.3 && iso_cut && decayModeFinding>0.5 && fabs(dxy)<=1000 && fabs(dz)<=0.2;   
      bool nomin_cut = fabs(PDGId)==15 && daughter.Pt()>20 && fabs(daughter.Eta())<2.3 && iso_cut && decayModeFinding>0.5 && abs(dxy)<=1000 && abs(dz)<=0.2 && antiMu>0 && antiE>0;     
      
      if( (sample=="sync" && sync_cut) || (sample!="sync" && nomin_cut)){	
	
	bool dR_veto=false;
	
	/*for(unsigned int i_lep=0; i_lep<reco_leptons.size(); i_lep++){

	  TLorentzVector lep=reco_leptons[i_lep].second;
	  float dR_lep_tau=lep.DeltaR(daughter);
	  if(dR_lep_tau<0.4){
	    dR_veto=true;
	    break;
	  }
	  }*/

	for(unsigned int i_lep=0; i_lep<reco_mus.size(); i_lep++){
	  
	  TLorentzVector lep=reco_mus[i_lep].second;
	  float dR_lep_tau=lep.DeltaR(daughter);
	  if(dR_lep_tau<0.4){
	    dR_veto=true;
	    break;
	  }
	}

	for(unsigned int i_lep=0; i_lep<reco_eles.size(); i_lep++){
	  
	  TLorentzVector lep=reco_eles[i_lep].second;
	  float dR_lep_tau=lep.DeltaR(daughter);
	  if(dR_lep_tau<0.4){
	    dR_veto=true;
	    break;
	  }
	}

	if(dR_veto)
	  continue;

	reco_taus.push_back(daughter_pair);
	

      }

    }


    sort(reco_taus.begin(), reco_taus.end(), pT_comparison_pairs);


    _n_recotauh = reco_taus.size();

    for(unsigned int i_tauh=0; i_tauh<reco_taus.size(); i_tauh++){
      
      int i_daughter=reco_taus[i_tauh].first;
      TLorentzVector tauh=reco_taus[i_tauh].second;

      _recotauh_charge.push_back( (*_PDGIdDaughters)[i_daughter] > 0 ? -1 : 1 );
      _recotauh_decayMode.push_back( (*_decayMode)[i_daughter] );
      _recotauh_e.push_back( tauh.E() );
      _recotauh_px.push_back( tauh.Px() );
      _recotauh_py.push_back( tauh.Py() );
      _recotauh_pz.push_back( tauh.Pz() );
      _recotauh_pt.push_back( tauh.Pt() );
      _recotauh_eta.push_back( tauh.Eta() );
      _recotauh_phi.push_back( tauh.Phi() );
      _recotauh_dxy.push_back( (*_dxy)[i_daughter] );
      _recotauh_dz.push_back( (*_dz)[i_daughter] );
      _recotauh_iso.push_back( (*_daughters_byCombinedIsolationDeltaBetaCorrRaw3Hits)[i_daughter] );

      _recotauh_decayModeFindingOldDMs.push_back( (*_daughters_decayModeFindingOldDMs)[i_daughter] );
      _recotauh_decayModeFindingNewDMs.push_back( (*_daughters_decayModeFindingNewDMs)[i_daughter] );
      _recotauh_byLooseCombinedIsolationDeltaBetaCorr3Hits.push_back( ((*_tauID)[i_daughter]>>3)&1 );
      _recotauh_byMediumCombinedIsolationDeltaBetaCorr3Hits.push_back( ((*_tauID)[i_daughter]>>4)&1 );
      _recotauh_byTightCombinedIsolationDeltaBetaCorr3Hits.push_back( ((*_tauID)[i_daughter]>>5)&1 );
      _recotauh_byLooseCombinedIsolationDeltaBetaCorr3HitsdR03.push_back( ((*_tauID)[i_daughter]>>21)&1 );
      _recotauh_byMediumCombinedIsolationDeltaBetaCorr3HitsdR03.push_back( ((*_tauID)[i_daughter]>>22)&1 );
      _recotauh_byTightCombinedIsolationDeltaBetaCorr3HitsdR03.push_back( ((*_tauID)[i_daughter]>>23)&1 );
      _recotauh_byLooseIsolationMVArun2v1DBdR03oldDMwLT.push_back( ((*_tauID)[i_daughter]>>24)&1 );
      _recotauh_byMediumIsolationMVArun2v1DBdR03oldDMwLT.push_back( ((*_tauID)[i_daughter]>>25)&1 );
      _recotauh_byTightIsolationMVArun2v1DBdR03oldDMwLT.push_back( ((*_tauID)[i_daughter]>>26)&1 );
      _recotauh_byVTightIsolationMVArun2v1DBdR03oldDMwLT.push_back( ((*_tauID)[i_daughter]>>27)&1 );

      _recotauh_againstMuonLoose3.push_back( ((*_tauID)[i_daughter]>>6)&1 );
      _recotauh_againstMuonTight3.push_back( ((*_tauID)[i_daughter]>>7)&1 );
      _recotauh_againstElectronVLooseMVA6.push_back( ((*_tauID)[i_daughter]>>8)&1 );
      _recotauh_againstElectronLooseMVA6.push_back( ((*_tauID)[i_daughter]>>9)&1 );
      _recotauh_againstElectronMediumMVA6.push_back( ((*_tauID)[i_daughter]>>10)&1 );
      _recotauh_againstElectronTightMVA6.push_back( ((*_tauID)[i_daughter]>>11)&1 );
      _recotauh_againstElectronVTightMVA6.push_back( ((*_tauID)[i_daughter]>>12)&1 );

      pair<int,float> pair = find_i_dRmin_closest( tauh,
						   (*_genpart_px), (*_genpart_py), (*_genpart_pz), (*_genpart_e) );

      _recotauh_i_closest_genpart.push_back(pair.first);
      _recotauh_dR_closest_genpart.push_back(pair.second);


    }   

    
    ///Jets
    
    vector< pair<int,TLorentzVector> > reco_jets;
    vector< pair<int,float> > i_jet_CSV_pairs;

    for(unsigned int i_jet=0; i_jet<(*_jets_e).size(); i_jet++){

      TLorentzVector jet ( (*_jets_px)[i_jet] , (*_jets_py)[i_jet] , (*_jets_pz)[i_jet] , (*_jets_e)[i_jet] );

      _jets_pt.push_back(jet.Pt());
      _jets_eta.push_back(jet.Eta());
      _jets_phi.push_back(jet.Phi());      

      pair<int,TLorentzVector> jet_pair = make_pair(i_jet,jet);
      float CSVscore = (*_bCSVscore)[i_jet];
      pair<int,float> CSV_pair = make_pair(i_jet,CSVscore);
      float PUJetID = (*_jets_PUJetID)[i_jet];
      float PFJetID = (*_PFjetID)[i_jet];


      //if(jet.Pt()>25 && fabs(jet.Eta())<2.4 && PUJetID>-0.63 && PFJetID>1){
      if(jet.Pt()>25 && fabs(jet.Eta())<2.4 && PFJetID>0){

	bool dR_veto=false;

	/*for(unsigned int i_lep=0; i_lep<reco_leptons.size(); i_lep++){

	  TLorentzVector lep=reco_leptons[i_lep].second;
	  float dR_lep_jet=lep.DeltaR(jet);
	  if(dR_lep_jet<0.4){
	    dR_veto=true;
	    break;
	  }
	
	  }*/

	for(unsigned int i_lep=0; i_lep<reco_mus.size(); i_lep++){
	  
	  TLorentzVector lep=reco_mus[i_lep].second;
	  float dR_lep_tau=lep.DeltaR(jet);
	  if(dR_lep_tau<0.4){
	    dR_veto=true;
	    break;
	  }
	}

	for(unsigned int i_lep=0; i_lep<reco_eles.size(); i_lep++){
	  
	  TLorentzVector lep=reco_eles[i_lep].second;
	  float dR_lep_tau=lep.DeltaR(jet);
	  if(dR_lep_tau<0.4){
	    dR_veto=true;
	    break;
	  }
	}

	for(unsigned int i_tauh=0; i_tauh<reco_taus.size(); i_tauh++){

	  TLorentzVector tauh=reco_taus[i_tauh].second;
	  float dR_tauh_jet=tauh.DeltaR(jet);
	  if(dR_tauh_jet<0.4){
	    dR_veto=true;
	    break;
	  }
	
	}

	if(dR_veto)
	  continue;

	reco_jets.push_back(jet_pair);
	i_jet_CSV_pairs.push_back(CSV_pair);

	//Tight CSV WP: CSV>0.941
	//Medium CSV WP: CSV>0.814
	//Loose CSV WP: CSV>0.423   

	if(CSVscore>0.423)
	  _n_recoPFJet_btag_loose++;
	if(CSVscore>0.814)
	  _n_recoPFJet_btag_medium++;

      }

    }


    sort(reco_jets.begin(), reco_jets.end(), pT_comparison_pairs);
    sort(i_jet_CSV_pairs.begin(), i_jet_CSV_pairs.end(), CSV_comparison_pairs);
    

    _n_recoPFJet = reco_jets.size();
    

    for(unsigned int i_PFJet=0; i_PFJet<reco_jets.size(); i_PFJet++){

      int i_jet = reco_jets[i_PFJet].first;
      TLorentzVector jet =  reco_jets[i_PFJet].second;
      
      _recoPFJet_e.push_back( jet.E() );
      _recoPFJet_pt.push_back( jet.Pt() );
      _recoPFJet_px.push_back( jet.Px() );
      _recoPFJet_py.push_back( jet.Py() );
      _recoPFJet_pz.push_back( jet.Pz() );
      _recoPFJet_eta.push_back( jet.Eta() );
      _recoPFJet_phi.push_back( jet.Phi() );
      _recoPFJet_CSVscore.push_back(  (*_bCSVscore)[i_jet] );
      _recoPFJet_Flavour.push_back(  (*_jets_Flavour)[i_jet] );


      int imin = -1;
      float dRmin = 100000;
      int imin_2nd = -1;
      float dRmin_2nd = 100000;
      
      for(unsigned int i_gen=0; i_gen<(*_genpart_e).size(); i_gen++){

	TLorentzVector genpart_tlv( (*_genpart_px)[i_gen], (*_genpart_py)[i_gen], (*_genpart_pz)[i_gen], (*_genpart_e)[i_gen]);	
	float dR = jet.DeltaR(genpart_tlv);

	if(dR<dRmin_2nd){
	  if(dR<dRmin){
	    imin_2nd=imin;
	    dRmin_2nd=dRmin;
	    dRmin=dR;
	    imin=i_gen;
	  } 
	  else{
	    imin_2nd=i_gen;
	    dRmin_2nd=dR;
	  }
	}
	
      }

      _recoPFJet_i_closest_genpart.push_back(imin);
      _recoPFJet_dR_closest_genpart.push_back(dRmin);
      _recoPFJet_i_2nd_closest_genpart.push_back(imin_2nd);
      _recoPFJet_dR_2nd_closest_genpart.push_back(dRmin_2nd);


      pair<int,float> pair_lep = find_i_dRmin_closest( jet,
						       _recolep_px, _recolep_py, _recolep_pz, _recolep_e );

      _recoPFJet_i_closest_lep.push_back(pair_lep.first);
      _recoPFJet_dR_closest_lep.push_back(pair_lep.second);      


      pair<int,float> pair_tauh = find_i_dRmin_closest( jet,
						       _recotauh_px, _recotauh_py, _recotauh_pz, _recotauh_e );

      _recoPFJet_i_closest_tau.push_back(pair_tauh.first);
      _recoPFJet_dR_closest_tau.push_back(pair_tauh.second);  



    }



    for(unsigned int i_PFJet=0; i_PFJet<i_jet_CSV_pairs.size(); i_PFJet++){

      int i_jet = i_jet_CSV_pairs[i_PFJet].first;
      float CSVscore= i_jet_CSV_pairs[i_PFJet].second;
      
      TLorentzVector jet  ( (*_jets_px)[i_jet] , (*_jets_py)[i_jet] , (*_jets_pz)[i_jet] , (*_jets_e)[i_jet] );
      
      _recoPFJet_CSVsort_e.push_back( jet.E() );
      _recoPFJet_CSVsort_pt.push_back( jet.Pt() );
      _recoPFJet_CSVsort_px.push_back( jet.Px() );
      _recoPFJet_CSVsort_py.push_back( jet.Py() );
      _recoPFJet_CSVsort_pz.push_back( jet.Pz() );
      _recoPFJet_CSVsort_eta.push_back( jet.Eta() );
      _recoPFJet_CSVsort_phi.push_back( jet.Phi() );
      _recoPFJet_CSVsort_CSVscore.push_back( CSVscore );
      _recoPFJet_CSVsort_Flavour.push_back(  (*_jets_Flavour)[i_jet] );

      if(i_PFJet<2){
	_recoPFJet_btag_e.push_back( jet.E() );
	_recoPFJet_btag_pt.push_back( jet.Pt() );
	_recoPFJet_btag_px.push_back( jet.Px() );
	_recoPFJet_btag_py.push_back( jet.Py() );
	_recoPFJet_btag_pz.push_back( jet.Pz() );
	_recoPFJet_btag_eta.push_back( jet.Eta() );
	_recoPFJet_btag_phi.push_back( jet.Phi() );
	_recoPFJet_btag_CSVscore.push_back( CSVscore );
	_recoPFJet_btag_Flavour.push_back(  (*_jets_Flavour)[i_jet] );
      }

      else{
	_recoPFJet_untag_e.push_back( jet.E() );
	_recoPFJet_untag_pt.push_back( jet.Pt() );
	_recoPFJet_untag_px.push_back( jet.Px() );
	_recoPFJet_untag_py.push_back( jet.Py() );
	_recoPFJet_untag_pz.push_back( jet.Pz() );
	_recoPFJet_untag_eta.push_back( jet.Eta() );
	_recoPFJet_untag_phi.push_back( jet.Phi() );
	_recoPFJet_untag_CSVscore.push_back( CSVscore );
	_recoPFJet_untag_Flavour.push_back(  (*_jets_Flavour)[i_jet] );
      }

    }

    _n_recoPFJet_untag=_recoPFJet_untag_e.size();


    //W-tag
    double mW=80.4;


    if(_recoPFJet_untag_e.size()>1){

      vector<int> index_Wtag;
      index_Wtag.push_back(0);
      index_Wtag.push_back(0);
	    
      for(unsigned int i_jet1=0; i_jet1<_recoPFJet_untag_e.size()-1; i_jet1++){
	TLorentzVector jet1 ( _recoPFJet_untag_px[i_jet1], _recoPFJet_untag_py[i_jet1], _recoPFJet_untag_pz[i_jet1], _recoPFJet_untag_e[i_jet1] );
	
	for(unsigned int i_jet2=i_jet1+1; i_jet2<_recoPFJet_untag_e.size(); i_jet2++){
	  

	  TLorentzVector jet2 ( _recoPFJet_untag_px[i_jet2], _recoPFJet_untag_py[i_jet2], _recoPFJet_untag_pz[i_jet2], _recoPFJet_untag_e[i_jet2] );
	  
	  double mjj = (jet1+jet2).M();
	  if(mjj>60 && mjj<100)
	    _n_pair_Wtag_recoPFJet_untag++;


	  if( abs( mjj - mW ) < abs( _recoPFJet_untag_best_mW - mW ) ){
	    
	    _recoPFJet_untag_best_mW = mjj;
	    
	    if(jet1.Pt()>jet2.Pt()){
	      index_Wtag[0]=i_jet1;
	      index_Wtag[1]=i_jet2;
	    }
	    else{
	      index_Wtag[0]=i_jet2;
	      index_Wtag[1]=i_jet1;
	    }

	  }
	    
	  
	}
	
      }

      for(int k=0;k<2;k++){

	int i_jet=index_Wtag[k];

	_recoPFJet_untag_Wtag_e.push_back( _recoPFJet_untag_e[i_jet] );
	_recoPFJet_untag_Wtag_pt.push_back( _recoPFJet_untag_pt[i_jet] );
	_recoPFJet_untag_Wtag_px.push_back( _recoPFJet_untag_px[i_jet] );
	_recoPFJet_untag_Wtag_py.push_back( _recoPFJet_untag_py[i_jet] );
	_recoPFJet_untag_Wtag_pz.push_back( _recoPFJet_untag_pz[i_jet] );
	_recoPFJet_untag_Wtag_eta.push_back( _recoPFJet_untag_eta[i_jet] );
	_recoPFJet_untag_Wtag_phi.push_back( _recoPFJet_untag_phi[i_jet] );
	_recoPFJet_untag_Wtag_CSVscore.push_back( _recoPFJet_untag_CSVscore[i_jet] );
	_recoPFJet_untag_Wtag_Flavour.push_back( _recoPFJet_untag_Flavour[i_jet] );

      }

    }
    

    if( _n_recolep==2 && _n_recotauh>=1 && _n_recoPFJet>=4){
  
      for(int perm=0; perm<4; perm++){
	
	TLorentzVector Whad_1 ( _recoPFJet_untag_Wtag_px[0], _recoPFJet_untag_Wtag_py[0], _recoPFJet_untag_Wtag_pz[0], _recoPFJet_untag_Wtag_e[0] );
	TLorentzVector Whad_2 ( _recoPFJet_untag_Wtag_px[1], _recoPFJet_untag_Wtag_py[1], _recoPFJet_untag_Wtag_pz[1], _recoPFJet_untag_Wtag_e[1] );
	TLorentzVector tauh ( _recotauh_px[0], _recotauh_py[0], _recotauh_pz[0], _recotauh_e[0]);
	
	TLorentzVector Bjet_1 ( _recoPFJet_btag_px[0], _recoPFJet_btag_py[0], _recoPFJet_btag_pz[0], _recoPFJet_btag_e[0] );
	TLorentzVector Bjet_2 ( _recoPFJet_btag_px[1], _recoPFJet_btag_py[1], _recoPFJet_btag_pz[1], _recoPFJet_btag_e[1] );
	
	TLorentzVector lep_1 ( _recolep_px[0], _recolep_py[0], _recolep_pz[0], _recolep_e[0] );
	TLorentzVector lep_2 ( _recolep_px[1], _recolep_py[1], _recolep_pz[1], _recolep_e[1] );
	
	TLorentzVector bjet_leptop, bjet_hadtop, lep_top, lep_tau;
	
	switch(perm){
	case 0:
	  lep_top = lep_1;
	  lep_tau = lep_2;
	  bjet_leptop = Bjet_1;
	  bjet_hadtop = Bjet_2;	
	  break;
	  
	case 1:
	  lep_top = lep_2;
	  lep_tau = lep_1;
	  bjet_leptop = Bjet_1;
	  bjet_hadtop = Bjet_2;
	  break;
	  
	case 2:
	  lep_top = lep_1;
	  lep_tau = lep_2;
	  bjet_leptop = Bjet_2;
	  bjet_hadtop = Bjet_1;	
	  break;
	  
	case 3:
	  lep_top = lep_2;
	  lep_tau = lep_1;
	  bjet_leptop = Bjet_2;
	  bjet_hadtop = Bjet_1;	
	  break;
	  
	default:
	  break;
	  
	}
	
	_mtop_had_perm.push_back( (Whad_1+Whad_2+bjet_hadtop).M() );
	_mblep_perm.push_back( (bjet_leptop+lep_top).M() );
	_mleptauh_perm.push_back( (lep_tau+tauh).M() );
	
      }

    }

    ///MET

    if( (*_MET_cov00_vect).size() > 0 ){

      _PFMETx = (*_METx_vect)[0];
      _PFMETy = (*_METy_vect)[0];

      _PFMET_cov00 = (*_MET_cov00_vect)[0];
      _PFMET_cov01 = (*_MET_cov01_vect)[0];
      _PFMET_cov10 = (*_MET_cov10_vect)[0];
      _PFMET_cov11 = (*_MET_cov11_vect)[0];
      
      for(unsigned int i_MET=0;i_MET<(*_MET_cov00_vect).size();i_MET++){
	
	if( (*_METx_vect)[i_MET]!=_PFMETx || (*_METy_vect)[i_MET]!=_PFMETy || (*_MET_cov00_vect)[i_MET]!=_PFMET_cov00 || (*_MET_cov01_vect)[i_MET]!=_PFMET_cov01 || (*_MET_cov10_vect)[i_MET]!=_PFMET_cov10 || (*_MET_cov11_vect)[i_MET]!=_PFMET_cov11 ){
	  cout<<"Problem with MET"<<endl;
	  return;
	}

      }
      
    }

    TVector3 PFMET_tv3;
    PFMET_tv3.SetXYZ(_PFMETx,_PFMETy,0);
    _PFMET = PFMET_tv3.Pt();    
    _PFMET_phi = PFMET_tv3.Phi();


    // Gen information

    vector<int> genlep_index;
    vector<int> gentauh_index;
    vector<int> gentau_index;
    vector<int> gentop_index;
    vector<int> genW_index;
    vector<int> genH_index;
    vector<int> genb_index;
    vector<int> genq_index;
    vector<int> gennu_index;


    for(unsigned int i_gen=0; i_gen<(*_genpart_e).size(); i_gen++){

      TLorentzVector genpart_tlv( (*_genpart_px)[i_gen], (*_genpart_py)[i_gen], (*_genpart_pz)[i_gen], (*_genpart_e)[i_gen]);
      
      _genpart_pt.push_back(genpart_tlv.Pt());
      _genpart_eta.push_back(genpart_tlv.Eta());
      _genpart_phi.push_back(genpart_tlv.Phi());

      pair<int,float> pair = find_i_dRmin_closest( genpart_tlv,
						   (*_daughters_px), (*_daughters_py), (*_daughters_pz), (*_daughters_e) );
      _genpart_i_closest_daughter.push_back(pair.first);
      _genpart_dR_closest_daughter.push_back(pair.second);  

      int TauMothInd = (*_genpart_TauMothInd)[i_gen];
      int HMothInd = (*_genpart_HMothInd)[i_gen];
      int TopMothInd = (*_genpart_TopMothInd)[i_gen];
      int WMothInd = (*_genpart_WMothInd)[i_gen];

      int flags = (*_genpart_flags)[i_gen];
      bool isFromHardProcess = (flags >> 8) & 1;
      bool isDirectTauDecayProduct = (flags >> 4) & 1;
      bool isHardProcessTauDecayProduct = (flags >> 9) & 1;

      if( abs( (*_genpart_pdg)[i_gen] )==11 || abs( (*_genpart_pdg)[i_gen] )==13){

	_genlep_pdg.push_back( (*_genpart_pdg)[i_gen] );
	_genlep_charge.push_back( (*_genpart_pdg)[i_gen]>0 ? -1:1 );
	
	_genlep_e.push_back( genpart_tlv.E() );
	_genlep_px.push_back( genpart_tlv.Px() );
	_genlep_py.push_back( genpart_tlv.Py() );
	_genlep_pz.push_back( genpart_tlv.Pz() );
	_genlep_pt.push_back( genpart_tlv.Pt() );
	_genlep_eta.push_back( genpart_tlv.Eta() );
	_genlep_phi.push_back( genpart_tlv.Phi() );
	_genlep_flags.push_back(flags);

	if( TauMothInd>-1 && isDirectTauDecayProduct && isHardProcessTauDecayProduct )
	  _n_genlep_fromTau++;
	if( TopMothInd>-1 && WMothInd>-1 && isFromHardProcess)
	  _n_genlep_fromTop++;
	if( genpart_tlv.Pt()>10)
	  _n_genlep10++;
	if( genpart_tlv.Pt()>20)
	  _n_genlep20++;
	if( genpart_tlv.Pt()>20 && abs(genpart_tlv.Eta())<2.1)
	  _n_genlep20_eta21++;

	genlep_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )==66615){

	_gentauh_charge.push_back( (*_genpart_pdg)[i_gen]>0 ? -1:1 );
	
	_gentauh_e.push_back( genpart_tlv.E() );
	_gentauh_px.push_back( genpart_tlv.Px() );
	_gentauh_py.push_back( genpart_tlv.Py() );
	_gentauh_pz.push_back( genpart_tlv.Pz() );
	_gentauh_pt.push_back( genpart_tlv.Pt() );
	_gentauh_eta.push_back( genpart_tlv.Eta() );
	_gentauh_phi.push_back( genpart_tlv.Phi() );
	_gentauh_flags.push_back(flags);

	int flag_Mother = (*_genpart_flags)[(*_genpart_TauMothInd)[i_gen]];
	bool isMotherFromHardProcess = (flag_Mother >> 8) & 1;

	if( TauMothInd>-1 && isMotherFromHardProcess )
	  _n_gentauh_fromTau++;
	if( TopMothInd>-1 && WMothInd>-1 && TauMothInd>-1 && isMotherFromHardProcess )
	  _n_gentauh_fromTop++;
	if( genpart_tlv.Pt()>10)
	  _n_gentauh10++;
	if( genpart_tlv.Pt()>30)
	  _n_gentauh30++;
	if( genpart_tlv.Pt()>30 && abs(genpart_tlv.Eta())<2.1 )
	  _n_gentauh30_eta21++;

	gentauh_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )==15){

	_gentau_decayMode.push_back( (*_genpart_TauGenDecayMode)[i_gen] );
	_gentau_charge.push_back( (*_genpart_pdg)[i_gen]>0 ? -1:1 );

	_gentau_e.push_back( genpart_tlv.E() );
	_gentau_px.push_back( genpart_tlv.Px() );
	_gentau_py.push_back( genpart_tlv.Py() );
	_gentau_pz.push_back( genpart_tlv.Pz() );
	_gentau_pt.push_back( genpart_tlv.Pt() );
	_gentau_eta.push_back( genpart_tlv.Eta() );
	_gentau_phi.push_back( genpart_tlv.Phi() );
	_gentau_flags.push_back(flags);

	if( HMothInd>-1 && isFromHardProcess)
	  _n_gentau_fromH++;
	if( TopMothInd>-1 && WMothInd>-1 && isFromHardProcess )
	  _n_gentau_fromTop++;

	gentau_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )==25){

	_genH_decayMode.push_back( (*_genpart_HZDecayMode)[i_gen] );

	_genH_e.push_back( genpart_tlv.E() );
	_genH_px.push_back( genpart_tlv.Px() );
	_genH_py.push_back( genpart_tlv.Py() );
	_genH_pz.push_back( genpart_tlv.Pz() );
	_genH_pt.push_back( genpart_tlv.Pt() );
	_genH_eta.push_back( genpart_tlv.Eta() );
	_genH_phi.push_back( genpart_tlv.Phi() );
	_genH_flags.push_back(flags);

	genH_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )==6){

	_gentop_pdg.push_back( (*_genpart_pdg)[i_gen] );
		
	_gentop_decayMode.push_back(  (*_genpart_TopDecayMode)[i_gen] );
	_gentop_e.push_back( genpart_tlv.E() );
	_gentop_px.push_back( genpart_tlv.Px() );
	_gentop_py.push_back( genpart_tlv.Py() );
	_gentop_pz.push_back( genpart_tlv.Pz() );
	_gentop_pt.push_back( genpart_tlv.Pt() );
	_gentop_eta.push_back( genpart_tlv.Eta() );
	_gentop_phi.push_back( genpart_tlv.Phi() );
	_gentop_flags.push_back(flags);

	gentop_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )==24){

	_genW_pdg.push_back( (*_genpart_pdg)[i_gen] );
		
	_genW_decayMode.push_back(  (*_genpart_TopDecayMode)[i_gen] );
	_genW_e.push_back( genpart_tlv.E() );
	_genW_px.push_back( genpart_tlv.Px() );
	_genW_py.push_back( genpart_tlv.Py() );
	_genW_pz.push_back( genpart_tlv.Pz() );
	_genW_pt.push_back( genpart_tlv.Pt() );
	_genW_eta.push_back( genpart_tlv.Eta() );
	_genW_phi.push_back( genpart_tlv.Phi() );
	_genW_flags.push_back(flags);

	if( TopMothInd>-1 )
	  _n_genW_fromTop++;

	genW_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )==5){

	_genb_pdg.push_back( (*_genpart_pdg)[i_gen] );

	_genb_e.push_back( genpart_tlv.E() );
	_genb_px.push_back( genpart_tlv.Px() );
	_genb_py.push_back( genpart_tlv.Py() );
	_genb_pz.push_back( genpart_tlv.Pz() );
	_genb_pt.push_back( genpart_tlv.Pt() );
	_genb_eta.push_back( genpart_tlv.Eta() );
	_genb_phi.push_back( genpart_tlv.Phi() );
	_genb_flags.push_back(flags);

	if( TopMothInd>-1 && WMothInd==-1 && isFromHardProcess )
	  _n_genb_fromTop++;
	if( genpart_tlv.Pt()>10)
	  _n_genb10++;

	genb_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )<5){

	_genq_pdg.push_back( (*_genpart_pdg)[i_gen] );

	_genq_e.push_back( genpart_tlv.E() );
	_genq_px.push_back( genpart_tlv.Px() );
	_genq_py.push_back( genpart_tlv.Py() );
	_genq_pz.push_back( genpart_tlv.Pz() );
	_genq_pt.push_back( genpart_tlv.Pt() );
	_genq_eta.push_back( genpart_tlv.Eta() );
	_genq_phi.push_back( genpart_tlv.Phi() );
	_genq_flags.push_back(flags);

	if( TopMothInd>-1 && WMothInd>-1 && isFromHardProcess )
	  _n_genq_fromTop++;
	if( genpart_tlv.Pt()>10)
	  _n_genq10++;

	genq_index.push_back(i_gen);

      }

      else if( abs( (*_genpart_pdg)[i_gen] )==12 || abs( (*_genpart_pdg)[i_gen] )==14 || abs( (*_genpart_pdg)[i_gen] )==16){

	_gennu_pdg.push_back( (*_genpart_pdg)[i_gen] );

	_gennu_e.push_back( genpart_tlv.E() );
	_gennu_px.push_back( genpart_tlv.Px() );
	_gennu_py.push_back( genpart_tlv.Py() );
	_gennu_pz.push_back( genpart_tlv.Pz() );
	_gennu_pt.push_back( genpart_tlv.Pt() );
	_gennu_eta.push_back( genpart_tlv.Eta() );
	_gennu_phi.push_back( genpart_tlv.Phi() );
	_gennu_flags.push_back(flags);

	//Only count lep from tau from Higgs or top
	if( TauMothInd>-1 && ( HMothInd>-1  || (TopMothInd>-1 && WMothInd>-1 && isFromHardProcess) ) )
	  _n_gennu_fromTau++;
	if( (TopMothInd>-1 && WMothInd>-1 && isFromHardProcess) )
	  _n_gennu_fromTop++;

	gennu_index.push_back(i_gen);


      }


    }

    _n_genlep = _genlep_e.size();
    _n_gentauh = _gentauh_e.size();
    _n_gentau = _gentau_e.size();
    _n_genH = _genH_e.size();
    _n_gentop = _gentop_e.size();
    _n_genW = _genW_e.size();
    _n_genb = _genb_e.size();
    _n_genq = _genq_e.size();
    _n_gennu = _gennu_e.size();


    for(int i_lep=0; i_lep<_n_genlep; i_lep++){

      int i_gen = genlep_index[i_lep];
      
      int i_tau_Moth = -1;
      int i_gen_TauMoth = (*_genpart_TauMothInd)[i_gen];
      if( i_gen_TauMoth > -1 ){
	for(int i_tau=0; i_tau<_n_gentau; i_tau++){
	  if( gentau_index[i_tau]==i_gen_TauMoth){
	    i_tau_Moth = i_tau;
	    break;
	  }
	}
      }
      _genlep_TauMothInd.push_back(i_tau_Moth);

      int i_top_Moth = -1;
      int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
      if( i_gen_TopMoth > -1 ){
	for(int i_top=0; i_top<_n_gentop; i_top++){
	  if( gentop_index[i_top]==i_gen_TopMoth){
	    i_top_Moth = i_top;
	    break;
	  }
	}
      }      
      _genlep_TopMothInd.push_back(i_top_Moth);

      int i_W_Moth = -1;
      int i_gen_WMoth = (*_genpart_WMothInd)[i_gen];
      if( i_gen_WMoth > -1 ){
	for(int i_W=0; i_W<_n_genW; i_W++){
	  if( genW_index[i_W]==i_gen_WMoth){
	    i_W_Moth = i_W;
	    break;
	  }
	}
      }      
      _genlep_WMothInd.push_back(i_W_Moth);


    }


    for(int i_tauh=0; i_tauh<_n_gentauh; i_tauh++){

      int i_gen = gentauh_index[i_tauh];
      
      int i_tau_Moth = -1;
      int i_gen_TauMoth = (*_genpart_TauMothInd)[i_gen];
      if( i_gen_TauMoth > -1 ){
	for(int i_tau=0; i_tau<_n_gentau; i_tau++){
	  if( gentau_index[i_tau]==i_gen_TauMoth){
	    i_tau_Moth = i_tau;
	    break;
	  }
	}
      }
      _gentauh_TauMothInd.push_back(i_tau_Moth);

      int i_top_Moth = -1;
      int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
      if( i_gen_TopMoth > -1 ){
	for(int i_top=0; i_top<_n_gentop; i_top++){
	  if( gentop_index[i_top]==i_gen_TopMoth){
	    i_top_Moth = i_top;
	    break;
	  }
	}
      }      
      _gentauh_TopMothInd.push_back(i_top_Moth);

      int i_W_Moth = -1;
      int i_gen_WMoth = (*_genpart_WMothInd)[i_gen];
      if( i_gen_WMoth > -1 ){
	for(int i_W=0; i_W<_n_genW; i_W++){
	  if( genW_index[i_W]==i_gen_WMoth){
	    i_W_Moth = i_W;
	    break;
	  }
	}
      }      
      _gentauh_WMothInd.push_back(i_W_Moth);

    }

    
    for(int i_tau=0; i_tau<_n_gentau; i_tau++){

      int i_gen = gentau_index[i_tau];     

      int i_top_Moth = -1;
      int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
      if( i_gen_TopMoth > -1 ){
	for(int i_top=0; i_top<_n_gentop; i_top++){
	  if( gentop_index[i_top]==i_gen_TopMoth){
	    i_top_Moth = i_top;
	    break;
	  }
	}
      }      
      _gentau_TopMothInd.push_back(i_top_Moth);

      int i_W_Moth = -1;
      int i_gen_WMoth = (*_genpart_WMothInd)[i_gen];
      if( i_gen_WMoth > -1 ){
	for(int i_W=0; i_W<_n_genW; i_W++){
	  if( genW_index[i_W]==i_gen_WMoth){
	    i_W_Moth = i_W;
	    break;
	  }
	}
      }      
      _gentau_WMothInd.push_back(i_W_Moth);

      int i_H_Moth = -1;
      int i_gen_HMoth = (*_genpart_HMothInd)[i_gen];
      if( i_gen_HMoth > -1 ){
	for(int i_H=0; i_H<_n_genH; i_H++){
	  if( genH_index[i_H]==i_gen_HMoth){
	    i_H_Moth = i_H;
	    break;
	  }
	}
      }      
      _gentau_HMothInd.push_back(i_H_Moth);


    }


    for(int i_W=0; i_W<_n_genW; i_W++){

      int i_gen = genW_index[i_W];     

      int i_top_Moth = -1;
      int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
      if( i_gen_TopMoth > -1 ){
	for(int i_top=0; i_top<_n_gentop; i_top++){
	  if( gentop_index[i_top]==i_gen_TopMoth){
	    i_top_Moth = i_top;
	    break;
	  }
	}
      }      
      _genW_TopMothInd.push_back(i_top_Moth);


    }


    for(int i_b=0; i_b<_n_genb; i_b++){

      int i_gen = genb_index[i_b];     

      int i_top_Moth = -1;
      int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
      if( i_gen_TopMoth > -1 ){
	for(int i_top=0; i_top<_n_gentop; i_top++){
	  if( gentop_index[i_top]==i_gen_TopMoth){
	    i_top_Moth = i_top;
	    break;
	  }
	}
      }      
      _genb_TopMothInd.push_back(i_top_Moth);

      int i_W_Moth = -1;
      int i_gen_WMoth = (*_genpart_WMothInd)[i_gen];
      if( i_gen_WMoth > -1 ){
	for(int i_W=0; i_W<_n_genW; i_W++){
	  if( genW_index[i_W]==i_gen_WMoth){
	    i_W_Moth = i_W;
	    break;
	  }
	}
      }      
      _genb_WMothInd.push_back(i_W_Moth);


    }


    for(int i_q=0; i_q<_n_genq; i_q++){

      int i_gen = genq_index[i_q];     

      int i_top_Moth = -1;
      int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
      if( i_gen_TopMoth > -1 ){
	for(int i_top=0; i_top<_n_gentop; i_top++){
	  if( gentop_index[i_top]==i_gen_TopMoth){
	    i_top_Moth = i_top;
	    break;
	  }
	}
      }      
      _genq_TopMothInd.push_back(i_top_Moth);

      int i_W_Moth = -1;
      int i_gen_WMoth = (*_genpart_WMothInd)[i_gen];
      if( i_gen_WMoth > -1 ){
	for(int i_W=0; i_W<_n_genW; i_W++){
	  if( genW_index[i_W]==i_gen_WMoth){
	    i_W_Moth = i_W;
	    break;
	  }
	}
      }      
      _genq_WMothInd.push_back(i_W_Moth);


    }


    for(int i_nu=0; i_nu<_n_gennu; i_nu++){

      int i_gen = gennu_index[i_nu];
      
      int i_tau_Moth = -1;
      int i_gen_TauMoth = (*_genpart_TauMothInd)[i_gen];
      if( i_gen_TauMoth > -1 ){
	for(int i_tau=0; i_tau<_n_gentau; i_tau++){
	  if( gentau_index[i_tau]==i_gen_TauMoth){
	    i_tau_Moth = i_tau;
	    break;
	  }
	}
      }
      _gennu_TauMothInd.push_back(i_tau_Moth);

      int i_top_Moth = -1;
      int i_gen_TopMoth = (*_genpart_TopMothInd)[i_gen];
      if( i_gen_TopMoth > -1 ){
	for(int i_top=0; i_top<_n_gentop; i_top++){
	  if( gentop_index[i_top]==i_gen_TopMoth){
	    i_top_Moth = i_top;
	    break;
	  }
	}
      }      
      _gennu_TopMothInd.push_back(i_top_Moth);


      int i_W_Moth = -1;
      int i_gen_WMoth = (*_genpart_WMothInd)[i_gen];
      if( i_gen_WMoth > -1 ){
	for(int i_W=0; i_W<_n_genW; i_W++){
	  if( genW_index[i_W]==i_gen_WMoth){
	    i_W_Moth = i_W;
	    break;
	  }
	}
      }      
      _gennu_WMothInd.push_back(i_W_Moth);


    }



    //b + tau matching for PFJet30_CSVsort

    for(int i_PFJet30=0; i_PFJet30<_n_recoPFJet; i_PFJet30++){

	TLorentzVector jet( (_recoPFJet_CSVsort_px)[i_PFJet30], (_recoPFJet_CSVsort_py)[i_PFJet30], (_recoPFJet_CSVsort_pz)[i_PFJet30], (_recoPFJet_CSVsort_e)[i_PFJet30]);

	pair<int,float> pair_genb = find_i_dRmin_closest( jet,
							  _genb_px, _genb_py, _genb_pz, _genb_e );

	_recoPFJet_CSVsort_i_closest_genb.push_back(pair_genb.first);
	_recoPFJet_CSVsort_dR_closest_genb.push_back(pair_genb.second);  

	
	pair<int,float> pair_gentauh = find_i_dRmin_closest( jet,
							     _gentauh_px, _gentauh_py, _gentauh_pz, _gentauh_e );

	_recoPFJet_CSVsort_i_closest_gentauh.push_back(pair_gentauh.first);
	_recoPFJet_CSVsort_dR_closest_gentauh.push_back(pair_gentauh.second);



    }



    //Check lepton top/Higgs decay product
    for(unsigned int i_lepton=0; i_lepton<reco_leptons.size(); i_lepton++){

      int reco_TopMothInd = -1;
      int reco_HMothInd = -1;
      
      TLorentzVector lep=reco_leptons[i_lepton].second;
      int i_daughter = reco_leptons[i_lepton].first;
      pair<int,float> pair = find_i_dRmin_closest( lep,
						   _genlep_px, _genlep_py, _genlep_pz, _genlep_e );

      int i_genlep = pair.first;
      float dR = pair.second;
      

      //Check matching reco/gen lepton
      if(fabs((*_PDGIdDaughters)[i_daughter]) == fabs(_genlep_pdg[i_genlep]) && dR<0.1){

	bool isFromHardProcess = ( (_genlep_flags)[i_genlep] >> 8 ) & 1;
	bool isDirectTauDecayProduct = ( (_genlep_flags)[i_genlep] >> 4) & 1;
	bool isHardProcessTauDecayProduct = ( (_genlep_flags)[i_genlep] >> 9) & 1;
	int TauMothInd = (_genlep_TauMothInd)[i_genlep];
	int TopMothInd = (_genlep_TopMothInd)[i_genlep];
	int HMothInd = -1;
	bool isTauFromHardProcess = false;
	if(TauMothInd>=0){
	  HMothInd = (_gentau_HMothInd)[TauMothInd];
	  isTauFromHardProcess = ( (_gentau_flags)[TauMothInd] >> 8 ) & 1;
	}

	//Top
	if(TopMothInd>=0){

	  if( (_gentop_decayMode[TopMothInd]==1 || _gentop_decayMode[TopMothInd]==2) && isFromHardProcess)
	    reco_TopMothInd = TopMothInd;

	  else if( (_gentop_decayMode[TopMothInd]==3 || _gentop_decayMode[TopMothInd]==4) && isTauFromHardProcess && isDirectTauDecayProduct && isHardProcessTauDecayProduct)
	    reco_TopMothInd = TopMothInd;


	}

	//Higgs
	if(HMothInd>=0){
	  
	  if( (_genH_decayMode[HMothInd]==0 || _genH_decayMode[HMothInd]==1 || _genH_decayMode[HMothInd]==3 || _genH_decayMode[HMothInd]==4 || _genH_decayMode[HMothInd]==5) && isTauFromHardProcess && isDirectTauDecayProduct && isHardProcessTauDecayProduct)
	    reco_HMothInd = HMothInd;

	}
	  
      }

      _recolep_TopMothInd.push_back(reco_TopMothInd);
      _recolep_HMothInd.push_back(reco_HMothInd);
      

    }

    
    

    tree_new->Fill();

  }


  tree_new->Write();
  f_new->Close();


  return;

}
