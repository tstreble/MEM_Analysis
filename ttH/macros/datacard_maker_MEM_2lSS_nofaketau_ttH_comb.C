#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>
#include <TF1.h>

#include<algorithm>

#include "Helpers.C"

//float luminosity = 36814; //35.914 fb-1
float luminosity = 35867; //35.867 fb-1

float XS_ttH = 0.2151;
float XS_tHq = 0.07096*0.324;
float XS_tHW = 0.01561;
float XS_ttW = 0.2043;
//float XS_ttZ = 0.2529;
float XS_ttZ = 0.2731;
float XS_ttZ_lowmass = 0.0283;
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
float XS_ZZJJ = 0.0004404;


vector<float> XS;

//MC


TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/ttHJet_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_tHq = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/THQ_split_2lSS_MEM_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3_BDTMEM.root";
TString filename_tHW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/THW_split_2lSS_MEM_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3_BDTMEM.root";

TString filename_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttZ_ext = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_ext_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttZ_lowmass = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_lowmass_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttG = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttG_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttWW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/ttWW_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";


//TString filename_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/WZ_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/WZ_powheg_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/ZZ_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_WWW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WWW_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WWZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WWZ_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WZZ_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ZZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/ZZZ_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WpWp = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WpWp_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_tZq = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/tZq_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_TTTT = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/TTTT_split_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";


TString filename_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_DL*_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_ttbar_SLfromT = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_ttbar_SLfromTbar = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";


TString filename_lepMVA_CR_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/ttHJet_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_tHq = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/THQ_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_MCtHq_be_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_tHW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/THW_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_MCtHq_be_leptauSF3_BDTMEM.root";

TString filename_lepMVA_CR_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttW_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_ttZ_lowmass = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_lowmass_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_ttG = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttG_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_ttWW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/ttWW_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";


//TString filename_lepMVA_CR_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/WZ_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/WZ_powheg_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_ZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/ZZ_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";

TString filename_lepMVA_CR_WWW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WWW_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_WWZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WWZ_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_WZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WZZ_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_ZZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/ZZZ_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";

TString filename_lepMVA_CR_WpWp = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WpWp_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_tZq = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/tZq_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";
TString filename_lepMVA_CR_TTTT = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/TTTT_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_leptauSF3_BDTMEM.root";


TString filename_norm_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_PU_ttHJet_Hnonbb.root";
TString filename_norm_tHq = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_PU_THQ.root";
TString filename_norm_tHW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_PU_THW.root";

TString filename_norm_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttW.root";
TString filename_norm_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttZ.root";
TString filename_norm_ttZ_lowmass = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttZ_lowmass.root";
TString filename_norm_ttZ_ext = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttZ_ext.root";
TString filename_norm_ttG = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttV/ntuple_PU_ttG.root";
TString filename_norm_ttWW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_ttWW.root";

//TString filename_norm_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_PU_WZ.root";
TString filename_norm_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_PU_WZ_powheg.root";
TString filename_norm_ZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/EWK/ntuple_PU_ZZ.root";

TString filename_norm_WWW = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_WWW.root";
TString filename_norm_WWZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_WWZ.root";
TString filename_norm_WZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_WZZ.root";
TString filename_norm_ZZZ = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_ZZZ.root";

TString filename_norm_WpWp = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_WpWp.root";
TString filename_norm_tZq = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_tZq.root";
TString filename_norm_TTTT = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/Rares/ntuple_PU_TTTT.root";

TString filename_norm_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_DL*.root";
TString filename_norm_ttbar_SLfromT = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_SLfromT.root";
TString filename_norm_ttbar_SLfromTbar = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_SLfromTbar.root";


vector<TString> filename_MC;
vector<TString> filename_lepMVA_CR_MC;
vector<TString> filename_norm_MC;




//Data

TString filename_DoubleEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016B_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_MuonEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016B_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_DoubleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016B_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleEle_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016B_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016B_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";

TString filename_DoubleEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016C_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_MuonEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016C_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_DoubleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016C_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleEle_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016C_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016C_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";

TString filename_DoubleEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016D_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_MuonEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016D_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_DoubleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016D_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleEle_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016D_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016D_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_DoubleEG_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016E_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_MuonEG_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016E_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_DoubleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016E_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleEle_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016E_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016E_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";

TString filename_DoubleEG_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016F_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_MuonEG_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016F_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_DoubleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016F_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleEle_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016F_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016F_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";

TString filename_DoubleEG_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016G_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_MuonEG_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016G_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_DoubleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016G_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleEle_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016G_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016G_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";

TString filename_DoubleEG_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016Hv2_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_MuonEG_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016Hv2_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_DoubleMu_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016Hv2_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleEle_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016Hv2_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_SingleMu_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016Hv2_split_2lSS_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";

/*TString filename_DoubleEG_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016_split_2lSS_MEM.root";
TString filename_MuonEG_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016_split_2lSS_MEM.root";
TString filename_DoubleMu_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016_split_2lSS_MEM.root";
TString filename_SingleEle_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016_split_2lSS_MEM.root";
TString filename_SingleMu_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016_split_2lSS_MEM.root";*/


TString filename_lepMVA_CR_DoubleEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_MuonEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_DoubleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleEle_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016B_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
			  
TString filename_lepMVA_CR_DoubleEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_MuonEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_DoubleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleEle_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016C_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
			  
TString filename_lepMVA_CR_DoubleEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016D_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_MuonEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016D_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_DoubleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016D_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleEle_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016D_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016D_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
			  
TString filename_lepMVA_CR_DoubleEG_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016E_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_MuonEG_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016E_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_DoubleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016E_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleEle_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016E_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016E_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
			  
TString filename_lepMVA_CR_DoubleEG_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016F_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_MuonEG_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016F_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_DoubleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016F_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleEle_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016F_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016F_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
			  
TString filename_lepMVA_CR_DoubleEG_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016G_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_MuonEG_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016G_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_DoubleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016G_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleEle_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016G_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016G_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
			  
TString filename_lepMVA_CR_DoubleEG_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016Hv2_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_MuonEG_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016Hv2_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_DoubleMu_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016Hv2_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleEle_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016Hv2_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleMu_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016Hv2_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";

TString filename_lepMVA_CR_DoubleEG_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016Hv3_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_MuonEG_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016Hv3_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_DoubleMu_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016Hv3_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleEle_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016Hv3_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_lepMVA_CR_SingleMu_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016Hv3_split_2lSS_lepMVA_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";

/*TString filename_lepMVA_CR_DoubleEG_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016_split_2lSS_lepMVA_CR_MEM.root";
TString filename_lepMVA_CR_MuonEG_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016_split_2lSS_lepMVA_CR_MEM.root";
TString filename_lepMVA_CR_DoubleMu_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016_split_2lSS_lepMVA_CR_MEM.root";
TString filename_lepMVA_CR_SingleEle_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016_split_2lSS_lepMVA_CR_MEM.root";
TString filename_lepMVA_CR_SingleMu_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016_split_2lSS_lepMVA_CR_MEM.root";*/


TString filename_2lOS_CR_DoubleEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016B_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_MuonEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016B_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_DoubleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016B_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleEle_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016B_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016B_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
		 	  
TString filename_2lOS_CR_DoubleEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016C_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_MuonEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016C_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_DoubleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016C_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleEle_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016C_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016C_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
		 	  
TString filename_2lOS_CR_DoubleEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016D_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_MuonEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016D_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_DoubleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016D_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleEle_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016D_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016D_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
		 	  
TString filename_2lOS_CR_DoubleEG_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016E_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_MuonEG_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016E_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_DoubleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016E_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleEle_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016E_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016E_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
		 	  
TString filename_2lOS_CR_DoubleEG_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016F_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_MuonEG_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016F_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_DoubleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016F_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleEle_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016F_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016F_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
		 	  
TString filename_2lOS_CR_DoubleEG_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016G_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_MuonEG_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016G_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_DoubleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016G_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleEle_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016G_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016G_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
		 	  
TString filename_2lOS_CR_DoubleEG_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016Hv2_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_MuonEG_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016Hv2_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_DoubleMu_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016Hv2_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleEle_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016Hv2_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleMu_2016Hv2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016Hv2_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";

TString filename_2lOS_CR_DoubleEG_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016Hv3_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_MuonEG_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016Hv3_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_DoubleMu_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016Hv3_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleEle_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016Hv3_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";
TString filename_2lOS_CR_SingleMu_2016Hv3 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016Hv3_split_2lOS_CR_MEM_NBadMu_trig_weight_new_be_BDTMEM.root";

/*TString filename_2lOS_CR_DoubleEG_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleEG_2016_split_2lOS_CR_MEM.root";
TString filename_2lOS_CR_MuonEG_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/MuonEG_2016_split_2lOS_CR_MEM.root";
TString filename_2lOS_CR_DoubleMu_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/DoubleMu_2016_split_2lOS_CR_MEM.root";
TString filename_2lOS_CR_SingleEle_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleEle_2016_split_2lOS_CR_MEM.root";
TString filename_2lOS_CR_SingleMu_2016 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/SingleMu_2016_split_2lOS_CR_MEM.root";*/

vector<TString> filename_data;
vector<TString> filename_data_lepMVA_CR;
vector<TString> filename_data_2lOS_CR;


vector<TString> MC_sample_name;
vector<TString> MC_sample_cut;

vector<TString> filename_MC_thu_unc;
vector<TString> MC_sample_name_thu_unc;
vector<TString> MC_sample_cut_thu_unc;


// MC JEC + TES


TString filename_ttH_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/ttH/ttHJet_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttH_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/ttH/ttHJet_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttH_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/ttH/ttHJet_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttH_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/ttH/ttHJet_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_tHq_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/ttH/THQ_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3_BDTMEM.root";
TString filename_tHq_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/ttH/THQ_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3_BDTMEM.root";
TString filename_tHq_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/ttH/THQ_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3_BDTMEM.root";
TString filename_tHq_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/ttH/THQ_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3_BDTMEM.root";

TString filename_tHW_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/ttH/THW_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3_BDTMEM.root";
TString filename_tHW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/ttH/THW_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3_BDTMEM.root";
TString filename_tHW_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/ttH/THW_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3_BDTMEM.root";
TString filename_tHW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/ttH/THW_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3_BDTMEM.root";

TString filename_ttZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/ttV/ttZ_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/ttV/ttZ_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/ttV/ttZ_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/ttV/ttZ_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_ttG_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/ttV/ttG_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttG_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/ttV/ttG_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttG_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/ttV/ttG_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttG_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/ttV/ttG_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_ttW_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/ttV/ttW_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/ttV/ttW_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttW_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/ttV/ttW_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/ttV/ttW_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_ttWW_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/Rares/ttWW_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttWW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/Rares/ttWW_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttWW_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/Rares/ttWW_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ttWW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/Rares/ttWW_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

/*TString filename_WZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/EWK/WZ_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/EWK/WZ_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/EWK/WZ_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/EWK/WZ_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";*/

TString filename_WZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/EWK/WZ_powheg_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/EWK/WZ_powheg_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/EWK/WZ_powheg_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/EWK/WZ_powheg_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_ZZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/EWK/ZZ_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ZZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/EWK/ZZ_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ZZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/EWK/ZZ_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ZZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/EWK/ZZ_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_WWW_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/Rares/WWW_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WWW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/Rares/WWW_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WWW_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/Rares/WWW_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WWW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/Rares/WWW_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_WWZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/Rares/WWZ_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WWZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/Rares/WWZ_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WWZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/Rares/WWZ_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WWZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/Rares/WWZ_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_WZZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/Rares/WZZ_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WZZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/Rares/WZZ_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WZZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/Rares/WZZ_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WZZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/Rares/WZZ_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_ZZZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/Rares/ZZZ_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ZZZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/Rares/ZZZ_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ZZZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/Rares/ZZZ_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_ZZZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/Rares/ZZZ_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_WpWp_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/Rares/WpWp_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WpWp_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/Rares/WpWp_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WpWp_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/Rares/WpWp_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_WpWp_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/Rares/WpWp_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_tZq_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/Rares/tZq_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_tZq_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/Rares/tZq_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_tZq_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/Rares/tZq_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_tZq_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/Rares/tZq_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

TString filename_TTTT_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/Rares/TTTT_split_JECup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_TTTT_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECdown/Rares/TTTT_split_JECdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_TTTT_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESup/Rares/TTTT_split_TESup_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";
TString filename_TTTT_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/TESdown/Rares/TTTT_split_TESdown_2lSS_MEM_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root";

