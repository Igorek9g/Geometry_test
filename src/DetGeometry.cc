//Вариант 1
//
//Реализовать геометрию со следующими параметрами:
//Расположить в плоскости XZ G4Cons G4Para и G4Tubs по вершинам вписанного в окружность равностороннего треугольника
//в плоскости Y фигуры должны распологаться одна над другой (начиная с G4Cons заканчивая G4Tubs)


#include <G4Box.hh>
#include <G4AssemblyVolume.hh>
#include <G4SubtractionSolid.hh>
#include "DetGeometry.hh"

DetGeometry::DetGeometry() {
    world_sizeXYZ   = 100 * m;
    nist            = G4NistManager::Instance();
    world_mat       = nist->FindOrBuildMaterial("G4_AIR");
    solidWorld      = new G4Box("solWorld", 0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);
    logicWorld      = new G4LogicalVolume(solidWorld, world_mat, "logWorld");
    physWorld       = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "phyWorld", 0, false, 0);

    G4cout<<"Geometry of detector is build successfully\t\t\t\t\t\tOK!!!"<<G4endl;
}

DetGeometry::~DetGeometry() {}

G4VPhysicalVolume* DetGeometry::Construct(){
    G4Material* c_material = nist->FindOrBuildMaterial("G4_Fe");
    G4Material* p_material = nist->FindOrBuildMaterial("G4_ALANINE");
    G4Material* t_material = nist->FindOrBuildMaterial("G4_ANTHRACENE");

//G4Cons* con = new G4Cons ("conus", 20 *cm, 40 *cm, 10 *cm, 20 *cm, 50 *cm, 0, pi);
    G4Box* cube = new G4Box ("cube", 100*cm, 100 *cm, 100*cm);
    G4Tubs* tube = new G4Tubs ("tube", 0 *cm, 50 *cm, 200 *cm, 0, pi*2);
    //G4Tubs* tube2 = new G4Tubs ("tube", 0 *cm, 70 *cm, 200 *cm, 0, pi*2);
    //G4Tubs* tube3 = new G4Tubs ("tube", 0 *cm, 70 *cm, 200 *cm, 0, pi*2);



    //G4Tubs* res2 = new G4Tubs ("tube", 0 *cm, 120 *cm, 20 *cm, 0, pi*2);
    //G4Para* para = new G4Para ("para", 20 *cm, 20 *cm, 20 *cm, pi/3, pi/3, pi/3);

    G4RotationMatrix* RM1 = new G4RotationMatrix (0, pi/2,0);
    G4RotationMatrix* RM2 = new G4RotationMatrix (pi/2, pi/2, 0);

    G4SubtractionSolid* part = new G4SubtractionSolid ("part", cube, tube, 0, G4ThreeVector());
    part = new G4SubtractionSolid ("part", part, tube, RM1, G4ThreeVector());
    part = new G4SubtractionSolid ("part", part, tube, RM2, G4ThreeVector());


    G4LogicalVolume* assy = new G4LogicalVolume (part, c_material, "smth");
    for(int i=0; i<5; i++)
        for (int j=0; j<5; j++)
        {
            {
                G4RotationMatrix *RMtmp = new G4RotationMatrix(pi/24*i*j, -pi/16*i, pi / 16 * j);
                new G4PVPlacement(RMtmp, G4ThreeVector(300 * i * cm, 300*j *cm, 0), assy, "assy", logicWorld, false, 0);
            }
        }
    //new G4PVPlacement (0, G4ThreeVector(), assy, "assy",logicWorld,false,0);


   // G4LogicalVolume* conus2 = new G4LogicalVolume (con, c_material, "mat_cone");
/*    G4LogicalVolume* tube2 = new G4LogicalVolume (tube, c_material, "mat_tube");
    G4LogicalVolume* res2 = new G4LogicalVolume (res, c_material, "mat_tube");
   // G4LogicalVolume* para2 = new G4LogicalVolume (para, c_material, "mat_para");

    G4AssemblyVolume* tubs = new G4AssemblyVolume();
    G4ThreeVector vect(0,0,275*cm);
    tubs->AddPlacedVolume(tube2, vect,0);
    G4ThreeVector vect2(0,0,0);
    tubs->AddPlacedVolume(res2, vect2,0);

    tubs->MakeImprint(logicWorld, vect2,0,0,false);

    G4ThreeVector vect3(0,0,-500*cm);
    tubs->MakeImprint(logicWorld, vect3,new G4RotationMatrix(0,pi,0),0,false);*/

  //  G4VPhysicalVolume* conus = new G4PVPlacement (0, G4ThreeVector(-250 *cm,0,0), conus2, "cons1",logicWorld,false,0);
 /*   G4VPhysicalVolume* tubes = new G4PVPlacement (0, G4ThreeVector(), tube2, "tube1",logicWorld,false,0);
    G4VPhysicalVolume* res3 = new G4PVPlacement (0, G4ThreeVector(), res2, "tube1",logicWorld,false,0);
 */  // G4VPhysicalVolume* paras = new G4PVPlacement (0, G4ThreeVector(250 *cm,500*cm,0), para2, "para1",logicWorld,false,0);


    return physWorld;
}


