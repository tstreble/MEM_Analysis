#include <TLorentzVector.h>



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





double getEqbar_Enu(double CosTheta_qq, double Eq){

  double MW = 80.385;
  double Eqbar= MW*MW / (2*Eq*(1-CosTheta_qq));
  return Eqbar;

}


double getEb(TLorentzVector W, TLorentzVector bjet){

  double Mt = 173.21;
  double MW = 80.385;
  double mb = 4.7;

  double deltaM2=0.5*(Mt*Mt-MW*MW-mb*mb);
  double EW=W.E();
  TVector3 eb=(bjet.Vect()).Unit();
  double Web=W.Vect()*eb;

  double Eb_plus= ( EW*deltaM2 + fabs(Web)*TMath::Sqrt(deltaM2*deltaM2 - mb*mb*(EW*EW - Web*Web)) ) / (EW*EW - Web*Web);
  double Eb_minus= ( EW*deltaM2 - fabs(Web)*TMath::Sqrt(deltaM2*deltaM2 - mb*mb*(EW*EW - Web*Web)) ) / (EW*EW - Web*Web);

  if(Web>0){
    if(Eb_plus > deltaM2/EW)
      return Eb_plus;
    else if(Eb_minus > deltaM2/EW)
      return Eb_minus;
  }
  
  else{
    if(Eb_plus < deltaM2/EW)
      return Eb_plus;
    else if(Eb_minus < deltaM2/EW)
      return Eb_minus;
  }

  return 0;

}




double getAlpha(double CosThetaTauLepPi, double CosThetaTauHadPi, double CosThetaTauTau){
    double alpha = 0.;

    double SinThetaTauLepPi=TMath::Sqrt(1-CosThetaTauLepPi*CosThetaTauLepPi);
    alpha = (CosThetaTauTau - CosThetaTauLepPi*CosThetaTauHadPi)/(SinThetaTauLepPi*SinThetaTauLepPi);
    
    return alpha;
}


double getBeta(double CosThetaTauLepPi, double CosThetaTauHadPi, double CosThetaTauTau){
    double beta = 0.;
    double SinThetaTauLepPi=TMath::Sqrt(1-CosThetaTauLepPi*CosThetaTauLepPi);
    beta = (CosThetaTauHadPi - CosThetaTauLepPi*CosThetaTauTau)/(SinThetaTauLepPi*SinThetaTauLepPi);
    
    return beta;
}




double getCosThetaTauHadPi( double P_Tau_Had, TLorentzVector HadSys4P, double m_Tau){
    
  double E_Tau=TMath::Sqrt(m_Tau*m_Tau+P_Tau_Had*P_Tau_Had);
  double E_Pi=HadSys4P.E();
  double m_Pi=HadSys4P.M();
  double P_Pi=HadSys4P.P();
    
  double CosThetaTauHadPi = (2*E_Tau*E_Pi - (m_Tau*m_Tau + m_Pi*m_Pi))/(2*P_Tau_Had*P_Pi);
    
  return CosThetaTauHadPi;
}




double getPTauHad( double tau_lep_P, double costheta_tautau, double mtautau2, double m_tau){

  double E_tau_lep=TMath::Sqrt(m_tau*m_tau+tau_lep_P*tau_lep_P);
  double sin2theta_tautau=1-costheta_tautau*costheta_tautau;
  double M2=0.5*mtautau2-m_tau*m_tau;

  double u_plus=TMath::Sqrt( mtautau2/sin2theta_tautau * (mtautau2/(4*m_tau*m_tau) - 1) );

  double P_Tau_Had=0;

  if(tau_lep_P<u_plus)
    P_Tau_Had=(M2*tau_lep_P*costheta_tautau + E_tau_lep*TMath::Sqrt(M2*M2-m_tau*m_tau*(m_tau*m_tau+tau_lep_P*tau_lep_P*sin2theta_tautau))) / (m_tau*m_tau + tau_lep_P*tau_lep_P*sin2theta_tautau);  

  return P_Tau_Had;

}


double getGamma2(TLorentzVector HadSys4P, TLorentzVector Lep4P, double tau_lep_P, double CosThetaTauTau, double mtautau2, double m_tau){

  TVector3 HadSys3P=HadSys4P.Vect();
  TVector3 e_had=HadSys3P.Unit();
  TVector3 Lep3P=Lep4P.Vect();
  TVector3 e_lep=Lep3P.Unit();

  double CosThetaTauLepPi=e_lep*e_had;

  double tau_had_P=getPTauHad( tau_lep_P, CosThetaTauTau, mtautau2, m_tau);
  double CosThetaTauHadPi=getCosThetaTauHadPi( tau_had_P, HadSys4P, m_tau);

  double alpha = getAlpha(CosThetaTauLepPi, CosThetaTauHadPi, CosThetaTauTau);
  double beta = getBeta(CosThetaTauLepPi, CosThetaTauHadPi, CosThetaTauTau);
  double gamma2 = (1- (alpha*alpha) - (beta*beta) - 2*alpha*beta*CosThetaTauLepPi );
  return gamma2;
}



