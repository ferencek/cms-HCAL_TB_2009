server.workspace('DQMQuality', 0, 'Summaries', 'Summary')
server.workspace('DQMSummary', 1, 'Summaries', 'Reports')
server.workspace('DQMShift',   2, 'Summaries', 'Shift')

server.workspace('DQMContent', 10, 'Tracker', 'Pixel', '^Pixel/',
                 'Pixel/Layouts/00 - Pixel_RawData_FED_Summary',
                 'Pixel/Layouts/01 - Pixel_RawData_Summary',
                 'Pixel/Layouts/02 - Pixel_Digi_Occupancy',
                 'Pixel/Layouts/03 - Pixel_Digi_Summary',
                 'Pixel/Layouts/04 - Pixel_Cluster_Summary')

server.workspace('DQMContent', 10, 'Tracker', 'SiStrip', '^SiStrip/',
                 'SiStrip/Layouts/00 - Tracks',
                 'SiStrip/Layouts/01 - OnTrackClusters(Total Number)',
                 'SiStrip/Layouts/02 - OnTrackCluster (StoN)', 
                 'SiStrip/Layouts/03 - OffTrackCluster (Total Number)',
                 'SiStrip/Layouts/04 - OffTrackCluster (Charge)',
                 'SiStrip/Layouts/05 - TIBSummary',
                 'SiStrip/Layouts/06 - TIDFSummary',
                 'SiStrip/Layouts/07 - TIDBSummary',
                 'SiStrip/Layouts/08 - TOBSummary',
                 'SiStrip/Layouts/09 - TECFSummary',
                 'SiStrip/Layouts/10 - TECBSummary',
                 'SiStrip/Layouts/11 - FedMonitoringSummary')

server.workspace('DQMContent', 20, 'Calorimeter', 'EcalPreshower', '^EcalPreshower',
#                 'Ecal/Layouts/00-Global-Summary',
                 'Ecal/Layouts/01-IntegritySummary-EcalPreshower'
#                 'Ecal/Layouts/02-Cluster-Summary')
)
server.workspace('DQMContent', 20, 'Calorimeter', 'EcalBarrel', '^EcalBarrel/',
                 'EcalBarrel/Layouts/00-Global-Summary-EcalBarrel',
                 'EcalBarrel/Layouts/01-Occupancy-Summary-EcalBarrel',
                 'EcalBarrel/Layouts/02-Cluster-Summary-EcalBarrel')

server.workspace('DQMContent', 20, 'Calorimeter', 'EcalEndcap', '^EcalEndcap/',
                 'EcalEndcap/Layouts/00-Global-Summary-EcalEndcap',
                 'EcalEndcap/Layouts/01-Occupancy-Summary-EcalEndcap',
                 'EcalEndcap/Layouts/02-Cluster-Summary-EcalEndcap')

server.workspace('DQMContent', 20, 'Luminosity', 'HLX', '^HLX',
                 'HLX/Layouts/HF-Comparison',
                 'HLX/Layouts/HLX-Averages',
                 'HLX/Layouts/HLX-Luminosity',
                 'HLX/Layouts/HLX-Occupancy-Check-Sums',
                 'HLX/Layouts/HLX-EtSumAndLumi-History-Plots')


server.workspace('DQMContent', 20, 'Calorimeter', 'HCAL', '^Hcal/'
                 #'Hcal/Layouts/HCAL DataFormat Problems',
                 #'Hcal/Layouts/HCAL Digi Problems',
                 #'Hcal/Layouts/HCAL Dead Cell Check',
                 #'Hcal/Layouts/HCAL Hot Cell Check',
                 #'Hcal/Layouts/HCAL Pedestals',
                 #'Hcal/Layouts/HCAL Trigger Primitives',
                 #'Hcal/Layouts/HCAL Unsuppressed Channels',
                 #"Hcal/Layouts/01 HCAL Shifter Checklist Plots - DataFormat",
                 #"Hcal/Layouts/02 HCAL Shifter Checklist Plots - RecHits",
                 #"Hcal/Layouts/03 HCAL Shifter Checklist Plots - Summaries"
                 )

