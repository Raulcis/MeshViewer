/*
 * @Author: Raul Cisneros
 * @Date:   9/13/2021
 */
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	cam.setAutoDistance(true);
	cam.setDistance(30.0);
	//cam.lookAt(glm::vec3(0, 0, 0));
	ofSetBackgroundColor(ofColor::black);

	countVertecies = 0; 
	countFaces = 0;

	// hard-coded triangle (can be commented out if needed)
	addVertices(glm::vec3(10, 0, 0));
	addVertices(glm::vec3(15, 0, 0));
	addVertices(glm::vec3(10, 5, 0));

	addFaces(Triangle(0, 1, 2));
	
	// hard-coded triangle (can be commented out if needed)
	addVertices(glm::vec3(5, 0, 0));
	addVertices(glm::vec3(10, 0, 0));
	addVertices(glm::vec3(10, 5, 0));

	addFaces(Triangle(3, 4, 5));
	
}



void ofApp::openFile(string filename1) {
	ifstream infile;
	string filename;
	string readCharacter;
	float num1, num2, num3;
	int Vert,Vert2,Vert3, TextureV, Normalv;

	infile.open(filename1);

	//this block of code not used since drag and drop feature is implemented
	while (!infile)  // check to see if the file is available if not error message is shown
	{
		cout << "Error opening the file." << endl;
		cout << "Please enter file name: " << endl;

		getline(cin, filename); //gets user response

		infile.open(filename.c_str()); //tries to open file
	}
	
	while (infile >> readCharacter) {//reads and stores any info found in the v lines
		if (readCharacter == "v") {
			infile.ignore();
			infile >> num1 >> num2 >> num3;

			addVertices(glm::vec3(num1, num2, num3));
		}
		else if (readCharacter == "vt") { //reads and stores any info found in the vt lines
			infile.ignore();
			infile >> num1 >> num2;

			vt.push_back(glm::vec2(num1, num2));
		}
		else if (readCharacter == "vn") {//reads and stores any info found in the vn lines

			infile.ignore();
			infile >> num1 >> num2 >> num3;

			vn.push_back(glm::vec3(num1, num2, num3));

		}else if (readCharacter == "f") { //reads and stores any info found in the f lines
			string string_buffer,one,two, three;
			int test;
			
			//ignores space
			infile.ignore();

			//gets first line in the file
			getline(infile, string_buffer);
			
			// used to parse read in line
			stringstream linestream(string_buffer);
				linestream >> one >> two >> three;
			
				//removes / symbols to facilitate parsing
				for (int i = 0; i < one.size(); i++) {
					if (one[i] == '/') {
						one[i] = ' ';
					}
				}
				// used to parse read in line
				stringstream linestream2(one);

				linestream2 >> Vert >> TextureV >> Normalv;

			//	cout << Vert << " " << TextureV << " " << Normalv << endl; used to print out read data

				// stores all file information in its proper vector just in case
				vertexIndecies.push_back(Vert);
				textIndecies.push_back(TextureV);
				normalIndecies.push_back(Normalv);

				//removes / symbols to facilitate parsing
				for (int i = 0; i < two.size(); i++) {
					if (two[i] == '/') {
						two[i] = ' ';
					}
				}

				// used to parse read in line
				stringstream linestream3(two);

				linestream3 >> Vert2 >> TextureV >> Normalv;

			//	cout << Vert2 << " " << TextureV << " " << Normalv << endl; used to print out read data

				// stores all file information in its proper vector just in case
				vertexIndecies.push_back(Vert2);
				textIndecies.push_back(TextureV);
				normalIndecies.push_back(Normalv);

				//removes / symbols to facilitate parsing
				for (int i = 0; i < three.size(); i++) {
					if (three[i] == '/') {
						three[i] = ' ';
					}
				}

				// used to parse read in line
				stringstream linestream4(three);

				linestream4 >> Vert3 >> TextureV >> Normalv;

			//	cout << Vert3 << " " << TextureV << " " << Normalv << endl; used to print out read data

				//creates a new triangle with read in vertices
				addFaces(Triangle(Vert-1, Vert2 -1, Vert3 -1));
				
				// stores all file information in its proper vector just in case
				vertexIndecies.push_back(Vert3);
				textIndecies.push_back(TextureV);
				normalIndecies.push_back(Normalv);

		}
		
	}
	infile.close();
	diagnostic();
}
//prints mesh info
void ofApp::diagnostic() {

	cout << "Number of vertices: " << countVertecies << endl;
	cout << "Number of Faces: " << countFaces << endl;
	cout << "Mesh Size: " << calcMeshSize() << " Kb" << endl;

}
//--------------------------------------------------------------
double ofApp::calcMeshSize() {
	//returns mesh size in kb
	return (sizeof Triangle * mesh.triangles.size() + sizeof mesh.verts[0] * mesh.verts.size()) /1000;
}

// adds new vertices to the verts vector and updates counter
void ofApp::addVertices(glm::vec3 newVec) {
		mesh.verts.push_back(newVec);
		countVertecies++;
}

// adds new triangle to the triangle vector and updates counter
void ofApp::addFaces(Triangle newTri) {
	mesh.triangles.push_back(newTri);
	countFaces++;
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::drawAxis() {
	//creates the axis
	ofSetColor(ofColor::green);
	ofDrawLine(glm::vec3(0, -10, 0), glm::vec3(0, 10, 0));
	ofSetColor(ofColor::red);
	ofDrawLine(glm::vec3(-10, 0, 0), glm::vec3(10, 0, 0));
	ofSetColor(ofColor::blue);
	ofDrawLine(glm::vec3(0, 0,-10), glm::vec3(0, 0, 10));
}
//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();
	drawAxis();

	//	ofDrawGrid();
	//	ofSetColor(0, 255, 0);  // red, green, blue components for RGB space

	//sets color of triangle 
	ofSetColor(ofColor::white);
	ofNoFill();

	//print out all triangles and their vertecies
	
	for (int i = 0; i < mesh.triangles.size(); i++) {
		ofDrawTriangle(mesh.verts[(mesh.triangles[i].vertInd[0])], mesh.verts[(mesh.triangles[i].vertInd[1])], mesh.verts[(mesh.triangles[i].vertInd[2])]);
	}
	
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {
	//used to be able to drag and drop a file
	if (dragInfo.files.size() > 0) {
		mesh.verts.clear();
		mesh.triangles.clear();
		openFile(dragInfo.files[0]);
	}

}
