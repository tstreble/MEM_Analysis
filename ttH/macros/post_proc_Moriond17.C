#include "add_bTag_CSVshape_SF.C"
#include "add_event_weight.C"
#include "add_BDT.C"
#include "trigger_filter_1l2tau_Xtrig.C"
#include "add_NBadMu.C"
#include "add_low_mass_veto.C"
#include "add_event_weight_be.C"
#include "add_tauSF.C"
#include "add_lepSF_v3.C"


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

    add_event_weight_be(file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto.root",
			file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be.root",		    
			treename,isMC);

    add_tauSF(file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be.root",
			file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_tauSF3.root",		    
			treename,isMC);

    add_lepSF_v3(file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_tauSF3.root",
		 file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root",		    
		 treename,isMC);

    add_3l1tau_BDT(file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3.root",
		   file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_be_leptauSF3_BDT3l.root",		    
		   treename);
    
  }


  else{


    treename.push_back("HTauTauTree_1l_2tau");
    treename.push_back("HTauTauTree_1l_2tau_fake_CR");
    //treename.push_back("HTauTauTree_2lSS");
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

    //treename.erase(treename.begin()+2);
    add_low_mass_veto(file+"_BDT_1l2tau_trig_weight_new.root",
		      file+"_BDT_1l2tau_trig_weight_new_massveto.root",
		      treename);

    add_event_weight_be(file+"_BDT_1l2tau_trig_weight_new_massveto.root",
		     file+"_BDT_1l2tau_trig_weight_new_massveto_be.root",
		     treename,isMC);

    add_3l1tau_BDT(file+"_BDT_1l2tau_trig_weight_new_massveto_be.root",
		   file+"_BDT_1l2tau_trig_weight_new_massveto_be_BDT3l.root",		    
		   treename);

  }




}





void add_everything_tHq(TString file,TString file_secondary){

  vector<TString> treename;
  bool isMC = true;

  treename.push_back("HTauTauTree_1l_2tau");
  treename.push_back("HTauTauTree_1l_2tau_fake_CR");
  treename.push_back("HTauTauTree_2lSS");
  treename.push_back("HTauTauTree_2lSS_lepMVA_CR");
  treename.push_back("HTauTauTree_3l");
  treename.push_back("HTauTauTree_3l_ttZ_CR");
  treename.push_back("HTauTauTree_3l_lepMVA_CR");

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
    
  add_low_mass_veto(file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new.root",
		    file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto.root",
		    treename);
  
  add_MC_weight_tHq_fromSecondary(file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto.root",
				  file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq.root",
				  treename,
				  file_secondary,
				  "HTauTauTree");

  add_tauSF(file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq.root",
	    file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_tauSF3.root",		    
	    treename,isMC);

  add_lepSF_v3(file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_tauSF3.root",
	       file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_leptauSF3.root",		    
	       treename,isMC);
  
  add_3l1tau_BDT(file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_leptauSF3.root",
		   file+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq_leptauSF3_BDT3l.root",		    
		   treename);
  
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

    add_trigger_filter_1l2tau_Xtrig(file+"_btagSF_new.root",
				    file+"_btagSF_trig_new.root",
				    treename,isMC);

    add_event_weight(file+"_btagSF_trig_new.root",
		   file+"_btagSF_trig_lepTauSF_new.root",
		   treename,isMC);

    TString file2=file+"_btagSF_trig_lepTauSF_new";

    if(file.Contains("lepMVA_CR")){
      file2+="_be";
      add_event_weight_be(file+"_btagSF_trig_lepTauSF_new.root",
			  file+"_btagSF_trig_lepTauSF_new_be.root",
			  treename,isMC);
    }
  
    add_tauSF(file2+".root",
	      file2+"_tauSF3.root",		    
	      treename,isMC);

    add_lepSF_v3(file2+"_tauSF3.root",
		  file2+"_leptauSF3.root",		    
		  treename,isMC);

    add_2lSS1tau_MEM_BDT(file2+"_leptauSF3.root",
			 file2+"_leptauSF3_BDTMEM.root",
			 treename);

  }

  else if(!file.Contains("nominal")){

    add_bTag_CSVshape_SF_fromSecondaryFile(file+".root",
					   file+"_btagSF_new.root",
					   "T",
					   file2,
					   treename2);

    add_trigger_filter_1l2tau_Xtrig(file+"_btagSF_new.root",
				    file+"_btagSF_trig_new.root",
				    treename,isMC);

    add_event_weight_fromSecondary(file+"_btagSF_trig_new.root",
				   file+"_btagSF_trig_lepTauSF_new.root",
				   "T",
				   file2,
				   treename2);

    add_tauSF(file+"_btagSF_trig_lepTauSF_new.root",
	      file+"_btagSF_trig_lepTauSF_new_tauSF3.root",		    
	      treename,isMC);

    add_lepSF_v3(file+"_btagSF_trig_lepTauSF_new_tauSF3.root",
	      file+"_btagSF_trig_lepTauSF_new_leptauSF3.root",		    
	      treename,isMC);

    add_2lSS1tau_MEM_BDT(file+"_btagSF_trig_lepTauSF_new_leptauSF3.root",
			 file+"_btagSF_trig_lepTauSF_new_leptauSF3_BDTMEM.root",
			 treename);
    
  }



  else if(file.Contains("Data")){

    add_NBadMu_fromSecondary(file+".root",
			     file+"_NBadMu.root",
			     "T",
			     file2,
			     treename2);

    add_trigger_filter_1l2tau_Xtrig(file+"_NBadMu.root",
				    file+"_NBadMu_trig_new.root",
				    treename,isMC);
    
    add_event_weight(file+"_NBadMu_trig.root",
		     file+"_NBadMu_trig_weight_new.root",
		     treename,isMC);

    add_event_weight_be(file+"_NBadMu_trig_weight_new.root",
		     file+"_NBadMu_trig_weight_new_be.root",
		     treename,isMC);

   add_2lSS1tau_MEM_BDT(file+"_NBadMu_trig_weight_new_be.root",
			 file+"_NBadMu_trig_weight_new_be_BDTMEM.root",
			 treename);
    
  }


}




