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

Eri spellTypet tekee paremmin damaa tiettyj� vihollisia / objekteja vastaan ja antavat eri abilityj�.
Esim wind vois antaa dashin tai double jumpi 

Forest antais healttia ja nopeutta.
Darkness damagee
Light armoria
water nopeutta ja damagee
fire damagee ja antaa palamis effectin eli ottaa damagee hetken aikaa ly�nnin j�lkeen.

*/


class ItemSpell
{
private:
	SpellType _spellType;
	//Spell type vaikuttaa staffin v�riin?
public:
	void setSpellType();
};