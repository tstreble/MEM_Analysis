#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>

#include "Helpers.C"

float luminosity = 4000; //4.0 fb-1

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
float XS_TTJets_DL = 87.3;
float XS_TTJets_SLfromT = 182;
float XS_TTJets_SLfromTbar = 182;



void datacard_maker_MVA_2lSS(){

  vector<TH1F*> h;
  

  TString var="1*(MVA_2lSS_ttbar>-1 && MVA_2lSS_ttbar<=-0.2 && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=1) + 2*(MVA_2lSS_ttbar>-0.2 && MVA_2lSS_ttbar<=0.1 && MVA_2lSS_ttV>-1 && MVA_2lSS_ttV<=1) + 3*(MVA_2lSS_ttbar>0.1 && MVA_2lSS_ttbar<=0.4 && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=0.3) + 4*(MVA_2lSS_ttbar>0.1 && MVA_2lSS_ttbar<=0.4 && MVA_2lSS_ttV>0.3 && MVA_2lSS_ttV<=1) + 5*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=0.1) + 6*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>0.1 && MVA_2lSS_ttV<=0.4) + 7*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>0.4 && MVA_2lSS_ttV<=1)";

  
  int nbin = 7;
  float xmin = 0.5;
  float xmax = 7.5;


  //ttH

  TH1F* h_ttH =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttH/HTauTauTree_ttH_Hnonbb_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11)",
			   nbin,xmin,xmax);

  TH1F* h_ttH_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttH->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH->SetNameTitle("h_ttH","h_ttH");
  h.push_back(h_ttH);


  //ttW

  TH1F* h_ttW =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_ttW_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11)",
			   nbin,xmin,xmax);

  TH1F* h_ttW_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttW_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttW->Scale(luminosity*XS_ttW/h_ttW_norm->Integral());
  h_ttW->SetNameTitle("h_ttW","h_ttW");
  h.push_back(h_ttW);



  //ttZ

  TH1F* h_ttZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_ttZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11)",
			   nbin,xmin,xmax);

  TH1F* h_ttZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttZ->Scale(luminosity*XS_ttZ/h_ttZ_norm->Integral());
  h_ttZ->SetNameTitle("h_ttZ","h_ttZ");
  h.push_back(h_ttZ);



  //TTLL low mass

  TH1F* h_TTLL_lowmass =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/topG/HTauTauTree_TTLL_lowmass_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11)",
			   nbin,xmin,xmax);

  TH1F* h_TTLL_lowmass_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_TTLL_lowmass_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					 "HTauTauTree",
					 "1",
					 "MC_weight",
					 3,0,2);
  
  h_TTLL_lowmass->Scale(luminosity*XS_TTLL_lowmass/h_TTLL_lowmass_norm->Integral());
  h_TTLL_lowmass->SetNameTitle("h_TTLL_lowmass","h_TTLL_lowmass");
  h.push_back(h_TTLL_lowmass);



  //ttG

  TH1F* h_ttG =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/topG/HTauTauTree_ttG_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11)",
			   nbin,xmin,xmax);

  TH1F* h_ttG_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_ttG_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ttG->Scale(luminosity*XS_ttG/h_ttG_norm->Integral());
  h_ttG->SetNameTitle("h_ttG","h_ttG");
  h.push_back(h_ttG);

  

  //WpWp

  TH1F* h_WpWp =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WpWp_split.root",
			    "HTauTauTree_2lSS",
			    var,
			    "MC_weight*(category==11)",
			    nbin,xmin,xmax);

  TH1F* h_WpWp_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WpWp_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
    
  h_WpWp->Scale(luminosity*XS_WpWp/h_WpWp_norm->Integral());
  h_WpWp->SetNameTitle("h_WpWp","h_WpWp");
  h.push_back(h_WpWp);

  
  //WZ

  TH1F* h_WZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Diboson/HTauTauTree_WZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11)",
			   nbin,xmin,xmax);

  TH1F* h_WZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_WZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZ->Scale(luminosity*XS_WZ/h_WZ_norm->Integral());
  h_WZ->SetNameTitle("h_WZ","h_WZ");
  h.push_back(h_WZ);


  //ZZ

  TH1F* h_ZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Diboson/HTauTauTree_ZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11)",
			   nbin,xmin,xmax);

  TH1F* h_ZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_ZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZ->Scale(luminosity*XS_ZZ/h_ZZ_norm->Integral());
  h_ZZ->SetNameTitle("h_ZZ","h_ZZ");
  h.push_back(h_ZZ);



  //ZZZ

  TH1F* h_ZZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_ZZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11)",
			   nbin,xmin,xmax);

  TH1F* h_ZZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZZ->Scale(luminosity*XS_ZZZ/h_ZZZ_norm->Integral());
  h_ZZZ->SetNameTitle("h_ZZZ","h_ZZZ");
  h.push_back(h_ZZZ);



  //WZZ

  TH1F* h_WZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11)",
			   nbin,xmin,xmax);

  TH1F* h_WZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZZ->Scale(luminosity*XS_WZZ/h_WZZ_norm->Integral());
  h_WZZ->SetNameTitle("h_WZZ","h_WZZ");
  h.push_back(h_WZZ);



  //WWZ

  TH1F* h_WWZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WWZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11)",
			   nbin,xmin,xmax);

  TH1F* h_WWZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WWZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WWZ->Scale(luminosity*XS_WWZ/h_WWZ_norm->Integral());
  h_WWZ->SetNameTitle("h_WWZ","h_WWZ");
  h.push_back(h_WWZ);


  //tZq

  TH1F* h_tZq =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_tZq_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11)",
			   nbin,xmin,xmax);

  TH1F* h_tZq_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_tZq_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_tZq->Scale(luminosity*XS_tZq/h_tZq_norm->Integral());
  h_tZq->SetNameTitle("h_tZq","h_tZq");
  h.push_back(h_tZq);



  //TTTT

  TH1F* h_TTTT =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/TTTT/HTauTauTree_TTTT_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11)",
			   nbin,xmin,xmax);

  TH1F* h_TTTT_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTTT/ntuple_TTTT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
  
  h_TTTT->Scale(luminosity*XS_TTTT/h_TTTT_norm->Integral());
  h_TTTT->SetNameTitle("h_TTTT","h_TTTT");
  h.push_back(h_TTTT);


  //Fakes

  vector<TString> files_data;
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleEG_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleEG_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleMu_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleMu_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_MuonEG_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_MuonEG_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleEle_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleEle_2016C_split_trig_filtroot");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016C_split_trig_filt.root");

  TH1F* h_fakes =single_plot(files_data,
			     "HTauTauTree_2lSS_lepMVA_CR",
			     var,
			     "MC_weight*event_weight_ttH*(category==41 && isTrig)",
			     nbin,xmin,xmax);

  h_fakes->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_fakes->SetNameTitle("h_fakes","h_fakes");
  h.push_back(h_fakes);

  
  //Fakes MC

  TH1F* h_fakes_DL_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root",
				   "HTauTauTree_2lSS_lepMVA_CR",
				   var,
				   "MC_weight*event_weight_ttH*(category==41)",
				   nbin,xmin,xmax);

  TH1F* h_fakes_DL_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					"HTauTauTree",
					"1",
					"MC_weight",
					3,0,2);
    
  h_fakes_DL_MC->Scale(luminosity*XS_TTJets_DL/h_fakes_DL_MC_norm->Integral());
  h_fakes_DL_MC->SetNameTitle("h_fakes_DL_MC","h_fakes_DL_MC");
  h.push_back(h_fakes_DL_MC);


  TH1F* h_fakes_SLfromT_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160718.root",
					"HTauTauTree_2lSS_lepMVA_CR",
					var,
					"MC_weight*event_weight_ttH*(category==41)",
					nbin,xmin,xmax);

  TH1F* h_fakes_SLfromT_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					     "HTauTauTree",
					     "1",
					     "MC_weight",
					     3,0,2);
    
  h_fakes_SLfromT_MC->Scale(luminosity*XS_TTJets_SLfromT/h_fakes_SLfromT_MC_norm->Integral());
  h_fakes_SLfromT_MC->SetNameTitle("h_fakes_SLfromT_MC","h_fakes_SLfromT_MC");
  h.push_back(h_fakes_SLfromT_MC);


  TH1F* h_fakes_SLfromTbar_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160718.root",
					"HTauTauTree_2lSS_lepMVA_CR",
					var,
					"MC_weight*event_weight_ttH*(category==41)",
					nbin,xmin,xmax);

  TH1F* h_fakes_SLfromTbar_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_SLfromTbar_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					     "HTauTauTree",
					     "1",
					     "MC_weight",
					     3,0,2);
    
  h_fakes_SLfromTbar_MC->Scale(luminosity*XS_TTJets_SLfromTbar/h_fakes_SLfromTbar_MC_norm->Integral());
  h_fakes_SLfromTbar_MC->SetNameTitle("h_fakes_SLfromTbar_MC","h_fakes_SLfromTbar_MC");
  h.push_back(h_fakes_SLfromTbar_MC);


  
  

  //Charge flips

  TH1F* h_flips =single_plot(files_data,
			     "HTauTauTree_2lOS_CR",
			     var,
			     "MC_weight*event_weight_ttH*(category==-11 && isTrig)",
			     nbin,xmin,xmax);

  h_flips->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_flips->SetNameTitle("h_flips","h_flips");
  h.push_back(h_flips);


  
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS.root";

  TFile* f_new = TFile::Open(file,"RECREATE");


  for(unsigned int i=0;i<h.size();i++)
    h[i]->Write();

  f_new->Close();


}






