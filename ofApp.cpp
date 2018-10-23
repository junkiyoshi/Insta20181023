#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	this->number_of_targets = 60;
	for (int i = 0; i < this->number_of_targets; i++) {

		this->targets1.push_back(glm::vec2());
		this->targets2.push_back(glm::vec2());
	}

	this->shader.load("shader/shader.vert", "shader/shader.frag");
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	float radius = 250;
	for (int i = 0; i < this->number_of_targets; i++) {

		int deg = i * 3 + 90;
		ofPoint point = ofPoint(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));

		float noise_value = ofNoise(deg * 0.03, ofGetFrameNum() * 0.008);
		float x_param = 0;
		if (noise_value > 0.75) {

			x_param = ofMap(noise_value, 0.75, 1.0, 0, 150);
		}
		else if (noise_value < 0.25) {

			x_param = ofMap(noise_value, 0.25, 0.0, 0, -150);
		}

		this->targets1[i] = glm::vec2(point.x + x_param + ofGetWidth() * 0.5, point.y + ofGetHeight() * 0.5);
		this->targets2[i] = glm::vec2(-point.x + x_param + ofGetWidth() * 0.5, point.y + ofGetHeight() * 0.5);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform2fv("targets1", &this->targets1[0].x, this->number_of_targets);
	this->shader.setUniform2fv("targets2", &this->targets2[0].x, this->number_of_targets);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}