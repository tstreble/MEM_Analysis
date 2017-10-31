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

  TLegend* leg=new TLegend(0.2,0.5,0.56,0.87);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  if(leg_title!="")
    leg->SetHeader(leg_title);

  for(unsigned int i=0; i<ROC.size(); i++){
    ROC[i]->SetLineWidth(2);
    ROC[i]->SetFillColor(0);
    ROC[i]->SetLineColor(i+2);
    if(i>2)
    //if(i>1)
      ROC[i]->SetLineColor(i+3);
    if(i>6)
      ROC[i]->SetLineColor(i+4);
      
    ROC[i]->SetFillColor(0);
    leg->AddEntry(ROC[i],leg_entry[i]);
  }

  ROC[0]->Draw("AL");
  for(unsigned int i=1; i<ROC.size(); i++)
    ROC[i]->Draw("sameL");
  leg->Draw("same");
  
  /*TLatex *texl = new TLatex(0.01,1.01,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation");
  texl->SetTextSize(0.03);
  texl->Draw("same");*/

  TLatex tex;
  tex.SetTextSize(0.03);
  tex.DrawLatexNDC(0.16,0.91,"CMS #bf{#it{Preliminary}}");
  float luminosity = 35900.;
  tex.DrawLatexNDC(0.7,0.91,Form("#bf{%.1f fb^{-1} (13 TeV)}",luminosity/1000.));

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
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  //ROCs.push_back(get_ROC_ttbar_DL_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  //ROCs.push_back(get_ROC_ttH_ttbar_DL_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17));
  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17));


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


  TString leg_title="#bf{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=fake lep. data-driven}";

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
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17));


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
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15));


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











void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttZ_Ztautau_12092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160909.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160909.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160909.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11)");
  cut_num_sig.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && genZ_decayMode[0]<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));

  ROCs.push_back(get_ROC_ttZ_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttZ_Zll_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttZ Z#rightarrow#tau#tau MEM weight");
  leg_entry.push_back("ttZ Z#rightarrowll MEM weight");

  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttZ_Ztautau_12092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}





void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttZ_Ztautau_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160914.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && genZ_decayMode[0]<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));

  ROCs.push_back(get_ROC_ttZ_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttZ_Zll_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttZ Z#rightarrow#tau#tau MEM weight");
  leg_entry.push_back("ttZ Z#rightarrowll MEM weight");

  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttZ_Ztautau_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}












void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttZ_Zll_12092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160909.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160909.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160909.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11)");
  cut_num_sig.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));

  ROCs.push_back(get_ROC_ttZ_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttZ_Zll_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttZ Z#rightarrow#tau#tau MEM weight");
  leg_entry.push_back("ttZ Z#rightarrowll MEM weight");

  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrowll";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttZ_Zll_12092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttZ_Zll_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160914.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));

  ROCs.push_back(get_ROC_ttZ_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttZ_Zll_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttZ Z#rightarrow#tau#tau MEM weight");
  leg_entry.push_back("ttZ Z#rightarrowll MEM weight");

  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrowll";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttZ_Zll_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttZ_12092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160909.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160909.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160909.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11)");
  cut_num_sig.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));

  ROCs.push_back(get_ROC_ttZ_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttZ_Zll_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttZ Z#rightarrow#tau#tau MEM weight");
  leg_entry.push_back("ttZ Z#rightarrowll MEM weight");

  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttZ_12092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}




void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttZ_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160914.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,1e-15));

  ROCs.push_back(get_ROC_ttZ_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttZ_Zll_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttZ Z#rightarrow#tau#tau MEM weight");
  leg_entry.push_back("ttZ Z#rightarrowll MEM weight");

  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttZ_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}












void plot_ROC_LR_full_bkg_ttZ_Ztautau_no_miss_12092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160909.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160909.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160909.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && genZ_decayMode[0]<=5 && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttZ_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,0.5,0));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttZ Z#rightarrow#tau#tau MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR (k_{tt}=1e-17, k_{ttZ #tau#tau}=0, k_{ttZ ll}=0)");
  leg_entry.push_back("ttH vs ttZ #tau#tau MEM LR (k_{tt}=0, k_{ttZ #tau#tau}=0.5, k_{ttZ ll}=0)");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ #tau#tau MEM LR (k_{tt}=1e-17, k_{ttZ #tau#tau}=0.5, k_{ttZ ll}=0)");

  
  TString leg_title="#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau}{No missing jet}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Ztautau_nomiss_12092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_LR_full_bkg_ttZ_Ztautau_missing_12092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160909.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160909.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160909.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1)");
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && genZ_decayMode[0]<=5 && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttZ_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0.5,0));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttZ Z#rightarrow#tau#tau MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR (k_{tt}=1e-15, k_{ttZ #tau#tau}=0, k_{ttZ ll}=0)");
  leg_entry.push_back("ttH vs ttZ #tau#tau MEM LR (k_{tt}=0, k_{ttZ #tau#tau}=0.5, k_{ttZ ll}=0)");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ #tau#tau MEM LR (k_{tt}=1e-15, k_{ttZ #tau#tau}=0.5, k_{ttZ ll}=0)");

  
  TString leg_title="#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau}{Missing jet}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Ztautau_missing_12092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_Ztautau_incl_12092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160909.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160909.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160909.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11)");
  cut_num_sig.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && genZ_decayMode[0]<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,50));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttZ_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,0,0,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,0,0.5,0,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,0.5,0,1e-15,0.5,0));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttZ Z#rightarrow#tau#tau MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ #tau#tau MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ #tau#tau MEM LR");

  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Ztautau_12092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_Zll_incl_12092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160909.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160909.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160909.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11)");
  cut_num_sig.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,50));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttZ_Zll_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,0,0,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,0,0,10.,0,0,10.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,0.5,10,1e-15,0.5,10));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttZ Z#rightarrowll MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ ll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ #tau#tau + ttZ ll MEM LR");

  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrowll";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Zll_12092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}










void plot_ROC_LR_full_bkg_ttZ_incl_12092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160909.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160909.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160909.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11)");
  cut_num_sig.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,50));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,0,0,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,0,0.5,0.,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,0,0,10.,0,0,10.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,50,true,1e-17,0.5,10,1e-15,0.5,10));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ #tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ ll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ #tau#tau + ttZ ll MEM LR");

  
  TString leg_title="Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_12092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}