void datacard_maker_MVA_2lSS_pt25(){

  vector<TH1F*> h;
  

  TString var="1*(MVA_2lSS_ttbar>-1 && MVA_2lSS_ttbar<=-0.2 && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=1) + 2*(MVA_2lSS_ttbar>-0.2 && MVA_2lSS_ttbar<=0.1 && MVA_2lSS_ttV>-1 && MVA_2lSS_ttV<=1) + 3*(MVA_2lSS_ttbar>0.1 && MVA_2lSS_ttbar<=0.4 && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=0.3) + 4*(MVA_2lSS_ttbar>0.1 && MVA_2lSS_ttbar<=0.4 && MVA_2lSS_ttV>0.3 && MVA_2lSS_ttV<=1) + 5*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=0.1) + 6*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>0.1 && MVA_2lSS_ttV<=0.4) + 7*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>0.4 && MVA_2lSS_ttV<=1)";

  
  int nbin = 7;
  float xmin = 0.5;
  float xmax = 7.5;


  //ttH

  TH1F* h_ttH =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttH/HTauTauTree_ttH_Hnonbb_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttH_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttH->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH->SetNameTitle("h_ttH","h_ttH");
  h.push_back(h_ttH);

  
  TH1F* h_ttH_tautau =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttH/HTauTauTree_ttH_Hnonbb_split.root",
				  "HTauTauTree_2lSS",
				  var,
				  "MC_weight*(category==11 && recolep_sel_pt[0]>25 && genH_decayMode[1]<=5)",
				  nbin,xmin,xmax);

  
  h_ttH_tautau->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_tautau->SetNameTitle("h_ttH_tautau","h_ttH_tautau");
  h.push_back(h_ttH_tautau);

  TH1F* h_ttH_boson =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttH/HTauTauTree_ttH_Hnonbb_split.root",
				 "HTauTauTree_2lSS",
				 var,
				 "MC_weight*(category==11 && recolep_sel_pt[0]>25 && genH_decayMode[1]>5)",
				 nbin,xmin,xmax);
  
  
  h_ttH_boson->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_boson->SetNameTitle("h_ttH_boson","h_ttH_boson");
  h.push_back(h_ttH_boson);
  

  //ttW

  TH1F* h_ttW =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_ttW_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttW_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttW_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttW->Scale(luminosity*XS_ttW/h_ttW_norm->Integral());
  h_ttW->SetNameTitle("h_ttW","h_ttW");
  h.push_back(h_ttW);



  //ttZ

  TH1F* h_ttZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_ttZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttZ->Scale(luminosity*XS_ttZ/h_ttZ_norm->Integral());
  h_ttZ->SetNameTitle("h_ttZ","h_ttZ");
  h.push_back(h_ttZ);



  //TTLL low mass

  TH1F* h_TTLL_lowmass =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/topG/HTauTauTree_TTLL_lowmass_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTLL_lowmass_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_TTLL_lowmass_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					 "HTauTauTree",
					 "1",
					 "MC_weight",
					 3,0,2);
  
  h_TTLL_lowmass->Scale(luminosity*XS_TTLL_lowmass/h_TTLL_lowmass_norm->Integral());
  h_TTLL_lowmass->SetNameTitle("h_TTLL_lowmass","h_TTLL_lowmass");
  h.push_back(h_TTLL_lowmass);



  //ttG

  TH1F* h_ttG =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/topG/HTauTauTree_ttG_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttG_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_ttG_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ttG->Scale(luminosity*XS_ttG/h_ttG_norm->Integral());
  h_ttG->SetNameTitle("h_ttG","h_ttG");
  h.push_back(h_ttG);


  //TTZ = ttZ + TTLL_lowmass + ttG
  
  TH1F h_TTZ = *h_ttZ;
  h_TTZ.Add(h_TTLL_lowmass);
  h_TTZ.Add(h_ttG);
  h_TTZ.SetNameTitle("h_TTZ","h_TTZ");
  h.push_back(&h_TTZ);


  //WpWp

  TH1F* h_WpWp =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WpWp_split.root",
			    "HTauTauTree_2lSS",
			    var,
			    "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			    nbin,xmin,xmax);

  TH1F* h_WpWp_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WpWp_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
    
  h_WpWp->Scale(luminosity*XS_WpWp/h_WpWp_norm->Integral());
  h_WpWp->SetNameTitle("h_WpWp","h_WpWp");
  h.push_back(h_WpWp);

  
 //WZ

  TH1F* h_WZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Diboson/HTauTauTree_WZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_WZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZ->Scale(luminosity*XS_WZ/h_WZ_norm->Integral());
  h_WZ->SetNameTitle("h_WZ","h_WZ");
  h.push_back(h_WZ);


  //ZZ

  TH1F* h_ZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Diboson/HTauTauTree_ZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_ZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZ->Scale(luminosity*XS_ZZ/h_ZZ_norm->Integral());
  h_ZZ->SetNameTitle("h_ZZ","h_ZZ");
  h.push_back(h_ZZ);


  //Diboson = WZ + ZZ
  
  TH1F h_Diboson = *h_WZ;
  h_Diboson.Add(h_ZZ);
  h_Diboson.SetNameTitle("h_Diboson","h_Diboson");
  h.push_back(&h_Diboson);


  //ZZZ

  TH1F* h_ZZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_ZZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZZ->Scale(luminosity*XS_ZZZ/h_ZZZ_norm->Integral());
  h_ZZZ->SetNameTitle("h_ZZZ","h_ZZZ");
  h.push_back(h_ZZZ);



  //WZZ

  TH1F* h_WZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZZ->Scale(luminosity*XS_WZZ/h_WZZ_norm->Integral());
  h_WZZ->SetNameTitle("h_WZZ","h_WZZ");
  h.push_back(h_WZZ);



  //WWZ

  TH1F* h_WWZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WWZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WWZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WWZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WWZ->Scale(luminosity*XS_WWZ/h_WWZ_norm->Integral());
  h_WWZ->SetNameTitle("h_WWZ","h_WWZ");
  h.push_back(h_WWZ);


  //tZq

  TH1F* h_tZq =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_tZq_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_tZq_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_tZq_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_tZq->Scale(luminosity*XS_tZq/h_tZq_norm->Integral());
  h_tZq->SetNameTitle("h_tZq","h_tZq");
  h.push_back(h_tZq);



  //TTTT

  TH1F* h_TTTT =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/TTTT/HTauTauTree_TTTT_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTTT_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTTT/ntuple_TTTT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
  
  h_TTTT->Scale(luminosity*XS_TTTT/h_TTTT_norm->Integral());
  h_TTTT->SetNameTitle("h_TTTT","h_TTTT");
  h.push_back(h_TTTT);

  //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
  TH1F h_Rares = *h_ZZZ;
  h_Rares.Add(h_WZZ);
  h_Rares.Add(h_WWZ);
  h_Rares.Add(h_tZq);
  h_Rares.Add(h_TTTT);
  h_Rares.SetNameTitle("h_Rares","h_Rares");
  h.push_back(&h_Rares);



  //Fakes

  vector<TString> files_data;
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleEG_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleEG_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleMu_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleMu_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_MuonEG_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_MuonEG_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleEle_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleEle_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016C_split_trig_filt.root");

  TH1F* h_fakes =single_plot(files_data,
			     "HTauTauTree_2lSS_lepMVA_CR",
			     var,
			     "event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_fakes->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_fakes->SetNameTitle("h_fakes","h_fakes");

  h.push_back(h_fakes);

  //Fakes MC

  TH1F* h_fakes_DL_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/TTJets/HTauTauTree_ttbar_DL_split.root",
				   "HTauTauTree_2lSS_lepMVA_CR",
				   var,
				   "MC_weight*event_weight_ttH*(category==41)",
				   nbin,xmin,xmax);

  TH1F* h_fakes_DL_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					"HTauTauTree",
					"1",
					"MC_weight",
					3,0,2);
    
  h_fakes_DL_MC->Scale(luminosity*XS_TTJets_DL/h_fakes_DL_MC_norm->Integral());
  h_fakes_DL_MC->SetNameTitle("h_fakes_DL_MC","h_fakes_DL_MC");
  h.push_back(h_fakes_DL_MC);


  TH1F* h_fakes_SLfromT_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/TTJets/HTauTauTree_ttbar_SLfromT_split.root",
					"HTauTauTree_2lSS_lepMVA_CR",
					var,
					"MC_weight*event_weight_ttH*(category==41)",
					nbin,xmin,xmax);

  TH1F* h_fakes_SLfromT_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					     "HTauTauTree",
					     "1",
					     "MC_weight",
					     3,0,2);
    
  h_fakes_SLfromT_MC->Scale(luminosity*XS_TTJets_SLfromT/h_fakes_SLfromT_MC_norm->Integral());
  h_fakes_SLfromT_MC->SetNameTitle("h_fakes_SLfromT_MC","h_fakes_SLfromT_MC");
  h.push_back(h_fakes_SLfromT_MC);


  TH1F* h_fakes_SLfromTbar_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/TTJets/HTauTauTree_ttbar_SLfromTbar_split.root",
					"HTauTauTree_2lSS_lepMVA_CR",
					var,
					"MC_weight*event_weight_ttH*(category==41)",
					nbin,xmin,xmax);

  TH1F* h_fakes_SLfromTbar_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_SLfromTbar_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					     "HTauTauTree",
					     "1",
					     "MC_weight",
					     3,0,2);
    
  h_fakes_SLfromTbar_MC->Scale(luminosity*XS_TTJets_SLfromTbar/h_fakes_SLfromTbar_MC_norm->Integral());
  h_fakes_SLfromTbar_MC->SetNameTitle("h_fakes_SLfromTbar_MC","h_fakes_SLfromTbar_MC");
  h.push_back(h_fakes_SLfromTbar_MC);


  //Fakes MC
  TH1F h_fakes_MC = *h_fakes_DL_MC;
  h_fakes_MC.Add(h_fakes_SLfromT_MC);
  h_fakes_MC.Add(h_fakes_SLfromTbar_MC);
  h_fakes_MC.SetNameTitle("h_fakes_MC","h_fakes_MC");
  h.push_back(&h_fakes_MC);


  //Charge flips

  TH1F* h_flips =single_plot(files_data,
			     "HTauTauTree_2lOS_CR",
			     var,
			     "event_weight_ttH*(category==-11 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_flips->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_flips->SetNameTitle("h_flips","h_flips");
  h.push_back(h_flips);

  
  //Data

  /*TH1F* h_data_obs =single_plot(files_data,
				"HTauTauTree_2lSS",
				var,
				"(category==11 && recolep_sel_pt[0]>25 && isTrig)",
				nbin,xmin,xmax);

				h_data_obs->Scale(luminosity/8538.); //Data files for 8.5 fb-1

  h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(h_data_obs);*/

  TH1F h_data_obs = *h_ttH;
  h_data_obs.Add(h_ttW);
  h_data_obs.Add(&h_TTZ);
  h_data_obs.Add(h_WpWp);
  h_data_obs.Add(&h_Diboson);
  h_data_obs.Add(&h_Rares);
  h_data_obs.Add(h_fakes);
  h_data_obs.Add(h_flips);

  h_data_obs.SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(&h_data_obs);



  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_pt25.root";

  TFile* f_new = TFile::Open(file,"RECREATE");


  for(unsigned int i=0;i<h.size();i++)
    h[i]->Write();

  f_new->Close();


}








void datacard_maker_counting(){

  vector<TH1F*> h;
  

  TString var="1";

  
  int nbin = 3;
  float xmin = 0;
  float xmax = 3;


  //ttH

  TH1F* h_ttH =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttH/HTauTauTree_ttH_Hnonbb_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttH_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttH->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH->SetNameTitle("h_ttH","h_ttH");
  h.push_back(h_ttH);

  
  TH1F* h_ttH_tautau =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttH/HTauTauTree_ttH_Hnonbb_split.root",
				  "HTauTauTree_2lSS",
				  var,
				  "MC_weight*(category==11 && recolep_sel_pt[0]>25 && genH_decayMode[1]<=5)",
				  nbin,xmin,xmax);

  
  h_ttH_tautau->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_tautau->SetNameTitle("h_ttH_tautau","h_ttH_tautau");
  h.push_back(h_ttH_tautau);

  TH1F* h_ttH_boson =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttH/HTauTauTree_ttH_Hnonbb_split.root",
				 "HTauTauTree_2lSS",
				 var,
				 "MC_weight*(category==11 && recolep_sel_pt[0]>25 && genH_decayMode[1]>5)",
				 nbin,xmin,xmax);
  
  
  h_ttH_boson->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_boson->SetNameTitle("h_ttH_boson","h_ttH_boson");
  h.push_back(h_ttH_boson);
  

  //ttW

  TH1F* h_ttW =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_ttW_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttW_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttW_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttW->Scale(luminosity*XS_ttW/h_ttW_norm->Integral());
  h_ttW->SetNameTitle("h_ttW","h_ttW");
  h.push_back(h_ttW);



  //ttZ

  TH1F* h_ttZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_ttZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttZ->Scale(luminosity*XS_ttZ/h_ttZ_norm->Integral());
  h_ttZ->SetNameTitle("h_ttZ","h_ttZ");
  h.push_back(h_ttZ);



  //TTLL low mass

  TH1F* h_TTLL_lowmass =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/topG/HTauTauTree_TTLL_lowmass_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTLL_lowmass_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_TTLL_lowmass_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					 "HTauTauTree",
					 "1",
					 "MC_weight",
					 3,0,2);
  
  h_TTLL_lowmass->Scale(luminosity*XS_TTLL_lowmass/h_TTLL_lowmass_norm->Integral());
  h_TTLL_lowmass->SetNameTitle("h_TTLL_lowmass","h_TTLL_lowmass");
  h.push_back(h_TTLL_lowmass);



  //ttG

  TH1F* h_ttG =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/topG/HTauTauTree_ttG_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttG_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_ttG_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ttG->Scale(luminosity*XS_ttG/h_ttG_norm->Integral());
  h_ttG->SetNameTitle("h_ttG","h_ttG");
  h.push_back(h_ttG);


  //TTZ = ttZ + TTLL_lowmass + ttG
  
  TH1F h_TTZ = *h_ttZ;
  h_TTZ.Add(h_TTLL_lowmass);
  h_TTZ.Add(h_ttG);
  h_TTZ.SetNameTitle("h_TTZ","h_TTZ");
  h.push_back(&h_TTZ);


  //WpWp

  TH1F* h_WpWp =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WpWp_split.root",
			    "HTauTauTree_2lSS",
			    var,
			    "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			    nbin,xmin,xmax);

  TH1F* h_WpWp_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WpWp_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
    
  h_WpWp->Scale(luminosity*XS_WpWp/h_WpWp_norm->Integral());
  h_WpWp->SetNameTitle("h_WpWp","h_WpWp");
  h.push_back(h_WpWp);

  
 //WZ

  TH1F* h_WZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Diboson/HTauTauTree_WZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_WZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZ->Scale(luminosity*XS_WZ/h_WZ_norm->Integral());
  h_WZ->SetNameTitle("h_WZ","h_WZ");
  h.push_back(h_WZ);


  //ZZ

  TH1F* h_ZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Diboson/HTauTauTree_ZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_ZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZ->Scale(luminosity*XS_ZZ/h_ZZ_norm->Integral());
  h_ZZ->SetNameTitle("h_ZZ","h_ZZ");
  h.push_back(h_ZZ);


  //Diboson = WZ + ZZ
  
  TH1F h_Diboson = *h_WZ;
  h_Diboson.Add(h_ZZ);
  h_Diboson.SetNameTitle("h_Diboson","h_Diboson");
  h.push_back(&h_Diboson);


  //ZZZ

  TH1F* h_ZZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_ZZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZZ->Scale(luminosity*XS_ZZZ/h_ZZZ_norm->Integral());
  h_ZZZ->SetNameTitle("h_ZZZ","h_ZZZ");
  h.push_back(h_ZZZ);



  //WZZ

  TH1F* h_WZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZZ->Scale(luminosity*XS_WZZ/h_WZZ_norm->Integral());
  h_WZZ->SetNameTitle("h_WZZ","h_WZZ");
  h.push_back(h_WZZ);



  //WWZ

  TH1F* h_WWZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WWZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WWZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WWZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WWZ->Scale(luminosity*XS_WWZ/h_WWZ_norm->Integral());
  h_WWZ->SetNameTitle("h_WWZ","h_WWZ");
  h.push_back(h_WWZ);


  //tZq

  TH1F* h_tZq =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_tZq_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_tZq_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_tZq_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_tZq->Scale(luminosity*XS_tZq/h_tZq_norm->Integral());
  h_tZq->SetNameTitle("h_tZq","h_tZq");
  h.push_back(h_tZq);



  //TTTT

  TH1F* h_TTTT =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/TTTT/HTauTauTree_TTTT_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTTT_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTTT/ntuple_TTTT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
  
  h_TTTT->Scale(luminosity*XS_TTTT/h_TTTT_norm->Integral());
  h_TTTT->SetNameTitle("h_TTTT","h_TTTT");
  h.push_back(h_TTTT);

  //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
  TH1F h_Rares = *h_ZZZ;
  h_Rares.Add(h_WZZ);
  h_Rares.Add(h_WWZ);
  h_Rares.Add(h_tZq);
  h_Rares.Add(h_TTTT);
  h_Rares.SetNameTitle("h_Rares","h_Rares");
  h.push_back(&h_Rares);



  //Fakes

  vector<TString> files_data;
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleEG_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleEG_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleMu_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleMu_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_MuonEG_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_MuonEG_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleEle_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleEle_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016C_split_trig_filt.root");

  TH1F* h_fakes =single_plot(files_data,
			     "HTauTauTree_2lSS_lepMVA_CR",
			     var,
			     "event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_fakes->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_fakes->SetNameTitle("h_fakes","h_fakes");

  h.push_back(h_fakes);

  //Fakes MC

  TH1F* h_fakes_DL_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/TTJets/HTauTauTree_ttbar_DL_split.root",
				   "HTauTauTree_2lSS_lepMVA_CR",
				   var,
				   "MC_weight*event_weight_ttH*(category==41)",
				   nbin,xmin,xmax);

  TH1F* h_fakes_DL_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					"HTauTauTree",
					"1",
					"MC_weight",
					3,0,2);
    
  h_fakes_DL_MC->Scale(luminosity*XS_TTJets_DL/h_fakes_DL_MC_norm->Integral());
  h_fakes_DL_MC->SetNameTitle("h_fakes_DL_MC","h_fakes_DL_MC");
  h.push_back(h_fakes_DL_MC);


  TH1F* h_fakes_SLfromT_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/TTJets/HTauTauTree_ttbar_SLfromT_split.root",
					"HTauTauTree_2lSS_lepMVA_CR",
					var,
					"MC_weight*event_weight_ttH*(category==41)",
					nbin,xmin,xmax);

  TH1F* h_fakes_SLfromT_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					     "HTauTauTree",
					     "1",
					     "MC_weight",
					     3,0,2);
    
  h_fakes_SLfromT_MC->Scale(luminosity*XS_TTJets_SLfromT/h_fakes_SLfromT_MC_norm->Integral());
  h_fakes_SLfromT_MC->SetNameTitle("h_fakes_SLfromT_MC","h_fakes_SLfromT_MC");
  h.push_back(h_fakes_SLfromT_MC);


  TH1F* h_fakes_SLfromTbar_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/TTJets/HTauTauTree_ttbar_SLfromTbar_split.root",
					"HTauTauTree_2lSS_lepMVA_CR",
					var,
					"MC_weight*event_weight_ttH*(category==41)",
					nbin,xmin,xmax);

  TH1F* h_fakes_SLfromTbar_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_SLfromTbar_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					     "HTauTauTree",
					     "1",
					     "MC_weight",
					     3,0,2);
    
  h_fakes_SLfromTbar_MC->Scale(luminosity*XS_TTJets_SLfromTbar/h_fakes_SLfromTbar_MC_norm->Integral());
  h_fakes_SLfromTbar_MC->SetNameTitle("h_fakes_SLfromTbar_MC","h_fakes_SLfromTbar_MC");
  h.push_back(h_fakes_SLfromTbar_MC);


  //Fakes MC
  TH1F h_fakes_MC = *h_fakes_DL_MC;
  h_fakes_MC.Add(h_fakes_SLfromT_MC);
  h_fakes_MC.Add(h_fakes_SLfromTbar_MC);
  h_fakes_MC.SetNameTitle("h_fakes_MC","h_fakes_MC");
  h.push_back(&h_fakes_MC);


  //Charge flips

  TH1F* h_flips =single_plot(files_data,
			     "HTauTauTree_2lOS_CR",
			     var,
			     "event_weight_ttH*(category==-11 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_flips->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_flips->SetNameTitle("h_flips","h_flips");
  h.push_back(h_flips);

  
  //Data

  /*TH1F* h_data_obs =single_plot(files_data,
				"HTauTauTree_2lSS",
				var,
				"(category==11 && recolep_sel_pt[0]>25 && isTrig)",
				nbin,xmin,xmax);

				h_data_obs->Scale(luminosity/8538.); //Data files for 8.5 fb-1

  h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(h_data_obs);*/

  TH1F h_data_obs = *h_ttH;
  h_data_obs.Add(h_ttW);
  h_data_obs.Add(&h_TTZ);
  h_data_obs.Add(h_WpWp);
  h_data_obs.Add(&h_Diboson);
  h_data_obs.Add(&h_Rares);
  h_data_obs.Add(h_fakes);
  h_data_obs.Add(h_flips);

  h_data_obs.SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(&h_data_obs);



  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_counting.root";

  TFile* f_new = TFile::Open(file,"RECREATE");


  for(unsigned int i=0;i<h.size();i++)
    h[i]->Write();

  f_new->Close();


}






