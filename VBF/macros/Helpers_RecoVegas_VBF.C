#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <TString.h>
#include <algorithm>
#include <map>
#include <sstream>

#include "compute_ME.C"
#include "Helpers_RecoVegas.C"


double compute_ME_VBF_RecoVegas(int version, //1 full, 2 v2, 3 v3
				cteqpdf ct10nn,
				CPPProcess_uu_to_uuH process_uu_to_uuH,
				CPPProcess_ud_to_udH process_ud_to_udH,
				CPPProcess_uc_to_ucH process_uc_to_ucH,
				CPPProcess_us_to_usH process_us_to_usH,
				CPPProcess_us_to_dcH process_us_to_dcH,
				CPPProcess_uubar_to_uubarH process_uubar_to_uubarH,
				CPPProcess_uubar_to_ddbarH process_uubar_to_ddbarH,
				CPPProcess_udbar_to_udbarH process_udbar_to_udbarH,
				CPPProcess_ucbar_to_ucbarH process_ucbar_to_ucbarH,
				CPPProcess_ucbar_to_dsbarH process_ucbar_to_dsbarH,
				CPPProcess_usbar_to_usbarH process_usbar_to_usbarH,
				CPPProcess_dd_to_ddH process_dd_to_ddH,
				CPPProcess_ds_to_dsH process_ds_to_dsH,
				CPPProcess_ddbar_to_ddbarH process_ddbar_to_ddbarH,
				CPPProcess_ddbar_to_uubarH process_ddbar_to_uubarH,
				CPPProcess_dsbar_to_dsbarH process_dsbar_to_dsbarH,
				CPPProcess_dsbar_to_ucbarH process_dsbar_to_ucbarH,
				map<TString,TLorentzVector> LV_MC,
				double mtautau2,
				double tau_lep_P,
				double costheta_tautau,
				double q1_E,
				double q2_E){

  /////////Reconstruction of the 4P from the integration variables////////

  map<TString,TLorentzVector> LV_reco=LV_RecoVegas(LV_MC, 
						   mtautau2,
						   tau_lep_P,
						   costheta_tautau,
						   q1_E,
						   q2_E);
  TLorentzVector tau_lep_reco=LV_reco["tau_lep_reco"];
  
  
  TLorentzVector tau_had_reco=LV_reco["tau_had_reco"];
  TLorentzVector out_q1_reco=LV_reco["out_q1_reco"];
  TLorentzVector out_q2_reco=LV_reco["out_q2_reco"];
  TLorentzVector tot4P=tau_lep_reco + tau_had_reco + out_q1_reco + out_q2_reco;

  if(tau_had_reco.E()==0)
    return 0;

  /////////Boost////////
  
  TVector3 boost3D = tot4P.BoostVector();
  boost3D.SetZ(0);
  
  tot4P.Boost(-boost3D );
  tau_lep_reco.Boost(-boost3D );
  tau_had_reco.Boost(-boost3D );
  out_q1_reco.Boost(-boost3D );
  out_q2_reco.Boost(-boost3D );
        
  /////////Incoming quarks////////
  
  double Sqrt_S = 8000.; // Energy expressed in GeV
  //double Sqrt_S = 13000.; // Energy expressed in GeV
  double x_a;
  double x_b;
  TLorentzVector in_q1_reco;
  TLorentzVector in_q2_reco;
  
  x_a = ((tot4P.E() + tot4P.Pz())/(Sqrt_S));
  x_b = ((tot4P.E() - tot4P.Pz())/(Sqrt_S));

  //cout<<"x_a="<<x_a<<endl;
  //cout<<"x_b="<<x_b<<endl;
  
  in_q1_reco.SetPxPyPzE(0., 0., +0.5*x_a*Sqrt_S, 0.5*x_a*Sqrt_S);
  in_q2_reco.SetPxPyPzE(0., 0., -0.5*x_b*Sqrt_S, 0.5*x_b*Sqrt_S);


  /////////Matrix element////////
  
  vector<double*> p;
  
  /* p[0] incoming quark0
     p[1] incoming quark1
     p[2] outgoing quark0
     p[3] outgoing quark1
     p[4] outgoing tau-
     p[5] outgoing tau+*/
  
  p.push_back(new double[4]);
  p[0][0] = 	in_q1_reco.E();
  p[0][1] = 	in_q1_reco.Px();
  p[0][2] = 	in_q1_reco.Py();
  p[0][3] = 	in_q1_reco.Pz();
  
  p.push_back(new double[4]);
  p[1][0] = 	in_q2_reco.E();
  p[1][1] = 	in_q2_reco.Px();
  p[1][2] = 	in_q2_reco.Py();
  p[1][3] = 	in_q2_reco.Pz();
		
  p.push_back(new double[4]);
  p[2][0] = 	out_q1_reco.E();
  p[2][1] = 	out_q1_reco.Px();
  p[2][2] = 	out_q1_reco.Py();
  p[2][3] = 	out_q1_reco.Pz();
			
  p.push_back(new double[4]);
  p[3][0] = 	out_q2_reco.E();
  p[3][1] = 	out_q2_reco.Px();
  p[3][2] = 	out_q2_reco.Py();
  p[3][3] = 	out_q2_reco.Pz();
		
  p.push_back(new double[4]);
  p[4][0] = 	tau_lep_reco.E();
  p[4][1] = 	tau_lep_reco.Px();
  p[4][2] = 	tau_lep_reco.Py();
  p[4][3] = 	tau_lep_reco.Pz();

  p.push_back(new double[4]);
  p[5][0] = 	tau_had_reco.E();
  p[5][1] = 	tau_had_reco.Px();
  p[5][2] = 	tau_had_reco.Py();
  p[5][3] = 	tau_had_reco.Pz();

  double wME2_reco = 0;
  
  if(version==1){

    wME2_reco = compute_ultimate_ME_VBF( ct10nn,
					 process_uu_to_uuH,
					 process_ud_to_udH,
					 process_uc_to_ucH,
					 process_us_to_usH,
					 process_us_to_dcH,
					 process_uubar_to_uubarH,
					 process_uubar_to_ddbarH,
					 process_udbar_to_udbarH,
					 process_ucbar_to_ucbarH,
					 process_ucbar_to_dsbarH,
					 process_usbar_to_usbarH,
					 process_dd_to_ddH,
					 process_ds_to_dsH,
					 process_ddbar_to_ddbarH,
					 process_ddbar_to_uubarH,
					 process_dsbar_to_dsbarH,
					 process_dsbar_to_ucbarH,
					 p,
					 Sqrt_S/2);

  }

  else if(version==2){
    
    wME2_reco = compute_ME_VBF_v2( ct10nn,
				   process_uu_to_uuH,
				   process_ud_to_udH,
				   process_us_to_dcH,
				   p);
  }

  else if(version==3){
    
    wME2_reco = compute_ME_VBF_v3( ct10nn,
				   process_ud_to_udH,
				   p);
  }



  return wME2_reco;

}



