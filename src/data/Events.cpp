#include "Events.h"

ofEvent<LayerAlpha> Events::LayerAlphaChange;
ofEvent<int> Events::ToggleObject;
ofEvent<DrawAreaState> Events::DrawAreaStateChange;
ofEvent<float>  Events::MixThresChange;