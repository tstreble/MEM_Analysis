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
TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_PU_newtrig_MVA_3l.root";

TString filename_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_PU_newtrig_MVA_3l.root";
TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_PU_newtrig_MVA_3l.root";
TString filename_ttG = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttG_split_PU_newtrig_MVA_3l.root";

TString filename_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_PU_newtrig_MVA_3l.root";

TString filename_WWW = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WWW_split_PU_newtrig_MVA_3l.root";
TString filename_WWZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WWZ_split_PU_newtrig_MVA_3l.root";
TString filename_WZZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WZZ_split_PU_newtrig_MVA_3l.root";
TString filename_ZZZ = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_ZZZ_split_PU_newtrig_MVA_3l.root";
TString filename_tZq = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_tZq_split_PU_newtrig_MVA_3l.root";


TString filename_WpWp = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WpWp_split_PU_newtrig_MVA_3l.root";

TString filename_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_*split_PU_newtrig_MVA_3l.root";
TString filename_ttbar_SLfromT = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromT_split_PU_newtrig_MVA_3l.root";

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

TString filename_DoubleEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split_newtrig_MVA_3l.root";
TString filename_MuonEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split_newtrig_MVA_3l.root";
TString filename_DoubleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split_newtrig_MVA_3l.root";
TString filename_SingleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split_newtrig_MVA_3l.root";
TString filename_SingleEle_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split_newtrig_MVA_3l.root";

TString filename_DoubleEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split_newtrig_MVA_3l.root";
TString filename_MuonEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split_newtrig_MVA_3l.root";
TString filename_DoubleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split_newtrig_MVA_3l.root";
TString filename_SingleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split_newtrig_MVA_3l.root";
TString filename_SingleEle_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split_newtrig_MVA_3l.root";

TString filename_DoubleEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split_newtrig_MVA_3l.root";
TString filename_MuonEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split_newtrig_MVA_3l.root";
TString filename_DoubleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split_newtrig_MVA_3l.root";
TString filename_SingleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split_newtrig_MVA_3l.root";
TString filename_SingleEle_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split_newtrig_MVA_3l.root";

TString filename_DoubleEG_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016E_split_newtrig_MVA_3l.root";
TString filename_MuonEG_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016E_split_newtrig_MVA_3l.root";
TString filename_DoubleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016E_split_newtrig_MVA_3l.root";
TString filename_SingleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016E_split_newtrig_MVA_3l.root";
TString filename_SingleEle_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016E_split_newtrig_MVA_3l.root";

TString filename_DoubleEG_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016F_split_newtrig_MVA_3l.root";
TString filename_MuonEG_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016F_split_newtrig_MVA_3l.root";
TString filename_DoubleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016F_split_newtrig_MVA_3l.root";
TString filename_SingleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016F_split_newtrig_MVA_3l.root";
TString filename_SingleEle_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016F_split_newtrig_MVA_3l.root";

TString filename_DoubleEG_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016G_split_newtrig_MVA_3l.root";
TString filename_MuonEG_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016G_split_newtrig_MVA_3l.root";
TString filename_DoubleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016G_split_newtrig_MVA_3l.root";
TString filename_SingleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016G_split_newtrig_MVA_3l.root";
TString filename_SingleEle_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016G_split_newtrig_MVA_3l.root";

TString filename_DoubleEG_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016Hv2_split_newtrig_MVA_3l.root";
TString filename_MuonEG_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016Hv2_split_newtrig_MVA_3l.root";
TString filename_DoubleMu_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016Hv2_split_newtrig_MVA_3l.root";
TString filename_SingleMu_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv2_split_newtrig_MVA_3l.root";
TString filename_SingleEle_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv2_split_newtrig_MVA_3l.root";

TString filename_DoubleEG_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016Hv3_split_newtrig_MVA_3l.root";
TString filename_MuonEG_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016Hv3_split_newtrig_MVA_3l.root";
TString filename_DoubleMu_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016Hv3_split_newtrig_MVA_3l.root";
TString filename_SingleMu_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv3_split_newtrig_MVA_3l.root";
TString filename_SingleEle_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv3_split_newtrig_MVA_3l.root";


vector<TString> filename_data;

vector<TString> MC_sample_name;
vector<TString> MC_sample_cut;

vector<TString> filename_MC_thu_unc;
vector<TString> MC_sample_name_thu_unc;
vector<TString> MC_sample_cut_thu_unc;


// MC JEC + TES


TString filename_ttH_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/ttH/HTauTauTree_ttH_Hnonbb_split_JECup_PU_newtrig_MVA_3l.root";
TString filename_ttH_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/ttH/HTauTauTree_ttH_Hnonbb_split_JECdown_PU_newtrig_MVA_3l.root";
TString filename_ttH_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/ttH/HTauTauTree_ttH_Hnonbb_split_TESup_PU_newtrig_MVA_3l.root";
TString filename_ttH_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/ttH/HTauTauTree_ttH_Hnonbb_split_TESdown_PU_newtrig_MVA_3l.root";