map<TString, double> Full_ME_VBF_TF_Vegas(int version, //1 full, 2 v2, 3 v3
					  cteqpdf ct10nn,
					  CPPProcess_uu_to_uuH process_uu_to_uuH,
					  CPPProcess_ud_to_udH process_ud_to_udH,
					  CPPProcess_uc_to_ucH process_uc_to_ucH,
					  CPPProcess_us_to_usH process_us_to_usH,
					  CPPProcess_us_to_dcH process_us_to_dcH,
					  CPPProcess_uubar_to_uubarH process_uubar_to_uubarH,
					  CPPProcess_uubar_to_ddbarH process_uubar_to_ddbarH,
					  CPPProcess_udbar_to_udbarH process_udbar_to_udbarH,
					  CPPProcess_ucbar_to_ucbarH process_ucbar_to_ucbarH,
					  CPPProcess_ucbar_to_dsbarH process_ucbar_to_dsbarH,
					  CPPProcess_usbar_to_usbarH process_usbar_to_usbarH,
					  CPPProcess_dd_to_ddH process_dd_to_ddH,
					  CPPProcess_ds_to_dsH process_ds_to_dsH,
					  CPPProcess_ddbar_to_ddbarH process_ddbar_to_ddbarH,
					  CPPProcess_ddbar_to_uubarH process_ddbar_to_uubarH,
					  CPPProcess_dsbar_to_dsbarH process_dsbar_to_dsbarH,
					  CPPProcess_dsbar_to_ucbarH process_dsbar_to_ucbarH,
					  map<TString,TLorentzVector> LV_MC,
					  vector<vector<double> > MET_cov_matrix,
					  double mtautau2,
					  double tau_lep_P,
					  double costheta_tautau,
					  double q1_E,
					  double q2_E){


  map<TString, double> output;
  output["TF_jet1"]=0;
  output["TF_jet2"]=0;
  output["TF_bjet_lep"]=0;
  output["TF_bjet_had"]=0;
  output["TF_MET"]=0;
  output["TF_tau_lep"]=0;
  output["TF_tau_lep_jac"]=0;
  output["TF_tau_had"]=0;
  output["TF_tau_had_jac"]=0;
  output["Jacobian_tautau"]=0;
  output["Jacobian_top_had"]=0;
  output["Jacobian_top_lep"]=0;
  output["Jacobian"]=0;
  output["ME"]=0;
  output["Integrand"]=0;

  TLorentzVector jet1=LV_MC["jet1"];
  TLorentzVector jet2=LV_MC["jet2"];
  TLorentzVector lep=LV_MC["lep"];
  TLorentzVector pi=LV_MC["pi"];
  TLorentzVector MET=LV_MC["MET"];


  /////////Reconstruction of the 4P from the integration variables////////

  map<TString,TLorentzVector> LV_reco=LV_RecoVegas(LV_MC, 
						   mtautau2,
						   tau_lep_P,
						   costheta_tautau,
						   q1_E,
						   q2_E);
  
  TLorentzVector tau_lep_reco=LV_reco["tau_lep_reco"];
  TLorentzVector tau_had_reco=LV_reco["tau_had_reco"];
  TLorentzVector out_q1_reco=LV_reco["out_q1_reco"];
  TLorentzVector out_q2_reco=LV_reco["out_q2_reco"];

  if(tau_had_reco.E()==0)
    return output;


  double costheta_tautau_reco=TMath::Cos(tau_lep_reco.Angle(tau_had_reco.Vect()));


  TLorentzVector tot4P(0.,0.,0.,0.);
  TLorentzVector rho4P(0.,0.,0.,0.);
  tot4P=tau_lep_reco+tau_had_reco+out_q1_reco+out_q2_reco;
  rho4P=MET+pi+lep+jet1+jet2;


  /////////Jet TF////////

  double TF_jet1 = 1.0;
  double TF_jet2 = 1.0;

  if( fabs(out_q1_reco.Eta())<1.5 )
    TF_jet1=getJetTFBarrel( out_q1_reco, jet1);
  else
    TF_jet1=getJetTFEndcap( out_q1_reco, jet1);

  if( fabs(out_q2_reco.Eta())<1.5 )
    TF_jet2=getJetTFBarrel( out_q2_reco, jet2);
  else
    TF_jet2=getJetTFEndcap( out_q2_reco, jet2);

  output["TF_jet1"]=TF_jet1;
  output["TF_jet2"]=TF_jet2;

  /*cout<<""<<endl;
  cout<<"TF_jet1="<<TF_jet1<<endl;
  cout<<"TF_jet2="<<TF_jet2<<endl;*/


  /////////MET TF////////
 
  TVector3 RhoT;
  RhoT.SetXYZ((rho4P).Px(), (rho4P).Py(), 0);
  //cout<<"RhoT.Mag()="<<RhoT.Mag()<<endl;

  TVector3 PT;
  PT.SetXYZ((tot4P).Px(), (tot4P).Py(), 0);
  //cout<<"PT.Mag()="<<PT.Mag()<<endl;
 

  TVector3 Rec = RhoT-PT;
  //cout<<"Rec.Mag()="<<Rec.Mag()<<endl;

  double V00=MET_cov_matrix[0][0];
  double V01=MET_cov_matrix[0][1];
  double V10=MET_cov_matrix[1][0];
  double V11=MET_cov_matrix[1][1];

  double arg_TF_MET=Rec.X()*(V00*Rec.X() + V10*Rec.Y()) + Rec.Y()*(V01*Rec.X() + V11* Rec.Y());
  double detV=1./(V00*V11-V01*V10);

  double TF_MET=1/(2*TMath::Pi()*TMath::Sqrt(detV))*exp(-0.5*arg_TF_MET);

  output["TF_MET"]=TF_MET;

  //cout<<"TF_MET="<<TF_MET<<endl;

  /////////Tau lep TF////////

  double tau_lep_P_reco=tau_lep_reco.P();
  double tau_lep_E_reco=tau_lep_reco.E();
  double z=lep.E()/tau_lep_reco.E();

  ////True TF
  double TF_tau_lep=  (1-z) * (5 + 5*z - 4*z*z ) / (3*tau_lep_E_reco);
  output["TF_tau_lep"]=TF_tau_lep;

  ////TF * jacobian from tau
  double TF_tau_lep_jac = TF_tau_lep * (tau_lep_P_reco*tau_lep_P_reco) / (tau_lep_E_reco);

  output["TF_tau_lep_jac"]=TF_tau_lep_jac;


  //cout<<"TF_tau_lep="<<TF_tau_lep<<endl;
  //cout<<"TF_tau_lep_jac="<<TF_tau_lep_jac<<endl;

  

  /////////Tau had TF////////

  double tau_had_P_reco=tau_had_reco.P();
  double tau_had_E_reco=tau_had_reco.E();

  ////True TF
  double TF_tau_had= 1 / tau_had_E_reco;
  output["TF_tau_had"]=TF_tau_had;

  ////TF * jacobian from tau
  double TF_tau_had_jac = TF_tau_had * (tau_had_P_reco*tau_had_P_reco) / (tau_had_E_reco);
  output["TF_tau_had_jac"]=TF_tau_had_jac;

  //cout<<"TF_tau_had="<<TF_tau_had<<endl;
  //cout<<"TF_tau_had_jac="<<TF_tau_had_jac<<endl;


  /////////Jacobian////////

  double cosThetaTauLepPi=TMath::Cos(tau_lep_reco.Angle(pi.Vect()));
  TVector3 epi=(pi.Vect()).Unit();
  TVector3 etau_lep=(tau_lep_reco.Vect()).Unit();
  TVector3 etau_had=(tau_had_reco.Vect()).Unit();  
  TVector3 eyy=etau_lep.Cross(epi);
  eyy=eyy.Unit();
  double gamma=etau_had*eyy;
  //cout<<"gamma="<<gamma<<endl;

  double J=getJacobian( tau_lep_P_reco, tau_had_P_reco, gamma, cosThetaTauLepPi, costheta_tautau_reco);

  output["Jacobian"]=J;

  //cout<<"Jacobian="<<J<<endl;

  /////////Boost////////

  TVector3 boost3D = tot4P.BoostVector();
  boost3D.SetZ(0);
  
  tot4P.Boost(-boost3D );
  tau_lep_reco.Boost(-boost3D );
  tau_had_reco.Boost(-boost3D );
  out_q1_reco.Boost(-boost3D );
  out_q2_reco.Boost(-boost3D );

  //cout<<"boost3D.Mag()="<<boost3D.Mag()<<endl;

  /////////Incoming quarks////////

  double Sqrt_S = 8000.; // Energy expressed in GeV
  double x_a;
  double x_b;
  TLorentzVector in_q1_reco;
  TLorentzVector in_q2_reco;

  x_a = ((tot4P.E() + tot4P.Pz())/(Sqrt_S));
  x_b = ((tot4P.E() - tot4P.Pz())/(Sqrt_S));

  if(x_a<0 || x_a>1 || x_b<0 || x_b>1)
    return output;

  //cout<<"x_a="<<x_a<<endl;
  //cout<<"x_b="<<x_b<<endl;

  in_q1_reco.SetPxPyPzE(0., 0., +0.5*x_a*Sqrt_S, 0.5*x_a*Sqrt_S);
  in_q2_reco.SetPxPyPzE(0., 0., -0.5*x_b*Sqrt_S, 0.5*x_b*Sqrt_S);


  /////////Matrix element////////
  
  vector<double*> p;
        
  /* p[0] incoming quark0
     p[1] incoming quark1
     p[2] outgoing quark0
     p[3] outgoing quark1
     p[4] outgoing tau-
     p[5] outgoing tau+*/
  
  p.push_back(new double[4]);
  p[0][0] = 	in_q1_reco.E();
  p[0][1] = 	in_q1_reco.Px();
  p[0][2] = 	in_q1_reco.Py();
  p[0][3] = 	in_q1_reco.Pz();
		
  p.push_back(new double[4]);
  p[1][0] = 	in_q2_reco.E();
  p[1][1] = 	in_q2_reco.Px();
  p[1][2] = 	in_q2_reco.Py();
  p[1][3] = 	in_q2_reco.Pz();

  p.push_back(new double[4]);
  p[2][0] = 	out_q1_reco.E();
  p[2][1] = 	out_q1_reco.Px();
  p[2][2] = 	out_q1_reco.Py();
  p[2][3] = 	out_q1_reco.Pz();

  p.push_back(new double[4]);
  p[3][0] = 	out_q2_reco.E();
  p[3][1] = 	out_q2_reco.Px();
  p[3][2] = 	out_q2_reco.Py();
  p[3][3] = 	out_q2_reco.Pz();
		
  p.push_back(new double[4]);
  p[4][0] = 	tau_lep_reco.E();
  p[4][1] = 	tau_lep_reco.Px();
  p[4][2] = 	tau_lep_reco.Py();
  p[4][3] = 	tau_lep_reco.Pz();

  p.push_back(new double[4]);
  p[5][0] = 	tau_had_reco.E();
  p[5][1] = 	tau_had_reco.Px();
  p[5][2] = 	tau_had_reco.Py();
  p[5][3] = 	tau_had_reco.Pz();

  double wME2_reco = 0;
  
  if(version==1){

    wME2_reco = compute_ultimate_ME_VBF( ct10nn,
					 process_uu_to_uuH,
					 process_ud_to_udH,
					 process_uc_to_ucH,
					 process_us_to_usH,
					 process_us_to_dcH,
					 process_uubar_to_uubarH,
					 process_uubar_to_ddbarH,
					 process_udbar_to_udbarH,
					 process_ucbar_to_ucbarH,
					 process_ucbar_to_dsbarH,
					 process_usbar_to_usbarH,
					 process_dd_to_ddH,
					 process_ds_to_dsH,
					 process_ddbar_to_ddbarH,
					 process_ddbar_to_uubarH,
					 process_dsbar_to_dsbarH,
					 process_dsbar_to_ucbarH,
					 p,
					 Sqrt_S/2);

  }

  else if(version==2){
    
    wME2_reco = compute_ME_VBF_v2( ct10nn,
				   process_uu_to_uuH,
				   process_ud_to_udH,
				   process_us_to_dcH,
				   p);
  }

  else if(version==3){
    
    wME2_reco = compute_ME_VBF_v3( ct10nn,
				   process_ud_to_udH,
				   p);
  }



  wME2_reco = wME2_reco/(x_a*x_b);

  output["ME"]=wME2_reco;


  /////////Integrand////////

  double I=wME2_reco*TF_jet1*out_q1_reco.E()*TF_jet2*out_q2_reco.E()*TF_tau_lep_jac*TF_tau_had_jac*TF_MET*J;

  //double mtautau2_reco=(tau_lep_reco+tau_had_reco).M2();

  output["Integrand"]=I;

  //cout<<"I="<<I<<endl;


  return output;

}

