#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TFile.h>
#include <TTree.h>
#include <TLatex.h>


#include "Helpers_ROCcurve.C"



void plot_ROC(vector<TGraphErrors*> ROC, vector<TString> leg_entry, bool save=false, TString filename="", TString leg_title=""){

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetGridx();
  c->SetGridy();

  ROC[0]->GetXaxis()->SetTitle("ttH efficiency");
  ROC[0]->GetYaxis()->SetTitle("Bkg efficiency");
  ROC[0]->GetXaxis()->SetRangeUser(0,1);
  ROC[0]->GetYaxis()->SetRangeUser(0,1);
  ROC[0]->GetYaxis()->SetTitleOffset(1.65);

  TLegend* leg=new TLegend(0.2,0.55,0.55,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillColor(0);
  if(leg_title!="")
    leg->SetHeader(leg_title);

  for(unsigned int i=0; i<ROC.size(); i++){
    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    ROC[i]->SetLineColor(i+1);
    if(i>3)
    //if(i>1)
      ROC[i]->SetLineColor(i+2);
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->Draw("AL");
  for(unsigned int i=1; i<ROC.size(); i++)
    ROC[i]->Draw("sameL");
  leg->Draw("same");
  
  TLatex *texl = new TLatex(0.01,1.01,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");

  if(save){
    c->SaveAs("../plots/pdf/"+filename+".pdf");
    c->SaveAs("../plots/png/"+filename+".png");
  }

  return;

}






void plot_ROC_weights(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/ttH/ttH_Htautau_split_2lSS_MEM_160622.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("category==11");
  vector<TString> cut_denom_sig = cut_num_sig;
  
  float XS_ttjets_SLfromT_eff = 182.*1.675208e-07;
  float XS_ttjets_SLfromTbar_eff = 182.*1.672702e-07;
  float XS_ttjets_DL_eff = 87.3*1.312176e-06;
  
  float XS_ttjets_eff = XS_ttjets_SLfromT_eff + XS_ttjets_SLfromTbar_eff + XS_ttjets_DL_eff;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back(Form("%f*event_weight_ttH*(category==41)",XS_ttjets_SLfromT_eff));
  cut_num_bkg.push_back(Form("%f*event_weight_ttH*(category==41)",XS_ttjets_SLfromTbar_eff));
  cut_num_bkg.push_back(Form("%f*event_weight_ttH*(category==41)",XS_ttjets_DL_eff));
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_SL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("t#bar{t} l+jets weight");
  leg_entry.push_back("t#bar{t} l+#tau weight");

  TString filename="ROC_MEM_weights";

  plot_ROC(ROCs,leg_entry,true,filename);

}






void plot_ROC_weights_missing_jet(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/ttH/ttH_Htautau_split_2lSS_MEM_160622.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("category==11 && integration_type==1");
  vector<TString> cut_denom_sig = cut_num_sig;
  
  float XS_ttjets_SLfromT_eff = 182.*1.675208e-07;
  float XS_ttjets_SLfromTbar_eff = 182.*1.672702e-07;
  float XS_ttjets_DL_eff = 87.3*1.312176e-06;
  
  float XS_ttjets_eff = XS_ttjets_SLfromT_eff + XS_ttjets_SLfromTbar_eff + XS_ttjets_DL_eff;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back(Form("%f*event_weight_ttH*(category==41 && integration_type==1)",XS_ttjets_SLfromT_eff));
  cut_num_bkg.push_back(Form("%f*event_weight_ttH*(category==41 && integration_type==1)",XS_ttjets_SLfromTbar_eff));
  cut_num_bkg.push_back(Form("%f*event_weight_ttH*(category==41 && integration_type==1)",XS_ttjets_DL_eff));
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_SL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("t#bar{t} l+jets weight");
  leg_entry.push_back("t#bar{t} l+#tau weight");

  TString filename="ROC_MEM_weights_missing_jet";

  plot_ROC(ROCs,leg_entry,true,filename);

}






void plot_ROC_LR(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/ttH/ttH_Htautau_split_2lSS_MEM_160620.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("category==11");
  vector<TString> cut_denom_sig = cut_num_sig;
  
  float XS_ttjets_SLfromT = 182. / (2*182. + 87.3);
  float XS_ttjets_SLfromTbar = XS_ttjets_SLfromT;
  float XS_ttjets_DL = 87.3 / (2*182. + 87.3);

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back(Form("%f*event_weight_ttH*(category==41)",XS_ttjets_SLfromT));
  cut_num_bkg.push_back(Form("%f*event_weight_ttH*(category==41)",XS_ttjets_SLfromTbar));
  cut_num_bkg.push_back(Form("%f*event_weight_ttH*(category==41)",XS_ttjets_DL));
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_SL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_ttbar_SL_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("t#bar{t} l+jets weight");
  leg_entry.push_back("ttH vs t#bar{t} l+jets LR");

  TString filename="ROC_MEM_LR";

  plot_ROC(ROCs,leg_entry,true,filename);

}








void plot_ROC_weights_notopmass_check(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/ttH/ttH_Htautau_split_2lSS_MEM_160622.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160620.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160621.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root");

  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/ttH/ttH_Htautau_split_2lSS_MEM_160628.root");

  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160627.root");
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160627.root");
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160627.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("category==11");
  vector<TString> cut_denom_sig = cut_num_sig;
  
  float XS_ttjets_SLfromT_eff = 182.*1.675208e-07;
  float XS_ttjets_SLfromTbar_eff = 182.*1.672702e-07;
  float XS_ttjets_DL_eff = 87.3*1.312176e-06;
  
  float XS_ttjets_eff = XS_ttjets_SLfromT_eff + XS_ttjets_SLfromTbar_eff + XS_ttjets_DL_eff;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back(Form("%f*event_weight_ttH*(category==41)",XS_ttjets_SLfromT_eff));
  cut_num_bkg.push_back(Form("%f*event_weight_ttH*(category==41)",XS_ttjets_SLfromTbar_eff));
  cut_num_bkg.push_back(Form("%f*event_weight_ttH*(category==41)",XS_ttjets_DL_eff));
  vector<TString> cut_denom_bkg=cut_num_bkg;


  

  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_SL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_SL_weight(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("t#bar{t} l+jets weight");
  leg_entry.push_back("t#bar{t} l+#tau weight");
  leg_entry.push_back("ttH weight v2");
  leg_entry.push_back("t#bar{t} l+jets weight v2");
  leg_entry.push_back("t#bar{t} l+#tau weight v2");

  TString filename="ROC_MEM_weights_notopmass_check";

  plot_ROC(ROCs,leg_entry,true,filename);

}






void plot_ROC_weights_force_missing_jet_integration(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/ttH/ttH_Htautau_split_2lSS_MEM_160622.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_76X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160620.root");

  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160704.root");

  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160704.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("category==11 && Integral_ttbar_DL>0 && genH_decayMode[1]<=0");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && Integral_ttbar_DL>0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;

  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttW_weight(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("t#bar{t} l+#tau weight");
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA v2");
  leg_entry.push_back("ttH weight v2");
  leg_entry.push_back("t#bar{t} l+#tau weight v2");
  leg_entry.push_back("ttW weight v2");

  TString filename="ROC_MEM_weights_force_missing_jet_integration";

  plot_ROC(ROCs,leg_entry,true,filename);

}






void plot_ROC_weights_force_missing_jet_integration_ttbar(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160704.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160704.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("(category==11 && genH_decayMode[1]<=0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttW_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));



  vector<TString> leg_entry;
  leg_entry.push_back("BKG=t#bar{t}: 2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("BKG=t#bar{t}: 2lSS ttH vs ttV MVA");
  leg_entry.push_back("BKG=t#bar{t}: ttH weight");
  leg_entry.push_back("BKG=t#bar{t}: t#bar{t} l+#tau weight");
  leg_entry.push_back("BKG=t#bar{t}: ttW weight");


  TString filename="ROC_MEM_weights_force_missing_jet_integration_ttbar";

  plot_ROC(ROCs,leg_entry,true,filename);

}






void plot_ROC_weights_force_missing_jet_integration_ttW(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160704.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttW/ttW_split_2lSS_MEM_160705.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("(category==11 && genH_decayMode[1]<=0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("(category==11)");
  vector<TString> cut_denom_bkg=cut_num_bkg;

  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttW_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));


  vector<TString> leg_entry;
  leg_entry.push_back("BKG=ttW: 2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("BKG=ttW: 2lSS ttH vs ttV MVA");
  leg_entry.push_back("BKG=ttW: ttH weight");
  leg_entry.push_back("BKG=ttW: t#bar{t} l+#tau weight");
  leg_entry.push_back("BKG=ttW: ttW weight");

  TString filename="ROC_MEM_weights_force_missing_jet_integration_ttW";

  plot_ROC(ROCs,leg_entry,true,filename);

}










void plot_ROC_weights_force_missing_jet_integration_ifnoperm_ttbar(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root");

  vector<TString> file_bkg;
  //file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160706.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("(category==11 && genH_decayMode[1]<=0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  //ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  //ROCs.push_back(get_ROC_ttW_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  //leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("t#bar{t} l+#tau weight");
  //leg_entry.push_back("ttW weight");


  TString filename="ROC_MEM_weights_force_missing_jet_integration_ifnoperm_ttbar";

  plot_ROC(ROCs,leg_entry,true,filename);

}






void plot_ROC_weights_force_missing_jet_integration_ifnoperm_ttW(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160706.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("(category==11 && genH_decayMode[1]<=0 && PTauHad_ttbar_DL_ttW_Lower>0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("(category==11 && ((gentop_decayMode[0]==5 && gentop_decayMode[1]>0 && gentop_decayMode[1]<5) || (gentop_decayMode[1]==5 && gentop_decayMode[0]>0 && gentop_decayMode[0]<5)) && genW_decayMode[0]>0 && genW_decayMode[0]<5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;

  vector<TGraphErrors*> ROCs;
  //ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  //ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  //ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttW_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));


  vector<TString> leg_entry;
  //leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH weight");
  //leg_entry.push_back("t#bar{t} l+#tau weight");
  leg_entry.push_back("ttW weight");

  TString filename="ROC_MEM_weights_force_missing_jet_integration_ifnoperm_ttW";

  plot_ROC(ROCs,leg_entry,true,filename);

}








void plot_ROC_LR_ttbar(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160706.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("category==11 && genH_decayMode[1]<=0 && integration_type==1");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_ttbar_SL_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-6));
  ROCs.push_back(get_ROC_ttH_ttbar_SL_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-8));
  ROCs.push_back(get_ROC_ttH_ttbar_SL_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-10));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("t#bar{t} l+#tau weight");
  leg_entry.push_back("LR k=1e-7");
  leg_entry.push_back("LR k=1e-8");
  leg_entry.push_back("LR k=1e-9");


  TString filename="ROC_LR_ttbar";

  plot_ROC(ROCs,leg_entry,true,filename);

}









void plot_ROC_weights_force_missing_jet_integration_ifnoperm_ttW_14072016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160708.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("(category==11 && genH_decayMode[1]<=0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("(category==11)");
  vector<TString> cut_denom_bkg=cut_num_bkg;

  vector<TGraphErrors*> ROCs;
  //ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  //ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttW_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));


  vector<TString> leg_entry;
  //leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH weight");
  //leg_entry.push_back("t#bar{t} l+#tau weight");
  leg_entry.push_back("ttW weight");

  TString filename="ROC_MEM_weights_force_missing_jet_integration_ifnoperm_ttW_14072016";

  plot_ROC(ROCs,leg_entry,true,filename);

}









void plot_ROC_weights_force_missing_jet_integration_ifnoperm_ttbar_14072016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("(category==11 && genH_decayMode[1]<=0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("t#bar{t} l+#tau weight");
  leg_entry.push_back("t#bar{t} l+#tau + fake lep.=b weight");



  TString filename="ROC_MEM_weights_force_missing_jet_integration_ifnoperm_ttbar_14072016";

  plot_ROC(ROCs,leg_entry,true,filename);

}





void plot_ROC_weights_no_missjet_ttbar_14072016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");

  TString leg_title="#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=t#bar{t} DL MC}{No missing jet}";

  TString filename="ROC_MEM_weights_no_missjet_ttbar_14072016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}




void plot_ROC_weights_missjet_ttbar_14072016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25 && integration_type==1)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25 && integration_type==1)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25 && integration_type==1)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25 && integration_type==1)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25 && integration_type==1)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25 && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,500));
  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");

  TString leg_title="#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=t#bar{t} DL MC}{Missing jet}";

  TString filename="ROC_MEM_weights_missjet_ttbar_14072016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttbar_14072016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && recolep_sel_pt[0]>25)");
  
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*event_weight_ttH*(category==41 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,500));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));




  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");

  TString leg_title="Sig=ttH H#rightarrow#tau#tau / Bkg=t#bar{t} DL MC";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttbar_14072016";

  plot_ROC(ROCs,leg_entry,true,filename, leg_title);

}






