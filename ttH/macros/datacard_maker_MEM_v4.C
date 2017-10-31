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
float XS_ZZJJ = 0.0004404;


vector<float> XS;

//MC

TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root";
TString filename_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttW*PU.root";
TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root";
TString filename_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/EWK/WZ_split_2lSS_MEM_PU.root";

TString filename_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/TTbar/TTbar_DL_split_2lSS_lepMVA_CR_MEM_PU_FR_clos.root";

TString filename_norm_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_PU_ttH_Hnonbb.root";
TString filename_norm_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttV/ntuple_PU_ttW_*.root";
TString filename_norm_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttV/ntuple_PU_ttZ.root";
TString filename_norm_WZ = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/EWK/ntuple_PU_WZ.root";

TString filename_norm_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_DL.root";



vector<TString> filename_MC;
vector<TString> filename_norm_MC;




//Data

TString filename_fake_DoubleEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_*.root";
TString filename_fake_MuonEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_*.root";
TString filename_fake_DoubleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_*.root";
TString filename_fake_SingleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/SingleMu_2016B_split_2lSS_lepMVA_CR_*.root";
TString filename_fake_SingleEle_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_*.root";

TString filename_fake_DoubleEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_*.root";
TString filename_fake_MuonEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_*.root";
TString filename_fake_DoubleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_*.root";
TString filename_fake_SingleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/SingleMu_2016C_split_2lSS_lepMVA_CR_*.root";
TString filename_fake_SingleEle_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_*.root";

TString filename_fake_DoubleEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/DoubleEG_2016D_split_2lSS_lepMVA_CR_*.root";
TString filename_fake_MuonEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/MuonEG_2016D_split_2lSS_lepMVA_CR_*.root";
TString filename_fake_DoubleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/DoubleMu_2016D_split_2lSS_lepMVA_CR_*.root";
TString filename_fake_SingleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/SingleMu_2016D_split_2lSS_lepMVA_CR_*.root";
TString filename_fake_SingleEle_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/SingleEle_2016D_split_2lSS_lepMVA_CR_*.root";


TString filename_flip_DoubleEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/DoubleEG_2016B_split_2lOS_CR_*.root";
TString filename_flip_MuonEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/MuonEG_2016B_split_2lOS_CR_*.root";
TString filename_flip_DoubleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/DoubleMu_2016B_split_2lOS_CR_*.root";
TString filename_flip_SingleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/SingleMu_2016B_split_2lOS_CR_*.root";
TString filename_flip_SingleEle_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/SingleEle_2016B_split_2lOS_CR_*.root";
		 
TString filename_flip_DoubleEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/DoubleEG_2016C_split_2lOS_CR_*.root";
TString filename_flip_MuonEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/MuonEG_2016C_split_2lOS_CR_*.root";
TString filename_flip_DoubleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/DoubleMu_2016C_split_2lOS_CR_*.root";
TString filename_flip_SingleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/SingleMu_2016C_split_2lOS_CR_*.root";
TString filename_flip_SingleEle_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/SingleEle_2016C_split_2lOS_CR_*.root";
		 
TString filename_flip_DoubleEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/DoubleEG_2016D_split_2lOS_CR_*.root";
TString filename_flip_MuonEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/MuonEG_2016D_split_2lOS_CR_*.root";
TString filename_flip_DoubleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/DoubleMu_2016D_split_2lOS_CR_*.root";
TString filename_flip_SingleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/SingleMu_2016D_split_2lOS_CR_*.root";
TString filename_flip_SingleEle_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/Data/SingleEle_2016D_split_2lOS_CR_*.root";


vector<TString> filename_data_fake;
vector<TString> filename_data_flip;

vector<TString> MC_sample_name;
vector<TString> MC_sample_cut;

vector<TString> filename_MC_thu_unc;
vector<TString> MC_sample_name_thu_unc;
vector<TString> MC_sample_cut_thu_unc;


// MC JEC + TES

