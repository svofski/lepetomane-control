import sys
sys.path.append('c:\users\svo\projects\lepetocontrol')
import copyposrot
dx
import pcbnew
borat=pcbnew.GetBoard()
h1=borat.FindModuleByReference('H1')
h2=borat.FindModuleByReference('H2')
dx=(h2.GetPosition()-h1.GetPosition()).x
copyposrot.klonor(range(1, 17), range(16, 33), dx)