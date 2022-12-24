from Entities.Enemies.Enemy import Enemy

class FallingRock(Enemy):
    def __init__(self, pos, maxRuudut, animate, col, kuva, width, height, display_surface, animationSpeed) -> None:
        super().__init__(pos, maxRuudut, animate, col, kuva,
                         width, height, display_surface, animationSpeed)