void plot_ROC_LR_full_bkg_ttZ_incl_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-15,0,0,1e-13,0,0));


  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,5e-2,1e-1,1e-15,5e-3,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_LR_full_bkg_ttW_incl_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttW*");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-15,0,0,1e-13,0,0));


  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,5e-2,1e-1,1e-15,5e-3,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttW}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttW_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_LR_full_bkg_ttbar_MC_incl_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/*.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;



  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-15,0,0,1e-13,0,0));


  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,5e-2,1e-1,1e-15,5e-3,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=fake lep. MC}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttbar_MC_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}




void plot_ROC_LR_full_bkg_ttbar_datadriven_incl_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/Data/*.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;



  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-15,0,0,1e-13,0,0));


  ROCs.push_back(get_ROC_ttH_full_bkg_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-17,5e-2,1e-1,1e-15,5e-3,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=fake lep. data-driven}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttbar_datadriven_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_nomiss_12092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160909.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160909.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160909.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,10.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,0.5,10));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ #tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ ll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ #tau#tau + ttZ ll MEM LR");

  
  TString leg_title="#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{No missing jet}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_nomiss_12092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_LR_full_bkg_ttZ_missing_12092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160909.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160909.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160909.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1)");
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,10.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0.5,10));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ #tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ ll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ #tau#tau + ttZ ll MEM LR");

  
  TString leg_title="#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{Missing jet}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_missing_12092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttZ_nomiss_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160914.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_2_160915.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_3_160915.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_4_160916.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_5_160917.root");
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_6_16091.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,500,true,1e-15,5e-2,1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ #tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ ll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ #tau#tau + ttZ ll MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_nomiss_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}










void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttW_15092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160914.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_160915.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11)");
  vector<TString> cut_denom_sig = cut_num_sig;
  
  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11)");
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

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttW_15092016";

  plot_ROC(ROCs,leg_entry,true,filename, leg_title);

}








void plot_ROC_weights_no_missjet_ttW_15092016(){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160914.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_160915.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==0)");
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
  //leg_entry.push_back("t#bar{t} l+#tau weight");
  leg_entry.push_back("t#bar{t} l+#tau");
  //leg_entry.push_back("ttH vs t#bar{t} l+#tau LR");
  leg_entry.push_back("ttH vs t#bar{t} l+#tau LR");



  TString filename="ROC_MEM_weights_no_missjet_ttW_15092016";

  plot_ROC(ROCs,leg_entry,true,filename);

}




void plot_ROC_weights_missjet_ttW_15092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160914.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_160915.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1)");
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
  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15));




  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH weight");
  leg_entry.push_back("t#bar{t} l+#tau weight");
  //leg_entry.push_back("t#bar{t} l+#tau + fake lep.=b weight");
  leg_entry.push_back("ttH vs t#bar{t} l+#tau LR");
  //leg_entry.push_back("ttH vs t#bar{t} l+#tau + fake lep.=b LR");


  TString filename="ROC_MEM_weights_missjet_ttW_15092016";

  plot_ROC(ROCs,leg_entry,true,filename);

}








void plot_ROC_LR_ttH_vs_ttbar_DL_fakelep_ttbar_datadriven_092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/Data/*.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttH_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000));

  ROCs.push_back(get_ROC_ttH_vs_ttbar_DL_fakelep_LR_incl(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,20,true,1e-15,1e-13));




  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");


  TString leg_title="#bf{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=fake lep. data-driven}";

  TString filename="ROC_MEM_LR_ttH_vs_ttbar_DL_fakelep_ttbar_datadriven_092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}














void plot_ROC_weights_no_missjet_ttbar_datadriven_092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/Data/*.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && isTrig && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;



  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");

  TString leg_title="#bf{#splitline{Bkg=fake lep. data-driven}{No missing jet}}";


  TString filename="ROC_MEM_weights_no_missjet_ttbar_datadriven_092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_weights_no_missjet_ttbar_MC_092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/*.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && isTrig && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;



  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");

  TString leg_title="#bf{#splitline{Bkg=fake lep. MC}{No missing jet}}";


  TString filename="ROC_MEM_weights_no_missjet_ttbar_MC_092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_weights_missing_jet_ttbar_datadriven_092016(){

 vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/Data/*.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && isTrig && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-13));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");

  TString leg_title="#splitline{Bkg=fake lep. data-driven}{Missing jet}";


  TString filename="ROC_MEM_weights_missing_jet_ttbar_datadriven_092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_weights_missingjet_ttbar_MC_092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/*.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && isTrig && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;



  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));
  ROCs.push_back(get_ROC_ttbar_DL_fakelep_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_ttbar_DL_fakelep_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-13));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("t#bar{t} MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");

  TString leg_title="#bf{#splitline{Bkg=fake lep. MC}{Missing jet}}";


  TString filename="ROC_MEM_weights_missingjet_ttbar_MC_092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_LR_full_bkg_ttZ_Ztautau_no_miss_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && genZ_decayMode[0]<=5 && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  //ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,5e-2,0.1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  //leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrow#tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrowll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");


  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Ztautau_nomiss_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_LR_full_bkg_ttZ_Ztautau_missing_14092016(){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && genZ_decayMode[0]<=5 && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;

  vector<TGraphErrors*> ROCs;

  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  //ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-13,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-14,5e-2,1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  //leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrow#tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrowll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Ztautau_missing_14092016";


  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}










void plot_ROC_LR_full_bkg_ttZ_Zll_no_miss_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && (genZ_decayMode[0]==6||genZ_decayMode[0]==7) && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  //ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,5e-2,0.1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  //leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrow#tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrowll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrowll}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Zll_nomiss_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_LR_full_bkg_ttZ_Zll_missing_14092016(){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && (genZ_decayMode[0]==6||genZ_decayMode[0]==7) && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;

  vector<TGraphErrors*> ROCs;

  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  //ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-13,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-14,5e-2,1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  //leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrow#tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrowll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrowll}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Zll_missing_14092016";


  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttZ_no_miss_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,5e-2,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrow#tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrowll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_nomiss_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_missing_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-13,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,5e-3,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrow#tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrowll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_missing_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttW_no_miss_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttW*.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,5e-2,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrow#tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrowll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttW}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttW_nomiss_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttW_missing_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttW*.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,5e-3,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrow#tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrowll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttW}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttW_missing_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttbar_datadriven_nomiss_14092016(){


 vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/Data/*.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && isTrig && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;



  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  //ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,5e-2,0.1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  //leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrow#tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrowll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=fake lep. datadriven}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttbar_datadriven_nomiss_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttbar_datadriven_missing_14092016(){

 vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/Data/*.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && isTrig && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;



  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  //ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-14,5e-2,1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  //leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrow#tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrowll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=fake lep. data-driven}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttbar_datadriven_missing_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttbar_MC_nomiss_14092016(){

 vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/ttbar_DL_*.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && isTrig && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;



  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  //ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));


  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,5e-2,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  //leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrow#tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrowll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=fake lep. MC}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttbar_datadriven_nomiss_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttbar_MC_missing_14092016(){

 vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/*.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && isTrig && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  //ROCs.push_back(get_ROC_ttH_weight_category(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-14,5e-2,1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  //leg_entry.push_back("ttH MEM weight");
  leg_entry.push_back("ttH vs t#bar{t} MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrow#tau#tau MEM LR");
  leg_entry.push_back("ttH vs ttZ Z#rightarrowll MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=fake lep. MC}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttbar_MC_missing_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_LR_full_bkg_ttbar_datadriven_nomiss_test_14092016(){

 vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/Data/*.root");



  vector<TString> cut_num_sig0;
  cut_num_sig0.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && EventNumber%4==0)");
  vector<TString> cut_denom_sig0 = cut_num_sig0;
  vector<TString> cut_num_bkg0;
  cut_num_bkg0.push_back("event_weight_ttH*(category==41 && isTrig && integration_type==0 && EventNumber%4==0)");
  vector<TString> cut_denom_bkg0=cut_num_bkg0;


  vector<TString> cut_num_sig1;
  cut_num_sig1.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && EventNumber%4==1)");
  vector<TString> cut_denom_sig1 = cut_num_sig1;  
  vector<TString> cut_num_bkg1;
  cut_num_bkg1.push_back("event_weight_ttH*(category==41 && isTrig && integration_type==0 && EventNumber%4==1)");
  vector<TString> cut_denom_bkg1=cut_num_bkg1;

  vector<TString> cut_num_sig2;
  cut_num_sig2.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && EventNumber%4==2)");
  vector<TString> cut_denom_sig2 = cut_num_sig2;  
  vector<TString> cut_num_bkg2;
  cut_num_bkg2.push_back("event_weight_ttH*(category==41 && isTrig && integration_type==0 && EventNumber%4==2)");
  vector<TString> cut_denom_bkg2=cut_num_bkg2;

  vector<TString> cut_num_sig3;
  cut_num_sig3.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && isTrig && integration_type==0 && EventNumber%4==3)");
  vector<TString> cut_denom_sig3 = cut_num_sig3;  
  vector<TString> cut_num_bkg3;
  cut_num_bkg3.push_back("event_weight_ttH*(category==41 && isTrig && integration_type==0 && EventNumber%4==3)");
  vector<TString> cut_denom_bkg3=cut_num_bkg3;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig0,cut_denom_sig0,cut_num_bkg0,cut_denom_bkg0,100));
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig1,cut_denom_sig1,cut_num_bkg1,cut_denom_bkg1,100));
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig2,cut_denom_sig2,cut_num_bkg2,cut_denom_bkg2,100));
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig3,cut_denom_sig3,cut_num_bkg3,cut_denom_bkg3,100));


  vector<TString> leg_entry;
  leg_entry.push_back("Event%4==0");
  leg_entry.push_back("Event%4==1");
  leg_entry.push_back("Event%4==2");
  leg_entry.push_back("Event%4==3");
 

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=fake lep. MC}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttbar_datadriven_nomiss_14092016";

  plot_ROC(ROCs,leg_entry,false,filename,leg_title);

}












void plot_ROC_LR_full_bkg_ttZ_nomiss_fullperm_14092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160914.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");

  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_fullperm_1_160930.root");

  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttV/ttZ_split_2lSS_MEM_full_perm_161003.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,5e-2,1e-1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,5e-2,1e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR full perm");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_nomiss_fullperm_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_missing_fullperm_14092016(){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160914.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");

  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_fullperm_1_160930.root");

  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttV/ttZ_split_2lSS_MEM_full_perm_161003.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,5e-3,1e-1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,5e-2,1e-1));

  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR full perm");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_missing_fullperm_14092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}










void plot_ROC_LR_full_bkg_ttZ_nomiss_missing_jet_fix_092016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");

  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");

  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttV/ttZ_split_2lSS_MEM_160927.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,5e-2,1e-1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,5e-2,1e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR new");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_nomiss_missing_jet_fix_092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_missing_missing_jet_fix_092016(){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");

  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");

  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttV/ttZ_split_2lSS_MEM_160927.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,5e-3,1e-1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-17,5e-2,1e-1));

  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR");
  leg_entry.push_back("ttH vs t#bar{t} + ttZ MEM LR new");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_missing_missing_jet_fix_092016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}










void plot_ROC_LR_full_bkg_ttZ_Ztautau_no_miss_15102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig)");
  //cut_num_sig.push_back("(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && genZ_decayMode[0]<=5 && integration_type==0 && isTrig)");
  //cut_num_bkg.push_back("(category==11 && genZ_decayMode[0]<=5 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  //ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-18,1e-1,2e-1));

  vector<TString> leg_entry;
  //leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t}");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Ztautau_nomiss_15102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_Ztautau_missing_15102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig)");
  //cut_num_sig.push_back("(category==11 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && genZ_decayMode[0]<=5 && integration_type==1 && isTrig)");
  //cut_num_bkg.push_back("(category==11 && genZ_decayMode[0]<=5 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  //ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-12,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,5e-15,5e-2,5e-1));


  vector<TString> leg_entry;
  //leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t}");
  leg_entry.push_back("Combined LR");


  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Ztautau_missing_15102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_LR_full_bkg_ttZ_Zll_no_miss_15102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig)");
  //cut_num_sig.push_back("(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7) && integration_type==0 && isTrig)");
  //cut_num_bkg.push_back("(category==11 && (genZ_decayMode[0]==6||genZ_decayMode[0]==7) && integration_type==0 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  //ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-18,1e-1,2e-1));

  vector<TString> leg_entry;
  //leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t}");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrowll}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Zll_nomiss_15102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_Zll_missing_15102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig)");
  //cut_num_sig.push_back("(category==11 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && (genZ_decayMode[0]==6||genZ_decayMode[0]==7) && integration_type==1 && isTrig)");
  //cut_num_bkg.push_back("(category==11 && (genZ_decayMode[0]==6||genZ_decayMode[0]==7) && integration_type==1 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  //ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-12,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,5e-15,5e-2,5e-1));


  vector<TString> leg_entry;
  //leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t}");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrowll}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Zll_missing_15102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttbar_DL_no_miss_15102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/ttbar_DL_*.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig)");
  //cut_num_sig.push_back("(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && integration_type==0 && isTrig)");
  //cut_num_bkg.push_back("(category==41 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  //ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,0,0,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));

  vector<TString> leg_entry;
  //leg_entry.push_back("2lSS ttH vs t#{b} MVA");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t}");
  leg_entry.push_back("Combined LR");



  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=Fake lepton MC}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttbar_DL_nomiss_15102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttbar_DL_missing_15102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/ttbar_DL_*.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig)");
  //cut_num_sig.push_back("(category==11 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && integration_type==1 && isTrig)");
  //cut_num_bkg.push_back("(category==41 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  //ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-12,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,5e-15,5e-2,5e-1));


  vector<TString> leg_entry;
  //leg_entry.push_back("2lSS ttH vs t#{b} MVA");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t}");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=Fake lepton MC}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttbar_DL_missing_15102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}










void plot_ROC_LR_full_bkg_ttZ_Ztautau_no_miss_fullperm_20102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");

  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_fullperm_*");


  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttV/ttZ_split_2lSS_MEM_full_perm_161003.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && genZ_decayMode[0]<=5 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-18,1e-1,2e-1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-18,1e-1,2e-1));

  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau old");
  leg_entry.push_back("Combined LR old");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau new");
  leg_entry.push_back("Combined LR new");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Ztautau_nomiss_fullperm_20102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_Ztautau_missing_fullperm_20102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");

  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_fullperm_*");


  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttV/ttZ_split_2lSS_MEM_full_perm_161003.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && genZ_decayMode[0]<=5 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,5e-15,5e-2,5e-1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,5e-15,5e-2,5e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau old");
  leg_entry.push_back("Combined LR old");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrow#tau#tau new");
  leg_entry.push_back("Combined LR new");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrow#tau#tau}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Ztautau_missing_fullperm_20102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}










void plot_ROC_LR_full_bkg_ttZ_Zll_no_miss_fullperm_20102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");

  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_fullperm_*");

  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttV/ttZ_split_2lSS_MEM_full_perm_161003.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7) && integration_type==0 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-18,1e-1,2e-1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-18,1e-1,2e-1));

  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll old");
  leg_entry.push_back("Combined LR old");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll new");
  leg_entry.push_back("Combined LR new");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrowll}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Zll_nomiss_fullperm_20102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_Zll_missing_fullperm_20102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_160914.root");

  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_fullperm_*");

  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttV/ttZ_split_2lSS_MEM_full_perm_161003.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && (genZ_decayMode[0]==6||genZ_decayMode[0]==7) && integration_type==1 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,5e-15,5e-2,5e-1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,5e-15,5e-2,5e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll old");
  leg_entry.push_back("Combined LR old");
  leg_entry.push_back("Specif. LR ttZ Z#rightarrowll new");
  leg_entry.push_back("Combined LR new");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ Z#rightarrowll}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttZ_Zll_missing_fullperm_20102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttbar_DL_no_miss_fullperm_20102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/ttbar_DL_*.root");

  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/TTJets/ttbar_DL_*.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));

  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("Specif. LR t#bar{t} old");
  leg_entry.push_back("Combined LR old");
  leg_entry.push_back("Specif. LR t#bar{t} new");
  leg_entry.push_back("Combined LR new");


  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=Fake lepton MC}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttbar_DL_nomiss_fullperm_20102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttbar_DL_missing_fullperm_20102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/ttbar_DL_*.root");


  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");

  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_dev/nominal/TTJets/ttbar_DL_*.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-12,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,5e-15,5e-2,5e-1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-12,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,5e-15,5e-2,5e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("Specif. LR t#bar{t} old");
  leg_entry.push_back("Combined LR old");
  leg_entry.push_back("Specif. LR t#bar{t} new");
  leg_entry.push_back("Combined LR new");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=Fake lepton MC}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_full_bkg_ttbar_DL_missing_fullperm_20102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_LR_full_bkg_ttbar_DL_no_miss_26102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/ttbar_DL_*.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  //ROCs.push_back(get_ROC_ttbar_DL_fakelep_ttau_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("Specif. LR t#bar{t} fake tlep+ttau");
  leg_entry.push_back("Specif. LR t#bar{t} fake ttau");
  leg_entry.push_back("Combined LR old");


  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=Fake lepton MC}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_ttbar_DL_fakelep_ttau_nomiss_26102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttbar_DL_missing_26102016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_*.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM/nominal/TTJets/ttbar_DL_*.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig;
  

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==41 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,1e-15,0,0));

  //ROCs.push_back(get_ROC_ttbar_DL_fakelep_ttau_weight(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("Specif. LR t#bar{t} fake tlep+ttau");
  leg_entry.push_back("Specif. LR t#bar{t} fake ttau");
  leg_entry.push_back("Combined LR old");


  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=Fake lepton MC}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_ttbar_DL_fakelep_ttau_missing_26102016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}





void plot_ROC_LR_full_bkg_ttZ_nomiss_07112016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttH_genmatch/ttH_Hnonbb_split_2lSS_MEM_genmatch.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttV_genmatch/ttZ_split_2lSS_MEM_genmatch.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau ");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll ");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_nomiss_07112016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_LR_full_bkg_ttZ_genmatch_no_miss_07112016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttH_genmatch/ttH_Hnonbb_split_2lSS_MEM_genmatch.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttV_genmatch/ttZ_split_2lSS_MEM_genmatch.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig && isGenMatched)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig && isGenMatched)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau ");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll ");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{No missing jet gen. match.}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_genmatch_nomiss_07112016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttZ_genmatch_antilep_no_miss_07112016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttH_genmatch/ttH_Hnonbb_split_2lSS_MEM_genmatch.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttV_genmatch/ttZ_split_2lSS_MEM_genmatch.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig && isGenMatched && recotauh_sel_againstMuonLoose3[0] && recotauh_sel_againstElectronLooseMVA6[0])");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig && isGenMatched && recotauh_sel_againstMuonLoose3[0] && recotauh_sel_againstElectronLooseMVA6[0])");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau ");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll ");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{No missing jet gen. match. + antilep.}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_genmatch_antilep_nomiss_07112016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}










void plot_ROC_LR_full_bkg_ttZ_missing_07112016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttH_genmatch/ttH_Hnonbb_split_2lSS_MEM_genmatch.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttV_genmatch/ttZ_split_2lSS_MEM_genmatch.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau ");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll ");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_missing_07112016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_LR_full_bkg_ttZ_genmatch_missing_07112016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttH_genmatch/ttH_Hnonbb_split_2lSS_MEM_genmatch.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttV_genmatch/ttZ_split_2lSS_MEM_genmatch.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig && isGenMatched)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig && isGenMatched)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau ");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll ");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{Missing jet gen. match.}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_genmatch_missing_07112016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttZ_genmatch_antilep_missing_07112016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttH_genmatch/ttH_Hnonbb_split_2lSS_MEM_genmatch.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_09_2016/ntuples_MEM_missing_jet_fix/nominal/ttV_genmatch/ttZ_split_2lSS_MEM_genmatch.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig && isGenMatched && recotauh_sel_againstMuonLoose3[0] && recotauh_sel_againstElectronLooseMVA6[0])");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig && isGenMatched && recotauh_sel_againstMuonLoose3[0] && recotauh_sel_againstElectronLooseMVA6[0])");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau ");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll ");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{Missing jet gen. match. + antilep}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_genmatch_antilep_missing_07112016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttZ_genmatch_no_miss_22112016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_temp.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig && isGenMatched)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig && isGenMatched)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau ");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll ");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{No missing jet gen. match.}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_genmatch_nomiss_22112016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_genmatch_missing_22112016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_temp.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig && isGenMatched && n_recoPFJet>=4)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig && isGenMatched && n_recoPFJet>=4)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau ");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll ");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{Missing jet gen. match.}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_genmatch_missing_22112016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttW_genmatch_no_miss_22112016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_temp.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttW_*");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig && isGenMatched)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig && isGenMatched)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau ");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll ");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttW}{No missing jet gen. match.}}";

  TString filename="ROC_MEM_LR_ttH_ttW_genmatch_nomiss_22112016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttW_genmatch_missing_22112016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_temp.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttW_*");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig && isGenMatched)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig && isGenMatched)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau ");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll ");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttW}{Missing jet gen. match.}}";

  TString filename="ROC_MEM_LR_ttH_ttW_genmatch_missing_22112016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_no_miss_122016(){

  vector<TString> file_sig0;
  file_sig0.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root");
  vector<TString> file_sig1;
  file_sig1.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root");
vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root");
  vector<TString> file_sig3;
  file_sig3.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root");
  vector<TString> file_sig4;
  file_sig4.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root");


  vector<TString> file_bkg0;
  file_bkg0.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.1_161205.root");
  vector<TString> file_bkg1;
  file_bkg1.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.25_161205.root");
  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.5_161203.root");
  vector<TString> file_bkg3;
  file_bkg3.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117.root");
  vector<TString> file_bkg4;
  file_bkg4.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x2_161203.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig0,file_bkg0,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-17,5e-2,1e-1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig1,file_bkg1,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-17,5e-2,1e-1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-17,5e-2,1e-1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig3,file_bkg3,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-17,5e-2,1e-1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig4,file_bkg4,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-17,5e-2,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("#points nominal / 10");
  leg_entry.push_back("#points nominal / 4");
  leg_entry.push_back("#points nominal / 2");
  leg_entry.push_back("#points nominal");
  leg_entry.push_back("#points nominal * 2");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_nomiss_122016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_missing_122016(){

  vector<TString> file_sig0;
  file_sig0.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.1_161205.root");
  vector<TString> file_sig1;
  file_sig1.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.25_161204.root");
  vector<TString> file_sig2;
  file_sig2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x0.5_161204.root");
  vector<TString> file_sig3;
  file_sig3.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_161119.root");
  vector<TString> file_sig4;
  file_sig4.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_nbr_points_x2_161203.root");

  vector<TString> file_bkg0;
  file_bkg0.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.1_161205.root");
  vector<TString> file_bkg1;
  file_bkg1.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.25_161205.root");
  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x0.5_161203.root");
  vector<TString> file_bkg3;
  file_bkg3.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_161117.root");
  vector<TString> file_bkg4;
  file_bkg4.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_nbr_points_x2_161203.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight*triggerSF_weight*leptonSF_ttH_weight*bTagSF_weight*(category==11 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig0,file_bkg0,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-14,5e-2,1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig1,file_bkg1,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-14,5e-2,1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig2,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-14,5e-2,1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig3,file_bkg3,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-14,5e-2,1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig4,file_bkg4,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-14,5e-2,1));


  vector<TString> leg_entry;
  leg_entry.push_back("#points nominal / 10");
  leg_entry.push_back("#points nominal / 4");
  leg_entry.push_back("#points nominal / 2");
  leg_entry.push_back("#points nominal");
  leg_entry.push_back("#points nominal * 2");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau/WW/ZZ / Bkg=ttZ}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_missing_122016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}











void plot_ROC_LR_full_bkg_ttZ_Ztautau_genmatch_nomiss_10122016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && isGenMatched && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && isGenMatched && genZ_decayMode[0]<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-17,5e-2,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH, H#rightarrow#tau#tau / Bkg=ttZ, Z#rightarrow#tau#tau }{No missing jet + gen. match.}}";

  TString filename="ROC_MEM_LR_ttH_tautau_ttZ_tautau_genmatch_nomiss_10122016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_LR_full_bkg_ttZ_Ztautau_genmatch_missing_10122016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && isGenMatched && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && isGenMatched && genZ_decayMode[0]<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-14,5e-2,1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH, H#rightarrow#tau#tau / Bkg=ttZ, Z#rightarrow#tau#tau }{Missing jet + gen. match.}}";

  TString filename="ROC_MEM_LR_ttH_tautau_ttZ_tautau_genmatch_missing_10122016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttZ_Zll_genmatch_nomiss_10122016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && isGenMatched && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && isGenMatched && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-17,5e-2,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH, H#rightarrow#tau#tau / Bkg=ttZ, Z#rightarrowll}{No missing jet + gen. match.}}";

  TString filename="ROC_MEM_LR_ttH_tautau_ttZ_Zll_genmatch_nomiss_10122016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_LR_full_bkg_ttZ_Zll_genmatch_missing_10122016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && isGenMatched && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && isGenMatched && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-14,5e-2,1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH, H#rightarrow#tau#tau / Bkg=ttZ, Z#rightarrowll}{Missing jet + gen. match.}}";

  TString filename="ROC_MEM_LR_ttH_tautau_ttZ_Zll_genmatch_missing_10122016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttbar_DL_nomiss_10122016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/TTbar/TTbar_DL_split_2lSS_lepMVA_CR_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && isGenMatched && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && integration_type==0 && isTrig && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-17,5e-2,1e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t}");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH, H#rightarrow#tau#tau / Bkg=t#bar{t} DL}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_tautau_ttbar_DL_nomiss_10122016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_LR_full_bkg_ttbar_DL_missing_10122016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_11_2016/ntuples_MEM/nominal/TTbar/TTbar_DL_split_2lSS_lepMVA_CR_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_ICHEP*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && isGenMatched && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight_ICHEP*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && integration_type==1 && isTrig && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-14,5e-2,1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH, H#rightarrow#tau#tau / Bkg=t#bar{t} DL}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_tautau_ttbar DL_missing_10122016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttZ_Ztautau_nomiss_04012016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && genH_decayMode[1]<=5)");
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && genZ_decayMode[0]<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttZ Z#rightarrow#tau#tau}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_Ztautau_nomiss_04012016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_Zll_nomiss_04012016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttZ Z#rightarrowll}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_Zll_nomiss_04012016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_LR_full_bkg_fakes_nomiss_04012016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/*_2016*_2lSS_lepMVA_CR_MEM_*.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && isTrig && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && integration_type==0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=Fakes}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_fakes_nomiss_04012016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_LR_full_bkg_ttZ_Ztautau_missing_04012016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && genZ_decayMode[0]<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,5e-15,5e-2,5e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttZ Z#rightarrow#tau#tau}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_Ztautau_missing_04012016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_Zll_missing_04012016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA_ttV(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,5e-15,5e-2,5e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs ttV MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttZ Z#rightarrowll}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_ttZ_Zll_missing_04012016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_LR_full_bkg_fakes_missing_04012016(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/*_2016*_2lSS_lepMVA_CR_MEM_*.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*(category==41 && isTrig && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0] && integration_type==1)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_2lSS_MVA(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,5e-15,5e-2,5e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("2lSS ttH vs t#bar{t} MVA");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=Fakes}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_fakes_missing_04012016";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}











void plot_ROC_LR_full_bkg_ttZ_Ztautau_nomiss_10012017(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && genZ_decayMode[0]<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttZ Z#rightarrow#tau#tau}{No missing jet}}";

  TString filename="2lss1tau_Moriond/ROC_MEM_LR_ttH_tautau_ttZ_Ztautau_nomiss";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}





void plot_ROC_LR_full_bkg_ttZ_Ztautau_missing_10012017(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && genZ_decayMode[0]<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,5e-15,5e-2,5e-1));

  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttZ Z#rightarrow#tau#tau}{Missing jet}}";

  TString filename="2lss1tau_Moriond/ROC_MEM_LR_ttH_tautau_ttZ_Ztautau_missing";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_full_bkg_ttZ_Zll_nomiss_10012017(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttZ Z#rightarrowll}{No missing jet}}";

  TString filename="2lss1tau_Moriond/ROC_MEM_LR_ttH_tautau_ttZ_Zll_nomiss";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}




void plot_ROC_LR_MVA_2lSS1tau_full_bkg_ttZ_nomiss(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig_v2)");
  vector<TString> cut_denom_sig = cut_num_sig;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig_v2)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,1.));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_noMEM_ttV",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_MEM_LR_ttV",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_MEM_weights_ttV",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Combined LR ttZ");
  leg_entry.push_back("MVA ttH/ttZ no MEM");
  leg_entry.push_back("MVA ttH/ttZ MEM LR");
  leg_entry.push_back("MVA ttH/ttZ MEM weights");
  

  TString leg_title="#bf{#splitline{Sig=ttH / Bkg=ttZ}{No missing jet}}";

  TString filename="ROC_MEM_LR_MVA_2lSS1tau_ttH_ttZ_nomiss";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}




void plot_ROC_LR_MVA_2lSS1tau_full_bkg_ttZ_missing(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig_BDTMEM.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig_v2)");
  vector<TString> cut_denom_sig = cut_num_sig;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig_v2)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,1.));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_noMEM_ttV",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_MEM_LR_ttV",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_MEM_weights_ttV",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Combined LR ttZ");
  leg_entry.push_back("MVA ttH/ttZ no MEM");
  leg_entry.push_back("MVA ttH/ttZ MEM LR");
  leg_entry.push_back("MVA ttH/ttZ MEM weights");
  

  TString leg_title="#bf{#splitline{Sig=ttH / Bkg=ttZ}{Missing jet}}";

  TString filename="ROC_MEM_LR_MVA_2lSS1tau_ttH_ttZ_missing";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}




void plot_ROC_LR_full_bkg_ttZ_Zll_missing_10012017(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,5e-15,5e-2,5e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");  

  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttZ Z#rightarrowll}{Missing jet}}";

  TString filename="2lss1tau_Moriond/ROC_MEM_LR_ttH_tautau_ttZ_Zll_missing";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttbar_DL_nomiss_10012017(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_*split_2lSS_lepMVA_CR_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight_MCSummer2016*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && integration_type==0 && isTrig && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");
  
  TString leg_title="#bf{#splitline{Sig=ttH, H#rightarrow#tau#tau / Bkg=t#bar{t} DL}{No missing jet}}";

  TString filename="2lss1tau_Moriond/ROC_MEM_LR_ttH_tautau_ttbar_DL_nomiss";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_LR_full_bkg_ttbar_DL_missing_10012017(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_*split_2lSS_lepMVA_CR_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH*MC_weight*PU_weight_MCSummer2016*triggerSF_weight*bTagSF_CSVshape_weight*(category==41 && integration_type==1 && isTrig && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,5e-15,5e-2,5e-1));

  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");
  
  TString leg_title="#bf{#splitline{Sig=ttH, H#rightarrow#tau#tau / Bkg=t#bar{t} DL}{Missing jet}}";

  TString filename="2lss1tau_Moriond/ROC_MEM_LR_ttH_tautau_ttbar_DL_missing";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}











void plot_ROC_LR_MVA_2lSS1tau_full_bkg_ttbar_DL_nomiss(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/ttHJet_split_2lSS_MEM_btagSF_trig_lepTauSF_new_BDT.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_DL*_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_BDT.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v2*bTagSF_CSVshape_weight_v2*(category==11 && integration_type==0 && isTrig_v2 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)");
  vector<TString> cut_denom_sig = cut_num_sig;


  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH_v2*MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v2*bTagSF_CSVshape_weight_v2*(category==41 && integration_type==0 && isTrig_v2 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs; 
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_noMEM_ttbar",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_MEM_LR_ttbar",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("MVA ttH/t#bar{t} no MEM");
  leg_entry.push_back("MVA ttH/t#bar{t} w/ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH / Bkg=t#bar{t} DL}{No missing jet}}";

  TString filename="ROC_MEM_LR_MVA_ttH_ttbar_DL_nomiss";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_LR_MVA_2lSS1tau_full_bkg_ttbar_DL_missing(){


 vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/ttHJet_split_2lSS_MEM_btagSF_trig_lepTauSF_new_BDT.root");

  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_DL*_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_BDT.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v2*bTagSF_CSVshape_weight_v2*(category==11 && integration_type==1 && isTrig_v2 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)");
  vector<TString> cut_denom_sig = cut_num_sig;


  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("event_weight_ttH_v2*MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v2*bTagSF_CSVshape_weight_v2*(category==41 && integration_type==1 && isTrig_v2 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0 && recotauh_sel_byMediumIsolationMVArun2v1DBdR03oldDMwLT[0])");
  vector<TString> cut_denom_bkg=cut_num_bkg;



  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-15,0,0));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_noMEM_ttbar",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_MEM_LR_ttbar",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("MVA ttH/t#bar{t} no MEM");
  leg_entry.push_back("MVA ttH/t#bar{t} w/ MEM LR");

  
  TString leg_title="#bf{#splitline{Sig=ttH / Bkg=t#bar{t} DL}{Missing jet}}";

  TString filename="ROC_MEM_LR_MVA_ttH_ttbar_DL_missing";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);


}









void plot_ROC_1l2tau_ttbar_SL(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_PU_newtrig_BDT_1l2tau.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split_PU_newtrig_BDT_1l2tau.root");

  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==20 && isTrig_v2)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*bTagSF_CSVshape_weight*(category==20 && isTrig_v2)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs; 
  //ROCs.push_back(get_ROC_mvis(file_sig,file_bkg,"HTauTauTree_1l_2tau",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_1l2tau_ttbar",file_sig,file_bkg,"HTauTauTree_1l_2tau",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));


  vector<TString> leg_entry;
  //leg_entry.push_back("m_{vis}(#tau#tau)");
  leg_entry.push_back("MVA ttH/t#bar{t}");
  
  TString leg_title="#bf{Sig=ttH / Bkg=t#bar{t} SL}";

  TString filename="ROC_BDT_1l2tau_ttH_ttbar_SL";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_LR_MVA_2lSS1tau_full_bkg_ttW_nomiss(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig_v2)");
  vector<TString> cut_denom_sig = cut_num_sig;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig_v2)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,1.));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_noMEM_ttV",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_MEM_LR_ttV",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_MEM_weights_ttV",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Combined LR ttZ");
  leg_entry.push_back("MVA ttH/ttZ no MEM");
  leg_entry.push_back("MVA ttH/ttZ MEM LR");
  leg_entry.push_back("MVA ttH/ttZ MEM weights");
  

  TString leg_title="#bf{#splitline{Sig=ttH / Bkg=ttW}{No missing jet}}";

  TString filename="ROC_MEM_LR_MVA_2lSS1tau_ttH_ttW_nomiss";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}




void plot_ROC_LR_MVA_2lSS1tau_full_bkg_ttW_missing(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig_BDTMEM.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig_BDTMEM.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig_v2)");
  vector<TString> cut_denom_sig = cut_num_sig;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig_v2)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,1.));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_noMEM_ttV",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_MEM_LR_ttV",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA("MVA_2lSS1tau_MEM_weights_ttV",file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Combined LR ttZ");
  leg_entry.push_back("MVA ttH/ttZ no MEM");
  leg_entry.push_back("MVA ttH/ttZ MEM LR");
  leg_entry.push_back("MVA ttH/ttZ MEM weights");
  

  TString leg_title="#bf{#splitline{Sig=ttH / Bkg=ttW}{Missing jet}}";

  TString filename="ROC_MEM_LR_MVA_2lSS1tau_ttH_ttW_missing";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}







void plot_ROC_LR_MVA_2lSS1tau_full_bkg_ttV_nomiss(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/ttHJet_split_2lSS_MEM_btagSF_trig_lepTauSF_new_BDT.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_btagSF_trig_lepTauSF_new_BDT.root");

  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_btagSF_trig_lepTauSF_new_BDT.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v2*bTagSF_CSVshape_weight_v2*(category==11 && integration_type==0 && isTrig_v2 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)");
  vector<TString> cut_denom_sig = cut_num_sig;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v2*bTagSF_CSVshape_weight_v2*(category==11 && integration_type==0 && isTrig_v2 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2bkg(file_sig,file_bkg,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,3.07,1.10,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2bkg(file_sig,file_bkg,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,3.07,1.10,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2bkg(file_sig,file_bkg,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,3.07,1.10,true,0,0.2,0.4));


  ROCs.push_back(get_ROC_2lSS1tau_MVA_2bkg("MVA_2lSS1tau_noMEM_ttV",file_sig,file_bkg,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,3.07,1.10,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA_2bkg("MVA_2lSS1tau_MEM_LR_ttV",file_sig,file_bkg,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,3.07,1.10,true));



  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Combined LR ttZ");
  leg_entry.push_back("MVA ttH/ttV no MEM");
  leg_entry.push_back("MVA ttH/ttV w/ MEM LR");
  

  TString leg_title="#bf{#splitline{Sig=ttH / Bkg=ttV}{No missing jet}}";

  TString filename="ROC_MEM_LR_MVA_2lSS1tau_ttH_ttV_nomiss";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}










void plot_ROC_LR_MVA_2lSS1tau_full_bkg_ttV_missing(){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/ttHJet_split_2lSS_MEM_btagSF_trig_lepTauSF_new_BDT.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_btagSF_trig_lepTauSF_new_BDT.root");

  vector<TString> file_bkg2;
  file_bkg2.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_btagSF_trig_lepTauSF_new_BDT.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v2*bTagSF_CSVshape_weight_v2*(category==11 && integration_type==1 && isTrig_v2 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)");
  vector<TString> cut_denom_sig = cut_num_sig;

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight_v2*leptonSF_ttH_weight_v2*bTagSF_CSVshape_weight_v2*(category==11 && integration_type==1 && isTrig_v2 && recolep_sel_charge[0]*recotauh_sel_charge[0]<0)");
  vector<TString> cut_denom_bkg=cut_num_bkg;



  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2bkg(file_sig,file_bkg,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,8.33,7.18,true,0,0.05,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2bkg(file_sig,file_bkg,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,8.33,7.18,true,0,0.,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR_2bkg(file_sig,file_bkg,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,8.33,7.18,true,0,0.01,0.1));

  ROCs.push_back(get_ROC_2lSS1tau_MVA_2bkg("MVA_2lSS1tau_noMEM_ttV",file_sig,file_bkg,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,8.33,7.18,true));

  ROCs.push_back(get_ROC_2lSS1tau_MVA_2bkg("MVA_2lSS1tau_MEM_LR_ttV",file_sig,file_bkg,file_bkg2,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,8.33,7.18,true));



  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Combined LR ttZ");
  leg_entry.push_back("MVA ttH/ttV no MEM");
  leg_entry.push_back("MVA ttH/ttV w/ MEM LR");
  

  TString leg_title="#bf{#splitline{Sig=ttH / Bkg=ttV}{Missing jet}}";

  TString filename="ROC_MEM_LR_MVA_2lSS1tau_ttH_ttV_missing";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}











void plot_ROC_LR_full_bkg_ttW_nomiss_10012017(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==0 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttW}{No missing jet}}";

  TString filename="2lss1tau_Moriond/ROC_MEM_LR_ttH_tautau_ttW_nomiss";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}









void plot_ROC_LR_full_bkg_ttW_missing_10012017(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root");


  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*PU_weight_MCSummer2016*triggerSF_weight*leptonSF_ttH_weight*bTagSF_CSVshape_weight*(category==11 && integration_type==1 && isTrig)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.05,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,0.1));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-15,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,5e-15,5e-2,5e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b");
  leg_entry.push_back("Combined LR");  

  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttW}{Missing jet}}";

  TString filename="2lss1tau_Moriond/ROC_MEM_LR_ttH_tautau_ttW_missing";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}








void plot_ROC_LR_full_bkg_ttZ_Ztautau_nomiss_GPU(){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig.root");
  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM.root");

  vector<TString> file_sig_GPU;
  file_sig_GPU.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttH/test_ttH.root");
  vector<TString> file_bkg_GPU;
  file_bkg_GPU.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttV/test_ttZ.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==0 && isTrig && genZ_decayMode[0]<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau MPI");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau GPU");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll MPI");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll GPU");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b MPI");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b GPU");
  leg_entry.push_back("Combined LR MPI");
  leg_entry.push_back("Combined LR GPU");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttZ Z#rightarrow#tau#tau}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_tautau_ttZ_Ztautau_nomiss_GPU";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}





void plot_ROC_LR_full_bkg_ttZ_Ztautau_missing_GPU(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig.root");
  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM.root");

  vector<TString> file_sig_GPU;
  file_sig_GPU.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttH/test_ttH.root");
  vector<TString> file_bkg_GPU;
  file_bkg_GPU.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttV/test_ttZ.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==1 && isTrig && genZ_decayMode[0]<=5)");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau MPI");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau GPU");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll MPI");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll GPU");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b MPI");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b GPU");
  leg_entry.push_back("Combined LR MPI");
  leg_entry.push_back("Combined LR GPU");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttZ Z#rightarrow#tau#tau}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_tautau_ttZ_Ztautau_missing_GPU";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}






void plot_ROC_LR_full_bkg_ttZ_Zll_nomiss_GPU(){

  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig.root");
  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM.root");

  vector<TString> file_sig_GPU;
  file_sig_GPU.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttH/test_ttH.root");
  vector<TString> file_bkg_GPU;
  file_bkg_GPU.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttV/test_ttZ.root");


  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==0 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==0 && isTrig && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));


  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau MPI");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau GPU");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll MPI");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll GPU");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b MPI");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b GPU");
  leg_entry.push_back("Combined LR MPI");
  leg_entry.push_back("Combined LR GPU");
  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttZ Z#rightarrowll}{No missing jet}}";

  TString filename="ROC_MEM_LR_ttH_tautau_ttZ_Zll_nomiss_GPU";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}





void plot_ROC_LR_full_bkg_ttZ_Zll_missing_GPU(){


  vector<TString> file_sig;
  file_sig.push_back("/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig.root");
  vector<TString> file_bkg;
  file_bkg.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM.root");

  vector<TString> file_sig_GPU;
  file_sig_GPU.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttH/test_ttH.root");
  vector<TString> file_bkg_GPU;
  file_bkg_GPU.push_back("/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM_GPU/nominal/ttV/test_ttZ.root");



  vector<TString> cut_num_sig;
  cut_num_sig.push_back("MC_weight*(category==11 && integration_type==1 && isTrig && genH_decayMode[1]<=5)");
  vector<TString> cut_denom_sig = cut_num_sig; 

  vector<TString> cut_num_bkg;
  cut_num_bkg.push_back("MC_weight*(category==11 && integration_type==1 && isTrig && (genZ_decayMode[0]==6 || genZ_decayMode[0]==7))");
  vector<TString> cut_denom_bkg=cut_num_bkg;


  vector<TGraphErrors*> ROCs;
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.5,0.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,100,true,0,0.,1.));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,0,0));

  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig,file_bkg,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));
  ROCs.push_back(get_ROC_ttH_full_bkg_LR(file_sig_GPU,file_bkg_GPU,"T",cut_num_sig,cut_denom_sig,cut_num_bkg,cut_denom_bkg,1000,true,1e-18,1e-1,2e-1));



  vector<TString> leg_entry;
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau MPI");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrow#tau#tau GPU");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll MPI");
  leg_entry.push_back("Specif. LR ttZ, Z#rightarrowll GPU");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b MPI");
  leg_entry.push_back("Specif. LR t#bar{t} + lep. from b GPU");
  leg_entry.push_back("Combined LR MPI");
  leg_entry.push_back("Combined LR GPU");

  
  TString leg_title="#bf{#splitline{Sig=ttH H#rightarrow#tau#tau / Bkg=ttZ Z#rightarrowll}{Missing jet}}";

  TString filename="ROC_MEM_LR_ttH_tautau_ttZ_Zll_missing_GPU";

  plot_ROC(ROCs,leg_entry,true,filename,leg_title);

}