TLorentzVector Vegas_blep_4P(TLorentzVector lep_4P, TLorentzVector bjet_4P,
			      double phiNu, double cosThetaNu){

  TLorentzVector b_lep_reco_4P;
  TLorentzVector W_lep_4P;
  TLorentzVector nu_top_4P;
  double mb = 4.7;

  TVector3 enu;
  enu.SetMagThetaPhi(1,TMath::ACos(cosThetaNu),phiNu);
  double CosThetalnu_top=TMath::Cos(lep_4P.Angle(enu));
  double Enu=getEqbar_Enu(CosThetalnu_top,lep_4P.E());
  TLorentzVector nu_top_4P_dummy(Enu*enu,Enu);
  nu_top_4P=nu_top_4P_dummy;
  W_lep_4P=nu_top_4P+lep_4P;
    
  double Eb_lep=getEb(W_lep_4P, bjet_4P);
  double b_lep_Pmag=TMath::Sqrt(Eb_lep*Eb_lep - mb*mb);
  double pT_bl=b_lep_Pmag/TMath::CosH(bjet_4P.Eta());
  if(Eb_lep>0){
    b_lep_reco_4P.SetPtEtaPhiE(pT_bl,bjet_4P.Eta(),bjet_4P.Phi(),Eb_lep);
  }

  return b_lep_reco_4P;

}






TLorentzVector Vegas_nult_4P(TLorentzVector lep_4P,
			     double phiNu, double cosThetaNu){


  TVector3 enu;
  enu.SetMagThetaPhi(1,TMath::ACos(cosThetaNu),phiNu);
  double CosThetalnu_top=TMath::Cos(lep_4P.Angle(enu));
  double Enu=getEqbar_Enu(CosThetalnu_top,lep_4P.E());
  TLorentzVector nu_top_4P(Enu*enu,Enu);

  return nu_top_4P;

}








