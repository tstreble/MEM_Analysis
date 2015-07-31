#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <Helpers.C>
#include <vector>

using namespace std;

void plot_genth_mass(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt(genth_e**2-genth_px**2-genth_py**2-genth_pz**2)","",50,120,220));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt((genbh_e+genWh_e)**2-(genbh_px+genWh_px)**2-(genbh_py+genWh_py)**2-(genbh_pz+genWh_pz)**2)","",50,120,220));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt((genbh_e+genq1_e+genq2_e)**2-(genbh_px+genq1_px+genq2_px)**2-(genbh_py+genq1_py+genq2_py)**2-(genbh_pz+genq1_pz+genq2_pz)**2)","",50,120,220));
 

  vector<TString> leg_entry;
  leg_entry.push_back("t_{h}");
  leg_entry.push_back("b_{h}+W_{h}");
  leg_entry.push_back("b_{h}+q_{1}+q_{2}");


  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h_norm->Integral());
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Mass [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Hadronic top mass distribution at generator level");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="genth_mass_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}



void plot_gentl_mass(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt(gentl_e**2-gentl_px**2-gentl_py**2-gentl_pz**2)","",50,120,220));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt((genbl_e+genWl_e)**2-(genbl_px+genWl_px)**2-(genbl_py+genWl_py)**2-(genbl_pz+genWl_pz)**2)","",50,120,220));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt((genbl_e+genlt_e+gennult_e)**2-(genbl_px+genlt_px+gennult_px)**2-(genbl_py+genlt_py+gennult_py)**2-(genbl_pz+genlt_pz+gennult_pz)**2)","",50,120,220));
 

  vector<TString> leg_entry;
  leg_entry.push_back("t_{l}");
  leg_entry.push_back("b_{l}+W_{l}");
  leg_entry.push_back("b_{l}+l_{t}+#nu_{t}");


  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h_norm->Integral());
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Mass [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Leptonic top mass distribution at generator level");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="gentl_mass_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}





void plot_genH_mass(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt(genH_e**2-genH_px**2-genH_py**2-genH_pz**2)","",100,100,150));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt((gentaulep_fromH_e+gentauhad_fromH_e)**2-(gentaulep_fromH_px+gentauhad_fromH_px)**2-(gentaulep_fromH_py+gentauhad_fromH_py)**2-(gentaulep_fromH_pz+gentauhad_fromH_pz)**2)","",100,100,150));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt((genltau_e+gennu1taul_e+gennu2taul_e+genpi_e+gennutauh_e)**2-(genltau_px+gennu1taul_px+gennu2taul_px+genpi_px+gennutauh_px)**2-(genltau_py+gennu1taul_py+gennu2taul_py+genpi_py+gennutauh_py)**2-(genltau_pz+gennu1taul_pz+gennu2taul_pz+genpi_pz+gennutauh_pz)**2)","",100,100,150));
 

  vector<TString> leg_entry;
  leg_entry.push_back("H");
  leg_entry.push_back("#tau_{lep}+#tau_{had}");
  leg_entry.push_back("l_{#tau}+#tau_{h}+#nu's");


  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h_norm->Integral());
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Mass [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("Higgs mass distribution at generator level");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="genH_mass_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_gentauhad_mass(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt(gentauhad_fromH_e**2-gentauhad_fromH_px**2-gentauhad_fromH_py**2-gentauhad_fromH_pz**2)","",100,1.7,1.85));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt((genpi_e+gennutauh_e)**2-(genpi_px+gennutauh_px)**2-(genpi_py+gennutauh_py)**2-(genpi_pz+gennutauh_pz)**2)","",100,1.7,1.85));
 

  vector<TString> leg_entry;
  leg_entry.push_back("#tau_{had}");
  leg_entry.push_back("#tau_{h}+#nu");


  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h_norm->Integral());
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Mass [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("#tau_{had} mass distribution at generator level");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="gentauhad_mass_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}




void plot_genpi_mass(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt((genpi_e)**2-(genpi_px)**2-(genpi_py)**2-(genpi_pz)**2)","",50,0,2));
 

  vector<TString> leg_entry;
  leg_entry.push_back("#tau_{h}");



  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h_norm->Integral());
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Mass [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("#tau_{h} mass distribution at generator level");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  //leg->Draw("same");


  TString filename="genpi_mass_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}







void plot_gentaulep_mass(){

  vector<TH1F*> h;

  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt(gentaulep_fromH_e**2-gentaulep_fromH_px**2-gentaulep_fromH_py**2-gentaulep_fromH_pz**2)","",100,1.7,1.85));
  h.push_back(single_plot("/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root","HTauTauTree","sqrt((genltau_e+gennu1taul_e+gennu2taul_e)**2-(genltau_px+gennu1taul_px+gennu2taul_px)**2-(genltau_py+gennu1taul_py+gennu2taul_py)**2-(genltau_pz+gennu1taul_pz+gennu2taul_pz)**2)","",100,1.7,1.85));
 

  vector<TString> leg_entry;
  leg_entry.push_back("#tau_{lep}");
  leg_entry.push_back("l_{#tau}+#nu's");


  TLegend* leg=new TLegend(0.3,0.65,0.5,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetFillColor(0);
  

  for(unsigned int i=0; i<h.size();i++){
    h[i]->SetLineColor(i+1);
    h[i]->SetLineWidth(2);
    h[i]->Sumw2();
    h[i]->SetStats(0);
    //h[i]->Scale(1/h_norm->Integral());
    h[i]->Scale(1/h[i]->Integral());
    leg->AddEntry(h[i],leg_entry[i]);
  }


  h=sort_histo(h);
  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  h[0]->SetMaximum(1.25*h[0]->GetMaximum());
  h[0]->GetXaxis()->SetTitle("Mass [GeV]");
  h[0]->GetYaxis()->SetTitle(Form("Fraction of events / %.2f [GeV]",binning(h[0])));
h[0]->GetYaxis()->SetTitleOffset(1.7);
  h[0]->SetTitle("#tau_{lep} mass distribution at generator level");

  h[0]->Draw("");
  for(unsigned int i=1; i<h.size();i++){
    h[i]->Draw("same");
  }
  
  leg->Draw("same");


  TString filename="gentaulep_mass_ttH";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}