void add_everything_MEM_tHq(TString file,TString file2,bool isMC){

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

    add_trigger_filter_1l2tau_Xtrig(file+"_btagSF_new.root",
                                    file+"_btagSF_trig_new.root",
                                    treename,isMC);

   add_event_weight(file+"_btagSF_trig_new.root",
                   file+"_btagSF_trig_lepTauSF_new.root",
                   treename,isMC);

   add_MC_weight_tHq_fromSecondary(file+"_btagSF_trig_lepTauSF_new.root",
                                  file+"_btagSF_trig_lepTauSF_new_MCtHq.root",
                                  treename,
                                  file2,
                                  treename2);

   TString file3=file+"_btagSF_trig_lepTauSF_new_MCtHq";

   if(file.Contains("lepMVA_CR")){
     file3+="_be";
     add_event_weight_be(file+"_btagSF_trig_lepTauSF_new_MCtHq.root",
			 file+"_btagSF_trig_lepTauSF_new_MCtHq_be.root",
			 treename,isMC);

   }

   add_tauSF(file3+".root",
	     file3+"_tauSF3.root",		    
	     treename,isMC);

   add_lepSF_v3(file3+"_tauSF3.root",
	     file3+"_leptauSF3.root",		    
	     treename,isMC);

   add_2lSS1tau_MEM_BDT(file3+"_leptauSF3.root",
			file3+"_leptauSF3_BDTMEM.root",
			treename);


  }

  else if(!file.Contains("nominal")){

    add_bTag_CSVshape_SF_fromSecondaryFile(file+".root",
                                           file+"_btagSF_new.root",
                                           "T",
                                           file2,
                                           treename2);

    add_trigger_filter_1l2tau_Xtrig(file+"_btagSF_new.root",
                                    file+"_btagSF_trig_new.root",
                                    treename,isMC);

   add_event_weight_fromSecondary(file+"_btagSF_trig_new.root",
                                   file+"_btagSF_trig_lepTauSF_new.root",
                                   "T",
                                   file2,
                                   treename2);

   add_MC_weight_tHq_fromSecondary(file+"_btagSF_trig_lepTauSF_new.root",
                                  file+"_btagSF_trig_lepTauSF_new_MCtHq.root",
                                  treename,
                                  file2,
                                  treename2);

   add_tauSF(file+"_btagSF_trig_lepTauSF_new_MCtHq.root",
	     file+"_btagSF_trig_lepTauSF_new_MCtHq_tauSF3.root",		    
	      treename,isMC);

   add_lepSF_v3(file+"_btagSF_trig_lepTauSF_new_MCtHq_tauSF3.root",
		file+"_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3.root",
		treename,isMC);

   add_2lSS1tau_MEM_BDT(file+"_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3.root",
		       file+"_btagSF_trig_lepTauSF_new_MCtHq_leptauSF3_BDTMEM.root",
		       treename);


  }


}