void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttbar_ttH_incl_14072016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_DL_split_2lSS_lepMVA_CR_MEM_160708.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*event_weight_ttH*(category==41 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,500));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));




  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");

  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=t#bar{t} DL MC";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttbar_ttH_incl_14072016";

  plot_ROC(ROCs,leg_entry,true,filename, leg_title);

}







void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttW_14072016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160708.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  //ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,200));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));




  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  //leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");

  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttW";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttW_14072016";

  plot_ROC(ROCs,leg_entry,true,filename, leg_title);

}







void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttZ_14072016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttZ_split_2lSS_MEM_160720.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  //ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));




  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  //leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttZ_14072016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttZZtautau_14072016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttZ_split_2lSS_MEM_160720.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25 && genpart_pdg==23 && genpart_HZDecayMode<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  //ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));




  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  //leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttZZtautau_14072016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}





void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttZZnotautau_14072016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttZ_split_2lSS_MEM_160720.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25 && genpart_pdg==23 && genpart_HZDecayMode<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  //ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));




  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  //leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ not Z#rightarrow#tau#tau";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttZZnotautau_14072016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}





void plot_ROC_weights_no_missjet_ttW_14072016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160708.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  //ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  //ROCs.push_back(get_ROC_ttH_ttbar_DL_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17));
  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH weight");
  //leg_entry.push_back("t#bar{t} l+#tau weight");
  leg_entry.push_back("t#bar{t} l+#tau");
  //leg_entry.push_back("ttH vs t#bar{t} l+#tau LR");
  leg_entry.push_back("ttH vs t#bar{t} l+#tau LR");



  TString filename="ROC_MEM_weights_no_missjet_ttW_14072016";

  plot_ROC(ROCs,leg_entry,true,filename);

}




