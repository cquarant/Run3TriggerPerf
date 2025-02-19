#define GCC_VERSION ( 10000 * __GNUC__ + 100 * __GNUC_MINOR__ + __GNUC_PATCHLEVEL__ )
// for ultra-legacy AOD (10_6_4 or higher)
#if GCC_VERSION > 70400
// this one comes on top of the previous
#define CMSSW106plus
#endif
#if GCC_VERSION > 80300
// for Run 3 MC studies
// this one comes on top of the previous
// GCC_VERSION preliminary, might need to be changed/sharpened
#define CMSSW11plus
#endif
#if GCC_VERSION > 90299
// for 2021 pilot data 
// this one comes on top of the previous
#define CMSSW12plus
#endif

// system include files
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include "Math/VectorUtil.h"

// Root
#include "TMath.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"

// Utilities
#include "../interface/helperfunc.h"
#include "../interface/MyStruct.h"


//*****************************
// general user include files *
//*****************************
#include "FWCore/Framework/interface/Frameworkfwd.h"
#ifndef CMSSW12plus
// Run 1 and 2
#include "FWCore/Framework/interface/EDAnalyzer.h"
#else
// Run 3
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#endif

// FWCore
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"

// ------ EXTRA HEADER FILES--------------------//
#include "FWCore/Framework/interface/EventSetup.h"
#ifndef CMSSW12plus
#include "FWCore/Framework/interface/ESHandle.h"
#endif

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/Math/interface/deltaR.h"

//**************************
// for trigger information *
//**************************
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/L1Trigger/interface/BXVector.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"

//***************************
// for tracking information *
//***************************
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"

//*************************
// for vertex information *
//*************************
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include <DataFormats/VertexReco/interface/Vertex.h>
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

//***********************
// for electron information *
//***********************
#include "DataFormats/PatCandidates/interface/Electron.h"

//*******************************
// for gen particle information *
//*******************************
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

// set namespaces
using namespace edm;
using namespace reco;
using namespace std;


//***********************************
// main analyzer class (EDAnalyzer) *
//***********************************

