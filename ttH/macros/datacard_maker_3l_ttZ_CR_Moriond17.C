#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>

#include "Helpers.C"

float luminosity = 36814; //36.814 fb-1

float XS_ttH = 0.2151;
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
float XS_WWW = 0.2086;

float XS_tZq = 0.0758;
float XS_TTTT = 0.009103;
float XS_ttbar_DL = 87.3;
float XS_ttbar_SLfromT = 182;
float XS_ttbar_SLfromTbar = 182;
float XS_ZZJJ = 0.0004404;


vector<float> XS;


//MC
TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bestMZ.root";

TString filename_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_bestMZ.root";
TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bestMZ.root";
TString filename_ttG = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttG_split_bestMZ.root";

TString filename_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_bestMZ.root";

TString filename_WWW = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WWW_split.root";
TString filename_WWZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WWZ_split.root";
TString filename_WZZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WZZ_split.root";
TString filename_ZZZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_ZZZ_split.root";
TString filename_tZq = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_tZq_split_bestMZ.root";


TString filename_WpWp = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WpWp_split.root";

TString filename_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_*split.root";
TString filename_ttbar_SLfromT = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromT_split.root";

TString filename_norm_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root";

TString filename_norm_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/ttV/ntuple_PU_ttW.root";
TString filename_norm_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/ttV/ntuple_PU_ttZ.root";
TString filename_norm_ttG = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/ttV/ntuple_PU_ttG.root";

TString filename_norm_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/EWK/ntuple_PU_WZ.root";

TString filename_norm_WWW = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/Rares/ntuple_PU_WWW.root";
TString filename_norm_WWZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/Rares/ntuple_PU_WWZ.root";
TString filename_norm_WZZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/Rares/ntuple_PU_WZZ.root";
TString filename_norm_ZZZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/Rares/ntuple_PU_ZZZ.root";
TString filename_norm_tZq = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/Rares/ntuple_PU_tZq.root";


TString filename_norm_WpWp = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/Rares/ntuple_PU_WpWp.root";

TString filename_norm_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_DL*.root";
TString filename_norm_ttbar_SLfromT = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_SLfromT.root";



vector<TString> filename_MC;
vector<TString> filename_norm_MC;




//Data

TString filename_DoubleEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split_bestMZ.root";
TString filename_MuonEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split_bestMZ.root";
TString filename_DoubleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split_bestMZ.root";
TString filename_SingleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split_bestMZ.root";
TString filename_SingleEle_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split_bestMZ.root";

TString filename_DoubleEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split_bestMZ.root";
TString filename_MuonEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split_bestMZ.root";
TString filename_DoubleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split_bestMZ.root";
TString filename_SingleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split_bestMZ.root";
TString filename_SingleEle_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split_bestMZ.root";

TString filename_DoubleEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split_bestMZ.root";
TString filename_MuonEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split_bestMZ.root";
TString filename_DoubleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split_bestMZ.root";
TString filename_SingleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split_bestMZ.root";
TString filename_SingleEle_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split_bestMZ.root";

TString filename_DoubleEG_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016E_split_bestMZ.root";
TString filename_MuonEG_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016E_split_bestMZ.root";
TString filename_DoubleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016E_split_bestMZ.root";
TString filename_SingleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016E_split_bestMZ.root";
TString filename_SingleEle_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016E_split_bestMZ.root";

TString filename_DoubleEG_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016F_split_bestMZ.root";
TString filename_MuonEG_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016F_split_bestMZ.root";
TString filename_DoubleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016F_split_bestMZ.root";
TString filename_SingleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016F_split_bestMZ.root";
TString filename_SingleEle_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016F_split_bestMZ.root";

TString filename_DoubleEG_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016G_split_bestMZ.root";
TString filename_MuonEG_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016G_split_bestMZ.root";
TString filename_DoubleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016G_split_bestMZ.root";
TString filename_SingleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016G_split_bestMZ.root";
TString filename_SingleEle_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016G_split_bestMZ.root";

TString filename_DoubleEG_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016Hv2_split_bestMZ.root";
TString filename_MuonEG_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016Hv2_split_bestMZ.root";
TString filename_DoubleMu_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016Hv2_split_bestMZ.root";
TString filename_SingleMu_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv2_split_bestMZ.root";
TString filename_SingleEle_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv2_split_bestMZ.root";

TString filename_DoubleEG_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016Hv3_split_bestMZ.root";
TString filename_MuonEG_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016Hv3_split_bestMZ.root";
TString filename_DoubleMu_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016Hv3_split_bestMZ.root";
TString filename_SingleMu_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv3_split_bestMZ.root";
TString filename_SingleEle_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv3_split_bestMZ.root";


vector<TString> filename_data;

vector<TString> MC_sample_name;
vector<TString> MC_sample_cut;

vector<TString> filename_MC_thu_unc;
vector<TString> MC_sample_name_thu_unc;
vector<TString> MC_sample_cut_thu_unc;


// MC JEC + TES


TString filename_ttH_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/ttH/HTauTauTree_ttH_Hnonbb_split_JECup.root";
TString filename_ttH_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/ttH/HTauTauTree_ttH_Hnonbb_split_JECdown.root";
TString filename_ttH_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/ttH/HTauTauTree_ttH_Hnonbb_split_TESup.root";
TString filename_ttH_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/ttH/HTauTauTree_ttH_Hnonbb_split_TESdown.root";


