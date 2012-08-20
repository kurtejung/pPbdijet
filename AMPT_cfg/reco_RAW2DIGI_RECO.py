# Auto generated configuration file
# using: 
# Revision: 1.341 
# Source: /cvs/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: reco -s RAW2DIGI,RECO --filein AMPT_MinBias_pgen_4400GeV_shift.root --fileout reco_AMPT_MB_pgen_4400GeV_shift.root --conditions STARTHI44_V7::All
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.Reconstruction_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(700)
)

fllist = ''
flarr = []

filen = open('amptlist.txt','r')
for line in filen:
    flarr.append(line)
fllist = ', '.join(flarr)
fllist = `fllist.splitlines()`
fllist = fllist.replace("', ', ", "', '")
#fllist = fllist[2:-2]

myfilelist = cms.untracked.vstring()
myfilelist.extend([('/store/user/kjung/AMPT_MB_RAW/AMPT_MB_RAW/cbebabe63c149f96954af6ce0013816e/AMPT_MinBias_5020GeV_ppb_b15_shift_%d.root'% i) for i in range(1,52) if( i != 5) if(i != 19) if(i!=22) if(i!=32) if(i!=37)])

#myfilelist.extend( flarr )
# Input source
process.source = cms.Source("PoolSource",
    secondaryFileNames = cms.untracked.vstring(),
    fileNames = myfilelist
    #fileNames = cms.untracked.vstring('/store/user/kjung/AMPT_MB_RAW/AMPT_MB_RAW/cbebabe63c149f96954af6ce0013816e//AMPT_MinBias_5020GeV_ppb_b15_shift_44_1_KrZ.root')
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.341 $'),
    annotation = cms.untracked.string('reco nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition

process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    fileName = cms.untracked.string('reco_AMPT_MB_pgen_5020GeV_b15_shift.root'),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'STARTHI50_V16::All'

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.RECOSIMoutput_step)

