#pragma once
#include "ofxOsc.h"
#include "Events.h"

// Singleton obeject (global and only one) to collect OSC from the Max Controller
class DataListener {
public:
	static DataListener& instance() {
		static DataListener* listener = new DataListener();
		return *listener;
	}

	void update() {

		while (receiver.isListening()) {
			ofxOscMessage msg;
			receiver.getNextMessage(msg);

			std::string address = msg.getAddress();
			std::vector<std::string> dir = ofSplitString(address, "/");

			if (dir[1] == "audio") {
				
				if (dir[2] == "bang") {
				


				} else if (dir[2] == "vol") {
					volume = msg.getArgAsFloat(0);
				}

			} else if (dir[1] == "layer") {
				
				int id = std::stoi(dir[2]);
				float a = msg.getArgAsFloat(0);
				ofNotifyEvent(Events::LayerAlphaChange, LayerAlpha(id, a));

			} else if (dir[1] == "obj") {
				
				int id = std::stoi(dir[2]);
				ofNotifyEvent(Events::ToggleObject, id);

			}

		}
	
	}

private:
	DataListener() {
		receiver.setup(7401);
	}

	ofxOscReceiver receiver;
	float volume;


};