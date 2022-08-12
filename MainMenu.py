import pygame, os, sys, time
from Text import Text
from Music import Music

class MainMenu:
    def __init__(self,screen) -> None:
        self.screen = screen
        self.napit = []
        self.texts = ["Play","Credits","Quit"]
        self.TeeNapit(3)
        self.taustat = ["Tausta1.png","Tausta2.png","Tausta3.png","Tausta3.png","Tausta4.png","Tausta5.png"]
        self.rats = []
        for num in range(1,46):
            self.rats.append("rat-spinning"+str(num)+".png")
        self.tausta = Animate((0,0),self.taustat,"Taustat",screen,(800,800),0.03)
        self.rat = Animate((600,600),self.rats,"Rat",screen,(200,200),0.3)
        self.Title = Text(self.screen,(100,20),"Dawn of the Rats",64,(255,255,255))      
        self.musiikki = Music()
        self.musiikki.type = 3
        self.click = False
        self.päällä = True
        self.hidden = False
        self.credit_texts = []
        self.sus = pygame.mixer.Sound(os.path.join("Musiikit","Amogus.mp3"))
        
        
    
        self.credits_text = ["Dawn of the Rats"," ","Producers","Game desinger: Minä and Tuke"," ","lead designer: Minä"," ","Software Developer: Minä"," ","Game Programmer: Minä"," ",
        "Audio Engineer: Tuke"," ","Game Animator","Player: Random guy from interweb","Enemies: Minä and Tuke","Others: Tuke"," ",
        "Game Artist","Blocks: Minä and Tuke","Enemies: Tuke","Backgrounds: Minä"," ","Interpreters and Translators: Äitis"," ","Game Play Tester: Minä",
        " ","Professional Gamer: Rat"," "," "," ","If you're reading this, you're sus"]      
      
         
    def credits(self):  
        for rivi,teksti in enumerate(reversed(self.credits_text)):
            self.credit = Text(self.screen,(100,-1500+50*rivi),teksti,32,(0,0,0))
            self.credit_texts.append(self.credit)

    def TeeNapit(self,määrä):
        for x in range(määrä):
            self.button = Button(self.texts[x],(50,150+x*200),300,100,self.screen,(100,100,255,128))
            self.napit.append(self.button)

    def run(self):
        self.tausta.Animate_stuff()
        self.rat.Animate_stuff()
        if not self.hidden:
            for sprite in self.napit:
                if sprite.rect.collidepoint(pygame.mouse.get_pos()):
                    sprite.color = (200,200,255,128)
                    sprite.kohdalla()
                    if self.click:
                        self.click = False
                        self.katso_nappi(sprite)
                else:  
                    sprite.color = (100,100,255,128)
                    sprite.kohdalla()
                    
                self.screen.blit(sprite.button,sprite.pos)
                sprite.tekstikohta.update()

            self.Title.update()
        if self.hidden:
            for teksti in self.credit_texts:
                teksti.update()
                teksti.liiku()
            if self.credit_texts[0].pos_y >= 780:
                self.hidden = False
                self.credit_texts = []

        if self.rat.rect.collidepoint(pygame.mouse.get_pos()) and self.click and pygame.mixer.music.get_busy():
            self.click = False
            pygame.mixer.music.fadeout(50)
            pygame.mixer.music.load(os.path.join("Musiikit","Rat.mp3"))
            pygame.mixer.music.set_volume(0.1)
            pygame.mixer.music.play()

                

        self.musiikki.Play_music()


    def katso_nappi(self,sprite):
        if sprite.text == "Play":
            pygame.mixer.music.fadeout(500)
            self.sus.play()
            self.sus.set_volume(0.1)
            self.päällä = False
        elif sprite.text == "Quit":
            pygame.mixer.music.fadeout(500)
            self.sus.play()
            self.sus.set_volume(0.1)
            self.päällä = False
            time.sleep(3)
            pygame.quit()
            sys.exit()
        else:
            self.hidden = True
            self.credits()

            
        

        

class Animate:
    def __init__(self,pos,kuvat,folder,screen,koko,time) -> None:
        self.currentFrame = 0
        self.pos = pos
        self.kuvat = kuvat
        self.folder = folder
        self.screen = screen
        self.koko = koko
        self.time = time

        
    def Animate_stuff(self):
        self.currentFrame += self.time
        if self.currentFrame >= len(self.kuvat):
            self.currentFrame = 0 
        self.image = pygame.image.load(os.path.join("Kuvat","MainMenuStuff",self.folder,self.kuvat[int(self.currentFrame)])).convert_alpha()
        self.image = pygame.transform.scale(self.image,(self.koko[0],self.koko[1]))
        self.screen.blit(self.image,self.pos)
        self.rect = self.image.get_rect(topleft = self.pos)


class Button:
    def __init__(self,text,pos,width,height,näyttö,color) -> None:
        self.näyttö = näyttö
        self.text = text
        self.pos = pos
        self.width = width
        self.height = height
        self.color = color


        self.button = pygame.Surface((self.width,self.height), pygame.SRCALPHA)   # per-pixel alpha
        self.button.fill(self.color)
        pygame.draw.rect(self.button, (255, 255, 255, 200), (0, 0, self.width, self.height), 1)                   
        näyttö.blit(self.button, (0,0))
        self.rect = self.button.get_rect(topleft = pos)
        self.tekstikohta = Text(self.näyttö,(self.rect.x+5,self.rect.y+20),self.text,64,(255,255,255)) 

    def kohdalla(self):
        self.button.fill(self.color)
        pygame.draw.rect(self.button, (255, 255, 255, 200), (0, 0, self.width, self.height), 1)   


        


