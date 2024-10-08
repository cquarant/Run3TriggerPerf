#cmsRun  config_generic_opt_skimmed.py  RunPeriod="Fall17" # for MC
#cmsRun  config_generic_opt_skimmed.py  RunPeriod="Run2017B" # for Data from 2017
#cmsRun  config_generic_opt_skimmed.py  RunPeriod="Run2018B" # for Data from 2018
#cmsRun  config_generic_opt_skimmed.py  RunPeriod="Autumn18" # for MC from 2018
#cmsRun  config_generic_opt_skimmed.py  RunPeriod="Summer16" # for MC from 2016


###### Process initialization ##########

import FWCore.ParameterSet.Config as cms

process = cms.Process("Ntuple")

process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.Geometry.GeometryRecoDB_cff')

from TrackingTools.GeomPropagators.AnalyticalPropagator_cfi import AnalyticalPropagator


process.TFileService = cms.Service("TFileService",
                                    fileName = cms.string('flatTuple.root')
                                   )

#from EXOVVNtuplizerRunII.Ntuplizer.ntuplizerOptions_data_cfi import config
from EXOVVNtuplizerRunII.Ntuplizer.ntuplizerOptions_generic_cfi import config

# change from its original value
#config["DZCUT"] = 0.25
#config["FSIGCUT"] = 3
#config["VPROBCUT"] = 0.1
#config["DNNCUT"] = 0.2

isData = True

### SWITCHES ###

print('isData? ', isData)


config["ISBKG"] = False

if isData:
  config["RUNONMC"] = False
  config["USEHAMMER"] = False
  config["USEJSON"] = False
  config["DOGENPARTICLES"] = False
  config["DOGENEVENT"] = False
  config["DOPILEUP"] = False
  config["DOGENHIST"] = False

else:
  config["RUNONMC"] = True
  
  if not config["ISBKG"]:
    config["USEHAMMER"] = True
  else:
    config["USEHAMMER"] = False

  config["USEJSON"] = False
  config["DOGENPARTICLES"] = True
  config["DOGENEVENT"] = True
  config["DOPILEUP"] = True
  config["DOGENHIST"] = True

print('-'*80)
for key, val in config.items():
  print(key.ljust(20), '====>', val)
print('-'*80)



				   
####### Config parser ##########

import FWCore.ParameterSet.VarParsing as VarParsing

options = VarParsing.VarParsing ('analysis')

options.register( 'RunPeriod',
                  '',
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,          # string, int, or float
                  "RunNumber (Default Run2017B)")

options.register( 'runUpToEarlyF',
                  'false',
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list                                                                                                                                 
                  VarParsing.VarParsing.varType.bool,          # string, int, or float                                                                                                                        
                  "false")# https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideAboutPythonConfigFile

####



#options.maxEvents = 1000
options.maxEvents = -1


