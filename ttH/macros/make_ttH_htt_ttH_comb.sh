WriteDatacards_1l_2tau_ttH_comb -i /data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards_ttH_comb/datacard_BDT_1l2tau_syst_35.9fb_042017.root

WriteDatacards_2lss_1tau_ttH_comb -i /data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards_ttH_comb/datacard_MEM_ttH_vs_full_bkg_2lSS_nomiss_nofaketau_35.9fb_042017.root -o ttH_2lss_1tau_MEM_nomiss.root -b ttH_2lss_1tau_nomiss

WriteDatacards_2lss_1tau_ttH_comb -i /data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards_ttH_comb/datacard_MEM_ttH_vs_full_bkg_2lSS_missing_nofaketau_35.9fb_042017.root -o ttH_2lss_1tau_MEM_missing.root -b ttH_2lss_1tau_missing

WriteDatacards_3l_1tau_ttH_comb -i /data_CMS/cms/strebler/ttH_prod_80X_01_2017/datacards_ttH_comb/datacard_MVA_3l_syst_nofaketau_35.9fb_042017.root


combineCards.py ttH_1l_2tau.txt ttH_2lss_1tau_MEM_nomiss.txt ttH_2lss_1tau_MEM_missing.txt ttH_3l_1tau.txt > ttH_htt_2016_4cat.txt


combine -M MaxLikelihoodFit -m 125 ttH_htt_2016_4cat.txt

combine -M Asymptotic -m 125 ttH_htt_2016_4cat.txt