void datacard_maker_MVA_2lSS_ttbar(){

  vector<TH1F*> h;
  

  TString var="MVA_2lSS_ttbar";

  
  int nbin = 10;
  float xmin = -1;
  float xmax = 1;


  //ttH

  TH1F* h_ttH =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttH/HTauTauTree_ttH_Hnonbb_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 &&  recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttH_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttH->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH->SetNameTitle("h_ttH","h_ttH");
  h.push_back(h_ttH);


  //ttW

  TH1F* h_ttW =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_ttW_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttW_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttW_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttW->Scale(luminosity*XS_ttW/h_ttW_norm->Integral());
  h_ttW->SetNameTitle("h_ttW","h_ttW");
  h.push_back(h_ttW);



  //ttZ

  TH1F* h_ttZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_ttZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttZ->Scale(luminosity*XS_ttZ/h_ttZ_norm->Integral());
  h_ttZ->SetNameTitle("h_ttZ","h_ttZ");
  h.push_back(h_ttZ);



  //TTLL low mass

  TH1F* h_TTLL_lowmass =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/topG/HTauTauTree_TTLL_lowmass_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTLL_lowmass_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_TTLL_lowmass_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					 "HTauTauTree",
					 "1",
					 "MC_weight",
					 3,0,2);
  
  h_TTLL_lowmass->Scale(luminosity*XS_TTLL_lowmass/h_TTLL_lowmass_norm->Integral());
  h_TTLL_lowmass->SetNameTitle("h_TTLL_lowmass","h_TTLL_lowmass");
  h.push_back(h_TTLL_lowmass);



  //ttG

  TH1F* h_ttG =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/topG/HTauTauTree_ttG_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttG_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_ttG_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ttG->Scale(luminosity*XS_ttG/h_ttG_norm->Integral());
  h_ttG->SetNameTitle("h_ttG","h_ttG");
  h.push_back(h_ttG);

  
  //TTZ = ttZ + TTLL_lowmass + ttG
  
  TH1F h_TTZ = *h_ttZ;
  h_TTZ.Add(h_TTLL_lowmass);
  h_TTZ.Add(h_ttG);
  h_TTZ.SetNameTitle("h_TTZ","h_TTZ");
  h.push_back(&h_TTZ);


  //WpWp

  TH1F* h_WpWp =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WpWp_split.root",
			    "HTauTauTree_2lSS",
			    var,
			    "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			    nbin,xmin,xmax);

  TH1F* h_WpWp_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WpWp_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
    
  h_WpWp->Scale(luminosity*XS_WpWp/h_WpWp_norm->Integral());
  h_WpWp->SetNameTitle("h_WpWp","h_WpWp");
  h.push_back(h_WpWp);

   //WZ

  TH1F* h_WZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Diboson/HTauTauTree_WZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_WZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZ->Scale(luminosity*XS_WZ/h_WZ_norm->Integral());
  h_WZ->SetNameTitle("h_WZ","h_WZ");
  h.push_back(h_WZ);


  //ZZ

  TH1F* h_ZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Diboson/HTauTauTree_ZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_ZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZ->Scale(luminosity*XS_ZZ/h_ZZ_norm->Integral());
  h_ZZ->SetNameTitle("h_ZZ","h_ZZ");
  h.push_back(h_ZZ);


  //Diboson = WZ + ZZ
  
  TH1F h_Diboson = *h_WZ;
  h_Diboson.Add(h_ZZ);
  h_Diboson.SetNameTitle("h_Diboson","h_Diboson");
  h.push_back(&h_Diboson);


  //ZZZ

  TH1F* h_ZZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_ZZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZZ->Scale(luminosity*XS_ZZZ/h_ZZZ_norm->Integral());
  h_ZZZ->SetNameTitle("h_ZZZ","h_ZZZ");
  h.push_back(h_ZZZ);



  //WZZ

  TH1F* h_WZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZZ->Scale(luminosity*XS_WZZ/h_WZZ_norm->Integral());
  h_WZZ->SetNameTitle("h_WZZ","h_WZZ");
  h.push_back(h_WZZ);



  //WWZ

  TH1F* h_WWZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WWZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WWZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WWZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WWZ->Scale(luminosity*XS_WWZ/h_WWZ_norm->Integral());
  h_WWZ->SetNameTitle("h_WWZ","h_WWZ");
  h.push_back(h_WWZ);


  //tZq

  TH1F* h_tZq =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_tZq_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_tZq_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_tZq_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_tZq->Scale(luminosity*XS_tZq/h_tZq_norm->Integral());
  h_tZq->SetNameTitle("h_tZq","h_tZq");
  h.push_back(h_tZq);



  //TTTT

  TH1F* h_TTTT =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/TTTT/HTauTauTree_TTTT_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTTT_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTTT/ntuple_TTTT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
  
  h_TTTT->Scale(luminosity*XS_TTTT/h_TTTT_norm->Integral());
  h_TTTT->SetNameTitle("h_TTTT","h_TTTT");
  h.push_back(h_TTTT);


  //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
  TH1F h_Rares = *h_ZZZ;
  h_Rares.Add(h_WZZ);
  h_Rares.Add(h_WWZ);
  h_Rares.Add(h_tZq);
  h_Rares.Add(h_TTTT);
  h_Rares.SetNameTitle("h_Rares","h_Rares");
  h.push_back(&h_Rares);

  //Fakes

  vector<TString> files_data;
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleEG_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleEG_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleMu_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleMu_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_MuonEG_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_MuonEG_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleEle_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleEle_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016C_split_trig_filt.root");


  TH1F* h_fakes =single_plot(files_data,
			     "HTauTauTree_2lSS_lepMVA_CR",
			     var,
			     "event_weight_ttH*(category==41  && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_fakes->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_fakes->SetNameTitle("h_fakes","h_fakes");
  h.push_back(h_fakes);


  //Charge flips

  TH1F* h_flips =single_plot(files_data,
			     "HTauTauTree_2lOS_CR",
			     var,
			     "event_weight_ttH*(category==-11 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_flips->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_flips->SetNameTitle("h_flips","h_flips");
  h.push_back(h_flips);


  //Data

  /*TH1F* h_data_obs =single_plot(files_data,
				"HTauTauTree_2lSS",
				var,
				"(category==11 && recolep_sel_pt[0]>25 && isTrig)",
				nbin,xmin,xmax);

  h_data_obs->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(h_data_obs);*/

  TH1F h_data_obs = *h_ttH;
  h_data_obs.Add(h_ttW);
  h_data_obs.Add(&h_TTZ);
  h_data_obs.Add(h_WpWp);
  h_data_obs.Add(&h_Diboson);
  h_data_obs.Add(&h_Rares);
  h_data_obs.Add(h_fakes);
  h_data_obs.Add(h_flips);

  h_data_obs.SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(&h_data_obs);

  
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_ttbar.root";

  TFile* f_new = TFile::Open(file,"RECREATE");


  for(unsigned int i=0;i<h.size();i++)
    h[i]->Write();

  f_new->Close();


}










void datacard_maker_MVA_2lSS_ttV(){

  vector<TH1F*> h;
  

  TString var="MVA_2lSS_ttV";

  
  int nbin = 10;
  float xmin = -1;
  float xmax = 1;


  //ttH

  TH1F* h_ttH =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttH/HTauTauTree_ttH_Hnonbb_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttH_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttH->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH->SetNameTitle("h_ttH","h_ttH");
  h.push_back(h_ttH);


  //ttW

  TH1F* h_ttW =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_ttW_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttW_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttW_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttW->Scale(luminosity*XS_ttW/h_ttW_norm->Integral());
  h_ttW->SetNameTitle("h_ttW","h_ttW");
  h.push_back(h_ttW);



  //ttZ

  TH1F* h_ttZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_ttZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttZ->Scale(luminosity*XS_ttZ/h_ttZ_norm->Integral());
  h_ttZ->SetNameTitle("h_ttZ","h_ttZ");
  h.push_back(h_ttZ);



  //TTLL low mass

  TH1F* h_TTLL_lowmass =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/topG/HTauTauTree_TTLL_lowmass_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTLL_lowmass_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_TTLL_lowmass_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					 "HTauTauTree",
					 "1",
					 "MC_weight",
					 3,0,2);
  
  h_TTLL_lowmass->Scale(luminosity*XS_TTLL_lowmass/h_TTLL_lowmass_norm->Integral());
  h_TTLL_lowmass->SetNameTitle("h_TTLL_lowmass","h_TTLL_lowmass");
  h.push_back(h_TTLL_lowmass);



  //ttG

  TH1F* h_ttG =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/topG/HTauTauTree_ttG_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttG_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_ttG_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ttG->Scale(luminosity*XS_ttG/h_ttG_norm->Integral());
  h_ttG->SetNameTitle("h_ttG","h_ttG");
  h.push_back(h_ttG);

  
  //TTZ = ttZ + TTLL_lowmass + ttG
  
  TH1F h_TTZ = *h_ttZ;
  h_TTZ.Add(h_TTLL_lowmass);
  h_TTZ.Add(h_ttG);
  h_TTZ.SetNameTitle("h_TTZ","h_TTZ");
  h.push_back(&h_TTZ);


  //WpWp

  TH1F* h_WpWp =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WpWp_split.root",
			    "HTauTauTree_2lSS",
			    var,
			    "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			    nbin,xmin,xmax);

  TH1F* h_WpWp_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WpWp_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
    
  h_WpWp->Scale(luminosity*XS_WpWp/h_WpWp_norm->Integral());
  h_WpWp->SetNameTitle("h_WpWp","h_WpWp");
  h.push_back(h_WpWp);

 //WZ

  TH1F* h_WZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Diboson/HTauTauTree_WZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_WZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZ->Scale(luminosity*XS_WZ/h_WZ_norm->Integral());
  h_WZ->SetNameTitle("h_WZ","h_WZ");
  h.push_back(h_WZ);


  //ZZ

  TH1F* h_ZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Diboson/HTauTauTree_ZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_ZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZ->Scale(luminosity*XS_ZZ/h_ZZ_norm->Integral());
  h_ZZ->SetNameTitle("h_ZZ","h_ZZ");
  h.push_back(h_ZZ);  


  //Diboson = WZ + ZZ
  
  TH1F h_Diboson = *h_WZ;
  h_Diboson.Add(h_ZZ);
  h_Diboson.SetNameTitle("h_Diboson","h_Diboson");
  h.push_back(&h_Diboson);

  //ZZZ

  TH1F* h_ZZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_ZZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZZ->Scale(luminosity*XS_ZZZ/h_ZZZ_norm->Integral());
  h_ZZZ->SetNameTitle("h_ZZZ","h_ZZZ");
  h.push_back(h_ZZZ);



  //WZZ

  TH1F* h_WZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WZZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZZ->Scale(luminosity*XS_WZZ/h_WZZ_norm->Integral());
  h_WZZ->SetNameTitle("h_WZZ","h_WZZ");
  h.push_back(h_WZZ);



  //WWZ

  TH1F* h_WWZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WWZ_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WWZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WWZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WWZ->Scale(luminosity*XS_WWZ/h_WWZ_norm->Integral());
  h_WWZ->SetNameTitle("h_WWZ","h_WWZ");
  h.push_back(h_WWZ);


  //tZq

  TH1F* h_tZq =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_tZq_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_tZq_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_tZq_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_tZq->Scale(luminosity*XS_tZq/h_tZq_norm->Integral());
  h_tZq->SetNameTitle("h_tZq","h_tZq");
  h.push_back(h_tZq);



  //TTTT

  TH1F* h_TTTT =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/TTTT/HTauTauTree_TTTT_split.root",
			   "HTauTauTree_2lSS",
			   var,
			   "MC_weight*(category==11 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTTT_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTTT/ntuple_TTTT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
  
  h_TTTT->Scale(luminosity*XS_TTTT/h_TTTT_norm->Integral());
  h_TTTT->SetNameTitle("h_TTTT","h_TTTT");
  h.push_back(h_TTTT);

  //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
  TH1F h_Rares = *h_ZZZ;
  h_Rares.Add(h_WZZ);
  h_Rares.Add(h_WWZ);
  h_Rares.Add(h_tZq);
  h_Rares.Add(h_TTTT);
  h_Rares.SetNameTitle("h_Rares","h_Rares");
  h.push_back(&h_Rares);

  //Fakes

  vector<TString> files_data;
 files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleEG_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleEG_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleMu_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_DoubleMu_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_MuonEG_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_MuonEG_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleEle_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleEle_2016C_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016B_split_trig_filt.root");
  files_data.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_splitted/Data/HTauTauTree_SingleMuon_2016C_split_trig_filt.root");


  TH1F* h_fakes =single_plot(files_data,
			     "HTauTauTree_2lSS_lepMVA_CR",
			     var,
			     "event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_fakes->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_fakes->SetNameTitle("h_fakes","h_fakes");
  h.push_back(h_fakes);


  //Charge flips

  TH1F* h_flips =single_plot(files_data,
			     "HTauTauTree_2lOS_CR",
			     var,
			     "event_weight_ttH*(category==-11 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_flips->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_flips->SetNameTitle("h_flips","h_flips");
  h.push_back(h_flips);


  //Data

  /*TH1F* h_data_obs =single_plot(files_data,
				"HTauTauTree_2lSS",
				var,
				"(category==11 && recolep_sel_pt[0]>25 && isTrig)",
				nbin,xmin,xmax);

  h_data_obs->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(h_data_obs);*/

  TH1F h_data_obs = *h_ttH;
  h_data_obs.Add(h_ttW);
  h_data_obs.Add(&h_TTZ);
  h_data_obs.Add(h_WpWp);
  h_data_obs.Add(&h_Diboson);
  h_data_obs.Add(&h_Rares);
  h_data_obs.Add(h_fakes);
  h_data_obs.Add(h_flips);

  h_data_obs.SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(&h_data_obs);

  
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_ttV.root";

  TFile* f_new = TFile::Open(file,"RECREATE");


  for(unsigned int i=0;i<h.size();i++)
    h[i]->Write();

  f_new->Close();


}









void datacard_maker_MEM_LR_nomiss(){

  vector<TH1F*> h;
  

  TString var="Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;

  /*TString var="-log(1-Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)))*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) + 40*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0 && Integral_ttH>0) - ((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0 && Integral_ttH==0)";

  int nbin = 43;
  float xmin = -2.;
  float xmax = 41.;*/


  //ttH
  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  TH1F* h_ttH =single_plot(files_ttH,
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttH_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttH->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH->SetNameTitle("h_ttH","h_ttH");
  h.push_back(h_ttH);


  TH1F* h_ttH_tautau =single_plot(files_ttH,
				  "T",
				  var,
				  "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && genH_decayMode[1]<=5)",
				  nbin,xmin,xmax);

  
  h_ttH_tautau->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_tautau->SetNameTitle("h_ttH_tautau","h_ttH_tautau");
  h.push_back(h_ttH_tautau);

  TH1F* h_ttH_boson =single_plot(files_ttH,
				 "T",
				 var,
				 "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && genH_decayMode[1]>5)",
				 nbin,xmin,xmax);
  
  
  h_ttH_boson->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_boson->SetNameTitle("h_ttH_boson","h_ttH_boson");
  h.push_back(h_ttH_boson);


  //ttW

  TH1F* h_ttW =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160708.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttW_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttW_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttW->Scale(luminosity*XS_ttW/h_ttW_norm->Integral());
  h_ttW->SetNameTitle("h_ttW","h_ttW");
  h.push_back(h_ttW);



  //ttZ

  TH1F* h_ttZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttZ_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttZ->Scale(luminosity*XS_ttZ/h_ttZ_norm->Integral());
  h_ttZ->SetNameTitle("h_ttZ","h_ttZ");
  h.push_back(h_ttZ);



  //TTLL low mass

  TH1F* h_TTLL_lowmass =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/TTLL_lowmass_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTLL_lowmass_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_TTLL_lowmass_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					 "HTauTauTree",
					 "1",
					 "MC_weight",
					 3,0,2);
  
  h_TTLL_lowmass->Scale(luminosity*XS_TTLL_lowmass/h_TTLL_lowmass_norm->Integral());
  h_TTLL_lowmass->SetNameTitle("h_TTLL_lowmass","h_TTLL_lowmass");
  h.push_back(h_TTLL_lowmass);



  //ttG

  TH1F* h_ttG =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttG/ttG_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttG_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_ttG_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ttG->Scale(luminosity*XS_ttG/h_ttG_norm->Integral());
  h_ttG->SetNameTitle("h_ttG","h_ttG");
  h.push_back(h_ttG);


  //TTZ = ttZ + TTLL_lowmass + ttG
  
  TH1F h_TTZ = *h_ttZ;
  h_TTZ.Add(h_TTLL_lowmass);
  h_TTZ.Add(h_ttG);
  h_TTZ.SetNameTitle("h_TTZ","h_TTZ");
  h.push_back(&h_TTZ);  



  //WpWp

  TH1F* h_WpWp =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WpWp_2lSS_MEM_160719.root",
			    "T",
			    var,
			    "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			    nbin,xmin,xmax);

  TH1F* h_WpWp_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WpWp_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
    
  h_WpWp->Scale(luminosity*XS_WpWp/h_WpWp_norm->Integral());
  h_WpWp->SetNameTitle("h_WpWp","h_WpWp");
  h.push_back(h_WpWp);

  
  //WZ

  TH1F* h_WZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Diboson/WZ_split_2lSS_MEM_160805.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_WZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZ->Scale(luminosity*XS_WZ/h_WZ_norm->Integral());
  h_WZ->SetNameTitle("h_WZ","h_WZ");
  h.push_back(h_WZ);


  //ZZ

  TH1F* h_ZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Diboson/ZZ_split_2lSS_MEM_160804.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_ZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZ->Scale(luminosity*XS_ZZ/h_ZZ_norm->Integral());
  h_ZZ->SetNameTitle("h_ZZ","h_ZZ");
  h.push_back(h_ZZ);

  //Diboson = WZ + ZZ
  
  TH1F h_Diboson = *h_WZ;
  h_Diboson.Add(h_ZZ);
  h_Diboson.SetNameTitle("h_Diboson","h_Diboson");
  h.push_back(&h_Diboson);

  //ZZZ

  TH1F* h_ZZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/ZZZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZZ->Scale(luminosity*XS_ZZZ/h_ZZZ_norm->Integral());
  h_ZZZ->SetNameTitle("h_ZZZ","h_ZZZ");
  h.push_back(h_ZZZ);



  //WZZ

  TH1F* h_WZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WZZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZZ->Scale(luminosity*XS_WZZ/h_WZZ_norm->Integral());
  h_WZZ->SetNameTitle("h_WZZ","h_WZZ");
  h.push_back(h_WZZ);



  //WWZ

  TH1F* h_WWZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WWZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WWZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WWZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WWZ->Scale(luminosity*XS_WWZ/h_WWZ_norm->Integral());
  h_WWZ->SetNameTitle("h_WWZ","h_WWZ");
  h.push_back(h_WWZ);


  //tZq

  TH1F* h_tZq =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/tZq_split_2lSS_MEM_160722.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_tZq_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_tZq_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_tZq->Scale(luminosity*XS_tZq/h_tZq_norm->Integral());
  h_tZq->SetNameTitle("h_tZq","h_tZq");
  h.push_back(h_tZq);



  //TTTT

  TH1F* h_TTTT =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTTT/TTTT_split_2lSS_MEM_160722.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTTT_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTTT/ntuple_TTTT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
  
  h_TTTT->Scale(luminosity*XS_TTTT/h_TTTT_norm->Integral());
  h_TTTT->SetNameTitle("h_TTTT","h_TTTT");
  h.push_back(h_TTTT);

  //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
  TH1F h_Rares = *h_ZZZ;
  h_Rares.Add(h_WZZ);
  h_Rares.Add(h_WWZ);
  h_Rares.Add(h_tZq);
  h_Rares.Add(h_TTTT);
  h_Rares.SetNameTitle("h_Rares","h_Rares");
  h.push_back(&h_Rares);

  //Fakes

  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");


  TH1F* h_fakes =single_plot(files_data_fakes,
			     "T",
			     var,
			     "event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_fakes->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_fakes->SetNameTitle("h_fakes","h_fakes");

  h.push_back(h_fakes);

  //Fakes MC

  TH1F* h_fakes_DL_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root",
				   "T",
				   var,
				   "MC_weight*event_weight_ttH*(category==41 && integration_type==0)",
				   nbin,xmin,xmax);

  TH1F* h_fakes_DL_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					"HTauTauTree",
					"1",
					"MC_weight",
					3,0,2);
    
  h_fakes_DL_MC->Scale(luminosity*XS_TTJets_DL/h_fakes_DL_MC_norm->Integral());
  h_fakes_DL_MC->SetNameTitle("h_fakes_DL_MC","h_fakes_DL_MC");
  h.push_back(h_fakes_DL_MC);


  TH1F* h_fakes_SLfromT_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160718.root",
					"T",
					var,
					"MC_weight*event_weight_ttH*(category==41 && integration_type==0)",
					nbin,xmin,xmax);

  TH1F* h_fakes_SLfromT_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					     "HTauTauTree",
					     "1",
					     "MC_weight",
					     3,0,2);
    
  h_fakes_SLfromT_MC->Scale(luminosity*XS_TTJets_SLfromT/h_fakes_SLfromT_MC_norm->Integral());
  h_fakes_SLfromT_MC->SetNameTitle("h_fakes_SLfromT_MC","h_fakes_SLfromT_MC");
  h.push_back(h_fakes_SLfromT_MC);


  TH1F* h_fakes_SLfromTbar_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160718.root",
					"T",
					var,
					"MC_weight*event_weight_ttH*(category==41 && integration_type==0)",
					nbin,xmin,xmax);

  TH1F* h_fakes_SLfromTbar_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_SLfromTbar_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					     "HTauTauTree",
					     "1",
					     "MC_weight",
					     3,0,2);
    
  h_fakes_SLfromTbar_MC->Scale(luminosity*XS_TTJets_SLfromTbar/h_fakes_SLfromTbar_MC_norm->Integral());
  h_fakes_SLfromTbar_MC->SetNameTitle("h_fakes_SLfromTbar_MC","h_fakes_SLfromTbar_MC");
  h.push_back(h_fakes_SLfromTbar_MC);


  //Fakes MC
  TH1F h_fakes_MC = *h_fakes_DL_MC;
  h_fakes_MC.Add(h_fakes_SLfromT_MC);
  h_fakes_MC.Add(h_fakes_SLfromTbar_MC);
  h_fakes_MC.SetNameTitle("h_fakes_MC","h_fakes_MC");
  h.push_back(&h_fakes_MC);


  //Charge flips


  vector<TString> files_data_flips;
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lOS_CR_MEM_160804_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lOS_CR_MEM_160804_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");



  TH1F* h_flips =single_plot(files_data_flips,
			     "T",
			     var,
			     "event_weight_ttH*(category==-11 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_flips->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_flips->SetNameTitle("h_flips","h_flips");
  h.push_back(h_flips);


//Data

  /*TH1F* h_data_obs =single_plot(files_data,
				"HTauTauTree_2lSS",
				var,
				"(category==11 && recolep_sel_pt[0]>25 && isTrig)",
				nbin,xmin,xmax);

  h_data_obs->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(h_data_obs);*/

  TH1F h_data_obs = *h_ttH;
  h_data_obs.Add(h_ttW);
  h_data_obs.Add(&h_TTZ);
  h_data_obs.Add(h_WpWp);
  h_data_obs.Add(&h_Diboson);
  h_data_obs.Add(&h_Rares);
  h_data_obs.Add(h_fakes);
  h_data_obs.Add(h_flips);

  h_data_obs.SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(&h_data_obs);
  
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_nomiss.root";

  TFile* f_new = TFile::Open(file,"RECREATE");


  for(unsigned int i=0;i<h.size();i++)
    h[i]->Write();

  f_new->Close();


}