if isData:
#  options.inputFiles = '/store/user/ytakahas/EphemeralZeroBias/EphemeralZeroBias3/winter21/211205_060748/0000/output_242.root'
  options.inputFiles = [

'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/0356dc7a-65ed-4877-a329-91ea198780fb.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/0ab7145f-b18c-44ff-a6ac-abf095df2c74.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/0af24a80-1c53-4f76-baf0-e153fb80b90f.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/1e7c70d2-8723-4e21-b17b-1b9401de03b8.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/21107bb2-850f-460f-b6bd-2c4e473c3565.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/216c7ab1-b990-445c-8fb8-415d124327be.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/2789b4ec-e433-4f6c-bf43-332105b5bd56.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/353477a1-e5c3-45a3-abcb-9db4ea5d3762.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/396726cf-c8c6-4103-8d32-e39acdedf982.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/3a20b212-04fa-45a3-8599-e9b905743d06.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/3aa55f50-5db8-489a-bc58-e9e4463e1cb8.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/40ad741a-86ee-4d8a-860a-08cd9e5c3250.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/489ec76a-db61-4817-8396-36f23fc87c5c.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/49fa69c1-edb9-46e4-bcb6-91b0d055e3f9.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/51f04118-3427-47a7-833d-c1e2fb75b333.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/5258b503-f72e-43ca-a422-bd4c8494cb30.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/5a06eb66-41d3-4100-a51c-da0bee984431.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/5c575d92-e0a5-4fbe-b9e7-fefb534345db.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/5ccc006b-c504-4123-ae7c-2ebadbf30ca7.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/60847469-b9a2-42fa-a27a-9560365b3fcd.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/6871d038-77ac-4e38-845c-f2732fd5363f.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/69e40a46-a527-4270-8e78-24328f6220da.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/726226bf-b70a-4615-9732-63cbe1fac7a0.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/84f3ce9e-e36d-4150-9f53-cf3b03911460.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/86e355e9-7563-42ce-9a8c-e7e928867914.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/96d115f8-b1bb-4661-8a1f-542b1c4445bf.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/a4f265b2-1e70-49e5-a72c-a57bfcc90c3f.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/ada00ca8-2a23-45cb-8694-77bf36c4d9b0.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/b2dccab2-6d68-4844-adeb-66af28b63e7e.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/b81f6c25-e40c-430e-8dd4-cac7509ff8c4.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/c3fd7f61-3260-46f9-95c3-1de10f4dc054.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/c7ba2418-76d7-41f0-a29c-f8b22233c8e2.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/ca97d216-c801-4ecb-b40b-971dd636ec35.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/d088e565-fa85-4169-b9f6-2e49a958bb1c.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/d2fe4c1b-040f-4820-b627-8b66206feaee.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/d5010f0a-3cbc-4842-9e72-5ea56f216c66.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/e2148e60-8df5-403f-92f6-72dea5a31fb8.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/e4a52e7e-adc9-4899-99bb-e53103dc557d.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/e4f611c7-5c6d-45f9-b686-0e5d0f2b41cc.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/e5119c34-4bd2-44fe-bdf2-71c0a4290e3e.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/f83a0a9d-7956-4904-8587-75ce4ce9337e.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/f87e7adb-a3c0-4c1e-af05-ed7a5e15484a.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/fa76243e-e07e-4e21-81c8-5222c8f84516.root',
'/store/data/Run2022B/HLTPhysics/MINIAOD/PromptReco-v1/000/355/404/00000/fb664f69-f96e-40b9-a09b-0736b5e850f4.root',

    
]

#  options.inputFiles = 'file:/pnfs/psi.ch/cms/trivcat/store/user/ytakahas/purityStudy_CMSSW12_1_0/EphemeralZeroBias1/winter21/211129_085534/0000/output_*.root'

#  options.inputFiles = "file:/work/ytakahas/work/HLT/CMSSW_12_1_0/src/output.root"

#  options.inputFiles = []
#  import glob
#
#  listoffiles  = glob.glob('/pnfs/psi.ch/cms/trivcat/store/user/ytakahas/purityStudy_CMSSW12_1_0/EphemeralZeroBias1/winter21/211129_085534/0000/output_11*.root')
#
#  for file in listoffiles:
#    print('check',file)
#    options.inputFiles.append('file:' + file)
  

else:

  if config["ISBKG"]:
#    options.inputFiles = '/store/mc/RunIISummer20UL18MiniAOD/HbToJPsiMuMu_TuneCP5_13TeV-pythia8-evtgen/MINIAODSIM/106X_upgrade2018_realistic_v11_L1v1-v1/00000/014EC954-4C5E-AD48-BB44-401D779323E3.root'
#    options.inputFiles = '/store/user/ytakahas/qq_JpsiX_MuMu_20211012/UL18_MINIAOD_v1_noDuplCheck/211018_022715/0000/output_file_MINIAOD_92.root'

    options.inputFiles = []
    for a in range(1,176):
      options.inputFiles.append('/store/user/ytakahas/qq_JpsiX_MuMu_20211012/UL18_MINIAOD_v1_noDuplCheck/211018_022715/0000/output_file_MINIAOD_' + str(a) + '.root')

#    options.inputFiles = 'file:/scratch/ytakahas/HbToJPsiMuMu/014EC954-4C5E-AD48-BB44-401D779323E3.root'
  else:
