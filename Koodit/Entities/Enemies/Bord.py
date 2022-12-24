from Entities.Enemies.Enemy import Enemy

class Bord(Enemy):
    __slots__ = "suunnat", "currentMovement", "movingSpeed", "movingSpeed", "kokopalikka", "startPos"

    def __init__(self, pos, maxRuudut, animate, col, kuva, width, height, display_surface, suunnat) -> None:
        super().__init__(pos, maxRuudut, animate, col,
                         kuva, width, height, display_surface, 0.2)
        self.suunnat = suunnat  # lista vector2 arvoja
        self.currentMovement = 0
        self.movingSpeed = 1
        self.kokopalikka = [(self.width/self.maxRuudut),
                            (self.height/self.maxRuudut)]
        self.startPos = self.rect.x, self.rect.y

    def Moving(self):
        if self.suunnat[self.currentMovement][0] < 0:
            self.rect.x -= self.movingSpeed
            self.vasemmalle = False
        elif self.suunnat[self.currentMovement][0] > 0:
            self.rect.x += self.movingSpeed
            self.vasemmalle = True

        if self.suunnat[self.currentMovement][1] < 0:
            self.rect.y -= self.movingSpeed
        elif self.suunnat[self.currentMovement][1] > 0:
            self.rect.y += self.movingSpeed

        if self.startPos[0] + (self.suunnat[self.currentMovement][0]*int(self.kokopalikka[0])) == self.rect.x and self.startPos[1] + (self.suunnat[self.currentMovement][1]*int(self.kokopalikka[1])) == self.rect.y:
            self.currentMovement += 1
            self.startPos = self.rect.x, self.rect.y
            if self.currentMovement == len(self.suunnat)-1:
                self.currentMovement = 0
