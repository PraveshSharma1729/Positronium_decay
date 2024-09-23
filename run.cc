#include "run.hh"
#include <sstream>

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
G4AnalysisManager *man = G4AnalysisManager::Instance();

man->OpenFile("1.02MeV.root");

man->CreateNtuple("E_Dep","E_Dep");
for (G4int i =0; i<200;i++){
std::string Name = "Crystal_CopyNumber" + std::to_string(i);
man->CreateNtupleDColumn(Name);
}
man->FinishNtuple(0);

man->CreateNtuple("Resolution","Resolution");
man->CreateNtupleDColumn("Resolution_with_1.02MeV_photon");
man->FinishNtuple(1);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
G4AnalysisManager *man = G4AnalysisManager::Instance();

man->Write();

man->CloseFile();

}