#    options.inputFiles = '/store/mc/RunIISummer19UL18MiniAOD/BcToJPsiTauNu_TuneCP5_13TeV-bcvegpy2-pythia8-evtgen/MINIAODSIM/106X_upgrade2018_realistic_v11_L1v1_ext1-v2/100000/02F13381-1D94-CC43-948A-2EFFB8572949.root'
#    options.inputFiles = '/store/mc/RunIISummer20UL18MiniAOD/BcToJPsiMuMu_inclusive_TuneCP5_13TeV-bcvegpy2-pythia8-evtgen/MINIAODSIM/106X_upgrade2018_realistic_v11_L1v1-v2/00000/06261AC0-CB13-4241-8FCE-729E5E649532.root'

#    options.inputFiles = 'file:/work/ytakahas/work/prod/nanoAOD/Trigger_MC_Winter21/EGM-Run3Winter21DRMiniAOD-00021.root'
    options.inputFiles = 'root://cms-xrd-global.cern.ch//store/mc/Run3Winter21DRMiniAOD/BuToKee_SoftQCDnonD_TuneCP5_14TeV-pythia8-evtgen/MINIAODSIM/FlatPU30to80FEVT_rndm_112X_mcRun3_2021_realistic_v16-v2/260000/0df5bfde-eaca-42fd-a9a8-2ff483e9db6f.root'
#    options.inputFiles = '/store/mc/RunIIAutumn18MiniAOD/BuToKee_Mufilter_SoftQCDnonD_TuneCP5_13TeV-pythia8-evtgen/MINIAODSIM/Custom_RK_BParking_for_RK_102X_upgrade2018_realistic_v15-v2/110000/00D9F371-FE16-E744-A1E0-29A7AEBCAF25.root'

print('file=', options.inputFiles)


options.parseArguments()

process.options  = cms.untracked.PSet( 
                     wantSummary = cms.untracked.bool(True),
                     SkipEvent = cms.untracked.vstring('ProductNotFound'),
                     allowUnscheduled = cms.untracked.bool(True),
                     )


#if isData:
#  print('setting process.options.numberOfThreads = 2')
#  process.options.numberOfThreads=cms.untracked.uint32(2)


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )

# run, lumi, event ID
#                              eventsToProcess = cms.untracked.VEventRange('1:94:182460'),

if config["RUNONMC"]:
  process.source = cms.Source("PoolSource",
                              fileNames = cms.untracked.vstring(options.inputFiles),
                              # Run, lumi, Event
#                              eventsToProcess = cms.untracked.VEventRange('1:15965:82689'),
                              duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),                              
                              ) 
else:                    
  process.source = cms.Source("PoolSource",
                              fileNames = cms.untracked.vstring(options.inputFiles),
#                              skipEvents=cms.untracked.uint32(23000)
                              ) 

print(" process source filenames %s" %(process.source))

#print " process source filenames ", process.source.fileNames
######## Sequence settings ##########

hltFiltersProcessName = 'RECO'
if config["RUNONMC"] or config["JSONFILE"].find('reMiniAOD') != -1:
  hltFiltersProcessName = 'PAT'

# ####### Logger ##########
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.MessageLogger.cerr.threshold = 'INFO'
#process.MessageLogger.categories.append('Ntuple')
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    limit = cms.untracked.int32(1)
)

process.MessageLogger.cerr.FwkReport.reportEvery = 1000

####### Define conditions ##########
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

from Configuration.AlCa.GlobalTag import GlobalTag as customiseGlobalTag

GT = 'auto:run3_hlt'


jetcorr_levels=[]
jetcorr_levels_groomed=[]
if config["RUNONMC"]:
  jetcorr_levels = cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute'])
  jetcorr_levels_groomed = cms.vstring(['L2Relative', 'L3Absolute']) # NO L1 corretion for groomed jets
else:
  jetcorr_levels = cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual'])
  jetcorr_levels_groomed = cms.vstring(['L2Relative', 'L3Absolute', 'L2L3Residual'])

   