TString filename_ttZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttZ_split_JECup_PU_newtrig_MVA_3l.root";
TString filename_ttZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/ttV/HTauTauTree_ttZ_split_JECdown_PU_newtrig_MVA_3l.root";
TString filename_ttZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/ttV/HTauTauTree_ttZ_split_TESup_PU_newtrig_MVA_3l.root";
TString filename_ttZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttZ_split_TESdown_PU_newtrig_MVA_3l.root";

TString filename_ttG_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttG_split_JECup_PU_newtrig_MVA_3l.root";
TString filename_ttG_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/ttV/HTauTauTree_ttG_split_JECdown_PU_newtrig_MVA_3l.root";
TString filename_ttG_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/ttV/HTauTauTree_ttG_split_TESup_PU_newtrig_MVA_3l.root";
TString filename_ttG_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttG_split_TESdown_PU_newtrig_MVA_3l.root";


TString filename_ttW_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttW_split_JECup_PU_newtrig_MVA_3l.root";
TString filename_ttW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/ttV/HTauTauTree_ttW_split_JECdown_PU_newtrig_MVA_3l.root";
TString filename_ttW_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/ttV/HTauTauTree_ttW_split_TESup_PU_newtrig_MVA_3l.root";
TString filename_ttW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttW_split_TESdown_PU_newtrig_MVA_3l.root";

TString filename_WZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/EWK/HTauTauTree_WZ_split_JECup_PU_newtrig_MVA_3l.root";
TString filename_WZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/EWK/HTauTauTree_WZ_split_JECdown_PU_newtrig_MVA_3l.root";
TString filename_WZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/EWK/HTauTauTree_WZ_split_TESup_PU_newtrig_MVA_3l.root";
TString filename_WZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/EWK/HTauTauTree_WZ_split_TESdown_PU_newtrig_MVA_3l.root";

TString filename_WWW_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_WWW_split_JECup_PU_newtrig_MVA_3l.root";
TString filename_WWW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_WWW_split_JECdown_PU_newtrig_MVA_3l.root";
TString filename_WWW_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_WWW_split_TESup_PU_newtrig_MVA_3l.root";
TString filename_WWW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_WWW_split_TESdown_PU_newtrig_MVA_3l.root";

TString filename_WWZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_WWZ_split_JECup_PU_newtrig_MVA_3l.root";
TString filename_WWZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_WWZ_split_JECdown_PU_newtrig_MVA_3l.root";
TString filename_WWZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_WWZ_split_TESup_PU_newtrig_MVA_3l.root";
TString filename_WWZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_WWZ_split_TESdown_PU_newtrig_MVA_3l.root";

TString filename_WZZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_WZZ_split_JECup_PU_newtrig_MVA_3l.root";
TString filename_WZZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_WZZ_split_JECdown_PU_newtrig_MVA_3l.root";
TString filename_WZZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_WZZ_split_TESup_PU_newtrig_MVA_3l.root";
TString filename_WZZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_WZZ_split_TESdown_PU_newtrig_MVA_3l.root";

TString filename_ZZZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_ZZZ_split_JECup_PU_newtrig_MVA_3l.root";
TString filename_ZZZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_ZZZ_split_JECdown_PU_newtrig_MVA_3l.root";
TString filename_ZZZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_ZZZ_split_TESup_PU_newtrig_MVA_3l.root";
TString filename_ZZZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_ZZZ_split_TESdown_PU_newtrig_MVA_3l.root";

TString filename_WpWp_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_WpWp_split_JECup_PU_newtrig_MVA_3l.root";
TString filename_WpWp_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_WpWp_split_JECdown_PU_newtrig_MVA_3l.root";
TString filename_WpWp_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_WpWp_split_TESup_PU_newtrig_MVA_3l.root";
TString filename_WpWp_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_WpWp_split_TESdown_PU_newtrig_MVA_3l.root";

