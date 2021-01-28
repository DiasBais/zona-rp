stock IsAPistol(gunid)
{
	if(gunid >= 22 && gunid <=24) { return true; }
	return false;
}
stock IsAMelee(gunid)
{
	if(gunid >= 2 && gunid <= 9 ) { return true; }
	return false;
}
stock IsAGirlsStuff(gunid)
{
	if(gunid >= 10 && gunid <= 15 || gunid == 46) { return true; }
	return false;
}
stock IsAGrenade(gunid)
{
	if((gunid >= 16 && gunid <= 18) || gunid == 39) { return true; }
	return false;
}
stock IsAShotgun(gunid)
{
	if(gunid >= 25 && gunid <= 27) { return true; }
	return false;
}
stock IsAMachineGun(gunid)
{
	if(gunid == 28 || gunid == 29 || gunid == 32) { return true; }
	return false;
}
stock IsAnAssault(gunid)
{
	if(gunid == 30 || gunid == 31) { return true; }
	return false;
}
stock IsARifle(gunid)
{
	if(gunid == 33 || gunid == 34) { return true; }
	return false;
}
stock IsAHeavyAssault(gunid)//базуки
{
	if(gunid >= 35 && gunid <= 37 ) { return true; }
	return false;
}
stock IsAStuff1(gunid)//Баллончик
{
	if(gunid >= 41 && gunid <= 43 ) { return true; }
	return false;
}

stock GiveRichGun(playerid,weaponid,ammo)
{
	PyxiTime[playerid] = 5;
	if(IsAPistol(weaponid))
	{
		PlayerInfo[playerid][pSlot2] = weaponid;
		PlayerInfo[playerid][pSlotammo2] += ammo;
	}
	else if(IsAShotgun(weaponid))
	{
		PlayerInfo[playerid][pSlot3] = weaponid;
		PlayerInfo[playerid][pSlotammo3] += ammo;
	}
	else if(IsAMachineGun(weaponid))
	{
		PlayerInfo[playerid][pSlot4] = weaponid;
		PlayerInfo[playerid][pSlotammo4] += ammo;
	}
	else if(IsAnAssault(weaponid))
	{
		PlayerInfo[playerid][pSlot5] = weaponid;
		PlayerInfo[playerid][pSlotammo5] += ammo;
	}
	else if(IsARifle(weaponid))
	{
		PlayerInfo[playerid][pSlot6] = weaponid;
		PlayerInfo[playerid][pSlotammo6] += ammo;
	}
	else if(IsAHeavyAssault(weaponid))
	{
		PlayerInfo[playerid][pSlot7] = weaponid;
		PlayerInfo[playerid][pSlotammo7] += ammo;
	}
	else if(IsAHeavyAssault(weaponid))
	{
		PlayerInfo[playerid][pSlot7] = weaponid;
		PlayerInfo[playerid][pAmmo7] += ammo;
	}
	else if(IsAGrenade(weaponid))
	{
		PlayerInfo[playerid][pSlot8] = weaponid;
		PlayerInfo[playerid][pSlotammo8] += ammo;
	}
	else if(IsAStuff1(weaponid))
	{
		PlayerInfo[playerid][pSlot9] = weaponid;
		PlayerInfo[playerid][pSlotammo9] += ammo;
	}
	else if(IsAGirlsStuff(weaponid))
	{
		PlayerInfo[playerid][pSlot10] = weaponid;
		PlayerInfo[playerid][pSlotammo10] += ammo;
	}
	GiveWeapon(playerid,weaponid,ammo);
	return true;
}