######### read JSON file for data ##########					                                                             
if not(config["RUNONMC"]) and config["USEJSON"]:

  import FWCore.PythonUtilities.LumiList as LumiList
  import FWCore.ParameterSet.Types as CfgTypes
  process.source.lumisToProcess = CfgTypes.untracked(CfgTypes.VLuminosityBlockRange())
  myLumis = LumiList.LumiList(filename = config["JSONFILE"]).getCMSSWString().split(',')
  process.source.lumisToProcess.extend(myLumis) 

  

####### Redo Jet clustering sequence ##########
betapar = cms.double(0.0)
fatjet_ptmin = 100.0

from RecoJets.Configuration.RecoPFJets_cff import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *
from RecoJets.JetProducers.PFJetParameters_cfi import *

from PhysicsTools.PatAlgos.tools.helpers import *
pattask = getPatAlgosToolsTask(process)
                                                                                                          
process.chs = cms.EDFilter("CandPtrSelector",
  src = cms.InputTag('packedPFCandidates'),
  cut = cms.string('fromPV')
)

process.ak4PFJetsCHS = ak4PFJetsCHS.clone( src = 'chs' )
process.ak4PFJetsCHS.doAreaFastjet = True


from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

#dataFormat=DataFormat.MiniAOD
#switchOnVIDElectronIdProducer(process,dataFormat,task=pattask)

#process.egmGsfElectronIDSequence = cms.Sequence(process.egmGsfElectronIDs)
     
#my_id_modules = [
#                 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Fall17_94X_V1_cff',
#                 'RecoEgamma.ElectronIdentification.Identification.cutBasedElectronHLTPreselecition_Summer16_V1_cff',
#                 'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV70_cff',
#                 'RecoEgamma.ElectronIdentification.Identification.mvaElectronID_Fall17_noIso_V1_cff',
#                 ]
           
#add them to the VID producer
#for idmod in my_id_modules:
#    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection,task=pattask)

####### Ntuplizer initialization ##########
jetsAK4 = "slimmedJets"


METS = "slimmedMETs"
METS_EGclean = "slimmedMETsEGClean"
METS_MEGclean = "slimmedMETsMuEGClean"
METS_uncorr = "slimmedMETsUncorrected"


##___________________ MET significance and covariance matrix ______________________##


##___________________ Jets ______________________##

  

######## JEC ########
jecLevelsAK8chs = []
jecLevelsAK8Groomedchs = []
jecLevelsAK4chs = []
jecLevelsAK4 = []
jecLevelsAK8Puppi = []
jecLevelsForMET = []

print("1. options.RunPeriod ", options.RunPeriod)
if options.RunPeriod=="" : options.RunPeriod=options.inputFiles[0]

if  config["RUNONMC"] :
  JECprefix = ""
  if ("Fall17" in options.RunPeriod):
    JECprefix = "Fall17_17Nov2017_V32"
    GT ='94X_mcRun2_asymptotic_v3'
  elif ("Summer16" in options.RunPeriod):
    JECprefix = "Summer16_07Aug2017_V11"
    GT = '94X_mc2017_realistic_v17'
  elif (("Autumn18" in options.RunPeriod) or ("Fall18" in options.RunPeriod)):
    JECprefix = "Autumn18_V8"
    GT = '102X_upgrade2018_realistic_v18'
  else:
    JECprefix = "Autumn18_V8"
    GT = '102X_upgrade2018_realistic_v18'

  #jecAK8chsUncFile = "JEC/%s_MC_Uncertainty_AK8PFchs.txt"%(JECprefix)
  jecAK4chsUncFile = "JEC/%s_MC_Uncertainty_AK4PFchs.txt"%(JECprefix)
 



