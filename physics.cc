#include "physics.hh"

MyPhysicsList::MyPhysicsList()
{

	//decay physics
        //RegisterPhysics(new G4DecayPhysics());


	 //hadronic physics
        //RegisterPhysics(new G4HadronPhysicsFTFP_BERT());
        
        
         //ion physics
       // RegisterPhysics(new G4IonPhysics());
        
        
        
	RegisterPhysics (new G4EmStandardPhysics());
	//RegisterPhysics (new FTFP_BERT_EMV());
	//RegisterPhysics (new QGSP_BIC_EMY());
	//RegisterPhysics (new G4OpticalPhysics());	

}

MyPhysicsList::~MyPhysicsList()
{}
