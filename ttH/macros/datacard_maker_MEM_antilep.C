#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>

#include "Helpers.C"

float luminosity = 12900; //12.9 fb-1

float XS_ttH = 0.2586;
float XS_ttW = 0.2043;
float XS_ttZ = 0.2529;
float XS_TTLL_lowmass = 0.0283;
float XS_ttG = 3.697;
float XS_WpWp = 0.03711;
float XS_WZ = 4.102;
float XS_ZZ = 1.256;
float XS_ZZZ = 0.01398;
float XS_WZZ = 0.05565;
float XS_WWZ = 0.1651;
float XS_tZq = 0.0758;
float XS_TTTT = 0.009103;
float XS_ttbar_DL = 87.3;
float XS_ttbar_SLfromT = 182;
float XS_ttbar_SLfromTbar = 182;

vector<float> XS;

//MC

TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttH_genmatch/ttH_Hnonbb_split_2lSS_MEM_genmatch.root";
TString filename_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttV/ttW_*.root";
TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttV_genmatch/ttZ_split_2lSS_MEM_genmatch.root";
TString filename_TTLL_lowmass = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/topG/HTauTauTree_TTLL_lowmass_split.root";
TString filename_ttG = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/topG/HTauTauTree_ttG_split.root";
TString filename_WpWp = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/Rares_EW/HTauTauTree_WpWp_split.root";
TString filename_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/Diboson/HTauTauTree_WZ_split.root";
TString filename_ZZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/Diboson/HTauTauTree_ZZ_split.root";
TString filename_ZZZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/Rares_EW/HTauTauTree_ZZZ_split.root";
TString filename_WZZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/Rares_EW/HTauTauTree_WZZ_split.root";
TString filename_WWZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/Rares_EW/HTauTauTree_WWZ_split.root";
TString filename_tZq = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/ttV/HTauTauTree_tZq_split.root";
TString filename_TTTT = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/Rares_EW/HTauTauTree_TTTT_split.root";
TString filename_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160921.root";
TString filename_ttbar_SLfromT = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/TTJets/HTauTauTree_ttbar_SLfromT_split.root";
TString filename_ttbar_SLfromTbar = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/TTJets/HTauTauTree_ttbar_SLfromTbar_split.root";


TString filename_norm_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/nominal/ttV/ntuple_ttW_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/nominal/ttV/ntuple_ttZ_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_TTLL_lowmass = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/ttV/ntuple_TTLL_lowmass_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_ttG = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/topG/ntuple_ttG_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_WpWp = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/Rares_EW/ntuple_WpWp_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/Diboson/ntuple_WZ_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_ZZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/Diboson/ntuple_WZ_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_ZZZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_WZZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/Rares_EW/ntuple_WZZ_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_WWZ = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/Rares_EW/ntuple_WWZ_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_tZq = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/ttV/ntuple_tZq_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_TTTT = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/Rares_EW/ntuple_TTTT_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/nominal/TTJets/ntuple_ttbar_DL*.root";
TString filename_norm_ttbar_SLfromT = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_converted/TTJets/ntuple_ttbar_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_ttbar_SLfromTbar = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/TTJets/HTauTauTree_ttbar_SLfromTbar_split.root";

vector<TString> filename_MC;
vector<TString> filename_norm_MC;




//Data

TString filename_DoubleEG_2016B_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_*.root";
TString filename_MuonEG_2016B_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_*.root";
TString filename_DoubleMu_2016B_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_*.root";
TString filename_SingleMu_2016B_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/SingleMu_2016B_split_2lSS_lepMVA_CR_MEM_*.root";
TString filename_SingleEle_2016B_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_*.root";

TString filename_DoubleEG_2016C_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_*.root";
TString filename_MuonEG_2016C_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_*.root";
TString filename_DoubleMu_2016C_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_*.root";
TString filename_SingleMu_2016C_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/SingleMu_2016C_split_2lSS_lepMVA_CR_MEM_*.root";
TString filename_SingleEle_2016C_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_*.root";

TString filename_DoubleEG_2016D_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/DoubleEG_2016D_split_2lSS_lepMVA_CR_MEM_*.root";
TString filename_MuonEG_2016D_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/MuonEG_2016D_split_2lSS_lepMVA_CR_MEM_*.root";
TString filename_DoubleMu_2016D_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/DoubleMu_2016D_split_2lSS_lepMVA_CR_MEM_*.root";
TString filename_SingleMu_2016D_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/SingleMu_2016D_split_2lSS_lepMVA_CR_MEM_*.root";
TString filename_SingleEle_2016D_lepMVA_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/SingleEle_2016D_split_2lSS_lepMVA_CR_MEM_*.root";



TString filename_DoubleEG_2016B_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/DoubleEG_2016B_split_2lOS_CR_MEM_160916.root";
TString filename_MuonEG_2016B_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/MuonEG_2016B_split_2lOS_CR_MEM_160916.root";
TString filename_DoubleMu_2016B_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/DoubleMu_2016B_split_2lOS_CR_MEM_160916.root";
TString filename_SingleMu_2016B_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/SingleMu_2016B_split_2lOS_CR_MEM_160917.root";
TString filename_SingleEle_2016B_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/SingleEle_2016B_split_2lOS_CR_MEM_160918.root";

TString filename_DoubleEG_2016C_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/DoubleEG_2016C_split_2lOS_CR_MEM_160918.root";
TString filename_MuonEG_2016C_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/MuonEG_2016C_split_2lOS_CR_MEM_160919.root";
TString filename_DoubleMu_2016C_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/DoubleMu_2016C_split_2lOS_CR_MEM_160919.root";
TString filename_SingleMu_2016C_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/SingleMu_2016C_split_2lOS_CR_MEM_160919.root";
TString filename_SingleEle_2016C_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/SingleEle_2016C_split_2lOS_CR_MEM_160919.root";

TString filename_DoubleEG_2016D_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/DoubleEG_2016D_split_2lOS_CR_MEM_160920.root";
TString filename_MuonEG_2016D_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/MuonEG_2016D_split_2lOS_CR_MEM_160920.root";
TString filename_DoubleMu_2016D_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/DoubleMu_2016D_split_2lOS_CR_MEM_160920.root";
TString filename_SingleMu_2016D_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/SingleMu_2016D_split_2lOS_CR_MEM_160920.root";
TString filename_SingleEle_2016D_2lOS_CR = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/Data/SingleEle_2016D_split_2lOS_CR_MEM_160920.root";


vector<TString> filename_data_lepMVA_CR;
vector<TString> filename_data_2lOS_CR;
vector<TString> filename_data_SR;


vector<TString> MC_sample_name;

vector<TString> filename_MC_thu_unc;
vector<TString> MC_sample_name_thu_unc;


// MC JEC + TES

TString filename_ttH_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/JECup/ttH/HTauTauTree_ttH_Hnonbb_split_JECup_*.root";
TString filename_ttH_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/JECup/ttH/HTauTauTree_ttH_Hnonbb_split_JECdown_*.root";
TString filename_ttH_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/TESup/ttH/HTauTauTree_ttH_Hnonbb_split_TESup_*.root";
TString filename_ttH_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/TESdown/ttH/HTauTauTree_ttH_Hnonbb_split_TESdown_*.root";


TString filename_ttZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttZ_split_JECup_*.root";
TString filename_ttZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttZ_split_JECdown_*.root";
TString filename_ttZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/TESup/ttV/HTauTauTree_ttZ_split_TESup_*.root";
TString filename_ttZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttZ_split_TESdown_*.root";


TString filename_ttW_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttW_split_JECup_*.root";
TString filename_ttW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttW_split_JECdown_*.root";
TString filename_ttW_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/TESup/ttV/HTauTauTree_ttW_split_TESup_*.root";
TString filename_ttW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttW_split_TESdown_*.root";


vector<TString> filename_MC_JECup;
vector<TString> filename_MC_JECdown;
vector<TString> filename_MC_TESup;
vector<TString> filename_MC_TESdown;