else : #Data
   JECprefix = ""
   JEC_runDependent_suffix= ""

   if ("2017" in options.RunPeriod):
     if ("Run2017B" in  options.RunPeriod): JEC_runDependent_suffix= "B"
     elif ("Run2017C" in  options.RunPeriod): JEC_runDependent_suffix= "C"
     elif ("Run2017D" in  options.RunPeriod): JEC_runDependent_suffix= "D"
     elif ("Run2017E" in  options.RunPeriod): JEC_runDependent_suffix= "E"
     elif ("Run2017F" in  options.RunPeriod): JEC_runDependent_suffix= "F"
     
     JECprefix = "Fall17_17Nov2017"+JEC_runDependent_suffix+"_V32"
     GT = '94X_dataRun2_v11'
     
     
   elif ("2016" in options.RunPeriod):
     if ("Run2016D" in  options.RunPeriod or "Run2016B" in  options.RunPeriod  or "Run2016C" in  options.RunPeriod  ): JEC_runDependent_suffix= "ABC"
     elif ("Run2016E" in  options.RunPeriod): JEC_runDependent_suffix= "EF"
     elif ("Run2016G" in  options.RunPeriod): JEC_runDependent_suffix= "GH"
     elif ("Run2016F" in  options.RunPeriod and  not options.runUpToEarlyF): JEC_runDependent_suffix= "GH"
     elif ("Run2016F" in  options.RunPeriod and   options.runUpToEarlyF): JEC_runDependent_suffix= "EF"


     JECprefix = "Summer16_07Aug2017"+JEC_runDependent_suffix+"_V11"
     GT ='94X_dataRun2_v10'

   elif ("2018" in options.RunPeriod):
     if ("Run2018A" in  options.RunPeriod ): 
       JEC_runDependent_suffix= "A"
       GT="102X_dataRun2_Sep2018ABC_v2" 
     elif ("Run2018B" in  options.RunPeriod): 
       JEC_runDependent_suffix= "B"
       GT="102X_dataRun2_Sep2018ABC_v2"
     elif ("Run2018C" in  options.RunPeriod): 
       JEC_runDependent_suffix= "C"
       GT="102X_dataRun2_Sep2018ABC_v2"
     elif ("Run2018D" in  options.RunPeriod): 
       JEC_runDependent_suffix= "D"
       GT = '102X_dataRun2_Prompt_v16' 

     JECprefix = "Autumn18_Run"+JEC_runDependent_suffix+"_V8"
    
   #jecAK8chsUncFile = "JEC/%s_DATA_Uncertainty_AK8PFchs.txt"%(JECprefix)
   jecAK4chsUncFile = "JEC/%s_DATA_Uncertainty_AK4PFchs.txt"%(JECprefix)
 
#   GT = '106X_dataRun2_v27' 
   print("jec JEC_runDependent_suffix %s ,  prefix %s " %(JEC_runDependent_suffix,JECprefix))

print("jec prefix ", JECprefix)

print("doing corrections  to met on the fly %s" ,config["CORRMETONTHEFLY"])

print("*************************************** GLOBAL TAG *************************************************" )
print(GT)
print("****************************************************************************************************" )

process.GlobalTag = cms.ESSource( "PoolDBESSource",
  DBParameters = cms.PSet(
    connectionRetrialTimeOut = cms.untracked.int32( 60 ),
    idleConnectionCleanupPeriod = cms.untracked.int32( 10 ),
    enableReadOnlySessionOnUpdateConnection = cms.untracked.bool( False ),
    enablePoolAutomaticCleanUp = cms.untracked.bool( False ),
    messageLevel = cms.untracked.int32( 0 ),
    authenticationPath = cms.untracked.string( "." ),
    connectionRetrialPeriod = cms.untracked.int32( 10 ),
    connectionTimeOut = cms.untracked.int32( 0 ),
    enableConnectionSharing = cms.untracked.bool( True )
  ),
  connect = cms.string( "frontier://FrontierProd/CMS_CONDITIONS" ),
  globaltag = cms.string( "103X_dataRun2_HLT_v1" ),
  snapshotTime = cms.string( "" ),
  toGet = cms.VPSet(
  ),
  DumpStat = cms.untracked.bool( False ),
  ReconnectEachRun = cms.untracked.bool( False ),
  RefreshAlways = cms.untracked.bool( False ),
  RefreshEachRun = cms.untracked.bool( False ),
  RefreshOpenIOVs = cms.untracked.bool( False ),
  pfnPostfix = cms.untracked.string( "None" )
)



