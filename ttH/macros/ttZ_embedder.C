#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TString.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TRandom.h>


using namespace std;



double getFakeTauLepTFresolution(double pT_gen,int leptype) const {
  double cst[2];
  if(abs(leptype)==11){
    cst[0] = 4.69;
    cst[1] = 0.04;
  }
  else if(abs(leptype)==13){
    cst[0] = 4.46;
    cst[1] = 0.02;
  }
  double res = cst[0]+cst[1]*pT_gen;
  return res;
}


double getFakeTauLepTFmean(double pT_gen,int leptype) const {
  double cst[2];
  if(abs(leptype)==11){
    cst[0] = 0.84;
    cst[1] = 0.96;
  }
  else if(abs(leptype)==13){
    cst[0] = 1.17;
    cst[1] = 0.97;
  }
  double mean = cst[0]+cst[1]*pT_gen;
  return mean;
}

double getFakeTauLepTFn(double pT_gen,int leptype) const {
  double cst[2];
  if(abs(leptype)==11){
    cst[0] = 0.;
    cst[1] = 0.;
  }
  else if(abs(leptype)==13){
    cst[0] = 2.29;
    cst[1] = -0.0151;
  }
  double n = cst[0]+cst[1]*pT_gen;
  if(n<0.1) n=0.1;
  return n;
}

double getFakeTauLepTF( const TLorentzVector &lep4P, const TLorentzVector &evTau4P, int leptype) const {
  double pT_gen = lep4P.Pt();
  double pT_reco = evTau4P.Pt();
  double mu = getFakeTauLepTFmean(pT_gen,leptype);
  double sigma = getFakeTauLepTFresolution(pT_gen,leptype);
  double n = getFakeTauLepTFn(pT_gen,leptype);
  double TF = 1.;
  if(abs(leptype)==11){
    double I = 1/(TMath::Pi()*sigma);
    
    TF = I / (1 + pow((pT_reco-mu)/sigma , 2));
  }
  else if (abs(leptype)==13){
    double chi = (pT_reco-mu)/sigma;
    double alpha = 1.2;
    double A = pow(n/alpha,n) * exp(-alpha*alpha/2.);
    double B = n/alpha - alpha;
    //double C = n/alpha * 1./(n-1.) * exp(-alpha*alpha/2.);
    double C = exp(-alpha*alpha/2.)/(n-1.) *(pow(n/alpha,1-n)-pow(B+5.,1-n));
    double D = TMath::Sqrt(TMath::Pi()/2.) * (1 + TMath::Erf(alpha/TMath::Sqrt(2.)));
    double N = 1./(sigma*(C+D));
    if(abs(chi)>5)
      TF = 0;
    else if ( chi < alpha )
      TF = N * exp( - 0.5*chi*chi );
    else
      TF = N * A * pow(B + chi,-n);       
  }
  return TF;
}



