#pragma once
#include "Header.h"
#include "MediaClasses.h"

MediaBase* mediaType();
void addMedia(vector<MediaBase*>& vec);
void deleteMedia(vector<MediaBase*>& vec);
void editMedia(vector<MediaBase*>& vec);