import pcbnew


def klonor(nums_proto, nums_tgt, ofsx):
    borat = pcbnew.GetBoard()
    for fr,to in zip(nums_proto, nums_tgt):
        src = borat.FindModuleByReference('D' + str(fr))
        dst = borat.FindModuleByReference('D' + str(to))
        dst.SetOrientationDegrees(src.GetOrientationDegrees())
        srcpos = src.GetPosition()
        dstpos = pcbnew.wxPoint(srcpos.x + ofsx, srcpos.y)
        dst.SetPosition(dstpos)
        print(to, ' set angle=', src.GetOrientationDegrees(), ' pos=', dstpos)

def run():
  borat = pcbnew.GetBoard()
  h1=borat.FindModuleByReference('H1')
  h2=borat.FindModuleByReference('H2')
  dx=(h2.GetPosition()-h1.GetPosition()).x
  klonor(range(1, 17), range(1+16, 17+16), dx)
  klonor(range(1, 17), range(1+32, 17+32), dx*2)
  klonor(range(1, 17), range(1+48, 17+48), dx*3)

