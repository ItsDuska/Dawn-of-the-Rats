from Entities.Enemies.Enemy import Enemy

class Bord(Enemy):
    __slots__ = "directions", "currentMovement", "movingSpeed", "movingSpeed", "blockSize", "startPos"

    def __init__(self, pos, maxTiles, animate, col, images, width, height, display_surface, directions) -> None:
        super().__init__(pos, maxTiles, animate, col,
                         images, width, height, display_surface, 0.2)
        self.directions = directions  # lista vector2 arvoja
        self.currentMovement = 0
        self.movingSpeed = 1
        self.blockSize = [(self.width/self.maxTiles),
                            (self.height/self.maxTiles)]
        self.startPos = self.rect.x, self.rect.y

    def Moving(self):
        if self.directions[self.currentMovement][0] < 0:
            self.rect.x -= self.movingSpeed
            self.facingLeft = False
        elif self.directions[self.currentMovement][0] > 0:
            self.rect.x += self.movingSpeed
            self.facingLeft = True

        if self.directions[self.currentMovement][1] < 0:
            self.rect.y -= self.movingSpeed
        elif self.directions[self.currentMovement][1] > 0:
            self.rect.y += self.movingSpeed

        if self.startPos[0] + (self.directions[self.currentMovement][0]*int(self.blockSize[0])) == self.rect.x and self.startPos[1] + (self.directions[self.currentMovement][1]*int(self.blockSize[1])) == self.rect.y:
            self.currentMovement += 1
            self.startPos = self.rect.x, self.rect.y
            if self.currentMovement == len(self.directions)-1:
                self.currentMovement = 0
