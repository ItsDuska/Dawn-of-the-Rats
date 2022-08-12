import pygame,os
from random import choice
class Music:

    def __init__(self) -> None:
        self.Musiikit = [["Flower_Solo.mp3","Peace_In_The_Meadows.mp3","Field_Of_The_Wild.mp3","Hearth_Of_The_Kingdom1.mp3","Chorus_Wheat.mp3","Rats_Behold.mp3"],
        ["Flowers_In_The_Moon_Light.mp3","Night_Charm.mp3"],
        ["Bells_Of_Wisdom.mp3","Moon_Bell.mp3"],["Cosmic_star.mp3","Space_Vortex.mp3"]]
        self.songDelay = 0
        self.type = 0  #0 == päivä musiikit, 1 == yö musiikit, 2== boss battle, 3== main menu
        self.song = None
     

    def Play_music(self):
        if pygame.mixer.music.get_busy():
            return  

        self.songDelay += 0.1
        if not self.songDelay >= 10:
            return
            
        self.songDelay = 0 
        while True:
            song = choice(self.Musiikit[self.type])
            if self.song != song:
                break
        self.song = song
        pygame.mixer.music.load(os.path.join("Musiikit",self.song))
        pygame.mixer.music.set_volume(0.1)
        pygame.mixer.music.play()