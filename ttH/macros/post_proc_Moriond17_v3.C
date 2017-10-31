#include "add_bTag_CSVshape_SF.C"
#include "add_event_weight.C"
#include "add_BDT.C"
#include "trigger_filter_1l2tau_Xtrig.C"
#include "add_NBadMu.C"
#include "add_low_mass_veto.C"


void add_everything(TString file,bool isMC){

  vector<TString> treename;

  if(isMC){

    treename.push_back("HTauTauTree_1l_2tau");
    treename.push_back("HTauTauTree_1l_2tau_fake_CR");
    treename.push_back("HTauTauTree_2lSS");
    treename.push_back("HTauTauTree_2lSS_lepMVA_CR");
    //treename.push_back("HTauTauTree_2lOS_CR");
    treename.push_back("HTauTauTree_3l");
    treename.push_back("HTauTauTree_3l_ttZ_CR");
    treename.push_back("HTauTauTree_3l_lepMVA_CR");
    //treename.push_back("HTauTauTree_3l_ttZ_lepMVA_CR");

    if(file.Contains("ttbar_DL")) treename.push_back("HTauTauTree_2lOS_CR");

    add_1l2tau_BDT(file+".root",
                   file+"_BDT_1l2tau.root",
                   treename);

    add_bTag_CSVshape_SF(file+"_BDT_1l2tau.root",
                         file+"_BDT_1l2tau_btagSF_new.root",
                         treename);    

    add_trigger_filter_1l2tau_Xtrig(file+"_BDT_1l2tau_btagSF_new.root",
				    file+"_BDT_1l2tau_btagSF_trig_new.root",
				    treename,isMC);
    
    add_event_weight(file+"_BDT_1l2tau_btagSF_trig_new.root",
		     file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new.root",
		     treename,isMC);
    
    //treename.erase(treename.begin()+2);
    add_low_mass_veto(file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new.root",
		      file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto.root",
		      treename);
    
  }


  else{


    treename.push_back("HTauTauTree_1l_2tau");
    treename.push_back("HTauTauTree_1l_2tau_fake_CR");
    treename.push_back("HTauTauTree_2lSS");
    treename.push_back("HTauTauTree_2lSS_lepMVA_CR");
    treename.push_back("HTauTauTree_2lOS_CR");
    treename.push_back("HTauTauTree_3l");
    treename.push_back("HTauTauTree_3l_ttZ_CR");
    treename.push_back("HTauTauTree_3l_lepMVA_CR");
    treename.push_back("HTauTauTree_3l_ttZ_lepMVA_CR");
   
    add_1l2tau_BDT(file+".root",
                   file+"_BDT_1l2tau.root",
                   treename);
 
    add_trigger_filter_1l2tau_Xtrig(file+"_BDT_1l2tau.root",
				    file+"_BDT_1l2tau_trig_new.root",
				    treename,isMC);
    
    add_event_weight(file+"_BDT_1l2tau_trig_new.root",
		     file+"_BDT_1l2tau_trig_weight_new.root",
		     treename,isMC);

    treename.erase(treename.begin()+2);
    add_low_mass_veto(file+"_BDT_1l2tau_trig_weight_new.root",
		      file+"_BDT_1l2tau_trig_weight_new_massveto.root",
		      treename);

  }




}




void add_everything_MEM(TString file,TString file2,bool isMC){

  vector<TString> treename;
  treename.push_back("T");

 TString treename2="HTauTauTree_2lSS";
  if(file.Contains("2lOS_CR"))
    treename2="HTauTauTree_2lOS_CR";
  if(file.Contains("lepMVA_CR"))
    treename2="HTauTauTree_2lSS_lepMVA_CR";


  if(file.Contains("nominal") and !file.Contains("Data")){

    add_bTag_CSVshape_SF(file+".root",
			 file+"_btagSF_new.root",
			 treename);

    add_event_weight(file+"_btagSF_new.root",
		   file+"_btagSF_lepTauSF_new.root",
		   treename,isMC);

  }

  else if(!file.Contains("nominal")){

    add_bTag_CSVshape_SF_fromSecondaryFile(file+".root",
					   file+"_btagSF_new.root",
					   "T",
					   file2,
					   treename2);

    add_event_weight_fromSecondary(file+"_btagSF_new.root",
				   file+"_btagSF_lepTauSF_new.root",
				   "T",
				   file2,
				   treename2);
    
  }



  else if(file.Contains("Data")){

    add_NBadMu_fromSecondary(file+".root",
			     file+"_NBadMu.root",
			     "T",
			     file2,
			     treename2);
    
    add_event_weight(file+"_NBadMu.root",
		     file+"_NBadMu_weight_new.root",
		     treename,isMC);
    
  }


}