TString filename_ttZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttZ_split_JECup.root";
TString filename_ttZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/ttV/HTauTauTree_ttZ_split_JECdown.root";
TString filename_ttZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/ttV/HTauTauTree_ttZ_split_TESup.root";
TString filename_ttZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttZ_split_TESdown.root";

TString filename_ttG_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttG_split_JECup.root";
TString filename_ttG_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/ttV/HTauTauTree_ttG_split_JECdown.root";
TString filename_ttG_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/ttV/HTauTauTree_ttG_split_TESup.root";
TString filename_ttG_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttG_split_TESdown.root";


TString filename_ttW_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttW_split_JECup.root";
TString filename_ttW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/ttV/HTauTauTree_ttW_split_JECdown.root";
TString filename_ttW_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/ttV/HTauTauTree_ttW_split_TESup.root";
TString filename_ttW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttW_split_TESdown.root";

TString filename_WZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/EWK/HTauTauTree_WZ_split_JECup.root";
TString filename_WZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/EWK/HTauTauTree_WZ_split_JECdown.root";
TString filename_WZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/EWK/HTauTauTree_WZ_split_TESup.root";
TString filename_WZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/EWK/HTauTauTree_WZ_split_TESdown.root";

TString filename_WWW_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_WWW_split_JECup.root";
TString filename_WWW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_WWW_split_JECdown.root";
TString filename_WWW_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_WWW_split_TESup.root";
TString filename_WWW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_WWW_split_TESdown.root";

TString filename_WWZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_WWZ_split_JECup.root";
TString filename_WWZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_WWZ_split_JECdown.root";
TString filename_WWZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_WWZ_split_TESup.root";
TString filename_WWZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_WWZ_split_TESdown.root";

TString filename_WZZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_WZZ_split_JECup.root";
TString filename_WZZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_WZZ_split_JECdown.root";
TString filename_WZZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_WZZ_split_TESup.root";
TString filename_WZZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_WZZ_split_TESdown.root";

TString filename_ZZZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_ZZZ_split_JECup.root";
TString filename_ZZZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_ZZZ_split_JECdown.root";
TString filename_ZZZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_ZZZ_split_TESup.root";
TString filename_ZZZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_ZZZ_split_TESdown.root";

TString filename_WpWp_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_WpWp_split_JECup.root";
TString filename_WpWp_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_WpWp_split_JECdown.root";
TString filename_WpWp_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_WpWp_split_TESup.root";
TString filename_WpWp_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_WpWp_split_TESdown.root";

TString filename_tZq_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_tZq_split_JECup.root";
TString filename_tZq_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_tZq_split_JECdown.root";
TString filename_tZq_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_tZq_split_TESup.root";
TString filename_tZq_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_tZq_split_TESdown.root";

vector<TString> filename_MC_JECup;
vector<TString> filename_MC_JECdown;
vector<TString> filename_MC_TESup;
vector<TString> filename_MC_TESdown;



// bTag systematics
vector<TString> bTag_syst_names;


