#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <Helpers.C>
#include <vector>
#include <TLatex.h>
#include <TGraphErrors.h>
#include <fstream>
#include <sstream>
#include <TString.h>

using namespace std;





void plot_recolep_goodsign_ee_0tauh_2T(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH2F* h = single_plot2D(files,"HTauTauTree","recolep_goodsign[0]","recolep_goodsign[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",3,-1,2,4,-1,3); 
  h->Scale(1/h->Integral());

  h->SetStats(0);
  h->SetTitle("");

  TLegend* leg=new TLegend(0.35,0.75,0.85,0.85);
  leg->SetHeader("#splitline{Dielectron channel}{0 #tau_{h}, 2 tight leptons}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  h->SetMaximum(1.25*h->GetMaximum());
  h->GetXaxis()->SetTitle("Charge assign.(lead. lep.)");
  h->GetYaxis()->SetTitle("Charge assign.(sublead. lep)");

  h->Draw("colz");
  leg->Draw("same");

  TLatex *texl = new TLatex(-0.9,3.1,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="recolep_goodsign_ee_notauh_1L1T";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}






void plot_recolep_goodsign_mumu_0tauh_2T(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH2F* h = single_plot2D(files,"HTauTauTree","recolep_goodsign[0]","recolep_goodsign[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",3,-1,2,4,-1,3); 
  h->Scale(1/h->Integral());

  h->SetStats(0);
  h->SetTitle("");

  TLegend* leg=new TLegend(0.35,0.75,0.85,0.85);
  leg->SetHeader("#splitline{Dimuon channel}{0 #tau_{h}, 2 tight leptons}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  h->SetMaximum(1.25*h->GetMaximum());
  h->GetXaxis()->SetTitle("Charge assign.(lead. lep.)");
  h->GetYaxis()->SetTitle("Charge assign.(sublead. lep)");

  h->Draw("colz");
  leg->Draw("same");

  TLatex *texl = new TLatex(-0.9,3.1,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="recolep_goodsign_mumu_notauh_1L1T";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}








void plot_recolep_goodsign_emu_0tauh_2T(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH2F* h = single_plot2D(files,"HTauTauTree","recolep_goodsign[0]","recolep_goodsign[1]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",3,-1,2,4,-1,3); 
  h->Add(single_plot2D(files,"HTauTauTree","recolep_goodsign[1]","recolep_goodsign[0]","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[1])==11 && abs(recolep_ID[0])==13 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",3,-1,2,4,-1,3)); 

  h->Scale(1/h->Integral());

  h->SetStats(0);
  h->SetTitle("");

  TLegend* leg=new TLegend(0.35,0.75,0.85,0.85);
  leg->SetHeader("#splitline{e#mu channel}{0 #tau_{h}, 2 tight leptons}");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.035);
  leg->SetFillStyle(0);

  TCanvas* c=new TCanvas("c","c",650,600);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.15);

  h->SetMaximum(1.25*h->GetMaximum());
  h->GetXaxis()->SetTitle("Charge assign.(e)");
  h->GetYaxis()->SetTitle("Charge assign.(#mu)");

  h->Draw("colz");
  leg->Draw("same");

  TLatex *texl = new TLatex(-0.9,3.1,"CMS Preliminary, #sqrt{s}=13 TeV, Simulation t#bar{t}");
  texl->SetTextSize(0.03);
  texl->Draw("same");


  TString filename="recolep_goodsign_emu_notauh_1L1T";
  c->SaveAs("../plots/pdf/"+filename+".pdf");
  c->SaveAs("../plots/png/"+filename+".png");

  return;

}









void compute_OS_fractions_ee(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recotauh_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",3,0,3);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recotauh_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65 && (recolep_goodsign[0]==-1||recolep_goodsign[1]==-1))",3,0,3);  

  TH1F* h_B = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recotauh_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65)||(recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",3,0,3);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recotauh_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65)||(recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1||recolep_goodsign[1]==-1))",3,0,3);

  TH1F* h_C = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",3,0,3);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65 && (recolep_goodsign[0]==-1||recolep_goodsign[1]==-1))",3,0,3);  

  TH1F* h_D = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65)||(recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",3,0,3);

  TH1F* h_D_OS = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==11 && abs(recolep_ID[1])==11 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65)||(recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1||recolep_goodsign[1]==-1))",3,0,3);

  float n_A=h_A->Integral();
  float frac_A=h_A_OS->Integral()/n_A;
  float uncert_A=sqrt( frac_A*(1-frac_A)/n_A);

  float n_B=h_B->Integral();
  float frac_B=h_B_OS->Integral()/n_B;
  float uncert_B=sqrt( frac_B*(1-frac_B)/n_B);

  float n_C=h_C->Integral();
  float frac_C=h_C_OS->Integral()/n_C;
  float uncert_C=sqrt( frac_C*(1-frac_C)/n_C);

  float n_D=h_D->Integral();
  float frac_D=h_D_OS->Integral()/n_D;
  float uncert_D=sqrt( frac_D*(1-frac_D)/n_D);

  std::ofstream out("/home/llr/cms/strebler/MEM_Analysis/ttH/macros/OS_fractions_ee_channel.txt");
  out<<"OS(A)/A = "<<frac_A<<" +/- "<<uncert_A<<'\n';
  out<<"OS(B)/B = "<<frac_B<<" +/- "<<uncert_B<<'\n';
  out<<"OS(C)/C = "<<frac_C<<" +/- "<<uncert_C<<'\n';
  out<<"OS(D)/D = "<<frac_D<<" +/- "<<uncert_D<<'\n';


  return;

}







