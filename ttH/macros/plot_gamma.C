#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <iostream>
#include <TLegend.h>
#include <Helpers.C>
#include <TF1.h>
#include <TF2.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TLatex.h>
#include <TLorentzVector.h>

#include "Helpers_RecoVegas_ttH.C"



vector<float> integration_lim(TF2* gamma2,float costheta_lpi, float t_m,float t_p){

  float costheta_tautau=costheta_lpi;
  float P_taul=t_m;
  float P_taul_int_min=-1;
  float P_taul_int_max=-1;
  float P_taul_max=-1;
  float g2_max=-1;


  //while(P_taul_int_max==-1 && P_taul<min(t_plus,1500.)){
  while(P_taul_int_max==-1 && P_taul<t_p){
    float g2=gamma2->Eval(P_taul,costheta_tautau);
    if(P_taul_int_min==-1 && g2>0)
      P_taul_int_min=abs(P_taul-1);
    if(g2>g2_max){
      g2_max=g2;
      P_taul_max=P_taul;
    }
    if(P_taul_int_min!=-1 && g2<0)
      P_taul_int_max=P_taul;
    P_taul+=1;
  }

  if(P_taul_int_max==-1)
    P_taul_int_max=abs(t_p);

  P_taul=P_taul_max;
  float costheta_tautau_int_min=-2;
  float costheta_tautau_int_max=-2;

  while(costheta_tautau_int_min==-2 && costheta_tautau>=-1){
    float g2=gamma2->Eval(P_taul,costheta_tautau);
    if(g2<0)
      costheta_tautau_int_min=costheta_tautau;
    costheta_tautau-=0.0001;
  }
  
  costheta_tautau=costheta_lpi;
  while(costheta_tautau_int_max==-2 && costheta_tautau<=1){
    float g2=gamma2->Eval(P_taul,costheta_tautau);
    if(g2<0)
      costheta_tautau_int_max=costheta_tautau;
    costheta_tautau+=0.0001;
  }

  vector<float> lim;
  lim.push_back(P_taul_int_min);
  lim.push_back(P_taul_int_max);
  lim.push_back(costheta_tautau_int_min);
  lim.push_back(costheta_tautau_int_max);

  return lim;

}