void initialize(){

  XS.clear();
  filename_MC.clear();
  filename_norm_MC.clear();
  MC_sample_name.clear();
  MC_sample_cut.clear();
  filename_data.clear();

  filename_MC_JECup.clear();
  filename_MC_JECdown.clear();
  filename_MC_TESup.clear();
  filename_MC_TESdown.clear();

  filename_MC_thu_unc.clear();
  MC_sample_name_thu_unc.clear();
  MC_sample_cut_thu_unc.clear();
  bTag_syst_names.clear();

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);  

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_htt");
  MC_sample_cut.push_back("genH_decayMode[1]<=5");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_htt_gentau");
  MC_sample_cut.push_back("genH_decayMode[1]<=5 && recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_htt_faketau");
  MC_sample_cut.push_back("genH_decayMode[1]<=5 && !recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hww");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genW==4");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hww_gentau");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genW==4 && recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hww_faketau");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genW==4 && !recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hzz");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genZ==2");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hzz_gentau");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genZ==2 && recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hzz_faketau");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genZ==2 && !recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttW);
  filename_MC.push_back(filename_ttW);
  filename_norm_MC.push_back(filename_norm_ttW);
  MC_sample_name.push_back("TTW");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back(filename_ttW_JECup);
  filename_MC_JECdown.push_back(filename_ttW_JECdown);
  filename_MC_TESup.push_back(filename_ttW_TESup);
  filename_MC_TESdown.push_back(filename_ttW_TESdown);

  XS.push_back(XS_ttW);
  filename_MC.push_back(filename_ttW);
  filename_norm_MC.push_back(filename_norm_ttW);
  MC_sample_name.push_back("TTW_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttW_JECup);
  filename_MC_JECdown.push_back(filename_ttW_JECdown);
  filename_MC_TESup.push_back(filename_ttW_TESup);
  filename_MC_TESdown.push_back(filename_ttW_TESdown);

  XS.push_back(XS_ttW);
  filename_MC.push_back(filename_ttW);
  filename_norm_MC.push_back(filename_norm_ttW);
  MC_sample_name.push_back("TTW_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttW_JECup);
  filename_MC_JECdown.push_back(filename_ttW_JECdown);
  filename_MC_TESup.push_back(filename_ttW_TESup);
  filename_MC_TESdown.push_back(filename_ttW_TESdown);

  XS.push_back(XS_ttZ);
  filename_MC.push_back(filename_ttZ);
  filename_norm_MC.push_back(filename_norm_ttZ);
  MC_sample_name.push_back("ttZ");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back(filename_ttZ_JECup);
  filename_MC_JECdown.push_back(filename_ttZ_JECdown);
  filename_MC_TESup.push_back(filename_ttZ_TESup);
  filename_MC_TESdown.push_back(filename_ttZ_TESdown);
  
  XS.push_back(XS_ttZ);
  filename_MC.push_back(filename_ttZ);
  filename_norm_MC.push_back(filename_norm_ttZ);
  MC_sample_name.push_back("ttZ_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttZ_JECup);
  filename_MC_JECdown.push_back(filename_ttZ_JECdown);
  filename_MC_TESup.push_back(filename_ttZ_TESup);
  filename_MC_TESdown.push_back(filename_ttZ_TESdown);

  XS.push_back(XS_ttZ);
  filename_MC.push_back(filename_ttZ);
  filename_norm_MC.push_back(filename_norm_ttZ);
  MC_sample_name.push_back("ttZ_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttZ_JECup);
  filename_MC_JECdown.push_back(filename_ttZ_JECdown);
  filename_MC_TESup.push_back(filename_ttZ_TESup);
  filename_MC_TESdown.push_back(filename_ttZ_TESdown);


  XS.push_back(XS_ttG);
  filename_MC.push_back(filename_ttG);
  filename_norm_MC.push_back(filename_norm_ttG);
  MC_sample_name.push_back("ttG");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back(filename_ttG_JECup);
  filename_MC_JECdown.push_back(filename_ttG_JECdown);
  filename_MC_TESup.push_back(filename_ttG_TESup);
  filename_MC_TESdown.push_back(filename_ttG_TESdown);
  
  XS.push_back(XS_ttG);
  filename_MC.push_back(filename_ttG);
  filename_norm_MC.push_back(filename_norm_ttG);
  MC_sample_name.push_back("ttG_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttG_JECup);
  filename_MC_JECdown.push_back(filename_ttG_JECdown);
  filename_MC_TESup.push_back(filename_ttG_TESup);
  filename_MC_TESdown.push_back(filename_ttG_TESdown);

  XS.push_back(XS_ttG);
  filename_MC.push_back(filename_ttG);
  filename_norm_MC.push_back(filename_norm_ttG);
  MC_sample_name.push_back("ttG_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttG_JECup);
  filename_MC_JECdown.push_back(filename_ttG_JECdown);
  filename_MC_TESup.push_back(filename_ttG_TESup);
  filename_MC_TESdown.push_back(filename_ttG_TESdown);


  XS.push_back(XS_WZ);
  filename_MC.push_back(filename_WZ);
  filename_norm_MC.push_back(filename_norm_WZ);
  MC_sample_name.push_back("EWK");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back(filename_WZ_JECup);
  filename_MC_JECdown.push_back(filename_WZ_JECdown);
  filename_MC_TESup.push_back(filename_WZ_TESup);
  filename_MC_TESdown.push_back(filename_WZ_TESdown);

  XS.push_back(XS_WZ);
  filename_MC.push_back(filename_WZ);
  filename_norm_MC.push_back(filename_norm_WZ);
  MC_sample_name.push_back("EWK_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_WZ_JECup);
  filename_MC_JECdown.push_back(filename_WZ_JECdown);
  filename_MC_TESup.push_back(filename_WZ_TESup);
  filename_MC_TESdown.push_back(filename_WZ_TESdown);

  XS.push_back(XS_WZ);
  filename_MC.push_back(filename_WZ);
  filename_norm_MC.push_back(filename_norm_WZ);
  MC_sample_name.push_back("EWK_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_WZ_JECup);
  filename_MC_JECdown.push_back(filename_WZ_JECdown);
  filename_MC_TESup.push_back(filename_WZ_TESup);
  filename_MC_TESdown.push_back(filename_WZ_TESdown);




  /*XS.push_back(XS_WWW);
  filename_MC.push_back(filename_WWW);
  filename_norm_MC.push_back(filename_norm_WWW);
  MC_sample_name.push_back("WWW");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back(filename_WWW_JECup);
  filename_MC_JECdown.push_back(filename_WWW_JECdown);
  filename_MC_TESup.push_back(filename_WWW_TESup);
  filename_MC_TESdown.push_back(filename_WWW_TESdown);

  XS.push_back(XS_WWW);
  filename_MC.push_back(filename_WWW);
  filename_norm_MC.push_back(filename_norm_WWW);
  MC_sample_name.push_back("WWW_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_WWW_JECup);
  filename_MC_JECdown.push_back(filename_WWW_JECdown);
  filename_MC_TESup.push_back(filename_WWW_TESup);
  filename_MC_TESdown.push_back(filename_WWW_TESdown);

  XS.push_back(XS_WWW);
  filename_MC.push_back(filename_WWW);
  filename_norm_MC.push_back(filename_norm_WWW);
  MC_sample_name.push_back("WWW_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_WWW_JECup);
  filename_MC_JECdown.push_back(filename_WWW_JECdown);
  filename_MC_TESup.push_back(filename_WWW_TESup);
  filename_MC_TESdown.push_back(filename_WWW_TESdown);


  XS.push_back(XS_WWZ);
  filename_MC.push_back(filename_WWZ);
  filename_norm_MC.push_back(filename_norm_WWZ);
  MC_sample_name.push_back("WWZ");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back(filename_WWZ_JECup);
  filename_MC_JECdown.push_back(filename_WWZ_JECdown);
  filename_MC_TESup.push_back(filename_WWZ_TESup);
  filename_MC_TESdown.push_back(filename_WWZ_TESdown);

  XS.push_back(XS_WWZ);
  filename_MC.push_back(filename_WWZ);
  filename_norm_MC.push_back(filename_norm_WWZ);
  MC_sample_name.push_back("WWZ_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_WWZ_JECup);
  filename_MC_JECdown.push_back(filename_WWZ_JECdown);
  filename_MC_TESup.push_back(filename_WWZ_TESup);
  filename_MC_TESdown.push_back(filename_WWZ_TESdown);

  XS.push_back(XS_WWZ);
  filename_MC.push_back(filename_WWZ);
  filename_norm_MC.push_back(filename_norm_WWZ);
  MC_sample_name.push_back("WWZ_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_WWZ_JECup);
  filename_MC_JECdown.push_back(filename_WWZ_JECdown);
  filename_MC_TESup.push_back(filename_WWZ_TESup);
  filename_MC_TESdown.push_back(filename_WWZ_TESdown);
  
  
  XS.push_back(XS_WZZ);
  filename_MC.push_back(filename_WZZ);
  filename_norm_MC.push_back(filename_norm_WZZ);
  MC_sample_name.push_back("WZZ");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back(filename_WZZ_JECup);
  filename_MC_JECdown.push_back(filename_WZZ_JECdown);
  filename_MC_TESup.push_back(filename_WZZ_TESup);
  filename_MC_TESdown.push_back(filename_WZZ_TESdown);

  XS.push_back(XS_WZZ);
  filename_MC.push_back(filename_WZZ);
  filename_norm_MC.push_back(filename_norm_WZZ);
  MC_sample_name.push_back("WZZ_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_WZZ_JECup);
  filename_MC_JECdown.push_back(filename_WZZ_JECdown);
  filename_MC_TESup.push_back(filename_WZZ_TESup);
  filename_MC_TESdown.push_back(filename_WZZ_TESdown);

  XS.push_back(XS_WZZ);
  filename_MC.push_back(filename_WZZ);
  filename_norm_MC.push_back(filename_norm_WZZ);
  MC_sample_name.push_back("WZZ_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_WZZ_JECup);
  filename_MC_JECdown.push_back(filename_WZZ_JECdown);
  filename_MC_TESup.push_back(filename_WZZ_TESup);
  filename_MC_TESdown.push_back(filename_WZZ_TESdown);


  XS.push_back(XS_ZZZ);
  filename_MC.push_back(filename_ZZZ);
  filename_norm_MC.push_back(filename_norm_ZZZ);
  MC_sample_name.push_back("ZZZ");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back(filename_ZZZ_JECup);
  filename_MC_JECdown.push_back(filename_ZZZ_JECdown);
  filename_MC_TESup.push_back(filename_ZZZ_TESup);
  filename_MC_TESdown.push_back(filename_ZZZ_TESdown);

  XS.push_back(XS_ZZZ);
  filename_MC.push_back(filename_ZZZ);
  filename_norm_MC.push_back(filename_norm_ZZZ);
  MC_sample_name.push_back("ZZZ_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ZZZ_JECup);
  filename_MC_JECdown.push_back(filename_ZZZ_JECdown);
  filename_MC_TESup.push_back(filename_ZZZ_TESup);
  filename_MC_TESdown.push_back(filename_ZZZ_TESdown);

  XS.push_back(XS_ZZZ);
  filename_MC.push_back(filename_ZZZ);
  filename_norm_MC.push_back(filename_norm_ZZZ);
  MC_sample_name.push_back("ZZZ_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ZZZ_JECup);
  filename_MC_JECdown.push_back(filename_ZZZ_JECdown);
  filename_MC_TESup.push_back(filename_ZZZ_TESup);
  filename_MC_TESdown.push_back(filename_ZZZ_TESdown);


  XS.push_back(XS_WpWp);
  filename_MC.push_back(filename_WpWp);
  filename_norm_MC.push_back(filename_norm_WpWp);
  MC_sample_name.push_back("WWss");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back(filename_WpWp_JECup);
  filename_MC_JECdown.push_back(filename_WpWp_JECdown);
  filename_MC_TESup.push_back(filename_WpWp_TESup);
  filename_MC_TESdown.push_back(filename_WpWp_TESdown);

  XS.push_back(XS_WpWp);
  filename_MC.push_back(filename_WpWp);
  filename_norm_MC.push_back(filename_norm_WpWp);
  MC_sample_name.push_back("WWss_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_WpWp_JECup);
  filename_MC_JECdown.push_back(filename_WpWp_JECdown);
  filename_MC_TESup.push_back(filename_WpWp_TESup);
  filename_MC_TESdown.push_back(filename_WpWp_TESdown);

  XS.push_back(XS_WpWp);
  filename_MC.push_back(filename_WpWp);
  filename_norm_MC.push_back(filename_norm_WpWp);
  MC_sample_name.push_back("WWss_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_WpWp_JECup);
  filename_MC_JECdown.push_back(filename_WpWp_JECdown);
  filename_MC_TESup.push_back(filename_WpWp_TESup);
  filename_MC_TESdown.push_back(filename_WpWp_TESdown);*/

  XS.push_back(XS_tZq);
  filename_MC.push_back(filename_tZq);
  filename_norm_MC.push_back(filename_norm_tZq);
  MC_sample_name.push_back("tZq");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back(filename_tZq_JECup);
  filename_MC_JECdown.push_back(filename_tZq_JECdown);
  filename_MC_TESup.push_back(filename_tZq_TESup);
  filename_MC_TESdown.push_back(filename_tZq_TESdown);

  XS.push_back(XS_tZq);
  filename_MC.push_back(filename_tZq);
  filename_norm_MC.push_back(filename_norm_tZq);
  MC_sample_name.push_back("tZq_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_tZq_JECup);
  filename_MC_JECdown.push_back(filename_tZq_JECdown);
  filename_MC_TESup.push_back(filename_tZq_TESup);
  filename_MC_TESdown.push_back(filename_tZq_TESdown);

  XS.push_back(XS_tZq);
  filename_MC.push_back(filename_tZq);
  filename_norm_MC.push_back(filename_norm_tZq);
  MC_sample_name.push_back("tZq_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_tZq_JECup);
  filename_MC_JECdown.push_back(filename_tZq_JECdown);
  filename_MC_TESup.push_back(filename_tZq_TESup);
  filename_MC_TESdown.push_back(filename_tZq_TESdown);


  filename_data.push_back(filename_DoubleEG_2016B);
  filename_data.push_back(filename_MuonEG_2016B);
  filename_data.push_back(filename_DoubleMu_2016B);
  filename_data.push_back(filename_SingleMu_2016B);
  filename_data.push_back(filename_SingleEle_2016B);

  filename_data.push_back(filename_DoubleEG_2016C);
  filename_data.push_back(filename_MuonEG_2016C);
  filename_data.push_back(filename_DoubleMu_2016C);
  filename_data.push_back(filename_SingleMu_2016C);
  filename_data.push_back(filename_SingleEle_2016C);

  filename_data.push_back(filename_DoubleEG_2016D);
  filename_data.push_back(filename_MuonEG_2016D);
  filename_data.push_back(filename_DoubleMu_2016D);
  filename_data.push_back(filename_SingleMu_2016D);
  filename_data.push_back(filename_SingleEle_2016D);

  filename_data.push_back(filename_DoubleEG_2016E);
  filename_data.push_back(filename_MuonEG_2016E);
  filename_data.push_back(filename_DoubleMu_2016E);
  filename_data.push_back(filename_SingleMu_2016E);
  filename_data.push_back(filename_SingleEle_2016E);

  filename_data.push_back(filename_DoubleEG_2016F);
  filename_data.push_back(filename_MuonEG_2016F);
  filename_data.push_back(filename_DoubleMu_2016F);
  filename_data.push_back(filename_SingleMu_2016F);
  filename_data.push_back(filename_SingleEle_2016F);

  filename_data.push_back(filename_DoubleEG_2016G);
  filename_data.push_back(filename_MuonEG_2016G);
  filename_data.push_back(filename_DoubleMu_2016G);
  filename_data.push_back(filename_SingleMu_2016G);
  filename_data.push_back(filename_SingleEle_2016G);

  filename_data.push_back(filename_DoubleEG_2016Hv2);
  filename_data.push_back(filename_MuonEG_2016Hv2);
  filename_data.push_back(filename_DoubleMu_2016Hv2);
  filename_data.push_back(filename_SingleMu_2016Hv2);
  filename_data.push_back(filename_SingleEle_2016Hv2);

  filename_data.push_back(filename_DoubleEG_2016Hv3);
  filename_data.push_back(filename_MuonEG_2016Hv3);
  filename_data.push_back(filename_DoubleMu_2016Hv3);
  filename_data.push_back(filename_SingleMu_2016Hv3);
  filename_data.push_back(filename_SingleEle_2016Hv3);



  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH");
  MC_sample_cut_thu_unc.push_back("1");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_gentau");
  MC_sample_cut_thu_unc.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_faketau");
  MC_sample_cut_thu_unc.push_back("!recotauh_sel_isGenMatched[0]");

  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_htt");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]<=5");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_htt_gentau");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]<=5 && recotauh_sel_isGenMatched[0]");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_htt_faketau");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]<=5 && !recotauh_sel_isGenMatched[0]");

  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hww");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genW==4");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hww_gentau");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genW==4 && recotauh_sel_isGenMatched[0]");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hww_faketau");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genW==4 && !recotauh_sel_isGenMatched[0]");

  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hzz");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genZ==2");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hzz_gentau");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genZ==2 && recotauh_sel_isGenMatched[0]");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hzz_faketau");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genZ==2 && !recotauh_sel_isGenMatched[0]");

  filename_MC_thu_unc.push_back(filename_ttW);
  MC_sample_name_thu_unc.push_back("TTW");
  MC_sample_cut_thu_unc.push_back("1");
  filename_MC_thu_unc.push_back(filename_ttW);
  MC_sample_name_thu_unc.push_back("TTW_gentau");
  MC_sample_cut_thu_unc.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_thu_unc.push_back(filename_ttW);
  MC_sample_name_thu_unc.push_back("TTW_faketau");
  MC_sample_cut_thu_unc.push_back("!recotauh_sel_isGenMatched[0]");

  filename_MC_thu_unc.push_back(filename_ttZ);
  MC_sample_name_thu_unc.push_back("ttZ");
  MC_sample_cut_thu_unc.push_back("1");
  filename_MC_thu_unc.push_back(filename_ttZ);
  MC_sample_name_thu_unc.push_back("ttZ_gentau");
  MC_sample_cut_thu_unc.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_thu_unc.push_back(filename_ttZ);
  MC_sample_name_thu_unc.push_back("ttZ_faketau");
  MC_sample_cut_thu_unc.push_back("!recotauh_sel_isGenMatched[0]");

  filename_MC_thu_unc.push_back(filename_ttG);
  MC_sample_name_thu_unc.push_back("ttG");
  MC_sample_cut_thu_unc.push_back("1");
  filename_MC_thu_unc.push_back(filename_ttG);
  MC_sample_name_thu_unc.push_back("ttG_gentau");
  MC_sample_cut_thu_unc.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_thu_unc.push_back(filename_ttG);
  MC_sample_name_thu_unc.push_back("ttG_faketau");
  MC_sample_cut_thu_unc.push_back("!recotauh_sel_isGenMatched[0]");


  bTag_syst_names.push_back("JESUp");
  bTag_syst_names.push_back("JESDown");
  bTag_syst_names.push_back("LFUp");
  bTag_syst_names.push_back("LFDown");
  bTag_syst_names.push_back("HFUp");
  bTag_syst_names.push_back("HFDown");
  bTag_syst_names.push_back("HFStats1Up");
  bTag_syst_names.push_back("HFStats1Down");
  bTag_syst_names.push_back("HFStats2Up");
  bTag_syst_names.push_back("HFStats2Down");
  bTag_syst_names.push_back("LFStats1Up");
  bTag_syst_names.push_back("LFStats1Down");
  bTag_syst_names.push_back("LFStats2Up");
  bTag_syst_names.push_back("LFStats2Down");
  bTag_syst_names.push_back("CFErr1Up");
  bTag_syst_names.push_back("CFErr1Down");
  bTag_syst_names.push_back("CFErr2Up");
  bTag_syst_names.push_back("CFErr2Down");


}