void datacard_maker_MEM_LR_missingjet(){

  vector<TH1F*> h;
  

  TString var="Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;


  //ttH
  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  TH1F* h_ttH =single_plot(files_ttH,
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttH_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttH->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH->SetNameTitle("h_ttH","h_ttH");
  h.push_back(h_ttH);

 TH1F* h_ttH_tautau =single_plot(files_ttH,
				  "T",
				  var,
				  "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && genH_decayMode[1]<=5)",
				  nbin,xmin,xmax);

  
  h_ttH_tautau->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_tautau->SetNameTitle("h_ttH_tautau","h_ttH_tautau");
  h.push_back(h_ttH_tautau);

  TH1F* h_ttH_boson =single_plot(files_ttH,
				 "T",
				 var,
				 "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && genH_decayMode[1]>5)",
				 nbin,xmin,xmax);
  
  
  h_ttH_boson->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_boson->SetNameTitle("h_ttH_boson","h_ttH_boson");
  h.push_back(h_ttH_boson);


  //ttW

  TH1F* h_ttW =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160708.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttW_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttW_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttW->Scale(luminosity*XS_ttW/h_ttW_norm->Integral());
  h_ttW->SetNameTitle("h_ttW","h_ttW");
  h.push_back(h_ttW);



  //ttZ

  TH1F* h_ttZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttZ_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttZ->Scale(luminosity*XS_ttZ/h_ttZ_norm->Integral());
  h_ttZ->SetNameTitle("h_ttZ","h_ttZ");
  h.push_back(h_ttZ);



  //TTLL low mass

  TH1F* h_TTLL_lowmass =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/TTLL_lowmass_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTLL_lowmass_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_TTLL_lowmass_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					 "HTauTauTree",
					 "1",
					 "MC_weight",
					 3,0,2);
  
  h_TTLL_lowmass->Scale(luminosity*XS_TTLL_lowmass/h_TTLL_lowmass_norm->Integral());
  h_TTLL_lowmass->SetNameTitle("h_TTLL_lowmass","h_TTLL_lowmass");
  h.push_back(h_TTLL_lowmass);



  //ttG

  TH1F* h_ttG =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttG/ttG_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttG_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_ttG_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ttG->Scale(luminosity*XS_ttG/h_ttG_norm->Integral());
  h_ttG->SetNameTitle("h_ttG","h_ttG");
  h.push_back(h_ttG);


  //TTZ = ttZ + TTLL_lowmass + ttG
  
  TH1F h_TTZ = *h_ttZ;
  h_TTZ.Add(h_TTLL_lowmass);
  h_TTZ.Add(h_ttG);
  h_TTZ.SetNameTitle("h_TTZ","h_TTZ");
  h.push_back(&h_TTZ);  
  

  //WpWp

  TH1F* h_WpWp =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WpWp_2lSS_MEM_160719.root",
			    "T",
			    var,
			    "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			    nbin,xmin,xmax);

  TH1F* h_WpWp_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WpWp_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
    
  h_WpWp->Scale(luminosity*XS_WpWp/h_WpWp_norm->Integral());
  h_WpWp->SetNameTitle("h_WpWp","h_WpWp");
  h.push_back(h_WpWp);


  //WZ
  
  TH1F* h_WZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Diboson/WZ_split_2lSS_MEM_160805.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_WZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZ->Scale(luminosity*XS_WZ/h_WZ_norm->Integral());
  h_WZ->SetNameTitle("h_WZ","h_WZ");
  h.push_back(h_WZ);


  //ZZ

  TH1F* h_ZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Diboson/ZZ_split_2lSS_MEM_160804.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_ZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZ->Scale(luminosity*XS_ZZ/h_ZZ_norm->Integral());
  h_ZZ->SetNameTitle("h_ZZ","h_ZZ");
  h.push_back(h_ZZ);

  //Diboson = WZ + ZZ
  
  TH1F h_Diboson = *h_WZ;
  h_Diboson.Add(h_ZZ);
  h_Diboson.SetNameTitle("h_Diboson","h_Diboson");
  h.push_back(&h_Diboson);

  //ZZZ

  TH1F* h_ZZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/ZZZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZZ->Scale(luminosity*XS_ZZZ/h_ZZZ_norm->Integral());
  h_ZZZ->SetNameTitle("h_ZZZ","h_ZZZ");
  h.push_back(h_ZZZ);



  //WZZ

  TH1F* h_WZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WZZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZZ->Scale(luminosity*XS_WZZ/h_WZZ_norm->Integral());
  h_WZZ->SetNameTitle("h_WZZ","h_WZZ");
  h.push_back(h_WZZ);



  //WWZ

  TH1F* h_WWZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WWZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WWZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WWZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WWZ->Scale(luminosity*XS_WWZ/h_WWZ_norm->Integral());
  h_WWZ->SetNameTitle("h_WWZ","h_WWZ");
  h.push_back(h_WWZ);


  //tZq

  TH1F* h_tZq =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/tZq_split_2lSS_MEM_160722.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_tZq_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_tZq_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_tZq->Scale(luminosity*XS_tZq/h_tZq_norm->Integral());
  h_tZq->SetNameTitle("h_tZq","h_tZq");
  h.push_back(h_tZq);



  //TTTT

  TH1F* h_TTTT =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTTT/TTTT_split_2lSS_MEM_160722.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTTT_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTTT/ntuple_TTTT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
  
  h_TTTT->Scale(luminosity*XS_TTTT/h_TTTT_norm->Integral());
  h_TTTT->SetNameTitle("h_TTTT","h_TTTT");
  h.push_back(h_TTTT);

  //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
  TH1F h_Rares = *h_ZZZ;
  h_Rares.Add(h_WZZ);
  h_Rares.Add(h_WWZ);
  h_Rares.Add(h_tZq);
  h_Rares.Add(h_TTTT);
  h_Rares.SetNameTitle("h_Rares","h_Rares");
  h.push_back(&h_Rares);


  //Fakes

  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");



  TH1F* h_fakes =single_plot(files_data_fakes,
			     "T",
			     var,
			     "event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_fakes->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_fakes->SetNameTitle("h_fakes","h_fakes");

  h.push_back(h_fakes);


  //Fakes MC

  TH1F* h_fakes_DL_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root",
				   "T",
				   var,
				   "MC_weight*event_weight_ttH*(category==41 && integration_type==1)",
				   nbin,xmin,xmax);

  TH1F* h_fakes_DL_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_DL_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					"HTauTauTree",
					"1",
					"MC_weight",
					3,0,2);
    
  h_fakes_DL_MC->Scale(luminosity*XS_TTJets_DL/h_fakes_DL_MC_norm->Integral());
  h_fakes_DL_MC->SetNameTitle("h_fakes_DL_MC","h_fakes_DL_MC");
  h.push_back(h_fakes_DL_MC);


  TH1F* h_fakes_SLfromT_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160718.root",
					"T",
					var,
					"MC_weight*event_weight_ttH*(category==41 && && integration_type==1)",
					nbin,xmin,xmax);

  TH1F* h_fakes_SLfromT_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_SLfromT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					     "HTauTauTree",
					     "1",
					     "MC_weight",
					     3,0,2);
    
  h_fakes_SLfromT_MC->Scale(luminosity*XS_TTJets_SLfromT/h_fakes_SLfromT_MC_norm->Integral());
  h_fakes_SLfromT_MC->SetNameTitle("h_fakes_SLfromT_MC","h_fakes_SLfromT_MC");
  h.push_back(h_fakes_SLfromT_MC);


  TH1F* h_fakes_SLfromTbar_MC =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160718.root",
					"T",
					var,
					"MC_weight*event_weight_ttH*(category==41 && integration_type==1)",
					nbin,xmin,xmax);

  TH1F* h_fakes_SLfromTbar_MC_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTJets/ntuple_ttbar_SLfromTbar_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					     "HTauTauTree",
					     "1",
					     "MC_weight",
					     3,0,2);
    
  h_fakes_SLfromTbar_MC->Scale(luminosity*XS_TTJets_SLfromTbar/h_fakes_SLfromTbar_MC_norm->Integral());
  h_fakes_SLfromTbar_MC->SetNameTitle("h_fakes_SLfromTbar_MC","h_fakes_SLfromTbar_MC");
  h.push_back(h_fakes_SLfromTbar_MC);


  //Fakes MC
  TH1F h_fakes_MC = *h_fakes_DL_MC;
  h_fakes_MC.Add(h_fakes_SLfromT_MC);
  h_fakes_MC.Add(h_fakes_SLfromTbar_MC);
  h_fakes_MC.SetNameTitle("h_fakes_MC","h_fakes_MC");
  h.push_back(&h_fakes_MC);



  //Charge flips


  vector<TString> files_data_flips;
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lOS_CR_MEM_160804_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lOS_CR_MEM_160804_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");


  TH1F* h_flips =single_plot(files_data_flips,
			     "T",
			     var,
			     "event_weight_ttH*(category==-11 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_flips->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_flips->SetNameTitle("h_flips","h_flips");
  h.push_back(h_flips);


//Data

  /*TH1F* h_data_obs =single_plot(files_data,
				"HTauTauTree_2lSS",
				var,
				"(category==11 && recolep_sel_pt[0]>25 && isTrig)",
				nbin,xmin,xmax);

  h_data_obs->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(h_data_obs);*/

  TH1F h_data_obs = *h_ttH;
  h_data_obs.Add(h_ttW);
  h_data_obs.Add(&h_TTZ);
  h_data_obs.Add(h_WpWp);
  h_data_obs.Add(&h_Diboson);
  h_data_obs.Add(&h_Rares);
  h_data_obs.Add(h_fakes);
  h_data_obs.Add(h_flips);

  h_data_obs.SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(&h_data_obs);
  
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_missingjet.root";

  TFile* f_new = TFile::Open(file,"RECREATE");


  for(unsigned int i=0;i<h.size();i++)
    h[i]->Write();

  f_new->Close();


}





