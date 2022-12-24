import pygame
from os import path
from Player.PlayersInput import PlayersInput
from Player.OrbHandler import OrbHandler


class Pelaaja(pygame.sprite.Sprite):
    def __init__(self, pos, groups, collision_sprites):
        super().__init__(groups)
        self.idle = ["idle1.png", "idle2.png", "idle3.png", "idle4.png", "idle5.png", "idle6.png", "idle7.png", "idle8.png", "idle9.png",
                     "idle10.png", "idle11.png", "idle12.png", "idle13.png", "idle14.png", "idle15.png", "idle16.png", "idle17.png", "idle18.png"]
        self.juoksu = ["Juoksu1.png", "Juoksu2.png", "Juoksu3.png", "Juoksu4.png", "Juoksu5.png", "Juoksu6.png", "Juoksu7.png", "Juoksu8.png", "Juoksu9.png",
                       "Juoksu10.png", "Juoksu11.png", "Juoksu12.png", "Juoksu13.png", "Juoksu14.png", "Juoksu15.png", "Juoksu16.png", "Juoksu17.png", "Juoksu18.png",
                       "Juoksu19.png", "Juoksu20.png", "Juoksu21.png", "Juoksu22.png", "Juoksu23.png", "Juoksu24.png"]
        self.hyppy = ["Jump1.png", "Jump2.png", "Jump3.png", "Jump4.png",
                      "Jump5.png", "Jump6.png", "Jump7.png", "Jump8.png", "Jump9.png"]
        self.tippuu = ["Jump10.png", "Jump11.png", "Jump12.png",
                       "Jump13.png", "Jump14.png", "Jump15.png"]
        self.laskeutuminen = ["Jump16.png",
                              "Jump17.png", "Jump18.png", "Jump19.png"]
        self.attack = ["Attack1.png", "Attack2.png", "Attack3.png", "Attack4.png", "Attack5.png", "Attack6.png", "Attack7.png", "Attack8.png", "Attack9.png",
                       "Attack10.png", "Attack11.png", "Attack12.png", "Attack13.png", "Attack14.png", "Attack15.png", "Attack16.png", "Attack17.png", "Attack18.png",
                       "Attack19.png", "Attack20.png", "Attack21.png", "Attack22.png", "Attack23.png", "Attack24.png", "Attack25.png", "Attack26.png"]
        self.hurt = ["Hurt1.png", "Hurt2.png", "Hurt3.png",
                     "Hurt4.png", "Hurt5.png", "Hurt6.png", "Hurt7.png"]

        self.hp = 20  # normaali on kolme
        self.currentFrame = 0
        self.image = pygame.image.load(path.join("kuvat", "Pelaaja", "Pelaaja_idle", self.idle[self.currentFrame])).convert_alpha()
        self.rect = self.image.get_rect(topleft=pos)
        self.collision_sprites = collision_sprites
        self.on_floor = False
        self.vasemmalle = False
        self.falling = False
        self.hyökkäys = False
        self.animate = False # turha?
        self.hurting = False
        self.hurtingTime = 0
        self.lopetaHurting = False
        self.type = None  # tää pois
        self.playerInput = PlayersInput()
        self.orbHandler = OrbHandler()

        self.rect.w += self.rect.w/2
        self.rect.h += self.rect.h/2

        self.leveys = self.rect.w
        self.korkeus = self.rect.h

    def FrameCheck(self, kuvat, time, folder, loppu):
        self.currentFrame += time
        if self.currentFrame >= len(kuvat):
            self.currentFrame = len(kuvat)-1 if loppu == True else 0
        self.image = pygame.image.load(path.join("Kuvat", "Pelaaja", folder, kuvat[int(self.currentFrame)])).convert_alpha()
        self.checkVasen()

    def checkVasen(self):
        if self.vasemmalle:
            self.image = pygame.transform.flip(self.image, True, False)
     
    def do_animation(self):
        # x akselin suunnat
        if self.hurting:
            self.leveys += 6
            if self.hurtingTime == 0:
                self.currentFrame = 0
            if self.currentFrame >= 6:
                self.lopetaHurting = False
            self.FrameCheck(self.hurt, 0.15, "PlayerHurt", True)

        elif self.playerInput.direction == (0, 0) and not self.hyökkäys:
            self.FrameCheck(self.idle, 0.25, "Pelaaja_idle", False)

        elif self.playerInput.direction.x in [1,-1] and self.on_floor:   
            self.FrameCheck(self.juoksu, 0.8, "Pelaaja_Juoksu", False)
            self.vasemmalle = self.playerInput.direction.x != 1

        elif self.playerInput.direction.y < 0:
            self.FrameCheck(self.hyppy, 0.2, "Pelaaja_Jump", True)

        elif self.playerInput.direction.y > 1 and self.on_floor == False:
            self.FrameCheck(self.tippuu, 0.3, "Pelaaja_Tippuu", True)
            self.falling = True

        elif self.falling == True and self.playerInput.direction == (0, 0):
            if self.currentFrame >= len(self.laskeutuminen):
                self.falling = False
            self.FrameCheck(self.laskeutuminen, 0.25,"Pelaaja_Laskeutuminen", False)

        elif self.hyökkäys == True and self.playerInput.direction.x == 0:
            self.FrameCheck(self.attack, 0.25, "Pelaaja_Attack", False)
            self.leveys += 22
 
        self.image = pygame.transform.scale(
            self.image, (self.leveys, self.korkeus))
        self.leveys = self.rect.w

    def horizontal_collisions(self):
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

    def vertical_collisions(self):
        for sprite in self.collision_sprites.sprites():
            if sprite.passable and sprite.rect.colliderect(self.rect):
                if self.playerInput.direction.y > 0 and (sprite.type not in [36, 37, 38] or not self.playerInput.alas):
                    self.rect.bottom = sprite.rect.top
                    self.playerInput.direction.y = 0
                    self.on_floor = True
                    self.orbHandler.useOrb = False

                if self.playerInput.direction.y < 0 and sprite.type not in [36, 37, 38]:
                    self.rect.top = sprite.rect.bottom
                    self.playerInput.direction.y = 0

        if self.on_floor and self.playerInput.direction.y != 0:
            self.on_floor = False
            self.playerInput.alas = False



    def damage(self):
        if not self.hurting:
            return
        self.hurtingTime += 0.1
        if self.hurtingTime >= 6:
            self.hp -= 1
            self.hurtingTime = 0
            self.hurting = False

    def Check_hurting(self, objekt):
        if objekt.colliderect(self.rect) and not self.lopetaHurting:
            self.hurting = True
            self.lopetaHurting = True

    def update(self):
        self.do_animation()
        self.playerInput.input(self.orbHandler.inOrb,self.on_floor)
        self.rect.x += self.playerInput.applySpeed()
        self.horizontal_collisions()
        self.rect.y += self.playerInput.aplyGravity()
        self.vertical_collisions()
        self.orbHandler.update(self.currentFrame,self.playerInput.oikea,self.playerInput.vasen,self.playerInput.alas)
        temp = self.orbHandler.getDirection()
        self.rect.x += temp[0]
        self.playerInput.direction.y += temp[1]
        self.damage()