void datacard_maker(TString var1, int nbin, float xmin, float xmax,
		    TString cut_cat1, TString file, bool syst=false){


  TString var = var1 + "*(" + var1 + Form("<=%f && ",xmax) + var1 + Form(">=%f)",xmin)  + Form("+ %f*(",0.999*xmax) + var1 + Form(">%f)",xmax) + Form("+ %f*(",1.001*xmin) + var1 + Form("<%f)",xmin);
  cout<<var<<endl;

  TString cut_cat = "abs(recolep_sel_charge[0] + recolep_sel_charge[1] + recolep_sel_charge[2])==1 &&" + cut_cat1;

  initialize();


  
  vector<TString> cat_names;
  cat_names.push_back("ttH_3l_1tau");


  vector<int> cat;
  cat.push_back(16);

  vector<int> cat_fakes;
  for(unsigned int i=0;i<cat.size();i++){
    cat_fakes.push_back(30+cat[i]);
  }
  
  TFile* f_new = TFile::Open(file,"RECREATE");
  


  for(unsigned int i_cat=0;i_cat<cat_names.size();i_cat++){

    cout<<cat_names[i_cat]<<endl;

    f_new->cd();
    //TDirectory* dir = f_new->mkdir(cat_names[i_cat]);
    //dir->cd();

    //////////////////////////////////////////
    //////////////////////////////////////////
    /////////          NOMINAL        ////////
    //////////////////////////////////////////
    //////////////////////////////////////////


    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      TH1F* h_MC = single_plot(filename_MC[i_MC],
			       "HTauTauTree_3l_ttZ_CR",
			       var,
			       "MC_weight*PU_weight_2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(isTrig_3l &&" + MC_sample_cut[i_MC] + " && " + cut_cat + ")",
			       nbin,xmin,xmax);     
      
      TH1F* h_MC_norm = single_plot(filename_norm_MC[i_MC],
				    "HTauTauTree",
				    "1",
				    "MC_weight*PU_weight_2016",
				    3,0,3);


      h_MC->Scale(luminosity*XS[i_MC]/h_MC_norm->Integral());
      h_MC->SetNameTitle("x_"+MC_sample_name[i_MC],"x_"+MC_sample_name[i_MC]);
      h_MC->Write();


    }


    vector<TString> bkg_type;
    bkg_type.push_back("");
    bkg_type.push_back("_gentau");
    bkg_type.push_back("_faketau");

    for(unsigned int i=0;i<bkg_type.size();i++){
      
      TH1F* h_TTZ = (TH1F*)f_new->Get("x_ttZ"+bkg_type[i]);
      h_TTZ->Add( (TH1F*)f_new->Get("x_ttG"+bkg_type[i]) );
      h_TTZ->SetNameTitle("x_TTZ"+bkg_type[i],"x_TTZ"+bkg_type[i]);
      h_TTZ->Write();
      
      TH1F* h_Rares = (TH1F*)f_new->Get("x_tZq"+bkg_type[i]);
      /*h_Rares->Add( (TH1F*)f_new->Get("x_WWZ"+bkg_type[i]) );
      h_Rares->Add( (TH1F*)f_new->Get("x_WZZ"+bkg_type[i]) );
      h_Rares->Add( (TH1F*)f_new->Get("x_ZZZ"+bkg_type[i]) );
      h_Rares->Add( (TH1F*)f_new->Get("x_WWss"+bkg_type[i]) );
      h_Rares->Add( (TH1F*)f_new->Get("x_WWW"+bkg_type[i]) );*/
      h_Rares->SetNameTitle("x_Rares"+bkg_type[i],"x_Rares"+bkg_type[i]);
      h_Rares->Write();

    }

    bkg_type.erase(bkg_type.begin()+3);

    
    //Fakes
    
    /*TH1F* h_fakes =single_plot(filename_data,
			       "HTauTauTree_3l_lepMVA_CR",
			       var,
			       Form("event_weight_ttH*(category==%i && isTrig_3l_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",
			       nbin,xmin,xmax);
    
    h_fakes->Scale(luminosity/36814.); //Data files for 36.8 fb-1
    h_fakes->Add( (TH1F*)f_new->Get("x_ttH_genmatch_fake_CR"), -1 );
    h_fakes->Add( (TH1F*)f_new->Get("x_TTW_genmatch_fake_CR"), -1 );
    h_fakes->Add( (TH1F*)f_new->Get("x_TTZ_genmatch_fake_CR"), -1 );
    h_fakes->Add( (TH1F*)f_new->Get("x_EWK_genmatch_fake_CR"), -1 );
    h_fakes->Add( (TH1F*)f_new->Get("x_Rares_genmatch_fake_CR"), -1 );
    h_fakes->SetNameTitle("x_fakes_data","x_fakes_data");
    h_fakes->Write();*/

    
    //Data
    
    TH1F* h_data_obs =single_plot(filename_data,
				  "HTauTauTree_3l_ttZ_CR",
				  var,
				  "isTrig_3l && " + cut_cat,		
				  nbin,xmin,xmax);
      
    h_data_obs->Scale(luminosity/36814.); //Data files for 36.8 fb-1
      
    h_data_obs->SetNameTitle("x_data_obs","x_data_obs");
    h_data_obs->Write();

  }

  f_new->Close();
  return;

}









  /*void datacard_maker_MVA_3l_syst(){

  TString var="1*(MVA_3l_ttbar>-1 && MVA_3l_ttbar<=-0.3 && MVA_3l_ttV_v2>-1. && MVA_3l_ttV_v2<=1) + 2*(MVA_3l_ttbar>-0.3 && MVA_3l_ttbar<=0.3 && MVA_3l_ttV_v2>-1. && MVA_3l_ttV_v2<=0.25) + 3*(MVA_3l_ttbar>-0.3 && MVA_3l_ttbar<=0.3 && MVA_3l_ttV_v2>0.25 && MVA_3l_ttV_v2<=1.) + 4*(MVA_3l_ttbar>0.3 && MVA_3l_ttbar<=1. && MVA_3l_ttV_v2>-1. && MVA_3l_ttV_v2<=0.25) + 5*(MVA_3l_ttbar>0.3 && MVA_3l_ttbar<=1. && MVA_3l_ttV_v2>0.25 && MVA_3l_ttV_v2<=1.)";

  
  int nbin = 5;
  float xmin = 0.5;
  float xmax = 5.5;

  TString cut = "1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MVA_3l_syst_nofaketau_36.8fb.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file,true);


  }*/







