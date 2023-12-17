#ifndef SERVICE_BRANCH
#define SERVICE_BRANCH

#include "../others/Service.h"
extern LinkedList<Service> ServiceList;

void getServiceList();
void saveServiceList();
void ViewAllServices();
void CreateNewService();
void OpenExistService(bool manager = false);
std::string getServiceName(const std::string &);
int getServicePrice(const std::string &);
#endif