process.GlobalTag = customiseGlobalTag(process.GlobalTag, globaltag = GT)




if config["CORRMETONTHEFLY"]:  
   if config["RUNONMC"]:
     jecLevelsForMET = [				       
     	 'JEC/%s_MC_L1FastJet_AK4PFchs.txt'%(JECprefix),
     	 'JEC/%s_MC_L2Relative_AK4PFchs.txt'%(JECprefix),
     	 'JEC/%s_MC_L3Absolute_AK4PFchs.txt'%(JECprefix)
       ]
   else:       					       
     jecLevelsForMET = [
     	 'JEC/%s_DATA_L1FastJet_AK4PFchs.txt'%(JECprefix),
     	 'JEC/%s_DATA_L2Relative_AK4PFchs.txt'%(JECprefix),
     	 'JEC/%s_DATA_L3Absolute_AK4PFchs.txt'%(JECprefix),
         'JEC/%s_DATA_L2L3Residual_AK4PFchs.txt'%(JECprefix)
       ]	
      	



################## Ntuplizer ###################
process.ntuplizer = cms.EDAnalyzer("Ntuplizer",
    runOnMC	      = cms.bool(config["RUNONMC"]),
    useHammer	      = cms.bool(config["USEHAMMER"]),
    doGenParticles    = cms.bool(config["DOGENPARTICLES"]),
    doGenEvent	      = cms.bool(config["DOGENEVENT"]),
    doPileUp	      = cms.bool(config["DOPILEUP"]),
    doJpsiMu	      = cms.bool(config["DOJPSIMU"]),
    doJpsiTau	      = cms.bool(config["DOJPSITAU"]),
    doJpsiK	      = cms.bool(config["DOJPSIK"]),
    doJpsiKE	      = cms.bool(config["DOJPSIKE"]),
    doRob	      = cms.bool(config["DOROB"]),
    doVertices	      = cms.bool(config["DOVERTICES"]),
    doMissingEt       = cms.bool(config["DOMISSINGET"]),
    doGenHist         = cms.bool(config["DOGENHIST"]),
    verbose           = cms.bool(config["VERBOSE"]),
    dzcut             = cms.double(config['DZCUT']),
    fsigcut           = cms.double(config['FSIGCUT']),
    vprobcut          = cms.double(config['VPROBCUT']),
    tau_charge        = cms.uint32(config['TAU_CHARGE']),
#    dnnfile_old       = cms.string(config['DNNFILE_OLD']),                        
    dnnfile_perPF     = cms.string(config['DNNFILE_PERPF']),                        
    dnnfile_perEVT_mc    = cms.string(config['DNNFILE_PEREVT_MC']),                        
    dnnfile_perEVT_data    = cms.string(config['DNNFILE_PEREVT_DATA']),                        
#    dnnfile_perEVT_v2 = cms.string(config['DNNFILE_PEREVT_V2']),
    bweightfile = cms.string(config['BWEIGHTFILE']),
    isBkgBSample      = cms.bool(config['ISBKG']),
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    beamSpot = cms.InputTag("offlineBeamSpot"),
    taus = cms.InputTag("slimmedTaus"),
    muons = cms.InputTag("slimmedMuons"),
                                   electrons = cms.InputTag("slimmedElectrons"),
                                   hltobj = cms.InputTag("hltEgammaHLTExtra", "", "MYHLT"),
                                   l1obj = cms.InputTag("hltGtStage2Digis", "EGamma", "MYHLT"),
    ebRecHits = cms.InputTag("reducedEgamma","reducedEBRecHits"),

#    eleHEEPId51Map = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV51"),
#    eleHEEPIdMap = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV60"),
#    eleVetoIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-veto"),
#    eleLooseIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-loose"),
#    eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-medium"),
#    eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-tight"),

#    eleVetoIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-veto"),
#    eleLooseIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-loose"),
#    eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-medium"),
#    eleTightIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-tight"),

#    eleHLTIdMap = cms.InputTag("egmGsfElectronIDs:cutBasedElectronHLTPreselection-Summer16-V1"), 
#    eleHEEPIdMap = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV70"),
                                   
#    eleMVAMediumIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Fall17-noIso-V1-wp90"),
#    eleMVATightIdMap  = cms.InputTag("egmGsfElectronIDs:mvaEleID-Fall17-noIso-V1-wp80"),
#    mvaValuesMap     = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Fall17NoIsoV1Values"),
#    mvaCategoriesMap = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Categories"),
    dupCluster          = cms.InputTag("particleFlowEGammaGSFixed:dupECALClusters"),
    hitsNotReplaced     = cms.InputTag("ecalMultiAndGSGlobalRecHitEB:hitsNotReplaced"),
    mets = cms.InputTag(METS),
    mets_EGclean = cms.InputTag(METS_EGclean),
    mets_MEGclean = cms.InputTag(METS_MEGclean),
    mets_uncorr = cms.InputTag(METS_uncorr),
    mets_puppi = cms.InputTag("slimmedMETsPuppi"),
    mets_mva = cms.InputTag("MVAMET","MVAMET"),
    corrMetPx = cms.string("+0.1166 + 0.0200*Nvtx"),
    corrMetPy = cms.string("+0.2764 - 0.1280*Nvtx"),
    jecAK4forMetCorr = cms.vstring( jecLevelsForMET ),
    jetsForMetCorr = cms.InputTag(jetsAK4),
    rho = cms.InputTag("fixedGridRhoFastjetAll"),
    genparticles = cms.InputTag("prunedGenParticles"),
    packedgenparticles = cms.InputTag("packedGenParticles"),
#    gentaus = cms.InputTag("tauGenJets"),
    PUInfo = cms.InputTag("slimmedAddPileupInfo"),
    genEventInfo = cms.InputTag("generator"),
    externallheProducer = cms.InputTag("externalLHEProducer"),
    HLT = cms.InputTag("TriggerResults","","HLT"),
    triggerobjects = cms.InputTag("slimmedPatTrigger"),
    triggerprescales = cms.InputTag("patTrigger"),
    noiseFilter = cms.InputTag('TriggerResults','', hltFiltersProcessName),
    jecpath = cms.string(''),
   
    
    ## Noise Filters ###################################
    # defined here: https://github.com/cms-sw/cmssw/blob/CMSSW_7_4_X/PhysicsTools/PatAlgos/python/slimming/metFilterPaths_cff.py
    noiseFilterSelection_HBHENoiseFilter = cms.string('Flag_HBHENoiseFilter'),   # both data and MC for 2018,
    noiseFilterSelection_HBHENoiseFilterLoose = cms.InputTag("HBHENoiseFilterResultProducer", "HBHENoiseFilterResultRun2Loose"),
    noiseFilterSelection_HBHENoiseFilterTight = cms.InputTag("HBHENoiseFilterResultProducer", "HBHENoiseFilterResultRun2Tight"),
    noiseFilterSelection_HBHENoiseIsoFilter = cms.InputTag("HBHENoiseFilterResultProducer", "HBHEIsoNoiseFilterResult"),    # both data and MC for 2018,  
    noiseFilterSelection_ecalBadCalibReducedMINIAODFilter = cms.InputTag("ecalBadCalibReducedMINIAODFilter"),  # both data and MC for 2018,
    noiseFilterSelection_CSCTightHaloFilter = cms.string('Flag_CSCTightHaloFilter'),
    noiseFilterSelection_CSCTightHalo2015Filter = cms.string('Flag_CSCTightHalo2015Filter'),
    noiseFilterSelection_hcalLaserEventFilter = cms.string('Flag_hcalLaserEventFilter'),
    noiseFilterSelection_EcalDeadCellTriggerPrimitiveFilter = cms.string('Flag_EcalDeadCellTriggerPrimitiveFilter'),  # both data and MC for 2018,
    noiseFilterSelection_goodVertices = cms.string('Flag_goodVertices'),  # both data and MC for 2018,
    noiseFilterSelection_trackingFailureFilter = cms.string('Flag_trackingFailureFilter'),
    noiseFilterSelection_eeBadScFilter = cms.string('Flag_eeBadScFilter'),
    noiseFilterSelection_ecalLaserCorrFilter = cms.string('Flag_ecalLaserCorrFilter'),
    noiseFilterSelection_trkPOGFilters = cms.string('Flag_trkPOGFilters'),
    
    #New for ICHEP 2016
    noiseFilterSelection_CSCTightHaloTrkMuUnvetoFilter = cms.string('Flag_CSCTightHaloTrkMuUnvetoFilter'),
    noiseFilterSelection_globalTightHalo2016Filter = cms.string('Flag_globalTightHalo2016Filter'),
    noiseFilterSelection_globalSuperTightHalo2016Filter = cms.string('Flag_globalSuperTightHalo2016Filter'), # both data and MC for 2018,  
    noiseFilterSelection_HcalStripHaloFilter = cms.string('Flag_HcalStripHaloFilter'),
    noiseFilterSelection_chargedHadronTrackResolutionFilter = cms.string('Flag_chargedHadronTrackResolutionFilter'),
    noiseFilterSelection_muonBadTrackFilter = cms.string('Flag_muonBadTrackFilter'),
    
    #New for Moriond
    noiseFilterSelection_badMuonsFilter = cms.string('Flag_BadPFMuonFilter'),    #('Flag_badMuons'),  # both data and MC for 2018, 
    noiseFilterSelection_duplicateMuonsFilter = cms.string('Flag_duplicateMuons'),
    noiseFilterSelection_nobadMuonsFilter = cms.string('Flag_nobadMuons'),

    # and the sub-filters
    noiseFilterSelection_trkPOG_manystripclus53X = cms.string('Flag_trkPOG_manystripclus53X'),
    noiseFilterSelection_trkPOG_toomanystripclus53X = cms.string('Flag_trkPOG_toomanystripclus53X'),
    noiseFilterSelection_trkPOG_logErrorTooManyClusters = cms.string('Flag_trkPOG_logErrorTooManyClusters'),
    # summary
    noiseFilterSelection_metFilters = cms.string('Flag_METFilters'),

                                   packedpfcandidates = cms.InputTag('packedPFCandidates'),
    SecondaryVertices = cms.InputTag('slimmedSecondaryVertices'),
#    losttrack = cms.InputTag('lostTracks')
)

