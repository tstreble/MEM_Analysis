#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <TString.h>
#include <algorithm>
#include <map>
#include <sstream>
#include <TF1.h>


#ifndef Helpers_RecoVegas_C
#define Helpers_RecoVegas_C





double GetAlpha(double CosThetaTauLepPi, double CosThetaTauHadPi, double CosThetaTauTau){
    double alpha = 0.;

    double SinThetaTauLepPi=TMath::Sqrt(1-CosThetaTauLepPi*CosThetaTauLepPi);
    alpha = (CosThetaTauTau - CosThetaTauLepPi*CosThetaTauHadPi)/(SinThetaTauLepPi*SinThetaTauLepPi);
    
    return alpha;
}


double GetBeta(double CosThetaTauLepPi, double CosThetaTauHadPi, double CosThetaTauTau){
    double beta = 0.;
    double SinThetaTauLepPi=TMath::Sqrt(1-CosThetaTauLepPi*CosThetaTauLepPi);
    beta = (CosThetaTauHadPi - CosThetaTauLepPi*CosThetaTauTau)/(SinThetaTauLepPi*SinThetaTauLepPi);
    
    return beta;
}


/*double GetGamma2(double alpha, double beta, double CosThetaTauLepPi){
    double gamma2 = (1- (alpha*alpha) - (beta*beta) - 2*alpha*beta*CosThetaTauLepPi );
    return gamma2;
    }*/



double GetCosThetaTauHadPi( double P_Tau_Had, TLorentzVector HadSys4P, double m_Tau){
    
  double E_Tau=TMath::Sqrt(m_Tau*m_Tau+P_Tau_Had*P_Tau_Had);
  double E_Pi=HadSys4P.E();
  double m_Pi=HadSys4P.M();
  double P_Pi=HadSys4P.P();
    
  double CosThetaTauHadPi = (2*E_Tau*E_Pi - (m_Tau*m_Tau + m_Pi*m_Pi))/(2*P_Tau_Had*P_Pi);
    
  return CosThetaTauHadPi;
}


double GetPTauHad( double tau_lep_P, double costheta_tautau, double mtautau2, double m_tau){

  double E_tau_lep=TMath::Sqrt(m_tau*m_tau+tau_lep_P*tau_lep_P);
  double sin2theta_tautau=1-costheta_tautau*costheta_tautau;
  double M2=0.5*mtautau2-m_tau*m_tau;

  double u_plus=TMath::Sqrt( mtautau2/sin2theta_tautau * (mtautau2/(4*m_tau*m_tau) - 1) );

  double P_Tau_Had=0;

  if(tau_lep_P<u_plus)
    P_Tau_Had=(M2*tau_lep_P*costheta_tautau + E_tau_lep*TMath::Sqrt(M2*M2-m_tau*m_tau*(m_tau*m_tau+tau_lep_P*tau_lep_P*sin2theta_tautau))) / (m_tau*m_tau + tau_lep_P*tau_lep_P*sin2theta_tautau);  

  return P_Tau_Had;

}


double GetGamma2(TLorentzVector HadSys4P, TLorentzVector Lep4P, double tau_lep_P, double CosThetaTauTau, double mtautau2, double m_tau){

  TVector3 HadSys3P=HadSys4P.Vect();
  TVector3 e_had=HadSys3P.Unit();
  TVector3 Lep3P=Lep4P.Vect();
  TVector3 e_lep=Lep3P.Unit();

  double CosThetaTauLepPi=e_lep*e_had;

  double tau_had_P=GetPTauHad( tau_lep_P, CosThetaTauTau, mtautau2, m_tau);
  double CosThetaTauHadPi=GetCosThetaTauHadPi( tau_had_P, HadSys4P, m_tau);

  double alpha = GetAlpha(CosThetaTauLepPi, CosThetaTauHadPi, CosThetaTauTau);
  double beta = GetBeta(CosThetaTauLepPi, CosThetaTauHadPi, CosThetaTauTau);
  double gamma2 = (1- (alpha*alpha) - (beta*beta) - 2*alpha*beta*CosThetaTauLepPi );
  return gamma2;
}