vector<TString> filename_MC_JECup;
vector<TString> filename_MC_JECdown;
vector<TString> filename_MC_TESup;
vector<TString> filename_MC_TESdown;



// Systematics
vector<TString> bTag_syst_names;
vector<TString> jetToTau_FR_syst_names;
vector<TString> fake_syst_names;

void initialize(){

  XS.clear();
  filename_MC.clear();
  filename_lepMVA_CR_MC.clear();
  filename_norm_MC.clear();
  MC_sample_name.clear();
  MC_sample_cut.clear();
  filename_data.clear();
  filename_data_lepMVA_CR.clear();
  filename_data_2lOS_CR.clear();

  filename_MC_JECup.clear();
  filename_MC_JECdown.clear();
  filename_MC_TESup.clear();
  filename_MC_TESdown.clear();

  filename_MC_thu_unc.clear();
  MC_sample_name_thu_unc.clear();
  MC_sample_cut_thu_unc.clear();
  bTag_syst_names.clear();
  jetToTau_FR_syst_names.clear();
  fake_syst_names.clear();

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH");
  MC_sample_cut.push_back("!(n_genW==2 && n_genZ<2 && genH_decayMode[1]>5) && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && !(n_genZ<2 && n_genW==2 && genH_decayMode[1]>5) && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && !(n_genZ<2 && n_genW==2 && genH_decayMode[1]>5) && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_htt");
  MC_sample_cut.push_back("genH_decayMode[1]<=5 && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_htt_gentau");
  MC_sample_cut.push_back("genH_decayMode[1]<=5 && recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_htt_faketau");
  MC_sample_cut.push_back("genH_decayMode[1]<=5 && !recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hww");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genW==4 && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hww_gentau");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genW==4 && recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hww_faketau");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genW==4 && !recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hzz");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genZ==2 && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hzz_gentau");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genZ==2 && recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_hzz_faketau");
  MC_sample_cut.push_back("genH_decayMode[1]>5 && n_genZ==2 && !recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttW);
  filename_MC.push_back(filename_ttW);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttW);
  filename_norm_MC.push_back(filename_norm_ttW);
  MC_sample_name.push_back("TTW");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttW_JECup);
  filename_MC_JECdown.push_back(filename_ttW_JECdown);
  filename_MC_TESup.push_back(filename_ttW_TESup);
  filename_MC_TESdown.push_back(filename_ttW_TESdown);

  XS.push_back(XS_ttW);
  filename_MC.push_back(filename_ttW);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttW);
  filename_norm_MC.push_back(filename_norm_ttW);
  MC_sample_name.push_back("TTW_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttW_JECup);
  filename_MC_JECdown.push_back(filename_ttW_JECdown);
  filename_MC_TESup.push_back(filename_ttW_TESup);
  filename_MC_TESdown.push_back(filename_ttW_TESdown);

  XS.push_back(XS_ttW);
  filename_MC.push_back(filename_ttW);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttW);
  filename_norm_MC.push_back(filename_norm_ttW);
  MC_sample_name.push_back("TTW_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttW_JECup);
  filename_MC_JECdown.push_back(filename_ttW_JECdown);
  filename_MC_TESup.push_back(filename_ttW_TESup);
  filename_MC_TESdown.push_back(filename_ttW_TESdown);

  XS.push_back(XS_ttZ);
  filename_MC.push_back(filename_ttZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttZ);
  filename_norm_MC.push_back(filename_norm_ttZ);
  MC_sample_name.push_back("TTZ");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttZ_JECup);
  filename_MC_JECdown.push_back(filename_ttZ_JECdown);
  filename_MC_TESup.push_back(filename_ttZ_TESup);
  filename_MC_TESdown.push_back(filename_ttZ_TESdown);
  
  XS.push_back(XS_ttZ);
  filename_MC.push_back(filename_ttZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttZ);
  filename_norm_MC.push_back(filename_norm_ttZ);
  MC_sample_name.push_back("TTZ_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttZ_JECup);
  filename_MC_JECdown.push_back(filename_ttZ_JECdown);
  filename_MC_TESup.push_back(filename_ttZ_TESup);
  filename_MC_TESdown.push_back(filename_ttZ_TESdown);

  XS.push_back(XS_ttZ);
  filename_MC.push_back(filename_ttZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttZ);
  filename_norm_MC.push_back(filename_norm_ttZ);
  MC_sample_name.push_back("TTZ_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttZ_JECup);
  filename_MC_JECdown.push_back(filename_ttZ_JECdown);
  filename_MC_TESup.push_back(filename_ttZ_TESup);
  filename_MC_TESdown.push_back(filename_ttZ_TESdown);

  /*XS.push_back(XS_ttZ);
  filename_MC.push_back(filename_ttZ);
  filename_norm_MC.push_back(filename_norm_ttZ);
  MC_sample_name.push_back("ttZ_Ztautau");
  MC_sample_cut.push_back("genZ_decayMode[0]<=5");
  filename_MC_JECup.push_back(filename_ttZ_JECup);
  filename_MC_JECdown.push_back(filename_ttZ_JECdown);
  filename_MC_TESup.push_back(filename_ttZ_TESup);
  filename_MC_TESdown.push_back(filename_ttZ_TESdown);

  XS.push_back(XS_ttZ);
  filename_MC.push_back(filename_ttZ);
  filename_norm_MC.push_back(filename_norm_ttZ);
  MC_sample_name.push_back("ttZ_Zll");
  MC_sample_cut.push_back("(genZ_decayMode[0]==6 || genZ_decayMode[0]==7)");
  filename_MC_JECup.push_back(filename_ttZ_JECup);
  filename_MC_JECdown.push_back(filename_ttZ_JECdown);
  filename_MC_TESup.push_back(filename_ttZ_TESup);
  filename_MC_TESdown.push_back(filename_ttZ_TESdown);*/


  XS.push_back(XS_ttG);
  filename_MC.push_back(filename_ttG);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttG);
  filename_norm_MC.push_back(filename_norm_ttG);
  MC_sample_name.push_back("Convs");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back(filename_ttG_JECup);
  filename_MC_JECdown.push_back(filename_ttG_JECdown);
  filename_MC_TESup.push_back(filename_ttG_TESup);
  filename_MC_TESdown.push_back(filename_ttG_TESdown);
  
  XS.push_back(XS_ttG);
  filename_MC.push_back(filename_ttG);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttG);
  filename_norm_MC.push_back(filename_norm_ttG);
  MC_sample_name.push_back("Convs_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttG_JECup);
  filename_MC_JECdown.push_back(filename_ttG_JECdown);
  filename_MC_TESup.push_back(filename_ttG_TESup);
  filename_MC_TESdown.push_back(filename_ttG_TESdown);

  XS.push_back(XS_ttG);
  filename_MC.push_back(filename_ttG);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttG);
  filename_norm_MC.push_back(filename_norm_ttG);
  MC_sample_name.push_back("Convs_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back(filename_ttG_JECup);
  filename_MC_JECdown.push_back(filename_ttG_JECdown);
  filename_MC_TESup.push_back(filename_ttG_TESup);
  filename_MC_TESdown.push_back(filename_ttG_TESdown);


  XS.push_back(XS_WZ);
  filename_MC.push_back(filename_WZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WZ);
  filename_norm_MC.push_back(filename_norm_WZ);
  MC_sample_name.push_back("WZ");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WZ_JECup);
  filename_MC_JECdown.push_back(filename_WZ_JECdown);
  filename_MC_TESup.push_back(filename_WZ_TESup);
  filename_MC_TESdown.push_back(filename_WZ_TESdown);

  XS.push_back(XS_WZ);
  filename_MC.push_back(filename_WZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WZ);
  filename_norm_MC.push_back(filename_norm_WZ);
  MC_sample_name.push_back("WZ_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WZ_JECup);
  filename_MC_JECdown.push_back(filename_WZ_JECdown);
  filename_MC_TESup.push_back(filename_WZ_TESup);
  filename_MC_TESdown.push_back(filename_WZ_TESdown);

  XS.push_back(XS_WZ);
  filename_MC.push_back(filename_WZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WZ);
  filename_norm_MC.push_back(filename_norm_WZ);
  MC_sample_name.push_back("WZ_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WZ_JECup);
  filename_MC_JECdown.push_back(filename_WZ_JECdown);
  filename_MC_TESup.push_back(filename_WZ_TESup);
  filename_MC_TESdown.push_back(filename_WZ_TESdown);

  XS.push_back(XS_ZZ);
  filename_MC.push_back(filename_ZZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ZZ);
  filename_norm_MC.push_back(filename_norm_ZZ);
  MC_sample_name.push_back("ZZ");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ZZ_JECup);
  filename_MC_JECdown.push_back(filename_ZZ_JECdown);
  filename_MC_TESup.push_back(filename_ZZ_TESup);
  filename_MC_TESdown.push_back(filename_ZZ_TESdown);

  XS.push_back(XS_ZZ);
  filename_MC.push_back(filename_ZZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ZZ);
  filename_norm_MC.push_back(filename_norm_ZZ);
  MC_sample_name.push_back("ZZ_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ZZ_JECup);
  filename_MC_JECdown.push_back(filename_ZZ_JECdown);
  filename_MC_TESup.push_back(filename_ZZ_TESup);
  filename_MC_TESdown.push_back(filename_ZZ_TESdown);

  XS.push_back(XS_ZZ);
  filename_MC.push_back(filename_ZZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ZZ);
  filename_norm_MC.push_back(filename_norm_ZZ);
  MC_sample_name.push_back("ZZ_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ZZ_JECup);
  filename_MC_JECdown.push_back(filename_ZZ_JECdown);
  filename_MC_TESup.push_back(filename_ZZ_TESup);
  filename_MC_TESdown.push_back(filename_ZZ_TESdown);




  XS.push_back(XS_WWW);
  filename_MC.push_back(filename_WWW);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WWW);
  filename_norm_MC.push_back(filename_norm_WWW);
  MC_sample_name.push_back("WWW");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WWW_JECup);
  filename_MC_JECdown.push_back(filename_WWW_JECdown);
  filename_MC_TESup.push_back(filename_WWW_TESup);
  filename_MC_TESdown.push_back(filename_WWW_TESdown);

  XS.push_back(XS_WWW);
  filename_MC.push_back(filename_WWW);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WWW);
  filename_norm_MC.push_back(filename_norm_WWW);
  MC_sample_name.push_back("WWW_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WWW_JECup);
  filename_MC_JECdown.push_back(filename_WWW_JECdown);
  filename_MC_TESup.push_back(filename_WWW_TESup);
  filename_MC_TESdown.push_back(filename_WWW_TESdown);

  XS.push_back(XS_WWW);
  filename_MC.push_back(filename_WWW);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WWW);
  filename_norm_MC.push_back(filename_norm_WWW);
  MC_sample_name.push_back("WWW_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WWW_JECup);
  filename_MC_JECdown.push_back(filename_WWW_JECdown);
  filename_MC_TESup.push_back(filename_WWW_TESup);
  filename_MC_TESdown.push_back(filename_WWW_TESdown);


  XS.push_back(XS_WWZ);
  filename_MC.push_back(filename_WWZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WWZ);
  filename_norm_MC.push_back(filename_norm_WWZ);
  MC_sample_name.push_back("WWZ");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WWZ_JECup);
  filename_MC_JECdown.push_back(filename_WWZ_JECdown);
  filename_MC_TESup.push_back(filename_WWZ_TESup);
  filename_MC_TESdown.push_back(filename_WWZ_TESdown);

  XS.push_back(XS_WWZ);
  filename_MC.push_back(filename_WWZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WWZ);
  filename_norm_MC.push_back(filename_norm_WWZ);
  MC_sample_name.push_back("WWZ_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WWZ_JECup);
  filename_MC_JECdown.push_back(filename_WWZ_JECdown);
  filename_MC_TESup.push_back(filename_WWZ_TESup);
  filename_MC_TESdown.push_back(filename_WWZ_TESdown);

  XS.push_back(XS_WWZ);
  filename_MC.push_back(filename_WWZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WWZ);
  filename_norm_MC.push_back(filename_norm_WWZ);
  MC_sample_name.push_back("WWZ_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WWZ_JECup);
  filename_MC_JECdown.push_back(filename_WWZ_JECdown);
  filename_MC_TESup.push_back(filename_WWZ_TESup);
  filename_MC_TESdown.push_back(filename_WWZ_TESdown);
  
  
  XS.push_back(XS_WZZ);
  filename_MC.push_back(filename_WZZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WZZ);
  filename_norm_MC.push_back(filename_norm_WZZ);
  MC_sample_name.push_back("WZZ");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WZZ_JECup);
  filename_MC_JECdown.push_back(filename_WZZ_JECdown);
  filename_MC_TESup.push_back(filename_WZZ_TESup);
  filename_MC_TESdown.push_back(filename_WZZ_TESdown);

  XS.push_back(XS_WZZ);
  filename_MC.push_back(filename_WZZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WZZ);
  filename_norm_MC.push_back(filename_norm_WZZ);
  MC_sample_name.push_back("WZZ_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WZZ_JECup);
  filename_MC_JECdown.push_back(filename_WZZ_JECdown);
  filename_MC_TESup.push_back(filename_WZZ_TESup);
  filename_MC_TESdown.push_back(filename_WZZ_TESdown);

  XS.push_back(XS_WZZ);
  filename_MC.push_back(filename_WZZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WZZ);
  filename_norm_MC.push_back(filename_norm_WZZ);
  MC_sample_name.push_back("WZZ_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WZZ_JECup);
  filename_MC_JECdown.push_back(filename_WZZ_JECdown);
  filename_MC_TESup.push_back(filename_WZZ_TESup);
  filename_MC_TESdown.push_back(filename_WZZ_TESdown);


  XS.push_back(XS_ZZZ);
  filename_MC.push_back(filename_ZZZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ZZZ);
  filename_norm_MC.push_back(filename_norm_ZZZ);
  MC_sample_name.push_back("ZZZ");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ZZZ_JECup);
  filename_MC_JECdown.push_back(filename_ZZZ_JECdown);
  filename_MC_TESup.push_back(filename_ZZZ_TESup);
  filename_MC_TESdown.push_back(filename_ZZZ_TESdown);

  XS.push_back(XS_ZZZ);
  filename_MC.push_back(filename_ZZZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ZZZ);
  filename_norm_MC.push_back(filename_norm_ZZZ);
  MC_sample_name.push_back("ZZZ_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ZZZ_JECup);
  filename_MC_JECdown.push_back(filename_ZZZ_JECdown);
  filename_MC_TESup.push_back(filename_ZZZ_TESup);
  filename_MC_TESdown.push_back(filename_ZZZ_TESdown);

  XS.push_back(XS_ZZZ);
  filename_MC.push_back(filename_ZZZ);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ZZZ);
  filename_norm_MC.push_back(filename_norm_ZZZ);
  MC_sample_name.push_back("ZZZ_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ZZZ_JECup);
  filename_MC_JECdown.push_back(filename_ZZZ_JECdown);
  filename_MC_TESup.push_back(filename_ZZZ_TESup);
  filename_MC_TESdown.push_back(filename_ZZZ_TESdown);


  XS.push_back(XS_WpWp);
  filename_MC.push_back(filename_WpWp);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WpWp);
  filename_norm_MC.push_back(filename_norm_WpWp);
  MC_sample_name.push_back("WWss");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WpWp_JECup);
  filename_MC_JECdown.push_back(filename_WpWp_JECdown);
  filename_MC_TESup.push_back(filename_WpWp_TESup);
  filename_MC_TESdown.push_back(filename_WpWp_TESdown);

  XS.push_back(XS_WpWp);
  filename_MC.push_back(filename_WpWp);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WpWp);
  filename_norm_MC.push_back(filename_norm_WpWp);
  MC_sample_name.push_back("WWss_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WpWp_JECup);
  filename_MC_JECdown.push_back(filename_WpWp_JECdown);
  filename_MC_TESup.push_back(filename_WpWp_TESup);
  filename_MC_TESdown.push_back(filename_WpWp_TESdown);

  XS.push_back(XS_WpWp);
  filename_MC.push_back(filename_WpWp);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_WpWp);
  filename_norm_MC.push_back(filename_norm_WpWp);
  MC_sample_name.push_back("WWss_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_WpWp_JECup);
  filename_MC_JECdown.push_back(filename_WpWp_JECdown);
  filename_MC_TESup.push_back(filename_WpWp_TESup);
  filename_MC_TESdown.push_back(filename_WpWp_TESdown);

  XS.push_back(XS_tZq);
  filename_MC.push_back(filename_tZq);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_tZq);
  filename_norm_MC.push_back(filename_norm_tZq);
  MC_sample_name.push_back("tZq");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_tZq_JECup);
  filename_MC_JECdown.push_back(filename_tZq_JECdown);
  filename_MC_TESup.push_back(filename_tZq_TESup);
  filename_MC_TESdown.push_back(filename_tZq_TESdown);

  XS.push_back(XS_tZq);
  filename_MC.push_back(filename_tZq);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_tZq);
  filename_norm_MC.push_back(filename_norm_tZq);
  MC_sample_name.push_back("tZq_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_tZq_JECup);
  filename_MC_JECdown.push_back(filename_tZq_JECdown);
  filename_MC_TESup.push_back(filename_tZq_TESup);
  filename_MC_TESdown.push_back(filename_tZq_TESdown);

  XS.push_back(XS_tZq);
  filename_MC.push_back(filename_tZq);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_tZq);
  filename_norm_MC.push_back(filename_norm_tZq);
  MC_sample_name.push_back("tZq_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_tZq_JECup);
  filename_MC_JECdown.push_back(filename_tZq_JECdown);
  filename_MC_TESup.push_back(filename_tZq_TESup);
  filename_MC_TESdown.push_back(filename_tZq_TESdown);

  XS.push_back(XS_TTTT);
  filename_MC.push_back(filename_TTTT);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_TTTT);
  filename_norm_MC.push_back(filename_norm_TTTT);
  MC_sample_name.push_back("TTTT");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_TTTT_JECup);
  filename_MC_JECdown.push_back(filename_TTTT_JECdown);
  filename_MC_TESup.push_back(filename_TTTT_TESup);
  filename_MC_TESdown.push_back(filename_TTTT_TESdown);

  XS.push_back(XS_TTTT);
  filename_MC.push_back(filename_TTTT);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_TTTT);
  filename_norm_MC.push_back(filename_norm_TTTT);
  MC_sample_name.push_back("TTTT_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_TTTT_JECup);
  filename_MC_JECdown.push_back(filename_TTTT_JECdown);
  filename_MC_TESup.push_back(filename_TTTT_TESup);
  filename_MC_TESdown.push_back(filename_TTTT_TESdown);

  XS.push_back(XS_TTTT);
  filename_MC.push_back(filename_TTTT);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_TTTT);
  filename_norm_MC.push_back(filename_norm_TTTT);
  MC_sample_name.push_back("TTTT_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_TTTT_JECup);
  filename_MC_JECdown.push_back(filename_TTTT_JECdown);
  filename_MC_TESup.push_back(filename_TTTT_TESup);
  filename_MC_TESdown.push_back(filename_TTTT_TESdown);


  XS.push_back(XS_tHq);
  filename_MC.push_back(filename_tHq);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_tHq);
  filename_norm_MC.push_back(filename_norm_tHq);
  MC_sample_name.push_back("tHq");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_tHq_JECup);
  filename_MC_JECdown.push_back(filename_tHq_JECdown);
  filename_MC_TESup.push_back(filename_tHq_TESup);
  filename_MC_TESdown.push_back(filename_tHq_TESdown);

  XS.push_back(XS_tHq);
  filename_MC.push_back(filename_tHq);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_tHq);
  filename_norm_MC.push_back(filename_norm_tHq);
  MC_sample_name.push_back("tHq_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_tHq_JECup);
  filename_MC_JECdown.push_back(filename_tHq_JECdown);
  filename_MC_TESup.push_back(filename_tHq_TESup);
  filename_MC_TESdown.push_back(filename_tHq_TESdown);

  XS.push_back(XS_tHq);
  filename_MC.push_back(filename_tHq);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_tHq);
  filename_norm_MC.push_back(filename_norm_tHq);
  MC_sample_name.push_back("tHq_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_tHq_JECup);
  filename_MC_JECdown.push_back(filename_tHq_JECdown);
  filename_MC_TESup.push_back(filename_tHq_TESup);
  filename_MC_TESdown.push_back(filename_tHq_TESdown);


  XS.push_back(XS_tHW);
  filename_MC.push_back(filename_tHW);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_tHW);
  filename_norm_MC.push_back(filename_norm_tHW);
  MC_sample_name.push_back("tHW");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_tHW_JECup);
  filename_MC_JECdown.push_back(filename_tHW_JECdown);
  filename_MC_TESup.push_back(filename_tHW_TESup);
  filename_MC_TESdown.push_back(filename_tHW_TESdown);

  XS.push_back(XS_tHW);
  filename_MC.push_back(filename_tHW);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_tHW);
  filename_norm_MC.push_back(filename_norm_tHW);
  MC_sample_name.push_back("tHW_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_tHW_JECup);
  filename_MC_JECdown.push_back(filename_tHW_JECdown);
  filename_MC_TESup.push_back(filename_tHW_TESup);
  filename_MC_TESdown.push_back(filename_tHW_TESdown);

  XS.push_back(XS_tHW);
  filename_MC.push_back(filename_tHW);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_tHW);
  filename_norm_MC.push_back(filename_norm_tHW);
  MC_sample_name.push_back("tHW_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_tHW_JECup);
  filename_MC_JECdown.push_back(filename_tHW_JECdown);
  filename_MC_TESup.push_back(filename_tHW_TESup);
  filename_MC_TESdown.push_back(filename_tHW_TESdown);

  XS.push_back(XS_ttWW);
  filename_MC.push_back(filename_ttWW);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttWW);
  filename_norm_MC.push_back(filename_norm_ttWW);
  MC_sample_name.push_back("TTWW");
  MC_sample_cut.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttWW_JECup);
  filename_MC_JECdown.push_back(filename_ttWW_JECdown);
  filename_MC_TESup.push_back(filename_ttWW_TESup);
  filename_MC_TESdown.push_back(filename_ttWW_TESdown);

  XS.push_back(XS_ttWW);
  filename_MC.push_back(filename_ttWW);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttWW);
  filename_norm_MC.push_back(filename_norm_ttWW);
  MC_sample_name.push_back("TTWW_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttWW_JECup);
  filename_MC_JECdown.push_back(filename_ttWW_JECdown);
  filename_MC_TESup.push_back(filename_ttWW_TESup);
  filename_MC_TESdown.push_back(filename_ttWW_TESdown);

  XS.push_back(XS_ttWW);
  filename_MC.push_back(filename_ttWW);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttWW);
  filename_norm_MC.push_back(filename_norm_ttWW);
  MC_sample_name.push_back("TTWW_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_JECup.push_back(filename_ttWW_JECup);
  filename_MC_JECdown.push_back(filename_ttWW_JECdown);
  filename_MC_TESup.push_back(filename_ttWW_TESup);
  filename_MC_TESdown.push_back(filename_ttWW_TESdown);
 
  /*XS.push_back(XS_ttZ_lowmass);
  filename_MC.push_back(filename_ttZ_lowmass);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttZ_lowmass);
  filename_norm_MC.push_back(filename_norm_ttZ_lowmass);
  MC_sample_name.push_back("Convs");
  MC_sample_cut.push_back("1");
  filename_MC_JECup.push_back("");
  filename_MC_JECdown.push_back("");
  filename_MC_TESup.push_back("");
  filename_MC_TESdown.push_back("");

  XS.push_back(XS_ttZ_lowmass);
  filename_MC.push_back(filename_ttZ_lowmass);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttZ_lowmass);
  filename_norm_MC.push_back(filename_norm_ttZ_lowmass);
  MC_sample_name.push_back("Convs_gentau");
  MC_sample_cut.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back("");
  filename_MC_JECdown.push_back("");
  filename_MC_TESup.push_back("");
  filename_MC_TESdown.push_back("");

  XS.push_back(XS_ttZ_lowmass);
  filename_MC.push_back(filename_ttZ_lowmass);
  filename_lepMVA_CR_MC.push_back(filename_lepMVA_CR_ttZ_lowmass);
  filename_norm_MC.push_back(filename_norm_ttZ_lowmass);
  MC_sample_name.push_back("Convs_faketau");
  MC_sample_cut.push_back("!recotauh_sel_isGenMatched[0]");
  filename_MC_JECup.push_back("");
  filename_MC_JECdown.push_back("");
  filename_MC_TESup.push_back("");
  filename_MC_TESdown.push_back("");*/

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

  /*filename_data.push_back(filename_DoubleEG_2016);
  filename_data.push_back(filename_MuonEG_2016);
  filename_data.push_back(filename_DoubleMu_2016);
  filename_data.push_back(filename_SingleMu_2016);
  filename_data.push_back(filename_SingleEle_2016);*/



  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleEG_2016B);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_MuonEG_2016B);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleMu_2016B);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleMu_2016B);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleEle_2016B);

  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleEG_2016C);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_MuonEG_2016C);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleMu_2016C);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleMu_2016C);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleEle_2016C);

  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleEG_2016D);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_MuonEG_2016D);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleMu_2016D);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleMu_2016D);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleEle_2016D);

  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleEG_2016E);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_MuonEG_2016E);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleMu_2016E);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleMu_2016E);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleEle_2016E);

  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleEG_2016F);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_MuonEG_2016F);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleMu_2016F);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleMu_2016F);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleEle_2016F);

  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleEG_2016G);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_MuonEG_2016G);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleMu_2016G);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleMu_2016G);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleEle_2016G);

  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleEG_2016Hv2);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_MuonEG_2016Hv2);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleMu_2016Hv2);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleMu_2016Hv2);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleEle_2016Hv2);

  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleEG_2016Hv3);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_MuonEG_2016Hv3);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleMu_2016Hv3);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleMu_2016Hv3);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleEle_2016Hv3);

  /*filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleEG_2016);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_MuonEG_2016);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_DoubleMu_2016);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleMu_2016);
  filename_data_lepMVA_CR.push_back(filename_lepMVA_CR_SingleEle_2016);*/



  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleEG_2016B);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_MuonEG_2016B);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleMu_2016B);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleMu_2016B);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleEle_2016B);

  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleEG_2016C);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_MuonEG_2016C);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleMu_2016C);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleMu_2016C);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleEle_2016C);

  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleEG_2016D);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_MuonEG_2016D);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleMu_2016D);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleMu_2016D);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleEle_2016D);

  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleEG_2016E);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_MuonEG_2016E);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleMu_2016E);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleMu_2016E);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleEle_2016E);

  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleEG_2016F);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_MuonEG_2016F);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleMu_2016F);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleMu_2016F);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleEle_2016F);

  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleEG_2016G);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_MuonEG_2016G);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleMu_2016G);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleMu_2016G);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleEle_2016G);

  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleEG_2016Hv2);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_MuonEG_2016Hv2);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleMu_2016Hv2);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleMu_2016Hv2);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleEle_2016Hv2);

  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleEG_2016Hv3);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_MuonEG_2016Hv3);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleMu_2016Hv3);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleMu_2016Hv3);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleEle_2016Hv3);

  /*filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleEG_2016);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_MuonEG_2016);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_DoubleMu_2016);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleMu_2016);
  filename_data_2lOS_CR.push_back(filename_2lOS_CR_SingleEle_2016);*/

  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH");
  MC_sample_cut_thu_unc.push_back("!(n_genW==2 && n_genZ<2 && genH_decayMode[1]>5) && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_gentau");
  MC_sample_cut_thu_unc.push_back("!(n_genW==2 && n_genZ<2 && genH_decayMode[1]>5) && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && recotauh_sel_isGenMatched[0]");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_faketau");
  MC_sample_cut_thu_unc.push_back("!(n_genW==2 && n_genZ<2 && genH_decayMode[1]>5) && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && !recotauh_sel_isGenMatched[0]");

  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_htt");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]<=5 && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_htt_gentau");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]<=5 && recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_htt_faketau");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]<=5 && !recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");

  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hww");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genW==4 && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hww_gentau");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genW==4 && recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hww_faketau");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genW==4 && !recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");

  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hzz");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genZ==2 && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hzz_gentau");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genZ==2 && recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH_hzz_faketau");
  MC_sample_cut_thu_unc.push_back("genH_decayMode[1]>5 && n_genZ==2 && !recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");

  filename_MC_thu_unc.push_back(filename_ttW);
  MC_sample_name_thu_unc.push_back("TTW");
  MC_sample_cut_thu_unc.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_thu_unc.push_back(filename_ttW);
  MC_sample_name_thu_unc.push_back("TTW_gentau");
  MC_sample_cut_thu_unc.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_thu_unc.push_back(filename_ttW);
  MC_sample_name_thu_unc.push_back("TTW_faketau");
  MC_sample_cut_thu_unc.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");

  filename_MC_thu_unc.push_back(filename_ttZ);
  MC_sample_name_thu_unc.push_back("TTZ");
  MC_sample_cut_thu_unc.push_back("recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_thu_unc.push_back(filename_ttZ);
  MC_sample_name_thu_unc.push_back("TTZ_gentau");
  MC_sample_cut_thu_unc.push_back("recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");
  filename_MC_thu_unc.push_back(filename_ttZ);
  MC_sample_name_thu_unc.push_back("TTZ_faketau");
  MC_sample_cut_thu_unc.push_back("!recotauh_sel_isGenMatched[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1]");

  /*filename_MC_thu_unc.push_back(filename_ttG);
  MC_sample_name_thu_unc.push_back("ttG");
  MC_sample_cut_thu_unc.push_back("1");
  filename_MC_thu_unc.push_back(filename_ttG);
  MC_sample_name_thu_unc.push_back("ttG_gentau");
  MC_sample_cut_thu_unc.push_back("recotauh_sel_isGenMatched[0]");
  filename_MC_thu_unc.push_back(filename_ttG);
  MC_sample_name_thu_unc.push_back("ttG_faketau");
  MC_sample_cut_thu_unc.push_back("!recotauh_sel_isGenMatched[0]");*/


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

  fake_syst_names.push_back("ele_up");
  fake_syst_names.push_back("ele_down");
  fake_syst_names.push_back("ele_pt1");
  fake_syst_names.push_back("ele_pt2");
  fake_syst_names.push_back("ele_b1");
  fake_syst_names.push_back("ele_b2");
  fake_syst_names.push_back("ele_ec1");
  fake_syst_names.push_back("ele_ec2");
  fake_syst_names.push_back("ele_be1");
  fake_syst_names.push_back("ele_be2");

  fake_syst_names.push_back("mu_up");
  fake_syst_names.push_back("mu_down");
  fake_syst_names.push_back("mu_pt1");
  fake_syst_names.push_back("mu_pt2");
  fake_syst_names.push_back("mu_b1");
  fake_syst_names.push_back("mu_b2");
  fake_syst_names.push_back("mu_ec1");
  fake_syst_names.push_back("mu_ec2");
  fake_syst_names.push_back("mu_be1");
  fake_syst_names.push_back("mu_be2");

}