void initialize(){

  XS.clear();
  filename_MC.clear();
  filename_norm_MC.clear();
  MC_sample_name.clear();
  filename_data_lepMVA_CR.clear();
  filename_data_2lOS_CR.clear();
  filename_MC_thu_unc.clear();
  MC_sample_name_thu_unc.clear();

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH");
  /*filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);*/

  /*XS.push_back(XS_ttW);
  filename_MC.push_back(filename_ttW);
  filename_norm_MC.push_back(filename_norm_ttW);
  MC_sample_name.push_back("ttW");*/
  /*filename_MC_JECup.push_back(filename_ttW_JECup);
  filename_MC_JECdown.push_back(filename_ttW_JECdown);
  filename_MC_TESup.push_back(filename_ttW_TESup);
  filename_MC_TESdown.push_back(filename_ttW_TESdown);*/

  XS.push_back(XS_ttZ);
  filename_MC.push_back(filename_ttZ);
  filename_norm_MC.push_back(filename_norm_ttZ);
  MC_sample_name.push_back("ttZ");
  /*filename_MC_JECup.push_back(filename_ttZ_JECup);
  filename_MC_JECdown.push_back(filename_ttZ_JECdown);
  filename_MC_TESup.push_back(filename_ttZ_TESup);
  filename_MC_TESdown.push_back(filename_ttZ_TESdown);*/

  /*XS.push_back(XS_TTLL_lowmass);
  filename_MC.push_back(filename_TTLL_lowmass);
  filename_norm_MC.push_back(filename_norm_TTLL_lowmass);
  MC_sample_name.push_back("TTLL_lowmass");

  XS.push_back(XS_ttG);
  filename_MC.push_back(filename_ttG);
  filename_norm_MC.push_back(filename_norm_ttG);
  MC_sample_name.push_back("ttG");

  XS.push_back(XS_WpWp);
  filename_MC.push_back(filename_WpWp);
  filename_norm_MC.push_back(filename_norm_WpWp);
  MC_sample_name.push_back("WpWp");

  XS.push_back(XS_WZ);
  filename_MC.push_back(filename_WZ);
  filename_norm_MC.push_back(filename_norm_WZ);
  MC_sample_name.push_back("WZ");

  XS.push_back(XS_ZZ);
  filename_MC.push_back(filename_ZZ);
  filename_norm_MC.push_back(filename_norm_ZZ);
  MC_sample_name.push_back("ZZ");

  XS.push_back(XS_ZZZ);
  filename_MC.push_back(filename_ZZZ);
  filename_norm_MC.push_back(filename_norm_ZZZ);
  MC_sample_name.push_back("ZZZ");

  XS.push_back(XS_WZZ);
  filename_MC.push_back(filename_WZZ);
  filename_norm_MC.push_back(filename_norm_WZZ);
  MC_sample_name.push_back("WZZ");

  XS.push_back(XS_WWZ);
  filename_MC.push_back(filename_WWZ);
  filename_norm_MC.push_back(filename_norm_WWZ);
  MC_sample_name.push_back("WWZ");

  XS.push_back(XS_tZq);
  filename_MC.push_back(filename_tZq);
  filename_norm_MC.push_back(filename_norm_tZq);
  MC_sample_name.push_back("tZq");

  XS.push_back(XS_TTTT);
  filename_MC.push_back(filename_TTTT);
  filename_norm_MC.push_back(filename_norm_TTTT);
  MC_sample_name.push_back("TTTT");*/


  /*filename_data_lepMVA_CR.push_back(filename_DoubleEG_2016B_lepMVA_CR);
  filename_data_lepMVA_CR.push_back(filename_MuonEG_2016B_lepMVA_CR);
  filename_data_lepMVA_CR.push_back(filename_DoubleMu_2016B_lepMVA_CR);
  filename_data_lepMVA_CR.push_back(filename_SingleMu_2016B_lepMVA_CR);
  filename_data_lepMVA_CR.push_back(filename_SingleEle_2016B_lepMVA_CR);
	       
  filename_data_lepMVA_CR.push_back(filename_DoubleEG_2016C_lepMVA_CR);
  filename_data_lepMVA_CR.push_back(filename_MuonEG_2016C_lepMVA_CR);
  filename_data_lepMVA_CR.push_back(filename_DoubleMu_2016C_lepMVA_CR);
  filename_data_lepMVA_CR.push_back(filename_SingleMu_2016C_lepMVA_CR);
  filename_data_lepMVA_CR.push_back(filename_SingleEle_2016C_lepMVA_CR);
	       
  filename_data_lepMVA_CR.push_back(filename_DoubleEG_2016D_lepMVA_CR);
  filename_data_lepMVA_CR.push_back(filename_MuonEG_2016D_lepMVA_CR);
  filename_data_lepMVA_CR.push_back(filename_DoubleMu_2016D_lepMVA_CR);
  filename_data_lepMVA_CR.push_back(filename_SingleMu_2016D_lepMVA_CR);
  filename_data_lepMVA_CR.push_back(filename_SingleEle_2016D_lepMVA_CR);

  filename_data_2lOS_CR.push_back(filename_DoubleEG_2016B_2lOS_CR);
  filename_data_2lOS_CR.push_back(filename_MuonEG_2016B_2lOS_CR);
  filename_data_2lOS_CR.push_back(filename_DoubleMu_2016B_2lOS_CR);
  filename_data_2lOS_CR.push_back(filename_SingleMu_2016B_2lOS_CR);
  filename_data_2lOS_CR.push_back(filename_SingleEle_2016B_2lOS_CR);
	       	
  filename_data_2lOS_CR.push_back(filename_DoubleEG_2016C_2lOS_CR);
  filename_data_2lOS_CR.push_back(filename_MuonEG_2016C_2lOS_CR);
  filename_data_2lOS_CR.push_back(filename_DoubleMu_2016C_2lOS_CR);
  filename_data_2lOS_CR.push_back(filename_SingleMu_2016C_2lOS_CR);
  filename_data_2lOS_CR.push_back(filename_SingleEle_2016C_2lOS_CR);
	       	
  filename_data_2lOS_CR.push_back(filename_DoubleEG_2016D_2lOS_CR);
  filename_data_2lOS_CR.push_back(filename_MuonEG_2016D_2lOS_CR);
  filename_data_2lOS_CR.push_back(filename_DoubleMu_2016D_2lOS_CR);
  filename_data_2lOS_CR.push_back(filename_SingleMu_2016D_2lOS_CR);
  filename_data_2lOS_CR.push_back(filename_SingleEle_2016D_2lOS_CR);*/


  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH");
  
  //filename_MC_thu_unc.push_back(filename_ttW);
  //MC_sample_name_thu_unc.push_back("ttW");

  filename_MC_thu_unc.push_back(filename_ttZ);
  MC_sample_name_thu_unc.push_back("ttZ");

  /*filename_MC_thu_unc.push_back(filename_TTLL_lowmass);
  MC_sample_name_thu_unc.push_back("TTLL_lowmass");

  filename_MC_thu_unc.push_back(filename_ttG);
  MC_sample_name_thu_unc.push_back("ttG");*/


}







