#include <RooFitResult.h>
#include <TH2F.h>
#include <TFile.h>
#include <TCanvas.h>



void plot_correlation(TString filename, TString plotname){

    TFile* f = TFile::Open(filename);

    RooFitResult* fit_s = (RooFitResult*)f->Get("fit_s");

    vector<TString> sample_MC;
    sample_MC.push_back("TTZ");
    sample_MC.push_back("TTW");
    sample_MC.push_back("EWK");
    sample_MC.push_back("Rares");

    vector<TString> type;
    type.push_back("gentau");
    type.push_back("faketau");

    vector<TString> sample;
    for(unsigned int i=0;i<sample_MC.size();i++){
      for(unsigned int j=0; j<type.size();j++){
	sample.push_back(sample_MC[i]+"_"+type[j]);
      }
    }

    sample.push_back("fakes_data");
    sample.push_back("flips_data");


    vector<TString> syst;
    syst.push_back("CMS_ttHl_tauES");
    syst.push_back("CMS_ttHl_JES");
    for(int i=0;i<sample.size();i++){
      for(unsigned int j=1;j<11;j++){
	
	if(sample[i]=="EWK_faketau" && (j!=1 || j!=5)) continue;
	if(sample[i].Contains("TTW") && j==1) continue;
	syst.push_back("CMS_ttH_2lss_1tau_missing_"+sample[i]+Form("_bin_%i",j));
      }
    }

    /*syst.push_back("CMS_ttHl_Clos_e_norm");
    syst.push_back("CMS_ttHl_Clos_e_shape");
    syst.push_back("CMS_ttHl_Clos_m_norm");
    syst.push_back("CMS_ttHl_Clos_m_shape");
    syst.push_back("CMS_ttHl_EWK_4j");
    syst.push_back("CMS_ttHl_FRe_b");
    syst.push_back("CMS_ttHl_FRe_ec");
    syst.push_back("CMS_ttHl_FRe_norm");
    syst.push_back("CMS_ttHl_FRe_pt");
    syst.push_back("CMS_ttHl_FRjt_norm");
    syst.push_back("CMS_ttHl_FRjt_shape");
    syst.push_back("CMS_ttHl_FRm_b");
    syst.push_back("CMS_ttHl_FRm_ec");
    syst.push_back("CMS_ttHl_FRm_norm");
    syst.push_back("CMS_ttHl_FRm_pt");
    syst.push_back("CMS_ttHl_QF");
    syst.push_back("CMS_ttHl_Rares");
    syst.push_back("CMS_ttHl_btag_HF");
    syst.push_back("CMS_ttHl_btag_HFStats1");
    syst.push_back("CMS_ttHl_btag_HFStats2");
    syst.push_back("CMS_ttHl_btag_LF");
    syst.push_back("CMS_ttHl_btag_LFStats1");
    syst.push_back("CMS_ttHl_btag_LFStats2");
    syst.push_back("CMS_ttHl_btag_cErr1");
    syst.push_back("CMS_ttHl_btag_cErr2");
    syst.push_back("CMS_ttHl_lepEff_elloose");
    syst.push_back("CMS_ttHl_lepEff_muloose");
    syst.push_back("CMS_ttHl_lepEff_tight");
    syst.push_back("CMS_ttHl_tauID");
    syst.push_back("CMS_ttHl_thu_shape_ttH_x1");
    syst.push_back("CMS_ttHl_thu_shape_ttH_y1");
    syst.push_back("CMS_ttHl_thu_shape_ttW_x1");
    syst.push_back("CMS_ttHl_thu_shape_ttW_y1");
    syst.push_back("CMS_ttHl_thu_shape_ttZ_x1");
    syst.push_back("CMS_ttHl_thu_shape_ttZ_y1");
    syst.push_back("CMS_ttHl_trigger_uncorr");
    syst.push_back("QCDscale_ttH");
    syst.push_back("QCDscale_ttW");
    syst.push_back("QCDscale_ttZ");
    syst.push_back("lumi_13TeV_2016");
    syst.push_back("pdf_Higgs");
    syst.push_back("pdf_gg");
    syst.push_back("pdf_qqbar");*/


    TH2F* covariance=new TH2F("","",syst.size(),0,syst.size(),syst.size(),0,syst.size());
    //TH2F* covariance=new TH2F("","",syst.size(),0,syst.size(),2,0,2);

    covariance->SetMinimum(-1);
    covariance->SetMaximum(1);

    for(unsigned int i=0;i<syst.size();i++){
      cout<<i<<" "<<syst[i]<<endl;

      for(unsigned int j=0;j<syst.size();j++){
	//for(unsigned int j=0;j<2;j++){
		
	//if(i==j) continue;
	if(fit_s->correlation(syst[i],syst[j])>3.438354e-02)
	  cout<<"larger "<<syst[i]<<" "<<syst[j]<<" "<<fit_s->correlation(syst[i],syst[j]);

	//cout<<fit_s->correlation(syst[i],syst[j])<<endl;
	covariance->Fill(i,j,fit_s->correlation(syst[i],syst[j]));

      }
    }



    TCanvas* c=new TCanvas("c","c",650,600);
    c->SetLeftMargin(0.15);
    c->SetRightMargin(0.15);

    gPad->SetTicks();

    covariance->SetStats(0);
    covariance->Draw("colz");
      




}






void test(){

  TString filename="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/toys_fits/mlfit.root";
  //TString filename="/home/llr/cms/strebler/CMSSW_7_4_7_Combine_dev/CMSSW_7_4_7/src/CombineHarvester/ttH_htt/toys_fits/mlfittoys_10k.root";
  TString plotname="correlation_syst_2lss1tau_missing";

  plot_correlation(filename,plotname);


}
