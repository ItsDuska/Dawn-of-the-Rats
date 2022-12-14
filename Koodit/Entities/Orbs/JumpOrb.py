from Entities.Orbs.Orb import Orb

class JumpOrb(Orb):
    def __init__(self, pos, maxTiles, image, screen, width, height, isPassable, animate, type) -> None:
        super().__init__(pos, maxTiles, image, screen, width, height, isPassable, animate, type)
        self.color = [(250, 160, 240), (200, 130, 200), (50, 50, 50)]
        self.glow.color = [130, 70, 130,1]

    def Orb_Jump(self,direction):
        if not self.inOrb: #Jos ei ole orbissa
            return  
        
        direction.y = -12
        self.inOrb = False
        self.useOrb = False

    def run(self,direction):
        self.Orb_Jump(direction)
        self.glow.update(self.image)