void add_everything_BDT_2lSS1tau(TString file){

  vector<TString> treename;
  treename.push_back("T");

  add_2lSS1tau_MEM_BDT(file+".root",
		       file+"_BDT.root",
		       treename);



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

  /*TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_ttH_Hnonbb_split";
    add_everything(file,true);*/

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_THQ_split";
  add_everything(file,true);
  
  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_THW_split";
  add_everything(file,true);

  /*file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_ttHJet_Hnonbb_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttW_ext_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Rares/HTauTauTree_ttWW_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_lowmass_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_ext_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttG_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_split";
  add_everything(file,true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/EWK/HTauTauTree_WZ_powheg_split";
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
  syst.push_back("TESup");
  syst.push_back("TESdown");

  for(unsigned int i=0;i<syst.size();i++){

    /*file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttH/HTauTauTree_ttHJet_Hnonbb_split_"+syst[i];
      add_everything(file,true);*/

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttH/HTauTauTree_THQ_split_"+syst[i];
    TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_PU_THQ.root";
    add_everything_tHq(file,file2);    

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttH/HTauTauTree_THW_split_"+syst[i];
    file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_converted/nominal/ttH/ntuple_PU_THW.root";
    add_everything_tHq(file,file2);

    /*file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttZ_lowmass_split_"+syst[i];
    add_everything(file,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttW_split_"+syst[i];
    add_everything(file,true);

   file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttW_ext_split_"+syst[i];
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttZ_split_"+syst[i];
    add_everything(file,true);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_ttWW_split_"+syst[i];
    add_everything(file,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttV/HTauTauTree_ttG_split_"+syst[i];
    add_everything(file,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/EWK/HTauTauTree_WZ_split_"+syst[i];
    add_everything(file,true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/EWK/HTauTauTree_WZ_powheg_split_"+syst[i];
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
    add_everything(file,true);*/
      

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
  
  /*for(unsigned int i=0;i<dataset.size();i++){
    TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/Data/HTauTauTree_"+dataset[i]+"_split";
      add_everything(file,false);
      }*/


}







