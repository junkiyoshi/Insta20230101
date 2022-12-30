#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);

	this->font_size = 40;
	ofTrueTypeFontSettings font_settings("fonts/msgothic.ttc", this->font_size);
	this->font.load(font_settings);

	this->words = {

		"2", "0", "2", "3",
	};

	for (int y = this->font_size * 12; y >= this->font_size * -12; y -= this->font_size * 1.2) {

		for (int x = this->font_size * -12; x <= this->font_size * 12; x += this->font_size * 0.8) {

			this->location_list.push_back(glm::vec2(x, y));
			this->index_list.push_back((int)ofRandom(this->words.size()));
			this->param_list.push_back(true);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	for (auto& param : this->param_list) {

		param = false;
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		auto y = ((int)((this->location_list[i].x + 1000) * 2 + ofGetFrameNum() * 20) % 1200) - 600;

		if (this->location_list[i].y > y - 60 && this->location_list[i].y < y + 60) {

			this->index_list[i] += ofRandom(1, 5);

			this->index_list[i] = (int)this->index_list[i] % this->words.size();
			this->param_list[i] = true;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofTranslate(this->font_size * 0.5, this->font_size * 0.5);
	ofRotate(330);

	ofColor color;

	for (int i = 0; i < this->location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->location_list[i]);

		if (this->param_list[i]) {

			ofRotateY(ofMap(ofNoise(this->location_list[i].y * 0.005, ofGetFrameNum() * 0.03), 0, 1, -3600, 3600));
		}

		if (i < this->location_list.size() - 4 &&
			this->words[this->index_list[i]] == "2" &&
			this->words[this->index_list[i + 1]] == "0" &&
			this->words[this->index_list[i + 2]] == "2" &&
			this->words[this->index_list[i + 3]] == "3") {

			color.setHsb(0, 200, 255);
			ofSetColor(color);
		}
		else if (i > 1 &&
			i < this->location_list.size() < 4 &&
			this->words[this->index_list[i - 1]] == "2" &&
			this->words[this->index_list[i]] == "0" &&
			this->words[this->index_list[i + 1]] == "2" &&
			this->words[this->index_list[i + 2]] == "3") {

			color.setHsb(64, 200, 255);
			ofSetColor(color);
		}
		else if (i > 2 &&
			i < this->location_list.size() < 4 &&
			this->words[this->index_list[i - 2]] == "2" &&
			this->words[this->index_list[i - 1]] == "0" &&
			this->words[this->index_list[i]] == "2" &&
			this->words[this->index_list[i + 1]] == "3") {
			
			color.setHsb(128, 200, 255);
			ofSetColor(color);
		}
		else if (i > 3 &&
			i < this->location_list.size() < 4 &&
			this->words[this->index_list[i - 3]] == "2" &&
			this->words[this->index_list[i - 2]] == "0" &&
			this->words[this->index_list[i - 1]] == "2" &&
			this->words[this->index_list[i]] == "3") {

			color.setHsb(192, 200, 255);
			ofSetColor(color);
		}
		else {

			ofSetColor(0);
		}

		this->font.drawString(this->words[this->index_list[i]], this->font_size * -0.25, this->font_size * -0.5);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}