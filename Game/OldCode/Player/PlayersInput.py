from pygame import key, K_SPACE, K_m, K_d, K_a, K_s, K_w,Vector2

class PlayersInput:
    __slots__ = "direction","down","left","right","up","jump_on_air","gravity","jump_speed","speed","mute"
    def __init__(self) -> None:
        self.direction = Vector2()
        self.down = False
        self.left = False
        self.right = False
        self.up = False
        self.jump_on_air = False
        self.gravity = 0.9
        self.jump_speed = 14 # 16
        self.speed = 4  # 5
        #Utils
        self.mute = False
        
    def input(self, inOrb,on_floor):
        if inOrb:
            return
        self.jump_on_air = False
        keys = key.get_pressed()
        self.movement(keys)
        if keys[K_SPACE]:
            if on_floor:
                self.direction.y = -self.jump_speed
            self.jump_on_air = True
        #if keys[K_m]:
            #self.mute = not self.mute

    def movement(self, keys):
        if keys[K_d]:
            self.left = True
            self.direction.x = 1
        elif keys[K_a]:
            self.direction.x = -1
            self.right = True
        elif keys[K_s]:
            self.down = True
        elif keys[K_w]:
            self.up = True
        else:
            self.resetVelocity()

    def resetVelocity(self):
        self.direction.x = 0
        self.down = False
        self.left = False
        self.right = False
        self.up = False

    def aplyGravity(self):
        self.direction.y += self.gravity
        return self.direction.y
      
    def applySpeed(self):
        return self.direction.x * self.speed