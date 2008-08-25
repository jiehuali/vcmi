#define VCMI_DLL
#include "../stdafx.h"
#include "CArtHandler.h"
#include "CLodHandler.h"
#include <boost/assign/std/vector.hpp>
#include <boost/assign/list_of.hpp>
#include "../lib/VCMI_Lib.h"
extern CLodHandler *bitmaph;
using namespace boost::assign;
CArtHandler::CArtHandler()
{
	VLC->arth = this;
}
void CArtHandler::loadArtifacts()
{
	std::vector<ui16> slots;
	slots += 17, 16, 15,14,13, 18, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0;
	std::map<char,EartClass> classes = 
	  map_list_of('S',SartClass)('T',TartClass)('N',NartClass)('J',JartClass)('R',RartClass);
	std::string buf = bitmaph->getTextFile("ARTRAITS.TXT"), dump, pom;
	int it=0;
	for(int i=0; i<2; ++i)
	{
		loadToIt(dump,buf,it,3);
	}
	for (int i=0; i<ARTIFACTS_QUANTITY; i++)
	{
		CArtifact nart;
		loadToIt(nart.name,buf,it,4);
		loadToIt(pom,buf,it,4);
		nart.price=atoi(pom.c_str());
		for(int j=0;j<slots.size();j++)
		{
			loadToIt(pom,buf,it,4);
			if(pom[0]=='x')
				nart.possibleSlots.push_back(slots[j]);
		}
		loadToIt(pom,buf,it,4);
		nart.aClass = classes[pom[0]];
		loadToIt(nart.description,buf,it,3);
		nart.id=i;
		artifacts.push_back(nart);
	}
	for(int i=0;i<144;i++) //do 144, bo nie chcemy bzdurek
	{
		switch (artifacts[i].aClass)
		{
		case TartClass:
			treasures.push_back(&(artifacts[i]));
			break;
		case NartClass:
			minors.push_back(&(artifacts[i]));
			break;
		case JartClass:
			majors.push_back(&(artifacts[i]));
			break;
		case RartClass:
			relics.push_back(&(artifacts[i]));
			break;
		}
	}
}