void datacard_maker_MEM_LR_1cat(){

  vector<TH1F*> h;

  TString file_nomiss="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_nomiss.root";
  TString file_miss="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_missingjet.root";

  TFile* f_nomiss = TFile::Open(file_nomiss);
  TFile* f_miss = TFile::Open(file_miss);

  TH1F* h_flips = (TH1F*)f_nomiss->Get("h_flips");
  h_flips->Add( (TH1F*)f_miss->Get("h_flips") );
  h.push_back(h_flips);

  TH1F* h_fakes = (TH1F*)f_nomiss->Get("h_fakes");
  h_fakes->Add( (TH1F*)f_miss->Get("h_fakes") );
  h.push_back(h_fakes);

  TH1F* h_Rares = (TH1F*)f_nomiss->Get("h_Rares");
  h_Rares->Add( (TH1F*)f_miss->Get("h_Rares") );
  h.push_back(h_Rares);

  TH1F* h_WpWp = (TH1F*)f_nomiss->Get("h_WpWp");
  h_WpWp->Add( (TH1F*)f_miss->Get("h_WpWp") );
  h.push_back(h_WpWp);

  TH1F* h_Diboson = (TH1F*)f_nomiss->Get("h_Diboson");
  h_Diboson->Add( (TH1F*)f_miss->Get("h_Diboson") );
  h.push_back(h_Diboson);

  TH1F* h_TTZ = (TH1F*)f_nomiss->Get("h_TTZ");
  h_TTZ->Add( (TH1F*)f_miss->Get("h_TTZ") );
  h.push_back(h_TTZ);

  TH1F* h_ttW = (TH1F*)f_nomiss->Get("h_ttW");
  h_ttW->Add( (TH1F*)f_miss->Get("h_ttW") );
  h.push_back(h_ttW);

  TH1F* h_ttH = (TH1F*)f_nomiss->Get("h_ttH");
  h_ttH->Add( (TH1F*)f_miss->Get("h_ttH") );
  h.push_back(h_ttH);

  TH1F* h_ttH_tautau = (TH1F*)f_nomiss->Get("h_ttH_tautau");
  h_ttH_tautau->Add( (TH1F*)f_miss->Get("h_ttH_tautau") );
  h.push_back(h_ttH_tautau);

  TH1F* h_ttH_boson = (TH1F*)f_nomiss->Get("h_ttH_boson");
  h_ttH_boson->Add( (TH1F*)f_miss->Get("h_ttH_boson") );
  h.push_back(h_ttH_boson);

  TH1F* h_data_obs = (TH1F*)f_nomiss->Get("h_data_obs");
  h_data_obs->Add( (TH1F*)f_miss->Get("h_data_obs") );
  h.push_back(h_data_obs);

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR.root";

  TFile* f_new = TFile::Open(file,"RECREATE");

  for(unsigned int i=0;i<h.size();i++)
    h[i]->Write();

  f_new->Close();
  f_miss->Close();
  f_nomiss->Close();

}






