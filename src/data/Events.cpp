#include "Events.h"

ofEvent<LayerAlpha> Events::LayerAlphaChange;
ofEvent<int> Events::ToggleObject;
ofEvent<DrawAreaState> Events::DrawAreaStateChange;
ofEvent<float>  Events::MixThresChange;
ofEvent<int> Events::Bang;
ofEvent<AudioVolume> Events::AudioVolumeChange;

ofEvent<BangStateObj> Events::ToggleBangStateObj;
ofEvent<BangStateLayer> Events::ToggleBangStateLayer;

ofEvent<int> Events::TogglePfx;