
import pygame
import os

class Pelaaja(pygame.sprite.Sprite):
    def __init__(self,pos,groups,collision_sprites):
        super().__init__(groups)
        self.idle = ["idle1.png","idle2.png","idle3.png","idle4.png","idle5.png","idle6.png","idle7.png","idle8.png","idle9.png",
        "idle10.png","idle11.png","idle12.png","idle13.png","idle14.png","idle15.png","idle16.png","idle17.png","idle18.png"]
        self.juoksu = ["Juoksu1.png","Juoksu2.png","Juoksu3.png","Juoksu4.png","Juoksu5.png","Juoksu6.png","Juoksu7.png","Juoksu8.png","Juoksu9.png",
        "Juoksu10.png","Juoksu11.png","Juoksu12.png","Juoksu13.png","Juoksu14.png","Juoksu15.png","Juoksu16.png","Juoksu17.png","Juoksu18.png",
        "Juoksu19.png","Juoksu20.png","Juoksu21.png","Juoksu22.png","Juoksu23.png","Juoksu24.png"]
        self.hyppy = ["Jump1.png","Jump2.png","Jump3.png","Jump4.png","Jump5.png","Jump6.png","Jump7.png","Jump8.png","Jump9.png"]
        self.tippuu = ["Jump10.png","Jump11.png","Jump12.png","Jump13.png","Jump14.png","Jump15.png"]
        self.laskeutuminen = ["Jump16.png","Jump17.png","Jump18.png","Jump19.png"]
        self.attack = ["Attack1.png","Attack2.png","Attack3.png","Attack4.png","Attack5.png","Attack6.png","Attack7.png","Attack8.png","Attack9.png",
        "Attack10.png","Attack11.png","Attack12.png","Attack13.png","Attack14.png","Attack15.png","Attack16.png","Attack17.png","Attack18.png",
        "Attack19.png","Attack20.png","Attack21.png","Attack22.png","Attack23.png","Attack24.png","Attack25.png","Attack26.png"]
        self.hurt = ["Hurt1.png","Hurt2.png","Hurt3.png","Hurt4.png","Hurt5.png","Hurt6.png","Hurt7.png"]


        self.hp = 3
        self.currentFrame = 0
        self.image = pygame.image.load(os.path.join("kuvat","Pelaaja","Pelaaja_idle",self.idle[self.currentFrame])).convert_alpha()
        self.rect = self.image.get_rect(topleft = pos)
        self.direction = pygame.math.Vector2()
        self.speed = 4
        self.gravity = 0.8
        self.jump_speed = 13
        self.collision_sprites = collision_sprites
        self.on_floor = False
        self.vasemmalle = False
        self.falling = False
        self.colliding_x = False
        self.hyppymax = False
        self.hyökkäys = False
        self.animate = False
        self.orb = None
        self.orbissa = False
        self.jump_on_air = False
        self.orbattu = False
        self.alas = False
        self.vasen = False
        self.oikea = False
        self.ylös = False
        self.hurting = False
        self.hurtingTime = 0
        self.lopetaHurting = False
        self.orbType = 0
        self.times = 0
        self.lopetaOrb = False
        self.mute = False
        self.suunta = [0,0]
        self.surface = pygame.Surface((self.rect.w,self.rect.h),pygame.SRCALPHA) #pygame.SRCALPHA
        self.type = None


    def FrameCheck(self,kuvat,time,folder,loppu):
        self.currentFrame += time  
        if self.currentFrame >= len(kuvat):
            if loppu == True:
                self.currentFrame = len(kuvat)-1
            else:
                self.currentFrame = 0 
       
        self.image = pygame.image.load(os.path.join("Kuvat","Pelaaja",folder,kuvat[int(self.currentFrame)])).convert_alpha()
        
        
        
    def CheckVasen(self):
        if self.vasemmalle:
            self.image = pygame.transform.flip(self.image,True,False)
               

    def do_animation(self):
        #x akselin suunnat
        if self.hurtingTime == 0 and self.hurting:
            self.currentFrame = 0


        if self.hurting == True:
            if self.currentFrame >= 6:
               # self.hurting = False
                self.lopetaHurting = False
            self.FrameCheck(self.hurt,0.15,"PlayerHurt",True)
            self.CheckVasen()

        elif self.direction == (0,0) and not self.hyökkäys:
            self.FrameCheck(self.idle,0.25,"Pelaaja_idle",False)
            self.CheckVasen()
            
        elif self.direction.x == 1 and self.on_floor:
            self.FrameCheck(self.juoksu,0.8,"Pelaaja_Juoksu",False)
            self.vasemmalle = False

        elif self.direction.x == -1 and self.on_floor:
            self.FrameCheck(self.juoksu,0.8,"Pelaaja_Juoksu",False)
            self.image = pygame.transform.flip(self.image,True,False) # muuttaa sen kävely suunnan
            self.vasemmalle = True

        #y akselin suunnat
        elif self.direction.y < 0:
            self.FrameCheck(self.hyppy,0.2,"Pelaaja_Jump",True)
            self.CheckVasen()

        elif self.direction.y > 1 and self.on_floor == False:
            self.FrameCheck(self.tippuu,0.3,"Pelaaja_Tippuu",True)
            self.falling = True
            self.CheckVasen()

        elif self.falling == True and self.direction == (0,0):
            if self.currentFrame >= len(self.laskeutuminen):
                self.falling = False
            self.FrameCheck(self.laskeutuminen,0.25,"Pelaaja_Laskeutuminen",False)
            self.CheckVasen()
            
        
        elif self.hyökkäys == True and self.direction.x == 0:
            self.FrameCheck(self.attack,0.25,"Pelaaja_Attack",False)
            self.CheckVasen()
        
        
        

    def input(self):
        if self.orbissa:
            return
        
        self.jump_on_air = False
        keys = pygame.key.get_pressed()
        if keys[pygame.K_d]:
            self.vasen = True
            self.direction.x = 1
        elif keys[pygame.K_a]:
            self.direction.x = -1
            self.oikea = True
        elif keys[pygame.K_s]:
            self.alas = True
        elif keys[pygame.K_w]:
            self.ylös = True


        else:
            self.direction.x = 0
            self.alas = False
            self.vasen = False
            self.oikea = False
            self.ylös = False

        if keys[pygame.K_SPACE] and self.on_floor: 
            self.direction.y = -self.jump_speed
            self.jump_on_air = True
            
        elif keys[pygame.K_SPACE] and not self.on_floor:
            self.jump_on_air = True
        
        if keys[pygame.K_m]:
            self.mute = not self.mute
        
    def horizontal_collisions(self):
        for sprite in self.collision_sprites.sprites():
            if sprite.passable and sprite.rect.colliderect(self.rect):
                if not sprite.type in [36,37,38]: # jos type = platform niin se ei katso horizontal collisioneita
                    if self.direction.x < 0: 
                        self.colliding_x = True
                        self.rect.left = sprite.rect.right
                    elif self.direction.x > 0: 
                        self.colliding_x = True
                        self.rect.right = sprite.rect.left
                    else:
                        self.colliding_x = False
                        

    def vertical_collisions(self):
        for sprite in self.collision_sprites.sprites():  
            if sprite.passable and sprite.rect.colliderect(self.rect):   
                if self.direction.y > 0:
                    if sprite.type in [36,37,38] and self.alas:
                        pass
                    else:
                        self.rect.bottom = sprite.rect.top
                        self.direction.y = 0
                        self.on_floor = True
                        self.orbattu = False 
                           
                if self.direction.y < 0 and not sprite.type in [36,37,38]:
                    self.rect.top = sprite.rect.bottom
                    self.direction.y = 0
            
        if self.on_floor and self.direction.y != 0:
            self.on_floor = False
            self.alas = False

        


    def apply_gravity(self):
        self.direction.y += self.gravity
        self.rect.y += self.direction.y


    def OrbCheck(self,type):
        self.orbType = type
      


    def Orb_Jump(self):
        if not self.orbissa: 
            return
        if self.orbType == 2:
            self.direction.y = -12

            self.orbissa = False 
            self.orbattu = True 


    def Orb_Dash(self):
        if not self.orbType == 1:
            return

        if not self.lopetaOrb:
            self.lopetaOrb = True
            if self.oikea:
                self.suunta[0] = -5
                self.suunta[1]= 0
            elif self.vasen:
                self.suunta[0] = 5
                self.suunta[1]= 0

            elif self.alas:
                self.suunta[1] = 10
            else:
                self.suunta[1] = -10


        self.times += 0.4
        if self.times >= 10:
            self.times = 0
            self.orbissa = False 
            self.suunta = [0,0]
            self.lopetaOrb = False
        
        

        self.rect.x += self.suunta[0] 
        self.direction.y = self.suunta[1] 

        if self.currentFrame >= 9:
            self.orbKuva("Dash9.png")
            if self.suunta[0] == -5:
                self.image = pygame.transform.flip(self.image,True,False)
        
        else:
            self.orbKuva("Dash15.png")
            if self.suunta[0] == -5:
                
                self.image = pygame.transform.flip(self.image,True,False)
    

    def Orbs(self):
        if not self.orbissa:
            return
        self.Orb_Jump()
        self.Orb_Dash()
            

    def orbKuva(self,kuva): 
        self.image = pygame.image.load(os.path.join("Kuvat","Pelaaja","PlayerDash",kuva)).convert_alpha()


    def damage(self):
        if self.hurting == True:
            self.hurtingTime += 0.1
            if self.hurtingTime >= 6:   
                self.hp -= 1
                self.hurtingTime = 0
                self.hurting = False
                

    def Check_hurting(self,objekt):
        if objekt.colliderect(self.rect) and not self.lopetaHurting:
            self.hurting = True  
            self.lopetaHurting = True
             

    def update(self):
        self.do_animation()
        self.input()
        self.rect.x += self.direction.x * self.speed
        self.horizontal_collisions()
        self.apply_gravity()
        self.vertical_collisions()
        self.Orbs()
        self.damage()

    
        
        
        