void test(){

  //TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/JECup/ttH/ttHJet_split_JECup_2lSS_MEM_1_160205";
  //TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/JECup/ttH/HTauTauTree_ttHJet_Hnonbb_split_JECup_trig_btagSF_lepTauSF_new.root";
  //add_everything_MEM(file,file2,true);

  //TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_1_160127";
  //add_everything_MEM(file,"",true);

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/syncNtuple_ttH_tautau_prod012017_split";
  TString file2 = "";
  add_everything(file,true);


}



void full_proc(){

  //TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split";
  //add_everything(file,true);

  /*TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_ttHJet_Hnonbb_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_ext_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttG_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_ZZ_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WWW_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WWZ_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WZZ_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_ZZZ_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_tZq_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_TTTT_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_WpWp_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_ext_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromT_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split";
  add_everything(file,true);*/

  vector<TString> syst;
  syst.push_back("JECup");
  syst.push_back("JECdown");
  //syst.push_back("TESup");
  //syst.push_back("TESdown");

  TString file="";

  for(unsigned int i=0;i<syst.size();i++){

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttH/HTauTauTree_ttHJet_Hnonbb_split_"+syst[i];
    add_everything(file,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttW_split_"+syst[i];
    add_everything(file,true);

   file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttW_ext_split_"+syst[i];
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttZ_split_"+syst[i];
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttG_split_"+syst[i];
    add_everything(file,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/EWK/HTauTauTree_WZ_split_"+syst[i];
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/EWK/HTauTauTree_ZZ_split_"+syst[i];
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_WWW_split_"+syst[i];
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_WWZ_split_"+syst[i];
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_WZZ_split_"+syst[i];
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_ZZZ_split_"+syst[i];
    add_everything(file,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_tZq_split_"+syst[i];
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_TTTT_split_"+syst[i];
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_WpWp_split_"+syst[i];
    add_everything(file,true);
      

    }


  vector<TString> dataset;
  dataset.push_back("DoubleEG_2016B");
  dataset.push_back("DoubleEG_2016C");
  dataset.push_back("DoubleEG_2016D");
  dataset.push_back("DoubleEG_2016E");
  dataset.push_back("DoubleEG_2016F");
  dataset.push_back("DoubleEG_2016G");
  dataset.push_back("DoubleEG_2016Hv2");
  dataset.push_back("DoubleEG_2016Hv3");
  dataset.push_back("DoubleMu_2016B");
  dataset.push_back("DoubleMu_2016C");
  dataset.push_back("DoubleMu_2016D");
  dataset.push_back("DoubleMu_2016E");
  dataset.push_back("DoubleMu_2016F");
  dataset.push_back("DoubleMu_2016G");
  dataset.push_back("DoubleMu_2016Hv2");
  dataset.push_back("DoubleMu_2016Hv3");
  dataset.push_back("MuonEG_2016B");
  dataset.push_back("MuonEG_2016C");
  dataset.push_back("MuonEG_2016D");
  dataset.push_back("MuonEG_2016E");
  dataset.push_back("MuonEG_2016F");
  dataset.push_back("MuonEG_2016G");
  dataset.push_back("MuonEG_2016Hv2");
  dataset.push_back("MuonEG_2016Hv3");
  dataset.push_back("SingleEle_2016B");
  dataset.push_back("SingleEle_2016C");
  dataset.push_back("SingleEle_2016D");
  dataset.push_back("SingleEle_2016E");
  dataset.push_back("SingleEle_2016F");
  dataset.push_back("SingleEle_2016G");
  dataset.push_back("SingleEle_2016Hv2");
  dataset.push_back("SingleEle_2016Hv3");
  dataset.push_back("SingleMu_2016B");
  dataset.push_back("SingleMu_2016C");
  dataset.push_back("SingleMu_2016D");
  dataset.push_back("SingleMu_2016E");
  dataset.push_back("SingleMu_2016F");
  dataset.push_back("SingleMu_2016G");
  dataset.push_back("SingleMu_2016Hv2");  
  dataset.push_back("SingleMu_2016Hv3");
  
  for(unsigned int i=0;i<dataset.size();i++){
    TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_"+dataset[i]+"_split";
    add_everything(file,false);
    }


}







void full_proc_MEM(){

  /*TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/ttHJet_split_2lSS_MEM";
  add_everything_MEM(file,"",true);

  vector<TString> type;
  type.push_back("2lSS");
  type.push_back("2lSS_lepMVA_CR");

  for(unsigned int i=0;i<type.size();i++){

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttG_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttW_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/WZ_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/ZZ_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/TTTT_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/tZq_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WWW_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WWZ_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WZZ_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/ZZZ_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WpWp_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);


    }*/

  //TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_DL_split_2lSS_lepMVA_CR_MEM";
  //add_everything_MEM(file,"",true);


    vector<TString> syst;
    syst.push_back("JECup");
    //syst.push_back("JECdown");
    //syst.push_back("TESup");
    //syst.push_back("TESdown");

    /*for(unsigned int i=0;i<syst.size();i++){

      TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/ttH/ttHJet_split_"+syst[i]+"_2lSS_MEM";
      TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttH/HTauTauTree_ttHJet_Hnonbb_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/ttV/ttG_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttG_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/ttV/ttZ_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttZ_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/ttV/ttW_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttW_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/EWK/WZ_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/EWK/HTauTauTree_WZ_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/EWK/ZZ_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/EWK/HTauTauTree_ZZ_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/tZq_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_tZq_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/TTTT_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_TTTT_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/WWW_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_WWW_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/WWZ_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_WWZ_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/WZZ_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_WZZ_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/ZZZ_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_ZZZ_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/WpWp_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_WpWp_split_"+syst[i]+"_trig_btagSF_lepTauSF_new_BDT_1l2tau.root";
      add_everything_MEM(file,file2,true);

      }*/

    vector<TString> dataset;
    dataset.push_back("DoubleEG_2016B");
    dataset.push_back("DoubleEG_2016C");
    dataset.push_back("DoubleEG_2016D");
    //dataset.push_back("DoubleEG_2016E");
    //dataset.push_back("DoubleEG_2016F");
    //dataset.push_back("DoubleEG_2016G");
    //dataset.push_back("DoubleEG_2016Hv2");
    //dataset.push_back("DoubleEG_2016Hv3");
    //dataset.push_back("DoubleMu_2016B");
    dataset.push_back("DoubleMu_2016C");
    dataset.push_back("DoubleMu_2016D");
    /*dataset.push_back("DoubleMu_2016E");
      dataset.push_back("DoubleMu_2016F");
      dataset.push_back("DoubleMu_2016G");
      dataset.push_back("DoubleMu_2016Hv2");
      dataset.push_back("DoubleMu_2016Hv3");*/
      dataset.push_back("MuonEG_2016B");
      dataset.push_back("MuonEG_2016C");
      dataset.push_back("MuonEG_2016D");
      /*dataset.push_back("MuonEG_2016E");
      dataset.push_back("MuonEG_2016F");
      dataset.push_back("MuonEG_2016G");
      dataset.push_back("MuonEG_2016Hv2");
      dataset.push_back("MuonEG_2016Hv3");*/
      dataset.push_back("SingleEle_2016B");
      dataset.push_back("SingleEle_2016C");
      /*dataset.push_back("SingleEle_2016D");
    dataset.push_back("SingleEle_2016E");
    dataset.push_back("SingleEle_2016F");
    dataset.push_back("SingleEle_2016G");
    dataset.push_back("SingleEle_2016Hv2");*/
      //dataset.push_back("SingleEle_2016Hv3");
      dataset.push_back("SingleMu_2016B");
      dataset.push_back("SingleMu_2016C");
      //dataset.push_back("SingleMu_2016D");
      /*dataset.push_back("SingleMu_2016F");
    dataset.push_back("SingleMu_2016G");
    dataset.push_back("SingleMu_2016Hv2");
    dataset.push_back("SingleMu_2016Hv3");*/

    vector<TString> type;
    type.push_back("2lSS");
    type.push_back("2lSS_lepMVA_CR");
    type.push_back("2lOS_CR");

    for(unsigned int i=0;i<dataset.size();i++){
      for(unsigned int j=0;j<type.size();j++){
	TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/"+dataset[i]+"_split_"+type[j]+"_MEM";
	TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_"+dataset[i]+"_split.root";
	add_everything_MEM(file,file2,false);	
      }
    }

}











void full_proc_122016(){

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttG_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_PU_newtrig";
  add_everything(file,true);

  //file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/EWK/HTauTauTree_ZZ_split_PU_newtrig";
  //add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WWW_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WWZ_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WZZ_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_ZZZ_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_tZq_split_PU_newtrig";
  add_everything(file,true);

  //file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_TTTT_split";
  //add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WpWp_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_ext_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromT_split_PU_newtrig";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split_PU_newtrig";
  add_everything(file,true);

  vector<TString> syst;
  syst.push_back("JECup");
  syst.push_back("JECdown");
  syst.push_back("TESup");
  syst.push_back("TESdown");

  for(unsigned int i=0;i<syst.size();i++){

    TString file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/ttH/HTauTauTree_ttH_Hnonbb_split_"+syst[i]+"_PU_newtrig";
    add_everything(file,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttW_split_"+syst[i]+"_PU_newtrig";
    add_everything(file,true);
    

    file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttZ_split_"+syst[i]+"_PU_newtrig";
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttG_split_"+syst[i]+"_PU_newtrig";
    add_everything(file,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/EWK/HTauTauTree_WZ_split_"+syst[i]+"_PU_newtrig";
    add_everything(file,true);
    
    //file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/EWK/HTauTauTree_ZZ_split_"+syst[i]+"_PU_newtrig";
    //add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_WWW_split_"+syst[i]+"_PU_newtrig";
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_WWZ_split_"+syst[i]+"_PU_newtrig";
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_WZZ_split_"+syst[i]+"_PU_newtrig";
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_ZZZ_split_"+syst[i]+"_PU_newtrig";
    add_everything(file,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_tZq_split_"+syst[i]+"_PU_newtrig";
    add_everything(file,true);
    
    //file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_TTTT_split_"+syst[i]+"_PU_newtrig";
    //add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_WpWp_split_"+syst[i]+"_PU_newtrig";
    add_everything(file,true);
      

    }


  vector<TString> dataset;
  /*dataset.push_back("DoubleEG_2016B");
  dataset.push_back("DoubleEG_2016C");
  dataset.push_back("DoubleEG_2016E");
  dataset.push_back("DoubleEG_2016F");
  dataset.push_back("DoubleEG_2016G");*/
  dataset.push_back("DoubleEG_2016Hv2");
  dataset.push_back("DoubleEG_2016Hv3");
  /*dataset.push_back("DoubleMu_2016B");
  dataset.push_back("DoubleMu_2016C");
  dataset.push_back("DoubleMu_2016E");
  dataset.push_back("DoubleMu_2016F");
  dataset.push_back("DoubleMu_2016G");*/
  dataset.push_back("DoubleMu_2016Hv2");
  dataset.push_back("DoubleMu_2016Hv3");
  /*dataset.push_back("MuonEG_2016B");
  dataset.push_back("MuonEG_2016C");
  dataset.push_back("MuonEG_2016D");
  dataset.push_back("MuonEG_2016E");
  dataset.push_back("MuonEG_2016F");
  dataset.push_back("MuonEG_2016G");*/
  dataset.push_back("MuonEG_2016Hv2");
  dataset.push_back("MuonEG_2016Hv3");
  /*dataset.push_back("SingleEle_2016B");
  dataset.push_back("SingleEle_2016C");
  dataset.push_back("SingleEle_2016D");
  dataset.push_back("SingleEle_2016E");
  dataset.push_back("SingleEle_2016F");
  dataset.push_back("SingleEle_2016G");*/
  dataset.push_back("SingleEle_2016Hv2");
  dataset.push_back("SingleEle_2016Hv3");
  /*dataset.push_back("SingleMu_2016B");
  dataset.push_back("SingleMu_2016C");
  dataset.push_back("SingleMu_2016D");
  dataset.push_back("SingleMu_2016E");
  dataset.push_back("SingleMu_2016F");
  dataset.push_back("SingleMu_2016G");*/
  dataset.push_back("SingleMu_2016Hv2");  
  dataset.push_back("SingleMu_2016Hv3");
  
  for(unsigned int i=0;i<dataset.size();i++){
    TString file = "/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_"+dataset[i]+"_split_newtrig";
    add_everything(file,false);
  }


}