TString filename_tZq_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECup/Rares/HTauTauTree_tZq_split_JECup_PU_newtrig_MVA_3l.root";
TString filename_tZq_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/JECdown/Rares/HTauTauTree_tZq_split_JECdown_PU_newtrig_MVA_3l.root";
TString filename_tZq_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESup/Rares/HTauTauTree_tZq_split_TESup_PU_newtrig_MVA_3l.root";
TString filename_tZq_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/TESdown/Rares/HTauTauTree_tZq_split_TESdown_PU_newtrig_MVA_3l.root";

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




  XS.push_back(XS_WWW);
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
  filename_MC_TESdown.push_back(filename_WpWp_TESdown);

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


 TString var = var1 + "*(" + var1 + Form("<=%f) + %f*(",xmax,0.999*xmax) + var1 + Form(">%f)",xmax);
  cout<<var<<endl;

  TString cut_cat = "(recolep_sel_charge[0] + recolep_sel_charge[1] + recolep_sel_charge[2] + recotauh_sel_charge[0])==0 &&" + cut_cat1;

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

    vector<float> norm_MC;
    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      TH1F* h_MC_norm = single_plot(filename_norm_MC[i_MC],
                                    "HTauTauTree",
                                    "1",
                                    "MC_weight*PU_weight_MCSummer2016",
                                    3,0,3);

      norm_MC.push_back(h_MC_norm->Integral());

    }


    //////////////////////////////////////////
    //////////////////////////////////////////
    /////////          NOMINAL        ////////
    //////////////////////////////////////////
    //////////////////////////////////////////


    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      TH1F* h_MC = single_plot(filename_MC[i_MC],
			       "HTauTauTree_3l",
			       var,
			       Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(1-0.1*recotauh_sel_isGenMatched[0])*(category==%i && isTrig_3l_v2 &&",cat[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat + ")",
			       nbin,xmin,xmax);

      h_MC->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC->SetNameTitle("x_"+MC_sample_name[i_MC],"x_"+MC_sample_name[i_MC]);
      makeBinContentsPositive(h_MC,true);
      h_MC->Write();

      if(MC_sample_name[i_MC].Contains("gentau") || MC_sample_name[i_MC].Contains("faketau")) continue;

      TH1F* h_MC_genmatch = single_plot(filename_MC[i_MC],
				    "HTauTauTree_3l_lepMVA_CR",
				    var,
				    Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*event_weight_ttH*(1-0.1*recotauh_sel_isGenMatched[0])*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recolep_sel_isGenMatched[2] && ",cat_fakes[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat + ")",
				    nbin,xmin,xmax);

      h_MC_genmatch->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_genmatch->SetNameTitle("x_"+MC_sample_name[i_MC]+"_genmatch_fake_CR","x_"+MC_sample_name[i_MC]+"_genmatch_fake_CR");
      h_MC_genmatch->Write();


    }


    vector<TString> bkg_type;
    bkg_type.push_back("");
    bkg_type.push_back("_gentau");
    bkg_type.push_back("_faketau");
    bkg_type.push_back("_genmatch_fake_CR");

    for(unsigned int i=0;i<bkg_type.size();i++){
      
      TH1F* h_TTZ = (TH1F*)f_new->Get("x_ttZ"+bkg_type[i]);
      h_TTZ->Add( (TH1F*)f_new->Get("x_ttG"+bkg_type[i]) );
      h_TTZ->SetNameTitle("x_TTZ"+bkg_type[i],"x_TTZ"+bkg_type[i]);
      h_TTZ->Write();
      
      TH1F* h_Rares = (TH1F*)f_new->Get("x_WWW"+bkg_type[i]);
      h_Rares->Add( (TH1F*)f_new->Get("x_WWZ"+bkg_type[i]) );
      h_Rares->Add( (TH1F*)f_new->Get("x_WZZ"+bkg_type[i]) );
      h_Rares->Add( (TH1F*)f_new->Get("x_ZZZ"+bkg_type[i]) );
      h_Rares->Add( (TH1F*)f_new->Get("x_WWss"+bkg_type[i]) );
      h_Rares->Add( (TH1F*)f_new->Get("x_tZq"+bkg_type[i]) );
      h_Rares->SetNameTitle("x_Rares"+bkg_type[i],"x_Rares"+bkg_type[i]);
      h_Rares->Write();

    }

    bkg_type.erase(bkg_type.begin()+3);

    
    //Fakes
    
    TH1F* h_fakes =single_plot(filename_data,
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
    makeBinContentsPositive(h_fakes,true);
    h_fakes->Write();



    //Fakes MC
    
    TH1F* h_ttbar_DL_fakes_MC =single_plot(filename_ttbar_DL,
				  "HTauTauTree_3l_lepMVA_CR",
				  var,
				  Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*bTagSF_CSVshape_weight*event_weight_ttH*(1-0.1*recotauh_sel_isGenMatched[0])*(category==%i && isTrig_3l_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",
				  nbin,xmin,xmax);
    
    TH1F* h_ttbar_DL_norm =single_plot(filename_norm_ttbar_DL,
				       "HTauTauTree",
				       "1",
				       "MC_weight*PU_weight_MCSummer2016",
				       3,0,3);
 
    h_ttbar_DL_fakes_MC->Scale(luminosity*XS_ttbar_DL/h_ttbar_DL_norm->Integral());
    h_ttbar_DL_fakes_MC->SetNameTitle("x_fakes_MC","x_fakes_MC");
    h_ttbar_DL_fakes_MC->Write();
 
    
    
    //Data
    
    /*TH1F* h_data_obs =single_plot(filename_data,
				  "HTauTauTree_3l",
				  var,
				  Form("(category==%i && isTrig_3l_v2 &&",cat[i_cat]) + cut_cat + ")",		
				  nbin,xmin,xmax);
      
    h_data_obs->Scale(luminosity/36814.); //Data files for 36.8 fb-1
      
    h_data_obs->SetNameTitle("x_data_obs","x_data_obs");
    h_data_obs->Write();*/


    TH1F* h_data_obs = (TH1F*)f_new->Get("x_ttH");
    h_data_obs->Add( (TH1F*)f_new->Get("x_TTW") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_TTZ") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_EWK") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_Rares") );  
    h_data_obs->Add( (TH1F*)f_new->Get("x_fakes_data") );
    h_data_obs->SetNameTitle("x_data_obs","x_data_obs");
    h_data_obs->Write();

    

    if(!syst){
      f_new->Close();
      return;
    }

    cout<<"OK nominal"<<endl;


    //////////////////////////////////////////
    //////////////////////////////////////////
    /////////       SYSTEMATICS       ////////
    //////////////////////////////////////////
    //////////////////////////////////////////

    
    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      //float norm = ((TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]))->Integral();

      for(unsigned int i_b=0;i_b<bTag_syst_names.size();i_b++){       
		    
	TString cut = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*(1-0.1*recotauh_sel_isGenMatched[0])*bTagSF_CSVshape_weight_" + bTag_syst_names[i_b];
	cut+=Form("*(category==%i && isTrig_3l_v2 &&",cat[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat +")";

	TH1F* h_MC_btag_syst = single_plot(filename_MC[i_MC],
					   "HTauTauTree_3l",
					   var,
					   cut,
					   nbin,xmin,xmax);

        h_MC_btag_syst->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);      

	TString h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHl_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHl_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHl_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHl_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHl_btag_cErr2Down";	

	h_MC_btag_syst->SetNameTitle(h_name,h_name);
        makeBinContentsPositive(h_MC_btag_syst);
	h_MC_btag_syst->Write();

      }

    }




    for(unsigned int i_b=0;i_b<bTag_syst_names.size();i_b++){  

      for(unsigned int i_bkg=0;i_bkg<bkg_type.size();i_bkg++){

	TString h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Down";
	
	TString h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Down";
	
	TString h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Down";

	
	TH1F* h_TTZ = (TH1F*)f_new->Get(h_name_ttZ);
	h_TTZ->Add( (TH1F*)f_new->Get(h_name_ttG) );
	h_TTZ->SetNameTitle(h_name_TTZ,h_name_TTZ);
	h_TTZ->Write();
	

	TString h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Down";
	
	TString h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Down";
	
	TString h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Down";
	
	TString h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Down";

	TString h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Down";

	TString h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Down";
	
	TString h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl_btag_cErr2Down";

	
	TH1F* h_Rares = (TH1F*)f_new->Get(h_name_WWW);
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WZZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_ZZZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWss) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_tZq) );
	h_Rares->SetNameTitle(h_name_Rares,h_name_Rares);
	h_Rares->Write();
	
      }

    }

    cout<<"OK syst btag"<<endl;





    for(unsigned i_MC=0;i_MC<MC_sample_name_thu_unc.size();i_MC++){

      //cout<<MC_sample_name_thu_unc[i_MC]<<endl;

      TString syst_name="CMS_ttHl_thu_shape_";
      if(MC_sample_name_thu_unc[i_MC].Contains("ttH"))
	syst_name+="ttH";
      else if(MC_sample_name_thu_unc[i_MC].Contains("ttZ"))
	syst_name+="ttZ";
      else if(MC_sample_name_thu_unc[i_MC].Contains("ttG"))
	syst_name+="ttG";
      else if(MC_sample_name_thu_unc[i_MC].Contains("TTW"))
	syst_name+="ttW";

      //float norm = ((TH1F*)f_new->Get("x_"+MC_sample_name_thu_unc[i_MC]))->Integral();
		    
      TString cut = "PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(1-0.1*recotauh_sel_isGenMatched[0])";
      cut+=Form("*(category==%i && isTrig_3l_v2 && ",cat[i_cat]) + MC_sample_cut_thu_unc[i_MC] + " && " + cut_cat + ")";

      TH1F* h_MC_x1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "HTauTauTree_3l",
				     var,
				     "MC_weight_scale_muR2*"+cut,
				     nbin,xmin,xmax);
      
      h_MC_x1_up->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);      
      h_MC_x1_up->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Up","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Up");
      makeBinContentsPositive(h_MC_x1_up);
      h_MC_x1_up->Write();

      TH1F* h_MC_x1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "HTauTauTree_3l",
				       var,
				       "MC_weight_scale_muR0p5*"+cut,
				       nbin,xmin,xmax);

      h_MC_x1_down->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_x1_down->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Down","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Down");
      makeBinContentsPositive(h_MC_x1_down);
      h_MC_x1_down->Write();

      TH1F* h_MC_y1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "HTauTauTree_3l",
				     var,
				     "MC_weight_scale_muF2*"+cut,
				     nbin,xmin,xmax);
      
      h_MC_y1_up->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_y1_up->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Up","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Up");
      makeBinContentsPositive(h_MC_y1_up);
      h_MC_y1_up->Write();

      TH1F* h_MC_y1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "HTauTauTree_3l",
				       var,
				       "MC_weight_scale_muF0p5*"+cut,
				       nbin,xmin,xmax);
      
      h_MC_y1_down->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_y1_down->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Down","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Down");
      makeBinContentsPositive(h_MC_y1_down);      
      h_MC_y1_down->Write();
      
    }


    vector<TString> thu_uncert;
    thu_uncert.push_back("x1Up");
    thu_uncert.push_back("x1Down");
    thu_uncert.push_back("y1Up");
    thu_uncert.push_back("y1Down");
    

    for(unsigned int i=0;i<thu_uncert.size();i++){

      for(unsigned int i_bkg=0;i_bkg<bkg_type.size();i_bkg++){

	TString h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl_thu_shape_ttZ_"+thu_uncert[i];
	TString h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl_thu_shape_ttG_"+thu_uncert[i];
	TString h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl_thu_shape_ttZ_"+thu_uncert[i];
	
	
	TH1F* h_TTZ = (TH1F*)f_new->Get(h_name_ttZ)->Clone();
	h_TTZ->Add( (TH1F*)f_new->Get(h_name_ttG) );
	h_TTZ->SetNameTitle(h_name_TTZ,h_name_TTZ);
	h_TTZ->Write();

      }

    }

    cout<<"OK syst theoretical "<<endl;


    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){
      
      TString cut = "MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(1-0.1*recotauh_sel_isGenMatched[0])";
      cut+=Form("*(category==%i && isTrig_3l_v2 &&",cat[i_cat]) + MC_sample_cut[i_MC]  + " && " + cut_cat + ")";

      float norm = ((TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]))->Integral();
      
      TH1F* h_MC_JEC_up = single_plot(filename_MC_JECup[i_MC],
				      "HTauTauTree_3l",
				      var,
				      cut,
				      nbin,xmin,xmax);

      h_MC_JEC_up->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);      
      h_MC_JEC_up->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl_JESUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl_JECUp");
      makeBinContentsPositive(h_MC_JEC_up);
      h_MC_JEC_up->Write();

      
      TH1F* h_MC_JEC_down = single_plot(filename_MC_JECdown[i_MC],
					"HTauTauTree_3l",
					var,
					cut,
					nbin,xmin,xmax);
      
      h_MC_JEC_down->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_JEC_down->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl_JESDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl_JECDown");
      makeBinContentsPositive(h_MC_JEC_down);
      h_MC_JEC_down->Write();

      TH1F* h_MC_TES_up = single_plot(filename_MC_TESup[i_MC],
				      "HTauTauTree_3l",
				      var,
				      cut,
				      nbin,xmin,xmax);

      h_MC_TES_up->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);      
      h_MC_TES_up->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl_tauESUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl_tauESUp");
      makeBinContentsPositive(h_MC_TES_up);
      h_MC_TES_up->Write();

      
      TH1F* h_MC_TES_down = single_plot(filename_MC_TESdown[i_MC],
					"HTauTauTree_3l",
					var,
					cut,
					nbin,xmin,xmax);

      h_MC_TES_down->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);      
      h_MC_TES_down->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl_tauESDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl_tauESDown");
      makeBinContentsPositive(h_MC_TES_down);
      h_MC_TES_down->Write();

    }


  
    vector<TString> JES_TES_uncert;
    JES_TES_uncert.push_back("JESUp");
    JES_TES_uncert.push_back("JESDown");
    JES_TES_uncert.push_back("tauESUp");
    JES_TES_uncert.push_back("tauESDown");


    for(unsigned int i=0;i<JES_TES_uncert.size();i++){

      for(unsigned int i_bkg=0;i_bkg<bkg_type.size();i_bkg++){

	TString h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	TString h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	TString h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	
	TH1F* h_TTZ = (TH1F*)f_new->Get(h_name_ttZ)->Clone();
	h_TTZ->Add( (TH1F*)f_new->Get(h_name_ttG) );
	h_TTZ->SetNameTitle(h_name_TTZ,h_name_TTZ);
	h_TTZ->Write();
	
	TString h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	TString h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	TString h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	TString h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	TString h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	TString h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	TString h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	
	TH1F* h_Rares = (TH1F*)f_new->Get(h_name_WWW)->Clone();
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WZZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_ZZZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWss) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_tZq) );
	h_Rares->SetNameTitle(h_name_Rares,h_name_Rares);
	h_Rares->Write();
	
      }

    }
    



    cout<<"OK JEC/TES "<<endl;

    //Bin-by-bin uncertainty
    /*for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      TH1F* h_MC = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]);
      
      for(int i_bin=0;i_bin<=h_MC->GetNbinsX();i_bin++){
	
	double bin_content = h_MC->GetBinContent(i_bin);
	double bin_error = h_MC->GetBinError(i_bin);

	if(bin_error/bin_content>0.05){

	  TString h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHt_templstat_3l_1tau_"+MC_sample_name[i_MC]+Form("_bin%i",i_bin);

	  cout<<h_name<<endl;

	  TH1F* h_MC_bin_up = (TH1F*)h_MC->Clone();
	  h_MC_bin_up->SetBinContent(i_bin,bin_content+bin_error);
	  h_MC_bin_up->Scale(h_MC->Integral()/h_MC_bin_up->Integral());	
	  h_MC_bin_up->SetNameTitle(h_name+"Up",h_name+"Up");
	  h_MC_bin_up->Write();

	  TH1F* h_MC_bin_down = (TH1F*)h_MC->Clone();
	  h_MC_bin_down->SetBinContent(i_bin,bin_content-bin_error);
	  h_MC_bin_down->Scale(h_MC->Integral()/h_MC_bin_down->Integral());
	  h_MC_bin_down->SetNameTitle(h_name+"Down",h_name+"Down");
	  h_MC_bin_down->Write();
	  
	}

      }

    }

          
    for(int i_bin=0;i_bin<=h_fakes->GetNbinsX();i_bin++){
	
      double bin_content = h_fakes->GetBinContent(i_bin);
      double bin_error = h_fakes->GetBinError(i_bin);

      if(bin_error/bin_content>0.05){

	TString h_name = Form("x_fakes_data_CMS_ttHt_templstat_3l_1tau_fakes_bin%i",i_bin);

	cout<<h_name<<endl;

	TH1F* h_fakes_bin_up = (TH1F*)h_fakes->Clone();
	h_fakes_bin_up->SetBinContent(i_bin,bin_content+bin_error);
	h_fakes_bin_up->Scale(h_fakes->Integral()/h_fakes_bin_up->Integral());
	h_fakes_bin_up->SetNameTitle(h_name+"Up",h_name+"Up");
	h_fakes_bin_up->Write();

	TH1F* h_fakes_bin_down = (TH1F*)h_fakes->Clone();
	h_fakes_bin_down->SetBinContent(i_bin,bin_content-bin_error);
	h_fakes_bin_down->Scale(h_fakes->Integral()/h_fakes_bin_down->Integral());
	h_fakes_bin_down->SetNameTitle(h_name+"Down",h_name+"Down");
	h_fakes_bin_down->Write();
	
      }
      
    }
    

    for(unsigned int i_bkg=0;i_bkg<bkg_type.size();i_bkg++){

      TH1* h_TTZ = (TH1F*)f_new->Get("x_TTZ"+bkg_type[i_bkg])->Clone();

      for(int i_bin=0;i_bin<h_TTZ->GetNbinsX();i_bin++){

	double bin_content = h_TTZ->GetBinContent(i_bin);
	double bin_error = h_TTZ->GetBinError(i_bin);
	
	if(bin_error/bin_content>0.05){
	  
	  TString h_name = Form("x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHt_templstat_3l_1tau_TTZ"+bkg_type[i_bkg]+"_bin%i",i_bin);
	  
	  cout<<h_name<<endl;
	  
	  TH1F* h_TTZ_bin_up = (TH1F*)h_TTZ->Clone();
	  h_TTZ_bin_up->SetBinContent(i_bin,bin_content+bin_error);
	  h_TTZ_bin_up->Scale(h_TTZ->Integral()/h_TTZ_bin_up->Integral());
	  h_TTZ_bin_up->SetNameTitle(h_name+"Up",h_name+"Up");
	  h_TTZ_bin_up->Write();
	  
	  TH1F* h_TTZ_bin_down = (TH1F*)h_TTZ->Clone();
	  h_TTZ_bin_down->SetBinContent(i_bin,bin_content-bin_error);
	  h_TTZ_bin_down->Scale(h_TTZ->Integral()/h_TTZ_bin_down->Integral());
	  h_TTZ_bin_down->SetNameTitle(h_name+"Down",h_name+"Down");
	  h_TTZ_bin_down->Write();
	  
	}
	
      }



      TH1* h_Rares = (TH1F*)f_new->Get("x_Rares"+bkg_type[i_bkg])->Clone();

      for(int i_bin=0;i_bin<h_Rares->GetNbinsX();i_bin++){
	
	double bin_content = h_Rares->GetBinContent(i_bin);
	double bin_error = h_Rares->GetBinError(i_bin);
	
	if(bin_error/bin_content>0.05){
	  
	  TString h_name = Form("x_Rares"+bkg_type[i_bkg]+"_CMS_ttHt_templstat_3l_1tau_Rares"+bkg_type[i_bkg]+"_bin%i",i_bin);
	  
	  cout<<h_name<<endl;
	  
	  TH1F* h_Rares_bin_up = (TH1F*)h_Rares->Clone();
	  h_Rares_bin_up->SetBinContent(i_bin,bin_content+bin_error);
	  h_Rares_bin_up->Scale(h_Rares->Integral()/h_Rares_bin_up->Integral());
	  h_Rares_bin_up->SetNameTitle(h_name+"Up",h_name+"Up");
	  h_Rares_bin_up->Write();
	  
	  TH1F* h_Rares_bin_down = (TH1F*)h_Rares->Clone();
	  h_Rares_bin_down->SetBinContent(i_bin,bin_content-bin_error);
	  h_Rares_bin_down->Scale(h_Rares->Integral()/h_Rares_bin_down->Integral());
	  h_Rares_bin_down->SetNameTitle(h_name+"Down",h_name+"Down");
	  h_Rares_bin_down->Write();
	  
	}
	
      }
      


    }


    cout<<"OK bin-by-bin"<<endl;*/

    
    //Fakes closure
    
    TH1F* h_TT_DL_clos_ele_diff = single_plot(filename_ttbar_DL,
					    "HTauTauTree_3l_lepMVA_CR",
					    var,
					    Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*bTagSF_CSVshape_weight*(1-0.1*recotauh_sel_isGenMatched[0])*(event_weight_ttH_ele_FR_TT_MC-event_weight_ttH_ele_FR_QCD_MC)*(category==%i && isTrig_3l_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",
					    nbin,xmin,xmax);
    
    h_TT_DL_clos_ele_diff->Scale(luminosity*XS_ttbar_DL/h_ttbar_DL_norm->Integral());

    TH1F* h_fakes_clos_ele_Up = (TH1F*)h_fakes->Clone();
    h_fakes_clos_ele_Up->Add(h_TT_DL_clos_ele_diff,+1);  
    h_fakes_clos_ele_Up->Scale(h_fakes->Integral()/h_fakes_clos_ele_Up->Integral());  
    h_fakes_clos_ele_Up->SetNameTitle("x_fakes_data_CMS_ttHt_Clos_e_shapeUp","x_fakes_data_CMS_ttHt_Clos_e_shapeUp");
    h_fakes_clos_ele_Up->Write();


    TH1F* h_fakes_clos_ele_Down = (TH1F*)h_fakes->Clone();
    h_fakes_clos_ele_Down->Add(h_TT_DL_clos_ele_diff,-1);  
    h_fakes_clos_ele_Down->Scale(h_fakes->Integral()/h_fakes_clos_ele_Up->Integral());  
    h_fakes_clos_ele_Down->SetNameTitle("x_fakes_data_CMS_ttHt_Clos_e_shapeDown","x_fakes_data_CMS_ttHt_Clos_e_shapeDown");
    h_fakes_clos_ele_Down->Write();


   TH1F* h_TT_DL_clos_mu_diff = single_plot(filename_ttbar_DL,
					    "HTauTauTree_3l_lepMVA_CR",
					    var,
					    Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*bTagSF_CSVshape_weight*(1-0.1*recotauh_sel_isGenMatched[0])*(event_weight_ttH_mu_FR_TT_MC-event_weight_ttH_mu_FR_QCD_MC)*(category==%i && isTrig_3l_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",
					    nbin,xmin,xmax);
    
    h_TT_DL_clos_mu_diff->Scale(luminosity*XS_ttbar_DL/h_ttbar_DL_norm->Integral());

    TH1F* h_fakes_clos_mu_Up = (TH1F*)h_fakes->Clone();
    h_fakes_clos_mu_Up->Add(h_TT_DL_clos_mu_diff,+1);  
    h_fakes_clos_mu_Up->Scale(h_fakes->Integral()/h_fakes_clos_mu_Up->Integral());  
    h_fakes_clos_mu_Up->SetNameTitle("x_fakes_data_CMS_ttHt_Clos_m_shapeUp","x_fakes_data_CMS_ttHt_Clos_m_shapeUp");
    h_fakes_clos_mu_Up->Write();


    TH1F* h_fakes_clos_mu_Down = (TH1F*)h_fakes->Clone();
    h_fakes_clos_mu_Down->Add(h_TT_DL_clos_mu_diff,-1);  
    h_fakes_clos_mu_Down->Scale(h_fakes->Integral()/h_fakes_clos_mu_Up->Integral());  
    h_fakes_clos_mu_Down->SetNameTitle("x_fakes_data_CMS_ttHt_Clos_m_shapeDown","x_fakes_data_CMS_ttHt_Clos_m_shapeDown");
    h_fakes_clos_mu_Down->Write();


    cout<<"OK closure syst"<<endl;
  

  }

  f_new->Close();
  return;

}