server.workspace('DQMContent', 30, 'Muon', 'CSC', '^CSC/',
                 'CSC/Layouts/00 Top Physics Efficiency',
                 'CSC/Layouts/01 Station Physics Efficiency',
		 'CSC/Layouts/02 EMU Summary/EMU Test01 - DDUs in Readout',
		 'CSC/Layouts/02 EMU Summary/EMU Test03 - DDU Reported Errors',
		 'CSC/Layouts/02 EMU Summary/EMU Test04 - DDU Format Errors',
		 'CSC/Layouts/02 EMU Summary/EMU Test05 - DDU Inputs Status',
		 'CSC/Layouts/02 EMU Summary/EMU Test06 - DDU Inputs in ERROR-WARNING State',
		 'CSC/Layouts/02 EMU Summary/EMU Test08 - CSCs Reporting Data and Unpacked',
		 'CSC/Layouts/02 EMU Summary/EMU Test10 - CSCs with Errors and Warnings (Fractions)',
		 'CSC/Layouts/02 EMU Summary/EMU Test11 - CSCs without Data Blocks')

server.workspace('DQMContent', 30, 'Muon', 'DT', '^DT/',
                 'DT/Layouts/00-Summary/00-DataIntegritySummary',
                 'DT/Layouts/00-Summary/01-OccupancySummary',
                 'DT/Layouts/00-Summary/02-SegmentSummary',
                 'DT/Layouts/00-Summary/03-DDU_TriggerCorrFactionSummary',
                 'DT/Layouts/00-Summary/04-DDU_Trigger2ndFactionSummary',
                 'DT/Layouts/00-Summary/05-DCC_TriggerCorrFactionSummary',
                 'DT/Layouts/00-Summary/06-DCC_Trigger2ndFactionSummary',
                 'DT/Layouts/00-Summary/07-NoiseChannelsSummary')

server.workspace('DQMContent', 30, 'Muon', 'RPC', '^RPC/',
                 'RPC/Layouts/RPC_BarrelOccupancy',      
                 'RPC/Layouts/RPC_EndcapOccupancy') 

server.workspace('DQMContent', 40, 'Trigger/DAQ', 'L1T', '^L1T/',
                 'L1T/L1TGT/algo_bits',
                 'L1T/L1TGT/tt_bits',
                 'L1T/L1TGMT/Regional_trigger',
                 'L1T/L1TGMT/GMT_etaphi',
                 'L1T/L1TGCT/IsoEmRankEtaPhi',
                 'L1T/L1TGCT/NonIsoEmRankEtaPhi',
                 'L1T/L1TGCT/CenJetsEtEtaPhi',
                 'L1T/L1TGCT/ForJetsEtEtaPhi',
                 'L1T/L1TGCT/TauJetsEtEtaPhi',
                 'L1T/L1TRCT/RctEmNonIsoEmEtEtaPhi',
                 'L1T/L1TRCT/RctEmIsoEmEtEtaPhi',
                 'L1T/L1TRCT/RctRegionsEtEtaPhi',
		 'L1T/L1TDTTF/DTTF_TRACKS/INTEG/Occupancy Summary',
		 'L1T/L1TCSCTF/CSCTF_Chamber_Occupancies',
		 'L1T/L1TCSCTF/CSCTF_occupancies',
		 'L1T/L1TRPCTF/RPCTF_muons_tower_phipacked')

server.workspace('DQMContent', 40, 'Trigger/DAQ', 'L1TEMU', '^L1TEMU/',
                 'L1TEMU/common/sysrates',
                 'L1TEMU/common/errorflag',
                 'L1TEMU/common/sysncandData',
                 'L1TEMU/common/sysncandEmul',
                 'L1TEMU/GT/GLTErrorFlag',
                 'L1TEMU/GCT/GCTErrorFlag',
                 'L1TEMU/GMT/GMTErrorFlag',
                 'L1TEMU/RCT/RCTErrorFlag',
                 'L1TEMU/CSCTF/CTFErrorFlag',
                 'L1TEMU/CSCTPG/CTPErrorFlag',
                 'L1TEMU/DTTF/DTFErrorFlag',
                 'L1TEMU/DTTPG/DTPErrorFlag',
                 'L1TEMU/RPC/RPCErrorFlag',
                 'L1TEMU/ECAL/ETPErrorFlag',
                 'L1TEMU/HCAL/HTPErrorFlag')


server.workspace('DQMContent', 41, 'Trigger/DAQ', 'HLT', '^HLT/',
                 'HLT/HLTMonMuon/Summary/PassingBits_Summary',
                 'HLT/HLTMonMuon/Summary/Ratio_HLT_L1MuOpen',
                 'HLT/HLTMonMuon/L1PassThrough/Level1/HLTMuonL1_etaphi',
                 'HLT/HLTMonMuon/L1PassThrough/Level1/HLTMuonL1_eta',
                 'HLT/HLTMonMuon/L1PassThrough/Level1/HLTMuonL1_phi')


server.workspace('DQMContent', 90, 'Other', 'Everything', '^')
server.workspace('EVDSnapshot', 99, 'Other', 'Event display', '/home/dqm/iguana-snapshots')
