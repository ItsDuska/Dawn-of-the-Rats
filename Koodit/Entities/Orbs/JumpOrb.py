from Entities.Orbs.Orb import Orb

class JumpOrb(Orb):
    def __init__(self, pos, maxRuudut, kuva, näyttö, width, height, kasvi, animate, type) -> None:
        super().__init__(pos, maxRuudut, kuva, näyttö, width, height, kasvi, animate, type)
        self.color = [(130, 160, 250), (90, 120, 200), (50, 50, 50)]


    def Orb_Jump(self,direction):
        if self.inOrb:
            return
        direction.y = -12
        #self.inOrb = False
        self.useOrb = False

        # ei ole hyötyä mutta tarvitaan että dash toimii
    def getInOrb(self):
        return self.inOrb

    def run(self,direction):
        self.Orb_Jump(direction)