double getJacobian( double P_TauLep, double P_TauHad, double gamma, double cosThetaTauLepPi, double cosThetaTauTau)  {

  double m_tau=1.777;

  double Jacobian	=	0.;
  
  double SinThetaTauLepPi    =   TMath::Sqrt(1. - (cosThetaTauLepPi*cosThetaTauLepPi));

  double E_TauLep=TMath::Sqrt(m_tau*m_tau+P_TauLep*P_TauLep);
  double E_TauHad=TMath::Sqrt(m_tau*m_tau+P_TauHad*P_TauHad);



  Jacobian         =   1. / fabs(E_TauLep * P_TauHad/E_TauHad - P_TauLep * cosThetaTauTau) * 1./fabs(gamma*SinThetaTauLepPi);
 

  return Jacobian;
}



double t_plus( TLorentzVector HadSys4P ){
    double E_Pi     =   0.;
    double P_Pi     =   0.;
    double m_Tau    =   1.777;
    double m_Tau_2  =   0.;
    double m_Pi_2   =   0.;
    double tPlus    =   0.;
    
    E_Pi	= HadSys4P.E();
    P_Pi	= HadSys4P.P();
    
    m_Pi_2  = ((E_Pi*E_Pi)-(P_Pi*P_Pi));
    
    //May have m_Pi_2<0 for some electrons
    if(m_Pi_2<0)
      m_Pi_2=0.000511*0.000511;

    m_Tau_2 = m_Tau*m_Tau;
    
    tPlus = (((m_Tau_2+m_Pi_2)*P_Pi + E_Pi*(m_Tau_2-m_Pi_2))/(2*m_Pi_2));
    
    return tPlus;
}
//-------------------------------------------------------------------------------

//----------------------------------- t_minus ------------------------------------
double t_minus( TLorentzVector HadSys4P ){
    double E_Pi     =   0.;
    double P_Pi     =   0.;
    double m_Tau    =   1.777;
    double m_Tau_2  =   0.;
    double m_Pi_2   =   0.;
    double tMinus   =   0.;
    
    E_Pi	= HadSys4P.E();
    P_Pi	= HadSys4P.P();
    
    m_Pi_2 = ((E_Pi*E_Pi)-(P_Pi*P_Pi));
    //May have m_Pi_2<0 for some electrons
    if(m_Pi_2<0)
      m_Pi_2=0.000511*0.000511;

    m_Tau_2 = (m_Tau*m_Tau);
    
    tMinus = (((m_Tau_2+m_Pi_2)*P_Pi - E_Pi*(m_Tau_2-m_Pi_2))/(2*m_Pi_2));
    
    return tMinus;
}