void compute_OS_fractions_mumu(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recotauh_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",3,0,3);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recotauh_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65 && (recolep_goodsign[0]==-1||recolep_goodsign[1]==-1))",3,0,3);  

  TH1F* h_B = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recotauh_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65)||(recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",3,0,3);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recotauh_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65)||(recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1||recolep_goodsign[1]==-1))",3,0,3);

  TH1F* h_C = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",3,0,3);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65 && (recolep_goodsign[0]==-1||recolep_goodsign[1]==-1))",3,0,3);  

  TH1F* h_D = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65)||(recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",3,0,3);

  TH1F* h_D_OS = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && abs(recolep_ID[0])==13 && abs(recolep_ID[1])==13 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65)||(recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && (recolep_goodsign[0]==-1||recolep_goodsign[1]==-1))",3,0,3);

  float n_A=h_A->Integral();
  float frac_A=h_A_OS->Integral()/n_A;
  float uncert_A=sqrt( frac_A*(1-frac_A)/n_A);

  float n_B=h_B->Integral();
  float frac_B=h_B_OS->Integral()/n_B;
  float uncert_B=sqrt( frac_B*(1-frac_B)/n_B);

  float n_C=h_C->Integral();
  float frac_C=h_C_OS->Integral()/n_C;
  float uncert_C=sqrt( frac_C*(1-frac_C)/n_C);

  float n_D=h_D->Integral();
  float frac_D=h_D_OS->Integral()/n_D;
  float uncert_D=sqrt( frac_D*(1-frac_D)/n_D);

  std::ofstream out("/home/llr/cms/strebler/MEM_Analysis/ttH/macros/OS_fractions_mumu_channel.txt");
  out<<"OS(A)/A = "<<frac_A<<" +/- "<<uncert_A<<'\n';
  out<<"OS(B)/B = "<<frac_B<<" +/- "<<uncert_B<<'\n';
  out<<"OS(C)/C = "<<frac_C<<" +/- "<<uncert_C<<'\n';
  out<<"OS(D)/D = "<<frac_D<<" +/- "<<uncert_D<<'\n';


  return;

}







void compute_OS_fractions_emu(){

  vector<TString> files;
  files.push_back("/data_CMS/cms/strebler/TTJets_Samples/ntuples_converted/MiniAODv2_prod_02_2016/ntuple_TTJets_dRveto_gen_iso70_skimmed_lepsign.root");

  TH1F* h_A = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recotauh_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && ((abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11) || (abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)) && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",3,0,3);

  TH1F* h_A_OS = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recotauh_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46  && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65 && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13 && recolep_goodsign[0]==-1)||(abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11 && recolep_goodsign[1]==-1)))",3,0,3);  

  TH1F* h_B = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recotauh_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11) || (abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)) && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65)||(recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",3,0,3);

  TH1F* h_B_OS = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh>=1 && recolep_charge[0]*recotauh_charge[0]<0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65)||(recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13 && recolep_goodsign[0]==-1)||(abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11 && recolep_goodsign[1]==-1)))",3,0,3);

  TH1F* h_C = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11) || (abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)) && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65)",3,0,3);

  TH1F* h_C_OS = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46   && recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]>0.65 && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13 && recolep_goodsign[0]==-1)||(abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11 && recolep_goodsign[1]==-1)))",3,0,3);  

  TH1F* h_D = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11) || (abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13)) && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65)||(recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)))",3,0,3);

  TH1F* h_D_OS = single_plot(files,"HTauTauTree","1","MC_weight*PUReweight*(n_recolep==2 && n_recotauh==0 && recolep_charge[0]*recolep_charge[1]>0 && n_recoPFJet>=3 && recoPFJet_CSVsort_CSVscore[0]>0.8 && recoPFJet_CSVsort_CSVscore[1]>0.46 && ((recolep_leptonMVA[0]>0.65 && recolep_leptonMVA[1]<0.65)||(recolep_leptonMVA[0]<0.65 && recolep_leptonMVA[1]>0.65)) && ((abs(recolep_ID[0])==11 && abs(recolep_ID[1])==13 && recolep_goodsign[0]==-1)||(abs(recolep_ID[0])==13 && abs(recolep_ID[1])==11 && recolep_goodsign[1]==-1)) )",3,0,3);

  float n_A=h_A->Integral();
  float frac_A=h_A_OS->Integral()/n_A;
  float uncert_A=sqrt( frac_A*(1-frac_A)/n_A);

  float n_B=h_B->Integral();
  float frac_B=h_B_OS->Integral()/n_B;
  float uncert_B=sqrt( frac_B*(1-frac_B)/n_B);

  float n_C=h_C->Integral();
  float frac_C=h_C_OS->Integral()/n_C;
  float uncert_C=sqrt( frac_C*(1-frac_C)/n_C);

  float n_D=h_D->Integral();
  float frac_D=h_D_OS->Integral()/n_D;
  float uncert_D=sqrt( frac_D*(1-frac_D)/n_D);

  std::ofstream out("/home/llr/cms/strebler/MEM_Analysis/ttH/macros/OS_fractions_emu_channel.txt");
  out<<"OS(A)/A = "<<frac_A<<" +/- "<<uncert_A<<'\n';
  out<<"OS(B)/B = "<<frac_B<<" +/- "<<uncert_B<<'\n';
  out<<"OS(C)/C = "<<frac_C<<" +/- "<<uncert_C<<'\n';
  out<<"OS(D)/D = "<<frac_D<<" +/- "<<uncert_D<<'\n';


  return;

}