TString filename_ttH_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/JECup/ttH/ttH_Hnonbb_split_JECup_2lSS_MEM_PU_genH.root";
TString filename_ttH_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/JECdown/ttH/ttH_Hnonbb_split_JECdown_2lSS_MEM_PU_genH.root";
TString filename_ttH_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESup/ttH/ttH_Hnonbb_split_TESup_2lSS_MEM_PU_genH.root";
TString filename_ttH_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/ttH/ttH_Hnonbb_split_TESdown_2lSS_MEM_PU_genH.root";


TString filename_ttZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/JECup/ttV/ttZ_split_JECup_2lSS_MEM_PU_MCweight.root";
TString filename_ttZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/JECdown/ttV/ttZ_split_JECdown_2lSS_MEM_PU_MCweight.root";
TString filename_ttZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESup/ttV/ttZ_split_TESup_2lSS_MEM_PU_MCweight.root";
TString filename_ttZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/ttV/ttZ_split_TESdown_2lSS_MEM_PU_MCweight.root";


TString filename_ttW_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/JECup/ttV/ttW_*split_JECup_2lSS_MEM_PU_MCweight.root";
TString filename_ttW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/JECdown/ttV/ttW_*split_JECdown_2lSS_MEM_PU_MCweight.root";
TString filename_ttW_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESup/ttV/ttW_*split_TESup_2lSS_MEM_PU_MCweight.root";
TString filename_ttW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/ttV/ttW_*split_TESdown_2lSS_MEM_PU_MCweight.root";

TString filename_WZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/JECup/EWK/WZ_split_JECup_2lSS_MEM_PU_MCweight.root";
TString filename_WZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/JECdown/EWK/WZ_split_JECdown_2lSS_MEM_PU_MCweight.root";
TString filename_WZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESup/EWK/WZ_split_TESup_2lSS_MEM_PU_MCweight.root";
TString filename_WZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/TESdown/EWK/WZ_split_TESdown_2lSS_MEM_PU_MCweight.root";


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
  filename_data_fake.clear();
  filename_data_flip.clear();

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
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  /*XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_genmatch");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);*/

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH_fake");
  MC_sample_cut.push_back("!isGenMatched");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

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


  XS.push_back(XS_WZ);
  filename_MC.push_back(filename_WZ);
  filename_norm_MC.push_back(filename_norm_WZ);
  MC_sample_name.push_back("EWK");
  MC_sample_cut.push_back("isGenMatched");
  filename_MC_JECup.push_back(filename_WZ_JECup);
  filename_MC_JECdown.push_back(filename_WZ_JECdown);
  filename_MC_TESup.push_back(filename_WZ_TESup);
  filename_MC_TESdown.push_back(filename_WZ_TESdown);



  filename_data_fake.push_back(filename_fake_DoubleEG_2016B);
  filename_data_fake.push_back(filename_fake_MuonEG_2016B);
  filename_data_fake.push_back(filename_fake_DoubleMu_2016B);
  filename_data_fake.push_back(filename_fake_SingleMu_2016B);
  filename_data_fake.push_back(filename_fake_SingleEle_2016B);

  filename_data_fake.push_back(filename_fake_DoubleEG_2016C);
  filename_data_fake.push_back(filename_fake_MuonEG_2016C);
  filename_data_fake.push_back(filename_fake_DoubleMu_2016C);
  filename_data_fake.push_back(filename_fake_SingleMu_2016C);
  filename_data_fake.push_back(filename_fake_SingleEle_2016C);

  filename_data_fake.push_back(filename_fake_DoubleEG_2016D);
  filename_data_fake.push_back(filename_fake_MuonEG_2016D);
  filename_data_fake.push_back(filename_fake_DoubleMu_2016D);
  filename_data_fake.push_back(filename_fake_SingleMu_2016D);
  filename_data_fake.push_back(filename_fake_SingleEle_2016D);


  filename_data_flip.push_back(filename_flip_DoubleEG_2016B);
  filename_data_flip.push_back(filename_flip_MuonEG_2016B);
  filename_data_flip.push_back(filename_flip_DoubleMu_2016B);
  filename_data_flip.push_back(filename_flip_SingleMu_2016B);
  filename_data_flip.push_back(filename_flip_SingleEle_2016B);

  filename_data_flip.push_back(filename_flip_DoubleEG_2016C);
  filename_data_flip.push_back(filename_flip_MuonEG_2016C);
  filename_data_flip.push_back(filename_flip_DoubleMu_2016C);
  filename_data_flip.push_back(filename_flip_SingleMu_2016C);
  filename_data_flip.push_back(filename_flip_SingleEle_2016C);

  filename_data_flip.push_back(filename_flip_DoubleEG_2016D);
  filename_data_flip.push_back(filename_flip_MuonEG_2016D);
  filename_data_flip.push_back(filename_flip_DoubleMu_2016D);
  filename_data_flip.push_back(filename_flip_SingleMu_2016D);
  filename_data_flip.push_back(filename_flip_SingleEle_2016D);



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







