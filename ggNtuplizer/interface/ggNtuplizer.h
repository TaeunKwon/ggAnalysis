#ifndef ggNtuplizer_h
#define ggNtuplizer_h

#include "TTree.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
//#include "EgammaAnalysis/ElectronTools/interface/EnergyScaleCorrection_class.h"
#include "HiggsAnalysis/HiggsTo2photons/interface/CiCPhotonID.h"
#include "JetMETCorrections/Modules/interface/JetResolution.h"
//#include "PhysicsTools/SelectorUtils/interface/PFJetIDSelectionFunctor.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"

#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/TransientTrack/interface/GsfTransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "MagneticField/ParametrizedEngine/src/OAEParametrizedMagneticField.h"

#include "DataFormats/TrackReco/interface/DeDxData.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "RecoVertex/VertexTools/interface/VertexDistance3D.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"

using namespace std;

void setbit(UShort_t& x, UShort_t bit);

class ggNtuplizer : public edm::EDAnalyzer {
 public:

  explicit ggNtuplizer(const edm::ParameterSet&);
  ~ggNtuplizer();
  
  //   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
 private:
  
  //   virtual void beginJob() {};
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  //   virtual void endJob() {};
  
  void initTriggerFilters(const edm::Event&);
  ULong64_t matchSingleElectronTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchDoubleElectronTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchSinglePhotonTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchDoublePhotonTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchTriplePhotonTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchMuonTriggerFilters(double pt, double eta, double phi);
  vector<bool> muonTriggerMap(const edm::Event&);
  ULong64_t matchJetTriggerFilters(double pt, double eta, double phi);
  ULong64_t matchL1TriggerFilters(double pt, double eta, double phi);
  Double_t deltaPhi(Double_t phi1, Double_t phi2);
  Double_t deltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);
  Double_t getMiniIsolation(edm::Handle<pat::PackedCandidateCollection> pfcands, const reco::Candidate* ptcl,  
			    double r_iso_min, double r_iso_max, double kt_scale, bool charged_only);
  bool isAncestor(const reco::Candidate* ancestor, const reco::Candidate* particle);

  void branchesGlobalEvent(TTree*);
  void branchesTriggers   (TTree*);
  void branchesGenInfo    (TTree*, edm::Service<TFileService>&);
  void branchesGenPart    (TTree*);
  void branchesMatchGenParticles    (TTree*);
  void branchesMET        (TTree*);
  void branchesPhotons    (TTree*);
  void branchesPFPhotons  (TTree*);
  void branchesElectrons  (TTree*);
  void branchesHadrons    (TTree*);
  void branchesHFElectrons(TTree*);
  void branchesMuons      (TTree*);
  void branchesTaus       (TTree*);
  void branchesJets       (TTree*);
  void branchesLowPtElectrons(TTree*);
  void branchesMixElectrons(TTree*);

  void fillGlobalEvent(const edm::Event&, const edm::EventSetup&);
  void fillGenInfo    (const edm::Event&);
  void fillGenPart    (const edm::Event&);
  void fillMatchGenParticles  (const edm::Event&, const edm::EventSetup&, math::XYZPoint&, const reco::Vertex);
  void fillMET        (const edm::Event&, const edm::EventSetup&);
  void fillPhotons    (const edm::Event&, const edm::EventSetup&);
  void fillPFPhotons  (const edm::Event&, const edm::EventSetup&);
  void fillElectrons  (const edm::Event&, const edm::EventSetup&, math::XYZPoint&, const reco::Vertex);
  void fillHadrons    (const edm::Event&, const edm::EventSetup&, math::XYZPoint&);
  void fillHFElectrons(const edm::Event&);
  void fillMuons      (const edm::Event&, math::XYZPoint&, const reco::Vertex);
  void fillTaus       (const edm::Event&);
  void fillJets       (const edm::Event&, const edm::EventSetup&);
  void fillLowPtElectrons(const edm::Event&, const edm::EventSetup&, math::XYZPoint&, const reco::Vertex);
  void fillMixElectrons(const edm::Event&, const edm::EventSetup&, math::XYZPoint&, const reco::Vertex);
  const reco::TransientTrack getTransientTrack(const reco::Track& track);
  const reco::TransientTrack getTransientTrack(const reco::GsfTrack& track);
  OAEParametrizedMagneticField *paramField = new OAEParametrizedMagneticField("3_8T"); 

  void cleanupPhotons();

  bool development_;
  bool separateVtxFit_;
  bool addFilterInfoAOD_;  
  bool addFilterInfoMINIAOD_;  
  bool doNoHFMET_;
  bool doGenParticles_;
  bool runOnParticleGun_;
  bool runOnSherpa_;
  bool dumpPhotons_;
  bool dumpTaus_;
  bool dumpJets_;
  bool dumpSubJets_;
  bool dumpSoftDrop_;
  bool dumpPDFSystWeight_;

  bool isAOD_;
  bool runHFElectrons_;
  bool dumpElectrons_;
  bool dumpMuons_;
  bool dumpLowPtElectrons_;

  vector<int> newparticles_;

  double trgFilterDeltaPtCut_;
  double trgFilterDeltaRCut_;

  edm::EDGetTokenT<reco::VertexCollection>         vtxLabel_;
  edm::EDGetTokenT<reco::VertexCollection>         vtxBSLabel_;
  edm::EDGetTokenT<double>                         rhoLabel_;
  edm::EDGetTokenT<double>                         rhoCentralLabel_;
  edm::EDGetTokenT<trigger::TriggerEvent>          trgEventLabel_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerObjectsLabel_;
  edm::EDGetTokenT<edm::TriggerResults>            trgResultsLabel_;
  string                                           trgResultsProcess_;
  edm::EDGetTokenT<edm::TriggerResults>            patTrgResultsLabel_;
  edm::EDGetTokenT<GenEventInfoProduct>            generatorLabel_;
  edm::EDGetTokenT<LHEEventProduct>                lheEventLabel_;
  edm::EDGetTokenT<vector<PileupSummaryInfo> >     puCollection_;
  edm::EDGetTokenT<vector<reco::GenParticle> >     genParticlesCollection_;
  edm::EDGetTokenT<edm::View<pat::MET> >           pfMETlabel_;
  edm::EDGetTokenT<edm::View<pat::Electron> >      electronCollection_;
  edm::EDGetTokenT<edm::View<pat::Electron> >      calibelectronCollection_;
  edm::EDGetTokenT<edm::View<pat::Photon> >        photonCollection_;
  edm::EDGetTokenT<edm::View<pat::Photon> >        calibphotonCollection_;
  edm::EDGetTokenT<edm::View<pat::Muon> >          muonCollection_;
  edm::EDGetTokenT<vector<pat::Tau> >              tauCollection_;
  edm::EDGetTokenT<EcalRecHitCollection>           ebReducedRecHitCollection_;
  edm::EDGetTokenT<EcalRecHitCollection>           eeReducedRecHitCollection_;
  edm::EDGetTokenT<EcalRecHitCollection>           esReducedRecHitCollection_; 
  edm::EDGetTokenT<reco::PhotonCollection>         recophotonCollection_;
  edm::EDGetTokenT<reco::TrackCollection>          tracklabel_;
  edm::EDGetTokenT<reco::GsfElectronCollection>    gsfElectronlabel_;
  edm::EDGetTokenT<edm::View<reco::GsfTrack> >     gsfTracks_;
  edm::EDGetTokenT<reco::PFCandidateCollection>    pfAllParticles_;
  edm::EDGetTokenT<vector<pat::PackedCandidate> >  pckPFCdsLabel_;
  edm::EDGetTokenT<edm::View<reco::Candidate> >    recoCdsLabel_;
  edm::EDGetTokenT<edm::View<pat::Jet> >           jetsAK4Label_;
  edm::EDGetTokenT<edm::View<pat::Jet> >           jetsAK8Label_;
  edm::EDGetTokenT<reco::JetTagCollection>         boostedDoubleSVLabel_;
  edm::EDGetTokenT<pat::PackedCandidateCollection> pckPFCandidateCollection_;
  edm::EDGetTokenT<pat::PackedCandidateCollection> lostTracksLabel_;
  edm::EDGetTokenT<edm::View<pat::PackedGenParticle> >packedGenParticlesCollection_;

  // for MET filters
  edm::EDGetTokenT<bool> BadChCandFilterToken_;
  edm::EDGetTokenT<bool> BadPFMuonFilterToken_;

  ///Photon ID in VID framework - 11th May, 2015
  // photon ID decision objects and isolations
  edm::EDGetTokenT<edm::ValueMap<bool> >  phoLooseIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >  phoMediumIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >  phoTightIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<float> > phoMVAValuesMapToken_;
  edm::EDGetTokenT<edm::ValueMap<float> > phoChargedIsolationToken_; 
  edm::EDGetTokenT<edm::ValueMap<float> > phoNeutralHadronIsolationToken_; 
  edm::EDGetTokenT<edm::ValueMap<float> > phoPhotonIsolationToken_; 
  edm::EDGetTokenT<edm::ValueMap<float> > phoWorstChargedIsolationToken_; 
  edm::EDGetTokenT<edm::ValueMap<float> > phoChargedIsolationToken_CITK_;
  edm::EDGetTokenT<edm::ValueMap<float> > phoNeutralHadronIsolationToken_CITK_;
  edm::EDGetTokenT<edm::ValueMap<float> > phoPhotonIsolationToken_CITK_;

  // elecontr ID decisions objects
  edm::EDGetTokenT<edm::ValueMap<bool> >  eleVetoIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >  eleLooseIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >  eleMediumIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >  eleTightIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<bool> >  eleHEEPIdMapToken_;
  edm::EDGetTokenT<edm::ValueMap<float> > eleMVAIsoValuesMapToken_;
  edm::EDGetTokenT<edm::ValueMap<float> > eleMVANoIsoValuesMapToken_;
  edm::EDGetTokenT<edm::ValueMap<float> > elePFClusEcalIsoToken_;
  edm::EDGetTokenT<edm::ValueMap<float> > elePFClusHcalIsoToken_;
  edm::EDGetTokenT<reco::PFCandidateCollection> pfCandidateCollection_;

  //check
  edm::EDGetToken gsfEle_;
  edm::EDGetTokenT< std::vector<std::pair<edm::Ptr<pat::Electron>, reco::Track>> > tok_eleTtk_;
  edm::EDGetTokenT< reco::DeDxDataValueMap > deDxProducer_;  
  edm::EDGetToken lowpTelectronlabel_;
  edm::EDGetTokenT<edm::ValueMap<float> > eleBWPToken_;
  edm::EDGetTokenT<edm::ValueMap<float> > eleUnBWPToken_;
  edm::EDGetTokenT<reco::ConversionCollection> conversionsToken_;

  string processName_;
  HLTConfigProvider hltConfig_;

  TTree   *tree_;
  TH1F    *hEvents_;
  TH1F    *hPU_;
  TH1F    *hPUTrue_;
  TH1F    *hGenWeight_;
  TH1F    *hSumGenWeight_;
  TH1F    *htrgMudpT_;
  TH1F    *htrgMudR_;

  CiCPhotonID                 *cicPhotonId_;
  //EnergyScaleCorrection_class *egmScaler_;

  JME::JetResolution            jetResolution_;
  JME::JetResolutionScaleFactor jetResolutionSF_;
  JME::JetResolution            AK8jetResolution_;
  JME::JetResolutionScaleFactor AK8jetResolutionSF_;

  //PFJetIDSelectionFunctor pfLooseId_;
  //boost::shared_ptr<FactorizedJetCorrector> jecAK8_;
  //boost::shared_ptr<FactorizedJetCorrector> jecAK8pSD_;
  //std::vector<std::string> jecAK8PayloadNames_;
  HLTPrescaleProvider hltPrescaleProvider_;
};

#endif
