import pygame
from os import path
from Player.PlayersInput import PlayersInput

class Pelaaja(pygame.sprite.Sprite):
    def __init__(self, pos, groups, collision_sprites,orb_group):
        super().__init__(groups)
        self.idle = ["idle1.png", "idle2.png", "idle3.png", "idle4.png", "idle5.png", "idle6.png", "idle7.png", "idle8.png", "idle9.png",
                     "idle10.png", "idle11.png", "idle12.png", "idle13.png", "idle14.png", "idle15.png", "idle16.png", "idle17.png", "idle18.png"]
        self.runningAnimations = ["Juoksu1.png", "Juoksu2.png", "Juoksu3.png", "Juoksu4.png", "Juoksu5.png", "Juoksu6.png", "Juoksu7.png", "Juoksu8.png", "Juoksu9.png",
                       "Juoksu10.png", "Juoksu11.png", "Juoksu12.png", "Juoksu13.png", "Juoksu14.png", "Juoksu15.png", "Juoksu16.png", "Juoksu17.png", "Juoksu18.png",
                       "Juoksu19.png", "Juoksu20.png", "Juoksu21.png", "Juoksu22.png", "Juoksu23.png", "Juoksu24.png"]
        self.jumpAnimations = ["Jump1.png", "Jump2.png", "Jump3.png", "Jump4.png",
                      "Jump5.png", "Jump6.png", "Jump7.png", "Jump8.png", "Jump9.png"]
        self.fallingAnimations = ["Jump10.png", "Jump11.png", "Jump12.png",
                       "Jump13.png", "Jump14.png", "Jump15.png"]
        self.landingAnimations = ["Jump16.png",
                              "Jump17.png", "Jump18.png", "Jump19.png"]
        self.attackAnimations = ["Attack1.png", "Attack2.png", "Attack3.png", "Attack4.png", "Attack5.png", "Attack6.png", "Attack7.png", "Attack8.png", "Attack9.png",
                       "Attack10.png", "Attack11.png", "Attack12.png", "Attack13.png", "Attack14.png", "Attack15.png", "Attack16.png", "Attack17.png", "Attack18.png",
                       "Attack19.png", "Attack20.png", "Attack21.png", "Attack22.png", "Attack23.png", "Attack24.png", "Attack25.png", "Attack26.png"]
        self.hurtingAnimations = ["Hurt1.png", "Hurt2.png", "Hurt3.png",
                     "Hurt4.png", "Hurt5.png", "Hurt6.png", "Hurt7.png"]

        self.hp = 20  # normaali on kolme
        self.currentFrame = 0
        self.image = pygame.image.load(path.join("kuvat", "Pelaaja", "Pelaaja_idle", self.idle[self.currentFrame])).convert_alpha()
        self.rect = self.image.get_rect(topleft=pos)
        self.collision_sprites = collision_sprites
        self.orb_group = orb_group
        self.on_floor = False
        self.isFacingLeft = False
        self.falling = False
        self.attacking = False
        self.animate = False # turha?
        self.hurting = False
        self.hurtingTime = 0
        self.lockMovements = False
        self.lopetaHurting = False
        self.type = None  # t???? pois
        self.playerInput = PlayersInput()
        self.offSet = pygame.math.Vector2(0, 0)
        self.updateObject = True
        
        #self.orbHandler = OrbHandler()
        #self.rect.w += self.rect.w/2
        #self.rect.h += self.rect.h/2
        

        self.width = self.rect.w
        self.height = self.rect.h

    def FrameCheck(self, kuvat, time, folder, loppu):
        self.currentFrame += time
        if self.currentFrame >= len(kuvat):
            self.currentFrame = len(kuvat)-1 if loppu == True else 0
        self.image = pygame.image.load(path.join("Kuvat", "Pelaaja", folder, kuvat[int(self.currentFrame)])).convert_alpha()
        self.checkLeft()

    def checkLeft(self):
        if self.isFacingLeft:
            self.image = pygame.transform.flip(self.image, True, False)
     
    def doAnimation(self):
        if self.hurting:
            self.width += 6
            if self.hurtingTime == 0:
                self.currentFrame = 0
            if self.currentFrame >= 6:
                self.lopetaHurting = False
            self.FrameCheck(self.hurtingAnimations, 0.15, "PlayerHurt", True)

        elif self.playerInput.direction == (0, 0) and not self.attacking:
            self.FrameCheck(self.idle, 0.25, "Pelaaja_idle", False)

        elif self.playerInput.direction.x in [1,-1] and self.on_floor:   
            self.FrameCheck(self.runningAnimations, 0.8, "Pelaaja_Juoksu", False)
            self.isFacingLeft = self.playerInput.direction.x != 1

        elif self.playerInput.direction.y < 0:
            self.FrameCheck(self.jumpAnimations, 0.2, "Pelaaja_Jump", True)

        elif self.playerInput.direction.y > 1 and self.on_floor == False:
            self.FrameCheck(self.fallingAnimations, 0.3, "Pelaaja_Tippuu", True)
            self.falling = True

        elif self.falling == True and self.playerInput.direction == (0, 0):
            if self.currentFrame >= len(self.landingAnimations):
                self.falling = False
            self.FrameCheck(self.landingAnimations, 0.25,"Pelaaja_Laskeutuminen", False)

        elif self.attacking == True and self.playerInput.direction.x == 0:
            self.FrameCheck(self.attackAnimations, 0.25, "Pelaaja_Attack", False)
            self.width += 22
        
        
        self.image = pygame.transform.scale(
            self.image, (self.width, self.height))
        self.width = self.rect.w

    def horizontalCollisions(self):
        for sprite in self.collision_sprites.sprites():
            if (
                sprite.passable
                and sprite.rect.colliderect(self.rect)
                and sprite.type not in [36, 37, 38]
            ):
                if self.playerInput.direction.x < 0:
                    self.rect.left = sprite.rect.right
                elif self.playerInput.direction.x > 0:
                    self.rect.right = sprite.rect.left

    def verticalCollision(self):
        for sprite in self.collision_sprites.sprites():
            if sprite.passable and sprite.rect.colliderect(self.rect):
                if self.playerInput.direction.y > 0 and (sprite.type not in [36, 37, 38] or not self.playerInput.down):
                    self.rect.bottom = sprite.rect.top
                    self.playerInput.direction.y = 0
                    self.on_floor = True
                if self.playerInput.direction.y < 0 and sprite.type not in [36, 37, 38]:
                    self.rect.top = sprite.rect.bottom
                    self.playerInput.direction.y = 0

        if self.on_floor and self.playerInput.direction.y != 0:
            self.on_floor = False
            self.playerInput.down = False

    def orbColliding(self):
        for sprite in self.orb_group:
            #sprite.AddParticle(self.offSet)
            #sprite.Update_Particle(-self.offSet[0], -self.offSet[1])  

            self.lockMovements = bool(sprite.lockMovement)
            
            if sprite.drawPlayerOrbing:
                self.image = sprite.dashSprite(self.playerInput.direction.x,self.currentFrame)

            if self.on_floor:
                sprite.useOrb = True
            if (
                sprite.rect.colliderect(self.rect)
                and self.playerInput.jump_on_air
                and sprite.useOrb == True  # useORb on True jos sit?? voi k??ytt????
            ):
                sprite.inOrb = True
            sprite.run(self.playerInput.direction)

    def damage(self):
        if not self.hurting:
            return
        self.hurtingTime += 0.1
        if self.hurtingTime >= 6:
            self.hp -= 1
            self.hurtingTime = 0
            self.hurting = False

    def checkHurting(self, objekt):
        if objekt.colliderect(self.rect) and not self.lopetaHurting:
            self.hurting = True
            self.lopetaHurting = True

    def update(self):
        self.doAnimation()
        self.playerInput.input(self.lockMovements,self.on_floor)
        self.orbColliding()
        self.rect.x += self.playerInput.applySpeed()
        self.horizontalCollisions()
        self.rect.y += self.playerInput.aplyGravity()
        self.verticalCollision()
        self.damage()
