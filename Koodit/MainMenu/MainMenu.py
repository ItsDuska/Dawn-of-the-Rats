import pygame
from os import path
from sys import exit
from time import sleep
from Visuals.Text import Text
from Visuals.Music import Music


class MainMenu:
    __slots__ = "screen","width","height","buttons","texts","backgrounds","rats","background","rat","Title","music","click","isWindowOn","hidden","credits_text","amogusSound","button","credit","allCredits"
    def __init__(self, screen, w, h) -> None:
        self.screen = screen
        self.width = w
        self.height = h
        self.buttons = []
        self.texts = ["Play", "Credits", "Quit"]
        self.createButtons(3)
        self.backgrounds = ["Tausta1.png", "Tausta2.png", "Tausta3.png",
                        "Tausta3.png", "Tausta4.png", "Tausta5.png"]
        self.rats = [f"rat-spinning{str(num)}.png" for num in range(1, 46)]
        self.background = Animate((0, 0), self.backgrounds, "Taustat",
                              screen, (self.width, self.height), 0.03)
        self.rat = Animate((self.width-200, self.height-200),
                           self.rats, "Rat", screen, (200, 200), 0.3)
        self.Title = Text(self.screen, (self.width/4+150, 20),
                          "Dawn of the Rats", 64, (255, 255, 255), self.width, self.height)
        self.music = Music()
        self.music.type = 3
        self.click = False
        self.isWindowOn = True
        self.hidden = False
        self.allCredits = []
        self.amogusSound = pygame.mixer.Sound(path.join("Musiikit", "Amogus.mp3"))

        self.credits_text = ["Dawn of the Rats", " ", "Producers", "Game desinger: Minä and Tuke", " ", "lead designer: Minä", " ", "Software Developer: Minä", " ", "Game Programmer: Minä", " ",
                             "Audio Engineer: Tuke", " ", "Game Animator", "Player: Random guy from interweb", "Enemies: Minä and Tuke", "Others: Tuke", " ",
                             "Game Artist", "Blocks: Minä and Tuke", "Enemies: Tuke", "Backgrounds: Minä", " ", "Interpreters and Translators: Äitis", " ", "Game Play Tester: Minä",
                             " ", "Professional Gamer: Rat", " ", " ", " ", "If you're reading this, you're amogusSound"]

    def credits(self):
        for rivi, teksti in enumerate(reversed(self.credits_text)):
            self.credit = Text(self.screen, (self.width/3, -1500+50*rivi),
                               teksti, 32, (0, 0, 0), self.width, self.height)
            self.allCredits.append(self.credit)

    def createButtons(self, määrä):
        for x in range(määrä):
            self.button = Button(
                self.texts[x], (self.width/2-100, 150+x*200), 300, 100, self.screen, (100, 100, 255, 128))
            self.buttons.append(self.button)

    def run(self):
        self.background.Animate_stuff()
        self.rat.Animate_stuff()
        if not self.hidden:
            for sprite in self.buttons:
                if sprite.rect.collidepoint(pygame.mouse.get_pos()):
                    sprite.color = (200, 200, 255, 128)
                    sprite.mouseOnButton()
                    if self.click:
                        self.click = False
                        self.checkButton(sprite)
                else:
                    sprite.color = (100, 100, 255, 128)
                    sprite.mouseOnButton()

                self.screen.blit(sprite.button, sprite.pos)
                sprite.tekstikohta.update()
            self.Title.update()
        if self.hidden:
            for teksti in self.allCredits:
                teksti.update()
                teksti.moveEndCredits()
            if self.allCredits[0].pos_y >= 780:
                self.hidden = False
                self.allCredits = []

        if self.rat.rect.collidepoint(pygame.mouse.get_pos()) and self.click and pygame.mixer.music.get_busy():
            self.click = False
            pygame.mixer.music.fadeout(50)
            pygame.mixer.music.load(path.join("Musiikit", "Rat.mp3"))
            pygame.mixer.music.set_volume(0.1)
            pygame.mixer.music.play()

        self.music.playMusic(False)

    def checkButton(self, sprite):
        if sprite.text == "Play":
            self.activateButton()
        elif sprite.text == "Quit":
            self.activateButton()
            sleep(1)
            pygame.quit()
            exit()
        else:
            self.hidden = True
            self.credits()

    def activateButton(self):
        pygame.mixer.music.fadeout(500)
        self.amogusSound.play()
        self.amogusSound.set_volume(0.1)
        self.isWindowOn = False


class Animate:
    __slots__ = "currentFrame","pos","images","folder","screen","size","time","image","rect"
    def __init__(self, pos, images, folder, screen, size, time) -> None:
        self.currentFrame = 0
        self.pos = pos
        self.images = images
        self.folder = folder
        self.screen = screen
        self.size = size
        self.time = time

    def Animate_stuff(self):
        self.currentFrame += self.time
        if self.currentFrame >= len(self.images):
            self.currentFrame = 0
        self.image = pygame.image.load(path.join(
            "Kuvat", "MainMenuStuff", self.folder, self.images[int(self.currentFrame)])).convert_alpha()
        self.image = pygame.transform.scale(
            self.image, (self.size[0], self.size[1]))
        self.screen.blit(self.image, self.pos)
        self.rect = self.image.get_rect(topleft=self.pos)


class Button:
    __slots__ = "screen","text","pos","width","height","color","button","rect","tekstikohta"
    def __init__(self, text, pos, width, height, screen, color) -> None:
        self.screen = screen
        self.text = text
        self.pos = pos
        self.width = width
        self.height = height
        self.color = color

        self.button = pygame.Surface((self.width, self.height), pygame.SRCALPHA)
        self.button.fill(self.color)
        pygame.draw.rect(self.button, (255, 255, 255, 200),(0, 0, self.width, self.height), 1)
        screen.blit(self.button, (0, 0))
        self.rect = self.button.get_rect(topleft=pos)
        self.tekstikohta = Text(self.screen, (self.rect.x+5, self.rect.y-50), self.text, 64, (255, 255, 255), self.width, self.height)

    def mouseOnButton(self):
        self.button.fill(self.color)
        pygame.draw.rect(self.button, (255, 255, 255, 200), (0, 0, self.width, self.height), 1)
