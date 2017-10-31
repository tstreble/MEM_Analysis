#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TH1F.h>

#include "Helpers.C"

float luminosity = 12900; //12.9 fb-1

float XS_ttbar_DL = 87.3;

TString filename_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split_bTagSF_CSVshape_PU_FR_clos.root";

TString filename_norm_ttbar_DL = "/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_converted/nominal/TTbar/ntuple_PU_ttbar_DL.root";



void write_2lSS(){

  TString var="1*(MVA_2lSS_ttbar>-1 && MVA_2lSS_ttbar<=-0.2 && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=1) + 2*(MVA_2lSS_ttbar>-0.2 && MVA_2lSS_ttbar<=0.1 && MVA_2lSS_ttV>-1 && MVA_2lSS_ttV<=1) + 3*(MVA_2lSS_ttbar>0.1 && MVA_2lSS_ttbar<=0.4 && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=0.3) + 4*(MVA_2lSS_ttbar>0.1 && MVA_2lSS_ttbar<=0.4 && MVA_2lSS_ttV>0.3 && MVA_2lSS_ttV<=1) + 5*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>-1. && MVA_2lSS_ttV<=0.1) + 6*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>0.1 && MVA_2lSS_ttV<=0.4) + 7*(MVA_2lSS_ttbar>0.4 && MVA_2lSS_ttbar<=1. && MVA_2lSS_ttV>0.4 && MVA_2lSS_ttV<=1)";

  
  int nbin = 7;
  float xmin = 0.5;
  float xmax = 7.5;

  TString cut_cat = "1";


  TString file = "Closure_FR_lepton_syst_2lSS1tau_nofaketau_MVA_2lSS_12.9fb.root";

  TFile* f_new = TFile::Open(file,"RECREATE");

  TH1F* h_ttbar_DL_norm =single_plot(filename_norm_ttbar_DL,
				     "HTauTauTree",
				     "1",
				     "MC_weight*PU_weight_ICHEP",
				     3,0,3);
  

  //Fakes closure
    
  TH1F* h_TT_DL_clos_ele_diff = single_plot(filename_ttbar_DL,
					    "HTauTauTree_2lSS_lepMVA_CR",
					    var,
					    Form("MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(event_weight_ttH_ele_FR_TT_MC-event_weight_ttH_ele_FR_QCD_MC)*(category==%i && isTrig && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",41) + cut_cat + ")",
					    nbin,xmin,xmax);

  h_TT_DL_clos_ele_diff->Scale(luminosity*XS_ttbar_DL/h_ttbar_DL_norm->Integral());
  
  h_TT_DL_clos_ele_diff->SetNameTitle("x_TT_DL_FR_TT_MC_minus_FR_QCD_MC_ele","x_TT_DL_FR_TT_MC_minus_FR_QCD_MC_ele");
  h_TT_DL_clos_ele_diff->Write();

  
  TH1F* h_TT_DL_clos_mu_diff = single_plot(filename_ttbar_DL,
					   "HTauTauTree_2lSS_lepMVA_CR",
					   var,
					   Form("MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(event_weight_ttH_mu_FR_TT_MC-event_weight_ttH_mu_FR_QCD_MC)*(category==%i && isTrig && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",41) + cut_cat + ")",
					   nbin,xmin,xmax);
    
  h_TT_DL_clos_mu_diff->Scale(luminosity*XS_ttbar_DL/h_ttbar_DL_norm->Integral());
  h_TT_DL_clos_mu_diff->SetNameTitle("x_TT_DL_FR_TT_MC_minus_FR_QCD_MC_mu","x_TT_DL_FR_TT_MC_minus_FR_QCD_MC_mu");
  h_TT_DL_clos_mu_diff->Write();


  return;


}








void write_3l(){

  TString var="1*(MVA_3l_ttbar>-1 && MVA_3l_ttbar<=-0.3 && MVA_3l_ttV>-1. && MVA_3l_ttV<=1) + 2*(MVA_3l_ttbar>-0.3 && MVA_3l_ttbar<=0.3 && MVA_3l_ttV>-1. && MVA_3l_ttV<=0.25) + 3*(MVA_3l_ttbar>-0.3 && MVA_3l_ttbar<=0.3 && MVA_3l_ttV>0.25 && MVA_3l_ttV<=1.) + 4*(MVA_3l_ttbar>0.3 && MVA_3l_ttbar<=1. && MVA_3l_ttV>-1. && MVA_3l_ttV<=0.25) + 5*(MVA_3l_ttbar>0.3 && MVA_3l_ttbar<=1. && MVA_3l_ttV>0.25 && MVA_3l_ttV<=1.)";

  
  int nbin = 5;
  float xmin = 0.5;
  float xmax = 5.5;


  TString cut_cat = "1";


  TString file = "Closure_FR_lepton_syst_3l1tau_nofaketau_MVA_3l_12.9fb.root";

  TFile* f_new = TFile::Open(file,"RECREATE");

  TH1F* h_ttbar_DL_norm =single_plot(filename_norm_ttbar_DL,
				     "HTauTauTree",
				     "1",
				     "MC_weight*PU_weight_ICHEP",
				     3,0,3);

  //Fakes closure
    
  TH1F* h_TT_DL_clos_ele_diff = single_plot(filename_ttbar_DL,
					    "HTauTauTree_3l_lepMVA_CR",
					    var,
					    Form("MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(event_weight_ttH_ele_FR_TT_MC-event_weight_ttH_ele_FR_QCD_MC)*(category==%i && isTrig && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",46) + cut_cat + ")",
					    nbin,xmin,xmax);
    
  h_TT_DL_clos_ele_diff->Scale(luminosity*XS_ttbar_DL/h_ttbar_DL_norm->Integral());
  
  h_TT_DL_clos_ele_diff->SetNameTitle("x_TT_DL_FR_TT_MC_minus_FR_QCD_MC_ele","x_TT_DL_FR_TT_MC_minus_FR_QCD_MC_ele");
  h_TT_DL_clos_ele_diff->Write();

  
  TH1F* h_TT_DL_clos_mu_diff = single_plot(filename_ttbar_DL,
					   "HTauTauTree_3l_lepMVA_CR",
					   var,
					   Form("MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(event_weight_ttH_mu_FR_TT_MC-event_weight_ttH_mu_FR_QCD_MC)*(category==%i && isTrig && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && ",46) + cut_cat + ")",
					   nbin,xmin,xmax);
    
  h_TT_DL_clos_mu_diff->Scale(luminosity*XS_ttbar_DL/h_ttbar_DL_norm->Integral());
  h_TT_DL_clos_mu_diff->SetNameTitle("x_TT_DL_FR_TT_MC_minus_FR_QCD_MC_mu","x_TT_DL_FR_TT_MC_minus_FR_QCD_MC_mu");
  h_TT_DL_clos_mu_diff->Write();


  return;

}