void plot_gamma2_f_taul_costheta_taultauh(TString sample, int ientry,bool save=false){

  TString file;
  if(sample=="ttH")
    file="/data_CMS/cms/strebler/ttH_Samples/ntuples_converted/ttH_HToTauTau_pfMET_prod_07072015/ntuple_ttH_dRveto_gen_skimmed.root";
 
  TFile* f = TFile::Open(file);
  TTree* tree = (TTree*) f->Get("HTauTauTree");

  float m_tau = 1.777;
  float m_tautau = 125;
  float E_pi;
  float Px_pi;
  float Py_pi;
  float Pz_pi;
  float E_ltau;
  float Px_ltau;
  float Py_ltau;
  float Pz_ltau;

  float E_taul;
  float Px_taul;
  float Py_taul;
  float Pz_taul;
  float E_tauh;
  float Px_tauh;
  float Py_tauh;
  float Pz_tauh;

  float P_pi;
  float m_pi;
  float costheta_lpi;
  float costheta_taultauh;
  
  float P_taul;
  float t_m;
  float t_p;
  float s_m;
  float s_p;


  tree->SetBranchAddress("genpi_e",&E_pi);
  tree->SetBranchAddress("genpi_px",&Px_pi);
  tree->SetBranchAddress("genpi_py",&Py_pi);
  tree->SetBranchAddress("genpi_pz",&Pz_pi);

  tree->SetBranchAddress("genltau_e",&E_ltau);
  tree->SetBranchAddress("genltau_px",&Px_ltau);
  tree->SetBranchAddress("genltau_py",&Py_ltau);
  tree->SetBranchAddress("genltau_pz",&Pz_ltau);

  tree->SetBranchAddress("gentaulep_fromH_e",&E_taul);
  tree->SetBranchAddress("gentaulep_fromH_px",&Px_taul);
  tree->SetBranchAddress("gentaulep_fromH_py",&Py_taul);
  tree->SetBranchAddress("gentaulep_fromH_pz",&Pz_taul);

  tree->SetBranchAddress("gentauhad_fromH_e",&E_tauh);
  tree->SetBranchAddress("gentauhad_fromH_px",&Px_tauh);
  tree->SetBranchAddress("gentauhad_fromH_py",&Py_tauh);
  tree->SetBranchAddress("gentauhad_fromH_pz",&Pz_tauh);



  tree->GetEntry(ientry);
  
  TLorentzVector genpi_tlv(Px_pi, Py_pi, Pz_pi, E_pi);
  P_pi = genpi_tlv.P();
  m_pi = genpi_tlv.M();
  s_m = t_minus(genpi_tlv);
  s_p = t_plus(genpi_tlv);
  
  TLorentzVector genltau_tlv(Px_ltau, Py_ltau, Pz_ltau, E_ltau);
  TLorentzVector gentaul_tlv(Px_taul, Py_taul, Pz_taul, E_taul);
  TLorentzVector gentauh_tlv(Px_tauh, Py_tauh, Pz_tauh, E_tauh);
  costheta_lpi = cos(genltau_tlv.Angle(genpi_tlv.Vect()));
  costheta_taultauh = cos(gentaul_tlv.Angle(gentauh_tlv.Vect()));
  P_taul = gentaul_tlv.P();
  t_m = t_minus(genltau_tlv);
  t_p = t_plus(genltau_tlv);
  
  cout<<"ientry="<<ientry<<endl;


  TF2* P_tauh=new TF2("P_tauh","([0]*y*x+sqrt([2]+x^2)*sqrt([0]^2-[2]*([2]+(1-y^2)*x^2)))/([2]+(1-y^2)*x^2)",0,1500,-1,1);
  P_tauh->SetParameter(0,0.5*m_tautau*m_tautau-m_tau*m_tau);
  P_tauh->SetParameter(2,m_tau*m_tau);

  cout<<"P_tauh(P_taul_true,costheta_tautau_true)="<<P_tauh->Eval(P_taul,costheta_lpi)<<endl;

  TF2* costheta_tauhpi=new TF2("costheta_tauhpi","(2*sqrt([0]+P_tauh^2)*[1]-[0]-[2])/(2*P_tauh*[3])",0,1500,-1,1);
  costheta_tauhpi->SetParameter(0,m_tau*m_tau);
  costheta_tauhpi->SetParameter(1,E_pi);
  costheta_tauhpi->SetParameter(2,m_pi*m_pi);
  costheta_tauhpi->SetParameter(3,P_pi);

  TF2* alpha=new TF2("alpha","(y-[0]*costheta_tauhpi)/(1-[0]^2)",0,1500,-1,1);
  alpha->SetParameter(0,costheta_lpi);

  TF2* beta=new TF2("beta","(costheta_tauhpi-[0]*y)/(1-[0]^2)",0,1500,-1,1);
  beta->SetParameter(0,costheta_lpi);

  TF2* gamma2=new TF2("gamma2","1-alpha^2-beta^2-2*alpha*beta*[0]",0,1500,-1,1);

  gamma2->SetParameter(0,costheta_lpi);

  float gamma2_true=gamma2->Eval(P_taul,costheta_taultauh);
  
  cout<<"P_taul="<<P_taul<<endl;
  cout<<"t_minus="<<t_m<<endl;
  cout<<"t_plus="<<t_p<<endl;
  cout<<"gamma2="<<gamma2_true<<endl;
  cout<<"costheta_lpi="<<costheta_lpi<<endl;
  cout<<"costheta_taultauh="<<costheta_taultauh<<endl;
 

  TGraph* t_minus_gr=new TGraph();
  t_minus_gr->SetPoint(0,t_m,-1);
  t_minus_gr->SetPoint(1,t_m,1);
  t_minus_gr->SetLineColor(2);
  t_minus_gr->SetLineWidth(2);

  TGraph* t_plus_gr=new TGraph();
  t_plus_gr->SetPoint(0,t_m,-1);
  t_plus_gr->SetPoint(1,t_m,1);
  t_plus_gr->SetLineColor(2);
  t_plus_gr->SetLineWidth(2);

  vector<float> lim=integration_lim(gamma2,costheta_lpi,t_m,t_p);
  gamma2->SetRange(0.75*lim[0],lim[2]-0.001,1.75*lim[1],lim[3]+0.005);
  cout<<"costheta_taultauh min="<<lim[2]<<endl;
  cout<<"costheta_taultauh max="<<lim[3]<<endl;

  TGraph* true_P_taul=new TGraph();
  true_P_taul->SetPoint(0,P_taul,-1);
  true_P_taul->SetPoint(1,P_taul,1);
  true_P_taul->SetLineStyle(9);
  true_P_taul->SetFillColor(0);

  TGraph* true_costheta_taultauh=new TGraph();
  true_costheta_taultauh->SetPoint(0,0,costheta_taultauh);
  true_costheta_taultauh->SetPoint(1,lim[1],costheta_taultauh);
  true_costheta_taultauh->SetLineStyle(9);

  TGraph* true_costheta_lpi=new TGraph();
  true_costheta_lpi->SetPoint(0,0,costheta_lpi);
  true_costheta_lpi->SetPoint(1,lim[1],costheta_lpi);
  true_costheta_lpi->SetLineStyle(3);
  true_costheta_lpi->SetLineWidth(2);
  true_costheta_lpi->SetFillColor(0);


  TGraph* P_taul_int_min=new TGraph();
  P_taul_int_min->SetPoint(0,max(t_m,lim[0]),lim[2]);
  P_taul_int_min->SetPoint(1,max(t_m,lim[0]),lim[3]);
  P_taul_int_min->SetLineColor(1);
  P_taul_int_min->SetLineWidth(2);
  P_taul_int_min->SetFillColor(0);

  TGraph* P_taul_int_max=new TGraph();
  P_taul_int_max->SetPoint(0,min(t_p,lim[1]),lim[2]);
  P_taul_int_max->SetPoint(1,min(t_p,lim[1]),lim[3]);
  P_taul_int_max->SetLineColor(1);
  P_taul_int_max->SetLineWidth(2);

  TGraph* costheta_tautau_int_min=new TGraph();
  costheta_tautau_int_min->SetPoint(0,max(t_m,lim[0]),lim[2]);
  costheta_tautau_int_min->SetPoint(1,min(t_p,lim[1]),lim[2]);
  costheta_tautau_int_min->SetLineColor(1);
  costheta_tautau_int_min->SetLineWidth(2);

  TGraph* costheta_tautau_int_max=new TGraph();
  costheta_tautau_int_max->SetPoint(0,max(t_m,lim[0]),lim[3]);
  costheta_tautau_int_max->SetPoint(1,min(t_p,lim[1]),lim[3]);
  costheta_tautau_int_max->SetLineColor(1);
  costheta_tautau_int_max->SetLineWidth(2);

  TLegend* leg=new TLegend(0.56,0.55,0.85,0.85);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillStyle(0);

  leg->AddEntry(true_P_taul,"#splitline{MC-truth values}{of |#tau_{l}| and cos#theta_{#tau#tau}}");
  leg->AddEntry(true_costheta_lpi,"#splitline{MC-truth values}{of cos#theta_{#mu#pi}}");
  leg->AddEntry(P_taul_int_min,"#splitline{Limits of the integration}{region}");



  TCanvas* c=new TCanvas("c","c",650,600);
  gamma2->SetTitle("#gamma^{2}=f(|#tau_{l}|,cos#theta_{#tau#tau}) in the collinear approximation");
  gamma2->GetXaxis()->SetTitle("|#tau_{l}| [GeV]");
  gamma2->GetYaxis()->SetTitle("cos#theta_{#tau#tau}");
  gamma2->GetYaxis()->SetTitleOffset(1.25);
  gamma2->SetMinimum(0);

  gamma2->Draw("colz");
  true_P_taul->Draw("sameL");
  true_costheta_taultauh->Draw("sameL");
  true_costheta_lpi->Draw("sameL");
  P_taul_int_min->Draw("sameL");
  P_taul_int_max->Draw("sameL");
  costheta_tautau_int_min->Draw("sameL");
  costheta_tautau_int_max->Draw("sameL");
  leg->Draw("same");

  if(save){
    TString filename=Form("gamma2_f_taul_costheta_taultauh_ievent%i",ientry);
    filename+="_"+sample;
    c->SaveAs("../pdf/"+filename+".pdf");
    c->SaveAs("../png/"+filename+".png");
  }

  return;

}