#ifndef CMSSW12plus
// Run 1 and 2
class NanoAnalyzerDoubleEle : public edm::EDAnalyzer
#else
// Run 3
class NanoAnalyzerDoubleEle : public edm::one::EDAnalyzer<>
#endif
{
public:
  explicit NanoAnalyzerDoubleEle(const edm::ParameterSet&);
  ~NanoAnalyzerDoubleEle();

  static void fillDescriptions(edm::ConfigurationDescriptions & descriptions);

private:

  virtual void beginJob(const edm::ParameterSet& iConfig);
  virtual void beginRun(const edm::Run &iRun, const edm::EventSetup &iStp);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void endJob();

  void createBranch();

  void reset();

  const edm::ESGetToken<MagneticField, IdealMagneticFieldRecord> bFieldToken_;
  EDGetTokenT<reco::VertexCollection> verticeToken_;
  EDGetTokenT<pat::ElectronCollection> electronToken_;
  EDGetTokenT<edm::TriggerResults> triggerToken_;  
  EDGetTokenT<pat::TriggerObjectStandAloneCollection> triggerobjectToken_;
  edm::EDGetTokenT<l1t::EGammaBxCollection> l1EG_;      

  Handle<pat::ElectronCollection> electrons_;
  Handle< reco::VertexCollection > vertices_;
  Handle< edm::TriggerResults> HLTtriggers_;
  Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;



/////////////////////////////////////////////////////////////////////////
////////////////////////// declare tree, file, //////////////////////////
/////////////////////////////////////////////////////////////////////////
  
  edm::Service<TFileService> fs;
  TTree* tree_;

  /// original nanos
  UInt_t run;
  ULong64_t event;
  UInt_t luminosityBlock;
  int nvtx;

  float  Jpsi_e1_pt;
  float  Jpsi_e1_eta;
  float  Jpsi_e1_phi;
  float  Jpsi_e1_mass;
  int    Jpsi_e1_q;   
  float  Jpsi_e1_isElectron;   
  float  Jpsi_e1_passMVA;   
  // 
  float  Jpsi_e1_bestL1pt;
  float  Jpsi_e1_bestL1eta;
  float  Jpsi_e1_bestL1phi;
  float  Jpsi_e1_bestL1dR;
  //
  //
  float  Jpsi_e2_pt      ;
  float  Jpsi_e2_eta     ;
  float  Jpsi_e2_phi     ;
  float  Jpsi_e2_mass     ;
  int    Jpsi_e2_alsotag ;
  int    Jpsi_e2_q   ;   
  float  Jpsi_e2_isElectron;     
  float  Jpsi_e2_passMVA  ;
  // 
  float  Jpsi_e2_bestL1pt ;
  float  Jpsi_e2_bestL1eta ;
  float  Jpsi_e2_bestL1phi ;
  float  Jpsi_e2_bestL1dR ;
  //
  //
  float  Jpsi_e1_trgobj_pt      ;
  float  Jpsi_e1_trgobj_eta     ;
  float  Jpsi_e1_trgobj_phi     ;
  float  Jpsi_e1_trgobj_mass     ;
  int    Jpsi_e1_trgobj_q      ;   
  float  Jpsi_e1_trgobj_dR      ;
  // 
  float  Jpsi_e2_trgobj_pt ;
  float  Jpsi_e2_trgobj_eta ;
  float  Jpsi_e2_trgobj_phi ;
  float  Jpsi_e2_trgobj_mass ;
  int    Jpsi_e2_trgobj_q ;   
  float  Jpsi_e2_trgobj_dR ;
  //
  //
  int SingleEle_fired=0;
  std::vector<int> DoubleEle_fired{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  
  std::vector<int> ele1_matchedDiEle{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<int> ele2_matchedDiEle{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  std::vector<float> ele1_matchedDiEle_pt{-999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999.};
  std::vector<float> ele2_matchedDiEle_pt{-999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999.};
  std::vector<float> ele1_matchedDiEle_eta{-999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999.};
  std::vector<float> ele2_matchedDiEle_eta{-999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999.};
  std::vector<float> ele1_matchedDiEle_phi{-999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999.};
  std::vector<float> ele2_matchedDiEle_phi{-999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999., -999.};
  
  float ele1_matchedDiEle_dR  = 0;
  float ele2_matchedDiEle_dR  = 0;
  // float ele1_matchedDiEle_pt  = 0;
  // float ele2_matchedDiEle_pt  = 0;
  // float ele1_matchedDiEle_eta = 0;
  // float ele2_matchedDiEle_eta = 0;
  // float ele1_matchedDiEle_phi = 0;
  // float ele2_matchedDiEle_phi = 0;
  //
  //
  float  Jpsi_fit_pt;
  float  Jpsi_nonfit_pt;
  float  Jpsi_fit_eta;
  float  Jpsi_nonfit_eta;
  float  Jpsi_fit_phi;
  float  Jpsi_nonfit_phi;
  float  Jpsi_fit_mass;
  float  Jpsi_nonfit_mass;
  float  Jpsi_fit_vprob;
  float  Jpsi_electronsDr;


  // Not for tree, other variables declaration
  helperfunc aux;
  float chi = 0.;
  float ndf = 0.;

  TH1F * hist; 

}; // end of class member


NanoAnalyzerDoubleEle::NanoAnalyzerDoubleEle(const edm::ParameterSet& iConfig): 
  bFieldToken_(esConsumes<MagneticField, IdealMagneticFieldRecord>())
{
  electronToken_           = consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"));

  verticeToken_       = consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertices"));

  triggerToken_	      = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("HLT"));
  triggerobjectToken_ = consumes<pat::TriggerObjectStandAloneCollection>(iConfig.getParameter<edm::InputTag>("triggerobjects"));

  l1EG_               = consumes<l1t::EGammaBxCollection>(iConfig.getParameter<edm::InputTag>("l1EG"));

  
  hist = fs->make<TH1F>("cutflow", "cutflow", 10,0,10);
  tree_ = fs->make<TTree>( "tree", "tree" );

  createBranch();
} // end of constructor


NanoAnalyzerDoubleEle::~NanoAnalyzerDoubleEle() { }

void NanoAnalyzerDoubleEle::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  reset();

  const auto& bField = iSetup.getData(bFieldToken_);

  iEvent.getByToken(verticeToken_, vertices_ );
  iEvent.getByToken(triggerToken_, HLTtriggers_);
  iEvent.getByToken(triggerobjectToken_ , triggerObjects); 

  nvtx = vertices_->size();

  run = (iEvent.id()).run();
  event = (iEvent.id()).event();
  luminosityBlock = (iEvent.id()).luminosityBlock();

  // check if the reference trigger and/or the analysis trigger fired
  bool isTriggered = false;
  const edm::TriggerNames& trigNames = iEvent.triggerNames(*HLTtriggers_);
  std::string refTriggerName="";    
  std::string finalTriggerName="";  

  // pT thresholds for di-ele trigger
  std::vector<std::string> pt_thr_v_string{"10", "9p5", "9", "8p5", "8", "7p5", "7", "6p5", "6", "5p5", "5", "4p5", "4"};

  // Loop over HLT paths to check if the reference and doubleEle path fired
  for (unsigned int i = 0, n = HLTtriggers_->size(); i < n; ++i) {

    // std::cout << "Loop over all triggers: i = " << i << ", name = " << trigNames.triggerName(i) << ", fired = " << HLTtriggers_->accept(i) << std::endl;
    
    // Check if the reference trigger path fired
    if(trigNames.triggerName(i).find("HLT_SingleEle8_SingleEGL1_v")!= std::string::npos){             // chiara
      if(HLTtriggers_->accept(i)){
        isTriggered = true;
        refTriggerName = trigNames.triggerName(i);  
        SingleEle_fired = 1;
        // std::cout << "Loop over all triggers: i = " << i << ", name = " << trigNames.triggerName(i) << ", fired = " << HLTtriggers_->accept(i) << std::endl;
      }
    }
    
    // Check if any of the di-ele trigger paths fired
    for(int j=0; j<int(pt_thr_v_string.size()); j++){
      std::string pt_thr_string = pt_thr_v_string[j];
      std::string DoubleEleTrigName = "HLT_DoubleEle"+pt_thr_string+"_eta1p22_mMax6";
      if(trigNames.triggerName(i).find(DoubleEleTrigName)!= std::string::npos){
	      if(HLTtriggers_->accept(i)){
	        DoubleEle_fired[j]=1;
	        // std::cout << "Event = " << event << " : DoubleEle_fired[j] fired for j = " << j << std::endl;
	      }
      }
    }
  }

  /*
  std::cout << std::endl;
  std::cout << "Ref trigger? " << isTriggered << std::endl;
  std::cout << "finalTriggerName = " << finalTriggerName << std::endl;
  std::cout << std::endl;
  */

  // Our reference path fired
  if(!isTriggered) return;    
  hist->Fill(0);

  // Take the electrons collection
  iEvent.getByToken(electronToken_ , electrons_    );

  // Output collections
  std::vector<pat::Electron> electroncollection;                  // collection with offline electrons passing minimal selection
  std::vector<pat::TriggerObjectStandAlone> trg_obj_collection;   // collection with HLT candidate with best match with offline electrons
                                                                  // (passing matching criteria) - at most one per electron
  std::vector<int> electronmatched;                               // integer with the position in the trg_obj_collection of the HLT object matched to electron
  // 
  electroncollection.clear();
  trg_obj_collection.clear();
  electronmatched.clear();

  // std::cout << "event = " << event << ", electrons_->size() = " << electrons_->size() << std::endl;

  // Loop over offline electrons + matching with reference trigger
  for(size_t ielectron = 0; ielectron < electrons_->size(); ielectron++){
    const pat::Electron & electron = (*electrons_)[ielectron];

    // std::cout << "Offline: " << electron.pt() << " " << electron.eta() << " " << electron.phi() << std::endl;

    // Offline cuts
    if(electron.pt() < 2.5) continue;
    hist->Fill(1);
    if(fabs(electron.eta()) > 2.4) continue;
    hist->Fill(2);
    if(!(electron.gsfTrack().isNonnull())) continue;
    hist->Fill(3);
    // const reco::GsfTrackRef gsfTrk = electron.gsfTrack();
    // if(!gsfTrk.isNonnull()) continue;
    
    // std::cout << "event = " << event << ", ielectron = " << ielectron << ", electron.pt() =  " << electron.pt() << std::endl;

    // Trigger matching
    bool trigObjMatchEle = false;                      // this offline electron matches a HLT ele-candidate
    pat::TriggerObjectStandAlone best_match_obj;      // this offline electron matches a HLT ele-candidate and this is the best matched candidate
    Float_t best_match_dR = 9999999;                  // this offline electron matches a HLT ele-candidate and this is the best match DR

    // Loop over trigger objects matching the reference path
    for (pat::TriggerObjectStandAlone obj : *triggerObjects) {
      
      // consider only objects which match the ref path    
      obj.unpackPathNames(trigNames);
      obj.unpackFilterLabels(iEvent, *HLTtriggers_);
      std::vector<std::string> pathNamesAll  = obj.pathNames(false);
      bool isPathExist = false;
      for (unsigned h = 0, n = pathNamesAll.size(); h < n; ++h) {
	      if(pathNamesAll[h]==refTriggerName) isPathExist = true;     
      }
      if(!isPathExist) continue;
      
      int eleObjNumber = -1;
      for (unsigned hh = 0; hh < obj.filterLabels().size(); ++hh){	
        if(obj.filterLabels()[hh].find("hltSingleEle8SingleEGL1ValidHitsFilter") != std::string::npos) {  // chiara  HLT_Ele8
          eleObjNumber = hh;
        }
      }
        
      // here HLT obj vs reco electron candidates
      TVector3 eleTV3, objTV3;
      eleTV3.SetPtEtaPhi( electron.pt(), electron.eta(), electron.phi() );
      objTV3.SetPtEtaPhi( obj.pt(), obj.eta(), obj.phi() );
      Float_t deltaR = fabs(eleTV3.DeltaR(objTV3));
    
      // here HLT-electron candidates
      if (eleObjNumber>=0) {
        if(deltaR < 0.3){    // chiara
          trigObjMatchEle = true;
          if (deltaR < best_match_dR){
            best_match_dR = deltaR;
            best_match_obj = obj;
          }
        }
      }

    } // Loop over trigger object
    
    // This is to further process 
    electroncollection.push_back(electron);
    if(trigObjMatchEle){ 
      trg_obj_collection.push_back(best_match_obj);
      electronmatched.push_back(int(trg_obj_collection.size())-1);
    }
    else{
      electronmatched.push_back(-999);	
    }

  } // Loop over offline electrons
  
  if (electroncollection.size() < 2) return; 
  hist->Fill(4);

  // NB: electroncollection and electronmatched elest have the same size
  if (electroncollection.size() != electronmatched.size() ) return;
  hist->Fill(5);

  // Prepare offline electron pairs
  float jpsi_max_pt = -1;
  int mcidx_e1 = -1;
  int mcidx_e2 = -1;
  int mcidx_trgobj1 = -1;
  int mcidx_trgobj2 = -1;
  TLorentzVector jpsi_tlv_highest;

  for(int ie = 0; ie < (int)electroncollection.size(); ie++){
    for(int je = ie+1; je < (int)electroncollection.size(); je++){
      
      // at least 1 electron of the jpsi pair should match a trigger electron
      if ( electronmatched[ie]<0 && electronmatched[je]<0 ) continue;
      
      // match with trigger electron
      int this_mcidx_trgobj1 = -1;
      int this_mcidx_trgobj2 = -1;
      if (electronmatched[ie]>-999){
        this_mcidx_trgobj1 = electronmatched[ie];
      }
      if (electronmatched[je]>-999){
        this_mcidx_trgobj2 = electronmatched[je];
      }
      
      const pat::Electron ele1 = electroncollection[ie];
      const pat::Electron ele2 = electroncollection[je];

      /*
      std::cout << "Ele1 " << ie << ", pt = " << ele1.pt() << ", eta = " << ele1.eta() << ", phi = " << ele1.phi() << ", id = " << ele1.pdgId() << std::endl;
      
      if (this_mcidx_trgobj1>=0) std::cout << "TrgObj1 pt = " << trg_obj_collection[this_mcidx_trgobj1].pt() << ", eta = " << trg_obj_collection[this_mcidx_trgobj1].eta() << ", phi = " << trg_obj_collection[this_mcidx_trgobj1].phi() << std::endl; 
      else 
      std::cout << "TrgObj1 not found" << std::endl;
      
      std::cout << "Ele2 " << je << ", pt = " << ele2.pt() << ", eta = " << ele2.eta() << ", phi = " << ele2.phi() << ", id = " << ele2.pdgId() << std::endl;
      
      if (this_mcidx_trgobj2>=0) std::cout << "TrgObj2 pt = " << trg_obj_collection[this_mcidx_trgobj2].pt() << ", eta = " << trg_obj_collection[this_mcidx_trgobj2].eta() << ", phi = " << trg_obj_collection[this_mcidx_trgobj2].phi() << std::endl; 
      else 
      std::cout << "TrgObj2 not found" << std::endl;
      */

      TLorentzVector tlv_e1;
      TLorentzVector tlv_e2;
      tlv_e1.SetPtEtaPhiM(ele1.pt(), ele1.eta(), ele1.phi(), aux.mass_electron);
      tlv_e2.SetPtEtaPhiM(ele2.pt(), ele2.eta(), ele2.phi(), aux.mass_electron);

      TLorentzVector tlv_jpsi = (tlv_e1 + tlv_e2);
      float jpsi_mass = tlv_jpsi.M();
      float jpsi_pt = tlv_jpsi.Pt();

      if (ele1.charge() + ele2.charge() !=0) continue;
      if (jpsi_mass < 2.0) continue; 
      if (jpsi_mass > 4.0) continue;
      
      if(jpsi_max_pt < jpsi_pt){
        jpsi_max_pt = jpsi_pt;
        mcidx_e1 = ie;
        mcidx_e2 = je;
        mcidx_trgobj1 = this_mcidx_trgobj1;
        mcidx_trgobj2 = this_mcidx_trgobj2;
        jpsi_tlv_highest = tlv_jpsi;
      }
      // std::cout << "jpsi_mass = " << jpsi_mass << ", jpsi_max_pt = " << jpsi_max_pt << ", jpsi_pt = " << jpsi_pt << std::endl;      
      // std::cout << "event = " << event << "; In the loop: mcidx_e1 = " << mcidx_e1 << ", mcidx_e2 = " << mcidx_e2 << std::endl;
    }
  }

  // At least 1 reco J/psi
  if(jpsi_max_pt == -1) return;  
  hist->Fill(6);

  // Swap 1<->2 so that: 1 is always tag, 2 is always probe, and additional variable tells if 2 is also tag
  // if both are tags, then the tag is the one with higher pT at reco level
  int mcidx_tag = -99;
  int mcidx_pro = -99;
  int mcidx_trgobj_tag = -99;
  int mcidx_trgobj_pro = -99;
  int is_probe_also_tag = 0;

  if ((mcidx_trgobj1 >= 0) & (mcidx_trgobj2 >= 0)) {
    if (electroncollection[mcidx_e1].pt() >= electroncollection[mcidx_e2].pt()) {
      mcidx_tag = mcidx_e1;
      mcidx_trgobj_tag = mcidx_trgobj1;
      mcidx_pro = mcidx_e2;
      mcidx_trgobj_pro = mcidx_trgobj2;
    } else {
      mcidx_tag = mcidx_e2;
      mcidx_trgobj_tag = mcidx_trgobj2;
      mcidx_pro = mcidx_e1;
      mcidx_trgobj_pro = mcidx_trgobj1;
    }
    is_probe_also_tag = 1;
  } else if (mcidx_trgobj1 >= 0) {
    mcidx_tag = mcidx_e1;
    mcidx_trgobj_tag = mcidx_trgobj1;
    mcidx_pro = mcidx_e2;
    mcidx_trgobj_pro = mcidx_trgobj2;
  } else {
    mcidx_tag = mcidx_e2;
    mcidx_trgobj_tag = mcidx_trgobj2;
    mcidx_pro = mcidx_e1;
    mcidx_trgobj_pro = mcidx_trgobj1;
  }

  mcidx_e1 = mcidx_tag;
  mcidx_e2 = mcidx_pro;
  mcidx_trgobj1 = mcidx_trgobj_tag;
  mcidx_trgobj2 = mcidx_trgobj_pro;


  // Kinematic fit to offline electrons
  float reco_e1_pt  = electroncollection[mcidx_e1].pt(); 
  float reco_e1_eta = electroncollection[mcidx_e1].eta(); 
  float reco_e1_phi = electroncollection[mcidx_e1].phi(); 
  float reco_e2_pt  = electroncollection[mcidx_e2].pt(); 
  float reco_e2_eta = electroncollection[mcidx_e2].eta(); 
  float reco_e2_phi = electroncollection[mcidx_e2].phi(); 
  TVector3 ele1TV3, ele2TV3;
  ele1TV3.SetPtEtaPhi( reco_e1_pt, reco_e1_eta, reco_e1_phi );
  ele2TV3.SetPtEtaPhi( reco_e2_pt, reco_e2_eta, reco_e2_phi );

  // Kin fit
  const reco::TransientTrack electron1TT((*(electroncollection[mcidx_e1].bestTrack())),&bField);  
  const reco::TransientTrack electron2TT((*(electroncollection[mcidx_e2].bestTrack())),&bField);
  KinematicParticleFactoryFromTransientTrack pFactory;
  std::vector<RefCountedKinematicParticle> electronParticles;
  electronParticles.push_back(pFactory.particle(electron1TT, aux.electron_mass, chi, ndf, aux.electron_sigma));
  electronParticles.push_back(pFactory.particle(electron2TT, aux.electron_mass, chi, ndf, aux.electron_sigma));

  // Kinematic fit of the two electrons to a common vtx
  RefCountedKinematicParticle jpsi_part;
  RefCountedKinematicVertex jpsi_vertex;
  RefCountedKinematicTree jpTree;
  Bool_t jpsifit_flag;
  std::tie(jpsifit_flag, jpsi_part, jpsi_vertex, jpTree) = aux.KinematicFit(electronParticles, -1, -1);
  
  // Successfull kin fit
  if(!jpsifit_flag) return;
  hist->Fill(7);

  Jpsi_fit_pt    = jpsi_part->currentState().globalMomentum().perp();
  Jpsi_fit_eta   = jpsi_part->currentState().globalMomentum().eta();
  Jpsi_fit_phi   = jpsi_part->currentState().globalMomentum().phi();
  Jpsi_fit_mass  = jpsi_part->currentState().mass();
  Jpsi_fit_vprob = TMath::Prob(jpsi_part->chiSquared(), jpsi_part->degreesOfFreedom());


  // Match analysis HLT / offline
  // Match elepair at HLT / ele pair offline, when fired
  for(int j=0; j<int(pt_thr_v_string.size()); j++){
    if (DoubleEle_fired[j]==1) {   

      std::string pt_thr_string = pt_thr_v_string[j];
      std::string DoubleEleTrigName = "HLT_DoubleEle"+pt_thr_string+"_eta1p22_mMax6";
      std::string DoubleEleObjName  = "hltDoubleEle"+pt_thr_string+"eta1p22mMax6ValidHitsFilter"; 
    
      // Loop over trigger objects matching the dielectron path 
      for (pat::TriggerObjectStandAlone obj : *triggerObjects) {
      
        // check if this obj comes from the wanted di-electron path
        obj.unpackPathNames(trigNames);
        obj.unpackFilterLabels(iEvent, *HLTtriggers_);
        std::vector<std::string> pathNamesAll = obj.pathNames(false);
        bool isPathExist = false;
        for (unsigned h = 0, n = pathNamesAll.size(); h < n; ++h) {
          if(pathNamesAll[h].find(DoubleEleTrigName)!= std::string::npos) {
            isPathExist = true;   
          }
        }
        if(!isPathExist) continue;
                
        for (unsigned hh = 0; hh < obj.filterLabels().size(); ++hh){	
          // check if the object is from the correct filter
          if(obj.filterLabels()[hh].find(DoubleEleObjName) != std::string::npos) {

            TVector3 objTV3;
            objTV3.SetPtEtaPhi( obj.pt(), obj.eta(), obj.phi() );
            Float_t deltaEta11 = fabs(ele1TV3.Eta() - objTV3.Eta());
            Float_t deltaPhi11 = fabs(ele1TV3.DeltaPhi(objTV3));
            Float_t deltaEta21 = fabs(ele2TV3.Eta() - objTV3.Eta());
            Float_t deltaPhi21 = fabs(ele2TV3.DeltaPhi(objTV3));

            if (ele1_matchedDiEle_pt[j]<0 && deltaEta11<0.07 && deltaPhi11<0.2) {
                ele1_matchedDiEle[j] = 1;      
                ele1_matchedDiEle_pt[j]  = obj.pt();
                ele1_matchedDiEle_eta[j] = obj.eta();
                ele1_matchedDiEle_phi[j] = obj.phi();
                //std::cout << "Ok match offline1 / online1 " << std::endl;
            }
            else if (ele2_matchedDiEle_pt[j]<0 && deltaEta21<0.07 && deltaPhi21<0.2) {
                ele2_matchedDiEle[j] = 1; 
                ele2_matchedDiEle_pt[j]  = obj.pt();
                ele2_matchedDiEle_eta[j] = obj.eta();
                ele2_matchedDiEle_phi[j] = obj.phi();
                //std::cout << "Ok match offline2 / online1 " << std::endl;
            }
          }
        }
      }
    }
  } 

  // Match L1 / offline
  float bestMatchE1_eta = -99.;
  float bestMatchE1_phi = -99.;
  float bestMatchE1_pt  = -99.;
  float bestMatchE1_dR  = 999.;
  float bestMatchE2_eta = -99.;
  float bestMatchE2_phi = -99.;
  float bestMatchE2_pt  = -99.;
  float bestMatchE2_dR  = 999.;

  // Get the L1 EGamma collection from the event
  const auto &l1EG = iEvent.get(l1EG_); 

  // Loop over L1 EGamma objects
  for (l1t::EGammaBxCollection::const_iterator L1ele = l1EG.begin(0); L1ele != l1EG.end(0); L1ele++) {
    pat::TriggerObjectStandAlone l1obj(L1ele->p4());
    
    // Create TVector3 for L1 object
    TVector3 l1objTV3;
    l1objTV3.SetPtEtaPhi(L1ele->pt(), L1ele->eta(), L1ele->phi());

    // Calculate deltaEta, deltaPhi, and deltaR for electron 1
    Float_t deltaEta1 = fabs(ele1TV3.Eta() - l1objTV3.Eta());
    Float_t deltaPhi1 = fabs(ele1TV3.DeltaPhi(l1objTV3));
    Float_t deltaRE1  = fabs(ele1TV3.DeltaR(l1objTV3));

    // Calculate deltaEta, deltaPhi, and deltaR for electron 2
    Float_t deltaEta2 = fabs(ele2TV3.Eta() - l1objTV3.Eta());
    Float_t deltaPhi2 = fabs(ele2TV3.DeltaPhi(l1objTV3));
    Float_t deltaRE2  = fabs(ele2TV3.DeltaR(l1objTV3));

    // Check if L1 object matches electron 1 and has higher pt than the current best match
    if (deltaEta1 < 0.07 && deltaPhi1 < 0.2 && L1ele->pt() > bestMatchE1_pt) {
      // If there is already a previous match for electron 1, (let's call it L1eleOld), 
      // before substituting L1eleOld with L1ele, check if L1eleOld can be a better match for electron 2
      if (bestMatchE1_pt > 0 && deltaEta2 < 0.07 && deltaPhi2 < 0.2 && L1ele->pt() > bestMatchE2_pt) {
        bestMatchE2_eta  = bestMatchE1_eta; 
        bestMatchE2_phi  = bestMatchE1_phi; 
        bestMatchE2_pt   = bestMatchE1_pt; 
        bestMatchE2_dR   = bestMatchE1_dR;          
      }
      // Update best match for electron 1
      bestMatchE1_eta  = L1ele->eta(); 
      bestMatchE1_phi  = L1ele->phi(); 
      bestMatchE1_pt   = L1ele->pt();    
      bestMatchE1_dR   = deltaRE1;
    }
    // Check if L1 object matches electron 2 and has higher pt than the current best match
    else if (deltaEta2 < 0.07 && deltaPhi2 < 0.2 && L1ele->pt() > bestMatchE2_pt) {
      // Update best match for electron 2
      bestMatchE2_eta  = L1ele->eta(); 
      bestMatchE2_phi  = L1ele->phi(); 
      bestMatchE2_pt   = L1ele->pt(); 
      bestMatchE2_dR   = deltaRE2;
    }
  }

  // Infos about JPsi candidate
  Jpsi_e1_pt   = electroncollection[mcidx_e1].pt();
  Jpsi_e1_eta  = electroncollection[mcidx_e1].eta();
  Jpsi_e1_phi  = electroncollection[mcidx_e1].phi();
  Jpsi_e1_mass = electroncollection[mcidx_e1].mass();
  Jpsi_e1_q    = electroncollection[mcidx_e1].charge();
  Jpsi_e1_isElectron = electroncollection[mcidx_e1].isElectron();
  Jpsi_e1_passMVA = electroncollection[mcidx_e1].electronID("mvaEleID-Fall17-noIso-V2-wpLoose");
  Jpsi_e1_bestL1pt   = bestMatchE1_pt;
  Jpsi_e1_bestL1eta  = bestMatchE1_eta;
  Jpsi_e1_bestL1phi  = bestMatchE1_phi;
  Jpsi_e1_bestL1dR   = bestMatchE1_dR;  

  Jpsi_e2_pt   = electroncollection[mcidx_e2].pt();
  Jpsi_e2_eta  = electroncollection[mcidx_e2].eta();
  Jpsi_e2_phi  = electroncollection[mcidx_e2].phi();
  Jpsi_e2_mass = electroncollection[mcidx_e2].mass();
  Jpsi_e2_alsotag = is_probe_also_tag;
  Jpsi_e2_q    = electroncollection[mcidx_e2].charge();
  Jpsi_e2_isElectron = electroncollection[mcidx_e2].isElectron();
  Jpsi_e2_passMVA = electroncollection[mcidx_e2].electronID("mvaEleID-Fall17-noIso-V2-wpLoose");
  Jpsi_e2_bestL1pt  = bestMatchE2_pt;
  Jpsi_e2_bestL1eta = bestMatchE2_eta;
  Jpsi_e2_bestL1phi = bestMatchE2_phi;
  Jpsi_e2_bestL1dR  = bestMatchE2_dR;  
  
  if (mcidx_trgobj1>=0) {
    
    Jpsi_e1_trgobj_pt   = trg_obj_collection[mcidx_trgobj1].pt();
    Jpsi_e1_trgobj_eta  = trg_obj_collection[mcidx_trgobj1].eta();
    Jpsi_e1_trgobj_phi  = trg_obj_collection[mcidx_trgobj1].phi();
    Jpsi_e1_trgobj_mass = trg_obj_collection[mcidx_trgobj1].mass();
    Jpsi_e1_trgobj_q    = trg_obj_collection[mcidx_trgobj1].charge();
    TVector3 trgobj1TV3;
    trgobj1TV3.SetPtEtaPhi( Jpsi_e1_trgobj_pt, Jpsi_e1_trgobj_eta, Jpsi_e1_trgobj_phi);
    Jpsi_e1_trgobj_dR = fabs(ele1TV3.DeltaR(trgobj1TV3));
  }

  if (mcidx_trgobj2>=0) {

    Jpsi_e2_trgobj_pt   = trg_obj_collection[mcidx_trgobj2].pt();
    Jpsi_e2_trgobj_eta  = trg_obj_collection[mcidx_trgobj2].eta();
    Jpsi_e2_trgobj_phi  = trg_obj_collection[mcidx_trgobj2].phi();
    Jpsi_e2_trgobj_mass = trg_obj_collection[mcidx_trgobj2].mass();
    Jpsi_e2_trgobj_q    = trg_obj_collection[mcidx_trgobj2].charge();
    TVector3 trgobj2TV3;
    trgobj2TV3.SetPtEtaPhi( Jpsi_e2_trgobj_pt, Jpsi_e2_trgobj_eta, Jpsi_e2_trgobj_phi);
    Jpsi_e2_trgobj_dR = fabs(ele2TV3.DeltaR(trgobj2TV3));
  }

  Jpsi_nonfit_pt   = jpsi_tlv_highest.Pt();
  Jpsi_nonfit_eta  = jpsi_tlv_highest.Eta();
  Jpsi_nonfit_phi  = jpsi_tlv_highest.Phi();
  Jpsi_nonfit_mass = jpsi_tlv_highest.M(); 

  Jpsi_electronsDr = ele1TV3.DeltaR(ele2TV3); 

  tree_->Fill();

  return;

} //NanoAnalyzer::analyze ends



//**************************************************
//************* additional methods *****************
//**************************************************

void NanoAnalyzerDoubleEle::beginJob(const edm::ParameterSet& iConfig) { }

void NanoAnalyzerDoubleEle::beginRun(const edm::Run &iRun, const edm::EventSetup &iStp) { }

void NanoAnalyzerDoubleEle::fillDescriptions(edm::ConfigurationDescriptions & descriptions) { }

void NanoAnalyzerDoubleEle::endRun(edm::Run const&, edm::EventSetup const&) { }

void NanoAnalyzerDoubleEle::endJob() { }

//define this as a plug-in

// branch title creation
void NanoAnalyzerDoubleEle::createBranch() { 

  tree_->Branch("run", &run, "run/i");
  tree_->Branch("event", &event, "event/l");
  tree_->Branch("luminosityBlock", &luminosityBlock, "luminosityBlock/i");
  tree_->Branch("nvtx", &nvtx, "nvtx/i");

  // Offline
  tree_->Branch("Jpsi_e1_pt", &Jpsi_e1_pt );
  tree_->Branch("Jpsi_e1_eta", &Jpsi_e1_eta );
  tree_->Branch("Jpsi_e1_phi", &Jpsi_e1_phi );
  tree_->Branch("Jpsi_e1_mass", &Jpsi_e1_mass );
  tree_->Branch("Jpsi_e1_q", &Jpsi_e1_q );
  tree_->Branch("Jpsi_e1_isElectron", &Jpsi_e1_isElectron );
  tree_->Branch("Jpsi_e1_passMVA"   , &Jpsi_e1_passMVA    );
  tree_->Branch("Jpsi_e1_bestL1pt"  , &Jpsi_e1_bestL1pt   );
  tree_->Branch("Jpsi_e1_bestL1eta" , &Jpsi_e1_bestL1eta  );
  tree_->Branch("Jpsi_e1_bestL1phi" , &Jpsi_e1_bestL1phi  );
  tree_->Branch("Jpsi_e1_bestL1dR",   &Jpsi_e1_bestL1dR );

  tree_->Branch("Jpsi_e2_pt", &Jpsi_e2_pt );
  tree_->Branch("Jpsi_e2_eta", &Jpsi_e2_eta );
  tree_->Branch("Jpsi_e2_phi", &Jpsi_e2_phi );
  tree_->Branch("Jpsi_e2_mass", &Jpsi_e2_mass );
  tree_->Branch("Jpsi_e2_alsotag", &Jpsi_e2_alsotag );
  tree_->Branch("Jpsi_e2_q", &Jpsi_e2_q );
  tree_->Branch("Jpsi_e2_isElectron"   , &Jpsi_e2_isElectron    );
  tree_->Branch("Jpsi_e2_passMVA"   , &Jpsi_e2_passMVA    );
  tree_->Branch("Jpsi_e2_bestL1pt",   &Jpsi_e2_bestL1pt );
  tree_->Branch("Jpsi_e2_bestL1eta" , &Jpsi_e2_bestL1eta );
  tree_->Branch("Jpsi_e2_bestL1phi" , &Jpsi_e2_bestL1phi );
  tree_->Branch("Jpsi_e2_bestL1dR" ,  &Jpsi_e2_bestL1dR );

  // Analysis double-ele trigger
  tree_->Branch("Jpsi_e1_DoubleEle10Match_pt" ,  &ele1_matchedDiEle_pt[0] );
  tree_->Branch("Jpsi_e1_DoubleEle9p5Match_pt",  &ele1_matchedDiEle_pt[1] );
  tree_->Branch("Jpsi_e1_DoubleEle9Match_pt"  ,  &ele1_matchedDiEle_pt[2] );
  tree_->Branch("Jpsi_e1_DoubleEle8p5Match_pt",  &ele1_matchedDiEle_pt[3] );
  tree_->Branch("Jpsi_e1_DoubleEle8Match_pt"  ,  &ele1_matchedDiEle_pt[4] );
  tree_->Branch("Jpsi_e1_DoubleEle7p5Match_pt",  &ele1_matchedDiEle_pt[5] );
  tree_->Branch("Jpsi_e1_DoubleEle7Match_pt"  ,  &ele1_matchedDiEle_pt[6] );
  tree_->Branch("Jpsi_e1_DoubleEle6p5Match_pt",  &ele1_matchedDiEle_pt[7] );
  tree_->Branch("Jpsi_e1_DoubleEle6Match_pt"  ,  &ele1_matchedDiEle_pt[8] );
  tree_->Branch("Jpsi_e1_DoubleEle5p5Match_pt",  &ele1_matchedDiEle_pt[9] );
  tree_->Branch("Jpsi_e1_DoubleEle5Match_pt"  ,  &ele1_matchedDiEle_pt[10] );
  tree_->Branch("Jpsi_e1_DoubleEle4p5Match_pt",  &ele1_matchedDiEle_pt[11] );
  tree_->Branch("Jpsi_e1_DoubleEle4Match_pt"  ,  &ele1_matchedDiEle_pt[12] );

  tree_->Branch("Jpsi_e1_DoubleEle10Match_eta" ,  &ele1_matchedDiEle_eta[0] );
  tree_->Branch("Jpsi_e1_DoubleEle9p5Match_eta",  &ele1_matchedDiEle_eta[1] );
  tree_->Branch("Jpsi_e1_DoubleEle9Match_eta"  ,  &ele1_matchedDiEle_eta[2] );
  tree_->Branch("Jpsi_e1_DoubleEle8p5Match_eta",  &ele1_matchedDiEle_eta[3] );
  tree_->Branch("Jpsi_e1_DoubleEle8Match_eta"  ,  &ele1_matchedDiEle_eta[4] );
  tree_->Branch("Jpsi_e1_DoubleEle7p5Match_eta",  &ele1_matchedDiEle_eta[5] );
  tree_->Branch("Jpsi_e1_DoubleEle7Match_eta"  ,  &ele1_matchedDiEle_eta[6] );
  tree_->Branch("Jpsi_e1_DoubleEle6p5Match_eta",  &ele1_matchedDiEle_eta[7] );
  tree_->Branch("Jpsi_e1_DoubleEle6Match_eta"  ,  &ele1_matchedDiEle_eta[8] );
  tree_->Branch("Jpsi_e1_DoubleEle5p5Match_eta",  &ele1_matchedDiEle_eta[9] );
  tree_->Branch("Jpsi_e1_DoubleEle5Match_eta"  ,  &ele1_matchedDiEle_eta[10] );
  tree_->Branch("Jpsi_e1_DoubleEle4p5Match_eta",  &ele1_matchedDiEle_eta[11] );
  tree_->Branch("Jpsi_e1_DoubleEle4Match_eta"  ,  &ele1_matchedDiEle_eta[12] );

  tree_->Branch("Jpsi_e1_DoubleEle10Match_phi" ,  &ele1_matchedDiEle_phi[0] );
  tree_->Branch("Jpsi_e1_DoubleEle9p5Match_phi",  &ele1_matchedDiEle_phi[1] );
  tree_->Branch("Jpsi_e1_DoubleEle9Match_phi"  ,  &ele1_matchedDiEle_phi[2] );
  tree_->Branch("Jpsi_e1_DoubleEle8p5Match_phi",  &ele1_matchedDiEle_phi[3] );
  tree_->Branch("Jpsi_e1_DoubleEle8Match_phi"  ,  &ele1_matchedDiEle_phi[4] );
  tree_->Branch("Jpsi_e1_DoubleEle7p5Match_phi",  &ele1_matchedDiEle_phi[5] );
  tree_->Branch("Jpsi_e1_DoubleEle7Match_phi"  ,  &ele1_matchedDiEle_phi[6] );
  tree_->Branch("Jpsi_e1_DoubleEle6p5Match_phi",  &ele1_matchedDiEle_phi[7] );
  tree_->Branch("Jpsi_e1_DoubleEle6Match_phi"  ,  &ele1_matchedDiEle_phi[8] );
  tree_->Branch("Jpsi_e1_DoubleEle5p5Match_phi",  &ele1_matchedDiEle_phi[9] );
  tree_->Branch("Jpsi_e1_DoubleEle5Match_phi"  ,  &ele1_matchedDiEle_phi[10] );
  tree_->Branch("Jpsi_e1_DoubleEle4p5Match_phi",  &ele1_matchedDiEle_phi[11] );
  tree_->Branch("Jpsi_e1_DoubleEle4Match_phi"  ,  &ele1_matchedDiEle_phi[12] );

  tree_->Branch("Jpsi_e2_DoubleEle20Match_pt" ,  &ele2_matchedDiEle_pt[0] );
  tree_->Branch("Jpsi_e2_DoubleEle9p5Match_pt",  &ele2_matchedDiEle_pt[1] );
  tree_->Branch("Jpsi_e2_DoubleEle9Match_pt"  ,  &ele2_matchedDiEle_pt[2] );
  tree_->Branch("Jpsi_e2_DoubleEle8p5Match_pt",  &ele2_matchedDiEle_pt[3] );
  tree_->Branch("Jpsi_e2_DoubleEle8Match_pt"  ,  &ele2_matchedDiEle_pt[4] );
  tree_->Branch("Jpsi_e2_DoubleEle7p5Match_pt",  &ele2_matchedDiEle_pt[5] );
  tree_->Branch("Jpsi_e2_DoubleEle7Match_pt"  ,  &ele2_matchedDiEle_pt[6] );
  tree_->Branch("Jpsi_e2_DoubleEle6p5Match_pt",  &ele2_matchedDiEle_pt[7] );
  tree_->Branch("Jpsi_e2_DoubleEle6Match_pt"  ,  &ele2_matchedDiEle_pt[8] );
  tree_->Branch("Jpsi_e2_DoubleEle5p5Match_pt",  &ele2_matchedDiEle_pt[9] );
  tree_->Branch("Jpsi_e2_DoubleEle5Match_pt"  ,  &ele2_matchedDiEle_pt[10] );
  tree_->Branch("Jpsi_e2_DoubleEle4p5Match_pt",  &ele2_matchedDiEle_pt[11] );
  tree_->Branch("Jpsi_e2_DoubleEle4Match_pt"  ,  &ele2_matchedDiEle_pt[12] );

  tree_->Branch("Jpsi_e2_DoubleEle20Match_eta" ,  &ele2_matchedDiEle_eta[0] );
  tree_->Branch("Jpsi_e2_DoubleEle9p5Match_eta",  &ele2_matchedDiEle_eta[1] );
  tree_->Branch("Jpsi_e2_DoubleEle9Match_eta"  ,  &ele2_matchedDiEle_eta[2] );
  tree_->Branch("Jpsi_e2_DoubleEle8p5Match_eta",  &ele2_matchedDiEle_eta[3] );
  tree_->Branch("Jpsi_e2_DoubleEle8Match_eta"  ,  &ele2_matchedDiEle_eta[4] );
  tree_->Branch("Jpsi_e2_DoubleEle7p5Match_eta",  &ele2_matchedDiEle_eta[5] );
  tree_->Branch("Jpsi_e2_DoubleEle7Match_eta"  ,  &ele2_matchedDiEle_eta[6] );
  tree_->Branch("Jpsi_e2_DoubleEle6p5Match_eta",  &ele2_matchedDiEle_eta[7] );
  tree_->Branch("Jpsi_e2_DoubleEle6Match_eta"  ,  &ele2_matchedDiEle_eta[8] );
  tree_->Branch("Jpsi_e2_DoubleEle5p5Match_eta",  &ele2_matchedDiEle_eta[9] );
  tree_->Branch("Jpsi_e2_DoubleEle5Match_eta"  ,  &ele2_matchedDiEle_eta[10] );
  tree_->Branch("Jpsi_e2_DoubleEle4p5Match_eta",  &ele2_matchedDiEle_eta[11] );
  tree_->Branch("Jpsi_e2_DoubleEle4Match_eta"  ,  &ele2_matchedDiEle_eta[12] );

  tree_->Branch("Jpsi_e2_DoubleEle20Match_phi" ,  &ele2_matchedDiEle_phi[0] );
  tree_->Branch("Jpsi_e2_DoubleEle9p5Match_phi",  &ele2_matchedDiEle_phi[1] );
  tree_->Branch("Jpsi_e2_DoubleEle9Match_phi"  ,  &ele2_matchedDiEle_phi[2] );
  tree_->Branch("Jpsi_e2_DoubleEle8p5Match_phi",  &ele2_matchedDiEle_phi[3] );
  tree_->Branch("Jpsi_e2_DoubleEle8Match_phi"  ,  &ele2_matchedDiEle_phi[4] );
  tree_->Branch("Jpsi_e2_DoubleEle7p5Match_phi",  &ele2_matchedDiEle_phi[5] );
  tree_->Branch("Jpsi_e2_DoubleEle7Match_phi"  ,  &ele2_matchedDiEle_phi[6] );
  tree_->Branch("Jpsi_e2_DoubleEle6p5Match_phi",  &ele2_matchedDiEle_phi[7] );
  tree_->Branch("Jpsi_e2_DoubleEle6Match_phi"  ,  &ele2_matchedDiEle_phi[8] );
  tree_->Branch("Jpsi_e2_DoubleEle5p5Match_phi",  &ele2_matchedDiEle_phi[9] );
  tree_->Branch("Jpsi_e2_DoubleEle5Match_phi"  ,  &ele2_matchedDiEle_phi[10] );
  tree_->Branch("Jpsi_e2_DoubleEle4p5Match_phi",  &ele2_matchedDiEle_phi[11] );
  tree_->Branch("Jpsi_e2_DoubleEle4Match_phi"  ,  &ele2_matchedDiEle_phi[12] );

  tree_->Branch("SingleEle_fired", &SingleEle_fired );
  tree_->Branch("DoubleEle10_fired", &DoubleEle_fired[0] );
  tree_->Branch("DoubleEle9p5_fired", &DoubleEle_fired[1] );
  tree_->Branch("DoubleEle9_fired", &DoubleEle_fired[2] );
  tree_->Branch("DoubleEle8p5_fired", &DoubleEle_fired[3] );
  tree_->Branch("DoubleEle8_fired", &DoubleEle_fired[4] );
  tree_->Branch("DoubleEle7p5_fired", &DoubleEle_fired[5] );
  tree_->Branch("DoubleEle7_fired", &DoubleEle_fired[6] );
  tree_->Branch("DoubleEle6p5_fired", &DoubleEle_fired[7] );
  tree_->Branch("DoubleEle6_fired", &DoubleEle_fired[8] );
  tree_->Branch("DoubleEle5p5_fired", &DoubleEle_fired[9] );
  tree_->Branch("DoubleEle5_fired", &DoubleEle_fired[10] );
  tree_->Branch("DoubleEle4p5_fired", &DoubleEle_fired[11] );
  tree_->Branch("DoubleEle4_fired", &DoubleEle_fired[12] );
  
  // Reference single-ele trigger
  tree_->Branch("Jpsi_e1_trgobj_pt",   &Jpsi_e1_trgobj_pt );
  tree_->Branch("Jpsi_e1_trgobj_eta",  &Jpsi_e1_trgobj_eta );
  tree_->Branch("Jpsi_e1_trgobj_phi",  &Jpsi_e1_trgobj_phi );
  tree_->Branch("Jpsi_e1_trgobj_mass", &Jpsi_e1_trgobj_mass );
  tree_->Branch("Jpsi_e1_trgobj_q",    &Jpsi_e1_trgobj_q );
  tree_->Branch("Jpsi_e1_trgobj_dR",   &Jpsi_e1_trgobj_dR );

  tree_->Branch("Jpsi_e2_trgobj_pt",   &Jpsi_e2_trgobj_pt );
  tree_->Branch("Jpsi_e2_trgobj_eta",  &Jpsi_e2_trgobj_eta );
  tree_->Branch("Jpsi_e2_trgobj_phi",  &Jpsi_e2_trgobj_phi );
  tree_->Branch("Jpsi_e2_trgobj_mass", &Jpsi_e2_trgobj_mass );
  tree_->Branch("Jpsi_e2_trgobj_q",    &Jpsi_e2_trgobj_q );
  tree_->Branch("Jpsi_e2_trgobj_dR",   &Jpsi_e2_trgobj_dR );

  // JPsi and daughters
  tree_->Branch("Jpsi_fit_pt",      &Jpsi_fit_pt );
  tree_->Branch("Jpsi_nonfit_pt",   &Jpsi_nonfit_pt );
  tree_->Branch("Jpsi_fit_eta",     &Jpsi_fit_eta );
  tree_->Branch("Jpsi_nonfit_eta",  &Jpsi_nonfit_eta );
  tree_->Branch("Jpsi_fit_phi",     &Jpsi_fit_phi );
  tree_->Branch("Jpsi_nonfit_phi",  &Jpsi_nonfit_phi);
  tree_->Branch("Jpsi_fit_mass",    &Jpsi_fit_mass );
  tree_->Branch("Jpsi_nonfit_mass", &Jpsi_nonfit_mass );
  tree_->Branch("Jpsi_fit_vprob",   &Jpsi_fit_vprob );
  tree_->Branch("Jpsi_electronsDr",     &Jpsi_electronsDr );
}

void NanoAnalyzerDoubleEle::reset(void){

  run = -1;
  event = -1;
  luminosityBlock = -1;
  nvtx = -1;

  Jpsi_e1_pt = -99;
  Jpsi_e1_eta = -99;
  Jpsi_e1_phi = -99;
  Jpsi_e1_mass = -99;
  Jpsi_e1_q = -99;
  Jpsi_e1_isElectron = -99;
  Jpsi_e1_passMVA = -99;
  Jpsi_e1_bestL1pt = -99;
  Jpsi_e1_bestL1eta = -99;
  Jpsi_e1_bestL1phi = -99;
  Jpsi_e1_bestL1dR = -99;

  Jpsi_e2_pt = -99;
  Jpsi_e2_eta = -99;
  Jpsi_e2_phi = -99;
  Jpsi_e2_mass = -99;
  Jpsi_e2_alsotag = -99;
  Jpsi_e2_q = -99;
  Jpsi_e2_isElectron = -99;
  Jpsi_e2_passMVA = -99;
  Jpsi_e2_bestL1pt = -99;
  Jpsi_e2_bestL1eta = -99;
  Jpsi_e2_bestL1phi = -99;
  Jpsi_e2_bestL1dR = -99;

  Jpsi_e1_trgobj_pt   = -99;
  Jpsi_e1_trgobj_eta  = -99;
  Jpsi_e1_trgobj_phi  = -99;
  Jpsi_e1_trgobj_mass = -99;
  Jpsi_e1_trgobj_q  = -99;
  Jpsi_e1_trgobj_dR = -99;

  Jpsi_e2_trgobj_pt   = -99;
  Jpsi_e2_trgobj_eta  = -99;
  Jpsi_e2_trgobj_phi  = -99;
  Jpsi_e2_trgobj_mass = -99;
  Jpsi_e2_trgobj_q  = -99;
  Jpsi_e2_trgobj_dR = -99;

  SingleEle_fired = 0.;
  for (int ii=0; ii<13; ii++) DoubleEle_fired[ii] = 0.;

  for (int ii=0; ii<13; ii++) ele1_matchedDiEle[ii] = 0.;
  for (int ii=0; ii<13; ii++) ele2_matchedDiEle[ii] = 0.;
  for (int ii=0; ii<13; ii++) ele1_matchedDiEle_pt[ii]  = -999.;
  for (int ii=0; ii<13; ii++) ele2_matchedDiEle_pt[ii]  = -999.;
  for (int ii=0; ii<13; ii++) ele1_matchedDiEle_eta[ii] = -999.;
  for (int ii=0; ii<13; ii++) ele2_matchedDiEle_eta[ii] = -999.;
  for (int ii=0; ii<13; ii++) ele1_matchedDiEle_phi[ii] = -999.;
  for (int ii=0; ii<13; ii++) ele2_matchedDiEle_phi[ii] = -999.;

  ele1_matchedDiEle_dR = 0.;
  ele2_matchedDiEle_dR = 0.;

  Jpsi_fit_pt      = -99;
  Jpsi_nonfit_pt   = -99;
  Jpsi_fit_eta     = -99;
  Jpsi_nonfit_eta  = -99;
  Jpsi_fit_phi     = -99;
  Jpsi_nonfit_phi  = -99;
  Jpsi_fit_mass    = -99;
  Jpsi_nonfit_mass = -99;
  Jpsi_fit_vprob   = -99;
  Jpsi_electronsDr     = -99;

}

DEFINE_FWK_MODULE(NanoAnalyzerDoubleEle);