void full_proc_MEM(){


  /*vector<TString> type;
  type.push_back("2lSS");
  type.push_back("2lSS_lepMVA_CR");

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/syncNtuple_ttH_tautau_split_2lSS_MEM_170301";
  add_everything_MEM(file,"",true);   

  for(unsigned int i=0;i<type.size();i++){

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/ttHJet_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);    

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttG_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttW_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/WZ_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/WZ_powheg_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/ttWW_split_"+type[i]+"_MEM";
    add_everything_MEM(file,"",true);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/THQ_split_"+type[i]+"_MEM";
    TString file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_THQ_split.root";
   add_everything_MEM_tHq(file,file2,true);

   file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/THW_split_"+type[i]+"_MEM";
   file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttH/HTauTauTree_THW_split.root";
   add_everything_MEM_tHq(file,file2,true);

   file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_lowmass_split_"+type[i]+"_MEM";
   file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/nominal/ttV/HTauTauTree_ttZ_lowmass_split.root";
   add_everything_MEM(file,file2,true);

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


  }

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_DL_split_2lSS_lepMVA_CR_MEM";
  add_everything_MEM(file,"",true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM";
  add_everything_MEM(file,"",true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM";
  add_everything_MEM(file,"",true);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM";
  add_everything_MEM(file,"",true);

    vector<TString> syst;
    syst.push_back("JECup");
    syst.push_back("JECdown");
    syst.push_back("TESup");
    syst.push_back("TESdown");

    for(unsigned int i=0;i<syst.size();i++){

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

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/ttWW_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/Rares/HTauTauTree_ttWW_split_"+syst[i]+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto.root";
      add_everything_MEM(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/ttH/THQ_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttH/HTauTauTree_THQ_split_"+syst[i]+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq.root";
      add_everything_MEM_tHq(file,file2,true);

      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/ttH/THW_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/ttH/HTauTauTree_THW_split_"+syst[i]+"_BDT_1l2tau_btagSF_trig_lepTauSF_new_massveto_MCtHq.root";
      add_everything_MEM_tHq(file,file2,true);


      file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/EWK/WZ_powheg_split_"+syst[i]+"_2lSS_MEM";
      file2 = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_splitted/"+syst[i]+"/EWK/HTauTauTree_WZ_powheg_split_"+syst[i]+"_BDT_1l2tau_btagSF_trig_lepTauSF_new.root";
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

    vector<TString> type;
    type.push_back("2lSS");
    type.push_back("2lSS_lepMVA_CR");
    type.push_back("2lOS_CR");

    for(unsigned int i=0;i<dataset.size();i++){
      for(unsigned int j=0;j<type.size();j++){
	if(dataset[i].Contains("Hv3") && type[j]=="2lSS") continue;
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








void full_proc_MEM_BDT(){

  vector<TString> type;
  type.push_back("2lSS");
  type.push_back("2lSS_lepMVA_CR");

  for(unsigned int i=0;i<type.size();i++){

    TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttH/ttHJet_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttG_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttZ_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/ttV/ttW_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/WZ_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/WZ_powheg_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/EWK/ZZ_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/TTTT_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/tZq_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WWW_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WWZ_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WZZ_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/ZZZ_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Rares/WpWp_split_"+type[i]+"_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);


  }

  TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_DL_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
  add_everything_BDT_2lSS1tau(file);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_DL_ext_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
  add_everything_BDT_2lSS1tau(file);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_SLfromT_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
  add_everything_BDT_2lSS1tau(file);

  file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/TTbar/ttbar_SLfromTbar_split_2lSS_lepMVA_CR_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
  add_everything_BDT_2lSS1tau(file);


  vector<TString> syst;
  syst.push_back("JECup");
  syst.push_back("JECdown");
  syst.push_back("TESup");
  syst.push_back("TESdown");

  for(unsigned int i=0;i<syst.size();i++){

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/ttH/ttHJet_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/ttV/ttG_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/ttV/ttZ_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/ttV/ttW_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/EWK/WZ_powheg_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/EWK/ZZ_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/tZq_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/TTTT_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/WWW_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/WWZ_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);
    
    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/WZZ_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/ZZZ_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

    file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/"+syst[i]+"/Rares/WpWp_split_"+syst[i]+"_2lSS_MEM_btagSF_trig_lepTauSF_new_be_tauSF3";
    add_everything_BDT_2lSS1tau(file);

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
    
  type.clear();
  type.push_back("2lSS");
  type.push_back("2lSS_lepMVA_CR");
  type.push_back("2lOS_CR");

  for(unsigned int i=0;i<dataset.size();i++){
    for(unsigned int j=0;j<type.size();j++){
      if(dataset[i].Contains("2016Hv3") && type[j]=="2lSS") continue;
      TString file = "/data_CMS/cms/strebler/ttH_prod_80X_01_2017/ntuples_MEM/nominal/Data/"+dataset[i]+"_split_"+type[j]+"_MEM_NBadMu_trig_weight_new";
      add_everything_BDT_2lSS1tau(file);	
    }
  }

}


