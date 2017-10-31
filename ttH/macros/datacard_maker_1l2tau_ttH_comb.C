#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>
#include <TF1.h>

#include "Helpers.C"

//float luminosity = 36814; //35.914 fb-1
float luminosity = 35867; //35.867 fb-1

float XS_ttH = 0.2151;
float XS_tHq = 0.07096*0.324;
float XS_tHW = 0.01561;
float XS_ttW = 0.2043;
//float XS_ttZ = 0.2529;
float XS_ttZ = 0.2731;
float XS_ttZ_lowmass = 0.0493;
float XS_ttG = 3.697;
float XS_WpWp = 0.03711;
float XS_WZ = 4.43;
float XS_ZZ = 1.256;
float XS_ZZZ = 0.01398;
float XS_WZZ = 0.05565;
float XS_WWZ = 0.1651;
float XS_WWW = 0.2086;
float XS_ttWW = 0.011500*0.2002;

float XS_tZq = 0.0758;
float XS_TTTT = 0.009103;
float XS_ttbar_DL = 87.3;
float XS_ttbar_SLfromT = 182;
float XS_ttbar_SLfromTbar = 182;

vector<float> XS;

//MC

TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_ttHJet_Hnonbb_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_tHq = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_THQ_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_tHW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_THW_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";


TString filename_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_*split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttZ_lowmass = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_lowmass_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttG = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttG_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttWW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_ttWW_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

//TString filename_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_powheg_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_ZZ_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

TString filename_WWW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WWW_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WWZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WWZ_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WZZ_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ZZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_ZZZ_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_tZq = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_tZq_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_TTTT = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_TTTT_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

TString filename_WpWp = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WpWp_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

TString filename_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL*_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttbar_SLfromT = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromT_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttbar_SLfromTbar = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

TString filename_norm_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_PU_ttHJet_Hnonbb.root";
TString filename_norm_tHq = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_PU_THQ.root";
TString filename_norm_tHW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_PU_THW.root";


TString filename_norm_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttW*.root";
TString filename_norm_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttZ.root";
TString filename_norm_ttZ_lowmass = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttZ_lowmass.root";
TString filename_norm_ttG = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttG.root";
TString filename_norm_ttWW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_ttWW.root";


//TString filename_norm_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_PU_WZ.root";
TString filename_norm_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_PU_WZ_powheg.root";
TString filename_norm_ZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_PU_ZZ.root";

TString filename_norm_WWW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_WWW.root";
TString filename_norm_WWZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_WWZ.root";
TString filename_norm_WZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_WZZ.root";
TString filename_norm_ZZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_ZZZ.root";
TString filename_norm_tZq = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_tZq.root";
TString filename_norm_TTTT = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_TTTT.root";

TString filename_norm_WpWp = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_WpWp.root";

TString filename_norm_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_DL*.root";
TString filename_norm_ttbar_SLfromT = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_SLfromT.root";
TString filename_norm_ttbar_SLfromTbar = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_SLfromTbar.root";

vector<TString> filename_MC;
vector<TString> filename_norm_MC;




//Data


TString filename_SingleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split_BDT_1l2tau_trig_weight_new_massveto_be.root";
TString filename_SingleEle_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split_BDT_1l2tau_trig_weight_new_massveto_be.root";

TString filename_SingleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split_BDT_1l2tau_trig_weight_new_massveto_be.root";
TString filename_SingleEle_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split_BDT_1l2tau_trig_weight_new_massveto_be.root";

TString filename_SingleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split_BDT_1l2tau_trig_weight_new_massveto_be.root";
TString filename_SingleEle_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split_BDT_1l2tau_trig_weight_new_massveto_be.root";

TString filename_SingleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016E_split_BDT_1l2tau_trig_weight_new_massveto_be.root";
TString filename_SingleEle_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016E_split_BDT_1l2tau_trig_weight_new_massveto_be.root";

TString filename_SingleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016F_split_BDT_1l2tau_trig_weight_new_massveto_be.root";
TString filename_SingleEle_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016F_split_BDT_1l2tau_trig_weight_new_massveto_be.root";

TString filename_SingleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016G_split_BDT_1l2tau_trig_weight_new_massveto_be.root";
TString filename_SingleEle_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016G_split_BDT_1l2tau_trig_weight_new_massveto_be.root";

TString filename_SingleMu_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv2_split_BDT_1l2tau_trig_weight_new_massveto_be.root";
TString filename_SingleEle_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv2_split_BDT_1l2tau_trig_weight_new_massveto_be.root";

TString filename_SingleMu_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016Hv3_split_BDT_1l2tau_trig_weight_new_massveto_be.root";
TString filename_SingleEle_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016Hv3_split_BDT_1l2tau_trig_weight_new_massveto_be.root";



vector<TString> filename_data;


vector<TString> MC_sample_name;
vector<TString> MC_sample_cut;


vector<TString> filename_MC_thu_unc;
vector<TString> MC_sample_name_thu_unc;
vector<TString> MC_sample_cut_thu_unc;



// MC JEC + TES

TString filename_ttH_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttH/HTauTauTree_ttHJet_Hnonbb_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttH_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttH/HTauTauTree_ttHJet_Hnonbb_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttH_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttH/HTauTauTree_ttHJet_Hnonbb_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttH_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttH/HTauTauTree_ttHJet_Hnonbb_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";


TString filename_tHq_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttH/HTauTauTree_THQ_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_leptauSF3.root";
TString filename_tHq_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttH/HTauTauTree_THQ_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_leptauSF3.root";
TString filename_tHq_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttH/HTauTauTree_THQ_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_leptauSF3.root";
TString filename_tHq_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttH/HTauTauTree_THQ_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_leptauSF3.root";

TString filename_tHW_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttH/HTauTauTree_THW_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_leptauSF3.root";
TString filename_tHW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttH/HTauTauTree_THW_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_leptauSF3.root";
TString filename_tHW_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttH/HTauTauTree_THW_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_leptauSF3.root";
TString filename_tHW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttH/HTauTauTree_THW_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_leptauSF3.root";


TString filename_ttZ_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttV/HTauTauTree_ttZ_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttV/HTauTauTree_ttZ_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttZ_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttV/HTauTauTree_ttZ_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttV/HTauTauTree_ttZ_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

TString filename_ttZ_lowmass_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttV/HTauTauTree_ttZ_lowmass_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttZ_lowmass_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttV/HTauTauTree_ttZ_lowmass_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttZ_lowmass_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttV/HTauTauTree_ttZ_lowmass_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttZ_lowmass_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttV/HTauTauTree_ttZ_lowmass_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

TString filename_ttG_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttV/HTauTauTree_ttG_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttG_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttV/HTauTauTree_ttG_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttG_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttV/HTauTauTree_ttG_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttG_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttV/HTauTauTree_ttG_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

TString filename_ttW_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttV/HTauTauTree_ttW_*split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/ttV/HTauTauTree_ttW_*split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttW_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/ttV/HTauTauTree_ttW_*split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/ttV/HTauTauTree_ttW_*split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

TString filename_ttWW_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_ttWW_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttWW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_ttWW_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttWW_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_ttWW_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ttWW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_ttWW_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";


/*TString filename_WZ_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/EWK/HTauTauTree_WZ_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/EWK/HTauTauTree_WZ_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WZ_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/EWK/HTauTauTree_WZ_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/EWK/HTauTauTree_WZ_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";*/
TString filename_WZ_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/EWK/HTauTauTree_WZ_powheg_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/EWK/HTauTauTree_WZ_powheg_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WZ_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/EWK/HTauTauTree_WZ_powheg_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/EWK/HTauTauTree_WZ_powheg_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