void datacard_maker_MVA_3l_syst(){

  TString var="1*(MVA_3l_ttbar>-1 && MVA_3l_ttbar<=-0.3 && MVA_3l_ttV_v2>-1. && MVA_3l_ttV_v2<=1) + 2*(MVA_3l_ttbar>-0.3 && MVA_3l_ttbar<=0.3 && MVA_3l_ttV_v2>-1. && MVA_3l_ttV_v2<=0.25) + 3*(MVA_3l_ttbar>-0.3 && MVA_3l_ttbar<=0.3 && MVA_3l_ttV_v2>0.25 && MVA_3l_ttV_v2<=1.) + 4*(MVA_3l_ttbar>0.3 && MVA_3l_ttbar<=1. && MVA_3l_ttV_v2>-1. && MVA_3l_ttV_v2<=0.25) + 5*(MVA_3l_ttbar>0.3 && MVA_3l_ttbar<=1. && MVA_3l_ttV_v2>0.25 && MVA_3l_ttV_v2<=1.)";

  
  int nbin = 5;
  float xmin = 0.5;
  float xmax = 5.5;

  TString cut = "1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_MVA_3l_syst_nofaketau_36.8fb_012017.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file,true);


}







void datacard_maker_n_fakelep_3l1tau(){

  TString var="n_recolep_fakeable";

  
  int nbin = 5;
  float xmin = 2.;
  float xmax = 7.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_fakelep_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}