void plot_ROC_weights_missjet_ttW_14072016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttW_split_2lSS_MEM_160708.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==1)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==1)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==1)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==1)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==1)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  //ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  //ROCs.push_back(get_ROC_ttH_ttbar_DL_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17));
  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17));




  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("t#bar{t} l+#tau weight");
  //leg_entry.push_back("t#bar{t} l+#tau + fake lep.=b weight");
  leg_entry.push_back("ttH vs t#bar{t} l+#tau LR");
  //leg_entry.push_back("ttH vs t#bar{t} l+#tau + fake lep.=b LR");


  TString filename="ROC_MEM_weights_missjet_ttW_14072016";

  plot_ROC(ROCs,leg_entry,true,filename);

}







void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttbar_datadriven(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && recolep_sel_pt[0]>25 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17));




  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");


  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=fake lep. data-driven";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttbar_datadriven";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_weights_no_missjet_ttbar_datadriven(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");




  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==0 && recolep_sel_pt[0]>25 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");

  TString leg_title="#splitline{Bkg=fake lep. data-driven}{No missing jet}";


  TString filename="ROC_MEM_weights_no_missjet_ttbar_datadriven";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_weights_missing_jet_ttbar_datadriven(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016B_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleEG_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/DoubleMu_2016C_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016B_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/MuonEG_2016C_split_2lSS_lepMVA_CR_MEM_160804_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleEle_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016B_split_2lSS_lepMVA_CR_MEM_160810_trig_filt.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_08_2016/ntuples_MEM/Data/SingleMuon_2016C_split_2lSS_lepMVA_CR_MEM_160805_trig_filt.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==1 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==1 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==1 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==1 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==1 && recolep_sel_pt[0]>25)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==1 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)");
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && integration_type==1 && recolep_sel_pt[0]>25 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-15));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");

  TString leg_title="#splitline{Bkg=fake lep. data-driven}{Missing jet}";


  TString filename="ROC_MEM_weights_missing_jet_ttbar_datadriven";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_weights_no_missjet_ttbar_SL(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_160713.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160718.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160719.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160720.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_6_160720.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_160718.root");
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/TTJets/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_160718.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && genH_decayMode[1]<=0 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*event_weight_ttH*(category==41 && integration_type==0)");
  cut_num_bkg.push_back("MC_weight*event_weight_ttH*(category==41 && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("t#bar{t} l+#tau");
  leg_entry.push_back("ttH vs t#bar{t} l+#tau LR");



  TString filename="ROC_MEM_weights_no_missjet_ttbar_SL";

  plot_ROC(ROCs,leg_entry,true,filename);

}









void plot_ROC_LR_ttH_vs_ttZ_test_ttZ_23082016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_ttZ_test_160823.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttZ_split_2lSS_MEM_ttZ_test_160823.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttZ_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));
  ROCs.push_back(get_ROC_ttH_vs_ttZ_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1,1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttZ MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ MEM LR");
  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ";

  TString filename="ROC_MEM_LR_ttH_vs_ttZ_test_ttZ_23082016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_ttH_vs_ttZ_test_ttZtautau_23082016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttH/ttH_Hnonbb_split_2lSS_MEM_ttZ_test_160823.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_06_2016/ntuples_MEM/ttV/ttZ_split_2lSS_MEM_ttZ_test_160823.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && recolep_sel_pt[0]>25 && genpart_pdg==23 && genpart_HZDecayMode<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttZ_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));
  ROCs.push_back(get_ROC_ttH_vs_ttZ_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1,1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttZ MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ MEM LR");
  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau";

  TString filename="ROC_MEM_LR_ttH_vs_ttZ_test_ttZtautau_23082016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}