TString filename_ZZ_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/EWK/HTauTauTree_ZZ_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ZZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/EWK/HTauTauTree_ZZ_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ZZ_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/EWK/HTauTauTree_ZZ_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ZZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/EWK/HTauTauTree_ZZ_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";


TString filename_WWW_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_WWW_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WWW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_WWW_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WWW_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_WWW_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WWW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_WWW_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

TString filename_WWZ_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_WWZ_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WWZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_WWZ_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WWZ_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_WWZ_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WWZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_WWZ_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

TString filename_WZZ_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_WZZ_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WZZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_WZZ_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WZZ_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_WZZ_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WZZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_WZZ_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";

TString filename_ZZZ_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_ZZZ_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ZZZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_ZZZ_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ZZZ_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_ZZZ_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_ZZZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_ZZZ_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";


TString filename_tZq_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_tZq_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_tZq_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_tZq_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_tZq_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_tZq_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_tZq_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_tZq_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";


TString filename_TTTT_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_TTTT_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_TTTT_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_TTTT_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_TTTT_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_TTTT_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_TTTT_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_TTTT_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";


TString filename_WpWp_JECup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/Rares/HTauTauTree_WpWp_split_JECup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WpWp_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECdown/Rares/HTauTauTree_WpWp_split_JECdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WpWp_TESup   = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESup/Rares/HTauTauTree_WpWp_split_TESup_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";
TString filename_WpWp_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/TESdown/Rares/HTauTauTree_WpWp_split_TESdown_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root";


vector<TString> filename_MC_JECup;
vector<TString> filename_MC_JECdown;
vector<TString> filename_MC_TESup;
vector<TString> filename_MC_TESdown;



// Systematics
vector<TString> bTag_syst_names;
vector<TString> jetToTau_FR_syst_names;


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
  jetToTau_FR_syst_names.clear();

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH");
  MC_sample_cut.push_back("isGenMatched && n_genZ!=1");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  /*XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_fake");
  MC_sample_cut.push_back("!isGenMatched");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);*/

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_htt");
  MC_sample_cut.push_back("genH_decayMode[1]<=5 && isGenMatched");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hww");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genW==4 && isGenMatched");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hzz");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genZ==2 && isGenMatched");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttW);
  filename_MC.push_back(filename_ttW);
  filename_norm_MC.push_back(filename_norm_ttW);
  MC_sample_name.push_back("TTW");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_ttW_JECup);
  filename_MC_JECdown.push_back(filename_ttW_JECdown);
  filename_MC_TESup.push_back(filename_ttW_TESup);
  filename_MC_TESdown.push_back(filename_ttW_TESdown);

  XS.push_back(XS_ttZ);
  filename_MC.push_back(filename_ttZ);
  filename_norm_MC.push_back(filename_norm_ttZ);
  MC_sample_name.push_back("TTZ");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_ttZ_JECup);
  filename_MC_JECdown.push_back(filename_ttZ_JECdown);
  filename_MC_TESup.push_back(filename_ttZ_TESup);
  filename_MC_TESdown.push_back(filename_ttZ_TESdown);

  /*XS.push_back(XS_ttG);
  filename_MC.push_back(filename_ttG);
  filename_norm_MC.push_back(filename_norm_ttG);
  MC_sample_name.push_back("ttG");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_ttG_JECup);
  filename_MC_JECdown.push_back(filename_ttG_JECdown);
  filename_MC_TESup.push_back(filename_ttG_TESup);
  filename_MC_TESdown.push_back(filename_ttG_TESdown); */

  XS.push_back(XS_ttG);
  filename_MC.push_back(filename_ttG);
  filename_norm_MC.push_back(filename_norm_ttG);
  MC_sample_name.push_back("Convs");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recotauh_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttG_JECup);
  filename_MC_JECdown.push_back(filename_ttG_JECdown);
  filename_MC_TESup.push_back(filename_ttG_TESup);
  filename_MC_TESdown.push_back(filename_ttG_TESdown);

  XS.push_back(XS_WZ);
  filename_MC.push_back(filename_WZ);
  filename_norm_MC.push_back(filename_norm_WZ);
  MC_sample_name.push_back("WZ");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_WZ_JECup);
  filename_MC_JECdown.push_back(filename_WZ_JECdown);
  filename_MC_TESup.push_back(filename_WZ_TESup);
  filename_MC_TESdown.push_back(filename_WZ_TESdown);

  XS.push_back(XS_ZZ);
  filename_MC.push_back(filename_ZZ);
  filename_norm_MC.push_back(filename_norm_ZZ);
  MC_sample_name.push_back("ZZ");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_ZZ_JECup);
  filename_MC_JECdown.push_back(filename_ZZ_JECdown);
  filename_MC_TESup.push_back(filename_ZZ_TESup);
  filename_MC_TESdown.push_back(filename_ZZ_TESdown);


  XS.push_back(XS_WWW);
  filename_MC.push_back(filename_WWW);
  filename_norm_MC.push_back(filename_norm_WWW);
  MC_sample_name.push_back("WWW");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_WWW_JECup);
  filename_MC_JECdown.push_back(filename_WWW_JECdown);
  filename_MC_TESup.push_back(filename_WWW_TESup);
  filename_MC_TESdown.push_back(filename_WWW_TESdown);

  XS.push_back(XS_WWZ);
  filename_MC.push_back(filename_WWZ);
  filename_norm_MC.push_back(filename_norm_WWZ);
  MC_sample_name.push_back("WWZ");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_WWZ_JECup);
  filename_MC_JECdown.push_back(filename_WWZ_JECdown);
  filename_MC_TESup.push_back(filename_WWZ_TESup);
  filename_MC_TESdown.push_back(filename_WWZ_TESdown);

  XS.push_back(XS_WZZ);
  filename_MC.push_back(filename_WZZ);
  filename_norm_MC.push_back(filename_norm_WZZ);
  MC_sample_name.push_back("WZZ");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_WZZ_JECup);
  filename_MC_JECdown.push_back(filename_WZZ_JECdown);
  filename_MC_TESup.push_back(filename_WZZ_TESup);
  filename_MC_TESdown.push_back(filename_WZZ_TESdown);

  XS.push_back(XS_ZZZ);
  filename_MC.push_back(filename_ZZZ);
  filename_norm_MC.push_back(filename_norm_ZZZ);
  MC_sample_name.push_back("ZZZ");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_ZZZ_JECup);
  filename_MC_JECdown.push_back(filename_ZZZ_JECdown);
  filename_MC_TESup.push_back(filename_ZZZ_TESup);
  filename_MC_TESdown.push_back(filename_ZZZ_TESdown);

  XS.push_back(XS_tZq);
  filename_MC.push_back(filename_tZq);
  filename_norm_MC.push_back(filename_norm_tZq);
  MC_sample_name.push_back("tZq");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_tZq_JECup);
  filename_MC_JECdown.push_back(filename_tZq_JECdown);
  filename_MC_TESup.push_back(filename_tZq_TESup);
  filename_MC_TESdown.push_back(filename_tZq_TESdown);

  XS.push_back(XS_TTTT);
  filename_MC.push_back(filename_TTTT);
  filename_norm_MC.push_back(filename_norm_TTTT);
  MC_sample_name.push_back("TTTT");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_TTTT_JECup);
  filename_MC_JECdown.push_back(filename_TTTT_JECdown);
  filename_MC_TESup.push_back(filename_TTTT_TESup);
  filename_MC_TESdown.push_back(filename_TTTT_TESdown);

  XS.push_back(XS_WpWp);
  filename_MC.push_back(filename_WpWp);
  filename_norm_MC.push_back(filename_norm_WpWp);
  MC_sample_name.push_back("WWss");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_WpWp_JECup);
  filename_MC_JECdown.push_back(filename_WpWp_JECdown);
  filename_MC_TESup.push_back(filename_WpWp_TESup);
  filename_MC_TESdown.push_back(filename_WpWp_TESdown);


  XS.push_back(XS_tHq);
  filename_MC.push_back(filename_tHq);
  filename_norm_MC.push_back(filename_norm_tHq);
  MC_sample_name.push_back("tHq");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_tHq_JECup);
  filename_MC_JECdown.push_back(filename_tHq_JECdown);
  filename_MC_TESup.push_back(filename_tHq_TESup);
  filename_MC_TESdown.push_back(filename_tHq_TESdown);

  XS.push_back(XS_tHW);
  filename_MC.push_back(filename_tHW);
  filename_norm_MC.push_back(filename_norm_tHW);
  MC_sample_name.push_back("tHW");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_tHW_JECup);
  filename_MC_JECdown.push_back(filename_tHW_JECdown);
  filename_MC_TESup.push_back(filename_tHW_TESup);
  filename_MC_TESdown.push_back(filename_tHW_TESdown);

  XS.push_back(XS_ttWW);
  filename_MC.push_back(filename_ttWW);
  filename_norm_MC.push_back(filename_norm_ttWW);
  MC_sample_name.push_back("TTWW");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_ttWW_JECup);
  filename_MC_JECdown.push_back(filename_ttWW_JECdown);
  filename_MC_TESup.push_back(filename_ttWW_TESup);
  filename_MC_TESdown.push_back(filename_ttWW_TESdown);


  XS.push_back(XS_ttbar_DL);
  filename_MC.push_back(filename_ttbar_DL);
  filename_norm_MC.push_back(filename_norm_ttbar_DL);
  MC_sample_name.push_back("ttbar_DL");
  MC_sample_cut.push_back("1");

  XS.push_back(XS_ttbar_SLfromT);
  filename_MC.push_back(filename_ttbar_SLfromT);
  filename_norm_MC.push_back(filename_norm_ttbar_SLfromT);
  MC_sample_name.push_back("ttbar_SL_fromT");
  MC_sample_cut.push_back("1");

  XS.push_back(XS_ttbar_SLfromTbar);
  filename_MC.push_back(filename_ttbar_SLfromTbar);
  filename_norm_MC.push_back(filename_norm_ttbar_SLfromTbar);
  MC_sample_name.push_back("ttbar_SL_fromTbar");
  MC_sample_cut.push_back("1");



  filename_data.push_back(filename_SingleMu_2016B);
  filename_data.push_back(filename_SingleEle_2016B);
  filename_data.push_back(filename_SingleMu_2016C);
  filename_data.push_back(filename_SingleEle_2016C);
  filename_data.push_back(filename_SingleMu_2016D);
  filename_data.push_back(filename_SingleEle_2016D);
  filename_data.push_back(filename_SingleMu_2016E);
  filename_data.push_back(filename_SingleEle_2016E);
  filename_data.push_back(filename_SingleMu_2016F);
  filename_data.push_back(filename_SingleEle_2016F);
  filename_data.push_back(filename_SingleMu_2016G);
  filename_data.push_back(filename_SingleEle_2016G);
  filename_data.push_back(filename_SingleMu_2016Hv2);
  filename_data.push_back(filename_SingleEle_2016Hv2);
  filename_data.push_back(filename_SingleMu_2016Hv3);
  filename_data.push_back(filename_SingleEle_2016Hv3);

  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH");
  MC_sample_cut_thu_unc.push_back("isGenMatched");

  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_htt");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]<=5 && isGenMatched");

  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hww");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genW==4 && isGenMatched");

  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hzz");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genZ==2 && isGenMatched");
  
  filename_MC_thu_unc.push_back(filename_ttW);
  MC_sample_name_thu_unc.push_back("TTW");
  MC_sample_cut_thu_unc.push_back("isGenMatched");

  filename_MC_thu_unc.push_back(filename_ttZ);
  MC_sample_name_thu_unc.push_back("TTZ");
  MC_sample_cut_thu_unc.push_back("isGenMatched");

  /*filename_MC_thu_unc.push_back(filename_ttG);
  MC_sample_name_thu_unc.push_back("ttG");
  MC_sample_cut_thu_unc.push_back("isGenMatched");*/

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

  jetToTau_FR_syst_names.push_back("tauNormUp");
  jetToTau_FR_syst_names.push_back("tauNormDown");
  jetToTau_FR_syst_names.push_back("tauShapeUp");
  jetToTau_FR_syst_names.push_back("tauShapeDown");

}