void datacard_maker(TString var, int nbin, float xmin, float xmax,
		    TString cut,
		    TString file){



  initialize();


  
  vector<TString> cat_names;
  cat_names.push_back("ttH_2lss_1tau");

  vector<int> cat;
  cat.push_back(11);

  vector<int> cat_flips;
  vector<int> cat_fakes;
  for(unsigned int i=0;i<cat.size();i++){
    cat_flips.push_back(-1*cat[i]);
    cat_fakes.push_back(30+cat[i]);
  }
  

  TFile* f_new = TFile::Open(file,"RECREATE");
  


  for(unsigned int i_cat=0;i_cat<cat_names.size();i_cat++){

    cout<<cat_names[i_cat]<<endl;

    f_new->cd();

    //////////////////////////////////////////
    //////////////////////////////////////////
    /////////          NOMINAL        ////////
    //////////////////////////////////////////
    //////////////////////////////////////////


    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      TH1F* h_MC = single_plot(filename_MC[i_MC],
			       "T",
			       var,
			       Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
			       nbin,xmin,xmax);

      cout<<MC_sample_name[i_MC]<<endl;
      cout<<h_MC->Integral()<<endl;

      TH1F* h_MC_norm = single_plot(filename_norm_MC[i_MC],
				     "HTauTauTree",
				     "1",
				     "MC_weight*PU_weight",
				    3,0,3);

      h_MC->Scale(luminosity*XS[i_MC]/h_MC_norm->Integral());
      h_MC->SetNameTitle("h_"+MC_sample_name[i_MC],"h_"+MC_sample_name[i_MC]);
      h_MC->Write();

      cout<<h_MC->Integral()<<endl;




    }


    TH1F* h_ttH_norm =single_plot(filename_norm_ttH,
				  "HTauTauTree",
				  "1",
				  "MC_weight*PU_weight",
				  3,0,3);
    
    TH1F* h_ttH_tautau =single_plot(filename_ttH,
				    "T",
				    var,
				    Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && genH_decayMode[1]<=5 && isTrig &&",cat[i_cat]) + cut + ")",
				    nbin,xmin,xmax);
    
    
    h_ttH_tautau->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
    h_ttH_tautau->SetNameTitle("h_ttH_htt","h_ttH_htt");
    h_ttH_tautau->Write();
    

    TH1F* h_ttH_WW =single_plot(filename_ttH,
				"T",
				var,
				Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && genH_decayMode[1]>5 && n_genW==4 && isTrig &&",cat[i_cat]) + cut + ")",
				nbin,xmin,xmax);
  
    
    h_ttH_WW->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
    h_ttH_WW->SetNameTitle("h_ttH_hww","h_ttH_hww");
    h_ttH_WW->Write();

    TH1F* h_ttH_ZZ =single_plot(filename_ttH,
				"T",
				var,
				Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && genH_decayMode[1]>5 && n_genZ==2 && isTrig &&",cat[i_cat]) + cut + ")",
				nbin,xmin,xmax);
  
    
    h_ttH_ZZ->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
    h_ttH_ZZ->SetNameTitle("h_ttH_hzz","h_ttH_hzz");
    h_ttH_ZZ->Write();


    
    //TTZ = ttZ + TTLL_lowmass + ttG    
    TH1F* h_TTZ = (TH1F*)f_new->Get("h_ttZ");
    /*h_TTZ->Add( (TH1F*)f_new->Get("h_TTLL_lowmass") );
      h_TTZ->Add( (TH1F*)f_new->Get("h_ttG") );*/
    h_TTZ->SetNameTitle("h_TTZ","h_TTZ");
    h_TTZ->Write();

    
    //Diboson = WZ + ZZ
    /*TH1F* h_Diboson = (TH1F*)f_new->Get("h_WZ");
    h_Diboson->Add( (TH1F*)f_new->Get("h_ZZ") );
    h_Diboson->SetNameTitle("h_Diboson","h_Diboson");
    h_Diboson->Write();

    
    //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
    TH1F* h_Rares = (TH1F*)f_new->Get("h_ZZZ");
    h_Rares->Add( (TH1F*)f_new->Get("h_WZZ") );
    h_Rares->Add( (TH1F*)f_new->Get("h_WWZ") );
    h_Rares->Add( (TH1F*)f_new->Get("h_tZq") );
    h_Rares->Add( (TH1F*)f_new->Get("h_TTTT") );
    h_Rares->SetNameTitle("h_Rares","h_Rares");
    h_Rares->Write();

    */
    
    //Fakes
    
    /*TH1F* h_fakes =single_plot(filename_data_lepMVA_CR,
			       "T",
			       var,
			       Form("event_weight_ttH*(category==%i && isTrig &&",cat_fakes[i_cat]) + cut + ")",
			       nbin,xmin,xmax);

    
    h_fakes->Scale(luminosity/12900.); //Data files for 12.9 fb-1
    h_fakes->SetNameTitle("h_fakes","h_fakes");
    h_fakes->Write();*/


    //Fakes MC

    /*TH1F* h_fakes_DL_MC =single_plot(filename_ttbar_DL,
				     "T",
				     var,
				     Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*event_weight_ttH*(category==%i && isTrig &&",cat_fakes[i_cat]) + cut + ")",
				     nbin,xmin,xmax);

    TH1F* h_fakes_DL_MC_norm =single_plot(filename_norm_ttbar_DL,
					  "HTauTauTree",
					  "1",
					  "MC_weight*PU_weight",
					  3,0,3);
    
    h_fakes_DL_MC->Scale(luminosity*XS_ttbar_DL/h_fakes_DL_MC_norm->Integral());
    h_fakes_DL_MC->SetNameTitle("h_fakes_DL_MC","h_fakes_DL_MC");
    h_fakes_DL_MC->Write();*/


    /*TH1F* h_fakes_SLfromT_MC =single_plot(filename_ttbar_SLfromT,
					  "HTauTauTree_2lSS_lepMVA_CR",
					  var,
					  Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*event_weight_ttH*(category==%i && isTrig)",cat_fakes[i_cat]),					
					  nbin,xmin,xmax);

    TH1F* h_fakes_SLfromT_MC_norm =single_plot(filename_norm_ttbar_SLfromT,
					       "HTauTauTree",
					       "1",
					       "MC_weight*PU_weight",
					       3,0,3);
    
    h_fakes_SLfromT_MC->Scale(luminosity*XS_ttbar_SLfromT/h_fakes_SLfromT_MC_norm->Integral());
    h_fakes_SLfromT_MC->SetNameTitle("h_fakes_SLfromT_MC","h_fakes_SLfromT_MC");
    h_fakes_SLfromT_MC->Write();
    

    TH1F* h_fakes_SLfromTbar_MC =single_plot(filename_ttbar_SLfromTbar,
					     "HTauTauTree_2lSS_lepMVA_CR",
					     var,
					     Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*event_weight_ttH*(category==%i && isTrig)",cat_fakes[i_cat]),				
					     nbin,xmin,xmax);
    
    TH1F* h_fakes_SLfromTbar_MC_norm =single_plot(filename_norm_ttbar_SLfromTbar,
						  "HTauTauTree",
						  "1",
						  "MC_weight*PU_weight",
						  3,0,3);
    
    h_fakes_SLfromTbar_MC->Scale(luminosity*XS_ttbar_SLfromTbar/h_fakes_SLfromTbar_MC_norm->Integral());
    h_fakes_SLfromTbar_MC->SetNameTitle("h_fakes_SLfromTbar_MC","h_fakes_SLfromTbar_MC");
    h_fakes_SLfromTbar_MC->Write();*/
    
    
    //Fakes MC
    //TH1F* h_fakes_MC = h_fakes_DL_MC;
    //h_fakes_MC->Add(h_fakes_SLfromT_MC);
    //h_fakes_MC->Add(h_fakes_SLfromTbar_MC);
    //h_fakes_MC->SetNameTitle("h_fakes_MC","h_fakes_MC");
    //h_fakes_MC->Write();


    //Charge flips
    /*TH1F* h_flips =single_plot(filename_data_2lOS_CR,
			       "T",
			       var,
			       Form("event_weight_ttH*(category==%i && isTrig &&",cat_flips[i_cat]) + cut + ")",
			       nbin,xmin,xmax);
    
    h_flips->Scale(luminosity/12900.); //Data files for 12.9 fb-1
    h_flips->SetNameTitle("h_flips","h_flips");
    h_flips->Write();*/
 
    
    
    //Data
    
    /*TH1F* h_data_obs =single_plot(filename_data,
      "HTauTauTree_2lSS",
      var,
      Form("(category==%i && isTrig)",cat[i]),		
      nbin,xmin,xmax);
      
      h_data_obs->Scale(luminosity/12900.); //Data files for 12.9 fb-1
      
      h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
      h_data_obs->Write();
      h.push_back(h_data_obs);*/


    TH1F* h_data_obs = (TH1F*)f_new->Get("h_ttH");
    //h_data_obs->Add( (TH1F*)f_new->Get("h_ttW") );
    h_data_obs->Add( (TH1F*)f_new->Get("h_TTZ") );
    /*h_data_obs->Add( (TH1F*)f_new->Get("h_WpWp") );
    h_data_obs->Add( (TH1F*)f_new->Get("h_Diboson") );
    h_data_obs->Add( (TH1F*)f_new->Get("h_Rares") );*/
    //h_data_obs->Add( (TH1F*)f_new->Get("h_fakes") );
    //h_data_obs->Add( (TH1F*)f_new->Get("h_flips") );
    h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
    h_data_obs->Write();

    
    //////////////////////////////////////////
    //////////////////////////////////////////
    /////////       SYSTEMATICS       ////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    
    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      float norm = ((TH1F*)f_new->Get("h_"+MC_sample_name[i_MC]))->Integral();
		    
      TH1F* h_MC_btag_up = single_plot(filename_MC[i_MC],
				       "T",
				       var,
				       Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight_up*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
				       nbin,xmin,xmax);
      
      h_MC_btag_up->Scale(norm/h_MC_btag_up->Integral());
      h_MC_btag_up->SetNameTitle("h_"+MC_sample_name[i_MC]+"_btagUp","h_"+MC_sample_name[i_MC]+"_btagUp");
      h_MC_btag_up->Write();

      
      TH1F* h_MC_btag_down = single_plot(filename_MC[i_MC],
					 "T",
					 var,
					 Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight_down*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
					 nbin,xmin,xmax);
      
      h_MC_btag_down->Scale(norm/h_MC_btag_down->Integral());
      h_MC_btag_down->SetNameTitle("h_"+MC_sample_name[i_MC]+"_btagDown","h_"+MC_sample_name[i_MC]+"_btagDown");
      h_MC_btag_down->Write();

    }


    //TTZ = ttZ + TTLL_lowmass + ttG    
    TH1F* h_TTZ_btag_up = (TH1F*)f_new->Get("h_ttZ_btagUp");
    /*h_TTZ_btag_up->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_btag_up") );
      h_TTZ_btag_up->Add( (TH1F*)f_new->Get("h_ttG_btag_up") );*/
    h_TTZ_btag_up->SetNameTitle("h_TTZ_btagUp","h_TTZ_btagUp");
    h_TTZ_btag_up->Write();

    TH1F* h_TTZ_btag_down = (TH1F*)f_new->Get("h_ttZ_btagDown");
    /*h_TTZ_btag_down->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_btag_down") );
      h_TTZ_btag_down->Add( (TH1F*)f_new->Get("h_ttG_btag_down") );*/
    h_TTZ_btag_down->SetNameTitle("h_TTZ_btagDown","h_TTZ_btagDown");
    h_TTZ_btag_down->Write();

    //Diboson = WZ + ZZ
    /*TH1F* h_Diboson_btag_up = (TH1F*)f_new->Get("h_WZ_btag_up");
    h_Diboson_btag_up->Add( (TH1F*)f_new->Get("h_ZZ_btag_up") );
    h_Diboson_btag_up->SetNameTitle("h_Diboson_btag_up","h_Diboson_btag_up");
    h_Diboson_btag_up->Write();

    TH1F* h_Diboson_btag_down = (TH1F*)f_new->Get("h_WZ_btag_down");
    h_Diboson_btag_down->Add( (TH1F*)f_new->Get("h_ZZ_btag_down") );
    h_Diboson_btag_down->SetNameTitle("h_Diboson_btag_down","h_Diboson_btag_down");
    h_Diboson_btag_down->Write();
    
    //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
    TH1F* h_Rares_btag_up = (TH1F*)f_new->Get("h_ZZZ_btag_up");
    h_Rares_btag_up->Add( (TH1F*)f_new->Get("h_WZZ_btag_up") );
    h_Rares_btag_up->Add( (TH1F*)f_new->Get("h_WWZ_btag_up") );
    h_Rares_btag_up->Add( (TH1F*)f_new->Get("h_tZq_btag_up") );
    h_Rares_btag_up->Add( (TH1F*)f_new->Get("h_TTTT_btag_up") );
    h_Rares_btag_up->Write();

    TH1F* h_Rares_btag_down = (TH1F*)f_new->Get("h_ZZZ_btag_down");
    h_Rares_btag_down->Add( (TH1F*)f_new->Get("h_WZZ_btag_down") );
    h_Rares_btag_down->Add( (TH1F*)f_new->Get("h_WWZ_btag_down") );
    h_Rares_btag_down->Add( (TH1F*)f_new->Get("h_tZq_btag_down") );
    h_Rares_btag_down->Add( (TH1F*)f_new->Get("h_TTTT_btag_down") );
    h_Rares_btag_down->Write();*/

    for(unsigned i_MC=0;i_MC<MC_sample_name_thu_unc.size();i_MC++){

      float norm = ((TH1F*)f_new->Get("h_"+MC_sample_name_thu_unc[i_MC]))->Integral();
		    
      TH1F* h_MC_x1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "T",
				     var,
				     Form("MC_weight_scale_muF2*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
				     nbin,xmin,xmax);
      
      h_MC_x1_up->Scale(norm/h_MC_x1_up->Integral());
      h_MC_x1_up->SetNameTitle("h_"+MC_sample_name_thu_unc[i_MC]+"_x1Up","h_"+MC_sample_name_thu_unc[i_MC]+"_x1Up");
      h_MC_x1_up->Write();

      TH1F* h_MC_x1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "T",
				       var,
				       Form("MC_weight_scale_muF0p5*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
				       nbin,xmin,xmax);
      
      h_MC_x1_down->Scale(norm/h_MC_x1_down->Integral());
      h_MC_x1_down->SetNameTitle("h_"+MC_sample_name_thu_unc[i_MC]+"_x1Down","h_"+MC_sample_name_thu_unc[i_MC]+"_x1Down");
      h_MC_x1_down->Write();

      TH1F* h_MC_y1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "T",
				     var,
				     Form("MC_weight_scale_muR2*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
				     nbin,xmin,xmax);
      
      h_MC_y1_up->Scale(norm/h_MC_y1_up->Integral());
      h_MC_y1_up->SetNameTitle("h_"+MC_sample_name_thu_unc[i_MC]+"_y1Up","h_"+MC_sample_name_thu_unc[i_MC]+"_y1Up");
      h_MC_y1_up->Write();

      TH1F* h_MC_y1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "T",
				       var,
				       Form("MC_weight_scale_muR0p5*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
				       nbin,xmin,xmax);
      
      h_MC_y1_down->Scale(norm/h_MC_y1_down->Integral());
      h_MC_y1_down->SetNameTitle("h_"+MC_sample_name_thu_unc[i_MC]+"_y1Down","h_"+MC_sample_name_thu_unc[i_MC]+"_y1Down");
      h_MC_y1_down->Write();
      
 

    }


    //TTZ = ttZ + TTLL_lowmass + ttG    
    TH1F* h_TTZ_x1_up = (TH1F*)f_new->Get("h_ttZ_x1Up");
    /*h_TTZ_x1_up->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_x1_up") );
      h_TTZ_x1_up->Add( (TH1F*)f_new->Get("h_ttG_x1_up") );*/
    h_TTZ_x1_up->SetNameTitle("h_TTZ_x1Up","h_TTZ_x1Up");
    h_TTZ_x1_up->Write();

    TH1F* h_TTZ_x1_down = (TH1F*)f_new->Get("h_ttZ_x1Down");
    /*h_TTZ_x1_down->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_x1_down") );
      h_TTZ_x1_down->Add( (TH1F*)f_new->Get("h_ttG_x1_down") );*/
    h_TTZ_x1_down->SetNameTitle("h_TTZ_x1_down","h_TTZ_x1Down");
    h_TTZ_x1_down->Write();

    TH1F* h_TTZ_y1_up = (TH1F*)f_new->Get("h_ttZ_y1Up");
    /*h_TTZ_y1_up->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_y1_up") );
      h_TTZ_y1_up->Add( (TH1F*)f_new->Get("h_ttG_y1_up") );*/
    h_TTZ_y1_up->SetNameTitle("h_TTZ_y1_up","h_TTZ_y1Up");
    h_TTZ_y1_up->Write();

    TH1F* h_TTZ_y1_down = (TH1F*)f_new->Get("h_ttZ_y1Down");
    /*h_TTZ_y1_down->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_y1_down") );
      h_TTZ_y1_down->Add( (TH1F*)f_new->Get("h_ttG_y1_down") );*/
    h_TTZ_y1_down->SetNameTitle("h_TTZ_y1_down","h_TTZ_y1Down");
    h_TTZ_y1_down->Write();




    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){
      
      /*float norm = ((TH1F*)f_new->Get("h_"+MC_sample_name[i_MC]))->Integral();
      
      TH1F* h_MC_JEC_up = single_plot(filename_MC_JECup[i_MC],
				      "HTauTauTree_2lSS",
				      var,
				      Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig)",cat[i_cat]),
				      nbin,xmin,xmax);
      
      h_MC_JEC_up->Scale(norm/h_MC_JEC_up->Integral());
      h_MC_JEC_up->SetNameTitle("h_"+MC_sample_name[i_MC]+"_JECUp","h_"+MC_sample_name[i_MC]+"_JECUp");
      h_MC_JEC_up->Write();

      
      TH1F* h_MC_JEC_down = single_plot(filename_MC_JECdown[i_MC],
					"HTauTauTree_2lSS",
					var,
					Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig)",cat[i_cat]),
					nbin,xmin,xmax);
      
      h_MC_JEC_down->Scale(norm/h_MC_JEC_down->Integral());
      h_MC_JEC_down->SetNameTitle("h_"+MC_sample_name[i_MC]+"_JECDown","h_"+MC_sample_name[i_MC]+"_JECDown");
      h_MC_JEC_down->Write();

      TH1F* h_MC_TES_up = single_plot(filename_MC_TESup[i_MC],
				      "HTauTauTree_2lSS",
				      var,
				      Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig)",cat[i_cat]),
				      nbin,xmin,xmax);
      
      h_MC_TES_up->Scale(norm/h_MC_TES_up->Integral());
      h_MC_TES_up->SetNameTitle("h_"+MC_sample_name[i_MC]+"_TES_up","h_"+MC_sample_name[i_MC]+"_TES_up");
      h_MC_TES_up->Write();*/

      
      /*TH1F* h_MC_TES_down = single_plot(filename_MC_TESdown[i_MC],
					"HTauTauTree_2lSS",
					var,
					Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig)",cat[i_cat]),
					nbin,xmin,xmax);
      
      h_MC_TES_down->Scale(norm/h_MC_TES_down->Integral());
      h_MC_TES_down->SetNameTitle("h_"+MC_sample_name[i_MC]+"_TES_down","h_"+MC_sample_name[i_MC]+"_TES_down");
      h_MC_TES_down->Write();*/

    }


    //TTZ = ttZ + TTLL_lowmass + ttG    
    /*TH1F* h_TTZ_JEC_up = (TH1F*)f_new->Get("h_ttZ_JECUp");
    h_TTZ_JEC_up->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_JEC_up") );
      h_TTZ_JEC_up->Add( (TH1F*)f_new->Get("h_ttG_JEC_up") );
    h_TTZ_JEC_up->SetNameTitle("h_TTZ_JECUp","h_TTZ_JECUp");
    h_TTZ_JEC_up->Write();

    TH1F* h_TTZ_JEC_down = (TH1F*)f_new->Get("h_ttZ_JECDown");
    h_TTZ_JEC_down->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_JEC_down") );
      h_TTZ_JEC_down->Add( (TH1F*)f_new->Get("h_ttG_JEC_down") );
    h_TTZ_JEC_down->SetNameTitle("h_TTZ_JECDown","h_TTZ_JECDown");
    h_TTZ_JEC_down->Write();

    TH1F* h_TTZ_TES_up = (TH1F*)f_new->Get("h_ttZ_TES_up");
    h_TTZ_TES_up->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_TES_up") );
      h_TTZ_TES_up->Add( (TH1F*)f_new->Get("h_ttG_TES_up") );
    h_TTZ_TES_up->SetNameTitle("h_TTZ_TES_up","h_TTZ_TES_up");
    h_TTZ_TES_up->Write();*/

    //TH1F* h_TTZ_TES_down = (TH1F*)f_new->Get("h_ttZ_TES_down");
    /* h_TTZ_TES_down->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_TES_down") );
       h_TTZ_TES_down->Add( (TH1F*)f_new->Get("h_ttG_TES_down") );*/
    //h_TTZ_TES_down->SetNameTitle("h_TTZ_TES_down","h_TTZ_TES_down");
    //h_TTZ_TES_down->Write();

    //Diboson = WZ + ZZ
    /*TH1F* h_Diboson_JEC_up = (TH1F*)f_new->Get("h_WZ_JEC_up");
    h_Diboson_JEC_up->Add( (TH1F*)f_new->Get("h_ZZ_JEC_up") );
    h_Diboson_JEC_up->SetNameTitle("h_Diboson_JEC_up","h_Diboson_JEC_up");
    h_Diboson_JEC_up->Write();

    TH1F* h_Diboson_JEC_down = (TH1F*)f_new->Get("h_WZ_JEC_down");
    h_Diboson_JEC_down->Add( (TH1F*)f_new->Get("h_ZZ_JEC_down") );
    h_Diboson_JEC_down->SetNameTitle("h_Diboson_JEC_down","h_Diboson_JEC_down");
    h_Diboson_JEC_down->Write();

    TH1F* h_Diboson_TES_up = (TH1F*)f_new->Get("h_WZ_TES_up");
    h_Diboson_TES_up->Add( (TH1F*)f_new->Get("h_ZZ_TES_up") );
    h_Diboson_TES_up->SetNameTitle("h_Diboson_TES_up","h_Diboson_TES_up");
    h_Diboson_TES_up->Write();

    TH1F* h_Diboson_TES_down = (TH1F*)f_new->Get("h_WZ_TES_down");
    h_Diboson_TES_down->Add( (TH1F*)f_new->Get("h_ZZ_TES_down") );
    h_Diboson_TES_down->SetNameTitle("h_Diboson_TES_down","h_Diboson_TES_down");
    h_Diboson_TES_down->Write();
    
    //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
    TH1F* h_Rares_JEC_up = (TH1F*)f_new->Get("h_ZZZ_JEC_up");
    h_Rares_JEC_up->Add( (TH1F*)f_new->Get("h_WZZ_JEC_up") );
    h_Rares_JEC_up->Add( (TH1F*)f_new->Get("h_WWZ_JEC_up") );
    h_Rares_JEC_up->Add( (TH1F*)f_new->Get("h_tZq_JEC_up") );
    h_Rares_JEC_up->Add( (TH1F*)f_new->Get("h_TTTT_JEC_up") );
    h_Rares_JEC_up->Write();

    TH1F* h_Rares_JEC_down = (TH1F*)f_new->Get("h_ZZZ_JEC_down");
    h_Rares_JEC_down->Add( (TH1F*)f_new->Get("h_WZZ_JEC_down") );
    h_Rares_JEC_down->Add( (TH1F*)f_new->Get("h_WWZ_JEC_down") );
    h_Rares_JEC_down->Add( (TH1F*)f_new->Get("h_tZq_JEC_down") );
    h_Rares_JEC_down->Add( (TH1F*)f_new->Get("h_TTTT_JEC_down") );
    h_Rares_JEC_down->Write();

    TH1F* h_Rares_TES_up = (TH1F*)f_new->Get("h_ZZZ_TES_up");
    h_Rares_TES_up->Add( (TH1F*)f_new->Get("h_WZZ_TES_up") );
    h_Rares_TES_up->Add( (TH1F*)f_new->Get("h_WWZ_TES_up") );
    h_Rares_TES_up->Add( (TH1F*)f_new->Get("h_tZq_TES_up") );
    h_Rares_TES_up->Add( (TH1F*)f_new->Get("h_TTTT_TES_up") );
    h_Rares_TES_up->Write();

    TH1F* h_Rares_TES_down = (TH1F*)f_new->Get("h_ZZZ_TES_down");
    h_Rares_TES_down->Add( (TH1F*)f_new->Get("h_WZZ_TES_down") );
    h_Rares_TES_down->Add( (TH1F*)f_new->Get("h_WWZ_TES_down") );
    h_Rares_TES_down->Add( (TH1F*)f_new->Get("h_tZq_TES_down") );
    h_Rares_TES_down->Add( (TH1F*)f_new->Get("h_TTTT_TES_down") );
    h_Rares_TES_down->Write();*/





  }







  f_new->Close();


}








