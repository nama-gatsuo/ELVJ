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

		while (receiver.hasWaitingMessages()) {
			ofxOscMessage msg;
			receiver.getNextMessage(msg);

			std::string address = msg.getAddress();
			std::vector<std::string> dir = ofSplitString(address, "/");

			if (dir[1] == "audio") {
				
				if (dir[2] == "bang") {
					


				} else if (dir[2] == "vol") {
					
					dir[2] == "vol";
					volume = msg.getArgAsFloat(0);

				}

			} else if (dir[1] == "midi") {
				
				if (dir[2] == "ctrl") {
					

				} else if (dir[2] == "note") {
					
					// midi key assign	
				}

			} else if (dir[1] == "bin") {
				
				// for the objects in world
				DrawAreaState state;
				state.binId = std::stoi(dir[2]);
				state.layerId = msg.getArgAsInt(0);
				
				ofNotifyEvent(Events::DrawAreaStateChange, state);

				

			} else if (dir[1] == "layer") {
				if (dir[2] == "alpha") {

					int id = msg.getArgAsInt(0);
					float a = ofMap(msg.getArgAsInt(1), 2, 128, 0., 1.);
					
					LayerAlpha la(id, a);
					ofNotifyEvent(Events::LayerAlphaChange, la);
					
				}
			} else if (dir[1] == "mix") {
				
				if (dir[2] == "thres") {
					float thres = ofMap(msg.getArgAsInt(0), 1, 126, 0., 1.);
					ofNotifyEvent(Events::MixThresChange, thres);
				}

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