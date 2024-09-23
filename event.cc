#include "event.hh"
#include "G4SystemOfUnits.hh"
#include <chrono>
#include "Randomize.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
	fEdep = 0.;	
	for (G4int i = 0; i < 200; ++i) {
        fEdep0[i] = 0.;
    }
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
	
	// Set a new random seed based on the current system time
  	long seeds[2];
  	auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
  	seeds[0] = std::chrono::duration_cast<std::chrono::seconds>(now).count();
  	seeds[1] = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();
  	CLHEP::HepRandom::setTheSeeds(seeds);
	
	
	fEdep = 0.;	
	for (G4int i = 0; i < 200; ++i) {
        fEdep0[i] = 0.;
        }
}

void MyEventAction::EndOfEventAction(const G4Event*)
{
G4AnalysisManager *man = G4AnalysisManager::Instance();
G4double En;
G4double Eg = 1.02*MeV;
for (G4int i =0;i<200;i++){
man->FillNtupleDColumn(0, i, fEdep0[i]);
//G4cout<<"fEdep0[i] "<<i<<" "<<fEdep0[i]<<G4endl;
En = En + fEdep0[i];
}
G4cout<<En<<G4endl;
man->AddNtupleRow(0);

G4double Res = (En-Eg)/Eg;
man->FillNtupleDColumn(1, 0, Res);
man->AddNtupleRow(1);
}


void MyEventAction::AddEdep0(G4int copyNo, G4double edep) {
//for (G4int i=0;i<200;i++){
  //  if (copyNo >= 0 && copyNo < 200) {
        fEdep0[copyNo] += edep; // Store energy deposition in corresponding array element
        // G4cout<<"Check	"<<copyNo<<"  "<<"	"<<fEdep0[copyNo]<<G4endl; 
    //}
    
    
    //}
    
}

