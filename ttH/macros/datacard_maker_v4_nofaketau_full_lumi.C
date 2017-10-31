#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>

#include "Helpers.C"

float luminosity = 27656; //27.656 fb-1

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

TString filename_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_bTagSF_CSVshape.root";
TString filename_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW*_bTagSF_CSVshape.root";
TString filename_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_bTagSF_CSVshape.root";
TString filename_ZZJJ = "/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Diboson/HTauTauTree_ZZ_split_bTagSF_CSVshape.root";

TString filename_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split_bTagSF_CSVshape.root";


TString filename_norm_ttH = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttH/ntuple_ttH_Hnonbb_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_ttW = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttV/ntuple_ttW_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_ttZ = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/ttV/ntuple_ttZ_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";
TString filename_norm_ZZJJ = "/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/nominal/EWK/ntuple_ZZJJ_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";

TString filename_norm_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/TTbar/ntuple_ttbar_DL_*_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root";


vector<TString> filename_MC;
vector<TString> filename_norm_MC;




//Data

TString filename_DoubleEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016B_split.root";
TString filename_MuonEG_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016B_split.root";
TString filename_DoubleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016B_split.root";
TString filename_SingleMu_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016B_split.root";
TString filename_SingleEle_2016B = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016B_split.root";

TString filename_DoubleEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016C_split.root";
TString filename_MuonEG_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016C_split.root";
TString filename_DoubleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016C_split.root";
TString filename_SingleMu_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016C_split.root";
TString filename_SingleEle_2016C = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016C_split.root";

TString filename_DoubleEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016D_split.root";
TString filename_MuonEG_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016D_split.root";
TString filename_DoubleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016D_split.root";
TString filename_SingleMu_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016D_split.root";
TString filename_SingleEle_2016D = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016D_split.root";

TString filename_DoubleEG_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016E_split.root";
TString filename_MuonEG_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016E_split.root";
TString filename_DoubleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016E_split.root";
TString filename_SingleMu_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016E_split.root";
TString filename_SingleEle_2016E = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016E_split.root";

TString filename_DoubleEG_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016F_split.root";
TString filename_MuonEG_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016F_split.root";
TString filename_DoubleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016F_split.root";
TString filename_SingleMu_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016F_split.root";
TString filename_SingleEle_2016F = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016F_split.root";

TString filename_DoubleEG_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleEG_2016G_split.root";
TString filename_MuonEG_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_MuonEG_2016G_split.root";
TString filename_DoubleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_DoubleMu_2016G_split.root";
TString filename_SingleMu_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleMu_2016G_split.root";
TString filename_SingleEle_2016G = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/Data/HTauTauTree_SingleEle_2016G_split.root";


vector<TString> filename_data;

vector<TString> MC_sample_name;

vector<TString> filename_MC_thu_unc;
vector<TString> MC_sample_name_thu_unc;


// MC JEC + TES

TString filename_ttH_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/JECup/ttH/HTauTauTree_ttH_Hnonbb_split_JECup_*.root";
TString filename_ttH_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/JECup/ttH/HTauTauTree_ttH_Hnonbb_split_JECdown_*.root";
TString filename_ttH_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESup/ttH/HTauTauTree_ttH_Hnonbb_split_TESup_*.root";
TString filename_ttH_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESdown/ttH/HTauTauTree_ttH_Hnonbb_split_TESdown_*.root";


TString filename_ttZ_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttZ_split_JECup_*.root";
TString filename_ttZ_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttZ_split_JECdown_*.root";
TString filename_ttZ_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESup/ttV/HTauTauTree_ttZ_split_TESup_*.root";
TString filename_ttZ_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttZ_split_TESdown_*.root";


