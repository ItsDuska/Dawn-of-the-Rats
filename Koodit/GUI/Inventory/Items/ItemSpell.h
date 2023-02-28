#pragma once

enum SpellType
{
	WATER,
	FOREST,
	DARKNESS,
	LIGHT,
	FIRE,
	WIND,

};

/*

Eri spellTypet tekee paremmin damaa tiettyjä vihollisia / objekteja vastaan ja antavat eri abilityjä.
Esim wind vois antaa dashin tai double jumpi 

Forest antais healttia ja nopeutta.
Darkness damagee
Light armoria
water nopeutta ja damagee
fire damagee ja antaa palamis effectin eli ottaa damagee hetken aikaa lyönnin jälkeen.

*/


class ItemSpell
{
private:
	SpellType _spellType;
	//Spell type vaikuttaa staffin väriin?
public:
	void setSpellType();
};