void datacard_maker_MVA_2lSS_all_multilep_cat(){
  

  TString var="1*(MVA_2lSS_ttbar>-1 && MVA_2lSS_ttbar<=-0.2 && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=1) + 2*(MVA_2lSS_ttbar>-0.2 && MVA_2lSS_ttbar<=0.1 && MVA_2lSS_ttV>-1 && MVA_2lSS_ttV<=1) + 3*(MVA_2lSS_ttbar>0.1 && MVA_2lSS_ttbar<=0.4 && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=0.3) + 4*(MVA_2lSS_ttbar>0.1 && MVA_2lSS_ttbar<=0.4 && MVA_2lSS_ttV>0.3 && MVA_2lSS_ttV<=1) + 5*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=0.1) + 6*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>0.1 && MVA_2lSS_ttV<=0.4) + 7*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>0.4 && MVA_2lSS_ttV<=1)";

  
  int nbin = 7;
  float xmin = 0.5;
  float xmax = 7.5;


  vector<TString> cat_names;
  cat_names.push_back("ttH_2lss_1tau");
  cat_names.push_back("ttH_2lss_ee_0tau_neg");
  cat_names.push_back("ttH_2lss_ee_0tau_pos");
  cat_names.push_back("ttH_2lss_em_0tau_bl_neg");
  cat_names.push_back("ttH_2lss_em_0tau_bl_pos");
  cat_names.push_back("ttH_2lss_em_0tau_bt_neg");
  cat_names.push_back("ttH_2lss_em_0tau_bt_pos");
  cat_names.push_back("ttH_2lss_mm_0tau_bl_neg");
  cat_names.push_back("ttH_2lss_mm_0tau_bl_pos");
  cat_names.push_back("ttH_2lss_mm_0tau_bt_neg");
  cat_names.push_back("ttH_2lss_mm_0tau_bt_pos");
  cat_names.push_back("ttH_3l_bl_neg");
  cat_names.push_back("ttH_3l_bl_pos");
  cat_names.push_back("ttH_3l_bt_neg");
  cat_names.push_back("ttH_3l_bt_pos");

  vector<int> cat;
  cat.push_back(11);
  cat.push_back(10);
  cat.push_back(9);
  cat.push_back(8);
  cat.push_back(7);
  cat.push_back(6);
  cat.push_back(5);
  cat.push_back(4);
  cat.push_back(3);
  cat.push_back(2);
  cat.push_back(1);
  cat.push_back(15);
  cat.push_back(14);
  cat.push_back(13);
  cat.push_back(12);
  

  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MVA_2lSS_allcat.root";

  TFile* f_new = TFile::Open(file,"RECREATE");

  for(unsigned int i=0;i<cat_names.size();i++){

    cout<<cat_names[i]<<endl;

    TDirectory* dir = f_new->mkdir(cat_names[i]);
    dir->cd();

    vector<TH1F*> h;

    //ttH
    
    TH1F* h_ttH =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted_v2/ttH/HTauTauTree_ttH_Hnonbb_split.root",
			     "HTauTauTree_2lSS",
			     var,
			     Form("MC_weight*(category==%i)",cat[i]),
			     nbin,xmin,xmax);
    
    TH1F* h_ttH_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				  "HTauTauTree",
				  "1",
				  "MC_weight",
				  3,0,2);
    
    h_ttH->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
    h_ttH->SetNameTitle("h_ttH","h_ttH");
    h.push_back(h_ttH);
    

    /*
    //ttW
    
    TH1F* h_ttW =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_ttW_split.root",
			     "HTauTauTree_2lSS",
			     var,
			     Form("MC_weight*(category==%i)",cat[i]),
			   nbin,xmin,xmax);
    
    TH1F* h_ttW_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttW_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				  "HTauTauTree",
				  "1",
				  "MC_weight",
				  3,0,2);
    
    h_ttW->Scale(luminosity*XS_ttW/h_ttW_norm->Integral());
    h_ttW->SetNameTitle("h_ttW","h_ttW");
    h.push_back(h_ttW);

    
    
    //ttZ
    
    TH1F* h_ttZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_ttZ_split.root",
			     "HTauTauTree_2lSS",
			     var,
			     Form("MC_weight*(category==%i)",cat[i]),
			     nbin,xmin,xmax);
    
    TH1F* h_ttZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				  "HTauTauTree",
				  "1",
				  "MC_weight",
				  3,0,2);
    
    h_ttZ->Scale(luminosity*XS_ttZ/h_ttZ_norm->Integral());
    h_ttZ->SetNameTitle("h_ttZ","h_ttZ");
    h.push_back(h_ttZ);
    
    
    
    //TTLL low mass
    
    TH1F* h_TTLL_lowmass =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/topG/HTauTauTree_TTLL_lowmass_split.root",
				      "HTauTauTree_2lSS",
				      var,
				      Form("MC_weight*(category==%i)",cat[i]),
				      nbin,xmin,xmax);
    
    TH1F* h_TTLL_lowmass_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_TTLL_lowmass_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					   "HTauTauTree",
					   "1",
					   "MC_weight",
					   3,0,2);
    
    h_TTLL_lowmass->Scale(luminosity*XS_TTLL_lowmass/h_TTLL_lowmass_norm->Integral());
    h_TTLL_lowmass->SetNameTitle("h_TTLL_lowmass","h_TTLL_lowmass");
    h.push_back(h_TTLL_lowmass);
    
    
    
    //ttG
    
    TH1F* h_ttG =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/topG/HTauTauTree_ttG_split.root",
			     "HTauTauTree_2lSS",
			     var,
			     Form("MC_weight*(category==%i)",cat[i]),
			     nbin,xmin,xmax);
    
    TH1F* h_ttG_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_ttG_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				  "HTauTauTree",
				  "1",
				  "MC_weight",
				  3,0,2);
    
    h_ttG->Scale(luminosity*XS_ttG/h_ttG_norm->Integral());
    h_ttG->SetNameTitle("h_ttG","h_ttG");
    h.push_back(h_ttG);
    
    
    
    //WpWp
    
    TH1F* h_WpWp =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WpWp_split.root",
			      "HTauTauTree_2lSS",
			      var,
			      Form("MC_weight*(category==%i)",cat[i]),
			      nbin,xmin,xmax);
    
    TH1F* h_WpWp_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WpWp_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				   "HTauTauTree",
				   "1",
				   "MC_weight",
				   3,0,2);
    
    h_WpWp->Scale(luminosity*XS_WpWp/h_WpWp_norm->Integral());
    h_WpWp->SetNameTitle("h_WpWp","h_WpWp");
    h.push_back(h_WpWp);
    
    
    
    
    //ZZZ
    
    TH1F* h_ZZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_ZZZ_split.root",
			     "HTauTauTree_2lSS",
			     var,
			     Form("MC_weight*(category==%i)",cat[i]),
			     nbin,xmin,xmax);
    
    TH1F* h_ZZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				  "HTauTauTree",
				  "1",
				  "MC_weight",
				  3,0,2);
    
    h_ZZZ->Scale(luminosity*XS_ZZZ/h_ZZZ_norm->Integral());
    h_ZZZ->SetNameTitle("h_ZZZ","h_ZZZ");
    h.push_back(h_ZZZ);
    
    
    
    //WZZ
    
    TH1F* h_WZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WZZ_split.root",
			     "HTauTauTree_2lSS",
			     var,
			     Form("MC_weight*(category==%i)",cat[i]),
			     nbin,xmin,xmax);
    
    TH1F* h_WZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				  "HTauTauTree",
				  "1",
				  "MC_weight",
				  3,0,2);
    
    h_WZZ->Scale(luminosity*XS_WZZ/h_WZZ_norm->Integral());
    h_WZZ->SetNameTitle("h_WZZ","h_WZZ");
    h.push_back(h_WZZ);
    
    
    
    //WWZ
    
    TH1F* h_WWZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/Rares_EW/HTauTauTree_WWZ_split.root",
			     "HTauTauTree_2lSS",
			     var,
			     Form("MC_weight*(category==%i)",cat[i]),
			     nbin,xmin,xmax);
    
    TH1F* h_WWZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WWZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				  "HTauTauTree",
				  "1",
				  "MC_weight",
				  3,0,2);
    
    h_WWZ->Scale(luminosity*XS_WWZ/h_WWZ_norm->Integral());
    h_WWZ->SetNameTitle("h_WWZ","h_WWZ");
    h.push_back(h_WWZ);
    
    
    //tZq
    
    TH1F* h_tZq =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/ttV/HTauTauTree_tZq_split.root",
			     "HTauTauTree_2lSS",
			     var,
			     Form("MC_weight*(category==%i)",cat[i]),
			     nbin,xmin,xmax);
    
    TH1F* h_tZq_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_tZq_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				  "HTauTauTree",
				  "1",
				  "MC_weight",
				  3,0,2);
    
    h_tZq->Scale(luminosity*XS_tZq/h_tZq_norm->Integral());
    h_tZq->SetNameTitle("h_tZq","h_tZq");
    h.push_back(h_tZq);
    
    
    
    //TTTT
    
    TH1F* h_TTTT =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_splitted/TTTT/HTauTauTree_TTTT_split.root",
			      "HTauTauTree_2lSS",
			      var,
			      Form("MC_weight*(category==%i)",cat[i]),
			      nbin,xmin,xmax);
    
    TH1F* h_TTTT_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTTT/ntuple_TTTT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				   "HTauTauTree",
				   "1",
				   "MC_weight",
				   3,0,2);
    
    h_TTTT->Scale(luminosity*XS_TTTT/h_TTTT_norm->Integral());
    h_TTTT->SetNameTitle("h_TTTT","h_TTTT");
    h.push_back(h_TTTT);*/
    
    
    
    for(unsigned int i=0;i<h.size();i++)
      h[i]->Write();


    f_new->cd();
    

  }


  f_new->Close();




}











void datacard_maker_MEM_LR_nomiss_tauOS(){

  vector<TH1F*> h;
  

  TString var="Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;

  /*TString var="-log(1-Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)))*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) + 40*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0 && Integral_ttH>0) - ((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0 && Integral_ttH==0)";

  int nbin = 43;
  float xmin = -2.;
  float xmax = 41.;*/


  //ttH
  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  TH1F* h_ttH =single_plot(files_ttH,
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_ttH_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttH->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH->SetNameTitle("h_ttH","h_ttH");
  h.push_back(h_ttH);


  TH1F* h_ttH_tautau =single_plot(files_ttH,
				  "T",
				  var,
				  "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25  && recolep_sel_charge[0]*recotauh_sel_charge[0]<0 && genH_decayMode[1]<=5)",
				  nbin,xmin,xmax);

  
  h_ttH_tautau->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_tautau->SetNameTitle("h_ttH_tautau","h_ttH_tautau");
  h.push_back(h_ttH_tautau);

  TH1F* h_ttH_boson =single_plot(files_ttH,
				 "T",
				 var,
				 "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25  && recolep_sel_charge[0]*recotauh_sel_charge[0]<0 && genH_decayMode[1]>5)",
				 nbin,xmin,xmax);
  
  
  h_ttH_boson->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_boson->SetNameTitle("h_ttH_boson","h_ttH_boson");
  h.push_back(h_ttH_boson);


  //ttW

  TH1F* h_ttW =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160708.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_ttW_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttW_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttW->Scale(luminosity*XS_ttW/h_ttW_norm->Integral());
  h_ttW->SetNameTitle("h_ttW","h_ttW");
  h.push_back(h_ttW);



  //ttZ

  TH1F* h_ttZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttZ_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_ttZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttZ->Scale(luminosity*XS_ttZ/h_ttZ_norm->Integral());
  h_ttZ->SetNameTitle("h_ttZ","h_ttZ");
  h.push_back(h_ttZ);



  //TTLL low mass

  TH1F* h_TTLL_lowmass =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/TTLL_lowmass_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_TTLL_lowmass_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_TTLL_lowmass_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					 "HTauTauTree",
					 "1",
					 "MC_weight",
					 3,0,2);
  
  h_TTLL_lowmass->Scale(luminosity*XS_TTLL_lowmass/h_TTLL_lowmass_norm->Integral());
  h_TTLL_lowmass->SetNameTitle("h_TTLL_lowmass","h_TTLL_lowmass");
  h.push_back(h_TTLL_lowmass);



  //ttG

  TH1F* h_ttG =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttG/ttG_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_ttG_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_ttG_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ttG->Scale(luminosity*XS_ttG/h_ttG_norm->Integral());
  h_ttG->SetNameTitle("h_ttG","h_ttG");
  h.push_back(h_ttG);


  //TTZ = ttZ + TTLL_lowmass + ttG
  
  TH1F h_TTZ = *h_ttZ;
  h_TTZ.Add(h_TTLL_lowmass);
  h_TTZ.Add(h_ttG);
  h_TTZ.SetNameTitle("h_TTZ","h_TTZ");
  h.push_back(&h_TTZ);  



  //WpWp

  TH1F* h_WpWp =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WpWp_2lSS_MEM_160719.root",
			    "T",
			    var,
			    "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			    nbin,xmin,xmax);

  TH1F* h_WpWp_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WpWp_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
    
  h_WpWp->Scale(luminosity*XS_WpWp/h_WpWp_norm->Integral());
  h_WpWp->SetNameTitle("h_WpWp","h_WpWp");
  h.push_back(h_WpWp);

  
  //WZ

  TH1F* h_WZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Diboson/WZ_split_2lSS_MEM_160805.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_WZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_WZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZ->Scale(luminosity*XS_WZ/h_WZ_norm->Integral());
  h_WZ->SetNameTitle("h_WZ","h_WZ");
  h.push_back(h_WZ);


  //ZZ

  TH1F* h_ZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Diboson/ZZ_split_2lSS_MEM_160804.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_ZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_ZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZ->Scale(luminosity*XS_ZZ/h_ZZ_norm->Integral());
  h_ZZ->SetNameTitle("h_ZZ","h_ZZ");
  h.push_back(h_ZZ);

  //Diboson = WZ + ZZ
  
  TH1F h_Diboson = *h_WZ;
  h_Diboson.Add(h_ZZ);
  h_Diboson.SetNameTitle("h_Diboson","h_Diboson");
  h.push_back(&h_Diboson);

  //ZZZ

  TH1F* h_ZZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/ZZZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_ZZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZZ->Scale(luminosity*XS_ZZZ/h_ZZZ_norm->Integral());
  h_ZZZ->SetNameTitle("h_ZZZ","h_ZZZ");
  h.push_back(h_ZZZ);



  //WZZ

  TH1F* h_WZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WZZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_WZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZZ->Scale(luminosity*XS_WZZ/h_WZZ_norm->Integral());
  h_WZZ->SetNameTitle("h_WZZ","h_WZZ");
  h.push_back(h_WZZ);



  //WWZ

  TH1F* h_WWZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WWZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_WWZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WWZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WWZ->Scale(luminosity*XS_WWZ/h_WWZ_norm->Integral());
  h_WWZ->SetNameTitle("h_WWZ","h_WWZ");
  h.push_back(h_WWZ);


  //tZq

  TH1F* h_tZq =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/tZq_split_2lSS_MEM_160722.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_tZq_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_tZq_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_tZq->Scale(luminosity*XS_tZq/h_tZq_norm->Integral());
  h_tZq->SetNameTitle("h_tZq","h_tZq");
  h.push_back(h_tZq);



  //TTTT

  TH1F* h_TTTT =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTTT/TTTT_split_2lSS_MEM_160722.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_TTTT_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTTT/ntuple_TTTT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
  
  h_TTTT->Scale(luminosity*XS_TTTT/h_TTTT_norm->Integral());
  h_TTTT->SetNameTitle("h_TTTT","h_TTTT");
  h.push_back(h_TTTT);

  //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
  TH1F h_Rares = *h_ZZZ;
  h_Rares.Add(h_WZZ);
  h_Rares.Add(h_WWZ);
  h_Rares.Add(h_tZq);
  h_Rares.Add(h_TTTT);
  h_Rares.SetNameTitle("h_Rares","h_Rares");
  h.push_back(&h_Rares);

  //Fakes

  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");


  TH1F* h_fakes =single_plot(files_data_fakes,
			     "T",
			     var,
			     "event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0 && isTrig)",
			     nbin,xmin,xmax);

  h_fakes->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_fakes->SetNameTitle("h_fakes","h_fakes");

  h.push_back(h_fakes);


  //Charge flips


  vector<TString> files_data_flips;
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lOS_CR_MEM_160804_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lOS_CR_MEM_160804_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");



  TH1F* h_flips =single_plot(files_data_flips,
			     "T",
			     var,
			     "event_weight_ttH*(category==-11 && integration_type==0 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0 && isTrig)",
			     nbin,xmin,xmax);

  h_flips->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_flips->SetNameTitle("h_flips","h_flips");
  h.push_back(h_flips);


//Data

  /*TH1F* h_data_obs =single_plot(files_data,
				"HTauTauTree_2lSS",
				var,
				"(category==11 && recolep_sel_pt[0]>25 && isTrig)",
				nbin,xmin,xmax);

  h_data_obs->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(h_data_obs);*/

  TH1F h_data_obs = *h_ttH;
  h_data_obs.Add(h_ttW);
  h_data_obs.Add(&h_TTZ);
  h_data_obs.Add(h_WpWp);
  h_data_obs.Add(&h_Diboson);
  h_data_obs.Add(&h_Rares);
  h_data_obs.Add(h_fakes);
  h_data_obs.Add(h_flips);

  h_data_obs.SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(&h_data_obs);
  
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_nomiss_tauOS.root";

  TFile* f_new = TFile::Open(file,"RECREATE");


  for(unsigned int i=0;i<h.size();i++)
    h[i]->Write();

  f_new->Close();


}