map<TString,TLorentzVector> LV_RecoVegas(map<TString,TLorentzVector> LV_MC,double mtautau2, double tau_lep_P, double CosThetaTauTau, double q1_E, double q2_E){

  TLorentzVector jet1_MC=LV_MC["jet1"];
  TLorentzVector jet2_MC=LV_MC["jet2"];
  TLorentzVector lep_MC=LV_MC["lep"];
  TLorentzVector pi_MC=LV_MC["pi"];

  TLorentzVector out_q1_reco;
  double pt_q1=q1_E/TMath::CosH(jet1_MC.Eta());
  out_q1_reco.SetPtEtaPhiE(pt_q1,jet1_MC.Eta(),jet1_MC.Phi(),q1_E);
  TLorentzVector out_q2_reco;
  double pt_q2=q2_E/TMath::CosH(jet2_MC.Eta());
  out_q2_reco.SetPtEtaPhiE(pt_q2,jet2_MC.Eta(),jet2_MC.Phi(),q2_E);

  double m_tau=1.777;

  double s_m=t_minus(pi_MC);
  double s_p=t_plus(pi_MC);
  double t_m=t_minus(lep_MC);
  double t_p=t_plus(lep_MC);


  TVector3 lep_3P=lep_MC.Vect();
  TVector3 el=lep_3P.Unit();
  TVector3 tau_lep_3P=tau_lep_P*el;
  double E_tau_lep=TMath::Sqrt(m_tau*m_tau+tau_lep_P*tau_lep_P);
  TLorentzVector tau_lep_reco(tau_lep_3P,E_tau_lep);

  TVector3 pi_3P=pi_MC.Vect();
  TVector3 epi=pi_3P.Unit();
  TVector3 etau=tau_lep_3P.Unit();
  TVector3 eyy=etau.Cross(epi);
  eyy=eyy.Unit();

  double tau_had_P=GetPTauHad(tau_lep_P, CosThetaTauTau, mtautau2, m_tau);

  double CosThetaTauLepPi = etau*epi;
  double CosThetaTauHadPi = GetCosThetaTauHadPi(tau_had_P, pi_MC,m_tau);
  double alpha = GetAlpha(CosThetaTauLepPi, CosThetaTauHadPi, CosThetaTauTau);
  double beta = GetBeta(CosThetaTauLepPi, CosThetaTauHadPi, CosThetaTauTau);
  //double gamma2 = GetGamma2(alpha, beta, CosThetaTauLepPi);
  double gamma2=GetGamma2(pi_MC, lep_MC, tau_lep_P, CosThetaTauTau, mtautau2, m_tau);

  double gamma=0;
  if(gamma2>0)
    gamma=TMath::Sqrt(gamma2);


  TVector3 tau_had_3P=tau_had_P*( alpha*etau + beta*epi + gamma*eyy );
  
  TVector3 etau_had=tau_had_3P.Unit();

  //cout<<"etau_had*eyy="<<etau_had*eyy<<endl;
  double E_tau_had=TMath::Sqrt(m_tau*m_tau+tau_had_P*tau_had_P);
  TLorentzVector tau_had_reco(tau_had_3P,E_tau_had);



  if(gamma2<0 || tau_had_P==0 || !(t_m<=tau_lep_P && tau_lep_P<=t_p) ||  !(s_m<=tau_had_P && tau_had_P<=s_p) )
    tau_had_reco.SetPxPyPzE(0,0,0,0);


  map<TString,TLorentzVector> LV_reco;
  LV_reco["out_q1_reco"]=out_q1_reco;
  LV_reco["out_q2_reco"]=out_q2_reco;
  LV_reco["tau_lep_reco"]=tau_lep_reco;
  LV_reco["tau_had_reco"]=tau_had_reco;

  return LV_reco;


}




double getJetTFBarrel( const TLorentzVector &quark4P, const TLorentzVector &jet4P)  {
  TF1 res("res", "([0]+[1]*TMath::Sqrt(x))+[2]*x");
  res.FixParameter(0,3.548);
  res.FixParameter(1,0.202);
  res.FixParameter(2,0.04874);

  double sigmaV = ( res.Eval(quark4P.E() ) ); 

  TF1 TFgaus("TFgaus", "gaus",0,4000);
  TFgaus.FixParameter(0, 1/(sigmaV*TMath::Sqrt(2*TMath::Pi()) ) );
  TFgaus.FixParameter(1, quark4P.E());
  TFgaus.FixParameter(2, sigmaV);

  return TFgaus.Eval( jet4P.E());  
}

  
double getJetTFEndcap( const TLorentzVector &quark4P,  const TLorentzVector &jet4P)  {
  TF1 res("res", "([0]+[1]*TMath::Sqrt(x))+[2]*x");

  res.FixParameter(0,3.196);
  res.FixParameter(1,1.51);
  res.FixParameter(2,0.07918);
  double sigmaV = ( res.Eval(quark4P.E() ) ); 

  TF1 TFgaus("TFgaus", "gaus",0,4000);
  TFgaus.FixParameter(0, 1/(sigmaV*TMath::Sqrt(2*TMath::Pi()) ) );
  TFgaus.FixParameter(1, quark4P.E());
  TFgaus.FixParameter(2, sigmaV);

  return TFgaus.Eval( jet4P.E());  
}    


#endif