void make_embedding(TString filein,
		    TString fileout,
		    TString treename){


  TChain * tree = new TChain(treename);
  tree->Add(filein);
  

  Long64_t nentries = tree->GetEntries();
  //nentries=100;

  cout<<"nentries="<<tree->GetEntries()<<endl;
  
  TFile* f_new = TFile::Open(dir_out+file);
  if(f_new!=0){
    cout<<dir_out+file<<" already exists, please delete it before converting again"<<endl;
    return;
  }

  
  f_new = TFile::Open(dir_out+file,"RECREATE");


  //Old branches used
  vector<int> *_recolep_sel_pdg;
  vector<int> *_recolep_sel_charge;  
  vector<float> *_recolep_sel_px;
  vector<float> *_recolep_sel_py;
  vector<float> *_recolep_sel_pz;
  vector<float> *_recolep_sel_e;
  float _PFMET;
  float _PFMET_phi;

  tree->SetBranchAddress("recolep_sel_pdg",&_recolep_sel_pdg);
  tree->SetBranchAddress("recolep_sel_charge",&_recolep_sel_charge);
  tree->SetBranchAddress("recolep_sel_px",&_recolep_sel_px);
  tree->SetBranchAddress("recolep_sel_py",&_recolep_sel_py);
  tree->SetBranchAddress("recolep_sel_pz",&_recolep_sel_pz);
  tree->SetBranchAddress("recolep_sel_e",&_recolep_sel_e);
  tree->SetBranchAddress("PFMET",&_PFMET);
  tree->SetBranchAddress("PFMET_phi",&_PFMET_phi);


  //New branches
  int _genZ_emb_decayMode;

  float _gentau1_emb_px;
  float _gentau1_emb_py;
  float _gentau1_emb_pz;
  float _gentau1_emb_e;
  float _gentau1_emb_pt;
  float _gentau1_emb_eta;
  float _gentau1_emb_phi;

  float _gentau2_emb_px;
  float _gentau2_emb_py;
  float _gentau2_emb_pz;
  float _gentau2_emb_e;
  float _gentau2_emb_pt;
  float _gentau2_emb_eta;
  float _gentau2_emb_phi;

  float _recolep_tau1_px;
  float _recolep_tau1_py;
  float _recolep_tau1_pz;
  float _recolep_tau1_e;
  float _recolep_tau1_pt;
  float _recolep_tau1_eta;
  float _recolep_tau1_phi;

  float _recotauh_tau2_px;
  float _recotauh_tau2_py;
  float _recotauh_tau2_pz;
  float _recotauh_tau2_e;
  float _recotauh_tau2_pt;
  float _recotauh_tau2_eta;
  float _recotauh_tau2_phi;

  vector<int> _recolep_sel_emb_pdg;
  vector<int> _recolep_sel_emb_charge;
  vector<float> _recolep_sel_emb_px;
  vector<float> _recolep_sel_emb_py;
  vector<float> _recolep_sel_emb_pz;
  vector<float> _recolep_sel_emb_e;
  vector<float> _recolep_sel_emb_pt;
  vector<float> _recolep_sel_emb_eta;
  vector<float> _recolep_sel_emb_phi;
  
  vector<int> _recotauh_sel_emb_pdg;
  vector<int> _recotauh_sel_emb_charge;
  vector<float> _recotauh_sel_emb_px;
  vector<float> _recotauh_sel_emb_py;
  vector<float> _recotauh_sel_emb_pz;
  vector<float> _recotauh_sel_emb_e;
  vector<float> _recotauh_sel_emb_pt;
  vector<float> _recotauh_sel_emb_eta;
  vector<float> _recotauh_sel_emb_phi;

  float _PFMET_emb;
  float _PFMET_emb_phi;
  
  tree_new->Branch("genZ_emb_decayMode",&_genZ_emb_decayMode);

  tree_new->Branch("gentau1_emb_px",&_gentau1_emb_px);
  tree_new->Branch("gentau1_emb_py",&_gentau1_emb_py);
  tree_new->Branch("gentau1_emb_pz",&_gentau1_emb_pz);
  tree_new->Branch("gentau1_emb_e",&_gentau1_emb_e);
  tree_new->Branch("gentau1_emb_pt",&_gentau1_emb_pt);
  tree_new->Branch("gentau1_emb_eta",&_gentau1_emb_eta);
  tree_new->Branch("gentau1_emb_phi",&_gentau1_emb_phi);

  tree_new->Branch("gentau2_emb_px",&_gentau2_emb_px);
  tree_new->Branch("gentau2_emb_py",&_gentau2_emb_py);
  tree_new->Branch("gentau2_emb_pz",&_gentau2_emb_pz);
  tree_new->Branch("gentau2_emb_e",&_gentau2_emb_e);
  tree_new->Branch("gentau2_emb_pt",&_gentau2_emb_pt);
  tree_new->Branch("gentau2_emb_eta",&_gentau2_emb_eta);
  tree_new->Branch("gentau12_emb_phi",&_gentau2_emb_phi);

  tree_new->Branch("recolep_tau1_px",&_recolep_tau1_px);
  tree_new->Branch("recolep_tau1_py",&_recolep_tau1_py);
  tree_new->Branch("recolep_tau1_pz",&_recolep_tau1_pz);
  tree_new->Branch("recolep_tau1_e",&_recolep_tau1_e);
  tree_new->Branch("recolep_tau1_pt",&_recolep_tau1_pt);
  tree_new->Branch("recolep_tau1_eta",&_recolep_tau1_eta);
  tree_new->Branch("recolep_tau1_phi",&_recolep_tau1_phi);
  
  tree_new->Branch("recotauh_tau2_px",&_recotauh_tau1_px);
  tree_new->Branch("recotauh_tau2_py",&_recotauh_tau1_py);
  tree_new->Branch("recotauh_tau2_pz",&_recotauh_tau1_pz);
  tree_new->Branch("recotauh_tau2_e",&_recotauh_tau2_e);
  tree_new->Branch("recotauh_tau2_pt",&_recotauh_tau2_pt);
  tree_new->Branch("recotauh_tau2_eta",&_recotauh_tau2_eta);
  tree_new->Branch("recotauh_tau2_phi",&_recotauh_tau2_phi);


  tree_new->Branch("recolep_sel_emb_pdg",&_recolep_sel_emb_pdg);
  tree_new->Branch("recolep_sel_emb_charge",&_recolep_sel_emb_charge);
  tree_new->Branch("recolep_sel_emb_px",&_recolep_sel_emb_px);
  tree_new->Branch("recolep_sel_emb_py",&_recolep_sel_emb_py);
  tree_new->Branch("recolep_sel_emb_pz",&_recolep_sel_emb_pz);
  tree_new->Branch("recolep_sel_emb_e",&_recolep_sel_emb_e);
  tree_new->Branch("recolep_sel_emb_pt",&_recolep_sel_emb_pt);
  tree_new->Branch("recolep_sel_emb_eta",&_recolep_sel_emb_eta);
  tree_new->Branch("recolep_sel_emb_phi",&_recolep_sel_emb_phi);

  tree_new->Branch("recotauh_sel_emb_pdg",&_recotauh_sel_emb_pdg);
  tree_new->Branch("recotauh_sel_emb_charge",&_recotauh_sel_emb_charge);
  tree_new->Branch("recotauh_sel_emb_px",&_recotauh_sel_emb_px);
  tree_new->Branch("recotauh_sel_emb_py",&_recotauh_sel_emb_py);
  tree_new->Branch("recotauh_sel_emb_pz",&_recotauh_sel_emb_pz);
  tree_new->Branch("recotauh_sel_emb_e",&_recotauh_sel_emb_e);
  tree_new->Branch("recotauh_sel_emb_pt",&_recotauh_sel_emb_pt);
  tree_new->Branch("recotauh_sel_emb_eta",&_recotauh_sel_emb_eta);
  tree_new->Branch("recotauh_sel_emb_phi",&_recotauh_sel_emb_phi);

  tree_new->Branch("PFMET_emb",&_PFMET_emb);
  tree_new->Branch("PFMET_emb_phi",&_PFMET_emb_phi);


  TF1* TauLepTF = new TF1("TauLepTF","(1-x)*(5 + 5*x - 4*x*x)",0,1);

  TF1* TauHadTF = new TF1("TauLepTF","x>[0]",0,1);
  double mTau = 1.777; double mPi = 0.140;
  TauHadTF->SetParameter(0,pow(mPi/mTau,2));

  TRandom* rng=new TRandom();

  for (int i=0;i<nentries;i++) {

    if(i%10000==0)
      cout<<"i="<<i<<endl;

    _recolep_sel_pdg = 0;
    _recolep_sel_charge = 0;  
    _recolep_sel_px = 0;
    _recolep_sel_py = 0;
    _recolep_sel_pz = 0;
    _recolep_sel_e = 0;
    _PFMET = 0;
    _PFMET_phi = 0;

    _genZ_emb_decayMode = 0;

    _gentau1_emb_px = 0;
    _gentau1_emb_py = 0;
    _gentau1_emb_pz = 0;
    _gentau1_emb_e = 0;
    _gentau1_emb_pt = 0;
    _gentau1_emb_eta = 0;
    _gentau1_emb_phi = 0;
    
    _gentau2_emb_px = 0;
    _gentau2_emb_py = 0;
    _gentau2_emb_pz = 0;
    _gentau2_emb_e = 0;
    _gentau2_emb_pt = 0;
    _gentau2_emb_eta = 0;
    _gentau2_emb_phi = 0;
   
    _recolep_tau1_px = 0;
    _recolep_tau1_py = 0;
    _recolep_tau1_pz = 0;
    _recolep_tau1_e = 0;
    _recolep_tau1_pt = 0;
    _recolep_tau1_eta = 0;
    _recolep_tau1_phi = 0;
    
    _recotauh_tau2_px = 0;
    _recotauh_tau2_py = 0;
    _recotauh_tau2_pz = 0;
    _recotauh_tau2_e = 0;
    _recotauh_tau2_pt = 0;
    _recotauh_tau2_eta = 0;
    _recotauh_tau2_phi = 0;
  

    _recolep_sel_emb_pdg.clear();
    _recolep_sel_emb_charge.clear();
    _recolep_sel_emb_px.clear();
    _recolep_sel_emb_py.clear();
    _recolep_sel_emb_pz.clear();
    _recolep_sel_emb_e.clear();
    _recolep_sel_emb_pt.clear();
    _recolep_sel_emb_eta.clear();
    _recolep_sel_emb_phi.clear();
  
    _recotauh_sel_emb_pdg.clear();
    _recotauh_sel_emb_charge.clear();
    _recotauh_sel_emb_px.clear();
    _recotauh_sel_emb_py.clear();
    _recotauh_sel_emb_pz.clear();
    _recotauh_sel_emb_e.clear();
    _recotauh_sel_emb_pt.clear();
    _recotauh_sel_emb_eta.clear();
    _recotauh_sel_emb_phi.clear();

    _PFMET_emb = 0;
    _PFMET_emb_phi = 0;

    int entry_ok = tree->GetEntry(i);

    vector<TLorentzVector> recolep_sel;
    for(unsigned int i_lep=0;i_lep<3;i_lep++)
      recolep_sel.push_back(TLorentzVector((*_recolep_sel_px)[i_lep],(*_recolep_sel_py)[i_lep],(*_recolep_sel_pz)[i_lep],(*_recolep_sel_e)[i_lep]));



    TLorentzVector lep_Z1;
    TLorentzVector lep_Z2;
    TLorentzVector lep_top;

    
    int sum_charge = (*_recolep_sel_charge)[0]+(*_recolep_sel_charge)[1]+(*_recolep_sel_charge)[2];
    int i_lep_Z1 = -1;
    int i_lep_Z2 = -1;
    int i_lep_top = -1;

    for(unsigned int i_lep=0;i_lep<3;i_lep++){
      if((*_recolep_sel_charge)[i_lep]==-sum_charge){
	lep_Z2 = recolep_sel[i_lep];
	i_lep_Z2 = i_lep;
      }
    }

    float best_mZ = -10.;

    for(unsigned int i_lep=0;i_lep<3;i_lep++){
      if(i_lep==i_lep_Z2) continue;
      
      float mZ = (recolep_sel[i_lep]+lep_Z2).M();
      if(best_mZ<0 || abs(mZ-91.2)<abs(best_mZ-91.2)){
	best_mZ = mZ;
	i_lep_Z1 = i_lep;
	lep_Z1 = recolep_sel[i_lep];
      }

    }

    for(unsigned int i_lep=0;i_lep<3;i_lep++){
     if(i_lep==i_lep_Z1 || i_lep==i_lep_Z2) continue;
     i_lep_top = i_lep;
     lep_top = recolep_sel[i_lep];
    }
     

    double x_DM = rng->Uniform();
    if(x_DM<0.45) _genZ_emb_decayMode = 5;
    else{
      if(abs((*_recolep_sel_pdg)[i_lep_Z1])==11) _genZ_emb_decayMode = 6;
      else _genZ_emb_decayMode = 7;
    }


    TLorentzVector gentau1 = lep_Z1;
    TLorentzVector gentau2 = lep_Z2;
    TLorentzVector lep_tau1 = lep_Z1;
    TLorentzVector tauh_tau2 = lep_Z2;
    TLorentzVector PFMET_emb_tv3;
    PFMET_emb_tv3.SetPtEtaPhi(_PFMET,0,_PFMET_phi);

    
    if(_genZ_emb_decayMode==5){
      
      double z_lep = TauLepTF->GetRandom();
      double E_lep = gentau1.E()*z_lep;
      double pT_lep = sqrt(E_lep*E_lep-lep_Z1.M2())/TMath::CosH(lep_Z1.Eta());
      lep_tau1.SetPtEtaPhiM(pT_lep,lep_Z1.Eta(),lep_Z1.Phi(),lep_Z1.M());

      TVector3 nu_tau1_perp;
      nu_tau1_perp.SetPtEtaPhi((gentau1-lep_tau1).Pt(),0,(gentau1-lep_tau1).Phi());

      double z_tauh = TauHadTF->GetRandom();
      double E_tauh = gentau2.E()*z_tauh;
      double pT_tauh = sqrt(E_tauh*E_tauh-lep_Z2.M2())/TMath::CosH(lep_Z2.Eta());
      tauh_tau2.SetPtEtaPhiM(pT_tauh,lep_Z2.Eta(),lep_Z2.Phi(),mPi);     

      TVector3 nu_tau2_perp;
      nu_tau2_perp.SetPtEtaPhi((gentau2-tauh_tau2).Pt(),0,(gentau2-tauh_tau2).Phi());
      PFMET_emb_tv3 = PFMET_emb_tv3 + nu_tau1_perp + nu_tau2_perp


    }


    else if(_genZ_emb_decayMode==6){

      int leptype = 11;
      double pT_gen = gentau1.pT();
      double mu = getFakeTauLepTFmean(pT_gen,leptype);
      double sigma = getFakeTauLepTFresolution(pT_gen,leptype);
      double xmin = max(0,mu-5*sigma);
      double xmax = mu+5*sigma;

      double I = 1/(TMath::Pi()*sigma);      
      TF1* TFEleFakeTau = new TF1("TFEleFakeTau","[0]/(1+((x-[1])/[2])**2)",xmin,xmax);
      TFEleFakeTau->SetParameter(0,I);
      TFEleFakeTau->SetParameter(1,mu);
      TFEleFakeTau->SetParameter(2,sigma);
      double pT_reco = TFEleFakeTau->GetRandom();
      tauh_tau2.SetPtEtaPhiM(pT_reco,lep_Z2.Eta(),lep_Z2.Phi(),mPi);

    }


    else if(_genZ_emb_decayMode==7){

      int leptype = 13;
      double pT_gen = gentau1.pT();
      double mu = getFakeTauLepTFmean(pT_gen,leptype);
      double sigma = getFakeTauLepTFresolution(pT_gen,leptype);
      double n = getFakeTauLepTFn(pT_gen,leptype);
      double alpha = 1.2;
      double xmin = max(0,mu-5*sigma);
      double xmax = mu+5*sigma;

      TF1* TFMuFakeTau = new TF1("TFMuFakeTau","ROOT::Math::crystalball_function(x, [0], [1], [2], [3])",xmin,xmax);
      TFEleFakeTau->SetParameter(0,alpha);
      TFEleFakeTau->SetParameter(1,n);
      TFEleFakeTau->SetParameter(2,sigma);
      TFEleFakeTau->SetParameter(3,mu);
      double pT_reco = TFMuFakeTau->GetRandom();
      tauh_tau2.SetPtEtaPhiM(pT_reco,lep_Z2.Eta(),lep_Z2.Phi(),mPi);

    }
    
    _gentau1_emb_px = gentau1.Px();
    _gentau1_emb_py = gentau1.Py();
    _gentau1_emb_pz = gentau1.Pz();
    _gentau1_emb_e = gentau1.E();
    _gentau1_emb_pt = gentau1.Pt();
    _gentau1_emb_eta = gentau1.Eta();
    _gentau1_emb_phi = gentau1.Phi();

    _gentau2_emb_px = gentau2.Px();
    _gentau2_emb_py = gentau2.Py();
    _gentau2_emb_pz = gentau2.Pz();
    _gentau2_emb_e = gentau2.E();
    _gentau2_emb_pt = gentau2.Pt();
    _gentau2_emb_eta = gentau2.Eta();
    _gentau2_emb_phi = gentau2.Phi();

    _recolep_tau1_px = lep_tau2.Px();
    _recolep_tau1_py = lep_tau2.Py();
    _recolep_tau1_pz = lep_tau2.Pz();
    _recolep_tau1_e = lep_tau2.E();
    _recolep_tau1_pt = lep_tau2.Pt();
    _recolep_tau1_eta = lep_tau2.Eta();
    _recolep_tau1_phi = lep_tau2.Phi();

    _recotauh_tau2_px = tauh_tau2.Px();
    _recotauh_tau2_py = tauh_tau2.Py();
    _recotauh_tau2_pz = tauh_tau2.Pz();
    _recotauh_tau2_e = tauh_tau2.E();
    _recotauh_tau2_pt = tauh_tau2.Pt();
    _recotauh_tau2_eta = tauh_tau2.Eta();
    _recotauh_tau2_phi = tauh_tau2.Phi();
 
    _PFMET_emb = PFMET_emb_tv3.Pt();
    _PFMET_emb_phi = PFMET_emb_tv3.Phi();

    
    if(lep_top.Pt()>lep_tau1.Pt()){
      _recolep_sel_emb_pdg.push_back((*_recolep_sel_pdg)[i_lep_top]);
      _recolep_sel_emb_charge.push_back((*_recolep_sel_charge)[i_lep_top]);
      _recolep_sel_emb_px.push_back(lep_top.Px());
      _recolep_sel_emb_py.push_back(lep_top.Py());
      _recolep_sel_emb_pz.push_back(lep_top.Pz());
      _recolep_sel_emb_e.push_back(lep_top.E());
      _recolep_sel_emb_pt.push_back(lep_top.Pt());
      _recolep_sel_emb_eta.push_back(lep_top.Eta());
      _recolep_sel_emb_phi.push_back(lep_top.Phi());

      _recolep_sel_emb_pdg.push_back((*_recolep_sel_pdg)[i_lep_Z1]);
      _recolep_sel_emb_charge.push_back((*_recolep_sel_charge)[i_lep_Z1]);
      _recolep_sel_emb_px.push_back(lep_tau1.Px());
      _recolep_sel_emb_py.push_back(lep_tau1.Py());
      _recolep_sel_emb_pz.push_back(lep_tau1.Pz());
      _recolep_sel_emb_e.push_back(lep_tau1.E());
      _recolep_sel_emb_pt.push_back(lep_tau1.Pt());
      _recolep_sel_emb_eta.push_back(lep_tau1.Eta());
      _recolep_sel_emb_phi.push_back(lep_tau1.Phi());
    }

    else{

      _recolep_sel_emb_pdg.push_back((*_recolep_sel_pdg)[i_lep_Z1]);
      _recolep_sel_emb_charge.push_back((*_recolep_sel_charge)[i_lep_Z1]);
      _recolep_sel_emb_px.push_back(lep_tau1.Px());
      _recolep_sel_emb_py.push_back(lep_tau1.Py());
      _recolep_sel_emb_pz.push_back(lep_tau1.Pz());
      _recolep_sel_emb_e.push_back(lep_tau1.E());
      _recolep_sel_emb_pt.push_back(lep_tau1.Pt());
      _recolep_sel_emb_eta.push_back(lep_tau1.Eta());
      _recolep_sel_emb_phi.push_back(lep_tau1.Phi());

      _recolep_sel_emb_pdg.push_back((*_recolep_sel_pdg)[i_lep_top]);
      _recolep_sel_emb_charge.push_back((*_recolep_sel_charge)[i_lep_top]);
      _recolep_sel_emb_px.push_back(lep_top.Px());
      _recolep_sel_emb_py.push_back(lep_top.Py());
      _recolep_sel_emb_pz.push_back(lep_top.Pz());
      _recolep_sel_emb_e.push_back(lep_top.E());
      _recolep_sel_emb_pt.push_back(lep_top.Pt());
      _recolep_sel_emb_eta.push_back(lep_top.Eta());
      _recolep_sel_emb_phi.push_back(lep_top.Phi());

    }

    _recotauh_sel_emb_pdg.push_back((*_recolep_sel_charge)[i_lep_Z2]*(-15));
    _recotauh_sel_emb_charge.push_back((*_recolep_sel_charge)[i_lep_Z2]);
    _recotauh_sel_emb_px.push_back(tauh_tau2.Px());
    _recotauh_sel_emb_py.push_back(tauh_tau2.Py());
    _recotauh_sel_emb_pz.push_back(tauh_tau2.Pz());
    _recotauh_sel_emb_e.push_back(tauh_tau2.E());
    _recotauh_sel_emb_pt.push_back(tauh_tau2.Pt());
    _recotauh_sel_emb_eta.push_back(tauh_tau2.Eta());
    _recotauh_sel_emb_phi.push_back(tauh_tau2.Phi());
    

  }



}
