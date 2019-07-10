if __name__ == '__main__':

# Usage : python crabConfig.py (to create jobs)
#         ./multicrab -c status -d <work area> (to check job status)

    from CRABAPI.RawCommand import crabCommand
    from httplib import HTTPException

    from CRABClient.UserUtilities import config
    config = config()
    
    from multiprocessing import Process

    # Common configuration

    config.General.workArea     = 'crab_projects_ntuples'
    config.General.transferLogs = False
    config.JobType.pluginName   = 'Analysis' # PrivateMC
    config.JobType.psetName     = 'run_data_105X_ZtoEE_mini.py'
    #config.JobType.psetName     = 'run_data_101X_BsToJPsiPhi_mini.py'
    #config.JobType.inputFiles   = ['Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt', 'Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt', 'Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt', 'Summer16_23Sep2016AllV4_DATA.db']
    config.JobType.sendExternalFolder = True
    config.Data.inputDBS        = 'global'    
    config.Data.splitting       = 'LumiBased' # EventBased, FileBased, LumiBased (1 lumi ~= 300 events)
    #config.Data.splitting       = 'Automatic' # EventBased, FileBased, LumiBased (1 lumi ~= 300 events)

    config.Data.totalUnits      = -1
    config.Data.publication     = False
    #config.Data.lumiMask        = 'testjson.txt'
    #config.Data.lumiMask        = 'Cert_314472-317080_13TeV_PromptReco_Collisions18_JSON.txt'
    #config.Data.lumiMask        = 'Cert_314472-323523_13TeV_PromptReco_Collisions18_JSON.txt'
    config.Data.lumiMask        = 'Cert_314472-325175_13TeV_PromptReco_Collisions18_JSON.txt'

    config.Site.storageSite     = 'T3_US_FNALLPC'
    #config.Site.storageSite     = 'T0_CH_CERN'
    config.JobType.maxMemoryMB = 4000
    config.Data.allowNonValidInputDataset = True

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException, hte:
            print hte.headers

    # dataset dependent configuration

    config.General.requestName = 'ParkingBPH1_Run2018A-22Mar2019-v1_09Jul2019_MINIAOD'
    #config.General.requestName = 'ZToEE_NNPDF31_13TeV-powheg_M_50_120_AOD_8Jul19_DielectronSpectrum'

    config.Data.unitsPerJob    = 10
    config.Data.inputDataset   = '/ParkingBPH1/Run2018A-22Mar2019-v1/MINIAOD'
    #config.Data.inputDataset   = '/ZToEE_NNPDF31_13TeV-powheg_M_50_120/RunIIFall17DRPremix-94X_mc2017_realistic_v10-v2/AODSIM'

    #config.Data.outLFNDirBase  = '/store/user/tkwon/ParkingBPH_Run2018B_PromptReco-v1'
    p = Process(target=submit, args=(config,))
    p.start()
    p.join()