void datacard_maker(TString var, int nbin, double* x,
		    TString cut,
		    TString file){



  initialize();


  
  vector<TString> cat_names;
  cat_names.push_back("ttH_2lss_1tau");

  vector<int> cat;
  cat.push_back(11);

  vector<int> cat_flips;
  vector<int> cat_fakes;
  for(unsigned int i=0;i<cat.size();i++){
    cat_flips.push_back(-1*cat[i]);
    cat_fakes.push_back(30+cat[i]);
  }
  

  TFile* f_new = TFile::Open(file,"RECREATE");
  


  for(unsigned int i_cat=0;i_cat<cat_names.size();i_cat++){

    cout<<cat_names[i_cat]<<endl;

    f_new->cd();

    //////////////////////////////////////////
    //////////////////////////////////////////
    /////////          NOMINAL        ////////
    //////////////////////////////////////////
    //////////////////////////////////////////


    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      TH1F* h_MC = single_plot(filename_MC[i_MC],
			       "T",
			       var,
			       Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
			       nbin, x);

      TH1F* h_MC_norm = single_plot(filename_norm_MC[i_MC],
				     "HTauTauTree",
				     "1",
				     "MC_weight*PU_weight",
				    3,0,3);

      h_MC->Scale(luminosity*XS[i_MC]/h_MC_norm->Integral());
      h_MC->SetNameTitle("h_"+MC_sample_name[i_MC],"h_"+MC_sample_name[i_MC]);
      h_MC->Write();

    }


    TH1F* h_ttH_norm =single_plot(filename_norm_ttH,
				  "HTauTauTree",
				  "1",
				  "MC_weight*PU_weight",
				  3,0,3);
    
    TH1F* h_ttH_tautau =single_plot(filename_ttH,
				    "T",
				    var,
				    Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && genH_decayMode[1]<=5 && isTrig &&",cat[i_cat]) + cut + ")",
				    nbin, x);
    
    
    h_ttH_tautau->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
    h_ttH_tautau->SetNameTitle("h_ttH_htt","h_ttH_htt");
    h_ttH_tautau->Write();
    
    TH1F* h_ttH_WW =single_plot(filename_ttH,
				"T",
				var,
				Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && genH_decayMode[1]>5 && n_genW==4 && isTrig &&",cat[i_cat]) + cut + ")",
				nbin, x);
  
    
    h_ttH_WW->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
    h_ttH_WW->SetNameTitle("h_ttH_hww","h_ttH_hww");
    h_ttH_WW->Write();

    TH1F* h_ttH_ZZ =single_plot(filename_ttH,
				"T",
				var,
				Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && genH_decayMode[1]>5 && n_genZ==2 && isTrig &&",cat[i_cat]) + cut + ")",
				nbin, x);
  
    
    h_ttH_ZZ->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
    h_ttH_ZZ->SetNameTitle("h_ttH_hzz","h_ttH_hzz");
    h_ttH_ZZ->Write();


    
    //TTZ = ttZ + TTLL_lowmass + ttG    
    TH1F* h_TTZ = (TH1F*)f_new->Get("h_ttZ");
    /*h_TTZ->Add( (TH1F*)f_new->Get("h_TTLL_lowmass") );
      h_TTZ->Add( (TH1F*)f_new->Get("h_ttG") );*/
    h_TTZ->SetNameTitle("h_TTZ","h_TTZ");
    h_TTZ->Write();

    
    //Diboson = WZ + ZZ
    /*TH1F* h_Diboson = (TH1F*)f_new->Get("h_WZ");
    h_Diboson->Add( (TH1F*)f_new->Get("h_ZZ") );
    h_Diboson->SetNameTitle("h_Diboson","h_Diboson");
    h_Diboson->Write();

    
    //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
    TH1F* h_Rares = (TH1F*)f_new->Get("h_ZZZ");
    h_Rares->Add( (TH1F*)f_new->Get("h_WZZ") );
    h_Rares->Add( (TH1F*)f_new->Get("h_WWZ") );
    h_Rares->Add( (TH1F*)f_new->Get("h_tZq") );
    h_Rares->Add( (TH1F*)f_new->Get("h_TTTT") );
    h_Rares->SetNameTitle("h_Rares","h_Rares");
    h_Rares->Write();

    */
    
    //Fakes
    
    /*TH1F* h_fakes =single_plot(filename_data_lepMVA_CR,
			       "T",
			       var,
			       Form("event_weight_ttH*(category==%i && isTrig &&",cat_fakes[i_cat]) + cut + ")",
			       nbin, x);
    
    h_fakes->Scale(luminosity/12900.); //Data files for 12.9 fb-1
    h_fakes->SetNameTitle("h_fakes","h_fakes");
    h_fakes->Write();*/

    //Fakes MC

    /*TH1F* h_fakes_DL_MC =single_plot(filename_ttbar_DL,
				     "T",
				     var,
				     Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*event_weight_ttH*(category==%i && isTrig &&",cat_fakes[i_cat]) + cut + ")",
				     nbin, x);

    TH1F* h_fakes_DL_MC_norm =single_plot(filename_norm_ttbar_DL,
					  "HTauTauTree",
					  "1",
					  "MC_weight*PU_weight",
					  3,0,3);
    
    h_fakes_DL_MC->Scale(luminosity*XS_ttbar_DL/h_fakes_DL_MC_norm->Integral());
    h_fakes_DL_MC->SetNameTitle("h_fakes_DL_MC","h_fakes_DL_MC");
    h_fakes_DL_MC->Write();*/


    /*TH1F* h_fakes_SLfromT_MC =single_plot(filename_ttbar_SLfromT,
					  "HTauTauTree_2lSS_lepMVA_CR",
					  var,
					  Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*event_weight_ttH*(category==%i && isTrig)",cat_fakes[i_cat]),					
					  nbin, x);

    TH1F* h_fakes_SLfromT_MC_norm =single_plot(filename_norm_ttbar_SLfromT,
					       "HTauTauTree",
					       "1",
					       "MC_weight*PU_weight",
					       3,0,3);
    
    h_fakes_SLfromT_MC->Scale(luminosity*XS_ttbar_SLfromT/h_fakes_SLfromT_MC_norm->Integral());
    h_fakes_SLfromT_MC->SetNameTitle("h_fakes_SLfromT_MC","h_fakes_SLfromT_MC");
    h_fakes_SLfromT_MC->Write();
    

    TH1F* h_fakes_SLfromTbar_MC =single_plot(filename_ttbar_SLfromTbar,
					     "HTauTauTree_2lSS_lepMVA_CR",
					     var,
					     Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*event_weight_ttH*(category==%i && isTrig)",cat_fakes[i_cat]),				
					     nbin, x);
    
    TH1F* h_fakes_SLfromTbar_MC_norm =single_plot(filename_norm_ttbar_SLfromTbar,
						  "HTauTauTree",
						  "1",
						  "MC_weight*PU_weight",
						  3,0,3);
    
    h_fakes_SLfromTbar_MC->Scale(luminosity*XS_ttbar_SLfromTbar/h_fakes_SLfromTbar_MC_norm->Integral());
    h_fakes_SLfromTbar_MC->SetNameTitle("h_fakes_SLfromTbar_MC","h_fakes_SLfromTbar_MC");
    h_fakes_SLfromTbar_MC->Write();*/
    
    
    //Fakes MC
    //TH1F* h_fakes_MC = h_fakes_DL_MC;
    //h_fakes_MC->Add(h_fakes_SLfromT_MC);
    //h_fakes_MC->Add(h_fakes_SLfromTbar_MC);
    //h_fakes_MC->SetNameTitle("h_fakes_MC","h_fakes_MC");
    //h_fakes_MC->Write();


    //Charge flips
    /*TH1F* h_flips =single_plot(filename_data_2lOS_CR,
			       "T",
			       var,
			       Form("event_weight_ttH*(category==%i && isTrig &&",cat_flips[i_cat]) + cut + ")",
			       nbin, x);
    
    h_flips->Scale(luminosity/12900.); //Data files for 12.9 fb-1
    h_flips->SetNameTitle("h_flips","h_flips");
    h_flips->Write();*/
 
    
    
    //Data
    
    /*TH1F* h_data_obs =single_plot(filename_data,
      "HTauTauTree_2lSS",
      var,
      Form("(category==%i && isTrig)",cat[i]),		
      nbin, x);
      
      h_data_obs->Scale(luminosity/12900.); //Data files for 12.9 fb-1
      
      h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
      h_data_obs->Write();
      h.push_back(h_data_obs);*/


    TH1F* h_data_obs = (TH1F*)f_new->Get("h_ttH");
    //h_data_obs->Add( (TH1F*)f_new->Get("h_ttW") );
    h_data_obs->Add( (TH1F*)f_new->Get("h_TTZ") );
    /*h_data_obs->Add( (TH1F*)f_new->Get("h_WpWp") );
    h_data_obs->Add( (TH1F*)f_new->Get("h_Diboson") );
    h_data_obs->Add( (TH1F*)f_new->Get("h_Rares") );*/
    //h_data_obs->Add( (TH1F*)f_new->Get("h_fakes") );
    //h_data_obs->Add( (TH1F*)f_new->Get("h_flips") );
    h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
    h_data_obs->Write();

    
    //////////////////////////////////////////
    //////////////////////////////////////////
    /////////       SYSTEMATICS       ////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    
    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      float norm = ((TH1F*)f_new->Get("h_"+MC_sample_name[i_MC]))->Integral();
		    
      TH1F* h_MC_btag_up = single_plot(filename_MC[i_MC],
				       "T",
				       var,
				       Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight_up*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
				       nbin, x);
      
      h_MC_btag_up->Scale(norm/h_MC_btag_up->Integral());
      h_MC_btag_up->SetNameTitle("h_"+MC_sample_name[i_MC]+"_btagUp","h_"+MC_sample_name[i_MC]+"_btagUp");
      h_MC_btag_up->Write();

      
      TH1F* h_MC_btag_down = single_plot(filename_MC[i_MC],
					 "T",
					 var,
					 Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight_down*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
					 nbin, x);
      
      h_MC_btag_down->Scale(norm/h_MC_btag_down->Integral());
      h_MC_btag_down->SetNameTitle("h_"+MC_sample_name[i_MC]+"_btagDown","h_"+MC_sample_name[i_MC]+"_btagDown");
      h_MC_btag_down->Write();

    }


    //TTZ = ttZ + TTLL_lowmass + ttG    
    TH1F* h_TTZ_btag_up = (TH1F*)f_new->Get("h_ttZ_btagUp");
    /*h_TTZ_btag_up->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_btag_up") );
      h_TTZ_btag_up->Add( (TH1F*)f_new->Get("h_ttG_btag_up") );*/
    h_TTZ_btag_up->SetNameTitle("h_TTZ_btagUp","h_TTZ_btagUp");
    h_TTZ_btag_up->Write();

    TH1F* h_TTZ_btag_down = (TH1F*)f_new->Get("h_ttZ_btagDown");
    /*h_TTZ_btag_down->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_btag_down") );
      h_TTZ_btag_down->Add( (TH1F*)f_new->Get("h_ttG_btag_down") );*/
    h_TTZ_btag_down->SetNameTitle("h_TTZ_btagDown","h_TTZ_btagDown");
    h_TTZ_btag_down->Write();

    //Diboson = WZ + ZZ
    /*TH1F* h_Diboson_btag_up = (TH1F*)f_new->Get("h_WZ_btag_up");
    h_Diboson_btag_up->Add( (TH1F*)f_new->Get("h_ZZ_btag_up") );
    h_Diboson_btag_up->SetNameTitle("h_Diboson_btag_up","h_Diboson_btag_up");
    h_Diboson_btag_up->Write();

    TH1F* h_Diboson_btag_down = (TH1F*)f_new->Get("h_WZ_btag_down");
    h_Diboson_btag_down->Add( (TH1F*)f_new->Get("h_ZZ_btag_down") );
    h_Diboson_btag_down->SetNameTitle("h_Diboson_btag_down","h_Diboson_btag_down");
    h_Diboson_btag_down->Write();
    
    //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
    TH1F* h_Rares_btag_up = (TH1F*)f_new->Get("h_ZZZ_btag_up");
    h_Rares_btag_up->Add( (TH1F*)f_new->Get("h_WZZ_btag_up") );
    h_Rares_btag_up->Add( (TH1F*)f_new->Get("h_WWZ_btag_up") );
    h_Rares_btag_up->Add( (TH1F*)f_new->Get("h_tZq_btag_up") );
    h_Rares_btag_up->Add( (TH1F*)f_new->Get("h_TTTT_btag_up") );
    h_Rares_btag_up->Write();

    TH1F* h_Rares_btag_down = (TH1F*)f_new->Get("h_ZZZ_btag_down");
    h_Rares_btag_down->Add( (TH1F*)f_new->Get("h_WZZ_btag_down") );
    h_Rares_btag_down->Add( (TH1F*)f_new->Get("h_WWZ_btag_down") );
    h_Rares_btag_down->Add( (TH1F*)f_new->Get("h_tZq_btag_down") );
    h_Rares_btag_down->Add( (TH1F*)f_new->Get("h_TTTT_btag_down") );
    h_Rares_btag_down->Write();*/

    for(unsigned i_MC=0;i_MC<MC_sample_name_thu_unc.size();i_MC++){

      float norm = ((TH1F*)f_new->Get("h_"+MC_sample_name_thu_unc[i_MC]))->Integral();
		    
      TH1F* h_MC_x1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "T",
				     var,
				     Form("MC_weight_scale_muF2*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
				     nbin, x);
      
      h_MC_x1_up->Scale(norm/h_MC_x1_up->Integral());
      h_MC_x1_up->SetNameTitle("h_"+MC_sample_name_thu_unc[i_MC]+"_x1Up","h_"+MC_sample_name_thu_unc[i_MC]+"_x1Up");
      h_MC_x1_up->Write();

      TH1F* h_MC_x1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "T",
				       var,
				       Form("MC_weight_scale_muF0p5*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
				       nbin, x);
      
      h_MC_x1_down->Scale(norm/h_MC_x1_down->Integral());
      h_MC_x1_down->SetNameTitle("h_"+MC_sample_name_thu_unc[i_MC]+"_x1Down","h_"+MC_sample_name_thu_unc[i_MC]+"_x1Down");
      h_MC_x1_down->Write();

      TH1F* h_MC_y1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "T",
				     var,
				     Form("MC_weight_scale_muR2*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
				     nbin, x);
      
      h_MC_y1_up->Scale(norm/h_MC_y1_up->Integral());
      h_MC_y1_up->SetNameTitle("h_"+MC_sample_name_thu_unc[i_MC]+"_y1Up","h_"+MC_sample_name_thu_unc[i_MC]+"_y1Up");
      h_MC_y1_up->Write();

      TH1F* h_MC_y1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "T",
				       var,
				       Form("MC_weight_scale_muR0p5*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig &&",cat[i_cat]) + cut + ")",
				       nbin, x);
      
      h_MC_y1_down->Scale(norm/h_MC_y1_down->Integral());
      h_MC_y1_down->SetNameTitle("h_"+MC_sample_name_thu_unc[i_MC]+"_y1Down","h_"+MC_sample_name_thu_unc[i_MC]+"_y1Down");
      h_MC_y1_down->Write();
      
 

    }


    //TTZ = ttZ + TTLL_lowmass + ttG    
    TH1F* h_TTZ_x1_up = (TH1F*)f_new->Get("h_ttZ_x1Up");
    /*h_TTZ_x1_up->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_x1_up") );
      h_TTZ_x1_up->Add( (TH1F*)f_new->Get("h_ttG_x1_up") );*/
    h_TTZ_x1_up->SetNameTitle("h_TTZ_x1Up","h_TTZ_x1Up");
    h_TTZ_x1_up->Write();

    TH1F* h_TTZ_x1_down = (TH1F*)f_new->Get("h_ttZ_x1Down");
    /*h_TTZ_x1_down->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_x1_down") );
      h_TTZ_x1_down->Add( (TH1F*)f_new->Get("h_ttG_x1_down") );*/
    h_TTZ_x1_down->SetNameTitle("h_TTZ_x1_down","h_TTZ_x1Down");
    h_TTZ_x1_down->Write();

    TH1F* h_TTZ_y1_up = (TH1F*)f_new->Get("h_ttZ_y1Up");
    /*h_TTZ_y1_up->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_y1_up") );
      h_TTZ_y1_up->Add( (TH1F*)f_new->Get("h_ttG_y1_up") );*/
    h_TTZ_y1_up->SetNameTitle("h_TTZ_y1_up","h_TTZ_y1Up");
    h_TTZ_y1_up->Write();

    TH1F* h_TTZ_y1_down = (TH1F*)f_new->Get("h_ttZ_y1Down");
    /*h_TTZ_y1_down->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_y1_down") );
      h_TTZ_y1_down->Add( (TH1F*)f_new->Get("h_ttG_y1_down") );*/
    h_TTZ_y1_down->SetNameTitle("h_TTZ_y1_down","h_TTZ_y1Down");
    h_TTZ_y1_down->Write();




    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){
      
      /*float norm = ((TH1F*)f_new->Get("h_"+MC_sample_name[i_MC]))->Integral();
      
      TH1F* h_MC_JEC_up = single_plot(filename_MC_JECup[i_MC],
				      "HTauTauTree_2lSS",
				      var,
				      Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig)",cat[i_cat]),
				      nbin, x);
      
      h_MC_JEC_up->Scale(norm/h_MC_JEC_up->Integral());
      h_MC_JEC_up->SetNameTitle("h_"+MC_sample_name[i_MC]+"_JECUp","h_"+MC_sample_name[i_MC]+"_JECUp");
      h_MC_JEC_up->Write();

      
      TH1F* h_MC_JEC_down = single_plot(filename_MC_JECdown[i_MC],
					"HTauTauTree_2lSS",
					var,
					Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig)",cat[i_cat]),
					nbin, x);
      
      h_MC_JEC_down->Scale(norm/h_MC_JEC_down->Integral());
      h_MC_JEC_down->SetNameTitle("h_"+MC_sample_name[i_MC]+"_JECDown","h_"+MC_sample_name[i_MC]+"_JECDown");
      h_MC_JEC_down->Write();

      TH1F* h_MC_TES_up = single_plot(filename_MC_TESup[i_MC],
				      "HTauTauTree_2lSS",
				      var,
				      Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig)",cat[i_cat]),
				      nbin, x);
      
      h_MC_TES_up->Scale(norm/h_MC_TES_up->Integral());
      h_MC_TES_up->SetNameTitle("h_"+MC_sample_name[i_MC]+"_TES_up","h_"+MC_sample_name[i_MC]+"_TES_up");
      h_MC_TES_up->Write();*/

      
      /*TH1F* h_MC_TES_down = single_plot(filename_MC_TESdown[i_MC],
					"HTauTauTree_2lSS",
					var,
					Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==%i && isTrig)",cat[i_cat]),
					nbin, x);
      
      h_MC_TES_down->Scale(norm/h_MC_TES_down->Integral());
      h_MC_TES_down->SetNameTitle("h_"+MC_sample_name[i_MC]+"_TES_down","h_"+MC_sample_name[i_MC]+"_TES_down");
      h_MC_TES_down->Write();*/

    }


    //TTZ = ttZ + TTLL_lowmass + ttG    
    /*TH1F* h_TTZ_JEC_up = (TH1F*)f_new->Get("h_ttZ_JECUp");
    h_TTZ_JEC_up->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_JEC_up") );
      h_TTZ_JEC_up->Add( (TH1F*)f_new->Get("h_ttG_JEC_up") );
    h_TTZ_JEC_up->SetNameTitle("h_TTZ_JECUp","h_TTZ_JECUp");
    h_TTZ_JEC_up->Write();

    TH1F* h_TTZ_JEC_down = (TH1F*)f_new->Get("h_ttZ_JECDown");
    h_TTZ_JEC_down->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_JEC_down") );
      h_TTZ_JEC_down->Add( (TH1F*)f_new->Get("h_ttG_JEC_down") );
    h_TTZ_JEC_down->SetNameTitle("h_TTZ_JECDown","h_TTZ_JECDown");
    h_TTZ_JEC_down->Write();

    TH1F* h_TTZ_TES_up = (TH1F*)f_new->Get("h_ttZ_TES_up");
    h_TTZ_TES_up->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_TES_up") );
      h_TTZ_TES_up->Add( (TH1F*)f_new->Get("h_ttG_TES_up") );
    h_TTZ_TES_up->SetNameTitle("h_TTZ_TES_up","h_TTZ_TES_up");
    h_TTZ_TES_up->Write();*/

    //TH1F* h_TTZ_TES_down = (TH1F*)f_new->Get("h_ttZ_TES_down");
    /* h_TTZ_TES_down->Add( (TH1F*)f_new->Get("h_TTLL_lowmass_TES_down") );
       h_TTZ_TES_down->Add( (TH1F*)f_new->Get("h_ttG_TES_down") );*/
    //h_TTZ_TES_down->SetNameTitle("h_TTZ_TES_down","h_TTZ_TES_down");
    //h_TTZ_TES_down->Write();

    //Diboson = WZ + ZZ
    /*TH1F* h_Diboson_JEC_up = (TH1F*)f_new->Get("h_WZ_JEC_up");
    h_Diboson_JEC_up->Add( (TH1F*)f_new->Get("h_ZZ_JEC_up") );
    h_Diboson_JEC_up->SetNameTitle("h_Diboson_JEC_up","h_Diboson_JEC_up");
    h_Diboson_JEC_up->Write();

    TH1F* h_Diboson_JEC_down = (TH1F*)f_new->Get("h_WZ_JEC_down");
    h_Diboson_JEC_down->Add( (TH1F*)f_new->Get("h_ZZ_JEC_down") );
    h_Diboson_JEC_down->SetNameTitle("h_Diboson_JEC_down","h_Diboson_JEC_down");
    h_Diboson_JEC_down->Write();

    TH1F* h_Diboson_TES_up = (TH1F*)f_new->Get("h_WZ_TES_up");
    h_Diboson_TES_up->Add( (TH1F*)f_new->Get("h_ZZ_TES_up") );
    h_Diboson_TES_up->SetNameTitle("h_Diboson_TES_up","h_Diboson_TES_up");
    h_Diboson_TES_up->Write();

    TH1F* h_Diboson_TES_down = (TH1F*)f_new->Get("h_WZ_TES_down");
    h_Diboson_TES_down->Add( (TH1F*)f_new->Get("h_ZZ_TES_down") );
    h_Diboson_TES_down->SetNameTitle("h_Diboson_TES_down","h_Diboson_TES_down");
    h_Diboson_TES_down->Write();
    
    //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
    TH1F* h_Rares_JEC_up = (TH1F*)f_new->Get("h_ZZZ_JEC_up");
    h_Rares_JEC_up->Add( (TH1F*)f_new->Get("h_WZZ_JEC_up") );
    h_Rares_JEC_up->Add( (TH1F*)f_new->Get("h_WWZ_JEC_up") );
    h_Rares_JEC_up->Add( (TH1F*)f_new->Get("h_tZq_JEC_up") );
    h_Rares_JEC_up->Add( (TH1F*)f_new->Get("h_TTTT_JEC_up") );
    h_Rares_JEC_up->Write();

    TH1F* h_Rares_JEC_down = (TH1F*)f_new->Get("h_ZZZ_JEC_down");
    h_Rares_JEC_down->Add( (TH1F*)f_new->Get("h_WZZ_JEC_down") );
    h_Rares_JEC_down->Add( (TH1F*)f_new->Get("h_WWZ_JEC_down") );
    h_Rares_JEC_down->Add( (TH1F*)f_new->Get("h_tZq_JEC_down") );
    h_Rares_JEC_down->Add( (TH1F*)f_new->Get("h_TTTT_JEC_down") );
    h_Rares_JEC_down->Write();

    TH1F* h_Rares_TES_up = (TH1F*)f_new->Get("h_ZZZ_TES_up");
    h_Rares_TES_up->Add( (TH1F*)f_new->Get("h_WZZ_TES_up") );
    h_Rares_TES_up->Add( (TH1F*)f_new->Get("h_WWZ_TES_up") );
    h_Rares_TES_up->Add( (TH1F*)f_new->Get("h_tZq_TES_up") );
    h_Rares_TES_up->Add( (TH1F*)f_new->Get("h_TTTT_TES_up") );
    h_Rares_TES_up->Write();

    TH1F* h_Rares_TES_down = (TH1F*)f_new->Get("h_ZZZ_TES_down");
    h_Rares_TES_down->Add( (TH1F*)f_new->Get("h_WZZ_TES_down") );
    h_Rares_TES_down->Add( (TH1F*)f_new->Get("h_WWZ_TES_down") );
    h_Rares_TES_down->Add( (TH1F*)f_new->Get("h_tZq_TES_down") );
    h_Rares_TES_down->Add( (TH1F*)f_new->Get("h_TTTT_TES_down") );
    h_Rares_TES_down->Write();*/





  }







  f_new->Close();


}








