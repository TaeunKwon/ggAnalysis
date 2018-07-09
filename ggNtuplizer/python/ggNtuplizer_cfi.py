import FWCore.ParameterSet.Config as cms
from HiggsAnalysis.HiggsTo2photons.hggPhotonIDCuts_cfi import *
#from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector
#from CMGTools.External.pujetidproducer_cfi import stdalgos, chsalgos

ggNtuplizer = cms.EDAnalyzer("ggNtuplizer",
                             hggPhotonIDConfiguration = hggPhotonIDCuts,
                             doGenParticles       = cms.bool(False),
                             runOnParticleGun     = cms.bool(False),
                             runOnSherpa          = cms.bool(False),
                             dumpPhotons          = cms.bool(False), 
                             dumpJets             = cms.bool(False),
                             dumpSubJets          = cms.bool(False),
                             dumpTaus             = cms.bool(False),
                             dumpPDFSystWeight    = cms.bool(False),
                             isAOD                = cms.bool(True), #### actually configured through run_data_74x.py
                             runHFElectrons       = cms.bool(False),
                             development          = cms.bool(False),
                             addFilterInfoAOD     = cms.bool(False),
                             addFilterInfoMINIAOD = cms.bool(False),
                             doNoHFMET            = cms.bool(False),
                             separateVtxFit       = cms.bool(False),

                             trgFilterDeltaPtCut  = cms.double(0.5),
                             trgFilterDeltaRCut   = cms.double(0.3),

                             triggerEvent         = cms.InputTag("hltTriggerSummaryAOD", "", "HLT"),
                             #triggerEvent         = cms.InputTag("selectedPatTrigger", "", ""),
                             triggerResults       = cms.InputTag("TriggerResults", "", "HLT"),
                             patTriggerResults    = cms.InputTag("TriggerResults", "", "PAT"),
                             #patTriggerResults    = cms.InputTag("TriggerResults", "", "RECO"),
                             genParticleSrc       = cms.InputTag("genParticles"),
                             generatorLabel       = cms.InputTag("generator"),
                             LHEEventLabel        = cms.InputTag("externalLHEProducer"),
                             newParticles         = cms.vint32(1000006, 1000021, 1000022, 1000024, 1000025, 1000039, 3000001, 3000002, 35),
                             pileupCollection     = cms.InputTag("addPileupInfo"),
                             VtxLabel             = cms.InputTag("offlinePrimaryVertices"),
                             VtxBSLabel           = cms.InputTag("offlinePrimaryVerticesWithBS"),
                             rhoLabel             = cms.InputTag("fixedGridRhoFastjetAll"),
                             rhoCentralLabel      = cms.InputTag("fixedGridRhoFastjetCentralNeutral"),
                             pfMETLabel           = cms.InputTag("patMETs"),
                             electronSrc          = cms.InputTag("selectedPatElectrons"),
                             #calibelectronSrc     = cms.InputTag("calibratedPatElectrons"),
                             calibelectronSrc     = cms.InputTag("selectedPatElectrons"),
                             photonSrc            = cms.InputTag("selectedPatPhotons"),
                             #calibphotonSrc       = cms.InputTag("calibratedPatPhotons"),
                             calibphotonSrc       = cms.InputTag("selectedPatPhotons"),
                             muonSrc              = cms.InputTag("selectedPatMuons"),
                             gsfTrackSrc          = cms.InputTag("electronGsfTracks"),
                             ebReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsEB"),
                             eeReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsEE"),
                             esReducedRecHitCollection = cms.InputTag("reducedEcalRecHitsES"),
                             recoPhotonSrc             = cms.InputTag("reducedEgamma", "reducedGedPhotonCores"),
                             TrackLabel                = cms.InputTag("generalTracks"),
                             gsfElectronLabel          = cms.InputTag("gsfElectrons"),
                             PFAllCandidates           = cms.InputTag("particleFlow"),
                             #ak4JetSrc                 = cms.InputTag("updatedJets"),
                             #ak4JetSrc                 = cms.InputTag("slimmedJets"),
                             ak4JetSrc                 = cms.InputTag("patJets"),

                             #ak4JetSrc                 = cms.InputTag("selectedUpdatedPatJetsUpdatedJEC"),
                             ak8JetSrc                 = cms.InputTag("slimmedJetsAK8"),
                             #ak8JetSrc                 = cms.InputTag("selectedUpdatedPatJetsUpdatedJECAK8"),
                             #boostedDoubleSVLabel      = cms.InputTag("pfBoostedDoubleSecondaryVertexAK8BJetTags"),
                             tauSrc                    = cms.InputTag("selectedPatTaus"),
                             #pfLooseId                 = pfJetIDSelector.clone(),

                             phoLooseIdMap   = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Fall17-94X-V1-loose"),
                             phoMediumIdMap  = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Fall17-94X-V1-medium"),
                             phoTightIdMap   = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Fall17-94X-V1-tight"),
                             phoMVAValuesMap = cms.InputTag("photonMVAValueMapProducer:PhotonMVAEstimatorRunIIFall17v1Values"),
                             phoChargedIsolation       = cms.InputTag("photonIDValueMapProducer:phoChargedIsolation"),
                             phoNeutralHadronIsolation = cms.InputTag("photonIDValueMapProducer:phoNeutralHadronIsolation"),
                             phoPhotonIsolation        = cms.InputTag("photonIDValueMapProducer:phoPhotonIsolation"),
                             phoWorstChargedIsolation  = cms.InputTag("photonIDValueMapProducer:phoWorstChargedIsolation"),
                             phoChargedIsolation_CITK        = cms.InputTag("egmPhotonIsolationMiniAOD:h+-DR030-"),
                             phoPhotonIsolation_CITK         = cms.InputTag("egmPhotonIsolationMiniAOD:gamma-DR030-"),
                             phoNeutralHadronIsolation_CITK  = cms.InputTag("egmPhotonIsolationMiniAOD:h0-DR030-"),
                             #packedPFCands   = cms.InputTag("packedPFCandidates"),
                             packedPFCands   = cms.InputTag("particleFlow::RECO"),

                             eleVetoIdMap    = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-veto"),
                             eleLooseIdMap   = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-loose"),
                             eleMediumIdMap  = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-medium"),
                             eleTightIdMap   = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Fall17-94X-V1-tight"),
                             eleHEEPIdMap    = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV70"),
                             eleMVAIsoValuesMap   = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Fall17IsoV1Values"),
                             eleMVANoIsoValuesMap = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Fall17NoIsoV1Values"),
                             elePFClusEcalIsoProducer = cms.InputTag("electronEcalPFClusterIsolationProducer"),
                             elePFClusHcalIsoProducer = cms.InputTag("electronHcalPFClusterIsolationProducer"),
                             BadChargedCandidateFilter = cms.InputTag("BadChargedCandidateFilter"),
                             BadPFMuonFilter           = cms.InputTag("BadPFMuonFilter")
)
