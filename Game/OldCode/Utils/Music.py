import pygame
from os import path
from random import choice

"""
Class that can play music or play sound
"""
class Music:
    __slots__ = "musics", "songDelay", "type", "song"

    def __init__(self) -> None:
        self.musics = [["Flower_Solo.mp3", "Peace_In_The_Meadows.mp3", "Field_Of_The_Wild.mp3", "Hearth_Of_The_Kingdom1.mp3", "Chorus_Wheat.mp3", "Rats_Behold.mp3"],
                         ["Flowers_In_The_Moon_Light.mp3", "Night_Charm.mp3"],
                         ["Bells_Of_Wisdom.mp3", "Moon_Bell.mp3"], ["Cosmic_star.mp3", "Space_Vortex.mp3"]]
        self.songDelay = 0
        self.type = 0  # 0 == päivä musiikit, 1 == yö musiikit, 2== boss battle, 3== main menu
        self.song = None
        #self.firstMute = False

    def playMusic(self,mute):
        return
        if mute:
            pygame.mixer.music.fadeout(50)
            return

        if pygame.mixer.music.get_busy():
            return

        self.songDelay += 0.1
        if self.songDelay < 10:
            return

        self.songDelay = 0
        while True:
            song = choice(self.musics[self.type])
            if self.song != song:
                break
        self.song = song
        pygame.mixer.music.load(path.join("Musiikit", self.song))
        pygame.mixer.music.set_volume(0.05)
        pygame.mixer.music.play()


    def playSound(self,soundPath):
        print(path.join("Musiikit",soundPath))
        sound = pygame.mixer.Sound(path.join("Musiikit",soundPath))
        if pygame.mixer.Sound.get_num_channels(sound) >= 1:
            return
        pygame.mixer.Sound.play(sound)