void datacard_maker_n_fakelep_3l_ttZ_CR(){

  TString var="n_recolep_fakeable";

  
  int nbin = 5;
  float xmin = 2.;
  float xmax = 7.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_fakelep_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}



void datacard_maker_n_fakeele_3l_ttZ_CR(){

  TString var="n_recoele_fakeable";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 5.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_fakeele_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}



void datacard_maker_n_fakemu_3l_ttZ_CR(){

  TString var="n_recomu_fakeable";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 5.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_fakemu_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}





void datacard_maker_n_faketau_3l_ttZ_CR(){

  TString var="n_recotauh";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 5.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_faketau_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}



void datacard_maker_n_jet_3l_ttZ_CR(){

  TString var="n_recoPFJet";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 10.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_jet_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}





void datacard_maker_n_jet_CSVloose_3l_ttZ_CR(){

  TString var="n_recoPFJet_btag_loose";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 5.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_jet_CSVloose_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}





void datacard_maker_n_jet_CSVmedium_3l_ttZ_CR(){

  TString var="n_recoPFJet_btag_medium";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 5.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_jet_CSVmedium_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}




void datacard_maker_ETmiss_3l_ttZ_CR(){

  TString var="PFMET";

  
  int nbin = 12;
  float xmin = 0.;
  float xmax = 300.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_ETmiss_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}






