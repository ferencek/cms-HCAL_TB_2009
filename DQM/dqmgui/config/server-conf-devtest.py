import os.path
global CONFIGDIR
BASEDIR   = os.path.dirname(os.path.dirname(__file__))
CONFIGDIR = os.path.normcase(os.path.abspath(__file__)).rsplit('/', 1)[0]

LAYOUTS = ["%s/%s-layouts.py" % (CONFIGDIR, x) for x in
	   ("csc", "dt", "eb", "ee", "hcal", "hlt", "hlx", "l1t", "l1temulator", "rpc", "pixel", "sistrip")]
LAYOUTS += ["%s/shift_%s_layout.py" % (CONFIGDIR, x) for x in
            ("csc", "dt", "eb", "ee", "hcal", "hlt", "hlx", "l1t", "l1temulator", "rpc", "pixel", "sistrip" , "fed" )]

modules = ("GuiDQM", "GuiEventDisplay")
envsetup = "export QUIET_ASSERT=a"

server.port        = 8888
server.serverDir   = BASEDIR + "/gui"
server.baseUrl     = '/dqm/testbeam'
server.title       = 'CMS data quality'
server.serviceName = 'Testbeam'

server.plugin('render', BASEDIR + "/style/*.cc")
server.source('DQMUnknown', 'unknown', 'DQMArchive', 9192)
server.source('DQMLive', 'dqm',
              '--listen 9191', '--collector localhost:9190',
              '--load ' + server.pathOfPlugin('render'))
server.source('DQMArchive', 'file',
              BASEDIR + "/dqm.db", '--listen 9192',
              '--load ' + server.pathOfPlugin('render'))
server.source('DQMLayout', 'layouts', *LAYOUTS)

execfile(CONFIGDIR + "/dqm-services.py")
execfile(CONFIGDIR + "/workspaces-online.py")
