/*
 * @Author: Raul Cisneros
 * @Date:   9/13/2021
 */
#pragma once

#include "ofMain.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>

class Triangle {
public:
	Triangle(int i1, int i2, int i3) { vertInd[0] = i1, vertInd[1] = i2, vertInd[2] = i3; }
	int vertInd[3];
};

class MyMesh {
public:
	vector<glm::vec3> verts;
	vector<Triangle> triangles;
};


class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void drawAxis();
	void openFile(string filename1);
	void diagnostic();
	void addVertices(glm::vec3 newVec);
	void addFaces(Triangle newTri);
	double calcMeshSize();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	vector<ofImage> image;
	ofEasyCam cam;

	int countVertecies, countFaces;

	//used to store texture and normal info
	vector<glm::vec2> vt;
	vector<glm::vec3> vn;

	//vectors used to store all info read from file just in case
	vector<int> vertexIndecies;
	vector<int> textIndecies;
	vector<int> normalIndecies;

	MyMesh mesh;

};