void datacard_maker_MEM_LR_missingjet_tauOS(){

  vector<TH1F*> h;
  

  TString var="Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau))";

  
  int nbin = 10;
  float xmin = 0.;
  float xmax = 1.;


  //ttH
  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  TH1F* h_ttH =single_plot(files_ttH,
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_ttH_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttH->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH->SetNameTitle("h_ttH","h_ttH");
  h.push_back(h_ttH);

 TH1F* h_ttH_tautau =single_plot(files_ttH,
				  "T",
				  var,
				  "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0 && genH_decayMode[1]<=5)",
				  nbin,xmin,xmax);

  
  h_ttH_tautau->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_tautau->SetNameTitle("h_ttH_tautau","h_ttH_tautau");
  h.push_back(h_ttH_tautau);

  TH1F* h_ttH_boson =single_plot(files_ttH,
				 "T",
				 var,
				 "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0 && genH_decayMode[1]>5)",
				 nbin,xmin,xmax);
  
  
  h_ttH_boson->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_boson->SetNameTitle("h_ttH_boson","h_ttH_boson");
  h.push_back(h_ttH_boson);


  //ttW

  TH1F* h_ttW =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160708.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_ttW_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttW_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttW->Scale(luminosity*XS_ttW/h_ttW_norm->Integral());
  h_ttW->SetNameTitle("h_ttW","h_ttW");
  h.push_back(h_ttW);



  //ttZ

  TH1F* h_ttZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttZ_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_ttZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttZ->Scale(luminosity*XS_ttZ/h_ttZ_norm->Integral());
  h_ttZ->SetNameTitle("h_ttZ","h_ttZ");
  h.push_back(h_ttZ);



  //TTLL low mass

  TH1F* h_TTLL_lowmass =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/TTLL_lowmass_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_TTLL_lowmass_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_TTLL_lowmass_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					 "HTauTauTree",
					 "1",
					 "MC_weight",
					 3,0,2);
  
  h_TTLL_lowmass->Scale(luminosity*XS_TTLL_lowmass/h_TTLL_lowmass_norm->Integral());
  h_TTLL_lowmass->SetNameTitle("h_TTLL_lowmass","h_TTLL_lowmass");
  h.push_back(h_TTLL_lowmass);



  //ttG

  TH1F* h_ttG =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttG/ttG_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_ttG_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_ttG_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ttG->Scale(luminosity*XS_ttG/h_ttG_norm->Integral());
  h_ttG->SetNameTitle("h_ttG","h_ttG");
  h.push_back(h_ttG);


  //TTZ = ttZ + TTLL_lowmass + ttG
  
  TH1F h_TTZ = *h_ttZ;
  h_TTZ.Add(h_TTLL_lowmass);
  h_TTZ.Add(h_ttG);
  h_TTZ.SetNameTitle("h_TTZ","h_TTZ");
  h.push_back(&h_TTZ);  
  

  //WpWp

  TH1F* h_WpWp =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WpWp_2lSS_MEM_160719.root",
			    "T",
			    var,
			    "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			    nbin,xmin,xmax);

  TH1F* h_WpWp_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WpWp_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
    
  h_WpWp->Scale(luminosity*XS_WpWp/h_WpWp_norm->Integral());
  h_WpWp->SetNameTitle("h_WpWp","h_WpWp");
  h.push_back(h_WpWp);


  //WZ
  
  TH1F* h_WZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Diboson/WZ_split_2lSS_MEM_160805.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_WZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_WZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZ->Scale(luminosity*XS_WZ/h_WZ_norm->Integral());
  h_WZ->SetNameTitle("h_WZ","h_WZ");
  h.push_back(h_WZ);


  //ZZ

  TH1F* h_ZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Diboson/ZZ_split_2lSS_MEM_160804.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_ZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_ZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZ->Scale(luminosity*XS_ZZ/h_ZZ_norm->Integral());
  h_ZZ->SetNameTitle("h_ZZ","h_ZZ");
  h.push_back(h_ZZ);

  //Diboson = WZ + ZZ
  
  TH1F h_Diboson = *h_WZ;
  h_Diboson.Add(h_ZZ);
  h_Diboson.SetNameTitle("h_Diboson","h_Diboson");
  h.push_back(&h_Diboson);

  //ZZZ

  TH1F* h_ZZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/ZZZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_ZZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZZ->Scale(luminosity*XS_ZZZ/h_ZZZ_norm->Integral());
  h_ZZZ->SetNameTitle("h_ZZZ","h_ZZZ");
  h.push_back(h_ZZZ);



  //WZZ

  TH1F* h_WZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WZZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_WZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZZ->Scale(luminosity*XS_WZZ/h_WZZ_norm->Integral());
  h_WZZ->SetNameTitle("h_WZZ","h_WZZ");
  h.push_back(h_WZZ);



  //WWZ

  TH1F* h_WWZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WWZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_WWZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WWZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WWZ->Scale(luminosity*XS_WWZ/h_WWZ_norm->Integral());
  h_WWZ->SetNameTitle("h_WWZ","h_WWZ");
  h.push_back(h_WWZ);


  //tZq

  TH1F* h_tZq =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/tZq_split_2lSS_MEM_160722.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_tZq_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_tZq_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_tZq->Scale(luminosity*XS_tZq/h_tZq_norm->Integral());
  h_tZq->SetNameTitle("h_tZq","h_tZq");
  h.push_back(h_tZq);



  //TTTT

  TH1F* h_TTTT =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTTT/TTTT_split_2lSS_MEM_160722.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)",
			   nbin,xmin,xmax);

  TH1F* h_TTTT_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTTT/ntuple_TTTT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
  
  h_TTTT->Scale(luminosity*XS_TTTT/h_TTTT_norm->Integral());
  h_TTTT->SetNameTitle("h_TTTT","h_TTTT");
  h.push_back(h_TTTT);

  //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
  TH1F h_Rares = *h_ZZZ;
  h_Rares.Add(h_WZZ);
  h_Rares.Add(h_WWZ);
  h_Rares.Add(h_tZq);
  h_Rares.Add(h_TTTT);
  h_Rares.SetNameTitle("h_Rares","h_Rares");
  h.push_back(&h_Rares);


  //Fakes

  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");



  TH1F* h_fakes =single_plot(files_data_fakes,
			     "T",
			     var,
			     "event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0 && isTrig)",
			     nbin,xmin,xmax);

  h_fakes->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_fakes->SetNameTitle("h_fakes","h_fakes");

  h.push_back(h_fakes);


  //Charge flips


  vector<TString> files_data_flips;
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lOS_CR_MEM_160804_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lOS_CR_MEM_160804_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");


  TH1F* h_flips =single_plot(files_data_flips,
			     "T",
			     var,
			     "event_weight_ttH*(category==-11 && integration_type==1 && recolep_sel_pt[0]>25 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0 && isTrig)",
			     nbin,xmin,xmax);

  h_flips->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_flips->SetNameTitle("h_flips","h_flips");
  h.push_back(h_flips);


//Data

  /*TH1F* h_data_obs =single_plot(files_data,
				"HTauTauTree_2lSS",
				var,
				"(category==11 && recolep_sel_pt[0]>25 && isTrig)",
				nbin,xmin,xmax);

  h_data_obs->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(h_data_obs);*/

  TH1F h_data_obs = *h_ttH;
  h_data_obs.Add(h_ttW);
  h_data_obs.Add(&h_TTZ);
  h_data_obs.Add(h_WpWp);
  h_data_obs.Add(&h_Diboson);
  h_data_obs.Add(&h_Rares);
  h_data_obs.Add(h_fakes);
  h_data_obs.Add(h_flips);

  h_data_obs.SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(&h_data_obs);
  
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_missingjet_tauOS.root";

  TFile* f_new = TFile::Open(file,"RECREATE");


  for(unsigned int i=0;i<h.size();i++)
    h[i]->Write();

  f_new->Close();


}