void datacard_maker_MEM_ttH_vs_full_bkg_genmatch_2lSS_nomiss_log(){

  float k_ttbar=1e-17;
  float k_ttZ_tautau=5e-2;
  float k_ttZ_Zll=1e-1;

  TString var=Form("-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll))*((%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll)>0 && (-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll))<=9)) + 9*(((%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll)==0 && Integral_ttH>0)||(-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll))>9)) - ((%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll)==0 && Integral_ttH==0)",k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll);

  cout<<var<<endl;


  double x[16];
  x[0]=-2;
  x[1]=-1.1;
  x[2]=-0.9;
  x[3]=0;
  x[4]=0.25;
  x[5]=0.5;
  x[6]=1.;
  x[7]=1.5;
  x[8]=2.;
  x[9]=2.5;
  x[10]=3.;
  x[11]=3.5;
  x[12]=4.;
  x[13]=5.;
  x[14]=6.;
  x[15]=10.;
  int nbin = 15;


  TString cut="integration_type==0 && isGenMatched";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MEM_ttH_vs_full_bkg_genmatch_2lSS_nomiss_12.9fb_log.root";


  datacard_maker(var,nbin,x,cut,file);


}






void datacard_maker_MEM_ttH_vs_full_bkg_genmatch_2lSS_missing_log(){

  float k_ttbar=1e-14;
  float k_ttZ_tautau=5e-2;
  float k_ttZ_Zll=1;


  TString var=Form("-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll))*((%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll)>0 && (-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll))<=3)) + 9*(((%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll)==0 && Integral_ttH>0)||(-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll))>3)) - ((%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll)==0 && Integral_ttH==0)",k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll);

  cout<<var<<endl;


  double x[12];
  x[0]=-2;
  x[1]=-1.1;
  x[2]=-0.9;
  x[3]=0;
  x[4]=0.25;
  x[5]=0.5;
  x[6]=1.;
  x[7]=1.5;
  x[8]=2.;
  x[9]=2.5;
  x[10]=3.;
  x[11]=10.;
  int nbin = 11;


  TString cut="integration_type==1 && isGenMatched";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MEM_ttH_vs_full_bkg_genmatch_2lSS_missing_12.9fb_log.root";


  datacard_maker(var,nbin,x,cut,file);


}