void datacard_maker_n_fakeele_3l1tau(){

  TString var="n_recoele_fakeable";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 5.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_fakeele_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}



void datacard_maker_n_fakemu_3l1tau(){

  TString var="n_recomu_fakeable";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 5.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_fakemu_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}





void datacard_maker_n_faketau_3l1tau(){

  TString var="n_recotauh";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 5.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_faketau_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}



void datacard_maker_n_jet_3l1tau(){

  TString var="n_recoPFJet";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 10.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_jet_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}





void datacard_maker_n_jet_CSVloose_3l1tau(){

  TString var="n_recoPFJet_btag_loose";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 5.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_jet_CSVloose_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}





void datacard_maker_n_jet_CSVmedium_3l1tau(){

  TString var="n_recoPFJet_btag_medium";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 5.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_n_jet_CSVmedium_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}




void datacard_maker_ETmiss_3l1tau(){

  TString var="PFMET";

  
  int nbin = 12;
  float xmin = 0.;
  float xmax = 300.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_ETmiss_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}






void datacard_maker_pT_lep1_3l1tau(){

  TString var="recolep_pt[0]";

  
  int nbin = 12;
  float xmin = 0.;
  float xmax = 240.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_lep1_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}




void datacard_maker_pT_lep2_3l1tau(){

  TString var="recolep_pt[1]";

  
  int nbin = 15;
  float xmin = 0.;
  float xmax = 150.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_lep2_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}




