#include "pch.h"
#include <fstream>
#include <vector>
#include <string>
#include "teamStore.h"
#include "../pm.types/team.h"

void pm::dal::TeamStore::createNewTeam(pm::types::Team& team)
{
	std::ofstream file("../../data/Teams.txt", std::ios::in | std::ios::ate);

	file << team.id << ',' << team.title << ',' << team.dateOfCreation << ',' << team.idOfCreator <<
		',' << team.dateOfLastChange << ',' << team.idOfChange << ',';

	file << '\n';

	file.close();
}