void datacard_maker_MEM_ttH_vs_full_bkg_genmatch_antilep_2lSS_nomiss_log(){

  float k_ttbar=1e-17;
  float k_ttZ_tautau=5e-2;
  float k_ttZ_Zll=1e-1;

  TString var=Form("-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll))*((%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll)>0 && (-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll))<=9)) + 9*(((%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll)==0 && Integral_ttH>0)||(-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll))>9)) - ((%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll)==0 && Integral_ttH==0)",k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll);

  cout<<var<<endl;


  double x[16];
  x[0]=-2;
  x[1]=-1.1;
  x[2]=-0.9;
  x[3]=0;
  x[4]=0.25;
  x[5]=0.5;
  x[6]=1.;
  x[7]=1.5;
  x[8]=2.;
  x[9]=2.5;
  x[10]=3.;
  x[11]=3.5;
  x[12]=4.;
  x[13]=5.;
  x[14]=6.;
  x[15]=10.;
  int nbin = 15;


  TString cut="integration_type==0 && isGenMatched && recotauh_sel_againstMuonLoose3[0] && recotauh_sel_againstElectronLooseMVA6[0]";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MEM_ttH_vs_full_bkg_genmatch_antilep_2lSS_nomiss_12.9fb_log.root";


  datacard_maker(var,nbin,x,cut,file);


}