void datacard_maker_pT_lep1_3l_ttZ_CR(){

  TString var="recolep_pt[0]";

  
  int nbin = 15;
  float xmin = 0.;
  float xmax = 300.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_lep1_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}





void datacard_maker_min_mll_3l_ttZ_CR(){

  TString var="min( min(sqrt((recolep_sel_e[0]+recolep_sel_e[1])**2-(recolep_sel_px[0]+recolep_sel_px[1])**2-(recolep_sel_py[0]+recolep_sel_py[1])**2-(recolep_sel_pz[0]+recolep_sel_pz[1])**2),sqrt((recolep_sel_e[2]+recolep_sel_e[1])**2-(recolep_sel_px[2]+recolep_sel_px[1])**2-(recolep_sel_py[2]+recolep_sel_py[1])**2-(recolep_sel_pz[2]+recolep_sel_pz[1])**2) ), sqrt((recolep_sel_e[0]+recolep_sel_e[2])**2-(recolep_sel_px[0]+recolep_sel_px[2])**2-(recolep_sel_py[0]+recolep_sel_py[2])**2-(recolep_sel_pz[0]+recolep_sel_pz[2])**2) )";

  
  int nbin = 60;
  float xmin = 60.;
  float xmax = 120.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_min_mll_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}





void datacard_maker_bestMZ_3l_ttZ_CR(){

  TString var="best_mZ";

  
  int nbin = 30;
  float xmin = 60.;
  float xmax = 120.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_bestMZ_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}