void datacard_maker_MEM_LR_nomiss_log(){

  vector<TH1F*> h;
  

  TString var="-log(1-Integral_ttH/(Integral_ttH+1e-17*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)))*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) + 40*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0 && Integral_ttH>0) - ((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0 && Integral_ttH==0)";
  
  int nbin = 43;
  float xmin = -2.;
  float xmax = 41.;



  //ttH
  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  TH1F* h_ttH =single_plot(files_ttH,
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttH_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttH->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH->SetNameTitle("h_ttH","h_ttH");
  h.push_back(h_ttH);


  TH1F* h_ttH_tautau =single_plot(files_ttH,
				  "T",
				  var,
				  "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && genH_decayMode[1]<=5)",
				  nbin,xmin,xmax);

  
  h_ttH_tautau->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_tautau->SetNameTitle("h_ttH_tautau","h_ttH_tautau");
  h.push_back(h_ttH_tautau);

  TH1F* h_ttH_boson =single_plot(files_ttH,
				 "T",
				 var,
				 "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25 && genH_decayMode[1]>5)",
				 nbin,xmin,xmax);
  
  
  h_ttH_boson->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_boson->SetNameTitle("h_ttH_boson","h_ttH_boson");
  h.push_back(h_ttH_boson);


  //ttW

  TH1F* h_ttW =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160708.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttW_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttW_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttW->Scale(luminosity*XS_ttW/h_ttW_norm->Integral());
  h_ttW->SetNameTitle("h_ttW","h_ttW");
  h.push_back(h_ttW);



  //ttZ

  TH1F* h_ttZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttZ_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttZ->Scale(luminosity*XS_ttZ/h_ttZ_norm->Integral());
  h_ttZ->SetNameTitle("h_ttZ","h_ttZ");
  h.push_back(h_ttZ);



  //TTLL low mass

  TH1F* h_TTLL_lowmass =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/TTLL_lowmass_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTLL_lowmass_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_TTLL_lowmass_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					 "HTauTauTree",
					 "1",
					 "MC_weight",
					 3,0,2);
  
  h_TTLL_lowmass->Scale(luminosity*XS_TTLL_lowmass/h_TTLL_lowmass_norm->Integral());
  h_TTLL_lowmass->SetNameTitle("h_TTLL_lowmass","h_TTLL_lowmass");
  h.push_back(h_TTLL_lowmass);



  //ttG

  TH1F* h_ttG =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttG/ttG_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttG_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_ttG_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ttG->Scale(luminosity*XS_ttG/h_ttG_norm->Integral());
  h_ttG->SetNameTitle("h_ttG","h_ttG");
  h.push_back(h_ttG);


  //TTZ = ttZ + TTLL_lowmass + ttG
  
  TH1F h_TTZ = *h_ttZ;
  h_TTZ.Add(h_TTLL_lowmass);
  h_TTZ.Add(h_ttG);
  h_TTZ.SetNameTitle("h_TTZ","h_TTZ");
  h.push_back(&h_TTZ);  



  //WpWp

  TH1F* h_WpWp =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WpWp_2lSS_MEM_160719.root",
			    "T",
			    var,
			    "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			    nbin,xmin,xmax);

  TH1F* h_WpWp_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WpWp_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
    
  h_WpWp->Scale(luminosity*XS_WpWp/h_WpWp_norm->Integral());
  h_WpWp->SetNameTitle("h_WpWp","h_WpWp");
  h.push_back(h_WpWp);

  
  //WZ

  TH1F* h_WZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Diboson/WZ_split_2lSS_MEM_160805.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_WZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZ->Scale(luminosity*XS_WZ/h_WZ_norm->Integral());
  h_WZ->SetNameTitle("h_WZ","h_WZ");
  h.push_back(h_WZ);


  //ZZ

  TH1F* h_ZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Diboson/ZZ_split_2lSS_MEM_160804.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_ZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZ->Scale(luminosity*XS_ZZ/h_ZZ_norm->Integral());
  h_ZZ->SetNameTitle("h_ZZ","h_ZZ");
  h.push_back(h_ZZ);

  //Diboson = WZ + ZZ
  
  TH1F h_Diboson = *h_WZ;
  h_Diboson.Add(h_ZZ);
  h_Diboson.SetNameTitle("h_Diboson","h_Diboson");
  h.push_back(&h_Diboson);

  //ZZZ

  TH1F* h_ZZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/ZZZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZZ->Scale(luminosity*XS_ZZZ/h_ZZZ_norm->Integral());
  h_ZZZ->SetNameTitle("h_ZZZ","h_ZZZ");
  h.push_back(h_ZZZ);



  //WZZ

  TH1F* h_WZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WZZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZZ->Scale(luminosity*XS_WZZ/h_WZZ_norm->Integral());
  h_WZZ->SetNameTitle("h_WZZ","h_WZZ");
  h.push_back(h_WZZ);



  //WWZ

  TH1F* h_WWZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WWZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WWZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WWZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WWZ->Scale(luminosity*XS_WWZ/h_WWZ_norm->Integral());
  h_WWZ->SetNameTitle("h_WWZ","h_WWZ");
  h.push_back(h_WWZ);


  //tZq

  TH1F* h_tZq =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/tZq_split_2lSS_MEM_160722.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_tZq_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_tZq_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_tZq->Scale(luminosity*XS_tZq/h_tZq_norm->Integral());
  h_tZq->SetNameTitle("h_tZq","h_tZq");
  h.push_back(h_tZq);



  //TTTT

  TH1F* h_TTTT =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTTT/TTTT_split_2lSS_MEM_160722.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==0 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTTT_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTTT/ntuple_TTTT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
  
  h_TTTT->Scale(luminosity*XS_TTTT/h_TTTT_norm->Integral());
  h_TTTT->SetNameTitle("h_TTTT","h_TTTT");
  h.push_back(h_TTTT);

  //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
  TH1F h_Rares = *h_ZZZ;
  h_Rares.Add(h_WZZ);
  h_Rares.Add(h_WWZ);
  h_Rares.Add(h_tZq);
  h_Rares.Add(h_TTTT);
  h_Rares.SetNameTitle("h_Rares","h_Rares");
  h.push_back(&h_Rares);

  //Fakes

  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");


  TH1F* h_fakes =single_plot(files_data_fakes,
			     "T",
			     var,
			     "event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_fakes->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_fakes->SetNameTitle("h_fakes","h_fakes");

  h.push_back(h_fakes);


  //Charge flips


  vector<TString> files_data_flips;
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lOS_CR_MEM_160804_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lOS_CR_MEM_160804_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");



  TH1F* h_flips =single_plot(files_data_flips,
			     "T",
			     var,
			     "event_weight_ttH*(category==-11 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_flips->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_flips->SetNameTitle("h_flips","h_flips");
  h.push_back(h_flips);


//Data

  /*TH1F* h_data_obs =single_plot(files_data,
				"HTauTauTree_2lSS",
				var,
				"(category==11 && recolep_sel_pt[0]>25 && isTrig)",
				nbin,xmin,xmax);

  h_data_obs->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(h_data_obs);*/

  TH1F h_data_obs = *h_ttH;
  h_data_obs.Add(h_ttW);
  h_data_obs.Add(&h_TTZ);
  h_data_obs.Add(h_WpWp);
  h_data_obs.Add(&h_Diboson);
  h_data_obs.Add(&h_Rares);
  h_data_obs.Add(h_fakes);
  h_data_obs.Add(h_flips);

  h_data_obs.SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(&h_data_obs);
  
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_nomiss_log.root";

  TFile* f_new = TFile::Open(file,"RECREATE");


  for(unsigned int i=0;i<h.size();i++)
    h[i]->Write();

  f_new->Close();


}








void datacard_maker_MEM_LR_missingjet_log(){

  vector<TH1F*> h;
  
  TString var="-log(1-Integral_ttH/(Integral_ttH+1e-15*(Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)))*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)>0) + 40*((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0 && Integral_ttH>0) - ((Integral_ttbar_DL_fakelep_tlep+Integral_ttbar_DL_fakelep_ttau)==0 && Integral_ttH==0)";

  
  int nbin = 43;
  float xmin = -2.;
  float xmax = 41.;



  //ttH
  vector<TString> files_ttH;
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  files_ttH.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  TH1F* h_ttH =single_plot(files_ttH,
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttH_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttH/ntuple_ttH_Hnonbb_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttH->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH->SetNameTitle("h_ttH","h_ttH");
  h.push_back(h_ttH);

 TH1F* h_ttH_tautau =single_plot(files_ttH,
				  "T",
				  var,
				  "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && genH_decayMode[1]<=5)",
				  nbin,xmin,xmax);

  
  h_ttH_tautau->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_tautau->SetNameTitle("h_ttH_tautau","h_ttH_tautau");
  h.push_back(h_ttH_tautau);

  TH1F* h_ttH_boson =single_plot(files_ttH,
				 "T",
				 var,
				 "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25 && genH_decayMode[1]>5)",
				 nbin,xmin,xmax);
  
  
  h_ttH_boson->Scale(luminosity*XS_ttH/h_ttH_norm->Integral());
  h_ttH_boson->SetNameTitle("h_ttH_boson","h_ttH_boson");
  h.push_back(h_ttH_boson);


  //ttW

  TH1F* h_ttW =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160708.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttW_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttW_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttW->Scale(luminosity*XS_ttW/h_ttW_norm->Integral());
  h_ttW->SetNameTitle("h_ttW","h_ttW");
  h.push_back(h_ttW);



  //ttZ

  TH1F* h_ttZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttZ_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_ttZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
  
  h_ttZ->Scale(luminosity*XS_ttZ/h_ttZ_norm->Integral());
  h_ttZ->SetNameTitle("h_ttZ","h_ttZ");
  h.push_back(h_ttZ);



  //TTLL low mass

  TH1F* h_TTLL_lowmass =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/TTLL_lowmass_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTLL_lowmass_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_TTLL_lowmass_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
					 "HTauTauTree",
					 "1",
					 "MC_weight",
					 3,0,2);
  
  h_TTLL_lowmass->Scale(luminosity*XS_TTLL_lowmass/h_TTLL_lowmass_norm->Integral());
  h_TTLL_lowmass->SetNameTitle("h_TTLL_lowmass","h_TTLL_lowmass");
  h.push_back(h_TTLL_lowmass);



  //ttG

  TH1F* h_ttG =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttG/ttG_split_2lSS_MEM_160720.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ttG_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/topG/ntuple_ttG_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ttG->Scale(luminosity*XS_ttG/h_ttG_norm->Integral());
  h_ttG->SetNameTitle("h_ttG","h_ttG");
  h.push_back(h_ttG);


  //TTZ = ttZ + TTLL_lowmass + ttG
  
  TH1F h_TTZ = *h_ttZ;
  h_TTZ.Add(h_TTLL_lowmass);
  h_TTZ.Add(h_ttG);
  h_TTZ.SetNameTitle("h_TTZ","h_TTZ");
  h.push_back(&h_TTZ);  
  

  //WpWp

  TH1F* h_WpWp =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WpWp_2lSS_MEM_160719.root",
			    "T",
			    var,
			    "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			    nbin,xmin,xmax);

  TH1F* h_WpWp_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WpWp_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
    
  h_WpWp->Scale(luminosity*XS_WpWp/h_WpWp_norm->Integral());
  h_WpWp->SetNameTitle("h_WpWp","h_WpWp");
  h.push_back(h_WpWp);


  //WZ
  
  TH1F* h_WZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Diboson/WZ_split_2lSS_MEM_160805.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_WZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZ->Scale(luminosity*XS_WZ/h_WZ_norm->Integral());
  h_WZ->SetNameTitle("h_WZ","h_WZ");
  h.push_back(h_WZ);


  //ZZ

  TH1F* h_ZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Diboson/ZZ_split_2lSS_MEM_160804.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Diboson/ntuple_ZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZ->Scale(luminosity*XS_ZZ/h_ZZ_norm->Integral());
  h_ZZ->SetNameTitle("h_ZZ","h_ZZ");
  h.push_back(h_ZZ);

  //Diboson = WZ + ZZ
  
  TH1F h_Diboson = *h_WZ;
  h_Diboson.Add(h_ZZ);
  h_Diboson.SetNameTitle("h_Diboson","h_Diboson");
  h.push_back(&h_Diboson);

  //ZZZ

  TH1F* h_ZZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/ZZZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_ZZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_ZZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_ZZZ->Scale(luminosity*XS_ZZZ/h_ZZZ_norm->Integral());
  h_ZZZ->SetNameTitle("h_ZZZ","h_ZZZ");
  h.push_back(h_ZZZ);



  //WZZ

  TH1F* h_WZZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WZZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WZZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WZZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WZZ->Scale(luminosity*XS_WZZ/h_WZZ_norm->Integral());
  h_WZZ->SetNameTitle("h_WZZ","h_WZZ");
  h.push_back(h_WZZ);



  //WWZ

  TH1F* h_WWZ =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/Rares_EW/WWZ_2lSS_MEM_160719.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_WWZ_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/Rares_EW/ntuple_WWZ_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_WWZ->Scale(luminosity*XS_WWZ/h_WWZ_norm->Integral());
  h_WWZ->SetNameTitle("h_WWZ","h_WWZ");
  h.push_back(h_WWZ);


  //tZq

  TH1F* h_tZq =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/tZq_split_2lSS_MEM_160722.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_tZq_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/ttV/ntuple_tZq_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				"HTauTauTree",
				"1",
				"MC_weight",
				3,0,2);
    
  h_tZq->Scale(luminosity*XS_tZq/h_tZq_norm->Integral());
  h_tZq->SetNameTitle("h_tZq","h_tZq");
  h.push_back(h_tZq);



  //TTTT

  TH1F* h_TTTT =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTTT/TTTT_split_2lSS_MEM_160722.root",
			   "T",
			   var,
			   "MC_weight*(category==11 && integration_type==1 && recolep_sel_pt[0]>25)",
			   nbin,xmin,xmax);

  TH1F* h_TTTT_norm =single_plot("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_converted/TTTT/ntuple_TTTT_byLooseIsolationMVArun2v1DBdR03oldDMwLT.root",
				 "HTauTauTree",
				 "1",
				 "MC_weight",
				 3,0,2);
  
  h_TTTT->Scale(luminosity*XS_TTTT/h_TTTT_norm->Integral());
  h_TTTT->SetNameTitle("h_TTTT","h_TTTT");
  h.push_back(h_TTTT);

  //Rares = ZZZ + WZZ + WWZ + tZq + TTTT
  TH1F h_Rares = *h_ZZZ;
  h_Rares.Add(h_WZZ);
  h_Rares.Add(h_WWZ);
  h_Rares.Add(h_tZq);
  h_Rares.Add(h_TTTT);
  h_Rares.SetNameTitle("h_Rares","h_Rares");
  h.push_back(&h_Rares);


  //Fakes

  vector<TString> files_data_fakes;
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  files_data_fakes.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");



  TH1F* h_fakes =single_plot(files_data_fakes,
			     "T",
			     var,
			     "event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_fakes->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_fakes->SetNameTitle("h_fakes","h_fakes");

  h.push_back(h_fakes);


  //Charge flips


  vector<TString> files_data_flips;
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lOS_CR_MEM_160804_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lOS_CR_MEM_160804_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lOS_CR_MEM_160810_trig_filt.root");
  files_data_flips.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lOS_CR_MEM_160805_trig_filt.root");


  TH1F* h_flips =single_plot(files_data_flips,
			     "T",
			     var,
			     "event_weight_ttH*(category==-11 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)",
			     nbin,xmin,xmax);

  h_flips->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_flips->SetNameTitle("h_flips","h_flips");
  h.push_back(h_flips);


//Data

  /*TH1F* h_data_obs =single_plot(files_data,
				"HTauTauTree_2lSS",
				var,
				"(category==11 && recolep_sel_pt[0]>25 && isTrig)",
				nbin,xmin,xmax);

  h_data_obs->Scale(luminosity/8538.); //Data files for 8.5 fb-1
  h_data_obs->SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(h_data_obs);*/

  TH1F h_data_obs = *h_ttH;
  h_data_obs.Add(h_ttW);
  h_data_obs.Add(&h_TTZ);
  h_data_obs.Add(h_WpWp);
  h_data_obs.Add(&h_Diboson);
  h_data_obs.Add(&h_Rares);
  h_data_obs.Add(h_fakes);
  h_data_obs.Add(h_flips);

  h_data_obs.SetNameTitle("h_data_obs","h_data_obs");
  h.push_back(&h_data_obs);
  
  TString file="/data_CMS/cms/strebler/ttH_prod_80X_06_2016/datacards/datacard_MEM_LR_missingjet_log.root";

  TFile* f_new = TFile::Open(file,"RECREATE");


  for(unsigned int i=0;i<h.size();i++)
    h[i]->Write();

  f_new->Close();


}