void datacard_maker_MEM_ttH_vs_full_bkg_genmatch_antilep_2lSS_missing_log(){

  float k_ttbar=1e-14;
  float k_ttZ_tautau=5e-2;
  float k_ttZ_Zll=1;


  TString var=Form("-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll))*((%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll)>0 && (-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll))<=3)) + 9*(((%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll)==0 && Integral_ttH>0)||(-log(1-Integral_ttH/(Integral_ttH+%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll))>3)) - ((%.20f*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+%.20f*Integral_ttZ+%.20f*Integral_ttZ_Zll)==0 && Integral_ttH==0)",k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll,k_ttbar,k_ttZ_tautau,k_ttZ_Zll);

  cout<<var<<endl;


  double x[12];
  x[0]=-2;
  x[1]=-1.1;
  x[2]=-0.9;
  x[3]=0;
  x[4]=0.25;
  x[5]=0.5;
  x[6]=1.;
  x[7]=1.5;
  x[8]=2.;
  x[9]=2.5;
  x[10]=3.;
  x[11]=10.;
  int nbin = 11;


  TString cut="integration_type==1 && isGenMatched && recotauh_sel_againstMuonLoose3[0] && recotauh_sel_againstElectronLooseMVA6[0]";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_09_2016/datacards/datacard_MEM_ttH_vs_full_bkg_genmatch_antilep_2lSS_missing_12.9fb_log.root";


  datacard_maker(var,nbin,x,cut,file);


}