TString filename_ttW_JECup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttW_split_JECup_*.root";
TString filename_ttW_JECdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/JECup/ttV/HTauTauTree_ttW_split_JECdown_*.root";
TString filename_ttW_TESup = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESup/ttV/HTauTauTree_ttW_split_TESup_*.root";
TString filename_ttW_TESdown = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/TESdown/ttV/HTauTauTree_ttW_split_TESdown_*.root";


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
  filename_MC_JECup.clear();
  filename_MC_JECdown.clear();
  filename_MC_TESup.clear();
  filename_MC_TESdown.clear();
  filename_data.clear();
  bTag_syst_names.clear();

  XS.push_back(XS_ttH);
  filename_MC.push_back(filename_ttH);
  filename_norm_MC.push_back(filename_norm_ttH);
  MC_sample_name.push_back("ttH");
  filename_MC_JECup.push_back(filename_ttH_JECup);
  filename_MC_JECdown.push_back(filename_ttH_JECdown);
  filename_MC_TESup.push_back(filename_ttH_TESup);
  filename_MC_TESdown.push_back(filename_ttH_TESdown);

  XS.push_back(XS_ttW);
  filename_MC.push_back(filename_ttW);
  filename_norm_MC.push_back(filename_norm_ttW);
  MC_sample_name.push_back("TTW");
  filename_MC_JECup.push_back(filename_ttW_JECup);
  filename_MC_JECdown.push_back(filename_ttW_JECdown);
  filename_MC_TESup.push_back(filename_ttW_TESup);
  filename_MC_TESdown.push_back(filename_ttW_TESdown);

  XS.push_back(XS_ttZ);
  filename_MC.push_back(filename_ttZ);
  filename_norm_MC.push_back(filename_norm_ttZ);
  MC_sample_name.push_back("TTZ");
  filename_MC_JECup.push_back(filename_ttZ_JECup);
  filename_MC_JECdown.push_back(filename_ttZ_JECdown);
  filename_MC_TESup.push_back(filename_ttZ_TESup);
  filename_MC_TESdown.push_back(filename_ttZ_TESdown);



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

  filename_MC_thu_unc.push_back(filename_ttH);
  MC_sample_name_thu_unc.push_back("ttH");
  
  filename_MC_thu_unc.push_back(filename_ttW);
  MC_sample_name_thu_unc.push_back("TTW");

  filename_MC_thu_unc.push_back(filename_ttZ);
  MC_sample_name_thu_unc.push_back("TTZ");


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
		    TString file, bool syst=false){



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
    //TDirectory* dir = f_new->mkdir(cat_names[i_cat]);
    //dir->cd();

    //////////////////////////////////////////
    //////////////////////////////////////////
    /////////          NOMINAL        ////////
    //////////////////////////////////////////
    //////////////////////////////////////////


    for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){

      TH1F* h_MC = single_plot(filename_MC[i_MC],
			       "HTauTauTree_2lSS",
			       var,
			       Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==%i && isTrig)",cat[i_cat]),
			       nbin,xmin,xmax);

      
      TH1F* h_MC_norm = single_plot(filename_norm_MC[i_MC],
				    "HTauTauTree",
				    "1",
				    "MC_weight*PU_weight",
				    3,0,3);


      h_MC->Scale(luminosity*XS[i_MC]/h_MC_norm->Integral());
      /*if(MC_sample_name[i_MC]=="ttH")
	h_MC->SetNameTitle("x_"+MC_sample_name[i_MC]+"_genmatch","x_"+MC_sample_name[i_MC]+"_genmatch");
	else*/
      h_MC->SetNameTitle("x_"+MC_sample_name[i_MC],"x_"+MC_sample_name[i_MC]);
      h_MC->Write();


    }


    TH1F* h_ttH_norm =single_plot(filename_norm_ttH,
				  "HTauTauTree",
				  "1",
				  "MC_weight*PU_weight",
				  3,0,3);
    
    /*TH1F* h_ttH_fake = single_plot(filename_ttH,
				   "HTauTauTree_2lSS",
				   var,
				   Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==%i && isTrig && !isGenMatched)",cat[i_cat]),
				   nbin,xmin,xmax);

    h_ttH_fake->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
    h_ttH_fake->SetNameTitle("x_ttH_fake","x_ttH_fake");
    h_ttH_fake->Write();

    TH1F* h_ttH = (TH1F*)f_new->Get("x_ttH_genmatch");
    h_ttH->Add((TH1F*)f_new->Get("x_ttH_fake"));
    h_ttH->SetNameTitle("x_ttH","x_ttH");
    h_ttH->Write();*/


    TH1F* h_ttH_tautau =single_plot(filename_ttH,
				    "HTauTauTree_2lSS",
				    var,
				    Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==%i && genH_decayMode[1]<=5 && isTrig)",cat[i_cat]),
				    nbin,xmin,xmax);
        
    h_ttH_tautau->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
    h_ttH_tautau->SetNameTitle("x_ttH_htt","x_ttH_htt");
    h_ttH_tautau->Write();
    
    TH1F* h_ttH_WW =single_plot(filename_ttH,
				"HTauTauTree_2lSS",
				var,
				Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==%i && genH_decayMode[1]>5 && n_genW==4 && isTrig)",cat[i_cat]),
				nbin,xmin,xmax);
  
    
    h_ttH_WW->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
    h_ttH_WW->SetNameTitle("x_ttH_hww","x_ttH_hww");
    h_ttH_WW->Write();

    TH1F* h_ttH_ZZ =single_plot(filename_ttH,
				"HTauTauTree_2lSS",
				var,
				Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==%i && genH_decayMode[1]>5 && n_genZ==2 && isTrig)",cat[i_cat]),
				nbin,xmin,xmax);
  
    
    h_ttH_ZZ->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
    h_ttH_ZZ->SetNameTitle("x_ttH_hzz","x_ttH_hzz");
    h_ttH_ZZ->Write();


    
    //Fakes
    
    TH1F* h_fakes =single_plot(filename_data,
			       "HTauTauTree_2lSS_lepMVA_CR",
			       var,
			       Form("event_weight_ttH*(category==%i && isTrig && n_fake_tau==0)",cat_fakes[i_cat]),
			       nbin,xmin,xmax);
    
    h_fakes->Scale(luminosity/27656.); //Data files for 27.656 fb-1
    //h_fakes->Add((TH1F*)f_new->Get("x_ttH_fake"),-1);
    h_fakes->SetNameTitle("x_fakes_data","x_fakes_data");
    h_fakes->Write();



    //Fakes MC
    
    TH1F* h_ttbar_DL_fakes_MC =single_plot(filename_ttbar_DL,
				  "HTauTauTree_2lSS_lepMVA_CR",
				  var,
				  Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*event_weight_ttH*(category==%i && isTrig && n_fake_tau==0)",cat_fakes[i_cat]),
				  nbin,xmin,xmax);
    
    TH1F* h_ttbar_DL_norm =single_plot(filename_norm_ttbar_DL,
				       "HTauTauTree",
				       "1",
				       "MC_weight*PU_weight",
				       3,0,3);
 
    h_ttbar_DL_fakes_MC->Scale(luminosity*XS_ttbar_DL/h_ttbar_DL_norm->Integral());
    h_ttbar_DL_fakes_MC->SetNameTitle("x_fakes_MC","x_fakes_MC");
    h_ttbar_DL_fakes_MC->Write();



    //Charge flips
    TH1F* h_flips =single_plot(filename_data,
			       "HTauTauTree_2lOS_CR",
			       var,
			       Form("event_weight_ttH*(category==%i && isTrig)",cat_flips[i_cat]),			    
			       nbin,xmin,xmax);
    
    h_flips->Scale(luminosity/27656.); //Data files for 27.656 fb-1
    h_flips->SetNameTitle("x_flips_data","x_flips_data");
    h_flips->Write();
 
    
    
    //Data
    
    /*TH1F* h_data_obs =single_plot(filename_data,
      "HTauTauTree_2lSS",
      var,
      Form("(category==%i && isTrig)",cat[i]),		
      nbin,xmin,xmax);
      
      h_data_obs->Scale(luminosity/27656.); //Data files for 27.656 fb-1
      
      h_data_obs->SetNameTitle("x_data_obs","x_data_obs");
      h_data_obs->Write();
      h.push_back(h_data_obs);*/


    TH1F* h_data_obs = (TH1F*)f_new->Get("x_ttH");
    h_data_obs->Add( (TH1F*)f_new->Get("x_TTW") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_TTZ") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_fakes_data") );
    h_data_obs->Add( (TH1F*)f_new->Get("x_flips_data") );
    h_data_obs->SetNameTitle("x_data_obs","x_data_obs");
    h_data_obs->Write();

    

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

      float norm = ((TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]))->Integral();

      for(unsigned int i_b=0;i_b<bTag_syst_names.size();i_b++){       
		    
	TString cut = "MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight_" + bTag_syst_names[i_b];
	if(MC_sample_name[i_MC]!="ttH")
	  cut+=Form("*(category==%i && isTrig && isGenMatched)",cat[i_cat]);
	else
	  cut+=Form("*(category==%i && isTrig)",cat[i_cat]);

	TH1F* h_MC_btag_syst = single_plot(filename_MC[i_MC],
					   "HTauTauTree_2lSS",
					   var,
					   cut,
					   nbin,xmin,xmax);
      
	h_MC_btag_syst->Scale(norm/h_MC_btag_syst->Integral());
	h_MC_btag_syst->SetNameTitle("x_"+MC_sample_name[i_MC]+"_btag_"+bTag_syst_names[i_b],"x_"+MC_sample_name[i_MC]+"_btag_"+bTag_syst_names[i_b]);
	h_MC_btag_syst->Write();

      }

    }



    for(unsigned i_MC=0;i_MC<MC_sample_name_thu_unc.size();i_MC++){

      float norm = ((TH1F*)f_new->Get("x_"+MC_sample_name_thu_unc[i_MC]))->Integral();
		    
      TString cut = Form("PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==%i && isTrig && isGenMatched)",cat[i_cat]);
      if(MC_sample_name[i_MC]=="ttH")
	cut = Form("PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==%i && isTrig)",cat[i_cat]);

      TH1F* h_MC_x1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "HTauTauTree_2lSS",
				     var,
				     "MC_weight_scale_muR2*"+cut,
				     nbin,xmin,xmax);
      
      h_MC_x1_up->Scale(norm/h_MC_x1_up->Integral());
      h_MC_x1_up->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_x1Up","x_"+MC_sample_name_thu_unc[i_MC]+"_x1Up");
      h_MC_x1_up->Write();

      TH1F* h_MC_x1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "HTauTauTree_2lSS",
				       var,
				       "MC_weight_scale_muR0p5*"+cut,
				       nbin,xmin,xmax);
      
      h_MC_x1_down->Scale(norm/h_MC_x1_down->Integral());
      h_MC_x1_down->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_x1Down","x_"+MC_sample_name_thu_unc[i_MC]+"_x1Down");
      h_MC_x1_down->Write();

      TH1F* h_MC_y1_up = single_plot(filename_MC_thu_unc[i_MC],
				     "HTauTauTree_2lSS",
				     var,
				     "MC_weight_scale_muF2*"+cut,
				     nbin,xmin,xmax);
      
      h_MC_y1_up->Scale(norm/h_MC_y1_up->Integral());
      h_MC_y1_up->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_y1Up","x_"+MC_sample_name_thu_unc[i_MC]+"_y1Up");
      h_MC_y1_up->Write();

      TH1F* h_MC_y1_down = single_plot(filename_MC_thu_unc[i_MC],
				       "HTauTauTree_2lSS",
				       var,
				       "MC_weight_scale_muF0p5*"+cut,
				       nbin,xmin,xmax);
      
      h_MC_y1_down->Scale(norm/h_MC_y1_down->Integral());
      h_MC_y1_down->SetNameTitle("x_"+MC_sample_name_thu_unc[i_MC]+"_y1Down","x_"+MC_sample_name_thu_unc[i_MC]+"_y1Down");
      h_MC_y1_down->Write();
      
 

    }





    /*for(unsigned i_MC=0;i_MC<MC_sample_name.size();i_MC++){
      
      TString cut=Form("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==%i && isTrig)",cat[i_cat]);

      float norm = ((TH1F*)f_new->Get("x_"+MC_sample_name[i_MC]))->Integral();
      
      TH1F* h_MC_JEC_up = single_plot(filename_MC_JECup[i_MC],
				      "HTauTauTree_2lSS",
				      var,
				      cut,
				      nbin,xmin,xmax);
      
      h_MC_JEC_up->Scale(norm/h_MC_JEC_up->Integral());
      h_MC_JEC_up->SetNameTitle("x_"+MC_sample_name[i_MC]+"_JECUp","x_"+MC_sample_name[i_MC]+"_JECUp");
      h_MC_JEC_up->Write();

      
      TH1F* h_MC_JEC_down = single_plot(filename_MC_JECdown[i_MC],
					"HTauTauTree_2lSS",
					var,
					cut,
					nbin,xmin,xmax);
      
      h_MC_JEC_down->Scale(norm/h_MC_JEC_down->Integral());
      h_MC_JEC_down->SetNameTitle("x_"+MC_sample_name[i_MC]+"_JECDown","x_"+MC_sample_name[i_MC]+"_JECDown");
      h_MC_JEC_down->Write();

      TH1F* h_MC_TES_up = single_plot(filename_MC_TESup[i_MC],
				      "HTauTauTree_2lSS",
				      var,
				      cut,
				      nbin,xmin,xmax);
      
      h_MC_TES_up->Scale(norm/h_MC_TES_up->Integral());
      h_MC_TES_up->SetNameTitle("x_"+MC_sample_name[i_MC]+"_TES_up","x_"+MC_sample_name[i_MC]+"_TES_up");
      h_MC_TES_up->Write();

      
      TH1F* h_MC_TES_down = single_plot(filename_MC_TESdown[i_MC],
					"HTauTauTree_2lSS",
					var,
					cut,
					nbin,xmin,xmax);
      
      h_MC_TES_down->Scale(norm/h_MC_TES_down->Integral());
      h_MC_TES_down->SetNameTitle("x_"+MC_sample_name[i_MC]+"_TES_down","x_"+MC_sample_name[i_MC]+"_TES_down");
      h_MC_TES_down->Write();

      }*/

  }







  f_new->Close();


}









void datacard_maker_MVA_2lSS_allcat_syst(){

  TString var="1*(MVA_2lSS_ttbar>-1 && MVA_2lSS_ttbar<=-0.2 && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=1) + 2*(MVA_2lSS_ttbar>-0.2 && MVA_2lSS_ttbar<=0.1 && MVA_2lSS_ttV>-1 && MVA_2lSS_ttV<=1) + 3*(MVA_2lSS_ttbar>0.1 && MVA_2lSS_ttbar<=0.4 && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=0.3) + 4*(MVA_2lSS_ttbar>0.1 && MVA_2lSS_ttbar<=0.4 && MVA_2lSS_ttV>0.3 && MVA_2lSS_ttV<=1) + 5*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=0.1) + 6*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>0.1 && MVA_2lSS_ttV<=0.4) + 7*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>0.4 && MVA_2lSS_ttV<=1)";

  
  int nbin = 7;
  float xmin = 0.5;
  float xmax = 7.5;


  TString file="/data_CMS/cms/strebler/ttH_prod_80X_11_2016/datacards/datacard_MVA_2lSS_allcat_syst_nofaketau_27.656fb_112016.root";


  datacard_maker(var,nbin,xmin,xmax,file);


}