void datacard_maker(TString var, int nbin, float xmin, float xmax,
		    TString cut_cat, TString file, bool syst=false, TString cat_name=""){



  initialize();


  
  //vector<TString> cat_names;
  //cat_names.push_back("ttH_2lss_1tau");


  vector<int> cat;
  cat.push_back(11);

  vector<int> cat_flips;
  vector<int> cat_fakes;
  for(unsigned int i=0;i<cat.size();i++){
    cat_flips.push_back(-1*cat[i]);
    cat_fakes.push_back(30+cat[i]);
  }
  
  TFile* f_new = TFile::Open(file,"RECREATE");
  


  for(unsigned int i_cat=0;i_cat<cat.size();i_cat++){

    //cout<<cat_names[i_cat]<<endl;

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
			       "T",
			       var,
			       Form("MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==%i && isTrig &&",cat[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat + ")",
			       nbin,xmin,xmax);

      
      TH1F* h_MC_norm = single_plot(filename_norm_MC[i_MC],
				    "HTauTauTree",
				    "1",
				    "MC_weight*PU_weight_ICHEP",
				    3,0,3);


      h_MC->Scale(luminosity*XS[i_MC]/h_MC_norm->Integral());
      h_MC->SetNameTitle("x_"+MC_sample_name[i_MC],"x_"+MC_sample_name[i_MC]);
      h_MC->Write();


    }


    
    //Fakes
    
    TH1F* h_fakes =single_plot(filename_data_fake,
			       "T",
			       var,
			       Form("event_weight_ttH*(category==%i && isTrig && ",cat_fakes[i_cat]) + cut_cat + ")",
			       nbin,xmin,xmax);
    
    h_fakes->Scale(luminosity/12900.); //Data files for 12.9 fb-1
    //h_fakes->Add((TH1F*)f_new->Get("x_ttH_fake"),-1);
    h_fakes->SetNameTitle("x_fakes_data","x_fakes_data");
    h_fakes->Write();


    //Fakes MC
    
    TH1F* h_ttbar_DL_fakes_MC =single_plot(filename_ttbar_DL,
				  "T",
				  var,
				  Form("MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*event_weight_ttH*(category==%i && isTrig && ",cat_fakes[i_cat]) + cut_cat + ")",
				  nbin,xmin,xmax);
    
    TH1F* h_ttbar_DL_norm =single_plot(filename_norm_ttbar_DL,
				       "HTauTauTree",
				       "1",
				       "MC_weight*PU_weight_ICHEP",
				       3,0,3);
 
    h_ttbar_DL_fakes_MC->Scale(luminosity*XS_ttbar_DL/h_ttbar_DL_norm->Integral());
    h_ttbar_DL_fakes_MC->SetNameTitle("x_fakes_MC","x_fakes_MC");
    h_ttbar_DL_fakes_MC->Write();



    //Charge flips
    TH1F* h_flips =single_plot(filename_data_flip,
			       "T",
			       var,
			       Form("event_weight_ttH*(category==%i && isTrig && ",cat_flips[i_cat]) + cut_cat + ")",
			       nbin,xmin,xmax);
    
    cout<<"h_flips->GetEntries()="<<h_flips->GetEntries()<<endl;

    h_flips->Scale(luminosity/12900.); //Data files for 12.9 fb-1
    h_flips->SetNameTitle("x_flips_data","x_flips_data");
    h_flips->Write();
 
    
    
    //Data
    
    /*TH1F* h_data_obs =single_plot(filename_data,
      "HTauTauTree_2lSS",
      var,
      Form("(category==%i && isTrig)",cat[i]),		
      nbin,xmin,xmax);
      
      h_data_obs->Scale(luminosity/12900.); //Data files for 12.9 fb-1
      
      h_data_obs->SetNameTitle("x_data_obs","x_data_obs");
      h_data_obs->Write();
      h.push_back(h_data_obs);*/


    TH1F* h_data_obs = (TH1F*)f_new->Get("x_ttH");
    h_data_obs->Add( (TH1F*)f_new->Get("x_TTW") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_TTZ") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_EWK") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_fakes_data") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_flips_data") );
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

      float norm = ((TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]))->Integral();

      for(unsigned int i_b=0;i_b<bTag_syst_names.size();i_b++){       
		    
	TString cut = "MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight_" + bTag_syst_names[i_b];
	cut+=Form("*(category==%i && isTrig &&",cat[i_cat]) + MC_sample_cut[i_MC] + " && " + cut_cat + ")";

	TH1F* h_MC_btag_syst = single_plot(filename_MC[i_MC],
					   "T",
					   var,
					   cut,
					   nbin,xmin,xmax);
      
	h_MC_btag_syst->Scale(norm/h_MC_btag_syst->Integral());

	TString h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHt_btag_"+bTag_syst_names[i_b];
	if(bTag_syst_names[i_b]=="CFErr1")
	  h_name = "x_"+MC_sample_name[i_MC]+"_btag_cErr1";
	else if(bTag_syst_names[i_b]=="CFErr2")
	  h_name = "x_"+MC_sample_name[i_MC]+"_btag_cErr2";

	h_MC_btag_syst->SetNameTitle(h_name,h_name);
	h_MC_btag_syst->Write();

      }

    }


    cout<<"OK syst btag"<<endl;



    for(unsigned i_MC=0;i_MC<MC_sample_name_thu_unc.size();i_MC++){

      TString syst_name="CMS_ttHt_thu_shape_";
      if(MC_sample_name_thu_unc[i_MC].Contains("ttH"))
	syst_name+="ttH";
      else
	syst_name+=MC_sample_name_thu_unc[i_MC];


      float norm = ((TH1F*)f_new->Get("x_"+MC_sample_name_thu_unc[i_MC]))->Integral();
		    
      TString cut = "PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight";
      cut+=Form("*(category==%i && isTrig && ",cat[i_cat]) + MC_sample_cut_thu_unc[i_MC] + " && " + cut_cat + ")";

      TH1F* h_MC_x1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "T",
				     var,
				     "MC_weight_scale_muR2*"+cut,
				     nbin,xmin,xmax);
      
      h_MC_x1_up->Scale(norm/h_MC_x1_up->Integral());
      h_MC_x1_up->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Up","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Up");
      h_MC_x1_up->Write();

      TH1F* h_MC_x1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "T",
				       var,
				       "MC_weight_scale_muR0p5*"+cut,
				       nbin,xmin,xmax);
      
      h_MC_x1_down->Scale(norm/h_MC_x1_down->Integral());
      h_MC_x1_down->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Down","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_x1Down");
      h_MC_x1_down->Write();

      TH1F* h_MC_y1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "T",
				     var,
				     "MC_weight_scale_muF2*"+cut,
				     nbin,xmin,xmax);
      
      h_MC_y1_up->Scale(norm/h_MC_y1_up->Integral());
      h_MC_y1_up->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Up", "x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Up");
      h_MC_y1_up->Write();

      TH1F* h_MC_y1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "T",
				       var,
				       "MC_weight_scale_muF0p5*"+cut,
				       nbin,xmin,xmax);
      
      h_MC_y1_down->Scale(norm/h_MC_y1_down->Integral());
      h_MC_y1_down->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Down","x_"+MC_sample_name_thu_unc[i_MC]+"_"+syst_name+"_y1Down");
      h_MC_y1_down->Write();
      
 

    }


    cout<<"OK syst theoretical "<<endl;


    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){
      
      TString cut = "MC_weight2*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight";
      cut+=Form("*(category==%i && isTrig &&",cat[i_cat]) + MC_sample_cut[i_MC]  + " && " + cut_cat + ")";

      float norm = ((TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]))->Integral();
      
      TH1F* h_MC_JEC_up = single_plot(filename_MC_JECup[i_MC],
				      "T",
				      var,
				      cut,
				      nbin,xmin,xmax);
      
      h_MC_JEC_up->Scale(norm/h_MC_JEC_up->Integral());
      h_MC_JEC_up->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHt_JESUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHt_JESUp");
      h_MC_JEC_up->Write();

      
      TH1F* h_MC_JEC_down = single_plot(filename_MC_JECdown[i_MC],
					"T",
					var,
					cut,
					nbin,xmin,xmax);
      
      h_MC_JEC_down->Scale(norm/h_MC_JEC_down->Integral());
      h_MC_JEC_down->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHt_JESDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHt_JESDown");
      h_MC_JEC_down->Write();

      TH1F* h_MC_TES_up = single_plot(filename_MC_TESup[i_MC],
				      "T",
				      var,
				      cut,
				      nbin,xmin,xmax);
      
      h_MC_TES_up->Scale(norm/h_MC_TES_up->Integral());
      h_MC_TES_up->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHt_TESUp","x_"+MC_sample_name[i_MC]+"_CMS_ttHt_TESUp");
      h_MC_TES_up->Write();

      
      TH1F* h_MC_TES_down = single_plot(filename_MC_TESdown[i_MC],
					"T",
					var,
					cut,
					nbin,xmin,xmax);
      h_MC_TES_down->Scale(norm/h_MC_TES_down->Integral());
      h_MC_TES_down->SetNameTitle("x_"+MC_sample_name[i_MC]+"_CMS_ttHt_TESDown","x_"+MC_sample_name[i_MC]+"_CMS_ttHt_TESDown");
      h_MC_TES_down->Write();

    }

    cout<<"OK JEC/TES "<<endl;


   //Bin-by-bin uncertainty
    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      TH1F* h_MC = (TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]);
      
      for(unsigned int i_bin=0;i_bin<=h_MC->GetNbinsX();i_bin++){
	
	double bin_content = h_MC->GetBinContent(i_bin);
	double bin_error = h_MC->GetBinError(i_bin);

	if(bin_error/bin_content>0.05){

	  TString h_name = "x_"+MC_sample_name[i_MC]+"_CMS_ttHt_templstat_"+cat_name+"_"+MC_sample_name[i_MC]+Form("_bin%i",i_bin);

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

          
    for(unsigned int i_bin=0;i_bin<=h_fakes->GetNbinsX();i_bin++){
	
      double bin_content = h_fakes->GetBinContent(i_bin);
      double bin_error = h_fakes->GetBinError(i_bin);

      if(bin_error/bin_content>0.05){

	TString h_name = Form("x_fakes_data_CMS_ttHt_templstat_"+cat_name+"_fakes_bin%i",i_bin);

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


    for(unsigned int i_bin=0;i_bin<=h_flips->GetNbinsX();i_bin++){
	
      double bin_content = h_flips->GetBinContent(i_bin);
      double bin_error = h_flips->GetBinError(i_bin);

      if(bin_error/bin_content>0.05){

	TString h_name = Form("x_flips_data_CMS_ttHt_templstat_"+cat_name+"_flips_bin%i",i_bin);

	TH1F* h_flips_bin_up = (TH1F*)h_flips->Clone();
	h_flips_bin_up->SetBinContent(i_bin,bin_content+bin_error);
	h_flips_bin_up->Scale(h_flips->Integral()/h_flips_bin_up->Integral());
	h_flips_bin_up->SetNameTitle(h_name+"Up",h_name+"Up");
	h_flips_bin_up->Write();

	TH1F* h_flips_bin_down = (TH1F*)h_flips->Clone();
	h_flips_bin_down->SetBinContent(i_bin,bin_content-bin_error);
	h_flips_bin_down->Scale(h_flips->Integral()/h_flips_bin_down->Integral());
	h_flips_bin_down->SetNameTitle(h_name+"Down",h_name+"Down");
	h_flips_bin_down->Write();
	
      }
      
    }
    

    cout<<"OK bin-by-bin"<<endl;



  //Fakes closure
    
    TH1F* h_TT_DL_clos_ele_diff = single_plot(filename_ttbar_DL,
					      "T",
					      var,
					      Form("MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(event_weight_ttH_ele_FR_TT_MC-event_weight_ttH_ele_FR_QCD_MC)*(category==%i && isTrig && ",cat_fakes[i_cat]) + cut_cat + ")",
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
					    "T",
					    var,
					    Form("MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(event_weight_ttH_mu_FR_TT_MC-event_weight_ttH_mu_FR_QCD_MC)*(category==%i && isTrig && ",cat_fakes[i_cat]) + cut_cat + ")",
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









void datacard_maker_MEM_ttH_vs_full_bkg_2lSS_nomiss(){

  TString var="Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)";
  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;

  TString cut="integration_type==0";
  TString cat_name="2lss_1tau_nomiss";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_12.9fb_112016.root";

  datacard_maker(var,nbin,xmin,xmax,cut,file,true);


}




void datacard_maker_MEM_ttH_vs_full_bkg_2lSS_missing(){

  TString var="Integral_ttH/(Integral_ttH+5e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+5e-1*Integral_ttZ_Zll)";
  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;

  TString cut="integration_type==1";
  TString cat_name="2lss_1tau_missing";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_12.9fb_112016.root";

  datacard_maker(var,nbin,xmin,xmax,cut,file,true);


}




void datacard_maker_MEM_ttH_vs_full_bkg_2lSS_nomiss_missing(){

  TString var="Integral_ttH/(Integral_ttH+1e-18*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+1e-1*Integral_ttZ+2e-1*Integral_ttZ_Zll)*(integration_type==0) + Integral_ttH/(Integral_ttH+5e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)+5e-2*Integral_ttZ+5e-1*Integral_ttZ_Zll)*(integration_type==1)";
  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;

  TString cut="1";
  TString cat_name="2lss_1tau";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_missing_12.9fb_112016.root";

  datacard_maker(var,nbin,xmin,xmax,cut,file,true,cat_name);


}







void datacard_maker_MEM_ttH_vs_full_bkg_2lSS_nomiss_counting(){

  TString var="1";
  
  int nbin = 3;
  float xmin = 0.;
  float xmax = 3.;

  TString cut="integration_type==0";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_counting_12.9fb_112016.root";

  datacard_maker(var,nbin,xmin,xmax,cut,file,true);


}




void datacard_maker_MEM_ttH_vs_full_bkg_2lSS_missing_counting(){

  TString var="1";
  
  int nbin = 1;
  float xmin = 0.;
  float xmax = 3.;

  TString cut="integration_type==1";

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_counting_12.9fb_112016.root";

  datacard_maker(var,nbin,xmin,xmax,cut,file,true);


}

