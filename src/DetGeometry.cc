//Вариант 1
//
//Реализовать геометрию со следующими параметрами:
//Расположить в плоскости XZ G4Cons G4Para и G4Tubs по вершинам вписанного в окружность равностороннего треугольника
//в плоскости Y фигуры должны распологаться одна над другой (начиная с G4Cons заканчивая G4Tubs)


#include <G4Box.hh>
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

    G4Cons* con = new G4Cons ("conus", 20 *cm, 40 *cm, 10 *cm, 20 *cm, 50 *cm, 0, pi);
    G4Tubs* tube = new G4Tubs ("tube", 20 *cm, 40 *cm, 50 *cm, 0, pi/2);
    G4Para* para = new G4Para ("para", 20 *cm, 20 *cm, 20 *cm, pi/3, pi/3, pi/3);

    G4LogicalVolume* conus2 = new G4LogicalVolume (con, c_material, "mat_cone");
    G4LogicalVolume* tube2 = new G4LogicalVolume (tube, c_material, "mat_tube");
    G4LogicalVolume* para2 = new G4LogicalVolume (para, c_material, "mat_para");

    G4VPhysicalVolume* conus = new G4PVPlacement (0, G4ThreeVector(-250 *cm,0,0), conus2, "cons1",logicWorld,false,0);
    G4VPhysicalVolume* tubes = new G4PVPlacement (0, G4ThreeVector(0,250 *cm,500 *cm), tube2, "tube1",logicWorld,false,0);
    G4VPhysicalVolume* paras = new G4PVPlacement (0, G4ThreeVector(250 *cm,500*cm,0), para2, "para1",logicWorld,false,0);


    return physWorld;
}