void datacard_maker(TString var1, int nbin, float xmin, float xmax, double* x,
		    TString cut_cat1, TString file, bool syst=false){

  TString cut_cat = "recotauh_sel_pt[0]>30 && abs(recolep_sel_eta[0])<2.1 && !low_mass_lep && "+cut_cat1;

  TString var = var1 + "*(" + var1 + Form("<=%f) + %f*(",xmax,0.999*xmax) + var1 + Form(">%f)",xmax);
  cout<<var<<endl;


  initialize();


  
  vector<TString> cat_names;
  cat_names.push_back("ttH_1l_2tau");

  vector<int> cat;
  cat.push_back(20);

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

      TString MC_weight = "MC_weight";
      if(MC_sample_name[i_MC].Contains("tHq") || MC_sample_name[i_MC].Contains("tHW"))
	MC_weight += "_tHq_SM_457";

      TH1F* h_MC_norm = single_plot(filename_norm_MC[i_MC],
				    "HTauTauTree",
				    "1",
				    MC_weight + "*PU_weight_MCSummer2016",
				    3,0,3);     

      norm_MC.push_back(h_MC_norm->Integral());

    }


    //////////////////////////////////////////
    //////////////////////////////////////////
    /////////          NOMINAL        ////////
    //////////////////////////////////////////
    //////////////////////////////////////////


    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      TString MC_weight = "MC_weight";
      if(MC_sample_name[i_MC].Contains("tHq") || MC_sample_name[i_MC].Contains("tHW"))
	MC_weight += "_tHq_SM_457";


      TH1F* h_MC = single_plot(filename_MC[i_MC],
			       "HTauTauTree_1l_2tau",
			       var,
			       MC_weight + Form("*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*bTagSF_CSVshape_weight_v2*tauSF_weight_v3*(category==%i && isTrig_1l_v2 &&",cat[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat + ")",
			       nbin,x);  

      h_MC->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC->SetNameTitle("x_"+MC_sample_name[i_MC],"x_"+MC_sample_name[i_MC]);
      makeBinContentsPositive(h_MC,true);
      h_MC->Write();

      h_MC->SetNameTitle("x_"+MC_sample_name[i_MC]+"_gentau","x_"+MC_sample_name[i_MC]+"_gentau");
      h_MC->Write();

      TH1F* h_MC_genmatch = single_plot(filename_MC[i_MC],
					"HTauTauTree_1l_2tau_fake_CR",
					var,
					MC_weight + Form("*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*bTagSF_CSVshape_weight_v2*tauSF_weight_v3*event_weight_ttH_v2*(category==%i && isTrig_1l_v2 && isGenMatched &&",cat_fakes[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat + ")",
					nbin,x);

      h_MC_genmatch->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_genmatch->SetNameTitle("x_"+MC_sample_name[i_MC]+"_genmatch_fake_CR","x_"+MC_sample_name[i_MC]+"_genmatch_fake_CR");
      h_MC_genmatch->Write();


    }


    vector<TString> bkg_type;
    bkg_type.push_back("");
    bkg_type.push_back("_gentau");
    bkg_type.push_back("_genmatch_fake_CR");


    for(unsigned int i=0;i<bkg_type.size();i++){
     
      TH1F* h_TTH = (TH1F*)f_new->Get("x_ttH"+bkg_type[i]);
      h_TTH->Add( (TH1F*)f_new->Get("x_tHq"+bkg_type[i]) );
      h_TTH->Add( (TH1F*)f_new->Get("x_tHW"+bkg_type[i]) );
      h_TTH->SetNameTitle("x_TTH"+bkg_type[i],"x_TTH"+bkg_type[i]);
      h_TTH->Write();
      
      /*TH1F* h_TTZ = (TH1F*)f_new->Get("x_ttZ"+bkg_type[i]);
     h_TTZ->Add( (TH1F*)f_new->Get("x_ttG"+bkg_type[i]) );
     h_TTZ->SetNameTitle("x_TTZ"+bkg_type[i],"x_TTZ"+bkg_type[i]);
     h_TTZ->Write();*/
     
     TH1F* h_EWK = (TH1F*)f_new->Get("x_WZ"+bkg_type[i]);
     h_EWK->Add( (TH1F*)f_new->Get("x_ZZ"+bkg_type[i]) );
     h_EWK->SetNameTitle("x_EWK"+bkg_type[i],"x_EWK"+bkg_type[i]);
     h_EWK->Write();

     TH1F* h_Rares = (TH1F*)f_new->Get("x_WWW"+bkg_type[i]);
     h_Rares->Add( (TH1F*)f_new->Get("x_WWZ"+bkg_type[i]) );
     h_Rares->Add( (TH1F*)f_new->Get("x_WZZ"+bkg_type[i]) );
     h_Rares->Add( (TH1F*)f_new->Get("x_ZZZ"+bkg_type[i]) );
     h_Rares->Add( (TH1F*)f_new->Get("x_WWss"+bkg_type[i]) );
     h_Rares->Add( (TH1F*)f_new->Get("x_tZq"+bkg_type[i]) );
     h_Rares->Add( (TH1F*)f_new->Get("x_TTTT"+bkg_type[i]) );
     //h_Rares->Add( (TH1F*)f_new->Get("x_ttWW"+bkg_type[i]) );
     h_Rares->SetNameTitle("x_Rares"+bkg_type[i],"x_Rares"+bkg_type[i]);
     h_Rares->Write();
     
     TH1F* h_ttbar = (TH1F*)f_new->Get("x_ttbar_DL"+bkg_type[i]);
     h_ttbar->Add( (TH1F*)f_new->Get("x_ttbar_SL_fromT"+bkg_type[i]) );
     h_ttbar->Add( (TH1F*)f_new->Get("x_ttbar_SL_fromTbar"+bkg_type[i]) );
     h_ttbar->SetNameTitle("x_ttbar"+bkg_type[i],"x_ttbar"+bkg_type[i]);
     h_ttbar->Write();

   }


    bkg_type.erase(bkg_type.begin()+2);

    
    
    //Fakes
    
    TH1F* h_fakes =single_plot(filename_data,
			       "HTauTauTree_1l_2tau_fake_CR",
			       var,
			       Form("event_weight_ttH_v2*(category==%i && isTrig_1l_v2 && NBadMu==0 &&",cat_fakes[i_cat]) + cut_cat + ")",
			       nbin,x);

    h_fakes->Scale(luminosity/35867.); //Data files for 35.867 fb-1
    //h_fakes->Add( (TH1F*)f_new->Get("x_ttH_genmatch_fake_CR"), -1 );
    h_fakes->Add( (TH1F*)f_new->Get("x_TTW_genmatch_fake_CR"), -1 );
    h_fakes->Add( (TH1F*)f_new->Get("x_TTZ_genmatch_fake_CR"), -1 );
    h_fakes->Add( (TH1F*)f_new->Get("x_Convs_genmatch_fake_CR"), -1 );
    h_fakes->Add( (TH1F*)f_new->Get("x_EWK_genmatch_fake_CR"), -1 );
    h_fakes->Add( (TH1F*)f_new->Get("x_Rares_genmatch_fake_CR"), -1 );
    h_fakes->Add( (TH1F*)f_new->Get("x_TTWW_genmatch_fake_CR"), -1 );
    h_fakes->Add( (TH1F*)f_new->Get("x_tHq_genmatch_fake_CR"), -1 );
    h_fakes->Add( (TH1F*)f_new->Get("x_tHW_genmatch_fake_CR"), -1 );
    h_fakes->SetNameTitle("x_data_fakes","x_data_fakes");
    makeBinContentsPositive(h_fakes,true);
    h_fakes->Write();

    TH1F* h_fakes_unweighed =single_plot(filename_data,
					 "HTauTauTree_1l_2tau_fake_CR",
					 var,
					 Form("(category==%i && isTrig_1l_v2 && NBadMu==0 &&",cat_fakes[i_cat]) + cut_cat + ")",
					 nbin,x);

    h_fakes_unweighed->SetNameTitle("x_data_fakes_unweighed","x_data_fakes_unweighed");
    h_fakes_unweighed->Write();
    
    //Data
    
    TH1F* h_data_obs =single_plot(filename_data,
				  "HTauTauTree_1l_2tau",
				  var,
				  Form("(category==%i && isTrig_1l_v2 && NBadMu==0 && ",cat[i_cat]) + cut_cat + ")",
				  nbin,x);
      
    h_data_obs->Scale(luminosity/35867.); //Data files for 35.867 fb-1
    h_data_obs->SetNameTitle("x_data_obs","x_data_obs");
    h_data_obs->Write();

    /*TH1F* h_data_obs = (TH1F*)f_new->Get("x_ttH");
    h_data_obs->Add( (TH1F*)f_new->Get("x_TTW") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_TTZ") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_EWK") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_Rares") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_fakes_data") );
    //h_data_obs->Add( (TH1F*)f_new->Get("x_ttbar") );
    h_data_obs->SetNameTitle("x_data_obs","x_data_obs");
    h_data_obs->Write();*/


    cout<<"ok nominal"<<endl;

    if(!syst){
      f_new->Close();
      return;
    }

    //////////////////////////////////////////
    //////////////////////////////////////////
    /////////       SYSTEMATICS       ////////
    //////////////////////////////////////////
    //////////////////////////////////////////


   
    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      for(unsigned int i_b=0;i_b<bTag_syst_names.size();i_b++){       
		    
	TString MC_weight = "MC_weight";
	if(MC_sample_name[i_MC].Contains("tHq") || MC_sample_name[i_MC].Contains("tHW"))
	  MC_weight += "_tHq_SM_457";

	TString cut = MC_weight + "*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*tauSF_weight_v3*bTagSF_CSVshape_weight_" + bTag_syst_names[i_b] + "_v2";
	cut+=Form("*(category==%i && isTrig_1l_v2 &&",cat[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat + ")";

	TH1F* h_MC_btag_syst = single_plot(filename_MC[i_MC],
					   "HTauTauTree_1l_2tau",
					   var,
					   cut,
					   nbin,x);
	
	h_MC_btag_syst->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);



	for(unsigned int i_bkg=0;i_bkg<bkg_type.size();i_bkg++){

	  TString h_name = "x_"+MC_sample_name[i_MC]+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	  if(bTag_syst_names[i_b].Contains("Stats"))
	     h_name = "x_"+MC_sample_name[i_MC]+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];

	  if(bTag_syst_names[i_b]=="CFErr1Up")
	    h_name = "x_"+MC_sample_name[i_MC]+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	  else if(bTag_syst_names[i_b]=="CFErr1Down")
	    h_name = "x_"+MC_sample_name[i_MC]+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	  else if(bTag_syst_names[i_b]=="CFErr2Up")
	    h_name = "x_"+MC_sample_name[i_MC]+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	  else if(bTag_syst_names[i_b]=="CFErr2Down")
	    h_name = "x_"+MC_sample_name[i_MC]+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	  
	  h_MC_btag_syst->SetNameTitle(h_name,h_name);
	  makeBinContentsPositive(h_MC_btag_syst);
	  h_MC_btag_syst->Write();

	}

      }

    }


    for(unsigned int i_b=0;i_b<bTag_syst_names.size();i_b++){     


      for(unsigned int i_bkg=0;i_bkg<bkg_type.size();i_bkg++){
  
	TString h_name_ttH = "x_ttH"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	   h_name_ttH = "x_ttH"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_ttH = "x_ttH"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_ttH = "x_ttH"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_ttH = "x_ttH"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_ttH = "x_ttH"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	TString h_name_tHq = "x_tHq"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_tHq = "x_tHq"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_tHq = "x_tHq"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_tHq = "x_tHq"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_tHq = "x_tHq"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_tHq = "x_tHq"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	TString h_name_tHW = "x_tHW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_tHW = "x_tHW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_tHW = "x_tHW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_tHW = "x_tHW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_tHW = "x_tHW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_tHW = "x_tHW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	TString h_name_TTH = "x_TTH"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_TTH = "x_TTH"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_TTH = "x_TTH"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_TTH = "x_TTH"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_TTH = "x_TTH"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_TTH = "x_TTH"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";        
      
	TH1F* h_TTH = (TH1F*)f_new->Get(h_name_ttH);
	h_TTH->Add( (TH1F*)f_new->Get(h_name_tHq) );
	h_TTH->Add( (TH1F*)f_new->Get(h_name_tHW) );
	h_TTH->SetNameTitle(h_name_TTH,h_name_TTH);
	h_TTH->Write();
	
	TString h_name_WZ = "x_WZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_WZ = "x_WZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_WZ = "x_WZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_WZ = "x_WZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_WZ = "x_WZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_WZ = "x_WZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	TString h_name_ZZ = "x_ZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_ZZ = "x_ZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_ZZ = "x_ZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_ZZ = "x_ZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_ZZ = "x_ZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_ZZ = "x_ZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	TString h_name_EWK = "x_EWK"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_EWK = "x_EWK"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_EWK = "x_EWK"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_EWK = "x_EWK"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_EWK = "x_EWK"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_EWK = "x_EWK"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";      
	
	TH1F* h_EWK = (TH1F*)f_new->Get(h_name_WZ);
	h_EWK->Add( (TH1F*)f_new->Get(h_name_ZZ) );
	h_EWK->SetNameTitle(h_name_EWK,h_name_EWK);
	h_EWK->Write();
	
	
	TString h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
      
      
	TString h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	TString h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	
	TString h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	TString h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";

	TString h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	TString h_name_TTTT = "x_TTTT"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_TTTT = "x_TTTT"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_TTTT = "x_TTTT"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_TTTT = "x_TTTT"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_TTTT = "x_TTTT"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_TTTT = "x_TTTT"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	
	TString h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	
	TH1F* h_Rares = (TH1F*)f_new->Get(h_name_WWW);
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WZZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_ZZZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_tZq) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_TTTT) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWss) );
	//h_Rares->Add( (TH1F*)f_new->Get(h_name_ttWW) );
	h_Rares->SetNameTitle(h_name_Rares,h_name_Rares);
	h_Rares->Write();
	
      }

    }

    cout<<"OK syst btag"<<endl;



    for(unsigned i_MC=0;i_MC<MC_sample_name_thu_unc.size();i_MC++){

      TString syst_name="CMS_ttHl_thu_shape_";
      if(MC_sample_name_thu_unc[i_MC].Contains("ttH"))
	syst_name+="ttH1";
      else if(MC_sample_name_thu_unc[i_MC].Contains("TTZ"))
	syst_name+="ttZ1";
      /*else if(MC_sample_name_thu_unc[i_MC].Contains("ttG"))
	syst_name+="ttG";*/
      else if(MC_sample_name_thu_unc[i_MC].Contains("TTW"))
	syst_name+="ttW1";      

      TH1F* h_nomin = (TH1F*)f_new->Get("x_"+MC_sample_name_thu_unc[i_MC]);
      float norm = h_nomin->Integral();
		 
      TString cut = "PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*bTagSF_CSVshape_weight_v2*tauSF_weight_v3";
      cut+=Form("*(category==%i && isTrig_1l_v2 && ",cat[i_cat]) + MC_sample_cut_thu_unc[i_MC] + " && " + cut_cat + ")";

   
      TH1F* h_MC_x1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "HTauTauTree_1l_2tau",
				     var,
				     "MC_weight_scale_muR2*"+cut,
				     nbin,x);


      //h_MC_x1_up->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_x1_up->Scale(norm/h_MC_x1_up->Integral());
      h_MC_x1_up->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Up","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Up");
      makeBinContentsPositive(h_MC_x1_up);
      h_MC_x1_up->Write();
      h_MC_x1_up->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_gentau_"+syst_name+"_x1Up","x_"+MC_sample_name_thu_unc[i_MC]+"_gentau_"+syst_name+"_x1Up");
      h_MC_x1_up->Write();

      TH1F* h_MC_x1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "HTauTauTree_1l_2tau",
				       var,
				       "MC_weight_scale_muR0p5*"+cut,
				       nbin,x);
      
      //h_MC_x1_down->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_x1_down->Scale(norm/h_MC_x1_down->Integral());      
      h_MC_x1_down->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Down","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Down");
      makeBinContentsPositive(h_MC_x1_down);
      h_MC_x1_down->Write();
      h_MC_x1_down->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_gentau_"+syst_name+"_x1Down","x_"+MC_sample_name_thu_unc[i_MC]+"_gentau_"+syst_name+"_x1Down");
      h_MC_x1_down->Write();

      TH1F* h_MC_y1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "HTauTauTree_1l_2tau",
				     var,
				     "MC_weight_scale_muF2*"+cut,
				     nbin,x);
      
      //h_MC_y1_up->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_y1_up->Scale(norm/h_MC_y1_up->Integral());      
      h_MC_y1_up->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Up","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Up");
      makeBinContentsPositive(h_MC_y1_up);
      h_MC_y1_up->Write();
      h_MC_y1_up->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_gentau_"+syst_name+"_y1Up","x_"+MC_sample_name_thu_unc[i_MC]+"_gentau_"+syst_name+"_y1Up");
      h_MC_y1_up->Write();

      TH1F* h_MC_y1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "HTauTauTree_1l_2tau",
				       var,
				       "MC_weight_scale_muF0p5*"+cut,
				       nbin,x);
      
      //h_MC_y1_down->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_y1_down->Scale(norm/h_MC_y1_down->Integral());      
      h_MC_y1_down->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Down","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Down");
      makeBinContentsPositive(h_MC_y1_down);
      h_MC_y1_down->Write();
      h_MC_y1_down->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_gentau_"+syst_name+"_y1Down","x_"+MC_sample_name_thu_unc[i_MC]+"_gentau_"+syst_name+"_y1Down");
      h_MC_y1_down->Write();



      TH1F* ratio_x1_up = (TH1F*)h_MC_x1_up->Clone();
      ratio_x1_up->Divide(h_nomin);
      TF1* f_x1_up = new TF1("f_x1_up","pol1");
      ratio_x1_up->Fit(f_x1_up);
      double slope_x1_up = f_x1_up->GetParameter(1);

      TH1F* ratio_x1_down = (TH1F*)h_MC_x1_down->Clone();
      ratio_x1_down->Divide(h_nomin);
      TF1* f_x1_down = new TF1("f_x1_down","pol1");
      ratio_x1_down->Fit(f_x1_down);
      double slope_x1_down = f_x1_down->GetParameter(1);

      TH1F* ratio_y1_up = (TH1F*)h_MC_y1_up->Clone();
      ratio_y1_up->Divide(h_nomin);
      TF1* f_y1_up = new TF1("f_y1_up","pol1");
      ratio_y1_up->Fit(f_y1_up);
      double slope_y1_up = f_y1_up->GetParameter(1);

      TH1F* ratio_y1_down = (TH1F*)h_MC_y1_down->Clone();
      ratio_y1_down->Divide(h_nomin);
      TF1* f_y1_down = new TF1("f_y1_down","pol1");
      ratio_y1_down->Fit(f_y1_down);
      double slope_y1_down = f_y1_down->GetParameter(1);

      vector<double> slopes={slope_x1_up, slope_x1_down, slope_y1_up, slope_y1_down};
      int max_slope = distance(slopes.begin(), max_element(slopes.begin(),slopes.end()));
      int min_slope = distance(slopes.begin(), min_element(slopes.begin(),slopes.end()));

      TH1F* h_MC_thu_shapeUp; 
      if(max_slope==0)
	h_MC_thu_shapeUp = (TH1F*)h_MC_x1_up->Clone();
      else if(max_slope==1)
	h_MC_thu_shapeUp = (TH1F*)h_MC_x1_down->Clone();
      else if(max_slope==2)
	h_MC_thu_shapeUp = (TH1F*)h_MC_y1_up->Clone();
      else if(max_slope==3)
	h_MC_thu_shapeUp = (TH1F*)h_MC_y1_down->Clone();      
      h_MC_thu_shapeUp->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"Up","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"Up");
      h_MC_thu_shapeUp->Write();


      TH1F* h_MC_thu_shapeDown; 
      if(min_slope==0)
	h_MC_thu_shapeDown = (TH1F*)h_MC_x1_up->Clone();
      else if(min_slope==1)
	h_MC_thu_shapeDown = (TH1F*)h_MC_x1_down->Clone();
      else if(min_slope==2)
	h_MC_thu_shapeDown = (TH1F*)h_MC_y1_up->Clone();
      else if(min_slope==3)
	h_MC_thu_shapeDown = (TH1F*)h_MC_y1_down->Clone();      
      h_MC_thu_shapeDown->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"Down","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"Down");
      h_MC_thu_shapeDown->Write();
      
 

    }



    vector<TString> thu_uncert;
    thu_uncert.push_back("_x1Up");
    thu_uncert.push_back("_x1Down");
    thu_uncert.push_back("_y1Up");
    thu_uncert.push_back("_y1Down");
    thu_uncert.push_back("Up");
    thu_uncert.push_back("Down");
    

    for(unsigned int i=0;i<thu_uncert.size();i++){

      TString h_name_ttH = "x_ttH_CMS_ttHl_thu_shape_ttH1"+thu_uncert[i];
      TString h_name_tHq = "x_tHq"; //Just take nominal for tHq
      TString h_name_tHW = "x_tHW"; //Just take nominal for tHW
      TString h_name_TTH = "x_TTH_CMS_ttHl_thu_shape_ttH1"+thu_uncert[i];

      TH1F* h_TTH = (TH1F*)f_new->Get(h_name_ttH)->Clone();
      h_TTH->Add( (TH1F*)f_new->Get(h_name_tHq) );
      h_TTH->Add( (TH1F*)f_new->Get(h_name_tHW) );
      h_TTH->SetNameTitle(h_name_TTH,h_name_TTH);
      h_TTH->Write();

      h_name_TTH = "x_TTH_gentau_CMS_ttHl_thu_shape_ttH1"+thu_uncert[i];
      h_TTH->SetNameTitle(h_name_TTH,h_name_TTH);
      h_TTH->Write();


      /*TString h_name_ttZ = "x_ttZ_CMS_ttHl_thu_shape_ttZ_"+thu_uncert[i];
      TString h_name_ttG = "x_ttG_CMS_ttHl_thu_shape_ttG_"+thu_uncert[i];
      TString h_name_TTZ = "x_TTZ_CMS_ttHl_thu_shape_ttZ_"+thu_uncert[i];


      TH1F* h_TTZ = (TH1F*)f_new->Get(h_name_ttZ)->Clone();
      h_TTZ->Add( (TH1F*)f_new->Get(h_name_ttG) );
      h_TTZ->SetNameTitle(h_name_TTZ,h_name_TTZ);
      h_TTZ->Write();

      h_name_TTZ = "x_TTZ_gentau_CMS_ttHl_thu_shape_ttZ_"+thu_uncert[i];
      h_TTZ->SetNameTitle(h_name_TTZ,h_name_TTZ);
      h_TTZ->Write();*/


    }

    cout<<"OK syst theoretical "<<endl;


  
    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      if(MC_sample_name[i_MC].Contains("ttbar")) continue;
            
      TString MC_weight = "MC_weight";
      if(MC_sample_name[i_MC].Contains("tHq") || MC_sample_name[i_MC].Contains("tHW"))
	MC_weight += "_tHq_SM_457";

      TString cut = MC_weight + "*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*bTagSF_CSVshape_weight_v2*tauSF_weight_v3";
      cut+=Form("*(category==%i && isTrig_1l_v2 &&",cat[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat + ")";


      TH1F* h_MC_JEC_up = single_plot(filename_MC_JECup[i_MC],
				      "HTauTauTree_1l_2tau",
				      var,
				      cut,
				      nbin,x);

      h_MC_JEC_up->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_JEC_up->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_scale_jUp","x_"+MC_sample_name[i_MC]+"_CMS_scale_jUp");
      makeBinContentsPositive(h_MC_JEC_up);
      h_MC_JEC_up->Write();
      h_MC_JEC_up->SetNameTitle("x_"+MC_sample_name[i_MC]+"_gentau_CMS_scale_jUp","x_"+MC_sample_name[i_MC]+"_gentau_CMS_scale_jUp");
      h_MC_JEC_up->Write();

      
      TH1F* h_MC_JEC_down = single_plot(filename_MC_JECdown[i_MC],
					"HTauTauTree_1l_2tau",
					var,
					cut,
					nbin,x);

      h_MC_JEC_down->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_JEC_down->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_scale_jDown","x_"+MC_sample_name[i_MC]+"_CMS_scale_jDown");
      makeBinContentsPositive(h_MC_JEC_down);
      h_MC_JEC_down->Write();
      h_MC_JEC_down->SetNameTitle("x_"+MC_sample_name[i_MC]+"_gentau_CMS_scale_jDown","x_"+MC_sample_name[i_MC]+"_gentau_CMS_scale_jDown");
      h_MC_JEC_down->Write();

      TH1F* h_MC_TES_up = single_plot(filename_MC_TESup[i_MC],
				      "HTauTauTree_1l_2tau",
				      var,
				      cut,
				      nbin,x);
      
      h_MC_TES_up->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_TES_up->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_scale_tUp","x_"+MC_sample_name[i_MC]+"_CMS_scale_tUp");
      makeBinContentsPositive(h_MC_TES_up);
      h_MC_TES_up->Write();h_MC_TES_up->SetNameTitle("x_"+MC_sample_name[i_MC]+"_gentau_CMS_scale_tUp","x_"+MC_sample_name[i_MC]+"_gentau_CMS_scale_tUp");
      h_MC_TES_up->Write();

      
      TH1F* h_MC_TES_down = single_plot(filename_MC_TESdown[i_MC],
					"HTauTauTree_1l_2tau",
					var,
					cut,
					nbin,x);
      
      h_MC_TES_down->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_TES_down->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_scale_tDown","x_"+MC_sample_name[i_MC]+"_CMS_scale_tDown");
      makeBinContentsPositive(h_MC_TES_down);
      h_MC_TES_down->Write();
      h_MC_TES_down->SetNameTitle("x_"+MC_sample_name[i_MC]+"_gentau_CMS_scale_tDown","x_"+MC_sample_name[i_MC]+"_gentau_CMS_scale_tDown");
      h_MC_TES_down->Write();

    }

    
    vector<TString> JES_TES_uncert;
    JES_TES_uncert.push_back("jUp");
    JES_TES_uncert.push_back("jDown");
    JES_TES_uncert.push_back("tUp");
    JES_TES_uncert.push_back("tDown");


    for(unsigned int i=0;i<JES_TES_uncert.size();i++){

      for(unsigned int i_bkg=0;i_bkg<bkg_type.size();i_bkg++){

      TString h_name_ttH = "x_ttH"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      TString h_name_tHq = "x_tHq"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      TString h_name_tHW = "x_tHW"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      TString h_name_TTH = "x_TTH"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];

      TH1F* h_TTH = (TH1F*)f_new->Get(h_name_ttH)->Clone();
      h_TTH->Add( (TH1F*)f_new->Get(h_name_tHq) );
      h_TTH->Add( (TH1F*)f_new->Get(h_name_tHW) );
      h_TTH->SetNameTitle(h_name_TTH,h_name_TTH);
      h_TTH->Write();


      TString h_name_WZ = "x_WZ"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      TString h_name_ZZ = "x_ZZ"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      TString h_name_EWK = "x_EWK"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      
      TH1F* h_EWK = (TH1F*)f_new->Get(h_name_WZ)->Clone();
      h_EWK->Add( (TH1F*)f_new->Get(h_name_ZZ) );
      h_EWK->SetNameTitle(h_name_EWK,h_name_EWK);
      h_EWK->Write();
      
      TString h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      TString h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      TString h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      TString h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      TString h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      TString h_name_TTTT = "x_TTTT"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      TString h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
      TString h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];

      TH1F* h_Rares = (TH1F*)f_new->Get(h_name_WWW)->Clone();
      h_Rares->Add( (TH1F*)f_new->Get(h_name_WWZ) );
      h_Rares->Add( (TH1F*)f_new->Get(h_name_WZZ) );
      h_Rares->Add( (TH1F*)f_new->Get(h_name_ZZZ) );
      h_Rares->Add( (TH1F*)f_new->Get(h_name_tZq) );
      h_Rares->Add( (TH1F*)f_new->Get(h_name_TTTT) );
      h_Rares->Add( (TH1F*)f_new->Get(h_name_WWss) );
      h_Rares->SetNameTitle(h_name_Rares,h_name_Rares);
      h_Rares->Write();

      }

    }
    

    cout<<"OK JEC/TES "<<endl;

    
    for(unsigned int i_t=0;i_t<jetToTau_FR_syst_names.size();i_t++){       
      		    
      TString weight = "event_weight_ttH_"+ jetToTau_FR_syst_names[i_t] +"_v2";
      TString cut = weight + Form("*(category==%i && isTrig_1l_v2 && NBadMu==0 &&",cat_fakes[i_cat]) + cut_cat +")";


      TH1F* h_FRjt_syst = single_plot(filename_data,
				      "HTauTauTree_1l_2tau_fake_CR",
				      var,
				      cut,
				      nbin,x);

      h_FRjt_syst->Scale(luminosity/35867.); //Data files for 35.867 fb-1   

      for(unsigned int i_MC=0;i_MC<MC_sample_name.size();i_MC++){
	
	if(MC_sample_name[i_MC]=="ttH" || MC_sample_name[i_MC].Contains("ttbar")) continue;      	
	
	TString MC_weight = "MC_weight";
      if(MC_sample_name[i_MC].Contains("tHq") || MC_sample_name[i_MC].Contains("tHW"))
	MC_weight += "_tHq_SM_457";

        TString MC_cut = MC_weight + "*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*bTagSF_CSVshape_weight_v2*tauSF_weight_v3*"+weight+Form("*(category==%i && isTrig_1l_v2 && isGenMatched &&",cat_fakes[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat + ")";

	TH1F* h_MC_genmatch = single_plot(filename_MC[i_MC],
                                          "HTauTauTree_1l_2tau_fake_CR",
					  var,
					  MC_cut,
					  nbin,x);

        h_MC_genmatch->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
        h_FRjt_syst->Add(h_MC_genmatch,-1);
      }


      TString h_name = "x_data_fakes_CMS_ttHl16_FRjt_";
      if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
	h_name+="normUp";
      else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
	h_name+="normDown";
      else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
	h_name+="shapeUp";
      else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
	h_name+="shapeDown";

      h_FRjt_syst->SetNameTitle(h_name,h_name);
      makeBinContentsPositive(h_FRjt_syst);
      h_FRjt_syst->Write();      

    }


    cout<<"OK syst jetToTau FR"<<endl;



   for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){


     TH1F* h_MC_tauIDUp = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC])->Clone();
     h_MC_tauIDUp->Scale(1.1);
     h_MC_tauIDUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_eff_tUp", "x_"+MC_sample_name[i_MC]+"_CMS_eff_tUp");
     h_MC_tauIDUp->Write();

     TH1F* h_MC_tauIDDown = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC])->Clone();
     h_MC_tauIDDown->Scale(0.9);
     h_MC_tauIDDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_eff_tDown", "x_"+MC_sample_name[i_MC]+"_CMS_eff_tDown");
     h_MC_tauIDDown->Write();


   }


    cout<<"OK syst CMS_eff_t"<<endl;



   vector<TString> syst_type_tauID;
   syst_type_tauID.push_back("Up");
   syst_type_tauID.push_back("Down");

   for(unsigned int i_syst=0;i_syst<2;i_syst++){

     TString h_name_ttH = "x_ttH_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_tHq = "x_tHq_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_tHW = "x_tHW_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_TTH = "x_TTH_CMS_eff_t"+syst_type_tauID[i_syst];
 
     TH1F* h_TTH = (TH1F*)f_new->Get(h_name_ttH);
     h_TTH->Add( (TH1F*)f_new->Get(h_name_tHq) );
     h_TTH->Add( (TH1F*)f_new->Get(h_name_tHW) );
     h_TTH->SetNameTitle(h_name_TTH,h_name_TTH);
     h_TTH->Write();

	
     TString h_name_WZ = "x_WZ_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_ZZ = "x_ZZ_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_EWK = "x_EWK_CMS_eff_t"+syst_type_tauID[i_syst];
		
     TH1F* h_EWK = (TH1F*)f_new->Get(h_name_WZ);
     h_EWK->Add( (TH1F*)f_new->Get(h_name_ZZ) );
     h_EWK->SetNameTitle(h_name_EWK,h_name_EWK);
     h_EWK->Write();

     TString h_name_WWW = "x_WWW_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_WWZ = "x_WWZ_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_WZZ = "x_WZZ_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_ZZZ = "x_ZZZ_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_WWss = "x_WWss_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_tZq = "x_tZq_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_TTTT = "x_TTTT_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_Rares = "x_Rares_CMS_eff_t"+syst_type_tauID[i_syst];
		
     TH1F* h_Rares = (TH1F*)f_new->Get(h_name_WWW);
     h_Rares->Add( (TH1F*)f_new->Get(h_name_WWZ) );
     h_Rares->Add( (TH1F*)f_new->Get(h_name_WZZ) );
     h_Rares->Add( (TH1F*)f_new->Get(h_name_ZZZ) );
     h_Rares->Add( (TH1F*)f_new->Get(h_name_WWss) );
     h_Rares->Add( (TH1F*)f_new->Get(h_name_tZq) );	     
     h_Rares->Add( (TH1F*)f_new->Get(h_name_TTTT) );
     h_Rares->SetNameTitle(h_name_Rares,h_name_Rares);
     h_Rares->Write();

   }


    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      TString MC_weight = "MC_weight";
      if(MC_sample_name[i_MC].Contains("tHq") || MC_sample_name[i_MC].Contains("tHW"))
	MC_weight += "_tHq_SM_457";


      TString cut = MC_weight + Form("*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*bTagSF_CSVshape_weight_v2*tauSF_weight_v3*(category==%i && isTrig_1l_v2 &&",cat[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat;



      TH1F* h_MC_mu = single_plot(filename_MC[i_MC],
				  "HTauTauTree_1l_2tau",
				  var,
				  cut + " && abs(recolep_sel_pdg[0])==13)",
				  nbin,x);  

      TH1F* h_MC_ele = single_plot(filename_MC[i_MC],
				  "HTauTauTree_1l_2tau",
				  var,
				  cut + " && abs(recolep_sel_pdg[0])==11)",
				  nbin,x);  

      h_MC_mu->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_ele->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      
      TH1F* h_MC_lepEff_eltightUp = (TH1F*) h_MC_mu->Clone();
      h_MC_lepEff_eltightUp->Add(h_MC_ele,1.03);
      h_MC_lepEff_eltightUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_eltightUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_eltightUp");
      makeBinContentsPositive(h_MC_lepEff_eltightUp);
      h_MC_lepEff_eltightUp->Write();

      TH1F* h_MC_lepEff_eltightDown = (TH1F*) h_MC_mu->Clone();
      h_MC_lepEff_eltightDown->Add(h_MC_ele,0.97);
      h_MC_lepEff_eltightDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_eltightDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_eltightDown");
      makeBinContentsPositive(h_MC_lepEff_eltightDown);
      h_MC_lepEff_eltightDown->Write();


      TH1F* h_MC_lepEff_mutightUp = (TH1F*) h_MC_ele->Clone();
      h_MC_lepEff_mutightUp->Add(h_MC_mu,1.03);
      h_MC_lepEff_mutightUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mutightUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mutightUp");
      makeBinContentsPositive(h_MC_lepEff_mutightUp);
      h_MC_lepEff_mutightUp->Write();

      TH1F* h_MC_lepEff_mutightDown = (TH1F*) h_MC_ele->Clone();
      h_MC_lepEff_mutightDown->Add(h_MC_mu,0.97);
      h_MC_lepEff_mutightDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mutightDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mutightDown");
      makeBinContentsPositive(h_MC_lepEff_mutightDown);
      h_MC_lepEff_mutightDown->Write();


      TH1F* h_MC_lepEff_ellooseUp = (TH1F*) h_MC_mu->Clone();
      h_MC_lepEff_ellooseUp->Add(h_MC_ele,1.02);
      h_MC_lepEff_ellooseUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_ellooseUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_ellooseUp");
      makeBinContentsPositive(h_MC_lepEff_ellooseUp);
      h_MC_lepEff_ellooseUp->Write();

      TH1F* h_MC_lepEff_ellooseDown = (TH1F*) h_MC_mu->Clone();
      h_MC_lepEff_ellooseDown->Add(h_MC_ele,0.98);
      h_MC_lepEff_ellooseDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_ellooseDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_ellooseDown");
      makeBinContentsPositive(h_MC_lepEff_ellooseDown);
      h_MC_lepEff_ellooseDown->Write();


      TH1F* h_MC_lepEff_mulooseUp = (TH1F*) h_MC_ele->Clone();
      h_MC_lepEff_mulooseUp->Add(h_MC_mu,1.02);
      h_MC_lepEff_mulooseUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mulooseUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mulooseUp");
      makeBinContentsPositive(h_MC_lepEff_mulooseUp);
      h_MC_lepEff_mulooseUp->Write();

      TH1F* h_MC_lepEff_mulooseDown = (TH1F*) h_MC_ele->Clone();
      h_MC_lepEff_mulooseDown->Add(h_MC_mu,0.98);
      h_MC_lepEff_mulooseDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mulooseDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mulooseDown");
      makeBinContentsPositive(h_MC_lepEff_mulooseDown);
      h_MC_lepEff_mulooseDown->Write();


    }


    vector<TString> lepEff_syst;
    lepEff_syst.push_back("lepEff_eltightUp");
    lepEff_syst.push_back("lepEff_eltightDown");
    lepEff_syst.push_back("lepEff_mutightUp");
    lepEff_syst.push_back("lepEff_mutightDown");
    lepEff_syst.push_back("lepEff_ellooseUp");
    lepEff_syst.push_back("lepEff_ellooseDown");
    lepEff_syst.push_back("lepEff_mulooseUp");
    lepEff_syst.push_back("lepEff_mulooseDown");

    for(unsigned int i=0;i<lepEff_syst.size();i++){

      TString h_name_ttH = "x_ttH_CMS_ttHl16_"+lepEff_syst[i];
      TString h_name_tHq = "x_tHq_CMS_ttHl16_"+lepEff_syst[i];
      TString h_name_tHW = "x_tHW_CMS_ttHl16_"+lepEff_syst[i];
      TString h_name_TTH = "x_TTH_CMS_ttHl16_"+lepEff_syst[i];

      TH1F* h_TTH = (TH1F*)f_new->Get(h_name_ttH)->Clone();
      h_TTH->Add( (TH1F*)f_new->Get(h_name_tHq) );
      h_TTH->Add( (TH1F*)f_new->Get(h_name_tHW) );
      h_TTH->SetNameTitle(h_name_TTH,h_name_TTH);
      h_TTH->Write();
            

      TString h_name_WZ = "x_WZ_CMS_ttHl16_"+lepEff_syst[i];
      TString h_name_ZZ = "x_ZZ_CMS_ttHl16_"+lepEff_syst[i];
      TString h_name_EWK = "x_EWK_CMS_ttHl16_"+lepEff_syst[i];
      
      TH1F* h_EWK = (TH1F*)f_new->Get(h_name_WZ)->Clone();
      h_EWK->Add( (TH1F*)f_new->Get(h_name_ZZ) );
      h_EWK->SetNameTitle(h_name_EWK,h_name_EWK);
      h_EWK->Write();
      

      TString h_name_WWW = "x_WWW_CMS_ttHl16_"+lepEff_syst[i];
      TString h_name_WWZ = "x_WWZ_CMS_ttHl16_"+lepEff_syst[i];
      TString h_name_WZZ = "x_WZZ_CMS_ttHl16_"+lepEff_syst[i];
      TString h_name_ZZZ = "x_ZZZ_CMS_ttHl16_"+lepEff_syst[i];
      TString h_name_tZq = "x_tZq_CMS_ttHl16_"+lepEff_syst[i];
      TString h_name_TTTT = "x_TTTT_CMS_ttHl16_"+lepEff_syst[i];
      TString h_name_WWss = "x_WWss_CMS_ttHl16_"+lepEff_syst[i];
      TString h_name_Rares = "x_Rares_CMS_ttHl16_"+lepEff_syst[i];

      TH1F* h_Rares = (TH1F*)f_new->Get(h_name_WWW)->Clone();
      h_Rares->Add( (TH1F*)f_new->Get(h_name_WWZ) );
      h_Rares->Add( (TH1F*)f_new->Get(h_name_WZZ) );
      h_Rares->Add( (TH1F*)f_new->Get(h_name_ZZZ) );
      h_Rares->Add( (TH1F*)f_new->Get(h_name_tZq) );
      h_Rares->Add( (TH1F*)f_new->Get(h_name_TTTT) );
      h_Rares->Add( (TH1F*)f_new->Get(h_name_WWss) );
      h_Rares->SetNameTitle(h_name_Rares,h_name_Rares);
      h_Rares->Write();

    }


    cout<<"OK syst lepEff tight"<<endl;

  }







  f_new->Close();


}




void datacard_maker(TString var1, int nbin, float xmin, float xmax,
		    TString cut_cat1, TString file, bool syst=false){


  double x[nbin+1];
  for(int i=0;i<nbin+1;i++)
    x[i] = xmin + (xmax-xmin)*double(i)/nbin;
    
  datacard_maker(var1, nbin, xmin, xmax, x, cut_cat1, file, syst);


}





void datacard_maker_BDT_1l2tau_syst(){

  TString var="MVA_1l2tau_ttbar";

  
  int nbin = 5;
  float xmin = -1.;
  float xmax = 1.;

  TString cut="1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards_ttH_comb/datacard_BDT_1l2tau_syst_35.9fb_042017.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file,true);


}