void datacard_maker_min_mll_3l1tau_ttZ_CR(){

  TString var="min( min(sqrt((recolep_sel_e[0]+recolep_sel_e[1])**2-(recolep_sel_px[0]+recolep_sel_px[1])**2-(recolep_sel_py[0]+recolep_sel_py[1])**2-(recolep_sel_pz[0]+recolep_sel_pz[1])**2),sqrt((recolep_sel_e[2]+recolep_sel_e[1])**2-(recolep_sel_px[2]+recolep_sel_px[1])**2-(recolep_sel_py[2]+recolep_sel_py[1])**2-(recolep_sel_pz[2]+recolep_sel_pz[1])**2) ), sqrt((recolep_sel_e[0]+recolep_sel_e[2])**2-(recolep_sel_px[0]+recolep_sel_px[2])**2-(recolep_sel_py[0]+recolep_sel_py[2])**2-(recolep_sel_pz[0]+recolep_sel_pz[2])**2) )";

  
  int nbin = 60;
  float xmin = 60.;
  float xmax = 120.;

  TString cut="n_recotauh>0";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_min_mll_3l1tau_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}



void datacard_maker_bestMZ_3l1tau_ttZ_CR(){

  TString var="best_mZ";

  
  int nbin = 30;
  float xmin = 60.;
  float xmax = 120.;

  TString cut="n_recotauh>0";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_bestMZ_3l1tau_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}




