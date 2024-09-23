#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
  G4NistManager *nist = G4NistManager::Instance();

  G4Material *worldMat =nist->FindOrBuildMaterial("G4_Galactic");

  G4Material* BGO = new G4Material("BGO",7.10*g/cm3,3);
  BGO->AddElement(nist->FindOrBuildElement("O"),12);
  BGO->AddElement(nist->FindOrBuildElement("Ge"),3);
  BGO->AddElement(nist->FindOrBuildElement("Bi"),4);
  
  G4Box *solidWorld = new G4Box("solidWorld",20.0*m,20.0*m,20.0*m);
  G4LogicalVolume *logicWorld = new G4LogicalVolume( solidWorld, worldMat, "logicWorld");
  G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicWorld, "physWorld", 0, false, 0, true);
  
  // Defining Logic volume for Silicon sensors
  G4Box *solidDetector = new G4Box("solidDetector", 7.5/2*mm,7.5/2*mm,15/2*cm);
  logicDetector = new G4LogicalVolume(solidDetector, BGO, "logicDetector");
  
     // Set visualization attributes
    /*G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0)); // Blue color
    logicDetector->SetVisAttributes(visAttributes);*/
  //fScoringVolume = logicDetector;
		
  G4Box *solidDetector0 = new G4Box("solidDetector0", 7.5/2*mm,7.5/2*mm,5/2*cm);
  logicDetector0 = new G4LogicalVolume(solidDetector0, BGO, "logicDetector0");
  		
		
  for (G4int i=0;i<14;i++){
    for (G4int j=0;j<14;j++){
      G4int copyN = i*14+j;
      if(copyN==90|| copyN ==91 || copyN==104|| copyN==105){
        G4VPhysicalVolume *physDetector0 = new G4PVPlacement(0,G4ThreeVector(i*7.5*mm-6.5*7.5*mm,j*7.5*mm-6.5*7.5*mm,5*cm),logicDetector0,"physDetector0",logicWorld,false,copyN,true);
        G4int a = copyN/14;
        G4int b = copyN%14;
     physDetector0 = new G4PVPlacement(0,G4ThreeVector(i*7.5*mm-6.5*7.5*mm,j*7.5*mm-6.5*7.5*mm,-5.0*cm),logicDetector0,"physDetector0",logicWorld,false,196+(a-6)*2+(b-6),true);
        }
      else {
        G4VPhysicalVolume *physDetector = new G4PVPlacement(0,G4ThreeVector(i*7.5*mm-6.5*7.5*mm,j*7.5*mm-6.5*7.5*mm,0),logicDetector,"physDetector",logicWorld,false,copyN,true);
          }
                            }
                      }
  return physWorld;
}

void MyDetectorConstruction :: ConstructSDandField()
{
  MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
  G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
  logicDetector->SetSensitiveDetector(sensDet);
    G4cout<<"check1"<<G4endl;
   //MySensitiveDetector *sensDet0 = new MySensitiveDetector("SensitiveDetector0");
  logicDetector0->SetSensitiveDetector(sensDet);
 G4cout<<"check2"<<G4endl;
   
}