map<TString,TLorentzVector> LV_RecoVegas(map<TString,TLorentzVector> LV_MC,double mtautau2, double tau_lep_P, double CosThetaTauTau, double Eq1, double CosThetanu, double Phinu, int gamma_sign=1){

  TLorentzVector ltau_MC=LV_MC["ltau"];
  TLorentzVector pi_MC=LV_MC["pi"];

  TLorentzVector b_lep_MC=LV_MC["b_lep"];
  TLorentzVector lt_MC=LV_MC["lt"];

  TLorentzVector b_had_MC=LV_MC["b_had"];
  TLorentzVector jet1_MC=LV_MC["q1"];
  TLorentzVector jet2_MC=LV_MC["q2"];

  ///Leptonic top
  double m_b=4.7;

  TVector3 enu;
  enu.SetMagThetaPhi(1,TMath::ACos(CosThetanu),Phinu);
  double CosThetalnu_top=TMath::Cos(lt_MC.Angle(enu));
  double Enu=getEqbar_Enu(CosThetalnu_top,lt_MC.E());
  TLorentzVector nu_top(Enu*enu,Enu);
  TLorentzVector W_lep=nu_top+lt_MC;

  double Eb_lep=getEb(W_lep, b_lep_MC);
  double b_lep_Pmag=TMath::Sqrt(Eb_lep*Eb_lep - m_b*m_b);
  double pT_bl=b_lep_Pmag/TMath::CosH(b_lep_MC.Eta());
  TLorentzVector b_lep_reco(0.,0.,0.,0.);
  TLorentzVector t_lep(0.,0.,0.,0.);
  if(Eb_lep>0){
    b_lep_reco.SetPtEtaPhiE(pT_bl,b_lep_MC.Eta(),b_lep_MC.Phi(),Eb_lep);
    t_lep=W_lep+b_lep_reco;
  }

  //Hadronic top
  TLorentzVector q1_reco;
  double pt_q1=Eq1/TMath::CosH(jet1_MC.Eta());
  q1_reco.SetPtEtaPhiE(pt_q1,jet1_MC.Eta(),jet1_MC.Phi(),Eq1);

  TLorentzVector q2_reco;
  double CosTheta_qq=TMath::Cos(jet1_MC.Angle(jet2_MC.Vect()));
  double Eq2=getEqbar_Enu(CosTheta_qq,Eq1);
  double pt_q2=Eq2/TMath::CosH(jet2_MC.Eta());
  q2_reco.SetPtEtaPhiE(pt_q2,jet2_MC.Eta(),jet2_MC.Phi(),Eq2);

  TLorentzVector W_had=q1_reco+q2_reco;
  double Eb_had=getEb(W_had, b_had_MC);
  double b_had_Pmag=TMath::Sqrt(Eb_had*Eb_had - m_b*m_b);
  double pT_bh=b_had_Pmag/TMath::CosH(b_had_MC.Eta());
  TLorentzVector b_had_reco(0.,0.,0.,0.);
  TLorentzVector t_had(0.,0.,0.,0.);
  if(Eb_had>0){
    b_had_reco.SetPtEtaPhiE(pT_bh,b_had_MC.Eta(),b_had_MC.Phi(),Eb_had);
    t_had=W_had+b_had_reco;
  }


  //Higgs / Z
  double m_tau=1.777;

  double s_m=t_minus(pi_MC);
  double s_p=t_plus(pi_MC);
  double t_m=t_minus(ltau_MC);
  double t_p=t_plus(ltau_MC);

  TVector3 ltau_3P=ltau_MC.Vect();
  TVector3 el=ltau_3P.Unit();
  TVector3 tau_lep_3P=tau_lep_P*el;
  double E_tau_lep=TMath::Sqrt(m_tau*m_tau+tau_lep_P*tau_lep_P);
  TLorentzVector tau_lep_reco(tau_lep_3P,E_tau_lep);

  TVector3 pi_3P=pi_MC.Vect();
  TVector3 epi=pi_3P.Unit();
  TVector3 etau=tau_lep_3P.Unit();
  TVector3 eyy=etau.Cross(epi);
  eyy=eyy.Unit();

  double tau_had_P=getPTauHad(tau_lep_P, CosThetaTauTau, mtautau2, m_tau);

  double CosThetaTauLepPi = etau*epi;
  double CosThetaTauHadPi = getCosThetaTauHadPi(tau_had_P, pi_MC,m_tau);

  double alpha = getAlpha(CosThetaTauLepPi, CosThetaTauHadPi, CosThetaTauTau);
  double beta = getBeta(CosThetaTauLepPi, CosThetaTauHadPi, CosThetaTauTau);
//double gamma2 = getGamma2(alpha, beta, CosThetaTauLepPi);
  double gamma2=getGamma2(pi_MC, ltau_MC, tau_lep_P, CosThetaTauTau, mtautau2, m_tau);  

  double gamma=0;
  if(gamma2>0)
    gamma=gamma_sign*TMath::Sqrt(gamma2);

  TVector3 tau_had_3P=tau_had_P*( alpha*etau + beta*epi + gamma*eyy );  
  TVector3 etau_had=tau_had_3P.Unit();
  double E_tau_had=TMath::Sqrt(m_tau*m_tau+tau_had_P*tau_had_P);
  TLorentzVector tau_had_reco(tau_had_3P,E_tau_had);

  //cout<<"s_m="<<s_m<<", tau_had_P="<<tau_had_P<<", s_p="<<s_p<<endl;
  //cout<<"t_m="<<t_m<<", tau_lep_P="<<tau_lep_P<<", t_p="<<t_p<<endl;

  if(gamma2<0 || tau_had_P==0 || !(t_m<=tau_lep_P && tau_lep_P<=t_p) ||  !(s_m<=tau_had_P && tau_had_P<=s_p) )
    tau_had_reco.SetPxPyPzE(0,0,0,0);

  map<TString,TLorentzVector> LV_reco;
  LV_reco["nu_top_reco"]=nu_top;
  LV_reco["W_lep_reco"]=W_lep;
  LV_reco["b_lep_reco"]=b_lep_reco;
  LV_reco["t_lep_reco"]=t_lep;

  LV_reco["q1_reco"]=q1_reco;
  LV_reco["q2_reco"]=q2_reco;
  LV_reco["W_had_reco"]=W_had;
  LV_reco["b_had_reco"]=b_had_reco;
  LV_reco["t_had_reco"]=t_had;

  LV_reco["tau_lep_reco"]=tau_lep_reco;
  LV_reco["tau_had_reco"]=tau_had_reco;
  LV_reco["higgs_reco"]=tau_lep_reco+tau_had_reco;

  return LV_reco;


}