void datacard_maker_pT_lep3_3l1tau(){

  TString var="recolep_pt[2]";

  
  int nbin = 8;
  float xmin = 0.;
  float xmax = 80.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_lep3_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}



void datacard_maker_pT_tau_3l1tau(){

  TString var="recotauh_pt[0]";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 100.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_tau_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}



void datacard_maker_pT_jet1_3l1tau(){

  TString var="recoPFJet_pt[0]";

  int nbin = 7;
  float xmin = 0.;
  float xmax = 350.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_jet1_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}


void datacard_maker_pT_jet2_3l1tau(){

  TString var="recoPFJet_pt[1]";
  
  int nbin = 4;
  float xmin = 0.;
  float xmax = 200.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_jet2_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}





void datacard_maker_pT_bjet1_3l1tau(){

  TString var="recoPFJet_CSVsort_pt[0]";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 250.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_bjet1_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}


void datacard_maker_pT_bjet2_3l1tau(){

  TString var="recoPFJet_CSVsort_pt[1]";

  
  int nbin = 5;
  float xmin = 0.;
  float xmax = 250.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_pT_bjet2_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}





void datacard_maker_CSV_jet1_3l1tau(){

  TString var="recoPFJet_CSVscore[0]";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_CSV_jet1_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}


void datacard_maker_CSV_jet2_3l1tau(){

  TString var="recoPFJet_CSVscore[1]";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;

  TString cut="1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/datacards/datacard_CSV_jet2_3l1tau_syst_36.8fb_122016.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file);


}








void datacard_maker_all(){
  
  datacard_maker_MVA_3l_syst();
  datacard_maker_n_fakelep_3l1tau();
  datacard_maker_n_fakeele_3l1tau();
  datacard_maker_n_fakemu_3l1tau();
  datacard_maker_n_faketau_3l1tau();
  datacard_maker_n_jet_3l1tau();
  datacard_maker_n_jet_CSVloose_3l1tau();
  datacard_maker_n_jet_CSVmedium_3l1tau();
  datacard_maker_ETmiss_3l1tau();
  datacard_maker_pT_lep1_3l1tau();
  datacard_maker_pT_lep2_3l1tau();
  datacard_maker_pT_lep3_3l1tau();
  datacard_maker_pT_tau_3l1tau();
  datacard_maker_pT_jet1_3l1tau();
  datacard_maker_pT_jet2_3l1tau();
  datacard_maker_CSV_jet1_3l1tau();
  datacard_maker_CSV_jet2_3l1tau();
  datacard_maker_pT_bjet1_3l1tau();
  datacard_maker_pT_bjet2_3l1tau();

}