void datacard_maker(TString var1, int nbin, float xmin, float xmax,
		    TString cut_cat1, TString file, bool syst=false, TString catname="2lss_1tau"){

  //TString var = "(" + var1 + ")*((" + var1 + Form(")>=%f) + %f*((",xmin,0.999*xmin) + var1 + Form(")<%f)",xmin);
  TString var = "(" + var1 + ")*((" + var1 + Form(")<=%f) + %f*((",xmax,0.999*xmax) + var1 + Form(")>%f)",xmax);
  cout<<var<<endl;


  initialize();

  TString cut_cat = "recolep_sel_charge[0]*recotauh_sel_charge[0]<0 && " + cut_cat1;
  
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
			       "T",
			       var,			    
			       MC_weight + Form("*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*bTagSF_CSVshape_weight_v2*tauSF_weight_v3*(category==%i && isTrig_v2 &&",cat[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat + ")",
			       nbin,xmin,xmax);

      
      h_MC->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC->SetNameTitle("x_"+MC_sample_name[i_MC],"x_"+MC_sample_name[i_MC]);
      makeBinContentsPositive(h_MC,true);
      h_MC->Write();


      if(MC_sample_name[i_MC].Contains("gentau") || MC_sample_name[i_MC].Contains("faketau")) continue;

      TH1F* h_MC_genmatch = single_plot(filename_lepMVA_CR_MC[i_MC],
					"T",
					var,
					MC_weight + Form("*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*bTagSF_CSVshape_weight_v2*event_weight_ttH_v2*tauSF_weight_v3*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] && ",cat_fakes[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat + ")",
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

    }

    bkg_type.erase(bkg_type.begin()+3);
    
    //Fakes
    
    TH1F* h_fakes =single_plot(filename_data_lepMVA_CR,
			       "T",
			       var,			     
			       Form("event_weight_ttH_v2*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && NBadMu==0 &&",cat_fakes[i_cat]) + cut_cat + ")",
			       nbin,xmin,xmax);

    
    h_fakes->Scale(luminosity/35867.); //Data files for 35.9 fb-1
    //h_fakes->Add((TH1F*)f_new->Get("x_ttH_genmatch_fake_CR"),-1);
    h_fakes->Add((TH1F*)f_new->Get("x_TTW_genmatch_fake_CR"),-1);
    h_fakes->Add((TH1F*)f_new->Get("x_TTZ_genmatch_fake_CR"),-1);
    h_fakes->Add((TH1F*)f_new->Get("x_Convs_genmatch_fake_CR"),-1);
    h_fakes->Add((TH1F*)f_new->Get("x_EWK_genmatch_fake_CR"),-1);
    h_fakes->Add((TH1F*)f_new->Get("x_Rares_genmatch_fake_CR"),-1);
    h_fakes->Add((TH1F*)f_new->Get("x_TTWW_genmatch_fake_CR"),-1);
    h_fakes->Add((TH1F*)f_new->Get("x_tHq_genmatch_fake_CR"),-1);
    h_fakes->Add((TH1F*)f_new->Get("x_tHW_genmatch_fake_CR"),-1);
    h_fakes->SetNameTitle("x_data_fakes","x_data_fakes");
    makeBinContentsPositive(h_fakes,true);
    h_fakes->Write();


    //Fakes MC
    
    TH1F* h_ttbar_DL_fakes_MC =single_plot(filename_ttbar_DL,
				  "T",
				  var,
				  Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*bTagSF_CSVshape_weight_v2*leptonSF_ttH_weight_v3*tauSF_weight_v3*event_weight_ttH_v2*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",
				  nbin,xmin,xmax);

    TH1F* h_ttbar_DL_norm =single_plot(filename_norm_ttbar_DL,
				       "HTauTauTree",
				       "1",
				       "MC_weight*PU_weight_MCSummer2016",
				       3,0,3);
 
    h_ttbar_DL_fakes_MC->Scale(luminosity*XS_ttbar_DL/h_ttbar_DL_norm->Integral());

    TH1F* h_ttbar_SLfromT_fakes_MC =single_plot(filename_ttbar_SLfromT,
                                  "T",
                                  var,
                                  Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*bTagSF_CSVshape_weight_v2*leptonSF_ttH_weight_v3*tauSF_weight_v3*event_weight_ttH_v2*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",
                                  nbin,xmin,xmax);

    TH1F* h_ttbar_SLfromT_norm =single_plot(filename_norm_ttbar_SLfromT,
                                       "HTauTauTree",
                                       "1",
                                       "MC_weight*PU_weight_MCSummer2016",
                                       3,0,3);

    h_ttbar_SLfromT_fakes_MC->Scale(luminosity*XS_ttbar_SLfromT/h_ttbar_SLfromT_norm->Integral());

    TH1F* h_ttbar_SLfromTbar_fakes_MC =single_plot(filename_ttbar_SLfromTbar,
                                  "T",
                                  var,
                                  Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*bTagSF_CSVshape_weight_v2*leptonSF_ttH_weight_v3*tauSF_weight_v3*event_weight_ttH_v2*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",
                                  nbin,xmin,xmax);

    TH1F* h_ttbar_SLfromTbar_norm =single_plot(filename_norm_ttbar_SLfromTbar,
                                       "HTauTauTree",
                                       "1",
                                       "MC_weight*PU_weight_MCSummer2016",
                                       3,0,3);

    h_ttbar_SLfromTbar_fakes_MC->Scale(luminosity*XS_ttbar_SLfromTbar/h_ttbar_SLfromTbar_norm->Integral());

    TH1F* h_fakes_MC = (TH1F*)h_ttbar_DL_fakes_MC->Clone();
    h_fakes_MC->Add(h_ttbar_SLfromT_fakes_MC,+1);
    h_fakes_MC->Add(h_ttbar_SLfromTbar_fakes_MC,+1);
    h_fakes_MC->SetNameTitle("x_fakes_MC","x_fakes_MC");
    h_fakes_MC->Write();



    //Charge flips

    TString cut_cat_flips = "( (abs(recolep_sel_pdg[0])==11 && recolep_sel_charge[0]*recotauh_sel_charge[0]>0) || (abs(recolep_sel_pdg[1])==11 && recolep_sel_charge[1]*recotauh_sel_charge[0]>0) ) && " + cut_cat1;
    TH1F* h_flips =single_plot(filename_data_2lOS_CR,
			       "T",
			       var,
			       Form("event_weight_ttH_v2*(category==%i && isTrig_v2 && NBadMu==0 &&",cat_flips[i_cat]) + cut_cat_flips + ")",			      
			       nbin,xmin,xmax);
    
    h_flips->Scale(luminosity/35867.); //Data files for 35.9 fb-1
    h_flips->SetNameTitle("x_data_flips","x_data_flips");
    makeBinContentsPositive(h_flips,true);
    h_flips->Write();
 
    
    
    //Data
    
    TH1F* h_data_obs =single_plot(filename_data,
				  "T",
				  var,
				  Form("(category==%i && isTrig_v2 && NBadMu==0 &&",cat[i_cat]) +  cut_cat + ")",		
				  nbin,xmin,xmax);
      
    h_data_obs->Scale(luminosity/35867.); //Data files for 35.9 fb-1
      
    h_data_obs->SetNameTitle("x_data_obs","x_data_obs");
    h_data_obs->Write();
 

    /*TH1F* h_data_obs = (TH1F*)f_new->Get("x_ttH");
    h_data_obs->Add( (TH1F*)f_new->Get("x_TTW") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_TTZ") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_EWK") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_Rares") );    
    h_data_obs->Add( (TH1F*)f_new->Get("x_data_fakes") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_data_flips") );
    h_data_obs->SetNameTitle("x_data_obs","x_data_obs");
    h_data_obs->Write();*/

    

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

	TString MC_weight = "MC_weight";
	if(MC_sample_name[i_MC].Contains("tHq") || MC_sample_name[i_MC].Contains("tHW"))
	  MC_weight += "_tHq_SM_457";
		    
	TString cut = MC_weight + "*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*tauSF_weight_v3*bTagSF_CSVshape_weight_" + bTag_syst_names[i_b]+"_v2";
	cut+=Form("*(category==%i && isTrig_v2 &&",cat[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat +")";

	TH1F* h_MC_btag_syst = single_plot(filename_MC[i_MC],
					   "T",
					   var,
					   cut,
					   nbin,xmin,xmax);

      	h_MC_btag_syst->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);      
	makeBinContentsPositive(h_MC_btag_syst);

	if(h_MC_btag_syst->Integral()==0)
	   h_MC_btag_syst = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC])->Clone();        

	TString h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_btag_cErr2Down";

	h_MC_btag_syst->SetNameTitle(h_name,h_name);
	h_MC_btag_syst->Write();

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


      /*TString h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	TString h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	
	TString h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	  h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";
	

	TH1F* h_TTZ = (TH1F*)f_new->Get(h_name_ttZ);
	h_TTZ->Add( (TH1F*)f_new->Get(h_name_ttG) );
	h_TTZ->SetNameTitle(h_name_TTZ,h_name_TTZ);
	h_TTZ->Write();*/
	


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

	/*TString h_name_ttWW = "x_ttWW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b].Contains("Stats"))
	  h_name_ttWW = "x_ttWW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1Up")
	  h_name_ttWW = "x_ttWW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Up";
	else if(bTag_syst_names[i_b]=="CFErr1Down")
	  h_name_ttWW = "x_ttWW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr1Down";
	else if(bTag_syst_names[i_b]=="CFErr2Up")
	  h_name_ttWW = "x_ttWW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Up";
	else if(bTag_syst_names[i_b]=="CFErr2Down")
	h_name_ttWW = "x_ttWW"+bkg_type[i_bkg]+"_CMS_ttHl16_btag_cErr2Down";*/

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
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWss) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_tZq) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_TTTT) );
	//h_Rares->Add( (TH1F*)f_new->Get(h_name_ttWW) );
	h_Rares->SetNameTitle(h_name_Rares,h_name_Rares);
	h_Rares->Write();
	

      }

    }

    cout<<"OK syst btag"<<endl;





    for(unsigned i_MC=0;i_MC<MC_sample_name_thu_unc.size();i_MC++){

	//cout<<MC_sample_name_thu_unc[i_MC]<<endl;

      if(MC_sample_name_thu_unc[i_MC]!=MC_sample_name[i_MC]){
	cout<<MC_sample_name_thu_unc[i_MC]<<endl;
	cout<<MC_sample_name[i_MC]<<endl;
	cout<<"Problem!"<<endl;
	return;
      }

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
		    
      TString cut = "PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*tauSF_weight_v3*bTagSF_CSVshape_weight_v2";
      cut+=Form("*(category==%i && isTrig_v2 && ",cat[i_cat]) + MC_sample_cut_thu_unc[i_MC] + " && " + cut_cat + ")";

      TH1F* h_MC_x1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "T",
				     var,
				     "MC_weight_scale_muR2*"+cut,
				     nbin,xmin,xmax);
      
      //h_MC_x1_up->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_x1_up->Scale(norm/h_MC_x1_up->Integral());

      h_MC_x1_up->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Up","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Up");
      makeBinContentsPositive(h_MC_x1_up);
      h_MC_x1_up->Write();

      TH1F* h_MC_x1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "T",
				       var,
				       "MC_weight_scale_muR0p5*"+cut,
				       nbin,xmin,xmax);
      
      //h_MC_x1_down->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_x1_down->Scale(norm/h_MC_x1_down->Integral());
      h_MC_x1_down->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Down","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Down");
      makeBinContentsPositive(h_MC_x1_down);
      h_MC_x1_down->Write();

      TH1F* h_MC_y1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "T",
				     var,
				     "MC_weight_scale_muF2*"+cut,
				     nbin,xmin,xmax);
      
      //h_MC_y1_up->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_y1_up->Scale(norm/h_MC_y1_up->Integral());
      h_MC_y1_up->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Up","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Up");
      makeBinContentsPositive(h_MC_y1_up);
      h_MC_y1_up->Write();

      TH1F* h_MC_y1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "T",
				       var,
				       "MC_weight_scale_muF0p5*"+cut,
				       nbin,xmin,xmax);
      
      //h_MC_y1_down->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_y1_down->Scale(norm/h_MC_y1_down->Integral());
      h_MC_y1_down->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Down","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Down");
      makeBinContentsPositive(h_MC_y1_down);
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
      cout<<"x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"Up"<<endl;
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

      for(unsigned int i_bkg=0;i_bkg<bkg_type.size();i_bkg++){

	TString h_name_ttH = "x_ttH_CMS_ttHl_thu_shape_ttH1"+thu_uncert[i];
	TString h_name_tHq = "x_tHq"; //Just take nominal for tHq
	TString h_name_tHW = "x_tHW"; //Just take nominal for tHW
	TString h_name_TTH = "x_TTH_CMS_ttHl_thu_shape_ttH1"+thu_uncert[i];
	
	TH1F* h_TTH = (TH1F*)f_new->Get(h_name_ttH)->Clone();
	h_TTH->Add( (TH1F*)f_new->Get(h_name_tHq) );
	h_TTH->Add( (TH1F*)f_new->Get(h_name_tHW) );
	h_TTH->SetNameTitle(h_name_TTH,h_name_TTH);
	h_TTH->Write();
	
	h_name_TTH = "x_TTH_gentau_CMS_ttHl_thu_shape_ttH_"+thu_uncert[i];
	h_TTH->SetNameTitle(h_name_TTH,h_name_TTH);
	h_TTH->Write();


	/*TString h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl_thu_shape_ttZ_"+thu_uncert[i];
	TString h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl_thu_shape_ttG_"+thu_uncert[i];
	TString h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl_thu_shape_ttZ_"+thu_uncert[i];
	
	
	TH1F* h_TTZ = (TH1F*)f_new->Get(h_name_ttZ)->Clone();
	h_TTZ->Add( (TH1F*)f_new->Get(h_name_ttG) );
	h_TTZ->SetNameTitle(h_name_TTZ,h_name_TTZ);
	h_TTZ->Write();*/

      }

    }

    cout<<"OK syst theoretical "<<endl;


    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      TString MC_weight = "MC_weight";
      if(MC_sample_name[i_MC].Contains("tHq") || MC_sample_name[i_MC].Contains("tHW"))
	MC_weight += "_tHq_SM_457";
      
      TString cut = MC_weight + "*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*bTagSF_CSVshape_weight_v2*tauSF_weight_v3";
      cut+=Form("*(category==%i && isTrig_v2 &&",cat[i_cat]) + MC_sample_cut[i_MC]  + " && " + cut_cat + ")";

      
      TH1F* h_MC_JEC_up = single_plot(filename_MC_JECup[i_MC],
				      "T",
				      var,
				      cut,
				      nbin,xmin,xmax);

      
      h_MC_JEC_up->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      

      float norm_JEC_up = h_MC_JEC_up->Integral();


      h_MC_JEC_up = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]);
      h_MC_JEC_up->Scale(norm_JEC_up/h_MC_JEC_up->Integral());

      h_MC_JEC_up->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_scale_jUp","x_"+MC_sample_name[i_MC]+"_CMS_scale_jUp");
      makeBinContentsPositive(h_MC_JEC_up);
      h_MC_JEC_up->Write();

      
      TH1F* h_MC_JEC_down = single_plot(filename_MC_JECdown[i_MC],
					"T",
					var,
					cut,
					nbin,xmin,xmax);

      h_MC_JEC_down->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);

      float norm_JEC_down = h_MC_JEC_down->Integral();
      h_MC_JEC_down = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]);
      h_MC_JEC_down->Scale(norm_JEC_down/h_MC_JEC_down->Integral());

      h_MC_JEC_down->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_scale_jDown","x_"+MC_sample_name[i_MC]+"_CMS_scale_jDown");
      makeBinContentsPositive(h_MC_JEC_down);      
      h_MC_JEC_down->Write();

      TH1F* h_MC_TES_up = single_plot(filename_MC_TESup[i_MC],
				      "T",
				      var,
				      cut,
				      nbin,xmin,xmax);
      
      h_MC_TES_up->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);

      float norm_TES_up = h_MC_TES_up->Integral();
      h_MC_TES_up = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]);
      h_MC_TES_up->Scale(norm_TES_up/h_MC_TES_up->Integral());


      h_MC_TES_up->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_scale_tUp","x_"+MC_sample_name[i_MC]+"_CMS_scale_tUp");
      makeBinContentsPositive(h_MC_TES_up);
      h_MC_TES_up->Write();

      
      TH1F* h_MC_TES_down = single_plot(filename_MC_TESdown[i_MC],
					"T",
					var,
					cut,
					nbin,xmin,xmax);
      
      h_MC_TES_down->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);

      float norm_TES_down = h_MC_TES_down->Integral();
      h_MC_TES_down = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]);
      h_MC_TES_down->Scale(norm_TES_down/h_MC_TES_down->Integral());

      h_MC_TES_down->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_scale_tDown","x_"+MC_sample_name[i_MC]+"_CMS_scale_tDown");
      makeBinContentsPositive(h_MC_TES_down);
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
	
	TH1F* h_TTH = (TH1F*)f_new->Get(h_name_ttH);
	h_TTH->Add( (TH1F*)f_new->Get(h_name_tHq) );
	h_TTH->Add( (TH1F*)f_new->Get(h_name_tHW) );
	h_TTH->SetNameTitle(h_name_TTH,h_name_TTH);
	h_TTH->Write();

	/*TString h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	TString h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	TString h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl_"+JES_TES_uncert[i];
	
	TH1F* h_TTZ = (TH1F*)f_new->Get(h_name_ttZ)->Clone();
	h_TTZ->Add( (TH1F*)f_new->Get(h_name_ttG) );
	h_TTZ->SetNameTitle(h_name_TTZ,h_name_TTZ);
	h_TTZ->Write();*/
	
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
	TString h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
	TString h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
	TString h_name_TTTT = "x_TTTT"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];

	TString h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_scale_"+JES_TES_uncert[i];
	
	TH1F* h_Rares = (TH1F*)f_new->Get(h_name_WWW)->Clone();
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WZZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_ZZZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWss) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_tZq) );	
	h_Rares->Add( (TH1F*)f_new->Get(h_name_TTTT) );
	//h_Rares->Add( (TH1F*)f_new->Get(h_name_ttWW) );
	h_Rares->SetNameTitle(h_name_Rares,h_name_Rares);
	h_Rares->Write();
	
      }

    }
    

    cout<<"OK JEC/TES "<<endl;

 
   
   
    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      if(!MC_sample_name[i_MC].Contains("faketau")) continue;

      for(unsigned int i_t=0;i_t<jetToTau_FR_syst_names.size();i_t++){       
		    
	TString MC_weight = "MC_weight";
	if(MC_sample_name[i_MC].Contains("tHq") || MC_sample_name[i_MC].Contains("tHW"))
	  MC_weight += "_tHq_SM_457";

	TString cut = MC_weight + "*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*bTagSF_CSVshape_weight_v2*tauSF_weight_"+ jetToTau_FR_syst_names[i_t] +"_v3";
	cut+=Form("*(category==%i && isTrig_v2 &&",cat[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat +")";

	TH1F* h_MC_FRjt_syst = single_plot(filename_MC[i_MC],
						  "T",
						  var,
						  cut,
						  nbin,xmin,xmax);
	
      	h_MC_FRjt_syst->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);      

        TString h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name+="shapeDown";

	h_MC_FRjt_syst->SetNameTitle(h_name,h_name);
	makeBinContentsPositive(h_MC_FRjt_syst);
	h_MC_FRjt_syst->Write();

      }

    }




    for(unsigned int i_t=0;i_t<jetToTau_FR_syst_names.size();i_t++){  

      for(unsigned int i_bkg=0;i_bkg<bkg_type.size();i_bkg++){

        if(!bkg_type[i_bkg].Contains("faketau")) continue;

TString h_name_ttH = "x_ttH"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
	if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
	  h_name_ttH+="normUp";
	else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
	  h_name_ttH+="normDown";
	else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
	  h_name_ttH+="shapeUp";
	else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
	  h_name_ttH+="shapeDown";
	TString h_name_tHq = "x_tHq"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
	if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
	  h_name_tHq+="normUp";
	else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
	  h_name_tHq+="normDown";
	else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
	  h_name_tHq+="shapeUp";
	else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
	  h_name_tHq+="shapeDown";
	TString h_name_tHW = "x_tHW"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
	if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
	  h_name_tHW+="normUp";
	else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
	  h_name_tHW+="normDown";
	else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
	  h_name_tHW+="shapeUp";
	else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
	  h_name_tHW+="shapeDown";	
	TString h_name_TTH = "x_TTH"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
	if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
	  h_name_TTH+="normUp";
	else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
	  h_name_TTH+="normDown";
	else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
	  h_name_TTH+="shapeUp";
	else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
	  h_name_TTH+="shapeDown";	

	TH1F* h_TTH = (TH1F*)f_new->Get(h_name_ttH);
	h_TTH->Add( (TH1F*)f_new->Get(h_name_tHq) );
	h_TTH->Add( (TH1F*)f_new->Get(h_name_tHW) );
	h_TTH->SetNameTitle(h_name_TTH,h_name_TTH);
	h_TTH->Write();

	/*TString h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_ttZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_ttZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_ttZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_ttZ+="shapeDown";
        TString h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_ttG+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_ttG+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_ttG+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_ttG+="shapeDown";
	TString h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_TTZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_TTZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_TTZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_TTZ+="shapeDown";

		
	TH1F* h_TTZ = (TH1F*)f_new->Get(h_name_ttZ);
	h_TTZ->Add( (TH1F*)f_new->Get(h_name_ttG) );
	h_TTZ->SetNameTitle(h_name_TTZ,h_name_TTZ);
	h_TTZ->Write();*/
	
   	TString h_name_WZ = "x_WZ"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_WZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_WZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_WZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_WZ+="shapeDown";
        TString h_name_ZZ = "x_ZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_ZZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_ZZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_ZZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_ZZ+="shapeDown";
         TString h_name_EWK = "x_EWK"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_EWK+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_EWK+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_EWK+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_EWK+="shapeDown";


		
	TH1F* h_EWK = (TH1F*)f_new->Get(h_name_WZ);
	h_EWK->Add( (TH1F*)f_new->Get(h_name_ZZ) );
	h_EWK->SetNameTitle(h_name_EWK,h_name_EWK);
	h_EWK->Write();

	
	TString h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_WWW+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_WWW+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_WWW+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_WWW+="shapeDown";
        TString h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_WWZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_WWZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_WWZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_WWZ+="shapeDown";
        TString h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_WZZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_WZZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
      h_name_WZZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_WZZ+="shapeDown";
        TString h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_ZZZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_ZZZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_ZZZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_ZZZ+="shapeDown";
	TString h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_WWss+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_WWss+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_WWss+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_WWss+="shapeDown";
        TString h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_tZq+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_tZq+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_tZq+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_tZq+="shapeDown";
        TString h_name_TTTT = "x_TTTT"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_TTTT+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
	  h_name_TTTT+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_TTTT+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_TTTT+="shapeDown";
	/*TString h_name_ttWW = "x_ttWW"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
	if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
	  h_name_ttWW+="normUp";
	else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
	  h_name_ttWW+="normDown";
	else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
	  h_name_ttWW+="shapeUp";
	else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
	h_name_ttWW+="shapeDown";*/


        TString h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_Rares+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_Rares+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_Rares+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_Rares+="shapeDown";


	
	TH1F* h_Rares = (TH1F*)f_new->Get(h_name_WWW);
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WZZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_ZZZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWss) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_tZq) );	
	h_Rares->Add( (TH1F*)f_new->Get(h_name_TTTT) );
	//h_Rares->Add( (TH1F*)f_new->Get(h_name_ttWW) );
	h_Rares->SetNameTitle(h_name_Rares,h_name_Rares);
	h_Rares->Write();
	
      }

    }








    cout<<"OK syst jetToTau FR"<<endl;



   for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

     if(MC_sample_name[i_MC].Contains("faketau") || MC_sample_name[i_MC].Contains("gentau")) continue;

     TH1F* h_MC_tauIDUp = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]+"_faketau");
     h_MC_tauIDUp->Add((TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]+"_gentau"),1.05);
     h_MC_tauIDUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_eff_tUp", "x_"+MC_sample_name[i_MC]+"_CMS_eff_tUp");
     h_MC_tauIDUp->Write();

     TH1F* h_MC_tauIDDown = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]+"_faketau");
     h_MC_tauIDDown->Add((TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]+"_gentau"),0.95);
     h_MC_tauIDDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_eff_tDown", "x_"+MC_sample_name[i_MC]+"_CMS_eff_tDown");
     h_MC_tauIDDown->Write();

     
     
     TH1F* h_MC_FRjt_normUp = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]+"_gentau");
     h_MC_FRjt_normUp->Add((TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]+"_faketau_CMS_ttHl16_FRjt_normUp"));
     h_MC_FRjt_normUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_FRjt_normUp", "x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_FRjt_normUp");
     h_MC_FRjt_normUp->Write();
     
     TH1F* h_MC_FRjt_normDown = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]+"_gentau");
     h_MC_FRjt_normDown->Add((TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]+"_faketau_CMS_ttHl16_FRjt_normDown"));
     h_MC_FRjt_normDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_FRjt_normDown", "x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_FRjt_normDown");
     h_MC_FRjt_normDown->Write();
     

     TH1F* h_MC_FRjt_shapeUp = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]+"_gentau");
     h_MC_FRjt_shapeUp->Add((TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]+"_faketau_CMS_ttHl16_FRjt_shapeUp"));
     h_MC_FRjt_shapeUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_FRjt_shapeUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_FRjt_shapeUp");
     h_MC_FRjt_shapeUp->Write();
     
     TH1F* h_MC_FRjt_shapeDown = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]+"_gentau");
     h_MC_FRjt_shapeDown->Add((TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]+"_faketau_CMS_ttHl16_FRjt_shapeDown"));
     h_MC_FRjt_shapeDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_FRjt_shapeDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_FRjt_shapeDown");
     h_MC_FRjt_shapeDown->Write();


   }


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


     /*TString h_name_ttZ = "x_ttZ_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_ttG = "x_ttG_CMS_eff_t"+syst_type_tauID[i_syst];
     TString h_name_TTZ = "x_TTZ_CMS_eff_t"+syst_type_tauID[i_syst];
 
     TH1F* h_TTZ = (TH1F*)f_new->Get(h_name_ttZ);
     h_TTZ->Add( (TH1F*)f_new->Get(h_name_ttG) );
     h_TTZ->SetNameTitle(h_name_TTZ,h_name_TTZ);
     h_TTZ->Write();*/
	
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



   for(unsigned int i_t=0;i_t<jetToTau_FR_syst_names.size();i_t++){  

      for(unsigned int i_bkg=0;i_bkg<bkg_type.size();i_bkg++){

        if(bkg_type[i_bkg].Contains("faketau") || bkg_type[i_bkg].Contains("gentau")) continue;

	TString h_name_ttH = "x_ttH"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_ttH+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_ttH+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_ttH+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_ttH+="shapeDown";
        TString h_name_tHq = "x_tHq"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_tHq+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_tHq+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_tHq+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_tHq+="shapeDown";
	TString h_name_tHW = "x_tHW"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_tHW+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_tHW+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_tHW+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_tHW+="shapeDown";
	TString h_name_TTH = "x_TTH"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_TTH+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_TTH+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_TTH+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_TTH+="shapeDown";

		
	TH1F* h_TTH = (TH1F*)f_new->Get(h_name_ttH);
	h_TTH->Add( (TH1F*)f_new->Get(h_name_tHq) );
	h_TTH->Add( (TH1F*)f_new->Get(h_name_tHW) );
	h_TTH->SetNameTitle(h_name_TTH,h_name_TTH);
	h_TTH->Write();

	/*TString h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_ttZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_ttZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_ttZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_ttZ+="shapeDown";
        TString h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_ttG+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_ttG+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_ttG+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_ttG+="shapeDown";
	TString h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_TTZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_TTZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_TTZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_TTZ+="shapeDown";

		
	TH1F* h_TTZ = (TH1F*)f_new->Get(h_name_ttZ);
	h_TTZ->Add( (TH1F*)f_new->Get(h_name_ttG) );
	h_TTZ->SetNameTitle(h_name_TTZ,h_name_TTZ);
	h_TTZ->Write();*/
	
   	TString h_name_WZ = "x_WZ"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_WZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_WZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_WZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_WZ+="shapeDown";
        TString h_name_ZZ = "x_ZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_ZZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_ZZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_ZZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_ZZ+="shapeDown";
         TString h_name_EWK = "x_EWK"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_EWK+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_EWK+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_EWK+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_EWK+="shapeDown";


		
	TH1F* h_EWK = (TH1F*)f_new->Get(h_name_WZ);
	h_EWK->Add( (TH1F*)f_new->Get(h_name_ZZ) );
	h_EWK->SetNameTitle(h_name_EWK,h_name_EWK);
	h_EWK->Write();

	
	TString h_name_WWW = "x_WWW"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_WWW+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_WWW+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_WWW+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_WWW+="shapeDown";
        TString h_name_WWZ = "x_WWZ"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_WWZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_WWZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_WWZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_WWZ+="shapeDown";
        TString h_name_WZZ = "x_WZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_WZZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_WZZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
      h_name_WZZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_WZZ+="shapeDown";
        TString h_name_ZZZ = "x_ZZZ"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_ZZZ+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_ZZZ+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_ZZZ+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_ZZZ+="shapeDown";
    TString h_name_WWss = "x_WWss"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_WWss+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_WWss+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_WWss+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_WWss+="shapeDown";
        TString h_name_tZq = "x_tZq"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_tZq+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_tZq+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_tZq+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_tZq+="shapeDown";
        TString h_name_TTTT = "x_TTTT"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_TTTT+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
	  h_name_TTTT+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_TTTT+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_TTTT+="shapeDown";
	/*TString h_name_ttWW = "x_ttWW"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_ttWW+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
	  h_name_ttWW+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_ttWW+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
	h_name_ttWW+="shapeDown";*/

        TString h_name_Rares = "x_Rares"+bkg_type[i_bkg]+"_CMS_ttHl16_FRjt_";
        if(jetToTau_FR_syst_names[i_t]=="tauNormUp")
          h_name_Rares+="normUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauNormDown")
          h_name_Rares+="normDown";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeUp")
          h_name_Rares+="shapeUp";
        else if(jetToTau_FR_syst_names[i_t]=="tauShapeDown")
          h_name_Rares+="shapeDown";


	
	TH1F* h_Rares = (TH1F*)f_new->Get(h_name_WWW);
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WZZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_ZZZ) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_WWss) );	
	h_Rares->Add( (TH1F*)f_new->Get(h_name_tZq) );
	h_Rares->Add( (TH1F*)f_new->Get(h_name_TTTT) );
	//h_Rares->Add( (TH1F*)f_new->Get(h_name_ttWW) );
	h_Rares->SetNameTitle(h_name_Rares,h_name_Rares);
	h_Rares->Write();
	
      }

    }

   cout<<"OK syst tau fakes"<<endl;



    //Fakes closure
    
    TH1F* h_TT_DL_clos_ele_diff = single_plot(filename_ttbar_DL,
					      "T",
					      var,
					      Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*tauSF_weight_v3*bTagSF_CSVshape_weight*(event_weight_ttH_ele_FR_TT_MC_v2-event_weight_ttH_ele_FR_QCD_MC_v2)*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",
					    nbin,xmin,xmax);
    
    h_TT_DL_clos_ele_diff->Scale(luminosity*XS_ttbar_DL/h_ttbar_DL_norm->Integral());

    TH1F* h_TT_SLfromT_clos_ele_diff = single_plot(filename_ttbar_SLfromT,
                                            "T",
                                            var,
                                              Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*tauSF_weight_v3*bTagSF_CSVshape_weight*(event_weight_ttH_ele_FR_TT_MC_v2-event_weight_ttH_ele_FR_QCD_MC_v2)*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",
                                            nbin,xmin,xmax);

    h_TT_SLfromT_clos_ele_diff->Scale(luminosity*XS_ttbar_SLfromT/h_ttbar_SLfromT_norm->Integral());

    TH1F* h_TT_SLfromTbar_clos_ele_diff = single_plot(filename_ttbar_SLfromTbar,
                                            "T",
                                            var,
                                              Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*tauSF_weight_v3*bTagSF_CSVshape_weight*(event_weight_ttH_ele_FR_TT_MC_v2-event_weight_ttH_ele_FR_QCD_MC_v2)*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",
                                            nbin,xmin,xmax);

    h_TT_SLfromTbar_clos_ele_diff->Scale(luminosity*XS_ttbar_SLfromTbar/h_ttbar_SLfromTbar_norm->Integral());


    TH1F* h_fakes_clos_ele_Up = (TH1F*)h_fakes->Clone();
    h_fakes_clos_ele_Up->Add(h_TT_DL_clos_ele_diff,+1);  
    h_fakes_clos_ele_Up->Add(h_TT_SLfromT_clos_ele_diff,+1);
    h_fakes_clos_ele_Up->Add(h_TT_SLfromTbar_clos_ele_diff,+1);
    h_fakes_clos_ele_Up->Scale(h_fakes->Integral()/h_fakes_clos_ele_Up->Integral());  
    h_fakes_clos_ele_Up->SetNameTitle("x_data_fakes_CMS_ttHl16_Clos_e_shapeUp","x_data_fakes_CMS_ttHl16_Clos_e_shapeUp");
    makeBinContentsPositive(h_fakes_clos_ele_Up);
    h_fakes_clos_ele_Up->Write();


    TH1F* h_fakes_clos_ele_Down = (TH1F*)h_fakes->Clone();
    h_fakes_clos_ele_Down->Add(h_TT_DL_clos_ele_diff,-1);  
    h_fakes_clos_ele_Down->Add(h_TT_SLfromT_clos_ele_diff,-1);
    h_fakes_clos_ele_Down->Add(h_TT_SLfromTbar_clos_ele_diff,-1);
    h_fakes_clos_ele_Down->Scale(h_fakes->Integral()/h_fakes_clos_ele_Down->Integral());  
    h_fakes_clos_ele_Down->SetNameTitle("x_data_fakes_CMS_ttHl16_Clos_e_shapeDown","x_data_fakes_CMS_ttHl16_Clos_e_shapeDown");
    makeBinContentsPositive(h_fakes_clos_ele_Down);
    h_fakes_clos_ele_Down->Write();


   TH1F* h_TT_DL_clos_mu_diff = single_plot(filename_ttbar_DL,
					    "T",
					    var,
					    Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*bTagSF_CSVshape_weight*leptonSF_ttH_weight_v3*tauSF_weight_v3*(event_weight_ttH_mu_FR_TT_MC_v2-event_weight_ttH_mu_FR_QCD_MC_v2)*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",
					    nbin,xmin,xmax);
    
    h_TT_DL_clos_mu_diff->Scale(luminosity*XS_ttbar_DL/h_ttbar_DL_norm->Integral());

   TH1F* h_TT_SLfromT_clos_mu_diff = single_plot(filename_ttbar_SLfromT,
                                            	"T",
                                                var,
						Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*bTagSF_CSVshape_weight*leptonSF_ttH_weight_v3*tauSF_weight_v3*(event_weight_ttH_mu_FR_TT_MC_v2-event_weight_ttH_mu_FR_QCD_MC_v2)*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",
                                           nbin,xmin,xmax);

    h_TT_SLfromT_clos_mu_diff->Scale(luminosity*XS_ttbar_SLfromT/h_ttbar_SLfromT_norm->Integral());

   TH1F* h_TT_SLfromTbar_clos_mu_diff = single_plot(filename_ttbar_SLfromTbar,
                                            "T",
                                            var,
                                            Form("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*bTagSF_CSVshape_weight*leptonSF_ttH_weight_v3*tauSF_weight_v3*(event_weight_ttH_mu_FR_TT_MC_v2-event_weight_ttH_mu_FR_QCD_MC_v2)*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")",                                         
                                            nbin,xmin,xmax);

    h_TT_SLfromTbar_clos_mu_diff->Scale(luminosity*XS_ttbar_SLfromTbar/h_ttbar_SLfromTbar_norm->Integral());

    TH1F* h_fakes_clos_mu_Up = (TH1F*)h_fakes->Clone();
    h_fakes_clos_mu_Up->Add(h_TT_DL_clos_mu_diff,+1);  
    h_fakes_clos_mu_Up->Add(h_TT_SLfromT_clos_mu_diff,+1);
    h_fakes_clos_mu_Up->Add(h_TT_SLfromTbar_clos_mu_diff,+1);
    h_fakes_clos_mu_Up->Scale(h_fakes->Integral()/h_fakes_clos_mu_Up->Integral());  
    h_fakes_clos_mu_Up->SetNameTitle("x_data_fakes_CMS_ttHl16_Clos_m_shapeUp","x_data_fakes_CMS_ttHl16_Clos_m_shapeUp");
    makeBinContentsPositive(h_fakes_clos_mu_Up);
    h_fakes_clos_mu_Up->Write();


    TH1F* h_fakes_clos_mu_Down = (TH1F*)h_fakes->Clone();
    h_fakes_clos_mu_Down->Add(h_TT_DL_clos_mu_diff,-1);  
    h_fakes_clos_mu_Down->Add(h_TT_SLfromT_clos_mu_diff,-1);
    h_fakes_clos_mu_Down->Add(h_TT_SLfromTbar_clos_mu_diff,-1);
    h_fakes_clos_mu_Down->Scale(h_fakes->Integral()/h_fakes_clos_mu_Down->Integral());  
    h_fakes_clos_mu_Down->SetNameTitle("x_data_fakes_CMS_ttHl16_Clos_m_shapeDown","x_data_fakes_CMS_ttHl16_Clos_m_shapeDown");
    makeBinContentsPositive(h_fakes_clos_mu_Down);
    h_fakes_clos_mu_Down->Write();


    cout<<"OK closure syst"<<endl;
   

    //Fakes systematics

    for(unsigned int i_f=0;i_f<fake_syst_names.size();i_f++){

      TString weight = "event_weight_ttH_"+ fake_syst_names[i_f] +"_v2";
      TString cut = weight + Form("*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",cat_fakes[i_cat]) + cut_cat + ")";
      
      TH1F* h_fakes_syst =single_plot(filename_data_lepMVA_CR,
				      "T",
				      var,
				      cut,
				      nbin,xmin,xmax);
      
      h_fakes_syst->Scale(luminosity/35867.); //Data files for 35.9 fb-1
      
      for(unsigned int i_MC=0;i_MC<MC_sample_name.size();i_MC++){
	
	if(MC_sample_name[i_MC]=="ttH" || MC_sample_name[i_MC].Contains("ttbar")) continue;      	
	
	TString MC_weight = "MC_weight";
	if(MC_sample_name[i_MC].Contains("tHq") || MC_sample_name[i_MC].Contains("tHW"))
	  MC_weight += "_tHq_SM_457";
	
        TString MC_cut = MC_weight + "*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*bTagSF_CSVshape_weight_v2*tauSF_weight_v3*"+weight+Form("*(category==%i && isTrig_v2 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && recolep_sel_isGenMatched[0] && recolep_sel_isGenMatched[1] &&",cat_fakes[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat + ")";

	TH1F* h_MC_genmatch = single_plot(filename_lepMVA_CR_MC[i_MC],
                                          "T",
					  var,
					  MC_cut,
					  nbin,xmin,xmax);

        h_MC_genmatch->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
        h_fakes_syst->Add(h_MC_genmatch,-1);
      }


	 TString h_name = "x_data_fakes";
	 if(fake_syst_names[i_f]=="ele_up")
	     h_name+="_CMS_ttHl16_FRe_normUp";
	 else if(fake_syst_names[i_f]=="ele_down")
             h_name+="_CMS_ttHl16_FRe_normDown";	 
	 else if(fake_syst_names[i_f]=="ele_pt1")
             h_name+="_CMS_ttHl16_FRe_ptUp";
	 else if(fake_syst_names[i_f]=="ele_pt2")
             h_name+="_CMS_ttHl16_FRe_ptDown";
	 else if(fake_syst_names[i_f]=="ele_b1")
             h_name+="_CMS_ttHl16_FRe_bUp";
         else if(fake_syst_names[i_f]=="ele_b2")
             h_name+="_CMS_ttHl16_FRe_bDown";
	 else if(fake_syst_names[i_f]=="ele_ec1")
             h_name+="_CMS_ttHl16_FRe_ecUp";
         else if(fake_syst_names[i_f]=="ele_ec2")
             h_name+="_CMS_ttHl16_FRe_ecDown";
	 else if(fake_syst_names[i_f]=="ele_be1")
             h_name+="_CMS_ttHl16_FRe_beUp";
         else if(fake_syst_names[i_f]=="ele_be2")
             h_name+="_CMS_ttHl16_FRe_beDown";
	 
         else if(fake_syst_names[i_f]=="mu_up")
             h_name+="_CMS_ttHl16_FRm_normUp";
         else if(fake_syst_names[i_f]=="mu_down")
             h_name+="_CMS_ttHl16_FRm_normDown";
         else if(fake_syst_names[i_f]=="mu_pt1")
             h_name+="_CMS_ttHl16_FRm_ptUp";
         else if(fake_syst_names[i_f]=="mu_pt2")
             h_name+="_CMS_ttHl16_FRm_ptDown";
         else if(fake_syst_names[i_f]=="mu_b1")
             h_name+="_CMS_ttHl16_FRm_bUp";
         else if(fake_syst_names[i_f]=="mu_b2")
             h_name+="_CMS_ttHl16_FRm_bDown";
         else if(fake_syst_names[i_f]=="mu_ec1")
             h_name+="_CMS_ttHl16_FRm_ecUp";
         else if(fake_syst_names[i_f]=="mu_ec2")
             h_name+="_CMS_ttHl16_FRm_ecDown";
	 else if(fake_syst_names[i_f]=="mu_be1")
             h_name+="_CMS_ttHl16_FRm_beUp";
         else if(fake_syst_names[i_f]=="mu_be2")
             h_name+="_CMS_ttHl16_FRm_beDown";

	 if(!fake_syst_names[i_f].Contains("up") && !fake_syst_names[i_f].Contains("down"))
	    h_fakes_syst->Scale(h_fakes->Integral()/h_fakes_syst->Integral()); 

         h_fakes_syst->SetNameTitle(h_name,h_name);
         makeBinContentsPositive(h_fakes_syst);
         h_fakes_syst->Write();

    }





    cout<<"OK fake lep syst"<<endl;


    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      TString MC_weight = "MC_weight";
      if(MC_sample_name[i_MC].Contains("tHq") || MC_sample_name[i_MC].Contains("tHW"))
	MC_weight += "_tHq_SM_457";

      TString cut = MC_weight + Form("*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v3*bTagSF_CSVshape_weight_v2*tauSF_weight_v3*(category==%i && isTrig_v2 &&",cat[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat;

      TH1F* h_MC_ee = single_plot(filename_MC[i_MC],
			       "T",
			       var,			    
			       cut + "&& (abs(recolep_sel_pdg[0])+abs(recolep_sel_pdg[1]))==22)",
			       nbin,xmin,xmax);

      TH1F* h_MC_em = single_plot(filename_MC[i_MC],
			       "T",
			       var,			    
			       cut + "&& (abs(recolep_sel_pdg[0])+abs(recolep_sel_pdg[1]))==24)",
			       nbin,xmin,xmax);

      TH1F* h_MC_mm = single_plot(filename_MC[i_MC],
			       "T",
			       var,			    
			       cut + "&& (abs(recolep_sel_pdg[0])+abs(recolep_sel_pdg[1]))==26)",
			       nbin,xmin,xmax);

      h_MC_mm->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_em->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);
      h_MC_ee->Scale(luminosity*XS[i_MC]/norm_MC[i_MC]);

      TH1F* h_MC_lepEff_eltightUp = (TH1F*) h_MC_mm->Clone();
      h_MC_lepEff_eltightUp->Add(h_MC_em,1.03);
      h_MC_lepEff_eltightUp->Add(h_MC_ee,1.06);
      h_MC_lepEff_eltightUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_eltightUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_eltightUp");
      makeBinContentsPositive(h_MC_lepEff_eltightUp);
      h_MC_lepEff_eltightUp->Write();

      TH1F* h_MC_lepEff_eltightDown = (TH1F*) h_MC_mm->Clone();
      h_MC_lepEff_eltightDown->Add(h_MC_em,0.97);
      h_MC_lepEff_eltightDown->Add(h_MC_ee,0.94);
      h_MC_lepEff_eltightDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_eltightDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_eltightDown");
      makeBinContentsPositive(h_MC_lepEff_eltightDown);
      h_MC_lepEff_eltightDown->Write();

      TH1F* h_MC_lepEff_mutightUp = (TH1F*) h_MC_ee->Clone();
      h_MC_lepEff_mutightUp->Add(h_MC_em,1.03);
      h_MC_lepEff_mutightUp->Add(h_MC_mm,1.06);
      h_MC_lepEff_mutightUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mutightUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mutightUp");
      makeBinContentsPositive(h_MC_lepEff_mutightUp);
      h_MC_lepEff_mutightUp->Write();

      TH1F* h_MC_lepEff_mutightDown = (TH1F*) h_MC_ee->Clone();
      h_MC_lepEff_mutightDown->Add(h_MC_em,0.97);
      h_MC_lepEff_mutightDown->Add(h_MC_mm,0.94);
      h_MC_lepEff_mutightDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mutightDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mutightDown");
      makeBinContentsPositive(h_MC_lepEff_mutightDown);
      h_MC_lepEff_mutightDown->Write();

      TH1F* h_MC_lepEff_ellooseUp = (TH1F*) h_MC_mm->Clone();
      h_MC_lepEff_ellooseUp->Add(h_MC_em,1.02);
      h_MC_lepEff_ellooseUp->Add(h_MC_ee,1.04);
      h_MC_lepEff_ellooseUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_ellooseUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_ellooseUp");
      makeBinContentsPositive(h_MC_lepEff_ellooseUp);
      h_MC_lepEff_ellooseUp->Write();

      TH1F* h_MC_lepEff_ellooseDown = (TH1F*) h_MC_mm->Clone();
      h_MC_lepEff_ellooseDown->Add(h_MC_em,0.98);
      h_MC_lepEff_ellooseDown->Add(h_MC_ee,0.96);
      h_MC_lepEff_ellooseDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_ellooseDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_ellooseDown");
      makeBinContentsPositive(h_MC_lepEff_ellooseDown);
      h_MC_lepEff_ellooseDown->Write();

      TH1F* h_MC_lepEff_mulooseUp = (TH1F*) h_MC_ee->Clone();
      h_MC_lepEff_mulooseUp->Add(h_MC_em,1.02);
      h_MC_lepEff_mulooseUp->Add(h_MC_mm,1.04);
      h_MC_lepEff_mulooseUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mulooseUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mulooseUp");
      makeBinContentsPositive(h_MC_lepEff_mulooseUp);
      h_MC_lepEff_mulooseUp->Write();

      TH1F* h_MC_lepEff_mulooseDown = (TH1F*) h_MC_ee->Clone();
      h_MC_lepEff_mulooseDown->Add(h_MC_em,0.98);
      h_MC_lepEff_mulooseDown->Add(h_MC_mm,0.96);
      h_MC_lepEff_mulooseDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mulooseDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_lepEff_mulooseDown");
      makeBinContentsPositive(h_MC_lepEff_mulooseDown);
      h_MC_lepEff_mulooseDown->Write();


      TH1F* h_MC_trigger_eeUp = (TH1F*) h_MC_mm->Clone();
      h_MC_trigger_eeUp->Add(h_MC_em);
      h_MC_trigger_eeUp->Add(h_MC_ee,1.02);
      h_MC_trigger_eeUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_trigger_eeUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_trigger_eeUp");
      makeBinContentsPositive(h_MC_trigger_eeUp);
      h_MC_trigger_eeUp->Write();

      TH1F* h_MC_trigger_eeDown = (TH1F*) h_MC_mm->Clone();
      h_MC_trigger_eeDown->Add(h_MC_em);
      h_MC_trigger_eeDown->Add(h_MC_ee,0.98);
      h_MC_trigger_eeDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_trigger_eeDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_trigger_eeDown");
      makeBinContentsPositive(h_MC_trigger_eeDown);
      h_MC_trigger_eeDown->Write();

      TH1F* h_MC_trigger_emUp = (TH1F*) h_MC_mm->Clone();
      h_MC_trigger_emUp->Add(h_MC_ee);
      h_MC_trigger_emUp->Add(h_MC_em,1.01);
      h_MC_trigger_emUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_trigger_emUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_trigger_emUp");
      makeBinContentsPositive(h_MC_trigger_emUp);
      h_MC_trigger_emUp->Write();

      TH1F* h_MC_trigger_emDown = (TH1F*) h_MC_mm->Clone();
      h_MC_trigger_emDown->Add(h_MC_ee);
      h_MC_trigger_emDown->Add(h_MC_em,0.99);
      h_MC_trigger_emDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_trigger_emDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_trigger_emDown");
      makeBinContentsPositive(h_MC_trigger_emDown);
      h_MC_trigger_emDown->Write();

      TH1F* h_MC_trigger_mmUp = (TH1F*) h_MC_ee->Clone();
      h_MC_trigger_mmUp->Add(h_MC_em);
      h_MC_trigger_mmUp->Add(h_MC_mm,1.01);
      h_MC_trigger_mmUp->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_trigger_mmUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_trigger_mmUp");
      makeBinContentsPositive(h_MC_trigger_mmUp);
      h_MC_trigger_mmUp->Write();

      TH1F* h_MC_trigger_mmDown = (TH1F*) h_MC_ee->Clone();
      h_MC_trigger_mmDown->Add(h_MC_em);
      h_MC_trigger_mmDown->Add(h_MC_mm,0.99);
      h_MC_trigger_mmDown->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_trigger_mmDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHl16_trigger_mmDown");
      makeBinContentsPositive(h_MC_trigger_mmDown);
      h_MC_trigger_mmDown->Write();


    }



    vector<TString> lepEff_syst;
    lepEff_syst.push_back("ttHl16_lepEff_eltightUp");
    lepEff_syst.push_back("ttHl16_lepEff_eltightDown");
    lepEff_syst.push_back("ttHl16_lepEff_mutightUp");
    lepEff_syst.push_back("ttHl16_lepEff_mutightDown");
    lepEff_syst.push_back("ttHl16_lepEff_ellooseUp");
    lepEff_syst.push_back("ttHl16_lepEff_ellooseDown");
    lepEff_syst.push_back("ttHl16_lepEff_mulooseUp");
    lepEff_syst.push_back("ttHl16_lepEff_mulooseDown");
    lepEff_syst.push_back("ttHl16_trigger_eeUp");
    lepEff_syst.push_back("ttHl16_trigger_eeDown");
    lepEff_syst.push_back("ttHl16_trigger_emUp");
    lepEff_syst.push_back("ttHl16_trigger_emDown");
    lepEff_syst.push_back("ttHl16_trigger_mmUp");
    lepEff_syst.push_back("ttHl16_trigger_mmDown");

    for(unsigned int i=0;i<lepEff_syst.size();i++){

      TString h_name_ttH = "x_ttH_CMS_"+lepEff_syst[i];
      TString h_name_tHq = "x_tHq_CMS_"+lepEff_syst[i];
      TString h_name_tHW = "x_tHW_CMS_"+lepEff_syst[i];
      TString h_name_TTH = "x_TTH_CMS_"+lepEff_syst[i];

      TH1F* h_TTH = (TH1F*)f_new->Get(h_name_ttH)->Clone();
      h_TTH->Add( (TH1F*)f_new->Get(h_name_tHq) );
      h_TTH->Add( (TH1F*)f_new->Get(h_name_tHW) );
      h_TTH->SetNameTitle(h_name_TTH,h_name_TTH);
      h_TTH->Write();
            

      /*TString h_name_ttZ = "x_ttZ"+bkg_type[i_bkg]+"_CMS_ttHl_"+lepEff_syst[i];
      TString h_name_ttG = "x_ttG"+bkg_type[i_bkg]+"_CMS_ttHl_"+lepEff_syst[i];
      TString h_name_TTZ = "x_TTZ"+bkg_type[i_bkg]+"_CMS_ttHl_"+lepEff_syst[i];

      TH1F* h_TTZ = (TH1F*)f_new->Get(h_name_ttZ)->Clone();
      h_TTZ->Add( (TH1F*)f_new->Get(h_name_ttG) );
      h_TTZ->SetNameTitle(h_name_TTZ,h_name_TTZ);
      h_TTZ->Write();*/

      TString h_name_WZ = "x_WZ_CMS_"+lepEff_syst[i];
      TString h_name_ZZ = "x_ZZ_CMS_"+lepEff_syst[i];
      TString h_name_EWK = "x_EWK_CMS_"+lepEff_syst[i];
      
      TH1F* h_EWK = (TH1F*)f_new->Get(h_name_WZ)->Clone();
      h_EWK->Add( (TH1F*)f_new->Get(h_name_ZZ) );
      h_EWK->SetNameTitle(h_name_EWK,h_name_EWK);
      h_EWK->Write();
      

      TString h_name_WWW = "x_WWW_CMS_"+lepEff_syst[i];
      TString h_name_WWZ = "x_WWZ_CMS_"+lepEff_syst[i];
      TString h_name_WZZ = "x_WZZ_CMS_"+lepEff_syst[i];
      TString h_name_ZZZ = "x_ZZZ_CMS_"+lepEff_syst[i];
      TString h_name_tZq = "x_tZq_CMS_"+lepEff_syst[i];
      TString h_name_TTTT = "x_TTTT_CMS_"+lepEff_syst[i];
      TString h_name_WWss = "x_WWss_CMS_"+lepEff_syst[i];
      TString h_name_Rares = "x_Rares_CMS_"+lepEff_syst[i];

      TH1F* h_Rares = (TH1F*)f_new->Get(h_name_WWW)->Clone();
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


    cout<<"OK syst lepEff tight"<<endl;




  }


  f_new->Close();
  return;

}









void datacard_maker_MEM_2lSS_nomiss_syst(){

  TString var="Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;

  TString cut = "integration_type==0";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards_ttH_comb/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_042017.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file,true,"2lss_1tau_nomiss");


}








void datacard_maker_MEM_2lSS_missing_syst(){

  TString var="Integral_ttH/(Integral_ttH+5e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+5e-1*Integral_ttZ_Zll)";
  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;

  TString cut = "integration_type==1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards_ttH_comb/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_042017.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file,true,"2lss_1tau_missing");


}








void datacard_maker_BDTMEM_2lSS_syst(){

  TString var="MVA_2lSS1tau_MEM_LR_2Dbin";
  
  int nbin = 8;
  float xmin = 0.;
  float xmax = 8.;

  TString cut = "1";


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards_ttH_comb/datacard_MVA_2lSS1tau_MEM_ttH_vs_full_bkg_2lSS_nofaketau_35.9fb_042017.root";


  datacard_maker(var,nbin,xmin,xmax,cut,file,true,"2lss_1tau");


}