void datacard_maker_pT_lep2_3l_ttZ_CR(){

  TString var="recolep_pt[1]";

  
  int nbin = 15;
  float xmin = 0.;
  float xmax = 150.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_lep2_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}




void datacard_maker_pT_lep3_3l_ttZ_CR(){

  TString var="recolep_pt[2]";

  
  int nbin = 8;
  float xmin = 0.;
  float xmax = 80.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_lep3_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}



void datacard_maker_pT_tau_3l_ttZ_CR(){

  TString var="recotauh_pt[0]";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 100.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_tau_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}



void datacard_maker_pT_jet1_3l_ttZ_CR(){

  TString var="recoPFJet_pt[0]";

  int nbin = 7;
  float xmin = 0.;
  float xmax = 350.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_jet1_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}


void datacard_maker_pT_jet2_3l_ttZ_CR(){

  TString var="recoPFJet_pt[1]";
  
  int nbin = 4;
  float xmin = 0.;
  float xmax = 200.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_jet2_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}





void datacard_maker_pT_bjet1_3l_ttZ_CR(){

  TString var="recoPFJet_CSVsort_pt[0]";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 250.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_bjet1_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}


void datacard_maker_pT_bjet2_3l_ttZ_CR(){

  TString var="recoPFJet_CSVsort_pt[1]";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 250.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_bjet2_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}





void datacard_maker_CSV_jet1_3l_ttZ_CR(){

  TString var="recoPFJet_CSVscore[0]";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_CSV_jet1_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}


void datacard_maker_CSV_jet2_3l_ttZ_CR(){

  TString var="recoPFJet_CSVscore[1]";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_CSV_jet2_3l_ttZ_CR_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}








void datacard_maker_all(){
  
  datacard_maker_n_fakelep_3l_ttZ_CR();
  datacard_maker_n_fakeele_3l_ttZ_CR();
  datacard_maker_n_fakemu_3l_ttZ_CR();
  datacard_maker_n_faketau_3l_ttZ_CR();
  datacard_maker_n_jet_3l_ttZ_CR();
  datacard_maker_n_jet_CSVloose_3l_ttZ_CR();
  datacard_maker_n_jet_CSVmedium_3l_ttZ_CR();
  datacard_maker_ETmiss_3l_ttZ_CR();
  datacard_maker_pT_lep1_3l_ttZ_CR();
  datacard_maker_pT_lep2_3l_ttZ_CR();
  datacard_maker_pT_lep3_3l_ttZ_CR();
  datacard_maker_pT_tau_3l_ttZ_CR();
  datacard_maker_pT_jet1_3l_ttZ_CR();
  datacard_maker_pT_jet2_3l_ttZ_CR();
  datacard_maker_CSV_jet1_3l_ttZ_CR();
  datacard_maker_CSV_jet2_3l_ttZ_CR();
  datacard_maker_pT_bjet1_3l_ttZ_CR();
  datacard_maker_pT_bjet2_3l_ttZ_CR();

}