process.load('RecoMET.METFilters.ecalBadCalibFilter_cfi')

baddetEcallist = cms.vuint32(
    [872439604,872422825,872420274,872423218,
     872423215,872416066,872435036,872439336,
     872420273,872436907,872420147,872439731,
     872436657,872420397,872439732,872439339,
     872439603,872422436,872439861,872437051,
     872437052,872420649,872422436,872421950,
     872437185,872422564,872421566,872421695,
     872421955,872421567,872437184,872421951,
     872421694,872437056,872437057,872437313])


process.ecalBadCalibReducedMINIAODFilter = cms.EDFilter(
    "EcalBadCalibFilter",
    EcalRecHitSource = cms.InputTag("reducedEgamma:reducedEERecHits"),
    ecalMinEt        = cms.double(50.),
    baddetEcal    = baddetEcallist, 
    taggingMode = cms.bool(True),
    debug = cms.bool(True)#False
    )




process.TransientTrackBuilderESProducer = cms.ESProducer("TransientTrackBuilderESProducer",
    ComponentName = cms.string('TransientTrackBuilder')
)


####### Final path ##########
process.p = cms.Path()

#process.p += process.ecalBadCalibReducedMINIAODFilter

#if config["RUNONMC"]:
#  process.load("PhysicsTools.JetMCAlgos.TauGenJets_cfi")
#  process.tauGenJets.GenParticles = cms.InputTag('prunedGenParticles')
#  process.p += process.tauGenJets

process.nano = cms.EDAnalyzer('NanoAnalyzer',
                              isData = cms.bool(True)
)

process.p = cms.Path(process.nano)


#process.p += process.ntuplizer
#process.p.associate(pattask)

#print(pattask)

#  LocalWords:  tauIdMVAIsoDBoldDMwLT
