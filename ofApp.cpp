#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetBackgroundAuto(false);

	ofSetLineWidth(1.5);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofColor color;
	auto size = 144;
	for (auto x = size * 0.5; x < ofGetWidth(); x += size) {

		for (auto y = size * 0.5; y < ofGetHeight(); y += size) {

			float noise_seed_1 = ofRandom(1000);
			float noise_seed_2 = ofRandom(1000);

			int start_param = ofMap(ofNoise(noise_seed_1, ofGetFrameNum() * 0.005), 0, 1, 0, 100);
			int end_param = start_param + ofMap(ofNoise(noise_seed_2, ofGetFrameNum() * 0.005), 0, 1, 25, 50);

			color.setHsb(((int)ofRandom(1000) + ofGetFrameNum() * 3) % 255, 180, 255);
			ofSetColor(color);

			vector<glm::vec2> vertices;
			for (int param = start_param; param < end_param; param++) {

				vertices.push_back(this->make_point(size * 0.95, param) + glm::vec2(x, y));
			}

			ofFill();
			ofSetColor(color);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(39);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);
		}
	}
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}