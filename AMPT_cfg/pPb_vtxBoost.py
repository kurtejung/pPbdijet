# Auto generated configuration file
# using: 
# Revision: 1.341 
# Source: /cvs/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: davidlw/MCProduction/AMPT_Organ_MinBias_2760GeV_cfi.py -s GEN,SIM,DIGI,L1,DIGI2RAW,HLT:HIon -n 10 --conditions STARTHI44_V7::All --datatier GEN-SIM-RECODEBUG --eventcontent FEVTDEBUGHLT --scenario HeavyIons --geometry Extended --no_exec
import FWCore.ParameterSet.Config as cms
from IOMC.EventVertexGenerators.VtxSmearedParameters_cfi import *
process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('SimG4CMS.Forward.zdcGeometryXML_cfi')
process.load('Configuration.EventContent.EventContent_cff')
#process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedRealistic7TeV2011Collision_cfi')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.Sim_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_HIon_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2)
)

# Input source
process.source = cms.Source("EmptySource")

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.3 $'),
    annotation = cms.untracked.string('AMPT generator'),
    name = cms.untracked.string('$Source: test/pPb_vtxBoost.py,v $')

)
RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService",
    generator = cms.PSet(
        initialSeed = cms.untracked.uint32(93845934),
        engineName = cms.untracked.string('HepJamesRandom')
    )
   
)
# Output definition

process.FEVTDEBUGHLToutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
    fileName = cms.untracked.string('AMPT_MinBias_5020GeV_ppb_b15_shift.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-RECODEBUG')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)
#process.FEVTDEBUGHLToutput.outputCommands.append('keep *')

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'STARTHI50_V16::All'

process.generator = cms.EDFilter("AMPTGeneratorFilter",
    diquarky = cms.double(0.0),
    diquarkx = cms.double(0.0),
    diquarkpx = cms.double(7.0),
    ntmax = cms.int32(150),
    dpcoal = cms.double(1000000.0),
    diquarkembedding = cms.int32(0),
    maxmiss = cms.int32(1000),
    ktkick = cms.int32(1),
    mu = cms.double(3.2264),
    quenchingpar = cms.double(2.0),
    popcornpar = cms.double(1.0),
    drcoal = cms.double(1000000.0),
    amptmode = cms.int32(1),
    izpc = cms.int32(0),
    popcornmode = cms.bool(True),
    minijetpt = cms.double(-7.0),
    ks0decay = cms.bool(False),
    alpha = cms.double(0.47140452),
    dt = cms.double(0.2),
    rotateEventPlane = cms.bool(True),
    shadowingmode = cms.bool(True),
    diquarkpy = cms.double(0.0),
    deuteronfactor = cms.int32(5),
    stringFragB = cms.double(0.5),
    quenchingmode = cms.bool(False),
    stringFragA = cms.double(2.2),
    deuteronmode = cms.int32(0),
    doInitialAndFinalRadiation = cms.int32(3),
    phidecay = cms.bool(True),
    deuteronxsec = cms.int32(1),
    pthard = cms.double(2.0),
    firstRun = cms.untracked.uint32(1),
    frame = cms.string('CMS'),
    targ = cms.string('P'),
    izp = cms.int32(82),
    bMin = cms.double(0),
    firstEvent = cms.untracked.uint32(1),
    izt = cms.int32(1),
    proj = cms.string('A'),
    comEnergy = cms.double(5020.0),
    iat = cms.int32(1),
    bMax = cms.double(15),
    iap = cms.int32(208)
)
#add boost parameter Beta
SimBoostVtxSmearingParameters = cms.PSet(
     Phi = cms.double(0.0),
     BetaStar = cms.double(100.0),
     Emittance = cms.double(2.04e-07),
     Alpha = cms.double(0.0),
     SigmaZ = cms.double(7.06),
     TimeOffset = cms.double(0.0),
     X0 = cms.double(0.2445),
     Y0 = cms.double(0.4182),
     Z0 = cms.double(0.0847),
     Beta=cms.double(0.434)
)


process.VtxSmeared = cms.EDProducer("BetaBoostZEvtVtxGenerator",
#    Realistic7TeV2011CollisionVtxSmearingParameters,
   SimBoostVtxSmearingParameters,  
   VtxSmearedCommon
)
process.VertexSmearingboost = cms.Sequence(cms.SequencePlaceholder("VtxSmeared")) 

# ZDC Inclusion Code - WARNING - SLOW!
process.g4SimHits.ZdcSD.UseShowerLibrary = cms.bool(False)
process.g4SimHits.ZdcSD.UseShowerHits = cms.bool(True)
#process.g4SimHits.UseMagneticField = cms.bool(False)
#process.g4SimHits.Physics.DefaultCutValue = cms.double(10.)
#process.g4SimHits.Generator.MinEtaCut = cms.double(-9.0)
#process.g4SimHits.Generator.MaxEtaCut =  cms.double(9.0)
#process.g4SimHits.Watchers = cms.VPSet(cms.PSet(
#        type = cms.string('ZdcTestAnalysis'),
#        ZdcTestAnalysis = cms.PSet(
#        Verbosity = cms.int32(0),
#        StepNtupleFlag = cms.int32(0),
#        EventNtupleFlag = cms.int32(0),
#        StepNtupleFileName = cms.string('stepNtuple.root'),
#        EventNtupleFileName = cms.string('eventNtuple.root')
#        )           
#))
#process.g4SimHits.ZdcSD.UseShowerLibrary = cms.bool(True)
#process.g4SimHits.StackingAction.MaxTrackTime = cms.double(10000.)
#process.g4SimHits.CaloSD.TmaxHit = cms.double(10000.)

#CASTOR Inclusion Code
process.g4SimHits.Generator.MinEtaCut =-7.0
process.g4SimHits.Generator.MaxEtaCut = 5.5
process.g4SimHits.CastorSD.nonCompensationFactor = cms.double(0.77)
#process.g4SimHits.CastorSD.minEnergyInGeVforUsingSLibrary = 1 #FULL Simulation CASTOR

# Path and EndPath definitions
#process.pgen_shift = cms.Sequence(cms.SequencePlaceholder("randomEngineStateProducer")+process.VertexSmearingboost+process.hiGenParticles+process.hiGenJets)
process.pgen_shift = cms.Sequence(cms.SequencePlaceholder("randomEngineStateProducer")+process.VertexSmearingboost+process.GeneInfo+process.genJetMET)

#modification to enhance jet production
#process.iterativeCone5HiGenJets.jetPtMin = cms.untracked.int32(1)

process.generation_step = cms.Path(process.pgen_shift)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.FEVTDEBUGHLToutput_step = cms.EndPath(process.FEVTDEBUGHLToutput)
#process.keepGenJets_step = cms.EndPath(process.RecoGenJetsRECO)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.FEVTDEBUGHLToutput_step])
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.generator * getattr(process,path)._seq 

