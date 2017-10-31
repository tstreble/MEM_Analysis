#include "trigger_filter.C"


void test(){


  /*vector<TString> treename;
  treename.push_back("HTauTauTree_1l_2tau");
  treename.push_back("HTauTauTree_1l_2tau_fake_CR");
  treename.push_back("HTauTauTree_2lSS");
  treename.push_back("HTauTauTree_2lSS_lepMVA_CR");
  treename.push_back("HTauTauTree_2lOS_CR");
  treename.push_back("HTauTauTree_3l");
  treename.push_back("HTauTauTree_3l_lepMVA_CR");*/

  /*TString filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_tZq_split_PU.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_tZq_split_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);*/

  /*TString filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split_PU.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_split_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_ext_split_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_DL_ext_split_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);*/

  /*TString filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromT_split_PU.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromT_split_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/TTbar/HTauTauTree_ttbar_SLfromTbar_split_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);*/


  /*TString filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_PU.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split_PU_newtrig.root";
add_trigger_filter(filein,fileout,treename,true);

 filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_PU.root";
 fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split_PU_newtrig.root";
add_trigger_filter(filein,fileout,treename,true);

 filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_PU.root";
 fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split_PU_newtrig.root";
add_trigger_filter(filein,fileout,treename,true);

 filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_PU.root";
 fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split_PU_newtrig.root";
add_trigger_filter(filein,fileout,treename,true);

 filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttG_split_PU.root";
 fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/ttV/HTauTauTree_ttG_split_PU_newtrig.root";
add_trigger_filter(filein,fileout,treename,true);

 filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_PU.root";
 fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split_PU_newtrig.root";
add_trigger_filter(filein,fileout,treename,true);
 
 filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WWW_split_PU.root";
 fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WWW_split_PU_newtrig.root";
add_trigger_filter(filein,fileout,treename,true);

 filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WWZ_split_PU.root";
 fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WWZ_split_PU_newtrig.root";
add_trigger_filter(filein,fileout,treename,true);

 filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WZZ_split_PU.root";
 fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WZZ_split_PU_newtrig.root";
add_trigger_filter(filein,fileout,treename,true);

 filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_ZZZ_split_PU.root";
 fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_ZZZ_split_PU_newtrig.root";
add_trigger_filter(filein,fileout,treename,true);

 filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WpWp_split_PU.root";
 fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Rares/HTauTauTree_WpWp_split_PU_newtrig.root";
 add_trigger_filter(filein,fileout,treename,true);*/

 
  //vector<TString> dataset;
  /*dataset.push_back("DoubleEG");
  dataset.push_back("MuonEG");
  dataset.push_back("DoubleMu");*/
  //dataset.push_back("SingleMu");
  //dataset.push_back("SingleEle");

  //vector<TString> era;
  /*era.push_back("2016B");
  era.push_back("2016C");
  era.push_back("2016D");
  era.push_back("2016E");
  era.push_back("2016F");
  era.push_back("2016G");*/
  //era.push_back("2016Hv2");
  //era.push_back("2016Hv3");
  
  /*for(unsigned int i=0; i<dataset.size();i++){
    for(unsigned int j=0; j<era.size();j++){
      
      TString filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_"+dataset[i]+"_"+era[j]+"_split.root";
      TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/nominal/Data/HTauTauTree_"+dataset[i]+"_"+era[j]+"_split_newtrig.root";
      add_trigger_filter(filein,fileout,treename,false);

    }
    }*/

  /*vector<TString> syst_type;
  syst_type.push_back("JECup");
  syst_type.push_back("JECdown");
  syst_type.push_back("TESup");
  syst_type.push_back("TESdown");

  for(unsigned int i=0;i<syst_type.size();i++){*/

    /*TString filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/ttH/HTauTauTree_ttH_Hnonbb_split_"+syst_type[i]+"_PU.root";
    TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/ttH/HTauTauTree_ttH_Hnonbb_split_"+syst_type[i]+"_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);


    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/ttV/HTauTauTree_ttW_split_"+syst_type[i]+"_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/ttV/HTauTauTree_ttW_split_"+syst_type[i]+"_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);*/

    /*filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/ttV/HTauTauTree_ttW_ext_split_"+syst_type[i]+"_PU.root";
   fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/ttV/HTauTauTree_ttW_ext_split_"+syst_type[i]+"_PU_newtrig.root";
   add_trigger_filter(filein,fileout,treename);*/

  /*filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/ttV/HTauTauTree_ttZ_split_"+syst_type[i]+"_PU.root";
   fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/ttV/HTauTauTree_ttZ_split_"+syst_type[i]+"_PU_newtrig.root";
   add_trigger_filter(filein,fileout,treename,true);
   
   filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/ttV/HTauTauTree_ttG_split_"+syst_type[i]+"_PU.root";
   fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/ttV/HTauTauTree_ttG_split_"+syst_type[i]+"_PU_newtrig.root";
   add_trigger_filter(filein,fileout,treename,true);
   
    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/EWK/HTauTauTree_WZ_split_"+syst_type[i]+"_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/EWK/HTauTauTree_WZ_split_"+syst_type[i]+"_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);

    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/Rares/HTauTauTree_WWW_split_"+syst_type[i]+"_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/Rares/HTauTauTree_WWW_split_"+syst_type[i]+"_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);

    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/Rares/HTauTauTree_WWZ_split_"+syst_type[i]+"_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/Rares/HTauTauTree_WWZ_split_"+syst_type[i]+"_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);

    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/Rares/HTauTauTree_WZZ_split_"+syst_type[i]+"_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/Rares/HTauTauTree_WZZ_split_"+syst_type[i]+"_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);

    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/Rares/HTauTauTree_ZZZ_split_"+syst_type[i]+"_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/Rares/HTauTauTree_ZZZ_split_"+syst_type[i]+"_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);

    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/Rares/HTauTauTree_WpWp_split_"+syst_type[i]+"_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/Rares/HTauTauTree_WpWp_split_"+syst_type[i]+"_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);*/

  /*filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/Rares/HTauTauTree_tZq_split_"+syst_type[i]+"_PU.root";
    TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_splitted/"+syst_type[i]+"/Rares/HTauTauTree_tZq_split_"+syst_type[i]+"_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);

    }*/

  vector<TString> treename;
  treename.push_back("T");

  /*TString filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttH/ttH_Hnonbb_split_2lSS_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);
  
  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);
 
  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttG_split_2lSS_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttG_split_2lSS_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true); 
  
  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/EWK/WZ_split_2lSS_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/EWK/WZ_split_2lSS_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WWW_split_2lSS_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WWW_split_2lSS_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);
  
  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WWZ_split_2lSS_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WWZ_split_2lSS_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WZZ_split_2lSS_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WZZ_split_2lSS_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);
  
  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/ZZZ_split_2lSS_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/ZZZ_split_2lSS_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WpWp_split_2lSS_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WpWp_split_2lSS_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/tZq_split_2lSS_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/tZq_split_2lSS_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_split_2lSS_lepMVA_CR_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_split_2lSS_lepMVA_CR_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_split_2lSS_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/TTbar/ttbar_DL_split_2lSS_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);*/

  /*vector<TString> syst_type;
  syst_type.push_back("JECup");
  syst_type.push_back("JECdown");
  syst_type.push_back("TESup");
  syst_type.push_back("TESdown");*/

  //for(unsigned int i=0;i<syst_type.size();i++){

    /*TString filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/ttH/ttH_Hnonbb_split_"+syst_type[i]+"_2lSS_MEM_PU.root";
    TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/ttH/ttH_Hnonbb_split_"+syst_type[i]+"_2lSS_MEM_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);
    
    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/ttV/ttZ_split_"+syst_type[i]+"_2lSS_MEM_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/ttV/ttZ_split_"+syst_type[i]+"_2lSS_MEM_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);
    
    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/ttV/ttW_split_"+syst_type[i]+"_2lSS_MEM_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/ttV/ttW_split_"+syst_type[i]+"_2lSS_MEM_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);

    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/ttV/ttG_split_"+syst_type[i]+"_2lSS_MEM_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/ttV/ttG_split_"+syst_type[i]+"_2lSS_MEM_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);
        
    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/EWK/WZ_split_"+syst_type[i]+"_2lSS_MEM_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/EWK/WZ_split_"+syst_type[i]+"_2lSS_MEM_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);
        
    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/Rares/WWW_split_"+syst_type[i]+"_2lSS_MEM_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/Rares/WWW_split_"+syst_type[i]+"_2lSS_MEM_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);

    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/Rares/WWZ_split_"+syst_type[i]+"_2lSS_MEM_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/Rares/WWZ_split_"+syst_type[i]+"_2lSS_MEM_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);

    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/Rares/WZZ_split_"+syst_type[i]+"_2lSS_MEM_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/Rares/WZZ_split_"+syst_type[i]+"_2lSS_MEM_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);

    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/Rares/ZZZ_split_"+syst_type[i]+"_2lSS_MEM_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/Rares/ZZZ_split_"+syst_type[i]+"_2lSS_MEM_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);    

    filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/Rares/WpWp_split_"+syst_type[i]+"_2lSS_MEM_PU.root";
    fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/Rares/WpWp_split_"+syst_type[i]+"_2lSS_MEM_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);*/    
    
    /*TString filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/Rares/tZq_split_"+syst_type[i]+"_2lSS_MEM_PU.root";
    TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/"+syst_type[i]+"/Rares/tZq_split_"+syst_type[i]+"_2lSS_MEM_PU_newtrig.root";
    add_trigger_filter(filein,fileout,treename,true);      */

  //}


  //vector<TString> dataset;
  /*dataset.push_back("DoubleEG");
  dataset.push_back("MuonEG");
  dataset.push_back("DoubleMu");*/
  //dataset.push_back("SingleMu");
  //dataset.push_back("SingleEle");

  //vector<TString> era;
  /*era.push_back("2016B");
  era.push_back("2016C");
  era.push_back("2016D");
  era.push_back("2016E");
  era.push_back("2016F");
  era.push_back("2016G");*/
  //era.push_back("2016Hv2");
  //era.push_back("2016Hv3");
  
  /*for(unsigned int i=0; i<dataset.size();i++){
    for(unsigned int j=0; j<era.size();j++){

      TString filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/"+dataset[i]+"_"+era[j]+"_split_2lSS_lepMVA_CR_MEM_16*.root";
      TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/"+dataset[i]+"_"+era[j]+"_split_2lSS_lepMVA_CR_MEM_newtrig.root";
      add_trigger_filter(filein,fileout,treename,false);

      filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/"+dataset[i]+"_"+era[j]+"_split_2lOS_CR_MEM_16*.root";
      fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/"+dataset[i]+"_"+era[j]+"_split_2lOS_CR_MEM_newtrig.root";
      add_trigger_filter(filein,fileout,treename,false);

      if(era[j]=="2016Hv3") continue;

      filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/"+dataset[i]+"_"+era[j]+"_split_2lSS_MEM_16*.root";
      fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Data/"+dataset[i]+"_"+era[j]+"_split_2lSS_MEM_newtrig.root";
      add_trigger_filter(filein,fileout,treename,false);

    }
    }*/


  TString filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_lepMVA_CR_MEM_PU.root";
  TString fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttZ_split_2lSS_lepMVA_CR_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);
  
  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_lepMVA_CR_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttW_split_2lSS_lepMVA_CR_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);
 
  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttG_split_2lSS_lepMVA_CR_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/ttV/ttG_split_2lSS_lepMVA_CR_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true); 
  
  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/EWK/WZ_split_2lSS_lepMVA_CR_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/EWK/WZ_split_2lSS_lepMVA_CR_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);


  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WWW_split_2lSS_lepMVA_CR_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WWW_split_2lSS_lepMVA_CR_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);
  
  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WWZ_split_2lSS_lepMVA_CR_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WWZ_split_2lSS_lepMVA_CR_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WZZ_split_2lSS_lepMVA_CR_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WZZ_split_2lSS_lepMVA_CR_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);
  
  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/ZZZ_split_2lSS_lepMVA_CR_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/ZZZ_split_2lSS_lepMVA_CR_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WpWp_split_2lSS_lepMVA_CR_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/WpWp_split_2lSS_lepMVA_CR_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);

  filein="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/tZq_split_2lSS_lepMVA_CR_MEM_PU.root";
  fileout="/data_CMS/cms/strebler/ttH_prod_80X_12_2016/ntuples_MEM/nominal/Rares/tZq_split_2lSS_lepMVA_CR_MEM_PU_newtrig.root";
  add_trigger_filter(filein,fileout,treename,true);



}
