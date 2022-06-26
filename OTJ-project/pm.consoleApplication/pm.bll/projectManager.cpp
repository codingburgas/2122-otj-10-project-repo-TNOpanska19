#include "pch.h"
#include "projectManager.h"
#include "../pm.consoleApplication/projectsMenu.h"
#include "../pm.dal/userStore.h"
#include "../pm.dal/projectStore.h"


pm::bll::ProjectManager mProjectManager;
pm::dal::ProjectStore mProjectStore;
//pm::dal::UserStore mUserStore;
std::vector<pm::types::Project> projectList;

void pm::bll::ProjectManager::createProject(std::string title, std::string description, pm::types::User activeUser)
{
	pm::types::Project newProject;

	newProject.title = title;
	newProject.description = description;
	newProject.dateOfCreation = time(NULL);
	newProject.idOfCreator = activeUser.id;
	newProject.dateOfLastChange = time(NULL);
	newProject.idOfChange = activeUser.id;

	mProjectStore.createNewProject(newProject);

	projectsMenu::projectsManagementView(activeUser);
}
